/*

wsse2api.c

WS-Security plugin

gSOAP XML Web services tools
Copyright (C) 2000-2005, Robert van Engelen, Genivia Inc., All Rights Reserved.
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
Copyright (C) 2000-2005, Robert van Engelen, Genivia Inc., All Rights Reserved.
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

/**

@mainpage

- @ref wsse documents the wsse plugin for WS-Security 1.0 support.
- @ref smdevp documents the smdevp engine used by the wsse plugin.

*/

/**

@page wsse The wsse plugin

@section wsse_5 Security Header

The material in this section relates to the WS-Security specification section 5.

To use the wsse plugin:
-# Run wsdl2h -t typemap.dat on a WSDL of a service that requires WS-Security
   headers. The typemap.dat file is used to recognize and translate Security
   header blocks.
-# Run soapcpp2 on the header file produced by wsdl2h.
-# (Re-)compile stdsoap2.c/pp, dom.c/pp, smdevp.c, wsseapi.c and the generated
   source files with the -DWITH_DOM and -DWITH_OPENSSL compile flags set. The
   smdevp.c and wssapi.c files are located in the 'plugin' directory.
-# Use the wsse plugin API functions described below to add and verify
   Security headers.

An example wsse client/server application can be found in samples/wsse.

The Security header block was generated from the WS-Security schema with the
wsdl2h tool and WS/WS-typemap.dat:

@code
    $ wsdl2h -cegxy -o wsse.h -t WS/WS-typemap.dat WS/wsse.xsd
@endcode

The same process was used to generate the header file ds.h from the XML digital
signatures core schema.

The import/wsse.h file has the following definition for the Security header
block:

@code
typedef struct _wsse2__Security
{       struct _wsu__Timestamp*                 wsu__Timestamp;
        struct _wsse2__UsernameToken*            UsernameToken;
        struct _wsse2__BinarySecurityToken*      BinarySecurityToken;
        struct ds__SignatureType*               ds__Signature;
        @char*                                  SOAP_ENV__actor;
        @char*                                  SOAP_ENV__role;
} _wsse2__Security;
@endcode

To add an empty Security header block to the SOAP header, use:

@code
    soap_wsse_add_Security(soap);
@endcode

To delete a Security header, use:

@code
    soap_wsse_delete_Security(soap);
@endcode

Adding an empty Security header block is not very useful. We will mainly make
use of the higher-level functions of the wsse plugin to populate and verify
Security header content.

Note: The soap context includes an actor value soap.actor that is populated and
rendered as the SOAP-ENV:actor (SOAP 1.1) or SOAP-ENV:role (SOAP 1.2) attribute
in XML within the generic SOAP Header. The attribute is optional, but should be
used to target a recipient such as an intermediate node to process the SOAP
header.  In contrast, actor or role attributes within Security header blocks
target specific recipients to process the Security header block. The gSOAP
implementation does not automate this feature and application should set and
check the actor/role attribute when necessary. In addition, the current
implementation supports the inclusion of a single Security header block in the
SOAP header.

To populate the SOAP-ENV:actor or SOAP-ENV:role attribute within the Security
header, use:

@code
    soap_wsse_add_Security_actor(soap, "recipient");
@endcode

To obtain the actor or role value (e.g. after receiving a message), use:

@code
    _wsse2__Security *security = soap_wsse_Security(soap);
    if (security)
    { ... = security->SOAP_ENV__actor; // SOAP 1.1
      ... = security->SOAP_ENV__role;  // SOAP 1.2
@endcode

The SOAP-ENV:mustUnderstand attribute is automatically added and checked by the
gSOAP engine. A gSOAP application compiled without Security support will reject
Security headers.

Security header blocks are attached to the soap context, which means that the
information will be automatically kept to support multiple invocations.

@section wsse_6 Security Tokens

The material in this section relates to the WS-Security specification section 6.

@subsection wsse_6_2 User Name Token

To add a user name token to the Security header block, use:

@code
    soap_wsse_add_UsernameTokenText(soap, "Id", "username", NULL);
@endcode

The Id value is optional. When non-NULL the user name token is included in the
digital signature to protect its integrity. It is common for the wsse plugin
functions to accept such Ids, which are serialized as wsu:Id identifiers for
cross-referencing XML elements. The signature engine of the wsse plugin is
designed to automatically sign all wsu:Id attributed elements to simplify the
code you need to write to implement the signing process.

To add a user name token with clear text password, use:

@code
    soap_wsse_add_UsernameTokenText(soap, "Id", "username", "password");
@endcode

It is strongly recommended to use @ref soap_wsse_add_UsernameTokenText only in
combination with HTTPS encrypted transmission or not at all. A better
alternative is to use password digests. With password digest authentication,
the digest value of a password (with message creation time and a random nonce)
is compared on both sides, thus eliminating the need to exchange a password
over the wire.

To add a user name token with password digest, use:

@code
    soap_wsse_add_UsernameTokenDigest(soap, "Id", "username", "password");
@endcode

Although the password string is passed to this function, it is not rendered in
XML or stored in a message log. It has been argued that this approach adopted
by the WS-Security protocol is still vulnerable since the application retrieves
the password in text form requiring a database to store passwords in clear
text. However, a digest algorithm can be used to hash the passwords and store
their digests instead, which eliminates the need to store clear-text passwords.
Note that this is a common approach adopted by Unix for decades.

By setting the Id value to a unique string, the user name token is also
digitally signed by the signature engine further preventing tampering with its
value.

You must use @ref soap_wsse_add_UsernameTokenDigest for each message exchange
to refresh the password digest even when the user name and password are not
changed. Otherwise, the receiver might flag the message as a replay attack.

Clear-text passwords and password digests are verified with
@ref soap_wsse_verify_Password. To verify a password at the receiving side to
authorize a request (e.g. within a Web service operation), use:

@code
    int ns__myMethod(struct soap *soap, ...)
    { const char *username = soap_wsse_get_Username(soap);
      const char *password;
      if (!username)
        return soap->error; // no username: return FailedAuthentication
      password = ...; // lookup password of username
      if (soap_wsse_verify_Password(soap, password))
        return soap->error; // password verification failed: return FailedAuthentication
      ... // process request
      return SOAP_OK;
    }
@endcode

Note that the @ref soap_wsse_get_Username functions sets the
wsse:FailedAuthentication fault. It is common for the wsse plugin functions to
return SOAP_OK or a wsse fault that should be passed to the sender by returning
soap->error from service operations. The fault is displayed with the @ref
soap_print_fault function.

Password digest authentication prevents message replay attacks. The wsse plugin
keeps a database of password digests to thwart replay attacks. This is the
only part in the plugin code that requires mutex provided by threads.h.  Of
course, this only works correctly if the server is persistent, such as a
stand-alone service. Note that CGI-based services do not keep state. Machine
clocks must be synchronized and clock skew should not exceed @ref
SOAP_WSSE_CLKSKEW at the server side.

@subsection wsse_6_3 Binary Security Tokens

X509 certificates are commonly included in Security header blocks as binary
security tokens. A certificate is used to verify the digital signature of a
digitally signed message using the public key embedded within the certificate.
The certificate itself is signed by a certificate authority (CA) that vouches
for the authenticity of the certificate, i.e. to prove the identify of the
message originator. This verification process is important, because digital
signatures are useless without verification: an attacker could simply replace
the message, sign it, and replace the certificate.

Certificates are automatically verified by the wsse plugin signature engine
when received and accessed, which means that the certificates of the CAs must
be made accessible to the wsse plugin as follows:

@code
    soap->cafile = "cacerts.pem";  // use this
    soap->capath = "dir/to/certs"; // and/or point to CA certs
    soap->crlfile = "revoked.pem"; // use CRL (optional)
@endcode

The @ref soap_wsse_verify_X509 function checks the validity of a certificate.
The check is automatically performed. The check is also performed when
retrieving the certificate from a Security header block, either automatically
by the wsse plugin's signature verification engine or manually as follows:

@code
    X509 *cert = soap_wsse_get_BinarySecurityTokenX509(soap, "Id");
@endcode

where Id is the identification string of the binary security token or NULL.

The verification is an expensive process that will be optimized in future
releases by caching the certificate chain.

To attach a binary security token stored in a PEM file to a Security header
block for transmission, use:

@code
    soap_wsse_add_BinarySecurityTokenPEM(soap, NULL, "mycert.pem")
@endcode

A binary security token can be automatically signed by setting its Id
attribute:

@code
    soap_wsse_add_BinarySecurityTokenPEM(soap, "X509Token", "mycert.pem")
@endcode

Repeatedly loading a certificate from a PEM file is inefficient. To reuse a
certificate loaded from a PEM file for multiple invocations, use:

@code
    FILE *fd = fopen("mycert.pem", "r");
    X509 *cert = PEM_read_X509(fd, NULL, NULL, NULL);
    fclose(fd);
    if (soap_wsse_add_BinarySecurityTokenX509(soap, "X509Token", cert))
      ... // an error occurred
@endcode

Other types of binary security tokens can be added to the Security header block using:

@code
    soap_wsse_add_BinarySecurityToken(soap, "Id", "valueType", data, datalen);
@endcode

@section wsse_6_4 XML Tokens

The use and processing rules for XML tokens such as SAML assertions is specific
to an application.  The wsse plugin does not automate the use of XML tokens.
The developer is encouraged to generate code for the SAML schema with wsdl2h
and add the necessary assertions to the Security header block:

@code
typedef struct _wsse2__Security
{       struct _wsu__Timestamp*                 wsu__Timestamp;
        struct _wsse2__UsernameToken*            UsernameToken;
        struct _wsse2__BinarySecurityToken*      BinarySecurityToken;
        struct _saml__Assertion*		saml__Assertion; // added
        struct ds__SignatureType*               ds__Signature;
        @char*                                  SOAP_ENV__actor;
        @char*                                  SOAP_ENV__role;
} _wsse2__Security;
@endcode

Alternatively, a DOM can be used to store and retrieve XML tokens:

@code
#import "dom.h"
typedef struct _wsse2__Security
{       struct _wsu__Timestamp*                 wsu__Timestamp;
        struct _wsse2__UsernameToken*            UsernameToken;
        struct _wsse2__BinarySecurityToken*      BinarySecurityToken;
        struct ds__SignatureType*               ds__Signature;
        int					__size;
        xsd__anyType*				any;
        @char*                                  SOAP_ENV__actor;
        @char*                                  SOAP_ENV__role;
} _wsse2__Security;
@endcode

@section wsse_7 Token References

The material in this section relates to the WS-Security specification section 7.

To use a certificate for signature verification, add a direct security token
reference URI for the token to the KeyInfo, for example:

@code
    soap_wsse_add_KeyInfo_SecurityTokenReferenceURI(soap, "URI", "valueType");
@endcode

and:

@code
    soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(soap, "URI");
@endcode

For X509 certificates we use this to add a binary security token with the
certificate and a reference to the local token:

@code
    if (soap_wsse_add_BinarySecurityTokenX509(soap, "X509Token", cert)
     || soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(soap, "#X509Token"))
      ... // an error occurred
@endcode

This follows the recommended practice to place Security token references in
the KeyInfo element of a Signature. The KeyInfo is used to verify the validity
of a signature value.

Key identifiers can be used as well:

@code
    soap_wsse_add_KeyInfo_SecurityTokenReferenceKeyIdentifier(soap, "Id", "valueType", data, datalen);
@endcode

Embedded references are added with:

@code
    soap_wsse_add_KeyInfo_SecurityTokenReferenceEmbedded(soap, "Id", "valueType");
@endcode

Full support for embedded references requires coding to add tokens and
assertions, as well as to consume embedded references at the receiving side.
There is no automated mechanism to take the embedded references and process
them accordingly.

The use of key names is not recommended, but in case they are required they can
be added with:

@code
    soap_wsse_add_KeyInfo_KeyName(soap, "name");
@endcode

@section wsse_8 Signatures

The material in this section relates to the WS-Security specification section 8.

The wsse plugin must be registered to sign and verify messages:

@code
    soap_register_plugin(soap, soap_wsse);
@endcode

XML signatures are usually computed over normalized XML (to ensure the XML
processors of intermediate nodes can accurately reproduce the XML). To this
end, the exclusive canonical XML standard (exc-c14n) is required, which is set
using the SOAP_XML_CANONICAL flag:

@code
    struct soap *soap = soap_new1(SOAP_XML_CANONICAL);
    soap_register_plugin(soap, soap_wsse);
@endcode

If you prefer XML indentation, use:

@code
    struct soap *soap = soap_new1(SOAP_XML_CANONICAL | SOAP_XML_INDENT);
    soap_register_plugin(soap, soap_wsse);
@endcode

Next, we decide which signature algorithm is appropriate to use:
- HMAC-SHA1 uses a secret key (also known as a shared key in symmetric
  cryptography) to sign the SHA1 digest of the SignedInfo element.
- DSA-SHA1 uses a DSA private key to sign the SHA1 digest of the SignedInfo
  element.
- RSA-SHA1 uses a RSA private key to sign the SHA1 digest of the SignedInfo
  element.

HMAC-SHA1 is the simplest method, but relies on the fact that you have to make
absolutely sure the key is kept secret on both the sending and receiving side.
As long as the secret key is confidential, messages are securely signed.
However, this is virtually impossible when exchanging messages with untrusted
disparate parties. The advantage of HMAC-SHA1 is the speed by which messages
are signed and verified.

DSA-SHA1 and RSA-SHA1 rely on public key cryptography. In simplified terms, a
message is signed using the (confidential!) private key. The public key is used
to verify the signature. Since only the originating party could have used its
private key to sign the message, the integrity of the message is guaranteed. Of
course, we must trust the public key came from the originator (it is often
included as an X509 certificate in the message). To this end, a trusted
certificate authority should have signed the public key, thereby creating a
X509 certificate that contains the public key and the identity of the message
originator.

@subsection wsse_8_2a Signing Messages

After the plugin is registered and a signature algorithm selected, the
@ref soap_wsse_sign function or the @ref soap_wsse_sign_body function is used
to initiate the signature engine to automatically sign outbound messages.

The code to sign the SOAP Body of a message using HMAC-SHA1 is:

@code
    static char hmac_key[16] =
    { 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
      0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 };
    struct soap *soap = soap_new1(SOAP_XML_CANONICAL | SOAP_XML_INDENT);
    soap_register_plugin(soap, soap_wsse);
    if (soap_wsse_sign_body(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key))
      ... // an error occurred
    else if (soap_call_ns__myMethod(soap, ...))
      ... // a transmission error occurred
@endcode

The hmac_key is some secret key you generated for the sending side and
receiving side (don't use the one shown here).

As always, use @ref soap_print_fault to display the error message.

To sign the body of an outbound SOAP message using RSA-SHA1 (DSA-SHA1 is
similar), we include the X509 certificate with the public key as a
BinarySecurityToken in the header and a KeyInfo reference to the token to let
receivers use the public key in the certificate to verify the authenticity of
the message:

@code
    FILE *fd;
    EVP_PKEY *rsa_private_key;
    X509 *cert;
    struct soap *soap = soap_new1(SOAP_XML_CANONICAL | SOAP_XML_INDENT);
    soap_register_plugin(soap, soap_wsse);
    fd = fopen("privkey.pem", "r");
    rsa_private_key = PEM_read_PrivateKey(fd, NULL, NULL, "password");
    fclose(fd);
    fd = fopen("cert.pem", "r");
    X509 *cert = PEM_read_X509(fd, NULL, NULL, NULL);
    fclose(fd);
    if (soap_wsse_add_BinarySecurityTokenX509(soap, "X509Token", cert)
     || soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(soap, "#X509Token")
     || soap_wsse_sign_body(soap, SOAP_SMD_SIGN_RSA_SHA1, rsa_private_key, 0))
      ... // an error occurred
    else if (soap_call_ns__myMethod(soap, ...))
      ... // a transmission error occurred
@endcode

The private key and its certificate are often placed in the same file, see e.g.
server.pem in the package.

To summarize the signing process:
-# Register the wsse plugin.
-# Obtain an HMAC secret key or a DSA or RSA private key.
-# For DSA or RSA, obtain the X509 certificate with the public key signed by a
   certificate authority.
-# Add the X509 certificate as a BinarySecurityToken to the header.
-# Add a KeyInfo BinarySecurityTokenReference.
-# Invoke @ref soap_wsse_sign or @ref soap_wsse_sign_body to sign the message.
-# Always check the function return values for errors. You don't want to
   produce and accept messages with an invalid Security headers.

@subsection wsse_8_2b Signing Message Parts

The @ref soap_wsse_sign_body function signs the entire SOAP body. If it is
desirable to sign individual parts of a message the @ref soap_wsse_sign
function should be used. Message parts with wsu:Id attributes are signed. These
message parts should not be nested (nested elements will not be separately
signed).

For example, consider a transaction in which we only want to sign a contract in
the SOAP Body. This allows us to modify the rest of the message or extract the
contract in XML and pass it on with the signature.

The gSOAP header file includes a myContract declaration:

@code
    struct ns__myContract
    { @char* wsu_Id = "Contract";
      char* name;
      char* title;
      char* terms;
    };
    int ns__myMethod(struct ns__myContract agreement, bool* accepted);
@endcode

The default value of the wsu:Id is "Contract" so that we can instantiate the
struct, automatically sign it, and send it as follows:

@code
    struct ns__myContract contract;
    bool accept;
    soap_default_ns__myContract(soap, &contract);
    contract.name = ...;
    contract.title = ...;
    contract.terms = ...;
    if (soap_wsse_add_BinarySecurityTokenX509(soap, "X509Token", cert)
     || soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(soap, "#X509Token")
     || soap_wsse_sign(soap, SOAP_SMD_SIGN_RSA_SHA1, rsa_private_key, 0))
      ... // an error occurred
    else if (soap_call_ns__myMethod(soap, contract, &accept))
      ... // a transmission error occurred
@endcode

@subsection wsse_8_3 Signing Tokens

To sign security tokens such as user names, passwords, and binary security
tokens, just assign their Id values with a unique string, such as "Time" for
timestamps and "User" for user names. For example:

@code
    soap_wsse_add_Timestamp(soap, "Time", 600);
    soap_wsse_add_UsernameTokenDigest(soap, "User", "username", "password");
    ... // the rest of the signing code
@endcode

@subsection wsse_8_4 Signature Validation

To automatically verify the signature of an inbound message signed with DSA or
RSA algorithms, assuming the message contains the X509 certificate as a binary
security token, use:

@code
    struct soap *soap = soap_new1(SOAP_XML_CANONICAL | SOAP_XML_INDENT);
    soap_register_plugin(soap, soap_wsse);
    soap_wsse_verify_auto(soap, SOAP_SMD_NONE, NULL, 0);

    // server:
    if (soap_serve(soap))
      ... // an error occurred

    // client:
    if (soap_call_ns__myMethod(soap, ...))
      ... // an error occurred
@endcode

All locally referenced elements in the signed message will be verified.
Elements referenced with absolute URIs are not automatically verified. The
received message is stored in a DOM accessible with soap->dom. This enables
further analysis of the message content.

The @ref soap_wsse_verify_auto function keeps processing signed (and unsigned)
messages as they arrive. For unsigned messages this can be expensive and the
verification engine should be shut down using @ref soap_wsse_verify_done.

To verify the HMAC signature of an inbound message, the HMAC key must be
supplied:

@code
    static char hmac_key[16] = // the same secret key that was used to sign
    { 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
      0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 };
    struct soap *soap = soap_new1(SOAP_XML_CANONICAL | SOAP_XML_INDENT);
    soap_register_plugin(soap, soap_wsse);
    soap_wsse_verify_auto(soap, SOAP_SMD_HMAC_SHA1, hmac_key, sizeof(hmac_key));

    // server:
    if (soap_serve(soap))
      ... // an error occurred

    // client:
    if (soap_call_ns__myMethod(soap, ...))
      ... // an error occurred
@endcode

To summarize the signature verification process:
-# Register the wsse plugin.
-# For HMAC, obtain the HMAC secret key
-# Use @ref soap_wsse_verify_auto to verify inbound messages.
-# After receiving a message, the DOM in soap->dom can be traversed for further    analysis.
-# Always check the function return values for errors. You don't want to accept
   a request or response message with an invalid Security header.
-# Use @ref soap_wsse_verify_done to terminate verification, e.g. to consume
   plain messages more efficiently.

@section wsse_9 Encryption

The material in this section relates to the WS-Security specification section 9.

TODO item: encryption support is under construction.

@section wsse_10 Security Timestamps

The material in this section relates to the WS-Security specification section
10.

To add a timestamp with the creation time to the Security header, use:

@code
    soap_wsse_add_Timestamp(soap, NULL, 0); // no expiration
@endcode

The lifetime of a message (in seconds) is passed as the third argument, which
will be displayed as the timestamp expiration time:

@code
    soap_wsse_add_Timestamp(soap, NULL, 10); // 10 seconds lifetime
@endcode

Timestamps, like other header elements, are not automatically secured with a
digital signature. To secure a timestamp, we add an identifier (wsu:Id) to each
element we want the WS-Security plugin to sign thereby making it impossible for
someone to tamper with that part of the message. To do this for the timestamp,
we simply pass a unique identification string as the second argument:

@code
    soap_wsse_add_Timestamp(soap, "Time", 10); // timestamp will be signed
@endcode


*/

#include "wsseapi.h"
#include "smdevp.h"
#include "threads.h"	/* only need threads to enable mutex for MT */

/** Plugin identification for plugin registry */
const char soap_wsse_id[14] = SOAP_WSSE_ID;

/** Maximum number of SignedInfo References */
#define SOAP_WSSE_MAX_REF	(100)

/** Clock skew between machines (in sec) to fit message expiration in window */
#define SOAP_WSSE_CLKSKEW	(600)

/** Size of the random nonce */
#define SOAP_WSSE_NONCELEN	(20)
/** Digest authentication accepts messages that are not older than creation time + SOAP_WSSE_NONCETIME */
#define SOAP_WSSE_NONCETIME	(SOAP_WSSE_CLKSKEW + 240)

/******************************************************************************\
 *
 * Common URIs
 *
\******************************************************************************/

const char *wsse_PasswordTextURI = "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordText";
const char *wsse_PasswordDigestURI = "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordDigest";
const char *wsse_Base64BinaryURI = "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-soap-message-security-1.0#Base64Binary";
const char *wsse_X509v3URI = "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-x509-token-profile-1.0#X509v3";
const char *wsse_X509v3SubjectKeyIdentifierURI = "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-x509-token-profile-1.0#X509SubjectKeyIdentifier";

const char *ds_sha1URI = "http://www.w3.org/2000/09/xmldsig#sha1";
const char *ds_hmac_sha1URI = "http://www.w3.org/2000/09/xmldsig#hmac-sha1";
const char *ds_dsa_sha1URI = "http://www.w3.org/2000/09/xmldsig#dsa-sha1";
const char *ds_rsa_sha1URI = "http://www.w3.org/2000/09/xmldsig#rsa-sha1";

const char *ds_URI = "http://www.w3.org/2000/09/xmldsig#";
const char *c14n_URI = "http://www.w3.org/2001/10/xml-exc-c14n#";
const char *wsu_URI = "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd";

/******************************************************************************\
 *
 * Digest authentication session
 *
\******************************************************************************/

/**
@struct soap_wsse_session
@brief Digest authentication session data
*/
struct soap_wsse_session
{ struct soap_wsse_session *next;	/**< Next session in list */
  time_t expired;			/**< Session expiration */
  char hash[SOAP_SMD_SHA1_SIZE];	/**< SHA1 digest */
  char nonce[1]; /**< Nonce string flows into region below this struct */
};

/** The digest authentication session database */
static struct soap_wsse_session *soap_wsse_session = NULL;

/** Lock for digest authentication session database exclusive access */
static MUTEX_TYPE soap_wsse_session_lock;

static int soap_wsse_session_verify(struct soap *soap, const char hash[SOAP_SMD_SHA1_SIZE], const char *created, const char *nonce);
static void soap_wsse_session_cleanup(struct soap *soap);
static void calc_digest(struct soap *soap, const char *created, const char *nonce, int noncelen, const char *password, char hash[SOAP_SMD_SHA1_SIZE]);
static void calc_nonce(struct soap *soap, char nonce[SOAP_WSSE_NONCELEN]);

static int soap_wsse_init(struct soap *soap, struct soap_wsse_data *data, X509 *(*arg)(struct soap*));
static int soap_wsse_copy(struct soap *soap, struct soap_plugin *dst, struct soap_plugin *src);
static void soap_wsse_delete(struct soap *soap, struct soap_plugin *p);

static int soap_wsse_prepareinit(struct soap *soap);
static int soap_wsse_preparesend(struct soap *soap, const char *buf, size_t len);
static int soap_wsse_preparefinal(struct soap *soap);
static void soap_wsse_preparecleanup(struct soap *soap, struct soap_wsse_data *data);
static int soap_wsse_disconnect(struct soap *soap);

/******************************************************************************\
 *
 * wsse:Security header element
 *
\******************************************************************************/

/**
@fn _wsse2__Security* soap_wsse_add_Security(struct soap *soap)
@brief Adds Security header element.
@param soap context
@return _wsse2__Security object
*/
struct _wsse2__Security*
soap_wsse_add_Security(struct soap *soap)
{ DBGFUN("soap_wsse_add_Security");
  /* if we don't have a SOAP Header, create one */
  if (!soap->header)
  { soap->header = (struct SOAP_ENV__Header*)soap_malloc(soap, sizeof(struct SOAP_ENV__Header));
    soap_default_SOAP_ENV__Header(soap, soap->header); 
  }
  /* if we don't have a wsse:Security element in the SOAP Header, create one */
  if (!soap->header->wsse2__Security)
  { soap->header->wsse2__Security = (_wsse2__Security*)soap_malloc(soap, sizeof(_wsse2__Security));
    soap_default__wsse2__Security(soap, soap->header->wsse2__Security);
  }
  return soap->header->wsse2__Security;
}

/**
@fn _wsse2__Security* soap_wsse_add_Security_actor(struct soap *soap, const char *actor)
@brief Adds Security header element with actor or role attribute.
@param soap context
@param actor string
@return _wsse2__Security object
*/
struct _wsse2__Security*
soap_wsse_add_Security_actor(struct soap *soap, const char *actor)
{ _wsse2__Security *security = soap_wsse_add_Security(soap);
  DBGFUN1("soap_wsse_add_Security_actor", "actor=%s", actor);
  if (soap->namespaces && !strcmp(soap->namespaces[0].ns, "http://schemas.xmlsoap.org/soap/envelope/"))
    security->SOAP_ENV__actor = soap_strdup(soap, actor);
  else
    security->SOAP_ENV__role = soap_strdup(soap, actor);
  return security;
}

/**
@fn void soap_wsse_delete_Security(struct soap *soap)
@brief Deletes Security header element.
@param soap context
*/
void
soap_wsse_delete_Security(struct soap *soap)
{ DBGFUN("soap_wsse_delete_Security");
  if (soap->header)
    soap->header->wsse2__Security = NULL;
}

/**
@fn _wsse2__Security* soap_wsse_Security(struct soap *soap)
@brief Returns Security header element if present.
@param soap context
@return _wsse2__Security object or NULL
*/
struct _wsse2__Security*
soap_wsse_Security(struct soap *soap)
{ if (soap->header)
    return soap->header->wsse2__Security;
  return NULL;
}

/******************************************************************************\
 *
 * wsse:Security/ds:Signature header element
 *
\******************************************************************************/

/**
@fn ds__SignatureType* soap_wsse_add_Signature(struct soap *soap)
@brief Adds Signature header element.
@param soap context
@return ds__SignatureType object
*/
struct ds__SignatureType*
soap_wsse_add_Signature(struct soap *soap)
{ _wsse2__Security *security = soap_wsse_add_Security(soap);
  DBGFUN("soap_wsse_add_Signature");
  /* if we don't have a ds:Signature, create one */
  if (!security->ds__Signature)
  { security->ds__Signature = (ds__SignatureType*)soap_malloc(soap, sizeof(ds__SignatureType));
    soap_default_ds__SignatureType(soap, security->ds__Signature); 
  }
  return security->ds__Signature;
}

/**
@fn void soap_wsse_delete_Signature(struct soap *soap)
@brief Deletes Signature header element.
@param soap context
*/
void
soap_wsse_delete_Signature(struct soap *soap)
{ _wsse2__Security *security = soap_wsse_Security(soap);
  DBGFUN("soap_wsse_delete_Signature");
  if (security)
    security->ds__Signature = NULL;
}

/**
@fn ds__SignatureType* soap_wsse_Signature(struct soap *soap)
@brief Returns Signature header element if present.
@param soap context
@return ds__SignatureType object or NULL
*/
struct ds__SignatureType*
soap_wsse_Signature(struct soap *soap)
{ _wsse2__Security *security = soap_wsse_Security(soap);
  if (security)
    return security->ds__Signature;
  return NULL;
}

/******************************************************************************\
 *
 * wsse:Security/wsu:Timestamp header element
 *
\******************************************************************************/

/**
@fn int soap_wsse_add_Timestamp(struct soap *soap, const char *id, time_t lifetime)
@brief Adds Timestamp element with optional expiration date+time (lifetime).
@param[in] soap context
@param[in] id for signature referencing or NULL
@param[in] lifetime expressed in time_t units, or 0 for no expiration
@return SOAP_OK
*/
int
soap_wsse_add_Timestamp(struct soap *soap, const char *id, time_t lifetime)
{ _wsse2__Security *security = soap_wsse_add_Security(soap);
  time_t now = time(NULL);
  char *created = soap_strdup(soap, soap_dateTime2s(soap, now));
  char *expired = lifetime ? soap_strdup(soap, soap_dateTime2s(soap, now + lifetime)) : NULL;
  DBGFUN1("soap_wsse_add_Timestamp", "id=%s", id?id:"");
  /* allocate a Timestamp if we don't have one already */
  if (!security->wsu__Timestamp)
    security->wsu__Timestamp = (_wsu__Timestamp*)soap_malloc(soap, sizeof(_wsu__Timestamp));
  soap_default__wsu__Timestamp(soap, security->wsu__Timestamp);
  /* populate the wsu:Timestamp element */
  security->wsu__Timestamp->wsu__Id = soap_strdup(soap, id);
  security->wsu__Timestamp->Created = created;
  security->wsu__Timestamp->Expires = expired;
  return SOAP_OK;
}

/**
@fn _wsu__Timestamp *soap_wsse_Timestamp(struct soap *soap)
@brief Returns Timestamp element if present.
@param soap context
@return _wsu__Timestamp object or NULL
*/
struct _wsu__Timestamp*
soap_wsse_Timestamp(struct soap *soap)
{ _wsse2__Security *security = soap_wsse_Security(soap);
  if (security)
    return security->wsu__Timestamp;
  return NULL;
}

/**
@fn int soap_wsse_verify_Timestamp(struct soap *soap)
@brief Verifies the Timestamp/Expires element against the current time.
@param soap context
@return SOAP_OK or SOAP_FAULT with wsse:FailedAuthentication fault

Sets wsse:FailedAuthentication fault if wsu:Timestamp is expired. The
SOAP_WSSE_CLKSKEW value is used as a margin to mitigate clock skew. Keeps
silent when no timestamp is supplied or no expiration date is included in the
wsu:Timestamp element.
*/
int
soap_wsse_verify_Timestamp(struct soap *soap)
{ _wsu__Timestamp *timestamp = soap_wsse_Timestamp(soap);
  DBGFUN("soap_wsse_verify_Timestamp");
  /* if we have a timestamp with an expiration date, check it */
  if (timestamp && timestamp->Expires)
  { time_t now = time(NULL), expired;
    soap_s2dateTime(soap, timestamp->Expires, &expired);
    if (expired + SOAP_WSSE_CLKSKEW <= now)
    { const char *code = soap_wsu__tTimestampFault2s(soap, wsu__MessageExpired);
      return soap_sender_fault_subcode(soap, code, "Message has expired", timestamp->Expires);
    }
  }
  return SOAP_OK;
}

/******************************************************************************\
 *
 * wsse:Security/UsernameToken header element
 *
\******************************************************************************/

/**
@fn int soap_wsse_add_UsernameTokenText(struct soap *soap, const char *id, const char *username, const char *password)
@brief Adds UsernameToken element with optional clear-text password.
@param soap context
@param[in] id string for signature referencing or NULL
@param[in] username string
@param[in] password string or NULL to omit the password
@return SOAP_OK

Passwords are sent in the clear, so transport-level encryption is required.
Note: this release supports the use of at most one UsernameToken in the header.
*/
int
soap_wsse_add_UsernameTokenText(struct soap *soap, const char *id, const char *username, const char *password)
{ _wsse2__Security *security = soap_wsse_add_Security(soap);
  DBGFUN2("soap_wsse_add_UsernameTokenText", "id=%s", id?id:"", "username=%s", username?username:"");
  /* allocate a UsernameToken if we don't have one already */
  if (!security->UsernameToken)
    security->UsernameToken = (_wsse2__UsernameToken*)soap_malloc(soap, sizeof(_wsse2__UsernameToken));
  soap_default__wsse2__UsernameToken(soap, security->UsernameToken);
  /* populate the UsernameToken */
  security->UsernameToken->wsu__Id = soap_strdup(soap, id);
  security->UsernameToken->Username = soap_strdup(soap, username);
  /* allocate and populate the Password */
  if (password)
  { security->UsernameToken->Password = (_wsse2__Password*)soap_malloc(soap, sizeof(_wsse2__Password));
    soap_default__wsse2__Password(soap, security->UsernameToken->Password);
    security->UsernameToken->Password->Type = (char*)wsse_PasswordTextURI;
    security->UsernameToken->Password->__item = soap_strdup(soap, password);
  }
  return SOAP_OK;
}

/**
@fn int soap_wsse_add_UsernameTokenDigest(struct soap *soap, const char *id, const char *username, const char *password)
@brief Adds UsernameToken element for digest authentication.
@param soap context
@param[in] id string for signature referencing or NULL
@param[in] username string
@param[in] password string
@return SOAP_OK

Computes SHA1 digest of the time stamp, a nonce, and the password. The digest
provides the authentication credentials. Passwords are NOT sent in the clear.
Note: this release supports the use of at most one UsernameToken in the header.
*/
int
soap_wsse_add_UsernameTokenDigest(struct soap *soap, const char *id, const char *username, const char *password)
{ _wsse2__Security *security = soap_wsse_add_Security(soap);
  time_t now = time(NULL);
  const char *created = soap_dateTime2s(soap, now);
  char HA[SOAP_SMD_SHA1_SIZE], HABase64[29];
  char nonce[SOAP_WSSE_NONCELEN], *nonceBase64;
  DBGFUN2("soap_wsse_add_UsernameTokenDigest", "id=%s", id?id:"", "username=%s", username?username:"");
  /* generate a nonce */
  calc_nonce(soap, nonce);
  nonceBase64 = soap_s2base64(soap, (unsigned char*)nonce, NULL, SOAP_WSSE_NONCELEN);
  /* The specs are not clear: compute digest over binary nonce or base64 nonce? */
  /* compute SHA1(created, nonce, password) */
  calc_digest(soap, created, nonce, SOAP_WSSE_NONCELEN, password, HA);
  /*
  calc_digest(soap, created, nonceBase64, strlen(nonceBase64), password, HA);
  */
  soap_s2base64(soap, (unsigned char*)HA, HABase64, SOAP_SMD_SHA1_SIZE);
  /* populate the UsernameToken with digest */
  soap_wsse_add_UsernameTokenText(soap, id, username, HABase64);
  /* populate the remainder of the password, nonce, and created */
  security->UsernameToken->Password->Type = (char*)wsse_PasswordDigestURI;
  security->UsernameToken->Nonce = nonceBase64;
  security->UsernameToken->wsu__Created = soap_strdup(soap, created);
  return SOAP_OK;
}

/**
@fn _wsse2__UsernameToken* soap_wsse_UsernameToken(struct soap *soap, const char *id)
@brief Returns UsernameToken element if present.
@param soap context
@param[in] id string of UsernameToken or NULL
@return _wsse2__UsernameToken object or NULL

Note: this release supports the use of at most one UsernameToken in the header.
*/
struct _wsse2__UsernameToken*
soap_wsse_UsernameToken(struct soap *soap, const char *id)
{ _wsse2__Security *security = soap_wsse_Security(soap);
  if (security
   && security->UsernameToken
   && (!id || (security->UsernameToken->wsu__Id
            && !strcmp(security->UsernameToken->wsu__Id, id))))
    return security->UsernameToken;
  return NULL;
}

/**
@fn const char* soap_wsse_get_Username(struct soap *soap)
@brief Returns UsernameToken/username string or wsse:FailedAuthentication fault.
@param soap context
@return UsernameToken/username string or NULL with wsse:FailedAuthentication fault error set
@see soap_wsse_verify_Password

The returned username should be used to lookup the user's password in a
dictionary or database for server-side authentication with
soap_wsse_verify_Password.
*/
const char*
soap_wsse_get_Username(struct soap *soap)
{ _wsse2__UsernameToken *token = soap_wsse_UsernameToken(soap, NULL);
  DBGFUN("soap_wsse_get_Username");
  if (token)
    return token->Username;
  soap_wsse_fault(soap, wsse2__FailedAuthentication, "Authentication required");
  return NULL;
}

/**
@fn int soap_wsse_verify_Password(struct soap *soap, const char *password)
@brief Verifies the supplied password or sets wsse:FailedAuthentication fault.
@param soap context
@param[in] password string to verify against
@return SOAP_OK (authorized) or SOAP_FAULT with wsse:FailedAuthentication fault

The verification supports both clear-text password verification and digest
password authentication. For digest authentication a history mechanism with a
digest authentication session database ensures protection against replay
attacks.
Note: this release supports the use of at most one UsernameToken in the header.
*/
int
soap_wsse_verify_Password(struct soap *soap, const char *password)
{ _wsse2__UsernameToken *token = soap_wsse_UsernameToken(soap, NULL);
  DBGFUN("soap_wsse_verify_Password");
  /* if we have a UsernameToken with a Password, check it */
  if (token && token->Password)
  { /* password digest or text? */
    if (token->Password->Type
     && !strcmp(token->Password->Type, wsse_PasswordDigestURI))
    { /* check password digest: compute SHA1(created, nonce, password) */
      if (token->Nonce
       && token->wsu__Created
       && strlen(token->Password->__item) == 28)	/* digest pw len = 28 */
      { char HA1[SOAP_SMD_SHA1_SIZE], HA2[SOAP_SMD_SHA1_SIZE];
        /* The specs are not clear: compute digest over binary nonce or base64 nonce? The formet appears to be the case: */
        int noncelen;
        const char *nonce = soap_base642s(soap, token->Nonce, NULL, 0, &noncelen);
        /* compute HA1 = SHA1(created, nonce, password) */
        calc_digest(soap, token->wsu__Created, nonce, noncelen, password, HA1);
        /*
        calc_digest(soap, token->wsu__Created, token->Nonce, strlen(token->Nonce), password, HA1);
        */
        /* get HA2 = supplied digest from base64 Password */
        soap_base642s(soap, token->Password->__item, HA2, SOAP_SMD_SHA1_SIZE, NULL);
        /* compare HA1 to HA2 */
        if (!memcmp(HA1, HA2, SOAP_SMD_SHA1_SIZE))
        { /* authorize if HA1 and HA2 identical and not replay attack */
          if (!soap_wsse_session_verify(soap, HA1, token->wsu__Created, token->Nonce))
            return SOAP_OK;
          return soap->error; 
        }
      }
    }
    else
    { /* check password text */
      if (!strcmp(token->Password->__item, password))
        return SOAP_OK;
    }
  }
  return soap_wsse_fault(soap, wsse2__FailedAuthentication, "Authentication required");
}

/******************************************************************************\
 *
 * wsse:Security/BinarySecurityToken header element
 *
\******************************************************************************/

/**
@fn int soap_wsse_add_BinarySecurityToken(struct soap *soap, const char *id, const char *valueType, const unsigned char *data, int size)
@brief Adds BinarySecurityToken element.
@param soap context
@param[in] id string for signature referencing or NULL
@param[in] valueType string
@param[in] data points to binary token data
@param[in] size is length of binary token
@return SOAP_OK
*/
int
soap_wsse_add_BinarySecurityToken(struct soap *soap, const char *id, const char *valueType, const unsigned char *data, int size)
{ _wsse2__Security *security = soap_wsse_add_Security(soap);
  DBGFUN2("wsse_add_BinarySecurityToken", "id=%s", id?id:"", "valueType=%s", valueType?valueType:"");
  /* allocate BinarySecurityToken if we don't already have one */
  if (!security->BinarySecurityToken)
    security->BinarySecurityToken = (_wsse2__BinarySecurityToken*)soap_malloc(soap, sizeof(_wsse2__BinarySecurityToken));
  soap_default__wsse2__BinarySecurityToken(soap, security->BinarySecurityToken);
  /* populate the BinarySecurityToken */
  security->BinarySecurityToken->wsu__Id = soap_strdup(soap, id);
  security->BinarySecurityToken->ValueType = soap_strdup(soap, valueType);
  security->BinarySecurityToken->EncodingType = (char*)wsse_Base64BinaryURI;
  security->BinarySecurityToken->__item = soap_s2base64(soap, data, NULL, size);
  return SOAP_OK;
}

/**
@fn int soap_wsse_add_BinarySecurityTokenX509(struct soap *soap, const char *id, X509 *cert)
@brief Adds BinarySecurityToken element with X509 certificate.
@param soap context
@param[in] id string for signature reference
@param[in] cert points to the X509 certificate
@return SOAP_OK or SOAP_EOM

This function uses i2d_X509 from the the OpenSSL library to convert an X509
object to binary DER format.
*/
int
soap_wsse_add_BinarySecurityTokenX509(struct soap *soap, const char *id, X509 *cert)
{ int size;
  unsigned char *data, *next;
  if (!cert)
    return soap_wsse_fault(soap, wsse2__InvalidSecurityToken, "Invalid certificate");
  /* determine the storage requirement */
  size = i2d_X509(cert, NULL);
  if (size < 0)
    return soap_wsse_fault(soap, wsse2__InvalidSecurityToken, "Invalid certificate");
  /* use the gSOAP engine's look-aside buffer to temporarily hold the cert */
  if (soap_store_lab(soap, NULL, size))
    return SOAP_EOM;
  data = next = (unsigned char*)soap->labbuf;
  /* store in DER format */
  i2d_X509(cert, &next);
  /* populate the BinarySecurityToken with base64 certificate data */
  return soap_wsse_add_BinarySecurityToken(soap, id, wsse_X509v3URI, data, size);
}

/**
@fn int soap_wsse_add_BinarySecurityTokenPEM(struct soap *soap, const char *id, const char *filename)
@brief Adds BinarySecurityToken element from a PEM file.
@param soap context
@param[in] id string for signature reference
@param[in] filename
@return SOAP_OK or SOAP_FAULT with wsse2__InvalidSecurity fault when file cannot be read or does not contain a valid certificate

This function uses PEM_read_X509 from the the OpenSSL library to read a
certificate from a PEM formatted file.
*/
int
soap_wsse_add_BinarySecurityTokenPEM(struct soap *soap, const char *id, const char *filename)
{ FILE *fd;
  DBGFUN2("soap_wsse_add_BinarySecurityTokenPEM", "id=%s", id?id:"", "filename=%s", filename?filename:"");
  if ((fd = fopen(filename, "r")))
  { /* read the certificate */
    X509 *cert = PEM_read_X509(fd, NULL, NULL, NULL);
    fclose(fd);
    /* if okay, populate the BinarySecurityToken element */
    if (cert)
    { int err = soap_wsse_add_BinarySecurityTokenX509(soap, id, cert);
      X509_free(cert);
      return err;
    }
  }
  return soap_wsse_fault(soap, wsse2__InvalidSecurity, "No certificate");
}

/**
@fn _wsse2__BinarySecurityToken* soap_wsse_BinarySecurityToken(struct soap *soap, const char *id)
@brief Returns BinarySecurityToken element if present.
@param soap context
@param[in] id string of token to get or NULL
@return _wsse2__BinarySecurityToken object or NULL
*/
struct _wsse2__BinarySecurityToken*
soap_wsse_BinarySecurityToken(struct soap *soap, const char *id)
{ _wsse2__Security *security = soap_wsse_Security(soap);
  if (security
   && security->BinarySecurityToken
   && (!id || (security->BinarySecurityToken->wsu__Id
            && !strcmp(security->BinarySecurityToken->wsu__Id, id))))
    return security->BinarySecurityToken;
  return NULL;
}

/**
@fn int soap_wsse_get_BinarySecurityToken(struct soap *soap, const char *id, char **valueType, unsigned char **data, int *size)
@brief Get wsse:BinarySecurityToken element token data in binary form.
@param soap context
@param[in] id string of token to get or NULL
@param[out] valueType string
@param[out] data points to binary token data
@param[out] size is length of binary token
@return SOAP_OK or SOAP_FAULT with wsse:SecurityTokenUnavailable fault
*/
int
soap_wsse_get_BinarySecurityToken(struct soap *soap, const char *id, char **valueType, unsigned char **data, int *size)
{ _wsse2__BinarySecurityToken *token = soap_wsse_BinarySecurityToken(soap, id);
  DBGFUN1("soap_wsse_get_BinarySecurityToken", "id=%s", id?id:"");
  if (token)
  { *valueType = token->ValueType;
    /* it appears we don't need HexBinary after all
    if (token->EncodingType && !strcmp(token->EncodingType, wsse_HexBinaryURI))
      *data = (unsigned char*)soap_hex2s(soap, token->__item, NULL, 0, size);
    else
    */
    /* assume token is represented in base64 by default */
    *data = (unsigned char*)soap_base642s(soap, token->__item, NULL, 0, size);
    if (*data)
      return SOAP_OK;
  }
  return soap_wsse_fault(soap, wsse2__SecurityTokenUnavailable, "BinarySecurityToken required");
}

/**
@fn X509* soap_wsse_get_BinarySecurityTokenX509(struct soap *soap, const char *id)
@brief Get X509 wsse:BinarySecurityToken certificate and verify its content.
@param soap context
@param[in] id string of token to get or NULL
@return X509 certificate (dynamically allocated) or NULL with wsse:SecurityTokenUnavailable fault
*/
X509*
soap_wsse_get_BinarySecurityTokenX509(struct soap *soap, const char *id)
{ X509 *cert = NULL;
  char *valueType;
  unsigned char *data;
  int size;
  DBGFUN1("soap_wsse_get_BinarySecurityTokenX509", "id=%s", id?id:"");
  if (!soap_wsse_get_BinarySecurityToken(soap, id, &valueType, &data, &size)
   && valueType
   && !strcmp(valueType, wsse_X509v3URI))
    cert = d2i_X509(NULL, (unsigned char**)&data, size);
  /* verify the certificate */
  if (!cert || soap_wsse_verify_X509(soap, cert))
    return NULL;
  return cert;
}

/**
@fn int soap_wsse_verify_X509(struct soap *soap, X509 *cert)
@brief Verifies X509 certificate against soap->cafile, soap->capath, and soap->crlfile
@param soap context
@param[in] cert X509 certificate
@return SOAP_OK or fault

This is an expensive operation. Whenever a new soap context is created, the
cafile and objects are loaded into that context each time we need to verify a
certificate.
*/
int
soap_wsse_verify_X509(struct soap *soap, X509 *cert)
{ struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  X509_STORE_CTX *verify;
  DBGFUN("soap_wsse_verify_X509");
  if (!data)
    return soap_set_receiver_error(soap, "soap_wsse_sign", "Plugin not registered", SOAP_PLUGIN_ERROR);
  if (!data->store)
  { if (!(data->store = X509_STORE_new()))
      return soap_receiver_fault(soap, "soap_wsse_verify_X509", "Could not create X509_STORE object");
    DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Setting up a new X509 store\n"));
    X509_STORE_set_verify_cb_func(data->store, soap->fsslverify);
    if (soap->cafile || soap->capath)
    { if (X509_STORE_load_locations(data->store, soap->cafile, soap->capath) != 1)
        return soap_receiver_fault(soap, "soap_wsse_verify_X509", "Could not load CA file or path");
    }
#if (OPENSSL_VERSION_NUMBER > 0x00907000L)
    if (soap->crlfile)
    { X509_LOOKUP *lookup;
      if (!(lookup = X509_STORE_add_lookup(data->store, X509_LOOKUP_file())))
        return soap_receiver_fault(soap, "soap_wsse_verify_X509", "Could not create X509_LOOKUP object");
      if (X509_load_crl_file(lookup, soap->crlfile, X509_FILETYPE_PEM) != 1)
        return soap_receiver_fault(soap, "soap_wsse_verify_X509", "Could not read the CRL file");
      X509_STORE_set_flags(data->store, X509_V_FLAG_CRL_CHECK | X509_V_FLAG_CRL_CHECK_ALL);
    }
#endif
  }
  if (!(verify = X509_STORE_CTX_new()))
    return soap_receiver_fault(soap, "soap_wsse_verify_X509", "Could not create X509_STORE_CTX object");
#if (OPENSSL_VERSION_NUMBER > 0x00907000L)
  if (X509_STORE_CTX_init(verify, data->store, cert, NULL) != 1)
  { X509_STORE_CTX_free(verify);
    return soap_receiver_fault(soap, "soap_wsse_verify_X509", "Could not initialize X509_STORE_CTX object");
  }
#else
  X509_STORE_CTX_init(verify, data->store, cert, NULL);
#endif
  if (X509_verify_cert(verify) != 1)
  { X509_STORE_CTX_free(verify);
    return soap_sender_fault(soap, "soap_wsse_verify_X509", "Invalid certificate");
  }
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Certificate is valid\n"));
  return SOAP_OK;
}

/******************************************************************************\
 *
 * ds:Signature/SignedInfo
 *
\******************************************************************************/

/**
@fn ds__SignedInfoType* soap_wsse_add_SignedInfo(struct soap *soap)
@brief Adds SignedInfo element.
@param soap context
@return ds__SignedInfoType object
*/
struct ds__SignedInfoType*
soap_wsse_add_SignedInfo(struct soap *soap)
{ ds__SignatureType *signature = soap_wsse_add_Signature(soap);
  if (!signature->SignedInfo)
  { signature->SignedInfo = (ds__SignedInfoType*)soap_malloc(soap, sizeof(ds__SignedInfoType));
    soap_default_ds__SignedInfoType(soap, signature->SignedInfo);
  }
  return signature->SignedInfo;
}

/**
@fn int soap_wsse_add_SignedInfo_Reference(struct soap *soap, const char *URI, const char *transform, const char *inclusiveNamespaces, const char *HA)
@brief Adds SignedInfo element with Reference URI, transform algorithm used, and digest value.
@param soap context
@param[in] URI reference
@param[in] transform string should be c14n_URI for exc-c14n or NULL
@param[in] inclusiveNamespaces used by the exc-c14n transform or NULL
@param[in] HA is the SHA1 digest in binary form (length=SOAP_SMD_SHA1_SIZE)
@return SOAP_OK or SOAP_EOM when references exceed SOAP_WSSE_MAX_REF

This function can be called to add more references to the wsse:SignedInfo
element. A maximum number of SOAP_WSSE_MAX_REF references can be added. The
digest method is always SHA1. 
Note: XPath transforms cannot be specified in this release.
*/
int
soap_wsse_add_SignedInfo_Reference(struct soap *soap, const char *URI, const char *transform, const char *inclusiveNamespaces, const char *HA)
{ ds__SignedInfoType *signedInfo = soap_wsse_add_SignedInfo(soap);
  ds__ReferenceType *reference;
  DBGFUN2("soap_wsse_add_SignedInfo_Reference", "URI=%s", URI?URI:"", "transform=%s", transform?transform:"");
  /* if this is the first reference, allocate SOAP_WSSE_MAX_REF references */
  if (signedInfo->__sizeReference == 0)
    signedInfo->Reference = (ds__ReferenceType**)soap_malloc(soap, SOAP_WSSE_MAX_REF*sizeof(ds__ReferenceType*));
  else
  { /* maximum number of references exceeded? */
    if (signedInfo->__sizeReference >= SOAP_WSSE_MAX_REF)
      return SOAP_EOM;
  }
  /* allocate fresh new reference */
  reference = (ds__ReferenceType*)soap_malloc(soap, sizeof(ds__ReferenceType));
  soap_default_ds__ReferenceType(soap, reference);
  /* populate the URI */
  reference->URI = soap_strdup(soap, URI);
  /* if a transform algorithm was used, populate the Transforms element */
  if (transform)
  { reference->Transforms = (ds__TransformsType*)soap_malloc(soap, sizeof(ds__TransformsType));
    soap_default_ds__TransformsType(soap, reference->Transforms);
    /* only one transform */
    reference->Transforms->__sizeTransform = 1;
    reference->Transforms->Transform = (ds__TransformType*)soap_malloc(soap, sizeof(ds__TransformType));
    soap_default_ds__TransformType(soap, reference->Transforms->Transform);
    reference->Transforms->Transform->Algorithm = (char*)transform;
    /* populate the c14n:InclusiveNamespaces element */
    if (inclusiveNamespaces && *inclusiveNamespaces)
    { reference->Transforms->Transform->c14n__InclusiveNamespaces = (_c14n__InclusiveNamespaces*)soap_malloc(soap, sizeof(_c14n__InclusiveNamespaces));
      soap_default__c14n__InclusiveNamespaces(soap, reference->Transforms->Transform->c14n__InclusiveNamespaces);
      reference->Transforms->Transform->c14n__InclusiveNamespaces->PrefixList = soap_strdup(soap, inclusiveNamespaces);
    }
  }
  /* populate the DigestMethod element */
  reference->DigestMethod = (ds__DigestMethodType*)soap_malloc(soap, sizeof(ds__DigestMethodType));
  soap_default_ds__DigestMethodType(soap, reference->DigestMethod);
  /* the DigestMethod algorithm is always SHA1 */
  reference->DigestMethod->Algorithm = (char*)ds_sha1URI;
  /* populate the DigestValue element */
  reference->DigestValue = soap_s2base64(soap, (unsigned char*)HA, NULL, SOAP_SMD_SHA1_SIZE);
  /* add the fresh new reference to the array */
  signedInfo->Reference[signedInfo->__sizeReference] = reference;
  signedInfo->__sizeReference++;
  return SOAP_OK;
}

/**
@fn int soap_wsse_add_SignedInfo_SignatureMethod(struct soap *soap, const char *method, int canonical)
@brief Adds SignedInfo element with SignatureMethod.
@param soap context
@param[in] method is the URI of the signature algorithm (e.g. ds_rsa_sha1)
@param[in] canonical flag indicating that SignedInfo is signed in exc-c14n form
@return SOAP_OK

Note: the c14n:InclusiveNamespaces/PrefixList is set to "SOAP-ENV wsse".
*/
int
soap_wsse_add_SignedInfo_SignatureMethod(struct soap *soap, const char *method, int canonical)
{ ds__SignedInfoType *signedInfo = soap_wsse_add_SignedInfo(soap);
  DBGFUN2("soap_wsse_add_SignedInfo_SignatureMethod", "method=%s", method?method:"", "canonical=%d", canonical);
  /* if signed in exc-c14n form, populate CanonicalizationMethod element */
  if (canonical)
  { signedInfo->CanonicalizationMethod = (ds__CanonicalizationMethodType*)soap_malloc(soap, sizeof(ds__CanonicalizationMethodType));
    soap_default_ds__CanonicalizationMethodType(soap, signedInfo->CanonicalizationMethod);
    signedInfo->CanonicalizationMethod->Algorithm = (char*)c14n_URI;
    /* TODO: check c14n:InclusiveNamespaces/PrefixList requirements. It seems
     * that the WS-Security spec is at odds with the EXC C14N spec on this
     * issue?
     *
    signedInfo->CanonicalizationMethod->c14n__InclusiveNamespaces = (_c14n__InclusiveNamespaces*)soap_malloc(soap, sizeof(_c14n__InclusiveNamespaces));
    soap_default__c14n__InclusiveNamespaces(soap, signedInfo->CanonicalizationMethod->c14n__InclusiveNamespaces);
    signedInfo->CanonicalizationMethod->c14n__InclusiveNamespaces->PrefixList = "SOAP-ENV wsse";
    */
  }
  /* populate SignatureMethod element */
  signedInfo->SignatureMethod = (ds__SignatureMethodType*)soap_malloc(soap, sizeof(ds__SignatureMethodType));
  soap_default_ds__SignatureMethodType(soap, signedInfo->SignatureMethod);
  signedInfo->SignatureMethod->Algorithm = (char*)method;
  return SOAP_OK;
}

/**
@fn ds__SignedInfoType* soap_wsse_SignedInfo(struct soap *soap)
@brief Returns SignedInfo element if present.
@param soap context
@return ds__SignedInfoType object or NULL
*/
struct ds__SignedInfoType*
soap_wsse_SignedInfo(struct soap *soap)
{ ds__SignatureType *signature = soap_wsse_Signature(soap);
  if (signature)
    return signature->SignedInfo;
  return NULL;
}

/**
@fn int soap_wsse_get_SignedInfo_SignatureMethod(struct soap *soap, int *alg)
@brief Get SignatureMethod algorithm
@param soap context
@param[out] alg is SOAP_SMD_HMAC_SHA1, SOAP_SMD_VRFY_DSA_SHA1, or SOAP_SMD_VRFY_RSA_SHA1
@return SOAP_OK or SOAP_FAULT with wsse:UnsupportedAlgorithm or wsse:FailedCheck fault
*/
int
soap_wsse_get_SignedInfo_SignatureMethod(struct soap *soap, int *alg)
{ ds__SignedInfoType *signedInfo = soap_wsse_SignedInfo(soap);
  DBGFUN("soap_wsse_get_SignedInfo_SignatureMethod");
  *alg = SOAP_SMD_NONE;
  /* if we have a SignedInfo element, get the algorithm */
  if (signedInfo
   && signedInfo->SignatureMethod
   && signedInfo->SignatureMethod->Algorithm)
  { const char *method = signedInfo->SignatureMethod->Algorithm;
    if (!strcmp(method, ds_hmac_sha1URI))
      *alg = SOAP_SMD_HMAC_SHA1;
    else if (!strcmp(method, ds_dsa_sha1URI))
      *alg = SOAP_SMD_VRFY_DSA_SHA1;
    else if (!strcmp(method, ds_rsa_sha1URI))
      *alg = SOAP_SMD_VRFY_RSA_SHA1;
    else
      return soap_wsse_fault(soap, wsse2__UnsupportedAlgorithm, method);
    return SOAP_OK;
  }
  return soap_wsse_fault(soap, wsse2__FailedCheck, "Signature required");
}

/******************************************************************************\
 *
 * ds:Signature/SignatureValue
 *
\******************************************************************************/

/**
@fn int soap_wsse_add_SignatureValue(struct soap *soap, int alg, const void *key, int keylen)
@brief Adds SignedInfo/SignatureMethod element, signs the SignedInfo element, and adds the resulting SignatureValue element.
@param soap context
@param[in] alg is SOAP_SMD_HMAC_SHA1, SOAP_SMD_SIGN_DSA_SHA1, or SOAP_SMD_SIGN_RSA_SHA1
@param[in] key to use to sign (HMAC or EVP_PKEY)
@param[in] keylen length of HMAC key
@return SOAP_OK, SOAP_EOM, or fault

To sign the SignedInfo element with this function, populate SignedInfo with
Reference elements first using soap_wsse_add_SignedInfo_Reference. The
SignedInfo element must not be modified after signing.

The SOAP_XML_INDENT and SOAP_XML_CANONICAL flags are used to serialize the
SignedInfo to compute the signature.
*/
int
soap_wsse_add_SignatureValue(struct soap *soap, int alg, const void *key, int keylen)
{ ds__SignatureType *signature = soap_wsse_add_Signature(soap);
  const char *c14nexclude, *method = NULL;
  char *sig;
  int siglen;
  DBGFUN1("soap_wsse_add_SignatureValue", "alg=%d", alg);
  /* determine signature algorithm to use */
  switch (alg)
  { case SOAP_SMD_HMAC_SHA1:
      method = ds_hmac_sha1URI;
      break;
    case SOAP_SMD_SIGN_DSA_SHA1:
      method = ds_dsa_sha1URI;
      break;
    case SOAP_SMD_SIGN_RSA_SHA1:
      method = ds_rsa_sha1URI;
      break;
    default:
      return soap_wsse_fault(soap, wsse2__UnsupportedAlgorithm, NULL);
  }
  /* populate SignedInfo/SignatureMethod based on SOAP_XML_CANONICAL flag */
  soap_wsse_add_SignedInfo_SignatureMethod(soap, method, (soap->mode & SOAP_XML_CANONICAL));
  /* use the gSOAP engine's look-aside buffer to temporarily hold the sig */
  if (soap_store_lab(soap, NULL, soap_smd_size(alg, key)))
    return SOAP_EOM;
  sig = soap->labbuf;
  /* we will serialize SignedInfo as it appears exactly in the SOAP Header */
  /* set indent level for XML SignedInfo as it appears in the SOAP Header */
  soap->level = 4;
  /* with SOAP_XML_CANONICAL flag, exclude the "ds" prefix */
  c14nexclude = soap->c14nexclude;
  soap->c14nexclude = "ds";
  /* use smdevp engine to sign SignedInfo */
  if (soap_smd_begin(soap, alg, key, keylen)
   || soap_out_ds__SignedInfoType(soap, "ds:SignedInfo", 0, signature->SignedInfo, NULL)
   || soap_smd_end(soap, sig, &siglen))
    return soap_wsse_fault(soap, wsse2__InvalidSecurity, "Could not sign");
  /* restore c14nexclude */
  soap->c14nexclude = c14nexclude;
  /* populate the SignatureValue element */
  signature->SignatureValue = soap_s2base64(soap, (unsigned char*)sig, NULL, siglen);
  return SOAP_OK;
}

/**
@fn int soap_wsse_verify_SignatureValue(struct soap *soap, int alg, const void *key, int keylen)
@brief Verifies the SignatureValue of a SignedInfo element.
@param soap context
@param[in] alg is SOAP_SMD_HMAC_SHA1, SOAP_SMD_VRFY_DSA_SHA1, or SOAP_SMD_VRFY_RSA_SHA1 determined by the SignedInfo/SignatureMethod
@param[in] key to use to verify (HMAC or EVP_PKEY)
@param[in] keylen length of HMAC key
@return SOAP_OK, SOAP_EOM, or fault

This function searches for the SignedInfo element in the soap->dom DOM tree to
verify the signature in the SignatureValue element. Using the DOM ensures we
will verify the signature of a SignedInfo as it was exactly received by the
parser, by using the -DWITH_DOM compile flag and SOAP_XML_DOM runtime flag. If
there is no DOM, it verifies the signature of the deserialized SignedInfo
element in the SOAP Header. However, serializing deserialized data may change
the octet stream that was signed, unless we're using gSOAP as producers and
consumers (with the SOAP_XML_INDENT flag reset).
*/
int
soap_wsse_verify_SignatureValue(struct soap *soap, int alg, const void *key, int keylen)
{ ds__SignatureType *signature = soap_wsse_Signature(soap);
  DBGFUN1("soap_wsse_verify_SignatureValue", "alg=%d", alg);
  /* always need an HMAC secret key or DSA/RSA public key to verify */
  if (!key)
    return soap_wsse_fault(soap, wsse2__SecurityTokenUnavailable, NULL);
  /* verify the SignedInfo element with the SignatureValue element */
  if (signature
   && signature->SignedInfo
   && signature->SignatureValue)
  { char *sig;
    const char *sigval;
    int method, siglen, sigvallen;
    /* check that we are using the intended signature algorithm */
    if (soap_wsse_get_SignedInfo_SignatureMethod(soap, &method))
      return soap->error;
    if (alg != method)
      return soap_wsse_fault(soap, wsse2__FailedCheck, "Incorrect signature algorithm");
    /* retrieve the signature */
    sigval = soap_base642s(soap, signature->SignatureValue, NULL, 0, &sigvallen);
    /* search the DOM for SignedInfo */
    if (soap->dom)
    { struct soap_dom_element *elt;
      /* traverse the DOM while searching for SignedInfo in the ds namespace */
      for (elt = soap->dom; elt; elt = soap_dom_next_element(elt))
      { if (elt->name
         && elt->nstr
         && !strcmp(elt->nstr, ds_URI)
         && (!strcmp(elt->name, "SignedInfo") || !soap_tag_cmp(elt->name, "*:SignedInfo")))
          break;
      }
      /* found it? */
      if (elt)
      { /* output the DOM "as is" */
        soap->mode &= ~SOAP_XML_CANONICAL;
        soap->mode |= SOAP_DOM_ASIS;
        /* should not include leading whitespace in signature verification */
        elt->head = NULL;
        /* use smdevp engine to verify SignedInfo */
        if (alg == SOAP_SMD_HMAC_SHA1)
          sig = (char*)soap_malloc(soap, soap_smd_size(alg, key));
	else
        { sig = (char*)sigval;
          siglen = sigvallen;
        }
        if (soap_smd_begin(soap, alg, key, keylen)
         || soap_out_xsd__anyType(soap, NULL, 0, elt, NULL)
         || soap_smd_end(soap, sig, &siglen))
          return soap_wsse_fault(soap, wsse2__FailedCheck, NULL);
        if (alg == SOAP_SMD_HMAC_SHA1)
        { if (siglen != sigvallen || memcmp(sig, sigval, siglen))
            return soap_wsse_fault(soap, wsse2__FailedCheck, NULL);
        }
        DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Signature in DOM is valid\n"));
        return SOAP_OK;
      }
    }
    else
    { int err = SOAP_OK;
      const char *c14nexclude;
      soap_mode mode;
      /* serialize the SignedInfo element as it appeared in the SOAP Header */
      soap->level = 4;
      c14nexclude = soap->c14nexclude;
      soap->c14nexclude = "ds";
      mode = soap->mode;
      if (signature->SignedInfo->CanonicalizationMethod)
        soap->mode |= SOAP_XML_CANONICAL;
      else
        soap->mode &= ~SOAP_XML_CANONICAL;
      if (alg == SOAP_SMD_HMAC_SHA1)
        sig = (char*)soap_malloc(soap, soap_smd_size(alg, key));
      else
      { sig = (char*)sigval;
        siglen = sigvallen;
      }
      if (soap_smd_begin(soap, alg, key, keylen)
       || soap_out_ds__SignedInfoType(soap, "ds:SignedInfo", 0, signature->SignedInfo, NULL)
       || soap_smd_end(soap, sig, &siglen))
        err = soap->error;
      soap->mode = mode;
      soap->c14nexclude = c14nexclude;
      if (err)
        return soap_wsse_fault(soap, wsse2__FailedCheck, NULL);
      if (alg == SOAP_SMD_HMAC_SHA1)
      { if (siglen != sigvallen || memcmp(sig, sigval, siglen))
          return soap_wsse_fault(soap, wsse2__FailedCheck, NULL);
      }
      DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Signature is valid\n"));
      return SOAP_OK;
    }
  }
  return soap_wsse_fault(soap, wsse2__FailedCheck, "Signature required");
}

/**
@fn int soap_wsse_verify_SignedInfo(struct soap *soap)
@brief Verifies the digest values of the XML elements referenced by the SignedInfo References.
@param soap context
@return SOAP_OK or fault

This function searches for the SignedInfo element in the soap->dom DOM tree to
verify the digests contained therein. Using the DOM ensures we will verify the
digests of the locally signed elements as they were exactly received by the
parser, by using the -DWITH_DOM compile flag and SOAP_XML_DOM runtime flag. If
there is no DOM, the function fails.
*/
int
soap_wsse_verify_SignedInfo(struct soap *soap)
{ ds__SignedInfoType *signedInfo = soap_wsse_SignedInfo(soap);
  DBGFUN("soap_wsse_verify_SignedInfo");
  if (signedInfo)
  { int i;
    /* must have at least one reference element */
    if (signedInfo->__sizeReference == 0)
      return soap_wsse_fault(soap, wsse2__InvalidSecurity, "No SignedInfo/Reference");
    /* TODO: this would be a good place to re-canonicalize the entire DOM to improve interop. Two DOMs can be used: one with non-c14n XML and one with c14n XML so we can handle multiple different transforms. */
    /* for each reference element, check the digest */
    for (i = 0; i < signedInfo->__sizeReference; i++)
    { ds__ReferenceType *reference = signedInfo->Reference[i];
      /* reference element is complete? */
      if (!reference->URI
       || !reference->DigestMethod
       || !reference->DigestMethod->Algorithm
       || !reference->DigestValue)
        return soap_wsse_fault(soap, wsse2__InvalidSecurity, "Incomplete SignedInfo/Reference");
      /* reference is local? */
      if (*reference->URI == '#')
      { int alg;
        unsigned char hash[SOAP_SMD_MAX_SIZE];
        DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Verifying digest of locally referenced data %s\n", reference->URI));
        /* digest algorithm should be SHA1 */
        if (!strcmp(reference->DigestMethod->Algorithm, ds_sha1URI))
          alg = SOAP_SMD_DGST_SHA1;
        else
          return soap_wsse_fault(soap, wsse2__UnsupportedAlgorithm, reference->DigestMethod->Algorithm);
        /* if reference has a transform, it should be an exc-c14n transform */
        if (reference->Transforms
         && (reference->Transforms->__sizeTransform != 1
          || !reference->Transforms->Transform[0].Algorithm
          || strcmp(reference->Transforms->Transform[0].Algorithm, c14n_URI)))
          return soap_wsse_fault(soap, wsse2__UnsupportedAlgorithm, reference->Transforms->Transform[0].Algorithm);
        /* convert base64 digest to binary */
        soap_base642s(soap, reference->DigestValue, (char*)hash, SOAP_SMD_MAX_SIZE, NULL);
        /* verify the digest of a locally signed element */
        if (soap_wsse_verify_digest(soap, alg, reference->URI + 1, hash))
          return soap->error;
      }
    }
    return SOAP_OK;
  }
  return soap_wsse_fault(soap, wsse2__InvalidSecurity, "No SignedInfo");
}

/**
@fn int soap_wsse_verify_digest(struct soap *soap, int alg, const char *id, unsigned char hash[SOAP_SMD_MAX_SIZE])
@brief Verifies the digest value of an XML element referenced by id against the hash.
@param soap context
@param[in] alg digest algorithm
@param[in] id string of the XML element to verify
@param[in] hash digest value to verify against
@return SOAP_OK or fault
*/
int
soap_wsse_verify_digest(struct soap *soap, int alg, const char *id, unsigned char hash[SOAP_SMD_MAX_SIZE])
{ struct soap_dom_element *elt;
  DBGFUN1("soap_wsse_verify_digest", "alg=%d", alg);
  /* traverse the DOM to find the element with matching wsu:Id or ds:Id */
  for (elt = soap->dom; elt; elt = soap_dom_next_element(elt))
  { struct soap_dom_attribute *att;
    for (att = elt->atts; att; att = att->next)
    { /* check attribute */
      if (att->name
       && att->nstr
       && (!strcmp(att->nstr, wsu_URI) || !strcmp(att->nstr, ds_URI))
       && (!strcmp(att->name, "Id") || !soap_tag_cmp(att->name, "*:Id")))
      { /* found a match, compare attribute value with id */
        if (att->data && !strcmp(att->data, id))
        { unsigned char HA[SOAP_SMD_SHA1_SIZE];
          int len;
          DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Computing digest for Id=%s\n", id));
          /* compute digest over DOM node "as is" */
          soap->mode &= ~SOAP_XML_CANONICAL;
          soap->mode |= SOAP_DOM_ASIS;
          /* do not hash leading whitespace */
          elt->head = NULL;
          /* compute digest */
          if (soap_smd_begin(soap, alg, NULL, 0)
           || soap_out_xsd__anyType(soap, NULL, 0, elt, NULL)
           || soap_smd_end(soap, (char*)HA, &len))
            return soap_wsse_fault(soap, wsse2__FailedCheck, "Could not compute digest");
          /* compare digests, success if identical */
          DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Comparing digest hashes\n"));
          DBGHEX(TEST, hash, len);
          DBGLOG(TEST, SOAP_MESSAGE(fdebug, "\n--\n"));
          DBGHEX(TEST, HA, len);
          DBGLOG(TEST, SOAP_MESSAGE(fdebug, "\n"));
          if (!memcmp(hash, HA, (size_t)len))
            return SOAP_OK;
          return soap_wsse_fault(soap, wsse2__FailedCheck, "SignedInfo digest mismatch");
        }
      }
    }
  }
  return soap_wsse_fault(soap, wsse2__FailedCheck, "SignedInfo reference target not found");
}

/******************************************************************************\
 *
 * ds:Signature/KeyInfo
 *
\******************************************************************************/

/**
@fn ds__KeyInfoType* soap_wsse_add_KeyInfo(struct soap *soap)
@brief Adds KeyInfo element.
@param soap context
@return ds__KeyInfo object
*/
struct ds__KeyInfoType*
soap_wsse_add_KeyInfo(struct soap *soap)
{ ds__SignatureType *signature = soap_wsse_add_Signature(soap);
  if (!signature->KeyInfo)
    signature->KeyInfo = (ds__KeyInfoType*)soap_malloc(soap, sizeof(ds__KeyInfoType));
  soap_default_ds__KeyInfoType(soap, signature->KeyInfo);
  return signature->KeyInfo;
}

/**
@fn ds__KeyInfoType* soap_wsse_KeyInfo(struct soap *soap)
@brief Returns KeyInfo element if present.
@param soap context
@return ds__KeyInfo object or NULL
*/
struct ds__KeyInfoType*
soap_wsse_KeyInfo(struct soap *soap)
{ ds__SignatureType *signature = soap_wsse_Signature(soap);
  if (signature)
    return signature->KeyInfo;
  return NULL;
}

/******************************************************************************\
 *
 * ds:Signature/KeyInfo/KeyName
 *
\******************************************************************************/

/**
@fn int soap_wsse_add_KeyInfo_KeyName(struct soap *soap, const char *name)
@brief Adds KeyName element.
@param soap context
@param[in] name string of the KeyName
@return SOAP_OK

Note: the recommended method to add Key information is to utilize KeyIdentifier
instead of KeyName. A KeyName is useful mainly for internal use.
*/
int
soap_wsse_add_KeyInfo_KeyName(struct soap *soap, const char *name)
{ ds__KeyInfoType *keyInfo = soap_wsse_add_KeyInfo(soap);
  DBGFUN1("soap_wsse_add_KeyInfo_KeyName", "name=%s", name);
  /* populate the KeyName element */
  keyInfo->KeyName = soap_strdup(soap, name);
  return SOAP_OK;
}

/**
@fn int soap_wsse_get_KeyInfo_KeyName(struct soap *soap)
@brief Returns KeyName element if present.
@param soap context
@return string or NULL
*/
const char*
soap_wsse_get_KeyInfo_KeyName(struct soap *soap)
{ ds__KeyInfoType *keyInfo = soap_wsse_KeyInfo(soap);
  DBGFUN("soap_wsse_get_KeyInfo_KeyName");
  if (!keyInfo)
    return NULL;
  return keyInfo->KeyName;
}

/******************************************************************************\
 *
 * ds:Signature/KeyInfo/wsse:SecurityTokenReference/Reference/@URI
 *
\******************************************************************************/

/**
@fn int soap_wsse_add_KeyInfo_SecurityTokenReferenceURI(struct soap *soap, const char *URI, const char *valueType)
@brief Adds KeyInfo element with SecurityTokenReference URI.
@param soap context
@param[in] URI string referencing a security token
@param[in] valueType string or NULL
@return SOAP_OK
*/
int
soap_wsse_add_KeyInfo_SecurityTokenReferenceURI(struct soap *soap, const char *URI, const char *valueType)
{ ds__KeyInfoType *keyInfo = soap_wsse_add_KeyInfo(soap);
  DBGFUN2("soap_wsse_add_KeyInfo_SecurityTokenReferenceURI", "URI=%s", URI?URI:"", "valueType=%s", valueType?valueType:"");
  /* allocate SecurityTokenReference element if we don't have one already */
  if (!keyInfo->wsse2__SecurityTokenReference)
    keyInfo->wsse2__SecurityTokenReference = (_wsse2__SecurityTokenReference*)soap_malloc(soap, sizeof(_wsse2__SecurityTokenReference));
  soap_default__wsse2__SecurityTokenReference(soap, keyInfo->wsse2__SecurityTokenReference);
  /* allocate Reference element */
  keyInfo->wsse2__SecurityTokenReference->Reference = (_wsse2__Reference*)soap_malloc(soap, sizeof(_wsse2__Reference));
  soap_default__wsse2__Reference(soap, keyInfo->wsse2__SecurityTokenReference->Reference);
  /* populate the Reference element */
  keyInfo->wsse2__SecurityTokenReference->Reference->URI = soap_strdup(soap, URI);
  keyInfo->wsse2__SecurityTokenReference->Reference->ValueType = soap_strdup(soap, valueType);
  return SOAP_OK;
}

/**
@fn int soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(struct soap *soap, const char *URI)
@brief Adds KeyInfo element with SecurityTokenReference URI to an X509 cert.
@param soap context
@param[in] URI string referencing an X509 certificate
@return SOAP_OK
*/
int
soap_wsse_add_KeyInfo_SecurityTokenReferenceX509(struct soap *soap, const char *URI)
{ return soap_wsse_add_KeyInfo_SecurityTokenReferenceURI(soap, URI, wsse_X509v3URI);
}

/**
@fn const char* soap_wsse_get_KeyInfo_SecurityTokenReferenceURI(struct soap *soap)
@brief Returns a SecurityTokenReference URI if present.
@param soap context
@return string or NULL
*/
const char*
soap_wsse_get_KeyInfo_SecurityTokenReferenceURI(struct soap *soap)
{ ds__KeyInfoType *keyInfo = soap_wsse_KeyInfo(soap);
  if (keyInfo
   && keyInfo->wsse2__SecurityTokenReference
   && keyInfo->wsse2__SecurityTokenReference->Reference)
    return keyInfo->wsse2__SecurityTokenReference->Reference->URI;
  return NULL;
}

/**
@fn const char* soap_wsse_get_KeyInfo_SecurityTokenReferenceValueType(struct soap *soap)
@brief Returns a SecurityTokenReference ValueType if present.
@param soap context
@return string or NULL
*/
const char*
soap_wsse_get_KeyInfo_SecurityTokenReferenceValueType(struct soap *soap)
{ ds__KeyInfoType *keyInfo = soap_wsse_KeyInfo(soap);
  if (keyInfo
   && keyInfo->wsse2__SecurityTokenReference
   && keyInfo->wsse2__SecurityTokenReference->Reference)
    return keyInfo->wsse2__SecurityTokenReference->Reference->ValueType;
  return NULL;
}

/**
@fn X509* soap_wsse_get_KeyInfo_SecurityTokenReferenceX509(struct soap *soap)
@brief Returns a X509 certificate if present as a BinarySecurity token.
@param soap context
@return X509 object or NULL with wsse:SecurityTokenUnavailable fault
*/
X509*
soap_wsse_get_KeyInfo_SecurityTokenReferenceX509(struct soap *soap)
{ const char *URI = soap_wsse_get_KeyInfo_SecurityTokenReferenceURI(soap);
  X509 *cert = NULL;
  DBGFUN("soap_wsse_get_KeyInfo_SecurityTokenReferenceX509");
  if (URI && *URI == '#')
  { const char *valueType;
    valueType = soap_wsse_get_KeyInfo_SecurityTokenReferenceValueType(soap);
    if (!valueType || !strcmp(valueType, wsse_X509v3URI))
      cert = soap_wsse_get_BinarySecurityTokenX509(soap, URI + 1);
  }
  return cert;
}

/******************************************************************************\
 *
 * ds:Signature/KeyInfo/wsse:SecurityTokenReference/Reference/KeyIdentifier
 *
\******************************************************************************/

/**
@fn int soap_wsse_add_KeyInfo_SecurityTokenReferenceKeyIdentifier(struct soap *soap, const char *id, const char *valueType, unsigned char *data, int size)
@brief Adds KeyInfo element with SecurityTokenReference/KeyIdentifier binary data
@param soap context
@param[in] id string for signature reference
@param[in] valueType string
@param[in] data binary data
@param[in] size of binary data
@return SOAP_OK
*/
int
soap_wsse_add_KeyInfo_SecurityTokenReferenceKeyIdentifier(struct soap *soap, const char *id, const char *valueType, unsigned char *data, int size)
{ ds__KeyInfoType *keyInfo = soap_wsse_add_KeyInfo(soap);
  DBGFUN2("soap_wsse_add_KeyInfo_SecurityTokenReferenceKeyIdentifier", "id=%s", id?id:"", "valueType=%s", valueType?valueType:"");
  /* allocate SecurityTokenReference if we don't have one already */
  if (!keyInfo->wsse2__SecurityTokenReference)
    keyInfo->wsse2__SecurityTokenReference = (_wsse2__SecurityTokenReference*)soap_malloc(soap, sizeof(_wsse2__SecurityTokenReference));
  soap_default__wsse2__SecurityTokenReference(soap, keyInfo->wsse2__SecurityTokenReference);
  /* allocate KeyIdentifier */
  keyInfo->wsse2__SecurityTokenReference->KeyIdentifier = (_wsse2__KeyIdentifier*)soap_malloc(soap, sizeof(_wsse2__KeyIdentifier));
  soap_default__wsse2__KeyIdentifier(soap, keyInfo->wsse2__SecurityTokenReference->KeyIdentifier);
  /* populate KeyIdentifier */
  keyInfo->wsse2__SecurityTokenReference->KeyIdentifier->wsu__Id = soap_strdup(soap, id);
  keyInfo->wsse2__SecurityTokenReference->KeyIdentifier->ValueType = soap_strdup(soap, valueType);
  keyInfo->wsse2__SecurityTokenReference->KeyIdentifier->EncodingType = (char*)wsse_Base64BinaryURI;
  keyInfo->wsse2__SecurityTokenReference->KeyIdentifier->__item = soap_s2base64(soap, data, NULL, size);
  return SOAP_OK;
}

/**
@fn const char* soap_wsse_get_KeyInfo_SecurityTokenReferenceKeyIdentifierValueType(struct soap *soap)
@brief Returns KeyInfo/SecurityTokenReference/KeyIdentifier/ValueType if present
@param soap context
@return string or NULL
*/
const char*
soap_wsse_get_KeyInfo_SecurityTokenReferenceKeyIdentifierValueType(struct soap *soap)
{ ds__KeyInfoType *keyInfo = soap_wsse_KeyInfo(soap);
  DBGFUN("soap_wsse_get_KeyInfo_SecurityTokenReferenceKeyIdentifierValueType");
  if (!keyInfo
   || !keyInfo->wsse2__SecurityTokenReference
   || !keyInfo->wsse2__SecurityTokenReference->KeyIdentifier)
    return NULL;
  return keyInfo->wsse2__SecurityTokenReference->KeyIdentifier->ValueType;
}

/**
@fn const unsigned char* soap_wsse_get_KeyInfo_SecurityTokenReferenceKeyIdentifier(struct soap *soap, int *size)
@brief Returns KeyInfo/SecurityTokenReference/KeyIdentifier binary data
@param soap context
@param[out] size is set to the size of the decoded data
@return data or NULL
*/
const unsigned char*
soap_wsse_get_KeyInfo_SecurityTokenReferenceKeyIdentifier(struct soap *soap, int *size)
{ ds__KeyInfoType *keyInfo = soap_wsse_KeyInfo(soap);
  DBGFUN("soap_wsse_get_KeyInfo_SecurityTokenReferenceKeyIdentifier");
  if (!keyInfo
   || !keyInfo->wsse2__SecurityTokenReference
   || !keyInfo->wsse2__SecurityTokenReference->KeyIdentifier)
    return NULL;
  return (unsigned char*)soap_base642s(soap, keyInfo->wsse2__SecurityTokenReference->KeyIdentifier->__item, NULL, 0, size);
}

/******************************************************************************\
 *
 * ds:Signature/KeyInfo/wsse:SecurityTokenReference/Reference/Embedded
 *
\******************************************************************************/

/**
@fn int soap_wsse_add_KeyInfo_SecurityTokenReferenceEmbedded(struct soap *soap, const char *id, const char *valueType)
@brief Adds KeyInfo element with Embedded SecurityTokenReference.
@param soap context
@param[in] id string for signature reference
@param[in] valueType string
@return SOAP_OK

Note: this function does not add embedded tokens automatically. See code for comments.
*/
int
soap_wsse_add_KeyInfo_SecurityTokenReferenceEmbedded(struct soap *soap, const char *id, const char *valueType)
{ ds__KeyInfoType *keyInfo = soap_wsse_add_KeyInfo(soap);
  DBGFUN("soap_wsse_get_KeyInfo_SecurityTokenReferenceEmbedded");
  /* allocate SecurityTokenReference if we don't have one already */
  if (!keyInfo->wsse2__SecurityTokenReference)
    keyInfo->wsse2__SecurityTokenReference = (_wsse2__SecurityTokenReference*)soap_malloc(soap, sizeof(_wsse2__SecurityTokenReference));
  soap_default__wsse2__SecurityTokenReference(soap, keyInfo->wsse2__SecurityTokenReference);
  /* allocate Embedded element */
  keyInfo->wsse2__SecurityTokenReference->Embedded = (_wsse2__Embedded*)soap_malloc(soap, sizeof(_wsse2__Embedded));
  soap_default__wsse2__Embedded(soap, keyInfo->wsse2__SecurityTokenReference->Embedded);
  /* populate Embedded element */
  keyInfo->wsse2__SecurityTokenReference->Embedded->wsu__Id = soap_strdup(soap, id);
  keyInfo->wsse2__SecurityTokenReference->Embedded->ValueType = soap_strdup(soap, valueType);
  /* TODO: Add embedded tokens and assertions. Could use DOM here?
  keyInfo->wsse2__SecurityTokenReference->Embedded->xyz = ...;
  */
  return SOAP_OK;
}

/******************************************************************************\
 *
 * Faults
 *
\******************************************************************************/

/**
@fn int soap_wsse_fault(struct soap *soap, wsse2__FaultcodeEnum fault, const char *detail)
@brief Sets SOAP Fault (sub)code for server response.
@param soap context
@param[in] fault is one of wsse:FaultcodeEnum
@param[in] detail string with optional text message
@return SOAP_FAULT
*/
int
soap_wsse_fault(struct soap *soap, wsse2__FaultcodeEnum fault, const char *detail)
{ const char *code = soap_wsse2__FaultcodeEnum2s(soap, fault);
  DBGFUN2("soap_wsse_fault", "fault=%s", code?code:"", "detail=%s", detail?detail:"");
  /* remove incorrect or incomplete Security header */
  soap_wsse_delete_Security(soap);
  /* populate the SOAP Fault as per WS-Security spec */
  switch (fault)
  { case wsse2__UnsupportedSecurityToken:
      return soap_sender_fault_subcode(soap, code, "An unsupported token was provided", detail);
    case wsse2__UnsupportedAlgorithm:
      return soap_sender_fault_subcode(soap, code, "An unsupported signature or encryption algorithm was used", detail);
    case wsse2__InvalidSecurity:
      return soap_sender_fault_subcode(soap, code, "An error was discovered processing the <wsse:Security> header", detail);
    case wsse2__InvalidSecurityToken:
      return soap_sender_fault_subcode(soap, code, "An invalid security token was provided", detail);
    case wsse2__FailedAuthentication:
      return soap_sender_fault_subcode(soap, code, "The security token could not be authenticated or authorized", detail);
    case wsse2__FailedCheck:
      return soap_sender_fault_subcode(soap, code, "The signature or decryption was invalid", detail);
    case wsse2__SecurityTokenUnavailable:
      return soap_sender_fault_subcode(soap, code, "Referenced security token could not be retrieved", detail);
  }
  return SOAP_FAULT;
}

/******************************************************************************\
 *
 * Digest authentication session management
 *
\******************************************************************************/

/**
@fn static int soap_wsse_session_verify(struct soap *soap, const char hash[SOAP_SMD_SHA1_SIZE], const char *created, const char *nonce)
@brief Verifies and updates the digest, nonce, and creation time against the digest authentication session database to prevent replay attacks.
@param soap context
@param[in] hash binary digest value of PasswordDigest
@param[in] created string
@param[in] nonce string (base64)
@return SOAP_OK or SOAP_FAULT
*/
static int
soap_wsse_session_verify(struct soap *soap, const char hash[SOAP_SMD_SHA1_SIZE], const char *created, const char *nonce)
{ struct soap_wsse_session *session;
  time_t expired, now = time(NULL);
  DBGFUN("soap_wsse_session_verify");
  soap_s2dateTime(soap, created, &expired);
  /* creation time in the future? */
  if (expired > now + SOAP_WSSE_CLKSKEW)
    return soap_wsse_fault(soap, wsse2__FailedAuthentication, "Authorization request in future");
  expired += SOAP_WSSE_NONCETIME;
  /* expired? */
  if (expired <= now)
    return soap_wsse_fault(soap, wsse2__FailedAuthentication, "Authentication expired");
  /* purge expired messages, but don't do this all the time to improve efficiency */
  if (now % 10 == 0)
    soap_wsse_session_cleanup(soap);
  DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Verifying session nonce=%s\n", nonce));
  /* enter mutex to check and update session */
  MUTEX_LOCK(soap_wsse_session_lock);
  for (session = soap_wsse_session; session; session = session->next)
  { if (!memcmp(session->hash, hash, SOAP_SMD_SHA1_SIZE) && !strcmp(session->nonce, nonce))
      break;
  }
  /* if not found, allocate new session data */
  if (!session)
  { session = (struct soap_wsse_session*)malloc(sizeof(struct soap_wsse_session) + strlen(nonce));
    if (session)
    { session->next = soap_wsse_session;
      session->expired = expired;
      memcpy(session->hash, hash, SOAP_SMD_SHA1_SIZE);
      strcpy(session->nonce, nonce);
      soap_wsse_session = session;
    }
    session = NULL;
  }
  /* exit mutex */
  MUTEX_UNLOCK(soap_wsse_session_lock);
  /* if replay attack, return non-descript failure */
  if (session)
    return soap_wsse_fault(soap, wsse2__FailedAuthentication, NULL);
  return SOAP_OK;
}

/**
@fn static void soap_wsse_session_cleanup(struct soap *soap)
@brief Removes expired authentication data from the digest authentication session database.
@param soap context
*/
static void
soap_wsse_session_cleanup(struct soap *soap)
{ struct soap_wsse_session **session;
  time_t now = time(NULL);
  DBGFUN("soap_wsse_session_cleanup");
  /* enter mutex to purge expired session data */
  MUTEX_LOCK(soap_wsse_session_lock);
  session = &soap_wsse_session;
  while (*session)
  { if ((*session)->expired < now)
    { struct soap_wsse_session *p = *session;
      DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Deleting session nonce=%s\n", p->nonce));
      *session = p->next;
      free(p);
    }
    else
      session = &(*session)->next;
  }
  /* exit mutex */
  MUTEX_UNLOCK(soap_wsse_session_lock);
}

/******************************************************************************\
 *
 * Calculate SHA1(created, nonce, password) digest
 *
\******************************************************************************/

/**
@fn static void calc_digest(struct soap *soap, const char *created, const char *nonce, int noncelen, const char *password, char hash[SOAP_SMD_SHA1_SIZE])
@brief Calculates digest value SHA1(created, nonce, password)
@param soap context
@param[in] created string (XSD dateTime format)
@param[in] nonce value
@param[in] noncelen length of nonce value
@param[in] password string
@param[out] hash SHA1 digest
*/
static void
calc_digest(struct soap *soap, const char *created, const char *nonce, int noncelen, const char *password, char hash[SOAP_SMD_SHA1_SIZE])
{ struct soap_smd_data context;
  /* use smdevp engine */
  soap_smd_init(soap, &context, SOAP_SMD_DGST_SHA1, NULL, 0);
  soap_smd_update(soap, &context, nonce, noncelen);
  soap_smd_update(soap, &context, created, strlen(created));
  soap_smd_update(soap, &context, password, strlen(password));
  soap_smd_final(soap, &context, hash, NULL);
}

/******************************************************************************\
 *
 * Calculate randomized hex nonce
 *
\******************************************************************************/

/**
@fn static void calc_nonce(struct soap *soap, char nonce[SOAP_WSSE_NONCELEN])
@brief Calculates "randomized" nonce
@param soap context
@param[out] nonce value
*/
static void
calc_nonce(struct soap *soap, char nonce[SOAP_WSSE_NONCELEN])
{ static short count = 0xCA53;
  char buf[SOAP_WSSE_NONCELEN + 1];
  /* we could have used raw binary instead of hex as below */
  sprintf(buf, "%8.8x%4.4hx%8.8x", (int)time(NULL), count++, soap_random);
  memcpy(nonce, buf, SOAP_WSSE_NONCELEN);
}

/******************************************************************************\
 *
 * Plugin registry functions
 *
\******************************************************************************/

/**
@fn int soap_wsse(struct soap *soap, struct soap_plugin *p, void *arg)
@brief Plugin registry function, used with soap_register_plugin.
@param soap context
@param[in,out] p plugin created in registry
@param[in] arg passed from soap_register_plugin_arg is an optional security token handler callback
@return SOAP_OK
*/
int
soap_wsse(struct soap *soap, struct soap_plugin *p, void *arg)
{ DBGFUN("soap_wsse");
  p->id = soap_wsse_id;
  p->data = (void*)SOAP_MALLOC(soap, sizeof(struct soap_wsse_data));
  p->fcopy = soap_wsse_copy;
  p->fdelete = soap_wsse_delete;
  if (p->data)
  { if (soap_wsse_init(soap, (struct soap_wsse_data*)p->data, (X509*(*)(struct soap*))arg))
    { SOAP_FREE(soap, p->data);
      return SOAP_EOM;
    }
  }
  return SOAP_OK;
}

/**
@fn int soap_wsse_init(struct soap *soap, struct soap_wsse_data *data, void *arg)
@brief Initializes plugin data.
@param soap context
@param[in,out] data plugin data
@param arg security token handler callback
@return SOAP_OK
*/
static int
soap_wsse_init(struct soap *soap, struct soap_wsse_data *data, X509 *(*arg)(struct soap*))
{ static int done = 0;
  DBGFUN("soap_wsse_init");
  if (!done)
  { done = 1;
#ifdef WITH_OPENSSL
    OpenSSL_add_all_digests();
    OpenSSL_add_all_algorithms();
#endif
    MUTEX_SETUP(soap_wsse_session_lock);
  }
  data->sign_alg = SOAP_SMD_NONE;
  data->sign_key = NULL;
  data->sign_keylen = 0;
  data->vrfy_alg = SOAP_SMD_NONE;
  data->vrfy_key = NULL;
  data->vrfy_keylen = 0;
  data->digest = NULL;
  data->fprepareinit = NULL;
  data->fpreparesend = NULL;
  data->fpreparefinal = NULL;
  data->fdisconnect = NULL;
  data->store = NULL;
  data->security_token_handler = arg;
  return SOAP_OK;
}

/**
@fn int soap_wsse_copy(struct soap *soap, struct soap_plugin *dst, struct soap_plugin *src)
@brief Copies plugin data to localize plugin data for threads.
@param soap context
@param[out] dst target plugin
@param[in] src source plugin
@return SOAP_OK
*/
static int
soap_wsse_copy(struct soap *soap, struct soap_plugin *dst, struct soap_plugin *src)
{ DBGFUN("soap_wsse_copy");
  *dst = *src;
  dst->data = (void*)SOAP_MALLOC(soap, sizeof(struct soap_wsse_data));
  soap_wsse_init(soap, (struct soap_wsse_data*)dst->data, ((struct soap_wsse_data*)src->data)->security_token_handler);
  return SOAP_OK;
}

/**
@fn void soap_wsse_delete(struct soap *soap, struct soap_plugin *p)
@brief Deletes plugin data.
@param soap context
@param[in,out] p plugin
@return SOAP_OK
*/
static void
soap_wsse_delete(struct soap *soap, struct soap_plugin *p)
{ struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  DBGFUN("soap_wsse_delete");
  if (data)
  { soap_wsse_preparecleanup(soap, data);
    if (data->store)
    { X509_STORE_free(data->store);
      data->store = NULL;
    }
    SOAP_FREE(soap, data);
  }
}

/******************************************************************************\
 *
 * Plugin-specific functions
 *
\******************************************************************************/

/**
@fn int soap_wsse_sign(struct soap *soap, int alg, const void *key, int keylen)
@brief Uses the wsse plugin to sign all wsu:Id attributed elements.
@param soap context
@param[in] alg is the signature algorithm SOAP_SMD_HMAC_SHA1, SOAP_SMD_SIGN_DSA_SHA1, or SOAP_SMD_SIGN_RSA_SHA1
@param[in] key is the HMAC secret key or DSA/RSA private EVP_PKEY
@param[in] keylen is the HMAC key length
@return SOAP_OK or fault

This function does not actually sign the message, but initiates the plugin's
signature algorithm to sign the message upon message transfer.
*/
int
soap_wsse_sign(struct soap *soap, int alg, const void *key, int keylen)
{ struct soap_wsse_digest *digest, *next;
  struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  DBGFUN1("soap_wsse_sign", "alg=%d", alg);
  if (!data)
    return soap_set_receiver_error(soap, "soap_wsse_sign", "Plugin not registered", SOAP_PLUGIN_ERROR);
  if (!alg || !key)
    return soap_wsse_fault(soap, wsse2__InvalidSecurity, "Invalid signature algorithm or key");
  /* store alg and key in plugin data */
  data->sign_alg = alg;
  data->sign_key = key;
  data->sign_keylen = keylen;
  /* save and set the plugin's callbacks to preprocess outbound messages */
  if (soap->fprepareinit != soap_wsse_prepareinit)
  { data->fprepareinit = soap->fprepareinit;
    soap->fprepareinit = soap_wsse_prepareinit;
  }
  if (soap->fpreparesend != soap_wsse_preparesend)
  { data->fpreparesend = soap->fpreparesend;
    data->fpreparefinal = soap->fpreparefinal;
  }
  if (soap->fpreparefinal != soap_wsse_preparefinal)
  { soap->fpreparesend = soap_wsse_preparesend;
    soap->fpreparefinal = soap_wsse_preparefinal;
  }
  /* cleanup the digest data */
  for (digest = data->digest; digest; digest = next)
  { next = digest->next;
    SOAP_FREE(soap, digest);
  }
  data->digest = NULL;
  return SOAP_OK;
}

/**
@fn int soap_wsse_sign_body(struct soap *soap, int alg, const void *key, int keylen)
@brief Uses the wsse plugin to sign all wsu:Id attributed elements, including the SOAP Body (by adding a wsu:Id="Body" attribute).
@param soap context
@param[in] alg is the signature algorithm SOAP_SMD_HMAC_SHA1, SOAP_SMD_SIGN_DSA_SHA1, or SOAP_SMD_SIGN_RSA_SHA1
@param[in] key is the HMAC secret key or DSA/RSA private EVP_PKEY
@param[in] keylen is the HMAC key length
@return SOAP_OK

This function does not actually sign the message, but initiates the plugin's
signature algorithm to sign the message upon message transfer.
*/
int
soap_wsse_sign_body(struct soap *soap, int alg, const void *key, int keylen)
{ int err;
  DBGFUN1("soap_wsse_sign_body", "alg=%d", alg);
  soap_wsse_add_Security(soap);
  soap->omode |= SOAP_XML_SEC;
  err = soap_wsse_sign(soap, alg, key, keylen);
  return err;
}

/**
@fn int soap_wsse_verify_init(struct soap *soap)
@brief Uses the wsse plugin to initiate the verification of the signature and SignedInfo Reference digests.
@param soap context
@return SOAP_OK

This function does not actually verify the message, but initiates the plugin's
data to store the message in a DOM to verify the signature. The signature and
digests in the DOM must be verified manually.
*/
int
soap_wsse_verify_init(struct soap *soap)
{ DBGFUN("soap_wsse_verify_init");
  /* deserialize inbound message to DOM */
  soap->imode |= SOAP_XML_DOM;
  return SOAP_OK;
}

/**
@fn int soap_wsse_verify_auto(struct soap *soap, int alg, const void *key, size_t keylen)
@brief Uses the wsse plugin to initiate the automatic verification of the signature and SignedInfo Reference digests.
@param soap context
@param[in] alg to verify signature if signature has no secret or public key, use SOAP_SMD_NONE to omit
@param[in] key is HMAC key or EVP_PKEY or NULL
@param[in] keylen is HMAC key length or 0
@return SOAP_OK

This function does not actually verify the message, but initiates the plugin's
algorithm to store the message in a DOM to automatically verify the signature
and digests. If the message does not contain a key to verify the signature,
the alg, key, and keylen parameters are used. It is important that the X509
certificate used to verify the signature, which requires soap->cafile and/or
soap->capath to be set.
*/
int
soap_wsse_verify_auto(struct soap *soap, int alg, const void *key, size_t keylen)
{ struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  DBGFUN("soap_wsse_verify_auto");
  if (!data)
    return soap_set_receiver_error(soap, "soap_wsse_verify_auto", "Plugin not registered", SOAP_PLUGIN_ERROR);
  data->vrfy_alg = alg;
  data->vrfy_key = key;
  data->vrfy_keylen = keylen;
  if (soap->fdisconnect != soap_wsse_disconnect)
  { data->fdisconnect = soap->fdisconnect;
    soap->fdisconnect = soap_wsse_disconnect; 
  }
  return soap_wsse_verify_init(soap);
}

/**
@fn int soap_wsse_verify_done(struct soap *soap)
@brief Terminates the automatic verification of signatures.
@param soap context
@return SOAP_OK
*/
int
soap_wsse_verify_done(struct soap *soap)
{ struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  DBGFUN("soap_wsse_verify_done");
  if (!data)
    return soap_set_receiver_error(soap, "soap_wsse_verify_done", "Plugin not registered", SOAP_PLUGIN_ERROR);
  soap->imode &= ~SOAP_XML_DOM;
  soap->omode &= ~SOAP_XML_SEC;
  if (soap->fdisconnect == soap_wsse_disconnect)
    soap->fdisconnect = data->fdisconnect;
  return SOAP_OK;
}

/******************************************************************************\
 *
 * Callbacks registered by plugin
 *
\******************************************************************************/

/**
@fn int soap_wsse_prepareinit(struct soap *soap)
@brief Initiates message preprocessing with gSOAP engine's prepareinit callback.
@param soap context
@return SOAP_OK or fault

This callback is invoked to analyze a message before transmission.
*/
static int
soap_wsse_prepareinit(struct soap *soap)
{ struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  DBGFUN("soap_wsse_prepareinit");
  if (!data)
    return SOAP_PLUGIN_ERROR;
  if (data->fprepareinit)
    return data->fprepareinit(soap);
  return SOAP_OK;
}

/**
@fn int soap_wsse_preparesend(struct soap *soap, const char *buf, size_t len)
@brief Takes a piece of the XML message (tokenized) to compute digest.
@param soap context
@param[in] buf string (XML "tokenized") to be send
@param[in] len buf length
@return SOAP_OK or fault

This callback is invoked to analyze a message (usually during the HTTP content
length phase).  Note: nested elements with wsu:Id attributes cannot be
individually signed in this release.
*/
static int
soap_wsse_preparesend(struct soap *soap, const char *buf, size_t len)
{ struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  DBGFUN("soap_wsse_preparesend");
  if (!data)
    return SOAP_PLUGIN_ERROR;
  /* the gSOAP engine signals the start of a wsu:Id element */
  if (soap->part == SOAP_BEGIN_SECURITY)
  { /* found element with wsu:Id and change engine state */
    soap->part = SOAP_IN_SECURITY;
    if (data->digest && data->digest->level)
    { DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Nested hashing for signature not possible, wsu:Id='%s' ignored\n", soap->id));
    }
    else
    { /* initialize smdevp engine */
      struct soap_wsse_digest *digest;
      digest = (struct soap_wsse_digest*)SOAP_MALLOC(soap, sizeof(struct soap_wsse_digest) + strlen(soap->id) + 1);
      digest->next = data->digest;
      digest->level = soap->level;
      soap_smd_init(soap, &digest->smd, SOAP_SMD_DGST_SHA1, NULL, 0);
      memset(digest->hash, 0, sizeof(digest->hash));
      digest->id[0] = '#';
      strcpy(digest->id + 1, soap->id);
      data->digest = digest;
      /* omit indent for indented XML (next time around, we will catch '<') */
      if (*buf != '<')
        goto end;
    }
  }
  if (soap->part == SOAP_IN_SECURITY)
  { /* update smdevp engine */
    if (data->digest)
    { soap_smd_update(soap, &data->digest->smd, buf, len);
      if (soap->level < data->digest->level)
      { soap->part = SOAP_END_SECURITY;
        soap_smd_final(soap, &data->digest->smd, (char*)data->digest->hash, NULL);
        data->digest->level = 0;
      }
    }
  }
end:
  if (data->fpreparesend)
    return data->fpreparesend(soap, buf, len);
  return SOAP_OK;
}

/**
@fn int soap_wsse_preparefinal(struct soap *soap)
@brief Collects the digests of all the wsu:Id elements and populates the SignedInfo.
@param soap context
@return SOAP_OK or fault

This callback is invoked just before the message is send.
*/
static int
soap_wsse_preparefinal(struct soap *soap)
{ struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  DBGFUN("soap_wsse_preparefinal");
  if (!data)
    return SOAP_PLUGIN_ERROR;
  if (data->digest)
  { ds__SignatureType *signature = soap_wsse_Signature(soap);
    struct soap_wsse_digest *digest;
    const char *transform;
    int signature_added = 0;
    /* if message is canonicalized populate transform element accordingly */
    if (soap->mode & SOAP_XML_CANONICAL)
      transform = c14n_URI;
    else
      transform = NULL;
    /* to increase the message length counter we need to emit the Signature,
       SignedInfo and SignatureValue elements. However, this does not work if
       we already populated the wsse:Signature with SignedInfo! */
    if (!signature)
    { signature = soap_wsse_add_Signature(soap);
      signature_added = 1;
    }
    else if (signature->SignedInfo)
      return soap_set_receiver_error(soap, "wsse error", "Cannot use soap_wsse_sign with populated SignedInfo", SOAP_SSL_ERROR);
    /* add the SignedInfo/Reference elements for each digest */
    for (digest = data->digest; digest; digest = digest->next)
      soap_wsse_add_SignedInfo_Reference(soap, digest->id, transform, NULL, (char*)digest->hash);
    /* then compute the signature and add it */
    soap_wsse_add_SignatureValue(soap, data->sign_alg, data->sign_key, data->sign_keylen);
    if ((soap->mode & SOAP_IO) != SOAP_IO_CHUNK)
    { /* the code below ensures we increase the HTTP length counter */
      if (soap->mode & SOAP_XML_CANONICAL)
      { soap->ns = 0; /* need namespaces for canonicalization */
        if (soap->mode & SOAP_XML_INDENT)
          soap->count += 5; /* correction for soap->ns = 0: add \n+indent */
      }
      if (signature_added)
      { soap->level = 3; /* indent level for XML Signature */
        soap_out_ds__SignatureType(soap, "ds:Signature", 0, signature, NULL);
      }
      else
      { soap->level = 4; /* indent level for XML SignedInfo */
        soap->c14nexclude = "ds"; /* don't add xmlns:ds */
        soap_out_ds__SignedInfoType(soap, "ds:SignedInfo", 0, signature->SignedInfo, NULL);
        soap_outstring(soap, "ds:SignatureValue", 0, &signature->SignatureValue, NULL, 0);
        soap->c14nexclude = NULL;
      }
    }
  }
  /* Reset the callbacks and cleanup digests */
  soap_wsse_preparecleanup(soap, data);
  if (soap->fpreparefinal)
    return soap->fpreparefinal(soap);
  return SOAP_OK;
}

/**
@fn void soap_wsse_preparecleanup(struct soap *soap, struct soap_wsse_data *data)
@brief Restores engine state.
@param soap context
@param[in,out] data plugin data
*/
static void
soap_wsse_preparecleanup(struct soap *soap, struct soap_wsse_data *data)
{ struct soap_wsse_digest *digest, *next;
  DBGFUN("soap_wsse_preparecleanup");
  data->sign_alg = SOAP_SMD_NONE;
  data->sign_key = NULL;
  data->sign_keylen = 0;
  if (soap->fprepareinit == soap_wsse_prepareinit)
    soap->fprepareinit = data->fprepareinit;
  if (soap->fpreparesend == soap_wsse_preparesend)
    soap->fpreparesend = data->fpreparesend;
  if (soap->fpreparefinal == soap_wsse_preparefinal)
    soap->fpreparefinal = data->fpreparefinal;
  data->fprepareinit = NULL;
  data->fpreparesend = NULL;
  data->fpreparefinal = NULL;
  for (digest = data->digest; digest; digest = next)
  { next = digest->next;
    SOAP_FREE(soap, digest);
  }
  data->digest = NULL;
}

/**
@fn int soap_wsse_disconnect(struct soap *soap)
@brief Verify signature and SignedInfo digests initiated with soap_wsse_verify_auto.
@param soap context
@return SOAP_OK or fault
@see soap_wsse_verify_auto

This callback is invoked just after a message was received.
*/
static int
soap_wsse_disconnect(struct soap *soap)
{ struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  ds__SignedInfoType *signedInfo = soap_wsse_SignedInfo(soap);
  soap->imode &= ~SOAP_XML_DOM;
  soap->omode &= ~SOAP_XML_SEC;
  DBGFUN("soap_wsse_disconnect");
  if (!data)
    return SOAP_PLUGIN_ERROR;
  if (soap->fdisconnect == soap_wsse_disconnect)
    soap->fdisconnect = data->fdisconnect;
  if (signedInfo)
  { int alg, keylen = 0;
    const void *key = NULL;
    /* determine which signature algorithm was used */
    if (soap_wsse_get_SignedInfo_SignatureMethod(soap, &alg))
      return soap->error;
    /* for HMAC-SHA1, the secret key might be stored in the KeyIdentifier */
    if (alg == SOAP_SMD_HMAC_SHA1)
    { const char *valueType = soap_wsse_get_KeyInfo_SecurityTokenReferenceKeyIdentifierValueType(soap);
      /* if in the KeyIdentifier, retrieve it */
      if (valueType && !strcmp(valueType, ds_hmac_sha1URI))
      { DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Using HMAC key from KeyIdentifier to verify signature\n"));
        key = soap_wsse_get_KeyInfo_SecurityTokenReferenceKeyIdentifier(soap, &keylen);
      }
      else if (alg == data->vrfy_alg)
      { /* get the HMAC secret key from the plugin */
        DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Using HMAC key from plugin to verify signature\n"));
        key = data->vrfy_key;
        keylen = data->vrfy_keylen;
      }
    }
    else
    { X509 *cert;
      /* get the certificate from the KeyInfo reference */
      cert = soap_wsse_get_KeyInfo_SecurityTokenReferenceX509(soap);
      /* next, try the plugin's security token handler */
      if (!cert)
      { if (data->security_token_handler)
        { DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Getting certificate through security_token_handler callback\n"));
          cert = data->security_token_handler(soap);
        }
      }
      /* obtain the public key from the cert */
      if (cert)
        key = X509_get_pubkey(cert);
      else if (alg == data->vrfy_alg)
      { /* get the public key from the plugin */
        DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Using public key from plugin to verify signature\n"));
        key = data->vrfy_key;
        soap->error = SOAP_OK;
      }
    }
    /* if still no key, return fault */
    if (!key)
      return soap_wsse_fault(soap, wsse2__SecurityTokenUnavailable, NULL);
    /* verify SignedInfo with signature and check digests of local elements */
    if (soap_wsse_verify_SignatureValue(soap, alg, key, keylen)
     || soap_wsse_verify_SignedInfo(soap))
      return soap->error;
    data->vrfy_alg = SOAP_SMD_NONE;
    if (soap->fdisconnect)
      return soap->fdisconnect(soap);
    return SOAP_OK;
  }
  return soap_wsse_fault(soap, wsse2__FailedCheck, NULL);
}
