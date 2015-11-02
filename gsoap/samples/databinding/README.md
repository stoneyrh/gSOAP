
XML Data Bindings                                                    {#mainpage}
=================

[TOC]

This is a detailed overview of the gSOAP XML data bindings concepts and
implementation. At the end of this document two examples are given to
illustrate the application of data bindings.

The first example `address.cpp` shows how to use wsdl2h to bind an XML
schema to C++. The C++ application reads and writes an XML file into and from a
C++ "address book" data structure. The C++ data structure is an STL vector of
address objects.

The second example `graph.cpp` shows how XML is serialized as a tree, digraph,
and cyclic graph. The digraph and cyclic graph serialization rules are similar
to SOAP 1.1/1.2 encoded multi-ref elements with id-ref attributes to link
elements through IDREF XML "pointers".

These examples demonstrate XML data bindings only for relatively simple data
structures and types. The gSOAP tools support more than just these type of
structures, which we will explain in the next sections. Support for XML schema
components is practically unlimited. The wsdl2h tool maps schemas to C and C++
using built-in intuitive mapping rules, while allowing the mappings to be
customized using a `typemap.dat` file with mapping instructions for wsdl2h.

The information in this document is applicable to gSOAP 2.8.24 and higher, which
supports C++11 features. However, C++11 is not required to use this material
and follow the example, unless we need smart pointers and scoped enumerations.
While most of the examples in this document are given in C++, the concepts also
apply to C with the exception of containers, smart pointers, classes and their
methods. None of these exceptions limit the use of the gSOAP tools for C in any
way.

The data binding concepts described in this document have somewhat changed
and improved over the years since the first version of gSOAP was developed in
1999 (the project was called a "XML/SOAP stub/skeleton compiler" back
then). However, the principle of mapping XSD components to C/C++ types and vice
versa was envisioned, designed, and implemented early on in research conducted
by Dr. van Engelen at the Florida State University and subsequently adopted by
other tools, including Java web services and in C# WCF.


Mapping WSDL and XML schemas to C/C++                                   {#tocpp}
=====================================

To convert WSDL and XML schemas (XSD files), we use the wsdl2h command to
generate the data binding interface code in a special gSOAP header file:

    wsdl2h [options] -o file.h ... XSD and WSDL files ...

This converts WSDL and XSD files to C++ (or pure C with wsdl2h option `-c`) and
saves a special `file.h` data binding interface file.

The WSDL 1.1/2.0, SOAP 1.1/1.2, and XSD 1.0/1.1 standards are supported by the
gSOAP tools. In addition, the most popular WS specifications are also
supported, including WS-Addressing, WS-ReliableMessaging, WS-Discovery,
WS-Security, WS-Policy, WS-SecurityPolicy, and WS-SecureConversation.

This document focusses on XML data bindings and mapping C/C++ to XML 1.0/1.1
and XSD 1.0/1.1.  This covers all of the following standard XSD components with
their optional `[ attributes ]` properties:

    any [minOccurs, maxOccurs]
    anyAttribute
    all
    choice [minOccurs, maxOccurs]
    sequence [minOccurs, maxOccurs]
    group [name, ref]
    attributeGroup [name, ref]
    attribute [name, ref, type, use, default, fixed, form, wsdl:arrayType]
    element [name, ref, type, default, fixed, form, nillable, abstract, substitutionGroup, minOccurs, maxOccurs]
    simpleType [name]
    complexType [name, abstract, mixed]

And also the following standard XSD components:

    import              imports a schema into the importing schema for referencing
    include             include schema component definitions into a schema
    override            override by replacing schema component definitions
    redefine            extend or restrict schema component definitions
    annotation          annotates a component

The XSD facets and their mappings to C/C++ are:

    enumeration         maps to enum
    simpleContent       maps to class/struct wrapper with __item member
    complexContent      maps to class/struct
    list                maps to enum* bitmask (enum* enumerates up to 64 bit masks)
    extension           through inheritance
    restriction         partly through inheritance and redeclaration
    length              restricts content length
    minLength           restricst content length
    maxLength           restricst content length
    minInclusive        restricts numerical value range
    maxInclusive        restricts numerical value range
    minExclusive        restricts numerical value range
    maxExclusive        restricts numerical value range
    precision           maps to float/double but constraint is not validated
    scale               maps to float/double but constraint is not validated
    totalDigits         maps to float/double but constraint is not validated
    fractionDigits      maps to float/double but constraint is not validated
    pattern             must define `soap::fsvalidate` callback to validate patterns
    union               maps to string of values

All primitive XSD types are supported, including but not limited to the
following XSD types:

    anyType             maps to _XML string with literal XML content (or DOM with wsdl2h option -d)
    anyURI              maps to string
    string              maps to string (char*/wchar_t*/std::string/std::wstring)
    boolean             maps to bool (C++) or enum xsd__boolean (C)
    byte                maps to char (int8_t)
    short               maps to short (int16_t)
    int                 maps to int (int32_t)
    long                maps to LONG64 (long long and int64_t)
    unsignedByte        maps to unsigned char (uint8_t)
    unsignedShort       maps to unsigned short (uint16_t)
    unsignedInt         maps to unsigned int (uint32_t)
    unsignedLong        maps to ULONG64 (unsigned long long and uint64_t)
    float               maps to float
    double              maps to double
    integer             maps to string
    decimal             maps to string, or use "#import "custom/long_double.h"
    precisionDecimal    maps to string
    duration            maps to string, or use "#import "custom/duration.h"
    dateTime            maps to time_t, or use "#import "custom/struct_tm.h"
    time                maps to string, or use "#import "custom/long_time.h"
    date                maps to string, or use "#import "custom/struct_tm_date.h"
    hexBinary           maps to class/struct xsd__hexBinary
    base64Bianry        maps to class/struct xsd__base64Binary
    QName               maps to _QName (URI normalization rules are applied)

All other primitive XSD types not listed above are mapped to strings, by
generating a typedef. For example, xsd:token is bound to a C++ or C string,
which associates a value space to the type with the appropriate XSD type name
used by the soapcpp2-generated serializers:

    typedef std::string  xsd__token;  // C++
    typedef char        *xsd__token;  // C (wsdl2h option -c)

It is possible to remap types by adding the appropriate mapping rules to
`typemap.dat` as explained in the next section.


Using typemap.dat to customize generated bindings                     {#typemap}
=================================================

We use a `typemap.dat` file to redefine namespace prefixes and to customize
type bindings for the the generated header files produced by the wsdl2h tool.
The `typemap.dat` is the default file processed by wsdl2h. Use wsdl2h option
`-t` to specify an alternate file.

Declarations in `typemap.dat` can be broken up over multiple lines by
continuing on the next line by ending each line to be continued with a
backslash `\`.

XML namespace bindings                                               {#typemap1}
----------------------

The wsdl2h tool generates C/C++ type declarations that use `ns1`, `ns2`, etc.
as URI schema-binding prefixes. These default prefixes are generated somewhat
arbitrarily for each schema URI, meaning that their ordering may change
depending on the WSDL and XSD order of processing with wsdl2h.

It is **strongly recommended** to declare your own prefix for each schema URI
to enhance maintaince of your code. This is to anticipate possible changes of
the schema(s) and/or the binding URI(s) and/or the tooling procedures.

Therefore, the first and foremost important thing to do is to define prefix-URI
bindings for our C/C++ code by adding the following line(s) to our
`typemap.dat` or make a copy of this file and add the line(s) that bind our
choice of prefix name to each URI:

    prefix = "URI"

For example:

    g = "urn:graph"

This produces `g__name` C/C++ type names that are bound to the "urn:graph"
schema by association of `g` to the C/C++ types.

This means that `<g:name xmlns:g="urn:graph">` is parsed as an instance of a
`g__name` C/C++ type. Also `<x:name xmlns:x="urn:graph">` parses as an instance
of `g__name`, because the prefix `x` has the same URI value `urn:graph`.
Prefixes in XML have local scopes (like variables in a block).

The first run of wsdl2h will reveal the URIs, so we do not need to search WSDLs
and XSD files for all of the target namespaces.

XSD type bindings                                                    {#typemap2}
-----------------

Custom C/C++ type bindings can be declared in `typemap.dat` to associate C/C++
types with specific schema types. These type bindings have four parts:

    prefix__type = declaration | use | ptruse

where

- `prefix__type` is the schema type to be customized (the `prefix__type` name
  uses the common double underscore naming convention);
- `declaration` declares the C/C++ type in the wsdl2h-generated header file.
  This part can be empty if no explicit declaration is needed;
- `use` is an optional part that specifies how the C/C++ type is used in the
  code. When omitted, it is the same as `prefix__type`;
- `ptruse` is an optional part that specifies how the type is used as a
  pointer type. By default it is the `use` type name with a `*` or C++11
  `std::shared_ptr<>` (see further below).

For example, to map xsd:duration to a `long long` (`LONG64`) milliseconds
value, we can use the custom serializer declared in `custom/duration.h` by
adding the following line to `typemap.dat`:

    xsd__duration = #import "custom/duration.h" | xsd__duration

Here, we could have omitted the second field, because `xsd__duration` is the
name that wsdl2h uses to identify this type.

To map xsd:string to `wchar_t*` wide strings:

    xsd__string = | wchar_t* | wchar_t*

Note that the first field is empty, because `wchar_t` is a C type and does not
need to be declared. A `ptruse` field is given so that we do not end up
generating the wrong pointer types, such as `wchar_t**` and
`std::shared_ptr<wchar_t>`.

When the auto-generated declaration should be preserved but the `use` or
`ptruse` fields replaced, then we use an ellipsis for the declaration part:

    prefix__type = ... | use | ptruse

This is useful to map schema polymorphic types to C types for example, where we
need to be able to both handle a base type and its extensions as per schema
extensibility. Say we have a base type called ns:base that is extended, then we
can remap this to a C type that permits referening the extended types via a
`void*` as follows:

    ns__base = ... | int __type_base; void*

such that `__type_base` and `void*` are used to (de)serialize any data type,
including base and its derived types.

Class/struct member additions                                        {#typemap3}
-----------------------------

All generated classes and structs can be augmented with additional
members such as methods, constructors and destructors, and private members:

    prefix__type = $ member-declaration

For example, we can add method declarations and private members to a class, say
`ns__record` as follows:

    ns__record = $ ns__record(const ns__record &);  // copy constructor
    ns__record = $ void print();                    // a print method
    ns__record = $ private: int status;             // a private member

Note that method declarations cannot include any code, because soapcpp2's input
permits only type declarations, not code.

Replacing XSD types by equivalent alternatives                       {#typemap4}
----------------------------------------------

Type replacements can be given to replace one type entirely with another given
type:

    prefix__type1 == prefix__type2

This replaces all `prefix__type1` by `prefix__type2` in the wsdl2h output.
However, care muse be taken not to agressively replace types, because this can
cause XML validation to fail when a value-type mismatch is encountered in the
XML input. Therefore, only replace similar types with other similar types that
are wider (e.g.  `short` by `int` and `float` by `double`).

The built-in typemap.dat variables $CONTAINER and $POINTER           {#typemap5}
----------------------------------------------------------

The `typemap.dat` `$CONTAINER` variable defines the container to emit in the
generated declarations, which is `std::vector` by default. For example, to emit
`std::list` as the container in the wsdl2h-generated declarations:

    $CONTAINER = std::list

The `typemap.dat` `$POINTER` variable defines the smart pointer to emit in the
generated declarations, which replaces the use of `*` pointers. For example:

    $POINTER = std::shared_ptr

Not all pointers in the generated output can be replaced by smart pointers.
Standard pointers are itill sed as union members and for pointers to arrays of
objects.

User-defined content                                                 {#typemap6}
--------------------

Any other content to be generated by wsdl2h can be included in `typemap.dat` by
enclosing it within brackets `[` and `]` anywhere in the `typemap.dat` file.
Each of the two brackets MUST appear at the start of a new line.

For example, we can add an `#import "wsa5.h"` directive to the wsdl2h-generated
output as follows:

    [
    #import "wsa5.h"
    ]

which emits the `#import "wsa5.h"` literally at the start of the
wsdl2h-generated header file.


Mapping C/C++ to XML schema                                             {#toxsd}
===========================

The soapcpp2 command generates the data binding implementation code from a data
binding interface `file.h`:

    soapcpp2 [options] file.h

where `file.h` is a gSOAP header file that declares the XML data binding
interface. The `file.h` is typically generated by wsdl2h, but we can also
declare one ourself. If so, we add gSOAP directives and declare in this file
all our C/C++ types we want to serialize in XML. We can also declare functions
that will be converted to service operations by soapcpp2.

Global function declarations define service operations, which are of the form:

    int ns__name(arg1, arg2, ..., argn, result);

where `arg1`, `arg2`, ..., `argn` are formal argument declarations of the input
and `result` is a formal argument for the output, which must be a pointer or
reference to the result object to be populated. More information can be found
in the gSOAP user guide.

Overview of serializable C/C++ types                                   {#toxsd1}
------------------------------------

The following C/C++ types are supported by soapcpp2 and mapped to XSD types
and constructs. See the subsections below for more details or follow the links.

List of [C++ bool and C alternative](#toxsd3)

    bool                      C++ bool
    enum xsd__boolean         C alternative bool
 
List of [enumerations and bitmasks](#toxsd4)

    enum                      enumeration
    enum class                C++11 scoped enumeration (soapcpp2 -c++11)
    enum*                     a bitmask that enumerates values 1, 2, 4, 8, ...
    enum* class               C++11 scoped enumeration (soapcpp2 -c++11)

List of [numerical types](#toxsd5)

    char                      byte
    short                     16 bit integer
    int                       32 bit integer
    long                      32 bit integer
    LONG64                    64 bit integer
    long long                 same as LONG64
    unsigned char             unsigned byte
    unsigned short            unsigned 16 bit integer
    unsigned int              unsigned 32 bit integer
    unsigned long             unsigned 32 bit integer
    ULONG64                   unsigned 64 bit integer
    unsigned long long        same as ULONG64
    int8_t                    same as char
    int16_t                   same as short
    int32_t                   same as int
    int64_t                   same as LONG64
    uint8_t                   same as unsigned char
    uint16_t                  same as unsigned short
    uint32_t                  same as unsigned int
    uint64_t                  same as ULONG64
    size_t                    transient type (not serializable)
    float                     32 bit float
    double                    64 bit float
    long double               128 bit float, use #import "custom/long_double.h"
    typedef                   declares a type name, may restrict numeric range

List of [string types](#toxsd6)

    char*                     string
    wchar_t*                  wide string
    std::string               C++ string
    std::wstring              C++ wide string
    char[N]                   fixed-size string, requires soapcpp2 option -b
    _QName                    normalized QName content
    _XML                      literal XML string content
    typedef                   declares a type name, may restrict string length

List of [date and time types](#toxsd7)

    time_t                    date and time point since epoch
    struct tm                 date and time point, use #import "custom/struct_tm.h"
    struct tm                 date point, use #import "custom/struct_tm_date.h"
    struct timeval            date and time point, use #import "custom/struct_timeval.h"
    unsigned long long        time point in microseconds, use #import "custom/long_time.h"
    std::chrono::system_clock::time_point
                              date and time point, use #import "custom/chrono_time_point.h"

List of [time duration types](#toxsd8)

    long long                 duration in milliseconds, use #import "custom/duration.h"
    std::chrono::nanoseconds  duration in nanoseconds, use #import "custom/chrono_duration.h"

List of [classes and structs](#toxsd9)

    class                     C++ class with single inheritance only
    struct                    C struct or C++ struct without inheritance
    T*                        pointer to type T
    T[N]                      fixed-size array of type T
    std::shared_ptr<T>        C++11 smart shared pointer
    std::unique_ptr<T>        C++11 smart pointer
    std::auto_ptr<T>          C++ smart pointer
    std::deque<T>             use #import "stldeque.h"
    std::list<T>              use #import "stllist.h"
    std::vector<T>            use #import "stlvector.h"
    std::set<T>               use #import "stlset.h"
    template<T> class         a container with begin(), end(), size(), clear(), and insert() methods
    union                     requires a discriminant member
    void*                     requires a __type member to indicate the type of object pointed to

List of [special classes and structs](#toxsd10)

    Array                     single and multidimensional SOAP Arrays
    xsd__hexBinary            binary content
    xsd__base64Binary         binary content and optional MIME/MTOM attachments
    Wrapper                   complexTypes with simpleContent

Colon notation versus name prefixing                                   {#toxsd2}
------------------------------------

To bind C/C++ type names to XSD types, a simple form of name prefixing is used
by the gSOAP tools by prepending the XML namespace prefix to the C/C++ type
name with a pair of undescrores. This also ensures that name clashes cannot
occur when multiple WSDL and XSD files are converted to C/C++. Also, C++
namespaces are not sufficiently rich to capture XML schema namespaces
accurately, for example when class members are associated with schema elements
defined in another XML namespace and thus the XML namespace scope of the
member's name is relevant, not just its type.

However, from a C/C++ centric point of view this can be cumbersome. Therefore,
colon notation is an alternative to physically augmenting C/C++ names with
prefixes.

For example, the following class uses colon notation to bind the `record` class
to the `urn:types` schema:

    //gsoap ns schema namespace: urn:types
    class ns:record        // binding 'ns:' to a type name
    {
     public:
      std::string name;
      uint64_t    SSN;
      ns:record   *spouse;  // using 'ns:' with the type name
      ns:record();          // using 'ns:' here too
      ~ns:record();         // and here
    };

The colon notation is stripped away by soapcpp2 when generating the data
binding implementation code for our project. So the final code just uses
`record` to identify this class and its constructor/destructor.

When using colon notation we have to be consistent as we cannot use both forms
together. That is, `ns:record` differs from `ns__record` as a name.

C++ Bool and C alternative                                             {#toxsd3}
--------------------------

The C++ `bool` type is bound to built-in XSD type xsd:boolean.

The C alternative is to define an enumeration:

    enum xsd__boolean { false_, true_ };

or by defining an enumeration in C with pseudo-scoped enumeration values:

    enum xsd__boolean { xsd__boolean__false, xsd__boolean__true };

The XML value space of these types is `false` and `true`, but also accepts `0`
and `1` as values.

To prevent name clashes, `false_` and `true_` have an underscore which are
removed in the XML value space.

Enumerations and bitmasks                                              {#toxsd4}
-------------------------

Enumerations are mapped to XSD simpleType enumeration restrictions of
xsd:string, xsd:QName, and xsd:long.

Consider for example:

    enum ns__Color { RED, WHITE, BLUE };

which maps to a simpleType restriction of xsd:string in the soapcpp2-generated
schema:

    <simpleType name="Color">
      <restriction base="xsd:string">
        <enumeration value="RED"/>
        <enumeration value="WHITE"/>
        <enumeration value="BLUE"/>
      </restriction>
    </simpleType>

Enumeration name constants can be pseudo-scoped to prevent name clashes,
because enumeration name constants have a global scope in C and C++:

    enum ns__Color { ns__Color__RED, ns__Color__WHITE, ns__Color__BLUE };

We can also use C++11 scoped enumerations to prevent name clashes:

    enum class ns__Color : int { RED, WHITE, BLUE };

Here, the type part `: int` is optional. In place of `int` in the example
above, we can also use `int8_t`, `int16_t`, `int32_t`, or `int64_t`.

The XML value space of the enumertions defined above is `RED`, `WHITE`, and
`BLUE`.

Prefix-qualified enumeration name constants are mapped to simpleType
restrictions of xsd:QName, for example:

    enum ns__types { xsd__int, xsd__float };

which maps to a simpleType restriction of xsd:QName in the soapcpp2-generated
schema:

    <simpleType name="types">
      <restriction base="xsd:QName">
        <enumeration value="xsd:int"/>
        <enumeration value="xsd:float"/>
      </restriction>
    </simpleType>

Enumeration name constants can be pseudo-numeric as follows:

    enum ns__Primes { _3 = 3, _5 = 5, _7 = 7, _11 = 11 };

which maps to a simpleType restriction of `xsd:long`:

    <simpleType name="Color">
      <restriction base="xsd:long">
        <enumeration value="3"/>
        <enumeration value="5"/>
        <enumeration value="7"/>
        <enumeration value="11"/>
      </restriction>
    </simpleType>

The XML value space of this type is `3`, `5`, `7`, and `11`.

Besides (pseudo-) scoped enumerations, another way to prevent name clashes
accross enumerations is to start an enumeration name constant with one
underscore or followed it by any number of underscores, which makes it
unique. The leading and trailing underscores are removed in the XML value
space.

    enum ns__ABC { A, B, C };
    enum ns__BA  { B, A };      // BAD: B = 1 but B is already defined as 2
    enum ns__BA_ { B_, A_ };    // OK

The gSOAP soapcpp2 tool permits reusing enumeration name constants in other
(non-scoped) enumerations as long as these values are assigned the same
constant. Therefore, the following is permitted:

    enum ns__Primes { _3 = 3, _5 = 5, _7 = 7, _11 = 11 };
    enum ns__Throws { _1 = 1, _2 = 2, _3 = 3, _4 = 4, _5 = 5, _6 = 6 };

A bitmask type is an `enum*` "product" enumeration with a geometric,
power-of-two sequence of values assigned to the name constants:

    enum* ns__Options { SSL3, TLS10, TLS11, TLS12 };

where the product enum assigns 1 to `SSL3`, 2 to `TLS10`, 4 to `TLS11`, and 8
to `TLS12`, which allows the enumeration values to be used in composing
bitmasks with `|` (bitwise or) `&` (bitwise and), and `~` (bitwise not):

    enum ns__Options options = (enum ns__Options)(SSL3 | TLS10 | TLS11 | TLS12);
    if (options & SSL3)  // if SSL3 is an option, warn and remove from options
    {
      warning();
      options &= ~SSL3;
    }

The bitmask type maps to a simpleType list restriction of xsd:string in the
soapcpp2-generated schema:

    <simpleType name="Options">
      <list>
        <restriction base="xsd:string">
          <enumeration value="SSL3"/>
          <enumeration value="TLS10"/>
          <enumeration value="TLS11"/>
          <enumeration value="TLS12"/>
        </restriction>
      </list>
    </simpleType>

The XML value space of this type consists of all 16 possible subsets of the
four values, represented by an XML string with space-separated values. For
example, the bitmask `TLS10 | TLS11 | TLS12` equals 14 and is represented in by
the XML string `TLS10 TLS11 TLS12`.

To convert `enum` name constants to string, we use the soapcpp2 auto-generated
`const char *soap_T2s(soap, enum T)` function.

To convert a string to an `enum` name constant, we use the soapcpp2
auto-generated `int soap_s2T(soap, const char *str, enum T*)` function.

Numerical types                                                        {#toxsd5}
---------------

Integer and floating point types are mapped to the equivalent built-in XSD
types with the same sign and bit width.

The `size_t` type is transient (not serializable) because its width is platform
dependent. We recommend to use `uint64_t` instead.

The XML value space of integer types are their decimal representations without
loss of precision.

The XML value space of floating point types are their decimal representations.
The decimal representations are formatted with the printf format string "%.9G"
for floats and the printf format string "%.17lG" for double.  The value space
includes the values `INF`, `-INF`, and `NAN`. To change the format string, we
can change one of these `struct soap` context data members:

    const char * soap::float_format
    const char * soap::double_format

Note that decimal conversions may result in a loss of precision of the least
significant decimal.

A `long double` 128 bit floating point value requires a custom serializer:

    #import "custom/long_double.h"
    typedef long double xsd__decimal;

Compile and link your code with `custom/long_double.c`.

The range of a numerical type can be restricted with a typedef:

    typedef int ns__narrow -10:10;

which maps to a simpleType restriction of xsd:int in the soapcpp2-generated
schema:

    <simpleType name="narrow">
      <restriction base="xsd:int">
        <minInclusive value="-10"/>
        <maxInclusive value="10"/>
      </restriction>
    </simpleType>

The range of a float type can only be restricted within integral bounds. This
restriction may be dropped in future releases.

String types                                                           {#toxsd6}
------------

String types are mapped to the built-in xsd:string and xsd:QName XSD types.

The wide strings `wchar_t*` and `std::wstring` may contain Unicode that is
preserved in the XML value space.

Strings `char*` and `std::string` can only contain extended Latin, but we can
store UTF-8 content that is preserved in the XML value space when the `struct
soap` context is initialized with the flag `XML_C_UTFSTRING`.

Beware that many XML 1.0 parsers reject all control characters (those between
`#x1` and `#x1F`) except `#x9`, `#xA`, and `#xD`. With the newer XML 1.1
parsers (including gSOAP) you should be fine.

The length of a string type can be restricted with a typedef:

    typedef std::string ns__password 6:16;

which maps to a simpleType restriction of xsd:string in the soapcpp2-generated
schema:

    <simpleType name="password">
      <restriction base="xsd:string">
        <minLength value="6"/>
        <maxLength value="16"/>
      </restriction>
    </simpleType>

In addition, an XSD regex pattern restriction can be associated with a string
typedef:

    typedef std::string ns__password "([a-zA-Z]|[0-9]|-)+" 6:16;

which maps to a simpleType restriction of xsd:string in the soapcpp2-generated
schema:

    <simpleType name="password">
      <restriction base="xsd:string">
        <pattern value="([a-zA-Z0-9]|-)+"/>
        <minLength value="6"/>
        <maxLength value="16"/>
      </restriction>
    </simpleType>

Fixed-size strings (`char[N]`) are rare occurrences in the wild, but apparently
still used in some projects to store strings. To facilitate fixed-size string
serialization, use soapcpp2 option `-b`:

    typedef char ns__buffer[10];  // requires soapcpp2 option -b

which maps to a simpleType restriction of xsd:string in the soapcpp2-generated
schema:

    <simpleType name="buffer">
      <restriction base="xsd:string">
        <maxLength value="9"/>
      </restriction>
    </simpleType>

Note that fixed-size strings MUST contain NUL-terminated text and SHOULD NOT
contain raw binary data. Also, the length limitation is more restrictive for
UTF-8 content (enabled with the `SOAP_C_UTFSTRING`) that requires multibyte
character encodings. As a consequence, UTF-8 content may be truncated to fit.

Note that raw binary data can be stored in a `xsd__base64Binary` or
`xsd__hexBinary` structure, or transmitted as a MIME attachment.

The built-in `_QName` type is a regular C string type (`char*`) that maps to
xsd:QName but has the added advantage that it holds normalized qualified names.
There are actually two forms of normalized QName content, to ensure any QName
is represented accurately and uniquely:

    prefix:name
    "URI":name

where the first form is used when the prefix (and the binding URI) is defined
in the namespace table and is bound to a URI (see the .nsmap file). The second
form is used when the URI is not defined in the namespace table and therefore
no prefix is available to bind and normalize the URI to.

A `_QName` string may contain a sequence of space-separated QName values, not
just one, and all QName values are normalized to the format shown above.

To define a `std::string` base type for xsd:QName, we use a typedef:

    typedef std::string xsd__QName;

The `xsd__QName` string content is normalized, just as with the `_QName`
normalization.

To serialize strings that contain literal XML content to be reproduced in the
XML value space, use the built-in `_XML` string type, which is a regular C
string type (`char*`) that maps to plain XML CDATA.

To define a `std::string` base type for literal XML content, use a typedef:

    typedef std::string XML;

Strings can hold any of the values of the XSD built-in primitive types. We can
use a string typedef to declare the use of the string type as a XSD built-in
type:

    typedef std::string xsd__token;

We MUST ensure that the string values we populate in this type conform to the
XML standard, which in case of xsd:token is: the lexical and value spaces of
xsd:token are the sets of all strings after whitespace replacement of any
occurrence of `#x9`, `#xA` , and `#xD` by `#x20` and collapsing.

Date and time types                                                    {#toxsd7}
-------------------

The C/C++ `time_t` type is mapped to the built-in xsd:dateTime XSD type that
represents a date and time within a time zone (typically UTC).

The XML value space contains ISO 8601 Gregorian time instances of the form
`[-]CCYY-MM-DDThh:mm:ss.sss[Z|(+|-)hh:mm]`, where `Z` is the UTC time zone or a
time zone offset `(+|-)hh:mm]` from UTC is used.

A `time_t` value is considered and represented in UTC by the serializer.

Because the `time_t` value range is restricted to dates after 01/01/1970, care
must be taken to ensure the range of xsd:dateTime values in XML exchanges do
not exceed the `time_t` range.

This restriction does not hold for `struct tm` (`<time.h>`), which we can use
to store and communicate a date and time in UTC without date range restrictions.
The serializer uses the `tm` data members directly for conversion to/from the
XML value space of xsd:dateTime:

    struct tm
    {
      int    tm_sec;    // seconds (0 - 60)
      int    tm_min;    // minutes (0 - 59)
      int    tm_hour;   // hours (0 - 23)
      int    tm_mday;   // day of month (1 - 31)
      int    tm_mon;    // month of year (0 - 11)
      int    tm_year;   // year - 1900
      int    tm_wday;   // day of week (Sunday = 0) (NOT USED)
      int    tm_yday;   // day of year (0 - 365) (NOT USED)
      int    tm_isdst;  // is summer time in effect?
      char*  tm_zone;   // abbreviation of timezone (NOT USED)
    };

The `struct tm` type is mapped to the built-in xsd:dateTime XSD type and
serialized with the custom serializer `custom/struct_tm.h` that declares a
`xsd__dateTime` type:

    #import "custom/struct_tm.h"  // import typedef struct tm xsd__dateTime;
    ... use xsd__dateTime ...

Compile and link your code with `custom/struct_tm.c`.

The `struct tm` type is mapped to the built-in xsd:date XSD type and serialized
with the custom serializer `custom/struct_tm_date.h` that declares a
`xsd__date` type:

    #import "custom/struct_tm_date.h"  // import typedef struct tm xsd__date;
    ... use xsd__date ...

Compile and link your code with `custom/struct_tm_date.c`.

The XML value space of xsd:date are Gregorian calendar dates of the form
`[-]CCYY-MM-DD[Z|(+|-)hh:mm]`.

The `struct timeval` (`<sys/time.h>`) type is mapped to the built-in
xsd:dateTime XSD type and serialized with the custom serializer
`custom/struct_timeval.h` that declares a `xsd__dateTime` type:

    #import "custom/struct_timeval.h"  // import typedef struct timeval xsd__dateTime;
    ... use xsd__dateTime ...

Compile and link your code with `custom/struct_timeval.c`.

Note that the same value range restrictions apply to `struct timeval` as they
apply to `time_t`. The added benefit of `struct timeval` is the addition of
a microsecond-precise clock:

    struct timeval
    {
     time_t       tv_sec;   // seconds since Jan. 1, 1970
     suseconds_t  tv_usec;  // and microseconds
    };

An `unsigned long long` (`ULONG64` or `uint64_t`) type that contains a 24 hour
time in microseconds UTC is mapped to the built-in xsd:time XSD type and
serialized with the custom serializer `custom/long_time.h` that declares a
`xsd__time` type:

    #import "custom/long_time.h"  // import typedef unsigned long long xsd__time;
    ... use xsd__time ...

Compile and link your code with `custom/long_time.c`.

The XML value space of xsd:time are points in time recurring each day of the
form `hh:mm:ss.sss[Z|(+|-)hh:mm]`, where `Z` is the UTC time zone or a time
zone offset from UTC is used. The `xsd__time` value is always considered and
represented in UTC by the serializer.

A C++11 `std::chrono::system_clock::time_point` type is mapped to the built-in
xsd:dateTime XSD type and serialized with the custom serializer
`custom/chrono_time_point.h` that declares a `xsd__dateTime` type:

    #import "custom/chrono_time_point.h"  // import typedef std::chrono::system_clock::time_point xsd__dateTime;
    ... use xsd__dateTime ...

Compile and link your code with `custom/chrono_time_point.cpp`.

Time duration types                                                    {#toxsd8}
-------------------

The XML value space of xsd:duration are values of the form `PnYnMnDTnHnMnS`
where the capital letters are delimiters. Delimiters may be omitted when the
corresponding member is not used.

A `long long` (`LONG64` or `int64_t`) type that contains a duration (time
lapse) in milliseconds is mapped to the built-in xsd:duration XSD type and
serialized with the custom serializer `custom/duration.h` that declares a
`xsd__duration` type:

    #import "custom/duration.h"  // import typedef long long xsd__duration;
    ... use xsd__duration ...

Compile and link your code with `custom/duration.c`.

The duration type `xsd__duration` can represent 106,751,991,167 days forward
and backward with millisecond precision.

A C++11 `std::chrono::nanoseconds` type is mapped to the built-in xsd:duration
XSD type and serialized with the custom serializer `custom/chrono_duration.h`
that declares a `xsd__duration` type:

    #import "custom/chrono_duration.h"  // import typedef std::chrono::duration xsd__duration;
    ... use xsd__duration ...

Compile and link your code with `custom/chrono_duration.cpp`.

Classes and structs                                                    {#toxsd9}
-------------------

Classes and structs are mapped to XSD complexTypes. The XML value space
consists of XML elements with attributes and subelements, possibly constrained
by validation rules that enforce element and attribute occurrence contraints,
numerical value range constraints, and string length and pattern constraints.

Classes that are declared with the gSOAP tools are limited to single
inheritence only. Structs cannot be inherited.

The class and struct name is bound to an XML namespace by means of the prefix
naming convention or by using [colon notation](#toxsd1):

    //gsoap ns schema namespace: urn:types
    class ns__record
    {
     public:
      std::string  name;
      uint64_t     SSN;
      ns__record  *spouse;
      ns__record();
      ~ns__record();
     protected:
      struct soap  *soap;
    };

In the example above, we also added a context pointer to the `struct soap` that
manages this instance. It is set when the instance is created in the engine's
context, for example when deserialized and populated by the engine.

The class maps to a complexType in the soapcpp2-generated schema:

    <complexType name="record">
      <sequence>
        <element name="name" type="xsd:string" minOccurs="1" maxOccurs="1"/>
        <element name="SSN" type="xsd:unsignedLong" minOccurs="1" maxOccurs="1"/>
        <element name="spouse" type="ns:record" minOccurs="0" maxOccurs="1" nillable="true"/>
      </sequence>
    </complexType>

### Serializable versus transient types and members

Public data members of a class or struct are serialized. Private and protected
members are transient and not serializable.

Also `const` and `static` members are not serializable, with the exception of
`const char*` and `const wchar_t*`.

Types and specific class/struct members can be made transient by using the
`extern` qualifier:

    extern class std::ostream;  // declare 'std::ostream' transient
    class ns__record
    {
     public:
      extern int       num;         // not serialized
      std::ostream     out;         // not serialized
      static const int MAX = 1024;  // not serialized
    };

By declaring `std::ostream` transient we can use this type where we need it and
without soapcpp2 complaining that this class is not defined.

### Volatile classes and structs

Classes and structs can be declared `volatile` with the gSOAP tools. This means
that they are already declared elsewhere in our project's source code. We do
not want soapcpp2 to generate a second definition for these types.

For example, `struct tm` is declared in `<time.h>`. We want it serializable and
serialize only a selection of its data members:

    volatile struct tm
    {
      int    tm_sec;    // seconds (0 - 60)
      int    tm_min;    // minutes (0 - 59)
      int    tm_hour;   // hours (0 - 23)
      int    tm_mday;   // day of month (1 - 31)
      int    tm_mon;    // month of year (0 - 11)
      int    tm_year;   // year - 1900
    };

We can declare classes and structs `volatile` for any such types we want to
serialize by only providing the public data members we want to serialize.

Colon notation comes in handy to bind an existing class or struct to a schema.
For example, we can change the `tm` name as follows without affecting the code
that uses `struct tm` generated by soapcpp2:

    volatile struct ns:tm { ... }

This struct maps to a complexType in the soapcpp2-generated schema:

    <complexType name="tm">
      <sequence>
        <element name="tm-sec" type="xsd:int" minOccurs="1" maxOccurs="1"/>
        <element name="tm-min" type="xsd:int" minOccurs="1" maxOccurs="1"/>
        <element name="tm-hour" type="xsd:int" minOccurs="1" maxOccurs="1"/>
        <element name="tm-mday" type="xsd:int" minOccurs="1" maxOccurs="1"/>
        <element name="tm-mon" type="xsd:int" minOccurs="1" maxOccurs="1"/>
        <element name="tm-year" type="xsd:int" minOccurs="1" maxOccurs="1"/>
      </sequence>
    </complexType>

### Mutable classes and structs

Classes and structs can be declared `mutable` with the gSOAP tools. This means
that their definition can be spread out over the source code. This promotes the
concept of a class or struct as a *row of named values*, also known as a *named
tuple*, that can be extended as needed with additional entries. Because these
types differ from the traditional object-oriented principles of classes and
objects, constructors and destructors cannot be defined (also because we cannot
guarantee merging these into one such that all members will be initialized). A
default constructor, copy constructor, assignment operation, and destructor
will be assigned.

    mutable struct ns__tuple
    {
      @std::string  id;
    };

    mutable struct ns__tuple
    {
      std::string  name;
      std::string  value;
    };

The members are collected into one definition generated by soapcpp2. Members
may be repeated from one definition to another, but only if their associated
types are identical. So a third extension with a `value` member with a
different type fails:

    mutable struct ns__tuple
    {
      duuble       value;  // BAD: value is already declared std::string
    };

The `mutable` concept has proven to be very useful when declaring and
collecting SOAP Headers for multiple services, which are collected into one
`struct SOAP_ENV__Header` by the soapcpp2 tool.

### Default member values

Class and struct data members may be declared with a default initialization
value that is provided "inline" with the declaration of the member:

    class ns__record
    {
     public:
      std::string name = "Joe";

These initializations are made by the default constructor that is added by
soapcpp2 to each class and struct. A constructor is only added when a default
constructor is not already defined with the class declaration.

Initializations can only be provided for members that have primitive types
(`bool`, `enum`, `time_t`, numeric and string types).

### Attribute members

Class and struct data members can be declared as XML attributes by annotating
their type with a `@` with the declaration of the member:

    class ns__record
    {
     public:
      @std::string name;
      @uint64_t    SSN;
      ns__record  *spouse;
    };

This class maps to a complexType in the soapcpp2-generated schema:

    <complexType name="record">
      <sequence>
        <element name="spouse" type="ns:record" minOccurs="0" maxOccurs="1" nillable="true"/>
      </sequence>
      <attribute name="name" type="xsd:string" use="required"/>
      <attribute name="SSN" type="xsd:unsignedLong" use="required"/>
    </complexType>

An example XML instance of `ns__record` is:

    <ns:record xmlns:ns="urn:types" name="Joe" SSN="1234567890">
      <spouse>
        <name>Jane</name>
        <SSN>1987654320</SSN>
      </spouse>
    </ns:record>

Attribute data members are restricted to primitive types (`bool`, `enum`,
`time_t`, numeric and string types), `xsd__hexBinary`, `xsd__base64Binary`, and
custom serializers, such as `xsd__dateTime`. Custom serializers for types that
may be used as attributes MUST define `soap_s2T` and `soap_T2s` functions that
convert values of type `T` to strings and back.

Attribute data members can be pointers and smart pointers to these types, which
permits attributes to be optional.

### (Smart) pointer members and their occurrence constraints

A public pointer-typed data member is serialized by following its (smart)
pointer(s) to the value pointed to.

Pointers that are NULL and smart pointers that are empty are serialized to
produce omitted element and attribute values, unless an element is required
and is nillable.

To control the occurrence requirements of pointer-based data members,
occurrence constraints are associated with data members in the form of a range
`minOccurs : maxOccurs`. For non-repeatable (meaning, not a container or array)
data members, there are only three reasonable occurrence constraints:

- `0:0` means that this element or attribute is prohibited.
- `0:1` means that this element or attribute is optional.
- `1:1` means that this element or attribute is required.

Pointer-based data members have a default `0:1` occurrence constraint, making
them optional, and their XSD schema local element/attribute definition is
marked as nillable. Non-pointer data members have a default `1:1` occurence
constraint, making them required.

A pointer data member that is explicitly marked as required with `1:1` will be
serialized as an element with an xsi:nil attribute, thus effectively revealing
the NULL property of its value.

A non-pointer data member that is explicitly marked as optional with `0:1` will
be set to its default value when no XML value is presented to the deserializer.
A default value can be assigned to data members that have primitive types.

Consider for example:

    class ns__record
    {
     public:
      std::shared_ptr<std::string>  name;              // optional (0:1)
      uint64_t                      SSN    0:1 = 999;  // forced this to be optional with default 999
      ns__record                   *spouse 1:1;        // forced this to be required (only married people)
    };

This class maps to a complexType in the soapcpp2-generated schema:

    <complexType name="record">
      <sequence>
        <element name="name" type="xsd:string" minOccurs="0" maxOccurs="1" nillable="true"/>
        <element name="SSN" type="xsd:unsignedLong" minOccurs="0" maxOccurs="1" default="999"/>
        <element name="spouse" type="ns:record" minOccurs="1" maxOccurs="1" nillable="true"/>
      </sequence>
    </complexType>

An example XML instance of `ns__record` with its `name` string value set to
`Joe`, `SSN` set to its default, and `spouse` set to NULL:

    <ns:record xmlns:ns="urn:types">
      <name>Joe</name>
      <SSN>999</SSN>
      <spouse xsi:nil="true"/>
    </ns:record>

### Container members and their occurrence constraints

Class and struct data members declared as a container `std::deque`, `std::list`,
`std::set`, and `std::vector` are serialized as a collection of values:

    class ns__record
    {
     public:
      std::vector<std::string>  names;
      uint64_t                  SSN;
    };

To practically limit the number of names within reasonable bounds, occurrence
constraints are associated with the container. Occurrence constraints are of
the form `minOccurs : maxOccurs`:

    class ns__record
    {
     public:
      std::vector<std::string>  names 1:10;
      uint64_t                  SSN;
    };

This class maps to a complexType in the soapcpp2-generated schema:

    <complexType name="record">
      <sequence>
        <element name="name" type="xsd:string" minOccurs="1" maxOccurs="10"/>
        <element name="SSN" type="xsd:unsignedLong" minOccurs="1" maxOccurs="1""/>
      </sequence>
    </complexType>

Because C does not support a container template library, we can use a
dynamically-sized array of values. This array is declared as a size-pointer
member pair:

    struct ns__record
    {
      $int      sizeofnames;  // array size
      char*    *names;        // array of char* names
      uint64_t  SSN;
    };

where the marker `$` with `int` denotes a special type that is used to store
the array size and to indicate that this is a size-pointer member pair that
declares a dynamically-sized array.

This class maps to a complexType in the soapcpp2-generated schema:

    <complexType name="record">
      <sequence>
        <element name="name" type="xsd:string" minOccurs="0" maxOccurs="unbounded" nillable="true"/>
        <element name="SSN" type="xsd:unsignedLong" minOccurs="1" maxOccurs="1""/>
      </sequence>
    </complexType>

To limit the number of names in the array within reasonable bounds, occurrence
constraints are associated with the array size member. Occurrence constraints
are of the form `minOccurs : maxOccurs`:

    struct ns__record
    {
      $int      sizeofnames 1:10;  // array size 1..10
      char*    *names;             // array of one to ten char* names
      uint64_t  SSN;
    };

This class maps to a complexType in the soapcpp2-generated schema:

    <complexType name="record">
      <sequence>
        <element name="name" type="xsd:string" minOccurs="1" maxOccurs="10" nillable="true"/>
        <element name="SSN" type="xsd:unsignedLong" minOccurs="1" maxOccurs="1""/>
      </sequence>
    </complexType>

### Union members

A union member in a class or in a struct cannot be serialized unless a
discriminating variant selector is provided that tells the serializer which
union field to serialize.

The variant selector is associated with the union as a selector-union member
pair, where the variant selector is a special `$int` member:

    class ns__record
    {
     public:
      $int  xORnORs;  // variant selector
      union choice
      {
        float x;
        int   n;
        char *s;
      } u;
      std::string name;
    };

The variant selector values are auto-generated based on the union name `choice`
and the names of its members `x`, `n`, and `s`:

- `xORnORs = SOAP_UNION_choice_x` when `u.x` is valid.
- `xORnORs = SOAP_UNION_choice_n` when `u.n` is valid.
- `xORnORs = SOAP_UNION_choice_s` when `u.s` is valid.
- `xORnORs = 0` when none are valid (should only be used with great care,
  because XML content validation may fail when content is required but absent).

This class maps to a complexType with a sequence and choice in the
soapcpp2-generated schema:

    <complexType name="record">
      <sequence>
        <choice>
          <element name="x" type="xsd:float" minOccurs="1" maxOccurs="1"/>
          <element name="n" type="xsd:int" minOccurs="1" maxOccurs="1"/>
          <element name="s" type="xsd:string" minOccurs="0" maxOccurs="1" nillable="true"/>
        </choice>
        <element name="names" type="xsd:string" minOccurs="1" maxOccurs="10" nillable="true"/>
      </sequence>
    </complexType>

### Adding get and set methods

A public `get` method may be added to a class or struct, which will be
triggered by the deserializer. This method will be invoked right after the
instance is populated by the deserializer. The `get` method can be used to
update or verify deserialized content. It should return `SOAP_OK` or set
`soap::error` to a nonzero error code and return it.

A public `set` method may be added to a class or struct, which will be
triggered by the serializer. The method will be invoked just before the
instance is serialized. Likewise, the `set` method should return `SOAP_OK` or
set set `soap::error` to a nonzero error code and return it.

For example, adding a `set` and `get` method to a class declaration:

    class ns__record
    {
     public:
      int set(struct soap*);  // triggered before serialization
      int get(struct soap*);  // triggered after deserialization

To add these and othe rmethods to classes and structs with wsdl2h and
`typemap.dat`, please see section [class and struct addition](#typemap3).

### Defining document root elements

To define and reference XML document root elements we use type names that start
with an underscore:

    class _ns__record

Alternatively, we can use a typedef to define a document root element with a
given type:

    typedef ns__record _ns__record;

This typedef maps to a global root element that is added to the
soapcpp2-generated schema:

    <element name="record" type="ns:record"/>

An example XML instance of `_ns__record` is:

    <ns:record xmlns:ns="urn:types">
      <name>Joe</name>
      <SSN>1234567890</SSN>
      <spouse>
        <name>Jane</name>
        <SSN>1987654320</SSN>
      </spouse>
    </ns:record>

Global-level element/attribute definitions are also referenced and/or added to
the generated schema when serializable data members reference these by their
qualified name:

    typedef std::string _ns__name 1:100;
    class _ns__record
    {
     public:
      @_QName      xsi__type;  // built-in XSD attribute xsi:type
      _ns__name    ns__name;   // ref to global ns:name element
      uint64_t     SSN;
      _ns__record *spouse;
    };

These types map to the following comonents in the soapcpp2-generated schema:

    <simpleType name="name">
      <restriction base="xsd:string">
        <minLength value="1"/>
        <maxLength value="100"/>
      </restriction>
    </simpleType>
    <element name="name" type="ns:name"/>
    <complexType name="record">
      <sequence>
        <element ref="ns:name" minOccurs="1" maxOccurs="1"/>
        <element name="SSN" type="xsd:unsignedLong" minOccurs="1" maxOccurs="1"/>
        <element name="spouse" type="ns:record" minOccurs="0" maxOccurs="1" nillable="true"/>
      </sequence>
      <attribute ref="xsi:type" use="optional"/>
    </complexType>
    <element name="record" type="ns:record"/>

However, we must warn against using qualified member names when their types do
not match their definitions:

    class _ns__record
    {
     public:
      int  ns__name;  // BAD: element ns:name is NOT of an int type

Therefore, we recommend to avoid qualified member names and only use them when
referring to standard XSD elements and attributes, such as `xsi__type`, and
`xsd__lang`. The soapcpp2 tool does not prevent abuse of this mechanism.

### Operations on classes and structs

The following functions/macros are generated by soapcpp2 for each type `T`,
which should make it easier to send, receive, and copy XML data in C and in
C++:

- `int soap_write_T(struct soap*, T*)` writes an instance of `T` to a FILE (via
   `FILE *soap::sendfd)`) or to a stream (via `std::ostream *soap::os`).
   Returns `SOAP_OK` on success or an error code, also stored in `soap->error`.

- `int soap_read_T(struct soap*, T*)` reads an instance of `T` from a FILE (via
   `FILE *soap::recvfd)`) or from a stream (via `std::istream *soap::is`).
   Returns `SOAP_OK` on success or an error code, also stored in `soap->error`.

- `void soap_default_T(struct soap*, T*)` sets an instance `T` to its default
  value, resetting members of a struct to their initial values (for classes we
  use method `T::soap_default`, see below).

- `T * soap_dup_T(struct soap*, T *dst, const T *src)` (soapcpp2 option `-Ec`)
  deep copy `src` into `dst`, replicating all deep cycles and shared pointers
  when a managing soap context is provided as argument. When `dst` is NULL,
  allocates space for `dst`. Deep copy is a tree when argument is NULL, but the
  presence of deep cycles will lead to non-termination. Use flag
  `SOAP_XML_TREE` with managing context to copy into a tree without cycles and
  pointers to shared objects. Returns `dst` (or allocated space when `dst` is
  NULL).

- `void soap_del_T(const T*)` (soapcpp2 option `-Ed`) deletes all
  heap-allocated members of this object by deep deletion ONLY IF this object
  and all of its (deep) members are not managed by a soap context AND the deep
  structure is a tree (no cycles and co-referenced objects by way of multiple
  (non-smart) pointers pointing to the same data). Can be safely used after
  `soap_dup(NULL)` to delete the deep copy. Does not delete the object itself.

When in C++ mode, soapcpp2 tool adds several methods to classes and structs, in
addition to adding a default constructor and destructor (when these were not
explicitly declared).

The public methods added to a class/struct `T`:

- `virtual int T::soap_type(void)` returns a unique type ID (`SOAP_TYPE_T`).
  This numeric ID can be used to distinguish base from derived instances.

- `virtual void T::soap_default(struct soap*)` sets all data members to
  default values.

- `virtual void T::soap_serialize(struct soap*) const` serializes object to
  prepare for SOAP 1.1/1.2 encoded output (or with `SOAP_XML_GRAPH`) by
  analyzing its (cyclic) structures.

- `virtual int T::soap_put(struct soap*, const char *tag, const char *type) const`
  emits object in XML, compliant with SOAP 1.1 encoding style, return error
  code or `SOAP_OK`. Requires `soap_begin_send(soap)` and
  `soap_end_send(soap)`.

- `virtual int T::soap_out(struct soap*, const char *tag, int id, const char *type) const`
  emits object in XML, with tag and optional id attribute and xsi:type, return
  error code or `SOAP_OK`. Requires `soap_begin_send(soap)` and
  `soap_end_send(soap)`.

- `virtual void * T::soap_get(struct soap*, const char *tag, const char *type)`
  Get object from XML, compliant with SOAP 1.1 encoding style, return pointer
  to object or NULL on error. Requires `soap_begin_recv(soap)` and
  `soap_end_recv(soap)`.

- `virtual void *soap_in(struct soap*, const char *tag, const char *type)`
  Get object from XML, with matching tag and type (NULL matches any tag and
  type), return pointer to object or NULL on error. Requires
  `soap_begin_recv(soap)` and `soap_end_recv(soap)`

- `virtual T * T::soap_alloc(void) const` returns a new object of type `T`,
  default initialized and not managed by a soap context.

- `virtual T * T::soap_dup(struct soap*) const` (soapcpp2 option `-Ec`) returns
  a duplicate of this object by deep copying, replicating all deep cycles and
  shared pointers when a managing soap context is provided as argument. Deep
  copy is a tree when argument is NULL, but the presence of deep cycles will
  lead to non-termination. Use flag `SOAP_XML_TREE` with managing context to
  copy into a tree without cycles and pointers to shared objects.

- `virtual void T::soap_del() const` (soapcpp2 option `-Ed`) deletes all
  heap-allocated members of this object by deep deletion ONLY IF this object
  and all of its (deep) members are not managed by a soap context AND the deep
  structure is a tree (no cycles and co-referenced objects by way of multiple
  (non-smart) pointers pointing to the same data).Can be safely used after
  `soap_dup(NULL)` to delete the deep copy. Does not delete the object itself.

Special classes and structs                                           {#toxsd10}
---------------------------

A class or struct with the following layout is a one-dimensional SOAP Array
type:

    class Array
    {
     public:
      T   *__ptr;   // array pointer
      int  __size;  // array size
    };

where `T` is the array element type. A multidimensional SOAP Array is:

    class Array
    {
     public:
      T   *__ptr;      // array pointer
      int  __size[N];  // array size of each dimension
    };

where `N` is the constant number of dimensions. The pointer points to an array
of `__size[0]*__size[1]* ... * __size[N-1]` elements.

A special case of a one-dimensional array is used to define xsd:hexBinary and
xsd:base64Binary types when the pointer type is `unsigned char`:

    class xsd__hexBinary
    {
     public:
      unsigned char *__ptr;   // points to raw binary data
      int            __size;  // size of data
    };

and

    class xsd__base64Binary
    {
     public:
      unsigned char *__ptr;   // points to raw binary data
      int            __size;  // size of data
    };

A class or struct with a binary content layout can be extended to support
MIME/MTOM (and older DIME) attachments, such as in xop:Include elements:

    //gsoap xop schema import: http://www.w3.org/2004/08/xop/include
    class _xop__Include
    {
     public:
      unsigned char *__ptr;   // points to raw binary data
      int            __size;  // size of data
      char          *id;      // NULL to generate an id, or set to a unique UUID
      char          *type;    // MIME type of the data
      char          *options; // optional description of MIME attachment
    };

Attachments are beyond the scope of this document and we refer to the gSOAP
user guide for more details.

A class or struct with the following layout is a complexType with simpleContent
wrapper:

    class ns__simple
    {
     public:
      T   __item;
    };

A wrapper class/struct may have any number of attributes declared with `@`.

Memory management                                                      {#memory}
=================

Memory management with the `soap` context enables us to allocate data in
context-managed heap space that can be collectively deleted. All deserialized
data is placed on the context-managed heap by the gSOAP engine.

Memory management in C                                                {#memory1}
----------------------

In C (wsdl2h option `-c` and soapcpp2 option `-c`), the gSOAP engine allocates
data on a context-managed heap with:

- `void *soap_malloc(struct soap*, size_t len)`.

The `soap_malloc` function is a wrapper around `malloc`, but which also allows
the `struct soap` context to track all heap allocations for collective deletion
with `soap_end(soap)`:

    #include "soapH.h"
    #include "ns.nsmap"
    ...
    struct soap *soap = soap_new();  // new context
    ...
    struct ns__record *record = soap_malloc(soap, sizeof(struct ns__record));
    soap_default_ns__record(soap, record);
    ...
    soap_destroy(soap);  // only for C++, see section on C++ below
    soap_end(soap);      // delete record and all other heap allocations
    soap_free(soap);     // delete context

The soapcpp2 auto-generated deserializers in C use `soap_malloc` to allocate
and populate deserialized structures, which are managed by the context for
collective deletion.

To make `char*` and `wchar_t*` string copies to the context-managed heap, we
can use the functions:

- `char *soap_strdup(struct soap*, const char*)` and

- `wchar_t *soap_wstrdup(struct soap*, const wchar_t*)`.

We use the soapcpp2 auto-generated `soap_dup_T` functions to duplicate data
into another context (this requires soapcpp2 option `-Ec` to generate), here
shown for C with the second argument `dst` NULL because we want to allocate a
new managed structure:

    struct soap *other_soap = soap_new();  // another context
    struct ns__record *other_record = soap_dup_ns__record(other_soap, NULL, record);
    ...
    soap_destroy(other_soap);  // only for C++, see section on C++ below
    soap_end(other_soap);      // delete other_record and all of its deep data
    soap_free(other_soap);     // delete context

Note that the only reason to use another context and not to use the primary
context is when the primary context must be destroyed together with all of the
objects it manages while some of the objects must be kept alive. If the objects
that are kept alive contain deep cycles then this is the only option we have,
because deep copy with a managing context detects and preserves these
cycles unless the `SOAP_XML_TREE` flag is used with the context:

    struct soap *other_soap = soap_new1(SOAP_XML_TREE);  // another context
    struct ns__record *other_record = soap_dup_ns__record(other_soap, NULL, record);

The resulting deep copy will be a full copy of the source data structure as a
tree without co-referenced data (i.e. no digraph) and without cycles. Cycles
are pruned and (one of the) pointers that forms a cycle is repaced by NULL.

We can also deep copy into unmanaged space and use the auto-generated
`soap_del_T()` function (requires soapcpp2 option `-Ed` to generate) to delete
it later, but we MUST NOT do this for any data that we suspect has deep cycles:

    struct ns__record *other_record = soap_dup_ns__record(NULL, NULL, record);
    ...
    soap_del_ns__record(other_record);  // deep delete record data members
    free(other_record);                 // delete the record

Cycles in the data structure will lead to non-termination when making unmanaged
deep copies. Consider for example:

    struct ns__record
    {
      const char  *name;
      uint64_t     SSN;
      ns__record  *spouse;
    };

Our code to populate a structure with a mutual spouse relationship:

    struct soap *soap = soap_new();
    ...
    struct ns__record pers1, pers2;
    soap_default_ns__record(soap, &pers1);
    soap_default_ns__record(soap, &pers2);
    pers1.name = "Joe";                     // OK to serialize static data
    pers1.SSN = 1234567890;
    pers1.spouse = &pers2;
    pers2.name = soap_strdup(soap, "Jane"); // allocates and copies a string
    pers2.SSN = 1987654320;
    pers2.spouse = &pers1;
    ...
    struct ns__record *pers3 = soap_dup_ns__record(NULL, NULL, &pers1);  // BAD
    struct ns__record *pers4 = soap_dup_ns__record(soap, NULL, &pers1);  // OK
    soap_set_mode(soap, SOAP_XML_TREE);
    struct ns__record *pers5 = soap_dup_ns__record(soap, NULL, &pers1);  // OK

As we can see, the gSOAP serializer can serialize any heap, stack, or static
allocated data, such as in our code above. So we can serialize the
stack-allocated `pers1` record as follows:

    soap->sendfd = fopen("record.xml", "w");
    soap_set_mode(soap, SOAP_XML_GRAPH);  // support id-ref w/o requiring SOAP
    soap_clr_mode(soap, SOAP_XML_TREE);   // if set, clear
    soap_write_ns__record(soap, &pers1);
    fclose(soap->sendfd);
    soap->sendfd = NULL;

which produces an XML document record.xml that is similar to:

    <ns:record xmlns:ns="urn:types" id="Joe">
      <name>Joe</name>
      <SSN>1234567890</SSN>
      <spouse id="Jane">
        <name>Jane</name>
        <SSN>1987654320</SSN>
        <spouse ref="#Joe"/>
      </spouse>
    </ns:record>

Deserialization of an XML document with a SOAP 1.1/1.2 encoded id-ref graph
leads to the same non-termination problem when we later try to copy the data
into unmanaged space:
    
    struct soap *soap = soap_new1(SOAP_XML_GRAPH);  // support id-ref w/o SOAP
    ...
    struct ns__record pers1;
    soap->recvfd = fopen("record.xml", "r");
    soap_read_ns__record(soap, &pers1);
    fclose(soap->recvfd);
    soap->recvfd = NULL;
    ...
    struct ns__record *pers3 = soap_dup_ns__record(NULL, NULL, &pers1);  // BAD
    struct ns__record *pers4 = soap_dup_ns__record(soap, NULL, &pers1);  // OK
    soap_set_mode(soap, SOAP_XML_TREE);
    struct ns__record *pers5 = soap_dup_ns__record(soap, NULL, &pers1);  // OK

Copying data with `soap_dup_T(soap)` into managed space is always safe. Copying
into unmanaged space requires diligence. But deleting unmanaged data is easy
with `soap_del_T()`.

We can also use `soap_del_T()` to delete structures that we created in C, but
only if these structures are created with `malloc` and do NOT contain pointers
to stack and static data.

Memory management in C++                                              {#memory2}
------------------------

In C++, the gSOAP engine allocates data on a managed heap using a combination
of `void *soap_malloc(struct soap*, size_t len)` and `soap_new_T()`, where `T`
is the name of a class, struct, or class template (container or smart pointer).
Heap allocation is tracked by the `struct soap` context for collective
deletion with `soap_destroy(soap)` and `soap_end(soap)`.

Only structs, classes, and class templates are allocated with `new` via
`soap_new_T(struct soap*)` and mass-deleted with `soap_destroy(soap)`.

There are four variations of `soap_new_T` for class/struct/template type `T`
that soapcpp2 auto-generates to create instances on a context-managed heap:

- `T * soap_new_T(struct soap*)` returns a new instance of `T` with default data
  member initializations that are set with the soapcpp2 auto-generated `void
  T::soap_default(struct soap*)` method), but ONLY IF the soapcpp2
  auto-generated default constructor is used that invokes `soap_default()` and
  was not replaced by a user-defined default constructor.

- `T * soap_new_T(struct soap*, int n)` returns an array of `n` new instances of
  `T`. Similar to the above, instances are initialized.

- `T * soap_new_req_T(struct soap*, ...)` returns a new instance of `T` and sets
  the required data members to the values specified in `...`. The required data
  members are those with minOccurs > 0, see the subsection on occurrence
  constraints in [Classes and structs](#toxsd9).

- `T * soap_new_set_T(struct soap*, ...)` returns a new instance of `T` and sets
  the public/serializable data members to the values specified in `...`.

The above functions can be invoked with a NULL `soap` context, but we will be
responsible to use `delete T` to remove this instance from the unmanaged heap.

Primitive types and arrays of these are allocated with `soap_malloc` by the
gSOAP engine. As we stated above, all types except for classes, structs, class
templates (containers and smart pointers) are allocated with `soap_malloc` for
reasons of efficiency.

We can use a C++ template to simplify the managed allocation and initialization
of primitive values as follows (this is for primitive types only, because we
should allocate structs and classes with `soap_new_T`):

    template<class T>
    T * soap_make(struct soap *soap, T val)
    {
      T *p = (T*)soap_malloc(soap, sizeof(T));
      if (p)
        *p = val;
      return p;
    }

For example, assuming we have the following class:

    class ns__record
    {
     public:
      std::string  name;    // required name
      uint64_t    *SSN;     // optional SSN
      ns__record  *spouse;  // optional spouse
    };

We can instantiate a record by using the auto-generated
`soap_new_set_ns__record` and our `soap_make` to create a SSN value on the
managed heap:

    soap *soap = soap_new();  // new context
    ...
    ns__record *record = soap_new_set_ns__record(
        soap,
        "Joe",
        soap_make<uint64_t>(soap, 1234567890),
        NULL);
    ...
    soap_destroy(soap);  // delete record and all other managed instances
    soap_end(soap);      // delete managed soap_malloc'ed heap data
    soap_free(soap);     // delete context

Note however that the gSOAP serializer can serialize any heap, stack, or static
allocated data. So we can also create a new record as follows:

    uint64_t SSN = 1234567890;
    ns__record *record = soap_new_set_ns__record(soap, "Joe", &SSN, NULL);

which will be fine to serialize this record as long as the local `SSN`
stack-allocated value remains in scope when invoking the serializer and/or
using `record`. It does not matter if `soap_destroy` and `soap_end` are called
beyond the scope of `SSN`.

To facilitate our class methods to access the managing context, we can add a
soap context pointer to a class/struct:

    class ns__record
    {
      ...
      void create_more();  // needs a context to create more internal data
     protected:
      struct soap *soap;   // the context that manages this instance, or NULL
    };

The context is set when invoking `soap_new_T` (and similar) with a non-NULL
context argument.

We use the soapcpp2 auto-generated `soap_dup_T` functions to duplicate data
into another context (this requires soapcpp2 option `-Ec` to generate), here
shown for C++ with the second argument `dst` NULL because we want to allocate a
new managed object:

    soap *other_soap = soap_new();  // another context
    ns__record *other_record = soap_dup_ns__record(other_soap, NULL, record);
    ...
    soap_destroy(other_soap);  // delete record and other managed instances
    soap_end(other_soap);      // delete other data (the SSNs on the heap)
    soap_free(other_soap);     // delete context

To duplicate base and derived instances when a base class pointer or reference
is provided, use the auto-generated method `T * T::soap_dup(struct soap*)`:

    soap *other_soap = soap_new();  // another context
    ns__record *other_record = record->soap_dup(other_soap);
    ...
    soap_destroy(other_soap);  // delete record and other managed instances
    soap_end(other_soap);      // delete other data (the SSNs on the heap)
    soap_free(other_soap);     // delete context

Note that the only reason to use another context and not to use the primary
context is when the primary context must be destroyed together with all of the
objects it manages while some of the objects must be kept alive. If the objects
that are kept alive contain deep cycles then this is the only option we have,
because deep copy with a managing context detects and preserves these
cycles unless the `SOAP_XML_TREE` flag is used with the context:

    soap *other_soap = soap_new1(SOAP_XML_TREE);  // another context
    ns__record *other_record = record->soap_dup(other_soap);  // deep tree copy

The resulting deep copy will be a full copy of the source data structure as a
tree without co-referenced data (i.e. no digraph) and without cycles. Cycles
are pruned and (one of the) pointers that forms a cycle is repaced by NULL.

We can also deep copy into unmanaged space and use the auto-generated
`soap_del_T()` function or the `T::soap_del()` method (requires soapcpp2 option
`-Ed` to generate) to delete it later, but we MUST NOT do this for any data
that we suspect has deep cycles:

    ns__record *other_record = record->soap_dup(NULL);
    ...
    other_record->soap_del();  // deep delete record data members
    delete other_record;       // delete the record

Cycles in the data structure will lead to non-termination when making unmanaged
deep copies. Consider for example:

    class ns__record
    {
      const char  *name;
      uint64_t     SSN;
      ns__record  *spouse;
    };

Our code to populate a structure with a mutual spouse relationship:

    soap *soap = soap_new();
    ...
    ns__record pers1, pers2;
    pers1.name = "Joe";
    pers1.SSN = 1234567890;
    pers1.spouse = &pers2;
    pers2.name = "Jane";
    pers2.SSN = 1987654320;
    pers2.spouse = &pers1;
    ...
    ns__record *pers3 = soap_dup_ns__record(NULL, NULL, &pers1);  // BAD
    ns__record *pers4 = soap_dup_ns__record(soap, NULL, &pers1);  // OK
    soap_set_mode(soap, SOAP_XML_TREE);
    ns__record *pers5 = soap_dup_ns__record(soap, NULL, &pers1);  // OK

Note that the gSOAP serializer can serialize any heap, stack, or static
allocated data, such as in our code above. So we can serialize the
stack-allocated `pers1` record as follows:

    soap->sendfd = fopen("record.xml", "w");
    soap_set_mode(soap, SOAP_XML_GRAPH);  // support id-ref w/o requiring SOAP
    soap_clr_mode(soap, SOAP_XML_TREE);   // if set, clear
    soap_write_ns__record(soap, &pers1);
    fclose(soap->sendfd);
    soap->sendfd = NULL;

which produces an XML document record.xml that is similar to:

    <ns:record xmlns:ns="urn:types" id="Joe">
      <name>Joe</name>
      <SSN>1234567890</SSN>
      <spouse id="Jane">
        <name>Jane</name>
        <SSN>1987654320</SSN>
        <spouse ref="#Joe"/>
      </spouse>
    </ns:record>

Deserialization of an XML document with a SOAP 1.1/1.2 encoded id-ref graph
leads to the same non-termination problem when we later try to copy the data
into unmanaged space:
    
    soap *soap = soap_new1(SOAP_XML_GRAPH);  // support id-ref w/o SOAP
    ...
    ns__record pers1;
    soap->recvfd = fopen("record.xml", "r");
    soap_read_ns__record(soap, &pers1);
    fclose(soap->recvfd);
    soap->recvfd = NULL;
    ...
    ns__record *pers3 = soap_dup_ns__record(NULL, NULL, &pers1);  // BAD
    ns__record *pers4 = soap_dup_ns__record(soap, NULL, &pers1);  // OK
    soap_set_mode(soap, SOAP_XML_TREE);
    ns__record *pers5 = soap_dup_ns__record(soap, NULL, &pers1);  // OK

Copying data with `soap_dup_T(soap)` into managed space is always safe. Copying
into unmanaged space requires diligence. But deleting unmanaged data is easy
with `soap_del_T()`.

We can also use `soap_del_T()` to delete structures in C++, but only if these
structures are created with `new` (and `new []` for arrays when applicable) for
classes, structs, and class templates and with `malloc` for anything else, and
the structures do NOT contain pointers to stack and static data.

Features and limitations                                             {#features}
========================

There are several context initialization flags and mode flags to control XML
serialization at runtime:

- `SOAP_XML_STRICT`: strictly validates XML while deserializing. Should not be
  used together with SOAP 1.1/1.2 encoding style of messaging.

- `SOAP_XML_INDENT`: produces indented XML.

- `SOAP_XML_CANONICAL`: c14n canonocalization, removes unnecessary `xmlns`
  bindings and adds them to appropriate places by applying c14n normalization
  rules. Should not be used together with SOAP 1.1/1.2 encoding style of
  messaging.

- `SOAP_XML_TREE`: write tree XML without id-ref, pruning data structure
  cycles to prevent nontermination.

- `SOAP_XML_GRAPH`: write graph (digraph and cyclic graphs with shared pointers
  to objects) using id-ref attributes. That is, XML with SOAP multi-ref
  encoded id-ref elements. This is a structure-preserving serialization format,
  because co-referenced data and also cyclic relations are accurately represented.

- `SOAP_XML_DEFAULTNS`: uses xmlns default bindings, assuming that the schema
  element form is "qualified" by default (be warned if it is not!).

- `SOAP_XML_NOTYPE`: removes all xsi:type attribuation. This may affect the
  quality of the deserializer, which relies on xsi:type attributes to distinguish
  base class instances from derived class instanced.

- `SOAP_C_UTFSTRING`: enables all `std::string` and `char*` strings to
  contain UTF-8 content. 

Additional notes with respect to the wsdl2h and soapcpp2 tools:

- Nested classes, structs, and typedefs in a gSOAP header file are unnested by
  soapcpp2.

- Use `#import "file.h"` instead of `#include` to import other header files in
  a gSOAP header file for soapcpp2.  The `#include` and `#define` directives are
  accepted, but deferred to the generated code.

- To remove any SOAP-specific bindings, use soapcpp2 option `-0`.

- A gSOAP header file for soapcpp2 should not include any code statements, only
  data type declarations.

- C++ namespaces are supported, use wsdl2h option `-qname`. Or add a `namespace
  name { ... }` to the header file, but the `{ ... }` MUST cover the entire
  header file content from begin to end.
  
- Optional DOM support can be used to store mixed content or literal XML
  content. Otherwise, mixed content may be lost. Use wsdl2h option `-d` for
  DOM support and compile and link with `dom.c` or `dom.cpp`.


Removing SOAP namespaces from XML payloads                              {#nsmap}
==========================================

The soapcpp2 tool generates a `.nsmap` file that includes two bindings for SOAP
namespaces. We can remove all SOAP namespaces (and SOAP processing logic) with
soapcpp2 option `-0` or by simply setting the two entries to NULL:

    SOAP_NMAC struct Namespace namespaces[] =
    {
      {"SOAP-ENV", NULL, NULL, NULL},
      {"SOAP-ENC", NULL, NULL, NULL},
      ...

Note that once the `.nsmap` is generated, we can copy-paste the content into
our project code. However, if we rerun wsdl2h on updated WSDL/XSD files or
`typemap.dat` declarations then we need to use the updated table.


Examples                                                             {#examples}
========

Select the project files below to peruse the source code examples.


Source files
------------

- `address.xsd`         Address book schema
- `address.cpp`         Address book app (reads/writes address.xml file)
- `addresstypemap.dat`  Schema namespace prefix name preference for wsdl2h
- `graph.h`             Graph data binding (tree, digraph, cyclic graph)
- `graph.cpp`           Test graph serialization as tree, digraph, and cyclic


Generated files
---------------

- `address.h`      gSOAP-specific data binding definitions from address.xsd
- `addressStub.h`  C++ data binding definitions
- `addressH.h`     Serializers
- `addressC.cpp`   Serializers
- `address.xml`    Address book data generated by address app
- `graphStub.h`    C++ data binding definitions
- `graphH.h`       Serializers
- `graphC.cpp`     Serializers
- `g.xsd`          XSD schema with `g:Graph` complexType
- `g.nsmap`        xmlns bindings namespace mapping table


Build steps
-----------

Building the AddressBook example:

    wsdl2h -g -t addresstypemap.dat address.xsd
    soapcpp2 -0 -CS -I../../import -p address address.h
    c++ -I../.. address.cpp addressC.cpp -o address -lgsoap++

Building the graph serialization example:

    soapcpp2 -CS -I../../import -p graph graph.h
    c++ -I../.. graph.cpp graphC.cpp -o graph -lgsoap++

To compile without using the `libgsoap++` library: simply compile
`stdsoap2.cpp` together with the above.

Usage
-----

To execute the AddressBook example:

    ./address

To execute the Graph serialization example:

    ./graph

