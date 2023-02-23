/*      tcpclient-json.cpp

        Transfer JSON over TCP/IP

        Build steps:

        soapcpp2 -CSL ../xml-rpc-json/xml-rpc.h
        cc -I. -I../xml-rpc-json -o tcpclient-json tcpclient-json.cpp soapC.cpp ../xml-rpc-json/xml-rpc.cpp ../xml-rpc-json/json.cpp stdsoap2.cpp

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

static const char *server = "localhost:8080"; /* plain TCP/IP, no HTTP */

int main()
{
  /* SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed */
  /* SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP */
  soap *soap = soap_new1(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  value request(soap);
  value response(soap);

  /* enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes: */
  /* signal(SIGPIPE, SIG_IGN); */

  /* set sensible timeouts */

  soap->connect_timeout = 5;
  soap->transfer_timeout = 5;
  soap->recv_timeout = 3;
  soap->send_timeout = 3;

  /* two-way send and receive JSON with json_call() */

  request.clear();
  request["request"] = "echo";
  request["id"] = 1;
  request["message"] = "Hello";
  std::cout << "Client: " << request["message"] << '\n';

  if (json_call(soap, server, &request, &response) != SOAP_OK)
  {
    soap_stream_fault(soap, std::cerr);
  }
  else if (response.is_struct())
  {
    std::cout << "Server: " << response["message"] << '\n';
  }
  else
  {
    std::cout << "Invalid response\n";
  }

  /* one-way send JSON with json_call(,,NULL) followed by one-way receive JSON with json_recv() */

  request.clear();
  request["request"] = "echo";
  request["id"] = 2;
  request["message"] = "Hello again";
  std::cout << "Client: " << request["message"] << '\n';

  if (json_call(soap, server, &request, NULL) != SOAP_OK)
  {
    soap_stream_fault(soap, std::cerr);
  }
  else if (json_recv(soap, &response) != SOAP_OK)
  {
    soap_stream_fault(soap, std::cerr);
  }
  else if (response.is_struct())
  {
    std::cout << "Server: " << response["message"] << '\n';
  }
  else
  {
    std::cout << "Invalid response\n";
  }

  /* one-way send JSON with soap_call(,,NULL) followed by multiple one-way receive JSON with soap_recv() */

  request.clear();
  request["request"] = "more";
  request["id"] = 3;
  request["message"] = "Hello want more";
  std::cout << "Client: " << request["message"] << '\n';

  if (json_call(soap, server, &request, NULL) != SOAP_OK)
  {
    soap_stream_fault(soap, std::cerr);
  }
  else
  {
    while (json_recv(soap, &response) == SOAP_OK)
    {
      if (response.is_struct() && strcmp(response["message"], "") == 0)
        break;
      std::cout << "Server: " << response["message"] << "\n";
    }
    if (soap->error)
      soap_stream_fault(soap, std::cerr);
  }

  /* one-way send JSON to say goodbye */

  request.clear();
  request["request"] = "bye";
  std::cout << "Client: Bye\n";

  if (json_call(soap, server, &request, NULL) != SOAP_OK)
  {
    soap_stream_fault(soap, std::cerr);
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
