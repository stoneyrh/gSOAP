/*
	xml-rpc-io.cpp

	XML-RPC io stream operations on XML-RPC values

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2001-2008, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL or Genivia's license for commercial use.
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
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapH.h"
#include "xml-rpc-io.h"

std::ostream& operator<<(std::ostream& o, const struct value& v)
{ switch (v.__type)
  { case SOAP_TYPE__array: 
      o << "{array" << std::endl;
      for (_array::iterator i = ((struct _array)v).begin(); i != ((struct _array)v).end(); ++i)
        o << "[" << i.index() << "]=" << (*i) << std::endl;
      o << "}";
      break;
    case SOAP_TYPE__base64: 
      o << "{base64 " << ((struct _base64)v).size() << " bytes}";
      break;
    case SOAP_TYPE__boolean: 
      if (v.is_true())
        o << "TRUE";
      else
	o << "FALSE";
      break;
    case SOAP_TYPE__dateTime_DOTiso8601: 
      o << (const char*)v;
      break;
    case SOAP_TYPE__double: 
      o << (double)v;
      break;
    case SOAP_TYPE__i4: 
    case SOAP_TYPE__int: 
      o << (int)v;
      break;
    case SOAP_TYPE__string: 
      o << (const char*)v;
      break;
    case SOAP_TYPE__struct: 
      o << "{struct" << std::endl;
      for (_struct::iterator i = ((struct _struct)v).begin(); i != ((struct _struct)v).end(); ++i)
        o << "[" << i.index() << "]=" << (*i) << std::endl;
      o << "}";
      break;
    default:
      if (v.__any)
        o << v.__any;
      else
        o << "{?}";
  }
  return o;
}

std::istream& operator>>(std::istream& i, struct value& v)
{ if (!v.soap)
    v.soap = soap_new();
  std::istream *is = v.soap->is;
  v.soap->is = &i;
  if (soap_begin_recv(v.soap)
   || soap_get_value(v.soap, &v, "value", NULL)
   || soap_end_recv(v.soap))
  { /* handle error? Note: v.soap->error is set */
  }
  v.soap->is = is;
  return i;
}

