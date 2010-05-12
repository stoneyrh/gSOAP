/*
	xml-rpc-currentTimeServer.cpp

	XML-RPC currenTime server (C++ version)

	Returns XML-RPC message with current time to client.

	Compile:
	soapcpp2 xml-rpc.h
	cc xml-rpc-currentTimeServer.cpp xml-rpc.cpp xml-rpc-io.cpp stdsoap2.cpp soapC.cpp

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2001-2008, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL or Genivia's license for commercial use.
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
#include "xml-rpc-io.h"

using namespace std;

int serve_request(soap*);

int main(int argc, char **argv)
{
  soap *ctx = soap_new();

  if (argc < 2)
    return serve_request(ctx);

  int port = atoi(argv[1]);

  if (!soap_valid_socket(soap_bind(ctx, NULL, port, 100)))
  {
    soap_print_fault(ctx, stderr);
    exit(1);
  }

  for (;;)
  {
    if (!soap_valid_socket(soap_accept(ctx)))
    {
      soap_print_fault(ctx, stderr);
    }
    else
    {
      serve_request(ctx);
    }
  }
  soap_free(ctx);

  return 0;
}

int serve_request(soap* ctx)
{
  methodCall m(ctx);

  if (m.recv() != SOAP_OK)
    soap_print_fault(ctx, stderr);
  else
  {
    methodResponse r(ctx);

    if (!strcmp(m.name(), "currentTime.getCurrentTime"))
      // method name matches: first parameter of response is time
      r[0] = time(0);
    else
      // otherwise, set fault
      r.set_fault("Wrong method");

    if (r.send() != SOAP_OK)
      soap_print_fault(ctx, stderr);
  }

  // close (but keep-alive keeps socket open)
  soap_closesock(ctx);

  // clean up
  soap_destroy(ctx);
  soap_end(ctx);

  return ctx->error;
}

/* Don't need a namespace table. We put an empty one here to avoid link errors */
struct Namespace namespaces[] = { {NULL, NULL} };
