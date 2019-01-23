Simple examples illustrating asynchronous messaging with SOAP and REST:

- asyncsoap.c   C example SOAP asynchronous messaging with one thread
- asyncsoap.cpp C++ example SOAP asynchronous messaging with one thread
- asyncrest.c   C example REST asynchronous messaging with one thread
- asyncrest.cpp C++ example REST asynchronous messaging with one thread

- asyncsoap2.c   C example SOAP asynchronous messaging with two threads
- asyncsoap2.cpp C++ example SOAP asynchronous messaging with two threads
- asyncrest2.c   C example REST asynchronous messaging with two threads
- asyncrest2.cpp C++ example REST asynchronous messaging with two threads

These examples use the gSOAP webserver example located in the directory
gsoap/samples/webserver, which should be build to run the example.  The gSOAP
webserver optionally uses the httppipe HTTP pipelining plugin to support HTTP
pipelining.

To build the asynsoap C example:
$ soapcpp2 -c -CL -r -wx async.h
$ cc -o asyncsoap asyncsoap.c stdsoap2.c soapC.c soapClient.c

Start the webserver at port 8080, then run asyncsoap:
$ ../webserver/webserver 8080 &
$ ./asyncsoap

See also the build instructions in the C/C++ source code of the examples.

Asynchronous messaging splits the sending operation from the receive operation.
Sends should be paired with receives.  By contrast, HTTP pipelining allows
multiple sends to be followed by multiple receives.  HTTP pipelining requires
at least two threads, one for sending and one for receiving.  HTTP servers may
not implement HTTP pipelining that is required to handle multiple requests
messages.

HTTP pipelining may boost performance, though it is not widely supported and
the performance gains may dissapoint.

HTTP pipelining on the server side is easy with gSOAP, just add:

    #include "plugin/httppipe.h"

    struct soap *soap = soap_new1(SOAP_IO_KEEPALIVE); // keep-alive required
    soap_register_plugin(soap, httppipe);             // register

The gsoap/samples/webserver/webserver can be started with HTTP pipelining
enabled, say on port 8080 with options -e (pipeline) and -k (keepalive) as
follows:

    $ ../webserver/webserver -e -k 8080

Implementing HTTP pipelining correctly on the client side requires threads and
logic to deal with failed requests and responses.  Using only one thread may
cause significant message blocking issues or even deadlock with infinite IO
timeouts:

    Client              Server
    send req1 --------> recv req1
    send req2 --->      processing
    waiting        <--- send res1
    waiting             waiting
    :                   :
    send req1 failed    send res1 failed

Using two client threads T1 and T2 end orks:

    Client T1           Client T2               Server
    send req1 --------------------------------> recv req1
    send req2 --->      waiting                 processing
    waiting       \     recv res1 <------------ send res1
    waiting        ---------------------------> recv req2
    waiting             waiting                 processing
    waiting             recv res2 <------------ send res2
    done                done

When the client thread T2 does not receive one or more responses from the
server it may be caused by the lack of HTTP pipeline support by the server
or by a transmission error.  In either case the client thread T1 should resend
the message.  Such a send-resend scheme requires messaging to be "idempotent",
meaning that the server state does not matter.  HTTP GET, HEAD, PUT, and DELETE
are idempotent but HTTP POST is not.  However, HTTP POST can be made idempotent
if the POST message contents do not depend on the server state, which is
typical for SOAP/XML Web services that commonly use POST message exchanges.  In
general, be forewarned that if any of the messages depend on the server state
then HTTP pipelining is a bad idea.

No client-side HTTP pipelining example is included here, please contact Genivia
www.genivia.com if you are interested to see such examples in the future and we
will add them.

