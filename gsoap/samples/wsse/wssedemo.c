/*
	wssedemo.c

	WS-Security plugin demo application. See comments below.

gSOAP XML Web services tools
Copyright (C) 2000-2008, Robert van Engelen, Genivia Inc., All Rights Reserved.
This part of the software is released under one of the following licenses:
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

This application demonstrates the use of the wsse plugin.

Compile:

wsdl2h -c -t typemap.dat wssedemo.wsdl
soapcpp2 -I import wssedemo.h
cc -DWITH_OPENSSL -DWITH_DOM -o wssedemo wssedemo.c wsseapi.c smdevp.c dom.c stdsoap2.c soapC.c soapClient.c soapServer.c -lcrypto -lssl

Other required files:

server.pem
cacert.pem

Note:

The wsse.h, wsu.h, ds.h, c14n.h files are located in 'import'.
The smdevp.* and wsseapi.* files are located in 'plugin'.

Usage: wssedemo cinhkst [port]

with options:

a sign the ns:add operation in the SOAP Body (use option b to remove Body sig)
b don't sign the entire SOAP Body (signed by default)
c use chunked HTTP
h use hmac symmetric key
i indent XML
k don't use keys
n canonical XML
s server
t use plain-text passwords (password digest by default)
x use plain XML (no HTTP header), client only
y buffered sends (experimental, not critical)
z compressed sends/recv

For example, to generate a request message and store it in file 'wssedemo.xml':

./wssedemo in > wssedemo.xml < /dev/null

To parse and verify this request message:

./wssedemo ins < wssedemo.xml

Alternatively, using HMAC (fast but uses shared symmetric keys):

./wssedemo ihn > wssedemo.xml < /dev/null
./wssedemo ihns < wssedemo.xml

To run a stand-alone server:

./wssedemo ins 8080

And invoking it with a client:

./wssedemo in 8080

*/

#include "smdevp.h"
#include "wsseapi.h"
#include "wssetest.nsmap"

/* The client and server side use the same certificates and keys for demonstration purposes */
X509 *cert = NULL;
EVP_PKEY *rsa_privk = NULL, *rsa_pubk = NULL;

/* The secret HMAC key is shared between client and server */
static char hmac_key[16] = /* Not-so-random HMAC key for testing */
{ 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
  0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 };

int addsig = 0;
int nobody = 0;
int hmac = 0;
int nokey = 0;
int nohttp = 0;

int main(int argc, char **argv)
{ struct soap *soap;
  int server = 0;
  int text = 0;
  int port = 0;
  FILE *fd;
  double result;
  char *user;
  /* create context */
  soap = soap_new();
  /* register wsse plugin */
  soap_register_plugin(soap, soap_wsse);
  /* options */
  if (argc >= 2)
  { if (strchr(argv[1], 'c'))
      soap_set_omode(soap, SOAP_IO_CHUNK);
    else if (strchr(argv[1], 'y'))
      soap_set_omode(soap, SOAP_IO_STORE);
    if (strchr(argv[1], 'i'))
      soap_set_omode(soap, SOAP_XML_INDENT);
    if (strchr(argv[1], 'n'))
      soap_set_omode(soap, SOAP_XML_CANONICAL);
    if (strchr(argv[1], 'h'))
      hmac = 1;
    if (strchr(argv[1], 'k'))
      nokey = 1;
    if (strchr(argv[1], 's'))
      server = 1;
    if (strchr(argv[1], 't'))
      text = 1;
    if (strchr(argv[1], 'a'))
      addsig = 1;
    if (strchr(argv[1], 'b'))
      nobody = 1;
    if (strchr(argv[1], 'x'))
      nohttp = 1;
    if (strchr(argv[1], 'z'))
      soap_set_mode(soap, SOAP_ENC_ZLIB);
  }
  /* soap->actor = "..."; */ /* set only when required */
  user = getenv("USER");
  if (!user)
    user = "anyone";
  /* read RSA private key for signing */
  if ((fd = fopen("server.pem", "r")))
  { rsa_privk = PEM_read_PrivateKey(fd, NULL, NULL, (void*)"password");
    fclose(fd);
    if (!rsa_privk)
    { fprintf(stderr, "Could not read private RSA key from server.pem\n");
      exit(1);
    }
  }
  else
    fprintf(stderr, "Could not read server.pem\n");
  /* read certificate (more efficient is to keep certificate in memory): */
  if ((fd = fopen("server.pem", "r")))
  { cert = PEM_read_X509(fd, NULL, NULL, NULL);
    fclose(fd);
    if (!cert)
    { fprintf(stderr, "Could not read certificate from server.pem\n");
      exit(1);
    }
  }
  else
    fprintf(stderr, "Could not read server.pem\n");
  rsa_pubk = X509_get_pubkey(cert);
  if (!rsa_pubk)
  { fprintf(stderr, "Could not get public key from certificate\n");
    exit(1);
  }
  /* port argument */
  if (argc >= 3)
    port = atoi(argv[2]);
  /* need cacert to verify certificate */
  soap->cafile = "cacert.pem";
  /* server or client/ */
  if (server)
  { if (port)
    { /* stand-alone server serving messages over port */
      if (!soap_valid_socket(soap_bind(soap, NULL, port, 100)))
      { soap_print_fault(soap, stderr);
        exit(1);
      }
      printf("Server started at port %d\n", port);
      while (soap_valid_socket(soap_accept(soap)))
      { if (hmac)
          soap_wsse_verify_auto(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));
        else if (nokey)
          soap_wsse_verify_auto(soap, SOAP_SMD_VRFY_RSA_SHA1, rsa_pubk, 0);
        else
          soap_wsse_verify_auto(soap, SOAP_SMD_NONE, NULL, 0);
        if (soap_serve(soap))
        { soap_wsse_delete_Security(soap);
          soap_print_fault(soap, stderr);
          soap_print_fault_location(soap, stderr);
        }
      }
      soap_print_fault(soap, stderr);
      exit(1);
    }
    else
    { /* CGI-style server serving messages over stdin/out */
      if (hmac)
        soap_wsse_verify_auto(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));
      else if (nokey)
        soap_wsse_verify_auto(soap, SOAP_SMD_VRFY_RSA_SHA1, rsa_pubk, 0);
      else
        soap_wsse_verify_auto(soap, SOAP_SMD_NONE, NULL, 0);
      if (soap_serve(soap))
      { soap_wsse_delete_Security(soap);
        soap_print_fault(soap, stderr);
        soap_print_fault_location(soap, stderr);
      }
    }
  }
  else /* client */
  { char endpoint[80];
    /* client sending messages to stdout or over port */
    if (port)
      sprintf(endpoint, "http://localhost:%d", port);
    else if (nohttp)
      strcpy(endpoint, "");
    else
      strcpy(endpoint, "http://");
    /* message lifetime of 10 seconds */
    soap_wsse_add_Timestamp(soap, "Time", 10);
    /* add user name with text or digest password */
    if (text)
      soap_wsse_add_UsernameTokenText(soap, "User", user, "userPass");
    else
      soap_wsse_add_UsernameTokenDigest(soap, "User", user, "userPass");
    if (hmac)
    { if (nobody)
        soap_wsse_sign(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));
      else
        soap_wsse_sign_body(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));
    }
    else
    { if (nokey)
        soap_wsse_add_KeyInfo_KeyName(soap, "MyKey");
      else
      { soap_wsse_add_BinarySecurityTokenX509(soap, "X509Token", cert);
        soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(soap, "#X509Token");
      }
      if (nobody)
        soap_wsse_sign(soap, SOAP_SMD_SIGN_RSA_SHA1, rsa_privk, 0);
      else
        soap_wsse_sign_body(soap, SOAP_SMD_SIGN_RSA_SHA1, rsa_privk, 0);
    }
    /* enable automatic signature verification of server responses */
    if (hmac)
      soap_wsse_verify_auto(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));
    else if (nokey)
      soap_wsse_verify_auto(soap, SOAP_SMD_VRFY_RSA_SHA1, rsa_pubk, 0);
    else
      soap_wsse_verify_auto(soap, SOAP_SMD_NONE, NULL, 0);
    /* sign the response message in unsigned body? If so, set wsu:Id */
    if (addsig)
      soap_wsse_set_wsu_id(soap, "ns1:add");
    /* invoke the server. You can choose add, sub, mul, or div operations
     * that show different security aspects for demonstration purposes
     * (see server operations below) */
    if (!soap_call_ns1__add(soap, endpoint, NULL, 1.0, 2.0, &result))
    { if (!soap_wsse_verify_Timestamp(soap))
      { const char *servername = soap_wsse_get_Username(soap);
        if (servername
	 && !strcmp(servername, "server")
         && !soap_wsse_verify_Password(soap, "serverPass"))
          printf("Result = %g\n", result);
        else
	{ fprintf(stderr, "Server authentication failed\n");
          soap_print_fault(soap, stderr);
        }
      }
      else
      { fprintf(stderr, "Server response expired\n");
        soap_print_fault(soap, stderr);
      }
    }
    else
    { soap_print_fault(soap, stderr);
      soap_print_fault_location(soap, stderr);
    }
    /* clean up security header */
    soap_wsse_delete_Security(soap);
    /* disable soap_wsse_verify_auto */
    soap_wsse_verify_done(soap);
  }
  /* clean up keys */
  if (rsa_privk)
    EVP_PKEY_free(rsa_privk);
  if (rsa_pubk)
    EVP_PKEY_free(rsa_pubk);
  if (cert)
    X509_free(cert);
  /* clean up gSOAP engine */
  soap_end(soap);
  soap_done(soap);
  free(soap);
  /* done */
  return 0;
}

int ns1__add(struct soap *soap, double a, double b, double *result)
{ const char *username = soap_wsse_get_Username(soap);
  if (username)
    fprintf(stderr, "Hello %s, want to add %g + %g = ?\n", username, a, b);
  if (soap_wsse_verify_Timestamp(soap)
   || soap_wsse_verify_Password(soap, "userPass"))
  { soap_wsse_delete_Security(soap);
    return soap->error;
  }
  if (soap_wsse_verify_element(soap, "http://www.genivia.com/schemas/wssetest.xsd", "add") == 0)
  { soap_wsse_delete_Security(soap);
    return soap_sender_fault(soap, "Service operation not signed", NULL);
  }
  soap_wsse_delete_Security(soap);
  soap_wsse_add_Timestamp(soap, "Time", 10);	/* lifetime of 10 seconds */
  soap_wsse_add_UsernameTokenDigest(soap, "User", "server", "serverPass");
  if (hmac)
  { if (nobody)
      soap_wsse_sign(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));
    else
      soap_wsse_sign_body(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));
  }
  else
  { if (nokey)
      soap_wsse_add_KeyInfo_KeyName(soap, "MyKey");
    else
    { soap_wsse_add_BinarySecurityTokenX509(soap, "X509Token", cert);
      soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(soap, "#X509Token");
    }
    if (nobody)
      soap_wsse_sign(soap, SOAP_SMD_SIGN_RSA_SHA1, rsa_privk, 0);
    else
      soap_wsse_sign_body(soap, SOAP_SMD_SIGN_RSA_SHA1, rsa_privk, 0);
  }
  /* sign the response message in unsigned body? If so, set wsu:Id */
  if (addsig)
    soap_wsse_set_wsu_id(soap, "ns1:addResponse");
  *result = a + b;
  return SOAP_OK;
}

int ns1__sub(struct soap *soap, double a, double b, double *result)
{ const char *username = soap_wsse_get_Username(soap);
  if (username)
    fprintf(stderr, "Hello %s, want to subtract %g - %g = ?\n", username, a, b);
  if (soap_wsse_verify_Timestamp(soap)
   || soap_wsse_verify_Password(soap, "userPass"))
  { soap_wsse_delete_Security(soap);
    return soap->error;
  }
  if (soap_wsse_verify_element(soap, "http://www.genivia.com/schemas/wssetest.xsd", "sub") == 0)
  { soap_wsse_delete_Security(soap);
    return soap_sender_fault(soap, "Service operation not signed", NULL);
  }
  soap_wsse_delete_Security(soap);
  /* In this case we leave out the timestamp, which is the sender's
   * responsibility to add. The receiver only complains if the timestamp is out
   * of date, not that it is absent. */
  if (hmac)
    soap_wsse_sign_body(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));
  else
  { if (nokey)
      soap_wsse_add_KeyInfo_KeyName(soap, "MyKey");
    else
    { soap_wsse_add_BinarySecurityTokenX509(soap, "X509Token", cert);
      soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(soap, "#X509Token");
    }
    soap_wsse_sign_body(soap, SOAP_SMD_SIGN_RSA_SHA1, rsa_privk, 0);
  }
  *result = a - b;
  return SOAP_OK;
}

int ns1__mul(struct soap *soap, double a, double b, double *result)
{ const char *username = soap_wsse_get_Username(soap);
  if (username)
    fprintf(stderr, "Hello %s, want to multiply %g * %g = ?\n", username, a, b);
  if (soap_wsse_verify_Timestamp(soap)
   || soap_wsse_verify_Password(soap, "userPass"))
  { soap_wsse_delete_Security(soap);
    return soap->error;
  }
  if (soap_wsse_verify_element(soap, "http://www.genivia.com/schemas/wssetest.xsd", "mul") == 0)
  { soap_wsse_delete_Security(soap);
    return soap_sender_fault(soap, "Service operation not signed", NULL);
  }
  soap_wsse_delete_Security(soap);
  soap_wsse_add_Timestamp(soap, "Time", 10);	/* lifetime of 10 seconds */
  /* In this case we leave out the server name and password. Because the
   * receiver check the presence of authentication information, the client will
   * reject the response. */
  if (hmac)
    soap_wsse_sign_body(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));
  else
  { if (nokey)
      soap_wsse_add_KeyInfo_KeyName(soap, "MyKey");
    else
    { soap_wsse_add_BinarySecurityTokenX509(soap, "X509Token", cert);
      soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(soap, "#X509Token");
    }
    soap_wsse_sign_body(soap, SOAP_SMD_SIGN_RSA_SHA1, rsa_privk, 0);
  }
  *result = a * b;
  return SOAP_OK;
}

int ns1__div(struct soap *soap, double a, double b, double *result)
{ const char *username = soap_wsse_get_Username(soap);
  if (username)
    fprintf(stderr, "Hello %s, want to divide %g / %g = ?\n", username, a, b);
  if (soap_wsse_verify_Timestamp(soap)
   || soap_wsse_verify_Password(soap, "userPass"))
  { soap_wsse_delete_Security(soap);
    return soap->error;
  }
  if (soap_wsse_verify_element(soap, "http://www.genivia.com/schemas/wssetest.xsd", "div") == 0)
  { soap_wsse_delete_Security(soap);
    return soap_sender_fault(soap, "Service operation not signed", NULL);
  }
  soap_wsse_delete_Security(soap);
  soap_wsse_add_Timestamp(soap, "Time", 10);	/* lifetime of 10 seconds */
  soap_wsse_add_UsernameTokenDigest(soap, "User", "server", "serverPass");
  /* In this case we leave out the signature and the receiver will reject this
   * unsigned message. */
  if (b == 0.0)
    return soap_sender_fault(soap, "Division by zero", NULL);
  *result = a / b;
  return SOAP_OK;
}

