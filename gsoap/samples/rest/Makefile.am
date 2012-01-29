####### This is the input file for automake, which will generate Makefile.in ##########
## not a GNU package. You can remove this line, if
## you have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 1.4

noinst_PROGRAMS = httpgettest httpposttest
SOAPHEADER = httpposttest.h

include ../Makefile.defines
include ../Makefile.c_rules
SOAP_NS = $(SOAP_NS_DEF)

httpgettest_SOURCES = httpgettest.c $(SOAPHEADER) $(SOAP_C_CORE) ../../plugin/httpget.c
httpposttest_SOURCES = httpposttest.c $(SOAPHEADER) $(SOAP_C_SERVER) ../../plugin/httppost.c

