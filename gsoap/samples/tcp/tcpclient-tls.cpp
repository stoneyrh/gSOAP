/*      tcpclient-tls.cpp

        Transfer XML over TCP/IP

        Build steps:

        soapcpp2 tcpdemo.h
        c++ -DWITH_OPENSSL -o tcpclient-tls tcpclient-tls.cpp soapC.cpp soapClient.cpp stdsoap2.cpp -lcrypto -lss

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

#include "soaptcpdemoProxy.h"
#include "tcpdemo.nsmap"

/* must specify https URL to enable client-side SSL/TLS!!! Otherwise the message is sent in the clear */
/* SOAP_ENC_PLAIN forces non-HTTP(S) for plain XML over TCP/IP with TLS */
static const char *server = "https://localhost:8080";

int main()
{
  // SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed
  // SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP
  tcpdemoProxy proxy(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  ns__ClientData client_data;
  ns__ServerData server_data;

  // enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes:
  // signal(SIGPIPE, SIG_IGN);

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
  if (soap_ssl_client_context(proxy.soap,
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
    proxy.soap_stream_fault(std::cerr);
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
  if (soap_ssl_crl(proxy.soap, "")
  )
  {
    proxy.soap_stream_fault(std::cerr);
    exit(EXIT_FAILURE);
  }

  // set sensible timeouts

  proxy.soap->connect_timeout = 5;
  proxy.soap->transfer_timeout = 5;
  proxy.soap->recv_timeout = 3;
  proxy.soap->send_timeout = 3;

  // two-way send and receive XML with soap_call_...

  client_data.id = 1;
  client_data.client_message = "Hello";
  std::cout << "Client: " << client_data.client_message << '\n';

  if (proxy.echo(server, NULL, &client_data, &server_data) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }
  else
  {
    if (server_data.server_message)
      std::cout << "Server: " << server_data.server_message << '\n';
  }

  // one-way send XML with soap_send_... followed by one-way receive XML with soap_recv_...

  client_data.id = 2;
  client_data.client_message = "Hello again";
  std::cout << "Client: " << client_data.client_message << '\n';

  if (proxy.send_echo(server, NULL, &client_data) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }
  else if (proxy.recv_echo(&server_data) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }
  else
  {
    std::cout << "Server: " << server_data.server_message << '\n';
  }

  // one-way send XML with soap_send_... followed by multiple one-way receive XML with soap_recv_...

  client_data.id = 3;
  client_data.client_message = "Hello want more";
  std::cout << "Client: " << client_data.client_message << '\n';

  if (proxy.send_more(server, NULL, &client_data) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }
  else
  {
    ns__data data;
    while (proxy.recv_data(data) == SOAP_OK)
    {
      if (data._param_1 == NULL || data._param_1->server_message == NULL)
        break;
      std::cout << "Server: " << data._param_1->server_message << '\n';
    }
  }

  // one-way send XML to say goodbye

  std::cout << "Client: Bye\n";

  if (proxy.send_bye(server, NULL) != SOAP_OK)
  {
    proxy.soap_stream_fault(std::cerr);
  }

  // disable keep-alive, then close the socket

  proxy.soap->keep_alive = 0;
  proxy.soap_close_socket();

  // cleanup

  proxy.destroy();
}
