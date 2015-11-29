####### This is the input file for automake, which will generate Makefile.in ##########
## not a GNU package. You can remove this line, if
## you have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = subdir-objects foreign 1.4

noinst_PROGRAMS = jsoncpp json-GitHub xml-rpc-currentTime
SOAPHEADER = xml-rpc.h

include ../Makefile.defines
include ../Makefile.cpp_rules
SOAP_NS = $(SOAP_NS_DEF)

jsoncpp_SOURCES = jsoncpp.cpp xml-rpc.cpp json.cpp $(SOAPHEADER) $(SOAP_CPP_CORE)
jsoncpp_LDADD = $(SOAP_CPP_LIB) $(SAMPLE_EXTRA_LIBS)

json_GitHub_CPPFLAGS = -DWITH_OPENSSL -DWITH_GZIP
json_GitHub_SOURCES = json-GitHub.cpp xml-rpc.cpp json.cpp $(SOAPHEADER) $(SOAP_CPP_CORE)
json_GitHub_LDADD = $(SOAP_CPP_LIB_SSL) $(SAMPLE_EXTRA_LIBS) $(SAMPLE_SSL_LIBS)

xml_rpc_currentTime_SOURCES = xml-rpc-currentTime.cpp xml-rpc.cpp json.cpp $(SOAPHEADER) $(SOAP_CPP_CORE)
xml_rpc_currentTime_LDADD = $(SOAP_CPP_LIB) $(SAMPLE_EXTRA_LIBS)
