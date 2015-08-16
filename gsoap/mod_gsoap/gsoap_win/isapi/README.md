
The ISAPI extension for gSOAP                                        {#mainpage}
=============================

[TOC]

By Christian Aberger and Robert van Engelen.


Overview                                                             {#overview}
========

SOAP/XML and REST Web services can be easily created and deployed as gSOAP
standalone services or installed as (Fast)CGI applications. In addition, the
`mod_gsoap` Internet Server Application Programming Interface (ISAPI) extension
offers the ability to run gSOAP services directly inside the Microsoft Internet
Information Server (IIS). This is achieved through an ISAPI extension DLL. The
ISAPI extension supports the deployment of multiple gSOAP services that can run
together with the usual services on IIS. This approach offers a
production-quality Web services deployment scenario.

The `mod_gsoap` ISAPI extension is designed to keep things simple so that
existing gSOAP services can be recompiled for IIS deployment without
modification of the source code. The `mod_gsoap.dll` DLL (dynamic link library)
implements the ISAPI extension that uses the query string of the request URL to
determine which gSOAP back-end service to run. It will select the appropriate
service DLL to load the service dynamically, if not already present. Therefore,
to add more services, simply create new DLLs for these services. IIS need not
be restarted to deploy them.


Installation                                                          {#install}
============

To build and install the `mod_gsoap.dll` ISAPI extension for gSOAP:

- Open Visual Studio C++ 6.0 or later.
- Go to `Tools|Options` and activate the `Directories` Panel. 
- Select `Include Files` from the dropdown and add your project directory that
  contains `stdsoap2.h`.
- Select `Executable Path` and add the full path to the `gsoap/bin/win32`
  directory in the unpacked gSOAP package that contains the `soapcpp2.exe`
  tool.
- Open `all4iis.dsw` that can be found in `gsoap/mod_gsoap/gsoap_win/isapi`
  in the gSOAP package.
- Activate the `all4iis` project and build all.
- Install and use the `mod_gsoap.dll` ISAPI extension as described below.


Deploying services with ISAPI                                          {#deploy}
=============================

After building `mod_gsoap.dll` we are ready to deploy gSOAP services with the
ISAPI extension.

The gSOAP package contains a calculator example to demonstrate the ISAPI
extension. You will find this example in the gSOAP package under
`gsoap/mod_gsoap/gsoap_win/isapi/samples/calc`. We will use this example to
walk you through the creation and deployment of an ISAPI service.

- Make sure to compile all sources in C++ compilation mode with Visual Studio
  C++. If you migrate to a project file `.vcproj` then set `CompileAs="2"` in
  your `.vcproj`.
- Open `calc.dsw` found in `gsoap/mod_gsoap/gsoap_win/isapi/samples/calc` in
  the gSOAP package.
- Compile as a single DLL the service code `calcserver.cpp`, the gSOAP engine
  code `stdsoap2.cpp`, the soapcpp2-generated codes `soapC.cpp` and
  `soapServer.cpp`. You may have to run `soapcpp2.exe calc.h` from the DOS
  command window to generate code. Adding a custom-build step in Visual Studio
  can make this easier.
- Add a `gsoap` directory to your `wwwroot` directory, for example
  `C:\Inetpub\wwwroot\gsoap`.
- Open Internet Service Manager from the `Control Panel` select
  `Administrative` tools. 
- Create in Internet Service Manager a new virtual directory called `gsoap`,
  see [details here on how to create a virtual root](#vroot) and also shown in
  [this screen shot](http://www.genivia.com/images/gsoapvdir.png).
- Copy `mod_gsoap.dll` and `calc.dll` to the newly created `gsoap` directory
  (for example `C:\Inetpub\wwwroot\gsoap`).
- Start the "World Wide Web Publishing Service".
- Enter in your browser `http://localhost/gsoap/mod_gsoap.dll`. This should
  give a response from the server that explains what the correct URL is. This
  proves that `mod_gsoap.dll` is configured correctly.
- Enter in your browser `http://localhost/gsoap/mod_gsoap.dll?calc`. This
  should give a response from the server that you should use a POST command,
  not a GET. This proves that `mod_gsoap` was able to load your DLL. So in
  principle your installation and service deployment is OK.

To test the calculator IIS service with a simple client, do the following:

- Check that the client code `calcclnt.c` of the calculator example in
  `gsoap/mod_gsoap/gsoap_win/isapi/samples/calc` has the correct service
  endpoint URL, which must correspond to your installation:
  `const char server[] = "http://localhost/gsoap/mod_gsoap.dll?calc";`
- Build the `calcclnt.exe` client, e.g. using `calcclnt.dsp`.
- Open a DOS command window and go to the directory where `calcclnt.exe` was
  built and execute `calcclnt.exe add 3 5`.
- The response should be: `result=8`.

We recommend to test services first as standalone gSOAP services to ensure that
the service logic is correct. If the service logic is correct but the service
DLL does not produce a response, then please see the next section. Otherwise,
read on.

A `Makefile` is included that contains commands to start and stop debugging of
IIS and for cleaning the directory. The advanced user can compile everything
with just one command. Be sure that `msdev.exe` and `nmake.exe` are on your
PATH. Then enter the command `nmake` from a DOS command window and presto!

To develop your own service DLL in Visual Studio, select `File|New` and create
a new empty Dynamic Link Library project. Copy `stdsoap2.def` from the
`mod_gsoap/gsoap_win/isapi/samples/calc` directory to your project directory
and add it to the project. This will ensure that the required functions are
exported and visible to `mod_gsoap`, such as `soap_serve` that invokes service
operations (this function is auto-generated by `soapcpp2.exe` and defined in
`soapServer.cpp`).

In addition, two C functions should be defined by your service code, namely
`int mod_gsoap_init(void)` and `int mod_gsoap_terminate(void)`:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    extern "C" {
    int mod_gsoap_init(void) {
	// TODO: add your initialization code here 
	return SOAP_OK;
    }
    int mod_gsoap_terminate(void) {
	// TODO: add your termination code here
	return SOAP_OK;
    }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `mod_gsoap_init` function is called by `mod_gsoap` when the DLL was
successfully loaded and before processing begins. The `mod_gsoap_terminate`
function is called when the DLL is unloaded. These functions should return
`SOAP_OK` on success. You can use these initialization and termination hooks as
you see fit.

Multiple ISAPI services can run together with all other Internet services on
your machine on port 80 (or another port, as configured in IIS). The request
your client must submit is a URL with a query string, such as was illustrated
above with `http://127.0.0.1/gsoap/mod_gsoap.dll?calc`.

The requested URL is evaluated by IIS and the query string (the part after the
`?`) is used to dispatch the service request to the `calc.dll` service.

Note that instead of `127.0.0.1` (which is the `localhost`), clients on the
network should use the full domain name of the machine.

For security reasons only DLLs stored in the same directory as `mod_gsoap.dll`
can be used. If you want to do specialized initializations in your DLL then you
may want to add and export a `DllMain` function, which will be called when the
IIS process attaches to your DLL and before it detaches it. Do not rely on the
Thread attach/detach callback: in my experience IIS does not always call
`DllMain` in your DLL if these threads were already in the thread pool before
your DLL was loaded. Use thread local storage instead.


Troubleshooting                                                         {#debug}
===============

If the client receives an error from the ISAPI service, such as for example:

    SOAP FAULT: SOAP-ENV:Client
    "End of file or no input"
    Detail: http://localhost/gsoap/mod_gsoap.dll?calc

Then we recommend the following steps:

- Make sure that `dumpbin.exe` is in your PATH (it can be found somewhere in
  the Visual Studio binaries).
- Open a DOS command window and go to the directory where `mod_gsoap.dll` is
  located (`C:\Inetpub\wwwroot\gsoap`). Execute the following command:
  `dumpbin /exports calc.dll`.
- The output should contain the exported symbols that are listed in the
  `stdsoap2.def` file. If you don't find these symbols you propably forgot to
  add the necessary `stdsoap2.def` exports for your project. This should include
  `soap_initialize`, `soap_serve`, `soap_delete`, `soap_end`, `soap_done`,
  `soap_register_plugin_arg`, and `soap_lookup_plugin`. See for example
  `stdsoap2.def` in `gsoap/mod_gsoap/gsoap_win/isapi/samples/calc`.

If you want to debug a DLL, you must set the DLL to run in-proccess.
Right-click on the `gsoap` virtual root in internet service manager and set the
`Application Protection` to `Low (IIS Process)`. Remove the `Enable Session
State` and buffering and `Parent Paths`. Don't forget to allow the IISAdmin and
WWW Service to interact with the desktop.

To enable debugging of services and/or clients:
 
- Compile `calc.dll` and/or `calcclnt.exe` with the `DEBUG` option (in
  `Preprocessor Definitions` add `DEBUG`).
- Delete all `.log` files from the current directory, if any.
- Run the client `calcclnt.exe add 3 5` again.
- You should get three files with the extension `.log` in the current directory
  of the client and in the DLL directory. Please read what is there.

Note: for Debugging with Win2000 there are two `.reg` files in the `Div`
directory, that switch debugging of IIS on and off (see Q273639 and related),
and a start and stop command in the `Makefile` to start and stop IIS debugging.
Make sure that the path to `msdev` is in the System environment variables
(`PATH`) of the system account (not only of your own user account, this is not
seen by IISAdmin). 


Creating the virtual root                                               {#vroot}
=========================

If you have problems creating the virtual root then these instructions should
help.

- Open from the control panel `Administrative Tools` and then select
  `Internet Services Manager` (may be located in the Option Pack submenus).
- Click with the right mouse button on `Default Web Site`, then select
  `New` and `Virtual Directory`.
- Click `Next` and enter as `Alias` the name you want to give to the URL, such
  as `soap`. Then press `Next` again and browse for the directory where your
  DLL that you have built in the previous step is, for example in
  `c:\Inetpub\wwwroot\gsoap` and press `Next`.
- In the access permissions, disable all permissions except `Execute (such as
  ISAPI applications or CGI)`. This must be enabled.
- Click `Next` and `Finish`.

For testing it might be best to enable the `Browse` permission and then browse
to `http://localhost/gsoap`.


License                                                               {#license}
=======

The Apache modules for gSOAP are released under the gSOAP open source public
license (compatible with commercial licensing) and GPLv2.


Further reading                                                    {#references}
===============

[What is an ISAPI Extension?](http://www.codeproject.com/Articles/1432/What-is-an-ISAPI-Extension)

[ISAPI Extensions](https://msdn.microsoft.com/en-us/library/ms525282.aspx) as explained by Microsoft
