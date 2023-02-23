####### This is the input file for automake, which will generate Makefile.in ##########
## not a GNU package. You can remove this line, if
## you have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = subdir-objects foreign 1.4

noinst_PROGRAMS = tcpclient tcpserver
SOAPHEADER = tcpdemo.h

include ../Makefile.defines
include ../Makefile.c_rules
SOAP_NS = tcpdemo.nsmap

tcpclient_SOURCES = tcpclient.c $(SOAPHEADER) $(SOAP_C_CLIENT)

tcpserver_SOURCES = tcpserver.c $(SOAPHEADER) $(SOAP_C_CORE) soapClient.c soapServer.c

