/*
	wsrmdemo.c

	WS-ReliableMessaging and WS-Addressing demo service and client.

	See the wsrmdemo.h header file for build and usage details.

gSOAP XML Web services tools
Copyright (C) 2000-2010, Robert van Engelen, Genivia Inc., All Rights Reserved.
This part of the software is released under one of the following licenses:
GPL, the gSOAP public license, or Genivia's license for commercial use.
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
Copyright (C) 2000-2010, Robert van Engelen, Genivia Inc., All Rights Reserved.
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
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapH.h"
#include "wsrmdemo.nsmap"

#include <unistd.h>	/* defines _POSIX_THREADS if pthreads are available */
#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
#include <threads.h>	/* from plugin/threads.h */
#include <pthread.h>
#endif

#include "wsaapi.h"  /* from plugin/wsaapi.h */
#include "wsrmapi.h" /* from plugin/wsrmapi.h */

/******************************************************************************\
 *
 *	Common Constants
 *
\******************************************************************************/

#define OptRequestMessageID  "WSRM-DEMO-REQ-" /* unique message ID (use UUID) */
#define OptResponseMessageID "WSRM-DEMO-RES-" /* unique message ID (use UUID) */

#if defined(WITH_UDP)
# define TARGET "soap.udp:" /* Test WS-ReliableMessaging with SOAP-over-UDP */
#elif defined(WITH_OPENSSL)
# define TARGET "https:"    /* Test HTTPS */
# define HTTP_USERID "foo"  /* using Basic Auth */
# define HTTP_PASSWD "bar"  /* using Basic Auth */
#else
# define TARGET "http:"
#endif

/* WS-Addressing and WS-ReliableMessaging service endpoints */
const char *FromAddress    = TARGET"//localhost:11000";
const char *ToAddress      = TARGET"//localhost:11001";
const char *AcksToAddress  = TARGET"//localhost:11002";
const char *ReplyToAddress = TARGET"//localhost:11003";
const char *FaultToAddress = TARGET"//localhost:11004";

/* HTTP Basic Authentication (when applicable, only use over HTTPS!) */
#if defined(HTTP_USERID) && defined(HTTP_PASSWD)
const char *userid = HTTP_USERID;
const char *passwd = HTTP_PASSWD;
#else
const char *userid = NULL;
const char *passwd = NULL;
#endif

/* the matching SOAP/WSA actions, defined in wsdldemo.h service definitions */
const char *RequestAction  = "urn:wsrmdemo/wsrmdemoPort/wsrmdemo";
const char *ResponseAction = "urn:wsrmdemo/wsrmdemoPort/wsrmdemoResponse";

/******************************************************************************\
 *
 *	Main Implements a Server and Client
 *
\******************************************************************************/

#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
void *process_request(void *soap);
#endif
int CRYPTO_thread_setup();
void CRYPTO_thread_cleanup();

int main(int argc, char **argv)
{
  struct soap *soap = soap_new1(SOAP_XML_INDENT | SOAP_XML_STRICT);
  soap_register_plugin(soap, soap_wsa);
  soap_register_plugin(soap, soap_wsrm);
  if (argc < 2)
  { /* no args: act as CGI service over stdin/out */
    if (soap_serve(soap))
    { soap_print_fault(soap, stderr);
      soap_print_fault_location(soap, stderr);
    }
  }
  else
  { int port = atoi(argv[1]);
    /* port number: run stand-alone server serving messages over port */
    if (port)
    {
#if !defined(WITH_UDP) && (defined(_POSIX_THREADS) || defined(_SC_THREADS))
      pthread_t tid;
#endif
      /* TCP/IP and UDP timeouts + = seconds, - = microsecond*/
      soap->send_timeout = soap->recv_timeout = 5;
#if defined(WITH_UDP)
      /* set UDP server, pure XML w/o HTTP headers */
      soap_set_mode(soap, SOAP_IO_UDP);
#elif defined(WITH_OPENSSL)
      if (CRYPTO_thread_setup())
      { fprintf(stderr, "Cannot setup thread mutex for OpenSSL\n");
        exit(1);
      }
      /* WS-Addressing server uses client-side sends, so init SSL for client+server: */
      if (soap_ssl_server_context(soap,
        SOAP_SSL_DEFAULT,
        "server.pem",	/* keyfile (server) */
        "password",	/* password to read the key file (server) */
        "cacert.pem",	/* cacert file to store trusted certificates (client) */
        NULL,		/* optional capath */
        NULL, 		/* DH file name or DH param key len bits, NULL: RSA */
        NULL,		/* file with random data to seed randomness */ 
        argv[1]		/* unique server identification for SSL session cache */
      ))
      { soap_print_fault(soap, stderr);
        exit(1);
      }
#endif

      soap->bind_flags = SO_REUSEADDR;
      if (!soap_valid_socket(soap_bind(soap, NULL, port, 100)))
      { soap_print_fault(soap, stderr);
        exit(1);
      }

      printf("**** Server is running\n");

      for (;;)
      { /* TCP accept (for UDP simply returns current socket) */
        if (!soap_valid_socket(soap_accept(soap)))
        { if (soap->errnum)
	    soap_print_fault(soap, stderr);
	  else
	    fprintf(stdout, "Server timed out\n");
	  break;
        }

        /* do not spawn threads for UDP, since accept() is a no-op for UDP */
#if !defined(WITH_UDP) && (defined(_POSIX_THREADS) || defined(_SC_THREADS))
        pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)soap_copy(soap));
#else
#if !defined(WITH_UDP) && defined(WITH_OPENSSL)
        /* SSL accept */
        if (soap_ssl_accept(soap))
        { soap_print_fault(soap, stderr);
          fprintf(stderr, "SSL request failed, continue with next call...\n");
          continue;
        }
#endif
        if (soap_serve(soap))
        { soap_print_fault(soap, stderr);
          soap_print_fault_location(soap, stderr);
        }
	else
          printf("\n**** Request served\n");
        soap_wsrm_dump(soap, stdout);
        soap_destroy(soap);
        soap_end(soap);
#endif
      }
      soap_destroy(soap);
      soap_end(soap);
      soap_done(soap); /* MUST call before CRYPTO_thread_cleanup */
      CRYPTO_thread_cleanup();
    }
    else
    { /* client */
      const char *from = NULL, *acksto = NULL, *replyto = NULL, *faultto = NULL;
      short noreply = 0, offer = 1;
      xsd__duration expires = 30000; /* 10000 ms = 30 seconds to expire */
      soap_wsrm_sequence_handle seq;
      struct ns__wsrmdemoResponse res;

      /* TCP/IP and UDP timeouts + = seconds, - = microsecond*/
      soap->send_timeout = soap->recv_timeout = 5;

#if defined(WITH_UDP)
      /* "soap.udp:" endpoint specifies SOAP-over-UDP and should always be used for ReplyTo and FaultTo if these use UDP */
      /* When the endpoint is an IP with a UDP destination, it is important to set UDP: */
      soap_set_mode(soap, SOAP_IO_UDP);
#elif defined(WITH_OPENSSL)
      CRYPTO_thread_setup();
      if (soap_ssl_client_context(soap,
        SOAP_SSL_DEFAULT | SOAP_SSL_SKIP_HOST_CHECK,
        NULL, 		/* optional keyfile to authenticate to server */
        NULL, 		/* password to read the keyfile */
        "cacert.pem",	/* cacert file to store trusted certificates */
        NULL,		/* capath to directory with trusted certificates */
        NULL		/* optional file with random data to seed randomness */ 
      ))
      { soap_print_fault(soap, stderr);
        exit(1);
      }
#endif

      /* Command-line: From, ReplyTo/noReply, AcksTo, and FaultTo addresses */
      if (argc >= 3)
      { if (strchr(argv[2], 'f'))
        { from = FromAddress;
          acksto = FromAddress;
          replyto = FromAddress;
        }
        if (strchr(argv[2], 'a'))
          acksto = AcksToAddress;
        if (strchr(argv[2], 'n'))
          noreply = 1;
        else if (strchr(argv[2], 'r'))
          replyto = ReplyToAddress;
        if (strchr(argv[2], 'e'))
          faultto = FaultToAddress;
	/* do not use offer for one-way messages */
        if (noreply || replyto || strchr(argv[2], 'o'))
          offer = 0;
      }

      printf("\n**** Creating a Sequence\n");

      /* Basic Auth */
      soap->userid = userid; soap->passwd = passwd;
      if (offer)
        soap_wsrm_create_offer(soap, ToAddress, acksto, NULL, expires, DiscardEntireSequence, OptRequestMessageID"0", &seq);
      else
        soap_wsrm_create(soap, ToAddress, acksto, expires, OptRequestMessageID"0", &seq);
      if (soap->error)
      { soap_print_fault(soap, stderr);
        if (seq)
	  soap_wsrm_seq_free(soap, seq);
        return soap->error;
      }

      soap_wsrm_dump(soap, stdout);

      printf("\n**** Sending first message '%s'\n", argv[1]);

      if (soap_wsrm_request(soap, seq, OptRequestMessageID"1", RequestAction))
      { soap_print_fault(soap, stderr);
        return soap->error;
      }
      /* set From, ReplyTo/noReply, and FaultTo WS-Addressing headers */
      if (from)
        soap_wsa_add_From(soap, FromAddress);
      if (noreply)
        soap_wsa_add_NoReply(soap);
      else if (replyto)
        soap_wsa_add_ReplyTo(soap, replyto);
      if (faultto)
        soap_wsa_add_FaultTo(soap, faultto);
      /* Basic Auth */
      soap->userid = userid; soap->passwd = passwd;
      /* this shows how to use a retry loop to improve message delivery */
      /* UDP may timeout when no UDP response message is sent by the server */
      while (soap_call_ns__wsrmdemo(soap, soap_wsrm_to(seq), RequestAction, argv[1], &res))
      { if (soap->error == 202)
        { printf("\n**** Request was accepted\n");
          break;
        }
        else if (soap->error == SOAP_NO_TAG) /* empty <Body> */
        { printf("\n**** Request was accepted, acks received\n");
          break;
        }
        soap_print_fault(soap, stderr);
        /* only continue if retry is recommended */
        if (soap_wsrm_check_retry(soap, seq))
          break;
        /* wait a second to give network a chance to recover */
        printf("\n**** Transmission failed: retrying after 1 second...\n");
        sleep(1);
      }

      if (soap->error == SOAP_OK)
        printf("\n**** Response OK\n");

      soap_wsrm_dump(soap, stdout);

      printf("\n**** Sending second message, requesting acks\n");

      if (soap_wsrm_request_acks(soap, seq, OptRequestMessageID"2", RequestAction))
      { soap_print_fault(soap, stderr);
        return soap->error;
      }
      /* set From, ReplyTo/noReply, and FaultTo WS-Addressing headers */
      if (from)
        soap_wsa_add_From(soap, FromAddress);
      if (noreply)
        soap_wsa_add_NoReply(soap);
      else if (replyto)
        soap_wsa_add_ReplyTo(soap, replyto);
      if (faultto)
        soap_wsa_add_FaultTo(soap, faultto);
      /* Basic Auth */
      soap->userid = userid; soap->passwd = passwd;
      /* just send the message without retry loop */
      /* UDP may timeout when no UDP response message is sent by the server */
      if (soap_call_ns__wsrmdemo(soap, soap_wsrm_to(seq), RequestAction, (char*)"Second Message", &res))
      { if (soap->error == 202)
          printf("\n**** Request was accepted\n");
        else if (soap->error == SOAP_NO_TAG) /* empty <Body> */
          printf("\n**** Request was accepted, acks received\n");
        else
          soap_print_fault(soap, stderr);
      }
      else
        printf("\n**** Response OK\n");

      printf("\n**** Resending "SOAP_ULONG_FORMAT" Non-Acked Messages\n", soap_wsrm_nack(seq));
      /* optional: resend messages marked as non-acked */
      soap_wsrm_resend(soap, seq, 0, 0); /* 0 0 means full range of msg nums */

      soap_wsrm_dump(soap, stdout);

      printf("\n**** Sending third message\n");

      if (soap_wsrm_request(soap, seq, OptRequestMessageID"3", RequestAction))
      { soap_print_fault(soap, stderr);
        return soap->error;
      }
      /* set From, ReplyTo/noReply, and FaultTo WS-Addressing headers */
      if (from)
        soap_wsa_add_From(soap, FromAddress);
      if (noreply)
        soap_wsa_add_NoReply(soap);
      else if (replyto)
        soap_wsa_add_ReplyTo(soap, replyto);
      if (faultto)
        soap_wsa_add_FaultTo(soap, faultto);
      /* Basic Auth */
      soap->userid = userid; soap->passwd = passwd;
      /* just send the message without retry loop */
      /* UDP may timeout when no UDP response message is sent by the server */
      if (soap_call_ns__wsrmdemo(soap, soap_wsrm_to(seq), RequestAction, (char*)"Third Message", &res))
      { if (soap->error == 202)
          printf("\n**** Request was accepted\n");
        else if (soap->error == SOAP_NO_TAG) /* empty <Body> */
          printf("\n**** Request was accepted, acks received\n");
        else
          soap_print_fault(soap, stderr);
      }
      else
        printf("\n**** Response OK\n");

      soap_wsrm_dump(soap, stdout);

      printf("\n**** Closing the Sequence\n");

      /* Basic Auth */
      soap->userid = userid; soap->passwd = passwd;
      /* close the sequence */
      if (soap_wsrm_close(soap, seq, OptRequestMessageID"4"))
      { soap_print_fault(soap, stderr);
        soap_wsrm_seq_free(soap, seq);
        return soap->error;
      }

      soap_wsrm_dump(soap, stdout);

      printf("\n**** Resending "SOAP_ULONG_FORMAT" Non-Acked Messages\n", soap_wsrm_nack(seq));
      /* optional: resend messages marked as non-acked by close() */
      soap_wsrm_resend(soap, seq, 0, 0); /* 0 0 means full range of msg nums */

      printf("\n**** Terminating the Sequence\n");

      /* Basic Auth */
      soap->userid = userid; soap->passwd = passwd;
      /* termination fails if the server did not get all messages */
      if (soap_wsrm_terminate(soap, seq, OptRequestMessageID"5"))
      { soap_print_fault(soap, stderr);
        soap_wsrm_seq_free(soap, seq);
        return soap->error;
      }

      soap_wsrm_dump(soap, stdout);

      /* delete the sequence */
      soap_wsrm_seq_free(soap, seq);

      /* cleanup deserialized data, allowed at any time in/after sequence */
      soap_destroy(soap);
      soap_end(soap);
      soap_done(soap); /* MUST call before CRYPTO_thread_cleanup */
      CRYPTO_thread_cleanup();
    }
  }
  return 0;
}

/******************************************************************************\
 *
 *	Threaded Server
 *
\******************************************************************************/

#ifdef _POSIX_THREADS
void *process_request(void *soap)
{
  pthread_detach(pthread_self());
#if !defined(WITH_UDP) && defined(WITH_OPENSSL)
  /* SSL accept */
  if (soap_ssl_accept((struct soap*)soap))
  { soap_print_fault((struct soap*)soap, stderr);
    fprintf(stderr, "SSL request failed\n");
    soap_destroy((struct soap*)soap);
    soap_end((struct soap*)soap);
    soap_free((struct soap*)soap);
    return NULL;
  }
#endif
  if (soap_serve((struct soap*)soap))
  { soap_print_fault((struct soap*)soap, stderr);
    soap_print_fault_location((struct soap*)soap, stderr);
  }
  else
    printf("\n**** Request served by thread\n");
  soap_wsrm_dump((struct soap*)soap, stdout);
  soap_destroy((struct soap*)soap);
  soap_end((struct soap*)soap);
  soap_free((struct soap*)soap);
  return NULL;
}
#endif

/******************************************************************************\
 *
 *	Service Operation of Main Server
 *
\******************************************************************************/

int
ns__wsrmdemo(struct soap *soap, char *in, struct ns__wsrmdemoResponse *result)
{
  /* simulate a fatal server error, which is possibly relayed */
  /* for fatal errors that terminate the sequence, we must call soap_wsrm_sender_fault() before soap_wsrm_check() */
  if (in && !strcmp(in, "error"))
  { printf("\n**** Simulating Server Operation Fatal Error\n");
    return soap_wsrm_sender_fault(soap, "The demo service wsrmdemo() operation encountered a fatal fault", NULL);
  }

  /* check Basic Auth, when enabled */
  if (userid && passwd)
  { if (!soap->userid
     || !soap->passwd
     || strcmp(userid, soap->userid)
     || strcmp(passwd, soap->passwd))
      return 401; /* HTTP Unauthorized */
  }

  /* check for WS-RM/WSA and set WS-RM/WSA return headers */
  if (soap_wsrm_check(soap))
    return soap->error;

  printf("\n**** Received '%s'\n", in?in:"(null)");

  /* simulate a non-fatal user-defined error, which is can be relayed */
  if (in && !strcmp(in, "fault"))
  { printf("\n**** Simulating Server Operation Fault\n");
    return soap_wsrm_sender_fault(soap, "The demo service wsrmdemo() operation returned a fault", NULL);
  }

  result->out = in;

#if 0
  /* to just respond without requesting acks for response messages: */
  return soap_wsrm_reply(soap, OptResponseMessageID"1", ResponseAction);
#else
  /* to request acks for response messages (only when offer was made): */
  return soap_wsrm_reply_request_acks(soap, OptResponseMessageID"1", ResponseAction);
#endif
}

/******************************************************************************\
 *
 *	Relayed Response Handler for ReplyTo Server
 *
\******************************************************************************/

int ns__wsrmdemoResponse(struct soap *soap, char *out)
{
  /* check Basic Auth, when enabled */
  if (userid && passwd)
  { if (!soap->userid
     || !soap->passwd
     || strcmp(userid, soap->userid)
     || strcmp(passwd, soap->passwd))
      return soap_send_empty_response(soap, 401); /* HTTP Unauthorized */
  }

  /* acks are auto-processed when present (WS-RM headers may not be present) */
  /* do not use soap_wsrm_check(soap) */

  printf("\n**** Received Response = %s\n", out?out:"(null)");

  // TODO: should send back ack when requested!
  return soap_send_empty_response(soap, SOAP_OK); /* HTTP 202 Accepted */
}

/******************************************************************************\
 *
 *	Relayed SOAP-ENV:Fault Handler for FaultTo Server
 *
\******************************************************************************/

int SOAP_ENV__Fault(struct soap *soap, char *faultcode, char *faultstring, char *faultactor, struct SOAP_ENV__Detail *detail, struct SOAP_ENV__Code *SOAP_ENV__Code, struct SOAP_ENV__Reason *SOAP_ENV__Reason, char *SOAP_ENV__Node, char *SOAP_ENV__Role, struct SOAP_ENV__Detail *SOAP_ENV__Detail)
{ 
  /* populate the fault struct from the operation arguments to print it */
  soap_fault(soap);
  /* SOAP 1.1 */
  soap->fault->faultcode = faultcode;
  soap->fault->faultstring = faultstring;
  soap->fault->faultactor = faultactor;
  soap->fault->detail = detail;
  /* SOAP 1.2 */
  soap->fault->SOAP_ENV__Code = SOAP_ENV__Code;
  soap->fault->SOAP_ENV__Reason = SOAP_ENV__Reason;
  soap->fault->SOAP_ENV__Node = SOAP_ENV__Node;
  soap->fault->SOAP_ENV__Role = SOAP_ENV__Role;
  soap->fault->SOAP_ENV__Detail = SOAP_ENV__Detail;

  /* set error */
  soap->error = SOAP_FAULT;
  printf("\n**** Received Fault:\n");
  soap_print_fault(soap, stdout);

  return soap_send_empty_response(soap, SOAP_OK); /* HTTP 202 Accepted */
}

/******************************************************************************\
 *
 *	OpenSSL
 *
\******************************************************************************/

#ifdef WITH_OPENSSL

struct CRYPTO_dynlock_value
{ MUTEX_TYPE mutex;
};

static MUTEX_TYPE *mutex_buf;

static struct CRYPTO_dynlock_value *dyn_create_function(const char *file, int line)
{ struct CRYPTO_dynlock_value *value;
  value = (struct CRYPTO_dynlock_value*)malloc(sizeof(struct CRYPTO_dynlock_value));
  if (value)
    MUTEX_SETUP(value->mutex);
  return value;
}

static void dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l, const char *file, int line)
{ if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(l->mutex);
  else
    MUTEX_UNLOCK(l->mutex);
}

static void dyn_destroy_function(struct CRYPTO_dynlock_value *l, const char *file, int line)
{ MUTEX_CLEANUP(l->mutex);
  free(l);
}

void locking_function(int mode, int n, const char *file, int line)
{ if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(mutex_buf[n]);
  else
    MUTEX_UNLOCK(mutex_buf[n]);
}

unsigned long id_function()
{ return (unsigned long)THREAD_ID;
}

int CRYPTO_thread_setup()
{ int i;
  mutex_buf = (MUTEX_TYPE*)malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
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
{ int i;
  if (!mutex_buf)
    return;
  CRYPTO_set_id_callback(NULL);
  CRYPTO_set_locking_callback(NULL);
  CRYPTO_set_dynlock_create_callback(NULL);
  CRYPTO_set_dynlock_lock_callback(NULL);
  CRYPTO_set_dynlock_destroy_callback(NULL);
  for (i = 0; i < CRYPTO_num_locks(); i++)
    MUTEX_CLEANUP(mutex_buf[i]);
  free(mutex_buf);
  mutex_buf = NULL;
}

#else

/* OpenSSL not used */

int CRYPTO_thread_setup()
{ return SOAP_OK;
}

void CRYPTO_thread_cleanup()
{ }

#endif

