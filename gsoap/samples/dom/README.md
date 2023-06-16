
XML DOM & XPath                                                      {#mainpage}
===============

[TOC]

Introduction                                                            {#intro}
============

XML data bindings provide a powerful mechanism to parse, validate, manipulate,
and write XML data with ease as if we are working with native C and C++ data.
Occasionally we will need to work with raw XML data.  Raw XML can be parsed
with a DOM parser and stored in a DOM node graph.  The DOM (Document Object
Model) node graph (actually a node tree) can be inspected to retrieve text and
other values.  We can iteratively and recursively traverse the XML tree
via its DOM node graph at increasingly deeper levels to inspect and retrieve
values of XML elements and attributes.  We can also use XPath queries to locate
data deep in the DOM node hierarchy to retrieve specific values.

The gSOAP XML DOM API is compact in size but offers a wealth of operations to
construct, inspect, traverse, and search data in DOM node graphs.  The DOM API
offers powerful constructors to construct a DOM node graph for XML with **smart
XML namespace handling** to simplify coding.  The DOM API also offers a hybrid
**DOM + data binding approach** that allows you to embed serializable C/C++
data types including user-defined structs and classes.  You can also search and
retrieve values from XML and XML with namespaces using the DOM API's smart XML
namespace handling.

We also offer a new code generation tool, **domcpp**, that greatly simplifies
writing DOM API code by generating DOM construction code, DOM inspection code,
and XPath code to query a DOM.  The generated code uses the DOM API
transparently in C and C++ (C++ by default and pure C as an option).  So it is
easy to get familiar with the DOM API by using the domcpp tool.  In the first
part of this introduction we show how to effectively use the domcpp tool to get
started.

This document describes both the C and C++/C++11 APIs, see table of contents.

XML DOM and gSOAP                                                     {#intro-1}
-----------------

To help you quickly develop C/C++ code to construct, inspect, and search DOM
node graphs using the XML DOM API, we offer a new code generator **domcpp**
with the gSOAP package (version 2.8.28 and up).  You can find the domcpp tool
with the DOM examples in `gsoap/samples/dom`.

The domcpp command-line tool auto-generates C or C++ code from an XML fragment.
The generated code creates a DOM node graph for this fragment, which can be
further tweaked as necessary.  Let's demonstrate this with an example
`menu.xml` XML file, where we show each command executed in a command shell
followed by the results displayed in the terminal:

    cat menu.xml

<div class="alt">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.txt}
    <menu id="file" value="File">
      <popup>
        <menuitem value="New" onclick="CreateNewDoc()" />
        <menuitem value="Open" onclick="OpenDoc()" />
        <menuitem value="Close" onclick="CloseDoc()" />
      </popup>
    </menu>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</div>

    domcpp menu.xml

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    {
      struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
      ctx->double_format = "%lG";

      xsd__anyType dom(ctx, "menu");
      dom.att("id") = "file";
      dom.att("value") = "File";
      dom["popup"]["menuitem"][1].att("value") = "New";
      dom["popup"]["menuitem"][1].att("onclick") = "CreateNewDoc()";
      dom["popup"]["menuitem"][2].att("value") = "Open";
      dom["popup"]["menuitem"][2].att("onclick") = "OpenDoc()";
      dom["popup"]["menuitem"][3].att("value") = "Close";
      dom["popup"]["menuitem"][3].att("onclick") = "CloseDoc()";
      std::cout << dom << std::endl;

      soap_destroy(ctx); // delete objects
      soap_end(ctx);     // delete DOM data
      soap_free(ctx);    // free context
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The C++ DOM API is designed around the concept of XPath's path location to
construct a node graph by aligning the C++ `[]` overloaded operator to XPath's
path steps and position predicates.  You can use domcpp option `-e` to reveal
the XPath for each assignment statement.  For example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    xsd__anyType dom(ctx, "menu");
    // /menu/@id = file
    dom.att("id") = "file";
    // /menu/@value = File
    dom.att("value") = "File";
    // /menu/popup/menuitem[1]/@value = New
    dom["popup"]["menuitem"][1].att("value") = "New"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Domcpp option `-e` adds explanatory comments to the generated code, which
explains what the code does to help you understand the DOM API by including
XPath path locations and other details.

You can use domcpp option `-M` to narrow the generated code down to the
essentials, without the initialization and cleanup parts of the code.  This
makes the generated code suitable for direct inclusion in your codebase.

Generating code to populate a DOM node graph is one option.  Another option is
to generate code to inspect a DOM node graph.  Use domcpp option `-i` to
generate code to inspect the DOM node graph of XML parsed from input, given
that the XML file provided with option `-i` serves as a generic template:

    domcpp -i menu.xml

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    {
      struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
      ctx->double_format = "%lG";

      xsd__anyType dom(ctx);
      std::cin >> dom;
      if (dom.soap->error)
        exit(EXIT_FAILURE); // error parsing XML
      xsd__anyAttribute *att;
      xsd__anyType *elt;
      #define USE_ATT(path, text) std::cout << path << " = " << text << std::endl
      #define USE_ELT(path, text) std::cout << path << " = " << text << std::endl
      if ((att = dom.att_get("id")))
        USE_ATT("/menu/@id", att->get_text());
      if ((att = dom.att_get("value")))
        USE_ATT("/menu/@value", att->get_text());
      if ((elt = dom.elt_get("popup")))
      {
        xsd__anyType& dom_popup = *elt;
        for (xsd__anyType *it = dom_popup.elt_get("menuitem"); it; it = it->get_next())
        {
          xsd__anyType& dom_popup_menuitem = *it;
          if ((att = dom_popup_menuitem.att_get("value")))
            USE_ATT("/menu/popup/menuitem/@value", att->get_text());
          if ((att = dom_popup_menuitem.att_get("onclick")))
            USE_ATT("/menu/popup/menuitem/@onclick", att->get_text());
        }
      }
      std::cout << dom << std::endl;

      soap_destroy(ctx); // delete objects
      soap_end(ctx);     // delete DOM data
      soap_free(ctx);    // free context
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can also use domcpp option `-p` to generate efficient XPath query code to
query and retrieve specific XML values.

For example, let's write an XPath query to display the authors of books in a
store.  We will read the XML data from `std:cin` and filter the authors with
the query `/store/book/@author` to collect them in a DOM node graph `y` containing
the query results with domcpp option `-y`.  We generate the code from the
command line with domcpp as follows:

    domcpp -M -p'/store/book/@author' -y

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    xsd__anyType dom(ctx);
    std::cin >> dom;
    // XPath: /store/book/@author
    xsd__anyAttribute *att;
    xsd__anyType *elt;
    xsd__anyType y(ctx, "results");
    #define QUERY_YIELD_ATT(v) y.add(xsd__anyType(ctx, "result").add(v));
    #define QUERY_YIELD_ELT(v) y.add(xsd__anyType(ctx, "result").add(v));
    if (dom.match("store"))
    {
      size_t pos = 1;
      for (xsd__anyType *it = dom.elt_get("book"); it; it = it->get_next(), ++pos)
      {
        xsd__anyType& v = *it;
        if ((att = v.att_get("author")))
        {
          xsd__anyAttribute& v = *att;
          QUERY_YIELD_ATT(v);
        }
      }
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Let's apply this query to the `store.xml` file that you can find in section
[XPath by example](#domcpp-4):

    ./query < store.xml

<div class="alt">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.txt}
    <results>
      <result author="Nigel Rees"/>
      <result author="Evelyn Waugh"/>
      <result author="Herman Melville"/>
      <result author="J. R. R. Tolkien"/>
    </results>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</div>

You can compile this example yourself with:

    domcpp -o query.cpp -m -p'/store/book/@author' -y
    soapcpp2 -CSL import/dom.h
    c++ -o query query.cpp soapC.cpp dom.cpp stdsoap2.cpp

You can also embed C/C++ code in XPath queries to filter and select values from
XML at runtime.

The domcpp code generator aims to produce clean, high-quality and readable
C and C++ code.  You can also embed C/C++ code in XPath queries to filter and
select values from XML data at runtime.

We will present domcpp in more detail in the next section.  The remainder of
this document explains how you can use the DOM C and C++ APIs to create XML
data, access XML data, send/recv data via REST, and to read/write XML data to
files, streams, and string buffers.

XML DOM versus XML data bindings                                      {#intro-2}
--------------------------------

XML data bindings greatly simplify the development of XML applications.
Compared to DOM manipulation and search by DOM tree traversal, all that is
needed are declarations of the C/C++ data types that need to be serializable in
XML by using the soapcpp2 tool the generate the data binding implementation.
Furthermore, XML parsing is much faster with XML data bindings.  XML is
efficiently pulled and converted by the C/C++ deserializers.

For more details, see [XML Data Bindings](http://www.genivia.com/doc/databinding/html).

On the other hand, you can use the XML DOM API to develop REST operations for
SOAP and XML messaging by composing and decomposing the XML manually.  For
example in C++:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    struct Namespace namespaces[] = {
      {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/"},
      {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/"},
      {"xsi",      "http://www.w3.org/2001/XMLSchema-instance"},
      {"xsd",      "http://www.w3.org/2001/XMLSchema"},
      {"t",        "http://tempuri.org/t.xsd"},
      {NULL,       NULL}
    };
    int main()
    {
      soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
      const char *endpoint = "http://www.cs.fsu.edu/~engelen/gmtlitserver.cgi";
      xsd__anyType req(ctx, "SOAP-ENV:Envelope"); // DOM with SOAP envelope
      xsd__anyType res(ctx);                      // DOM for SOAP response
      req["SOAP-ENV:Body"]["t:gmt"] = "";         // SOAP Body with <t:gmt>
      soap_dom_call(ctx,                          // make a call (POST)
          endpoint,                               // the service endpoint URL
          NULL,                                   // no SOAPAction header
          req,                                    // request t:gmt
          res);                                   // response, if OK
      if (ctx->error) ...                         // handle IO error
      xsd__anyType::iterator i = res.find("param-1");
      if (i != res.end())                         // if found, display time
        cout << "Current time = " << i->get_text() << endl;
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `SOAP_DOM_TREE` context flag used here disables the deserialization of
embedded objects and data, which will be discussed in the next section.

Other REST methods can be used to manage the state of resources via URL
references, allowing for the storage of data (HTTP PUT), retrieval of data
(HTTP GET), and removal of data (HTTP DELETE) from a resource.  The
`soap_dom_call` function takes NULL as the service input request and service
output response parameters to facilitate PUT (NULL for response), GET (NULL for
request), and DELETE (both request and response are NULL).

However, XML data bindings greatly simplify the development of XML applications
such as client and server runtimes for XML messaging and message validation.
Compared to DOM manipulation and search by DOM tree traversal, all that is
needed are declarations of server operations as C functions and the C/C++ data
types passed to these functions.

For example, with XML data bindings it only takes one line to declare the
SOAP/XML service operation:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    t__gmt(time_t*);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The soapcpp2 tool generates the data binding implementation such that `t__gmt`
can be invoked as a function in a client-side C or C++ runtime:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    #include "t.nsmap"
    int main ()
    {
      soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT);
      time_t t;
      soap_call_t__gmt(ctx, endpoint, NULL, &t);
      if (ctx->error == SOAP_OK)
        cout << "Current time = " << ctime(t) << endl;
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The gSOAP DOM API offers a hybrid **DOM + data binding approach** that allows
you to use DOM nodes a members of serializable structs and classes (these DOM
parts are auto-generated by wsdl2h with option `-d`).  This hybrid approach
also allows you to embed serializable C/C++ data into a DOM node graph.  This
way, you get the best of both XML DOM and XML data bindings.

Embedding serializable objects and data in DOM element nodes          {#intro-3}
------------------------------------------------------------

To embed serializable data types we first declare these types in a header file
for soapcpp2 to generate the data binding code.  We also import `dom.h` from
`gsoap/import` to use the DOM API:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #import "import/dom.h"
    //gsoap t schema namespace: urn:demotime
    typedef time_t _t__time;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is a very small example to illustrate the concept.  You can add
declarations of data types to serialize.  If namespaces are used in the XML
document, then follow the naming conventions outlined in
[XML Data Bindings: Colon notation versus name prefixing](http://www.genivia.com/doc/databinding/html/index.html#toxsd2).

Importing `dom.h` is automated with wsdl2h option `-d` when running wsdl2h on
WSDL and XSD files to produce a header file with the data binding interface for
soapcpp2.  Here, we assume you are starting with a header file for soapcpp2
with the declarations of C/C++ types to serialize.

We use soapcpp2 to generate the data binding implementation code together with
the DOM API in `soapStub.h`, `soapH.h`, `soapC.cpp` and a namespace table file
`t.nsmap` and `t.xsd` schema that declares a `time` type (at line 11) and also
an element (at line 15) because by convention  the `_t__time` type name is
prefixed with a `_`:

<div class="alt">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.txt}
    <schema targetNamespace="urn:demotime"
        xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"
        xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns:xsd="http://www.w3.org/2001/XMLSchema"
        xmlns:t="urn:demotime"
        xmlns="http://www.w3.org/2001/XMLSchema"
        elementFormDefault="unqualified"
        attributeFormDefault="unqualified">
      <import namespace="http://schemas.xmlsoap.org/soap/encoding/"/>
      <simpleType name="time">
        <restriction base="xsd:dateTime">
        </restriction>
      </simpleType>
      <element name="time" type="xsd:dateTime"/>
    </schema>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</div>

For details on declaring C/C++ types for XML data bindings and serialization, see
[XML Data Bindings: Defining document root elements](http://www.genivia.com/doc/databinding/html/index.html#toxsd9-7).

You can use these serializable types declared in the header file as embedded
serializable objects and data in DOM element nodes.  The `SOAP_DOM_NODE`
context flag should be set to enable this feature.

In the following example we use `_t__time` to construct a DOM for an XML root
element `<t:time>` that contains an embedded serializable `time_t` value:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    #include "t.nsmap"
    int main()
    {
      soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_NODE);
      time_t t = time(0);
      xsd__anyType dom(ctx, NULL, "t:time", &t, SOAP_TYPE__t__time);
      cout << dom << endl;     // write XML <t:time>...</t:time>
      if (dom.soap->error)
        ... // handle IO error
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

and to parse and deserialize a `<t:time>` into a `time_t` value:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    #include "t.nsmap"
    int main()
    {
      soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_NODE);
      xsd__anyType dom(ctx);
      cin >> dom;              // parse XML <t:time>...<t:time>
      if (dom.soap->error)
        ... // handle IO error
      const time_t *t = static_cast<const time_t*>(dom.get_node(SOAP_TYPE__t__time));
      if (t)
        cout << "Time = " << ctime(t) << endl;
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

With the `SOAP_DOM_NODE` flag set, there are two ways the C/C++ types are
deserialized into DOM elements: by element tag name matching or by xsi:type
matching:

1. If an xsi:type attribute is present (which requires preparations on the
   sending side), then its value is matched against the names of the C/C++
   types to select a deserializer to parse and deserialize the data into a DOM
   element node as embedded objects/data.  If no xsi:type attribute is
   present or if no serializer is found, then:
2. The element tag is matched against the names of serializable C/C++ types to
   select a deserializer to deserialize the data into a DOM element node as
   embedded objects/data.  If no deserializer is found then the XML element is
   parsed and stored as a DOM element node.

While `SOAP_DOM_NODE` instructs the DOM parser to deserialize the values of
C/C++ types that match element tags, the opposite, `SOAP_DOM_TREE` prevents
deserialization, even when an `id` attribute is present in the XML payload.
The default is to deserialze only when an `id` attribute is present in the XML
payload.  This is to ensure that the SOAP encoding protocol deos not break when
id-ref attibutes are used for multireferenced objects.

The domcpp command-line tool                                           {#domcpp}
============================

The domcpp command produces high-quality, readable and reusable source code.
The generated code can be readily used in your projects to populate XML data
and retrieve XML data, thereby saving you substantial time and effort to write
DOM API code in C or C++.

The domcpp command-line tool generates C or C++ source code to populate a DOM
node graph with the XML data given in an XML file.  The command also has an
option `-i` to generate source code to inspect parsed XML by using an XML file
as a generic template for this code.  And option `-p` generates efficient
source code for XPath queries.  Even stand-alone XPath query filter
applications can be auto-generated with option `-m` (for main).

Compiling the domcpp command                                         {#domcpp-1}
----------------------------

You will find domcpp and the XML DOM examples in the gSOAP package in
`gsoap/samples/dom`.

To build domcpp, [install gSOAP](http://www.genivia.com/downloads.html) and
build all sample codes as follows:

    ./configure --enable-samples
    make
    make install

This builds the command-line tool domcpp in `gsoap/samples/dom` from where you
can use it and/or copy it for use with your projects.

If you do not have the samples built, you can use soapcpp2 (or soapcpp2.exe
in `gsoap/bin/win32`) from the command line to generate the C++ code required
for domcpp:

    cd gsoap/samples/dom
    soapcpp2 -CSL ../../import/dom.h
    c++ -I../.. -o domcpp domcpp.cpp soapC.cpp ../../dom.cpp ../../stdsoap2.cpp

The above builds the domcpp command-line tool.

Command-line options                                                 {#domcpp-2}
--------------------

The domcpp command takes several options and an optional XML input file:

    domcpp [-c] [-e] [-f%fmt] [-h] [-i] [-l] [-m] [-M] [-n] [-O] [-ofile] [-ppath] [-rroot] [-xcode] [-y] [infile]

where the domcpp command-line options are:

| Option   | Description                                                       |
| -------- | ----------------------------------------------------------------- |
| `-c`     | generate C code instead of C++                                    |
| `-e`     | add explanatory comments to the generated code                    |
| `-f%%fmt`| use `%%fmt` to format double floats, e.g. `-f%%lG`                |
| `-h`     | display help message                                              |
| `-i`     | generate code to inspect DOM node graph parsed from XML input     |
| `-l`     | generate code for option `-i` to store values in local variables  |
| `-m`     | generate stand-alone code by adding `main()`                      |
| `-M`     | generate minimal code unadorned with initialization and cleanup   |
| `-n`     | generate XML namespace table                                      |
| `-O`     | optimize code by factoring common indices when applicable         |
| `-ofile` | save source code to `file`                                        |
| `-ppath` | generate XPath query code for `path`                              |
| `-rroot` | use `root` instead of root value `dom` in the generated code      |
| `-xcode` | generate code that executes `code` for each XPath query result    |
| `-y`     | generate code that yields an array `y` of XPath query results     |
| `infile` | optional XML file to parse                                        |
| `-`      | read XML from standard input                                      |

The domcpp command takes an XML input file `infile` to generate code to
construct a DOM node graph in C/C++ for this XML, or, with option `-i`, to
generate code that reads XML from input and traverses it to inspect its value
by using the XML input file `infile` as a template to match against.  For
option `-i`, if you want additional code that uses local variables to store
boolean, integer, and floating point values retrieved from the DOM node graph,
then also use option `-l` with option `-i`.

Use option `-c` to generate C code instead of C++ and use option `-e` to add
explanatory comments to the generated code.

The domcpp command emits source code to standard output or to the file
specified with option `-o`.

Minimalistic code is generated with option `-M`, which is useful to automate
pasting of the unadorned source code into the source code of your project.

Optimized code is generated with option `-O` by factoring common array indices
and object field names.  This produces more elaborate code that is more
efficient but may be harder to read and modify.  This option has no effect on
the code generated with option `-i`.

The default name of the root value in the generated source code is `dom`.  To
change this name use option `-r`.  Do not use the name `v`, which represents
the current value in XPath query C/C++ code.  Other variable names to avoid are
`it`, `att`, `elt`, and `pos`, since these are internally used by the generated
code.

To include a namespace table in the generated code, use option `-n`.  This
option simplifies the use of the DOM API by removing namespace URIs passed to
API functions, as the use of qualified tag names will suffice in most cases.

Use option `-p` to generate code that filters XML data from a source of input
with an XPath query `path`.  Option `-x` specifies XPath query code to execute
for each query result.  The default action in the generated code is to print
each query result value in XML separated by newlines.  Option `-y` yields an
XML DOM with root `results` and each query result stored in a `result` element.
Option `-x` overrides option `-y`.

To generate a stand-alone application use option `-m`.  This option is useful
for testing XPath query filters given with option `-p`.

Option `-f%%fmt` sets the floating point double precision format to use in the
generated code.  By default, domcpp emits floating point numbers with up to 17
digit mantissas to preserve precision.  Use `-f%%lG` for the shortest floating
point representation.

XPath syntax support for domcpp                                      {#domcpp-3}
-------------------------------

XPath (the XML Path Language), is a query language for selecting nodes from an
XML document.  A XPath query returns the XML elements and attributes of a DOM
node structure of an XML document that match the selection criteria.

An XPath expression specifies a data query to select elements and attributes
(and their values) typically starting from the root node, and descending deeper
into the node graph to match child nodes.

For example, suppose we have a `<store>` root element with a number of `<book>`
child elements.  Each `<book>` element has a `title` attribute with the title
text and some other attributes which we will ignore for now.  The following
XPath query returns the titles of all books in the store:

    /store/book/@title

This example illustrates the most important kind of expression in XPath, which
is a **location path**.  A location path consists of a sequence of **location
steps**.  Locations steps are separated by '/'.  Each step consists of an
**axis** followed by an optional **node test** and zero or more **predicates**.

The axis, node tests, and predicates supported by domcpp XPath expressions are
listed in the three tables below.

| Axis          | Nodes matched and returned                                   |
| ------------- | ------------------------------------------------------------ |
| `/`           | document root (when used at the start of the location path)  |
| `//`          | descendant or self                                           |
| `.`           | self                                                         |
| `..`          | parent node                                                  |
| `@`           | attribute node                                               |
| `tag`         | tag name of attributes or elements in the null namespace     |
| `ns:tag`      | tag name of attributes or elements in the `ns` namespace     |
| `*` or `*:*`  | any tag name in any namespace                                |
| `*:tag`       | tag name in any namespace                                    |
| `ns:*`        | all tags in the `ns` namespace                               |

Note that domcpp XPath does not (yet) support the full XPath axis syntax.

| Node test     | Nodes matched and returned                                   |
| ------------- | ------------------------------------------------------------ |
| `text()`      | text-only child nodes                                        |

A `text()` node test is useful to select text-only child nodes when its
siblings are a mix of text and elements.  This mixed content of elements and
text is more common in XHTML markup, but not in XML Web service messaging for
example.

Zero or more predicates may follow to filter nodes by position, by path, or by
a C/C++ expression:

| Predicate     | Nodes filtered                                               |
| ------------- | ------------------------------------------------------------ |
| `[n]`         | select nodes that are at the n-th position                   |
| `[path]`      | select nodes if XPath `path` matches                         |
| `[?expr]`     | select nodes if C/C++ expression `expr` is true or nonzero   |

Note that domcpp XPath does not (yet) support functions and operators in
predicates.  Instead, you can use C/C++ expressions to filter nodes where
variable `v` refers to the axis node (i.e. self, which is an `xsd__anyType`
element node or an `xsd__anyAttribute` attribute node) and the integer variable
`pos` that refers to the query position.

Path subexpressions are grouped with `(` and `)`.  Grouping is useful to apply
predicates to a specific part of the location path.  Without grouping, a
predicate only applies to the axis that immediately preceeds it.  For example,
`x/y[1]` selects the first child element `y` of all `x` elements.  By contrast,
`(x/y)[1]` selects the first `y` child element of the first `x` element that
has at least one `y` child element.

XPath by example                                                     {#domcpp-4}
----------------

Consider the following XML document:

<div class="alt">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.txt}
    <store>
      <book
        category="reference"
        author="Nigel Rees"
        title="Sayings of the Century"
        price="8.95" />
      <book
        category="fiction"
        author="Evelyn Waugh"
        title="Sword of Honour"
        price="12.99" />
      <book
        category="fiction"
        author="Herman Melville"
        title="Moby Dick"
        isbn="0-553-21311-3"
        price="8.99" />
      <book
        category="fiction"
        author="J. R. R. Tolkien"
        title="The Lord of the Rings"
        isbn="0-395-19395-8"
        price="22.99" />
      <bicycle
        color="red"
        price="19.95" />
    </store>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</div>

To match the `title` of the first book in a `store`, starting at the root
indicated by `/`, we use the following XPath query expression:

    /store/book[1]/@title

This query returns `"Sayings of the Century"` when applied to the XML document.

To try the XPath examples yourself, we suggest to create a `store.xml` file
with the above XML and run domcpp from the command line to compile an XPath
query as follows:

    cd gsoap/samples/dom
    soapcpp2 -CSL ../../import/dom.h
    domcpp -o test-dom.cpp -m -p'/store/book[1]/@title'
    c++ -I../.. -o test-dom test-dom.cpp soapC.cpp ../../dom.cpp ../../stdsoap2.cpp
    ./test-dom < store.xml

The `soapC.cpp` file, and the header files `soapStub.h` and `soapH.h`, are
generated with the command `soapcpp2 -CSL dom.h`, which is done just once for
all C++ DOM applications.  Use soapcpp2 option `-c` to generate `soapC.c` for C
(with the corresponding `soapStub.h` and `soapH.h` in C).

The compiled XPath query is applied to the `store.xml` document and returns the
matches found.  Use domcpp option `-y` to collect and return all matches in an
XML document with root `results`:

    <results>
      <result title="Sayings of the Century"/>
    </results>

To match any tag name of an element or attribute, we use a wildcard `*`:

    /store/*/@price

This matches and returns the prices of all items in the store.  If we want to
obtain all `price` attributes at any level of the node graph, we can also use
`//` called "recursive descent" or simply "recurse" to select descendents (and
self when used at the root):

    //@price

This query selects all `price` attributes in an XML document at any level,
including the `price` attribute of the document root if any.  For our example
XML store this query returns the prices of all items in the store.

To select all attributes of a node we use a wildcard `@*`, for example to
obtain all attributes of the first book in the store:

    /store/book[1]/@*

We can predicate node selections with criteria based on path location matches.
For example, to select items from the store that have an `isbn` attribute, and
then obtain their price, we use a path location predicate `[@isbn]`:

    /store/*[@isbn]/@price

If we only want to find the first result, we specify a position predicate `[1]`
and apply it to all location steps in the XPath expression:

    /(store/*[@isbn]/@price)[1]

A predicate applies to the axis and its predicates located to the left of the
predicate as part of one location step, so we used parenthesis to group the
location steps to apply the `[1]` position predicate.

There can be several ways an XPath query can be formulated.  Here is a
different one without parenthesis to obtain the same result:

    /store/*[@isbn][@price][1]/@price

This query matches books with both an isbn and price attribute and returns the
price of the first match found.

Because all store items are priced in our XML store example, we can also use
the following XPath query:

    /store/*[@isbn][1]/@price

However, it is generally better to use more robust XPath queries that are not
based on assumptions, such as the previous queries for our XML store that cope
with price omissions.

More complex queries can be formulated by embedding C/C++ expressions in the
query as predicates with `[?expr]`.  This is an extension of domcpp and not
standard XPath expression syntax.

For example, the following XPath query with C++ predicate selects store items
with prices under 10.0:

    /store//@price[?(double)v < 10.0]

and in C:

    /store//@price[?soap_att_get_double(v) < 10.0]

We can combine the C/C++ predicate with a path predicate to get books priced
under 10.0:

    /store/book[@price[?(double)v < 10.0]]

and to obtain the book titles of these books only:

    /store/book[@price[?(double)v < 10.0]]/@title

XPath queries do not modify the node graph searched.  So you do not need to
worry about predicates with position indices that are out of bounds or about
tag names that refer to non-existent attributes or elements.

@warning In this respect we should caution you about using C/C++ expressions
that modify DOM nodes, since this may affect the query results in unpredictable
ways.  For example:

    //[?(double)v.att("price") < 10.0]

@warning The `att("price")` method sets an attribute, not just reads it, so
disaster strikes as we visit every node in the DOM node graph to set a price
attribute!

As you can see, C/C++ predicates can inspect the current XPath node by
accessing variable `v`.  This variable is either an `xsd__anyType` DOM element
node or an `xsd__anyAttribute` DOM attribute node, depending on the path.
Variable `v` is a reference in C++ and a pointer in C.

Besides the current node `v` you can also access the XPath root node `dom`.
Instead of the default root name `dom`, you can change `dom` to another name
with domcpp option `-r`.  You can also access `pos` which corresponds to the
XPath `position()` value.

You can access variables and functions in C/C++ predicates, but do not modify
the variables `it` and `pos` which are internally used by the generated XPath
query code.  

For example, you can access variable `pos` (but you should not change it):

    /(store/*[@isbn]/@price)[?pos > 1]

This XPath query returns the price of books with an `isbn`, but after the first
match was discarded by the predicate.

Other temporary variables used internally are a pointer to an attribute `att`
and a pointer to an element `elt`.  You may set and use these as temporaries in
the scope of a C/C++ predicate.

The C/C++ predicates are quite powerful and can be used to filter values as
shown earlier but also to select attributes and elements by matching their tag
name using `v,match(tag)` in C++ and `soap_att_match(v, NULL, tag)` or
`soap_elt_match(v, NULL, tag)` in C:

    //book/@*[?v.match(argv[1])]

This assumes that the command-line argument (`argv[1]`) of the application is a
book attribute name.  Otherwise, no results are returned.

After compiling the XPath query with

    domcpp -o test-dom.cpp -m -p'//book/@*[?v.match(argv[1])]'
    c++ -I../.. -o test-dom test-dom.cpp soapC.cpp ../../dom.cpp ../../stdsoap2.cpp

we can obtain the book titles with:

    ./test-dom title < store.xml

Finally, let's use the value of `argv` to filter products in the store by a
given command-line argument price:

    domcpp -m -p'//@price[?(double)v < strtod(argv[1], NULL))]'

and in C:

    domcpp -c -m -p'//@price[?soap_att_get_double(v) < strtod(argv[1], NULL))]'

Note that the `strtod` function returns the double float value of `argv[1]` and
is repeately called.  A more efficient implementation would store the value in
a temporary variable and use the temporary in the C/C++ predicate.

Understanding XML namespaces                                               {#ns}
============================

XML namespaces are commonly used with XML documents that are instances of XML
schemas.  A full introduction is beyond the scope of this document.  We
instroduce the basics here to help you understand why XML namespaces are
important and how they are used in the C/C++ DOM API of gSOAP.

XML namespace are important when XML documents contain instances of multiple XML
schemas.  XML elements and attributes that are declared in separate schemas
should be distinguishable and their content should be verifyable.  Tag name
conflicts that may be caused by combining multiple XML schemas to define an XML
document can be resolved by binding elements and attributes to specific XML
namespaces.

XML elements and attributes are bound to an XML namespace by using a namespace
prefix in qualified tag names of elements and attributes.  A qualified tag is
of the form `prefix:name`, such that the prefix is bound in the scope of the
tag to a namespace URI with an `xmlns:prefix="URI"` declaration.  Unqualified
tags can be bound to a namesapce with a `xmlns="URI"` default namespace
declaration.

An XML namespace is a Uniform Resource Identifier (URI).  There are two general
forms of URI: Uniform Resource Locators (URL) and Uniform Resource Names (URN).

Consider for example the XML document with elements and attributes in three
distinct XML namespaces `"urn:one"`, `"urn:two"`, and `"urn:three"`:

<div class="alt">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.txt}
    <x:e1 a1="1" xmlns:x="urn:one" xmlns:y="urn:two" y:a2="2">
      <e2 xmlns="urn:three" a3="3">
        <e3 />
      </e2>
    </x:e1>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</div>

Element `e1` is bound to `"urn:one"`, `e2` and `e3` are bound to `"urn:three"`.
Attribute `a1` has no namespace (it is in the null namespace), `a2` is bound to
`"urn:two"` and `a3` is bound to `"urn:three"`.

A namespace declaration (`xmlns`) scope extends to all descendants or until
redeclared.  The `x` and `y` prefixes declared in element `e1` have a scope of
visibility in all elements, since `e1` is the root.  The default namespace
declaration in element `e2` has a scope of visibility in element `e2` and
extends to all of its attributes and all of its child elements.

An XML namespace may refer to the defining XML schema by a URL, but often they
do not.  The URI string itself should be sufficiently unique, which is
important to distinguish XML elements and attributes in different XML
namespaces.  This is similar to C++ namespaces.  A unique c++ namespace name
suffices (we do not need to know where the source files are located).

The DOM API aims to simplify XML document construction and XML analysis by
offering an API that does not require full namespace URIs to passed to the API
functions when the URIs are defined in a namespace table.  You can simply use
qualified tag names to construct XML documents in a DOM and to analyze a DOM
after XML parsing.  This approach works on the basis of internal normalization
so that two prefixes match when their associated URI matches (i.e. prefix names
may differ but still match when their URIs match).

Assume we have the following namespace table of `{"prefix", "URI"}` bindings
that includes the three namespace URIs used in our example XML document, but we
pick three different prefixes `a`, `b`, and `c`:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    struct Namespace namespaces[] =
    {
      {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope",      NULL},
      {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding",      NULL},
      {"xsi",      "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
      {"xsd",      "http://www.w3.org/2001/XMLSchema",          "http://www.w3.org/*/XMLSchema",          NULL},
      {"a",        "urn:one"},
      {"b",        "urn:two"},
      {"c",        "urn:three"},
      {NULL, NULL, NULL, NULL}
    };
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

With this table defined globally (or by using `soap_set_namespaces()` see next
section), we can conveniently use qualified tag names with the prefixes `a`,
`b`, and `c` to construct and/or match XML elements and attributes in these
namespaces, because namespace matching is based on the URI of a prefix.

Therefore, the following qualified tag names match the following elements and
attributes in the example XML document:

| Tag name | Matches                                                 |
| -------- | ------------------------------------------------------- |
| `"a:e1"` | element `<x:e1>` in namespace scope `xmlns:x="urn:one"` |
| `"a1"`   | attribute `a1` in the null namespace                    |
| `"b:a2"` | attribute `y:a2` in namespace scope `xmlns:y="urn:two"` |
| `"c:e2"` | element `<e2>` in namespace scope `xmlns="urn:three"`   |
| `"c:a3"` | attribute `a3` in namespace scope `xmlns="urn:three"`   |
| `"c:e3"` | element `e3` in namespace scope `xmlns="urn:three"`     |

The choice of prefixes `a`, `b`, and `c` is rather arbitrary.  We can pick
prefix names for the table as long as they are unique and are valid names
(we refer to the XML syntax of "colonized names" and "non-colonized names").

The domcpp option `-n` includes XML namespaces in a namespace table in the
auto-generated code by copying namespace bindings from the XML document
analyzed by the tool to a namespace table.

@note You can also use the wsdl2h tool to retrieve namespaces and declare your
own prefix names in `typemap.dat`.  The soapcpp2 tool generates the data
binding implementation and a `.nsmap` file with the namespace bindings.

You can still use the DOM API without a namespace table or with an incomplete
table, but the namespace URIs that are left out from the table must be
specified as additional `ns` parameters in the DOM API functions.

C++ XML DOM API                                                           {#cpp}
===============

XML is represented as a DOM node graph internally consisting of values (text
strings of character data in UTF-8), attribute nodes with tag name and optional
namespace URI, and element nodes with optional tag names  and optional
namespace URI.  Tag names are stored in strings of UTF-8.  Tag names can be
qualified of the form `q:tag` or unqualified.  An element tag name that is
NULL represents a text-only node, which will only be present in mixed content
of elements and text character data (as in XHTML markup).

XML namespace handling is "smart" in the gSOAP DOM API: the DOM engine matches
and stores XML with namespace URIs to ensure that a prefix qualifier is always
locally bound to a namespace URI in the node graph.  Furthermore, you can use
qualified tags when constructing a DOM node instead of the full namespace URI,
but only if the prefix and URI are defined in the namespace table (global
`struct Namespace namesapces[]`.  When working with wsdl2h and soapcpp2 you
should include the soapcpp2-generated `.nsmap` file with namespace bindings
that are applicable to your XML tags.

List of C++ files                                                   {#cpp-files}
-----------------

The following files located in the package under `gsoap` are required to use
the C++ DOM API:

- `stdsoap2.h`:         gSOAP engine
- `stdsoap2.cpp`:       gSOAP engine
- `dom.cpp`:            DOM parser and DOM C/C++ API implementation
- `import/dom.h`:       DOM import for data bindings in a .h file for soapcpp2
                        (do not #include this file in your project builds).
                        Use soapcpp2 `-Iimport` to specify import path when
                        `dom.h` is imported in a header file for soapcpp2.

The gSOAP header file `dom.h` declares the DOM for use in data bindings and
should generally be imported with `#import` in gSOAP header files for the
soapcpp2 tool.

You can also run soapcpp2 directly on `import/dom.h` for DOM-only projects.
This generates `soapStub.h`, `soapH.h` and `soapC.cpp`.  To auto-generate these
files, execute:

    soapcpp2 -CSL import/dom.h

Then compile and link the `dom.cpp` files listed above with the auto-generated
`soapC.cpp` and `stdsoap2.cpp`:

    c++ -I../.. -o myapp myapp.cpp soapC.cpp ../../dom.cpp ../../stdsoap2.cpp

Instead of `stdsoap2.cpp` you can link `-lgsoap++.a` when installed by the
gSOAP package.  Or link `-lgsoapssl++.a` to get both `stdsoap2.cpp` and
`dom.cpp` with OpenSSL enabled for HTTPS:

    c++ -DWITH_OPENSSL -I../.. -o myapp myapp.cpp soapC.cpp -lgsoapssl++ -lssl -lcrypto

Note that we compile with `-DWITH_OPENSSL` and link `-lssl`, and `-lcrypto`.

Because XML namespaces are required except for the most simple plain XML
applications, you should include the generated `.nsmap` file:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    #include "soap.nsmap"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Or define your own namespace table.  For example, at a minimum you want a table
with SOAP and XSD bindings:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    struct Namespace namespaces[] =
    {
      {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope",      NULL},
      {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding",      NULL},
      {"xsi",      "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
      {"xsd",      "http://www.w3.org/2001/XMLSchema",          "http://www.w3.org/*/XMLSchema",          NULL},
      {NULL, NULL, NULL, NULL}
    };
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Then also add entries of the form `{"prefix", "URI"}` before the last NULL
entry to complete the table with xmlns prefix and URI bindings for your XML
project.

C++ DOM API functions                                                 {#cpp-api}
---------------------

This overview of the DOM API functions refers to the following types of
parameters and values, which are used throughout this section:

| Name   | Type and value                                                    |
| ------ | ----------------------------------------------------------------- |
| `ctx`  | `struct soap *ctx` context pointer (manages memory and IO)        |
| `ns`   | `const char *ns` XML namespace URI string or NULL                 |
| `tag`  | `const char *tag` or `const wchar_t *tag` (un)qualified tag name  |
| `utag` | `const char *utag` or `const wchar_t *utag` unqualified tag name  |
| `qtag` | `const char *qtag` or `const wchar_t *qtag` qualified tag name    |
| `patt` | (wide) string (un)qualified tag name pattern with `*` wildcard(s) |
| `text` | (wide) string                                                     |
| `node` | `const void *node` pointer to serializable C/C++ data object      |
| `type` | `SOAP_TYPE_T` type identifier of serializable C/C++ data type T   |
| `att`  | `xsd__anyAttribute att` DOM attribute node                        |
| `elt`  | `xsd__anyType elt` DOM element node                               |
| `dom`  | a DOM node (an element or an attribute node)                      |
| `val`  | bool, integer, float, or (wide) string                            |
| `pos`  | element position > 0 (XPath position numbering)                   |

The API includes functions that take wide strings and normalizes these
internally to UTF-8 encoded strings.  However, when retrieving tags and text
you will only be able to obtain UTF-8 strings.  You can convert UTF-8 strings
to wide strings that are managed by the context by using:

- `int soap_s2wchar(soap *ctx, const char *s, wchar_t **t, long minlen, long maxlen)`
  Convert string `s` with UTF-8 content to a `wchar_t` string and set `t` to
  point to this string.  If no length restrictions are enforced, pass -1 for
  `minlen` and `maxlen`.  Returns `SOAP_OK` (zero) if heap allocation
  succeeded, or an error code.

- `int soap_s2std__wstring(soap *ctx, const char *s, std::wstring *t, long minlen, long maxlen)`
  Convert string `s` with UTF-8 content to `std::wstring` pointed to by `t`.
  If no length restrictions are enforced, pass -1 for `minlen` and `maxlen`.
  Returns `SOAP_OK` (zero) if heap allocation succeeded, or an error code.

### Creating a DOM root element node                                 {#cpp-api1}

Creating a DOM node graph starts with creating the root element node using one
of the `xsd__anyType` constructors:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // 8 ways to create a root element node 'dom'
    xsd__anyType dom(ctx);                      // unnamed element node managed by context
    xsd__anyType dom(elt);                      // copy constructor (shares context and data)
    xsd__anyType dom(ctx, utag);                // element node <utag>
    xsd__anyType dom(ctx, qtag);                // element node <q:tag xmlns:q="ns">
    xsd__anyType dom(ctx, ns, utag);            // element node <utag xmlns="ns">
    xsd__anyType dom(ctx, ns, qtag);            // element node <q:tag xmlns:q="ns">
    xsd__anyType dom(ctx, ns, tag, text);       // element node as above with a text value
    xsd__anyType dom(ctx, ns, tag, node, type); // element node as above with serializable object
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The third and fourth constructors omit the `ns` parameter, which is the same as
passing a NULL `ns` parameter.

The fourth constructor is convenient to use to construct an element node that
is bound to an XML namespace by using a qualified tag name `qtag` without
specifying the namespace URI with the `ns` parameter.

To use this approach, you should define the namespace prefix in `qtag` in a
global namespace table, see [Understanding XML namespaces](#ns), and as shown
below:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // a global namespace table with {"prefix", "URI"} xmlns bindings
    struct Namespace namespaces[] =
    {
      ...
      {"q", "urn:example"},
      {NULL, NULL, NULL, NULL}
    };

    xsd__anyType dom(ctx, "q:tag");            // OK: "q" is in the namespace table
    xsd__anyType dom(ctx, "bad:tag");          // BAD: "bad" is not in the namespace table
    xsd__anyType dom(ctx, "urn:ok", "ok:tag"); // OK: "ok" is locally scoped in the DOM
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can also use multiple namespace tables and select the one you want to use
with the `soap_set_namespaces()` function:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // a local (static) namespace table with {"prefix", "URI"} xmlns bindings
    struct Namespace my_dom_namespaces[] =
    {
      ...
      {"q", "urn:example"},
      {NULL, NULL, NULL, NULL}
    };

    soap_set_namespaces(ctx, my_dom_namespaces); // use namespace table for qualified tags
    xsd__anyType dom(ctx, "q:tag");              // OK: "q" is in the namespace table
    ...
    soap_set_namespaces(ctx, namespaces);        // restore to global table
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To set or change the tag of an element, use:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    dom.set(ns, utag); // element node <utag xmlns="ns">
    dom.set(ns, qtag); // element node <q:tag xmlns:q="ns">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Assigning child nodes and values to a DOM node                   {#cpp-api2}

After creating a root element node we can start populating the root with
attributes, child elements, and values.

To assign a value to a DOM attribute node or element node `dom`, we can use the
the `xsd__anyType::set()` and `xsd__anyAttribute::set()` methods or use the
assignment operator as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // 4 ways to assign a value to an element node or to an attribute node
    dom.set(val); // set text character data from bool, integer, float, string value
    dom = val;    // same as above
    dom = att;    // copy attribute node to attribute dom node (shallow, shares data)
    dom = elt;    // copy element node to element dom node (shallow, shares data)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In addition, element nodes can be assigned serializable objects and data as
values, meaning that the object and data will be serialized in place of the
element content:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // two ways to assign serializable data to an element node 'dom'
    dom.set(node, type); // assign serializable C/C++ object or data to element node
    dom = node;          // assign serializable C/C++ object (object class must have soap_type() method)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To learn more about embedding serializable objects and data in DOM node graphs,
see [Embedding serializable objects and data in DOM element nodes](#intro-3).

To add attributes to the element node `xsd__anyType dom` we use one of the
`xsd__anyType::att()` methods as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // 4 ways to add an attribute to an element node 'dom' or extend an attribute list 'dom'
    dom.att(utag) = val;     // add attribute utag="val"
    dom.att(qtag) = val;     // add attribute q:tag="val" xmlns:q="ns"
    dom.att(ns, utag) = val; // add attribute _1:utag="val" xmlns:_1="ns" with temporary _1, _2, _3, ...
    dom.att(ns, qtag) = val; // add attribute q:tag="val" xmlns:q="ns" 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To add child elements to the element node `xsd__anyType dom` we use one of the
`xsd__anyType::elt()` methods and the bracket operator as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // 7 ways to add a child element to an element node 'dom'
    xsd__anyType& elt = dom.elt();         // add text-only child, unnamed (no tags)
    xsd__anyType& elt = dom.elt(utag);     // add child element <utag>
    xsd__anyType& elt = dom[utag];         // same as above
    xsd__anyType& elt = dom.elt(qtag);     // add child element <q:tag xmlns:q="ns">
    xsd__anyType& elt = dom[qtag];         // same as above
    xsd__anyType& elt = dom.elt(ns, utag); // add child <tag xmlns="ns">
    xsd__anyType& elt = dom.elt(ns, qtag); // add child <q:tag xmlns:q="ns">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Given the `elt` reference to a child element of the `dom` node above, you can
use this reference to build more complex node graphs by assigning attributes,
child elements, and values at increasingly deeper levels of the tree.

Because element nodes can have multiple children with the same tag name,
essentially representing an array, you can use the bracket operator to index
the child elements at their relative position among its siblings that have the
same tag name.  Position indexing starts at one (i.e. `[1]` XPath style) and
child elements are added up to the highest position index used:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // add 'array' of three child elements to an element node 'dom'
    xsd__anyType& elt = dom[tag]; // add child (using one of the methods above)
    elt[1] = val;                 // assign val to first child element <tag>
    elt[3] = val;                 // add children <tag> at positions 2 and 3, assign val to the 3rd
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note that `elt[1]` refers to `elt` itself, because indexing starts at 1 (as in
XPath).  Thus, position index `[1]` is optional to use.

You can combine these operations and methods in various ways to create more
complex DOM node graphs.  Let's illustrate this with an example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    xsd__anyType dom(ctx, "menu");
    dom.att("id") = 7;
    dom.att("key") = L"⌘F";
    dom["popup"]["menuitem"][1].att("value")   = "New";
    dom["popup"]["menuitem"][1].att("onclick") = "CreateNewDoc()";
    dom["popup"]["menuitem"][2].att("value")   = "Open";
    dom["popup"]["menuitem"][2].att("onclick") = "OpenDoc()";
    dom["popup"]["menuitem"][3].att("value")   = "Close";
    dom["popup"]["menuitem"][3].att("onclick") = "CloseDoc()";
    std::cout << dom;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When executed, this code emits the following XML output on the terminal:

    <menu id="7" key="⌘F">
      <popup>
        <menuitem value="New" onclick="CreateNewDoc()"/>
        <menuitem value="Open" onclick="OpenDoc()"/>
        <menuitem value="Close" onclick="CloseDoc()"/>
      </popup>
    </menu>

The `xsd__anyAttribute` DOM attribute node constructors are identical to the
`xsd__anyType` DOM element node constructors and can be used to create an
attribute node or to create a list of attributes.

As an alternative to creating attributes and elements in place, you can also
construct attribute and element nodes and add them to other element nodes by
using the `xsd__anyType::add()` method.  For example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // add an attribute 'att' and an element node 'elt' to another element node 'dom'
    xsd__anyAttribute att(ctx, NULL, "id", "7"); // id attribute
    xsd__anyType elt(ctx, "popup");              // popup element
    dom.add(att).add(elt);                       // add id attribute and popup as child element
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To create a list of two attributes and add them to an element node `dom`:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // add a list of attributes 'atts' to an element node 'dom'
    xsd__anyAttribute atts(ctx);
    atts.att("id") = 7;
    atts.att("key") = L"⌘F";
    dom.adds(atts);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Finally, you can use domcpp to generate DOM construction code from a sample XML
document.

### Matching and retrieving DOM node values and properties           {#cpp-api3}

Given a DOM node graph parsed from an XML document, we can match its tag names
and use methods to retrieve values, attribuets, child elements, and properties.

Given a DOM attribute node `xsd__anyAttribute dom` or element node
`xsd__anyType dom`, you can use the following methods to match and retrieve the
node's namespace and tag name:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    bool b = dom.match(patt);     // true if tag matches pattern
    bool b = dom.match(ns, patt); // true if ns and tag match the patterns

    const char *s = dom.ns();     // namespace URI string or NULL if none
    const char *t = dom.tag();    // (un)qualified tag name string, NULL if unnamed
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Given a DOM attribute node `xsd__anyAttribute dom` or element node
`xsd__anyType dom`, the following methods can be used to retrieve the value of
the node's character data content:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    bool        b = dom.is_true();    // true if text is "true" or "1"
    bool        b = dom.is_false();   // true if text is "false" or "0"
    LONG64      n = dom.get_int();    // 64 bit integer value of text, or 0
    double      x = dom.get_double(); // double float value of text, or NaN
    const char *t = dom.get_text();   // text string in UTF-8, or NULL if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can also cast an element or attribute node to a bool, an int, a double, or
a string to obtain its value.  For example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    int         n = dom; // integer value cast from text in DOM node, or 0
    const char *t = dom; // text string in UTF-8 of the DOM node, or NULL if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Element nodes may contain deserialized objects and data as values, which can be
retrieved with one of two methods:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    T *node = (T*)dom.get_node(SOAP_TYPE_T); // get deserialized C/C++ object or data of type T, NULL if none
    int type = dom.get_type(&node);          // get deserialized C/C++ object or data of any type, 0 if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To learn more about embedding serializable objects and data in DOM node graphs,
see [Embedding serializable objects and data in DOM element nodes](#intro-3).

Given a DOM element node `xsd__anyType dom`, one of the following methods can
be used to retrieve an attribute by its unqualfied tag name (default
namespace), by qualified tag name (assuming the prefix is defined in the
namespace table), or by namespace and unqualified tag name:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    xsd__anyAttribute *att = dom.att_get(utag);     // get attribute utag, NULL if none
    xsd__anyAttribute *att = dom.att_get(qtag);     // get attribute q:tag
    xsd__anyAttribute *att = dom.att_get(ns, utag); // get attribute utag in namespace ns, NULL if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The second form is convenient to use to retrieve attributes in namespaces by
using a qualified tag name `qtag` without having to specify the `ns` namespace
URI parameter.  This requires the namespace prefix used in `qtag` to be defined
in the global namespace table.

Given a DOM element node `xsd__anyType dom`, one of the following methods can
be used to retrieve a child element by its unqualfied tag name (default
namespace), by qualified tag name (assuming the prefix is defined in the
namespace table), or by namespace and unqualified tag name:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    xsd__anyType *elt = dom.elt_get();         // get first text-only child element, NULL if none
    xsd__anyType *elt = dom.elt_get(utag);     // get first child element <utag>, NULL if none
    xsd__anyType *elt = dom.elt_get(qtag);     // get first child element <q:tag xmlns:q="ns">, NULL if none
    xsd__anyType *elt = dom.elt_get(ns, utag); // get first child element <s:utag xmlsn:s="ns">, NULL if none

    elt = elt.get_next();                      // get next matching child element, NULL if none
    elt = elt.get_nth(pos);                    // get matching child element at pos counting from 1, NULL if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `get_next()` method can be used in loops to iterate over child elements
with the same namespace and tag, as if traversing an array.  For example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // iterate over <menuitem> child elements of element node 'dom'
    for (xsd__anyType *it = dom.elt_get("menuitem"); it; it = it->get_next())
      ...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To obtain various properties of an `xsd__anyType dom` element node:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    xsd__anyType *elt = dom.parent(); // parent node, or NULL when root
    size_t          n = dom.depth();  // depth from the root node (0 is root)
    size_t          n = dom.len();    // number of siblings that have the same tag name
    size_t        pos = dom.nth();    // node is at pos with the same tag name as some siblings, or 0 if alone
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following invariants hold (assuming that pointer dereferences (`->`) are
verified and valid):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    dom[tag].match(tag)                   == dom.elt(tag).match(tag) == true
    dom[tag].parent()                     == dom.elt(tag).parent()   == dom
    dom[tag].tag()                        == dom.elt(tag).tag()      == tag

    dom.elt(ns, tag).match(ns, tag)       == dom
    dom.elt(ns, tag).parent()             == dom
    dom.elt(ns, tag).ns()                 == ns
    dom.elt(ns, tag).tag()                == tag

    dom.att(tag).match(tag)               == true
    dom.att(ns, tag).match(ns, tag)       == true
    dom.att(ns, tag).ns()                 == ns
    dom.att(ns, tag).tag()                == tag

    dom.set(val)                          == val  // by casting to bool, int, float, string

    dom.elt_get(tag)->parent()            == dom
    dom.elt_get(tag)->depth()             == dom.depth() + 1
    dom.elt_get(tag)->nth()               <= dom.elt_get(tag)->len()
    dom.elt_get(tag)->nth()               == 0 if dom.elt_get(tag)->len() == 1
    dom.elt_get(tag)->nth()               == 1 if dom.elt_get(tag)->len() >  1
    dom.elt_get(tag)->get_next()->nth()   == 2
    dom.elt_get(tag)->get_nth(pos)->nth() == pos
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Traversing a DOM node graph                                      {#cpp-api4}

Given a DOM node graph, we can traverse its attribute list and its child
elements by using the iterators `xsd__anyAttribute::iterator` and
`xsd__anyType::iterator`, respectively:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // print attribute tags
    for (xsd__anyAttribute::iterator it = dom.att_begin(); it != dom.att_end(); ++it)
      std::cout << "@" << it->tag() << std::endl;

    // print child element tags
    for (xsd__anyType::iterator it = dom.elt_begin(); it != dom.elt_end(); ++it)
      std::cout << "<" << it->tag() << ">" << std::endl;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can also traverse the entire node graph below a certain DOM element node
`xsd__anyType dom` in depth-first order starting with the current `dom` node:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // print all element tags in depth-first order
    for (xsd__anyType::iterator it = dom.begin(); it != dom.end(); ++it)
      std::cout << "<" << it->tag() << "> at depth " << it->depth() << std::endl;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Searching a DOM node graph                                       {#cpp-api5}

Given a DOM node graph, we can search its attribute list and its child elements
by using a pattern with wildcards `*` to match namespace and/or tag names,
similar to XPath `*` pattern matching:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // print attribute tags that match *:id (* matches any namespace, including default)
    for (xsd__anyAttribute::iterator it = dom.att_find("*:id"); it != dom.att_end(); ++it)
      std::cout << "@" << it->tag() << std::endl;

    // print element tags in namespace "urn:one" (assuming "x" is "urn:one" in the namespace table)
    for (xsd__anyType::iterator it = dom.elt_find("x:*"); it != dom.elt_end(); ++it)
      std::cout << "<" << it->tag() << ">" << std::endl;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The above assumes that a namespace table is used that defines namespace `x`.
Alternatively, you can specify namespace parameters that can be NULL or `"*"` to
match any namespace URI (NULL can be used in place of a `"*"` pattern):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // print attribute tags that match *:id
    for (xsd__anyAttribute::iterator it = dom.att_find("*", "id"); it != dom.att_end(); ++it)
      std::cout << "@" << it->tag() << std::endl;

    // print element tags in namespace "urn:one"
    for (xsd__anyType::iterator it = dom.elt_find("urn:one", "*"); it != dom.elt_end(); ++it)
      std::cout << "<" << it->tag() << "<" << std::endl;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Patterns for namespaces and tags are not restricted to wildcards `*`.  You can
specify parts of a namespace URI or tag name and use one or more `*` to match
the rest.

You can also search the entire node graph below a certain DOM element node in
depth-first order starting with the current node:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // find all element nodes with attribute "id" deep in the node graph
    for (xsd__anyType::iterator it = dom.find("@*:id"); it != dom.end(); ++it)
      std::cout << "element " << it->tag() << " has an @id=" << it->att_get("*:id")->get_text() << std::endl;

    // print all element tags in namespace "urn:one"
    for (xsd__anyType::iterator it = dom.find("urn:one", "*"); it != dom.end(); ++it)
      std::cout << "<" << it->tag() << ">" << std::endl;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### XML DOM parsing and writing from/to streams                      {#cpp-api6}

To parse XML from a stream into a DOM node graph you can use the `>>` operator
on an input stream and a DOM element node:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // create new context and parse XML from 'cin' into 'dom'
    soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    xsd__anyType dom(ctx);
    std::cin >> dom;
    if (dom.soap->error)
      ... // check for IO end parse errors
    ...
    soap_destroy(ctx);
    soap_end(ctx);
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To write a DOM node graph in XML to a stream, you can use the `<<` operator on
an output stream and a DOM element node:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // create new context and create a 'dom', write its XML to 'cout'
    soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    xsd__anyType dom(ctx, "store");
    ...
    std::cout << dom << std::endl;
    if (dom.soap->error)
      ... // check for IO errors
    ...
    soap_destroy(ctx);
    soap_end(ctx);
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can also parse XML from a string into a DOM node graph by using a
`std::istringstream` object:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // create new context and parse XML from a string into 'dom'
    soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    std::istringstream in;
    in.str("<store><book title=\"Sayings of the Century\"/></store>");
    xsd__anyType dom(ctx);
    in >> dom;                      // parse XML into DOM
    if (dom.soap->error)
      ...        // check for IO and parse errors
    ...
    soap_destroy(ctx);
    soap_end(ctx);
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Likewise, you can write a DOM node graph in XML to a string by using a
`std::ostringstream` object:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    // create new context and create a 'dom', write its XML to a string
    soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    std::ostringstream out;
    xsd__anyType dom(ctx, "store");
    ...
    out << dom;                     // convert DOM to XML string in UTF-8
    ...
    soap_destroy(ctx);
    soap_end(ctx);
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is also possible to send and receive XML over HTTP as REST operations as was
illustrated in the introduction.  To make REST HTTP POST, GET, OUT, and DELETE
calls, use:

- `int soap_dom_call(soap *ctx, const char *URL, const char *action, const xsd__anyType *in, xsd__anyType *out)`
  Make a POST, GET, PUT, DELETE call.  Connect to endpoint `URL` with HTTP
  SOAPAction `action` (or NULL) and send request `in` to server and receive
  response `out`.  Returns `SOAP_OK` (zero) or an error code.  POST method:
  pass both `in` and `out`.  GET method: pass a NULL to `in`.  PUT method: pass
  a NULL to `out`.  DELETE method: pass both NULL to `in` and `out`.

This function is overloaded to accept references to the `in` and `out`
parameters in C++.

C XML DOM API                                                               {#c}
=============

XML is represented as a DOM node graph internally consisting of values (text
strings of character data in UTF-8), attribute nodes with tag name and optional
namespace URI, and element nodes with optional tag names  and optional
namespace URI.  Tag names are stored in strings of UTF-8.  Tag names can be
qualified of the form `q:tag` or unqualified.  An element tag name that is
NULL represents a text-only node, which will only be present in mixed content
of elements and text character data (as in XHTML markup).

XML namespace handling is "smart" in the gSOAP DOM API: the DOM engine matches
and stores XML with namespace URIs to ensure that a prefix qualifier is always
locally bound to a namespace URI in the node graph.  Furthermore, you can use
qualified tags when constructing a DOM node instead of the full namespace URI,
but only if the prefix and URI are defined in the namespace table (global
`struct Namespace namesapces[]`.  When working with wsdl2h and soapcpp2 you
should include the soapcpp2-generated `.nsmap` file with namespace bindings
that are applicable to your XML tags.

List of C files                                                       {#c-files}
---------------

The following files located in the package under `gsoap` are required to use
the C DOM API:

- `stdsoap2.h`:         gSOAP engine
- `stdsoap2.c`:         gSOAP engine
- `dom.c`:              DOM parser and DOM C/C++ API implementation
- `import/dom.h`:       DOM import for data bindings in a .h file for soapcpp2
                        (do not #include this file in your project builds)
                        Use soapcpp2 `-Iimport` to specify import path when
                        `dom.h` is imported in a header file for soapcpp2.

The gSOAP header file `dom.h` declares the DOM for use in data bindings and
should generally be imported with `#import` in gSOAP header files for the
soapcpp2 tool.

You can also run soapcpp2 directly on `import/dom.h` for DOM-only projects.
This generates `soapStub.h`, `soapH.h` and `soapC.cpp`.  To auto-generate these
files, execute:

    soapcpp2 -c -CSL import/dom.h

Then compile and link the `dom.c` files listed above with the auto-generated
`soapC.c` and `stdsoap2.c`:

    cc -I../.. -o myapp myapp.c soapC.c ../../dom.c ../../stdsoap2.c

Instead of `stdsoap2.c` you can link `-lgsoap.a` when installed by the gSOAP
package.  Or link `-lgsoapssl.a` to get both `stdsoap2.c` and `dom.c` with
OpenSSL enabled for HTTPS:

    cc -DWITH_OPENSSL -I../.. -o myapp myapp.c soapC.c -lgsoapssl -lssl -lcrypto

Note that we compile with `-DWITH_OPENSSL` and link `-lssl`, and `-lcrypto`.

Because XML namespaces are required except for the most simple plain XML
applications, you should include the generated `.nsmap` file:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    #include "soap.nsmap"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Or define your own namespace table.  For example, at a minimum you want a table
with SOAP and XSD bindings:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"
    struct Namespace namespaces[] =
    {
      {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope",      NULL},
      {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding",      NULL},
      {"xsi",      "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
      {"xsd",      "http://www.w3.org/2001/XMLSchema",          "http://www.w3.org/*/XMLSchema",          NULL},
      {NULL, NULL, NULL, NULL}
    };
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Then also add entries of the form `{"prefix", "URI"}` before the last NULL
entry to complete the table with xmlns prefix and URI bindings for your XML
project.

C DOM API functions                                                     {#c-api}
-------------------

This overview of the DOM API functions refers to the following types of
parameters and values, which are used throughout this section:

| Name   | Type and value                                                    |
| ------ | ----------------------------------------------------------------- |
| `ctx`  | `struct soap *ctx` context pointer (manages memory and IO)        |
| `ns`   | `const char *ns` XML namespace URI string or NULL                 |
| `tag`  | `const char *tag` or `const wchar_t *tag` (un)qualified tag name  |
| `utag` | `const char *utag` or `const wchar_t *utag` unqualified tag name  |
| `qtag` | `const char *qtag` or `const wchar_t *qtag` qualified tag name    |
| `patt` | (wide) string (un)qualified tag name pattern with `*` wildcard(s) |
| `text` | (wide) string                                                     |
| `node` | `const void *node` pointer to serializable C/C++ data object      |
| `type` | `SOAP_TYPE_T` type identifier of serializable C/C++ data type T   |
| `att`  | `xsd__anyAttribute *att` DOM attribute node pointer               |
| `elt`  | `xsd__anyType *elt` DOM element node pointer                      |
| `dom`  | a DOM node (a pointer to an element or an attribute node)         |
| `val`  | bool, integer, float, or (wide) string                            |
| `pos`  | element position > 0 (XPath position numbering)                   |

The API includes functions that take wide strings and normalizes these
internally to UTF-8 encoded strings.  However, when retrieving tags and text
you will only be able to obtain UTF-8 strings.  You can convert UTF-8 strings
to wide strings that are managed by the context by using:

- `int soap_s2wchar(struct soap *ctx, const char *s, wchar_t **t, long minlen, long maxlen)`
  Convert string `s` with UTF-8 content to a `wchar_t` string and set `t` to
  point to this string.  If no length restrictions are enforced, pass -1 for
  `minlen` and `maxlen`.  Returns `SOAP_OK` (zero) if heap allocation
  succeeded, or an error code.

### Creating a DOM root element node                                   {#c-api1}

Creating a DOM node graph starts with creating the root element node using one
of the `xsd__anyType` allocators:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // 4 ways to create a root element node pointer 'dom'
    xsd__anyType *dom = soap_elt_new(ctx, NULL, utag); // element node <utag>
    xsd__anyType *dom = soap_elt_new(ctx, NULL, qtag); // element node <q:tag xmlns:q="ns">
    xsd__anyType *dom = soap_elt_new(ctx, ns, utag);   // element node <utag xmlns="ns">
    xsd__anyType *dom = soap_elt_new(ctx, ns, qtag);   // element node <q:tag xmlns:q="ns">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For wide string tags, use `soap_elt_new_w(ctx, ns, tag)`.  All C API functions
that support wide strings end in `_w` by convention.

The second function call in the list is convenient to use to construct an
element node that is bound to an XML namespace by using a qualified tag name
`qtag` while specifying the namespace URI as NULL.

To use this approach, you should define the namespace prefix in `qtag` in a
global namespace table, see [Understanding XML namespaces](#ns), and as shown
below:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // a global namespace table with {"prefix", "URI"} xmlns bindings
    struct Namespace namespaces[] =
    {
      ...
      {"q", "urn:example"},
      {NULL, NULL, NULL, NULL}
    };

    xsd__anyType *dom = soap_elt_new(ctx, NULL, "q:tag");      // OK: "q" is in the namespace table
    xsd__anyType *dom = soap_elt_new(ctx, NULL, "bad:tag");    // BAD: "bad" is not in the namespace table
    xsd__anyType *dom = soap_elt_new(ctx, "urn:ok", "ok:tag"); // OK: "ok" is locally scoped in the DOM
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can also use multiple namespace tables and select the one you want to use
with the `soap_set_namespaces()` function:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // a local (static) namespace table with {"prefix", "URI"} xmlns bindings
    struct Namespace my_dom_namespaces[] =
    {
      ...
      {"q", "urn:example"},
      {NULL, NULL, NULL, NULL}
    };

    soap_set_namespaces(ctx, my_dom_namespaces);          // use namespace table for qualified tags
    xsd__anyType *dom = soap_elt_new(ctx, NULL, "q:tag"); // OK: "q" is in the namespace table
    ...
    soap_set_namespaces(ctx, namespaces);                 // restore to global table
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To set or change the tag of an element, use:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    soap_elt_set(dom, ns, utag); // element node <utag xmlns="ns">
    soap_elt_set(dom, ns, qtag); // element node <q:tag xmlns:q="ns">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Assigning child nodes and values to a DOM node                     {#c-api2}

After creating a root element node we can start populating the root with
attributes, child elements, and values.

To assign a value to a DOM element node `dom` you can use one the the following
functions:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // 6 ways to assign a value to an element node 'dom'
    soap_elt_bool(dom, val);   // set text to boolean "false" or "true"
    soap_elt_int(dom, val);    // set text to integer (64 bit)
    soap_elt_double(dom, val); // set text to (double) float
    soap_elt_text(dom, val);   // set text with UTF-8 string content
    soap_elt_text_w(dom, val); // set text with wide string content
    soap_elt_copy(dom, elt);   // copy element node to element dom node (shallow, shares data)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can use similar functions for DOM attribute nodes, altough you do not need
these to populate DOM element nodes because it is easier to use the
`soap_att()` function shown further below:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // 6 ways to assign a value to an attribute node 'dom'
    soap_att_bool(dom, val);   // set text to boolean "false" or "true"
    soap_att_int(dom, val);    // set text to integer (64 bit)
    soap_att_double(dom, val); // set text to (double) float
    soap_att_text(dom, val);   // set text with UTF-8 string content
    soap_att_text_w(dom, val); // set text with wide string content
    soap_att_copy(dom, elt);   // copy attribute node to attribute dom node (shallow, shares data)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In addition, element nodes can be assigned serializable objects and data as
values, meaning that the object and data will be serialized in place of the
element content:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // assign serializable data to an element node 'dom'
    soap_elt_node(dom, node, type); // assign serializable C data to element node
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To learn more about embedding serializable objects and data in DOM node graphs,
see [Embedding serializable objects and data in DOM element nodes](#intro-3).

To add attributes to an element node `dom` you can use one of the following
functions (use `soap_att_w` for wide string tags):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // 4 ways to add an attribute to an element node 'dom' or extend an attribute list 'dom'
    xsd__anyAttribute *att = soap_att(dom, NULL, utag); // add attribute utag="val"
    xsd__anyAttribute *att = soap_att(dom, NULL, qtag); // add attribute q:tag="val" xmlns:q="ns"
    xsd__anyAttribute *att = soap_att(dom, ns, utag);   // add attribute _1:utag="val" xmlns:_1="ns" with temporary _1, _2, _3, ...
    xsd__anyAttribute *att = soap_att(dom, ns, qtag);   // add attribute q:tag="val" xmlns:q="ns" 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can then set the value of the attribute `att` as was shown earlier.

To add child elements to the element node `dom` we use one of the following
functions (use `soap_elt_w` for wide string tags):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // 5 ways to add a child element to an element node 'dom'
    xsd__anyType *elt = soap_elt(dom, NULL, NULL); // add text-only child, unnamed (no tags)
    xsd__anyType *elt = soap_elt(dom, NULL, utag); // add child element <utag>
    xsd__anyType *elt = soap_elt(dom, NULL, qtag); // add child element <q:tag xmlns:q="ns">
    xsd__anyType *elt = soap_elt(dom, ns, utag);   // add child <tag xmlns="ns">
    xsd__anyType *elt = soap_elt(dom, ns, qtag);   // add child <q:tag xmlns:q="ns">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Given the `elt` pointer to a child element node of the `dom` node, you can use
the pointer to build more complex node graphs by assigning attributes, child
elements, and values at increasingly deeper levels of the tree.

Because element nodes can have multiple children with the same tag name,
essentially representing an array, you can index the child elements at their
relative position among its siblings that have the same tag name.  Position
indexing starts at one (i.e. XPath style) and child elements are added up to
the highest position index used:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // add 'array' of three child elements to an element node 'dom'
    xsd__anyType *elt = soap_elt(dom, NULL, tag); // add child (using one of the functions above)
    soap_elt_int(soap_nth(elt, 1), val);          // assign val to first child element <tag>
    soap_elt_int(soap_nth(elt, 3), val);          // add children <tag> at positions 2 and 3, assign val to the 3rd
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The combination `soap_nth(soap_elt(dom, ns, tag), pos)` can be shortend to
`soap_nth_elt(dom, ns, tag, pos)`.

Note that `soap_nth(elt, 1)` refers to `elt` itself, because indexing starts
at 1 (as in XPath).

You can combine these operations in various ways to create more complex DOM
node graphs.  Let's illustrate this with an example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    xsd__anyType *dom = soap_elt_new(ctx, NULL, "menu");
    soap_att_int(soap_att(dom, NULL, "id"), 7);
    soap_att_text_w(soap_att(dom, NULL, "value"), "⌘F");
    {
      xsd__anyType *dom_popup = soap_elt(dom, NULL, "popup");
      {
        xsd__anyType *dom_popup_menuitem = soap_nth_elt(dom_popup, NULL, "menuitem", 1);
        soap_att_text(soap_att(dom_popup_menuitem, NULL, "value"), "New");
        soap_att_text(soap_att(dom_popup_menuitem, NULL, "onclick"), "CreateNewDoc()");
      }
      {
        xsd__anyType *dom_popup_menuitem = soap_nth_elt(dom_popup, NULL, "menuitem", 2);
        soap_att_text(soap_att(dom_popup_menuitem, NULL, "value"), "Open");
        soap_att_text(soap_att(dom_popup_menuitem, NULL, "onclick"), "OpenDoc()");
      }
      {
        xsd__anyType *dom_popup_menuitem = soap_nth_elt(dom_popup, NULL, "menuitem", 3);
        soap_att_text(soap_att(dom_popup_menuitem, NULL, "value"), "Close");
        soap_att_text(soap_att(dom_popup_menuitem, NULL, "onclick"), "CloseDoc()");
      }
    }
    soap_write_xsd__anyType(ctx, dom);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When executed, this code emits the following XML output on the terminal:

    <menu id="7" key="⌘F">
      <popup>
        <menuitem value="New" onclick="CreateNewDoc()"/>
        <menuitem value="Open" onclick="OpenDoc()"/>
        <menuitem value="Close" onclick="CloseDoc()"/>
      </popup>
    </menu>

The `xsd__anyAttribute` DOM attribute node allocation functions are identical
to the `xsd__anyType` DOM element node allocation functions and can be used to
create an attribute node or to create a list of attributes.

As an alternative to creating attributes and elements in place, you can also
construct attribute and element nodes and add them to other element nodes:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // add an attribute 'att' and an element node 'elt' to another element node 'dom'
    xsd__anyAttribute *att = soap_att_new(ctx, NULL, "id");
    xsd__anyType *elt = soap_elt_new(ctx, NULL, "popup");
    soap_att_int(att, 7);
    soap_add_att(dom, att);
    soap_add_elt(dom, elt);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To create a list of two attributes and add them to an element node `dom`:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // add a list of attributes 'atts' to an element node 'dom'
    xsd__anyAttribute *atts = soap_att_new(ctx, NULL, NULL);
    soap_att_int(soap_att_add(atts, NULL, "id"), 7);
    soap_att_text_w(soap_att_add(atts, NULL, "key"), L"⌘F");
    soap_add_atts(dom, atts);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Finally, you can use domcpp to generate DOM construction code from a sample XML
document.

### Matching and retrieving DOM node values and properties             {#c-api3}

Given a DOM node graph parsed from an XML document, we can match its tag names
and use functions to retrieve values, attribuets, child elements, and
properties.

Given a DOM element node `dom`, you can use the following functions to match
and retrieve the node's namespace and tag name:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    int b = soap_elt_match(dom, NULL, patt); // true if tag matches pattern
    int b = soap_elt_match(dom, ns, patt);   // true if ns and tag match the patterns

    const char *s = soap_elt_get_ns(dom));   // namespace URI string or NULL if none
    const char *t = soap_elt_get_tag(dom);   // (un)qualified tag name string, NULL if unnamed
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Similar for attribute node `dom`:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    int b = soap_att_match(dom, NULL, patt); // true if tag matches pattern
    int b = soap_att_match(dom, ns, patt);   // true if ns and tag match the patterns

    const char *s = soap_att_get_ns(dom));   // namespace URI string or NULL if none
    const char *t = soap_att_get_tag(dom);   // (un)qualified tag name string, NULL if unnamed
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Given a DOM element node `dom`, the following functions can be used to retrieve
the value of the node's character data content:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    int         b = soap_elt_is_true(dom);    // true if text is "true" or "1"
    int         b = soap_elt_is_false(dom);   // true if text is "false" or "0"
    LONG64      n = soap_elt_get_int(dom));   // 64 bit integer value of text, or 0
    double      x = soap_elt_get_double(dom); // double float value of text, or NaN
    const char *t = soap_elt_get_text(dom));  // text string in UTF-8, or NULL if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Similar for attribute node `dom`:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    int         b = soap_att_is_true(dom);    // true if text is "true" or "1"
    int         b = soap_att_is_false(dom);   // true if text is "false" or "0"
    LONG64      n = soap_att_get_int(dom));   // 64 bit integer value of text, or 0
    double      x = soap_att_get_double(dom); // double float value of text, or NaN
    const char *t = soap_att_get_text(dom));  // text string in UTF-8, or NULL if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Element nodes may contain deserialized objects and data as values, which can be
retrieved with one of two methods:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    T *node = (T*)soap_elt_get_node(dom, SOAP_TYPE_T); // get deserialized C data of type T, NULL if none
    int type = soap_elt_get_type(dom, &node);          // get deserialized C data of any type, 0 if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To learn more about embedding serializable objects and data in DOM node graphs,
see [Embedding serializable objects and data in DOM element nodes](#intro-3).

Given a DOM element node `dom`, one of the following methods can be used to
retrieve an attribute by its unqualfied tag name (has no namespace), by
qualified tag name (assuming the prefix is defined in the namespace table), or
by namespace and unqualified tag name:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    xsd__anyAttribute *att = soap_att_get(dom, NULL, utag); // get attribute utag, NULL if none
    xsd__anyAttribute *att = soap_att_get(dom, NULL, qtag); // get attribute q:tag
    xsd__anyAttribute *att = soap_att_get(dom, ns, utag);   // get attribute utag in namespace ns, NULL if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The second form is convenient to use to retrieve attributes in namespaces by
using a qualified tag name `qtag` without having to specify the `ns` namespace
URI parameter.  This requires the namespace prefix used in `qtag` to be defined
in the global namespace table.

Given a DOM element node `dom`, one of the following functions can be used to
retrieve a child element by its unqualfied tag name (has no namespace), by
qualified tag name (assuming the prefix is defined in the namespace table), or
by namespace and unqualified tag name:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    xsd__anyType *elt = soap_elt_get(dom, NULL, NULL); // get first text-only child element, NULL if none
    xsd__anyType *elt = soap_elt_get(dom, NULL, utag); // get first child element <utag>, NULL if none
    xsd__anyType *elt = soap_elt_get(dom, NULL, qtag); // get first child element <q:tag xmlns:q="ns">, NULL if none
    xsd__anyType *elt = soap_elt_get(dom, ns, utag);   // get first child element <s:tag xmlsn:s="ns">, NULL if none

    elt = soap_elt_get_next(elt);                      // get next matching child element, NULL if none
    elt = soap_elt_get_nth(elt, pos);                  // get matching child element at pos counting from 1, NULL if none
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `soap_elt_get_next(elt)` function can be used in loops to iterate over
child elements with the same namespace and tag, as if traversing an array.  For
example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // iterate over <menuitem> child elements of element node 'dom'
    xsd__anyType *it;
    for (it = soap_elt_get(dom, NULL, "menuitem"); it; it = soap_elt_get_next(it))
      ...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To obtain various properties of a `dom` element node:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    xsd__anyType *elt = soap_elt_parent(dom); // parent node, or NULL when root
    size_t          n = soap_elt_depth(dom);  // depth from the root node (0 is root)
    size_t          n = soap_elt_len(dom);    // number of siblings that have the same tag name
    size_t        pos = soap_elt_nth(dom);    // node is at pos with the same tag name as some siblings, or 0 if alone
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following invariants hold (assuming that `soap_elt_get(dom, ns, tag)` is
not NULL and thus `dom` has a child element that matches namespace `ns` and `tag`):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    soap_elt_match(soap_elt(dom, NULL, tag), NULL, tag)             == true (nonzero)
    soap_elt_parent(soap_elt(dom, NULL, tag))                       == dom
    soap_elt_get_tag(soap_elt(dom, NULL, tag))                      == tag

    soap_elt_match(soap_elt(dom, ns, tag), ns, tag)                 == true (nonzero)
    soap_elt_parent(soap_elt(dom, ns, tag))                         == dom
    soap_elt_get_ns(soap_elt(dom, ns, tag))                         == ns
    soap_elt_get_tag(soap_elt(dom, ns, tag))                        == tag

    soap_att_match(soap_att(dom, ns, tag), ns, tag)                 == true (nonzero)
    soap_att_get_ns(soap_att(dom, ns, tag))                         == ns
    soap_att_get_tag(soap_att(dom, ns, tag))                        == tag

    soap_elt_get_int(soap_elt_int(dom, val))                        == val  // also holds for bool, double, string
    soap_att_get_int(soap_att_int(dom, val))                        == val  // also holds for bool, double, string

    soap_elt_parent(soap_elt_get(dom, ns, tag))                     == dom
    soap_elt_depth(soap_elt_get(dom, ns, tag))                      == soap_elt_depth(dom) + 1
    soap_elt_nth(soap_elt_get(dom, ns, tag))                        <= soap_elt_len(soap_elt_get(dom, ns, tag))
    soap_elt_nth(soap_elt_get(dom, ns, tag))                        == 0 if soap_elt_len(soap_elt_get(dom, ns, tag)) == 1
    soap_elt_nth(soap_elt_get(dom, ns, tag))                        == 1 if soap_elt_len(soap_elt_get(dom, ns, tag)) >  1
    soap_elt_nth(soap_elt_get_next(soap_elt_get(dom, ns, tag)))     == 2
    soap_elt_nth(soap_elt_get_nth(soap_elt_get(dom, ns, tag), pos)) == pos
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Traversing a DOM node graph                                        {#c-api4}

Given a DOM node graph `dom`, we can traverse its attribute list
`xsd__anyType::atts` and its child elements `xsd__anyType::elts` as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // print attribute tags
    xsd__anyAttribute *it;
    for (it = dom->atts; it; it = it->next)
      printf("@%s\n", soap_att_get_tag(it));

    // print child element tags
    xsd__anyType *it;
    for (it = dom->elts; it; it = it->next)
      printf("<%s>\n", soap_elt_get_tag(it));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can also traverse the entire node graph below a certain DOM element node
`dom` in depth-first order starting with the current `dom` and stepping through
all element nodes with `soap_dom_next_element(elt, end)` where `end` is a
pointer to the ending element node (exclusive), usually the starting node of
the graph traversal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // print all element tags in depth-first order
    xsd__anyType *it;
    for (it = dom; it; it = soap_dom_next_element(it, dom))
      printf("<%s> at depth %zd\n", soap_elt_get_tag(it), soap_elt_depth(it));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Searching a DOM node graph                                         {#c-api5}

Given a DOM node graph, we can search its attribute list and its child elements
by using a pattern with wildcards `*` to match namespace and/or tag names,
similar to XPath `*` pattern matching:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // print attribute tags that match *:id (* matches any namespace, including default)
    xsd__anyAttribute *it;
    for (it = soap_att_find(dom, NULL, "*:id"); it; it = soap_att_find_next(it, NULL, "*:id"))
      printf("@%s\n", soap_att_get_tag(it));

    // print element tags in namespace "urn:one" (assuming "x" is "urn:one" in the namespace table)
    xsd__anyType *it;
    for (it = soap_elt_find(dom, NULL, "x:*"); it; it = soap_elt_find_next(it, NULL, "x:*"))
      printf("<%s>\n", soap_elt_get_tag(it));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The above assumes that a namespace table is used that defines namespace `x`.
Alternatively, you can specify namespace parameters that can be NULL or `"*"` to
match any namespace URI (NULL can be used in place of a `"*"` pattern):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // print attribute tags that match *:id
    xsd__anyAttribute *it;
    for (it = soap_att_find(dom, "*", "id"); it; it = soap_att_find_next(it, "*", "id"))
      printf("@%s\n", soap_att_get_tag(it));

    // print element tags in namespace "urn:one"
    xsd__anyType *it;
    for (it = soap_elt_find(dom, "urn:one", "*"); it; it = soap_elt_find_next(it, "urn:one", "*"))
      printf("<%s>\n", soap_elt_get_tag(it));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Patterns for namespaces and tags are not restricted to wildcards `*`.  You can
specify parts of a namespace URI or tag name and use one or more `*` to match
the rest.

You can also search the entire node graph below a certain DOM element node in
depth-first order starting with the current node:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // find all element nodes with attribute "id" deep in the node graph
    xsd__anyType *it;
    for (it = soap_dom_find(dom, NULL, "@*:id"); it; it = soap_dom_find_next(it, dom, NULL, "@*:id")
      printf("element <%s> has an @id=%s\n", soap_elt_get_tag(it), soap_att_get_text(soap_att_find(it, NULL, "*:id")));

    // print all element tags in namespace "urn:one"
    xsd__anyType *it;
    for (it = soap_dom_find(dom, "urn:one", "*"); it; it = soap_dom_find_next(it, dom, "urn:one", "*"))
      printf("<%s>\n", soap_elt_get_tag(it));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### XML DOM parsing and writing from/to streams                        {#c-api6}

Reading and writing XML from/to files, streams and string buffers is done via
the managing context by setting one of the following context members that
control IO sources and sinks:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    ctx->recvfd = fd; // an int file descriptor to read from (0 by default)
    ctx->sendfd = fd; // an int file descriptor to write to (1 by default)
    ctx->is = cs;     // C only: a const char* string to read from (soap->is will advance)
    ctx->os = &cs;    // C only: pointer to a const char*, will be set to point to the string output
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To parse XML from a file descriptor `ctx->recvfd` into a DOM node graph you can
use to soapcpp2 auto-generated `soap_read_xsd__anyType(ctx, dom)` function:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // create new context and parse XML from 'cin' into 'dom'
    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    xsd__anyType *dom = soap_elt_new(ctx, NULL, NULL);
    ctx->recvfd = stdin;
    if (soap_read_xsd__anyType(ctx, dom))
      ... // check for IO end parse errors
    ...
    soap_end(ctx);
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To write a DOM node graph in XML to a file descriptor `ctx->sendfd` you can use
the soapcpp2 auto-generated `soap_write_xsd__anyType(ctx, dom)` function:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // create new context and create a 'dom', write its XML to 'cout'
    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    xsd__anyType *dom = soap_elt_new(ctx, NULL, "store");
    ...
    ctx->sendfd = stdout;
    if (soap_write_xsd__anyType(ctx, dom))
      ... // check for IO errors
    ...
    soap_end(ctx);
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can also parse XML from a string into a DOM node graph by using the
`ctx->is` input string and the soapcpp2 auto-generated
`soap_read_xsd__anyType(ctx, dom)` function:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // create new context and parse XML from a string into 'dom'
    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    const char *in = "<store><book title=\"Sayings of the Century\"/></store>";
    xsd__anyType *dom = soap_elt_new(ctx, NULL, NULL);
    ctx->is = in;
    if (soap_read_xsd__anyType(ctx, dom))
      ... // check for IO end parse errors
    ctx->is = NULL;
    ...
    soap_end(ctx);
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Likewise, you can write a DOM node graph in XML to a string by using the
`ctx->os` output string pointer and the soapcpp2 auto-generated
`soap_write_xsd__anyType(ctx, dom)` function:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    // create new context and create a 'dom', write its XML to a string
    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
    const char *out = NULL;
    xsd__anyType *dom = soap_elt_new(ctx, NULL, "store");
    ...
    ctx->os = &out;                    // string to set to point to the output
    soap_write_xsd__anyType(ctx, dom); // convert DOM to XML string in UTF-8
    ctx->os = NULL;
    printf("%s\n", out);
    ...
    soap_end(ctx);
    soap_free(ctx);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `soap_read_xsd__anyType(ctx, dom)` and `soap_write_xsd__anyType(ctx, dom)`
functions return `SOAP_OK` (zero) or an error code in `ctx->error`.

It is also possible to send and receive XML over HTTP as REST operations as was
illustrated in the introduction.  To make REST HTTP POST, GET, OUT, and DELETE
calls, use:

- `int soap_dom_call(struct soap *ctx, const char *URL, const char *action, const xsd__anyType *in, xsd__anyType *out)`
  Make a POST, GET, PUT, DELETE call.  Connect to endpoint `URL` with HTTP
  SOAPAction `action` (or NULL) and send request `in` to server and receive
  response `out`.  Returns `SOAP_OK` (zero) or an error code.  POST method:
  pass both `in` and `out`.  GET method: pass a NULL to `in`.  PUT method: pass
  a NULL to `out`.  DELETE method: pass both NULL to `in` and `out`.

XML DOM parsing and display options                                       {#opt}
===================================

The soap context flags that control XML parsing and visual display are set when
the context is created or with the `soap_set_mode` and `soap_clr_mode`
functions:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_DOM_TREE);

    soap_set_mode(ctx, SOAP_XML_INDENT);  // use indent

    soap_clr_mode(ctx, SOAP_XML_INDENT);  // no indent
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Options to control XML parsing, object serialization, and XML rendition are:

- (no flag): only elements with an `id` attribute are deserialized as C/C++
  data types when a deserializer is available.  This is to ensure that the SOAP
  encoding protocol deos not break when id-ref attibutes are used for
  multireferenced objects.

- `SOAP_DOM_TREE`: prevents deserialization of C/C++ data structures into the
  DOM even when an `id` attribute is present.

- `SOAP_DOM_NODE`: deserialize C/C++ data structures into the DOM.  A
  deserializer is selected based on matching the element tag name or the
  xsi:type attribute value with the C/C++ type name.

- `SOAP_DOM_ASIS`: render XML "as is", i.e. do not insert xmlns bindings for
  URIs internally stored with nodes. Assumes that the DOM is self-contained
  with respect to namespaces.

- `SOAP_XML_INDENT`: render XML with indent.

- `SOAP_XML_CANONICAL`: render XML in canonical (exc-c14n) form.

- `SOAP_C_UTFSTRING`: the XML DOM always uses UTF-8, but embedded serializable
  objects only use UTF-8 when this flag is also set.

Using DOM together with serializeble types in a gSOAP header file         {#dom}
=================================================================

To use DOM nodes with types declared in a gSOAP header file, import `dom.h` into
your header file for processing with soapcpp2:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #import "dom.h"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The import is automatically added by wsdl2h with option `-d`.  The wsdl2h tool
binds xsd:anyType, xsd:any, xsd:anyAttribute and xsd:mixed XML content to DOM
nodes instead of using XML literal strings.

The `#import "dom.h"` enables us use the DOM `xsd__anyType` element node and
`xsd__anyAttribute` attribute node in a gSOAP header file type declarations,
such as:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #import "dom.h"

    class ns__record
    {
     public:
      @xsd__anyAttribute  atts;  // list of DOM attributes
      ...
      xsd__anyType        __any; // xsd:any, consumes all other XML
    };
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

where `__any` contains XML stored in a DOM node set and `atts` is a list of all
visibly rendered attributes.  The name `atts` is arbitrary and any name
will suffice.

We should place the `xsd__anyType` members at the end of the struct or class.
This ensures that the DOM members are populated last as a "catch all".  A
member name starting with double underscore is a wildcard member name and
matches any XML tag.  These members are placed at the end of a struct or class
automatically by soapcpp2.


The soapcpp2 tool generates code that "serializes" the DOM nodes as part of the
serialization of the C/C++ types in which they are used.

@see Documentation of [XML Data Bindings: DOM anyType and anyAttribute](http://www.genivia.com/doc/databinding/html/index.html#toxsd10-5).

Example                                                               {#example}
=======

This example demonstrates the domcpp tool to generate code for a SOAP request
message to send to a calculator service and to generate code to obtain the
floating point value from the SOAP response returned.  The generated code is
copied and modified to create a DOM-based SOAP client application in C++
`dom2calc.cpp`.

We use a very simple calculator service to demonstrate the C++ DOM API to
populate a DOM node graph and to query a DOM node graph.  The codes to
accomplish both of these tasks can be generated with domcpp and modified as
needed for our purposes.

The SOAP calculator service and client on which this example is based are
located in `gsoap/samples/calc` (for C) and `gsoap/samples/calc++` (for C++) in
the gSOAP package.

We use the SOAP calculator sample SOAP message `calc.add.req.xml` generated by
soapcpp2 in `gsoap/samples/calc++`.  This XML message contains a SOAP request
to add two floating point values:

<div class="alt">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.txt}
    <?xml version="1.0" encoding="UTF-8"?>
    <SOAP-ENV:Envelope
      xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"
      xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xmlns:xsd="http://www.w3.org/2001/XMLSchema"
      xmlns:ns="urn:calc">
     <SOAP-ENV:Body SOAP-ENV:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/">
      <ns:add>
       <a>0.0</a>
       <b>0.0</b>
      </ns:add>
     </SOAP-ENV:Body>
    </SOAP-ENV:Envelope>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</div>

To generate code that populates this SOAP request message as a DOM node graph,
we invoke:

    domcpp -M -n -rrequest calc.add.req.xml

We copied the generated code into `dom2calc.cpp` as shown further below.

A sample SOAP response message `calc.add.res.xml` from the calculator service is:

<div class="alt">
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.txt}
    <?xml version="1.0" encoding="UTF-8"?>
    <SOAP-ENV:Envelope
      xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"
      xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xmlns:xsd="http://www.w3.org/2001/XMLSchema"
      xmlns:ns="urn:calc">
     <SOAP-ENV:Body SOAP-ENV:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/">
      <ns:addResponse>
       <result>0.0</result>
      </ns:addResponse>
     </SOAP-ENV:Body>
    </SOAP-ENV:Envelope>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</div>

We want to generate code that inspects the SOAP response message to extract the
value of `<result>`.  For this purpose we can use the XPath query
`/SOAP-ENV:Envelope/SOAP-ENV:Body/ns:addResponse/result` and use this XPath
with domcpp option `-p` and option `-x` to generate code that prints the
`<result>` value:

    domcpp -p'/SOAP-ENV:Envelope/SOAP-ENV:Body/ns:addResponse/result' \
      -rresponse -x'std::cout << "Result = " << v << std::endl;'

We copied the generated code into `dom2calc.cpp` as shown below:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapH.h"

    const char server[] = "http://websrv.cs.fsu.edu/~engelen/calcserver.cgi";

    // copied from:
    // domcpp -M -n -rrequest calc.add.req.xml
    struct Namespace namespaces[] = {
      {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope",      NULL},
      {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding",      NULL},
      {"xsi",      "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
      {"xsd",      "http://www.w3.org/2001/XMLSchema",          "http://www.w3.org/*/XMLSchema",          NULL},
      {"ns", "urn:calc", NULL, NULL },
      {NULL, NULL, NULL, NULL}
    };

    int main(int argc, char **argv)
    {
      struct soap *ctx = soap_new1(SOAP_DOM_TREE | SOAP_XML_INDENT);

      if (argc <= 3)
      {
        std::cerr << "Usage: dom2calc [add|sub|mul|div|pow] <num> <num>" << std::endl;
        exit(1);
      }

      // create command tag ns:add, ns:sub, ns:mul, ns:div, or ns:pow
      std::string command = std::string("ns:").append(argv[1]);

      // copied and modified from:
      // domcpp -M -n -rrequest calc.add.req.xml
      xsd__anyType request(ctx, "SOAP-ENV:Envelope");
      request["SOAP-ENV:Body"].att("SOAP-ENV:encodingStyle") = "http://schemas.xmlsoap.org/soap/encoding/";
      request["SOAP-ENV:Body"][command.c_str()]["a"] = strtod(argv[2], NULL);
      request["SOAP-ENV:Body"][command.c_str()]["b"] = strtod(argv[3], NULL);

      std::cout << "** Request message: " << std::endl << request << std::endl << std::endl;

      // create response
      xsd__anyType response(ctx);

      // invoke server: make POST XML request and receive XML response
      if (soap_dom_call(ctx, server, "", request, response))
      {
        soap_stream_fault(ctx, std::cerr);
      }
      else
      {
        std::cout << "** Response message:" << std::endl << response << std::endl << std::endl;

        // copied from:
        // domcpp -p'/SOAP-ENV:Envelope/SOAP-ENV:Body/ns:addResponse/result' -rresponse -x'std::cout << "Result = " << v << std::endl;'
        if (response.match("SOAP-ENV:Envelope"))
        {
          size_t pos = 1;
          for (xsd__anyType *it = response.elt_get("SOAP-ENV:Body"); it; it = it->get_next(), ++pos)
          {
            xsd__anyType& v = *it;
            size_t pos = 1;
            for (xsd__anyType *it = v.elt_get("ns:addResponse"); it; it = it->get_next(), ++pos)
            {
              xsd__anyType& v = *it;
              size_t pos = 1;
              for (xsd__anyType *it = v.elt_get("result"); it; it = it->get_next(), ++pos)
              {
                xsd__anyType& v = *it;
                std::cout << "Result = " << v.get_double() << std::endl;
              }
            }
          }
        }
      }

      soap_destroy(ctx); // delete objects
      soap_end(ctx);     // delete temp data
      soap_free(ctx);    // free context

      return 0;
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To compile `dom2calc.cpp` we first generate `soapC.cpp`, `soapStub.h` and
`soapH.h` from the gSOAP header file `dom.h`:

    soapcpp2 dom.h
    c++ -o dom2calc dom2calc.cpp soapC.cpp dom.cpp stdsoap2.cpp

Running the DOM-based calculator client gives:

    ./dom2calc add 3 4

    ** Request message: 
    <SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/">
            <SOAP-ENV:Body SOAP-ENV:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/">
                    <ns:add xmlns:ns="urn:calc">
                            <a>3</a>
                            <b>4</b>
                    </ns:add>
            </SOAP-ENV:Body>
    </SOAP-ENV:Envelope>

    ** Response message:
    <SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:ns="urn:calc">
            <SOAP-ENV:Body SOAP-ENV:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/">
                    <ns:addResponse>
                            <result>7</result>
                    </ns:addResponse>
            </SOAP-ENV:Body>
    </SOAP-ENV:Envelope>

    Result = 7

Another way to extract the floating point value from the SOAP response is to
use the `xsd__anyType::find()` method to search (and iterate) over `<result>`
elements:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    for (xsd__anyType::iterator it = response.find("result"); it != response.end(); ++it)
      std::cout << std::endl << "Result = " << it->get_double() << std::endl;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

where the `xsd__anyType::get_double()` method is used to cast the XML value to
a `double`.

Miscellaneous                                                            {#misc}
=============

Floating point format                                                      {#fp}
---------------------

The floating point format used to output values in XML-RPC and JSON is by
default ".17lG' to ensure accuracy up to the last digit.  The format can be set
as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
    struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT);
    ctx->double_format = "%lG";
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
