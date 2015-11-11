/* CalcStub.h
   Generated by gSOAP 2.8.25 from calc.h

gSOAP XML Web services tools
Copyright (C) 2000-2015, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#ifndef CalcStub_H
#define CalcStub_H
#ifndef WITH_NOGLOBAL
#define WITH_NOGLOBAL
#endif
#include "stdsoap2.h"
#if GSOAP_VERSION != 20825
# error "GSOAP VERSION 20825 MISMATCH IN GENERATED CODE VERSUS LIBRARY CODE: PLEASE REINSTALL PACKAGE"
#endif


namespace Calc {

/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes, Structs, and Unions                                               *
 *                                                                            *
\******************************************************************************/

struct ns__addResponse;	// calc.h:97
struct ns__add;	// calc.h:97
struct ns__subResponse;	// calc.h:100
struct ns__sub;	// calc.h:100
struct ns__mulResponse;	// calc.h:103
struct ns__mul;	// calc.h:103
struct ns__divResponse;	// calc.h:106
struct ns__div;	// calc.h:106
struct ns__powResponse;	// calc.h:109
struct ns__pow;	// calc.h:109

/* calc.h:97 */
#ifndef SOAP_TYPE_Calc_ns__addResponse
#define SOAP_TYPE_Calc_ns__addResponse (10)
/* ns:addResponse complex type: */
struct ns__addResponse
{
public:
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of XSD type xsd:double */
public:
	int soap_type() const { return 10; } /* = unique type id SOAP_TYPE_Calc_ns__addResponse */
	         ns__addResponse();
	virtual ~ns__addResponse() { }
};
#endif

/* calc.h:97 */
#ifndef SOAP_TYPE_Calc_ns__add
#define SOAP_TYPE_Calc_ns__add (11)
/* ns:add complex type: */
struct ns__add
{
public:
	double a;	/* required element of XSD type xsd:double */
	double b;	/* required element of XSD type xsd:double */
public:
	int soap_type() const { return 11; } /* = unique type id SOAP_TYPE_Calc_ns__add */
	         ns__add();
	virtual ~ns__add() { }
};
#endif

/* calc.h:100 */
#ifndef SOAP_TYPE_Calc_ns__subResponse
#define SOAP_TYPE_Calc_ns__subResponse (13)
/* ns:subResponse complex type: */
struct ns__subResponse
{
public:
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of XSD type xsd:double */
public:
	int soap_type() const { return 13; } /* = unique type id SOAP_TYPE_Calc_ns__subResponse */
	         ns__subResponse();
	virtual ~ns__subResponse() { }
};
#endif

/* calc.h:100 */
#ifndef SOAP_TYPE_Calc_ns__sub
#define SOAP_TYPE_Calc_ns__sub (14)
/* ns:sub complex type: */
struct ns__sub
{
public:
	double a;	/* required element of XSD type xsd:double */
	double b;	/* required element of XSD type xsd:double */
public:
	int soap_type() const { return 14; } /* = unique type id SOAP_TYPE_Calc_ns__sub */
	         ns__sub();
	virtual ~ns__sub() { }
};
#endif

/* calc.h:103 */
#ifndef SOAP_TYPE_Calc_ns__mulResponse
#define SOAP_TYPE_Calc_ns__mulResponse (16)
/* ns:mulResponse complex type: */
struct ns__mulResponse
{
public:
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of XSD type xsd:double */
public:
	int soap_type() const { return 16; } /* = unique type id SOAP_TYPE_Calc_ns__mulResponse */
	         ns__mulResponse();
	virtual ~ns__mulResponse() { }
};
#endif

/* calc.h:103 */
#ifndef SOAP_TYPE_Calc_ns__mul
#define SOAP_TYPE_Calc_ns__mul (17)
/* ns:mul complex type: */
struct ns__mul
{
public:
	double a;	/* required element of XSD type xsd:double */
	double b;	/* required element of XSD type xsd:double */
public:
	int soap_type() const { return 17; } /* = unique type id SOAP_TYPE_Calc_ns__mul */
	         ns__mul();
	virtual ~ns__mul() { }
};
#endif

/* calc.h:106 */
#ifndef SOAP_TYPE_Calc_ns__divResponse
#define SOAP_TYPE_Calc_ns__divResponse (19)
/* ns:divResponse complex type: */
struct ns__divResponse
{
public:
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of XSD type xsd:double */
public:
	int soap_type() const { return 19; } /* = unique type id SOAP_TYPE_Calc_ns__divResponse */
	         ns__divResponse();
	virtual ~ns__divResponse() { }
};
#endif

/* calc.h:106 */
#ifndef SOAP_TYPE_Calc_ns__div
#define SOAP_TYPE_Calc_ns__div (20)
/* ns:div complex type: */
struct ns__div
{
public:
	double a;	/* required element of XSD type xsd:double */
	double b;	/* required element of XSD type xsd:double */
public:
	int soap_type() const { return 20; } /* = unique type id SOAP_TYPE_Calc_ns__div */
	         ns__div();
	virtual ~ns__div() { }
};
#endif

/* calc.h:109 */
#ifndef SOAP_TYPE_Calc_ns__powResponse
#define SOAP_TYPE_Calc_ns__powResponse (22)
/* ns:powResponse complex type: */
struct ns__powResponse
{
public:
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of XSD type xsd:double */
public:
	int soap_type() const { return 22; } /* = unique type id SOAP_TYPE_Calc_ns__powResponse */
	         ns__powResponse();
	virtual ~ns__powResponse() { }
};
#endif

/* calc.h:109 */
#ifndef SOAP_TYPE_Calc_ns__pow
#define SOAP_TYPE_Calc_ns__pow (23)
/* ns:pow complex type: */
struct ns__pow
{
public:
	double a;	/* required element of XSD type xsd:double */
	double b;	/* required element of XSD type xsd:double */
public:
	int soap_type() const { return 23; } /* = unique type id SOAP_TYPE_Calc_ns__pow */
	         ns__pow();
	virtual ~ns__pow() { }
};
#endif

/* calc.h:0 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_Calc_SOAP_ENV__Header
#define SOAP_TYPE_Calc_SOAP_ENV__Header (24)
/* SOAP Header: */
struct SOAP_ENV__Header
{
public:
	int soap_type() const { return 24; } /* = unique type id SOAP_TYPE_Calc_SOAP_ENV__Header */
	         SOAP_ENV__Header();
	virtual ~SOAP_ENV__Header() { }
};
#endif
#endif

/* calc.h:0 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_Calc_SOAP_ENV__Code
#define SOAP_TYPE_Calc_SOAP_ENV__Code (25)
/* Type SOAP_ENV__Code is a recursive data type (in)directly referencing itself through its (base) class members */
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of XSD type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of XSD type SOAP-ENV:Code */
public:
	int soap_type() const { return 25; } /* = unique type id SOAP_TYPE_Calc_SOAP_ENV__Code */
	         SOAP_ENV__Code();
	virtual ~SOAP_ENV__Code() { }
};
#endif
#endif

/* calc.h:0 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_Calc_SOAP_ENV__Detail
#define SOAP_TYPE_Calc_SOAP_ENV__Detail (27)
/* SOAP-ENV:Detail complex type: */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below)
	   WARNING: do not create a cyclic data structure graph throught this element unless SOAP encoding or SOAP_XML_GRAPH are used for id-ref serialization */
	void *fault;	/* transient (not serialized) */
public:
	int soap_type() const { return 27; } /* = unique type id SOAP_TYPE_Calc_SOAP_ENV__Detail */
	         SOAP_ENV__Detail();
	virtual ~SOAP_ENV__Detail() { }
};
#endif
#endif

/* calc.h:0 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_Calc_SOAP_ENV__Reason
#define SOAP_TYPE_Calc_SOAP_ENV__Reason (30)
/* SOAP-ENV:Reason complex type: */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of XSD type xsd:string */
public:
	int soap_type() const { return 30; } /* = unique type id SOAP_TYPE_Calc_SOAP_ENV__Reason */
	         SOAP_ENV__Reason();
	virtual ~SOAP_ENV__Reason() { }
};
#endif
#endif

/* calc.h:0 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_Calc_SOAP_ENV__Fault
#define SOAP_TYPE_Calc_SOAP_ENV__Fault (31)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of XSD type xsd:QName */
	char *faultstring;	/* optional element of XSD type xsd:string */
	char *faultactor;	/* optional element of XSD type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of XSD type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of XSD type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of XSD type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of XSD type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of XSD type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of XSD type SOAP-ENV:Detail */
public:
	int soap_type() const { return 31; } /* = unique type id SOAP_TYPE_Calc_SOAP_ENV__Fault */
	         SOAP_ENV__Fault();
	virtual ~SOAP_ENV__Fault() { }
};
#endif
#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/


/* calc.h:97 */
#ifndef SOAP_TYPE_Calc__QName
#define SOAP_TYPE_Calc__QName (5)
typedef char *_QName;
#endif

/* calc.h:97 */
#ifndef SOAP_TYPE_Calc__XML
#define SOAP_TYPE_Calc__XML (6)
typedef char *_XML;
#endif

/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


} // namespace Calc


#endif

/* End of CalcStub.h */
