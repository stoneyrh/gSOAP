/*      tcpserver.cpp

        Transfer XML over TCP/IP
        Simple iterative server; see gSOAP documentation to implement threaded server

        Build steps:

        soapcpp2 -j tcpdemo.h
        c++ -o tcpserver tcpserver.cpp soapC.cpp soaptcpdemoService.cpp soaptcpdemoProxy.cpp stdsoap2.cpp

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

#include "soaptcpdemoService.h"
#include "soaptcpdemoProxy.h" // tcpdemoService::more() uses tcpdemoProxy.send_data()
#include "tcpdemo.nsmap"

int main()
{
  // SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed
  // SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP
  tcpdemoService service(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  SOAP_SOCKET m, s;

  // enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes:
  // signal(SIGPIPE, SIG_IGN);
  
  // reuse port immediately
  service.soap->bind_flags = SO_REUSEADDR;

  m = service.bind(NULL, 8080, 2);
  if (!soap_valid_socket(m))
  {
    service.soap_stream_fault(std::cerr);
    exit(EXIT_FAILURE);
  }

  std::cout << "Socket connection successful " << m << '\n';

  // set sensible timeouts to protect the server

  service.soap->accept_timeout = 60;
  service.soap->transfer_timeout = 5;
  service.soap->recv_timeout = 3;
  service.soap->send_timeout = 3;

  // keep alive forever potentially, no run-down counter

  service.soap->max_keep_alive = 0;

  // accept connection and serve it while the connection stays open

  s = service.accept();
  if (!soap_valid_socket(s))
  {
    service.soap_stream_fault(std::cerr);
  }
  else if (service.serve() != SOAP_OK)
  {
    if (service.soap->errnum)
      service.soap_stream_fault(std::cerr);
    else
      std::cout << "Server timed out\n";
  }

  service.destroy();

  return 0;
}

// echo client's message
int tcpdemoService::echo(ns__ClientData *client_data, ns__ServerData *server_data)
{
  size_t alloc;

  if (client_data->client_message == NULL)
    client_data->client_message = "";

  std::cout << "Client echo " << client_data->id << ": " << client_data->client_message << '\n';

  alloc = strlen(client_data->client_message) + 6;
  server_data->id = client_data->id;
  server_data->server_message = (char*)soap_malloc(soap, alloc);
  snprintf((char*)server_data->server_message, alloc, "ECHO %s", client_data->client_message);
  return SOAP_OK;
}

// the client requests more data
int tcpdemoService::more(ns__ClientData *client_data)
{
  int i;
  struct ns__ServerData *server_data = soap_new_ns__ServerData(this->soap, -1);
  size_t alloc;

  if (client_data->client_message == NULL)
    client_data->client_message = "";

  std::cout << "Client more " << client_data->id << ": " << client_data->client_message << '\n';

  alloc = strlen(client_data->client_message) + 32;
  server_data->id = client_data->id;
  server_data->server_message = (char*)soap_malloc(soap, alloc);

  // use some kind of magic here: we create a temporary proxy object to send data over TCP/IP
  // we want this proxy object to inherit the service 'soap' context settings and connection

  tcpdemoProxy proxy(this->soap);

  for (i = 1; i <= 3; ++i)
  {
    snprintf((char*)server_data->server_message, alloc, "ECHO %d %s", i, client_data->client_message);
    if (proxy.send_data(NULL, NULL, server_data) != SOAP_OK)
      break;
  }
  return proxy.send_data(NULL, NULL, NULL);
}

// dummy server operation, never called but defined because it is declared in tcpdemo.h
int tcpdemoService::data(ns__ServerData *)
{
  return SOAP_NO_METHOD;
}

// end the conversation
int tcpdemoService::bye()
{
  std::cout << "Bye\n";

  // disable keep-alive to end the soap_serve() loop and close the socket (resetting SOAP_KEEPALIVE is not sufficient)
  this->soap->keep_alive = 0;

  return SOAP_OK;
}
