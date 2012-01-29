GSOAP=../../bin/soapcpp2
SOAPH=../../stdsoap2.h
SOAPC=../../stdsoap2.c
SOAPCPP=../../stdsoap2.cpp
SOAPDOMC=../../dom.c
SOAPDOMCPP=../../dom.cpp
CC=gcc
CPP=g++
LIBS=
COFLAGS=-O2
CWFLAGS=-Wall
CIFLAGS=-I../..
CMFLAGS=
CFLAGS= $(CWFLAGS) $(COFLAGS) $(CIFLAGS) $(CMFLAGS)
all:		httpgettest httpposttest
httpgettest:	httpgettest.h httpgettest.c $(SOAPH) $(SOAPC)
		$(GSOAP) -c -CSL httpgettest.h
		$(CC) $(CFLAGS) -o httpgettest httpgettest.c soapC.c $(SOAPC) $(LIBS)
httpposttest:	httpposttest.h httpposttest.c $(SOAPH) $(SOAPC)
		$(GSOAP) -c -CSL httpposttest.h
		$(CC) $(CFLAGS) -o httpposttest httpposttest.c soapC.c $(SOAPC) $(LIBS)
.PHONY: clean distclean
clean:
		rm -f *.o soapH.h soapStub.h soapC.c soapC.cpp soapClient.c soapClient.cpp soapServer.c soapServer.cpp soapClientLib.c soapClientLib.cpp soapServerLib.c soapServerLib.cpp soap*Proxy.h soap*Proxy.cpp soap*Service.h soap*Service.cpp
distclean:
		rm -f *.o soapH.h soapStub.h soapC.c soapC.cpp soapClient.c soapClient.cpp soapServer.c soapServer.cpp soapClientLib.c soapClientLib.cpp soapServerLib.c soapServerLib.cpp soap*Proxy.h soap*Proxy.cpp soap*Service.h soap*Service.cpp
		rm -f *.wsdl *.xsd *.xml *.nsmap *.log
		rm -f httpgettest httpposttest
