/*      tcpserver.c

        Transfer XML over TCP/IP
        Simple iterative server; see gSOAP documentation to implement threaded server

        Build steps:

        soapcpp2 -c tcpdemo.h
        cc -o tcpserver tcpserver.c soapC.c soapServer.c soapClient.c stdsoap2.c

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

int main()
{
  /* SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed */
  /* SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP */
  struct soap *soap = soap_new1(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  SOAP_SOCKET m, s;

  /* enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes: */
  /* signal(SIGPIPE, SIG_IGN); */
  
  /* reuse port immediately */
  soap->bind_flags = SO_REUSEADDR;

  m = soap_bind(soap, NULL, 8080, 2);
  if (!soap_valid_socket(m))
  {
    soap_print_fault(soap, stderr);
    exit(EXIT_FAILURE);
  }

  printf("Socket connection successful %d\n", m);

  /* set sensible timeouts to protect the server */

  soap->accept_timeout = 60;
  soap->transfer_timeout = 5;
  soap->recv_timeout = 3;
  soap->send_timeout = 3;

  /* keep alive forever potentially, no run-down counter */

  soap->max_keep_alive = 0;

  /* accept connection and serve it while the connection stays open */

  s = soap_accept(soap);
  if (!soap_valid_socket(s))
  {
    soap_print_fault(soap, stderr);
  }
  else if (soap_serve(soap) != SOAP_OK)
  {
    if (soap->errnum)
      soap_print_fault(soap, stderr);
    else
      fprintf(stderr, "Server timed out\n");
  }

  soap_destroy(soap);
  soap_end(soap);
  soap_free(soap);

  return 0;
}

/* echo client's message */
int ns__echo(struct soap *soap, struct ns__ClientData *client_data, struct ns__ServerData *server_data)
{
  size_t alloc;

  if (client_data->client_message == NULL)
    client_data->client_message = "";

  printf("Client echo %d: %s\n", client_data->id, client_data->client_message);

  alloc = strlen(client_data->client_message) + 6;
  server_data->id = client_data->id;
  server_data->server_message = (char*)soap_malloc(soap, alloc);
  snprintf((char*)server_data->server_message, alloc, "ECHO %s", client_data->client_message);
  return SOAP_OK;
}

/* the client requests more data */
int ns__more(struct soap *soap, struct ns__ClientData *client_data)
{
  int i;
  struct ns__ServerData *server_data = soap_new_ns__ServerData(soap, -1);
  size_t alloc;

  if (client_data->client_message == NULL)
    client_data->client_message = "";

  printf("Client more %d: %s\n", client_data->id, client_data->client_message);

  alloc = strlen(client_data->client_message) + 32;
  server_data->id = client_data->id;
  server_data->server_message = (char*)soap_malloc(soap, alloc);
  for (i = 1; i <= 3; ++i)
  {
    snprintf((char*)server_data->server_message, alloc, "ECHO %d %s", i, client_data->client_message);

    /* soap_send_ns__data() is defined in the client-side soapClient.c, use it on the server side to send more data to the client */
    if (soap_send_ns__data(soap, NULL, NULL, server_data) != SOAP_OK)
      break;
  }
  return soap_send_ns__data(soap, NULL, NULL, NULL);
}

/* dummy server operation, never called but defined because it is declared in tcpdemo.h */
int ns__data(struct soap *soap, struct ns__ServerData *server_data)
{
  (void)soap; (void)server_data;
  return SOAP_NO_METHOD;
}

/* end the conversation */
int ns__bye(struct soap *soap)
{
  printf("Bye\n");

  /* disable keep-alive to end the soap_serve() loop and close the socket (resetting SOAP_KEEPALIVE is not sufficient) */
  soap->keep_alive = 0;

  return SOAP_OK;
}
