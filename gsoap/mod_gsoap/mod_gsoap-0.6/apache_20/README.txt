Apache 2.x modules for gSOAP

For a detailed walk-through, please visit

http://techiebitsandpieces.blogspot.com/2011/03/all-things-modgsoap.html

More about the mod-gsoap project:

http://mod-gsoap.sourceforge.net/

The modules are released under the gSOAP open source public license, see
license.pdf in the gSOAP root dir of the package. The license allows commercial
open source use and development with this package.

apache_gsoap.h			mod_gsoap module for Apache v2.x
mod_gsoap.c			mod_gsoap module for Apache v2.x
mod_gsoap.vcproj		MSVC project

To use the Apache extension mechanism your platform has to support the DSO
feature and your Apache httpd binary has to be built with the mod_so module.
The apxs tool automatically complains if this is not the case. You can check
this yourself by manually running the command

$ httpd -l

The module mod_so should be part of the displayed list.

Here's how to compile mod_gsoap for apache 2.x:

$ apxs -a -i -c -I/path/to/gsoap/installation mod_gsoap.c

SETTING UP HTTPD

Download and build Apache httpd:

$ mkdir testbuild
$ cd testbuild
$ tar -xjf httpd-2.2.17.tar.bz2
$ cd httpd-2.2.17
$ ./configure --prefix=`pwd`/.. --with-mpm=worker --enable-mods-shared=most
$ make -j4
$ make install

SETTING UP MOD_GSOAP

$ cd gsoap/mod_gsoap/mod_gsoap-0.6/apache_20
$ apxs -a -i -c -I testbuild/include mod_gsoap.c
$ cp apache_gsoap.h testbuild/include

This will install libraries in /usr/libexec/apache2

BUILDING AN EXAMPLE MOD_GSOAP SERVICE

Copy the calculator example:

$ cd testbuild
$ cp gsoap/samples/calc/* .
$ cp gsoap/stdsoap2.* .

Edit calcserver.c by removing main() and replace with:

#include "apache_gsoap.h"
IMPLEMENT_GSOAP_SERVER()

Then compile and build:

$ soapcpp2 -c -SL -wx calc.h
$ apxs -a -c calcserver.c soapC.c soapServer.c stdsoap2.c

This creates .libs/calcserver.so service module.

Make sure the .so file is universally readible:

-rwxr-xr-x  1 root  staff  304172 Aug 30 14:51 calcserver.so*

and make sure it is readible through the entire path testuser/testbuild/.libs.

To deploy your service, we need to add to httpd.conf (e.g. at the end):

<IfModule mod_gsoap.c>
 <Location /soap>
  SetHandler gsoap_handler
  SOAPLibrary /home/testuser/testbuild/.libs/calcserver.so
  Order allow,deny
  Allow from all
 </Location>
</IfModule>

The httpd.conf file is usually found under

/private/etc/apache2/httpd.conf

To start the service:

$ cd testbuild
$ bin/apacectl start

Point your browser to http://localhost:9080 and the page should show "It works!"

To use the service, direct the endpoint URL of clients to "http://localhost:9080/soap", for example in the calcclient.c code:

const char server[] = "http://localhost:9080/soap";

To build the client:

$ gcc -o calcclient calcclient.c soapC.c soapClient.c stdsoap2.c

and test it:

$ ./calcclient add 2 3

By default, the URI query ?wsdl returns the WSDL, e.g.
"http://domain/path/calc?wsdl" which pulls the file calc.wsdl from the current
location of the service. You need to copy the calc.wsdl file there.

USING DYNAMIC LIBRARIES

To avoid memory leaks when using dynamic libraries for mod_gsoap, add:

dlclose(pConfig->m_pLibraries->m_pSOAPLibrary->m_hLibrary);

at the end of gsoap_handler() in mod_gsoap.c

DEBUGGING

It is recommended to test the service first as a stand-alone server over a port
using soap_bind() and soap_accept(). Debugging as much easier this way.

