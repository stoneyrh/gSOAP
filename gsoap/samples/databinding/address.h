/* ./address.h
   Generated by wsdl2h 2.8.36 from ./address.xsd and ./addresstypemap.dat
   2016-09-21 20:50:53 GMT

   DO NOT INCLUDE THIS FILE DIRECTLY INTO YOUR PROJECT BUILDS
   USE THE soapcpp2-GENERATED SOURCE CODE FILES FOR YOUR PROJECT BUILDS

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

/** @page page_notes Notes

@note HINTS:
 - Run soapcpp2 on ./address.h to generate the SOAP/XML processing logic.
   Use soapcpp2 -I to specify paths for #import
   To build with STL, 'stl.h' is imported from 'import' dir in package.
   Use soapcpp2 -j to generate improved proxy and server classes.
   Use soapcpp2 -r to generate a report.
 - Use wsdl2h -c and -s to generate pure C code or C++ code without STL.
 - Use 'typemap.dat' to control namespace bindings and type mappings.
   It is strongly recommended to customize the names of the namespace prefixes
   generated by wsdl2h. To do so, modify the prefix bindings in the Namespaces
   section below and add the modified lines to 'typemap.dat' to rerun wsdl2h.
 - Run Doxygen (www.doxygen.org) on this file to generate documentation.
 - Use wsdl2h -R to generate REST operations.
 - Use wsdl2h -nname to use name as the base namespace prefix instead of 'ns'.
 - Use wsdl2h -Nname for service prefix and produce multiple service bindings
 - Use wsdl2h -d to enable DOM support for xsd:anyType.
 - Use wsdl2h -g to auto-generate readers and writers for root elements.
 - Use wsdl2h -b to auto-generate bi-directional operations (duplex ops).
 - Use wsdl2h -U to map XML names to C++ Unicode identifiers instead of _xNNNN.
 - Use wsdl2h -u to disable the generation of unions.
 - Struct/class members serialized as XML attributes are annotated with a '@'.
 - Struct/class members that have a special role are annotated with a '$'.

@warning
   DO NOT INCLUDE THIS ANNOTATED FILE DIRECTLY IN YOUR PROJECT SOURCE CODE.
   USE THE FILES GENERATED BY soapcpp2 FOR YOUR PROJECT'S SOURCE CODE:
   THE soapStub.h FILE CONTAINS THIS CONTENT WITHOUT ANNOTATIONS.

@copyright LICENSE:
@verbatim
--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
The wsdl2h tool and its generated software are released under the GPL.
This software is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org

This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial-use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
@endverbatim

*/


//gsoapopt c++,w

/******************************************************************************\
 *                                                                            *
 * Definitions                                                                *
 *   urn:address-book-example                                                 *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * $CONTAINER                                                                 *
 *   std::vector                                                              *
 *                                                                            *
\******************************************************************************/

template <class T> class std::vector;

/******************************************************************************\
 *                                                                            *
 * Import                                                                     *
 *                                                                            *
\******************************************************************************/

#import "stl.h"	// enable STL containers when used (option -s removes STL dependency)

/******************************************************************************\
 *                                                                            *
 * Schema Namespaces                                                          *
 *                                                                            *
\******************************************************************************/


/* NOTE:

It is strongly recommended to customize the names of the namespace prefixes
generated by wsdl2h. To do so, modify the prefix bindings below and add the
modified lines to typemap.dat to rerun wsdl2h:

a = "urn:address-book-example"

*/

/// <PRE><BLOCKQUOTE>
///   An example address book schema
/// </BLOCKQUOTE></PRE>
#define SOAP_NAMESPACE_OF_a	"urn:address-book-example"
//gsoap a     schema namespace:	urn:address-book-example
//gsoap a     schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Forward Declarations                                                       *
 *                                                                            *
\******************************************************************************/


//  Forward declaration of class a__address.
class a__address;

//  Forward declaration of class _a__address_book.
class _a__address_book;


/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   urn:address-book-example                                                 *
 *                                                                            *
\******************************************************************************/

/// @brief "urn:address-book-example":ISO-country is a simpleType restriction of XSD type xs:string.
///
/// <PRE><BLOCKQUOTE>
///   ISO country codes (limited to just a few for this example)
/// </BLOCKQUOTE></PRE>
/// @note The enum values are prefixed with "a__ISO_country__" to prevent name clashes: use wsdl2h option -e to omit this prefix or use option -c++11 for scoped enumerations
enum a__ISO_country
{
	a__ISO_country__be,	///< xs:string value="be"
	a__ISO_country__ca,	///< xs:string value="ca"
	a__ISO_country__de,	///< xs:string value="de"
	a__ISO_country__en,	///< xs:string value="en"
	a__ISO_country__gb,	///< xs:string value="gb"
	a__ISO_country__it,	///< xs:string value="it"
	a__ISO_country__nl,	///< xs:string value="nl"
	a__ISO_country__no,	///< xs:string value="no"
	a__ISO_country__ru,	///< xs:string value="ru"
	a__ISO_country__se,	///< xs:string value="se"
	a__ISO_country__us,	///< xs:string value="us"
};


/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   urn:address-book-example                                                 *
 *                                                                            *
\******************************************************************************/

/// @brief "urn:address-book-example":address is a complexType.
///
/// <PRE><BLOCKQUOTE>
///   An address information item
/// </BLOCKQUOTE></PRE>
/// class a__address operations:
/// - a__address* soap_new_a__address(soap*) allocate and default initialize
/// - a__address* soap_new_a__address(soap*, int num) allocate array and default initialize values
/// - a__address* soap_new_req_a__address(soap*, ...) allocate, set required members
/// - a__address* soap_new_set_a__address(soap*, ...) allocate, set all public members
/// - a__address::soap_default(soap*) default initialize members
/// - int soap_read_a__address(soap*, a__address*) deserialize from a stream
/// - int soap_write_a__address(soap*, a__address*) serialize to a stream
/// - a__address* a__address::soap_dup(soap*) returns deep copy of a__address, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - a__address::soap_del() deep deletes a__address data members, use only after a__address::soap_dup(NULL) (use soapcpp2 -Ed)
class a__address
{ public:
/// Element "name" of XSD type xs:string.
    std::string                          name                           1;	///< Required element.
/// Element "street" of XSD type xs:string.
    std::string                          street                         1;	///< Required element.
/// Element "city" of XSD type xs:string.
    std::string                          city                           1;	///< Required element.
/// Element "zip" of XSD type xs:string.
    std::string                          zip                            1;	///< Required element.
/// Element "country" of XSD type "":ISO-country.
    enum a__ISO_country                  country                        0 = a__ISO_country__us;	///< Default element value="us".
/// Element "phone" of XSD type xs:string.
    std::string*                         phone                          0;	///< Optional element.
/// Element "mobile" of XSD type xs:string.
    std::string*                         mobile                         0;	///< Optional element.
/// Element "dob" of XSD type xs:dateTime.
    time_t*                              dob                            0;	///< Optional element.
/// Attribute "ID" of XSD type xs:int.
   @int                                  ID                             1;	///< Required attribute.
/// A handle to the soap struct context that manages this instance when instantiated by a context or NULL otherwise (automatically set).
    struct soap                         *soap                          ;
};

/// @brief Top-level root element "urn:address-book-example":address-book
/// <PRE><BLOCKQUOTE>
///   The root element of the address book schema
/// </BLOCKQUOTE></PRE>
/// @brief "urn:address-book-example":address-book is a complexType.
///
/// class _a__address_book operations:
/// - _a__address_book* soap_new__a__address_book(soap*) allocate and default initialize
/// - _a__address_book* soap_new__a__address_book(soap*, int num) allocate array and default initialize values
/// - _a__address_book* soap_new_req__a__address_book(soap*, ...) allocate, set required members
/// - _a__address_book* soap_new_set__a__address_book(soap*, ...) allocate, set all public members
/// - _a__address_book::soap_default(soap*) default initialize members
/// - int soap_read__a__address_book(soap*, _a__address_book*) deserialize from a stream
/// - int soap_write__a__address_book(soap*, _a__address_book*) serialize to a stream
/// - _a__address_book* _a__address_book::soap_dup(soap*) returns deep copy of _a__address_book, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - _a__address_book::soap_del() deep deletes _a__address_book data members, use only after _a__address_book::soap_dup(NULL) (use soapcpp2 -Ed)
class _a__address_book
{ public:
/// Vector of a__address* of length 0..unbounded.
    std::vector<a__address*            > address                        0;
/// A handle to the soap struct context that manages this instance when instantiated by a context or NULL otherwise (automatically set).
    struct soap                         *soap                          ;
};


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   urn:address-book-example                                                 *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   urn:address-book-example                                                 *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * XML Data Binding                                                           *
 *                                                                            *
\******************************************************************************/


/**

@page page_XMLDataBinding XML Data Binding

SOAP/XML services use data bindings contractually bound by WSDL and auto-
generated by wsdl2h and soapcpp2 (see Service Bindings). Plain data bindings
are adopted from XML schemas as part of the WSDL types section or when running
wsdl2h on a set of schemas to produce non-SOAP-based XML data bindings.

The following readers and writers are C/C++ data type (de)serializers auto-
generated by wsdl2h and soapcpp2. Run soapcpp2 on this file to generate the
(de)serialization code, which is stored in soapC.c[pp]. Include "soapH.h" in
your code to import these data type and function declarations. Only use the
soapcpp2-generated files in your project build. Do not include the wsdl2h-
generated .h file in your code.

Data can be read and deserialized from:
  - an int file descriptor, using soap->recvfd = fd
  - a socket, using soap->socket = (int)...
  - a C++ stream (istream, stringstream), using soap->is = (istream*)...
  - a C string, using soap->is = (const char*)...
  - any input, using the soap->frecv() callback

Data can be serialized and written to:
  - an int file descriptor, using soap->sendfd = (int)...
  - a socket, using soap->socket = (int)...
  - a C++ stream (ostream, stringstream), using soap->os = (ostream*)...
  - a C string, using soap->os = (const char**)...
  - any output, using the soap->fsend() callback

The following options are available for (de)serialization control:
  - soap->encodingStyle = NULL; to remove SOAP 1.1/1.2 encodingStyle
  - soap_mode(soap, SOAP_XML_TREE); XML without id-ref (no cycles!)
  - soap_mode(soap, SOAP_XML_GRAPH); XML with id-ref (including cycles)
  - soap_set_namespaces(soap, struct Namespace *nsmap); to set xmlns bindings


@section a Top-level root elements of schema "urn:address-book-example"

  - <a:address-book> @ref _a__address_book
    @code
    // Reader (returns SOAP_OK on success):
    soap_read__a__address_book(struct soap*, _a__address_book*);
    // Writer (returns SOAP_OK on success):
    soap_write__a__address_book(struct soap*, _a__address_book*);
    @endcode

*/

/* End of ./address.h */
