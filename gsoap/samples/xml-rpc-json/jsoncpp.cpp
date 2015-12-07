/*
        jsoncpp.cpp
        
        A JSON C/C++ code generator for the gSOAP JSON API.

        1. Take a JSON sample document and render it in JSON API code:

        echo '\
        { "menu": {\
            "id": "file",\
            "value": "File",\
            "popup": {\
              "menuitem": [\
                {"value": "New", "onclick": "CreateNewDoc()"},\
                {"value": "Open", "onclick": "OpenDoc()"},\
                {"value": "Close", "onclick": "CloseDoc()"}\
              ]\
            }\
          }\
        }' | ./jsoncpp

        #include "json.h"
	{
	  struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT);
	  ctx->double_format = "%lG";

	  value x(ctx);
	  x["menu"]["id"] = "file";
	  x["menu"]["value"] = "File";
	  x["menu"]["popup"]["menuitem"][0]["value"] = "New";
	  x["menu"]["popup"]["menuitem"][0]["onclick"] = "CreateNewDoc()";
	  x["menu"]["popup"]["menuitem"][1]["value"] = "Open";
	  x["menu"]["popup"]["menuitem"][1]["onclick"] = "OpenDoc()";
	  x["menu"]["popup"]["menuitem"][2]["value"] = "Close";
	  x["menu"]["popup"]["menuitem"][2]["onclick"] = "CloseDoc()";
	  std::cout << x << std::endl;

	  soap_destroy(ctx);
	  soap_end(ctx);
	  soap_free(ctx);
	}

	2. Take a JSONPath to generate a stand-alone application that filters
	   JSON documents with a store of books to return their titles:

	jsoncpp -i -m -p'$.store.book[:].title'
        #include "json.h"
	struct Namespace namespaces[] = {{NULL,NULL,NULL,NULL}};
	int main(int argc, char **argv)
	{
	  struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT);
	  ctx->double_format = "%lG";

	  value x(ctx);
	  std::cin >> x;
	  // $.store.book[:].title
	  #define QUERY_YIELD(v) std::cout << v << std::endl
	  if (x.has("store"))
	  {
	    if (x["store"].has("book"))
	    {
	      if (x["store"]["book"].is_array())
	      {
		int j, k = x["store"]["book"].size()-1;
		for (j = 0; j <= k; j += 1)
		{
		  value& r = x["store"]["book"][j];
		  if (r.has("title"))
		  {
		    QUERY_YIELD(r["title"]);
		  }
		}
	      }
	    }
	  }

	  soap_destroy(ctx);
	  soap_end(ctx);
	  soap_free(ctx);
	  return 0;
	}

	3. To build jsoncpp:

	cd gsoap/samples/xml-rpc-json
	soapcpp2 -CSL xml-rpc.h
	c++ -I../.. -o jsoncpp jsoncpp.cpp json.cpp xml-rpc.cpp soapC.cpp ../../stdsoap2.cpp

	4. To compile and link jsoncpp-generated C++ code:

	jsoncpp -o myjson.cpp ...
	soapcpp2 -CSL xml-rpc.h
	c++ -I../.. -o myjson myjson.cpp json.cpp xml-rpc.cpp soapC.cpp ../../stdsoap2.cpp

	5. To compile and link jsoncpp-generated C code:

	jsoncpp -c -o myjson.c ...
	soapcpp2 -c -CSL xml-rpc.h
	cc -I../.. -o myjson myjson.c json.c xml-rpc.c soapC.c ../../stdsoap2.c

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
#include <fstream>
#include <iomanip>

struct Namespace namespaces[] = {{NULL,NULL,NULL,NULL}};

static bool coutput = false;            // -c
static bool explain = false;            // -e
static bool noinput = false;            // -i
static bool collect = false;            // -l
static bool genmain = false;            // -m
static bool minimal = false;            // -M
static bool optimal = false;            // -O
static const char *dform = NULL;        // -f%fmt
static const char *ofile = NULL;        // -ofile
static const char *jpath = NULL;        // -ppath
static const char *jroot = "x";         // -rroot
static const char *jcode = NULL;        // -xcode
static const char *ifile = NULL;        // [infile]

static void code_gen_c(soap*, value&, std::string, int);
static void code_gen_cpp(soap*, value&, std::string, int);
static void path_gen_cpp(soap*, const char*, std::string&, int, bool);
static void path_exec(soap*, std::string&, int);
static std::string getname(const char**);
static std::ostream& indent(soap*, int);

int main(int argc, char **argv)
{
  if (argc >= 2)
  {
    for (int i = 1; i < argc; i++)
    {
      const char *a = argv[i];
      if (*a == '-'
#ifdef WIN32
        || *a == '/'
#endif
         )
      {
        bool f = true;
        while (f && *++a)
        {
          switch (*a)
          {
            case 'c':
              coutput = true;
              break;
            case 'e':
              explain = true;
              break;
            case 'f':
              a++;
              f = false;
              if (*a)
                dform = a;
              else if (i < argc)
                dform = argv[++i];
              break;
            case 'i':
              noinput = true;
              break;
            case 'm':
              genmain = true;
              break;
            case 'M':
              minimal = true;
              break;
            case 'O':
              optimal = true;
              break;
            case 'o':
              a++;
              f = false;
              if (*a)
                ofile = a;
              else if (i < argc)
                ofile = argv[++i];
              break;
            case 'p':
              a++;
              f = false;
              if (*a)
                jpath = a;
              else if (i < argc)
                jpath = argv[++i];
              break;
            case 'r':
              a++;
              f = false;
              if (*a)
                jroot = a;
              else if (i < argc)
                jroot = argv[++i];
              break;
            case 'x':
              a++;
              f = false;
              if (*a)
                jcode = a;
              else if (i < argc)
                jcode = argv[++i];
              break;
            case 'y':
              collect = true;
              break;
            case '?':
            case 'h':
              fprintf(stderr,
                  "Usage: jsoncpp [-c] [-e] [-f%%fmt] [-h] [-i] [-m] [-M] [-O] [-ofile] [-ppath] [-rroot] [-xcode] [-y] [infile]\n\n"
                  "-c      generate C code instead of C++\n"
                  "-e      add explanatory comments to the generated code\n"
                  "-f%%fmt  use %%fmt to format double floats, e.g. -f%%lg\n"
                  "-h      display help message\n"
                  "-i      don't read JSON from stdin, generate code that reads JSON instead\n"
                  "-m      generate stand-alone code with main()\n"
                  "-M      generate minimal code unadorned with initialization and cleanup\n"
                  "-O      optimize code by factoring common indices\n"
                  "-ofile  save source code to file\n"
                  "-ppath  generate JSONPath query code for 'path'\n"
                  "-rroot  use 'root' instead of root value 'x' in the generated code\n"
                  "-xcode  generate code that executes 'code' for each JSONPath query result\n"
                  "-y      generate code that yields an array 'y' of JSONPath query results\n"
                  "infile  JSON file to parse\n\n");
              exit(EXIT_SUCCESS);
            default:
              fprintf(stderr, "jsoncpp: Unknown option %s\n\n", a);
              exit(EXIT_FAILURE);
          }
        }
      }
      else
      {
        ifile = argv[i];
      }
    }
  }

  if (genmain)
    minimal = false;

  soap *ctx = soap_new1(SOAP_C_UTFSTRING);

  if (dform && *dform == '%' && *(dform+1))
    ctx->double_format = dform;

  std::ifstream ifs;

  if (ifile)
  {
    ifs.open(ifile, std::ifstream::in);
    if (!ifs.is_open())
    {
      fprintf(stderr, "Cannot open %s for reading\n", ifile);
      exit(EXIT_FAILURE);
    }
    ctx->is = &ifs;
    noinput = false;
  }

  std::ofstream ofs;

  if (ofile)
  {
    ofs.open(ofile, std::ofstream::out);
    if (!ofs.is_open())
    {
      fprintf(stderr, "Cannot open %s for writing\n", ofile);
      exit(EXIT_FAILURE);
    }
    ctx->os = &ofs;
  }
  else
  {
    ctx->os = &std::cout;
  }

  value v(ctx);

  if (!noinput)
  {
    if (json_read(ctx, v))
    {
      soap_print_fault(ctx, stderr);
      soap_print_fault_location(ctx, stderr);
      exit(EXIT_FAILURE);
    }
  }

  if (ifile)
    ifs.close();

  if (!minimal)
  {
    if (coutput)
    {
      *ctx->os <<
        "/* Dependencies:\n"
        "     json.h xml-rpc-iters.h soapH.h soapStub.h stdsoap2.h\n"
        "     json.c xml-rpc.c soapC.c stdsoap2.c\n"
        "   Build:\n"
        "     soapcpp2 -c -CSL xml-rpc.h\n"
        "     cc ... json.c xml-rpc.c soapC.c stdsoap2.c ...\n"
        "*/\n";
    }
    else
    {
      *ctx->os <<
        "// Dependencies:\n"
        "//   json.h xml-rpc-iters.h soapH.h soapStub.h stdsoap2.h\n"
        "//   json.cpp xml-rpc.cpp soapC.cpp stdsoap2.cpp\n"
        "// Build:\n"
        "//   soapcpp2 -CSL xml-rpc.h\n"
        "//   c++ ... json.cpp xml-rpc.cpp soapC.cpp stdsoap2.cpp ...\n";
    }
    *ctx->os << "\n#include \"json.h\"\n";
    if (!coutput && jpath && strstr(jpath, ".."))
      *ctx->os << "#include <stack>\n";
  }

  if (genmain)
  {
    *ctx->os <<
      "struct Namespace namespaces[] = {{NULL,NULL,NULL,NULL}};\n"
      "int main(int argc, char **argv)\n";
  }

  if (!minimal)
  {
    *ctx->os << "{ /* Generated by jsoncpp";
    for (int i = 1; i < argc; ++i)
      *ctx->os << " " << argv[i];
    *ctx->os <<
      " */\n"
      "  struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT);\n"
      "  ctx->double_format = \"" << (dform ? dform : "%lG") << "\";\n\n";
  }

  if (coutput)
  {
    *ctx->os << "  struct value *" << jroot << " = new_value(ctx);\n";
    if (optimal)
      *ctx->os << "  struct value *p = " << jroot << ";\n";
    if (!noinput)
      code_gen_c(ctx, v, jroot, 2);
    else
      *ctx->os << "  json_read(ctx, " << jroot << ");\n";

    if (jpath) // TODO
    {
      *ctx->os <<
        "I will be enlarged in the upcoming releases to generate C JSONPath query code\n"
        "Thank you for your patience.\n";
    }
    else if (!minimal)
    {
      *ctx->os <<
        "  json_write(ctx, " << jroot << ");\n";
    }
    if (!minimal)
    {
      *ctx->os <<
        "\n"
        "  soap_end(ctx);\n"
        "  soap_free(ctx);\n"
        << (genmain ? "  return 0;\n" : "") <<
        "}\n";
    }
  }
  else
  {
    *ctx->os << "  value " << jroot << "(ctx);\n";
    if (optimal)
      *ctx->os << "  value *p = &" << jroot << ";\n";
    if (!noinput)
      code_gen_cpp(ctx, v, jroot, 2);
    else
      *ctx->os << "  std::cin >> " << jroot << ";\n";

    if (jpath)
    {
      *ctx->os << "  // " << jpath << "\n";
      if (!jcode)
      {
        if (collect)
        {
          *ctx->os <<
            "  value y(ctx);\n"
            "  #define QUERY_YIELD(v) y[y.size()] = v\n";
        }
        else
        {
          *ctx->os << "  #define QUERY_YIELD(v) std::cout << v << std::endl\n";
        }
      }
      std::string root(jroot);
      if (explain)
      {
        *ctx->os <<
          "  // Synopsis of variables used:\n"
          "  //   " << root << "\troot node value;\n"
          << ( collect ? "  //   y\tyield array of query results;\n" : "" ) <<
          "  //   v\tcurrent node value referenced in [(expr)];\n"
          "  //   i\tvalue::iterator over array and struct values;\n"
          "  //   j\tarray/struct index (loop counter) / loop start;\n"
          "  //   k\tswitch case counter / loop end;\n"
          "  //   p\tvalue pointer to current node;\n"
          "  //   q\tvalue pointer to current node;\n"
          "  //   r\tvalue reference to current node;\n"
          "  //   s\tvalue reference to current node;\n"
          "  //   S\tvalue stack for recursive descent.\n";
      }
      path_gen_cpp(ctx, jpath, root, 2, false);
      if (!minimal && collect)
        *ctx->os << "  std::cout << y << std::endl;\n";
    }
    else if (!minimal)
    {
      *ctx->os << "  std::cout << " << jroot << " << std::endl;\n";
    }

    if (!minimal)
    {
      *ctx->os <<
        "\n"
        "  soap_destroy(ctx);\n"
        "  soap_end(ctx);\n"
        "  soap_free(ctx);\n"
        << (genmain ? "  return 0;\n" : "") <<
        "}\n";
    }
  }

  if (ofile)
    ofs.close();

  soap_destroy(ctx);
  soap_end(ctx);
  soap_free(ctx);

  return 0;
}

static void code_gen_c(soap *ctx, value& v, std::string lhs, int k)
{
  if (explain && optimal)
    indent(ctx, k) << "/* p = " << lhs << " */\n";
  switch (v.__type)
  {
    case SOAP_TYPE__boolean:
      if (optimal)
        indent(ctx, k) << "*bool_of(p) = " << (v.is_true() ? 1 : 0) << ";\n";
      else
        indent(ctx, k) << "*bool_of(" << lhs << ") = " << (v.is_true() ? 1 : 0) << ";\n";
      break;
    case SOAP_TYPE__i4:
    case SOAP_TYPE__int:
      if (optimal)
        indent(ctx, k) << "*int_of(p) = ";
      else
        indent(ctx, k) << "*int_of(" << lhs << ") = ";
      json_send(ctx, v);
      *ctx->os << ";\n";
      break;
    case SOAP_TYPE__double:
      if (optimal)
        indent(ctx, k) << "*double_of(p) = ";
      else
        indent(ctx, k) << "*double_of(" << lhs << ") = ";
      json_send(ctx, v);
      *ctx->os << ";\n";
      break;
    case SOAP_TYPE__string:
      if (optimal)
        indent(ctx, k) << "*string_of(p) = ";
      else
        indent(ctx, k) << "*string_of(" << lhs << ") = ";
      json_send(ctx, v);
      *ctx->os << ";\n";
      break;
    case SOAP_TYPE__struct:
    {
      if (optimal)
      {
        indent(ctx, k) << "{\n";
        k += 2;
        indent(ctx, k) << "struct value *s = p;\n";
      }
      _struct& s = v;
      for (_struct::iterator i = s.begin(); i != s.end(); ++i)
      {
        std::string lhsidx = "value_at(";
        lhsidx.append(lhs).append(", \"").append(i.index()).append("\")"); // TODO later: handle special chars in i.index()
        if (optimal)
        {
          indent(ctx, k) << "p = value_at(s, ";
          json_send_string(ctx, i.index());
          *ctx->os << ");\n";
        }
        code_gen_c(ctx, *i, lhsidx, k);
      }
      if (optimal)
      {
        indent(ctx, k) << "p = s;\n";
        k -= 2;
        indent(ctx, k) << "}\n";
      }
      break;
    }
    case SOAP_TYPE__array:
    {
      if (optimal)
      {
        indent(ctx, k) << "{\n";
        k += 2;
        indent(ctx, k) << "struct value *a = p;\n";
      }
      _array& a = v;
      for (_array::iterator i = a.begin(); i != a.end(); ++i)
      {
        std::string lhsidx = "nth_value(";
        lhsidx.append(lhs).append(", ").append(soap_int2s(ctx, i.index())).append(")");
        if (optimal)
          indent(ctx, k) << "p = nth_value(a, " << i.index() << ");\n";
        code_gen_c(ctx, *i, lhsidx, k);
      }
      if (optimal)
      {
        indent(ctx, k) << "p = a;\n";
        k -= 2;
        indent(ctx, k) << "}\n";
      }
      break;
    }
    default:
      break;
  }
}

static void code_gen_cpp(soap *ctx, value& v, std::string lhs, int k)
{
  if (explain && optimal)
    indent(ctx, k) << "// p = &" << lhs << "\n";
  switch (v.__type)
  {
    case SOAP_TYPE__boolean:
    case SOAP_TYPE__i4:
    case SOAP_TYPE__int:
    case SOAP_TYPE__double:
    case SOAP_TYPE__string:
      if (optimal)
        indent(ctx, k) << "*p = ";
      else
        indent(ctx, k) << lhs << " = ";
      json_send(ctx, v);
      *ctx->os << ";\n";
      break;
    case SOAP_TYPE__struct:
    {
      if (optimal)
      {
        indent(ctx, k) << "{\n";
        k += 2;
        indent(ctx, k) << "value& s = *p;\n";
      }
      _struct& s = v;
      for (_struct::iterator i = s.begin(); i != s.end(); ++i)
      {
        std::string lhsidx = lhs;
        lhsidx.append("[\"").append(i.index()).append("\"]");
        if (optimal)
        {
          indent(ctx, k) << "p = &s[";
          json_send_string(ctx, i.index());
          *ctx->os << "];\n";
        }
        code_gen_cpp(ctx, *i, lhsidx, k);
      }
      if (optimal)
      {
        indent(ctx, k) << "p = &s;\n";
        k -= 2;
        indent(ctx, k) << "}\n";
      }
      break;
    }
    case SOAP_TYPE__array:
    {
      if (optimal)
      {
        indent(ctx, k) << "{\n";
        k += 2;
        indent(ctx, k) << "value& a = *p;\n";
      }
      _array& a = v;
      for (_array::iterator i = a.begin(); i != a.end(); ++i)
      {
        std::string lhsidx = lhs;
        lhsidx.append("[").append(soap_int2s(ctx, i.index())).append("]");
        if (optimal)
          indent(ctx, k) << "p = &a[" << i.index() << "];\n";
        code_gen_cpp(ctx, *i, lhsidx, k);
      }
      if (optimal)
      {
        indent(ctx, k) << "p = &a;\n";
        k -= 2;
        indent(ctx, k) << "}\n";
      }
      break;
    }
    default:
      break;
  }
}

static void path_gen_cpp(struct soap *ctx, const char *jpath, std::string& v, int k, bool throwup)
{
  if (*jpath == '$' || *jpath == '@') // strip $ and @ from path
    ++jpath;
  while (isspace(*jpath) || (*jpath == '.' && *(jpath + 1) != '.')) // skip space and single .
    ++jpath;
  if (*jpath == '.') // path: ..
  {
    ++jpath;
    if (*jpath == '.')
    {
      ++jpath;
      if (explain)
        indent(ctx, k) << "// iterate over descendants of current node " << v << " to match " << jpath << "\n";
      indent(ctx, k) << "std::stack<value*> S;\n";
      indent(ctx, k) << "S.push(&" << v << ");\n";
      indent(ctx, k) << "while (!S.empty())\n";
      indent(ctx, k) << "{\n";
      indent(ctx, k + 2) << "value *q = S.top();\n";
      indent(ctx, k + 2) << "S.pop();\n";
      indent(ctx, k + 2) << "for (int j = q->size()-1; j >= 0; --j)\n";
      indent(ctx, k + 4) << "S.push(&(*q)[j]);\n";
      v = "(*q)";
      path_gen_cpp(ctx, jpath, v, k + 2, throwup);
      indent(ctx, k) << "}\n";
    }
    else
    {
      fprintf(stderr, "jsoncpp: JSONPath unexpected end at '.'\n\n");
      exit(EXIT_FAILURE);
    }
  }
  else if (*jpath == '[') // path: [*]..., [?x], or [(),:]...
  {
    ++jpath;
    if (*jpath == '*') // path: [*]...
    {
      ++jpath;
      if (*jpath != ']')
      {
        fprintf(stderr, "jsoncpp: JSONPath ']' expected at ...->%s\n\n", jpath);
        exit(EXIT_FAILURE);
      }
      ++jpath;
      if (explain)
        indent(ctx, k) << "// iterate over current array/struct node " << v << " to match " << jpath << "\n";
      indent(ctx, k) << "value::iterator j = " << v << ".begin();\n";
      indent(ctx, k) << "value::iterator k = " << v << ".end();\n";
      indent(ctx, k) << "for (value::iterator i = j; i != k; ++i)\n";
      indent(ctx, k) << "{\n";
      v = "(*i)";
      path_gen_cpp(ctx, jpath, v, k + 2, throwup);
      indent(ctx, k) << "}\n";
    }
    else if (*jpath == '?') // path: [?x]... where x is a C++ bool expression
    {
      ++jpath;
      if (*jpath != '(')
      {
        fprintf(stderr, "jsoncpp: JSONPath '(' expected at ...->%s\n\n", jpath);
        exit(EXIT_FAILURE);
      }
      ++jpath;
      int nest = 0;
      const char *s;
      for (s = jpath; *s; ++s)
      {
        if (*s == ')')
        {
          if (nest == 0)
            break;
          --nest;
        }
        else if (*s == '(')
          ++nest;
      }
      if (*s != ')')
      {
        fprintf(stderr, "jsoncpp: JSONPath ')' expected at ...->%s\n\n", jpath);
        exit(EXIT_FAILURE);
      }
      std::string code(jpath, s - jpath);
      jpath = s + 1;
      if (*jpath != ']')
      {
        fprintf(stderr, "jsoncpp: JSONPath ']' expected at ...->%s\n\n", jpath);
        exit(EXIT_FAILURE);
      }
      ++jpath;
      if (explain)
        indent(ctx, k) << "// filter current node " << v << " with [?(" << code << ")] to match " << jpath << "\n";
      indent(ctx, k) << "value& v = " << v << ";\n";
      indent(ctx, k) << "if (" << code << ")\n";
      indent(ctx, k) << "{\n";
      path_gen_cpp(ctx, jpath, v, k + 2, throwup);
      indent(ctx, k) << "}\n";
    }
    else // path: [(),:]...
    {
      int subs = 0;
      std::string code;
      std::string name;
      int start, end, step;
      while (true)
      {
        ++subs;
        code.clear();
        name.clear();
        start = end = step = 0;
        if (*jpath == '(')
        {
          ++jpath;
          int nest = 0;
          const char *s;
          for (s = jpath; *s; ++s)
          {
            if (*s == ')')
            {
              if (nest == 0)
                break;
              --nest;
            }
            else if (*s == '(')
              ++nest;
          }
          if (*s != ')')
          {
            fprintf(stderr, "jsoncpp: JSONPath ')' expected at ...->%s\n\n", jpath);
            exit(EXIT_FAILURE);
          }
          code = std::string(jpath, s - jpath);
          jpath = s + 1;
        }
        else if (*jpath == ':')
        {
          ++jpath;
          bool hasend = true;
          if (*jpath == '-' || *jpath == '+' || isdigit(*jpath))
            end = soap_strtol(jpath, (char**)&jpath, 10);
          else
            hasend = false;
          if (*jpath == ':')
            step = soap_strtol(jpath + 1, (char**)&jpath, 10);
          else
            step = 1;
          if (step > 0) // end is exclusive (Python array slicing)
            --end;
          else if (hasend)
            ++end;
          if (step < 0)
            start = -1;
        }
        else if (*jpath == '\'' || *jpath == '"' || isalpha(*jpath))
        {
          name = getname(&jpath);
        }
        else if (*jpath == '-' || *jpath == '+' || isdigit(*jpath))
        {
          start = soap_strtol(jpath, (char**)&jpath, 10);
          if (*jpath == ':')
          {
            ++jpath;
            bool hasend = true;
            if (*jpath == '-' || *jpath == '+' || isdigit(*jpath))
              end = soap_strtol(jpath, (char**)&jpath, 10);
            else
              hasend = false;
            if (*jpath == ':')
              step = soap_strtol(jpath + 1, (char**)&jpath, 10);
            else
              step = 1;
            if (step > 0) // end is exclusive (Python array slicing)
              --end;
            else if (hasend)
              ++end;
          }
        }
        if ((step > 0 && !(start <= end || (start >= 0 && end < 0))) ||
            (step < 0 && !(start >= end || (start < 0 && end >= 0))))
          {
            fprintf(stderr, "jsoncpp: JSONPath inverted bounds at ...->%s\n\n", jpath);
            exit(EXIT_FAILURE);
          }
        if (subs == 1 && *jpath != ',') // path: [x]... with x a name or index or [start]:[end][:step] slice
          break;
        if (subs == 1) // path: [x,...]... with x a name or index or [start]:[end][:step] slice
        {
          if (explain)
            indent(ctx, k) << "// for each case\n";
          if (v.compare(0, 4, "(*p)") == 0)
          {
            indent(ctx, k) << "value& r = " << v << ";\n";
            v = "r";
          }
          indent(ctx, k) << "int j, k = 1;\n";
          indent(ctx, k) << "value *p;\n";
          indent(ctx, k) << "do\n";
          indent(ctx, k) << "{\n";
          indent(ctx, k + 2) << "switch (k)\n";
          indent(ctx, k + 2) << "{\n";
        }
        indent(ctx, k + 4) << "case " << 2*subs-1 << ":\n";
        if (!code.empty())
        {
          indent(ctx, k + 4) << "{\n";
          if (explain)
            indent(ctx, k + 6) << "// if current node " << v << " is an array/struct with field/element [(" << code << ")] ...\n";
          indent(ctx, k + 6) << "k = " << 2*subs+1 << ";\n";
          indent(ctx, k + 6) << "value& v = " << v << ";\n";
          indent(ctx, k + 6) << "j = v.nth(" << code << ");\n";
          indent(ctx, k + 6) << "if (j >= 0)\n";
          indent(ctx, k + 6) << "{\n";
          indent(ctx, k + 8) << "p = &v[j];\n";
          indent(ctx, k + 8) << "break;\n";
          indent(ctx, k + 6) << "}\n";
          indent(ctx, k + 4) << "}\n";
        }
        else if (!name.empty())
        {
          if (explain)
            indent(ctx, k + 6) << "// if current node " << v << " is a struct with field '" << name << "' ...\n";
          indent(ctx, k + 6) << "k = " << 2*subs+1 << ";\n";
          if (optimal)
          {
            indent(ctx, k + 6) << "j = " << v << ".nth(\"" << name << "\");\n";
            indent(ctx, k + 6) << "if (j >= 0)\n";
            indent(ctx, k + 6) << "{\n";
            indent(ctx, k + 8) << "p = &" << v << "[j];\n";
            indent(ctx, k + 8) << "break;\n";
            indent(ctx, k + 6) << "}\n";
          }
          else
          {
            indent(ctx, k + 6) << "if (" << v << ".has(\"" << name << "\"))\n";
            indent(ctx, k + 6) << "{\n";
            indent(ctx, k + 8) << "p = &" << v << "[\"" << name << "\"];\n";
            indent(ctx, k + 8) << "break;\n";
            indent(ctx, k + 6) << "}\n";
          }
        }
        else if (step > 0)
        {
          if (explain)
            indent(ctx, k + 6) << "// if current node " << v << " is an array then iterate from " << start << " to " << end << " by " << step << " ...\n";
          indent(ctx, k + 6) << "if (!" << v << ".is_array())\n";
          indent(ctx, k + 6) << "{\n";
          indent(ctx, k + 8) << "k = " << 2*subs+1 << ";\n";
          indent(ctx, k + 8) << "continue;\n";
          indent(ctx, k + 6) << "}\n";
          if (start < 0)
            indent(ctx, k + 6) << "j = (" << start << " >= -" << v << ".size() ? " << start << " : -" << v << ".size())-" << step << ";\n";
          else
            indent(ctx, k + 6) << "j = " << start-step << ";\n";
          indent(ctx, k + 6) << "k = " << 2*subs << ";\n";
          indent(ctx, k + 4) << "case " << 2*subs << ":\n";
          indent(ctx, k + 6) << "j += " << step << ";\n";
          if (start >= 0 && end < 0) // : 0 <= start <= size+end where end < 0
            indent(ctx, k + 6) << "if (j <= " << v << ".size()+" << end << ")\n";
          else if (start >= 0 && end >= 0) // : 0 <= start <= end < size
            indent(ctx, k + 6) << "if (j <= " << end << " && j < " << v << ".size())\n";
          else // start < 0 && end < 0 : -size <= start <= end < 0
            indent(ctx, k + 6) << "if (j <= " << end << ")\n";
          indent(ctx, k + 6) << "{\n";
          indent(ctx, k + 8) << "p = &" << v << "[j];\n";
          indent(ctx, k + 8) << "break;\n";
          indent(ctx, k + 6) << "}\n";
          indent(ctx, k + 6) << "else\n";
          indent(ctx, k + 8) << "k = " << 2*subs+1 << ";\n";
        }
        else if (step < 0)
        {
          if (explain)
            indent(ctx, k + 6) << "// if current node " << v << " is an array then iterate from " << start << " to " << end << " by " << step << " ...\n";
          indent(ctx, k + 6) << "if (!" << v << ".is_array())\n";
          indent(ctx, k + 6) << "{\n";
          indent(ctx, k + 8) << "k = " << 2*subs+1 << ";\n";
          indent(ctx, k + 8) << "continue;\n";
          indent(ctx, k + 6) << "}\n";
          if (start < 0 && end >= 0)
            indent(ctx, k + 6) << "j = " << v << ".size()+" << start-step << ";\n";
          else if (start >= 0 && end >= 0)
            indent(ctx, k + 6) << "j = (" << start << " < " << v << ".size() ? " << start << " : " << v << ".size()-1)+" << -step << ";\n";
          else // start < 0 && end < 0
            indent(ctx, k + 6) << "j = " << start-step << ";\n";
          indent(ctx, k + 6) << "k = " << 2*subs << ";\n";
          indent(ctx, k + 4) << "case " << 2*subs << ":\n";
          indent(ctx, k + 6) << "j -= " << -step << ";\n";
          if (start < 0 && end >= 0) // : 0 <= end <= size+start where start < 0
            indent(ctx, k + 6) << "if (j >= " << end << ")\n";
          else if (start >= 0 && end >= 0) // : 0 <= end <= start < size
            indent(ctx, k + 6) << "if (j >= " << end << ")\n";
          else // start < 0 && end < 0 : -size <= end <= start < 0
            indent(ctx, k + 6) << "if (j >= " << end << " && j >= -" << v << ".size()))\n";
          indent(ctx, k + 6) << "{\n";
          indent(ctx, k + 8) << "p = &" << v << "[j];\n";
          indent(ctx, k + 8) << "break;\n";
          indent(ctx, k + 6) << "}\n";
          indent(ctx, k + 6) << "else\n";
          indent(ctx, k + 8) << "k = " << 2*subs+1 << ";\n";
        }
        else
        {
          if (explain)
            indent(ctx, k + 6) << "// if current node " << v << " is an array with element [" << start << "] ...\n";
          indent(ctx, k + 6) << "k = " << 2*subs+1 << ";\n";
          indent(ctx, k + 6) << "if (" << v << ".has(" << start << "))\n";
          indent(ctx, k + 6) << "{\n";
          indent(ctx, k + 8) << "p = &" << v << "[" << start << "];\n";
          indent(ctx, k + 8) << "break;\n";
          indent(ctx, k + 6) << "}\n";
        }
        if (*jpath != ',')
          break;
        ++jpath;
      }
      if (subs == 0 && *jpath == ']')
      {
        fprintf(stderr, "jsoncpp: JSONPath empty '[]' at ...->%s\n\n", jpath);
        exit(EXIT_FAILURE);
      }
      if (*jpath != ']')
      {
        fprintf(stderr, "jsoncpp: JSONPath ']' expected at ...->%s\n\n", jpath);
        exit(EXIT_FAILURE);
      }
      ++jpath;
      if (subs == 1) // path: [x]... with x a name or index or [start]:[end][:step] range
      {
        if (!code.empty())
        {
          if (explain)
            indent(ctx, k) << "// if current node " << v << " is an array/struct with field/element [(" << code << ")] then match " << jpath << "\n";
          indent(ctx, k) << "value& v = " << v << ";\n";
          indent(ctx, k) << "int j = v.nth(" << code << ");\n";
          indent(ctx, k) << "if (j >= 0)\n";
          indent(ctx, k) << "{\n";
          indent(ctx, k + 2) << "value& r = v[j];\n";
          v = "r";
          path_gen_cpp(ctx, jpath, v, k + 2, throwup);
          indent(ctx, k) << "}\n";
        }
        else if (!name.empty())
        {
          if (optimal)
          {
            if (explain)
              indent(ctx, k) << "// if current node " << v << " is a struct with field '" << name << "' then match " << jpath << "\n";
            indent(ctx, k) << "int j = " << v << ".nth(\"" << name << "\");\n";
            indent(ctx, k) << "if (j >= 0)\n";
            indent(ctx, k) << "{\n";
            if (v[0] == 'r')
            {
              indent(ctx, k + 2) << "value& s = " << v << "[j];\n";
              v = "s";
              path_gen_cpp(ctx, jpath, v, k + 2, throwup);
            }
            else
            {
              indent(ctx, k + 2) << "value& r = " << v << "[j];\n";
              v = "r";
              path_gen_cpp(ctx, jpath, v, k + 2, throwup);
            }
            indent(ctx, k) << "}\n";
          }
          else
          {
            indent(ctx, k) << "if (" << v << ".has(\"" << name << "\"))\n";
            indent(ctx, k) << "{\n";
            v.append("[\"").append(name).append("\"]");
            path_gen_cpp(ctx, jpath, v, k + 2, throwup);
            indent(ctx, k) << "}\n";
          }
        }
        else if (step > 0)
        {
          if (explain)
            indent(ctx, k) << "// if current node " << v << " is an array then iterate from " << start << " to " << end << " by " << step << " to match " << jpath << "\n";
          indent(ctx, k) << "if (" << v << ".is_array())\n";
          indent(ctx, k) << "{\n";
          if (start >= 0 && end < 0)
          {
            indent(ctx, k + 2) << "int j, k = " << v << ".size()-" << -end << ";\n";
            indent(ctx, k + 2) << "for (j = " << start << "; j <= k; j += " << step << ")\n";
          }
          else if (start >= 0 && end >= 0)
          {
            indent(ctx, k + 2) << "int j, k = (" << end << " < " << v << ".size() ? " << end << " : " << v << ".size()-1);\n";
            indent(ctx, k + 2) << "for (j = " << start << "; j <= k; j += " << step << ")\n";
          }
          else // start < 0 && end < 0
          {
            indent(ctx, k + 2) << "int j, k = (" << start << " >= -" << v << ".size() ? " << start << " : -" << v << ".size());\n";
            indent(ctx, k + 2) << "for (j = k; j <= " << end << "; j += " << step << ")\n";
          }
          indent(ctx, k + 2) << "{\n";
          if (v[0] == 'r')
          {
            indent(ctx, k + 4) << "value& s = " << v << "[j];\n";
            v = "s";
            path_gen_cpp(ctx, jpath, v, k + 4, throwup);
          }
          else
          {
            indent(ctx, k + 4) << "value& r = " << v << "[j];\n";
            v = "r";
            path_gen_cpp(ctx, jpath, v, k + 4, throwup);
          }
          indent(ctx, k + 2) << "}\n";
          indent(ctx, k) << "}\n";
        }
        else if (step < 0)
        {
          if (explain)
            indent(ctx, k) << "// if current node " << v << " is an array then iterate from " << start << " to " << end << " by " << step << " to match " << jpath << "\n";
          indent(ctx, k) << "if (" << v << ".is_array())\n";
          indent(ctx, k) << "{\n";
          if (start < 0 && end >= 0)
          {
            indent(ctx, k + 2) << "int j, k = " << v << ".size()-" << -start << ";\n";
            indent(ctx, k + 2) << "for (j = k; j >= " << end << "; j -= " << -step << ")\n";
          }
          else if (start >= 0 && end >= 0)
          {
            indent(ctx, k + 2) << "int j, k = (" << start << " < " << v << ".size() ? " << start << " : " << v << ".size()-1);\n";
            indent(ctx, k + 2) << "for (j = k; j >= " << end << "; j -= " << -step << ")\n";
          }
          else // start < 0 && end < 0
          {
            indent(ctx, k + 2) << "int j, k = (" << end << " >= -" << v << ".size() ? " << end << " : -" << v << ".size());\n";
            indent(ctx, k + 2) << "for (j = " << start << "; j >= k; j -= " << -step << ")\n";
          }
          indent(ctx, k + 2) << "{\n";
          if (v[0] == 'r')
          {
            indent(ctx, k + 4) << "value& s = " << v << "[j];\n";
            v = "s";
            path_gen_cpp(ctx, jpath, v, k + 4, throwup);
          }
          else
          {
            indent(ctx, k + 4) << "value& r = " << v << "[j];\n";
            v = "r";
            path_gen_cpp(ctx, jpath, v, k + 4, throwup);
          }
          indent(ctx, k + 2) << "}\n";
          indent(ctx, k) << "}\n";
        }
        else
        {
          if (explain)
            indent(ctx, k) << "// if current node " << v << " is an array with element [" << start << "] then match " << jpath << "\n";
          indent(ctx, k) << "if (" << v << ".has(" << start << "))\n";
          indent(ctx, k) << "{\n";
          v.append("[").append(soap_int2s(ctx, start)).append("]");
          path_gen_cpp(ctx, jpath, v, k + 2, throwup);
          indent(ctx, k) << "}\n";
        }
      }
      else
      {
        indent(ctx, k + 4) << "default:\n";
        indent(ctx, k + 6) << "continue;\n";
        indent(ctx, k + 2) << "}\n";
        if (explain)
          indent(ctx, k + 2) << "// ... then match " << jpath << "\n";
        v = "(*p)";
        path_gen_cpp(ctx, jpath, v, k + 2, throwup);
        indent(ctx, k) << "} while (k <= " << 2*subs << ");\n";
      }
    }
  }
  else if (*jpath == '?') // path: P?Q means all values P such that Q (has at least one result)
  {
    if (throwup)
    {
      fprintf(stderr, "jsoncpp: JSONPath cannot nest '?' and '!' ...->%s\n\n", jpath);
      exit(EXIT_FAILURE);
    }
    ++jpath;
    if (explain)
      indent(ctx, k) << "// value of current node " << v << " if its descendants match " << jpath << "\n";
    indent(ctx, k) << "try\n";
    indent(ctx, k) << "{\n";
    std::string u = v;
    path_gen_cpp(ctx, jpath, v, k + 2, true);
    indent(ctx, k) << "}\n";
    indent(ctx, k) << "catch (const bool&)\n";
    indent(ctx, k) << "{\n";
    path_exec(ctx, u, k + 2);
    indent(ctx, k) << "}\n";
  }
  else if (*jpath == '!') // path: P!Q means all values P such that not Q (has no results)
  {
    if (throwup)
    {
      fprintf(stderr, "jsoncpp: JSONPath cannot nest '?' and '!' ...->%s\n\n", jpath);
      exit(EXIT_FAILURE);
    }
    ++jpath;
    if (explain)
      indent(ctx, k) << "// value of current node " << v << " if its descendants do not match " << jpath << "\n";
    indent(ctx, k) << "try\n";
    indent(ctx, k) << "{\n";
    std::string u = v;
    path_gen_cpp(ctx, jpath, v, k + 2, true);
    indent(ctx, k + 2) << "throw false;\n";
    indent(ctx, k) << "}\n";
    indent(ctx, k) << "catch (const bool& k)\n";
    indent(ctx, k) << "{\n";
    indent(ctx, k + 2) << "if (k == false)\n";
    path_exec(ctx, u, k + 4);
    indent(ctx, k) << "}\n";
  }
  else if (*jpath == '*') // path: *...
  {
    ++jpath;
    if (explain)
      indent(ctx, k) << "// iterate over current array/struct node " << v << " to match " << jpath << "\n";
    indent(ctx, k) << "value::iterator j = " << v << ".begin();\n";
    indent(ctx, k) << "value::iterator k = " << v << ".end();\n";
    indent(ctx, k) << "for (value::iterator i = j; i != k; ++i)\n";
    indent(ctx, k) << "{\n";
    v = "(*i)";
    path_gen_cpp(ctx, jpath, v, k + 2, throwup);
    indent(ctx, k) << "}\n";
  }
  else if (!*jpath)
  {
    if (throwup)
      indent(ctx, k) << "throw true;\n";
    else
      path_exec(ctx, v, k);
  }
  else // path: name...
  {
    std::string name = getname(&jpath);
    if (explain)
      indent(ctx, k) << "// if current node " << v << " is a struct with field '" << name << "' then match " << jpath << "\n";
    if (optimal)
    {
      indent(ctx, k) << "int j = " << v << ".nth(\"" << name << "\");\n";
      indent(ctx, k) << "if (j >= 0)\n";
      indent(ctx, k) << "{\n";
      if (v[0] == 'r')
      {
        indent(ctx, k + 2) << "value& s = " << v << "[j];\n";
        v = "s";
        path_gen_cpp(ctx, jpath, v, k + 2, throwup);
      }
      else
      {
        indent(ctx, k + 2) << "value& r = " << v << "[j];\n";
        v = "r";
        path_gen_cpp(ctx, jpath, v, k + 2, throwup);
      }
      indent(ctx, k) << "}\n";
    }
    else
    {
      indent(ctx, k) << "if (" << v << ".has(\"" << name << "\"))\n";
      indent(ctx, k) << "{\n";
      v.append("[\"").append(name).append("\"]");
      path_gen_cpp(ctx, jpath, v, k + 2, throwup);
      indent(ctx, k) << "}\n";
    }
  }
}

static void path_exec(struct soap *ctx, std::string& v, int k)
{
  if (jcode)
  {
    indent(ctx, k) << "value& v = " << v << ";\n";
    indent(ctx, k) << jcode << "\n";
  }
  else
  {
    indent(ctx, k) << "QUERY_YIELD(" << v << ");\n";
  }
}

static std::string getname(const char **jpath)
{
  const char *s = *jpath;
  const char *t = s;
  if (*t == '\'' || *t == '"')
  {
    while (*++t && *t != *s)
      if (*t == '\\' && *(t+1))
        ++t;
    if (*t)
      ++t;
    if (t == s + 2)
    {
      fprintf(stderr, "jsoncpp: JSONPath empty field name at ...->%s\n\n", s);
      exit(EXIT_FAILURE);
    }
    *jpath = t;
    return std::string(s + 1, t - s - 2);
  }
  while (*t && !ispunct(*t) && !isspace(*t))
    ++t;
  if (t == s)
  {
    fprintf(stderr, "jsoncpp: JSONPath empty field name at ...->%s\n\n", s);
    exit(EXIT_FAILURE);
  }
  *jpath = t;
  return std::string(s, t - s);
}

static std::ostream& indent(soap *ctx, int k)
{
  *ctx->os << std::setw(k) << "" << std::setw(0);
  return *ctx->os;
}
