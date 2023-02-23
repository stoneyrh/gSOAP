/*      tcpclient-tls.c

        Transfer XML over TCP/IP with TLS secured connection

        Build steps:

        soapcpp2 -c tcpdemo.h
        cc -DWITH_OPENSSL -o tcpclient tcpclient.c soapC.c soapClient.c stdsoap2.c -lcrypto -lssl

        SSL-enabled services use the gSOAP SSL interface. See
        samples/ssl/sslclient.c and samples/ssl/sslserver.c for example code
        with instructions and the gSOAP documentation more details on how to
        set up TLS/SSL.

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

/* must specify https URL to enable client-side SSL/TLS!!! Otherwise the message is sent in the clear */
/* SOAP_ENC_PLAIN forces non-HTTP(S) for plain XML over TCP/IP with TLS */
static const char *server = "https://localhost:8080";

int main()
{
  /* SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed */
  /* SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP */
  struct soap *soap = soap_new1(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  struct ns__ClientData client_data;
  struct ns__ServerData server_data;

  /* enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes: */
  /* signal(SIGPIPE, SIG_IGN); */

  /* The supplied server certificate "server.pem" assumes that the server is
     running on 'localhost', so clients can only connect from the same host when
     verifying the server's certificate. Use SOAP_SSL_NO_AUTHENTICATION to omit
     the authentication of the server and use encryption directly from any site.
     To verify the certificates of third-party services, they must provide a
     certificate issued by Verisign or another trusted CA. At the client-side,
     the capath parameter should point to a directory that contains these
     trusted (root) certificates or the cafile parameter should refer to one
     file will all certificates. To help you out, the supplied "cacerts.pem"
     file contains the certificates issued by various CAs. You should use this
     file for the cafile parameter instead of "cacert.pem" to connect to trusted
     servers.  Note that the client may fail to connect if the server's
     credentials have problems (e.g. expired). Use SOAP_SSL_NO_AUTHENTICATION
     and set cacert to NULL to encrypt messages if you don't care about the
     trustworthyness of the server.
     Note 1: the password and capath are not used with GNUTLS
     Note 2: setting capath may not work on Windows.
  */
  if (soap_ssl_client_context(soap,
    /* SOAP_SSL_NO_AUTHENTICATION, */ /* for encryption w/o authentication */
    /* SOAP_SSL_DEFAULT | SOAP_SSL_SKIP_HOST_CHECK, */ /* if we don't want the host name checks since these will change from machine to machine */
    SOAP_SSL_DEFAULT | SOAP_SSL_ALLOW_EXPIRED_CERTIFICATE, /* allow self-signed, expired, and certificates w/o CRL */
    /* SOAP_SSL_DEFAULT, */ /* use SOAP_SSL_DEFAULT in production code */
    NULL, 		/* keyfile (cert+key): required only when client must authenticate to server (see SSL docs to create this file) */
    NULL, 		/* password to read the keyfile */
    "cacert.pem",	/* optional cacert file to store trusted certificates, use cacerts.pem for all public certificates issued by common CAs, use gnutls-cacert.pem with GNUTLS and WolfSSL see README.txt */
    NULL,		/* optional capath to directory with trusted certificates */
    NULL		/* if randfile!=NULL: use a file with random data to seed randomness */ 
  ))
  {
    soap_print_fault(soap, stderr);
    exit(EXIT_FAILURE);
  }
  /* Consider using soap_ssl_client_setup() instead of soap_ssl_client_context() above:
     - automatically uses certificates stored in Unix/Linux common locations
     - automatically uses Windows system certificate store
     - when -DWITH_WININET is defined, uses the gSOAP WinInet plugin with WinInet system certificate store
     - when -DWITH_CURL is defined, uses the gSOAP CURL plugin with CURL certificate store
  if (soap_ssl_client_setup(soap,
    // SOAP_SSL_DEFAULT | SOAP_SSL_SKIP_HOST_CHECK, if we don't want the host name checks since these will change from machine to machine
    SOAP_SSL_DEFAULT | SOAP_SSL_ALLOW_EXPIRED_CERTIFICATE, // allow self-signed, expired, and certificates w/o CRL
    NULL, 		// keyfile (cert+key): required only when client must authenticate to server (see SSL docs to create this file)
    NULL, 		// password to read the keyfile
    "cacert.pem",	// optional cacert file to store trusted certificates, use cacerts.pem for all public certificates issued by common CAs
    NULL 		// optional capath to directory with trusted certificates
  ))
  {
    soap_print_fault(soap, stderr);
    exit(EXIT_FAILURE);
  }
  */
  /* code below enables CRL, may need SOAP_SSL_ALLOW_EXPIRED_CERTIFICATE when certs have no CRL resulting in a warning/error */
  if (soap_ssl_crl(soap, "")
  )
  {
    soap_print_fault(soap, stderr);
    exit(EXIT_FAILURE);
  }

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
