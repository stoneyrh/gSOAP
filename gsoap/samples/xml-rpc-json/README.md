
XML-RPC and JSON                                                     {#mainpage}
================

[TOC]

XML-RPC is a simple and effective messaging protocol. XML-RPC uses a generic
XML format to compose XML messages for platform-neutral data interchange.
XML-RPC serialization proceeds by marshaling parameters in predefined XML
elements. A simple type system is provided to cover primitive types, structs,
and arrays. That is, XML-RPC defines a collection of frequently used XML types
with common programming language equivalents. XML-RPC does NOT provide a data
binding to XML and does NOT support a validation mechanism to ensure that data
content is validated against a data type or schema.

See <http://www.xmlrpc.com> for more details.

JSON (JavaScript Object Notation) is an even simpler data format to support
platform-neutral data interchange that is highly compatible across programming
languages.

See <http://www.json.org> for more details.


C++ XML-RPC and JSON                                                      {#cpp}
====================

XML-RPC and JSON data is largely interchangeable in this implementation. That
is, XML-RPC data can be converted to/from JSON data by simply choosing the
XML-RPC or the JSON serializer. Data is interchangeable with the exception of
XML-RPC dateTime and XML-RPC base64-encoded data that have no JSON equivalents.
Also, JSON only supports floats. Ints are converted to double floats by the
JSON serializer. Developers should be aware of these limitations as a JSON
receiver will never receive an int value, dateTime, and base64 raw data. This
implementation sends ints as floats and dateTime and base64 data as string
type content in JSON.

The following source files are provided for XML-RPC support in C++:

- `xml-rpc.cpp`:	C++ XML-RPC implementation and data management
- `xml-rpc-io.h`:	C++ XML-RPC data serialization over streams
- `xml-rpc-io.cpp`:	C++ XML-RPC data serialization over streams
- `xml-rpc-iters.h`:	C++ iterators for structs, arrays, and parameters
- `xml-rpc.h`:		XML-RPC binding as a gSOAP .h file for soapcpp2
			(do not #include this file in your project builds)

For JSON serialization in C++, use the following files:

- `json.h`:		C++ JSON serializer over streams
- `json.cpp`:		C++ JSON serializer over streams

For JSON-RPC over HTTP (JSON REST method), please use the `plugin/httppost.c`
plugin. See [JSON-RPC over HTTP](#cpp-jr) explanation below.

Auto-generated files: note that `soapH.h`, `soapStub.h` and `soapC.cpp` are
required for XML-RPC and JSON. To auto-generate these C++ files, execute:

    soapcpp2 -CSL xml-rpc.h

Then compile and link these files together with `stdsoap2.cpp` (or link with
`libgsoap++.a` installed by the gSOAP package).


C++ Examples                                                           {#cpp-ex}
------------

Examples are provided in the software package:

- `xml-rpc-currentTime.cpp`:		XML-RPC client in C++, also uses JSON
- `xml-rpc-currentTimeServer.cpp`:	XML-RPC server in C++
- `xml-rpc-weblogs.cpp`:		XML-RPC client in C++
- `xml-rpc-json.cpp`:			XML-RPC to/from JSON example
- `json-currentTime.cpp`:		JSON client in C++
- `json-currentTimeServer.cpp`:		JSON server in C++

See `xml-rpc.h` for the C++ member functions to create XML-RPC messages and
decode responses. These functions provide intuitive type casts, assignments,
and indexing operations.

An XML-RPC data value is created in C++ as follows, which requires a context
`ctx` for the engine state (the soap struct) for communication, and managed
data allocation/deallocation:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING);
    value v(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Unicode can be stored in UTF8-formattted strings. For compatibility with XML-RPC
serialization of UTF8-encoded strings, use the `SOAP_C_UTFSTRING` flag.

The code shown above creates an empty value `v`. It can be set by any one of
the following assignments:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    v = 12345;			// an int
    v = 12.34;			// a double float
    v = "abc";			// a string
    v = string("abc");		// a std::string
    v = L"xyz";			// a wide string (converted to UTF8)
    v = wstring(L"xyz");	// a std::wstring (converted to UTF8)
    v = false;			// a Boolean
    v = time(0);		// a time_t value serialized as XML-RPC dateTime
    v[0] = 24;			// an array of [24, 99.99, "abc"]
    v[1] = 99.99;
    v[2] = "abc";
    v["name"] = "john";		// a struct {"name": "john", "age": 24}
    v["age"] = 24;
    _base64 img(ctx, 100, ptr_to_rawimage100bytes);
    v = img;			// a data block of 100 bytes in base64
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can combine this syntax to create arrays of arrays, arrays of structs, and
so on, for example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    v[0]["name"] = "bob";
    v[0]["toys"][0] = "ball";
    v[0]["toys"][1] = "furby";
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

which creates a singleton array containing a struct with two members `name` set
to `"bob"` and `toys` set to an array of `"ball"` and `"furby"`. In JSON format
this would be represented by:

    [{"name": "bob", "toys": ["ball", "furby"]}]

To check the type of a value, use the `is_type` methods:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    bool value::is_int();
    bool value::is_double();
    bool value::is_string();
    bool value::is_bool();
    bool value::is_true();
    bool value::is_false();
    bool value::is_dateTime();
    bool value::is_array();
    bool value::is_struct();
    bool value::is_base64();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are three additional methods to invoke on a value:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    void value::size(int);	// (re)set array size or pre-allocate space
    int value::size();		// get array/struct size
    bool value::empty();	// empty array/struct
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To extract data we can use casts and array/struct indexing on a value `v` as
follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    (int)v
    (double)v
    (char*)v
    (string)v
    (wchar_t*)v			// assuming UTF8 XML/JSON
    (wstring)v			// assuming UTF8 XML/JSON
    (bool)v
    (time_t)v
    (_base64)v
    v[0]
    v["name"]
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To access base64 binary raw data of a value `v`, use:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    _base64& bin = v;
    unsigned char *raw = bin.ptr();
    int size = bin.size();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We can also use iterators to traverse a value `v` that is an array or a struct:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    if (v.is_array())
    {   _array& vec = v;
        for (_array::iterator i = vec.begin(); i != vec.end(); ++i)
        {   const char *member_name = i.index();
            value& member_value = *i;
            ... // use member_value
        }
    }
    else if (v.is_struct())
    {   _struct& rec = v;
        for (_struct::iterator i = rec.begin(); i != rec.end(); ++i)
        {   value& array_value = *i;
            ... // use array_value
        }
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Parameter lists are similar to arrays and its values are indexed. We can also
iterate over parameter content of XML-RPC remote methods:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    methodCall rpc(ctx, "endpoint URL", "methodName");
    params request(ctx, 2);
    request[0] = ...;		// first request parameter
    request[1] = ...;		// second request parameter
    params response = rpc(request);
    for (params::iterator i = response.begin(); i != response.end(); ++i)
    {   value& param_value = *i;
        ... // use param_value of response params
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are two additional methods to invoke on parameters:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    int params::size();		// get number of parameters
    bool params::empty();	// true if no parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

All dynamically allocated memory that is internally used to store data is
deallocated with:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    soap_destroy(ctx);	// delete objects
    soap_end(ctx);	// deallocate temporary data
    soap_free(ctx);	// deallocate the context allocated with soap_new()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


C++ XML-RPC Client Example                                             {#cpp-cl}
--------------------------

A typical XML-RPC calling sequence in C++ is:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h" // generated by the command: soapcpp2 -CSL xml-rpc.h
    struct Namespace namespaces[] = { {NULL, NULL} }; // no XML namespaces

    // create an allocation context
    soap *ctx = soap_new1(SOAP_C_UTFSTRING); // Store Unicode in UTF8 format
    // create a call object
    methodCall rpc(ctx, "endpoint URL", "methodName");
    // create parameter list with 5 values
    params request(ctx, 5);
    // populate parameters
    request[0] = 123;           // first parameter is an integer
    request[1] = "abc";         // second is a string
    request[2]["name"] = "joe"; // a record, first member "name"
    request[2]["age"] = 23;     // a record, second member "age"
    request[3][0] = 456.789;    // an array, first element (a float)
    request[3][1] = "widget";   // an array, second element (a string)
    request[3][2] = true;       // an array, third element (a bool)
    value record(ctx);          // another struct
    record["foo"] = 1;
    record["bar"] = 2;
    request[4] = record;        // assign record to parameter
    // get list of parameters by making the XML-RPC call
    params response = rpc(request);
    // check result
    if (rpc.error())
        soap_print_fault(ctx, stderr);
    else if (response.empty())
        printf("No response data\n");
    else if (response.size() > 1)
        printf("More than one response data\n");
    else if (response[0].is_array() && !response[0].empty())
        for (int i = 0; i < response[0].size())
            ... = response[0][i];
    else if (response[0].is_struct())
    {   ... = response[0]["membername1"];
        ... = response[0]["membername2"];
    }
    else if (response[0].is_base64())
    {   _base64 raw& = response[0];
        unsigned char *raw = bin.ptr();
        int size = bin.size();
	... // use raw[0..size-1] data
    }
    else if (response[0].is_bool())
    {   bool flag = response[0];
        ... // use boolean flag
    }
    else if (response[0].is_int())
    {   int num = response[0];
        ... // use integer
    }
    else if (response[0].is_double())
    {   double num = response[0];
        ... // use double float
    }
    else if (response[0].is_string())
    {   const char *str = response[0];
        // use string, note that also legal is:
	const std::string& st = response[0];
        // and conversion from UTF8 to wide string unicode:
	const wchar_t *w = response[0];
	const std::string& ws = response[0];
    }
    else if (response[0].is_dateTime())
    {   time_t t = response[0];
        ... // use time
    }
    // deallocate all
    soap_destroy(ctx);
    soap_end(ctx);
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Alternatively when desired, the parameters of the methodCall object can be
directly populated as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    methodCall rpc(ctx, "endpoint URL", "methodName");
    // populate parameters
    rpc[0] = 123;           // first parameter is an integer
    rpc[1] = "abc";         // second is a string
    rpc[2]["name"] = "joe"; // a record, first member "name"
    rpc[2]["age"] = 23;     // a record, second member "age"
    rpc[3][0] = 456.789;    // an array, first element (a float)
    rpc[3][1] = "widget";   // an array, second element (a string)
    rpc[3][2] = true;       // an array, third element (a bool)
    rpc[4]["foo"] = 1;
    rpc[4]["bar"] = 2;
    // get list of parameters by making the XML-RPC call
    params response = rpc();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note that in the client code, after the response is retrieved, the implicit
type casts done by assignments extract the values. These casts can be used
anywhere to extract values:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    params response = rpc();
    double sum = 0.0;
    for (int i = 0; i < response.size(); i++)
        if (response[i].is_double())	// is this parameter a double float?
            sum += (double)response[i];
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Type casts can also be used to convert data, which means they never produce an
exception. Casting to string `(const char*)` converts atomic values and base64
data to strings, but does not convert compound types such as arrays and
structs.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    params response = rpc();
    for (int i = 0; i < response.size(); i++)
        printf("response[%d] = %s\n", i, (const char*)response[i]);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

which prints a string representation of the int, double, boolean, time, or
base64 values of parameters. An empty string is printed for arrays and structs.
Use iterators to walk over arrays and structs to print values. Or use the
JSON module to print values in JSON format, see further on JSON below.


C++ XML-RPC Server Example                                             {#cpp-sr}
--------------------------

A typical C++ XML-RPC server sequence is:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // create an allocation context
    soap *ctx = soap_new1(SOAP_C_UTFSTRING);
    // create a method object
    methodCall rpc(ctx);
    // option 1: parse and write to/from stdin/out
    // (no code needed)
    // option 2: parse and write to/from FILE
    // ctx->recvfd = ...; // set input FD
    // ctx->sendfd = ...; // set output FD
    // option 3: parse and write to/from IO streams
    // ctx->is = ...; // set input stream
    // ctx->os = ...; // set output stream
    if (rpc.recv() != SOAP_OK)
        soap_print_fault(ctx, stderr);
    else
    {   // create response
        methodResponse response(ctx);
        // check method name
        if (!strcmp(rpc.name(), "methodName"))
        {   // method name matches: populate response parameters with values:
            response[0] = ...;
            response[1] = ...;
            ... // add response data 
        }
        else
        {   // otherwise, set fault
            response.set_fault("Wrong method");
        }
        // send response
        if (response.send() != SOAP_OK)
            soap_print_fault(ctx, stderr);
    }
    // close (but keep-alive setting keeps socket open)
    soap_closesock(ctx);
    // clean up
    soap_destroy(ctx);
    soap_end(ctx);
    // free context (but we can reuse it to serve next call)
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

With option 1 the server code above uses standard in/out and thus runs over
CGI. Other possibilities are given by options 2 and 3.

To serve requests at a port, we use the `soap_bind()` and `soap_accept()` calls
to bind the server to a port and accept requests via socket, see also the docs
and examples for these calls (e.g. samples/webserver.c):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // create an allocation context
    soap *ctx = soap_new1(SOAP_IO_KEEPALIVE | SOAP_C_UTFSTRING);
    // bind to port 8080
    if (!soap_valid_socket(soap_bind(ctx, NULL, 8080, 100)))
        ... // error, stop
    // accept messages in server loop
    for (;;)
    {   if (!soap_valid_socket(soap_accept(ctx)))
            ... // error, stop
        // create a method object
        methodCall rpc(ctx);
        // parse it from socket
        if (rpc.recv() != SOAP_OK)
            soap_print_fault(ctx, stderr);
        ... // process request, produce result to send as shown above
        // close (but keep-alive setting keeps socket open)
        soap_closesock(ctx);
        // clean up
        soap_destroy(ctx);
        soap_end(ctx);
    }
    // free context
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


C++ XML-RPC Data Serialization from/to Streams                         {#cpp-io}
----------------------------------------------

To send and receive XML over streams, use `xml-rpc-io.h` and `xml-rpc-io.cpp`.
For example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "xml-rpc-io.h" // also compile and link xml-rpc-io.cpp

    std::cout << response[0] << std::endl;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

which will display the data in XML-RPC format. To parse XML-RPC data from a
stream, use:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "xml-rpc-io.h" // also compile and link xml-rpc-io.cpp

    value v(ctx);
    std::cin >> v;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


C++ JSON Serialization from/to Streams                                 {#cpp-js}
--------------------------------------

To display values in JSON format or to parse JSON data, use the json.h and
json.cpp JSON serializers in combination with xml-rpc.cpp and the
auto-generated soapH.h and soapC.cpp. It is also possible to send and receive
JSON data over HTTP as JSON-RPC operations, but this requires some more coding
(see [JSON-RPC over HTTP](#cpp-jr) below).

Because the internal data is the same for XML-RPC and JSON, You can dump data
in XML-RPC or in JSON format. You can also parse XML-RPC data and dump to JSON
data and vice versa.

For example, we can parse a JSON-formatted string and use that data to make an
XML-RPC call:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h" // also compile and link soapC.cpp and xml-rpc.cpp
    #include "json.h"  // also compile and link json.cpp for JSON serialization
    #include <sstream>
    struct Namespace namespaces[] = { {NULL, NULL} }; // no XML namespaces

    soap *ctx = soap_new1(SOAP_C_UTFSTRING); // UTF8 in char*/std::string
    value request(ctx);
    istringstream in;
    in.str("[ [1, \"2\", 3.14, true], {\"name\": \"john\", \"age\": 24} ]");
    in >> request;			// parse JSON, store as XML-PRC data
    params response = rpc(request);	// make the XML-RPC call
    std::cout << response << std::endl;	// display result in JSON
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The JSON protocol has fewer data types than XML-RPC, so type information can be
lost when serializing to JSON:

- XML-RPC distinguishes ints from floats while JSON only supports floats. Ints
  are converted to double floats by the JSON serializer.
- XML-RPC has a dateTime type, JSON does not. The JSON serializer converts the
  dateTime type to a dateTime-formatted string.
- XML-RPC uses a base64 type to exchange raw binary data. The base64 data is
  converted to a string with base64 content by the JSON serializer.

See the section on C++ Examples on how to populate and extract C++ data.

Strings are stored and exchanged in UTF8 format in 8-bit strings (`char*` and
`std::string`) by using the `SOAP_C_UTFSTRING` flag. Without this flag, 8-bit
strings are converted to UTF8. By contrast, wide character strings use unicode.

To force reading and writing JSON in ISO 8859-1 format from UTF8 strings, use
the `SOAP_ENC_LATIN` flag to set the context.


C++ JSON-RPC over HTTP (REST method)                                   {#cpp-jr}
------------------------------------

To invoke JSON-RPC over HTTP on the client side, use `json_call`:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"           // also compile and link soapC.cpp, xml-rpc.cpp
    #include "json.h"            // also compile and link json.cpp
    struct Namespace namespaces[] = { {NULL, NULL} }; // no XML namespaces

    soap *ctx = soap_new1(SOAP_C_UTFSTRING);
    value request(ctx), response(ctx);
    // now populate the 'request' data to send

    if (json_call(ctx, "URL", request, response) != SOAP_OK))
      ... // error
    else
      ... // use the 'response' data response

    // dealloc objects and temp data
    soap_destroy(ctx);
    soap_end(ctx);
    ... // make other calls etc.
    // dealloc context
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To implement a JSON-RPC server for CGI (e.g. install in cgi-bin):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"           // also compile and link soapC.cpp, xml-rpc.cpp
    #include "json.h"            // also compile and link json.cpp
    struct Namespace namespaces[] = { {NULL, NULL} }; // no XML namespaces

    int main()
    { soap *ctx = soap_new1(SOAP_C_UTFSTRING);
      value request(ctx), response(ctx);
      if (soap_begin_recv(ctx)
       || json_recv(ctx, request)
       || soap_end_recv(ctx))
        soap_send_fault(ctx);
      else
      { ... // use the 'request' value
	... // set the 'response' value
        // set http content type
        ctx->http_content = "application/json; charset=utf-8";
        // send http header and body
        if (soap_response(ctx, SOAP_FILE)
         || json_send(ctx, response)
         || soap_end_send(ctx))
          soap_print_fault(ctx, stdout);
      }
      // dealloc all
      soap_destroy(ctx);
      soap_end(ctx);
      soap_free(ctx);
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For client and server examples, please see the gSOAP package content:

- `gsoap/samples/xml-rpc-json/json-currentTime.cpp`
- `gsoap/samples/xml-rpc-json/json-currentTimeServer.cpp`

C XML-RPC and JSON                                                          {#c}
==================

The following source files are provided for XML-RPC support in C:

- `xml-rpc.h`:		XML-RPC binding as a gSOAP .h file for soapcpp2
			(do not #include this file in your project builds)

For JSON serialization, use the following files instead of xml-rpc-io.h and
xml-rpc-io.cpp:

- `json_c.h`:		C JSON serializer
- `json_c.c`:		C JSON serializer

For JSON-RPC over HTTP (JSON REST method), please use the `plugin/httppost.c`
plugin. See [JSON-RPC over HTTP](#c-jr) explanation below.

Note that `soapH.h`, `soapStub.h`, and `soapC.c` are required for XML-RPC and
JSON.  To generate these C files, you need to execute:

    soapcpp2 -c -CSL xml-rpc.h

Also compile and link with `stdsoap2.c` (or link with `libgsoap.a` installed by
the gSOAP package).


C Examples                                                               {#c-ex}
----------

Examples are provided in the software package:

- `xml-rpc-currentTime.c`:	client in C
- `xml-rpc-weblogs.c`:		client in C

All XML-RPC and JSON message manipulation is done at a very low-level.


C XML-RPC Client Example                                                 {#c-cl}
------------------------

An XML RPC call is made using the following function that you can define for
your convenience:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    #include "soapH.h" // generated by the command: soapcpp2 -c -CSL xml-rpc.h
    struct Namespace namespaces[] = { {NULL, NULL} }; // no XML namespaces

    int methodCall(struct soap *ctx, const char *URL, struct methodCall *m, struct methodResponse *r)
    {   /* no namespaces */
        ctx->namespaces = NULL;
        /* no SOAP encodingStyle */
        ctx->encodingStyle = NULL;
        /* connect, send request, and receive response */
        if (soap_connect(ctx, URL, NULL)
         || soap_begin_send(ctx)
         || soap_put_methodCall(ctx, m, "methodCall", NULL)
         || soap_end_send(ctx)
         || soap_begin_recv(ctx)
         || !soap_get_methodResponse(ctx, r, "methodResponse", NULL)
         || soap_end_recv(ctx))
            return soap_closesock(ctx); /* closes socket and returns error */
        soap_closesock(ctx);
        return SOAP_OK;
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Then use this XML-RPC method caller in C as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING); /* store UTF8 in char* */
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
    m.methodName = "methodName";
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
    if (methodCall(ctx, "http://domain/path/service", &m, &r))
    {   soap_print_fault(ctx, stderr);
        exit(ctx->error);
    }
    if (r.fault)
    {   /* print fault on stdout */
        soap_begin_send(ctx);
        soap_put_fault(ctx, r.fault, "fault", NULL);
        soap_end_send(ctx);
    }
    else
    {   /* print response parameters */
        int i;
        for (i = 0; i < r.params->__size; i++)
        {   printf("Return parameter %d = ", i+1);
            display(&r.params->param[i].value); /* SEE BELOW */
            printf("\n");
        }
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To dynamically allocate data for automatic deallocation by the gSOAP engine,
use `soap_malloc(ctx, size)`, for example as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    struct value *v = soap_malloc(ctx, 2 * sizeof(struct value));
    memset(v, 0, 2 * sizeof(struct value));

    soap_end(ctx); /* deallocate all */
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

See `xml-rpc-currentTime.c` and `xml-rpc-weblogs.c` for example C code.

A convenient way to display XML RPC data can be implemented as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    void display(struct value *v)
    {   int i;
        switch (v->__type)
        {   case SOAP_TYPE__boolean:
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
                printf("[%d bytes of raw data at %p]",
		    ((struct _base64*)v->ref)->__size,
		    ((struct _base64*)v->ref)->__ptr);
                break;
            case SOAP_TYPE__struct:
                printf("{\n");
                for (i = 0; i < ((struct _struct*)v->ref)->__size; i++)
                {   printf("\"%s\":", ((struct _struct*)v->ref)->member[i].name);
                    display(&((struct _struct*)v->ref)->member[i].value);
                    printf(",\n");
                }
                printf("}\n");
                break;
            case SOAP_TYPE__array:
                printf("[\n");
                for (i = 0; i < ((struct _array*)v->ref)->data.__size; i++)
                {   display(&((struct _array*)v->ref)->data.value[i]);
                    printf(",\n");
                }
                printf("]\n");
                break;
            default:
                if (!v->__type)
                    printf("\"%s\"", v->__any);
                else
                    printf("{?}");
        }
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


C JSON Serialization                                                     {#c-js}
--------------------

To display values in JSON format or parse JSON data, use the `json_c.h` and
`json_c.c` JSON serializers. It is also possible to send and receive JSON data
over HTTP.

You can dump the XML-RPC data in JSON or populate XML-RPC from JSON data,
because the data stored in C is independent of XML-RPC and JSON formats.

For example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    #include "json_c.h" // also compile and link json.cpp for JSON serialization
    struct Namespace namespaces[] = { {NULL, NULL} }; // no XML namespaces

    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING);
    struct value v;

    ctx->recvfd = ...;          // set file descriptor
    json_recv(ctx, &v);         // parse JSON, store as XML-PRC data

    ctx->sendfd = ...;          // set file descriptor
    json_send(ctx, &v);         // output JSON value
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The JSON protocol has fewer data types than XML-RPC, so type information can be
lost when serializing to JSON:

- XML-RPC distinguishes ints from floats while JSON only supports floats. Ints
  are converted to double floats by the JSON serializer.
- XML-RPC has a dateTime type, JSON does not. The JSON serializer converts the
  dateTime type to a dateTime-formatted string.
- XML-RPC uses a base64 type to exchange raw binary data. The base64 data is
  converted to a string with base64 content by the JSON serializer.

See the section on C++ Examples on how to populate and extract C++ data.

Strings are stored and exchanged in UTF8 format in 8-bit strings (`char*`)
by using the `SOAP_C_UTFSTRING` flag. Without this flag, 8-bit strings are
converted to UTF8. By contrast, wide character strings use unicode.

To force reading and writing JSON in ISO 8859-1 format from UTF8 strings, use
the `SOAP_ENC_LATIN` flag to set the context.


C JSON-RPC over HTTP (REST method)                                       {#c-jr}
----------------------------------

To serialize JSON over HTTP as a client application, use `plugin/httppost.c`,
for example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    #include "plugin/httppost.h"  // also compile and link plugin/httppost.c
    #include "json_c.h"           // also compile and link json_c.c
    struct Namespace namespaces[] = { {NULL, NULL} }; // no XML namespaces

    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING); // UTF8 in char*/std::string
    struct value request;
    ... // now populate the 'request' data to be send
    if (soap_post_connect(ctx, "URL", NULL, "application/json")
     || json_send(ctx, request)
     || soap_end_send(ctx))
        ... // error
    struct value response;
    if (soap_begin_recv(ctx)
     || json_recv(ctx, response)
     || soap_end_recv(ctx))
        ... // error
    ... // use the 'response' data response
    // dealloc objects and temp data
    soap_end(ctx);
    ... // make other calls etc.
    // dealloc context
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

