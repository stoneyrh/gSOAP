####### This is the input file for automake, which will generate Makefile.in ##########
## not a GNU package. You can remove this line, if
## you have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = subdir-objects foreign 1.4

noinst_PROGRAMS = testmsgr
SOAPHEADER = ../../import/dom.h

include ../Makefile.defines
include ../Makefile.cpp_rules
SOAP_NS = $(SOAP_NS_DEF)

testmsgr_CFLAGS = -DWITH_OPENSSL -DWITH_GZIP
testmsgr_SOURCES = testmsgr.cpp $(SOAPHEADER) $(SOAP_CPP_CORE)
testmsgr_LDADD = $(SOAP_CPP_LIB) $(SAMPLE_EXTRA_LIBS) $(SAMPLE_SSL_LIBS)
