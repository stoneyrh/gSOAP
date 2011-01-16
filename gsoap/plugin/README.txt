This directory contains plugins for extending the gSOAP engine's capabilities.

cacerts.*	To embed client-side certificate chain in code (no cacerts.pem)
httpda.*	HTTP Digest Authentication, see doc/httpda
httpget.*	HTTP GET method support
httpform.*	HTTP POST application/x-www-form-urlencoded support
httppost.*	HTTP POST method support for example non-SOAP requests
httpmd5.*	HTTP MD5 checksums
logging.*	Message logging (selective inbound/outbound)
plugin.*	Example plugin for aspiring plugin developers
wsaapi.*	WS-Addressing (wsa) plugin, see doc/wsa
wsrmapi.*	WS-ReliableMessaging (wsrm) plugin, see doc/wsrm
wsseapi.*	WS-Security (wsse) plugin, see doc/wsse

Supporting modules:

smdevp.*	EVP-based streaming (signed) message digest engine
mecevp.*	EVP-based streaming message encryption engine
md5evp.*	MD5 EVP interface for httpda and httpmd5
threads.*	Threads, mutex, and condition variables

C versus C++:

All files are suitable for C and C++ compilation and C++ checks are included in
the source code whenever applicable. If necessary, rename the .c file(s) to
.cpp for your project.

