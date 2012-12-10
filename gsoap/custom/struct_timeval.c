/*
	struct_timeval.c

	Custom serializer for struct timeval

	Compile this file and link it with your code.

	Changes:
	Feb 8, 2008: fixed local time to internal GMT conversion

gSOAP XML Web services tools
Copyright (C) 2000-2008, Robert van Engelen, Genivia Inc., All Rights Reserved.
This part of the software is released under ONE of the following licenses:
GPL, the gSOAP public license, OR Genivia's license for commercial use.
--------------------------------------------------------------------------------
gSOAP public license.

The contents of this file are subject to the gSOAP Public License Version 1.3
(the "License"); you may not use this file except in compliance with the
License. You may obtain a copy of the License at
http://www.cs.fsu.edu/~engelen/soaplicense.html
Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the License.

The Initial Developer of the Original Code is Robert A. van Engelen.
Copyright (C) 2000-2008, Robert van Engelen, Genivia, Inc., All Rights Reserved.
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
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

/* soapH.h generated by soapcpp2 from .h file containing #import "struct_timeval.h": */
#include "soapH.h"

void soap_default_xsd__dateTime(struct soap *soap, struct timeval *a)
{ memset(a, 0, sizeof(struct timeval));
}

void soap_serialize_xsd__dateTime(struct soap *soap, struct timeval const *a)
{ }

const char *soap_xsd__dateTime2s(struct soap *soap, const struct timeval a)
{ char *s = soap->tmpbuf;
  size_t n;
  soap_dateTime2s(soap, a.tv_sec); /* assuming result is in tmpbuf! */
  n = strlen(s);
  if (s[n-1] == 'Z')
    n--;
  sprintf(s + n, ".%.6dZ", a.tv_usec);
  return s;
}

int soap_out_xsd__dateTime(struct soap *soap, const char *tag, int id, const struct timeval *a, const char *type)
{ if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, a, SOAP_TYPE_xsd__dateTime), type)
   || soap_string_out(soap, soap_xsd__dateTime2s(soap, *a), 0))
    return soap->error;
  return soap_element_end_out(soap, tag);
}

int soap_s2xsd__dateTime(struct soap *soap, const char *s, struct timeval *a)
{ memset((void*)a, 0, sizeof(struct timeval));
  if (s)
  { char rest[32];
    const char *t;
    struct tm tm;
    memset((void*)&tm, 0, sizeof(struct tm));
    rest[sizeof(rest)-1] = '\0';
    if (strchr(s, '-'))
      t = "%d-%d-%dT%d:%d:%d%31s";
    else if (strchr(s, ':'))
      t = "%4d%2d%2dT%d:%d:%d%31s";
    else /* parse non-XSD-standard alternative ISO 8601 format */
      t = "%4d%2d%2dT%2d%2d%2d%31s";
    if (sscanf(s, t, &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec, rest) < 6)
      return soap->error = SOAP_TYPE;
    tm.tm_wday = -1;
    tm.tm_yday = -1;
    if (tm.tm_year == 1)
      tm.tm_year = 70;
    else
      tm.tm_year -= 1900;
    tm.tm_mon--;
    tm.tm_isdst = 0;
    if (*rest)
    { if (*rest == '.')
      { double f = 0;
        for (s = rest + 1; *s; s++)
          if (*s < '0' || *s > '9')
            break;
	sscanf(rest, "%lg", &f);
        a->tv_usec = (int)(f*1000000.0);
      }
      else
      { s = rest;
        a->tv_usec = 0;
      }
    }
    if (*s)
    { if (*s == '+' || *s == '-')
      { int h = 0, m = 0;
        if (s[3] == ':')
        { /* +hh:mm */
	  sscanf(s, "%d:%d", &h, &m);
          if (h < 0)
            m = -m;
        }
        else /* +hhmm */
        { m = (int)atol(s);
          h = m / 100;
          m = m % 100;
        }
        tm.tm_hour -= h;
        tm.tm_min -= m;
	/* put hour and min in range */
        tm.tm_hour += tm.tm_min / 60;
        tm.tm_min %= 60;
        if (tm.tm_min < 0)
        { tm.tm_min += 60;
	  tm.tm_hour--;
        }
        tm.tm_mday += tm.tm_hour / 24;
        tm.tm_hour %= 24;
        if (tm.tm_hour < 0)
        { tm.tm_hour += 24;
          tm.tm_mday--;
        }
	/* note: day of the month may be out of range, timegm() handles it */
      }
      a->tv_sec = soap_timegm(&tm);
    }
    else
      a->tv_sec = mktime(&tm);
  }
  return soap->error;
}

struct timeval *soap_in_xsd__dateTime(struct soap *soap, const char *tag, struct timeval *a, const char *type)
{ if (soap_element_begin_in(soap, tag, 0, NULL))
    return NULL;
  if (*soap->type
   && soap_match_tag(soap, soap->type, type)
   && soap_match_tag(soap, soap->type, ":dateTime"))
  { soap->error = SOAP_TYPE;
    soap_revert(soap);
    return NULL;
  }
  a = (struct timeval*)soap_id_enter(soap, soap->id, a, SOAP_TYPE_xsd__dateTime, sizeof(struct timeval), 0, NULL, NULL, NULL);
  if (*soap->href)
    a = (struct timeval*)soap_id_forward(soap, soap->href, a, 0, SOAP_TYPE_xsd__dateTime, 0, sizeof(struct timeval), 0, NULL);
  else if (a)
  { if (soap_s2xsd__dateTime(soap, soap_value(soap), a))
      return NULL;
  }
  if (soap->body && soap_element_end_in(soap, tag))
    return NULL;
  return a;
}
