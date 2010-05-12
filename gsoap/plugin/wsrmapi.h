/*
	wsrmapi.h

	WS-ReliableMessaging plugin.

	See wsrmapi.c for documentation and details.

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

#ifndef WSRMAPI_H
#define WSRMAPI_H

#include "wsaapi.h" /* also includes stdsoap2.h, soapH.h */
#include "threads.h" /* mutex for sequence database */

#ifdef __cplusplus
extern "C" {
#endif

/** Plugin identification for plugin registry */
#define SOAP_WSRM_ID "WS-RM-1.1"

/** Plugin identification for plugin registry */
extern const char soap_wsrm_id[];

/** Max number of retries that soap_wsrm_check_retry can succeed */
#ifndef SOAP_WSRM_MAX_RETRIES
# define SOAP_WSRM_MAX_RETRIES 100
#endif

/** Max seconds to expire a non-terminated sequence and reclaim its resources */
#ifndef SOAP_WSRM_MAX_SEC_TO_EXPIRE
# define SOAP_WSRM_MAX_SEC_TO_EXPIRE 3600
#endif

/** Seconds to timeout when sending ack messages to independent acksto server */
#ifndef SOAP_WSRM_TIMEOUT
# define SOAP_WSRM_TIMEOUT 10
#endif

/**
@enum soap_wsrm_state
@brief wsrm engine state
*/
enum soap_wsrm_enable { SOAP_WSRM_OFF, SOAP_WSRM_ON };

/**
@struct soap_wsrm_data
@brief Plugin data.
*/
struct soap_wsrm_data
{ enum soap_wsrm_enable state;
  struct soap_wsrm_sequence *seq;
  struct soap_wsrm_message *msg;
  int (*fsend)(struct soap*, const char*, size_t);
  int (*fpreparefinalrecv)(struct soap*);
  int (*fdisconnect)(struct soap*);
};

/**
@enum soap_wsrm_message_state
@brief Message state (init, nack or ack)
*/
enum soap_wsrm_message_state { SOAP_WSRM_INIT, SOAP_WSRM_NACK, SOAP_WSRM_ACK };

/**
@struct soap_wsrm_message
@brief Linked list of unacknowledged messages stored for retransmission.
*/
struct soap_wsrm_message
{ ULONG64 num;					/**< message number */
  enum soap_wsrm_message_state state;		/**< (n)ack state */
  struct soap_wsrm_content *list, *last;	/**< list of content blocks */
  struct soap_wsrm_message *next;		/**< next message in list */
};

/**
@struct soap_wsrm_content
@brief Linked list of message content blocks.
*/
struct soap_wsrm_content
{ char *buf;
  size_t len;
  struct soap_wsrm_content *next;
};

/**
@struct soap_wsrm_ranges
@brief Linked list of message range numbers.
*/
struct soap_wsrm_range
{ ULONG64 upper, lower;			/**< range */
  struct soap_wsrm_range *next;		/**< next range in list */
};

/**
@enum soap_wsrm_state
@brief Sequence state
*/
enum soap_wsrm_state
{ SOAP_WSRM_NONE,
  SOAP_WSRM_UNKNOWN,
  SOAP_WSRM_CREATED,
  SOAP_WSRM_CLOSED,
  SOAP_WSRM_TERMINATED
};

/**
@struct soap_wsrm_sequence
@brief Linked list of currently active message sequences.
*/
struct soap_wsrm_sequence
{ struct soap_wsrm_sequence *next;	/**< next sequence */
  short handle;		/**< sequence in use by source (has a handle) */
  const char *id;	/**< sequence ID (from dest) */
  const char *acksid;	/**< sequence ID for ack requests (gen by source) */
  const char *to;	/**< to endpoint */
  const char *acksto;	/**< ack to endpoint */
  time_t expires;	/**< date/time of expiration */
  int retry;		/**< retry count */
  enum wsrm__IncompleteSequenceBehaviorType behavior;
  ULONG64 num;		/**< current message num */
  ULONG64 lastnum;	/**< last num received */
  enum wsrm__FaultCodes fault;		/**< sequence fault (use when error) */
  enum soap_wsrm_state state;		/**< sequence state */
  struct soap_wsrm_message *messages;	/**< stores msg content */
  struct soap_wsrm_range *ranges;	/**< ranges of received messages */
};

typedef struct soap_wsrm_sequence *soap_wsrm_sequence_handle;

int soap_wsrm(struct soap *soap, struct soap_plugin *plugin, void *arg);

int soap_wsrm_create(struct soap *soap, const char *to, const char *acksto, LONG64 expires, const char *wsa_id, soap_wsrm_sequence_handle *seq);
int soap_wsrm_create_offer(struct soap *soap, const char *to, const char *acksto, const char *id, LONG64 expires, enum wsrm__IncompleteSequenceBehaviorType behavior, const char *wsa_id, soap_wsrm_sequence_handle *seq);

int soap_wsrm_request_num(struct soap *soap, soap_wsrm_sequence_handle seq, const char *wsa_id, const char *wsa_action, ULONG64 num);
int soap_wsrm_request(struct soap *soap, soap_wsrm_sequence_handle seq, const char *wsa_id, const char *wsa_action);
int soap_wsrm_request_acks(struct soap *soap, soap_wsrm_sequence_handle seq, const char *wsa_id, const char *wsa_action);

int soap_wsrm_check_retry(struct soap *soap, soap_wsrm_sequence_handle seq);

int soap_wsrm_resend(struct soap *soap, soap_wsrm_sequence_handle seq, ULONG64 lower, ULONG64 upper);

int soap_wsrm_close(struct soap *soap, soap_wsrm_sequence_handle seq, const char *wsa_id);

int soap_wsrm_terminate(struct soap *soap, soap_wsrm_sequence_handle seq, const char *wsa_id);

void soap_wsrm_seq_free(struct soap *soap, soap_wsrm_sequence_handle seq);

void soap_wsrm_cleanup(struct soap *soap);

const char *soap_wsrm_to(soap_wsrm_sequence_handle seq);
const char *soap_wsrm_acksto(soap_wsrm_sequence_handle seq);
ULONG64 soap_wsrm_num(soap_wsrm_sequence_handle seq);
ULONG64 soap_wsrm_nack(soap_wsrm_sequence_handle seq);

int soap_wsrm_check(struct soap *soap);

int soap_wsrm_reply_num(struct soap *soap);
int soap_wsrm_reply(struct soap *soap, const char *wsa_id, const char *wsa_action);
int soap_wsrm_reply_request_acks(struct soap *soap, const char *wsa_id, const char *wsa_action);

int soap_wsrm_fault_subcode(struct soap *soap, int flag, const char *faultsubcode, const char *faultstring, const char *faultdetail);
int soap_wsrm_sender_fault_subcode(struct soap *soap, const char *faultsubcode, const char *faultstring, const char *faultdetail);
int soap_wsrm_receiver_fault_subcode(struct soap *soap, const char *faultsubcode, const char *faultstring, const char *faultdetail);
int soap_wsrm_sender_fault(struct soap *soap, const char *faultstring, const char *faultdetail);
int soap_wsrm_receiver_fault(struct soap *soap, const char *faultstring, const char *faultdetail);

int soap_wsrm_check_fault(struct soap *soap, enum wsrm__FaultCodes *fault, const char **info);
int soap_wsrm_error(struct soap *soap, struct soap_wsrm_sequence *seq, enum wsrm__FaultCodes fault);

void soap_wsrm_dump(struct soap *soap, FILE *fd);

#ifdef __cplusplus
}
#endif

#endif
