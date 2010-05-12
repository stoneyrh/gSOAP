================================================================================

Thanks for using gSOAP!

The gSOAP toolkit provides a cross-platform software development toolkit for C
and C++ server and client Web service applications, and simplifies the overall
use of XML in any type of application. The toolkit supports SOAP 1.1/1.2 RPC
encoding and document/literal styles, WSDL 1.1, MTOM/MIME/DIME attachments
(streaming), SOAP-over-UDP, request-response and one-way messaging. The toolkit
also supports WS-Addressing and WS-Security, with several other WS-* available
or under development. See the official open-source gSOAP website
http://gsoap2.sourceforge.net for project status and latest news.

* The gSOAP 'soapcpp2' compiler and code generator and 'stdsoap2' runtime
  engine are stable since version release 2.1.3.

* The gSOAP 'wsdl2h' WSDL/schema parser and code generator is stable since
  wsdl2h version release 1.1.0. The 'wsdl2h' tool fully supports WSDL 1.1 and
  XML schemas.

The software is provided "as is", without any warranty. However, gSOAP
has received a lot of support from users and has been extensively tested
in the real world. We also continue to improve gSOAP and add new features.

================================================================================
WHAT'S COOL?
================================================================================

The gSOAP 'wsdl2h' tool is a gSOAP application itself, which demonstrates the
capabilities of the generic XML handling by the toolkit to parse WSDL, XML
schemas, and SOAP/XML.

The gSOAP toolkit supports streaming technologies to expedite SOAP/XML and
MTOM/MIME attachment transfers of potentially unlimited data lengths.

The gSOAP toolkit is the only toolkit that supports the serialization of native
C and C++ data types directly in XML. You can use it to export and import your
application data in XML without having to write wrapper routines.

The gSOAP toolkit ensures as small memory footprint. XML is a processed as a
transient format and not buffered. Many optimizations have been applied to
reduce resource requirements and to expedite XML parsing.

The gSOAP toolkit provides stand-alone HTTP(S) web server functionality as well
as Apache mod and IIS hooks. Also CGI and FastCGI is possible. A web server
example demonstrating the stand-alone functionality is included in the package.

================================================================================
PACKAGE
================================================================================

This distribution package contains platform-independent source code. Pre-built
'soapcpp2' and 'wsdl2h' binaries are included for the following platforms:

	* Win32 i386 compatible
	* Linux i386 compatible
	* MAC OS X universal

The binaries are located in 'gsoap/bin'.

Important: these 'wsdl2h' binaries use the default configuration without SSL
support (no HTTPS site access).

To configure and build the toolkit binaries and libraries, please see the
installation instructions in the 'INSTALLATION' section below.

================================================================================
INSTALLATION
================================================================================

This part explains how gSOAP is built on your platform.

Requirements to configure and build the package:

1. Automake tools (make and GNU m4) to configure and build
2. Bison http://www.gnu.org/software/bison or the alternative Yacc
3. Flex http://flex.sourceforge.net 
4. OpenSSL (for optional HTTPS) http://www.openssl.org
5. Zlib (for optional compression) http://www.zlib.net
6. Pthreads or win32 threads (optional)

The open source licenses for these tools are compatible with gSOAP licensing
under GPL and commercial licensing.

Some example applications won't compile without OpenSSL and Pthreads.

Win32 binaries and project code is included in this package. Win32 users can
start right away without autoconf/automake. The 'soapcpp2.exe' binary compiler
and 'wsdl2h.exe' WSDL parser are included in 'gsoap/bin/win32', see also the
'gsoap/VisualStudio2005' folder for the tool project files. The 'soapcpp2.exe'
and 'wsdl2h.exe' tools are command-line based and should be invoked from within
the IDE to process WSDL, XSD, and gSOAP service specification header files:

.wsdl .xsd --> wsdl2h.exe --> .h (special .h formatted with gSOAP annotations)
                              .h --> soapcpp2.exe --> .h .c .cpp .xml ...

Symbian instructions and example code is located in 'gsoap/Symbian'.

Palm OS support is no longer available for this release. The latest stable
release with Palm OS support is gSOAP 2.7.8c.

To build gSOAP on your platform using autoconf/automake, please enter the
following commands:

	$ ./configure
	$ make
	$ make install

This will install the executables and libraries on your system (and you need
root access to do so).

To build without OpenSSL support, use:

	$ ./configure --disable-openssl
	$ make
	$ make install

To configure and build the examples, use the --enable-samples option:

	$ ./configure --enable-samples

To configure and build the libraries in DEBUG mode, which produces 'SENT.log',
'RECV.log' and 'TEST.log' files for message logs and gSOAP engine event logs,
use:

	$ ./configure --enable-debug

If you want to install the executables in your local folder, enter:

	$ ./configure
	$ make
	$ make install exec_prefix=$HOME

To build your projects, you need the following executables:

	soapcpp2	the gSOAP stub/skeleton generator
	wsdl2h		the gSOAP WSDL/schema parser and code generator

These are created after 'make' in 'gsoap/src' and 'gsoap/wsdl'. Note that
pre-built executables for select platforms can be found in 'gsoap/bin'.

You also need the following libraries (build from stdsoap2.c[pp]):

	libgsoap++.a		C++ runtime
	libgsoapck++.a		C++ runtime with HTTP cookie support
	libgsoapssl++.a		C++ runtime with cookies, zlib, and SSL
	libgsoap.a		C runtime
	libgsoapck.a		C runtime with HTTP cookie support
	libgsoapssl.a		C runtime with cookies, zlib, and SSL

This version of gSOAP requires SSL support with OpenSSL 0.9.6 or later.

Alternatively, you can use the stdsoap2.c[pp] source code to build your project
instead of the libraries (libraries are all derived from stdsoap2.c[pp]). See
the gSOAP documentation on how to enable HTTP cookies, Zlib compression, and
SSL support in stdsoap2.c[pp].

For developers: there is a command file ./makemake
It can be used to generate the required ./configure script.
This will create the Makefiles:

	$ ./makemake
	$ make

You can also execute the following steps from the commandline:

	$ aclocal
	$ autoheader
	$ automake --add-missing
	$ autoconf
	$ automake
	$ ./configure --enable-samples
	$ make

If the above fails, try the following:

	* remove autom4te.cache
	* get the latest config.guess and config.sub from GNU

================================================================================
GETTING STARTED
================================================================================

The gSOAP 'wsdl2h' tool converts WSDLs into a gSOAP header file for processing
with the gSOAP stub/skeleton generator 'soapcpp2' to generate XML
serialization, stubs, and skeletons code to build Web services applications.
Use 'wsdl2h' followed by 'soapcpp2' to translate an entire set of WSDL and XML
schemas into representative C or C++ data structures and associated XML
parsers. You can also use the gSOAP 'soapcpp2' tool directly on existing C/C++
data structure declarations to create XML serialization routines for these
types to simplify the storage of data in XML.

Example translation of WSDL to code in two steps:

	$ wsdl2h -s -o calc.h http://www.cs.fsu.edu/~engelen/calc.wsdl
	$ soapcpp2 calc.h

The 'calc.h' header file contains the services and XML schema types represented
in C/C++, together with other useful information copied from the WSDL related
to the service. Run Doxygen on it to generate a nice set of pages.

Do not include the wsdl2h-generated 'calc.h' header file directly into your
code (the declarations are replicated in the generated code). The header file
is processed by the gSOAP stub compiler 'soapcpp2' to generate the following
files for your project:

	soapClient.cpp	client-side stub routines for service invocation
	soapServer.cpp	server-side skeleton routines for server development
	soapC.cpp	C/C++ parameter marshalling code
	calc.nsmap	An XML-to-C/C++ namespare mapping table

To compile a client, all you need to do is to compile and link 'soapC.cpp',
'soapClient.cpp', and 'stdsoap2.cpp' (or the installed libgsoap++, see
INSTALLATION below) with your code. In your source code, add:

	#include "soapH.h"
	#include "calc.nsmap"

This imports all soapcpp-generated definitions and the namespace mapping table.

To develop a C++ client application based on proxies, use 'soapcpp2' option -i:

	$ wsdl2h -s -o calc.h http://www.cs.fsu.edu/~engelen/calc.wsdl
	$ soapcpp2 -i calc.h

This generates 'soapcalcProxy.h' and 'soapcalcProxy.cpp' with a calcProxy
class you can use to invoke the service. For example:

	#include "soapcalcProxy.h"
	#include "calc.nsmap"
	main()
	{ calcProxy service;
	  double result;
	  if (service.add(1.0, 2.0, result) == SOAP_OK)
	    std::cout << "The sum of 1.0 and 2.0 is " << result << std::endl;
  	  else
	    service.soap_stream_fault(std::cerr);
	}

Compile and link with 'soapC.cpp' and 'stdsoap2.cpp' (or -lgsoap++).

To develop a C client, use 'wsdl2h' option -c to generate pure C code.

There are many options that you can use depending on the need to develop C
applications, C++ with or without STL, or C++ proxy and server objects. In
addition, the XML schema type mapping is defined by 'typemap.dat', located in
the project root and 'WS' folders. The 'typemap.dat' file is used to customize
the 'wsdl2h' output. It is important to use this file for larger projects that
depend in WS-* protocols, such as WS-Addressing and WS-Security.

More information about the 'wsdl2h' and 'soapcpp2' tools and their options can
be found in the gSOAP documentation and the Quick How-To page on the gSOAP Web
site, see: http://gsoap2.sourceforge.net

See also the 'gsoap/wsdl/README.txt' for more details on the WSDL parser and
installation. The 'gsoap/bin' folder includes pre-built 'soapcpp2' and
'wsdlh2' executables for various platforms.

================================================================================
BUILD NOTES
================================================================================

QNX

On QNX the bison.simple file is located in $QNX_HOST/usr/share/bison.simple
Update your .profile to include:

	export BISON_SIMPLE=$QNX_HOST/usr/share/bison/bison.simple 
	export BISON_HAIRY=$QNX_HOST/usr/share/bison/bison.hairy 

WIN32

Bison 1.6 can crash on Win32 systems if YYINITDEPTH is too small Compile with
/DYYINITDEPTH=5000

================================================================================
CHANGELOG
================================================================================

Visit http://www.cs.fsu.edu/~engelen/changelog.html to view the latest changes.

================================================================================
LICENSE
================================================================================

See LICENSE.txt

================================================================================
COPYRIGHT
================================================================================

gSOAP is copyrighted by Robert A. van Engelen, Genivia, Inc.
Copyright (C) 2000-2008 Robert A. van Engelen, Genivia, Inc.
All Rights Reserved.

================================================================================
USE RESTRICTIONS
================================================================================

You may not: (i) transfer rights to gSOAP or claim authorship; or (ii) remove
any product identification, copyright, proprietary notices or labels from gSOAP.

================================================================================
WARRANTY 
================================================================================

GENIVIA INC. EXPRESSLY DISCLAIMS ALL WARRANTIES, WHETHER EXPRESS, IMPLIED OR
STATUTORY, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, OF FITNESS FOR A PARTICULAR PURPOSE, NONINFRINGEMENT OF THIRD
PARTY INTELLECTUAL PROPERTY RIGHTS, AND ANY WARRANTY THAT MAY ARISE BY REASON
OF TRADE USAGE, CUSTOM, OR COURSE OF DEALING.  WITHOUT LIMITING THE
FOREGOING, YOU ACKNOWLEDGE THAT THE SOFTWARE IS PROVIDED "AS IS" AND THAT
GENIVIA INC. DO NOT WARRANT THE SOFTWARE WILL RUN UNINTERRUPTED OR ERROR FREE.
LIMITED LIABILITY: THE ENTIRE RISK AS TO RESULTS AND PERFORMANCE OF THE
SOFTWARE IS ASSUMED BY YOU.  UNDER NO CIRCUMSTANCES WILL GENIVIA INC. BE LIABLE
FOR ANY SPECIAL, INDIRECT, INCIDENTAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES OF
ANY KIND OR NATURE WHATSOEVER, WHETHER BASED ON CONTRACT, WARRANTY, TORT
(INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, ARISING OUT OF OR IN
ANY WAY RELATED TO THE SOFTWARE, EVEN IF GENIVIA INC. HAS BEEN ADVISED ON THE
POSSIBILITY OF SUCH DAMAGE OR IF SUCH DAMAGE COULD HAVE BEEN REASONABLY
FORESEEN, AND NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY
EXCLUSIVE REMEDY PROVIDED.  SUCH LIMITATION ON DAMAGES INCLUDES, BUT IS NOT
LIMITED TO, DAMAGES FOR LOSS OF GOODWILL, LOST PROFITS, LOSS OF DATA OR
SOFTWARE, WORK STOPPAGE, COMPUTER FAILURE OR MALFUNCTION OR IMPAIRMENT OF
OTHER GOODS.  IN NO EVENT WILL GENIVIA INC. BE LIABLE FOR THE COSTS OF
PROCUREMENT OF SUBSTITUTE SOFTWARE OR SERVICES.  YOU ACKNOWLEDGE THAT THIS
SOFTWARE IS NOT DESIGNED FOR USE IN ON-LINE EQUIPMENT IN HAZARDOUS
ENVIRONMENTS SUCH AS OPERATION OF NUCLEAR FACILITIES, AIRCRAFT NAVIGATION OR
CONTROL, OR LIFE-CRITICAL APPLICATIONS.  GENIVIA INC. EXPRESSLY DISCLAIM ANY
LIABILITY RESULTING FROM USE OF THE SOFTWARE IN ANY SUCH ON-LINE EQUIPMENT IN
HAZARDOUS ENVIRONMENTS AND ACCEPTS NO LIABILITY IN RESPECT OF ANY ACTIONS OR
CLAIMS BASED ON THE USE OF THE SOFTWARE IN ANY SUCH ON-LINE EQUIPMENT IN
HAZARDOUS ENVIRONMENTS BY YOU.  FOR PURPOSES OF THIS PARAGRAPH, THE TERM
"LIFE-CRITICAL APPLICATION" MEANS AN APPLICATION IN WHICH THE FUNCTIONING OR
MALFUNCTIONING OF THE SOFTWARE MAY RESULT DIRECTLY OR INDIRECTLY IN PHYSICAL
INJURY OR LOSS OF HUMAN LIFE.

================================================================================
EXTERNAL THIRD-PARTY LIBRARIES
================================================================================

The gSOAP toolkit is mostly self-contained and does not require any third-party
software to run in a basic configuration. When compression and SSL encryption
are required the Zlib and OpenSSL libraries must be installed.

To build the gSOAP 'soapcpp2' compiler, you must have Bison and Flex installed
or the older Yacc and Lex equivalents. Note that licensing differs for Flex
versus Lex, and Bison versus Yacc.

Win32 builds of clients and services requires winsock.dll. To do this in
Visual C++ 6.0, go to "Project", "settings", select the "Link" tab (the
project file needs to be selected in the file view) and add "wsock32.lib" to
the "Object/library modules" entry. The distribution contains a Visual Studio
2005 project example in the 'samples/calc_vs2005' folder with the necessary
project settings to link libraries and automatically invoke to soapcpp2
compiler as a custom build.

================================================================================
DISCLAIMER
================================================================================

WE TRY OUR BEST TO PROVIDE YOU WITH "REAL-WORLD" EXAMPLES BUT WE CANNOT
GUARANTEE THAT ALL CLIENT EXAMPLES CAN CONNECT TO THIRD PARTY WEB SERVICES
WHEN THESE SERVICES ARE DOWN OR HAVE BEEN REMOVED.

================================================================================
