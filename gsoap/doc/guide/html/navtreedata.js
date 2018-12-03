var NAVTREE =
[
  [ "gSOAP User Guide", "index.html", [
    [ "Introduction", "index.html#intro", null ],
    [ "Notational conventions", "index.html#conventions", null ],
    [ "Tooling characteristics", "index.html#features", null ],
    [ "API documentation modules", "index.html#start-modules", null ],
    [ "Getting started", "index.html#start", [
      [ "Where to find examples", "index.html#start-examples", null ],
      [ "Creating a SOAP/XML client application", "index.html#start-client", null ],
      [ "Creating a SOAP/XML service application", "index.html#start-service", null ]
    ] ],
    [ "Introduction to XML data bindings", "index.html#databindings", null ],
    [ "A quick user guide", "index.html#guide", [
      [ "How to build Web API clients", "index.html#client", [
        [ "Example", "index.html#example1", null ],
        [ "XML namespace considerations", "index.html#namespace", null ],
        [ "Example", "index.html#example2", null ],
        [ "How to generate C++ client proxy classes", "index.html#proxy", null ],
        [ "XSD type serialization", "index.html#encoding", null ],
        [ "Example", "index.html#example3", null ],
        [ "How to change the response element name", "index.html#response", null ],
        [ "Example", "index.html#example4", null ],
        [ "How to specify multiple output parameters", "index.html#multiple", null ],
        [ "Example", "index.html#example5", null ],
        [ "How to specify output parameters with compound data types", "index.html#compound", null ],
        [ "Example", "index.html#example6", null ],
        [ "How to specify anonymous parameter names", "index.html#anonymous", null ],
        [ "How to specify a service operation with no input parameters", "index.html#noinparam", null ],
        [ "How to specify a service operation with no output parameters", "index.html#nooutparam", null ],
        [ "How to switch to REST from SOAP", "index.html#restclient", null ]
      ] ],
      [ "How to build Web services APIs", "index.html#services", [
        [ "Example", "index.html#example7", null ],
        [ "MSVC++ builds", "index.html#msvc", null ],
        [ "How to create a stand-alone server", "index.html#stand-alone", null ],
        [ "How to create a multi-threaded stand-alone service", "index.html#mt", null ],
        [ "How to pass application state info to service operations", "index.html#user", null ],
        [ "How to generate C++ server classes", "index.html#object", null ],
        [ "How to chain C++ server classes to accept messages on the same port", "index.html#chaining", null ],
        [ "How to generate WSDL service descriptions", "index.html#wsdl", null ],
        [ "Example", "index.html#example8", null ],
        [ "How to make client-side calls within a service operation", "index.html#clientinservice", null ],
        [ "How to switch to REST from SOAP", "index.html#restservice", null ]
      ] ],
      [ "Asynchronous one-way message passing", "index.html#oneway1", null ],
      [ "How to use XML serializers to save and load application data", "index.html#bindings", [
        [ "Converting WSDL, WADL, and XML schema to C/C++ with wsdl2h", "index.html#wsdl2h", null ],
        [ "Mapping C/C++ to XML schema with soapcpp2", "index.html#soapcpp2mapping", null ],
        [ "Serializing C/C++ data to XML", "index.html#serialize", null ],
        [ "Example", "index.html#example9", null ],
        [ "Default values for omitted XML elements and attributes", "index.html#default", null ]
      ] ]
    ] ],
    [ "The wsdl2h tool", "index.html#wsdlin", [
      [ "wsdl2h options", "index.html#wsdl2hoptions", null ],
      [ "Customizing XML data bindings with the typemap.dat file", "index.html#typemap", null ]
    ] ],
    [ "The soapcpp2 tool", "index.html#soapcpp2", [
      [ "soapcpp2 options", "index.html#soapcpp2options", null ],
      [ "The #import directive", "index.html#import", null ],
      [ "The #include and #define directives", "index.html#pragmas", null ],
      [ "Service operation specification format", "index.html#specformat", [
        [ "Service operation parameter passing", "index.html#param", null ]
      ] ],
      [ "C/C++ identifier name to XML tag name translation", "index.html#idtrans", null ],
      [ "Generating a SOAP/XML client application with soapcpp2", "index.html#compilingclient", null ],
      [ "Generating a SOAP/XML Web service application with soapcpp2", "index.html#compilingservice", null ],
      [ "Generating an auto test server for client testing", "index.html#autotest", null ],
      [ "Generating deep copy and deletion functions", "index.html#deep", null ]
    ] ],
    [ "Serialization and deserialization rules", "index.html#rules", [
      [ "SOAP RPC encoding versus document/literal style messaging", "index.html#rpcversusdoclit", null ],
      [ "SOAP 1.1 versus SOAP 1.2 and dynamic switching", "index.html#switching", null ],
      [ "Primitive type serialization", "index.html#primtype", [
        [ "How to use multiple C/C++ types for a single primitive XSD type", "index.html#multiprim", null ],
        [ "How to use C++ wrapper classes to specify polymorphic primitive types", "index.html#primclass", null ],
        [ "Multi-reference strings", "index.html#multirefstrings", null ],
        [ "Smart string mixed-content deserialization", "index.html#smart", null ],
        [ "Changing the precision of float and double types", "index.html#precision", null ],
        [ "INF, -INF, and NaN values of float and double types", "index.html#floatinfnan", null ]
      ] ],
      [ "Enumeration serialization", "index.html#enum", [
        [ "Serialization of symbolic enumeration constants", "index.html#enumserialization", null ],
        [ "How to reuse symbolic enumeration constants", "index.html#enumreuse", null ],
        [ "Boolean enumeration serialization for C", "index.html#boolean", null ],
        [ "Bitmask enumeration serialization", "index.html#bitmask", null ]
      ] ],
      [ "Struct serialization", "index.html#struct", null ],
      [ "Class serialization", "index.html#class", [
        [ "Example", "index.html#example10", null ],
        [ "Class methods", "index.html#methods", null ],
        [ "Get and set methods", "index.html#gettersetter", null ],
        [ "Updating and checking instances with get and set methods", "index.html#streaming", null ],
        [ "Polymorphism, derived classes, and dynamic binding", "index.html#polymorph", null ],
        [ "How to declare XML attributes", "index.html#attributes", null ],
        [ "How to use QName attributes and elements", "index.html#qname", null ]
      ] ],
      [ "Union serialization", "index.html#union", null ],
      [ "Pointer type serialization", "index.html#pointer", [
        [ "Multi-referenced data serialization", "index.html#multiref", null ],
        [ "NULL pointers and nil elements", "index.html#null", null ]
      ] ],
      [ "Void pointer serialization", "index.html#void", null ],
      [ "Fixed-size array serialization", "index.html#fixedarrays", null ],
      [ "Dynamic array serialization", "index.html#dynarray", [
        [ "SOAP-encoded array bounds", "index.html#arraybounds", null ],
        [ "One-dimensional dynamic SOAP-encoded arrays", "index.html#oned", null ],
        [ "One-dimensional dynamic SOAP-encoded arrays with non-zero offsets", "index.html#onedoffset", null ],
        [ "Nested one-dimensional dynamic SOAP-encoded arrays", "index.html#nested", null ],
        [ "Multi-dimensional dynamic SOAP-encoded arrays", "index.html#multid", null ],
        [ "Non-SOAP dynamic arrays", "index.html#list", null ],
        [ "STL containers", "index.html#templates", null ],
        [ "Polymorphic dynamic arrays and lists", "index.html#polymorphicarrays", null ],
        [ "How to change the tag names of array item elements", "index.html#arrayitems", null ]
      ] ],
      [ "base64Binary serialization", "index.html#base64binary", null ],
      [ "hexBinary serialization", "index.html#hexbinary", null ],
      [ "SOAP RPC encoded versus document/literal style", "index.html#literal", [
        [ "Serializing mixed content with literal XML strings", "index.html#literal2", null ]
      ] ]
    ] ],
    [ "XML validation", "index.html#validation", [
      [ "Default values", "index.html#defaultvalues", null ],
      [ "Occurrence constraints", "index.html#occurrence", [
        [ "Elements with minOccurs and maxOccurs restrictions", "index.html#occurs", null ],
        [ "Required and prohibited attributes", "index.html#requiredandprohibited", null ]
      ] ],
      [ "Value constraints", "index.html#valueconstraints", [
        [ "Data length restrictions", "index.html#lengthconstraints", null ],
        [ "Value range restrictions", "index.html#valuerangeconstraints", null ],
        [ "Pattern restrictions", "index.html#patternconstraints", null ]
      ] ],
      [ "Element and attribute qualified/unqualified forms", "index.html#qualified", null ]
    ] ],
    [ "XML namespaces and the namespace mapping table", "index.html#nstable", null ],
    [ "SOAP Header processing", "index.html#header", null ],
    [ "SOAP Fault processing", "index.html#fault", null ],
    [ "MIME attachments", "index.html#MIME", [
      [ "Sending a collection of MIME attachments (SwA)", "index.html#SWAsending", null ],
      [ "Retrieving a collection of MIME attachments (SwA)", "index.html#SWAreceiving", null ]
    ] ],
    [ "DIME attachments", "index.html#DIME", [
      [ "Sending a collection of DIME attachments", "index.html#DIMEsending", null ],
      [ "Retrieving a collection of DIME attachments", "index.html#DIMEreceiving", null ],
      [ "Serializing binary data with DIME attachments", "index.html#DIMEbinary", null ],
      [ "Streaming DIME", "index.html#DIMEstreaming", null ],
      [ "Streaming chunked DIME", "index.html#dimechunking", null ],
      [ "WSDL bindings for DIME attachments", "index.html#DIMEWSDL", null ]
    ] ],
    [ "MTOM attachments", "index.html#MTOM", [
      [ "Generating MultipartRelated MIME attachment bindings in WSDL", "index.html#MIMEWSDL", null ],
      [ "Sending and receiving MTOM attachments", "index.html#MTOMsendingreceiving", null ],
      [ "Streaming MIME/MTOM", "index.html#MTOMstreaming", null ],
      [ "Redirecting inbound MIME/MTOM streams based on SOAP body content", "index.html#MTOMpoststreaming", null ],
      [ "Streaming chunked MIME/MTOM", "index.html#mimechunking", null ]
    ] ],
    [ "SOAP/XML over UDP", "index.html#UDP", [
      [ "Using WS-Addressing with SOAP-over-UDP", "index.html#wsaudp", [
        [ "Client-side one-way UDP unicast", "index.html#unicast", null ],
        [ "Client-side one-way UDP multicast", "index.html#multicast", null ],
        [ "Client-side request-response UDP unicast", "index.html#requestresponseunicast", null ],
        [ "Client-side request-response multicast", "index.html#requestresponsemulticast", null ]
      ] ],
      [ "SOAP-over-UDP server", "index.html#soapoverudp", [
        [ "SOAP-over-UDP multicast receiving server", "index.html#soapoverudpmulticast", null ]
      ] ]
    ] ],
    [ "Compile-time flags", "index.html#compilerflags", [
      [ "Using the soapdefs.h header file", "index.html#soapdefs", null ]
    ] ],
    [ "Run-time flags", "index.html#flags", null ],
    [ "Run-time error codes", "index.html#errcodes", null ],
    [ "Memory management", "index.html#memory", null ],
    [ "Intra-class memory management", "index.html#classmemory", null ],
    [ "Debugging", "index.html#debugging", null ],
    [ "Limitations", "index.html#limitations", null ],
    [ "Advanced features", "index.html#advanced", [
      [ "Internationalization", "index.html#internationalization", null ],
      [ "Directives", "index.html#directives", [
        [ "Service directives", "index.html#directives-1", null ],
        [ "Service method directives", "index.html#directives-2", null ],
        [ "Schema directives", "index.html#directives-3", null ],
        [ "Schema type directives", "index.html#directives-4", null ],
        [ "Example", "index.html#example12", null ]
      ] ],
      [ "Transient data types", "index.html#transient", null ],
      [ "Serialization \"as is\" of volatile data types", "index.html#volatile", null ],
      [ "How to declare custom serializers and deserializers", "index.html#extern", null ],
      [ "Function callbacks for customized I/O and HTTP handling", "index.html#callback", null ],
      [ "How to handle HTTP 307 temporary redirect", "index.html#http307", null ],
      [ "How to implement HTTP GET, PUT, and PATCH services", "index.html#get", null ],
      [ "TCP and HTTP keep-alive", "index.html#keepalive", null ],
      [ "HTTP chunked transfer encoding", "index.html#chunked", null ],
      [ "HTTP buffered sends", "index.html#buffered", null ],
      [ "HTTP authentication", "index.html#authentication", [
        [ "HTTP bearer authentication", "index.html#bearerauthentication", null ],
        [ "HTTP basic authentication", "index.html#basicauthentication", null ],
        [ "HTTP NTLM authentication", "index.html#NTLMauthentication", null ],
        [ "HTTP proxy NTLM authentication", "index.html#NTLMproxyauthentication", null ],
        [ "HTTP proxy basic authentication", "index.html#proxyauthentication", null ]
      ] ],
      [ "Performance improvement tips", "index.html#tips", null ],
      [ "Safety guards", "index.html#safety", null ],
      [ "Timeout management for non-blocking operations", "index.html#timeout", null ],
      [ "Closing connections by force", "index.html#forceclose", null ],
      [ "Socket options and flags", "index.html#socketopt", null ],
      [ "Overriding the host and port to connect", "index.html#hostportconnect", null ],
      [ "Secure Web services with HTTPS", "index.html#serveropenssl", null ],
      [ "Secure clients with HTTPS", "index.html#clientopenssl", null ],
      [ "SSL authentication callbacks", "index.html#sslauthenticationcallbacks", null ],
      [ "SSL certificates and key files", "index.html#ssl", null ],
      [ "SSL hardware acceleration", "index.html#sslhw", null ],
      [ "SSL on Windows", "index.html#sslwin", null ],
      [ "Zlib compression", "index.html#compression", null ],
      [ "Client-side cookie support", "index.html#clientcookie", null ],
      [ "Server-side cookie support", "index.html#servercookie", null ],
      [ "Connecting clients through proxy servers", "index.html#proxyservers", null ],
      [ "Bind before connect and setting the client interface address", "index.html#bindbeforeconnect", null ],
      [ "FastCGI", "index.html#fastcgi", null ],
      [ "How to minimize application memory footprint", "index.html#lean", null ],
      [ "How to remove the BSD socket library requirement", "index.html#noio", null ],
      [ "How to combine multiple client and server implementations into one executable", "index.html#combine", null ],
      [ "How to build a client or server in a C++ code namespace", "index.html#codenamespace", null ],
      [ "How to create client/server libraries", "index.html#dylibs", [
        [ "C++ examples", "index.html#example13", null ],
        [ "C examples", "index.html#example14", null ],
        [ "C services chaining example", "index.html#example15", null ]
      ] ],
      [ "How to create DLLs", "index.html#dll", [
        [ "Creating the base stdsoap2.dll", "index.html#basedll", null ],
        [ "Creating client and server DLLs", "index.html#clientserverdll", null ]
      ] ],
      [ "How to build modules and libraries with the #module directive", "index.html#module", null ],
      [ "Plugins, modules, and extensions", "index.html#plugins", [
        [ "DOM API", "index.html#dom", null ],
        [ "The message logging plugin", "index.html#loggingplugin", null ],
        [ "RESTful server-side API with the HTTP GET plugin", "index.html#RESTfulserverGET", null ],
        [ "RESTful server-side API with the HTTP POST plugin", "index.html#RESTfulservicePOST", null ],
        [ "The HTTP digest authentication plugin", "index.html#httpdaplugin", null ],
        [ "The HTTP sessions plugin", "index.html#sessionsplugin", null ],
        [ "The Apache module plugin", "index.html#apacheplugin", null ],
        [ "The ISAPI extension plugin", "index.html#isapiplugin", null ],
        [ "The CURL plugin", "index.html#curlplugin", null ],
        [ "The WinInet plugin", "index.html#wininetplugin", null ],
        [ "The WS-Addressing plugin", "index.html#wsaplugin", null ],
        [ "The WS-ReliableMessaging plugin", "index.html#wsrmplugin", null ],
        [ "The WS-Security plugin", "index.html#wsseplugin", null ],
        [ "The WS-Discovery plugin", "index.html#wsddplugin", null ]
      ] ]
    ] ],
    [ "Copyright                                                           ", "index.html#copyright", null ],
    [ "Modules", "modules.html", "modules" ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", null ],
        [ "Variables", "functions_vars.html", "functions_vars" ],
        [ "Typedefs", "functions_type.html", null ]
      ] ]
    ] ],
    [ "Files", null, [
      [ "File List", "files.html", "files" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", null ],
        [ "Variables", "globals_vars.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", null ],
        [ "Macros", "globals_defs.html", "globals_defs" ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"annotated.html",
"group__group__debug.html#ga245426f6e253f0d00529a2b72447b956",
"group__group__flags.html#gabdb47a4b2321c119055eff7db3ecd7e6",
"group__group__s2s.html#ga6da39f8ce07f4a3de37de6c5ce33ed83",
"group__group__with.html#ga24620333a812a36ed84902ff3d897ff6",
"index.html#start"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';