
Efficient XML and JSON exchange over TCP/IP with optional TLS message security
==============================================================================

This set of 6 examples include clients and servers to exchange XML or JSON data
efficiently over TCP/IP without HTTP(S).  Messages are sent unidirectional or
bidirectional over a socket.

The server example applications are accepting a message exchange session
request from a client on an open port.  A client-server session consists of
several exchanges to demonstrate bi-directional and uni-directional exchanges.
The session terminates with a "bye" message initiated by the client.

In fact, many other message exchange patterns are possible, including mixed
client and server behaviors in one application (not included, but should be
obvious from the client and server examples.)

A client/server application that exhanges messages over TCP/IP directly can
only use one serialization protocol at a time, either XML or JSON.  We cannot
alternate between different protocols, because there is no identifying payload
content type in a header, like with HTTP.

XML and JSON are "self-contained" in that an XML and JSON payload is parsed
from begin to end.  Therefore, an (HTTP) header is not required to identify the
payload content type and message body length.

How it works
------------

To send and receive plain XML and JSON over TCP/IP (or UDP or other transport
protocols), we use the `SOAP_ENC_PLAIN` flag to initialize the `soap` context.
To keep the connection open ("alive") we use the `SOAP_IO_KEEPALIVE` flag and
set `soap::max_keep_alive = 0` (no maximum) if the session should potentially
never terminate.

To terminate the session and close the socket, we set `soap::keep_alive = 0`
and call `soap_closesock(soap)` (with a C++ proxy/service class method
`soap_close_socket()`).

On the client side, the URL to connect to may or may not use `http://`.  This
is ignored when the `SOAP_ENC_PLAIN` flag is active.  To make an SSL/TLS
connection, we must use `https://` to enable SSL/TLS as if HTTPS is used.

These settings are sufficient and the only difference compared to messaging
over HTTP(S), but we also want to make sure the application is robust.

It is critical to set sensible timeouts to prevent a peer from using an open
socket too long without progress.  Setting timeouts prevent potential denial
of services.  For example:

    soap->transfer_timeout = 5;
    soap->recv_timeout = 3;
    soap->send_timeout = 3;

Note: timeouts are in seconds, negative values specify timeouts in
milliseconds.  Zero means no timeout is set.

On the client side we can specify a connection attempt timeout:

    soap->connect_timeout = 5;

And the server side a connection accept timeout:

    soap->accept_timeout = 5;

To limit the length of each message received by a receiver, we set:

    soap->recv_maxlength = nnnn;

where `nnnn` is the maximum message length in bytes.  A zero length means
unlimited.

Linux and Unix systems may receive a "broken pipe" signal when the other
side disconnects unexpectedly, for example after a timeout.  To silence the
signal:

    signal(SIGPIPE, SIG_IGN);

Note that a runtime error is produced when the other side disconnected, which
means that the open socket should be closed on this end too (see above).

The following example client and server applications demonstrate the
efficient use of XML or JSON over TCP/IP with optional SSL/TLS to encrypt the
messages.

SOAP/XML serialized payloads
----------------------------

- tcpclient.c example client in C
- tcpserver.c example server in C
- tcpclient.cpp example client in C++
- tcpserver.cpp example server in C++

SOAP/XML serialized payloads with SSL/TLS message security
----------------------------------------------------------

- tcpclient-tls.c example client in C
- tcpserver-tls.c example server in C
- tcpclient-tls.cpp example client in C++
- tcpserver-tls.cpp example server in C++

JSON payloads
-------------

- tcpclient-json.c example client in C
- tcpserver-json.c example server in C
- tcpclient-json.cpp example client in C++
- tcpserver-json.cpp example server in C++

A SSL/TLS JSON exchange example is not included, but can be easily derived from
the other examples.

Build steps
-----------

See the source code file headers for instructions to build the examples.

Resources
---------

- SSL/TLS documentation: https://www.genivia.com/tutorials.html#tls
- JSON API documentation: https://www.genivia.com/doc/xml-rpc-json/html/index.html
= Tutorials: https://www.genivia.com/tutorials.html
- gSOAP user guide: https://www.genivia.com/doc/guide/html/index.html
- gSOAP modules: https://www.genivia.com/doc/guide/html/modules.html
- gSOAP `soap` context API: https://www.genivia.com/doc/guide/html/group__group__context.html
- gSOAP `soap` context members: https://www.genivia.com/doc/guide/html/structsoap.html
