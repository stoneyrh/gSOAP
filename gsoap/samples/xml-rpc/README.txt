
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
  ... = output[0][0];
else if (output[0].is_struct())
  ... = output[0]["membername"];
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

See xml-rpc-currentTime.c for example C code.

