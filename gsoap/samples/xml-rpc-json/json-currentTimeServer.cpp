/*
        json-currentTimeServer.cpp

        JSON currenTime server (C++ version)
        CGI or stand-alone multi-threaded server

        Returns JSON message with current time to client.

        Compile:
        soapcpp2 -CSL xml-rpc.h
        c++ -o json-currentTimeServer json-currentTimeServer.cpp json.cpp xml-rpc.cpp stdsoap2.cpp soapC.cpp
        Install as CGI on Web server
        Or run as stand-alone server (e.g. on port 18000):
        ./json-currentTimeServer 18000

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

#include "json.h"

#include "plugin/threads.h"

using namespace std;

int serve_request(soap*);

int main(int argc, char **argv)
{
  soap *ctx = soap_new1(SOAP_C_UTFSTRING);

  if (argc < 2)
  {
    // process CGI request
    value request(ctx);

    if (soap_begin_recv(ctx)
     || json_recv(ctx, request)
     || soap_end_recv(ctx))
    {
      soap_send_fault(ctx);
    }
    else
    {
      value response(ctx);
  
      // if the name matches: set response to time, else error
      if (request.is_string() && !strcmp(request, "getCurrentTime"))
      {
        response = (ULONG64)time(0);
      }
      else
      {
        response["fault"] = "Wrong method";
        response["detail"] = request;
      }

      // set the http content type
      ctx->http_content = "application/json; charset=utf-8";
      // send the response
      if (soap_begin_count(ctx)
       || ((ctx->mode & SOAP_IO_LENGTH) && json_send(ctx, response))
       || soap_end_count(ctx)
       || soap_response(ctx, SOAP_FILE)
       || json_send(ctx, response)
       || soap_end_send(ctx))
        soap_print_fault(ctx, stderr);
    }
    soap_destroy(ctx);
    soap_end(ctx);
    soap_free(ctx);
    return 0;
  }

  int port = atoi(argv[1]);

  if (!soap_valid_socket(soap_bind(ctx, NULL, port, 100)))
  {
    soap_print_fault(ctx, stderr);
    exit(1);
  }

  ctx->send_timeout = 10;
  ctx->recv_timeout = 10;

  while (1)
  {
    THREAD_TYPE tid;
    if (!soap_valid_socket(soap_accept(ctx)))
      soap_print_fault(ctx, stderr);
    else
      THREAD_CREATE(&tid, (void*(*)(void*))serve_request, (void*)soap_copy(ctx));
  }
  soap_destroy(ctx);
  soap_end(ctx);
  soap_free(ctx);

  return 0;
}

int serve_request(soap* ctx)
{
  THREAD_DETACH(THREAD_ID);

  // HTTP keep-alive max number of iterations
  unsigned int k = ctx->max_keep_alive;
  value request(ctx);

  do
  {
    if (ctx->max_keep_alive > 0 && !--k)
      ctx->keep_alive = 0;

    // receive JSON request
    if (soap_begin_recv(ctx)
     || json_recv(ctx, request)
     || soap_end_recv(ctx))
      soap_send_fault(ctx);
    else
    {
      value response(ctx);
  
      if (request.is_string() && !strcmp(request, "getCurrentTime"))
      {
        response = (ULONG64)time(0);
      }
      else
      {
        response["fault"] = "Wrong method";
        response["detail"] = request;
      }

      ctx->http_content = "application/json; charset=utf-8";
      if (soap_begin_count(ctx)
       || ((ctx->mode & SOAP_IO_LENGTH) && json_send(ctx, response))
       || soap_end_count(ctx)
       || soap_response(ctx, SOAP_FILE)
       || json_send(ctx, response)
       || soap_end_send(ctx))
        soap_print_fault(ctx, stderr);
    }
    // close (keep-alive may keep socket open when client supports it)
    soap_closesock(ctx);

  } while (ctx->keep_alive);

  int err = ctx->error;

  // clean up
  soap_destroy(ctx);
  soap_end(ctx);
  soap_free(ctx);

  return err;
}

/* Don't need a namespace table. We put an empty one here to avoid link errors */
struct Namespace namespaces[] = { {NULL, NULL} };

