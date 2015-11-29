/*
        json.c[pp]

        JSON C/C++ API

	For more information please visit:

	http://www.genivia.com/doc/xml-rpc-json/html/

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

#include "json.h"

#ifdef JSON_NAMESPACE
# define SOAP_TYPE__boolean             SOAP_TYPE_json__boolean
# define SOAP_TYPE__i4                  SOAP_TYPE_json__i4
# define SOAP_TYPE__int                 SOAP_TYPE_json__int
# define SOAP_TYPE__double              SOAP_TYPE_json__double
# define SOAP_TYPE__dateTime_DOTiso8601 SOAP_TYPE_json__dateTime_DOTiso8601
# define SOAP_TYPE__string              SOAP_TYPE_json__string
# define SOAP_TYPE__array               SOAP_TYPE_json__array
# define SOAP_TYPE__struct              SOAP_TYPE_json__struct
# define SOAP_TYPE__base64              SOAP_TYPE_json__base64
#endif

#ifdef JSON_NAMESPACE
namespace json {
#endif

int json_write(struct soap *soap, const struct value *v)
{
  if (soap_begin_send(soap)
   || json_send(soap, v)
   || soap_end_send(soap))
    return soap->error;
  return SOAP_OK;
}

int json_send(struct soap *soap, const struct value *v)
{
  static const char *json_indent_string = ",\n                                                                                ";
  int i, n = 1;
  if (!v)
    return SOAP_OK;
  switch (v->__type)
  {
    case SOAP_TYPE__array: 
      if ((soap->mode & SOAP_XML_INDENT))
	n = 2 * (++soap->level % 40) + 2;
      if (soap_send_raw(soap, "["/*]*/, 1))
        return soap->error;
      for (i = 0; i < ((struct _array*)v->ref)->data.__size; i++)
      {
	if (soap_send_raw(soap, json_indent_string + (i == 0), n - (i == 0)))
	  return soap->error;
	if (json_send(soap, (((struct _array*)v->ref)->data.value) + i))
          return soap->error;
      }
      if ((soap->mode & SOAP_XML_INDENT))
      {
	if (i && soap_send_raw(soap, json_indent_string + 1, n - 3))
	  return soap->error;
	soap->level--;
      }
      return soap_send_raw(soap, /*[*/"]", 1);
    case SOAP_TYPE__boolean: 
      if (*(_boolean*)v->ref == 1)
        return soap_send_raw(soap, "true", 4);
      return soap_send_raw(soap, "false", 5);
    case SOAP_TYPE__double: 
      return soap_send(soap, soap_double2s(soap, (double)*(_double*)v->ref));
    case SOAP_TYPE__i4: 
      return soap_send(soap, soap_int2s(soap, (int)*(_i4*)v->ref));
    case SOAP_TYPE__int: 
      return soap_send(soap, soap_LONG642s(soap, (LONG64)*(_int*)v->ref));
    case SOAP_TYPE__string: 
    case SOAP_TYPE__dateTime_DOTiso8601: 
      return json_send_string(soap, (const char*)v->ref);
    case SOAP_TYPE__base64: 
      if (soap_send_raw(soap, "\"", 1)
       || soap_putbase64(soap, ((struct _base64*)v->ref)->__ptr, ((struct _base64*)v->ref)->__size))
	return soap->error;
      return soap_send_raw(soap, "\"", 1);
    case SOAP_TYPE__struct: 
      if ((soap->mode & SOAP_XML_INDENT))
	n = 2 * (++soap->level % 40) + 2;
      if (soap_send_raw(soap, "{"/*}*/, 1))
        return soap->error;
      for (i = 0; i < ((struct _struct*)v->ref)->__size; i++)
      {
	if (soap_send_raw(soap, json_indent_string + (i == 0), n - (i == 0)))
	  return soap->error;
	if (json_send_string(soap, (((struct _struct*)v->ref)->member + i)->name)
         || soap_send_raw(soap, ": ", 1 + (n > 1))
	 || json_send(soap, &(((struct _struct*)v->ref)->member + i)->value))
          return soap->error;
      }
      if ((soap->mode & SOAP_XML_INDENT))
      {
	if (i && soap_send_raw(soap, json_indent_string + 1, n - 3))
	  return soap->error;
	soap->level--;
      }
      return soap_send_raw(soap, /*{*/"}", 1);
    default:
      if (v->__any)
        return json_send_string(soap, v->__any);
      return soap_send_raw(soap, "null", 4);
  }
  return SOAP_OK;
}

int json_read(struct soap *soap, struct value *v)
{
  if (soap_begin_recv(soap)
   || json_recv(soap, v)
   || soap_end_recv(soap))
    return soap->error;
  return SOAP_OK;
}

int json_recv(struct soap *soap, struct value *v)
{
  soap_wchar c;
  if (!v)
    return SOAP_OK;
  v->__type = 0;
  v->ref = NULL;
  v->__any = NULL;
  v->soap = soap;
  while (((c = soap_getchar(soap)) > 0 && c <= 0x20) || c == 0xA0)
    continue;
  switch (c)
  {
    case EOF:
      return soap->error = SOAP_EOF;
    case '{'/*}*/:
    {
      struct value s;
#ifdef __cplusplus
      if (!(v->ref = (void*)soap_new__struct(soap)))
        return soap->error = SOAP_EOM;
#else
      if (!(v->ref = (void*)soap_malloc(soap, sizeof(struct _struct))))
        return soap->error = SOAP_EOM;
#endif
      soap_default__struct(soap, (struct _struct*)v->ref);
      v->__type = SOAP_TYPE__struct;
      while (((c = soap_getchar(soap)) > 0 && c <= 0x20) || c == 0xA0)
        continue;
      if (c == /*{*/'}')
        return SOAP_OK;
      soap_unget(soap, c);
      for (;;)
      {
        if (json_recv(soap, &s))
          return soap->error;
        if (s.__type != SOAP_TYPE__string)
          return soap_set_sender_error(soap, "name expected", (const char*)s.ref, SOAP_SYNTAX_ERROR);
        while (((c = soap_getchar(soap)) > 0 && c <= 0x20) || c == 0xA0)
          continue;
        if (c != ':')
          return soap_set_sender_error(soap, ": expected", (const char*)s.ref, SOAP_SYNTAX_ERROR);
#ifdef __cplusplus
	if (json_recv(soap, v->operator[]((const char*)s.ref)))
	  return soap->error;
#else
        if (json_recv(soap, value_at(v, (const char*)s.ref)))
          return soap->error;
#endif
        while (((c = soap_getchar(soap)) > 0 && c <= 0x20) || c == 0xA0)
          continue;
        if (c == /*{*/'}')
          break;
        if ((int)c == EOF)
          return soap->error = SOAP_EOF;
        if (c != ',')
          return soap_set_sender_error(soap, "} expected", NULL, SOAP_SYNTAX_ERROR);
      }
      return SOAP_OK;
    }
    case '['/*]*/:
    {
      int i;
#ifdef __cplusplus
      if (!(v->ref = (void*)soap_new__array(soap)))
        return soap->error = SOAP_EOM;
#else
      if (!(v->ref = (void*)soap_malloc(soap, sizeof(struct _array))))
        return soap->error = SOAP_EOM;
#endif
      soap_default__array(soap, (struct _array*)v->ref);
      v->__type = SOAP_TYPE__array;
      while (((c = soap_getchar(soap)) > 0 && c <= 0x20) || c == 0xA0)
        continue;
      if (c == /*[*/']')
        return SOAP_OK;
      soap_unget(soap, c);
      for (i = 0; ; i++)
      {
#ifdef __cplusplus
	if (json_recv(soap, v->operator[](i)))
	  return soap->error;
#else
	if (json_recv(soap, nth_value(v, i)))
	  return soap->error;
#endif
        while (((c = soap_getchar(soap)) > 0 && c <= 0x20) || c == 0xA0)
          continue;
        if (c == /*[*/']')
          break;
        if ((int)c == EOF)
          return soap->error = SOAP_EOF;
        if (c != ',')
          return soap_set_sender_error(soap, "] expected", NULL, SOAP_SYNTAX_ERROR);
      }
      return SOAP_OK;
    }
    case '"':
      soap->labidx = 0;
      for (;;)
      {
	char *s;
        const char *t = NULL;
        register size_t k;
        if (soap_append_lab(soap, NULL, 0))
          return soap->error = SOAP_EOM;
        s = soap->labbuf + soap->labidx;
        k = soap->lablen - soap->labidx;
        soap->labidx = soap->lablen;
        while (k--)
        {
	  if (t)
          {
	    *s++ = *t++;
            if (!*t)
              t = NULL;
          }
          else
          {
	    c = soap_getchar(soap);
            switch (c)
            {
	      case EOF:
                return soap->error = SOAP_EOF;
              case '"':
                *s = '\0';
                v->__type = SOAP_TYPE__string;
                if (!(v->ref = soap_strdup(soap, soap->labbuf)))
                  return soap->error = SOAP_EOM;
                return SOAP_OK;
              case '\\':
                c = soap_getchar(soap);
                switch (c)
                {
		  case EOF:
                    return soap->error = SOAP_EOF;
                  case 'b':
                    c = 8;
                    break;               
                  case 'f':
                    c = 12;
                    break;               
                  case 'n':
                    c = 10;
                    break;               
                  case 'r':
                    c = 13;
                    break;               
                  case 't':
                    c = 9;
                    break;               
                  case 'u':
                  {
		    char *h;
		    wchar_t wc[2];
		    int i;
                    /* hex to utf8 conversion */
                    h = soap->tmpbuf;
                    for (i = 0; i < 4; i++)
                    {
		      if ((c = soap_getchar(soap)) == EOF)
                        return soap->error = SOAP_EOF;
                      h[i] = c;
                    }
                    wc[0] = soap_strtol(h, NULL, 16);
                    wc[1] = 0;
                    t = soap_wchar2s(soap, wc);
                    c = *t++;
                    if (!*t)
                      t = NULL;
                  }
                }
                *s++ = c;
		break;
              default:
                if ((c & 0x80) && (soap->imode & SOAP_ENC_LATIN) && (soap->imode & SOAP_C_UTFSTRING)) /* ISO 8859-1 to utf8 */
                {
		  *s++ = (char)(0xC0 | ((c >> 6) & 0x1F));
                  soap->tmpbuf[0] = (0x80 | (c & 0x3F));
                  soap->tmpbuf[1] = '\0';
                  t = soap->tmpbuf;
                }
                else if ((c & 0x80) && !(soap->imode & SOAP_ENC_LATIN) && !(soap->imode & SOAP_C_UTFSTRING)) /* utf8 to ISO 8859-1 */
                {
		  soap_wchar c1 = soap_getchar(soap);
                  if (c1 == SOAP_EOF)
                    return soap->error = SOAP_EOF;
                  if (c < 0xE0 && (c & 0x1F) <= 0x03)
                    *s++ = ((c & 0x1F) << 6) | (c1 & 0x3F);
                  else
                    *s++ = '?';
                }
		else
                  *s++ = c;
            }
          }
        }
      }
    default: /* number, true, false, null */
    {
      char *s = soap->tmpbuf;
      do
      {
	*s++ = c;
        c = soap_getchar(soap);
      } while ((isalnum((int)c) || (int)c == '.' || (int)c == '+' || (int)c == '-') && s - soap->tmpbuf < (int)sizeof(soap->tmpbuf) - 1);
      *s = '\0';
      soap_unget(soap, c);
      if (soap->tmpbuf[0] == '-' || isdigit(soap->tmpbuf[0]))
      {
	LONG64 n = soap_strtoll(soap->tmpbuf, &s, 10);
	if (!*s)
	{
          v->__type = SOAP_TYPE__int;
          if (!(v->ref = soap_malloc(soap, sizeof(_int))))
            return soap->error = SOAP_EOM;
	  *(_int*)v->ref = n;
	}
	else
	{
	  double x;
	  soap_s2double(soap, soap->tmpbuf, &x);
          v->__type = SOAP_TYPE__double;
          if (!(v->ref = soap_malloc(soap, sizeof(_double))))
            return soap->error = SOAP_EOM;
	  *(_double*)v->ref = x;
        }
      }
      else if (!strcmp(soap->tmpbuf, "true"))
      {
        v->__type = SOAP_TYPE__boolean;
        if (!(v->ref = soap_malloc(soap, sizeof(_boolean))))
          return soap->error = SOAP_EOM;
	*(char*)v->ref = 1;
      }
      else if (!strcmp(soap->tmpbuf, "false"))
      {
        v->__type = SOAP_TYPE__boolean;
        if (!(v->ref = soap_malloc(soap, sizeof(_boolean))))
          return soap->error = SOAP_EOM;
	*(char*)v->ref = 0;
      }
      return SOAP_OK;
    }
  }
}

int json_call(struct soap *soap, const char *endpoint, const struct value *in, struct value *out)
{
  soap->http_content = "application/json; charset=utf-8";
  if (soap_begin_count(soap)
   || ((soap->mode & SOAP_IO_LENGTH) && json_send(soap, in))
   || soap_end_count(soap)
   || soap_connect_command(soap, in && out ? SOAP_POST_FILE : out ? SOAP_GET : in ? SOAP_PUT : SOAP_DEL, endpoint, NULL)
   || json_send(soap, in)
   || soap_end_send(soap)
   || soap_begin_recv(soap)
   || json_recv(soap, out)
   || soap_end_recv(soap))
    ;
  return soap_closesock(soap);
}

int json_send_string(struct soap *soap, const char *s)
{
  const char *t = s;
  int c;
  char buf[8];
  if (soap_send_raw(soap, "\"", 1))
    return soap->error;
  while ((c = *s++))
  {
    if (c < 0x20 && c > 0)
    {
      switch (c)
      {
        case '\b':
          c = 'b';
          break;
        case '\f':
          c = 'f';
          break;
        case '\n':
          c = 'n';
          break;
        case '\r':
          c = 'r';
          break;
        case '\t':
          c = 't';
          break;
      }
      if (c > 0x20)
      {
        buf[0] = '\\';
        buf[1]  = c;
        if (soap_send_raw(soap, t, s - t - 1) || soap_send_raw(soap, buf, 2))
          return soap->error;
        t = s;
      }
      else
      {
        (SOAP_SNPRINTF(buf, sizeof(buf), 7), "\\u%4x", c);
        if (soap_send_raw(soap, t, s - t - 1) || soap_send_raw(soap, buf, 6))
          return soap->error;
        t = s;
      }
    }
    else if (c == '"' || c == '\\')
    {
      buf[0] = '\\';
      buf[1]  = c;
      if (soap_send_raw(soap, t, s - t - 1) || soap_send_raw(soap, buf, 2))
        return soap->error;
      t = s;
    }
    else if ((c & 0x80))
    {
      if ((soap->omode & SOAP_ENC_LATIN) && (soap->omode & SOAP_C_UTFSTRING)) /* UTF-8 to ISO 8859-1 */
      {
        if (c < 0xE0 && (c & 0x1F) <= 0x03)
          buf[0] = ((c & 0x1F) << 6) | (*s++ & 0x3F);
        else
          buf[0] = '?';
        if (soap_send_raw(soap, t, s - t - 1) || soap_send_raw(soap, buf, 1))
          return soap->error;
        t = s;
      }
      else if (!(soap->omode & SOAP_ENC_LATIN) && !(soap->omode & SOAP_C_UTFSTRING)) /* ISO 8859-1 to UTF-8 */
      {
        buf[0] = (char)(0xC0 | ((c >> 6) & 0x1F));
        buf[1] = (char)(0x80 | (c & 0x3F));
        if (soap_send_raw(soap, t, s - t - 1) || soap_send_raw(soap, buf, 2))
          return soap->error;
        t = s;
      }
    }
  }
  if (soap_send_raw(soap, t, s - t - 1) || soap_send_raw(soap, "\"", 1))
    return soap->error;
  return SOAP_OK;
}

#ifdef __cplusplus

int json_write(struct soap *soap, const struct value& v)
{
  return json_write(soap, &v);
}

int json_send(struct soap *soap, const struct value& v)
{
  return json_send(soap, &v);
}

int json_read(struct soap *soap, struct value& v)
{
  return json_read(soap, &v);
}

int json_recv(struct soap *soap, struct value& v)
{
  return json_recv(soap, &v);
}

int json_call(struct soap *soap, const char *endpoint, const struct value& in, struct value& out)
{
  return json_call(soap, endpoint, &in, &out);
}

std::ostream& operator<<(std::ostream& o, const struct value& v)
{
  if (v.soap)
  {
    std::ostream *os = v.soap->os;
    v.soap->os = &o;
    json_write(v.soap, v);
    v.soap->os = os;
  }
  else
  {
    soap *ctx = soap_new();
    ctx->os = &o;
    json_write(ctx, v);
    soap_destroy(ctx);
    soap_end(ctx);
    soap_free(ctx);
  }
  return o;
}

std::istream& operator>>(std::istream& i, struct value& v)
{
  if (!v.soap)
    v.soap = soap_new();
  std::istream *is = v.soap->is;
  v.soap->is = &i;
  if (json_read(v.soap, v))
  {
    soap_sprint_fault(v.soap, v.soap->msgbuf, sizeof(v.soap->msgbuf));
    v["$error"] = v.soap->msgbuf;
    v["$code"] = v.soap->error;
  }
  v.soap->is = is;
  return i;
}

#endif

#ifdef JSON_NAMESPACE
} // namespace json
#endif
