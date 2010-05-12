/*
	xml-rpc.h

	XML-RPC binding for C or C++
	See xml-rpc.cpp for example API calls

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2001-2008, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
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
*/

#include "xml-rpc-iters.h"	// deferred to C++ compiler

/// for C++ only: external iterator class for structs
extern class _struct_iterator;

/// for C++ only: external iterator class for arrays
extern class _array_iterator;

/// for C++ only: external iterator class for parameters
extern class params_iterator;

/// Scalar <boolean> element

typedef char		_boolean;	///< boolean values are 0 (false) or 1 (true)

/// Scalar <double> element

typedef double		_double;	///< double floating point value

/// Scalar <i4> element

typedef int		_i4;		///< 32bit int value

/// Scalar <int> element

typedef int		_int;		///< 32bit int value

/// Scalar <string> element

typedef char*		_string;	///< string value

/// Scalar <dateTime.iso8601> element

typedef char*		_dateTime_DOTiso8601;	///< ISO8601 date and time formatted string

/// <base64> binary data element

struct _base64
{
// C++ function members, not available in C (when using stdsoap2 -c)
public:
  			_base64();
  			_base64(struct soap*);
  			_base64(struct soap*, int, unsigned char*);
  int			size() const;	///< byte size of data
  unsigned char*	ptr();		///< pointer to data
  void			size(int);	///< set byte size of data
  void			ptr(unsigned char*);///< set pointer to data

// serializable content
public:
  unsigned char*	__ptr;		///< pointer to raw binary data block
  int			__size;		///< size of raw binary data block
};

/// <struct> element

struct _struct
{
// C++ function members, not available in C (when using stdsoap2 -c)
public:
  typedef _struct_iterator iterator;
  			_struct();
  			_struct(struct soap*);
  			_struct(struct soap*, int);
  extern bool		empty() const;	///< true when struct is empty
  int			size() const;	///< number of accessors in struct
  struct value&		operator[](const char*);///< struct accessor index
  _struct_iterator	begin();	///< struct accessor iterator begin
  _struct_iterator	end();		///< struct accessor iterator end

// serializable content
public:
  int			__size;		///< number of members
  struct member*	member;		///< pointer to member array
  struct soap*		soap;		///< ref to soap struct that manages this type
};

/// <data> element

struct data
{
// serializable content
public:
  int			__size;		///< number of array elements
  struct value*		value;		///< pointer to array elements
};

/// <array> element

struct _array
{
// C++ function members, not available in C (when using stdsoap2 -c)
public:
  typedef _array_iterator iterator;
  			_array();
  			_array(struct soap*);
  			_array(struct soap*, int);
  extern bool		empty() const;	///< true when array is empty
  int			size() const;	///< number of array elements
  struct value&		operator[](int);///< array index
  _array_iterator	begin();	///< array iterator begin
  _array_iterator	end();		///< array iterator end
 
// serializable content
public:
  struct data		data;		///< data with values
  struct soap*		soap;		///< ref to soap struct that manages this type
};

/// <value>

/**
The value element contains either string data stored in __any or an other type
of data stored in a subelement. In case of a subelement, the __type member
indicates the type of data pointed to by the ref member. For example, when
__type = SOAP_TYPE__int then *(int*)ref is an integer and when __type =
SOAP_TYPE__string (char*)ref is a string.
*/
struct value
{
// C++ function members, not available in C (when using stdsoap2 -c)
public:
			value();
			value(struct soap*);
			value(struct soap*, struct _array&);
			value(struct soap*, struct _base64&);
			value(struct soap*, bool);
			value(struct soap*, char*);
			value(struct soap*, double);
			value(struct soap*, int);
			value(struct soap*, time_t);
			value(struct soap*, struct _struct&);
			operator struct _array&();
			operator const struct _array&() const;
			operator struct _base64&();
			operator const struct _base64&() const;
			operator char*();
			operator const char*() const;
			operator double() const;
			operator int() const;
			operator time_t() const;
			operator struct _struct&();
			operator const struct _struct&() const;
  struct value&		operator[](int);
  struct value&		operator[](const char*);
  struct _array&	operator=(struct _array&);
  struct _base64&	operator=(struct _base64&);
  extern bool		operator=(bool);
  char*			operator=(char*);
  double		operator=(double);
  int			operator=(int);
  time_t		operator=(time_t);
  struct _struct&	operator=(struct _struct&);
  extern bool		is_array() const;	///< true if value is array type
  extern bool		is_base64() const;	///< true if value is base64 type
  extern bool		is_bool() const;	///< true if value is boolean type
  extern bool		is_double() const;	///< true if value is double type
  extern bool		is_false() const;	///< true if value is boolean false
  extern bool		is_int() const;		///< true if value is int type
  extern bool		is_string() const;	///< true if value is string type
  extern bool		is_struct() const;	///< true if value is struct type
  extern bool		is_true() const;	///< true if value is boolean true
  extern bool		is_dateTime() const;	///< true if value is dateTime
 
// serializable content
public:
  int			__type 0;	///< optional SOAP_TYPE_X, where X is a type name
  void*			ref;		///< ref to data
  char*			__any;		///< <value> string content, when present
  struct soap*		soap;		///< ref to soap struct that manages this type
};

/// <member>

struct member
{ 
// serializable content
public:
  char*			name;		///< struct accessor name
  struct value		value;		///< struct accessor value
};

/// <params>

struct params
{
// C++ function members, not available in C (when using stdsoap2 -c)
public:
  typedef params_iterator iterator;
  			params();
  			params(struct soap*);
  			params(struct soap*, int);
  extern bool		empty() const;	///< true if no parameters
  int			size() const;	///< number of parameters
  struct value&		operator[](int);///< parameter index
  params_iterator	begin();	///< struct accessor iterator begin
  params_iterator	end();		///< struct accessor iterator end

// serializable content
public:
  int			__size;		///< number of parameters
  struct param*		param;		///< pointer to array of parameters
  struct soap*		soap;		///< ref to soap struct that manages this type
};

/// <param>

struct param
{
// serializable content
public:
  struct value		value;		///< parameter value
  struct soap*		soap;		///< ref to soap struct that manages this type
};

/// <methodResponse>
 
struct methodResponse
{
// C++ function members, not available in C (when using stdsoap2 -c)
public:
  			methodResponse();
  			methodResponse(struct soap*);
  struct value&		operator[](int);///< response parameter accessor index
  struct value&		get_fault(void);///< get fault, if set
  struct value&		set_fault(const char*);///< set fault
  struct value&		set_fault(struct value&);///< set fault
  int			recv();		///< receive response
  int			send();		///< send response

// serializable content
public:
  struct params*	params;		///< response parameters
  struct fault*		fault;		///< response fault
  struct soap*		soap;		///< ref to soap struct that manages this type
};
  
/// <methodCall>

struct methodCall
{
// private state info
private:
  char*			methodEndpoint;	///< XML-RPC endpoint
  struct methodResponse*methodResponse; ///< holds the response after the call

// C++ function members, not available in C (when using stdsoap2 -c)
public:
  			methodCall();
  			methodCall(struct soap*);
  			methodCall(struct soap*, const char *endpoint, const char *methodname);
			///< instantiate with endpoint and method name
  struct value&		operator[](int);///< method parameter accessor index
  struct params&	operator()();	///< method invocation
  struct params&	operator()(const struct params&);
  			///< method invocation with param list
  struct params&	response();	///< get last response
  struct value&		fault();	///< fault value of response
  const char*		name() const;	///< get method name
  int			error() const;	///< gSOAP error code
  int			recv();		///< receive call
  int			send();		///< send call

// serializable content
public:
  char*			methodName;	///< name of the method
  struct params		params;		///< method request parameters
  struct soap*		soap;		///< ref to soap struct that manages this type
};

/// <fault>

struct fault
{
// serializable content
public:
  struct value		value;		///< value of the fault
};
