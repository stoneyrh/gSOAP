/*      tcpserver-json.cpp

        Transfer JSON over TCP/IP
        Simple iterative server; see gSOAP documentation to implement threaded server

        Build steps:

        soapcpp2 -CSL ../xml-rpc-json/xml-rpc.h
        cc -I. -I../xml-rpc-json -o tcpserver-json tcpserver-json.c soapC.c ../xml-rpc-json/xml-rpc.c ../xml-rpc-json/json.c stdsoap2.c

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
#include "xml-rpc-iters.h" // optional to traverse JSON (or XML-RPC) data with iterators (not used in this demo)
#include "json.h"

int main()
{
  /* SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed */
  /* SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP */
  soap *soap = soap_new1(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  SOAP_SOCKET m, s;
  value request(soap);
  value response(soap);

  /* enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes: */
  /* signal(SIGPIPE, SIG_IGN); */
  
  /* reuse port immediately */
  soap->bind_flags = SO_REUSEADDR;

  m = soap_bind(soap, NULL, 8080, 2);
  if (!soap_valid_socket(m))
  {
    soap_stream_fault(soap, std::cerr);
    exit(EXIT_FAILURE);
  }

  std::cout << "Socket connection successful " << m << '\n';

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
    soap_stream_fault(soap, std::cerr);
  }
  else
  {
    while (1)
    {
      if (soap_begin_recv(soap) != SOAP_OK || json_recv(soap, request) != SOAP_OK || soap_end_recv(soap) != SOAP_OK)
      {
        soap_stream_fault(soap, std::cerr);
      }
      else
      {
        if (request.is_struct())
        {
          response.clear();

          if (strcmp(request["request"], "echo") == 0)
          {
            int id = request["id"];
            const char *client_message = request["message"];
            size_t alloc = strlen(client_message) + 6;
            char *server_message = (char*)soap_malloc(soap, alloc);

            std::cout << "Client echo " << id << ": " << client_message << '\n';

            response["response"] = "echo";
            response["id"] = id;
            snprintf(server_message, alloc, "ECHO %s", client_message);
            response["message"] = server_message;
            if (soap_begin_send(soap) != SOAP_OK || json_send(soap, response) != SOAP_OK || soap_end_send(soap) != SOAP_OK)
              break;
          }
          else if (strcmp(request["request"], "more") == 0)
          {
            int i;
            int id = request["id"];
            const char *client_message = request["message"];
            size_t alloc = strlen(client_message) + 32;
            char *server_message = (char*)soap_malloc(soap, alloc);

            std::cout << "Client echo " << id << ": " << client_message << '\n';

            response["response"] = "data";
            response["id"] = id;
            for (i = 1; i <= 3; ++i)
            {
              snprintf(server_message, alloc, "ECHO %d %s", i, client_message);
              response["message"] = server_message;
              if (soap_begin_send(soap) != SOAP_OK || json_send(soap, response) != SOAP_OK || soap_end_send(soap) != SOAP_OK)
                break;
            }
            response["message"] = "";
            if (soap_begin_send(soap) != SOAP_OK || json_send(soap, response) != SOAP_OK || soap_end_send(soap) != SOAP_OK)
              break;
          }
          else if (strcmp(request["request"], "bye") == 0)
          {
            std::cout << "Bye\n";
            break;
          }
          else
          {
            std::cout << "Unknown request\n";
            break;
          }
        }
        else
        {
          std::cout << "Invalid request\n";
          break;
        }
      }
    }

    soap_closesock(soap);
  }

  soap_destroy(soap);
  soap_end(soap);
  soap_free(soap);
}

/* Don't need a namespace table. We put an empty one here to avoid link errors */
struct Namespace namespaces[] = { {NULL, NULL} };
