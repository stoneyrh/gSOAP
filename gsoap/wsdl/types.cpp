/*
        types.cpp

        Generate gSOAP types from XML schemas (e.g. embedded in WSDL).

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2000-2015, Robert van Engelen, Genivia Inc. All Rights Reserved.
This software is released under one of the following licenses:
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

#include "types.h"

static char *getline(char *s, size_t n, FILE *fd);
static const char *nonblank(const char *s);
static const char *fill(char *t, int n, const char *s, int e);
static const char *utf8(char **t, const char *s, bool start);
static const char *cstring(const char *s);
static const char *xstring(const char *s);
static bool is_float(const char *s);
static bool is_integer(const char *s);
static LONG64 to_integer(const char *s);
static void documentation(const char *text);
static void operations(const char *t);

static int comment_nest = 0; /* keep track of block comments to avoid nesting */

////////////////////////////////////////////////////////////////////////////////
//
//      Keywords and reserved words
//
////////////////////////////////////////////////////////////////////////////////

static const char *keywords[] =
{
  "alignas",
  "alignof"
  "and",
  "and_eq",
  "asm",
  "auto",
  "bitand",
  "bitor",
  "bool",
  "break",
  "case",
  "catch",
  "char",
  "char16_t",
  "char32_t",
  "class",
  "compl",
  "const",
  "constexpr",
  "const_cast",
  "continue",
  "decltype",
  "default",
  "delete",
  "do",
  "double",
  "dynamic_cast",
  "else",       
  "enum",
  "errno",
  "explicit",
  "export",
  "extern",
  "false",
  "FILE",
  "final",
  "float",
  "for",
  "friend",
  "goto",
  "if",
  "INFINITY",
  "inline",
  "int",
  "interface",
  "long",
  "LONG64",
  "max",
  "min",
  "mustUnderstand",
  "mutable",
  "namespace",
  "new",
  "not",
  "not_eq",
  "NULL",
  "nullptr",
  "nullptr_t",
  "operator",
  "or",
  "or_eq",
  "override",
  "private",
  "protected",
  "public",
  "_QName",
  "register",
  "reinterpret_cast",
  "restrict",
  "return",
  "short",
  "signed",
  "size_t",
  "sizeof",
  "soap",
  "static",
  "static_assert",
  "static_cast",
  "struct",
  "switch",
  "template",
  "this",
  "thread_local",
  "throw",
  "time_t",
  "true",
  "try",
  "typedef",
  "typeid",
  "typeof",
  "typename",
  "ULONG64",
  "union",
  "unsigned",
  "using",
  "virtual",
  "void",
  "volatile",
  "wchar_t",
  "while",
  "XML",
  "_XML",
  "xor",
  "xor_eq",
};

////////////////////////////////////////////////////////////////////////////////
//
//      Types methods
//
////////////////////////////////////////////////////////////////////////////////

Types::Types()
{
  init();
}

int Types::read(const char *file)
{
  FILE *fd;
  char buf[4096], xsd[4096], def[4096], use[4096], ptr[4096], uri[4096];
  const char *s;
  short copy = 0;
  MapOfStringToString eqvtypemap;
  soap_strcpy(buf, sizeof(buf), file);
  fd = fopen(buf, "r");
  if (!fd && import_path)
  {
    (SOAP_SNPRINTF(buf, sizeof(buf), strlen(import_path) + strlen(file) + 1), "%s/%s", import_path, file);
    fd = fopen(buf, "r");
  }
  if (!fd)
  {
    fprintf(stderr, "Cannot open file \"%s\"\n", file);
    return SOAP_EOF;
  }
  fprintf(stderr, "Reading type definitions from type map \"%s\"\n", buf);
  while (getline(buf, sizeof(buf), fd))
  {
    s = buf;
    if (copy)
    {
      if (*s == ']')
        copy = 0;
      else
        fprintf(stream, "%s\n", buf);
    }
    else if (*s == '[')
    {
      copy = 1;
    }
    else if (*s == '<')
    {
      s = fill(uri, sizeof(uri), s+1, -1);
      infile[infiles++] = estrdup(uri);
      if (infiles >= MAXINFILES)
      {
        fprintf(stderr, "wsdl2h: too many files\n");
        exit(1);
      }
    }
    else if (*s == '>')
    {
      s = fill(uri, sizeof(uri), s+1, -1);
      if (!outfile)
      {
        outfile = estrdup(uri);
        stream = fopen(outfile, "w");
        if (!stream)
        {
          fprintf(stderr, "Cannot write to %s\n", outfile);
          exit(1);
        }
        if (cppnamespace)
          fprintf(stream, "namespace %s {\n", cppnamespace);
        fprintf(stderr, "Saving %s\n\n", outfile);
      }
    }
    else if (*s && *s != '#')
    {
      s = fill(xsd, sizeof(xsd), s, '=');
      if (s && *s == '=')
      {
        s = fill(use, sizeof(use), s+1, '|');
        if (*xsd && *use)
        {
          s = estrdup(xsd);
          eqvtypemap[s] = estrdup(use);
          deftypemap[s] = "";
          if (usetypemap.find(use) != usetypemap.end())
            usetypemap[s] = usetypemap[use];
          else
            usetypemap[s] = estrdup(use);
        }
      }
      else if (strstr(xsd, "__"))
      {
        s = fill(def, sizeof(def), s, '|');
        s = fill(use, sizeof(use), s, '|');
        s = fill(ptr, sizeof(ptr), s, '|');
        if (*xsd)
        {
          s = estrdup(xsd);
          if (*def == '$')
          {
            const char *t = modtypemap[s];
            if (t)
            {
              size_t l = strlen(t) + strlen(def);
              char *r = (char*)emalloc(l + 1);
              (SOAP_SNPRINTF(r, l + 1, l), "%s%s", t, def);
              free((void*)modtypemap[s]);
              modtypemap[s] = r;
            }
            else
              modtypemap[s] = estrdup(def);
          }
          else
          {
            if (*def)
            {
              if (strcmp(def, "..."))
                deftypemap[s] = estrdup(def);
            }
            else
              deftypemap[s] = "";
            if (*use)
              usetypemap[s] = estrdupf(use);
            else
              usetypemap[s] = estrdupf(xsd);
            if (*ptr)
              ptrtypemap[s] = estrdupf(ptr);
          }
        }
      }
      else if (*xsd == '$')
      {
        fill(use, sizeof(use), s, 0);
        if (*use)
        {
          s = estrdup(xsd);
          usetypemap[s] = estrdup(use);
        }
      }
      else if (*xsd)
      {
        s = fill(uri, sizeof(uri), s, 0);
        if (uri[0] == '"')
        {
          uri[strlen(uri) - 1] = '\0';
          nsprefix(xsd, estrdup(uri + 1));
        }
        else if (uri[0] == '<')
        {
          uri[strlen(uri) - 1] = '\0';
          char *s = estrdup(uri + 1);
          nsprefix(xsd, s);
          exturis.insert(s);
        }
        else
          nsprefix(xsd, estrdup(uri));
      }
    }
  }
  for (MapOfStringToString::const_iterator i = eqvtypemap.begin(); i != eqvtypemap.end(); ++i)
  {
    const char *s = (*i).first, *t = (*i).second;
    if (usetypemap.find(t) != usetypemap.end())
      t = usetypemap[t];
    deftypemap[s] = "";
    usetypemap[s] = t;
    if (ptrtypemap.find((*i).second) != ptrtypemap.end())
      ptrtypemap[s] = ptrtypemap[(*i).second];
    else
    {
      MapOfStringToString::iterator j = ptrtypemap.find(s);
      if (j != ptrtypemap.end())
        ptrtypemap.erase(j);
    }
    for (MapOfStringToString::iterator j = usetypemap.begin(); j != usetypemap.end(); ++j)
      if (!strcmp((*j).second, s))
        (*j).second = t;
    for (MapOfStringToString::iterator k = ptrtypemap.begin(); k != ptrtypemap.end(); ++k)
      if (!strcmp((*k).second, s))
        (*k).second = t;
  }
  fclose(fd);
  return SOAP_OK;
}

void Types::init()
{
  snum = 1;
  unum = 1;
  gnum = 1;
  with_union = false;
  fake_union = false;
  knames.insert(keywords, keywords + sizeof(keywords)/sizeof(char*));
  if (cflag)
  {
    deftypemap["xsd__ur_type"] = "";
    if (dflag)
    {
      usetypemap["xsd__ur_type"] = "xsd__anyType";
    }
    else
    {
      usetypemap["xsd__ur_type"] = "_XML";
      ptrtypemap["xsd__ur_type"] = "_XML";
    }
  }
  else
  {
    deftypemap["xsd__ur_type"] = "class xsd__ur_type { _XML __item; struct soap *soap; };";
    usetypemap["xsd__ur_type"] = "xsd__ur_type";
  }
  if (cflag)
  {
    deftypemap["xsd__anyType"] = "";
    if (dflag)
    {
      usetypemap["xsd__anyType"] = "xsd__anyType";
    }
    else
    {
      usetypemap["xsd__anyType"] = "_XML";
      ptrtypemap["xsd__anyType"] = "_XML";
    }
  }
  else
  {
    if (dflag)
      deftypemap["xsd__anyType"] = "";
    else
      deftypemap["xsd__anyType"] = "class xsd__anyType { _XML __item; struct soap *soap; };";
    usetypemap["xsd__anyType"] = "xsd__anyType";
  }
  deftypemap["xsd__any"] = "";
  if (dflag)
  {
    usetypemap["xsd__any"] = "xsd__anyType";
  }
  else
  {
    usetypemap["xsd__any"] = "_XML";
    ptrtypemap["xsd__any"] = "_XML";
  }
  deftypemap["xsd__anyAttribute"] = "";
  if (dflag)
  {
    usetypemap["xsd__anyAttribute"] = "xsd__anyAttribute";
  }
  else
  {
    usetypemap["xsd__anyAttribute"] = "_XML";
    ptrtypemap["xsd__anyAttribute"] = "_XML";
  }
  if (cflag)
  {
    deftypemap["xsd__base64Binary"] = "struct xsd__base64Binary\n{\tunsigned char *__ptr;\n\tint __size;\n\tchar *id, *type, *options; // NOTE: non-NULL for DIME/MIME/MTOM XOP attachments only\n};";
    usetypemap["xsd__base64Binary"] = "struct xsd__base64Binary";
    ptrtypemap["xsd__base64Binary"] = "struct xsd__base64Binary";
  }
  else
  {
    deftypemap["xsd__base64Binary"] = "class xsd__base64Binary\n{\tunsigned char *__ptr;\n\tint __size;\n\tchar *id, *type, *options; // NOTE: non-NULL for DIME/MIME/MTOM XOP attachments only\n\tstruct soap *soap;\n};";
    usetypemap["xsd__base64Binary"] = "xsd__base64Binary";
  }
  if (cflag)
  {
    if (eflag)
      deftypemap["xsd__boolean"] = "enum xsd__boolean { false_, true_ };";
    else
      deftypemap["xsd__boolean"] = "enum xsd__boolean { xsd__boolean__false_, xsd__boolean__true_ };";
    usetypemap["xsd__boolean"] = "enum xsd__boolean";
  }
  else
  {
    deftypemap["xsd__boolean"] = "";
    usetypemap["xsd__boolean"] = "bool";
  }
  deftypemap["xsd__byte"] = "typedef char xsd__byte;";
  usetypemap["xsd__byte"] = "xsd__byte";
  deftypemap["xsd__dateTime"] = "";
  usetypemap["xsd__dateTime"] = "time_t";
  deftypemap["xsd__double"] = "";
  usetypemap["xsd__double"] = "double";
  deftypemap["xsd__float"] = "";
  usetypemap["xsd__float"] = "float";
  if (cflag)
  {
    deftypemap["xsd__hexBinary"] = "struct xsd__hexBinary { unsigned char *__ptr; int __size; };";
    usetypemap["xsd__hexBinary"] = "struct xsd__hexBinary";
    ptrtypemap["xsd__hexBinary"] = "struct xsd__hexBinary";
  }
  else
  {
    deftypemap["xsd__hexBinary"] = "class xsd__hexBinary { unsigned char *__ptr; int __size; };";
    usetypemap["xsd__hexBinary"] = "xsd__hexBinary";
  }
  deftypemap["xsd__int"] = "";
  usetypemap["xsd__int"] = "int";
  deftypemap["xsd__long"] = "";
  usetypemap["xsd__long"] = "LONG64";
  deftypemap["xsd__short"] = "";
  usetypemap["xsd__short"] = "short";
  if (cflag || sflag)
  {
    deftypemap["xsd__string"] = "";
    usetypemap["xsd__string"] = "char*";
    ptrtypemap["xsd__string"] = "char*";
  }
  else
  {
    deftypemap["xsd__string"] = "";
    usetypemap["xsd__string"] = "std::string";
  }
  if (cflag || sflag)
  {
    deftypemap["xsd__QName"] = "";
    usetypemap["xsd__QName"] = "_QName";
    ptrtypemap["xsd__QName"] = "_QName";
  }
  else
  {
    deftypemap["xsd__QName"] = "typedef std::string xsd__QName;";
    usetypemap["xsd__QName"] = "xsd__QName";
  }
  deftypemap["xsd__unsignedByte"] = "typedef unsigned char xsd__unsignedByte;";
  usetypemap["xsd__unsignedByte"] = "xsd__unsignedByte";
  deftypemap["xsd__unsignedInt"] = "";
  usetypemap["xsd__unsignedInt"] = "unsigned int";
  deftypemap["xsd__unsignedLong"] = "";
  usetypemap["xsd__unsignedLong"] = "ULONG64";
  deftypemap["xsd__unsignedShort"] = "";
  usetypemap["xsd__unsignedShort"] = "unsigned short";
  if (cflag)
  {
    deftypemap["SOAP_ENC__base64Binary"] = "struct SOAP_ENC__base64Binary { unsigned char *__ptr; int __size; };";
    usetypemap["SOAP_ENC__base64Binary"] = "struct SOAP_ENC__base64Binary";
    ptrtypemap["SOAP_ENC__base64Binary"] = "struct SOAP_ENC__base64Binary";
    deftypemap["SOAP_ENC__base64"] = "struct SOAP_ENC__base64 { unsigned char *__ptr; int __size; };";
    usetypemap["SOAP_ENC__base64"] = "struct SOAP_ENC__base64";
    ptrtypemap["SOAP_ENC__base64"] = "struct SOAP_ENC__base64";
  }
  else
  {
    deftypemap["SOAP_ENC__base64Binary"] = "class SOAP_ENC__base64Binary { unsigned char *__ptr; int __size; };";
    usetypemap["SOAP_ENC__base64Binary"] = "SOAP_ENC__base64Binary";
    deftypemap["SOAP_ENC__base64"] = "class SOAP_ENC__base64 { unsigned char *__ptr; int __size; };";
    usetypemap["SOAP_ENC__base64"] = "SOAP_ENC__base64";
  }
  if (cflag)
  {
    deftypemap["SOAP_ENC__boolean"] = "enum SOAP_ENC__boolean { false_, true_ };";
    usetypemap["SOAP_ENC__boolean"] = "enum SOAP_ENC__boolean";
  }
  else
  {
    deftypemap["SOAP_ENC__boolean"] = "typedef bool SOAP_ENC__boolean;";
    usetypemap["SOAP_ENC__boolean"] = "SOAP_ENC__boolean";
  }
  deftypemap["SOAP_ENC__byte"] = "typedef char SOAP_ENC__byte;";
  usetypemap["SOAP_ENC__byte"] = "SOAP_ENC__byte";
  deftypemap["SOAP_ENC__dateTime"] = "typedef time_t SOAP_ENC__dateTime;";
  usetypemap["SOAP_ENC__dateTime"] = "SOAP_ENC__dateTime";
  deftypemap["SOAP_ENC__double"] = "typedef double SOAP_ENC__double;";
  usetypemap["SOAP_ENC__double"] = "SOAP_ENC__double";
  deftypemap["SOAP_ENC__float"] = "typedef float SOAP_ENC__float;";
  usetypemap["SOAP_ENC__float"] = "SOAP_ENC__float";
  if (cflag)
  {
    deftypemap["SOAP_ENC__hexBinary"] = "struct SOAP_ENC__hexBinary { unsigned char *__ptr; int __size; };";
    usetypemap["SOAP_ENC__hexBinary"] = "struct SOAP_ENC__hexBinary";
    ptrtypemap["SOAP_ENC__hexBinary"] = "struct SOAP_ENC__hexBinary";
  }
  else
  {
    deftypemap["SOAP_ENC__hexBinary"] = "class SOAP_ENC__hexBinary { unsigned char *__ptr; int __size; };";
    usetypemap["SOAP_ENC__hexBinary"] = "SOAP_ENC__hexBinary";
  }
  deftypemap["SOAP_ENC__int"] = "typedef int SOAP_ENC__int;";
  usetypemap["SOAP_ENC__int"] = "SOAP_ENC__int";
  deftypemap["SOAP_ENC__long"] = "typedef LONG64 SOAP_ENC__long;";
  usetypemap["SOAP_ENC__long"] = "SOAP_ENC__long";
  deftypemap["SOAP_ENC__short"] = "typedef short SOAP_ENC__short;";
  usetypemap["SOAP_ENC__short"] = "SOAP_ENC__short";
  if (cflag || sflag)
  {
    deftypemap["SOAP_ENC__string"] = "typedef char* SOAP_ENC__string;";
    usetypemap["SOAP_ENC__string"] = "SOAP_ENC__string";
    ptrtypemap["SOAP_ENC__string"] = "SOAP_ENC__string";
  }
  else
  {
    deftypemap["SOAP_ENC__string"] = "typedef std::string SOAP_ENC__string;";
    usetypemap["SOAP_ENC__string"] = "SOAP_ENC__string";
  }
  deftypemap["SOAP_ENC__unsignedByte"] = "typedef unsigned char SOAP_ENC__unsignedByte;";
  usetypemap["SOAP_ENC__unsignedByte"] = "SOAP_ENC__unsignedByte";
  deftypemap["SOAP_ENC__unsignedInt"] = "typedef unsigned int SOAP_ENC__unsignedInt;";
  usetypemap["SOAP_ENC__unsignedInt"] = "SOAP_ENC__unsignedInt";
  deftypemap["SOAP_ENC__unsignedLong"] = "typedef ULONG64 SOAP_ENC__unsignedLong;";
  usetypemap["SOAP_ENC__unsignedLong"] = "SOAP_ENC__unsignedLong";
  deftypemap["SOAP_ENC__unsignedShort"] = "typedef unsigned short SOAP_ENC__unsignedShort;";
  usetypemap["SOAP_ENC__unsignedShort"] = "SOAP_ENC__unsignedShort";
  deftypemap["SOAP_ENC__Array"] = "";
  usetypemap["SOAP_ENC__Array"] = "struct { _XML *__ptr; int __size; }";
  if (cflag)
    ptrtypemap["SOAP_ENC__Array"] = "struct { _XML *__ptr; int __size; }";
  deftypemap["_SOAP_ENC__arrayType"] = "";
  deftypemap["SOAP_ENV__Header"] = "";
  usetypemap["SOAP_ENV__Header"] = "struct SOAP_ENV__Header";
  deftypemap["_SOAP_ENV__mustUnderstand"] = "";
  if (cflag || sflag)
    usetypemap["_SOAP_ENV__mustUnderstand"] = "char*";
  else
    usetypemap["_SOAP_ENV__mustUnderstand"] = "std::string";
  deftypemap["SOAP_ENV__Fault"] = "";
  usetypemap["SOAP_ENV__Fault"] = "struct SOAP_ENV__Fault";
  deftypemap["SOAP_ENV__detail"] = "";
  usetypemap["SOAP_ENV__detail"] = "struct SOAP_ENV__Detail";
  deftypemap["SOAP_ENV__Detail"] = "";
  usetypemap["SOAP_ENV__Detail"] = "struct SOAP_ENV__Detail";
  deftypemap["SOAP_ENV__Code"] = "";
  usetypemap["SOAP_ENV__Code"] = "struct SOAP_ENV__Code";
  deftypemap["SOAP_ENV__Reason"] = "";
  usetypemap["SOAP_ENV__Reason"] = "struct SOAP_ENV__Reason";
  usetypemap["$CONTAINER"] = "std::vector";
  if (read(mapfile))
    fprintf(stderr, "Problem reading type map file '%s'.\nUsing internal type definitions for %s instead.\n\n", mapfile, cflag ? "C" : "C++");
}

const char *Types::nsprefix(const char *prefix, const char *URI)
{
  if (URI && *URI)
  {
    const char *s = uris[URI];
    if (!s)
    {
      size_t n;
      if (!prefix || !*prefix || *prefix == '_')
        s = schema_prefix;
      else
        s = estrdup(prefix);
      if (!syms[s])
        n = syms[s] = 1;
      else
        n = ++syms[s];
      if (n != 1 || !prefix || !*prefix || *prefix == '_')
      {
        size_t l = strlen(s);
        char *t = (char*)emalloc(l + 21);
        (SOAP_SNPRINTF(t, l + 21, l + 20), "%s%lu", s, (unsigned long)n);
        s = t;
      }
      uris[URI] = s;
      if (vflag)
        fprintf(stderr, "namespace prefix %s = \"%s\"\n", s, URI);
    }
    // if *prefix == '_', then add prefix string to s
    if (prefix && *prefix == '_')
    {
      size_t l = strlen(s);
      char *t = (char*)emalloc(l + 2);
      *t = '_';
      soap_strcpy(t + 1, l + 1, s);
      s = t;
    }
    return s;
  }
  return NULL;
}

const char *Types::prefix(const char *name)
{
  const char *s;
  char *t;
  if (*name == '"')
  {
    s = strchr(name + 1, '"');
    t = (char*)emalloc(s - name);
    soap_strncpy(t, s - name, name + 1, s - name - 1);
    return nsprefix(NULL, t);
  }
  s = strchr(name, ':');
  if (s)
  {
    t = (char*)emalloc(s - name + 1);
    soap_strncpy(t, s - name + 1, name, s - name);
    return t;
  }
  return NULL;
}

const char *Types::uri(const char *name)
{
  const char *s;
  char *t;
  if (*name == '"')
  {
    s = strchr(name + 1, '"');
    t = (char*)emalloc(s - name);
    soap_strncpy(t, s - name, name + 1, s - name - 1);
    return t;
  }
  s = strchr(name, ':');
  if (s)
  {
    struct Namespace *p = namespaces;
    if (p)
    {
      for (p += 6; p->id; p++)
      {
        if (!strncmp(p->id, name, s - name) && !p->id[s - name])
        {
          if (p->in && *p->in)
            return p->in;
          return p->ns;
        }
      }
    }
  }
  return NULL;
}

// Find a C name for a QName. If the name has no qualifier, use URI. Suggest prefix for URI
const char *Types::fname(const char *prefix, const char *URI, const char *qname, SetOfString *reserved, enum Lookup lookup, bool isqname)
{
  char buf[4096], *t;
  const char *p, *s, *name;
  if (!qname)
  {
    fprintf(stream, "// Warning: internal error, no QName in fname()\n");
    if (vflag)
      fprintf(stderr, "Internal error, no QName in fname()\n");
    qname = "?";
  }
  name = qname;
  if (isqname)
    s = strrchr(name, ':');
  else
    s = NULL;
  if (s)
  {
    name = s + 1;
    if (qname[0] == '"' && qname[1] == '"')
    {
      s = NULL;
    }
    else if (*qname == '"')
    {
      t = (char*)emalloc(s - qname - 1);
      soap_strncpy(t, s - qname - 1, qname + 1, s - qname - 2);
      URI = t;
    }
    else if (!strncmp(qname, "xs:", 3)) // this hack is necessary since the nsmap table defines "xs" for "xsd"
    {
      s = "xsd";
      URI = NULL;
    }
    else
    {
      t = (char*)emalloc(s - qname + 1);
      soap_strncpy(t, s - qname + 1, qname, s - qname);
      s = t;
      URI = NULL;
    }
  }
  if (URI && *URI)
    p = nsprefix(prefix, URI);
  else if (s)
    p = s;
  else
    p = "";
  s = NULL;
  if (lookup == LOOKUP)
  {
    if (qnames.find(Pair(p,name)) != qnames.end())
      s = qnames[Pair(p,name)];
  }
  if (!s)
  {
    t = buf;
    if (!prefix || *prefix)
    {
      s = p;
      // no longer add '_' when URI != NULL, since nsprefix() will do this
      if (prefix && *prefix == ':')
        *t++ = ':';
      else if (prefix && *prefix == '_')
      {
        if (!URI)
          *t++ = '_';
        if (prefix[1] == '_') // ensures ns prefix starts with __
        {
          soap_strcpy(t, sizeof(buf) - (t - buf), prefix + 1);
          t += strlen(prefix + 1);
        }
      }
      if (s && *s)
      {
        for (; *s; s++)
        {
          if (t >= buf + sizeof(buf) - 8)
            break;
          if (isalnum(*s))
          {
            *t++ = *s;
          }
          else if (*s == '-' && s[1] != '-' && s != p)
          {
            *t++ = '_';
          }
          else if (*s == '_')
          {
            if (s == p)
              *t++ = '_';
            else if (!_flag)
            {
              soap_strcpy(t, sizeof(buf) - (t - buf), "_USCORE");
              t += 7;
            }
            else
            {
              s = utf8(&t, s, t == buf);
            }
          }
          else
          {
            s = utf8(&t, s, t == buf);
          }
        }
        if (!prefix || *prefix != '*')
        {
          *t++ = '_';
          *t++ = '_';
        }
      }
      else if (isdigit(*name))
      {
        *t++ = '_';
      }
    }
    for (s = name; *s; s++)
    {
      if (t >= buf + sizeof(buf) - 8)
        break;
      if (isalnum(*s))
      {
        *t++ = *s;
      }
      else if (*s == '-' && s[1] != '-' && s[1] != '\0' && s != name)
      {
        *t++ = '_';
      }
      else if (!_flag && *s == '_')
      {
        soap_strcpy(t, sizeof(buf) - (t - buf), "_USCORE");
        t += 7;
      }
      else
      {
        s = utf8(&t, s, t == buf);
      }
    }
    *t = '\0';
    s = strchr(buf, ':');
    if (s)
      s++;
    else
      s = buf;
    while (knames.find(s) != knames.end() || (reserved && reserved->find(s) != reserved->end()))
    {
      *t++ = '_';
      *t = '\0';
    }
    if (isalpha(*buf) || *buf == '_' || *buf == ':')
    {
      size_t l = strlen(buf);
      t = (char*)emalloc(l + 1);
      soap_strcpy(t, l + 1, buf);
    }
    else
    {
      size_t l = strlen(buf);
      t = (char*)emalloc(l + 2);
      *t = '_';
      soap_strcpy(t + 1, l + 1, buf);
    }
    s = t;
    if (lookup == LOOKUP)
    {
      qnames[Pair(p,name)] = s;
      if (vflag)
      {
        cerr << "Mapping '" << p << ":" << name << "' to '" << s << "'" << endl;
#ifdef DEBUG
        for (MapOfPairToString::const_iterator i = qnames.begin(); i != qnames.end(); ++i)
          cerr << "Map[" << (*i).first.first << ":" << (*i).first.second << "]='" << (*i).second << "'" << endl;
#endif
      }
    }
  }
  return s;
}

bool Types::is_defined(const char *prefix, const char *URI, const char *qname)
{
  const char *t = fname(prefix, URI, qname, NULL, LOOKUP, true);
  return usetypemap.find(t) != usetypemap.end();
}

const char *Types::aname(const char *prefix, const char *URI, const char *qname)
{
  return fname(prefix, URI, qname, NULL, NOLOOKUP, true);
}

const char *Types::wname(const char *prefix, const char *URI, const char *qname)
{
  const char *s = aname(prefix, URI, qname);
  SetOfString reserved;
  reserved.insert(s);
  s = fname(prefix, URI, qname, &reserved, NOLOOKUP, true);
  knames.insert(s);
  return s;
}

const char *Types::cname(const char *prefix, const char *URI, const char *qname)
{
  return fname(prefix, URI, qname, NULL, LOOKUP, true);
}

const char *Types::tname(const char *prefix, const char *URI, const char *qname)
{
  const char *s, *t;
  t = cname(prefix, URI, qname);
  if (usetypemap.find(t) != usetypemap.end())
  {
    s = usetypemap[t];
    if (vflag)
      cerr << "Mapping use of '" << t << "' to '" << s << "'" << endl;
  }
  else
  {
    s = t;
    fprintf(stream, "\n/// @todo !FIXME! @warning Undefined QName %s for type %s in namespace \"%s\", check WSDL and schema definitions.\n", qname ? qname : "", t, URI ? URI : "?");
    if (vflag)
      fprintf(stderr, "\nWarning: undefined QName %s for type %s in namespace \"%s\"\n", qname ? qname : "", t, URI ? URI : "?");
  }
  return s;
}

const char *Types::tnameptr(bool flag, const char *prefix, const char *URI, const char *qname)
{
  const char *s = pname(flag, !flag, prefix, URI, qname);
  if (flag)
  {
    if (!strchr(s, '*') || !strncmp(s, "char", 4) || !strncmp(s, "const char", 10) || !strncmp(s, "wchar_t", 7) || !strncmp(s, "const wchar_t", 13))
    {
      size_t l = strlen(s);
      char *r = (char*)emalloc(l + 2);
      soap_strcpy(r, l + 2, s);
      soap_strcpy(r + l, 2, "*");
      return r;
    }
  }
  return s;
}

const char *Types::tnamenoptr(const char *prefix, const char *URI, const char *qname)
{
  const char *s = tname(prefix, URI, qname);
  if (strchr(s, '*') && (!strncmp(s, "char", 4) || !strncmp(s, "const char", 10) || !strncmp(s, "wchar_t", 7) || !strncmp(s, "const wchar_t", 13)))
    return s;
  size_t n = strlen(s);
  if (s[n - 1] == '*')
  {
    char *r = (char*)emalloc(n);
    soap_strncpy(r, n, s, n - 1);
    return r;
  }
  return s;
}

const char *Types::pname(bool flag, bool smart, const char *prefix, const char *URI, const char *qname)
{
  const char *s = NULL, *t;
  t = cname(prefix, URI, qname);
  if (flag)
  {
    const char *r = NULL;
    if (!cflag && smart && (r = vname("$POINTER")) && *r != '*' && *r != '$')
    {
      if (smptypemap.find(t) != smptypemap.end())
        s = smptypemap[t];
      else
      {
        if (usetypemap.find(t) != usetypemap.end())
          s = usetypemap[t];
        if (!s)
        {
          s = t;
          fprintf(stream, "\n/// @todo !FIXME! @warning Undefined QName %s for pointer to type %s, check WSDL and schema definitions.\n", qname, t);
          if (vflag)
            fprintf(stderr, "\nWarning: undefined QName %s for pointer to type %s in namespace \"%s\"\n", qname, t, URI ? URI : "?");
        }
        if (!is_ptr(prefix, URI, qname))
        {
          size_t k = strlen(r);
          size_t l = strlen(s);
          char *p = (char*)emalloc(k + l + 4);
          soap_strcpy(p, k + l + 4, r);
          soap_strcpy(p + k, l + 4, "<");
          soap_strcpy(p + k + 1, l + 3, s);
          soap_strcpy(p + k + l + 1, 3, "> ");
          s = p;
        }
        if (vflag)
          cerr << "Mapping \"smart\" pointer of '" << t << "' to '" << s << "'" << endl;
        smptypemap[t] = s;
      }
    }
    else if (ptrtypemap.find(t) != ptrtypemap.end())
    {
      s = ptrtypemap[t];
    }
    else
    {
      if (usetypemap.find(t) != usetypemap.end())
        s = usetypemap[t];
      if (!s)
      {
        s = t;
        fprintf(stream, "\n/// @todo !FIXME! @warning Undefined QName %s for pointer to type %s, check WSDL and schema definitions.\n", qname, t);
        if (vflag)
          fprintf(stderr, "\nWarning: undefined QName %s for pointer to type %s in namespace \"%s\"\n", qname, t, URI ? URI : "?");
      }
      if (!is_ptr(prefix, URI, qname))
      {
        size_t l = strlen(s);
        char *p = (char*)emalloc(l + 2);
        soap_strcpy(p, l + 2, s);
        soap_strcpy(p + l, 2, "*");
        s = p;
      }
      if (vflag)
        cerr << "Mapping pointer of '" << t << "' to '" << s << "'" << endl;
      ptrtypemap[t] = s;
    }
  }
  else if (usetypemap.find(t) != usetypemap.end())
  {
    if (!cflag && smart && smptypemap.find(t) != smptypemap.end() && ptrtypemap.find(t) != ptrtypemap.end() && usetypemap[t] == ptrtypemap[t])
      s = smptypemap[t];
    else
      s = usetypemap[t];
  }
  else
  {
    s = t;
    fprintf(stream, "\n/// @todo !FIXME! @warning Undefined QName %s for type %s in namespace \"%s\", check WSDL and schema definitions.\n", qname, t, URI ? URI : "?");
    if (vflag)
      fprintf(stderr, "\nWarning: undefined QName %s for type %s in namespace \"%s\"\n", qname, t, URI ? URI : "?");
  }
  return s;
}

const char *Types::deftname(enum Type type, bool mk_pointer, bool is_pointer, const char *prefix, const char *URI, const char *qname)
{
  char buf[4096];
  const char *t = fname(prefix, URI, qname, NULL, LOOKUP, true);
  if (deftypemap[t])
  {
    if (vflag)
      fprintf(stderr, "Name %s already defined (probably in typemap \"%s\")\n", qname, mapfile);
    return NULL;
  }
  if (usetypemap[t])
  {
    if (vflag)
      fprintf(stderr, "Name %s is mapped\n", qname);
    return t;
  }
  const char *q = NULL;
  switch (type)
  {
    case ENUM:
      if (!c11flag)
        q = "enum";
      if (c11flag || yflag)
        knames.insert(t);
      break;
    case STRUCT:
      q = "struct";
      if (yflag)
        knames.insert(t);
      break;
    case CLASS:
    case TYPEDEF:
      knames.insert(t);
    default:
      break;
  }
  buf[0] = '\0';
  size_t n = 0;
  if (q)
  {
    soap_strcpy(buf, sizeof(buf), q);
    n = strlen(buf);
    soap_strcpy(buf + n, sizeof(buf) - n, " ");
    ++n;
  }
  soap_strcpy(buf + n, sizeof(buf) - n, t);
  const char *r = vname("$POINTER");
  if (!cflag && !is_pointer && r && *r != '*' && *r != '$')
  {
    n = strlen(buf);
    size_t l = strlen(r);
    char *s = (char*)emalloc(l + n + 4);
    soap_strcpy(s, l + n + 4, r);
    soap_strcpy(s + l, n + 4,  "<");
    soap_strcpy(s + l + 1, n + 3, buf);
    soap_strcpy(s + l + n + 1, 3, "> ");
    smptypemap[t] = s;
  }
  if (mk_pointer)
  {
    n = strlen(buf);
    soap_strcpy(buf + n, sizeof(buf) - n, "*");
  }
  n = strlen(buf);
  char *s = (char*)emalloc(n + 1);
  soap_strcpy(s, n + 1, buf);
  usetypemap[t] = s;
  if (mk_pointer || is_pointer)
    ptrtypemap[t] = s;
  if (is_pointer)
    smptypemap[t] = s;
  if (vflag)
    cerr <<  "Defined '" << t << "' ('" << qname << "' in namespace '" << (URI ? URI : prefix ? prefix : "") << "') as '" << s << "'" << endl;
  return t;
}

// get enumeration value. URI/type refers to the enum simpleType.
const char *Types::ename(const char *type, const char *value, bool isqname)
{
  if (c11flag)
    return fname(NULL, NULL, value, NULL, NOLOOKUP, isqname);
  const char *s = enames[Pair(type,value)];
  if (!s)
  {
    s = fname(NULL, NULL, value, &rnames, NOLOOKUP, isqname);
    if (!eflag && type && *type)
    {
      // Add prefix to enum
      if (!*s || (s[0] == '_' && s[1] == '\0'))
        s = "_x0000";
      size_t l = strlen(type) + strlen(s);
      char *buf = (char*)emalloc(l + 3);
      // _xXXXX is OK here
      if (s[0] == '_' && s[1] != 'x' && strncmp(s, "_USCORE", 7))
        (SOAP_SNPRINTF(buf, l + 3, l + 1), "%s_%s", type, s);
      else
        (SOAP_SNPRINTF(buf, l + 3, l + 2), "%s__%s", type, s);
      s = buf;
    }
    else
      rnames.insert(s);
    enames[Pair(type,value)] = s;
  }
  return s;
}

// get operation name
const char *Types::oname(const char *prefix, const char *URI, const char *qname)
{
  const char *s = fname(prefix, URI, qname, NULL, LOOKUP, true);
  if (s && usetypemap.find(s) != usetypemap.end())
  {
    // Avoid name clash with structs/classes of the same name
    onames.insert(s);
  }
  s = fname(prefix, URI, qname, &onames, NOLOOKUP, true);
  onames.insert(s);
  return s;
}

// generate struct name
const char *Types::sname(const char *URI, const char *name)
{
  const char *s;
  char *t;
  if (!aflag && name)
  {
    size_t l = strlen(name) + 1;
    for (VectorOfString::const_iterator i = scope.begin(); i != scope.end(); ++i)
      l += strlen(*i) + 1;
    t = (char*)emalloc(l);
    size_t n = 0;
    for (VectorOfString::const_iterator j = scope.begin(); j != scope.end(); ++j)
    {
      soap_strcpy(t + n, l - n, *j);
      n = strlen(t);
      soap_strcpy(t + n, l - n, "-");
      ++n;
      if (n >= l)
        break;
    }
    soap_strcpy(t + n, l - n, name);
    s = fname("_", URI, t, &rnames, NOLOOKUP, true);
    rnames.insert(s);
  }
  else if (URI && *URI)
  {
    s = nsprefix(NULL, URI);
    size_t l = strlen(s);
    t = (char*)emalloc(l + 30);
    (SOAP_SNPRINTF(t, l + 30, l + 29), "_%s__struct_%d", s, snum++);
    s = t;
  }
  else
  {
    t = (char*)emalloc(28);
    (SOAP_SNPRINTF(t, 28, 27), "struct_%d", snum++);
    s = t;
  }
  return s;
}

// generate union name
const char *Types::uname(const char *URI)
{
  const char *s;
  char *t;
  if (!aflag)
  {
    size_t l = 0;
    for (VectorOfString::const_iterator i = scope.begin(); i != scope.end(); ++i)
      l += strlen(*i) + 1;
    t = (char*)emalloc(l + 6);
    soap_strcpy(t, l + 6, "union");
    size_t n = 5;
    for (VectorOfString::const_iterator j = scope.begin(); j != scope.end(); ++j)
    {
      soap_strcpy(t + n, l + 6 - n, "-");
      soap_strcpy(t + n + 1, l + 5 - n, *j);
      n = strlen(t);
    }
    s = fname("_", URI, t, &rnames, NOLOOKUP, true);
    rnames.insert(s);
  }
  else if (URI && *URI)
  {
    s = nsprefix(NULL, URI);
    size_t l = strlen(s);
    t = (char*)emalloc(l + 30);
    (SOAP_SNPRINTF(t, l + 30, l + 29), "_%s__union_%d", s, unum++);
    s = t;
  }
  else
  {
    t = (char*)emalloc(28);
    (SOAP_SNPRINTF(t, 28, 27), "_union_%d", unum++);
    s = t;
  }
  return s;
}

// generate enum name
const char *Types::gname(const char *URI, const char *name)
{
  const char *s;
  char *t;
  if (!aflag && name)
  {
    size_t l = strlen(name) + 1;
    for (VectorOfString::const_iterator i = scope.begin(); i != scope.end(); ++i)
      l += strlen(*i) + 1;
    t = (char*)emalloc(l);
    size_t n = 0;
    for (VectorOfString::const_iterator j = scope.begin(); j != scope.end(); ++j)
    {
      soap_strcpy(t + n, l - n, *j);
      n = strlen(t);
      soap_strcpy(t + n, l - n, "-");
      ++n;
      if (n >= l)
        break;
    }
    soap_strcpy(t + n, l - n, name);
    s = fname("_", URI, t, &rnames, LOOKUP, true);
    rnames.insert(s);
  }
  else if (URI && *URI)
  {
    s = nsprefix(NULL, URI);
    size_t l = strlen(s);
    t = (char*)emalloc(l + 30);
    (SOAP_SNPRINTF(t, l + 30, l + 29), "_%s__enum_%d", s, gnum++);
    s = t;
  }
  else
  {
    t = (char*)emalloc(28);
    (SOAP_SNPRINTF(t, 28, 27), "enum_%d", gnum++);
    s = t;
  }
  return s;
}

const char *Types::vname(const char *var)
{
  MapOfStringToString::const_iterator i = usetypemap.find(var);
  if (i != usetypemap.end())
    return (*i).second;
  return var;
}

// checks if nillable or minOccurs=0
bool Types::is_nillable(const xs__element& element)
{
  return (element.nillable || (element.minOccurs && !strcmp(element.minOccurs, "0")));
}

// checks if permitted as union member
bool Types::is_choicetype(const char *prefix, const char *URI, const char *type)
{
  // TODO: consider c11flag also safe, but classes containing unions must define assignment ops using the selector(s)
  if (cflag)
    return true;
  if (!strcmp(type, "xs:byte"))
    return true;
  const char *t = tname(prefix, URI, type);
  return (
      !strncmp(t, "enum ", 5) ||
      !strcmp(t, "bool") ||
      !strcmp(t, "int8_t") ||
      !strcmp(t, "int16_t") ||
      !strcmp(t, "int32_t") ||
      !strcmp(t, "int64_t") ||
      !strcmp(t, "uint8_t") ||
      !strcmp(t, "uint16_t") ||
      !strcmp(t, "uint32_t") ||
      !strcmp(t, "uint64_t") ||
      !strcmp(t, "char") ||
      !strcmp(t, "unsigned char") ||
      !strcmp(t, "short") ||
      !strcmp(t, "unsigned short") ||
      !strcmp(t, "int") ||
      !strcmp(t, "unsigned int") ||
      !strcmp(t, "long") ||
      !strcmp(t, "long long") ||
      !strcmp(t, "unsigned long") ||
      !strcmp(t, "unsigned long long") ||
      !strcmp(t, "LONG64") ||
      !strcmp(t, "ULONG64") ||
      !strcmp(t, "float") ||
      !strcmp(t, "double") ||
      !strcmp(t, "long double") ||
      !strcmp(t, "time_t") ||
      !strcmp(t, "_QName") ||
      !strcmp(t, "_XML")
      );
}

bool Types::is_ptr(const char *prefix, const char *URI, const char *qname)
{
  const char *t = cname(prefix, URI, qname);
  if (usetypemap.find(t) != usetypemap.end())
  {
    if (ptrtypemap.find(t) != ptrtypemap.end())
      return usetypemap[t] == ptrtypemap[t];
    const char *s = usetypemap[t];
    while (s && *s)
    {
      s = strchr(s + 1, '*');
      if (s && *(s-1) != '/' && *(s+1) != '/')
        return true;
    }
  }
  return false;
}

void Types::dump(FILE *fd)
{
  fprintf(fd, "\nTypes:\n");
  for (MapOfStringToString::const_iterator i = usetypemap.begin(); i != usetypemap.end(); ++i)
    fprintf(fd, "%s=%s\n", (*i).first, (*i).second ? (*i).second : "(null)");
  fprintf(fd, "\nPointers:\n");
  for (MapOfStringToString::const_iterator j = ptrtypemap.begin(); j != ptrtypemap.end(); ++j)
    fprintf(fd, "%s=%s\n", (*j).first, (*j).second ? (*j).second : "(null)");
}

void Types::define(const char *URI, const char *name, const xs__complexType& complexType)
{
  // generate prototype for structs/classes and store name
  const char *prefix = NULL;
  if (complexType.name)
    name = complexType.name;
  else
    prefix = "_";
  if (complexType.complexContent
   && complexType.complexContent->restriction
   && !strcmp(complexType.complexContent->restriction->base, "SOAP-ENC:Array"))
  {
    if (strcmp(schema_prefix, "ns"))
      prefix = "*";
    else
      prefix = "";
  }
  if (cflag)
  {
    const char *t = deftname(STRUCT, true, false, prefix, URI, name);
    if (t)
    {
      if (yflag)
        fprintf(stream, "/// @brief Typedef synonym for struct %s.\ntypedef struct %s %s;\n", t, t, t);
    }
    else if (name)
    {
      t = deftypemap[cname(prefix, URI, name)];
      if (t)
      {
        fprintf(stream, "/// Imported complexType \"%s\":%s from typemap \"%s\".\n", URI, name, mapfile ? mapfile : "");
        document(complexType.annotation);
        if (*t)
          format(t);
        else
          fprintf(stream, "// complexType definition intentionally left blank.\n");
        fprintf(stream, "\n");
      }
    }
  }
  else
  {
    const char *t = deftname(CLASS, true, false, prefix, URI, name);
    if (t)
      fprintf(stream, "//  Forward declaration of class %s.\nclass %s;\n\n", t, t);
    else if (name)
    {
      t = deftypemap[cname(prefix, URI, name)];
      if (t)
      {
        fprintf(stream, "/// Imported complexType \"%s\":%s from typemap \"%s\".\n", URI, name, mapfile ? mapfile : "");
        document(complexType.annotation);
        if (*t)
          format(t);
        else
          fprintf(stream, "// complexType definition intentionally left blank.\n");
        fprintf(stream, "\n");
      }
    }
  }
}

void Types::gen(const char *URI, const char *name, const xs__simpleType& simpleType, bool anonymous, bool nested_restriction)
{
  const char *t = NULL;
  const char *prefix = NULL;
  if (simpleType.name)
    name = simpleType.name;
  else if (!nested_restriction)
    prefix = "_";
  if (!anonymous)
  {
    t = deftypemap[cname(NULL, URI, name)];
    if (t)
    {
      fprintf(stream, "/// Imported simpleType \"%s\":%s from typemap \"%s\".\n", URI, name, mapfile ? mapfile : "");
      document(simpleType.annotation);
      if (*t)
        format(t);
      else
        fprintf(stream, "// simpleType definition intentionally left blank.\n");
      return;
    }
  }
  if (simpleType.restriction)
  {
    const char *base = simpleType.restriction->base;
    if (!base && simpleType.restriction->simpleType)
    {
      if (!anonymous)
      {
        if (simpleType.restriction->simpleType->list && simpleType.restriction->length && simpleType.restriction->length->value)
        {
          fprintf(stream, "/// @brief \"%s\":%s is a simpleType restriction list of length %s.\n///\n", URI ? URI : "", name, simpleType.restriction->length->value);
          document(simpleType.restriction->length->annotation);
        }
        else
        {
          const char *a = NULL, *b = "unbounded";
          if (simpleType.restriction->minLength)
          {
            a = simpleType.restriction->minLength->value;
            document(simpleType.restriction->minLength->annotation);
          }
          if (simpleType.restriction->maxLength)
          {
            b = simpleType.restriction->maxLength->value;
            document(simpleType.restriction->maxLength->annotation);
          }
          if (a || b)
            fprintf(stream, "/// @brief \"%s\":%s is a simpleType restriction list of length %s..%s.\n", URI ? URI : "", name, a ? a : "0", b ? b : "");
          else
            fprintf(stream, "/// @brief \"%s\":%s is a simpleType restriction.\n///\n", URI ? URI : "", name);
        }
      }
      gen(URI, name, *simpleType.restriction->simpleType, anonymous, true);
    }
    else
    {
      if (!base)
        base = "xsd:string";
      const char *baseURI = NULL;
      if (simpleType.restriction->simpleTypePtr() && simpleType.restriction->simpleTypePtr()->schemaPtr())
        baseURI = simpleType.restriction->simpleTypePtr()->schemaPtr()->targetNamespace;
      if (!anonymous)
        fprintf(stream, "/// @brief \"%s\":%s is a simpleType restriction of XSD type %s.\n///\n", URI ? URI : "", name, base);
      document(simpleType.annotation);
      document(simpleType.restriction->annotation);
      if (simpleType.restriction->assertion && simpleType.restriction->assertion->test)
      {
        fprintf(stream, "/// Assertion:\n");
        documentation(simpleType.restriction->assertion->test);
      }
      if (!simpleType.restriction->enumeration.empty())
      {
        bool is_qname = !strcmp(base, "xs:QName");
        if (!anonymous)
        {
          t = deftname(ENUM, false, false, prefix, URI, name);
          if (t && !eflag && !c11flag)
            fprintf(stream, "/// @note The enum values are prefixed with \"%s__\" to prevent name clashes: use wsdl2h option -e to omit this prefix or use option -c++11 for scoped enumerations\n", t);
        }
        if (!t)
          t = gname(URI, name);
        if (c11flag)
        {
          if (!anonymous)
            fprintf(stream, "enum class %s\n{\n", t);
          else
            fprintf(stream, "    enum class %s\n    {\n", t);
        }
        else
        {
          if (!anonymous)
            fprintf(stream, "enum %s\n{\n", t);
          else
            fprintf(stream, "    enum %s\n    {\n", t);
        }
        SetOfString enumvals;
        LONG64 enumval = 0;
        if (!is_qname)
        {
          bool letters_ok = true;
          for (vector<xs__enumeration>::const_iterator enumeration = simpleType.restriction->enumeration.begin(); enumeration != simpleType.restriction->enumeration.end(); ++enumeration)
          {
            const char *s;
            if ((s = (*enumeration).value))
            {
              if (!enumvals.count(s))
              {
                if (is_integer(s))
                {
                  document((*enumeration).annotation);
                  fprintf(stream, "\t%s = %s,\t///< %s value=\"%s\"\n", ename(eflag ? "enum int" : t, s, false), s, base, s); // type="enum int" if eflag so all int enum consts get the same value assigned
                  enumvals.insert(s);
                  LONG64 n = soap_strtoll(s, NULL, 10);
                  if (letters_ok)
                  {
                    if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z'))
                      letters_ok = false;
                  }
                  if (n > enumval)
                    enumval = n;
                }
              }
            }
          }
          if (letters_ok)
          {
            for (vector<xs__enumeration>::const_iterator enumeration = simpleType.restriction->enumeration.begin(); enumeration != simpleType.restriction->enumeration.end(); ++enumeration)
            {
              const char *s;
              if ((s = (*enumeration).value))
              {
                if (!enumvals.count(s))
                {
                  if (isalpha(s[0]) && !s[1])
                  {
                    document((*enumeration).annotation);
                    fprintf(stream, "\t%s = '%c',\t///< %s value=\"%s\"\n", ename(eflag ? "enum char" : t, s, false), *s, base, s); // type="enum char" if eflag so all char enum consts get the same value assigned
                    enumvals.insert(s);
                    if (*s > enumval)
                      enumval = *s;
                  }
                }
              }
            }
          }
        }
        for (vector<xs__enumeration>::const_iterator enumeration = simpleType.restriction->enumeration.begin(); enumeration != simpleType.restriction->enumeration.end(); ++enumeration)
        {
          const char *s;
          if ((s = (*enumeration).value))
          {
            if (!enumvals.count(s))
            {
              document((*enumeration).annotation);
              if (is_qname)
                fprintf(stream, "\t%s,\t///< %s value=\"%s\"\n", ename(t, (*enumeration).value_, true), base, (*enumeration).value_);
              else if (enumval)
                fprintf(stream, "\t%s = " SOAP_LONG_FORMAT ",\t///< %s value=\"%s\"\n", ename(t, s, false), ++enumval, base, s);
              else
                fprintf(stream, "\t%s,\t///< %s value=\"%s\"\n", ename(t, s, false), base, s);
              enumvals.insert(s);
            }
          }
          else
            fprintf(stream, "//\tunrecognized: enumeration \"%s\" has no value\n", name ? name : "");
        }
        if (!anonymous)
        {
          fprintf(stream, "};\n\n");
          if (!c11flag && yflag)
            fprintf(stream, "/// @brief Typedef synonym for enum %s.\ntypedef enum %s %s;\n", t, t, t);
          if (pflag && simpleType.name)
          {
            const char *s = wname(prefix, URI, name);
            fprintf(stream, "/// @brief A class wrapper.\n///\n");
            fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", s);
            fprintf(stream, elementformat, tname(prefix, URI, name), "__item;");
            modify(s);
            fprintf(stream, "\n};\n\n");
          }
        }
        else
          fprintf(stream, "    }\n");
      }
      else
      {
        if (simpleType.restriction->length && simpleType.restriction->length->value)
        {
          fprintf(stream, "/// Length of this string is %s.\n", simpleType.restriction->length->value);
          document(simpleType.restriction->length->annotation);
        }
        else
        {
          const char *a = NULL, *b = NULL;
          if (simpleType.restriction->minLength)
          {
            a = simpleType.restriction->minLength->value;
            document(simpleType.restriction->minLength->annotation);
          }
          if (simpleType.restriction->maxLength)
          {
            b = simpleType.restriction->maxLength->value;
            document(simpleType.restriction->maxLength->annotation);
          }
          if (a || b)
          {
            fprintf(stream, "/// Length of this string is %s to %s.\n", a ? a : "0", b ? b : "unbounded");
          }
        }
        char format[16];
        format[0] = '\0';
        if (simpleType.restriction->precision && simpleType.restriction->precision->value)
        {
          soap_strcpy(format, sizeof(format), simpleType.restriction->precision->value);
          fprintf(stream, "/// %s is %s.\n", simpleType.restriction->precision->fixed ? "Fixed precision" : "Precision", simpleType.restriction->precision->value);
        }
        else if (simpleType.restriction->totalDigits && simpleType.restriction->totalDigits->value)
        {
          soap_strcpy(format, sizeof(format), simpleType.restriction->totalDigits->value);
          fprintf(stream, "/// %s of total digits is %s.\n", simpleType.restriction->totalDigits->fixed ? "Fixed number" : "Number", simpleType.restriction->totalDigits->value);
        }
        if (simpleType.restriction->scale && simpleType.restriction->scale->value)
        {
          size_t n = strlen(format);
          soap_strcpy(format + n, sizeof(format) - n, ".");
          soap_strcpy(format + n + 1, sizeof(format) - n - 1, simpleType.restriction->scale->value);
          fprintf(stream, "/// %s is %s.\n", simpleType.restriction->scale->fixed ? "Fixed scale" : "Scale", simpleType.restriction->scale->value);
        }
        else if (simpleType.restriction->fractionDigits && simpleType.restriction->fractionDigits->value)
        {
          size_t n = strlen(format);
          soap_strcpy(format + n, sizeof(format) - n, ".");
          soap_strcpy(format + n + 1, sizeof(format) - n - 1, simpleType.restriction->fractionDigits->value);
          fprintf(stream, "/// %s of fraction digits is %s.\n", simpleType.restriction->fractionDigits->fixed ? "Fixed number" : "Number", simpleType.restriction->fractionDigits->value);
        }
        for (vector<xs__pattern>::const_iterator pattern1 = simpleType.restriction->pattern.begin(); pattern1 != simpleType.restriction->pattern.end(); ++pattern1)
          fprintf(stream, "/// Content pattern is \"%s\".\n", xstring((*pattern1).value));
        const char *ai = NULL, *ae = NULL, *bi = NULL, *be = NULL;
        if (simpleType.restriction->minInclusive)
        {
          ai = simpleType.restriction->minInclusive->value;
          document(simpleType.restriction->minInclusive->annotation);
        }
        else if (simpleType.restriction->minExclusive)
        {
          ae = simpleType.restriction->minExclusive->value;
          document(simpleType.restriction->minExclusive->annotation);
        }
        if (simpleType.restriction->maxInclusive)
        {
          bi = simpleType.restriction->maxInclusive->value;
          document(simpleType.restriction->maxInclusive->annotation);
        }
        else if (simpleType.restriction->maxExclusive)
        {
          be = simpleType.restriction->maxExclusive->value;
          document(simpleType.restriction->maxExclusive->annotation);
        }
        if (ai || ae || bi || be)
        {
          fprintf(stream, "/// Value range is ");
          if (ai)
            fprintf(stream, "%s", ai);
          else if (ae)
            fprintf(stream, "%s (exclusive)", ae);
          else
            fprintf(stream, "lowest");
          fprintf(stream, " to ");
          if (bi)
            fprintf(stream, "%s.\n", bi);
          else if (be)
            fprintf(stream, "%s (exclusive).\n", be);
          else
            fprintf(stream, "highest.\n");
        }
        if (!simpleType.restriction->attribute.empty())
        {
          if (!Wflag)
            fprintf(stderr, "\nWarning: simpleType \"%s\" should not have attributes\n", name ? name : "");
        }
        const char *s = tname(NULL, baseURI, base);
        if (!anonymous)
        {
          t = deftname(TYPEDEF, false, is_ptr(NULL, baseURI, base), prefix, URI, name);
          if (t)
            fprintf(stream, "typedef %s %s", s, t);
        }
        else
        {
          t = "";
          fprintf(stream, elementformat, s, "");
          fprintf(stream, "\n");
        }
        if (t)
        {
          if (!anonymous && !simpleType.restriction->pattern.empty())
          {
            fprintf(stream, " \"");
            for (vector<xs__pattern>::const_iterator pattern2 = simpleType.restriction->pattern.begin(); pattern2 != simpleType.restriction->pattern.end(); ++pattern2)
            {
              if (pattern2 != simpleType.restriction->pattern.begin())
                fprintf(stream, "|");
              fprintf(stream, "%s", xstring((*pattern2).value));
            }
            fprintf(stream, "\"");
          }
          // add range info only when type is numeric
          bool is_numeric_type = false, is_unsigned_type = false, is_long_type = false, is_double_type = false, is_float_type = false;
          if (!strncmp(s, "signed ", 7))
          {
            s += 7;
          }
          else if (!strncmp(s, "unsigned ", 9))
          {
            s += 9;
            is_unsigned_type = true;
          }
          if (!strncmp(s, "long ", 5))
          {
            s += 5;
            is_long_type = true;
          }
          else if (!strncmp(s, "short ", 6))
          {
            s += 6;
          }
          if (!strncmp(s, "xsd__unsigned", 13))
          {
            s += 13;
            is_unsigned_type = true;
          }
          else if (!strncmp(s, "xsd__", 5))
          {
            s += 5;
          }
          if (!strcmp(s, "float"))
            is_numeric_type = is_float_type = true;
          else if (!strcmp(s, "double"))
            is_numeric_type = is_float_type = is_double_type = true;
          else if (!strcmp(s, "bool")
           || !strcmp(s, "byte")
           || !strcmp(s, "Byte")
           || !strcmp(s, "char")
           || !strcmp(s, "int")
           || !strcmp(s, "Int")
           || !strcmp(s, "short")
           || !strcmp(s, "Short"))
            is_numeric_type = true;
          else if (!strcmp(s, "LONG64")
           || !strcmp(s, "long")
           || !strcmp(s, "Long"))
            is_numeric_type = is_long_type = true;
          else if (!strcmp(s, "ULONG64"))
            is_numeric_type = is_unsigned_type = is_long_type = true;
          if (!anonymous && *format)
          {
            if (is_double_type)
            {
              if (is_long_type)
                fprintf(stream, " \"%%%sLf\"", format);
              else
                fprintf(stream, " \"%%%slf\"", format);
            }
            else if (is_float_type)
            {
              fprintf(stream, " \"%%%sf\"", format);
            }
            else if (is_numeric_type)
            {
              if (is_unsigned_type)
              {
                if (is_long_type)
                  fprintf(stream, " \"%%%sllu\"", format);
                else
                  fprintf(stream, " \"%%%su\"", format);
              }
              else
              {
                if (is_long_type)
                  fprintf(stream, " \"%%%slld\"", format);
                else
                  fprintf(stream, " \"%%%sd\"", format);
              }
            }
          }
          if (!anonymous
                && simpleType.restriction->length
                && simpleType.restriction->length->value)
            fprintf(stream, " %s", simpleType.restriction->length->value);
          else if (!anonymous
                && simpleType.restriction->minLength
                && simpleType.restriction->minLength->value)
            fprintf(stream, " %s", simpleType.restriction->minLength->value);
          else if (is_float_type
                && !anonymous
                && simpleType.restriction->minInclusive
                && simpleType.restriction->minInclusive->value
                && is_float(simpleType.restriction->minInclusive->value))
            fprintf(stream, " %s", simpleType.restriction->minInclusive->value);
          else if (is_numeric_type
                && !anonymous
                && simpleType.restriction->minInclusive
                && simpleType.restriction->minInclusive->value
                && is_integer(simpleType.restriction->minInclusive->value))
            fprintf(stream, " %s", simpleType.restriction->minInclusive->value);
          else if (is_float_type
                && !anonymous
                && simpleType.restriction->minExclusive
                && simpleType.restriction->minExclusive->value
                && is_float(simpleType.restriction->minExclusive->value))
            fprintf(stream, " %s <", simpleType.restriction->minExclusive->value);
          else if (is_numeric_type
                && !anonymous
                && simpleType.restriction->minExclusive
                && simpleType.restriction->minExclusive->value
                && is_integer(simpleType.restriction->minExclusive->value))
            fprintf(stream, " " SOAP_LONG_FORMAT, to_integer(simpleType.restriction->minExclusive->value)+1);
          else if (!anonymous
                && simpleType.restriction->minInclusive
                && simpleType.restriction->minInclusive->value
                && is_integer(simpleType.restriction->minInclusive->value))
            fprintf(stream, " /* from %s (inclusive) @warning: could not determine if this type is numeric */", simpleType.restriction->minInclusive->value);
          else if (!anonymous
                && simpleType.restriction->minExclusive
                && simpleType.restriction->minExclusive->value
                && is_integer(simpleType.restriction->minExclusive->value))
            fprintf(stream, " /* from %s (exclusive) @warning: could not determine if this type is numeric */", simpleType.restriction->minExclusive->value);
          if (!anonymous
                && simpleType.restriction->length
                && simpleType.restriction->length->value)
            fprintf(stream, " : %s", simpleType.restriction->length->value);
          else if (!anonymous
                && simpleType.restriction->maxLength
                && simpleType.restriction->maxLength->value)
            fprintf(stream, " : %s", simpleType.restriction->maxLength->value);
          else if (is_float_type
                && !anonymous
                && simpleType.restriction->maxInclusive
                && simpleType.restriction->maxInclusive->value
                && is_float(simpleType.restriction->maxInclusive->value))
            fprintf(stream, " : %s", simpleType.restriction->maxInclusive->value);
          else if (is_numeric_type
                && !anonymous
                && simpleType.restriction->maxInclusive
                && simpleType.restriction->maxInclusive->value
                && is_integer(simpleType.restriction->maxInclusive->value))
            fprintf(stream, " : %s", simpleType.restriction->maxInclusive->value);
          else if (is_float_type
                && !anonymous
                && simpleType.restriction->maxExclusive
                && simpleType.restriction->maxExclusive->value
                && is_float(simpleType.restriction->maxExclusive->value))
            fprintf(stream, " :< %s", simpleType.restriction->maxExclusive->value);
          else if (is_numeric_type
                && !anonymous
                && simpleType.restriction->maxExclusive
                && simpleType.restriction->maxExclusive->value
                && is_integer(simpleType.restriction->maxExclusive->value))
            fprintf(stream, " : " SOAP_LONG_FORMAT, to_integer(simpleType.restriction->maxExclusive->value)-1);
          else if (!anonymous
                && simpleType.restriction->maxInclusive
                && simpleType.restriction->maxInclusive->value
                && is_integer(simpleType.restriction->maxInclusive->value))
            fprintf(stream, " /* to %s (inclusive) @warning: could not determine if this type is numeric */", simpleType.restriction->maxInclusive->value);
          else if (!anonymous
                && simpleType.restriction->maxExclusive
                && simpleType.restriction->maxExclusive->value
                && is_integer(simpleType.restriction->maxExclusive->value))
            fprintf(stream, " /* to %s (exclusive) @warning: could not determine if this type is numeric */", simpleType.restriction->maxExclusive->value);
          if (!anonymous)
          {
            fprintf(stream, ";\n\n");
            if (pflag && simpleType.name)
            {
              const char *s = wname(prefix, URI, name);
              fprintf(stream, "/// @brief A class wrapper.\n///\n");
              fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", s);
              fprintf(stream, elementformat, tname(prefix, URI, name), "__item;");
              modify(s);
              fprintf(stream, "\n};\n\n");
            }
          }
        }
      }
    }
  }
  else if (simpleType.list)
  {
    if (simpleType.list->restriction && simpleType.list->restriction->base)
    {
      if (!anonymous)
      {
        fprintf(stream, "/// @brief \"%s\":%s is a simpleType list restriction of XSD type %s.\n///\n", URI ? URI : "", name, simpleType.list->restriction->base);
        fprintf(stream, "/// @note This enumeration is a bitmask, so a set of values is supported (using | and & bit-ops on the bit vector).\n");
      }
      document(simpleType.annotation);
      if (!anonymous)
      {
        t = deftname(ENUM, false, false, prefix, URI, name);
        if (t)
        {
          if (c11flag)
            fprintf(stream, "enum * class : int64_t %s\n{\n", t);
          else
            fprintf(stream, "enum * %s\n{\n", t);
        }
      }
      else
      {
        t = "";
        fprintf(stream, "enum *\n{\n");
      }
      if (t)
      {
        for (vector<xs__enumeration>::const_iterator enumeration = simpleType.list->restriction->enumeration.begin(); enumeration != simpleType.list->restriction->enumeration.end(); ++enumeration)
        {
          if ((*enumeration).value)
          {
            if (!strcmp(simpleType.list->restriction->base, "xs:QName") && (*enumeration).value_)
              fprintf(stream, "\t%s,\t///< %s value=\"%s\"\n", ename(t, (*enumeration).value_, true), simpleType.list->restriction->base, (*enumeration).value_);
            else
              fprintf(stream, "\t%s,\t///< %s value=\"%s\"\n", ename(t, (*enumeration).value, false), simpleType.list->restriction->base, (*enumeration).value);
          }
          else
            fprintf(stream, "//\tunrecognized: bitmask enumeration \"%s\" has no value\n", t);
        }
        if (!anonymous)
        {
          fprintf(stream, "};\n\n");
          if (!c11flag && yflag)
            fprintf(stream, "/// @brief Typedef synonym for enum %s.\ntypedef enum %s %s;\n", t, t, t);
          if (pflag && simpleType.name)
          {
            const char *s = wname(prefix, URI, name);
            fprintf(stream, "/// @brief A class wrapper.\n///\n");
            fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", s);
            fprintf(stream, elementformat, tname(prefix, URI, name), "__item;");
            modify(s);
            fprintf(stream, "\n};\n\n");
          }
        }
        else
          fprintf(stream, "}\n");
      }
    }
    else if (simpleType.list->itemType)
    {
      const xs__simpleType *p = simpleType.list->itemTypePtr();
      if (p
       && p->restriction
       && p->restriction->base
       && !p->restriction->enumeration.empty()
       && p->restriction->enumeration.size() <= 64)
      {
        if (!anonymous)
        {
          fprintf(stream, "/// @brief \"%s\":%s is a simpleType list of %s.\n///\n", URI ? URI : "", name, simpleType.list->itemType);
          fprintf(stream, "/// @note This enumeration is a bitmask, so a set of values is supported (using | and & bit-ops on the bit vector).\n");
        }
        document(simpleType.annotation);
        if (!anonymous)
        {
          t = deftname(ENUM, false, false, prefix, URI, name);
          if (t)
          {
            if (c11flag)
              fprintf(stream, "enum * class %s : int64_t\n{\n", t);
            else
              fprintf(stream, "enum * %s\n{\n", t);
          }
        }
        else
        {
          t = "";
          fprintf(stream, "enum *\n{\n");
        }
        if (t)
        {
          for (vector<xs__enumeration>::const_iterator enumeration = p->restriction->enumeration.begin(); enumeration != p->restriction->enumeration.end(); ++enumeration)
          {
            if ((*enumeration).value)
            {
              if (!strcmp(p->restriction->base, "xs:QName") && (*enumeration).value_)
                fprintf(stream, "\t%s,\t///< %s value=\"%s\"\n", ename(t, (*enumeration).value_, true), p->restriction->base, (*enumeration).value_);
              else
                fprintf(stream, "\t%s,\t///< %s value=\"%s\"\n", ename(t, (*enumeration).value, false), p->restriction->base, (*enumeration).value);
            }
            else
              fprintf(stream, "//\tunrecognized: bitmask enumeration \"%s\" has no value\n", t);
          }
          if (!anonymous)
          {
            fprintf(stream, "};\n\n");
            if (!c11flag && yflag)
              fprintf(stream, "/// @brief Typedef synonym for enum %s.\ntypedef enum %s %s;\n", t, t, t);
            if (pflag && simpleType.name)
            {
              const char *s = wname(prefix, URI, name);
              fprintf(stream, "/// @brief A class wrapper.\n///\n");
              fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", s);
              fprintf(stream, elementformat, tname(prefix, URI, name), "__item;");
              modify(s);
              fprintf(stream, "\n};\n\n");
            }
          }
          else
            fprintf(stream, "}\n");
        }
      }
      else
      {
        const char *base;
        if (!strcmp(simpleType.list->itemType, "xs:QName"))
          base = "xsd:QName";
        else
          base = "xsd:string";
        const char *s = tname(NULL, NULL, base);
        if (!anonymous)
        {
          fprintf(stream, "/// @brief \"%s\":%s is a simpleType containing a whitespace separated list of %s.\n///\n", URI ? URI : "", name, simpleType.list->itemType);
          t = deftname(TYPEDEF, false, is_ptr(NULL, NULL, base), prefix, URI, name);
        }
        document(simpleType.annotation);
        if (t)
          fprintf(stream, "typedef %s %s;\n", s, t);
        else
        {
          fprintf(stream, elementformat, s, "");
          fprintf(stream, "\n");
        }
        fprintf(stream, "\n");
      }
    }
    else
    {
      if (!anonymous)
      {
        fprintf(stream, "/// @brief \"%s\":%s is a simpleType list.\n///\n", URI ? URI : "", name);
        fprintf(stream, "/// @note This enumeration is a bitmask, so a set of values is supported (using | and & bit-ops on the bit vector).\n");
      }
      document(simpleType.annotation);
      if (!anonymous)
      {
        t = deftname(ENUM, false, false, prefix, URI, name);
        if (t && !eflag && !c11flag)
          fprintf(stream, "/// @note The enum values are prefixed with \"%s__\" to prevent name clashes: use wsdl2h option -e to omit this prefix or use option -c++11 for scoped enumerations\n", t);
      }
      else
        t = "";
      if (t)
      {
        if (c11flag)
          fprintf(stream, "enum * class %s : int64_t\n{\n", t);
        else
          fprintf(stream, "enum * %s\n{\n", t);
        for (vector<xs__simpleType>::const_iterator simple = simpleType.list->simpleType.begin(); simple != simpleType.list->simpleType.end(); ++simple)
        {
          if ((*simple).restriction && (*simple).restriction->base)
          {
            for (vector<xs__enumeration>::const_iterator enumeration = (*simple).restriction->enumeration.begin(); enumeration != (*simple).restriction->enumeration.end(); ++enumeration)
            {
              if ((*enumeration).value)
              {
                if (!strcmp((*simple).restriction->base, "xs:QName") && (*enumeration).value_)
                  fprintf(stream, "\t%s,\t///< %s value=\"%s\"\n", ename(t, (*enumeration).value_, true), (*simple).restriction->base, (*enumeration).value_);
                else
                  fprintf(stream, "\t%s,\t///< %s value=\"%s\"\n", ename(t, (*enumeration).value, false), (*simple).restriction->base, (*enumeration).value);
              }
              else
                fprintf(stream, "//\tunrecognized: bitmask enumeration \"%s\" has no value\n", t);
            }
          }
        }
        if (!anonymous)
        {
          fprintf(stream, "};\n\n");
          if (!c11flag && yflag)
            fprintf(stream, "/// @brief Typedef synonym for enum %s.\ntypedef enum %s %s;\n", t, t, t);
          if (pflag && simpleType.name)
          {
            const char *s = wname(prefix, URI, name);
            fprintf(stream, "/// @brief A class wrapper.\n///\n");
            fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", s);
            fprintf(stream, elementformat, tname(prefix, URI, name), "__item;");
            modify(s);
            fprintf(stream, "\n};\n\n");
          }
        }
        else
          fprintf(stream, "}\n\n");
      }
    }
  }
  else if (simpleType.union_)
  {
    if (simpleType.union_->memberTypes)
    {
      const char *s = tname(NULL, NULL, "xsd:string");
      if (!anonymous)
        t = deftname(TYPEDEF, false, is_ptr(NULL, NULL, "xsd:string"), prefix, URI, name);
      fprintf(stream, "/// @brief Union of values from member types \"%s\".\n", simpleType.union_->memberTypes);
      if (t)
        fprintf(stream, "typedef %s %s;\n\n", s, t);
      else
      {
        fprintf(stream, elementformat, s, "");
        fprintf(stream, "\n");
      }
    }
    else if (!simpleType.union_->simpleType.empty())
    {
      const char *s = tname(NULL, NULL, "xsd:string");
      if (!anonymous)
        t = deftname(TYPEDEF, false, is_ptr(NULL, NULL, "xsd:string"), prefix, URI, name);
      for (vector<xs__simpleType>::const_iterator simpleType1 = simpleType.union_->simpleType.begin(); simpleType1 != simpleType.union_->simpleType.end(); ++simpleType1)
      {
        if ((*simpleType1).restriction)
        {
          fprintf(stream, "/// @brief Union of values from type \"%s\".\n", (*simpleType1).restriction->base);
          // TODO: are there any other types we should report here?
        }
      }
      if (t)
        fprintf(stream, "typedef %s %s;\n\n", s, t);
      else
      {
        fprintf(stream, elementformat, s, "");
        fprintf(stream, "\n");
      }
    }
    else
      fprintf(stream, "//\tunrecognized\n");
  }
  else
    fprintf(stream, "//\tunrecognized simpleType\n");
}

void Types::gen(const char *URI, const char *name, const xs__complexType& complexType, bool anonymous)
{
  const char *t = NULL;
  const char *prefix = NULL;
  bool soapflag = false;
  if (complexType.name)
    name = complexType.name;
  else
    prefix = "_";
  if (anonymous && name)
    t = sname(URI, name);
  else if (name)
  {
    t = cname(prefix, URI, name);
    if (deftypemap[t])
      return;
  }
  if (name)
    scope.push_back(name);
  if (complexType.simpleContent)
  {
    if (!anonymous)
      fprintf(stream, "/// @brief \"%s\":%s is a%s complexType with simpleContent.\n///\n", URI ? URI : "", name, complexType.abstract ? "n abstract" : "");
    document(complexType.annotation);
    if (!complexType.assert.empty())
    {
      fprintf(stream, "/// Assertions:\n");
      for (std::vector<xs__assert>::const_iterator a = complexType.assert.begin(); a != complexType.assert.end(); ++a)
        if ((*a).test)
          documentation((*a).test);
    }
    operations(t);
    if (complexType.simpleContent->restriction)
    {
      if (anonymous)
      {
        if (cflag)
          fprintf(stream, "    struct %s\n    {\n", t);
        else
          fprintf(stream, "    class %s\n    {\n", t);
      }
      else if (cflag)
        fprintf(stream, "struct %s\n{\n", t);
      else if (pflag && complexType.name)
        fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", t);
      else
        fprintf(stream, "class %s\n{ public:\n", t);
      const char *base = "xs:string";
      const char *baseURI = NULL;
      const xs__complexType *p = &complexType;
      do
      {
        if (!p->simpleContent)
          break;
        if (p->simpleContent->restriction)
        {
          if (p->simpleContent->restriction->complexTypePtr())
            p = p->simpleContent->restriction->complexTypePtr();
          else
          {
            base = p->simpleContent->restriction->base;
            if (p->simpleContent->restriction->simpleTypePtr() && p->simpleContent->restriction->simpleTypePtr()->schemaPtr())
              baseURI = p->simpleContent->restriction->simpleTypePtr()->schemaPtr()->targetNamespace;
            break;
          }
        }
        else if (p->simpleContent->extension)
        {
          if (p->simpleContent->extension->complexTypePtr())
            p = p->simpleContent->extension->complexTypePtr();
          else
          {
            base = p->simpleContent->extension->base;
            if (p->simpleContent->extension->simpleTypePtr() && p->simpleContent->extension->simpleTypePtr()->schemaPtr())
              baseURI = p->simpleContent->extension->simpleTypePtr()->schemaPtr()->targetNamespace;
            break;
          }
        }
        else
          break;
      }
      while (p);
      fprintf(stream, "/// __item wraps \"%s\" simpleContent.\n", base);
      fprintf(stream, elementformat, tname(NULL, baseURI, base), "__item");
      fprintf(stream, ";\n");
      p = &complexType;
      bool flag = true;
      do
      {
        if (!p->simpleContent)
          break;
        if (p->simpleContent->restriction)
        {
          // TODO: should only generate attribute when name is different?
          gen(URI, p->simpleContent->restriction->attribute);
          if (p->simpleContent->restriction->anyAttribute && flag)
          {
            gen(URI, *p->simpleContent->restriction->anyAttribute);
            flag = false;
          }
          if (p->simpleContent->restriction->complexTypePtr())
            p = p->simpleContent->restriction->complexTypePtr();
          else
            break;
        }
        else if (p->simpleContent->extension)
        {
          gen(URI, p->simpleContent->extension->attribute);
          gen(URI, p->simpleContent->extension->attributeGroup);
          if (p->simpleContent->extension->anyAttribute && flag)
          {
            gen(URI, *p->simpleContent->extension->anyAttribute);
            flag = false;
          }
          if (p->simpleContent->extension->complexTypePtr())
            p = p->simpleContent->extension->complexTypePtr();
          else
            break;
        }
        else
          break;
      }
      while (p);
    }
    else if (complexType.simpleContent->extension)
    {
      const char *base = "xs:string";
      const char *baseURI = NULL;
      if (cflag || fflag || anonymous)
      {
        if (anonymous)
        {
          if (cflag)
            fprintf(stream, "    struct %s\n    {\n", t);
          else
            fprintf(stream, "    class %s\n    {\n", t);
        }
        else if (cflag)
          fprintf(stream, "struct %s\n{\n", t);
        else if (pflag && complexType.name)
          fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", t);
        else
          fprintf(stream, "class %s\n{ public:\n", t);
        const xs__complexType *p = &complexType;
        do
        {
          if (!p->simpleContent)
            break;
          if (p->simpleContent->restriction)
          {
            if (p->simpleContent->restriction->complexTypePtr())
              p = p->simpleContent->restriction->complexTypePtr();
            else
            {
              base = p->simpleContent->restriction->base;
              if (p->simpleContent->restriction->simpleTypePtr() && p->simpleContent->restriction->simpleTypePtr()->schemaPtr())
                baseURI = p->simpleContent->restriction->simpleTypePtr()->schemaPtr()->targetNamespace;
              break;
            }
          }
          else if (p->simpleContent->extension)
          {
            if (p->simpleContent->extension->complexTypePtr())
              p = p->simpleContent->extension->complexTypePtr();
            else
            {
              base = p->simpleContent->extension->base;
              if (p->simpleContent->extension->simpleTypePtr() && p->simpleContent->extension->simpleTypePtr()->schemaPtr())
                baseURI = p->simpleContent->extension->simpleTypePtr()->schemaPtr()->targetNamespace;
              break;
            }
          }
          else
            break;
        }
        while (p);
        fprintf(stream, "/// __item wraps \"%s\" simpleContent.\n", base);
        fprintf(stream, elementformat, tname(NULL, baseURI, base), "__item");
        fprintf(stream, ";\n");
        p = &complexType;
        bool flag = true;
        do
        {
          if (!p->simpleContent)
            break;
          if (p->simpleContent->restriction)
          {
            gen(URI, p->simpleContent->restriction->attribute);
            if (p->simpleContent->restriction->anyAttribute && flag)
              gen(URI, *p->simpleContent->restriction->anyAttribute);
            break;
          }
          else if (p->simpleContent->extension)
          {
            gen(URI, p->simpleContent->extension->attribute);
            gen(URI, p->simpleContent->extension->attributeGroup);
            if (p->simpleContent->extension->anyAttribute && flag)
            {
              gen(URI, *p->simpleContent->extension->anyAttribute);
              flag = false;
            }
            if (p->simpleContent->extension->complexTypePtr())
              p = p->simpleContent->extension->complexTypePtr();
            else
              break;
          }
          else
            break;
        }
        while (p);
      }
      else
      {
        base = complexType.simpleContent->extension->base;
        if (
        /* TODO: in future, may want to add check here for base type == class
          complexType.simpleContent->extension->simpleTypePtr()
          ||
        */
          complexType.simpleContent->extension->complexTypePtr())
        {
          if (complexType.simpleContent->extension->complexTypePtr()->schemaPtr())
            baseURI = complexType.simpleContent->extension->complexTypePtr()->schemaPtr()->targetNamespace;
          fprintf(stream, "class %s : public %s\n{ public:\n", t, cname(NULL, baseURI, base));
          soapflag = true;
        }
        else
        {
          if (complexType.simpleContent->extension->simpleTypePtr() && complexType.simpleContent->extension->simpleTypePtr()->schemaPtr())
            baseURI = complexType.simpleContent->extension->simpleTypePtr()->schemaPtr()->targetNamespace;
          else if (complexType.simpleContent->extension->complexTypePtr() && complexType.simpleContent->extension->complexTypePtr()->schemaPtr())
            baseURI = complexType.simpleContent->extension->complexTypePtr()->schemaPtr()->targetNamespace;
          if (pflag && complexType.name)
            fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", t);
          else
            fprintf(stream, "class %s\n{ public:\n", t);
          fprintf(stream, "/// __item wraps \"%s\" simpleContent.\n", base);
          fprintf(stream, elementformat, tname(NULL, baseURI, base), "__item");
          fprintf(stream, ";\n");
        }
        gen(URI, complexType.simpleContent->extension->attribute);
        gen(URI, complexType.simpleContent->extension->attributeGroup);
        if (complexType.simpleContent->extension->anyAttribute)
          gen(URI, *complexType.simpleContent->extension->anyAttribute);
      }
    }
    else
      fprintf(stream, "//\tunrecognized\n");
  }
  else if (complexType.complexContent)
  {
    if (complexType.complexContent->restriction)
    {
      if (!anonymous)
        fprintf(stream, "/// @brief \"%s\":%s is a%s complexType with complexContent restriction of XSD type %s.\n///\n", URI ? URI : "", name, complexType.abstract ? "n abstract" : "", complexType.complexContent->restriction->base);
      document(complexType.annotation);
      document(complexType.complexContent->annotation);
      document(complexType.complexContent->restriction->annotation);
      if (!complexType.assert.empty())
      {
        fprintf(stream, "/// Assertions:\n");
        for (std::vector<xs__assert>::const_iterator a = complexType.assert.begin(); a != complexType.assert.end(); ++a)
          if ((*a).test)
            documentation((*a).test);
      }
      if (!complexType.complexContent->restriction->assert.empty())
      {
        fprintf(stream, "/// Assertions on restriction:\n");
        for (std::vector<xs__assert>::const_iterator a = complexType.complexContent->restriction->assert.begin(); a != complexType.complexContent->restriction->assert.end(); ++a)
          if ((*a).test)
            documentation((*a).test);
      }
      operations(t);
      if (!strcmp(complexType.complexContent->restriction->base, "SOAP-ENC:Array"))
      {
        char *item = NULL, *type = NULL;
        if (!complexType.complexContent->restriction->attribute.empty())
        {
          xs__attribute& attribute = complexType.complexContent->restriction->attribute.front();
          if (attribute.wsdl__arrayType)
            type = attribute.wsdl__arrayType;
        }
        xs__seqchoice *s = complexType.complexContent->restriction->sequence;
        if (s
         && !s->__contents.empty()
         && s->__contents.front().__union == SOAP_UNION_xs__union_content_element
         && s->__contents.front().__content.element)
        {
          xs__element& element = *s->__contents.front().__content.element;
          if (!type)
          {
            if (element.type)
              type = element.type;
            else if (element.simpleTypePtr())
            {
              if (element.simpleTypePtr()->name)
                type = element.simpleTypePtr()->name;
              else if (element.simpleTypePtr()->restriction)
                type = element.simpleTypePtr()->restriction->base;
            }
            else if (element.complexTypePtr())
            {
              if (element.complexTypePtr()->name)
                type = element.complexTypePtr()->name;
              else if (element.complexTypePtr()->complexContent && element.complexTypePtr()->complexContent->restriction)
                type = element.complexTypePtr()->complexContent->restriction->base;
            }
          }
          item = element.name; // <sequence><element name="item" type="..."/></sequence>
        }
        gen_soap_array(t, item, type);
      }
      else
      {
        if (anonymous)
        {
          if (cflag)
            fprintf(stream, "    struct %s\n    {\n", t);
          else
            fprintf(stream, "    class %s\n    {\n", t);
        }
        else if (cflag)
          fprintf(stream, "struct %s\n{\n", t);
        else if (pflag && complexType.name)
          fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", t);
        else
          fprintf(stream, "class %s\n{ public:\n", t);
        if (complexType.complexContent->restriction->group)
          gen(URI, *complexType.complexContent->restriction->group, NULL, NULL);
        if (complexType.complexContent->restriction->all)
          gen(URI, *complexType.complexContent->restriction->all, NULL, NULL);
        if (complexType.complexContent->restriction->sequence)
          gen(URI, *complexType.complexContent->restriction->sequence, NULL, NULL);
        if (complexType.complexContent->restriction->choice)
          gen(URI, name, *complexType.complexContent->restriction->choice, NULL, NULL);
        gen(URI, complexType.complexContent->restriction->attribute);
        bool flag = true;
        if (complexType.complexContent->restriction->anyAttribute)
        {
          gen(URI, *complexType.complexContent->restriction->anyAttribute);
          flag = false;
        }
        const xs__complexType *p = complexType.complexContent->restriction->complexTypePtr();
        while (p)
        {
          const char *pURI;
          if (p->schemaPtr())
            pURI = p->schemaPtr()->targetNamespace;
          else
            pURI = URI;
          const char *b = cname(NULL, pURI, p->name);
          if (zflag && zflag <= 5)
            fprintf(stream, "/// RESTRICTED FROM %s:\n", b);
          else if (comment_nest == 0)
            fprintf(stream, "/*  RESTRICTED FROM %s:\n", b);
          else
            fprintf(stream, "    RESTRICTED FROM %s:\n", b);
          comment_nest++;
          if (p->complexContent && p->complexContent->restriction)
          {
            gen(URI, p->complexContent->restriction->attribute);
            if (p->complexContent->restriction->anyAttribute && flag)
            {
              gen(URI, *p->complexContent->restriction->anyAttribute);
              flag = false;
            }
            p = p->complexContent->restriction->complexTypePtr();
          }
          else if (p->complexContent && p->complexContent->extension)
          {
            gen(URI, p->complexContent->extension->attribute);
            gen(URI, p->complexContent->extension->attributeGroup);
            if (p->complexContent->extension->anyAttribute && flag)
            {
              gen(URI, *p->complexContent->extension->anyAttribute);
              flag = false;
            }
            p = p->complexContent->extension->complexTypePtr();
          }
          else
          {
            gen(URI, p->attribute);
            gen(URI, p->attributeGroup);
            if (p->anyAttribute && flag)
              gen(URI, *p->anyAttribute);
            p = NULL;
          }
          comment_nest--;
          if (zflag && zflag <= 5)
            fprintf(stream, "//  END OF RESTRICTED FROM %s\n", b);
          else if (comment_nest == 0)
            fprintf(stream, "    END OF RESTRICTED FROM %s */\n", b);
          else
            fprintf(stream, "    END OF RESTRICTED FROM %s\n", b);
        }
      }
    }
    else if (complexType.complexContent->extension)
    {
      const char *base = complexType.complexContent->extension->base;
      xs__complexType *p = complexType.complexContent->extension->complexTypePtr();
      if (!anonymous)
        fprintf(stream, "/// @brief \"%s\":%s is a%s complexType with complexContent extension of XSD type %s.\n///\n", URI ? URI : "", name, complexType.abstract ? "n abstract" : "", base);
      document(complexType.annotation);
      document(complexType.complexContent->annotation);
      document(complexType.complexContent->extension->annotation);
      if (!complexType.assert.empty())
      {
        fprintf(stream, "/// Assertions:\n");
        for (std::vector<xs__assert>::const_iterator a = complexType.assert.begin(); a != complexType.assert.end(); ++a)
          if ((*a).test)
            documentation((*a).test);
      }
      if (!complexType.complexContent->extension->assert.empty())
      {
        fprintf(stream, "/// Assertions on extension:\n");
        for (std::vector<xs__assert>::const_iterator a = complexType.complexContent->extension->assert.begin(); a != complexType.complexContent->extension->assert.end(); ++a)
          if ((*a).test)
            documentation((*a).test);
      }
      operations(t);
      if (anonymous)
      {
        if (cflag)
          fprintf(stream, "    struct %s\n    {\n", t);
        else
          fprintf(stream, "    class %s\n    {\n", t);
      }
      else if (cflag)
        fprintf(stream, "struct %s\n{\n", t);
      else if (fflag)
        fprintf(stream, "class %s\n{ public:\n", t);
      else // TODO: what to do if base class is in another namespace and elements must be qualified in XML payload?
      {
        const char *baseURI = NULL;
        if (p && p->schemaPtr())
          baseURI = p->schemaPtr()->targetNamespace;
        fprintf(stream, "class %s : public %s\n{ public:\n", t, cname(NULL, baseURI, base));
        soapflag = true;
      }
      gen_inh(URI, p, anonymous);
      if (complexType.complexContent->extension->group)
        gen(URI, *complexType.complexContent->extension->group, NULL, NULL);
      if (complexType.complexContent->extension->all)
        gen(URI, *complexType.complexContent->extension->all, NULL, NULL);
      if (complexType.complexContent->extension->sequence)
        gen(URI, *complexType.complexContent->extension->sequence, NULL, NULL);
      if (complexType.complexContent->extension->choice)
        gen(URI, name, *complexType.complexContent->extension->choice, NULL, NULL);
      gen(URI, complexType.complexContent->extension->attribute);
      gen(URI, complexType.complexContent->extension->attributeGroup);
      if (complexType.complexContent->extension->anyAttribute)
        gen(URI, *complexType.complexContent->extension->anyAttribute);
    }
    else
      fprintf(stream, "//\tunrecognized\n");
  }
  else
  {
    if (!anonymous)
      fprintf(stream, "/// @brief \"%s\":%s is a%s complexType.\n///\n", URI ? URI : "", name, complexType.abstract ? "n abstract" : "");
    document(complexType.annotation);
    operations(t);
    if (anonymous)
    {
      if (cflag)
        fprintf(stream, "    struct %s\n    {\n", t);
      else
        fprintf(stream, "    class %s\n    {\n", t);
    }
    else if (cflag)
      fprintf(stream, "struct %s\n{\n", t);
    else if (pflag && complexType.name)
      fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", t);
    else
      fprintf(stream, "class %s\n{ public:\n", t);
    if (complexType.all)
      gen(URI, *complexType.all, NULL, NULL);
    else if (complexType.choice)
      gen(URI, name, *complexType.choice, NULL, NULL);
    else if (complexType.sequence)
      gen(URI, *complexType.sequence, NULL, NULL);
    else if (complexType.group)
      gen(URI, *complexType.group, NULL, NULL);
    else if (complexType.any)
      gen(URI, *complexType.any, NULL, NULL);
  }
  if (!(complexType.complexContent && complexType.complexContent->extension) && complexType.defaultAttributesApply && complexType.schemaPtr() && complexType.schemaPtr()->attributeGroupPtr())
  {
    fprintf(stream, "/// Default attributes \"%s\"\n", complexType.schemaPtr()->defaultAttributes);
    xs__attributeGroup *a = complexType.schemaPtr()->attributeGroupPtr();
    if (a->attributeGroupPtr())
      a = a->attributeGroupPtr();
    gen(URI, a->attribute);
    gen(URI, a->attributeGroup);
    if (a->anyAttribute)
      gen(URI, *a->anyAttribute);
  }
  gen(URI, complexType.attribute);
  gen(URI, complexType.attributeGroup);
  if (complexType.anyAttribute)
    gen(URI, *complexType.anyAttribute);
  if (complexType.mixed
   || (   complexType.complexContent
       && (
              complexType.complexContent->mixed
           || (   complexType.complexContent->extension
               && complexType.complexContent->extension->complexTypePtr()
               && complexType.complexContent->extension->complexTypePtr()->mixed
              )
          )
      ))
  {
    fprintf(stream, "/// @todo This mixed content complexType is user-definable.\n///       Consult the protocol documentation to change or insert declarations.\n///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element).\n");
    if (dflag)
    {
      if (with_union)
        fprintf(stream, pointerformat, "xsd__anyType", "__mixed");
      else
        fprintf(stream, elementformat, "xsd__anyType", "__mixed");
      fprintf(stream, "0;\t///< Catch mixed content in DOM soap_dom_element linked node structure.\n");
    }
    else
    {
      fprintf(stream, elementformat, "_XML", "__mixed");
      fprintf(stream, "0;\t///< Catch mixed content in XML string.\n");
    }
  }
  if (t)
    modify(t);
  if (!anonymous)
  {
    if (!cflag
     && !(pflag && complexType.name)
     && !soapflag)
    {
      if (!complexType.complexContent || !complexType.complexContent->extension || !complexType.complexContent->extension->complexTypePtr())
      {
        fprintf(stream, "/// A handle to the soap struct context that manages this instance when instantiated by a context or NULL otherwise (automatically set).\n");
        fprintf(stream, pointerformat, "struct soap", "soap");
        fprintf(stream, ";\n");
      }
    }
    fprintf(stream, "};\n\n");
  }
  scope.pop_back();
}

void Types::gen(const char *URI, const vector<xs__attribute>& attributes)
{
  for (vector<xs__attribute>::const_iterator attribute = attributes.begin(); attribute != attributes.end(); ++attribute)
    gen(URI, *attribute);
}

void Types::gen(const char *URI, const xs__attribute& attribute)
{
  const char *name = attribute.name;
  const char *type = attribute.type;
  const char *default_ = attribute.default_;
  const char *default__ = attribute.default__;
  const char *fixed = attribute.fixed;
  const char *fixed_ = attribute.fixed_;
  const char *nameURI = NULL, *typeURI = NULL, *nameprefix = NULL, *typeprefix = NULL;
  bool is_optional = attribute.use != required && !default_;
  document(attribute.annotation);
  if (!URI)
    URI = attribute.schemaPtr()->targetNamespace;
  if (attribute.targetNamespace)
  {
    if ((attribute.form && *attribute.form == qualified) || attribute.schemaPtr()->attributeFormDefault == qualified)
      nameURI = attribute.targetNamespace;
    else
      nameprefix = ":";
  }
  else if (!attribute.ref && URI && attribute.schemaPtr() && attribute.schemaPtr()->targetNamespace && strcmp(URI, attribute.schemaPtr()->targetNamespace))
  {
    if ((attribute.form && *attribute.form == qualified) || attribute.schemaPtr()->attributeFormDefault == qualified)
      nameURI = attribute.schemaPtr()->targetNamespace; // handles attributes defined in another namespace
    else
      nameprefix = ":";
  }
  else if (attribute.form)
  {
    if (*attribute.form == qualified)
      nameURI = URI;
    else
      nameprefix = ":";
  }
  if (attribute.attributePtr()) // attribute ref
  {
    name = attribute.attributePtr()->name;
    type = attribute.attributePtr()->type;
    if (!default_)
    {
      default_ = attribute.attributePtr()->default_;
      default__ = attribute.attributePtr()->default__;
    }
    if (!fixed)
    {
      fixed = attribute.attributePtr()->fixed;
      fixed_ = attribute.attributePtr()->fixed_;
    }
    if (default_)
      is_optional = false;
    else if (is_optional)
      is_optional = attribute.attributePtr()->use != required;
    if (!type)
    {
      type = name;
      typeprefix = "_";
    }
    if (attribute.attributePtr()->schemaPtr())
    {
      typeURI = attribute.attributePtr()->schemaPtr()->targetNamespace;
      if (attribute.form && *attribute.form == unqualified)
        nameprefix = ":";
      else if (zflag != 3 && zflag != 2
       && URI
       && typeURI
       && attribute.schemaPtr()->attributeFormDefault == qualified
       && !strcmp(URI, typeURI))
        nameprefix = NULL;
      else if (zflag == 3
       && URI
       && typeURI
       && attribute.schemaPtr()->attributeFormDefault == unqualified
       && !strcmp(URI, typeURI))
        nameprefix = NULL;
      else
        nameURI = typeURI;
    }
    if (attribute.ref)
      fprintf(stream, "/// Attribute reference \"%s\":%s.\n", attribute.schemaPtr()->targetNamespace, attribute.ref);
    document(attribute.attributePtr()->annotation);
    fprintf(stream, attributeformat, pname(is_optional, true, typeprefix, typeURI, type), aname(nameprefix, nameURI, name)); // make sure no name - type clash
  }
  else if (name && type)
  {
    fprintf(stream, "/// Attribute \"%s\" of XSD type %s.\n", name, type);
    fprintf(stream, attributeformat, pname(is_optional, true, NULL, URI, type), aname(nameprefix, nameURI, name)); // make sure no name - type clash
  }
  else if (name && attribute.simpleTypePtr())
  {
    const char *s = "";
    const char *r = NULL;
    if (!cflag && is_optional && (r = vname("$POINTER")) && *r != '*' && *r != '$')
    {
      s = ">";
      fprintf(stream, attrtemplateformat_open, r, "\n");
    }
    else
      fprintf(stream, "@");
    gen(URI, name, *attribute.simpleTypePtr(), true, false);
    if (r && *r != '*' && *r != '$')
      fprintf(stream, elementformat, s, aname(nameprefix, nameURI, name));
    else if (is_optional)
      fprintf(stream, pointerformat, s, aname(nameprefix, nameURI, name));
    else
      fprintf(stream, elementformat, s, aname(nameprefix, nameURI, name));
  }
  else if (attribute.ref)
  {
    fprintf(stream, "/// Imported attribute reference %s.\n", attribute.ref);
    fprintf(stream, attributeformat, pname(is_optional, true, "_", NULL, attribute.ref), aname(NULL, NULL, attribute.ref));
  }
  else
  {
    fprintf(stream, "/// Attribute \"%s\" has no type or ref: assuming string content.\n", name ? name : "");
    fprintf(stream, attributeformat, tname(NULL, NULL, "xs:string"), aname(NULL, nameURI, name));
  }
  switch (attribute.use)
  {
    case prohibited:
      fprintf(stream, " 0:0");
      break;
    case required:
      fprintf(stream, " 1");
      break;
    default:
      if (is_optional || default_)
        fprintf(stream, " 0");
      break;
  }
  if (default_)
  {
    const char *value, *QName;
    value = default_;
    QName = default__;
    const char *t = NULL;
    if (!type && attribute.simpleTypePtr())
    {
      if (attribute.simpleTypePtr()->restriction && attribute.simpleTypePtr()->restriction->base)
      {
        if (!attribute.simpleTypePtr()->restriction->enumeration.empty())
        {
          const char *s;
          if (is_integer(value))
            fprintf(stream, " = %s", value);
          else if (!*value)
            fprintf(stream, " = 0");
          else if ((s = enames[Pair(gname(URI, name),value)]))
            fprintf(stream, " = %s", s);
        }
        else
        {
          const char *baseURI = NULL;
          if (attribute.simpleTypePtr()->restriction->simpleTypePtr() && attribute.simpleTypePtr()->restriction->simpleTypePtr()->schemaPtr())
            baseURI = attribute.simpleTypePtr()->restriction->simpleTypePtr()->schemaPtr()->targetNamespace;
          t = tname(NULL, baseURI, attribute.simpleTypePtr()->restriction->base);
        }
      }
    }
    if (type && !t)
      t = tname(NULL, typeURI ? typeURI : URI, type);
    if (t)
    {
      if (!strncmp(t, "unsigned ", 9))
        t += 9;
      else if (!strncmp(t, "xsd__unsigned", 13))
        t += 13;
      else if (!strncmp(t, "xsd__", 5))
        t += 5;
      if (!strcmp(t, "bool")
       || !strcmp(t, "byte")
       || !strcmp(t, "Byte")
       || !strcmp(t, "char")
       || !strcmp(t, "double")
       || !strcmp(t, "float")
       || !strcmp(t, "int")
       || !strcmp(t, "Int")
       || !strcmp(t, "long")
       || !strcmp(t, "Long")
       || !strcmp(t, "LONG64")
       || !strcmp(t, "short")
       || !strcmp(t, "Short")
       || !strcmp(t, "ULONG64"))
        fprintf(stream, " = %s", value);
      else if (!strncmp(t, "enum ", 5))
      {
        const char *s;
        if (is_integer(value))
          fprintf(stream, " = %s", value);
        else if (!*value)
          fprintf(stream, " = 0");
        else if ((s = enames[Pair(t + 5,value)]))
          fprintf(stream, " = %s", s);
      }
      else if (!strncmp(t, "char", 4)
            || !strncmp(t, "const char", 10)
            || !strncmp(t, "wchar_t", 7)
            || !strncmp(t, "const wchar_t", 13)
            || !strncmp(t, "std::string", 11))
        fprintf(stream, " = \"%s\"", cstring(value));
      else if (!strcmp(t, "xsd__QName") && QName)       // QName
        fprintf(stream, " = \"%s\"", cstring(QName));
    }
    fprintf(stream, ";\t///< Default attribute value=\"%s\".\n", value);
  }
  else if (fixed)
    fprintf(stream, ";\t///< Fixed attribute value=\"%s\".\n", fixed);
  else if (attribute.use == required)
    fprintf(stream, ";\t///< Required attribute.\n");
  else if (attribute.use == prohibited)
    fprintf(stream, ";\t///< Prohibited attribute.\n");
  else
    fprintf(stream, ";\t///< Optional attribute.\n");
}

void Types::gen(const char *URI, const vector<xs__attributeGroup>& attributeGroups)
{
  for (vector<xs__attributeGroup>::const_iterator attributeGroup = attributeGroups.begin(); attributeGroup != attributeGroups.end(); ++attributeGroup)
  {
    static set<const xs__attributeGroup*> visited;
    const xs__attributeGroup *p = &*attributeGroup;
    if (visited.find(p) != visited.end())
    {
      if (p->ref)
        fprintf(stderr, "\nWarning: circular attributeGroup <xs:attributeGroup ref=\"%s\"/>\n", p->ref);
      else
        fprintf(stderr, "\nWarning: circular attributeGroup <xs:attributeGroup name=\"%s\"/>\n", p->name ? p->name : "");
      fprintf(stream, "/// @todo !FIXME! @warning %s is an attributeGroup with a circular reference.\n", p->ref ? p->ref : p->name ? p->name : "");
      return;
    }
    visited.insert(p);
    const char *pURI = URI;
    if (p->ref) // attributeGroup ref
      fprintf(stream, "//  BEGIN ATTRIBUTEGROUP <xs:attributeGroup ref=\"%s\">.\n", p->ref ? p->ref : "");
    else
      fprintf(stream, "//  BEGIN ATTRIBUTEGROUP <xs:attributeGroup name=\"%s\">.\n", p->name ? p->name : "");
    if (p->attributeGroupPtr())
    {
      gen(pURI, p->attributeGroupPtr()->attribute);
      gen(pURI, p->attributeGroupPtr()->attributeGroup);
    }
    else
    {
      gen(pURI, p->attribute);
      gen(pURI, p->attributeGroup);
    }
    if (p->anyAttribute)
      gen(pURI, *p->anyAttribute);
    fprintf(stream, "//  END OF ATTRIBUTEGROUP\n");
    visited.erase(p);
  }
}

void Types::gen(const char *URI, const vector<xs__all>& alls)
{
  for (vector<xs__all>::const_iterator all = alls.begin(); all != alls.end(); ++all)
    gen(URI, *all, NULL, NULL);
}

void Types::gen(const char *URI, const xs__all& all, const char *minOccurs, const char *maxOccurs)
{
  bool tmp_union1 = with_union;
  bool tmp_union2 = fake_union;
  with_union = false;
  fake_union = false;
  gen(URI, all.element, minOccurs, maxOccurs);
  with_union = tmp_union1;
  fake_union = tmp_union2;
}

void Types::gen(const char *URI, const vector<xs__contents>& contents)
{
  for (vector<xs__contents>::const_iterator content = contents.begin(); content != contents.end(); ++content)
  {
    switch ((*content).__union)
    {
      case SOAP_UNION_xs__union_content_element:
        if ((*content).__content.element)
          gen(URI, *(*content).__content.element, true, NULL, NULL);
        break;
      case SOAP_UNION_xs__union_content_group:
        if ((*content).__content.group)
          gen(URI, *(*content).__content.group, NULL, NULL);
        break;
      case SOAP_UNION_xs__union_content_choice:
        if ((*content).__content.choice)
          gen(URI, NULL, *(*content).__content.choice, NULL, NULL);
        break;
      case SOAP_UNION_xs__union_content_sequence:
        if ((*content).__content.sequence)
          gen(URI, *(*content).__content.sequence, NULL, NULL);
        break;
      case SOAP_UNION_xs__union_content_any:
        if ((*content).__content.any)
          gen(URI, *(*content).__content.any, NULL, NULL);
        break;
    }
  }
}

void Types::gen(const char *URI, const xs__seqchoice& sequence, const char *minOccurs, const char *maxOccurs)
{
  const char *s = NULL;
  const char *min = minOccurs;
  const char *max = maxOccurs;
  char *t = NULL;
  bool tmp_union = with_union;
  with_union = false;
  if (sequence.minOccurs)
    min = sequence.minOccurs;
  if (sequence.maxOccurs)
    max = sequence.maxOccurs;
  if ((min && strcmp(min, "1"))
   || (max && strcmp(max, "1")))
  {
    fprintf(stream, "//  BEGIN SEQUENCE <xs:sequence");
    if (min)
      fprintf(stream, " minOccurs=\"%s\"", min);
    if (max)
      fprintf(stream, " maxOccurs=\"%s\"", max);
    fprintf(stream, ">\n");
    document(sequence.annotation);
    s = sname(URI, "sequence");
    size_t l = strlen(s);
    t = (char*)emalloc(l + 2);
    soap_strcpy(t, l + 2, "_");
    soap_strcpy(t + 1, l + 1, s);
    s = strstr(s, "__");
    if (!s)
      s = t;
    if (max && strcmp(max, "1"))
    {
      if (cflag || sflag || zflag == 2)
      {
        fprintf(stream, sizeformat, "int", s + 1);
        if (!fake_union && min)
          fprintf(stream, " %s", min);
        if (max
         && strcmp(max, "1")
         && is_integer(max))
          fprintf(stream, ":%s", max);
        fprintf(stream, ";\n");
      }
      else
      {
        fprintf(stream, templateformat_open, vname("$CONTAINER"), "\n");
      }
    }
    if (cflag)
      fprintf(stream, "    struct %s\n    {\n", t);
    else
      fprintf(stream, "    class %s\n    {\n", t);
  }
  else
  {
    if (fake_union)
      fprintf(stream, "//  BEGIN SEQUENCE <xs:sequence>\n");
    document(sequence.annotation);
  }
  gen(URI, sequence.__contents);
  if (s)
  {
    if (max && strcmp(max, "1"))
    {
      if (cflag || sflag || zflag == 2)
        fprintf(stream, pointerformat, "}", s);
      else
      {
        fprintf(stream, elementformat, "}>", s);
        if (!fake_union && min)
          fprintf(stream, " %s", min);
        if (max
         && strcmp(max, "1")
         && is_integer(max))
          fprintf(stream, ":%s", max);
      }
    }
    else
    {
      fprintf(stream, pointerformat, "}", s);
      if (!fake_union && min)
        fprintf(stream, " %s", min);
    }
    fprintf(stream, ";\n");
  }
  if (s || fake_union)
    fprintf(stream, "//  END OF SEQUENCE\n");
  with_union = tmp_union;
}

void Types::gen(const char *URI, const vector<xs__element>& elements, const char *minOccurs, const char *maxOccurs)
{
  for (vector<xs__element>::const_iterator element = elements.begin(); element != elements.end(); ++element)
    gen(URI, *element, true, minOccurs, maxOccurs);
}

void Types::gen(const char *URI, const xs__element& element, bool substok, const char *minOccurs, const char *maxOccurs)
{
  const char *name = element.name;
  const char *type = element.type;
  const char *default_ = element.default_;
  const char *default__ = element.default__;
  const char *fixed = element.fixed;
  const char *fixed_ = element.fixed_;
  const char *min = minOccurs;
  const char *max = maxOccurs;
  bool nillable = element.nillable;
  const char *nameURI = NULL, *typeURI = NULL, *nameprefix = NULL, *typeprefix = NULL;
  document(element.annotation);
  if (!URI)
    URI = element.schemaPtr()->targetNamespace;
  if (element.minOccurs)
    min = element.minOccurs;
  if (element.maxOccurs)
    max = element.maxOccurs;
  if (element.xmime__expectedContentTypes)
    fprintf(stream, "/// MTOM attachment with content types %s.\n", element.xmime__expectedContentTypes);
  if (element.targetNamespace)
  {
    if ((element.form && *element.form == qualified) || element.schemaPtr()->elementFormDefault == qualified)
      nameURI = element.targetNamespace;
    else
      nameprefix = ":";
  }
  else if (!element.ref && URI && element.schemaPtr() && element.schemaPtr()->targetNamespace && strcmp(URI, element.schemaPtr()->targetNamespace))
  {
    if ((element.form && *element.form == qualified) || element.schemaPtr()->elementFormDefault == qualified)
      nameURI = element.schemaPtr()->targetNamespace; // handles elements defined in another namespace
    else
      nameprefix = ":";
  }
  else if (element.form)
  {
    if (*element.form == qualified)
      nameURI = URI;
    else
      nameprefix = ":";
  }
  if (element.elementPtr()) // element ref (or ref to substitution element)
  {
    name = element.elementPtr()->name;
    type = element.elementPtr()->type;
    if (!max || !strcmp(max, "1"))
    {
      if (!default_)
      {
	default_ = element.elementPtr()->default_;
	default__ = element.elementPtr()->default__;
      }
      if (!fixed)
      {
	fixed = element.elementPtr()->fixed;
	fixed_ = element.elementPtr()->fixed_;
      }
    }
    if (!nillable)
      nillable = element.elementPtr()->nillable;
    if (!type)
    {
      type = name;
      typeprefix = "_";
    }
    if (element.elementPtr()->schemaPtr())
    {
      typeURI = element.elementPtr()->schemaPtr()->targetNamespace;
      if (element.form && *element.form == unqualified)
        nameprefix = ":";
      else if (zflag != 3 && zflag != 2
       && URI
       && typeURI
       && element.schemaPtr()->elementFormDefault == qualified
       && !strcmp(URI, typeURI))
        nameprefix = NULL;
      else if (zflag == 3
       && URI
       && typeURI
       && element.schemaPtr()->elementFormDefault == unqualified
       && !strcmp(URI, typeURI))
        nameprefix = NULL;
      else
        nameURI = typeURI;
    }
    document(element.elementPtr()->annotation);
    if (element.elementPtr()->xmime__expectedContentTypes)
      fprintf(stream, "/// MTOM attachment with content types %s.\n", element.elementPtr()->xmime__expectedContentTypes);
    if (substok && element.elementPtr()->abstract)
    {
      fprintf(stream, "/// Reference %s to abstract element.\n", element.ref);
      gen_substitutions(URI, element);
    }
    else if (substok
          && element.elementPtr()->substitutionsPtr()
          && !element.elementPtr()->substitutionsPtr()->empty())
    {
      if (vflag)
        fprintf(stderr, "\nWarning: element ref \"%s\" stands as the head of a substitutionGroup but is not declared abstract\n", element.ref);
      gen_substitutions(URI, element);
    }
    else if (max && strcmp(max, "1")) // maxOccurs != "1"
    {
      const char *s = tnameptr(cflag && zflag != 1, typeprefix, typeURI, type);
      if (cflag || sflag)
      {
        fprintf(stream, "/// Size of the dynamic array of %s is %s..%s.\n", s, min ? min : "1", max);
        fprintf(stream, sizeformat, "int", aname(NULL, NULL, name));
        fprintf(stream, " %s", fake_union ? "0" : min ? min : "1");
        if (is_integer(max))
          fprintf(stream, ":%s", max);
        fprintf(stream, ";\n");
        if (cflag && zflag != 1)
        {
          fprintf(stream, "/// Array %s of size %s..%s.\n", s, min ? min : "1", max);
          fprintf(stream, elementformat, s, aname(nameprefix, nameURI, name));
        }
        else
        {
          fprintf(stream, "/// Pointer to array %s of size %s..%s.\n", s, min ? min : "1", max);
          fprintf(stream, pointerformat, s, aname(nameprefix, nameURI, name));
        }
      }
      else
      {
        fprintf(stream, "/// Vector of %s element refs of length %s..%s.\n", s, min ? min : "1", max);
        if (with_union)
          fprintf(stream, pointertemplateformat, vname("$CONTAINER"), s, aname(nameprefix, nameURI, name));
        else
          fprintf(stream, templateformat, vname("$CONTAINER"), s, aname(nameprefix, nameURI, name));
      }
    }
    else
    {
      if (element.ref)
        fprintf(stream, "/// Element reference \"%s:\"%s.\n", element.schemaPtr()->targetNamespace, element.ref);
      else
        fprintf(stream, "/// Element \"%s\":%s.\n", element.schemaPtr()->targetNamespace, name);
      fprintf(stream, elementformat, pname((with_union && !is_choicetype(typeprefix, typeURI, type)) || ((fake_union || element.nillable || (is_nillable(element) && !(with_union && is_choicetype(typeprefix, typeURI, type)))) && !default_) || fixed, !with_union, typeprefix, typeURI, type), aname(nameprefix, nameURI, name));
    }
  }
  else if (name && type)
  {
    if (substok && element.abstract)
    {
      fprintf(stream, "/// Abstract element %s of XSD type %s.\n", name, type);
      gen_substitutions(URI, element);
    }
    else if (substok
          && element.substitutionsPtr()
          && !element.substitutionsPtr()->empty())
    {
      if (vflag)
        fprintf(stderr, "\nWarning: element \"%s\" stands as the head of a substitutionGroup but is not declared abstract\n", name);
      gen_substitutions(URI, element);
    }
    else if (max && strcmp(max, "1")) // maxOccurs != "1"
    {
      const char *s = tnameptr(cflag && zflag != 1, NULL, URI, type);
      if (cflag || sflag)
      {
        fprintf(stream, "/// Size of array of %s is %s..%s.\n", s, min ? min : "1", max);
        fprintf(stream, sizeformat, "int", aname(NULL, NULL, name));
        fprintf(stream, " %s", fake_union ? "0" : min ? min : "1");
        if (is_integer(max))
          fprintf(stream, ":%s", max);
        fprintf(stream, ";\n");
        if (cflag && zflag != 1)
        {
          fprintf(stream, "/// Array %s of size %s..%s.\n", s, min ? min : "1", max);
          fprintf(stream, elementformat, s, aname(nameprefix, nameURI, name));
        }
        else
        {
          fprintf(stream, "/// Pointer to array %s of size %s..%s.\n", s, min ? min : "1", max);
          fprintf(stream, pointerformat, s, aname(nameprefix, nameURI, name));
        }
      }
      else
      {
        fprintf(stream, "/// Vector of %s of length %s..%s.\n", s, min ? min : "1", max);
        if (with_union)
          fprintf(stream, pointertemplateformat, vname("$CONTAINER"), s, aname(nameprefix, nameURI, name));
        else
          fprintf(stream, templateformat, vname("$CONTAINER"), s, aname(nameprefix, nameURI, name));
      }
    }
    else
    {
      fprintf(stream, "/// Element \"%s\" of XSD type %s.\n", name, type);
      fprintf(stream, elementformat, pname((with_union && !is_choicetype(NULL, URI, type)) || ((fake_union || element.nillable || (is_nillable(element) && !(with_union && is_choicetype(NULL, URI, type)))) && !default_) || fixed, !with_union, NULL, URI, type), aname(nameprefix, nameURI, name));
    }
  }
  else if (name && element.simpleTypePtr())
  {
    const char *s = "";
    const char *r = NULL;
    document(element.simpleTypePtr()->annotation);
    if (max && strcmp(max, "1")) // maxOccurs != "1"
    {
      if (cflag || sflag)
      {
        fprintf(stream, "/// Size of %s array is %s..%s.\n", name, min ? min : "1", max);
        fprintf(stream, sizeformat, "int", aname(NULL, NULL, name));
        fprintf(stream, " %s", fake_union ? "0" : min ? min : "1");
        if (is_integer(max))
          fprintf(stream, ":%s", max);
        fprintf(stream, ";\n");
      }
      else
      {
        s = ">";
        fprintf(stream, "/// Vector of %s of length %s..%s.\n", name, min ? min : "1", max);
        fprintf(stream, templateformat_open, vname("$CONTAINER"), "\n");
      }
    }
    else if (!cflag && !with_union && (r = vname("$POINTER")) && *r != '*' && *r != '$')
    {
      if ((is_nillable(element) && !default_)
       || fixed
       || (fake_union && !default_))
      {
        s = ">";
        fprintf(stream, templateformat_open, r, "\n");
      }
    }
    gen(URI, name, *element.simpleTypePtr(), true, false);
    if (r && *r != '*' && *r != '$')
      fprintf(stream, elementformat, s, aname(nameprefix, nameURI, name));
    else if ((is_nillable(element) && !default_)
     || fixed
     || ((cflag || sflag) && max && strcmp(max, "1")) // maxOccurs != "1"
     || (with_union && !cflag)
     || (fake_union && !default_))
      fprintf(stream, pointerformat, s, aname(nameprefix, nameURI, name));
    else
      fprintf(stream, elementformat, s, aname(nameprefix, nameURI, name));
  }
  else if (name && element.complexTypePtr())
  {
    const char *s = "}";
    const char *r = NULL;
    document(element.complexTypePtr()->annotation);
    if (max && strcmp(max, "1")) // maxOccurs != "1"
    {
      if (cflag || sflag)
      {
        fprintf(stream, "/// Size of %s array is %s..%s.\n", name, min ? min : "1", max);
        fprintf(stream, sizeformat, "int", aname(NULL, NULL, name));
        fprintf(stream, " %s", fake_union ? "0" : min ? min : "1");
        if (is_integer(max))
          fprintf(stream, ":%s", max);
        fprintf(stream, ";\n");
      }
      else
      {
        s = "}>";
        fprintf(stream, "/// Vector of %s of length %s..%s.\n", name, min ? min : "1", max);
        fprintf(stream, templateformat_open, vname("$CONTAINER"), "\n");
      }
    }
    else if (!cflag && !with_union && (r = vname("$POINTER")) && *r != '*' && *r != '$')
    {
      if ((is_nillable(element) && !default_)
       || fixed
       || (fake_union && !default_))
      {
        s = "}>";
        fprintf(stream, templateformat_open, r, "\n");
      }
    }
    gen(URI, name, *element.complexTypePtr(), true);
    if (r && *r != '*' && *r != '$')
      fprintf(stream, elementformat, s, aname(nameprefix, nameURI, name));
    else if ((is_nillable(element) && !default_)
     || fixed
     || ((cflag || sflag) && max && strcmp(max, "1")) // maxOccurs != "1"
     || (with_union && !cflag)
     || (fake_union && !default_))
      fprintf(stream, pointerformat, s, aname(nameprefix, nameURI, name));
    else
      fprintf(stream, elementformat, s, aname(nameprefix, nameURI, name));
  }
  else if (element.ref)
  {
    fprintf(stream, "/// Imported element reference %s.\n", element.ref);
    if (max && strcmp(max, "1")) // maxOccurs != "1"
    {
      if (cflag || sflag)
      {
        fprintf(stream, "/// Size of %s array is %s..%s.\n", element.ref, min ? min : "1", max);
        fprintf(stream, sizeformat, "int", aname(NULL, NULL, element.ref));
        fprintf(stream, " %s", fake_union ? "0" : min ? min : "1");
        if (is_integer(max))
          fprintf(stream, ":%s", max);
        fprintf(stream, ";\n");
        fprintf(stream, pointerformat, pname(true, true, "_", NULL, element.ref), aname(nameprefix, nameURI, element.ref));
      }
      else
      {
        fprintf(stream, "/// Vector of %s of length %s..%s.\n", element.ref, min ? min : "1", max);
        fprintf(stream, templateformat, vname("$CONTAINER"), tname("_", NULL, element.ref), aname(nameprefix, nameURI, element.ref));
      }
    }
    else
      fprintf(stream, elementformat, pname((with_union && !cflag) || ((fake_union || is_nillable(element)) && !default_) || fixed, !with_union, "_", NULL, element.ref), aname(nameprefix, nameURI, element.ref));
  }
  else if (name)
  {
    fprintf(stream, "/// Element \"%s\" has no type or ref (empty or with XML content).\n", name ? name : "");
    if (max && strcmp(max, "1")) // maxOccurs != "1"
    {
      if (cflag || sflag)
      {
        fprintf(stream, sizeformat, "int", aname(NULL, NULL, name));
        fprintf(stream, " %s", fake_union ? "0" : min ? min : "1");
        if (is_integer(max))
          fprintf(stream, ":%s", max);
        fprintf(stream, ";\n");
        fprintf(stream, "/// Pointer to array of XML.\n");
        fprintf(stream, pointerformat, "_XML", aname(NULL, nameURI, name));
      }
      else
      {
        fprintf(stream, "/// Vector of XML of length %s..%s.\n", min ? min : "1", max);
        if (with_union)
          fprintf(stream, pointertemplateformat, vname("$CONTAINER"), "_XML", aname(NULL, nameURI, name));
        else
          fprintf(stream, templateformat, vname("$CONTAINER"), "_XML", aname(NULL, nameURI, name));
      }
    }
    else
      fprintf(stream, elementformat, "_XML", aname(NULL, nameURI, name));
  }
  else
    fprintf(stream, "/// Element has no name, type, or ref.\n");
  if (!substok
   || (   !(element.elementPtr() && element.elementPtr()->abstract)
       && !(element.substitutionsPtr() && !element.substitutionsPtr()->empty())
       && !(element.elementPtr() && element.elementPtr()->substitutionsPtr() && !element.elementPtr()->substitutionsPtr()->empty())
      ))
  {
    if (!fake_union && !min && (default_ || fixed))
      fprintf(stream, " 0");
    else if (!fake_union && !min && !element.abstract)
      fprintf(stream, " 1");
    else if (!fake_union && min)
      fprintf(stream, " %s", min);
    if (max && strcmp(max, "1") && is_integer(max))
      fprintf(stream, ":%s", max);
    if (default_)
    {
      // determine whether the element can be assigned a default value, this is dependent on the choice of mapping for primitive types
      const char *value, *QName;
      value = default_;
      QName = default__;
      if (type)
      {
        const char *t = tname(NULL, typeURI ? typeURI : URI, type);
        if (!strncmp(t, "unsigned ", 9))
          t += 9;
        else if (!strncmp(t, "xsd__unsigned", 13))
          t += 13;
        else if (!strncmp(t, "xsd__", 5))
          t += 5;
        if (!strcmp(t, "bool")
         || !strcmp(t, "byte")
         || !strcmp(t, "Byte")
         || !strcmp(t, "char")
         || !strcmp(t, "double")
         || !strcmp(t, "float")
         || !strcmp(t, "int")
         || !strcmp(t, "Int")
         || !strcmp(t, "long")
         || !strcmp(t, "Long")
         || !strcmp(t, "LONG64")
         || !strcmp(t, "short")
         || !strcmp(t, "Short")
         || !strcmp(t, "ULONG64"))
          fprintf(stream, " = %s", value);
        else if (!strncmp(t, "enum ", 5))
        {
          const char *s;
          if (is_integer(value))
            fprintf(stream, " = %s", value);
          else if (!*value)
            fprintf(stream, " = 0");
          else if ((s = enames[Pair(t + 5, value)]))
            fprintf(stream, " = %s", s);
        }
        else if (!strncmp(t, "char", 4)
            || !strncmp(t, "const char", 10)
            || !strncmp(t, "wchar_t", 7)
            || !strncmp(t, "const wchar_t", 13)
            || !strncmp(t, "std::string", 11))
          fprintf(stream, " = \"%s\"", cstring(value));
        else if (!strcmp(t, "xsd__QName") && QName)     // QName
          fprintf(stream, " = \"%s\"", cstring(QName));
      }
      fprintf(stream, ";\t///< Default element value=\"%s\".\n", value);
    }
    else if (fixed)
      fprintf(stream, ";\t///< Fixed element value=\"%s\".\n", fixed);
    else if (nillable && (!min || !strcmp(min, "1")) && (!max || !strcmp(max, "1")))
      fprintf(stream, ";\t///< Optional (xsi:nil when NULL) element.\n");
    else if (!fake_union && (!min || !strcmp(min, "1")) && (!max || !strcmp(max, "1")))
      fprintf(stream, ";\t///< Required element.\n");
    else if (!fake_union && min && !strcmp(min, "0") && (!max || !strcmp(max, "1")))
      fprintf(stream, ";\t///< Optional element.\n");
    else
      fprintf(stream, ";\n");
  }
}

void Types::gen(const char *URI, const vector<xs__group>& groups)
{
  for (vector<xs__group>::const_iterator group = groups.begin(); group != groups.end(); ++group)
    gen(URI, *group, NULL, NULL);
}

void Types::gen(const char *URI, const xs__group& group, const char *minOccurs, const char *maxOccurs)
{
  static set<const xs__group*> visited;
  const char *min = minOccurs;
  const char *max = maxOccurs;
  if (visited.find(&group) != visited.end())
  {
    if (group.ref)
      fprintf(stderr, "\nWarning: circular group <xs:group ref=\"%s\"/>\n", group.ref);
    else
      fprintf(stderr, "\nWarning: circular group <xs:group name=\"%s\"/>\n", group.name ? group.name : "");
    fprintf(stream, "/// @todo !FIXME! @warning %s is a group with a circular reference.\n", group.ref ? group.ref : group.name ? group.name : "");
    return;
  }
  visited.insert(&group);
  if (group.minOccurs)
    min = group.minOccurs;
  if (group.maxOccurs)
    max = group.maxOccurs;
  if (group.groupPtr())
  {
    gen(URI, *group.groupPtr(), min, max);
  }
  else
  {
    fprintf(stream, "//  BEGIN GROUP <xs:group name=\"%s\"", group.name ? group.name : "");
    if (min)
      fprintf(stream, " minOccurs=\"%s\"", min);
    if (max)
      fprintf(stream, " maxOccurs=\"%s\"", max);
    fprintf(stream, ">\n");
    document(group.annotation);
    if (group.all)
      gen(URI, *group.all, min, max);
    else if (group.choice)
      gen(URI, NULL, *group.choice, min, max);
    else if (group.sequence)
      gen(URI, *group.sequence, min, max);
    fprintf(stream, "//  END OF GROUP\n");
  }
  visited.erase(&group);
}

void Types::gen(const char *URI, const char *name, const xs__seqchoice& choice, const char *minOccurs, const char *maxOccurs)
{
  const char *r = NULL, *s = NULL, *t = NULL;
  const char *min = minOccurs;
  const char *max = maxOccurs;
  bool use_union = !uflag;
  bool wrap_union = false;
  bool tmp_union;
  if (!URI && choice.schemaPtr())
    URI = choice.schemaPtr()->targetNamespace;
  fprintf(stream, "//  BEGIN CHOICE <xs:choice");
  if (choice.minOccurs)
    min = choice.minOccurs;
  if (choice.maxOccurs)
    max = choice.maxOccurs;
  if (min)
    fprintf(stream, " minOccurs=\"%s\"", min);
  if (max)
    fprintf(stream, " maxOccurs=\"%s\"", max);
  fprintf(stream, ">\n");
  document(choice.annotation);
  for (vector<xs__contents>::const_iterator c1 = choice.__contents.begin(); c1 != choice.__contents.end(); ++c1)
  {
    if ((*c1).__union == SOAP_UNION_xs__union_content_group
     || (*c1).__union == SOAP_UNION_xs__union_content_sequence)
    {
      fprintf(stream, "/// @note <xs:choice> with embedded <xs:sequence> or <xs:group> prevents the use of a union for <xs:choice>. Instead of being members of a union, the following members are declared optional. Only one member should be non-NULL by choice.\n");
      use_union = false;
      break;
    }
  }
  if (use_union && (cflag || sflag))
  {
    for (vector<xs__contents>::const_iterator c2 = choice.__contents.begin(); c2 != choice.__contents.end(); ++c2)
    {
      if ((*c2).__union == SOAP_UNION_xs__union_content_element
       && (*c2).__content.element
       && (*c2).__content.element->maxOccurs
       && strcmp((*c2).__content.element->maxOccurs, "1"))
      {
        fprintf(stream, "/// @note <xs:choice> with one ore more elements with maxOccurs>1 (%s) prevents the use of a union. Instead of being members of a union, the following members are declared optional. Only one member should be non-NULL by choice.\n", (*c2).__content.element->name ? (*c2).__content.element->name : "");
        use_union = false;
        break;
      }
    }
  }
  t = uname(URI);
  s = strstr(t, "__union");
#if 0  // Alternative name for choice selector (old style):
  r = aname(NULL, NULL, name);
#else
  if (s)
    r = s + 7;
  if (!r || !*r)
  {
    if (strncmp(t, "union", 5) == 0)
    {
      r = t + 5;
      s = r;
    }
    else
    {
      r = t;
      s = t;
    }
  }
#endif
  if (max && strcmp(max, "1"))
  {
    if (with_union)
    {
      // Generate a wrapper when we need a union within a union
      wrap_union = true;
      fprintf(stream, "    struct __%s\n    {\n", t);
    }
    fprintf(stream, sizeformat, "int", r);
    fprintf(stream, " %s", min ? min : "0");
    if (is_integer(max))
      fprintf(stream, ":%s", max);
    fprintf(stream, ";\n");
    if (cflag)
      fprintf(stream, "    struct _%s\n    {\n", t);
    else
      fprintf(stream, "    class _%s\n    {\n", t);
  }
  if (use_union)
  {
    if (!with_union || wrap_union)
    {
      fprintf(stream, choiceformat, "int", r);
      if (min)
        fprintf(stream, " %s", min);
      fprintf(stream, ";\t///< Union %s selector: set to SOAP_UNION_%s_<fieldname>%s\n", t, t, min && !strcmp(min, "0") ? " or 0 to omit" : "");
      if (name)
        fprintf(stream, "/// Union for choice in %s.\n", cname(NULL, URI, name));
      fprintf(stream, "    union %s\n    {\n", t);
    }
    tmp_union = with_union;
    with_union = true;
  }
  else
  {
    tmp_union = fake_union;
    fake_union = true;
  }
  gen(URI, choice.__contents);
  if (use_union)
  {
    with_union = tmp_union;
    if (!with_union || wrap_union)
    {
      fprintf(stream, elementformat, "}", s[0] == '_' && s[1] == '_' ? s+2 : s);
      fprintf(stream, ";\n");
    }
  }
  else
    fake_union = tmp_union;
  if (max && strcmp(max, "1"))
  {
    fprintf(stream, pointerformat, "}", s);
    fprintf(stream, ";\n");
  }
  if (wrap_union)
  {
    fprintf(stream, elementformat, "}", s);
    fprintf(stream, ";\n");
  }
  fprintf(stream, "//  END OF CHOICE\n");
}

void Types::gen(const char *URI, const vector<xs__any>& anys)
{
  for (vector<xs__any>::const_iterator any = anys.begin(); any != anys.end(); ++any)
    gen(URI, *any, NULL, NULL);
}

void Types::gen(const char *URI, const xs__any& any, const char *minOccurs, const char *maxOccurs)
{
  const char *min = minOccurs;
  const char *max = maxOccurs;
  (void)URI;
  fprintf(stream, "/// @todo <any");
  if (any.namespace_)
    fprintf(stream, " namespace=\"%s\"", any.namespace_);
  if (any.minOccurs)
    min = any.minOccurs;
  if (any.maxOccurs)
    max = any.maxOccurs;
  if (min)
    fprintf(stream, " minOccurs=\"%s\"", min);
  if (max)
    fprintf(stream, " maxOccurs=\"%s\"", max);
  fprintf(stream, ">\n/// @todo Schema extensibility is user-definable.\n///       Consult the protocol documentation to change or insert declarations.\n///       Use wsdl2h option -x to remove this element.\n///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):\n///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.\n");
  if (!xflag)
  {
    if (max && strcmp(max, "1"))
    {
      fprintf(stream, "/// Size of the array of XML or DOM nodes is %s..%s.\n", min ? min : "1", max);
      if (cflag || sflag)
      {
        if (!with_union)
        {
          fprintf(stream, sizeformat, "int", "");
          fprintf(stream, "0;\n");
          fprintf(stream, elementformat, pname(true, false, NULL, NULL, "xsd:any"), "__any");
        }
        else
          fprintf(stream, elementformat, tname(NULL, NULL, "xsd:any"), "__any");
      }
      else if (with_union)
        fprintf(stream, pointertemplateformat, vname("$CONTAINER"), tname(NULL, NULL, "xsd:any"), "__any");
      else
        fprintf(stream, templateformat, vname("$CONTAINER"), tname(NULL, NULL, "xsd:any"), "__any");
    }
    else
      fprintf(stream, elementformat, pname(with_union, false, NULL, NULL, "xsd:any"), "__any");
    if (dflag)
      fprintf(stream, "0;\t///< Catch any element content in DOM.\n");
    else
      fprintf(stream, "0;\t///< Catch any element content in XML string.\n");
  }
}

void Types::gen(const char *URI, const xs__anyAttribute& anyAttribute)
{
  (void)URI;
  if (anyAttribute.namespace_)
    fprintf(stream, "/// @todo <anyAttribute namespace=\"%s\">.\n", anyAttribute.namespace_);
  fprintf(stream, "/// @todo Schema extensibility is user-definable.\n///       Consult the protocol documentation to change or insert declarations.\n///       Use wsdl2h option -x to remove this attribute.\n///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).\n");
  if (!xflag)
  {
    const char *t = tname(NULL, NULL, "xsd:anyAttribute");
    fprintf(stream, attributeformat, t, "__anyAttribute");
    if (dflag)
      fprintf(stream, ";\t///< Store anyAttribute content in DOM soap_dom_attribute linked node structure.\n");
    else
      fprintf(stream, ";\t///< A placeholder that has no effect: please see comment.\n");
  }
}

void Types::gen_inh(const char *URI, const xs__complexType *complexType, bool anonymous)
{
  const xs__complexType *p = complexType;
  if (!p)
    return;
  const char *pURI;
  if (p->schemaPtr())
    pURI = p->schemaPtr()->targetNamespace;
  else
    pURI = URI;
  const char *b = cname(NULL, pURI, p->name);
  if (p->complexContent && p->complexContent->extension)
    gen_inh(URI, p->complexContent->extension->complexTypePtr(), anonymous);
  if (cflag || fflag || anonymous)
    fprintf(stream, "/// INHERITED FROM %s:\n", b);
  else if (comment_nest == 0)
    fprintf(stream, "/*  INHERITED FROM %s:\n", b);
  else
    fprintf(stream, "    INHERITED FROM %s:\n", b);
  comment_nest++;
  if (cflag || fflag)
    pURI = URI; // if base ns != derived ns then qualify elts and atts
  if (p->complexContent && p->complexContent->extension)
  {
    if (p->complexContent->extension->group)
      gen(pURI, *p->complexContent->extension->group, NULL, NULL);
    if (p->complexContent->extension->all)
      gen(pURI, *p->complexContent->extension->all, NULL, NULL);
    if (p->complexContent->extension->sequence)
      gen(pURI, *p->complexContent->extension->sequence, NULL, NULL);
    if (p->complexContent->extension->choice)
      gen(pURI, p->name, *p->complexContent->extension->choice, NULL, NULL);
    gen(pURI, p->complexContent->extension->attribute);
    gen(pURI, p->complexContent->extension->attributeGroup);
    if (p->complexContent->extension->anyAttribute)
      gen(pURI, *p->complexContent->extension->anyAttribute);
  }
  else
  {
    if (p->all)
      gen(pURI, p->all->element, NULL, NULL);
    else if (p->all)
      gen(pURI, *p->all, NULL, NULL);
    else if (p->choice)
      gen(pURI, p->name, *p->choice, NULL, NULL);
    else if (p->sequence)
      gen(pURI, *p->sequence, NULL, NULL);
    else if (p->any)
      gen(pURI, *p->any, NULL, NULL);
    if (p->defaultAttributesApply && p->schemaPtr() && p->schemaPtr()->attributeGroupPtr())
    {
      xs__attributeGroup *a = p->schemaPtr()->attributeGroupPtr();
      if (a->attributeGroupPtr())
        a = a->attributeGroupPtr();
      gen(pURI, a->attribute);
      gen(pURI, a->attributeGroup);
      if (a->anyAttribute)
        gen(pURI, *a->anyAttribute);
    }
    gen(pURI, p->attribute);
    gen(pURI, p->attributeGroup);
    if (p->anyAttribute)
      gen(pURI, *p->anyAttribute);
  }
  modify(b);
  comment_nest--;
  if (cflag || fflag || anonymous)
    fprintf(stream, "//  END OF INHERITED FROM %s\n", b);
  else if (comment_nest == 0)
    fprintf(stream, "    END OF INHERITED FROM %s */\n", b);
  else
    fprintf(stream, "    END OF INHERITED FROM %s\n", b);
}

void Types::gen_soap_array(const char *t, const char *item, const char *type)
{
  char *tmp = NULL, *dims = NULL, size[24];
  if (type)
    tmp = (char*)estrdup(type);
  *size = '\0';
  if (tmp)
    dims = strrchr(tmp, '[');
  if (dims)
    *dims++ = '\0';
  fprintf(stream, "/// SOAP encoded array of %s.\n", tmp ? tmp : "xs:anyType");
  if (cflag)
    fprintf(stream, "struct %s\n{\n", t);
  else if (pflag && *t)
    fprintf(stream, "class %s : public xsd__anyType\n{ public:\n", t);
  else
    fprintf(stream, "class %s\n{ public:\n", t);
  if (dims)
  {
    char *s = strchr(dims, ']');
    if (s && s != dims)
      (SOAP_SNPRINTF(size, 24, 23), "[%d]", (int)(s - dims + 1));
  }
  if (tmp)
  {
    if (strchr(tmp, '[') != NULL)
    {
      size_t l = strlen(t);
      if (!strncmp(t, "ArrayOf", 7) && l > 7)
        gen_soap_array(t + 7, item, tmp);
      else if (!strncmp(t, "Array", 5) && l > 5)
        gen_soap_array(t + 5, item, tmp);
      else
        gen_soap_array("", item, tmp);
      fprintf(stream, arrayformat, "}", item ? aname(NULL, NULL, item) : "");
      fprintf(stream, ";\n");
    }
    else
    {
      const char *s = tname(NULL, NULL, tmp);
      fprintf(stream, "/// Pointer to array of %s.\n", s);
      fprintf(stream, arrayformat, s, item ? aname(NULL, NULL, item) : "");
      fprintf(stream, ";\n");
    }
    if (*size)
      fprintf(stream, "/// Size of the multidimensional dynamic array with dimensions=%s.\n", size);
    else
      fprintf(stream, "/// Size of the dynamic array.\n");
    fprintf(stream, arraysizeformat, "int", size);
    fprintf(stream, ";\n/// Offset for partially transmitted arrays (uncomment only when required).\n");
    fprintf(stream, arrayoffsetformat, "int", size);
    fprintf(stream, ";\n");
  }
  else
  {
    // TODO: how to handle generic SOAP array? E.g. as an array of anyType?
    fprintf(stream, "// @todo Add declarations to handle generic SOAP-ENC:Array (array of anyType)\n");
  }
}

void Types::gen_substitutions(const char *URI, const xs__element& element)
{
  const std::vector<xs__element*> *substitutions;
  const char *name;
  const char *r = NULL, *s = NULL, *t = NULL;
  bool use_union = !uflag;
  bool wrap_union = false;
  bool tmp_union;
  bool abstract = false;
  if (!URI && element.schemaPtr())
    URI = element.schemaPtr()->targetNamespace;
  if (element.elementPtr())
  {
    name = element.elementPtr()->name;
    substitutions = element.elementPtr()->substitutionsPtr();
    abstract = element.elementPtr()->abstract;
    if (!abstract && element.elementPtr()->complexTypePtr())
      abstract = element.elementPtr()->complexTypePtr()->abstract;
  }
  else
  {
    name = element.name;
    substitutions = element.substitutionsPtr();
    abstract = element.abstract;
    if (!abstract && element.complexTypePtr())
      abstract = element.complexTypePtr()->abstract;
  }
  fprintf(stream, "//  BEGIN CHOICE OF SUBSTITUTIONS <xs:element substitutionGroup=\"%s\"", name);
  if (element.minOccurs)
    fprintf(stream, " minOccurs=\"%s\"", element.minOccurs);
  if (element.maxOccurs)
    fprintf(stream, " maxOccurs=\"%s\"", element.maxOccurs);
  fprintf(stream, "> with global elements");
  for (std::vector<xs__element*>::const_iterator i1 = substitutions->begin(); i1 != substitutions->end(); ++i1)
    fprintf(stream, " <%s>", (*i1)->name);
  fprintf(stream, "\n");
  t = uname(URI);
  s = strstr(t, "__union");
  r = aname(NULL, NULL, name);
  if (element.maxOccurs && strcmp(element.maxOccurs, "1"))
  {
    if (with_union)
    {
      // Generate a wrapper when we need a union within a union
      wrap_union = true;
      fprintf(stream, "    struct __%s\n    {\n", t);
    }
    fprintf(stream, sizeformat, "int", r);
    fprintf(stream, " %s", element.minOccurs ? element.minOccurs : "0");
    if (is_integer(element.maxOccurs))
      fprintf(stream, ":%s", element.maxOccurs);
    fprintf(stream, ";\n");
    if (cflag)
      fprintf(stream, "    struct _%s\n    {\n", t);
    else
      fprintf(stream, "    class _%s\n    {\n", t);
  }
  if (use_union)
  {
    if (!with_union || wrap_union)
    {
      fprintf(stream, choiceformat, "int", r);
      if (element.minOccurs)
        fprintf(stream, " %s", element.minOccurs);
      fprintf(stream, ";\t///< Union %s selector: set to SOAP_UNION_%s_<fieldname>%s\n", t, t, element.minOccurs && !strcmp(element.minOccurs, "0") ? " or 0 to omit" : "");
      if (name)
        fprintf(stream, "/// Union for substitutionGroup %s.\n", cname(NULL, URI, name));
      fprintf(stream, "    union %s\n    {\n", t);
    }
    tmp_union = with_union;
    with_union = true;
  }
  else
  {
    tmp_union = fake_union;
    fake_union = true;
  }
  if (!abstract)
    gen(URI, element, false, NULL, NULL);
  for (vector<xs__element*>::const_iterator i2 = substitutions->begin(); i2 != substitutions->end(); ++i2)
    gen(URI, *(*i2), true, NULL, NULL); // substitutions can be recursive?
  if (use_union)
  {
    with_union = tmp_union;
    if (!with_union || wrap_union)
    {
      fprintf(stream, elementformat, "}", s[0] == '_' && s[1] == '_' ? s+2 : s);
      fprintf(stream, ";\n");
    }
  }
  else
    fake_union = tmp_union;
  if (element.maxOccurs && strcmp(element.maxOccurs, "1"))
  {
    fprintf(stream, pointerformat, "}", s);
    fprintf(stream, ";\n");
  }
  if (wrap_union)
  {
    fprintf(stream, elementformat, "}", s);
    fprintf(stream, ";\n");
  }
  fprintf(stream, "//  END OF SUBSTITUTIONS\n");
}

void Types::document(const xs__annotation *annotation)
{
  if (annotation && annotation->documentation)
    documentation(annotation->documentation);
}

void Types::modify(const char *name)
{
  // TODO: consider support removal of elements/attributes with ns__X = $- Y
  const char *s = modtypemap[name];
  if (s)
  {
    while (*s)
    {
      if (*s++ == '$')
        fprintf(stream, "/// Member declared in %s\n   ", mapfile);
      s = format(s);
    }
  }
}

const char* Types::format(const char *text)
{
  const char *s = text;
  if (!s)
    return NULL;
  while (*s && *s != '$')
  {
    if (*s == '\\')
    {
      switch (s[1])
      {
        case 'n':
          fputc('\n', stream);
          break;
        case 't':
          fputc('\t', stream);
          break;
        default:
          fputc(s[1], stream);
      }
      s++;
    }
    else
      fputc(*s, stream);
    s++;
  }
  fputc('\n', stream);
  return s;
}

////////////////////////////////////////////////////////////////////////////////
//
//      Type map file parsing
//
////////////////////////////////////////////////////////////////////////////////

static char *getline(char *s, size_t n, FILE *fd)
{
  int c;
  char *t = s;
  if (n)
    n--;
  for (;;)
  {
    c = fgetc(fd);
    if (c == '\r')
      continue;
    if (c == '\\')
    {
      c = fgetc(fd);
      if (c == '\r')
        c = fgetc(fd);
      if (c < ' ')
        continue;
      if (n)
      {
        *t++ = '\\';
        n--;
      }
    }
    if (c == '\n' || c == EOF)
      break;
    if (n)
    {
      *t++ = c;
      n--;
    }
  }
  *t++ = '\0';
  if (!*s && c == EOF)
    return NULL;
  return s;
}

static const char *nonblank(const char *s)
{
  while (*s && isspace(*s))
    s++;
  return s;
}

static const char *fill(char *t, int n, const char *s, int e)
{
  int i = n;
  s = nonblank(s);
  while (*s && *s != e && --i)
    *t++ = *s++;
  while (*s && *s != e)
    s++;
  if (*s)
    s++;
  i = n - i;
  if (i == 0)
    *t = '\0';
  else
  {
    while (isspace(*--t) && i--)
      ;
    t[1] = '\0';
  }
  return s;
}

////////////////////////////////////////////////////////////////////////////////
//
//      Miscellaneous
//
////////////////////////////////////////////////////////////////////////////////

static const char *utf8(char **t, const char *s, bool start)
{
  unsigned int c = 0;
  unsigned int c1, c2, c3, c4;
  const char *r = s;
  c = (unsigned char)*r;
  if (c >= 0x80)
  {
    c1 = (unsigned char)*++r;
    if (c1 < 0x80)
      r--;
    else
    {
      c1 &= 0x3F;
      if (c < 0xE0)
        c = ((c & 0x1F) << 6) | c1;
      else
      {
        c2 = (unsigned char)*++r & 0x3F;
        if (c < 0xF0)
          c = ((c & 0x0F) << 12) | (c1 << 6) | c2;
        else
        {
          c3 = (unsigned char)*++r & 0x3F;
          if (c < 0xF8)
            c = ((c & 0x07) << 18) | (c1 << 12) | (c2 << 6) | c3;
          else
          {
            c4 = (unsigned char)*++r & 0x3F;
            if (c < 0xFC)
              c = ((c & 0x03) << 24) | (c1 << 18) | (c2 << 12) | (c3 << 6) | c4;
            else
              c = ((c & 0x01) << 30) | (c1 << 24) | (c2 << 18) | (c3 << 12) | (c4 << 6) | (*++r & 0x3F);
          }
        }
      }
    }
  }
  if (Uflag &&
      // Universal character names for identifier characters
      // E.1 Ranges of characters allowed
      ( c == 0x00A8
     || c == 0x00AA
     || c == 0x00AD
     || c == 0x00AF
     || (0x00B2 <= c && c <= 0x00B5)
     || (0x00B7 <= c && c <= 0x00BA)
     || (0x00BC <= c && c <= 0x00BE)
     || (0x00C0 <= c && c <= 0x00D6)
     || (0x00D8 <= c && c <= 0x00F6)
     || (0x00F8 <= c && c <= 0x00FF)
     || (0x0100 <= c && c <= 0x167F)
     || (0x1681 <= c && c <= 0x180D)
     || (0x180F <= c && c <= 0x1FFF)
     || (0x200B <= c && c <= 0x200D)
     || (0x202A <= c && c <= 0x202E)
     || (0x203F <= c && c <= 0x2040)
     || c == 0x2054
     || (0x2060 <= c && c <= 0x206F)
     || (0x2070 <= c && c <= 0x218F)
     || (0x2460 <= c && c <= 0x24FF)
     || (0x2776 <= c && c <= 0x2793)
     || (0x2C00 <= c && c <= 0x2DFF)
     || (0x2E80 <= c && c <= 0x2FFF)
     || (0x3004 <= c && c <= 0x3007)
     || (0x3021 <= c && c <= 0x302F)
     || (0x3031 <= c && c <= 0x303F)
     || (0x3040 <= c && c <= 0xD7FF)
     || (0xF900 <= c && c <= 0xFD3D)
     || (0xFD40 <= c && c <= 0xFDCF)
     || (0xFDF0 <= c && c <= 0xFE44)
     || (0xFE47 <= c && c <= 0xFFFD)
     || (0x10000 <= c && c <= 0x1FFFD)
     || (0x20000 <= c && c <= 0x2FFFD)
     || (0x30000 <= c && c <= 0x3FFFD)
     || (0x40000 <= c && c <= 0x4FFFD)
     || (0x50000 <= c && c <= 0x5FFFD)
     || (0x60000 <= c && c <= 0x6FFFD)
     || (0x70000 <= c && c <= 0x7FFFD)
     || (0x80000 <= c && c <= 0x8FFFD)
     || (0x90000 <= c && c <= 0x9FFFD)
     || (0xA0000 <= c && c <= 0xAFFFD)
     || (0xB0000 <= c && c <= 0xBFFFD)
     || (0xC0000 <= c && c <= 0xCFFFD)
     || (0xD0000 <= c && c <= 0xDFFFD)
     || (0xE0000 <= c && c <= 0xEFFFD)
     )
     &&
     // E.2 Ranges of characters disallowed initially
     !(start &&
         ( (0x0300 <= c && c <= 0x036F)
        || (0x1DC0 <= c && c <= 0x1DFF)
        || (0x20D0 <= c && c <= 0x20FF)
        || (0xFE20 <= c && c <= 0xFE2F)
        )
      )
     )
  {
    soap_strncpy(*t, 7, s, r - s + 1);
    *t += r - s + 1;
  }
  else
  {
    // encode up to UCS4 only
    if (c > 0xFFFF)
      c = 0xFFFF;
    (SOAP_SNPRINTF(*t, 7, 6), "_x%4.4x", c);
    *t += 6;
  }
  return r;
}

static const char *cstring(const char *s)
{
  size_t n;
  char *t;
  const char *r;
  for (n = 0, r = s; *r; n++, r++)
    if (*r == '"' || *r == '\\')
      n++;
    else if (*r < 32)
      n += 3;
  r = t = (char*)emalloc(n + 1);
  for (; *s; s++)
  {
    if (*s == '"' || *s == '\\')
    {
      *t++ = '\\';
      *t++ = *s;
    }
    else if (*s < 32)
    {
      (SOAP_SNPRINTF(t, 5, 4), "\\%03o", (unsigned int)(unsigned char)*s);
      t += 4;
    }
    else
      *t++ = *s;
  }
  *t = '\0';
  return r;
}

static const char *xstring(const char *s)
{
  size_t n;
  char *t;
  const char *r;
  for (n = 0, r = s; *r; n++, r++)
  {
    if (*r < 32 || *r >= 127)
      n += 4;
    else if (*r == '<' || *r == '>')
      n += 3;
    else if (*r == '&')
      n += 4;
    else if (*r == '"')
      n += 5;
    else if (*r == '\\')
      n += 1;
  }
  r = t = (char*)emalloc(n + 1);
  for (; *s; s++)
  {
    if (*s < 32 || *s >= 127)
    {
      (SOAP_SNPRINTF(t, 5, 4), "&#%.2x;", (unsigned char)*s);
      t += 5;
    }
    else if (*s == '<')
    {
      soap_strcpy(t, 5, "&lt;");
      t += 4;
    }
    else if (*s == '>')
    {
      soap_strcpy(t, 5, "&gt;");
      t += 4;
    }
    else if (*s == '&')
    {
      soap_strcpy(t, 6, "&amp;");
      t += 5;
    }
    else if (*s == '"')
    {
      soap_strcpy(t, 7, "&quot;");
      t += 6;
    }
    else if (*s == '\\')
    {
      soap_strcpy(t, 3, "\\\\");
      t += 2;
    }
    else
      *t++ = *s;
  }
  *t = '\0';
  return r;
}

static bool is_float(const char *s)
{
  if (*s == '-' || *s == '+')
    s++;
  if (!*s || strlen(s) > 20)
    return false;
  while (*s && isdigit(*s))
    s++;
  if (*s == '.')
    s++;
  while (*s && isdigit(*s))
    s++;
  if (*s == 'e' || *s == 'E')
  {
    s++;
    if (*s == '-' || *s == '+')
      s++;
    while (*s && isdigit(*s))
      s++;
  }
  return *s == '\0';
}

static bool is_integer(const char *s)
{
  if (*s == '-' || *s == '+')
    s++;
  if (!*s || strlen(s) > 20)
    return false;
  while (*s && isdigit(*s))
    s++;
  return *s == '\0';
}

static LONG64 to_integer(const char *s)
{
  char *r;
  return soap_strtoll(s, &r, 10);
}

static void documentation(const char *text)
{
  const char *s = text;
  const char *sep = "/// <PRE><BLOCKQUOTE>\n///   ";
  if (!s)
    return;
  while (*s)
  {
    switch (*s)
    {
      case '\n':
        if (!sep)
          sep = "\n///   ";
        break;
      case '\t':
      case ' ':
        if (!sep)
          sep = " ";
        break;
      default:
        if (*s > 32)
        {
          if (sep)
          {
            fputs(sep, stream);
            sep = NULL;
          }
          fputc(*s, stream);
        }
    }
    s++;
  }
  fprintf(stream, "\n/// </BLOCKQUOTE></PRE>\n");
}

static void operations(const char *t)
{
  if (cflag)
    fprintf(stream, "/// struct %s operations:\n/// - soap_default_%s(soap*, %s*) reset members to default\n/// - int soap_read_%s(soap*, %s*) deserialize from a source\n/// - int soap_write_%s(soap*, %s*) serialize to a sink\n/// - %s* soap_dup_%s(soap*, %s* dst, %s *src) returns deep copy of %s src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)\n/// - soap_del_%s(%s*) deep deletes %s data members, use only on dst after soap_dup_%s(NULL, %s *dst, %s *src) (use soapcpp2 -Ed)\n", t, t, t, t, t, t, t, t, t, t, t, t, t, t, t, t, t, t);
  else
    fprintf(stream, "/// class %s operations:\n/// - %s* soap_new_%s(soap*) allocate\n/// - %s* soap_new_%s(soap*, int num) allocate array\n/// - %s* soap_new_req_%s(soap*, ...) allocate, set required members\n/// - %s* soap_new_set_%s(soap*, ...) allocate, set all public members\n/// - %s::soap_default(soap*) reset members to default\n/// - int soap_read_%s(soap*, %s*) deserialize from a stream\n/// - int soap_write_%s(soap*, %s*) serialize to a stream\n/// - %s* %s::soap_dup(soap*) returns deep copy of %s, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)\n/// - %s::soap_del() deep deletes %s data members, use only after %s::soap_dup(NULL) (use soapcpp2 -Ed)\n", t, t, t, t, t, t, t, t, t, t, t, t, t, t, t, t, t, t, t, t);
}

////////////////////////////////////////////////////////////////////////////////
//
//      Allocation
//
////////////////////////////////////////////////////////////////////////////////

void *emalloc(size_t size)
{
  void *p = malloc(size);
  if (!p)
  {
    fprintf(stderr, "\nError: Malloc failed\n");
    exit(1);
  }
  return p;
}

char *estrdup(const char *s)
{
  size_t l = strlen(s);
  char *t = (char*)emalloc(l + 1);
  soap_strcpy(t, l + 1, s);
  return t;
}

char *estrdupf(const char *s)
{
  char *t = (char*)emalloc(strlen(s) + 1);
  char *p;
  for (p = t; *s; s++)
  {
    if (s[0] == '/' && s[1] == '*')
    {
      for (s += 2; s[0] && s[1]; s++)
      {
        if (s[0] == '*' && s[1] == '/')
        {
          s++;
          break;
        }
      }
      continue;
    }
    *p++ = *s;
  }
  *p = '\0';
  return t;
}
