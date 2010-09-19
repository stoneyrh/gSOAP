The soapcpp2 compiler source distribution contains the following files:

README.txt	This file
MakefileManual	Extra makefile when autoconf/automake fail to produce one
soapcpp2.h	Main header file
soapcpp2.c	Main application
symbol2.c	Symbol table handling and code generation module
error2.h	Header file for error2.c
error2.c	Error handling routines
init2.c		Compiler symbol table initialization
soapcpp2_lex.l	Flex/Lex tokens
soapcpp2_yacc.y	Yacc/Bison grammar

LICENSING
Please see LICENSE.txt in root directory of the package.

BUILD NOTES

To build soapcpp2 when autoconf/automake fail, use:

	make -f MakefileManual

QNX
===

On QNX the bison.simple file is located in $QNX_HOST/usr/share/bison.simple
Update your .profile to include:

export BISON_SIMPLE=$QNX_HOST/usr/share/bison/bison.simple 
export BISON_HAIRY=$QNX_HOST/usr/share/bison/bison.hairy 

WIN32
=====

You need to install Flex and Bison to build soapcpp2.

An MSN article explains how to do this with MS VS2005:

http://msdn.microsoft.com/en-us/library/aa730877(VS.80).aspx#vccustombr_topic3

The older Bison v1.6 can crash on Win32 systems if YYINITDEPTH is too small:
Compile with /DYYINITDEPTH=5000

