
This application demonstrates server-side and client-side logic for services
based on WS-Addressing. At the server side, WS-Addressing enables
forwarding/relaying of service responses and faults to other services. At the
client side, a relayed response or fault will not be received and an HTTP
ACCEPTED (code 202) is delivered instead, assuming that the relay was
successful.

This header file illustrates two gSOAP soapcpp2 tooling tricks to enable
services to accept SOAP Fault messages and to create a one-way service
operation to handle responses.

	Usage:

	After compilation, start the main server at port 11001:
	> ./wsademo 11001

	In a new window, start a return service at port 11002:
	> ./wsademo 11002
	This service handles response messages from the main service.

	In a new window, start a fault service at port 11003:
	> ./wsademo 11003
	This service handles faults from the main service.

	In a new window, run the client:
	> ./wsademo hello
	This example shows the server returning "hello" to the client.

	> ./wsademo fault
	This example shows the server returning a SOAP fault to the client.

	> ./wsademo hello r
	This example shows the server returning "hello" to the return service.

	> ./wsademo hello n
	This example shows the server accepting the message without reply.

	> ./wsademo error e
	This example shows the server returning a wsa fault to fault service.

	> ./wsademo fault e
	This example shows the server returning a SOAP fault to fault service.

	Note: when the response service is down, the response cannot be relayed
	and the client (or fault service) will be informed about the failure.

