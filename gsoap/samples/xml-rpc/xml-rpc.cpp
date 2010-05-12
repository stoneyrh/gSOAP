/*
	xml-rpc.cpp

	XML-RPC definitions for C++

	Note: 
	XML-RPC declarations are given in the gSOAP header file xml-rpc.h
	Iterators and iostream operators are declared in xml-rpc-iters.h

	Example calling sequence:

	// get XML-RPC serializers (link with soapC.cpp)
	#include "soapH.h"
	// get XML-RPC I/O operations (link with xml-rpc-io.cpp)
	#include "xml-rpc-io.h"

	// set up context (indent XML is optional)
	soap *ctx = soap_new1(SOAP_XML_INDENT);
	// define method call
	methodCall myMethod(ctx, "<endpoint-URL>", "<method-name>");
	// populate input parameters
	myMethod[0] = ...; // first param
	myMethod[1] = ...; // second param
	...
	// make the call and get the response parameters
	params result = myMethod();
	// error?
	if (myMethod.error())
	  soap_print_fault(ctx, stderr);
	else if (result.empty())
	  cout << myMethod.fault() << endl;
	else
	  for (params::iterator arg = result.begin(); arg != result.end(); ++arg)
	    cout << *arg << endl;
	// delete all
	soap_destroy(ctx);
	soap_end(ctx);
	soap_free(ctx);

	Compile with -DWITH_NONAMESPACES to omit global namespaces[] definition
	or add to your code:

	struct Namespace namespaces[] = { {NULL, NULL} };

        How to use XML-RPC data types?

        A value is stored in a 'struct value'. This struct has the following
        methods to query its content:
        bool is_array()
        bool is_base64()
        bool is_bool()
        bool is_double()
        bool is_false()
        bool is_int()
        bool is_string()
        bool is_struct()
        bool is_true()
        bool is_dateTime()

        To set a value:
        value v(soap); // the soap struct is used for memory management
        if (...)
          v[0] = 1; // assign 1 to first array element
        else if (...)
          v = new _base64(soap, 8, (unsigned char*)"raw data");
        else if (...)
          v = true; // boolean
        else if (...)
          v = 12.3; // double
        else if (...)
          v = 1234; // int
        else if (...)
          v = "xy"; // string
        else if (...)                                         
          v["name"] = "Abe"; // struct member 'name' = "Abe"
        else if (...)
          v = clock(); // dateTime

	To get a value:
	if (v.is_array())
	{ _array& a = v;
	  for (_array::iterator i = a.begin(); i != a.end(); ++i)
	    cout << (*i) << ", ";
	}
	else if (v.is_base64())
	{ _base64& b = v;
	  ... = b.size();
	  ... = b.ptr();
	}
	else if (v.is_bool())
	{ bool b = v.is_true();
	}
	else if (v.is_double())
	{ double n = v;
	}
	else if (v.is_int())
	{ int n = v;
	}
	else if (v.is_string())
	{ char *s = v;
	}
	else if (v.is_struct())
	{ _struct& s = v;
	  for (_struct::iterator i = s.begin(); i != s.end(); ++i)
	    cout << (*i) << ", ";
	}
	else if (v.is_dateTime())
	{ time_t = v;
	}

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

#include "soapH.h"

value::value()
{ }

value::value(struct soap *soap)
{ soap_default_value(soap, this);
}

value::value(struct soap *soap, struct _array &a)
{ soap_default_value(soap, this);
  *this = a;
}

value::value(struct soap *soap, _base64 &b)
{ soap_default_value(soap, this);
  *this = b;
}

value::value(struct soap *soap, bool b)
{ soap_default_value(soap, this);
  *this = b;
}

value::value(struct soap *soap, char *s)
{ soap_default_value(soap, this);
  *this = s;
}

value::value(struct soap *soap, double d)
{ soap_default_value(soap, this);
  *this = d;
}

value::value(struct soap *soap, int n)
{ soap_default_value(soap, this);
  *this = n;
}

value::value(struct soap *soap, time_t t)
{ soap_default_value(soap, this);
  *this = t;
}

value::value(struct soap *soap, struct _struct &r)
{ soap_default_value(soap, this);
  *this = r;
}

bool value::is_array() const
{ return __type == SOAP_TYPE__array;
}

bool value::is_base64() const
{ return __type == SOAP_TYPE__base64;
}

bool value::is_bool() const
{ return __type == SOAP_TYPE__boolean;
}

bool value::is_double() const
{ return __type == SOAP_TYPE__double;
}

bool value::is_false() const
{ return __type == SOAP_TYPE__boolean && (bool)*(_boolean*)ref == false;
}

bool value::is_int() const
{ return __type == SOAP_TYPE__int || __type == SOAP_TYPE__i4;
}

bool value::is_struct() const
{ return __type == SOAP_TYPE__struct;
}

bool value::is_string() const
{ return __type == SOAP_TYPE__string || (__any && *__any);
}

bool value::is_true() const
{ return __type == SOAP_TYPE__boolean && (bool)*(_boolean*)ref == true;
}

bool value::is_dateTime() const
{ return __type == SOAP_TYPE__dateTime_DOTiso8601;
}

value::operator struct _array&()
{ if (__type == SOAP_TYPE__array)
    return *(struct _array*)ref;
  return *soap_new__array(soap, -1);
}

value::operator const struct _array&() const
{ if (__type == SOAP_TYPE__array)
    return *(const struct _array*)ref;
  return *soap_new__array(soap, -1);
}

value::operator struct _base64&()
{ if (__type == SOAP_TYPE__base64)
    return *(struct _base64*)ref;
  return *soap_new__base64(soap, -1);
}

value::operator const struct _base64&() const
{ if (__type == SOAP_TYPE__base64)
    return *(const struct _base64*)ref;
  return *soap_new__base64(soap, -1);
}

value::operator char*()
{ if (__type == SOAP_TYPE__string || __type == SOAP_TYPE__dateTime_DOTiso8601)
    return (char*)ref;
  if (__any)
    return __any;
  return "";
}

value::operator const char*() const
{ if (__type == SOAP_TYPE__string || __type == SOAP_TYPE__dateTime_DOTiso8601)
    return (const char*)ref;
  if (__any)
    return __any;
  return "";
}

value::operator double() const
{ if (__type == SOAP_TYPE__double)
    return (double)*(_double*)ref;
  return 0.0;
}

value::operator int() const
{ if (__type == SOAP_TYPE__int)
    return (int)*(_int*)ref;
  if (__type == SOAP_TYPE__i4)
    return (int)*(_i4*)ref;
  return 0;
}

value::operator time_t() const
{ time_t t = 0;
  if (__type == SOAP_TYPE__dateTime_DOTiso8601)
    soap_s2dateTime(soap, (const char*)ref, &t);
  return t;
}

value::operator struct _struct&()
{ if (__type == SOAP_TYPE__struct)
    return *(struct _struct*)ref;
  return *soap_new__struct(soap, -1);
}

value::operator const struct _struct&() const
{ if (__type == SOAP_TYPE__struct)
    return *(const struct _struct*)ref;
  return *soap_new__struct(soap, -1);
}

struct value& value::operator[](int n)
{ return ((struct _array&)*this)[n];
}

struct value& value::operator[](const char *s)
{ return ((struct _struct&)*this)[s];
}

struct _array& value::operator=(struct _array& a)
{ __type = SOAP_TYPE__array;
  __any = NULL;
  ref = &a;
  return a;
}

_base64& value::operator=(_base64& b)
{ __type = SOAP_TYPE__base64;
  __any = NULL;
  ref = &b;
  return b;
}

bool value::operator=(bool b)
{ __type = SOAP_TYPE__boolean;
  __any = NULL;
  ref = soap_malloc(soap, sizeof(_boolean));
  *(_boolean*)ref = (_boolean)b;
  return b;
}

char* value::operator=(char *s)
{ __type = SOAP_TYPE__string;
  __any = NULL;
  ref = soap_strdup(soap, s);
  return s;
}

double value::operator=(double d)
{ __type = SOAP_TYPE__double;
  __any = NULL;
  ref = soap_malloc(soap, sizeof(_double));
  *(_double*)ref = (_double)d;
  return d;
}

int value::operator=(int n)
{ __type = SOAP_TYPE__int;
  __any = NULL;
  ref = soap_malloc(soap, sizeof(_int));
  *(_int*)ref = (_int)n;
  return n;
}

struct _struct& value::operator=(struct _struct& r)
{ __type = SOAP_TYPE__struct;
  __any = NULL;
  ref = &r;
  return r;
}

time_t value::operator=(time_t t)
{ __type = SOAP_TYPE__dateTime_DOTiso8601;
  __any = NULL;
  ref = soap_strdup(soap, soap_dateTime2s(soap, t));
  return t;
}

_struct::_struct()
{ }

_struct::_struct(struct soap *soap)
{ soap_default__struct(soap, this);
}

_struct::_struct(struct soap *soap, int len)
{ soap_default__struct(soap, this);
  __size = len;
  member = (struct member*)soap_malloc(soap, __size * sizeof(struct member));
  for (int i = 0; i < __size; i++)
    soap_default_member(soap, &member[i]);
}

bool _struct::empty() const
{ return __size == 0;
}

int _struct::size() const
{ return __size;
}

struct value& _struct::operator[](const char *s)
{ int i = 0;
  if (!member)
  { __size = 1;
    member = (struct member*)soap_malloc(soap, sizeof(struct member));
  }
  else
  { for (i = 0; i < __size; i++)
    { if (!strcmp(member[i].name, s))
        return member[i].value;
    }
    __size++;
    struct member *newmember = (struct member*)soap_malloc(soap, __size * sizeof(struct member));
    for (i = 0; i < __size - 1; i++)
      newmember[i] = member[i];
    soap_unlink(soap, member);
    free(member);
    member = newmember;
  }
  member[i].name = soap_strdup(soap, s);
  soap_default_value(soap, &member[i].value);
  return member[i].value;
}

_struct_iterator _struct::begin()
{ _struct_iterator iter(this);
  return iter;
}

_struct_iterator _struct::end()
{ _struct_iterator iter(this);
  iter += __size;
  return iter;
}

_array::_array()
{ }

_array::_array(struct soap *soap)
{ soap_default__array(soap, this);
}

_array::_array(struct soap *soap, int len)
{ soap_default__array(soap, this);
  data.__size = len;
  data.value = (struct value*)soap_malloc(soap, data.__size * sizeof(struct value));
  for (int i = 0; i < data.__size; i++)
    soap_default_value(soap, &data.value[i]);
}

bool _array::empty() const
{ return data.__size == 0;
}

int _array::size() const
{ return data.__size;
}

struct value& _array::operator[](int n)
{ if (!data.value)
  { data.__size = n + 1;
    data.value = (struct value*)soap_malloc(soap, data.__size * sizeof(struct value));
    for (int i = 0; i < data.__size; i++)
      soap_default_value(soap, &data.value[i]);
  }
  else if (data.__size <= n)
  { int oldsize = data.__size;
    data.__size = n + 1;
    struct value *newvalue = (struct value*)soap_malloc(soap, data.__size * sizeof(struct value));
    int i;
    for (i = 0; i < oldsize; i++)
      newvalue[i] = data.value[i];
    for (; i < data.__size; i++)
      soap_default_value(soap, &newvalue[i]);
    soap_unlink(soap, data.value);
    free(data.value);
    data.value = newvalue;
  }
  return data.value[n];
}

_array_iterator _array::begin()
{ _array_iterator iter(this);
  return iter;
}

_array_iterator _array::end()
{ _array_iterator iter(this);
  iter += data.__size;
  return iter;
}

_base64::_base64()
{ }

_base64::_base64(struct soap *soap)
{ soap_default__base64(soap, this);
}

_base64::_base64(struct soap *soap, int n, unsigned char *p)
{ soap_default__base64(soap, this);
  __size = n;
  __ptr = p;
}

int _base64::size() const
{ return __size;
}

unsigned char* _base64::ptr()
{ return __ptr;
}

void _base64::size(int n)
{ __size = n;
}

void _base64::ptr(unsigned char *p)
{ __ptr = p;
}

params::params()
{ }

params::params(struct soap *soap)
{ soap_default_params(soap, this);
}

params::params(struct soap *soap, int len)
{ soap_default_params(soap, this);
  __size = len;
  param = (struct param*)soap_malloc(soap, __size * sizeof(struct param));
  for (int i = 0; i < __size; i++)
    soap_default_param(soap, &param[i]);
}

bool params::empty() const
{ return __size == 0;
}

int params::size() const
{ return __size;
}

struct value& params::operator[](int n)
{ if (!param)
  { __size = n + 1;
    param = (struct param*)soap_malloc(soap, __size * sizeof(struct param));
    for (int i = 0; i < __size; i++)
      soap_default_param(soap, &param[i]);
  }
  else if (__size <= n)
  { int oldsize = __size;
    __size = n + 1;
    struct param *newparam = (struct param*)soap_malloc(soap, __size * sizeof(struct param));
    int i;
    for (i = 0; i < oldsize; i++)
      newparam[i] = param[i];
    for (; i < __size; i++)
      soap_default_param(soap, &newparam[i]);
    soap_unlink(soap, param);
    free(param);
    param = newparam;
  }
  return param[n].value;
}

params_iterator params::begin()
{ params_iterator iter(this);
  return iter;
}

params_iterator params::end()
{ params_iterator iter(this);
  iter += __size;
  return iter;
}

methodCall::methodCall()
{ }

methodCall::methodCall(struct soap *soap)
{ soap_default_methodCall(soap, this);
}

methodCall::methodCall(struct soap *soap, const char *endpoint, const char *name)
{ soap_default_methodCall(soap, this);
  methodName = soap_strdup(soap, name);
  methodEndpoint = soap_strdup(soap, endpoint);
  methodResponse = NULL;
}

struct value& methodCall::operator[](int n)
{ return params[n];
}

struct params& methodCall::operator()()
{ if (send() == SOAP_OK)
  { if (!methodResponse)
      methodResponse = soap_new_methodResponse(soap, -1);
    if (methodResponse->recv() != SOAP_OK)
      methodResponse = NULL;
    soap_closesock(soap);
  }
  else
    methodResponse = NULL;
  if (methodResponse && methodResponse->params)
    return *methodResponse->params;
  return *soap_new_params(soap, -1);
}

struct params& methodCall::operator()(const struct params& args)
{ /* parameters */
  params = args;
  /* invoke */
  return (*this)();
}

struct params& methodCall::response()
{ if (!methodResponse)
    methodResponse = soap_new_methodResponse(soap, -1);
  if (!methodResponse->params)
    methodResponse->params = soap_new_params(soap, -1);
  return *methodResponse->params;
}

struct value& methodCall::fault()
{ if (methodResponse)
    return methodResponse->get_fault();
  return *soap_new_value(soap, -1);
}

const char* methodCall::name() const
{ if (methodName)
    return methodName;
  return "";
}

int methodCall::error() const
{ return soap->error;
}

int methodCall::send()
{ /* no namespaces */
  soap->namespaces = NULL;
  /* no SOAP encodingStyle */
  soap->encodingStyle = NULL;
  /* content length */
  soap_begin_count(soap);
  if (soap->mode & SOAP_IO_LENGTH)
    soap_put_methodCall(soap, this, "methodCall", NULL);
  soap_end_count(soap);
  /* connect and send request */
  if (soap_connect(soap, methodEndpoint, NULL)
   || soap_put_methodCall(soap, this, "methodCall", NULL)
   || soap_end_send(soap))
    return soap->error;
  return SOAP_OK;
}

int methodCall::recv()
{ if (soap_begin_recv(soap)
   || !soap_get_methodCall(soap, this, "methodCall", NULL)
   || soap_end_recv(soap))
    return soap->error;
  return SOAP_OK;
}

methodResponse::methodResponse()
{ }

methodResponse::methodResponse(struct soap *soap)
{ soap_default_methodResponse(soap, this);
}

struct value& methodResponse::operator[](int n)
{ if (!params)
    params = soap_new_params(soap, -1);
  return (*params)[n];
}

struct value& methodResponse::get_fault()
{ if (!fault)
    fault = soap_new_fault(soap, -1);
  return fault->value;
}

struct value& methodResponse::set_fault(const char* s)
{ struct value* v = soap_new_value(soap, -1);
  *v = s;
  return get_fault() = *v;
}

struct value& methodResponse::set_fault(struct value& v)
{ return get_fault() = v;
}

int methodResponse::send()
{ /* no namespaces */
  soap->namespaces = NULL;
  /* no SOAP encodingStyle */
  soap->encodingStyle = NULL;
  /* content length */
  soap_begin_count(soap);
  if (soap->mode & SOAP_IO_LENGTH)
    soap_put_methodResponse(soap, this, "methodResponse", NULL);
  soap_end_count(soap);
  /* send response */
  if (soap_response(soap, SOAP_OK)
   || soap_put_methodResponse(soap, this, "methodResponse", NULL)
   || soap_end_send(soap))
    return soap->error;
  return SOAP_OK;
}

int methodResponse::recv()
{ if (soap_begin_recv(soap)
   || !soap_get_methodResponse(soap, this, "methodResponse", NULL)
   || soap_end_recv(soap))
    return soap->error;
  return SOAP_OK;
}

_array_iterator::_array_iterator()
{ value = start = NULL;
}

_array_iterator::_array_iterator(const struct _array* a)
{ value = start = a->data.value;
}

bool _array_iterator::operator==(const _array_iterator& that) const
{ return this->value == that.value;
}

bool _array_iterator::operator!=(const _array_iterator& that) const
{ return this->value != that.value;
}

int _array_iterator::index() const
{ return value - start;
}

struct value& _array_iterator::operator*() const
{ return *value;
}

_array_iterator& _array_iterator::operator++()
{ value++;
  return *this;
}

_array_iterator& _array_iterator::operator+=(int step)
{ value += step;
  return *this;
}

_struct_iterator::_struct_iterator()
{ member = NULL;
}

_struct_iterator::_struct_iterator(const struct _struct* s)
{ member = s->member;
}

bool _struct_iterator::operator==(const _struct_iterator& that) const
{ return this->member == that.member;
}

bool _struct_iterator::operator!=(const _struct_iterator& that) const
{ return this->member != that.member;
}

const char* _struct_iterator::index() const
{ return member->name;
}

struct value& _struct_iterator::operator*() const
{ return member->value;
}

_struct_iterator& _struct_iterator::operator++()
{ member++;
  return *this;
}

_struct_iterator& _struct_iterator::operator+=(int step)
{ member += step;
  return *this;
}

params_iterator::params_iterator()
{ start = param = NULL;
}

params_iterator::params_iterator(const struct params* s)
{ start = param = s->param;
}

bool params_iterator::operator==(const params_iterator& that) const
{ return this->param == that.param;
}

bool params_iterator::operator!=(const params_iterator& that) const
{ return this->param != that.param;
}

int params_iterator::index() const
{ return param - start;
}

struct value& params_iterator::operator*() const
{ return param->value;
}

params_iterator& params_iterator::operator++()
{ param++;
  return *this;
}

params_iterator& params_iterator::operator+=(int step)
{ param += step;
  return *this;
}
