/*
	wsrmdemo.h

	WS-ReliableMessaging and WS-Addressing demo service and client.
	This file is to be passed to soapcpp2 only.

	See usage comments below.

gSOAP XML Web services tools
Copyright (C) 2000-20110 Robert van Engelen, Genivia Inc., All Rights Reserved.
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
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------

	This example application demonstrates server-side and client-side logic
	for services based on WS-ReliableMessaging (which uses WS-Addressing).

	WS-ReliableMessaging provides a reliable message sequence mechanism. A
	message sequence is created by the WS-RM source (e.g. client), the
	messages follow with possible acknowledgements and resends of
	unacknowledged messages in between, then the sequence is closed and
	finally terminated. Sequences can expire, to allow local resources to
	be reclaimed.

	WS-ReliableMessaging is not useful to improve the reliability of
	request-response message exchanges between two parties over HTTP, since
	receiving a response obviously indicates successful delivery of the
	request.

	WS-ReliableMessaging is useful to improve the reliability of one-way
	asynchronous messaging, for unreliable data gram messaging
	(SOAP-over-UDP), or when responses are relayed to other destinations,
	such as response messages that are relayed to destinations indicated by
	the WS-Addressing ReplyTo header. It is also useful when multiple
	sources are sending messages that arrive in different order or must be
	flagged as an incomplete message assemble when messages are missing as
	defined by the notion of a sequence of related messages.

	WS-ReliableMessaging ensures that all messages must have been received
	for the message sequence to terminate normally (indicated by the
	DiscardEntireSequence behavior). Messages in a sequence are enumerated
	and message acknowledgements are message ranges received.
	Acknowledgements are normally sent to the source to help identify which
	messages should be resend. Acknowledgements can also be send to a
	destination, the AcksTo destination server.

	This example also uses WS-Addressing to indicate the ReplyTo and
	FaultTo destinations. WS-Addressing enables forwarding/relaying of
	service responses (ReplyTo) and faults (FaultTo) to other services. At
	the client side, a relayed response or fault will not be received and
	an HTTP ACCEPTED (code 202) is delivered instead, indicating that the
	relay was successful.

	This header file illustrates two gSOAP soapcpp2 tooling tricks to
	enable services to accept SOAP Fault messages (the SOAP_ENV__Fault
	message definition below) and to create a one-way service operation to
	handle WS-Addressing relayed responses (the ns__wsrmdemoResponse
	one-way message definition below) to accept a response as a service
	request.

	Compile with (note the use of soapcpp2 -a to handle http action header):

	soapcpp2 -a -c -Iimport wsrmdemo.h
	cc -Iplugin -o wsrmdemo wsrmdemo.c stdsoap2.c soapC.c soapClient.c soapServer.c plugin/wsaapi.c plugin/wsrmapi.c custom/duration.c

	Alternative compile step, to use SOAP-over-UDP testing (no HTTP!):
	cc -Iplugin -DWITH_UDP -o wsrmdemo_udp wsrmdemo.c stdsoap2.c soapC.c soapClient.c soapServer.c plugin/wsaapi.c plugin/wsrmapi.c custom/duration.c

	Alternative compile step, to use HTTPS and Basic Authentication:
	cc -Iplugin -DWITH_OPENSSL -o wsrmdemo_ssl wsrmdemo.c stdsoap2.c soapC.c soapClient.c soapServer.c plugin/wsaapi.c plugin/wsrmapi.c custom/duration.c -lssl -l crypto

	Usage:

	After compilation, start the main server at port 11001:
	> ./wsrmdemo 11001

	In a new window, start an ack service (AcksTo) at port 11002:
	> ./wsrmdemo 11002
	This service accepts WS-RM acknowledgements from the main server when
	the client uses option 'a' to redirect acks (this is the AcksTo server)

	In a new window, start a reply service (ReplyTo) at port 11003:
	> ./wsrmdemo 11003
	This service accepts relayed response messages from the main service.

	In a new window, start a fault service (FaultTo) at port 11004:
	> ./wsrmdemo 11004
	This service handles faults relayed from the main service.

	In a new window, run the client:
	> ./wsrmdemo hello
	This example shows the main server returning "hello" to the client.
	WS-RM message acknowledgements are also returned to the client as
	piggy-backed headers, so the client keeps track of ack'ed messages that
	do not need to be resend.

	> ./wsrmdemo hello f
	This example shows the main server returning "hello" to the client.
	The WS-Addressing From, ReplyTo, and WS-RM Acksto headers are set to
	the client's address. Thus, the behavior is the same as above with the
	response with the piggy-backed WS-RM message acknowledgements is
	returned to the client.

	> ./wsrmdemo hello a
	This example shows the main server returning "hello" to the client.
	WS-RM message acknowledgements are send to the AcksTo server. The
	client does not receive acks, so it issues more resends than stricly
	necessary.

	> ./wsrmdemo hello fa
	Same as above, but also sets the WS-Addessing From header and sets the
	Reply header to the client's address. This has no effect on the relayed
	WS-RM message acknowledgement messages to the AcksTo server.

	> ./wsrmdemo hello r
	This example shows the main server returning "hello" to the ReplyTo
	service. WS-RM message acknowledgements are returned to the client.
	The client receives WS-RM message acknowledgements and can keep track
	of ack'ed messages that do not need to be resend. Note on
	SOAP-over-UDP: the client's first message will timeout because it uses
	two-way messages. An ack is returned for the second message.

	> ./wsrmdemo hello fr
	Same as above, but also sets the WS-Addessing From header. This has no
	effect on the relayed response and acknowledgement messages.

	> ./wsrmdemo hello ra
	This example shows the main server returning "hello" to the ReplyTo
	service. WS-RM message acknowledgements are send to the AcksTo server.
	The client does not receive acks, so it issues more resends than
	stricly necessary. Note on SOAP-over-UDP: the client will timeout
	because it uses two-way messages and no response is received.
	
	> ./wsrmdemo hello fra
	Same as above, but also sets the WS-Addessing From header. This has no
	effect on the relayed response and acknowledgement messages.

	> ./wsrmdemo hello n
	This example shows the server accepting the message without reply.
	WS-RM message acknowledgements are returned to the client. Note on
	SOAP-over-UDP: the client's first message will timeout because it
	expects two-way messages. An ack is returned for the second message.
	Because no reply is produced (messages are one-way), the client uses
	soap_wsrm_create() without offer.

	> ./wsrmdemo hello fn
	Same as above, but also sets the WS-Addessing From header. This has no
	effect on the relayed acknowledgement messages.

	> ./wsrmdemo hello na
	This example shows the server accepting the message without reply.
	WS-RM message acknowledgements are send to the AcksTo server. The
	client does not receive acks, so it issues more resends than stricly
	necessary. Note on SOAP-over-UDP: the client will timeout because it
	exects two-way messages and no response is received. An ack is returned
	for the second message. Because no reply is produced (messages are
	one-way), the client uses soap_wsrm_create() without offer.

	> ./wsrmdemo hello fna
	Same as above, but also sets the WS-Addessing From header. This has no
	effect on the relayed acknowledgement messages.

	> ./wsrmdemo error
	This example shows the main server simulating a server operation fault.
	The error is considered fatal, so the server terminates the sequence.

	> ./wsrmdemo error e
	This example shows the main server simulating a server operation fault.
	The fault is relayed to the FaultTo service. The error is considered
	fatal, so the server terminates the sequence.

	> ./wsrmdemo fault
	This example shows the main server simulating a server operation fault.
	The message was received, so even though an error occurred the message
	was successfully received and counts as part of the sequence.

	> ./wsrmdemo fault e
	This example shows the main server simulating a server operation fault.
	The fault is relayed to the FaultTo service. The message was received,
	so even though an error occurred the message was successfully received
	and counts as part of the sequence.

	Note 1: when the ReplyTo service is down, the response cannot be
	relayed and the client (or fault service) will be informed about the
	failure.

	Note 2: HTTP Basic authentication can be enabled by setting the
	following values in wsrmdemo.c:
		const char *userid = "...";
		const char *passwd = "...";
	The client operations set HTTP Basic Auth while server operation check
	it. The WS-RM CreateSequence, CloseSequence, and TerminateSequence do
	NOT check the credentials of the client (only the sequence messages).
	Of course, and incomplete sequence abnormally terminates when the
	behavior is set to DiscardEntireSequence.

	Note 3: HTTP compression can be enabled by compiling the sources with
	-DWITH_ZLIB. Then use SOAP_ENC_ZLIB flag to send compressed messages.

	Note 4: HTTPS can be enabled by compiling with -DWITH_OPENSSL.

	Note 5: The client is set-up for two-way messaging, so UDP one-way
	messaging is not demonstrated. This also leads to timeouts at the
	client side when no response is received (and no acks or faults). To
	implement one-way messaging, please refer to the documentation.

*/

#import "soap12.h"
#import "wsrm.h"
#import "wsa5.h"

//gsoap ns service name:	wsrmdemo demonstrates WS-Addressing capabilities
//gsoap ns service port:	http://localhost:11001
//gsoap ns service type:	wsrmdemoPort
//gsoap ns service namespace:	urn:wsrmdemo

/* STEP 1: generate SOAP-ENV:Fault struct via a one-way service operation.
 * This allows us to implement a one-way service operation that accepts Faults.
 * Because a service operation input parameters has a corresponding struct, we
 * automatically generate the (original) SOAP_ENV__Fault struct on the fly!
 * Note: it is important to associate the wsa fault action with this operation
 * as defined below.
 */ 

//gsoap SOAP_ENV service method-action: Fault http://schemas.xmlsoap.org/ws/2004/08/addressing/fault
int SOAP_ENV__Fault
(       _QName			 faultcode,		// SOAP 1.1
        char			*faultstring,		// SOAP 1.1
        char			*faultactor,		// SOAP 1.1
        struct SOAP_ENV__Detail	*detail,		// SOAP 1.1
        struct SOAP_ENV__Code	*SOAP_ENV__Code,	// SOAP 1.2
        struct SOAP_ENV__Reason	*SOAP_ENV__Reason,	// SOAP 1.2
        char			*SOAP_ENV__Node,	// SOAP 1.2
        char			*SOAP_ENV__Role,	// SOAP 1.2
        struct SOAP_ENV__Detail	*SOAP_ENV__Detail,	// SOAP 1.2
	void
);

/* STEP 2: for the server side we need to generate a response struct for each
 * operation to implement one-way service response operations that can be
 * relayed. Because the service operation has a corresponding struct, we can
 * use that struct as a response parameter for the second two-way service
 * operation. This step is required to implement a wsa-capable server.
 */

//gsoap ns service method-header-part:     wsrmdemoResponse wsa5__MessageID
//gsoap ns service method-header-part:     wsrmdemoResponse wsa5__RelatesTo
//gsoap ns service method-header-part:     wsrmdemoResponse wsa5__From
//gsoap ns service method-header-part:     wsrmdemoResponse wsa5__ReplyTo
//gsoap ns service method-header-part:     wsrmdemoResponse wsa5__FaultTo
//gsoap ns service method-header-part:     wsrmdemoResponse wsa5__To
//gsoap ns service method-header-part:     wsrmdemoResponse wsa5__Action
//gsoap ns service method-header-part:     wsrmdemoResponse wsrm__Sequence
//gsoap ns service method-header-part:     wsrmdemoResponse wsrm__AckRequested
//gsoap ns service method-header-part:     wsrmdemoResponse wsrm__SequenceAcknowledgement
//gsoap ns service method-action:          wsademoResponse urn:wsrmdemo/wsrmdemoPort/wsrmdemoResponse
//gsoap ns service method-documentation:   wsrmdemoResponse accepts a string value from a relayed response
int ns__wsrmdemoResponse(char *out, void);

//gsoap ns service method-header-part:     wsrmdemo wsa5__MessageID
//gsoap ns service method-header-part:     wsrmdemo wsa5__RelatesTo
//gsoap ns service method-header-part:     wsrmdemo wsa5__From
//gsoap ns service method-header-part:     wsrmdemo wsa5__ReplyTo
//gsoap ns service method-header-part:     wsrmdemo wsa5__FaultTo
//gsoap ns service method-header-part:     wsrmdemo wsa5__To
//gsoap ns service method-header-part:     wsrmdemo wsa5__Action
//gsoap ns service method-header-part:     wsrmdemo wsrm__Sequence
//gsoap ns service method-header-part:     wsrmdemo wsrm__AckRequested
//gsoap ns service method-header-part:     wsrmdemo wsrm__SequenceAcknowledgement
//gsoap ns service method-action:          wsrmdemo urn:wsrmdemo/wsrmdemoPort/wsrmdemo
//gsoap ns service method-response-action: wsrmdemo urn:wsrmdemo/wsrmdemoPort/wsrmdemoResponse
//gsoap ns service method-documentation:   wsrmdemo echos a string value and relays the response to the wsa replyTo address (if present)
int ns__wsrmdemo(char *in, struct ns__wsrmdemoResponse *result);
