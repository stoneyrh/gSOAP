
[![Go down](images/go-down.png) Go down](#latest) to view the latest changes

Version 1.1 (1/1/2000)
---
- Added typedef conventions.
- Added enumerations.
- Added hexBinary encoding.
- Added base64 encoding.
- Enable pass by reference operator (&) for output parameter.
- Enable specification of methods in classes.

Version 1.2 (9/9/2001)
---
- Added WSDL generator.

Version 1.2w (9/14/2001)
---
- Win32 port.
- Fixed a socket communication problem in win32 version.
- Added namespace name pattern matching to ease validation.

Version 1.2.1 (10/24/2001)
---
- Added chunked HTTP 1.1 transfer support.
- Improved buffering.
- Fixed a problem with nested vector allocation.

Version 1.2.2 (11/2/2001)
---
- Support for special XML element names with dots, underscores, and center dots (see documentation section 5.3).
- Fixed a decoding problem with dynamic array of pointers to polymorphic objects.
- Fixed an encoding problem with enumerations.
- Added a "safe-mode" flag to disable serialization of multi-referenced objects with `soap_disable_href = 1;`
- You can set this global flag anywere in the code, but at least before serialization is performed. It will disable the use of href attributes when sending multi-reference data. Instead, the data is copied in the payload. When set, this flag will hang the serializer when sending cyclic data structures.

Version 1.2.3 (12/5/2001)
---

- Added bool type encoding/decoding.
- Added dynamic multi-dimensional arrays.
- Added support for primitive polymorphic types.
- Added full support for CDATA content decoding.
- More convenient customization of SOAP Headers and Faults. No separate soapheader.h and soapfault.h files required (and therefore no .cpp files have to be created for these). Instead, the compiler generates customized SOAP Header and SOAP Fault marshalling routines when struct/class `SOAP_ENV__Fault` and/or `SOAP_ENV__Header` are specified in the header file input to the compiler.
- On demand generation of the marshalling routines for the primitive types, which reduces the size of the executables.
- Fixed a WSDL incompatibility problem in the WSDL generator.
- Improved decoding of multi-reference elements (no *`xsi:type`* required anymore in receiving message so gSOAP does not break).
- Improved support for encoding/decoding indirect data (e.g. pointers to pointers to data).
- Improved encoding of data with the same pointers to shared data but with the shared data declared with different XML schema types (formerly encoded as multi-reference data which could cause type incmpatibilities at the receiving side). For example, in the declarations `typedef char *xsd__NCName; xsd__NCName *s="SOAP"; char *t = s;` the pointers s and t point to the same data, but will not be encoded as multi-reference data since the types are different.
- Added flag `soap_enable_null = 1;`
- When set, all NULL pointers will be explicitly encoded. By default, NULL pointers are omitted from the SOAP payload. For example, with this flag set all NULL strings and other NULL pointer data will appear as nil values in the SOAP payload.
- Added flag: `soap_enable_embedding = 1;`
- When set, multi-reference data will be encoded inline which will guarantee the exact preservation of the structure of the data transmitted. However, some SOAP implementations do not support embedding inline multi-reference data although this encoding style is likely to be included in future verions of the SOAP protocol. The flag is useful when creating C++ applications that need to communicate data to eachother and the data structures need to be preserved. Setting this flag may cause a duplication of multi-reference data by the receiver created with the SOAP stub compiler when the data is part of a struct/class or array. The data is not copied by the receiver when the struct/class or arrays use pointers to the data type.
- Added the ability to declare virtual destructors.
- Fixed a compilation error with fixed-size array of pointers.
- Fixed a problem with padding in Base64 (en/de)coding.
- Fixed XML entity decoding (hexadecimal).
- Added encoding of sparse arrays. A sparse array MUST be declared as a (fixed-size of dynamic) array of pointers. NULL pointer values are omitted from the output and *`SOAP-ENC:position`* attributes are used for non-NULL elements.
- Changed `soap_put` and `soap_get` functions to include explicit schema type parameters. This fixed a problem with Web services that need to return typedef-ed XML schema types The new stdsoap.cpp and stdsoap.h files are incompatible with the previous version(s).
- Added the ability to ignore the names of accessors when decoding fields through the use of a leading underscore (`_`) in a field name. For example: `ns__mymethod(xsd__string in, xsd__string &_return);`
- When used to invoke a remote method, the actual element name of the remote return parameter used by the service is insignificant.
- Improved memory management. Added new function: `soap_destroy()` to remove all class instances.
- Improved documentation.
- Added `time_t` type support, but still need to add encoding/decoding routines to the runtime (next version).
- Added `wchar_t` type support, but still need to add encoding/decoding routines to the runtime (next version).

Version 1.2.4 (12/17/2001)
---
- Added support for wide character strings (`wchar_t*`).
- Added support for `time_t` type.
- Added support for SOAP literal encoding.
- Fixed an obscure bug in the deserialization of data from the SOAP4R toolkit that caused the deserializer to hang.
- Fixed a problem with the `soap_disable_href` flag.
- Fixed a problem with the position attributes in sparse multi-dimensional arrays.
- Fixed a problem with the generation of .nsmap files.
- Fixed a problem with mixed content decoding in strings.

Version 1.2.5 (12/27/2001)
---
- Fixed a memory leak in the block allocation scheme used for strings, hexBinary, and base64 types.
- Fixed a bug in the WSDL generator for fixed-size arrays.
- Fixed a problem with the use of trailing underscores in field names in struct/class declarations.

Version 1.2.6 (1/25/2002)
---
- Improved portability.
- Improved id/href hash table efficiency and storage.
- Improved namespace URI matching with wildcards.
- Improved stand-alone deployment.
- Added `soap_disable_response_count` flag.
- Fixed operator declaration parsing (cast operators).
- Fixed a WSDL generator bug for output parameters and enumeration types.
- Renamed function `soap_return_fault()` into `soap_send_fault()`.

Version 2.0 (2/2/2002)
---
- Rewrote the compiler (soapcpp2) and the run-time engine libraries to create a thread safe implementation.

Versions 1.2.7 and 2.0.1 (2/11/2002)
---
- Added new soapcpp2 compiler options (-h -c -d -p).
- Added optional specification of service name, location, and namespace URI in header file.
- Improved interoperability.

Versions 1.2.8 and 2.0.2 (2/24/2002)
---
- Added function callbacks to support customized I/O and HTTP operations. This allows for plug-in HTTP code, NSAPI interface code, reading/writing from/to files or string buffers, etc.
- Added HTTP 1.0/1.1 keep-alive support.
- Added HTTP 1.1 chunked transfer support.
- Added `soap_disable_request_count` flag.
- Added `soap_enable_array_overflow` flag.
- Added type naming conventions to serialize elements without generating *`xsi:type`* attributes.
- Fixed a fixed-size array decoding problem (type mismatch).
- Fixed `</sequence/>` print bug in the WSDL generator.

Versions 1.3 and 2.1 (3/10/2002)
---
- Added client-side SSL (HTTPS) support (thanks to Massimo Cafaro for his suggestions).
- Added a naming convention for dynamic array `__ptr` fields which enables the naming of the XML tags of array elements.
- Added WSDL Header and Fault schema generation.
- Improved doc/literal encoding style.
- Improved WSDL service/schema namespace generation.
- Fixed *`SOAP-ENV:Header`* to be self contained.
- Fixed WSDL generation of xsd schema types declared as string.
- Fixed a method overriding type clash for derived classes.
- Fixed spurious occurrence of `id="-1"` with `soap_enable_null` flag enabled.
- Fixed a front-end gSOAP compiler problem with forward and cyclic struct declarations.

Versions 1.3.1 and 2.1.1 (3/25/2002)
---
- Added header file source constructs to support transient data types and transient struct/class fields to control gSOAP's code generatiion window for (de)serialization routines.
- Added callback for handling XML elements that are ignored on the receiving side (e.g. because of schema type problems). This feature is intended to enhance the reliability of services/clients.
- Added server-side SSL support and included an example multi-threaded stand-alone SSL secure SOAP server example.
- Added proxy server support.
- Improved message logging in gSOAP 2.1.1 (thanks to Jessie Ragsdale for his suggestions).
- Fixed WSDL generation for dynamic arrays.
- Fixed deserialization of empty multi-ref derived class instances.

Versions 1.3.2 and 2.1.2 (4/15/2002)
---
- Added socket timeout management.
- Added optional client and server cookie support.
- Added support for `maxOccurs="unbounded"` for arbitrary elements in complexTypes (not just limited to SOAP arrays).
- Improved generation of schema *`xs:extension`* definitions to allow XML validation in the presence of class overriding.
- Fixed ULONG64 type handling.
- Fixed light validation problem (now rejects invalid XML schema URIs).
- Fixed a deserialization type mismatch with typedef-ed pointer primitives.
- Fixed WSDL and schema interoperability problems.

Versions 1.3.3 and 2.1.3 (4/27/2002)
---
- Added `mustUnderstand` declaration qualifier for SOAP Header processing.
- Added `soap.actor` attribute for SOAP Header processing.
- Added method-header-part directive to identify methods with header message associations (WSDL requirement).
- Added bitmask (de)serialization.
- Added FastCGI support.
- Improved DLL build support (gSOAP 2.1.3 only).
- Improved WinCE support (gSOAP 2.1.3 only, thanks to Sean Ryan for his suggestions).
- Improved Mac OS X support.
- WSDL generator improvements and fixes.
- Workaround a bug in .NET SOAP Headers (non-unique id name values in .NET).
- Fixed `disable_href=1` bug.
- Fixed XML in string parsing code generation problem.

Versions 1.3.4 and 2.1.4 (6/9/2002)
---
- Added non-blocking `soap_accept()` with timeout management.
- Added support for SOAP Header and Fault declared as classes.
- Added syntax for `extern` declarations for transient types and fields.
- Added support for SOAP Headers in SOAP Fault messages.
- Added one-way SOAP messages (2.1.4 only).
- Added support for user-defined (de)serializers (2.1.4 only).
- Improved object memory management.
- Improved support for AIX and HP platforms.
- Fixed proxy server connect bug.
- Fixed an OpenSSL bug.
- Fixed `soap_instantiate_ClassX()` derived class allocation problem.
- Fixed generation of spurious .xsd files when lots of trailing underscores are used by identifiers in the header file.
- Fixed syntax error that occured with header files containing cyclic class declarations.
- Fixed 'class in struct' and 'vector of classes' VMT initialization bugs.

Version 2.1.5 (6/22/2002)
---
- Added non-blocking remote method calls (not supported in win32 version).
- Added specification of default values for struct/class fields.
- Added specification of minOccurs and maxOccurs for struct/class fields.
- Added support for the resolution operator `::` in identifiers.
- Added abstract method declaration support.
- Fixed WSDL generation of SOAP doc/lit.
- Fixed `WITH_FASTCGI` option.

Version 2.1.6 (7/10/2002)
---
- Added DIME attachment support.
- Added win32 non-blocking sockets.
- Changed `"%lld"` and `"%llu"` format strings into `"%I64d"` and `"%I64u"` format string for win32.
- Improved I/O.
- Fixed multi-dimensional dynamic array (de)serialization.
- Fixed WSDL enum and header namespace generation.

Version 2.1.7 (8/6/2002)
---
- Added generation of example SOAP/XML request and response messages by the compiler.
- Added RSA to SSL stack.
- Added two callbacks to the HTTP stack for efficient handling of HTTP headers in Apache-mod and IIS.
- Added compiler option -m (malloc() memory control) and updated doc on memory allocation policies.
- Added compiler option -i to support #include and #define directives.
- Improved HTTP cookie support to handle new and old cookie protocols.
- Improved external class (de)serialization support (std::string example is included).
- Fixed a SSL+proxy connect problem.
- Fixed uninitialized '//gsoap..executable:' string which caused sporadic exits.
- Fixed XML literal string encoding problem introduced with DIME.
- Fixed and removed WSDL duplicate response elements.
- Fixed LONG64 and ULONG64 types for WinCE.

Version 2.1.8 (8/28/2002)
---
- Added client-side proxy class source code generation.
- Added `soap.enable_strict` flag to enable very strict validation of messages (unknown namespace URIs and XML elements are not allowed).
- Added `soap.socket_flags` to control socket send and recv flags, e.g. to disable broken pipe signals (`soap.socket_flags=MSG_NOSIGNAL`).
- Added `//gsoap ns service method-action` header file directive.
- Added server-side `soap_receiver_fault()` and `soap_sender_fault()` functions to return SOAP 1.1 and SOAP 1.2 faults.
- Added seeding of the PRNG for SSL.
- Added soapcpp2 compiler option '-2' to automate SOAP 1.2 support (SOAP 1.2 features are Beta-release).
- Changed keep-alive support (see docs).
- Improved WSDL output.
- Workaround Bison 1.6 for win32 bug in gSOAP win32 version.
- Fixed a wild-card matching bug in `soap_tag_cmp()`.
- Fixed a string deserialization problem.
- Fixed a deserialization bug that can occur in a client-server combination with gSOAP and Apache Axis.

Version 2.1.9 (9/08/2002)
---
- Added HTTP proxy authentication.
- Added plug-in registry (Beta).
- Changed compiler exit status for compilation errors.
- Fixed stdin/stdout binary mode for DIME transfer with gSOAP for win32.
- Fixed win32 soapcpp2.exe bug in .res.xml file generation.

Version 2.1.10 (10/14/2002)
---
- Added `//gsoap ns service method-documentation:` directive.
- Added provision for additional documentation text with `//gsoap ns service name:` directive.
- Added #import pragma to (recursively) import gSOAP header files.
- Added plugin features and included a plugin example in 'extras' directory.
- Added automake/autoconf to generic gSOAP package (thanks to Christian Aberger).
- Added `-DWITH_LOCALTIME` compilation option to control `time_t` (de)serialization.
- Changed `time_t` (de)serialization (now uses timegm() and gmtime() to handle UTC). Found that mktime() library call is buggy on some systems.
- Improved and reorganized package directory structure.
- Fixed DDL linkage problem with instantiate/delete routines dealing with class instance memory management.
- Fixed compilation problem with Sun Workshop CC compiler and other compilers that adopt a specfic class VMT structure that could break object (de)serializers.
- Fixed bug in WSDL generator with multiple service namespaces.

Version 2.1.11 (11/10/2002)
---
- Added a multi-functional SOAP router application (message forwarding and message relay server).
- Added keep-alive support for asynchronous one-way messages.
- Improved parsing and handling of function prototypes and class methods.
- Improved modular design to enable the compilation and linkage of multiple client and service modules.
- Improved user-defined SOAP Fault detail handling.
- Fixed `SSL_accept` bug.
- Fixed serialization of pointers to dynamic arrays with multi-references.

Version 2.2 (12/12/2002)
---
- Added XML attribute (de)serialization support.
- Added XSD QName parsing and conversion support (`typedef char *xsd__QName`).
- Added compression support (`-DWITH_ZLIB` requires Zlib).
- Changed and improved transport and encoding settings by splitting up sending and receiving side flags into separate sets. Deprecated `soap.enable_X` and `soap.disable_X` flags.
- Improved keep-alive support (automatic client and server sides).
- Fixed a bug in mustUnderstand handling.
- Fixed a sporadic crash of the gSOAP compiler under win32.
- Fixed user-defined SOAP Fault output in WSDL generator.

Version 2.2.1 (12/18/2002)
---
- Added callbacks to enable custom streaming of DIME attachments.
- Fixed broken serialization of pointers to dynamic arrays with NULL `__ptr`.
- Fixed some WSDL issues.

Version 2.2.2 (1/25/2003)
---
- Added gzip support (`-DWITH_GZIP` requires Zlib).
- Added `faccept()` callback.
- Improved HTTP chunking.
- Fixed OpenSSL and `accept_timeout` (OpenSSL requires blocking sockets).
- Fixed HTTP header buffering.
- Fixed UTF8 decoding of a subset of characters (2-octet UTF).
- Fixed `operator==` parsing.
- Fixed a couple of WSDL issues.

Version 2.2.3 (3/2/2003)
---
- Added server-side HTTP basic authentication.
- Improved speed.
- Improved Tru64 portability.
- Changed `fpost()` function callback signature: added `int port` argument and added port number to the Host: HTTP header.
- Fixed memory leak in SSL connect when using OpenSSL DH.
- Fixed custom (de)serializer definitions parsing.
- Fixed a gzip/deflate bug with large transfers.
- Fixed use of `ftime()` for `time_t` (de)serialization with timezones.
- Fixed a problem with concurrent access to global namespace table by multiple threads.
- Fixed crash with //gsoap name directive.
- Fixed deserialization bug with multi-ref object encoding by Apache Axis.

Version 2.3.1-8 (9/24/2003)
---
- Updated SOAP 1.2 support (implements the SOAP 1.2 recommendation).
- Added STL container support and built-in `std::string` encoding.
- Added stand-alone Web server example to serve static and dynamic pages with a new HTTP GET plugin.
- Added `void*` (de)serialization, e.g. useful to support polymorphism with C applications and as an alternative to union types.
- Added XML DOM parser to support SOAP document encoding and for mixing of application data (de)serialization within an XML DOM.
- Added `WITH_LEAN` and `WITH_LEANER` compilation flags to improve support for small-memory devices such as WinCE and Palm.
- Added `SOAP_XML_CANONICAL` flag for canonical XML output (XML-C14N support and SOAP 1.2 normalization support).
- Added `//gsoap ns method-encoding:` directive.
- Added `//gsoap ns schema import:` directive.
- Added optional class getter and setter methods for object (de)serialization.
- Added `volatile` qualifier to indicate that certain type declarations should be treated 'as-is' when types are declared externally (e.g. part of a library).
- Added a new string notation for declarations to specify simpleType restriction patterns.
- Added soapcpp2 -I option to indicate #import path.
- Added support for (de)serialization of application data to C++ iostreams.
- Added `fsslauth()` callback.
- Added HTTP code error values.
- Added `SOAP_MALLOC` and `SOAP_FREE` macros to replace `malloc()` and `free()`.
- Added `soap_strdup(soap, string)` to copy strings in gSOAP's memory space.
- Added chunked streaming DIME output (thanks to J. Li for his suggestions).
- Added `SOAP_SOCKET` for win32 support (thanks to B. Gille for his suggestions).
- Added `SO_LINGER` support with `soap.connect_flags`.
- Added support for iso-8859-1 encoded XML parsing (default is utf8).
- Added #module directive to build shared libraries.
- Added C++ namespaces support to enable the compilation and linkage of multiple client and service codes.
- Added `WITH_CASEINSENSITIVETAGS` compilation flag to enable case insensitive XML parsing.
- Improved WSDL types schema output.
- Improved custom (de)serialization (note: extras/stringtest example has been changed).
- Improved SOAP literal encoding.
- Improved speed.
- Improved HTTP1.0/1.1 support.
- Removed `soap.defaultNamespace` in favor of automatic SOAP literal output based on `soap.encodingStyle` value.
- Fixed GMT to DST localtime conversion, but still issues with Sun Solaris.
- Fixed dynamic array `__offset` handling.
- Fixed class definition order.
- Fixed sporadic memory leak in HTTP cookie reader.
- Fixed multi-threaded server-side OpenSSL initialization.
- Fixed enumeration-based XML attribute deserialiation.
- Fixed *`SOAP-ENC:position`* attribute placement when arrays of pointers are mixed with nillable data.
- Fixed crash when parsing incorrect SOAP/XML attribute content.

Version 2.4 (12/20/2003)
---
- New WSDL parser and importer with improved support for SOAP document style and literal encoding.
- Added optional full schema validation (partial by default). Use `SOAP_XML_STRICT` flag.
- Added SSL session caching.
- Added `soap_set_namespaces()` to switch namespace tables.
- Fixed plugin memory leak. REQUIRED CHANGE to plugin allocation and copying.
- Fixed server-side blocking SSL accept.

Version 2.4.1 (01/07/2004)
---
- Changed `_USCORE_` and `_DOT_` naming conventions into `_USCORE` and `_DOT` to improve name mapping.
- Updated DOM parser (integrated into core gSOAP library).
- Improved WSDL parser and included several new features.
- Fixed WSDL schema import and WSDL literal output.

Version 2.5 (01/28/2004)
---
- Changed default encoding to SOAP RPC literal, as mandated by WS-I Basic Profile 1.0a and best practices.
- Added soapcpp2 compiler option -e for backward compatibility to gSOAP 2.4.1 and earlier that use SOAP RPC encoding defaults (helpful when migrating gSOAP projects to 2.5).
- Added automatic compiler-side WS-I Basic Profile 1.0a compliance warnings (warns before deployment).
- Added `fget()` callback for HTTP GET responses.
- Added IPv6 support contributed by Wind River Systems.
- Added VxWorks support contributed by Wind River Systems.
- Improved SOAP Fault handling.
- Improved interop with Axis RPC encoded response messages.
- Fixed `std::string` *`xsi:type`* attribute value.
- Fixed gSOAP 2.4 problems with serialization of enumeration values outside enumeration range.
- Fixed gSOAP 2.4 Pocket PC build problem.
- Fixed wsdl2h SOAP Fault and Header output.

Version 2.5.1 (02/12/2004)
---
- Improved WSDL output and WS-I BP1.0a compliance.
- Improved WSDL parser stability.
- Fixed problem parsing empty *`xsd:base64Binary`* elements.
- Fixed VxWorks and TRU64 portability issues.
- Fixed HTTP 400 error problem.
- Fixed soapcpp2 2.5 stability problem with one-way messages.

Version 2.5.2 (02/23/2004)
---
- Fixed WSDL generation warnings.
- Fixed LONG64 problem for PalmOS.
- Fixed module build link problem and 'components' example.

Version 2.6.0 (03/28/2004)
---
- Changed default style to doc/lit.
- Improved doc/lit WSDL handling.
- Improved soapcpp2 sample SOAP/XML message output.
- Added proxy support for wsdl2h.
- Fixed CONNECT method for proxy+SSL+gzip.

Version 2.6.1 (06/07/2004)
---
- Added optional multibyte character support.
- Improved WSDL output.
- Fixed STL container multi-ref deserialization problem with missing data.
- Fixed doc/lit server code generation from doc/lit WSDL definitions.

Version 2.6.2 (06/12/2004)
---
- Added Matlab(tm) code output (documentation is not availabel yet).
- Improved wsdl2h output for schema facets.
- Updated dom.cpp.
- Changed wsdl2h `std::string*` to `std::string` generation (to avoid double pointers `std::string**`). To obtain old behavior, add entry `xsd__string = | std::string* | std::string*` to typemap.dat.
- Fixed wsdl2h handling of *`xs:include>`*.
- Fixed wsdl2h handling of empty namespaces and absent targetNamespace schema attributes.
- Fixed MB char handling.

Version 2.7.0a/b/c/d/e/f (09/10/2004, 2/1/2005)
---
- Added multipart/related support for SOAP with MIME attachments (SwA).
- Added API functions for DIME open and closed layout support.
- Added `//gsoap schema elementForm:` and `//gsoap schema attributeForm` directives.
- Added `fclosesocket`, `fshutdownsocket`, `fpoll`, `fserveloop` callbacks.
- Added `soap.authrealm` string attribute to set basic authentication realm.
- Added `soap.prolog` string attribute to output optional XML prolog with processing instructions and directives.
- Added soapcpp2 option -t.
- Added wsdl2h options -e and -i.
- Added Palm OS and Symbian instructions and examples.
- Added xml-rpc support and examples.
- New `mod_gsoap` directory with modules for Apache 1.x/2.x, IIS, and WinInet
- Improved XML validation with `SOAP_XML_STRICT` flag.
- Improved memory footprint (reduced code size and reduced serialization overhead).
- Improved runtime id-ref serialization and deserialization.
- Improved wsdl2h translation.
- Updated dom.cpp.
- Updated webserver.c.
- Fixed issues with namespace qualification in doc/lit messages.
- Fixed `SOAP_HREF` error.
- Fixed proxy+SSL+zlib+chunking.
- Fixed SSL `select()` polling in `frecv()`.
- Fixed wsdl2h multidimensional SOAP arrays generate problem.

Version 2.7.1 (03/31/2005)
---
- Added new style of C++ proxy/object generation (objects derived from soap struct), enabled with soapcpp2 option -i.
- Added new features to wsdl2h generation to enable user-defined class/struct extensions such as member data and functions which are declared in typemap.dat.
- Added MIME multipart/form-data parsing to support HTTP POST HTML form handling (example included in samples/webserver).
- Added built-in memory leak detection enabled with `-DDEBUG`.
- Added UDDI v2 API and examples.
- Added 'WS' directory with WS protocols, such as WS-Addressing. This part will mature as more WS protocols will be added over time.
- Added `fseterror()` callback.
- Improved wsdl2h code output.
- Enhanced Web server sample code, and httpget and logging plugins.
- Fixed base64/hexBinary XML attribute serialization.
- Fixed a missing min/maxOccurs check for validation.

Version 2.7.2 (05/11/2005)
---
- Added SOAP-over-UDP IPv4/IPv6 support with examples.
- Added UDDI v2 API publish example.
- Improved wsdl2h parser accepting multiple WSDL/XSD files from the command line.
- Fixed wsdl2h schema import from included schema bug.
- Fixed SOAP 1.2 Fault Subcode handling.

Version 2.7.3 (06/27/2005)
---
- Added MTOM attachment support.
- Added 'plugin' directory with example plug-ins.
- Added 'import' directory for commonly #import-ed files such as stlvector.h.
- Added HTTP digest authentication plug-in 'plugins/httpda.h'.
- Added new import feature to wsdl2h using `ns=URI` convention for typemap.dat files, which enables wsdl2h to parse a WSDL that imports known WSDLs/schemas such as XOP, XML MIME, and WS-Addressing without actually reading the imported WSDL/schemas.
- Added soapcpp2 options -C and -S to generate client- or server-only codes.
- Added multi-path support for soappcpp2 option -I.
- Added C and C++ examples to combine multiple clients and services into one executable, see the samples/components directory in the package.
- Improved soapcpp2 option -e to generate SOAP RPC encoding style client/server codes by default (instead of document/literal by default).
- Fixed wsdl2h circular import of schemas.
- Fixed attributeGroup handling in wsdl2h.
- Fixed soapcpp2 handling of 'invisible' tags, e.g. `__any`, that should only be populated after all else failed to match the delivered XML content.
- Fixed validation of numeric enum constants with `SOAP_XML_STRICT` validation.
- Fixed engine's spurious log file generation issue.

Version 2.7.4 (07/24/2005)
---
- Added union serialization.
- Added `//gsoap ... type-documentation:` directive.
- Added `//gsoap ... method-mime-type:` directive.
- Added wsdl2h option -g for generating global element/attribute declarations for building modular .h files.
- Added wsdl2 option -y for generating typedef synonyms for structs and enums, with improved handling of typedefs by soapcpp2.
- Added wsdl2 option -u to disable union generation for *`xs:choice`*.
- Improved wsdl2h documentation generation.
- Improved wsdl2h and soapcpp2 MIME bindings.
- Improved dynamic memory allocation in engine with look-aside buffering.
- Fixed wsdl2h *`xs:complexContent/extension/attributeGroup`* translation.
- Fixed wsdl2h *`xs:choice`* with min/maxOccurs != 1 translation.
- Fixed wsdl2h *`soap:body parts`* attribute.

Version 2.7.5 (08/01/2005)
---
- Added *`xs:redefine`* processing to wsdl2h.
- Added HTML POST application/x-www-form-urlencoded plugin httpform.c (demo samples/webserver).
- Improved wsdl2h output.
- Fixed wsdl2h handling of duplicate values in single enum list.

Version 2.7.6 revision a/b/c/d/e (08/19/2005-02/18/06)
---
- Added WS-Security authentication, tokens, and signatures with new 'wsse' plugin, see documentation in 'doc' directory and 'samples/wsse'.
- Added 'doc' directory for documentation and moved soapdoc2.html and soapdoc2.pdf.
- Added `SOAP_XML_INDENT` flag.
- Added `soap_sender_fault_subcode()` and `soap_receiver_fault_subcode()` for SOAP 1.2 subcodes.
- Added `WITH_DOM` compile flag to enable flushing serialized and deserialized data to DOM (as well as a stream).
- Added soapcpp2 option -L.
- Added soapcpp2 option -a.
- Added wsdl2h option -a (for backward compatibility).
- Added wsdl2h option -d.
- Added `WITH_TCPFIN` comile flag to enable optional shutdown with how=1 (TCPFIN) after final sends to force EOF on other side (used to be the default behavior).
- Added schema substitutionGroup support.
- Added `soap_ssl_init()`.
- Improved DOM implementation and documentation.
- Improved AS400 portability.
- Improved schema choice support.
- Fixed wsdl2h multiple schema include issue.
- Fixed `soaps2dateTime` and `soap_timegm` functions when `timegm` is not available.
- Fixed exc-c14n formatting.
- Fixed SOAP 1.2 fault handling.
- Fixed missing `soap_flag___item2` issue.
- Fixed partial MIME boundary parsing issue.
- Fixed base64 parsing with `WITH_FAST`.
- Fixed MIME encoding of `\r\r` sequence.
- Fixed QName normalization issue.
- Fixed relative path schema import.
- Fixed MTOM cid matching with URL encoded IDs.
- Fixed wide-character (`wchar_t*`) XML attribute handling.
- Fixed `std::vector` element id-ref ordering in deserializer.

Version 2.7.7 (04/07/2006)
---
- Added streaming MTOM support (see also example in samples/mtom-stream).
- Added `long double` serialization support with custom serializer (`custom/long_double.h`).
- Added automatic detection of application's `soap_malloc()` data overruns in `-DDEBUG` mode.
- Improved `time_t` and `struct tm` (`custom/struct_tm.h`) serialization.
- Fixed issue with a wrongly generated namespace map entry.
- Fixed PalmOS socket connection issues.
- Fixed XML attributes with bitmask enumeration (`enum*`) values.

Version 2.7.8 revisions a/b/c (06/05/2006-06/24/2006))
---
- Added X509 extension checks.
- Added advanced MTOM streaming features.
- Added WS-Addressing plugin and demo.
- Moved soapcpp2 and wsdl2h to bin directory.
- Improved SOAP1.2 MTOM interop.
- Changed `soap_send_empty_response` function signature (additional status argument) for HTTP optional response binding.
- Changed `fmimewriteopen()` callback signature.
- Fixed wsdl2h top-level element and complexType name clash issue.
- Fixed HTTP chunking with empty response message body.
- Fixed WSSE digest authentication.
- Fixed WSDL response element output.
- Fixed SOAP 1.2 *`RPC:result`* handling with `SOAP_XML_STRICT` flag.
- Fixed WSSE signed response messages.
- Fixed Win32 max open connection exceeded checking.
- Fixed *`xsi:type`* matching for `__name` fields, which required a signature change of `soap_element_begin_in()` with an additional 'type' parameter (affecting custom deserializers, see custom dir).

Version 2.7.9 revisions a/b/c/d/e/f/g/h/i/j/k/l (10/24/2006-09/26/2007)
---
- Added wsdl2h option -j to omit the generation of SOAP Header and Faults for customization of these.
- Added wsdl2h option -q to generate C++ namespace qualified header files.
- Added `SOAP_SSLv3`, `SOAP_TLSv1`, `SOAP_SSL_SKIP_HOST_CHECK` flags.
- Added file input and output specifications (with `<` and `>`) to wsdl2h's typemap.dat to specify input and output for wsdl2h.
- Added WS-Addressing 2005/03 support.
- Added function `soap_free(soap)` that executes `soap_done(soap); free(soap)` and renamed previous `soap_free()` to `soap_temp_free()`.
- Added wsdl2h option `-_` to translate `_USCORE`.
- Added *`xsd:anyAttribute`* (using DOM parser) with wsdl2h option -d.
- Added multi-WSDL types section schema component merging.
- Added TCP keep-alive settings.
- Added QName list normalization.
- Changed soapcpp2 default rule for generating attribute form qualified to unqualified.
- Improved wsdl2h SOAP Fault coding.
- Improved performance and stability.
- Improved portability.
- Improved wsdl2h empty namespace handling ("" namespace).
- Improved wsdl2h and schema conversion to C and C++.
- Improved SSL timeouts and error handling.
- Improved soapcpp2 option -i (generate proxy and service classes).
- Improved class instance initialization.
- Improved use of IPv6.
- Improved proxy and server code output for soapcpp2 option -i.
- Improved soapcpp2 code output with additional exception checks.
- Fixed MIME/MTOM start id handling (SOAP message no longer required to be first attachment).
- Fixed WS-Security wsse plugin canonicalization format issue.
- Fixed ZIP content remainder parsing (CRC check).
- Fixed WSA API handling of messages with MIME/DIME attachments.
- Fixed wsdl2h *`xs:include`* relative path includes.
- Fixed `_XML` literal string parsing of root attributes.

Version 2.7.10 (01/27/2008)
---
- Combined pre-built win32, Linux i386, and Mac universal binaries into a single software distribution package to streamline the distribution.
- Added new Web service examples and removed XMethods dependence.
- Added soapcpp2 option -qname for automatic C++ namespace qualification.
- Added HTTP PUT, DELETE, HEAD callback support.
- Added ability to derive classes from soap struct (in gSOAP header files).
- Updated certificates and fixed cacerts.c.
- Improved soapcpp2 option -i proxy/server object generation.
- Improved socket timeout handling.
- Improved HTTP chunking handling and efficiency.
- Improved web server implementation.
- Improved soapcpp2 and wsdl2h warning and error reporting.
- Fixed dom parser handling of default xml namespace bindings.
- Fixed wsdl2h default ("") namespace handling.

Version 2.7.11 (07/26/2008)
---
- Added new wsseapi signature verification API functions.
- Added mutability property of `SOAP_ENV__Header` and `SOAP_ENV__Fault` struct to allow consistent redefinitions and on-the-fly member additions.
- Added wsdl2h -r option parameter for web proxy access.
- Added MINGW portability.
- Added configure option --disable-openssl to build wsdl2h and libraries without OpenSSL.
- Added `WITH_C_LOCALE` compilation flag to enable the use of `c_locale` and local-specific numeric conversion routines.
- Added WS-Addressing metadata (wsam) support.
- Fixed *`xml:lang`* in SOAP 1.2 *`SOAP-ENV:Text`*.
- Fixed XML literal strings with maxOccurs="unbounded"
- Fixed SSL connection engine issue.
- Fixed RPC literal part name handling issue.
- Fixed in update: SSL alloc/free issue and s2dateTime.

Version 2.7.12 (10/01/2008)
---
- Added multi-endpoint connect capability. Endpoint string can be a space-separated list of endpoint URLs, where each URL is tried in turn.
- Added `SOAP_SSL_NO_DEFAULT_CA_PATH` option.
- Fixed SSL connect issue when the SSL handshake or network connection fails.
- Fixed *`xsi:nil`* handling for strings (NULL vs. "") in case of empty elements.
- Fixed DOM xmlns="" namespace issue in XML output.
- Fixed `IP_MULTICAST_TTL` failure to compile.
- Fixed non-critical WSSE API `soap_wsse_verify_nested` code.

Version 2.7.13 (03/21/2009)
---
- Improved wsdl2h code output.
- Updated gsoapWinInet.
- Updated DOM xmlns namespace binding handling.
- Fixed OpenSSL memory leak.

Version 2.7.14 (09/07/2009)
---
- Added support for `poll()` to replace `select()` to prevent `FD_EXCEEDED`.
- Fixed enum local simpleType restriction attribute initialization.
- Fixed utf8 string parsing issue when first char in CDATA could cause problems.
- Fixed UDP IPv6 multicast-unicast exchange.
- Fixed gzip end-of-stream check.
- Fixed wsdl2h portType operation-input/output matching to ensure operations can be safely overloaded.

Version 2.7.15 (11/07/2009)
---
- Added `soap_read_X()` and `soap_write_X()` macros to simplify object reading and writing.
- Fixed `soap_new_X()` functions compilation problem.
- Fixed SSL session in context copy.
- Fixed win32 `select()` in `tcp_select()`.
- Fixed wstrings in unions.
- Fixed preservation of CDATA sections in literal XML strings.

Version 2.7.16 (04/05/2010)
---
- Added soapcpp2 option -T to generate auto-test echo server code with an example in samples/autotest based on 294 patterns for data binding W3C workgroup.
- Added soapcpp2 option -b to serialize byte arrays char[] as fixed-size strings (array of *`xsd:byte`* otherwise).
- Added *`xsd:duration`* serializer: import custom/duration.h.
- Added gsoap header syntax '$' type qualifier to indicate special struct/class members (array length, union discriminators).
- Added "colon notation" to attach XML prefixes to C/C++ names without changing the names, an alternative to the `ns__` prefix notation by writing `ns:name` instead of `ns__name` where the former stands for just `name` to the C/C++ compiler.
- Added wsdl2h options -z# for backward compatibility flags (-z1, -z2).
- Added `SOAP_XML_IGNORENS` to optionally ignore XML namespaces.
- Added WS-ReliableMessaging plugin.
- Added custom *`xsd:duration`* serializer.
- Added WSSE plugin `soap_wsse_set_wsu_id()` to simplify signing of elements (sets the wsu:Id of a given element tag name).
- Improved handling of struct/class member name clashes resulting from XML schemas definitions.
- Improved SOAP RPC ecoding response element tag acceptance.
- Improved VxWorks compatibility.
- Fixed FastCGI SOAP/XML processing with MIME attachments.
- Fixed `typedef std::string XML`, for literal XML serialization problem.
- Fixed a rare incorrect well-formedness error when xmlns default namespaces are absent.
- Fixed a zlib compression error when obsolete crc check is used.
- Fixed WS-Addressing HTTPS message relay (OpenSSL crash).

Version 2.7.17 (05/10/2010)
---
- Added WS-Policy 1.2 and 1.5, WS-SecurityPolicy 1.2 support for wsdl2h.
- Improved WS-ReliableMessaging interop and verified MT-safety.
- Improved WS-Security WSSE plugin documentation.
- Fixed soapcpp2 line number error reporting.
- Fixed WSSE plugin `soap_wsse_set_wsu_id()`.
- Fixed wsdl2h cycle problem with recursive *`xs:include`* and *`xs:import`*.
- Fixed enum translation of enum symbols with colons.
- Fixed `std::wstring` used as XML attribute value UTF8 encoding (internal stdsoap2 API changed).

Version 2.8.0 (09/20/2010)
---
- Added wsdl2h option -W: suppress warnings.
- Added wsdl2h option -i: for advanced uses only to skip schema imports.
- Added automatic *`xsi:nil`* output for NULL pointer members when minOccurs>0 (member has '1' occurence annotation).
- Improved wstring and `wchar_t*` handling when `wchar_t` is less than 4 bytes.
- Improved use of custom serializers in builds.
- Fixed wsdl2h type mapping of nested *`xs:sequence`* and *`xs:choice`*.
- Fixed soapcpp2 handling of extension base qualified elements and derived type unqualified elements.
- Fixed WSRM message resend buffer leak.
- Licensing change for reasons of consistency and transparency: the soapcpp2 tool (2.8.0 and up) is licensed under the same conditions as the wsdl2h tool, which means that soapcpp2 is no longer covered by the gSOAP public license.

Version 2.8.1 (01/14/2011)
---
- Added WS-Security WSSE plugin-integrated streaming XML encryption.
- Added WS-Security WSSE plugin `soap_wsse_sign_only()`.
- Added soapcpp2 -f flag to split large output source code files into parts.
- Fixed C++ mapping of *`xs:sequence`* with maxOccurs larger than 1.

Version 2.8.2 (04/17/2011)
---
- Added soapcpp2 -j option to generate C++ proxies and services in alternative format to the -i option.
- Fixed wsdl2h issue with optional elements with default value.
- Fixed cyclic WSDL import dependences in wsdl2h.
- Fixed WSRM server-side fault state handing.
- Fixed leading unicode character parsing and conversion issue in literal XML strings.

Version 2.8.3 (06/24/2011)
---
- Added soapcpp2 -y option to generate C/C++ type access information to the generated sample XML messages, allowing for the verification of C/C++ data access to the actual XML content.
- Added JSON support in addition to XML-RPC, see the XML-RPC content in the samples folder.
- Improved DOM processing (an optional feature).
- Fixed bugs, compilation and porting issues.

Version 2.8.4 (10/24/2011)
---
- Added NTLM support (enabled with `-DWITH_NTLM`, requires libntlm).
- Added WS-Discovery 1.1 support (see doc/wsdd and plugin/wsddapi.h and wsddapi.c).
- Added `//gsoap` typed directive to control *`xsi:type`* attribuation per namespace.
- Added `SOAP_XML_NOTYPE` flag to disable *`xsi:type`* attributes.
- Improved WS-Security encryption (AES, `soap_wsse_add_EncryptedKey_encrypt_only`).
- Improved HTTP proxy authentication support (digest and NTLM).
- Fixed bugs and portability issues.

Version 2.8.5 (11/19/2011)
---
- Fixed build issues with WS-Discovery.
- Fixed HTTP basic auth crash.
- Fixed `WITH_COMPAT` and `WITH_C_LOCALE`.
- Fixed wsdl2h output for XSD abstract element extraneous ';'.

Version 2.8.6 (12/14/2011)
---
- Improved WS-Security compatibility.
- Fixed multi and cyclic WSDL import.
- Fixed tags of qualified referenced elements.
- Fixed C builds for improved portability.

Version 2.8.7 (02/07/2012)
---
- Added new REST examples.
- Added versioning checks to ensure project builds are consistent.
- Improved interoperability of wsdl2h output wrt. to element qualification.
- Renamed `-DTANDEM` to `-DTANDEM_NONSTOP` to prevent naming conflicts.
- Fixed WS-Discovery URL.
- Fixed soapcpp2 option -i and -j server chaining.

Version 2.8.8 (02/20/2012)
---
- Added REST plugin (httppost.c) enhancements and examples.
- Added static version checks to prevent linkage to old incompatible libraries that could lead to runtime failures.

Version 2.8.9 (06/10/2012)
---
- Added examples to interoperate with WCF basicHttp, basicTransportSecurity, basicMessageSecurity, and wsDualHttp.
- Added soapcpp2 option -A for service dispatching based on Action values only.
- Added wsdl2h option -z3.
- Added wsse support for WS-SecureConversation.
- Added wsrm5 WS-ReliableMessaging 1.0 2005.
- Added iOS plugin with examples.
- Improved WS-Policy analysis and reporting.
- Fixed and improved wsse plugin for WS-Security interoperability with WCF and other implementations (required a small API change).
- Fixed HTTP headers for NTLM.
- Fixed httpda plugin OpenSSL init crash in md5evp.c.

Version 2.8.10 (08/16/2012)
---
- Added soapcpp2 -Q option (C++ namespaces).
- Added wsdl2h -b option (bi-directional operations for duplex services).
- Updated WS-Addressing and WS-ReliableMessaging plugins, documentation, and examples.

Version 2.8.11 (10/14/2012)
---
- Added soapcpp2 -0 option to remove SOAP bindings when applicable.
- Changed wsdl2h output for the few cases that multiple service bindings are defined, use wsdl2h -Nns for backward compatibility.
- Improved DOM processing.
- Improved C++0x/C++11 compatibility.
- Fixed httpda plugin crash.
- Fixed wsdl2h processing of *`xs:group maxOccurs="unbounded"`*.
- Fixed `mod_gsoap` plugin compilation issues.
- Fixed literal XML UTF8 (UTF8 is now retained with `SOAP_C_UTFSTRING`).

Version 2.8.12 (12/8/2012)
---
- Added WSDL 2.0 support to wsdl2h.
- Added //gsoap method-protocol directive.
- Improved XML REST support, soapcpp2 -0 option for "no-SOAP" services.
- Improved class instantiation with `soap_new_X`, `soap_new_set_X`, `soap_new_req_X`.
- Improved soapcpp2 -b option.
- Improved WCF WS-Addressing interop (duplex) channel.
- Changed code to normalize in/out MEP for solicit-response messaging.
- Fixed client-side OpenSSL host check that is known to crash in OpenSSL.

Version 2.8.13 (1/21/2013)
---
- Improved XML-RPC/JSON API and documentation, with one change: now must use `SOAP_C_UTFSTRING` to hold UTF8 in 8-bit strings.
- Improved VxWorks compatibility.
- Updated `soap_read_X` and `soap_write_X` to serialize object graphs with SOAP encoding enabled: use `soap_set_version(soap, V)` with V=0 (no SOAP), V=1 (SOAP1.1), V=2 (SOAP1.2).
- Fixed broken WSDL *`types`* nested schema XSD import.
- Fixed operation action overriding by input/output SOAP action.
- Deprecated old-style C++ service proxies and objects (use soapcpp2 -z1 flag to generate).

Version 2.8.14 (2/4/2013)
---
- Added explanation of wsdl2h option -Nname which is used to generate a service (and its prefix name) for each service binding (bindings are collected in one service by default).
- Fixed PRId64 formatting.
- Fixed broken MIME with doc/lit (when SOAP encodingStyle is not used).

Version 2.8.15 (5/12/2013)
---
- Added wsdl2h option -R for auto-generation of REST-based service operations (also added examples/rest example).
- Change `soap_read_X()` and `soap_write_X()` to prevent removal of HTTP headers after calling `soap_connect()`.
- Fixed automatic detection of DIME/MIME transfers.
- Fixed HTTP 1.0 chunking issue.
- Fixed HTTP digest authentication with DIME/MIME transfers.
- Fixed OpenSSL subject alt name check.
- Fixed HTTP 100 message handling issue.

Version 2.8.16 (8/12/2013)
---
- Improved support for Android platform.
- Improved WCF interop duplex messaging requiring ChannelInstances.
- Fixed complexType restriction of schema types with redefined attributes in wsdl2h output.
- Fixed wcf/WS/DualHttp example (wrong use of `send_X()` replaced by `X()` for client-side operations X, to allow HTTP keep-alive to be used).
- Fixed use of sprintf's that trigger Valgrind and Fortify warnings.
- Fixed parsing character strings from CDATA sections ending in ']'.
- Fixed DOM output for `SOAP_XML_CANONICAL` c14n normalization of xmlns namespace bindings.

Version 2.8.17r (12/1/2013)
---
- Added WS-RM message queueing option for WS-RM NoDiscard.
- Added wsdl2h option -r for authorized web access and proxy access.
- Improved C++11 compatibility.
- Improved ISO compatibility (compile -pedantic).
- Improved I/O timeouts timing accuracy in the presence of EINTR interrupts (set `SOAP_MAXEINTR`).
- Fixed in 2.8.17r: fixed socket timeout issue.

Version 2.8.18 (8/24/2014)
---
- Added *`xs:precision`* and *`xs:scale`* support.
- Added support for BPEL PartnerLink and VariableProperties to wsdl2h in support of BPEL projects.
- Added soapcpp -z2 flag for backward compatibility with to 2.7.x: omit XML output of elements for pointers that are NULL even when minOccurs=1 (required).
- Changed wsdl2h C++ output to always generate pass-by-reference response parameters (disable with -z6).
- Improved WS-RM interoperability.
- Fixed message part elements and types in default (xmlns="") namespace.
- Fixed `&#;`-entity code conversion bug in XML attribute deserialization.
- Fixed wsdl2h nested simpleType restriction with itemTypes.
- Fixed wsdl2h substitutionGroup element in other namespace.
- Fixed *`xs:choice`* strict validation.
- Fixed timeout/EINTR issue.

Version 2.8.19 (11/8/2014)
---
- Added string validation callbacks fsvalidate and fwvalidate for regex pattern-based validation of strings and wide strings against XML schema regex patterns.
- Fixed *`xs:choice`* strict validation with *`minOccurs="0"`* element(s).
- Fixed `TCP_FASTOPEN` with UDP.
- Fixed MTOM Content-Disposition ID overriding problem.
- AIX portability fixes.

Version 2.8.20 (11/30/2014)
---
- Added XML 1.1 control char encoding support.
- Fixed C/C++ compiler warnings.

Version 2.8.21 (12/05/2014)
---
- Added `-DWITH_REPLACE_ILLEGAL_UTF8` compilation option to replace UTF8 content that is outside the allowed range of XML 1.0.
- Improved WS-RM (memory usage).
- Fixed additional C/C++ compiler warnings.
- Fixed `strftime` `%F` and `%T` use (removed).

Version 2.8.22 (4/12/2015)
---
- Added XSD 1.1 support (*`xs:override`*, *`xs:defaultAttributes`*, *`xs:targetNamespace`* on element and attribute declarations, and other additions).
- Added import/wsdd5.h to support WS-Discovery 1.0 with WS-Addressing 2005/08 (typemap.dat now sets wsdd5.h instead of wsdd10.h by default).
- Improved portability, including Solaris and AIX porting.
- Improved option -R is now required to enable REST WSDL bindings and non-HTTP transport (in addition to enabling REST WSDL operations).
- Fixed wsdl2h handling of *`xs:redefine`*.
- Fixed deep class inherited `xsd__anyType` deserializer issue causing serialization and validation errors.
- Fixed `std::vector*` deserialization bug that occurs under very specific circumstances.
- Fixed wsdd plugin `SOAP_WSDD_APP_MAX_DELAY`.
- Fixed wsse/smdevp memory leak.

Version 2.8.23 (8/17/2015)
---
- Added TLS SNI.
- Added Unicode C++11 identifier support to soapcpp2, supported directly by UTF8 encoding and the UCN `\uNNNN` extension of identifier naming in the C99/C98++ standards.
- Added wsdl2h option -U to allow UTF8-encoded Unicode C/C++ identifiers upon mapping universal XML tag names to C/C++ identifier names (this is a C++ standard-dependent and compiler-dependent feature).
- Replaced C lib functions `memcpy`, `memmove`, `strcpy`, `strcat`, `strncpy`, `strncat`, `sscanf`, `sprintf` by more secure alternatives when available on target platform.
- Updated OpenSSL and GNUTLS integration.
- Fixed soapcpp2 SOAP RPC literal WSDL output (supported are SOAP RPC encoded, RPC literal, document literal, and REST).
- Fixed C++ struct soap context constructor memory leak when `WITH_GZIP` is enabled and changed struct soap context allocation in C++.
- Fixed redundant call to `OpenSSL_add_all_digests()`, since `OpenSSL_add_all_algorithms()` already adds digests. This caused issues on certain platforms with OpenSSL 1.0.1 and higher.
- Fixed missing client-side `soap_recv_fault` with empty doc/lit responses.
- Fixed missing *`xs:restriction`* tag in soapcpp2 WSDL/XSD output.

Version 2.8.24r (11/01/2015)
---
- Added new soapcpp2 option `-c++11`, enabling support for C++11 syntax and features, including:
    - scoped enumerations (`enum class`) with underlying types (`enum class : type` is 8, 16, 32, or 64 signed int);
    - serialization of smart pointers `std::shared_ptr` and `std::unique_ptr` (and deprecated `std::auto_ptr` if needed);
    - virtual method `final` and `override` syntax;
    - `nullptr` constant member initializer.
    -  More efficient C++11 STL vector, list, and deque deserialization code based on `emplace_back()`.
- Added new `xsd__date` custom serializer `custom/struct_tm_date.h` to bind `struct tm` to *`xsd:date`*.
- Added new `xsd__time` custom serializer `custom/long_time.h` to bind `ULONG64` to *`xsd:time`* with microsecond precision.
- Added new `xsd__duration` custom serializer `custom/chrono_duration.h` to bind C++11 `std::chrono::nanoseconds` to *`xsd:duration`*.
- Added `xsd__dateTime` custom serializer `custom/chrono_time_point.h` to bind C++11 `std::chrono::time_point` to *`xsd:dateTime`*.
- Added new TLS/SSL flags `SOAP_TLSv1_0`, `SOAP_TLSv1_1`, and `SOAP_TLSv1_2` to limit TLS protocol selections.
- Added new SHA224/SHA384 digest options, ECDSA (requires OpenSSL 0.9.8 or later), and HMACOutputLength truncation (within limits) to WSSE.
- Added Galois counter mode (GCM) authenticated encryption to WSSE with AES128/AES192/AES256, requires OpenSSL 1.0.2 or later.
- Added the concept of "mutable" structs and classes, which allow for incremental compile-time addition of new members to the struct/class, which gives them a tuple-like behavior with the tuple being populated in distinct parts of the soapcpp2 input source. This is similar to the way the `SOAP_ENV__Header` struct was already handled. This is not a standard C/C++ feature.
- Added `$CONTAINER = name` and `$POINTER = name` definitions to `typemap.dat` for specifying the C++ container to use (`std::vector` by default) and C++11 smart pointer to use (no smart pointer by default), see [databindings](www.genivia.com/doc/databinding/html).
- Improved soapcpp2 input source code analysis and C/C++ syntax coverage.
- Improved soapcpp2 output WSDL and XSD with added root-level elements and attributes on demand, see [databindings](www.genivia.com/doc/databinding/html).
- Improved efficiency and case coverage of SOAP encoded messages with id-ref anchors using redesigned pre- and post node graph construction analysis algorithms (`soap_id_enter`, `soap_id_forward`, `soap_id_lookup`, and `soap_update_pointers` have changed).
- Improved cyclic data structure detection and XML rendering with non-SOAP-encoded literal style (and/or the `SOAP_XML_TREE` flag) to prune cycles from trees. `SOAP_XML_TREE` produces XML document "trees" rather than id-ref XML graphs. Graphs are produced with SOAP encoding or with the `SOAP_XML_GRAPH` flag.
- Improved primitive `union` members access in C++ by removing unnecessary pointers.
- Improved checking of signatures in WSSE plugin.
- Updated soapcpp2 `size_t` mapping to transient (non-serializable) type. The wsdl2h tool does not generate `size_t`. If `size_t` is used in your header files for soapcpp2, then use `unsigned long` to replace `size_t`, which replicates the old `size_t` mapping to `unsigned long` (beware, this is not portable).
- Updated *`xsi:nil`* serialization rules for pointer-type struct/class members, by forcing *`xsi:nil="true"`* element output for required **nillable** elements (no longer requiring the `SOAP_XML_NIL` flag).
- Updated wsdl2h Nillable optional element annotations (i.e.g for `nillable=true` and `minOccurs>0`), now requiring inbound elements with *`xsi:nil`* or validation error. NULL pointer-based outbound nillable elements with `minOccurs>0` are now serialized with *`xsi:nil="true"`*, see above.
- Updated dateTime content validation with `SOAP_XML_STRICT`, otherwise accepts ISO8601 variants.
- Fixed `SOAP_UNION_name_type_member` macro constants for C++ namespace `name` (wsdl2h option `-qname` to ensure that the generated macro names are unique.
- Fixed attribute serialization when attribute of type `std::string` has a default value while actual value is set to "" (empty).
- Fixed class inheritance from base class `soap_dom_element` (declared in `dom.h`) which should include the content of the DOM node(s) together with the (de)serialized content of the derived class instance.
- Fixed default/fixed values of element/attribute references to global elements/attributes with global default/fixed values.
- Fixed *`xs:group`* and *`xs:substitutionGroup`* element namespace prefix qualifications of struct and classe members.
- Fixed deserialization of nested *`xs:sequence`* class pointers to NULL (structs are OK) when *`xs:sequence`* is optional and sequence data is not present on the inbound stream.
- Fixed missing `custom/struct_timeval.c` inbound microsecond fraction of *`xsd:dateTime`* values.
- Fixed `typedef` of a custom serializer type.
- Fixed `typedef` pointer type use in `@type` attribute declarations.
- Fixed linking against newer EVP functions in older OpenSSL versions to compile WSSE plugin.
- Fixed WSSE decryption with HTTP-chunked and fragmented messages in transport.

Version 2.8.25 (11/11/2015)
---
- Added `xsd__decimal` custom serializer `custom/float128.h` to bind `<quadmath.h>` quad precision float `__float128` to *`xsd:decimal`*.
- Added group circular reference detection to wsdl2h. Generates code for circular group references that is safe to use, but with loss of occurrence validation constraints, if any are present.
- Updated and improved XML-RPC and JSON implementation with wider `_int`, now 64 bit, while keeping XML-RPC type `_i4` to just 32 bit. Existing project C code that uses the XML-RPC and JSON plugin SHOULD be updated to use `_i4` (`int`) instead of `_int` when `_int` is still used as a 32 bit `int` in their project.
- Fixed strict validation of empty elements unless the element is href/ref-attributed with SOAP encoding (this validation check was temporarily lost in the 2.8.24r release).
- Fixed missing `#include <memory>` for smart pointers.
- Fixed float type minInclusive and maxInclusive fractional bounds validation.
- Fixed compilation issues when C++ namespaces (soapcpp2 option `-q`) are used with custom serializers.
- Fixed wsdl2h option `-p`, which may cause type name clashes with generated C++ `xsd__anyType` wrapper classes for simple types.

Version 2.8.26 (11/30/2015)
---
- Added new **jsoncpp** code generator that takes a JSON sample document and renders it in JSON API code for C or C++. The jsoncpp tool is located in `gsoap/samples/xml-rpc-json` with the XML-RPC and JSON APIs and samples.
- Added new C/C++ XML-RPC and JSON APIs `xml-rpc.c` and `json.c[pp]` to simplify JSON and XML-RPC in C and C++. The old `json_c.h` and `json_c.c` are deprecated and removed in favor of the improved APIs `json.h` and `json.c[pp]`.
- Added `xsd__integer` custom serializer `custom/int128.h` to bind big int `__int128_t` to *`xsd:integer`*.
- Added floating point exclusive range bounds notation to gSOAP header file syntax, with `<` on the side of `:` for an exclusive bound (`min <: max` makes `min` exclusive, `min <:< max` makes both exclusive, and `min :< max` makes `max` exclusive), while keeping `min : max` for inclusive bounds.
- Added C++11 syntax for struct/class member initialization with `{ initval }`, which has an identical effect as declaring members with `= initval` initializers. This works in C and C++.
- Added HTTP2 support to WinInet plugin.
- Expanded [XML-RPC and JSON documentation](http://www.genivia.com/doc/xml-rpc-json/html).
- Expanded [Data Bindings documentation](http://www.genivia.com/doc/databinding/html).
- Improved wsdl2h schema import processing when WSDL and XSD have the same namespace and *`xs:import`* is used instead of *`xs:include`* to populate the schema.
- Improved wsdl2h output for integer enumeration constants, omits trailing underscores for pseudo-numeric enum constants, updated soapcpp2 to accept duplicate enum constants in different enum lists when their values are the same.
- Fixed `soap_del_string` crash in `char*` string deletion.
- Fixed soapcpp2 option `-s` by enforcing `SOAP_XML_STRICT` on the body of inbound messages for client and server.
- Fixed a rare issue where elements end up missing in a substitutionGroup when several WSDLs with the same namespace are imported into one WSDL.
- Fixed strict validation rejection of empty element body when empty when permitted.

Version 2.8.27 (12/7/2015)
---
- Added new JSONPath code generation feature to jsoncpp in `gsoap/samples/xml-rpc-json` with new option `-p`. Supports C++ (and C in the next release).
- Improved JSON API functionality and robustness.
- Improved substitutionGroup union member: removed prefix `__` from member name and removed rogue `;`.
- Fixed `WITH_NOIDREF` broken `iht` initialization introduced in 2.8.25/26, which may lead to a crash.

Version 2.8.28 (02/01/2016)
---
- Added new **domcpp** code generator that takes an XML sample document and renders it in XML DOM API code for C or C++. Can also convert XPath to XML DOM API code with option `-p`. The domcpp tool is located in `gsoap/samples/dom` with the XML DOM samples.
- Added many new API functions to a fully redisigned XML DOM API v5 for C and C++ with new DOM API documentation.  The redesigned DOM API v5 is mostly backward compatible to DOM API v4, but with DOM string `data` members changed to `text` members.  Many API functions are added to define a clean interface without having to use the DOM structure data members.  The `soap_dom_next_element()` function now takes a second parameter that is an element pointer to stop deep traversal at (use NULL for old behavior).  See updated [XML DOM and XPath](http://www.genivia.com/doc/dom/html) documentation for details.
- Added C serialization to/from strings with new C `soap` struct members `const char *soap::is` input string to parse from and `const char **soap:os` pointer to string that is set by the engine to point to the output.  Note that C++ code is unchanged and the `soap::is` and `soap::os` are still members pointers to `istream` and `ostream` streams (use `std::stringstream` for input/output from/to strings).
- Added JSON API C function `set_size` to set/change array sizes and JSON API C function `set_struct` to create an empty JSON object.
- Improved jsoncpp command line tool to generate JSONPath C code and improved overall to generate more compact code.
- Improved `SOAP_DEFAULTNS` flag to emit XML default namespace declarations.
- Improved strictness of XML verification under default settings (i.e. without requiring `SOAP_XML_STRICT`).
- Changed string deserialization when XML content with tags is encountered: XML tags are no longer parsed as part of strings.  You must use `XML` string type to parse literal XML content or use DOM.
- Fixed C++ JSON/XML-RPC API `time_t` type usage to `ULONG64` to ensure portability.  This affects the `value(time_t)` constructor, the `value::operator=(time_t)` assignment operator, and `value::operator time_t()` cast, which have been replaced by versions using `ULONG64`.  To use these in C++ for `time_t` ISO 8601 date time serialization, simply cast `time_t` values to `ULONG64` values.
- Fixed gsoapWinInet.cpp:243, `pDst` should be `a_pDst`.
- Fixed SNI `SSL_set_tlsext_host_name` call for OpenSSL 0.9.8f.
- Fixed `soap_instantiate` of smart pointer when instantiating derived class by *`xsi:type`*.
- Fixed friend `__declspec(dllexport)` declarations in generated classes.

Version 2.8.29 (02/24/2016)
---
- Added new soapcpp2 option `-r` to generate a soapReadme.md report that summarizes the input .h file information, the serializable C/C++ types, the services, and the generated code. Use a markdown converter to browse or download the free readmeviewer.html from http://www.genivia.com/files/readmeviewer.html.zip to view the soapReadme.md report in a browser.
- Added new wsdl2h option `-M` to suppress error "must understand element with wsdl:required='true'".
- Upgraded HTTP digest authentication `httpda` plugin to 2.0 to support RFC7616 "HTTP Digest Access Authentication" with SHA2 (replacing MD5) that is compatible with RFC2617; compile and link upgraded `plugin/httpda.c` with `plugin/smdevp.c` instead of `plugin/md5evp.c`.
- Updated wsdl2h HTTPS-enabled build steps to use upgraded `httpda` plugin.
- Updated `samples/webserver` to use upgraded `httpda` plugin.
- Updated the samples with new AWS S3 SOAP API example `samples/aws`.
- Improved soapcpp2 code generation of inline object read/write functions in C++, instead of macros generated in C.
- Fixed and improved soapcpp2 code generation with options `-p` and `-q`.
- Fixed definitions/service/port/wsaw:UsingAddressing processing.
- Fixed SNI `SSL_set_tlsext_host_name` call for OpenSSL 0.9.8f.
- Fixed wsdl2h skipping *`mime:multipartRelated/mime:part`*.

Version 2.8.30 (04/02/2016)
---

- Added backtick XML tag name syntax to interface files for soapcpp2, which allows for the overriding of the translated tag names of struct/class members and service operation parameters, see the [Data Bindings documentation](http://www.genivia.com/doc/databinding/html#toxsd9-5). Older gSOAP versions do not support the backtick tag in the generated WSDL and schemas (messages are OK).
- Added macro `SOAP_MAXLEVEL` to trigger `SOAP_LEVEL` error when XML nesting level of inbound XML exceeds the value of `SOAP_MAXLEVEL`.  Default value is 10000.  Redefine `SOAP_MAXLEVEL` as needed, with lower values to restrict XML nesting depth for receivers to accept.
- Added macro `SOAP_MAXLENGTH` to trigger `SOAP_LENGTH` content length error when string content in inbound XML exceeds the value of `SOAP_MAXLENGTH`.  Applies to strings that are potentially unbounded, i.e. that are not already constrained by XML validation maxLength constaints (which could be larger than `SOAP_MAXLENGTH`).  Default value is zero (0) which means that string length is unconstrained if XML validation maxLength is not given.  Redefine `SOAP_MAXLENGTH` as needed, with lower values to restrict string lengths for receivers to accept.
- Added macro `SOAP_MAXOCCURS` to trigger `SOAP_OCCURS` content error when array and container lengths exceed the value of `SOAP_MAXOCCURS`.  Must be greater than zero (0).  Default value is 100000.  Redefine `SOAP_MAXOCCURS` as needed, with lower values to restrict array and container lengths for receivers to accept.
- Updated wsdl2h WS-Policy processing to include WS-RM protocol versioning.
- Updated `soap_ignore_element` processing efficiency.
- Updated `import/saml1.h` and `import/saml2.h`.
- Improved soapcpp2 generation of WSDL and XSD for unqualified C/C++ types or when mixing qualified and unqualified C/C++ types and type names.
- Changed soapcpp2 default behavior for generating WSDL and XSD files with *`elementFormDefault="unqualified"`* from the old default behavior with *`elementFormDefault="qualified"`*, i.e. when `//gsoap ns elementForm:` directive is NOT explicitly included in the interface .h file for soapcpp2 and when soapcpp2 option -e is not used.  *This change DOES NOT affect interface files produced by wsdl2h*, only those interface .h files that are not auto-generated and do not have elementForm directives.  *If you use soapcpp2 to generate WSDL and schemas AND you need backward compatible SOAP document/literal style messaging AND you DO NOT have `//gsoap ns service style: rpc` (or soapcpp2 option -e) AND you DO NOT have `//gsoap ns schema elementForm:` directives already in your .h file, then you SHOULD add `//gsoap ns schema elementForm: qualified` directives to your .h file for each `ns` prefix*.  This recommendation ensures backward compatibility in your current SOAP document/literal style messaging projects.  Changing the soapcpp2 default behavior to *`elementFormDefault="unqualified"`* simplifies data bindings.  It is also the accurate form to use when C/C++ types are not namespace qualified in the .h interface file for soapcpp2.
- Improved DLL export with compiler flag `/DSOAP_STD_EXPORTS` (which defines `SOAP_STD_EXPORTS`) to dllexport the API, classes, and the proxy and service classes.  Modified the plugins to support dllexport.
- Fixed soapcpp2 crash with enum constants > 255 due to libc `isalpha` crashing on some Linux systems.
- Fixed `import/wsp.h` soapcpp2 compilation error.
- Fixed soapcpp2 option `-w` that may cause a message response element tag name inconsistency with SOAP doc/lit style.
- Fixed deserialization issue with dynamic arrays of STL containers/smart-pointers (i.e. a pointer to an array of containers/smart-pointers, which is an unlikely combination to use, but should work).

Version 2.8.31 (05/1/2016)
---

- Added engine context `sndbuf` and `rcvbuf` attributes to (re)set `setsockopt` values for `SO_SNDBUF` and `SO_RCVBUF`, respectively.  Default value is `SOAP_BUFLEN`, same as engine's internal message buffer size.  Setting to zero forces the engine to omit the `setsockopt` `SO_SNDBUF` and `SOAP_RCVBUF` calls, which for example can be used to enable TCP buffer autotuning with Linux (Linux 2.4 and up).
- Added "http://userid:passwd@domain/path" userinfo syntax for HTTP Basic and NTLM authentication, i.e. this automatically sets `soap->userid` and `soap->passwd` from the userinfo and also sets `soap->authrealm` to the domain if not already set. HTTP Basic authentication is not recommended without secure https. For NTLM authentication, set `soap->ntlm_challenge = ""` to proceed immediately with NTLM instead of Basic authentication.
- Improved strengthening of `SOAP_XML_STRICT` and the soapcpp2 `-s` flag to reject all extra (non-deserializable) XML and character data by the parser and deserializers.
- Improved client-side certificate checking (DNS or IP, and wildcards).
- Improved soapcpp2 option `-t` and `//gsoap ns schema typed: y` directive that force the addition of *`xsi:type`* attributes to XML content except for types whose type names are prefixed with an underscore (i.e. root elements w/o type as per wsdl2h data bindings rules).
- Fixed crash with nested dynamic arrays in C++ (C is fine) i.e. classes and structs with `__ptr` and `__size` members as arrays of elements, where these arrays contain nested dynamic arrays.  [See here for patch](http://www.genivia.com/advisory.html).
- Fixed typedef of `xsd__hexBinary` struct/class, which should map to hexBinary but instead mapped to base64Binary.
- Fixed `nc` and `cnonce`, which are removed when `qop` directive is absent in HTTP digest authentication as per RFC2617.
- Fixed the digest authentication plugin from blocking basic authentication.
- Fixed soapcpp2 naming of unnamed function/method parameters as `_param_N` with N now counting up sequentially *per function* instead of globally counting up.  Use soapcpp2 option `-z3` for backward compatible global parameter indexing.
- Fixed (smart) pointer deserialization of non-base (derived) objects that are XML serialized with SOAP id-ref encoding using a href/ref that references a derived object (i.e. should result in a (smart) pointer to a derived instance, not a base instance or missing instance).
- Fixed strict validation (`SOAP_XML_STRICT`) of unqualified attributes in elements with a default namespace.
- Fixed wsdl2h 2.8.28-30 parsing of *`xs:unique`* causing wsdl2h to skip over schema components.  The fix also improved string-based parsing of XML content with a fix for 2.8.28-30 XML string handling.

Version 2.8.32 (05/10/2016)
---

- Improved soapcpp2 code generation of type converters `int soap_s2T(soap*, const char*, T*)` and `const char *soap_T2s(soap*, T)` for primitive and binary types T.
- Fixed unqualified *`xsi:type`* content matching with default namespace, which may lead to a failure in the 2.8.31 release to instantiate derived instances for complexType extensions.
- Fixed Solaris crash in `soap_wstrdup`.

Version 2.8.33 (06/14/2016)
---

- Updated WS-Trust gsoap/import/wstx.h `__wst__RequestSecurityToken` response message parameter to `wst__RequestSecurityTokenResponseCollection`
- Updated WS-Security gsoap/import/wsse.h with optional SAML assertions in the Security header.
- Updated response processing for empty HTTP body with HTTP code 200 to 202: no longer forces socket close when HTTP keep-alive is enabled.
- Updated `_XML` literal string XML serialization for qualified tag names, no longer uses default namespace (as in *`xmlns="URI"`*) but a prefixed tag name only.
- Updated wsdl2h options `-p` and `-d`, now generates `xsd__anyType*` (i.e. with pointer) data members without requiring the user to define a typemap.dat rule to do so. This change reinstates some of the old behavior of 2.8.23 and earlier versions.
- Fixed wsddapi.c compilation issue on Windows (`usleep` replaced).
- Fixed validation of *`simpleType/restriction/length`* when restriction base is a list that is mapped to a string.
- Fixed validation of *`simpleType/restriction`* with base type string length bounds restrictions.

Version 2.8.34 (08/17/2016) {#latest}
---

- Added custom serializers for QT primitive types and containers.  This serializes many QT types directly in XML.  The QT types to use for XSD types are specified in the typemap.dat.  See the updated gsoap/typemap.dat file in the distribution package and the updated [databindings](http://www.genivia.com/doc/databinding/html) documentation for details.
- Added HTTP server session management plugin to manage server-side session cookies.
- Added basic common WADL support to wsdl2h to generate code for WADL REST XML applications.
- Improved client-side URL query generation and support for URL templates for REST operations.
- Updated the iOS plugin and its Web service examples.
- Updated SSL calls for improved iOS portability.
- Updated wsdl2h headerfault support (optional fault details in SOAP Headers, not widely used by Web services tools).
- Updated VC++ ISAPI plugin.
- Fixed `soap_send_empty_response()` with HTTP keep-alive to prevent exit of the server loop back to `soap_accept()`, i.e. prematurely killing the keep-alive connection causing EOF/RST.
- Fixed `#import "wsse.h"` in `gsoap/import/ds.h` by moving it down to avoid missing type declaration of `_ds__KeyInfo` which may cause a soapcpp2 syntax error.
- Fixed WS-Security interoperability issues, fixes issues with XML encryption. Token handler callback has new parameters to pass the key data of SecurityTokenReference/KeyIdentifier.
- Fixed the internal `feltbegout` and `feltendout` callbacks: when set no longer emits XML and (alternative) output is expected to be emitted by these callbacks.

[![To top](http://www.genivia.com/images/go-up.png) To top](changelog.html)

