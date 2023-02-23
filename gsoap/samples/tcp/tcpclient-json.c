/*      tcpclient-json.c

        Transfer JSON over TCP/IP

        Build steps:

        soapcpp2 -c -CSL ../xml-rpc-json/xml-rpc.h
        cc -I. -I../xml-rpc-json -o tcpclient-json tcpclient-json.c soapC.c ../xml-rpc-json/xml-rpc.c ../xml-rpc-json/json.c stdsoap2.c

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
#include "json.h"

static const char *server = "localhost:8080"; /* plain TCP/IP, no HTTP */

int main()
{
  /* SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed */
  /* SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP */
  struct soap *soap = soap_new1(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  struct value *request = new_value(soap);
  struct value *response = new_value(soap);

  /* enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes: */
  /* signal(SIGPIPE, SIG_IGN); */

  /* set sensible timeouts */

  soap->connect_timeout = 5;
  soap->transfer_timeout = 5;
  soap->recv_timeout = 3;
  soap->send_timeout = 3;

  /* two-way send and receive JSON with json_call() */

  soap_default_value(soap, request);
  *string_of(value_at(request, "request")) = "echo";
  *int_of(value_at(request, "id")) = 1;
  *string_of(value_at(request, "message")) = "Hello";
  printf("Client: %s\n", *string_of(value_at(request, "message")));

  if (json_call(soap, server, request, response) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
  }
  else if (is_struct(response))
  {
    printf("Server: %s\n", *string_of(value_at(response, "message")));
  }
  else
  {
    printf("Invalid response\n");
  }

  /* one-way send JSON with json_call(,,NULL) followed by one-way receive JSON with json_recv() */

  soap_default_value(soap, request);
  *string_of(value_at(request, "request")) = "echo";
  *int_of(value_at(request, "id")) = 2;
  *string_of(value_at(request, "message")) = "Hello again";
  printf("Client: %s\n", *string_of(value_at(request, "message")));

  if (json_call(soap, server, request, NULL) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
  }
  else if (json_recv(soap, response) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
  }
  else if (is_struct(response))
  {
    printf("Server: %s\n", *string_of(value_at(response, "message")));
  }
  else
  {
    printf("Invalid response\n");
  }

  /* one-way send JSON with soap_call(,,NULL) followed by multiple one-way receive JSON with soap_recv() */

  soap_default_value(soap, request);
  *string_of(value_at(request, "request")) = "more";
  *int_of(value_at(request, "id")) = 3;
  *string_of(value_at(request, "message")) = "Hello want more";
  printf("Client: %s\n", *string_of(value_at(request, "message")));

  if (json_call(soap, server, request, NULL) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
  }
  else
  {
    while (json_recv(soap, response) == SOAP_OK)
    {
      if (is_struct(response) && strcmp(*string_of(value_at(response, "message")), "") == 0)
        break;
      printf("Server: %s\n", *string_of(value_at(response, "message")));
    }
    if (soap->error)
      soap_print_fault(soap, stderr);
  }

  /* one-way send JSON to say goodbye */

  soap_default_value(soap, request);
  *string_of(value_at(request, "request")) = "bye";
  printf("Client: Bye\n");

  if (json_call(soap, server, request, NULL) != SOAP_OK)
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

/* Don't need a namespace table. We put an empty one here to avoid link errors */
struct Namespace namespaces[] = { {NULL, NULL} };
