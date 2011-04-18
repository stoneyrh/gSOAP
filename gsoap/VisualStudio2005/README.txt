
Visual Studio 2005 Solution files for soapcpp2 and wsdl2h.

If not already installed, install the Platform SDK (R2) for winsock2.h

To build soapcpp2, first install Bison and Flex (in the default dirs):
	http://gnuwin32.sourceforge.net/packages/bison.htm
	http://gnuwin32.sourceforge.net/packages/flex.htm
then add the FlexBison.rules:
	http://msdn2.microsoft.com/en-us/library/aa730877(VS.80).aspx
These custom-build rules are used to build the scanner and parser for soapcpp2.

To build wsdl2h, you first need to build soapcpp2.exe and install it in
Program Files or copy it to the wsdl2h source file directory. This is needed to
execute the custom-build step on wsdl.h to generate wsdlStub.h, wsdlH.h, and
wsdlC.cpp.

