
The Tandem NonStop bridge enables the gSOAP toolkit for Tandem NonStop
platforms. The bridge replaces the IO operation of the gSOAP engine with Tandem
NonStop IO operations.

Tandem NonStop bridge source code for gSOAP 2.8.0 and higher:

  tandem.h	Tandem IO bridge interface
  tandem.c	Tandem blocking IO bridge
  tandem_nw.c	Tandem nonblocking IO (no wait) bridge

Usage:

  Add to your client/server code the following:

  #include "tandem.h"
  struct soap *soap = soap_new();
  tandem_init(soap, "ProcName");
  socket_set_inet_name(argv[0]); // See Tandem docs
  ... // client or server code goes here as per gSOAP documentation
  soap_destroy(soap);
  soap_end(soap);
  tandem_done(soap);
  soap_free(soap);

Compile flags for C/C++:

  -DTANDEM_NONSTOP

Linkage requirements:

  Compile and link with tandem.c or tandem_nw.c

Example:

  cc -DTANDEM_NONSTOP -o calcclient calcclient.c soapC.c soapClient.c stdsoap2.c tandem.c
    or
  cc -DTANDEM_NONSTOP -o calcclient calcclient.c soapC.c soapClient.c stdsoap2.c tandem_nw.c

  cc -DTANDEM_NONSTOP -o calcserver calcserver.c soapC.c soapServer.c stdsoap2.c tandem.c
    or
  cc -DTANDEM_NONSTOP -o calcserver calcserver.c soapC.c soapServer.c stdsoap2.c tandem_nw.c

Copyright

  Genivia Inc.

Licensing

  GPL (GNU Public License)
  Or the Commercial-use license from Genivia Inc.
