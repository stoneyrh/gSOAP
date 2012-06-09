/*
	calculator.cpp

	WCF wsDualHttpBinding demo

	See the README.txt

gSOAP XML Web services tools
Copyright (C) 2000-2012, Robert van Engelen, Genivia Inc., All Rights Reserved.
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
Copyright (C) 2000-2012, Robert van Engelen, Genivia Inc., All Rights Reserved.
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

#include "soapWSDualHttpBinding_USCOREICalculatorDuplexService.h"
#include "soapWSDualHttpBinding_USCOREICalculatorDuplexProxy.h"
#include "WSDualHttpBinding_USCOREICalculatorDuplex.nsmap"

// Set to the service URI, or NULL for default endpoint
//const char *serverURI = "http://localhost:8000";
const char *serverURI = "http://192.168.2.2:8000/ServiceModelSamples/service";

// Set to the client callback URI and port, or NULL for default endpoint
//const char *clientURI = "http://localhost:8001";
const char *clientURI = "http://10.0.1.2:8001";
int clientPort = 8001;

#include <sstream>
#include "wsrmapi.h"

class Service : public WSDualHttpBinding_USCOREICalculatorDuplexService
{
  private:
    double result;
    std::stringstream equation;
    WSDualHttpBinding_USCOREICalculatorDuplexProxy callback;

  public:
    Service()
    {
      soap_set_mode(soap, SOAP_XML_INDENT);
      soap_register_plugin(soap, soap_wsa);
      soap_register_plugin(soap, soap_wsrm);
      soap->send_timeout = soap->recv_timeout = 10; // 10 sec

      soap_set_mode(callback.soap, SOAP_XML_INDENT);
      soap_register_plugin(callback.soap, soap_wsa);
      soap_register_plugin(callback.soap, soap_wsrm);
      callback.soap->send_timeout = callback.soap->recv_timeout = 10; // 10 sec

      result = 0.0;
      equation.str("");
      equation << 0.0;
    }
    ~Service()
    {
      destroy();
      callback.destroy();
    }
    int start(int port);
    int Clear(_mssadh__Clear*);
    int AddTo(_mssadh__AddTo*);
    int SubtractFrom(_mssadh__SubtractFrom*);
    int MultiplyBy(_mssadh__MultiplyBy*);
    int DivideBy(_mssadh__DivideBy*);
};

class Client : public WSDualHttpBinding_USCOREICalculatorDuplexProxy
{
  private:
    WSDualHttpBinding_USCOREICalculatorDuplexService callback;

  public:
    Client(const char *serverURI)
    {
      soap_set_mode(soap, SOAP_XML_INDENT);
      soap_register_plugin(soap, soap_wsa);
      soap_register_plugin(soap, soap_wsrm);
      soap_endpoint = serverURI;
      soap->send_timeout = soap->recv_timeout = 10; // 10 sec

      soap_set_mode(callback.soap, SOAP_XML_INDENT);
      soap_register_plugin(callback.soap, soap_wsa);
      soap_register_plugin(callback.soap, soap_wsrm);
      callback.soap->send_timeout = callback.soap->recv_timeout = 10; // 10 sec

      if (!soap_valid_socket(callback.bind(NULL, clientPort, 100)))
      {
        callback.soap_stream_fault(std::cerr);
        exit(1);
      }
    }
    ~Client()
    {
      destroy();
      callback.destroy();
    }
    int poll(int timeout);
};

int main(int argc, char **argv)
{
  // Command line argument? yes, then run the service on a port
  if (argc >= 2)
  {
    int port = atoi(argv[1]);
    Service service;
    service.start(port);
  }
  else
  {
    Client client(serverURI);

    // Create a reliable messaging sequence handle for client-initiated session
    soap_wsrm_sequence_handle seq;

    xsd__duration expires = 30000; /* 30000 ms = 30 seconds to expire */
    const char *id = soap_wsa_rand_uuid(client.soap);
    double n;

    printf("\n**** Creating the Sequence\n");

    // Reliable messaging create session and init sequence handle
    if (soap_wsrm_create_offer(client.soap, serverURI, clientURI, id, expires, NoDiscard, soap_wsa_rand_uuid(client.soap), &seq))
    {
      client.soap_stream_fault(std::cerr);
      soap_wsrm_seq_free(client.soap, seq);
      return client.soap->error;
    }

    client.poll(-100000); // callback polling: 100 ms polling cycle

    // Reliable messaging request message
    if (soap_wsrm_request_acks(client.soap, seq, soap_wsa_rand_uuid(client.soap), "http://Microsoft.Samples.DualHttp/ICalculatorDuplex/AddTo"))
    {
      client.soap_stream_fault(std::cerr);
      return client.soap->error;
    }
    // Set ReplyTo and Faulto to client URI, so callback receives these messages
    soap_wsa_add_ReplyTo(client.soap, clientURI);
    soap_wsa_add_FaultTo(client.soap, clientURI);

    n = 3.14;

    _mssadh__AddTo addTo;
    addTo.n = &n;
    if (client.send_AddTo(&addTo) == SOAP_OK || client.soap->error == 202)
      std::cout << std::endl << "**** AddTo(" << *addTo.n << ")" << std::endl;
    else
      client.soap_stream_fault(std::cerr);
    client.destroy();

    client.poll(-100000); // callback polling: 100 ms polling cycle

    // Reliable messaging request message
    if (soap_wsrm_request_acks(client.soap, seq, soap_wsa_rand_uuid(client.soap), "http://Microsoft.Samples.DualHttp/ICalculatorDuplex/SubtractFrom"))
    {
      client.soap_stream_fault(std::cerr);
      return client.soap->error;
    }
    // Set ReplyTo and Faulto to client URI, so callback receives these messages
    soap_wsa_add_ReplyTo(client.soap, clientURI);
    soap_wsa_add_FaultTo(client.soap, clientURI);

    n = 1.41;

    _mssadh__SubtractFrom subtractFrom;
    subtractFrom.n = &n;
    if (client.send_SubtractFrom(&subtractFrom) == SOAP_OK || client.soap->error == 202)
      std::cout << std::endl << "**** SubtractFrom(" << *subtractFrom.n << ")" << std::endl;
    else
      client.soap_stream_fault(std::cerr);
    client.destroy();

    client.poll(-100000); // callback polling: 100 ms polling cycle

    // Reliable messaging request message
    if (soap_wsrm_request_acks(client.soap, seq, soap_wsa_rand_uuid(client.soap), "http://Microsoft.Samples.DualHttp/ICalculatorDuplex/Clear"))
    {
      client.soap_stream_fault(std::cerr);
      return client.soap->error;
    }
    // Set ReplyTo and Faulto to client URI, so callback receives these messages
    soap_wsa_add_ReplyTo(client.soap, clientURI);
    soap_wsa_add_FaultTo(client.soap, clientURI);

    _mssadh__Clear clear;
    if (client.send_Clear(&clear) == SOAP_OK || client.soap->error == 202)
      std::cout << std::endl << "**** Clear()" << std::endl;
    else
      client.soap_stream_fault(std::cerr);
    client.destroy();

    client.poll(-100000); // callback polling: 100 ms polling cycle

    // Reliable messaging: resend messages marked as non-acked (as an option)
    // This ensures we did not lose any calculations before getting result and
    // result can be trusted
    if (soap_wsrm_nack(seq))
    {
      printf("\n**** Resending "SOAP_ULONG_FORMAT" Non-Acked Messages\n", soap_wsrm_nack(seq));
      soap_wsrm_resend(client.soap, seq, 0, 0); /* 0 0 means full range of msg nums */
      client.poll(-100000); // callback polling: 100 ms polling cycle
    }

    printf("\n**** Acknowledge the Sequence Messages (optional)\n");

    if (soap_wsrm_acknowledgement(client.soap, seq, soap_wsa_rand_uuid(client.soap)))
    {
      client.soap_stream_fault(std::cerr);
      soap_wsrm_seq_free(client.soap, seq);
      return client.soap->error;
    }

    printf("\n**** Closing the Sequence\n");

    if (soap_wsrm_close(client.soap, seq, soap_wsa_rand_uuid(client.soap)))
    {
      client.soap_stream_fault(std::cerr);
      soap_wsrm_seq_free(client.soap, seq);
      return client.soap->error;
    }

    client.poll(-100000); // callback polling: 100 ms polling cycle

    printf("\n**** Terminating the Sequence\n");

    // Termination fails if the server did not get all messages
    if (soap_wsrm_terminate(client.soap, seq, soap_wsa_rand_uuid(client.soap)))
    {
      client.soap_stream_fault(std::cerr);
      soap_wsrm_seq_free(client.soap, seq);
      return client.soap->error;
    }

    client.poll(-100000); // callback polling: 100 ms polling cycle

    // Delete the reliable messaging session sequence
    soap_wsrm_seq_free(client.soap, seq);

  }
  return 0;
}

/******************************************************************************\
 *
 *	Client-side callback polling
 *
\******************************************************************************/

int Client::poll(int timeout)
{
  callback.soap->accept_timeout = timeout;

  printf("\n**** Callback Polling\n");

  while (soap_valid_socket(callback.accept()))
  {
    /* chain the WSRM operations after callback operations */
    if (soap_begin_serve(callback.soap) == SOAP_OK)
    {
      if (callback.dispatch() == SOAP_NO_METHOD)
      {
        if (soap_serve_request(callback.soap) != SOAP_OK)
          callback.soap_stream_fault(std::cerr);
      }
      else if (callback.soap->error)
        callback.soap_stream_fault(std::cerr);
    }
    callback.destroy();
    soap_wsrm_dump(callback.soap, stdout);
  }

  return SOAP_OK;
}

/******************************************************************************\
 *
 *	Client-side callback operations via callback polling service
 *
\******************************************************************************/

int WSDualHttpBinding_USCOREICalculatorDuplexService::Result(_mssadh__Result *req)
{
  /* check for WS-RM/WSA and set WS-RM/WSA return headers */
  if (soap_wsrm_check(soap))
    return soap->error;

  if (req->result)
    std::cout << std::endl << "**** Result(" << *req->result << ")" << std::endl;

  /* this is a one-way operation over HTTP */
  return soap_send_empty_response(soap, 202);
}

int WSDualHttpBinding_USCOREICalculatorDuplexService::Equation(_mssadh__Equation *req)
{
  /* check for WS-RM/WSA and set WS-RM/WSA return headers */
  if (soap_wsrm_check(soap))
    return soap->error;

  if (req->eqn)
    std::cout << std::endl << "**** Equation(" << *req->eqn << ")" << std::endl;

  /* this is a one-way operation over HTTP */
  return soap_send_empty_response(soap, 202);
}

/******************************************************************************\
 *
 *	Service operations
 *
\******************************************************************************/

int Service::start(int port)
{
  if (!soap_valid_socket(bind(NULL, port, 100)))
  {
    soap_stream_fault(std::cerr);
    exit(1);
  }
  std::cerr << "Server running" << std::endl;
  for (;;)
  {
    if (!soap_valid_socket(accept()))
    {
      soap_stream_fault(std::cerr);
      exit(1);
    }
    /* chain the WSRM service operations after the main service operations */
    if (soap_begin_serve(soap) == SOAP_OK)
    {
      if (dispatch() == SOAP_NO_METHOD)
      {
        if (soap_serve_request(soap) != SOAP_OK)
	{
	  soap_send_fault(soap);
	  soap_stream_fault(std::cerr);
        }
      }
      else if (soap->error)
        soap_stream_fault(std::cerr);
    }
    destroy();
    callback.destroy();
    soap_wsrm_dump(soap, stdout);
  }
  return SOAP_OK;
}

int Service::Clear(_mssadh__Clear *req)
{
  /* check for WS-RM/WSA and set WS-RM/WSA return headers */
  if (soap_wsrm_check(soap))
    return soap->error;

  /* get the handle to the current sequence of the inbound message */
  soap_wsrm_sequence_handle seq = soap_wsrm_seq(soap);

  /* this is a one-way operation over HTTP, so we're done with client */
  soap_send_empty_response(soap, 202);

  if (soap_wsrm_request_acks(callback.soap, seq, soap_wsa_rand_uuid(callback.soap), "http://Microsoft.Samples.DualHttp/ICalculatorDuplex/Equation"))
  { 
    callback.soap_stream_fault(std::cerr);
    return callback.soap->error;
  }
  callback.soap_endpoint = soap_wsrm_to(seq);

  equation << " = " << result;

  _mssadh__Equation eqn;
  std::string s = equation.str();
  eqn.eqn = &s;
  if (callback.send_Equation(&eqn) == SOAP_OK || callback.soap->error == 202)
    std::cout << "Equation(" << s << ")" << std::endl;
  else
    callback.soap_stream_fault(std::cerr);
  callback.destroy();

  result = 0.0;
  equation.str("");
  equation << 0.0;

  return SOAP_OK;
}

int Service::AddTo(_mssadh__AddTo *req)
{
  /* check for WS-RM/WSA and set WS-RM/WSA return headers */
  if (soap_wsrm_check(soap))
    return soap->error;

  if (req && req->n)
  {
    result += *req->n;
    equation << " + " << *req->n;
  }
  else
    return soap_sender_fault(soap, "Invalid data", NULL);

  /* this is a one-way operation over HTTP, so we're done with client */
  soap_send_empty_response(soap, 202);

  /* get the handle to the current sequence of the inbound message */
  soap_wsrm_sequence_handle seq = soap_wsrm_seq(soap);
  callback.soap_endpoint = soap_wsrm_to(seq);
  if (soap_wsrm_request_acks(callback.soap, seq, soap_wsa_rand_uuid(callback.soap), "http://Microsoft.Samples.DualHttp/ICalculatorDuplex/Result"))
  { 
    callback.soap_stream_fault(std::cerr);
    return callback.soap->error;
  }

  _mssadh__Result res;
  res.result = &result;
  if (callback.send_Result(&res) == SOAP_OK || callback.soap->error == 202)
    std::cout << "Result(" << result << ")" << std::endl;
  else
    callback.soap_stream_fault(std::cerr);
  callback.destroy();

  return SOAP_OK;
}

int Service::SubtractFrom(_mssadh__SubtractFrom *req)
{
  /* check for WS-RM/WSA and set WS-RM/WSA return headers */
  if (soap_wsrm_check(soap))
    return soap->error;

  if (req && req->n)
  {
    result -= *req->n;
    equation << " - " << *req->n;
  }
  else
    return soap_sender_fault(soap, "Invalid data", NULL);

  /* this is a one-way operation over HTTP, so we're done with client */
  soap_send_empty_response(soap, 202);

  /* get the handle to the current sequence of the inbound message */
  soap_wsrm_sequence_handle seq = soap_wsrm_seq(soap);
  callback.soap_endpoint = soap_wsrm_to(seq);
  if (soap_wsrm_request_acks(callback.soap, seq, soap_wsa_rand_uuid(callback.soap), "http://Microsoft.Samples.DualHttp/ICalculatorDuplex/Result"))
  { 
    callback.soap_stream_fault(std::cerr);
    return callback.soap->error;
  }

  _mssadh__Result res;
  res.result = &result;
  if (callback.send_Result(&res) == SOAP_OK || callback.soap->error == 202)
    std::cout << "Result(" << result << ")" << std::endl;
  else
    callback.soap_stream_fault(std::cerr);
  callback.destroy();

  return SOAP_OK;
}

int Service::MultiplyBy(_mssadh__MultiplyBy *req)
{
  /* check for WS-RM/WSA and set WS-RM/WSA return headers */
  if (soap_wsrm_check(soap))
    return soap->error;

  if (req && req->n)
  {
    result *= *req->n;
    equation << " * " << *req->n;
  }
  else
    return soap_sender_fault(soap, "Invalid data", NULL);

  /* this is a one-way operation over HTTP, so we're done with client */
  soap_send_empty_response(soap, 202);

  /* get the handle to the current sequence of the inbound message */
  soap_wsrm_sequence_handle seq = soap_wsrm_seq(soap);
  callback.soap_endpoint = soap_wsrm_to(seq);
  if (soap_wsrm_request_acks(callback.soap, seq, soap_wsa_rand_uuid(callback.soap), "http://Microsoft.Samples.DualHttp/ICalculatorDuplex/Result"))
  { 
    callback.soap_stream_fault(std::cerr);
    return callback.soap->error;
  }

  _mssadh__Result res;
  res.result = &result;
  if (callback.send_Result(&res) == SOAP_OK || callback.soap->error == 202)
    std::cout << "Result(" << result << ")" << std::endl;
  else
    callback.soap_stream_fault(std::cerr);
  callback.destroy();

  return SOAP_OK;
}

int Service::DivideBy(_mssadh__DivideBy *req)
{
  /* check for WS-RM/WSA and set WS-RM/WSA return headers */
  if (soap_wsrm_check(soap))
    return soap->error;

  if (req && req->n)
  {
    result /= *req->n;
    equation << " / " << *req->n;
  }
  else
    return soap_sender_fault(soap, "Invalid data", NULL);

  /* this is a one-way operation over HTTP, so we're done with client */
  soap_send_empty_response(soap, 202);

  /* get the handle to the current sequence of the inbound message */
  soap_wsrm_sequence_handle seq = soap_wsrm_seq(soap);
  callback.soap_endpoint = soap_wsrm_to(seq);
  if (soap_wsrm_request_acks(callback.soap, seq, soap_wsa_rand_uuid(callback.soap), "http://Microsoft.Samples.DualHttp/ICalculatorDuplex/Result"))
  { 
    callback.soap_stream_fault(std::cerr);
    return callback.soap->error;
  }

  _mssadh__Result res;
  res.result = &result;
  if (callback.send_Result(&res) == SOAP_OK || callback.soap->error == 202)
    std::cout << "Result(" << result << ")" << std::endl;
  else
    callback.soap_stream_fault(std::cerr);
  callback.destroy();

  return SOAP_OK;
}

/******************************************************************************\
 *
 *	Base Service operations (inactive)
 *
\******************************************************************************/

/* These service methods are defined to avoid vtable linking errors.
   A more elegant alternative is to compile all code with
     #define SOAP_PURE_VIRTUAL = NULL
   which makes all base service operations pure virtual (abstract)
*/

int WSDualHttpBinding_USCOREICalculatorDuplexService::Clear(_mssadh__Clear *req) { return SOAP_NO_METHOD; }
int WSDualHttpBinding_USCOREICalculatorDuplexService::AddTo(_mssadh__AddTo *req) { return SOAP_NO_METHOD; }
int WSDualHttpBinding_USCOREICalculatorDuplexService::SubtractFrom(_mssadh__SubtractFrom *req) { return SOAP_NO_METHOD; }
int WSDualHttpBinding_USCOREICalculatorDuplexService::MultiplyBy(_mssadh__MultiplyBy *req) { return SOAP_NO_METHOD; }
int WSDualHttpBinding_USCOREICalculatorDuplexService::DivideBy(_mssadh__DivideBy *req) { return SOAP_NO_METHOD; }
