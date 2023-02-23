/*      tcpserver-tls.c

        Transfer XML over TCP/IP with TLS secured connection
        Simple iterative server; see documentation to implement threaded server

        Build steps:

        soapcpp2 -c tcpdemo.h
        cc -DWITH_OPENSSL -o tcpserver tcpserver.c soapC.c soapServer.c soapClient.c stdsoap2.c -lcrypto -lssl

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

int CRYPTO_thread_setup();
void CRYPTO_thread_cleanup();

int main()
{
  /* SOAP_IO_KEEPALIVE: keep socket connection open until timeout or explicitly closed */
  /* SOAP_ENC_PLAIN: disable HTTP to transfer plain messages without HTTP */
  struct soap *soap = soap_new1(SOAP_IO_KEEPALIVE | SOAP_ENC_PLAIN);
  SOAP_SOCKET m, s;

  /* Uncomment to call this first before all else if SSL is initialized elsewhere, e.g. in application code */
  /* soap_ssl_noinit(); */
  /* Init SSL before any threads are started (do this just once) */
  soap_ssl_init();

  /* enable this line for SIGPIPE handler on Unix/Linux systems to catch broken pipes: */
  /* signal(SIGPIPE, SIG_IGN); */

  /* set up SSL locks (not needed for OpenSSL 1.1.0 and greater) */
  if (CRYPTO_thread_setup())
  {
    fprintf(stderr, "Cannot setup thread mutex for OpenSSL\n");
    exit(EXIT_FAILURE);
  }

  /* The supplied server certificate "server.pem" assumes that the server is
    running on 'localhost', so clients can only connect from the same host when
    verifying the server's certificate.
    To verify the certificates of third-party services, they must provide a
    certificate issued by Verisign or another trusted CA. At the client-side,
    the capath parameter should point to a directory that contains these
    trusted (root) certificates or the cafile parameter should refer to one
    file will all certificates. To help you out, the supplied "cacerts.pem"
    file contains the certificates issued by various CAs. You should use this
    file for the cafile parameter instead of "cacert.pem" to connect to trusted
    servers. Note that the client may fail to connect if the server's
    credentials have problems (e.g. expired).
    Note 1: the password and capath are not used with GNUTLS
    Note 2: setting capath may not work on Windows.
  */
  if (soap_ssl_server_context(soap,
    SOAP_SSL_DEFAULT,	/* use SOAP_SSL_REQUIRE_CLIENT_AUTHENTICATION to verify clients: client must provide a key file e.g. "client.pem" and "password" */
    "server.pem",	/* keyfile (cert+key): see README.txt to create this file, use non-password protected gnutls-server.pem with GNUTLS and WolfSSL see README.txt */
    "password",		/* password to read the private key in the key file */
    NULL, 	        /* cacert file to store trusted certificates (to authenticate clients), see README.txt */
    NULL,		/* capath */
    NULL,       	/* DH file name (e.g. "dh2048.pem") or DH param key len bits in string (e.g. "2048"), if NULL then RSA with 2048 bits is used instead (bits defined by SOAP_SSL_RSA_BITS) */
    NULL,		/* if randfile!=NULL: use a file with random data to seed randomness */ 
    "sslserver"		/* server identification for SSL session cache (unique server name, e.g. use argv[0]) */
  )
  )
  {
    soap_print_fault(soap, stderr);
    exit(EXIT_FAILURE);
  }
  /* enable CRL, may need SOAP_SSL_ALLOW_EXPIRED_CERTIFICATE when certs have no CRL
  if (soap_ssl_crl(soap, ""))
  {
    soap_print_fault(soap, stderr);
    exit(EXIT_FAILURE);
  }
  */

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

  /* accept secure connection and serve it while the connection stays open */

  s = soap_accept(soap);
  if (!soap_valid_socket(s))
  {
    soap_print_fault(soap, stderr);
  }
  else if (soap_ssl_accept(soap) != SOAP_OK)
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

  CRYPTO_thread_cleanup();

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

#if defined(WITH_OPENSSL) && OPENSSL_VERSION_NUMBER < 0x10100000L

struct CRYPTO_dynlock_value
{
  MUTEX_TYPE mutex;
};

static MUTEX_TYPE *mutex_buf = NULL;

static struct CRYPTO_dynlock_value *dyn_create_function(const char *file, int line)
{
  struct CRYPTO_dynlock_value *value;
  (void)file; (void)line;
  value = (struct CRYPTO_dynlock_value*)OPENSSL_malloc(sizeof(struct CRYPTO_dynlock_value));
  if (value)
    MUTEX_SETUP(value->mutex);
  return value;
}

static void dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l, const char *file, int line)
{
  (void)file; (void)line;
  if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(l->mutex);
  else
    MUTEX_UNLOCK(l->mutex);
}

static void dyn_destroy_function(struct CRYPTO_dynlock_value *l, const char *file, int line)
{
  (void)file; (void)line;
  MUTEX_CLEANUP(l->mutex);
  OPENSSL_free(l);
}

static void locking_function(int mode, int n, const char *file, int line)
{
  (void)file; (void)line;
  if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(mutex_buf[n]);
  else
    MUTEX_UNLOCK(mutex_buf[n]);
}

static unsigned long id_function()
{
  return (unsigned long)THREAD_ID;
}

int CRYPTO_thread_setup()
{
  int i;
  mutex_buf = (MUTEX_TYPE*)OPENSSL_malloc(CRYPTO_num_locks() * sizeof(MUTEX_TYPE));
  if (!mutex_buf)
    return SOAP_EOM;
  for (i = 0; i < CRYPTO_num_locks(); i++)
    MUTEX_SETUP(mutex_buf[i]);
  CRYPTO_set_id_callback(id_function);
  CRYPTO_set_locking_callback(locking_function);
  CRYPTO_set_dynlock_create_callback(dyn_create_function);
  CRYPTO_set_dynlock_lock_callback(dyn_lock_function);
  CRYPTO_set_dynlock_destroy_callback(dyn_destroy_function);
  return SOAP_OK;
}

void CRYPTO_thread_cleanup()
{
  int i;
  if (!mutex_buf)
    return;
  CRYPTO_set_id_callback(NULL);
  CRYPTO_set_locking_callback(NULL);
  CRYPTO_set_dynlock_create_callback(NULL);
  CRYPTO_set_dynlock_lock_callback(NULL);
  CRYPTO_set_dynlock_destroy_callback(NULL);
  for (i = 0; i < CRYPTO_num_locks(); i++)
    MUTEX_CLEANUP(mutex_buf[i]);
  OPENSSL_free(mutex_buf);
  mutex_buf = NULL;
}

#else

/* OpenSSL not used or OpenSSL prior to 1.1.0 */

int CRYPTO_thread_setup()
{
  return SOAP_OK;
}

void CRYPTO_thread_cleanup()
{ }

#endif
