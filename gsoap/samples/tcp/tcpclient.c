/*      tcpclient.c

        Transfer XML over TCP/IP

        Build steps:

        soapcpp2 -c tcpdemo.h
        cc -o tcpclient tcpclient.c soapC.c soapClient.c stdsoap2.c

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

#include "soapH.h"
#include "tcpdemo.nsmap"

static const char *server = "localhost:8080"; /* plain TCP/IP, no HTTP */

int main()
{
  /* SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed */
  /* SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP */
  struct soap *soap = soap_new1(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  struct ns__ClientData client_data;
  struct ns__ServerData server_data;

  /* enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes: */
  /* signal(SIGPIPE, SIG_IGN); */

  /* set sensible timeouts */

  soap->connect_timeout = 5;
  soap->transfer_timeout = 5;
  soap->recv_timeout = 3;
  soap->send_timeout = 3;

  /* two-way send and receive XML with soap_call_... */

  client_data.id = 1;
  client_data.client_message = "Hello";
  printf("Client: %s\n", client_data.client_message);

  if (soap_call_ns__echo(soap, server, NULL, &client_data, &server_data) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
  }
  else
  {
    if (server_data.server_message)
      printf("Server: %s\n", server_data.server_message);
  }

  /* one-way send XML with soap_send_... followed by one-way receive XML with soap_recv_... */

  client_data.id = 2;
  client_data.client_message = "Hello again";
  printf("Client: %s\n", client_data.client_message);

  if (soap_send_ns__echo(soap, server, NULL, &client_data) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
  }
  else if (soap_recv_ns__echo(soap, &server_data) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
  }
  else
  {
    printf("Server: %s\n", server_data.server_message);
  }

  /* one-way send XML with soap_send_... followed by multiple one-way receive XML with soap_recv_... */

  client_data.id = 3;
  client_data.client_message = "Hello want more";
  printf("Client: %s\n", client_data.client_message);

  if (soap_send_ns__more(soap, server, NULL, &client_data) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
  }
  else
  {
    struct ns__data data;
    while (soap_recv_ns__data(soap, &data) == SOAP_OK)
    {
      if (data._param_1 == NULL || data._param_1->server_message == NULL)
        break;
      printf("Server: %s\n", data._param_1->server_message);
    }
  }

  /* one-way send XML to say goodbye */

  printf("Client: Bye\n");

  if (soap_send_ns__bye(soap, server, NULL) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
  }

  /* disable keep-alive, then close the socket */

  soap->keep_alive = 0;
  soap_closesock(soap);

  /* cleanup */

  soap_destroy(soap);
  soap_end(soap);
  soap_free(soap);
}
