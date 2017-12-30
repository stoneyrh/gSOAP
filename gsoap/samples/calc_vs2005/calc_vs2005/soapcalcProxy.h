/* soapcalcProxy.h
   Generated by gSOAP 2.8.59 for calc.h

gSOAP XML Web services tools
Copyright (C) 2000-2017, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#ifndef soapcalcProxy_H
#define soapcalcProxy_H
#include "soapH.h"

    class SOAP_CMAC calcProxy : public soap {
      public:
        /// Endpoint URL of service 'calcProxy' (change as needed)
        const char *soap_endpoint;
        /// Variables globally declared in calc.h, if any
        /// Construct a proxy with new managing context
        calcProxy();
        /// Copy constructor
        calcProxy(const calcProxy& rhs);
        /// Construct proxy given a managing context
        calcProxy(const struct soap&);
        /// Constructor taking an endpoint URL
        calcProxy(const char *endpoint);
        /// Constructor taking input and output mode flags for the new managing context
        calcProxy(soap_mode iomode);
        /// Constructor taking endpoint URL and input and output mode flags for the new managing context
        calcProxy(const char *endpoint, soap_mode iomode);
        /// Constructor taking input and output mode flags for the new managing context
        calcProxy(soap_mode imode, soap_mode omode);
        /// Destructor deletes deserialized data and managing context
        virtual ~calcProxy();
        /// Initializer used by constructors
        virtual void calcProxy_init(soap_mode imode, soap_mode omode);
        /// Return a copy that has a new managing context with the same engine state
        virtual calcProxy *copy();
        /// Copy assignment
        calcProxy& operator=(const calcProxy&);
        /// Delete all deserialized data (uses soap_destroy() and soap_end())
        virtual void destroy();
        /// Delete all deserialized data and reset to default
        virtual void reset();
        /// Disables and removes SOAP Header from message by setting soap->header = NULL
        virtual void soap_noheader();
        /// Get SOAP Header structure (i.e. soap->header, which is NULL when absent)
        virtual ::SOAP_ENV__Header *soap_header();
        /// Get SOAP Fault structure (i.e. soap->fault, which is NULL when absent)
        virtual ::SOAP_ENV__Fault *soap_fault();
        /// Get SOAP Fault string (NULL when absent)
        virtual const char *soap_fault_string();
        /// Get SOAP Fault detail as string (NULL when absent)
        virtual const char *soap_fault_detail();
        /// Close connection (normally automatic, except for send_X ops)
        virtual int soap_close_socket();
        /// Force close connection (can kill a thread blocked on IO)
        virtual int soap_force_close_socket();
        /// Print fault
        virtual void soap_print_fault(FILE*);
    #ifndef WITH_LEAN
    #ifndef WITH_COMPAT
        /// Print fault to stream
        virtual void soap_stream_fault(std::ostream&);
    #endif
        /// Write fault to buffer
        virtual char *soap_sprint_fault(char *buf, size_t len);
    #endif
        /// Web service operation 'add' (returns SOAP_OK or error code)
        virtual int add(double a, double b, double *result)
        { return this->add(NULL, NULL, a, b, result); }
        virtual int add(const char *soap_endpoint, const char *soap_action, double a, double b, double *result);
        /// Web service operation 'sub' (returns SOAP_OK or error code)
        virtual int sub(double a, double b, double *result)
        { return this->sub(NULL, NULL, a, b, result); }
        virtual int sub(const char *soap_endpoint, const char *soap_action, double a, double b, double *result);
        /// Web service operation 'mul' (returns SOAP_OK or error code)
        virtual int mul(double a, double b, double *result)
        { return this->mul(NULL, NULL, a, b, result); }
        virtual int mul(const char *soap_endpoint, const char *soap_action, double a, double b, double *result);
        /// Web service operation 'div' (returns SOAP_OK or error code)
        virtual int div(double a, double b, double *result)
        { return this->div(NULL, NULL, a, b, result); }
        virtual int div(const char *soap_endpoint, const char *soap_action, double a, double b, double *result);
        /// Web service operation 'pow' (returns SOAP_OK or error code)
        virtual int pow(double a, double b, double *result)
        { return this->pow(NULL, NULL, a, b, result); }
        virtual int pow(const char *soap_endpoint, const char *soap_action, double a, double b, double *result);
    };
#endif
