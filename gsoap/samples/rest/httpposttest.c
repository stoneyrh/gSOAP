/*
	httpposttest.c

	gSOAP HTTP GET plugin example application.

gSOAP XML Web services tools
Copyright (C) 2000-2009, Robert van Engelen, Genivia, Inc., All Rights Reserved.

--------------------------------------------------------------------------------
gSOAP public license.

The contents of this file are subject to the gSOAP Public License Version 1.3
(the "License"); you may not use this file except in compliance with the
License. You may obtain a copy of the License at
http://www.cs.fsu.edu/~engelen/soaplicense.html
Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the License.

The Initial Developer of the Original Code is Robert A. van Engelen.
Copyright (C) 2000-2009, Robert van Engelen, Genivia, Inc., All Rights Reserved.
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

This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------

Compile:

soapcpp2 -S -c httpposttest.h
cc -Iplugin -o httpposttest httpposttest.c soapC.c soapServer.c httppost.c stdsoap2.c

To support https and compression, compile with:

cc -DWITH_OPENSSL -DWITH_GZIP -Iplugin -o httpposttest httpposttest.c soapC.c soapServer.c httppost.c stdsoap2.c -lssl -lcrypto -lz

*/

#include "soapH.h"
#include "httppost.h"

int jpg_handler(struct soap *soap);
int image_handler(struct soap *soap);
int text_handler(struct soap *soap);

int main(int argc, char **argv)
{ char *buf;
  size_t len;
  struct soap soap;

  soap_init(&soap);
  /* chunking conserves memory and is generally faster: */
  soap_set_omode(&soap, SOAP_IO_CHUNK);

  if (argc < 2)
  { /* CGI server */
    struct http_post_handlers handlers[] =
    { { "image/jpg", jpg_handler },
      { "image/*",   image_handler },
      { "image/*;*", image_handler },
      { "text/*",    text_handler },
      { "text/*;*",  text_handler },
      { NULL }
    };
    soap_register_plugin_arg(&soap, http_post, handlers); /* register plugin (server only) */
    soap_serve(&soap);
    exit(0);
  }

  /* client */
  if (soap_post_connect(&soap, argv[1], NULL, "text/html")
   || soap_send(&soap, "<html>")
   || soap_send(&soap, argc == 2 ? "Hello" : argv[2])
   || soap_send(&soap, "</html>")
   || soap_end_send(&soap))
  { soap_print_fault(&soap, stderr);
    exit(1);
  }
  /* after sending, receive body (note: POST handlers should not be set) */
  if (soap_begin_recv(&soap)
   || soap_http_body(&soap, &buf, &len)
   || soap_end_recv(&soap))
  { soap_print_fault(&soap, stderr);
    exit(1);
  }
  printf("Received %lu bytes of type %s:\n", (unsigned long)len, soap.http_content?soap.http_content:"");
  soap_end(&soap);
  soap_done(&soap);
  return 0;
}

/* dummy SOAP service operation */
int ns__dummy(struct soap *soap)
{ return SOAP_NO_METHOD;
}

/* the jpg handler just responds with HTTP OK */
int jpg_handler(struct soap *soap)
{ char *buf;
  size_t len;
  soap_http_body(soap, &buf, &len);
  soap_response(soap, SOAP_OK);
  soap_end_send(soap);
  return SOAP_OK;
}

/* the image handler responds with HTTP OK and a text/html body */
int image_handler(struct soap *soap)
{ char *buf;
  size_t len;
  soap_http_body(soap, &buf, &len);
  soap_response(soap, SOAP_HTML);
  soap_send(soap, "<html>Image received</html>");
  soap_end_send(soap);
  return SOAP_OK;
}

/* the text handler copies the message back */
int text_handler(struct soap *soap)
{ char *buf;
  size_t len;
  soap_http_body(soap, &buf, &len);
  /* use current soap->http_content from HTTP header as return HTTP type */
  soap_response(soap, SOAP_FILE);
  soap_send_raw(soap, buf, len);
  soap_end_send(soap);
  return SOAP_OK;
}

SOAP_NMAC struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{NULL, NULL, NULL, NULL}
};
