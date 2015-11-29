/*
        json.h
        
        JSON C/C++ supporting functions

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2000-2015, Robert van Engelen, Genivia, Inc. All Rights Reserved.
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

#ifdef JSON_NAMESPACE
# include "jsonH.h"
#else
# include "soapH.h"
#endif

#ifdef JSON_NAMESPACE
namespace json {
#endif

/** Write a value in JSON format to a file, socket, or stream */
extern int json_write(struct soap *soap, const struct value *v);

/** Send a value in JSON format to a file, socket, or stream (lower level function, must use soap_begin_send/soap_end_send also) */
extern int json_send(struct soap *soap, const struct value *v);

#ifdef __cplusplus
extern int json_write(struct soap *soap, const struct value& v);
extern int json_send(struct soap *soap, const struct value& v);
extern std::ostream& operator<<(std::ostream&, const struct value&);
#endif

/** Read a value in JSON format from a file, socket, or stream */
extern int json_read(struct soap *soap, struct value *v);

/** Receive a value in JSON format from a file, socket, or stream (lower level function, must use soap_begin_recv/soap_end_recv also) */
extern int json_recv(struct soap *soap, struct value *v);

#ifdef __cplusplus
extern int json_read(struct soap *soap, struct value& v);
extern int json_recv(struct soap *soap, struct value& v);
extern std::istream& operator>>(std::istream&, struct value&);
#endif

/** Client-side JSON REST call to endpoint URL with optional in and out values (POST in/out, GET out , PUT in), returns SOAP_OK or HTTP code */
extern int json_call(struct soap *soap, const char *endpoint, const struct value *in, struct value *out);

#ifdef __cplusplus
extern int json_call(struct soap *soap, const char *endpoint, const struct value& in, struct value& out);
#endif

extern int json_send_string(struct soap *soap, const char *s);

#ifdef JSON_NAMESPACE
} // namespace json
#endif
