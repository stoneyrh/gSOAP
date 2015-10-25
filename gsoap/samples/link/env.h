/*	env.h

	Defines SOAP-ENV Header and Fault global structures shared by client
	and service modules to process SOAP headers and faults when combining
	multiple client and/or services into one executable.

	Defines SOAP Fault and SOAP Header structures, which will be
	shared by client and service modules. The Header structure
	should contain all fields required by the clients and services.
	To obtain these, look into the wsdl2h-generated .h files for
	struct SOAP_ENV__Header and struct SOAP_ENV__Detail. Copy these below
	to make them globally visible to the gSOAP engine and plugins.

	Copyright (C) 2000-2003 Robert A. van Engelen, Genivia inc.
	All Rights Reserved.

	Compile:
	soapcpp2 -penv env.h
	c++ -c envC.cpp
	c++ -DWITH_NONAMESPACES -c stdsoap2.cpp
*/

#import "header.h"		// optional user-defined headers
#import "fault.h"		// optional user-defined fault details
