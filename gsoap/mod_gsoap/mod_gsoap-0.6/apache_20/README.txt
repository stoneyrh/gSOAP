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

Here's how to compile mod_gsoap for apache 2.x:

/usr/local/apache2/bin/apxs -a -i -c -I/path/to/gsoap/installation mod_gsoap.c

The URI query ?wsdl returns the WSDL, e.g. "http://domain/path/calc?wsdl" which
pulls the file calc.wsdl from the current location of the service.

To change the path to the WSDL files, modify mod_gsoap.c:

#define GSOAP_GET_WSDL_PATH ""

SETTING UP HTTPD

Download and build Apache httpd:

mkdir testbuild
cd testbuild
tar -xjf httpd-2.2.17.tar.bz2
cd httpd-2.2.17
./configure --prefix=`pwd`/.. --with-mpm=worker --enable-mods-shared=most
make -j4
make install

SETTING UP MOD_GSOAP

cd gsoap/mod_gsoap/mod_gsoap-0.6/apache_20
apxs -a -i -c -I testbuild/include mod_gsoap.c
cp apache_gsoap.h testbuild/include

BUILDING AN EXAMPLE MOD_GSOAP SERVICE

Copy the calculator example:

cp gsoap/samples/calc/* testbuild

Edit calcserver.c by removing main() and replace with:

include "apache_gsoap.h"
IMPLEMENT_GSOAP_SERVER()

Then compile and build:

soapcpp2 -c -L -x calc.h
apxs -a -c calcserver.c soapC.c soapServer.c -lgsoap

To deploy our service, we need to add to httpd.conf (e.g. at the end):

<IfModule mod_gsoap.c>
<Location /soap>
SetHandler gsoap_handler
SOAPLibrary /home/testuser/apachegsoap/gsoap-2.8/gsoap/samples/calc/.libs/calcserver.so
Order allow,deny
Allow from all
</Location>
</IfModule>

To start the service:

cd testbuild
bin/apacectl start

Point your browser to http://localhost:9080 and the page should show "It works!"

To use the service, direct the endpoint URL of clients to "http://localhost:9080/soap", for example in the calcclient.c code:

const char server[] = "http://localhost:9080/soap";

To build the client:

gcc -o calcclient calcclient.c soapC.c soapClient.c -lgsoap

and test it:

./calcclient add 2 3

USING DYNAMIC LIBRARIES

To avoid memory leaks when using dynamic libraries for mod_gsoap, add:

dlclose(pConfig->m_pLibraries->m_pSOAPLibrary->m_hLibrary);

at the end of gsoap_handler() in mod_gsoap.c

DEBUGGING

It is recommended to test the service first as a stand-alone server over a port
using soap_bind() and soap_accept(). Debugging as much easier this way.

