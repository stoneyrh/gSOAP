/*      tcpclient.cpp

        Transfer XML over TCP/IP

        Build steps:

        soapcpp2 tcpdemo.h
        c++ -o tcpclient tcpclient.cpp soapC.cpp soapClient.cpp stdsoap2.cpp

        Copyright (C) 2000-2023 Robert A. van Engelen, Genivia, Inc.
        All Rights Reserved.

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2001-2023, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soaptcpdemoProxy.h"
#include "tcpdemo.nsmap"

static const char *server = "localhost:8080"; // plain TCP/IP, no HTTP

int main()
{
  // SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed
  // SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP
  tcpdemoProxy proxy(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  ns__ClientData client_data;
  ns__ServerData server_data;

  // enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes:
  // signal(SIGPIPE, SIG_IGN);

  // set sensible timeouts

  proxy.soap->connect_timeout = 5;
  proxy.soap->transfer_timeout = 5;
  proxy.soap->recv_timeout = 3;
  proxy.soap->send_timeout = 3;

  // two-way send and receive XML with soap_call_...

  client_data.id = 1;
  client_data.client_message = "Hello";
  std::cout << "Client: " << client_data.client_message << '\n';

  if (proxy.echo(server, NULL, &client_data, &server_data) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }
  else
  {
    if (server_data.server_message)
      std::cout << "Server: " << server_data.server_message << '\n';
  }

  // one-way send XML with soap_send_... followed by one-way receive XML with soap_recv_...

  client_data.id = 2;
  client_data.client_message = "Hello again";
  std::cout << "Client: " << client_data.client_message << '\n';

  if (proxy.send_echo(server, NULL, &client_data) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }
  else if (proxy.recv_echo(&server_data) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }
  else
  {
    std::cout << "Server: " << server_data.server_message << '\n';
  }

  // one-way send XML with soap_send_... followed by multiple one-way receive XML with soap_recv_...

  client_data.id = 3;
  client_data.client_message = "Hello want more";
  std::cout << "Client: " << client_data.client_message << '\n';

  if (proxy.send_more(server, NULL, &client_data) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }
  else
  {
    ns__data data;
    while (proxy.recv_data(data) == SOAP_OK)
    {
      if (data._param_1 == NULL || data._param_1->server_message == NULL)
        break;
      std::cout << "Server: " << data._param_1->server_message << '\n';
    }
  }

  // one-way send XML to say goodbye

  std::cout << "Client: Bye\n";

  if (proxy.send_bye(server, NULL) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }

  // disable keep-alive, then close the socket

  proxy.soap->keep_alive = 0;
  proxy.soap_close_socket();

  // cleanup

  proxy.destroy();
}
