Apache 2.x modules for gSOAP

The modules are released under the gSOAP open source public license, see
license.pdf in the gSOAP root dir of the package. The license allows commercial
open source use and development with this package.

apache_gsoap.h			mod_gsoap module for Apache v2.x
mod_gsoap.c			mod_gsoap module for Apache v2.x
mod_gsoap.vcproj		MSVC project

Here's how to compile mod_gsoap for apache 2.x:

/usr/local/apache2/bin/apxs -a -i -c -I/path/to/gsoap/installation mod_gsoap.c

