
The Apache module for gSOAP                                          {#mainpage}
===========================

[TOC]

By Christian Aberger, Mick Wall, Robert van Engelen, David Viner, Ryan Troll,
and La Cam Chung.


Overview                                                             {#overview}
========

SOAP/XML and REST Web services can be easily created and deployed as gSOAP
standalone services or installed as (Fast)CGI applications. In addition, the
`mod_gsoap` Apache module offers the ability to run gSOAP services directly
inside the Apache HTTP server. The `mod_gsoap` Apache module supports the
deployment of multiple gSOAP services that can run together with the usual
services on Apache. This approach offers a production-quality Web services
deployment scenario.

The `mod_gsoap` Apache module is designed to keep things simple so that
existing gSOAP services can be recompiled for Apache HTTP server deployment
without modification of the source code. The Apache `apxs` command compiles
your gSOAP service code and installs it with `mod_gsoap`. Add your new service
to Apache `httpd.conf` and presto!

The original Apache module for gSOAP home page is at
<http://mod-gsoap.sourceforge.net>. Newer versions are included in the
gSOAP distribution package in the `gsoap/mod_gsoap/mod_gsoap-0.9` directory.

Apache modules for gSOAP are provided for both Apache 1.3 and 2.x. In the
following we will discuss the Apache module for Apache 2.x.


Installation                                                          {#install}
============

First download the [Apache httpd](https://httpd.apache.org) source code and
install the httpd server in a new directory, say `apachegsoap`:

    mkdir apachegsoap
    cd apachegsoap
    tar -xjf httpd-2.4.48.tar.bz2
    cd httpd-2.4.48
    ./configure --prefix=`pwd`/.. --with-mpm=worker --enable-mods-shared=most
    make -j4
    make install

If configure fails with "error: APR not found" or "error: APR-util not found",
download and install the [Apache Portable Runtime](http://apr.apache.org)
(APR).

To use the Apache extension mechanism, your platform has to support the DSO
feature and your Apache `httpd` binary has to be built with the `mod_so`
module. The `apxs` tool automatically complains if this is not the case. You
can check this yourself by manually running the `httpd -l` command (installed
locally in `apachegsoap/bin` with the instructions above):

    cd apachegsoap
    bin/httpd -l

The module `mod_so.c` should be on the displayed list of modules.

Next, we will build and install `mod_gsoap` for Apache 2.x and up. The source
code files are located under `gsoap/mod_gsoap/mod_gsoap-0.9/apache_20` and
include `apache_gsoap.h`, `mod_gsoap.c`, and a Visual Studio project file
`mod_gsoap.vcproj`.

To compile `mod_gsoap`, execute:

    cd /path/to/gsoap/installation/gsoap/mod_gsoap/mod_gsoap-0.9/apache_20
    ln -s ../../../stdsoap2.h .
    sudo $HOME/apachegsoap/bin/apxs -a -i -DWITH_GZIP -lz -c mod_gsoap.c

Invoking `apxs` with `-DWITH_GZIP -lz` enables decompression in `mod_gsoap`
with libz (`-lz`), which is not required, but useful and recommended.

Root permissions are required, so we used `sudo apxs` here.

The `apxs` command should be on your path or located in `apachegsoap/bin` where
we installed httpd.  Make sure to use `$HOME/apachegsoap/bin/apxs` if multiple
httpd versions are installed.

If a specific C compiler is required, say `cc`, then try `apxs -S CC=cc ...`.


Deploying C services with the Apache module                            {#deploy}
===========================================

After building `mod_gsoap` we are ready to deploy gSOAP services written in C
with the Apache module.

The gSOAP package contains a calculator example. We will use this example to
walk you through the creation and deployment of an Apache module gSOAP service.

First, copy the calculator example:

    cd apachegsoap
    cp /path/to/gsoap/installation/gsoap/samples/calc/* .
    cp /path/to/gsoap/installation/gsoap/stdsoap2.* .
    cp /path/to/gsoap/installation/gsoap/mod_gsoap/mod_gsoap-0.9/apache_20/apache_gsoap.h .

Next, edit `calcserver.c` by removing `main()` and replace it with
`IMPLEMENT_GSOAP_SERVER()` as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "apache_gsoap.h"
    IMPLEMENT_GSOAP_SERVER() /* replaces main() { ... } */
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To initialize the engine context with flags and/or plugins, see \ref plugins.

Then compile and build the service:

    soapcpp2 -c -SL -wx calc.h
    sudo $HOME/apachegsoap/bin/apxs -a -c calcserver.c soapC.c soapServer.c stdsoap2.c
    chmod 755 .libs/calcserver.so

Again, the `apxs` command should be on your path or located in
`apachegsoap/bin` where we installed httpd.  Make sure to use
`$HOME/apachegsoap/bin/apxs` as shown above if multiple httpd versions are
installed.

This creates `.libs/calcserver.so` service module that is universally readable.
Also make sure that `.libs/calcserver.so` is readable through the entire path,
that is through `/home/username/apachegsoap/.libs` where `username` is your
user account name.

If you have installed source files in other directories, then you will need to
add appropriate `-I` and `-L` options with the `apxs` command shown above.

To deploy the service, we will need to add our module with its properties to
`httpd.conf` (for example we can add it at the end):

    <IfModule mod_gsoap.c>
     <Location /soap>
      SetHandler gsoap_handler
      SOAPLibrary /home/username/apachegsoap/.libs/calcserver.so
      Order allow,deny
      Allow from all
     </Location>
    </IfModule>

The `httpd.conf` file is usually found under `/private/etc/apache2/httpd.conf`.
However, since we use a locally installed Apache `httpd` server that searches
the `/home/username/apachegsoap` path, you will find `httpd.conf` in
`/home/username/apachegsoap/conf`.

The `Location` property sets part of the URL of the service, which in this case
will be `http://localhost/soap` or if you set a port that is different than the
standard HTTP port 80, say 9080, the full URL is `http://localhost:9080/soap`.
To change the port from 80 to 9080, edit `httpd.conf` and change `Listen`:

    Listen 9080

To start the service:

    cd apachegsoap
    bin/apachectl start

Point your browser to `http://localhost:9080` and the page should show the
message "It works!".

To stop the server:

    bin/apachectl stop

To use the service by client applications, direct the endpoint URL of clients
to "http://localhost:9080/soap", for example in the `calcclient.c` code that
came with the gSOAP example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    const char server[] = "http://localhost:9080/soap";
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Then we build the client:

    soapcpp2 -c -CL -wx calc.h
    cc -o calcclient calcclient.c soapC.c soapClient.c stdsoap2.c

and run it to send a request to perform a computation within the Apache server
and to receive the response from the server, which is displayed:

    ./calcclient add 2 3
    result = 5

To let clients access the WSDL of a service, you can use the query `?wsdl` as
part of the URL such as `http://localhost:9080/soap?wsdl` to pull the file
WSDL file from the current location of the service, e.g.
`.libs/calcservice.wsdl` where our example `calcservice.so` lives.  Copy the
`calc.wsdl` file to `.libs/calcservice.wsdl` to make it available to the Apache
server.

Deployment of multiple modules is possible since gSOAP 2.8.71, by specifying
multiple `<Location>` entries in `<IfModule mod_gsoap.c>` in `httpd.conf`, one
for each service.  The change in gSOAP 2.8.71 modified function
`::SoapSharedLibrary_load` in `mod_gsoap.c` as follows to resolve linking
symbols locally:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    const int nFlags = RTLD_LAZY | RTLD_LOCAL; // was RTLD_LAZY | RTLD_GLOBAL
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Alternatively, if one module links against equally-named symbols coming from
another module, then it is recommended to pass a version info file to the
linker, instructing it to make all symbols local, except for the Apache module
table instance.  The version file (e.g. `myapachegsoap.ver`) looks something
like this:

    VERS_1.0 {
      global:
        myapachegsoap_module;
      local:
        *;
    };

This file is then passed to the linker with option `-Wl,myapachegsoapv.ver`.


Initialization and plugins                                            {#plugins}
==========================

By replacing `main()` with `IMPLEMENT_GSOAP_SERVER()`, several functions are
implemented that are used by the Apache module for gSOAP.  These functions
include `apache_default_soap_init()` to initialize a newly constructed context.

With gSOAP 2.8.54 and greater we can add our own initialization function to
initialize the context.  By doing so we can set context flags and register
plugins.  To define our own initialization function we use
`IMPLEMENT_GSOAP_SERVER_INIT(init_func)` instead of `IMPLEMENT_GSOAP_SERVER()`.
For example, to enable XML indentation, MTOM attachments and message logging
with the logging plugin:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "plugin/logging.h"
    #include "apache_gsoap.h"
    void mod_gsoap_init(struct soap *soap, request_rec *r)
    {
      static FILE *fdi = NULL, *fdo = NULL;
      if (fdi == NULL)
        fdi = fopen("/tmp/INBOUNDAUDIT.log", "a");
      if (fdo == NULL)
        fdo = fopen("/tmp/OUTBOUNDAUDIT.log", "a");
      soap_set_mode(soap, SOAP_XML_INDENT | SOAP_ENC_MTOM);
      soap_register_plugin(soap, logging);
      soap_set_logging_inbound(soap, fdi);
      soap_set_logging_outbound(soap, fdo);
    }
    IMPLEMENT_GSOAP_SERVER_INIT(mod_gsoap_init) /* replaces main() { ... } */
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `request_rec` type is an Apache structure that contains information for the
module to process HTTP requests and respond accordingly.  For details on this
structure, please consult the Apache documentation.

The `soap_set_mode(soap, SOAP_XML_INDENT | SOAP_ENC_MTOM)` sets XML indentation
in outbound XML messages and enables MTOM attachments.

The `soap_register_plugin(soap, logging)` and the following calls save the
audit logs of inbound and outbound messages (note that messages are not
continually flushed to the log files by the logging plugin, meaning the logs may
appear incomplete until you stop httpd to close these files).  The
gsoap/plugin/logging.h and logging.c files are located in the gSOAP source code
tree.  Add logging.c to the apxs command to compile the logging plugin source
code file.

Multiple plugin registrations can be performed as needed.  The following plugins
have been verified to work with the `mod_gsoap` Apache module:

- logging plugin to log messages
- httpget plugin to support HTTP GET
- httppost plugin to support HTTP PUT, PATCH, and DELETE
- wsaapi (WSA) plugin for WS-Addressing, requires plugin registry with `SOAP_WSA_NEW_TRANSFER`
- wsseapi (WSSE) plugin for WS-Security
- wstapi (WST) plugin for WS-Trust

@note the wsaapi plugin should be registered with
`soap_register_plugin_arg(soap, http_wsa, SOAP_WSA_NEW_TRANSFER)` to allow
connection relays and data transfers to reply and error servers.

@warning Do not use any of the `SOAP_IO` flags to initialize or set the
context, such as `SOAP_IO_KEEPALIVE` and `SOAP_IO_CHUNK`.  HTTP chunking
is handled automatically and the Apache server manages its connections.


REST services                                                           {#rest}
=============

An example use of the httpget and httppost plugins (see previous section) to
support HTTP GET and POST of JSON REST requests:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "json.h"
    #include "plugin/httpget.h"
    #include "plugin/httppost.h"
    #include "apache_gsoap.h"
    void mod_gsoap_init(struct soap *soap, request_rec *r)
    {
      static struct http_post_handlers handlers[] = {
        { "application/json", json_post_handler },
        { NULL }
      };
      soap_register_plugin_arg(soap, http_get, http_get_handler);
      soap_register_plugin_arg(soap, http_post, handlers);
    }
    IMPLEMENT_GSOAP_SERVER_INIT(mod_gsoap_init) /* replaces main() { ... } */
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

HTTP POST with Content-Type `application/json` is sent to the
`http_post_handler`, for example a currentTime server (this is based on
gsoap/samples/xml-rpc-json/json-currentTimeServer.c):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    int json_post_handler(struct soap *ctx)
    {
      /* receive JSON request */
      struct value request;
      if (soap_begin_recv(ctx)
       || json_recv(ctx, &request)
       || soap_end_recv(ctx))
      {
        json_send_fault(ctx);
      }
      else
      {
        if (is_string(&request) && !strcmp(*string_of(&request), "getCurrentTime"))
        {
          struct value *response = new_value(ctx);
          *dateTime_of(response) = soap_dateTime2s(ctx, time(0));
          ctx->http_content = "application/json; charset=utf-8";
          if (soap_response(ctx, SOAP_FILE)
           || json_send(ctx, response)
           || soap_end_send(ctx))
            return soap->error;
        }
        else
        {
          /* JSON error as per Google JSON Style Guide */
          json_send_error(ctx, 400, "Wrong method", *string_of(&request));
        }
      }
      return ctx->error;
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note that `soap_response(soap, SOAP_FILE)` produces the HTTP 200 OK response
header with the HTTP Content-Type specified by `soap->http_content`.  To
return a specific HTTP status code, return the status code from the handler: a
handler may return `SOAP_OK` or an HTTP status error code to indicate success
or failure, respecively.  To decline a request return `DECLINED` without
producing a response message.

A `soap_closesock()` call is typically used with stand-alone servers, but is
not needed to "close" the connection in the Apache module, but harmless when
called, even when called more than once.

If `soap_serve()` is not generated by soappcp2, for example when implementing
non-SOAP REST services, then you must define the following `soap_serve()` dummy
function in your REST service application's source code, see further below.
The `soap_serve()` function is invoked by `mod_gsoap` for any HTTP POST request
received, to handle SOAP/XML and REST HTTP POST service operations.

To support HTTP PUT, PATCH, DELETE and any POST requests, add the corresponding
entries to the table:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    static struct http_post_handlers handlers[] = {
      { "POST",      generic_POST_handler }, // warning: overrides soap_serve()
      { "PUT",       generic_PUT_handler },
      { "PATCH",     generic_PATCH_handler },
      { "DELETE",    generic_DELETE_handler },
      { NULL }
    };
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The httpget plugin sets the `soap::fget` callback function to serve HTTP GET
requests (this disables the `?wsdl` feature, but which can be implemented by
the handler).  The httppost plugin sets the `soap::fput`, `soap::fpatch` and
`soap::fdel` callbacks to serve HTTP PUT, PATCH and DELETE requests,
respectively.  The HTTP POST requests are handled differently, via
`soap_serve()` (generated by soapcpp2 if one or more SOAP/XML service
operations are defined) that invokes the `soap::fform` callback that points to
the handler.  This callback is set by the httppost plugin upon receiving a HTTP
POST request that matches the key in the table, i.e.  `"POST"` always matches
and `"application/json"` only matches when the HTTP Content-Type is
`application/json`.

@warning a `generic_POST_handler`, when specified with a `"POST"` key entry in
the table, takes priority over `soap_serve()`.  This means that SOAP/XML
messages will not be processed by `soap_serve()`!  Instead, a SOAP/XML
handler can be registered with the entries `"text/xml"` for SOAP 1.1 and
`"application/soap+xml"` for SOAP 1.2 (for SOAP with attachments, also register
a `"application/xop+xml"` handler for MTOM).  This handler should invoke
`soap_serve_request()` but never invoke `soap_serve()`.

For more details on plugins, see the logging, httpget and httppost plugin
documentation in the gSOAP manual.

The following `soap` context variables are populated from the HTTP request and
are made available to be inspected by the plugin handlers:

- `soap::action` the SOAPAction string or NULL
- `soap::bearer` the Bearer token or NULL
- `soap::endpoint` the URL string (http://hostname/path) of the request
- `soap::host` the hostname string of this server
- `soap::http_content` the Content-Type string or NULL (NULL if no Content-Type
    header was present such as in HTTP GET requests)
- `soap::ip` the IP4 address of the client is a 32 bit integer
- `soap::ip6[]` the IP6 address of the client is an array of four integers
- `soap::path` the path string of the URL

The `path` and `http_content` strings are very useful to decide the proper
response by a handler for to the type of request sent by the client.

@warning never return the contents of a file pointed to by `soap::endpoint` or
`soap::path`, unless the path of the URL is checked in the code to be valid and
blocked if it is not.  You must prevent unauthorized access to directories and
files by returning 404 (Not Found) if the path is not pointing to a
publicly-accessible resource.  You must also check for `..` in the path to
block requests from snooping around in higher dirs!

We can register a HTTP GET handler to display this information in a browser:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "plugin/httpget.h"
    #include "apache_gsoap.h"

    int http_get_handler(struct soap *soap)
    {
      const char *content = soap->http_content;
      soap->http_content = "text/html"; // the content-type as specified by ...
      soap_response(soap, SOAP_FILE);   // .... SOAP_FILE
      soap_send(soap, "<html>");
      soap_send(soap, "<br>Client IP4 = ");
      soap_send(soap, soap_unsignedInt2s(soap, soap->ip));
      soap_send(soap, "<br>Client IP6 = ");
      soap_send(soap, soap_unsignedInt2s(soap, soap->ip6[0]));
      soap_send(soap, ".");
      soap_send(soap, soap_unsignedInt2s(soap, soap->ip6[1]));
      soap_send(soap, ".");
      soap_send(soap, soap_unsignedInt2s(soap, soap->ip6[2]));
      soap_send(soap, ".");
      soap_send(soap, soap_unsignedInt2s(soap, soap->ip6[3]));
      soap_send(soap, ".");
      soap_send(soap, "<br>Endpoint = ");
      soap_send(soap, soap->endpoint);
      soap_send(soap, "<br>Host = ");
      soap_send(soap, soap->host);
      soap_send(soap, "<br>Path = ");
      soap_send(soap, soap->path);
      soap_send(soap, "<br>Content-Type = ");
      soap_send(soap, content ? content : "N/A");
      soap_send(soap, "<br>SOAPAction = ");
      soap_send(soap, soap->action);
      soap_send(soap, "<br>Bearer = ");
      soap_send(soap, soap->bearer);
      soap_send(soap, "</html>");
      soap_end_send(soap); 
      return SOAP_OK; 
    }

    void mod_gsoap_init(struct soap *soap, request_rec *r)
    {
      soap_register_plugin_arg(soap, http_get, http_get_handler);
    }
    IMPLEMENT_GSOAP_SERVER_INIT(mod_gsoap_init) /* replaces main() { ... } */
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Opening a browser with the server's URL (`http://localhost:9080/soap` for
example, as specified in `httpd.conf`) shows the values associated with the
HTTP GET request.

If `soap_serve()` is not generated by soappcp2, for example when implementing
non-SOAP REST services, then you must define the following `soap_serve()` dummy
function in your REST service application's source code:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    int soap_serve(struct soap *soap)
    {
      if (soap_begin_serve(soap) == SOAP_OK)
        soap->error = SOAP_NO_METHOD; // OK, but we have nothing to do
      return soap->error
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `soap_serve()` function is invoked by `mod_gsoap` for any HTTP POST request
received, to handle SOAP/XML and REST service operations.  In this case we
only have REST service operations and there is no `soap_serve()` generated by
soapcpp2 for a SOAP/XML interface header file (e.g. produced by wsdl2h).

The httppost plugin's POST handlers are invoked when `soap_begin_serve()`
executes, before any SOAP/XML request can be handled.  If a HTTP plugin is
registered to handle POST requests and the POST request was handled
successfully, then `soap_begin_serve()` returns `SOAP_STOP` indicating that the
request was served.

On the other hand, when a request is received that is a valid SOAP/XML POST
request (or a POST request that is not handled by one of your registered
(generic) POST handlers), then we return `SOAP_NO_METHOD` or we could return
404 for "Not Found" for example.

@warning when implementing SOAP/XML services in addition to REST services,
never call `soap_serve()` in a plugin handler function.  The `soap_serve()`
function is already called by the `mod_gsoap` module.  If you want to process a
SOAP/XML request in a handler, then call `soap_serve_request()` to process the
XML request message and produce an XML response message for "two-way" SOAP/XML
messaging with POST or PATCH.  "Two-way" POST or PATCH and "one-way" SOAP/XML
messaging with PUT and GET is possible and automatic when the interface header
file for soapcpp2 declares protocols for XML REST for service operations
`ns__Method`:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //gsoap ns service method-protocol: Method1 POST
    int ns__Method1(...);
    //gsoap ns service method-protocol: Method2 PUT
    int ns__Method2(...);
    //gsoap ns service method-protocol: Method3 GET
    int ns__Method3(...);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `POST` (or `HTTP` which is the same as `POST`) and `PATCH` methods are
"two-way".  The `PUT` and `GET` methods are "one-way" REST operations.  SOAP
protocols for messages with SOAP envelopes are declared similarly:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //gsoap ns service method-protocol: Method1 SOAP
    int ns__Method1(...);
    //gsoap ns service method-protocol: Method2 SOAP-PUT
    int ns__Method2(...);
    //gsoap ns service method-protocol: Method3 SOAP-GET
    int ns__Method3(...);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `SOAP` method is "two-way" messaging with SOAP envelopes.  The `SOAP-PUT`
and `SOAP-GET` methods are "one-way" SOAP operations.


Dynamic libraries                                                   {#libraries}
=================

If you are using dynamic libraries to deploy services with `mod_gsoap`, then
those should be closed properly to avoid memory leaks. To do so add the following line:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    dlclose(pConfig->m_pLibraries->m_pSOAPLibrary->m_hLibrary);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

at the end of the `gsoap_handler()` function in `mod_gsoap.c`.


Building C++ services from service classes                            {#classes}
==========================================

The Apache server is written in C. Building Apache modules in C++ can be tricky
and may not be fully guaranteed due to compiler differences.  Several online
resources exist that offer advice on how to implement C++ modules for Apache
2.x.  If this fails, the best alternative is to use FastCGI (see gSOAP user
guide on "FastCGI Support").

When using C++ gSOAP service classes generated by `soapcpp2` options `-i` or
`-j` we need to implement the C function `soap_serve()` that dispatches these
C++ services.

We will walk you through the implementation of a service using the same
calculator example demonstrated above, but written in C++ using a service class
`calcService`.

First, run `soapcpp2` with option `-j` to generate a service class:

    soapcpp2 -j -SL -wx calc.h

Create a new `calcerver.cpp` file with the following code:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "soapcalcService.h"
    #include "calc.nsmap"
    #include "apache_gsoap.h"
    IMPLEMENT_GSOAP_SERVER()
    extern "C" int soap_serve(struct soap *soap)
    {
      calcService service(soap);
      int err = service.serve();
      service.destroy();
      return err;
    }
    int calcService::add(double a, double b, double *result)
    {
      *result = a + b;
      return SOAP_OK;
    } 
    int calcService::sub(double a, double b, double *result)
    {
      *result = a - b;
      return SOAP_OK;
    } 
    int calcService::mul(double a, double b, double *result)
    {
      *result = a * b;
      return SOAP_OK;
    } 
    int calcService::div(double a, double b, double *result)
    {
      *result = b != 0 ? a / b : 0.0;
      return SOAP_OK;
    } 
    int calcService::pow(double a, double b, double *result)
    {
      *result = ::pow(a, b);
      return SOAP_OK;
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here, `calcService` is the service class declared and defined in the generated
`soapcalcService.h` and `soapcalcService.cpp` files, respectively.

The `apxs` command is used to compile as follows, with the `-S CC=c++` option:

    bin/apxs -a -c -S CC=c++ calcserver.cpp soapC.cpp soapcalcService.cpp stdsoap2.cpp
    chmod 755 .lib/calcserver.so

This creates `.libs/calcserver.so` service module that is universally readable.
Also make sure that `.libs/calcserver.so` is readable through the entire path,
that is through `/home/username/apachegsoap/.libs`.

After compilation, the new module should be added to `httpd.conf` as was
explained above.

When multiple service classes are defined, when `soapcpp2 -j` is applied to
multiple `.h` files, then you have two options:

-# create an `.so` library for each service with the `apxs` command and add
   each module to `httpd.conf` with a new `Location` property.
-# create one `.so` library with the services combined, all listening to the
   same service URL. Only one module is added to `httpd.conf` since the
   `Location` property is the same. Note that the `?wsdl` query is not as
   useful in this case, since we cannot publicize the service WSDLs combined.

The second option requires C++ namespaces as explained in section "How to Chain
C++ Server Classes to Accept Messages on the Same Port" in the gSOAP user guide.
Basically, you should chain the services as follows:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    #include "apache_gsoap.h"
    IMPLEMENT_GSOAP_SERVER()
    extern "C" int soap_serve(struct soap *soap)
    {
      int err;
      if ((err = soap_begin_serve(soap)) == SOAP_OK)
      {
        X::Service service_x(soap);
        if ((err = service_x.dispatch()) == SOAP_NO_METHOD)
        {
          Y::Service service_y(soap);
          if ((err = service_y.dispatch()) == SOAP_NO_METHOD)
          {
            Z::Service service_z(soap);
            err = service_z.dispatch();
          }
        }
      }               
      soap_destroy(soap);
      soap_end(soap);
      return err;
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Troubleshooting                                                         {#debug}
===============

It is recommended to test the service first as a stand-alone server over a port
using `soap_bind()` and `soap_accept()`. Debugging is much easier this way.

After testing as a stand-alone server, to debug the service with the Apache
module, compile your service application with compiler option `-g` (apxs option
`-Wc,-g`to control debug information output.  For example:

    bin/apxs -Wc,-g -a -c calcserver.c soapC.c soapServer.c stdsoap2.c

Debug the service as it is deployed while `httpd` is running.  To do so, we
first stop the service and start it up in single threaded mode so we can attach
to it to a debugger such as `gdb` or `lldb`:

    cd apachegsoap
    bin/apachectl stop
    bin/httpd -X -f /home/username/apachegsoap/conf/httpd.conf &

You will get a process ID, say 12345, which we will attach to a debugger:

    gdb -p 12345

You will see a load of symbols loading, including `mod_gsoap.so`.

Next, we set a breakpoint on the `soap_serve` call (the main entry point), let
`gdb` know that we accept the pending breakpoint, and then continue the
process:

    (gdb) b soap_serve
    Function "soap_serve" not defined.
    Make breakpoint pending on future shared library load? (y or [n]) y
    Breakpoint 1 (soap_serve) pending.
    (gdb) c
    Continuing.

We execute our `calcclient` from another window, which triggers the breakpoint.

    [Switching to Thread 0x7f3fbd209950 (LWP 25493)]
    Breakpoint 1, 0x00007f3fb059e398 in soap_serve () from /home/username/apachegsoap/gsoap-2.8/gsoap/samples/calc/.libs/calcserver.so
    Current language: auto; currently asm
    (gdb) n
    Single stepping until exit from function soap_serve,
    which has no line number information.
    0x00007f3fb05a5eec in apache_default_soap_serve () from /home/username/apachegsoap/gsoap-2.8/gsoap/samples/calc/.libs/calcserver.so
    (gdb)

Note that when Apache `httpd` runs as user `wwwrun` (or another user) then you
will have to run the debugger as that same user. To do so, execute:

    sudo -u wwwrun gdb /usr/sbin/httpd2-worker 25487

When failures occur, see also the error logs that are saved by httpd to
`/home/username/apachegsoap/logs/error_log`.

Thanks to Jon Scobie for suggestions to improve this section.


Limitations                                                       {#limitations}
===========

The gSOAP Apache module does not support receiving DIME protocol messages with
attachments.  MIME and MTOM attachments are supported.


License                                                               {#license}
=======

The Apache modules for gSOAP are released under the gSOAP open source public
license and GPLv2.  The open source licensing is replaced by Genivia's license
for commercial use when a commercial-use license is purchased by customer.


Further reading                                                    {#references}
===============

[All things `mod_gsoap`](http://techiebitsandpieces.blogspot.com/2011/03/all-things-modgsoap.html) by Jon Scobie

[Apache HTTP server project](http://httpd.apache.org/download.cgi).
