
XML-RPC Support
===============

XML-RPC is a simple and effective messaging protocol. XML-RPC uses a generic
XML format to compose messages. XML serialization proceeds by marshaling
parameters in predefined XML elements. A simple type system is provided to
cover primitive types, structs, and arrays. That is, XML-RPC defines a couple
of frequently used XML types with common programming language equivalents.
XML-RPC does NOT provide a data binding to XML and does NOT implement a
validation mechanism to ensure that XML content is valid.

See http://www.xmlrpc.com for more details.

C++ API
-------

Programming XML-RPC in C++ with gSOAP is made easy with method overloading.

The following source files are provided for XML-RPC support in C++:

xml-rpc.h            XML-RPC bindings (gSOAP specification file for soapcpp2)
xml-rpc.cpp          XML-RPC API
xml-rpc-io.h         C++ I/O support API for XML-RPC messages
xml-rpc-io.cpp       C++ I/O support API for XML-RPC messages
xml-rpc-iters.cpp    C++ iterators for structs, arrays, and parameters

Examples
--------

Two examples are provided, both using a C and C++ interface:

xml-rpc-currentTime.c		client in C
xml-rpc-currentTime.cpp		client in C++
xml-rpc-currentTimeServer.cpp	server in C++
xml-rpc-weblogs.c		client in C
xml-rpc-weblogs.cpp		client in C++

See xml-rpc.h for the C++ member functions to create XML-RPC messages and
decode responses.

A typical calling sequence is:

// create an allocation context
soap *ctx = soap_new();
// create a call object
methodCall mycallobj(ctx, "endpoint URL", "methodXMLTagName");
// create parameter list
params input(ctx);
// populate parameters
input[0] = 123;
input[1] = "abc";
_struct record(ctx);
record["name"] = "joe";
record["age"] = 23;
input[2] = record;
_array items(ctx);
items[0] = 456.789;
items[1] = "widget";
input[3] = items;
...
// get array of parameters
params output = mycallobj(input);
// check result
if (mycallobj.error())
  soap_print_fault(ctx, stderr);
else if (output.empty())
  printf("No response data\n");
else if (output.size() > 1)
  printf("More than one response data\n");
else if (output[0].is_array() && !((_array)output[0]).empty())
  for (int i = 0; i < ((_array)output[0]).size())
    ... = output[0][i];
else if (output[0].is_struct())
{ ... = output[0]["membername1"];
  ... = output[0]["membername2"];
}
else if (output[0].is_base64())
  _base64 raw = output[0];
else if (output[0].is_bool())
  bool flag = output[0];
else if (output[0].is_int())
  int num = output[0];
else if (output[0].is_double())
  double num = output[0];
else if (output[0].is_string())
  const char *str = output[0];
else if (output[0].is_dateTime())
  time_t t = output[0];
// deallocate all
soap_destroy(ctx);
soap_end(ctx);
soap_free(ctx);

A typical server sequence is:

// create an allocation context
soap *ctx = soap_new();
// create a method object
methodCall myobj(ctx);
// parse it from stdin, fd, or current socket
if (myobj.recv() != SOAP_OK)
  soap_print_fault(ctx, stderr);
else
{
  // create response
  methodResponse myresponse(ctx);
  // check method name
  if (!strcmp(myobj.name(), "methodXMLTagName"))
  { // method name matches: populate response parameters with values:
    myresponse[0] = ...;
    myresponse[1] = ...;
    ...
  }
  else
  { // otherwise, set fault
    myresponse.set_fault("Wrong method");
  }
  // send response
  if (myresponse.send() != SOAP_OK)
    soap_print_fault(ctx, stderr);
}
// close (but keep-alive setting keeps socket open)
soap_closesock(ctx);
// clean up
soap_destroy(ctx);
soap_end(ctx);
// free context (but we can reuse it to serve next call)
soap_free(ctx);

The server code above runs over CGI. Use the soap_bind() and soap_accept()
calls to bind the server to a port and accept requests via socket, see doc and
examples for these calls (e.g. samples/webserver.c).

C API
-----

For C code, only the xml-rpc.h file is needed. To generate the XML-RPC bindings
in C, use:

soapcpp2 -c xml-rpc.h

As a consequence, all message manipulation is done at a very low-level.

An XML RPC call is made using the following function you can defined for
convenience::

int methodCall(struct soap *soap, const char *URL, struct methodCall *m, struct methodResponse *r)
{ /* no namespaces */
  soap->namespaces = NULL;
  /* no SOAP encodingStyle */
  soap->encodingStyle = NULL;
  /* connect, send request, and receive response */
  if (soap_connect(soap, URL, NULL)
   || soap_begin_send(soap)
   || soap_put_methodCall(soap, m, "methodCall", NULL)
   || soap_end_send(soap)
   || soap_begin_recv(soap)
   || !soap_get_methodResponse(soap, r, "methodResponse", NULL)
   || soap_end_recv(soap))
    return soap_closesock(soap); /* closes socket and returns soap->error */
  soap_closesock(soap);
  return SOAP_OK;
}

Use this XML RPC method caller in C as follows:

  struct soap *soap = soap_new();
  struct methodCall m;
  struct methodResponse r;
  struct param p[4];  /* method has four parameters to send */
  int n;              /* an int */
  double x;           /* a float */
  struct _struct s;   /* a struct ... */
  struct member f[2]; /* ... with 2 members */
  struct _array a;    /* an array ... */
  struct value v[2];  /* ... with 2 values */
  _boolean False = 0, True = 1;
  /* Set up method call */
  m.methodName = "methodXMLTagName";
  /* set the four parameters */
  m.params.__size = 4;
  m.params.param = p;
  memset(p, 0, sizeof(p));
  p[0].value.__type = SOAP_TYPE__string;
  p[0].value.ref = "a string parameter";
  p[1].value.__type = SOAP_TYPE__int;
  p[1].value.ref = &n;
  n = 123;
  p[2].value.__type = SOAP_TYPE__double;
  p[2].value.ref = &x;
  x = 4.56;
  p[3].value.__type = SOAP_TYPE__struct;
  p[3].value.ref = &s;
  memset(&s, 0, sizeof(s));
  s.__size = 2;
  s.member = f;
  memset(f, 0, sizeof(f));
  f[0].name = "memberName1";
  f[0].value.__type = SOAP_TYPE__boolean;
  f[0].value.ref = &True;
  f[1].name = "memberName2";
  f[0].value.__type = SOAP_TYPE__array;
  f[0].value.ref = &a;
  memset(&a, 0, sizeof(a));
  a.data.__size = 2;
  a.data.value = v;
  memset(v, 0, sizeof(v));
  v[0].__type = SOAP_TYPE__string;
  v[0].ref = "hello";
  v[1].__type = SOAP_TYPE__string;
  v[1].ref = "world";
  /* connect, send request, and receive response */
  if (methodCall(soap, "http://domain/path/service", &m, &r))
  { soap_print_fault(soap, stderr);
    exit(soap->error);
  }
  if (r.fault)
  { /* print fault on stdout */
    soap_begin_send(soap);
    soap_put_fault(soap, r.fault, "fault", NULL);
    soap_end_send(soap);
  }
  else
  { /* print response parameters */
    int i;
    for (i = 0; i < r.params->__size; i++)
    { printf("Return parameter %d = ", i+1);
      display(&r.params->param[i].value); /* SEE BELOW */
      printf("\n");
    }
  }

To dynamically allocate data for automatic deallocation by the gSOAP engine,
use (instead of for example struct value v[2]):

  struct value *v = soap_malloc(soap, 2 * sizeof(struct value));
  memset(v, 0, 2 * sizeof(struct value));
  ...
  soap_end(soap); /* deallocate all */

See xml-rpc-currentTime.c and xml-rpc-weblogs.c for example C code.

A convenient way to display XML RPC data can be implemented as follows:

void display(struct value *v)
{ int i;
  switch (v->__type)
  { case SOAP_TYPE__boolean:
      printf(*((char*)v->ref) ? "TRUE" : "FALSE");
      break;
    case SOAP_TYPE__double:
      printf("%g", *((double*)v->ref));
      break;
    case SOAP_TYPE__i4:
    case SOAP_TYPE__int:
      printf("%d", *((int*)v->ref));
      break;
    case SOAP_TYPE__dateTime_DOTiso8601:
      printf("%s", (char*)v->ref);
      break;
    case SOAP_TYPE__string:
      printf("\"%s\"", (char*)v->ref);
      break;
    case SOAP_TYPE__base64:
      printf("[%d bytes of raw data at %p]", ((struct _base64*)v->ref)->__size, ((struct _base64*)v->ref)->__ptr);
      break;
    case SOAP_TYPE__struct:
      printf("{struct\n");
      for (i = 0; i < ((struct _struct*)v->ref)->__size; i++)
      { printf("[%s]=", ((struct _struct*)v->ref)->member[i].name);
        display(&((struct _struct*)v->ref)->member[i].value);
        printf("\n");
      }
      printf("}\n");
      break;
    case SOAP_TYPE__array:
      printf("{array\n");
      for (i = 0; i < ((struct _array*)v->ref)->data.__size; i++)
      { printf("[%d]=", i);
        display(&((struct _array*)v->ref)->data.value[i]);
        printf("\n");
      }
      printf("}\n");
      break;
    default:
      if (!v->__type)
        printf("\"%s\"", v->__any);
      else
        printf("{?}");
  }
}

