/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 42 "soapcpp2_yacc.y"


#include "soapcpp2.h"

#ifdef WIN32
#ifndef __STDC__
#define __STDC__
#endif
#define YYINCLUDED_STDLIB_H
#ifdef WIN32_WITHOUT_SOLARIS_FLEX
extern int soapcpp2lex(void);
#else
extern int yylex(void);
#endif
#else
extern int yylex(void);
#endif

#define MAXNEST 16      /* max. nesting depth of scopes */

typedef struct Scope
{
  Table   *table;
  Entry   *entry;
  Node    node;
  LONG64  val;
  int     offset;
  Bool    grow;   /* true if offset grows with declarations */
  Bool    mask;   /* true if enum is mask */
} Scope;

Scope stack[MAXNEST], /* stack of tables and offsets */
      *sp;            /* current scope stack pointer */

Table *classtable = NULL,
      *enumtable = NULL,
      *typetable = NULL,
      *booltable = NULL,
      *templatetable = NULL;

int     transient = 0;
int     permission = 0;
int     custom_header = 1;
int     custom_fault = 1;
Pragma  *pragmas = NULL;
Tnode   *qname = NULL;
Tnode   *xml = NULL;

/* function prototypes for support routine section */
static Entry      *undefined(Symbol*);
static Tnode      *mgtype(Tnode*, Tnode*);
static Node       op(const char*, Node, Node),
                  iop(const char*, Node, Node),
                  relop(const char*, Node, Node);
static void       mkscope(Table*, int),
                  enterscope(Table*, int),
                  exitscope(void);
static int        integer(Tnode*),
                  real(Tnode*),
                  numeric(Tnode*);
static void       set_value(Entry *p, Tnode *t, Node *n),
                  add_soap(void),
                  add_XML(void),
                  add_qname(void),
                  add_header(void),
                  add_fault(void),
                  add_response(Entry*, Entry*),
                  add_result(Tnode*),
                  add_request(Symbol*, Scope*),
                  add_pragma(const char*);

/* imported from symbol2.c */
extern int        is_string(Tnode*),
                  is_wstring(Tnode*),
                  is_smart(Tnode*),
                  is_XML(Tnode*),
                  is_stdXML(Tnode*),
                  is_anyType(Tnode*),
                  is_anyAttribute(Tnode*);
extern char       *c_storage(Storage);
extern const char *c_type(Tnode*);
extern int        is_primitive_or_string(Tnode*),
                  is_stdstr(Tnode*),
                  is_binary(Tnode*),
                  is_external(Tnode*),
                  is_mutable(Entry*);
extern Entry      *unlinklast(Table*);

/* Temporaries used in semantic rules */
int        i;
char       *s, *s1;
const char *s2;
Symbol     *sym;
Entry      *p, *q;
Tnode      *t;
Node       tmp, c;


#line 170 "soapcpp2_yacc.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "soapcpp2_yacc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PRAGMA = 3,                     /* PRAGMA  */
  YYSYMBOL_AUTO = 4,                       /* AUTO  */
  YYSYMBOL_DOUBLE = 5,                     /* DOUBLE  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_STRUCT = 7,                     /* STRUCT  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_LONG = 10,                      /* LONG  */
  YYSYMBOL_SWITCH = 11,                    /* SWITCH  */
  YYSYMBOL_CASE = 12,                      /* CASE  */
  YYSYMBOL_ENUM = 13,                      /* ENUM  */
  YYSYMBOL_REGISTER = 14,                  /* REGISTER  */
  YYSYMBOL_TYPEDEF = 15,                   /* TYPEDEF  */
  YYSYMBOL_CHAR = 16,                      /* CHAR  */
  YYSYMBOL_EXTERN = 17,                    /* EXTERN  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_UNION = 19,                     /* UNION  */
  YYSYMBOL_CONST = 20,                     /* CONST  */
  YYSYMBOL_FLOAT = 21,                     /* FLOAT  */
  YYSYMBOL_SHORT = 22,                     /* SHORT  */
  YYSYMBOL_UNSIGNED = 23,                  /* UNSIGNED  */
  YYSYMBOL_CONTINUE = 24,                  /* CONTINUE  */
  YYSYMBOL_FOR = 25,                       /* FOR  */
  YYSYMBOL_SIGNED = 26,                    /* SIGNED  */
  YYSYMBOL_VOID = 27,                      /* VOID  */
  YYSYMBOL_DEFAULT = 28,                   /* DEFAULT  */
  YYSYMBOL_GOTO = 29,                      /* GOTO  */
  YYSYMBOL_SIZEOF = 30,                    /* SIZEOF  */
  YYSYMBOL_VOLATILE = 31,                  /* VOLATILE  */
  YYSYMBOL_DO = 32,                        /* DO  */
  YYSYMBOL_IF = 33,                        /* IF  */
  YYSYMBOL_STATIC = 34,                    /* STATIC  */
  YYSYMBOL_WHILE = 35,                     /* WHILE  */
  YYSYMBOL_CLASS = 36,                     /* CLASS  */
  YYSYMBOL_PRIVATE = 37,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 38,                 /* PROTECTED  */
  YYSYMBOL_PUBLIC = 39,                    /* PUBLIC  */
  YYSYMBOL_VIRTUAL = 40,                   /* VIRTUAL  */
  YYSYMBOL_INLINE = 41,                    /* INLINE  */
  YYSYMBOL_OPERATOR = 42,                  /* OPERATOR  */
  YYSYMBOL_LLONG = 43,                     /* LLONG  */
  YYSYMBOL_BOOL = 44,                      /* BOOL  */
  YYSYMBOL_CFALSE = 45,                    /* CFALSE  */
  YYSYMBOL_CTRUE = 46,                     /* CTRUE  */
  YYSYMBOL_WCHAR = 47,                     /* WCHAR  */
  YYSYMBOL_TIME = 48,                      /* TIME  */
  YYSYMBOL_USING = 49,                     /* USING  */
  YYSYMBOL_NAMESPACE = 50,                 /* NAMESPACE  */
  YYSYMBOL_ULLONG = 51,                    /* ULLONG  */
  YYSYMBOL_MUSTUNDERSTAND = 52,            /* MUSTUNDERSTAND  */
  YYSYMBOL_SIZE = 53,                      /* SIZE  */
  YYSYMBOL_FRIEND = 54,                    /* FRIEND  */
  YYSYMBOL_TEMPLATE = 55,                  /* TEMPLATE  */
  YYSYMBOL_EXPLICIT = 56,                  /* EXPLICIT  */
  YYSYMBOL_TYPENAME = 57,                  /* TYPENAME  */
  YYSYMBOL_MUTABLE = 58,                   /* MUTABLE  */
  YYSYMBOL_null = 59,                      /* null  */
  YYSYMBOL_RESTRICT = 60,                  /* RESTRICT  */
  YYSYMBOL_FINAL = 61,                     /* FINAL  */
  YYSYMBOL_OVERRIDE = 62,                  /* OVERRIDE  */
  YYSYMBOL_UCHAR = 63,                     /* UCHAR  */
  YYSYMBOL_USHORT = 64,                    /* USHORT  */
  YYSYMBOL_UINT = 65,                      /* UINT  */
  YYSYMBOL_ULONG = 66,                     /* ULONG  */
  YYSYMBOL_NONE = 67,                      /* NONE  */
  YYSYMBOL_ID = 68,                        /* ID  */
  YYSYMBOL_LAB = 69,                       /* LAB  */
  YYSYMBOL_TYPE = 70,                      /* TYPE  */
  YYSYMBOL_LNG = 71,                       /* LNG  */
  YYSYMBOL_DBL = 72,                       /* DBL  */
  YYSYMBOL_CHR = 73,                       /* CHR  */
  YYSYMBOL_TAG = 74,                       /* TAG  */
  YYSYMBOL_STR = 75,                       /* STR  */
  YYSYMBOL_76_ = 76,                       /* ','  */
  YYSYMBOL_77_ = 77,                       /* '='  */
  YYSYMBOL_PA = 78,                        /* PA  */
  YYSYMBOL_NA = 79,                        /* NA  */
  YYSYMBOL_TA = 80,                        /* TA  */
  YYSYMBOL_DA = 81,                        /* DA  */
  YYSYMBOL_MA = 82,                        /* MA  */
  YYSYMBOL_AA = 83,                        /* AA  */
  YYSYMBOL_XA = 84,                        /* XA  */
  YYSYMBOL_OA = 85,                        /* OA  */
  YYSYMBOL_LA = 86,                        /* LA  */
  YYSYMBOL_RA = 87,                        /* RA  */
  YYSYMBOL_88_ = 88,                       /* '?'  */
  YYSYMBOL_89_ = 89,                       /* ':'  */
  YYSYMBOL_OR = 90,                        /* OR  */
  YYSYMBOL_AN = 91,                        /* AN  */
  YYSYMBOL_92_ = 92,                       /* '|'  */
  YYSYMBOL_93_ = 93,                       /* '^'  */
  YYSYMBOL_94_ = 94,                       /* '&'  */
  YYSYMBOL_EQ = 95,                        /* EQ  */
  YYSYMBOL_NE = 96,                        /* NE  */
  YYSYMBOL_97_ = 97,                       /* '<'  */
  YYSYMBOL_LE = 98,                        /* LE  */
  YYSYMBOL_99_ = 99,                       /* '>'  */
  YYSYMBOL_GE = 100,                       /* GE  */
  YYSYMBOL_LS = 101,                       /* LS  */
  YYSYMBOL_RS = 102,                       /* RS  */
  YYSYMBOL_103_ = 103,                     /* '+'  */
  YYSYMBOL_104_ = 104,                     /* '-'  */
  YYSYMBOL_105_ = 105,                     /* '*'  */
  YYSYMBOL_106_ = 106,                     /* '/'  */
  YYSYMBOL_107_ = 107,                     /* '%'  */
  YYSYMBOL_AR = 108,                       /* AR  */
  YYSYMBOL_PP = 109,                       /* PP  */
  YYSYMBOL_NN = 110,                       /* NN  */
  YYSYMBOL_111_ = 111,                     /* '{'  */
  YYSYMBOL_112_ = 112,                     /* '}'  */
  YYSYMBOL_113_ = 113,                     /* ';'  */
  YYSYMBOL_114_ = 114,                     /* '['  */
  YYSYMBOL_115_ = 115,                     /* ']'  */
  YYSYMBOL_116_ = 116,                     /* ')'  */
  YYSYMBOL_117_ = 117,                     /* '!'  */
  YYSYMBOL_118_ = 118,                     /* '~'  */
  YYSYMBOL_119_ = 119,                     /* '('  */
  YYSYMBOL_120_ = 120,                     /* '@'  */
  YYSYMBOL_121_ = 121,                     /* '$'  */
  YYSYMBOL_YYACCEPT = 122,                 /* $accept  */
  YYSYMBOL_prog = 123,                     /* prog  */
  YYSYMBOL_s1 = 124,                       /* s1  */
  YYSYMBOL_exts = 125,                     /* exts  */
  YYSYMBOL_exts1 = 126,                    /* exts1  */
  YYSYMBOL_ext = 127,                      /* ext  */
  YYSYMBOL_pragma = 128,                   /* pragma  */
  YYSYMBOL_decls = 129,                    /* decls  */
  YYSYMBOL_t1 = 130,                       /* t1  */
  YYSYMBOL_t2 = 131,                       /* t2  */
  YYSYMBOL_t3 = 132,                       /* t3  */
  YYSYMBOL_t4 = 133,                       /* t4  */
  YYSYMBOL_t5 = 134,                       /* t5  */
  YYSYMBOL_dclrs = 135,                    /* dclrs  */
  YYSYMBOL_dclr = 136,                     /* dclr  */
  YYSYMBOL_fdclr = 137,                    /* fdclr  */
  YYSYMBOL_id = 138,                       /* id  */
  YYSYMBOL_name = 139,                     /* name  */
  YYSYMBOL_ctor = 140,                     /* ctor  */
  YYSYMBOL_dtor = 141,                     /* dtor  */
  YYSYMBOL_func = 142,                     /* func  */
  YYSYMBOL_fname = 143,                    /* fname  */
  YYSYMBOL_fargso = 144,                   /* fargso  */
  YYSYMBOL_fargs = 145,                    /* fargs  */
  YYSYMBOL_farg = 146,                     /* farg  */
  YYSYMBOL_arg = 147,                      /* arg  */
  YYSYMBOL_sym = 148,                      /* sym  */
  YYSYMBOL_texpf = 149,                    /* texpf  */
  YYSYMBOL_texp = 150,                     /* texp  */
  YYSYMBOL_spec = 151,                     /* spec  */
  YYSYMBOL_tspec = 152,                    /* tspec  */
  YYSYMBOL_type = 153,                     /* type  */
  YYSYMBOL_structid = 154,                 /* structid  */
  YYSYMBOL_struct = 155,                   /* struct  */
  YYSYMBOL_classid = 156,                  /* classid  */
  YYSYMBOL_class = 157,                    /* class  */
  YYSYMBOL_unionid = 158,                  /* unionid  */
  YYSYMBOL_union = 159,                    /* union  */
  YYSYMBOL_enum = 160,                     /* enum  */
  YYSYMBOL_enumsc = 161,                   /* enumsc  */
  YYSYMBOL_mask = 162,                     /* mask  */
  YYSYMBOL_masksc = 163,                   /* masksc  */
  YYSYMBOL_sc = 164,                       /* sc  */
  YYSYMBOL_utype = 165,                    /* utype  */
  YYSYMBOL_tname = 166,                    /* tname  */
  YYSYMBOL_base = 167,                     /* base  */
  YYSYMBOL_s2 = 168,                       /* s2  */
  YYSYMBOL_s3 = 169,                       /* s3  */
  YYSYMBOL_s4 = 170,                       /* s4  */
  YYSYMBOL_s5 = 171,                       /* s5  */
  YYSYMBOL_s6 = 172,                       /* s6  */
  YYSYMBOL_store = 173,                    /* store  */
  YYSYMBOL_const = 174,                    /* const  */
  YYSYMBOL_abstract = 175,                 /* abstract  */
  YYSYMBOL_virtual = 176,                  /* virtual  */
  YYSYMBOL_ptrs = 177,                     /* ptrs  */
  YYSYMBOL_array = 178,                    /* array  */
  YYSYMBOL_arrayck = 179,                  /* arrayck  */
  YYSYMBOL_brinit = 180,                   /* brinit  */
  YYSYMBOL_init = 181,                     /* init  */
  YYSYMBOL_tag = 182,                      /* tag  */
  YYSYMBOL_occurs = 183,                   /* occurs  */
  YYSYMBOL_bounds = 184,                   /* bounds  */
  YYSYMBOL_nullptr = 185,                  /* nullptr  */
  YYSYMBOL_patt = 186,                     /* patt  */
  YYSYMBOL_value = 187,                    /* value  */
  YYSYMBOL_min = 188,                      /* min  */
  YYSYMBOL_minmax = 189,                   /* minmax  */
  YYSYMBOL_max = 190,                      /* max  */
  YYSYMBOL_expr = 191,                     /* expr  */
  YYSYMBOL_cexp = 192,                     /* cexp  */
  YYSYMBOL_qexp = 193,                     /* qexp  */
  YYSYMBOL_oexp = 194,                     /* oexp  */
  YYSYMBOL_obex = 195,                     /* obex  */
  YYSYMBOL_aexp = 196,                     /* aexp  */
  YYSYMBOL_abex = 197,                     /* abex  */
  YYSYMBOL_rexp = 198,                     /* rexp  */
  YYSYMBOL_lexp = 199,                     /* lexp  */
  YYSYMBOL_pexp = 200                      /* pexp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1703

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  122
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  79
/* YYNRULES -- Number of rules.  */
#define YYNRULES  301
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  469

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   351


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   117,     2,     2,   121,   107,    94,     2,
     119,   116,   105,   103,    76,   104,     2,   106,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    89,   113,
      97,    77,    99,    88,   120,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   114,     2,   115,    93,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   111,    92,   112,   118,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    90,    91,    95,    96,    98,   100,   101,   102,   108,
     109,   110
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   223,   223,   243,   258,   260,   262,   267,   269,   270,
     271,   272,   273,   283,   292,   296,   298,   300,   302,   304,
     306,   307,   312,   314,   316,   318,   320,   322,   323,   324,
     326,   327,   328,   329,   331,   333,   338,   343,   467,   485,
     486,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   537,
     559,   593,   654,   656,   657,   659,   660,   662,   666,   671,
     674,   696,   740,   772,   773,   780,   782,   790,   795,   836,
     888,   895,   900,   941,   993,   994,   995,   996,   997,   998,
     999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,  1008,
    1009,  1010,  1011,  1012,  1022,  1048,  1075,  1099,  1103,  1131,
    1156,  1177,  1205,  1230,  1251,  1278,  1305,  1314,  1323,  1337,
    1351,  1368,  1386,  1416,  1490,  1496,  1501,  1505,  1511,  1517,
    1523,  1530,  1535,  1560,  1565,  1592,  1597,  1622,  1640,  1659,
    1681,  1704,  1709,  1715,  1716,  1717,  1718,  1719,  1720,  1721,
    1731,  1735,  1737,  1738,  1739,  1741,  1743,  1744,  1745,  1754,
    1755,  1757,  1765,  1774,  1781,  1782,  1784,  1793,  1794,  1795,
    1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,
    1807,  1808,  1813,  1814,  1815,  1817,  1818,  1819,  1820,  1823,
    1824,  1826,  1827,  1829,  1830,  1838,  1843,  1849,  1850,  1868,
    1873,  1888,  1889,  1904,  1908,  1922,  1937,  1938,  1940,  1954,
    1970,  1987,  2012,  2033,  2048,  2065,  2090,  2110,  2111,  2113,
    2114,  2116,  2117,  2118,  2119,  2120,  2122,  2123,  2124,  2125,
    2127,  2128,  2129,  2130,  2131,  2133,  2134,  2135,  2144,  2145,
    2148,  2154,  2157,  2160,  2164,  2166,  2169,  2172,  2174,  2177,
    2178,  2179,  2180,  2181,  2182,  2183,  2184,  2185,  2186,  2187,
    2188,  2189,  2190,  2191,  2192,  2193,  2196,  2202,  2208,  2221,
    2222,  2233,  2238,  2245,  2248,  2249,  2258,  2264,  2270,  2276,
    2282,  2288
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PRAGMA", "AUTO",
  "DOUBLE", "INT", "STRUCT", "BREAK", "ELSE", "LONG", "SWITCH", "CASE",
  "ENUM", "REGISTER", "TYPEDEF", "CHAR", "EXTERN", "RETURN", "UNION",
  "CONST", "FLOAT", "SHORT", "UNSIGNED", "CONTINUE", "FOR", "SIGNED",
  "VOID", "DEFAULT", "GOTO", "SIZEOF", "VOLATILE", "DO", "IF", "STATIC",
  "WHILE", "CLASS", "PRIVATE", "PROTECTED", "PUBLIC", "VIRTUAL", "INLINE",
  "OPERATOR", "LLONG", "BOOL", "CFALSE", "CTRUE", "WCHAR", "TIME", "USING",
  "NAMESPACE", "ULLONG", "MUSTUNDERSTAND", "SIZE", "FRIEND", "TEMPLATE",
  "EXPLICIT", "TYPENAME", "MUTABLE", "null", "RESTRICT", "FINAL",
  "OVERRIDE", "UCHAR", "USHORT", "UINT", "ULONG", "NONE", "ID", "LAB",
  "TYPE", "LNG", "DBL", "CHR", "TAG", "STR", "','", "'='", "PA", "NA",
  "TA", "DA", "MA", "AA", "XA", "OA", "LA", "RA", "'?'", "':'", "OR", "AN",
  "'|'", "'^'", "'&'", "EQ", "NE", "'<'", "LE", "'>'", "GE", "LS", "RS",
  "'+'", "'-'", "'*'", "'/'", "'%'", "AR", "PP", "NN", "'{'", "'}'", "';'",
  "'['", "']'", "')'", "'!'", "'~'", "'('", "'@'", "'$'", "$accept",
  "prog", "s1", "exts", "exts1", "ext", "pragma", "decls", "t1", "t2",
  "t3", "t4", "t5", "dclrs", "dclr", "fdclr", "id", "name", "ctor", "dtor",
  "func", "fname", "fargso", "fargs", "farg", "arg", "sym", "texpf",
  "texp", "spec", "tspec", "type", "structid", "struct", "classid",
  "class", "unionid", "union", "enum", "enumsc", "mask", "masksc", "sc",
  "utype", "tname", "base", "s2", "s3", "s4", "s5", "s6", "store", "const",
  "abstract", "virtual", "ptrs", "array", "arrayck", "brinit", "init",
  "tag", "occurs", "bounds", "nullptr", "patt", "value", "min", "minmax",
  "max", "expr", "cexp", "qexp", "oexp", "obex", "aexp", "abex", "rexp",
  "lexp", "pexp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-366)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-269)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -366,    40,   -20,  -366,   -27,  -366,   256,   -56,   -39,  -366,
    -366,  -366,  -366,    16,  -366,    25,  -366,  -366,  -366,  -366,
    -366,    20,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
      21,   -13,  -366,   374,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,    10,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,   -22,    37,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,   -30,  -366,  -366,  -366,  -366,  -366,    34,  1091,    82,
    -366,   -38,    54,    86,  -366,   105,   108,   113,   119,  1484,
      31,  -366,    27,  -366,  -366,  -366,    36,  -366,  -366,  -366,
     126,   134,   -21,   -21,    17,  -366,    69,    69,   139,  -366,
     141,   142,  -366,  -366,    56,  -366,   167,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,   150,
    -366,  -366,   152,  -366,  -366,   495,   616,     9,  -366,    -1,
    1484,  -366,  -366,  -366,   165,  -366,  -366,  -366,    96,  -366,
     855,  -366,    26,   855,  -366,   855,  -366,  -366,  -366,  -366,
    -366,  -366,   -21,  1212,  -366,  -366,  -366,   855,  -366,  -366,
    -366,  -366,   196,   196,  1330,    32,  -366,  -366,  -366,   855,
    -366,   855,    30,  -366,  -366,   115,  -366,  -366,  -366,  -366,
    -366,   -21,  1584,  1584,  -366,   190,  -366,  -366,  -366,  -366,
    -366,  -366,    93,  -366,  -366,  -366,  -366,    38,   202,   204,
     206,   737,   189,   973,    -9,   -21,   -21,    26,    26,    26,
    -366,   191,   193,   194,  1330,  1330,  1330,  1330,  -366,  -366,
     201,  1330,  -366,  -366,     0,   239,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,   211,   213,   240,   123,  -366,   217,   234,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  1584,  1584,  1584,
    1584,  1584,  1584,  1584,  -366,    84,   155,   264,   266,   733,
    -366,  -366,  -366,  -366,   117,  -366,  1413,  -366,   288,  -366,
    -366,  -366,  -366,  -366,  -366,   249,   737,  -366,  -366,  -366,
    -366,  -366,   855,  -366,  -366,   239,   239,   239,   239,  -366,
     239,   257,   270,  -366,  -366,  -366,   240,   253,   347,  1484,
    -366,  -366,  -366,  -366,  -366,  -366,   -18,  -366,  1584,  1584,
    1584,  1584,  1584,  1584,  1584,  1584,  1584,  1584,  1584,  1584,
    1584,  1584,  1584,  1584,  1584,  1584,  1584,  -366,   124,   282,
    -366,   309,  -366,   327,   737,   737,   737,   737,  -366,   287,
     290,   291,   292,   294,   295,  -366,  -366,   240,   -21,   293,
    1584,  -366,   335,   323,   264,   733,   833,   847,   949,   858,
     858,   226,   226,   226,   226,   463,   463,   232,   232,  -366,
    -366,  -366,  1413,    19,  -366,  -366,  1555,   153,  -366,    75,
     338,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,  1584,   300,    80,  -366,   240,
    -366,    -1,  1584,  -366,  -366,  -366,   263,  -366,  -366,  -366,
    -366,  -366,   348,  -366,   288,  -366,   308,  -366,  -366,  -366,
     326,  -366,   177,   177,   -54,   177,  -366,   327,  -366,  -366,
    -366,  -366,   502,   269,  -366,   177,  -366,    -1,    88,  -366,
     623,  -366,  -366,   342,   353,  -366,   362,  -366,  -366
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       3,     0,     6,     1,     0,     2,     0,     0,     0,    13,
     187,   115,   109,     0,   110,     0,   188,   192,   106,   191,
     200,     0,   194,   114,   108,   117,   116,   104,   203,   189,
       0,   193,   198,     0,   111,   105,   107,   122,   112,   199,
     113,   197,     0,   190,   204,   195,   196,   118,   119,   120,
     121,   226,   142,    22,    23,   201,   202,     7,     9,    10,
      11,     0,    41,    79,    82,    82,    32,   213,     0,     0,
     181,     0,   127,     0,   182,     0,     0,     0,     0,     0,
       0,     6,     0,   146,    12,    36,     0,    39,    40,   181,
     130,     0,     0,     0,     0,   181,   140,   141,     0,   182,
     133,     0,   181,   154,     0,   193,   142,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    75,    73,    74,     0,
      42,    43,     0,    78,   213,     0,     0,     0,   227,   223,
       0,   213,     8,    30,     0,    31,    28,    82,     0,    99,
       0,   151,     0,     0,   153,     0,   155,   181,   181,   183,
     183,    98,     0,     0,   144,   145,   148,     0,   150,   161,
     162,   183,   171,   171,     0,   170,   157,   158,   149,     0,
     147,     0,     0,    76,    77,   217,   103,   102,   173,   172,
     174,     0,     0,     0,    92,     0,    93,   213,    33,    82,
     186,    29,   217,   216,   215,   214,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     178,     0,     0,     0,     0,     0,     0,     0,    80,     4,
       0,     0,   159,   160,     0,   184,   166,   167,   163,   165,
     168,   164,   169,     0,     0,   217,     0,    95,     0,     0,
     300,   301,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,   224,   261,     0,   264,     0,   267,
     285,   293,   225,   143,   217,    34,     0,   220,   226,    21,
      24,    25,    26,    20,   129,     0,     0,   179,   180,   176,
     175,   177,     0,   125,   132,   184,   184,   184,   184,   128,
     184,   213,     0,   131,   124,    96,   217,     0,     0,     0,
     291,   289,   288,   290,   286,   287,     0,   259,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   186,     0,     0,
      84,    85,   213,   237,     0,     0,     0,     0,    15,     0,
       0,     0,     0,     0,     0,   134,   219,   217,     0,     0,
       0,   294,   262,     0,   263,   266,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,     0,     0,    88,   205,     0,   217,   238,   223,
     239,    16,    17,    18,    19,   126,   136,   137,   138,   139,
     135,   218,   123,   292,   258,     0,     0,   209,    86,   217,
      89,   223,     0,    37,   221,   240,   233,   260,    94,   206,
     207,   208,     0,    81,   226,    90,     0,   242,   241,   243,
     255,   257,     0,     0,   246,     0,   210,   237,   222,   256,
     244,   245,   247,   249,   234,     0,   236,   223,   228,   252,
     248,   235,    91,   229,     0,   253,   230,   232,   231
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -366,  -366,  -366,  -366,   360,  -366,  -366,  -152,     8,   147,
    -366,  -366,  -366,    -2,   367,   376,   -12,   304,  -366,  -366,
     -46,  -366,    57,    67,  -366,  -366,  -366,  -366,  -140,    94,
     -25,   -33,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,   391,   -74,  -366,   122,   -45,   387,    29,   140,
     143,   -31,  -366,  -366,  -366,  -137,  -183,  -252,  -366,  -365,
    -273,  -366,  -366,    42,  -366,  -267,  -366,  -366,  -366,  -292,
    -197,  -366,  -366,  -366,   158,  -366,   478,    76,  -366
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,     5,     6,    57,    58,   222,   223,    60,
     354,   355,   356,   224,   208,   209,    62,    63,    64,    65,
     153,   154,   349,   350,   351,   420,    66,   205,   143,    67,
     352,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    97,   186,   201,   231,   161,   166,   236,   312,
     286,    79,   417,   433,    80,   158,   287,   288,   423,   204,
     149,   457,   399,   400,   426,   444,   454,   455,   445,   326,
     327,   373,   275,   276,   277,   278,   279,   280,   281
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     145,    90,   146,    96,    61,   274,   282,   195,   144,   100,
     206,   232,   257,   233,    59,   353,   198,    86,   103,   155,
     174,    98,   101,   187,    92,   240,    91,   164,   174,    82,
       4,   174,    92,   225,   424,   452,   372,   253,   246,   254,
       3,     7,   247,   453,   177,   199,   151,    87,   248,    88,
     184,   162,   148,    93,   249,    81,   435,   191,   370,   317,
      83,    93,   226,   227,   228,   229,   200,   151,    82,   293,
     284,   295,   315,   163,    84,   250,   202,    85,   414,   251,
     179,   180,   182,   152,    87,    87,    88,    88,    87,    87,
      88,    88,   462,    87,   203,    88,   230,   -39,   371,    83,
     429,   257,   252,   -35,   296,  -212,    82,   147,   242,   243,
     -27,   211,   145,   145,   146,   146,    85,   145,   175,   146,
     196,   197,   234,   235,   192,   207,   175,    89,   181,   175,
      94,    99,   102,   366,   150,   -87,    95,    83,    33,   -35,
     -35,   430,   431,  -181,   358,   421,   -27,   -27,   176,   172,
     359,   289,   202,   259,    85,    83,   -40,   432,   185,   463,
     238,   447,   159,   285,   212,  -181,    88,   434,   260,   261,
     203,    61,  -265,   171,  -265,   450,   451,   464,   456,   369,
    -171,    59,   245,   255,   411,   255,   422,   213,   461,   258,
     214,   262,   393,   160,   263,   264,   265,   165,   266,   237,
     394,   215,   401,   402,   403,   404,   213,   256,   213,   214,
     241,   214,   -39,   297,   298,   397,   167,   267,   427,   168,
     215,   419,   215,    83,   169,   436,   268,   269,   270,   256,
     170,   256,   305,   306,   307,   308,   347,  -152,   316,   310,
     271,   272,   273,   328,   213,   329,   178,   214,   437,   438,
     439,   188,  -156,   145,   190,   146,    -5,     8,   215,     9,
      10,    11,    12,    13,   150,   193,    14,   256,   194,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
     442,   443,    26,    27,   210,   185,   145,    28,   146,   283,
      29,   290,    30,   291,   144,   292,    31,    32,    33,    34,
      35,   294,   302,    36,    37,   303,   304,    38,    39,    40,
      41,    42,    43,   309,    44,   311,   318,    45,    46,    47,
      48,    49,    50,   313,    51,   314,    52,   340,   341,   342,
     343,   344,   345,   346,   437,   438,   439,   344,   345,   346,
    -254,  -254,  -254,   320,   321,   322,   323,   324,   325,   299,
     300,   301,   440,   319,   256,  -268,   412,   330,   460,   145,
     441,   146,   148,   145,    54,   146,   442,   443,   367,  -185,
      53,    54,  -254,  -254,  -211,   104,    55,    56,    10,    11,
      12,    13,   365,   368,    14,   396,   398,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,   395,   405,
      26,    27,   406,   407,   408,    28,   409,   410,    29,   413,
      30,   370,   415,   425,   105,    32,   428,    34,    35,   446,
     448,    36,    37,   449,   467,    38,    39,    40,    41,    42,
      43,   466,    44,   468,   156,    45,    46,    47,    48,    49,
      50,   173,   357,   157,   106,   360,   361,   362,   363,   416,
     364,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   216,   418,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   183,   189,   374,   139,   458,
     392,   140,   141,   142,    55,    56,   104,     0,     0,    10,
      11,    12,    13,     0,     0,    14,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
       0,    26,    27,     0,     0,     0,    28,     0,     0,    29,
       0,    30,     0,     0,     0,   105,    32,     0,    34,    35,
       0,     0,    36,    37,     0,     0,    38,    39,    40,    41,
      42,    43,     0,    44,     0,     0,    45,    46,    47,    48,
      49,    50,     0,  -101,     0,   106,   342,   343,   344,   345,
     346,  -101,  -101,  -250,  -250,  -250,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -101,     0,     0,  -101,
    -101,     0,     0,     0,  -101,     0,     0,     0,     0,   459,
    -101,     0,     0,     0,     0,  -250,  -250,     0,     0,  -101,
       0,  -101,     0,     0,  -101,    55,    56,   104,     0,     0,
      10,    11,    12,    13,     0,     0,    14,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       0,     0,    26,    27,     0,     0,     0,    28,     0,     0,
      29,     0,    30,     0,     0,     0,   105,    32,     0,    34,
      35,     0,     0,    36,    37,     0,     0,    38,    39,    40,
      41,    42,    43,     0,    44,     0,     0,    45,    46,    47,
      48,    49,    50,     0,  -100,     0,   106,     0,     0,     0,
       0,     0,  -100,  -100,  -251,  -251,  -251,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -100,     0,     0,
    -100,  -100,     0,     0,     0,  -100,     0,     0,     0,     0,
     465,  -100,     0,     0,     0,     0,  -251,  -251,     0,     0,
    -100,     0,  -100,     0,     0,  -100,    55,    56,   217,     0,
       0,    10,    11,    12,    13,     0,     0,    14,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     0,     0,    26,    27,     0,     0,     0,    28,     0,
       0,    29,     0,    30,   218,   219,   220,    31,    32,    33,
      34,    35,     0,     0,    36,    37,     0,     0,    38,    39,
      40,    41,    42,    43,     0,    44,     0,     0,    45,    46,
      47,    48,    49,    50,     0,    51,     0,    52,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,     0,     0,     0,     0,     0,     0,     0,     0,   -14,
     221,    53,   -14,     0,     0,  -211,   217,    55,    56,    10,
      11,    12,    13,     0,     0,    14,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
       0,    26,    27,     0,     0,     0,    28,     0,     0,    29,
       0,    30,   218,   219,   220,    31,    32,    33,    34,    35,
       0,     0,    36,    37,     0,     0,    38,    39,    40,    41,
      42,    43,     0,    44,     0,     0,    45,    46,    47,    48,
      49,    50,     0,    51,     0,    52,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,     0,   -14,   221,    53,
       0,     0,     0,  -211,   217,    55,    56,    10,    11,    12,
      13,     0,     0,    14,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,     0,    26,
      27,     0,     0,     0,    28,     0,     0,    29,     0,    30,
     218,   219,   220,    31,    32,    33,    34,    35,     0,     0,
      36,    37,     0,     0,    38,    39,    40,    41,    42,    43,
       0,    44,     0,     0,    45,    46,    47,    48,    49,    50,
       0,    51,     0,    52,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   221,    53,   -14,     0,
       0,  -211,   104,    55,    56,    10,    11,    12,    13,     0,
       0,    14,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,     0,    26,    27,     0,
       0,     0,    28,     0,     0,    29,     0,    30,     0,     0,
       0,   105,    32,   -97,    34,    35,     0,     0,    36,    37,
       0,     0,    38,    39,    40,    41,    42,    43,     0,    44,
       0,     0,    45,    46,    47,    48,    49,    50,     0,   -97,
       0,   106,     0,     0,     0,     0,     0,   -97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -97,     0,     0,   -97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -97,     0,     0,     0,
       0,     0,     0,   -97,   -97,     0,     0,     0,     0,     0,
       0,    55,    56,     8,     0,     9,    10,    11,    12,    13,
       0,     0,    14,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,     0,    26,    27,
       0,     0,     0,    28,     0,     0,    29,     0,    30,     0,
       0,     0,    31,    32,    33,    34,    35,     0,     0,    36,
      37,     0,     0,    38,    39,    40,    41,    42,    43,     0,
      44,     0,     0,    45,    46,    47,    48,    49,    50,     0,
      51,     0,    52,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   239,     0,    53,    54,     0,     0,
    -211,   244,    55,    56,    10,    11,    12,    13,     0,     0,
      14,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,    26,    27,     0,     0,
       0,    28,     0,     0,    29,     0,    30,     0,     0,     0,
      31,    32,    33,    34,    35,     0,     0,    36,    37,     0,
       0,    38,    39,    40,    41,    42,    43,     0,    44,     0,
       0,    45,    46,    47,    48,    49,    50,     0,    51,     0,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   348,     0,     0,    10,    11,    12,
      13,     0,     0,    14,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,     0,    26,
      27,     0,     0,     0,    28,     0,     0,    29,  -211,    30,
      55,    56,     0,   105,    32,     0,    34,    35,     0,     0,
      36,    37,     0,     0,    38,    39,    40,    41,    42,    43,
       0,    44,     0,     0,    45,    46,    47,    48,    49,    50,
       0,     0,     0,   106,     0,   104,     0,     0,    10,    11,
      12,    13,     0,     0,    14,     0,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     0,     0,
      26,    27,     0,     0,     0,    28,     0,     0,    29,     0,
      30,     0,     0,     0,   105,    32,     0,    34,    35,   -83,
       0,    36,    37,    55,    56,    38,    39,    40,    41,    42,
      43,     0,    44,     0,     0,    45,    46,    47,    48,    49,
      50,     0,     0,     0,   106,     0,   348,     0,     0,    10,
      11,    12,    13,     0,     0,    14,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
       0,    26,    27,     0,     0,     0,    28,     0,     0,    29,
       0,    30,     0,     0,     0,   105,    32,     0,    34,    35,
       0,     0,    36,    37,    55,    56,    38,    39,    40,    41,
      42,    43,     0,    44,   259,     0,    45,    46,    47,    48,
      49,    50,     0,     0,     0,   106,     0,     0,     0,   260,
     261,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   262,     0,     0,   263,   264,   265,     0,   266,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    55,    56,     0,   267,     0,
       0,     0,     0,     0,     0,     0,     0,   268,   269,   270,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,   272,   273
};

static const yytype_int16 yycheck[] =
{
      33,    13,    33,    15,     6,   202,   203,   144,    33,    21,
     150,   163,   195,   165,     6,   288,     7,     1,    30,    65,
       1,     1,     1,    97,     7,   177,     1,    72,     1,    68,
      50,     1,     7,     7,   399,    89,   328,   189,     6,   191,
       0,    68,    10,    97,    89,    36,    76,    68,    16,    70,
      95,    89,    74,    36,    22,   111,   421,   102,    76,   256,
      99,    36,    36,    37,    38,    39,    57,    76,    68,   221,
     207,   223,   255,   111,   113,    43,    77,   116,   370,    47,
      92,    93,    94,   113,    68,    68,    70,    70,    68,    68,
      70,    70,   457,    68,    95,    70,    70,   119,   116,    99,
      20,   284,    70,    76,   113,   118,    68,    97,   182,   183,
      76,   157,   145,   146,   145,   146,   116,   150,    99,   150,
     145,   146,   167,   168,    68,   150,    99,   111,   111,    99,
     105,   111,   111,   316,    97,   116,   111,    99,    42,   112,
     113,    61,    62,    89,   296,   397,   112,   113,   112,   118,
     302,   113,    77,    30,   116,    99,   119,    77,    89,    71,
     172,   434,    68,   209,    68,   111,    70,   419,    45,    46,
      95,   173,    88,    79,    90,   442,   443,    89,   445,   319,
     111,   173,   184,    68,   367,    68,   111,    91,   455,   201,
      94,    68,    68,   111,    71,    72,    73,   111,    75,   170,
      76,   105,   354,   355,   356,   357,    91,   114,    91,    94,
     181,    94,   119,   225,   226,   352,   111,    94,   415,   111,
     105,    68,   105,    99,   111,   422,   103,   104,   105,   114,
     111,   114,   234,   235,   236,   237,   119,   111,   115,   241,
     117,   118,   119,    88,    91,    90,   112,    94,    71,    72,
      73,   112,   111,   286,   112,   286,     0,     1,   105,     3,
       4,     5,     6,     7,    97,   115,    10,   114,   116,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     103,   104,    26,    27,   119,    89,   319,    31,   319,    99,
      34,    89,    36,    89,   319,    89,    40,    41,    42,    43,
      44,   112,   111,    47,    48,   112,   112,    51,    52,    53,
      54,    55,    56,   112,    58,    76,    99,    61,    62,    63,
      64,    65,    66,   112,    68,   112,    70,   101,   102,   103,
     104,   105,   106,   107,    71,    72,    73,   105,   106,   107,
      71,    72,    73,   267,   268,   269,   270,   271,   272,   227,
     228,   229,    89,   119,   114,    91,   368,    91,    89,   392,
      97,   392,    74,   396,   115,   396,   103,   104,   115,   112,
     114,   115,   103,   104,   118,     1,   120,   121,     4,     5,
       6,     7,   112,    36,    10,    76,    59,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,   116,   112,
      26,    27,   112,   112,   112,    31,   112,   112,    34,   116,
      36,    76,    89,    75,    40,    41,   116,    43,    44,    71,
     112,    47,    48,    97,    71,    51,    52,    53,    54,    55,
      56,    89,    58,    71,    67,    61,    62,    63,    64,    65,
      66,    81,   295,    67,    70,   305,   306,   307,   308,   392,
     310,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,   158,   396,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,    94,    99,   329,   114,   447,
     347,   117,   118,   119,   120,   121,     1,    -1,    -1,     4,
       5,     6,     7,    -1,    -1,    10,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    36,    -1,    -1,    -1,    40,    41,    -1,    43,    44,
      -1,    -1,    47,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    -1,    -1,    61,    62,    63,    64,
      65,    66,    -1,    68,    -1,    70,   103,   104,   105,   106,
     107,    76,    77,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,
      95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    97,
     105,    -1,    -1,    -1,    -1,   103,   104,    -1,    -1,   114,
      -1,   116,    -1,    -1,   119,   120,   121,     1,    -1,    -1,
       4,     5,     6,     7,    -1,    -1,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,
      34,    -1,    36,    -1,    -1,    -1,    40,    41,    -1,    43,
      44,    -1,    -1,    47,    48,    -1,    -1,    51,    52,    53,
      54,    55,    56,    -1,    58,    -1,    -1,    61,    62,    63,
      64,    65,    66,    -1,    68,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    76,    77,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,
      97,   105,    -1,    -1,    -1,    -1,   103,   104,    -1,    -1,
     114,    -1,   116,    -1,    -1,   119,   120,   121,     1,    -1,
      -1,     4,     5,     6,     7,    -1,    -1,    10,    -1,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,    -1,
      -1,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    -1,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    -1,    -1,    61,    62,
      63,    64,    65,    66,    -1,    68,    -1,    70,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
     113,   114,   115,    -1,    -1,   118,     1,   120,   121,     4,
       5,     6,     7,    -1,    -1,    10,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    -1,    -1,    61,    62,    63,    64,
      65,    66,    -1,    68,    -1,    70,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,    -1,   112,   113,   114,
      -1,    -1,    -1,   118,     1,   120,   121,     4,     5,     6,
       7,    -1,    -1,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    26,
      27,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      47,    48,    -1,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    -1,    -1,    61,    62,    63,    64,    65,    66,
      -1,    68,    -1,    70,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,    -1,
      -1,   118,     1,   120,   121,     4,     5,     6,     7,    -1,
      -1,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    -1,    26,    27,    -1,
      -1,    -1,    31,    -1,    -1,    34,    -1,    36,    -1,    -1,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    47,    48,
      -1,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      -1,    -1,    61,    62,    63,    64,    65,    66,    -1,    68,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    91,    -1,    -1,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,
      -1,    -1,    -1,   112,   113,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,     1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    36,    -1,
      -1,    -1,    40,    41,    42,    43,    44,    -1,    -1,    47,
      48,    -1,    -1,    51,    52,    53,    54,    55,    56,    -1,
      58,    -1,    -1,    61,    62,    63,    64,    65,    66,    -1,
      68,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,   115,    -1,    -1,
     118,     1,   120,   121,     4,     5,     6,     7,    -1,    -1,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    26,    27,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    -1,
      -1,    51,    52,    53,    54,    55,    56,    -1,    58,    -1,
      -1,    61,    62,    63,    64,    65,    66,    -1,    68,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,     4,     5,     6,
       7,    -1,    -1,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    26,
      27,    -1,    -1,    -1,    31,    -1,    -1,    34,   118,    36,
     120,   121,    -1,    40,    41,    -1,    43,    44,    -1,    -1,
      47,    48,    -1,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    -1,    -1,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    -1,     1,    -1,    -1,     4,     5,
       6,     7,    -1,    -1,    10,    -1,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      26,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,
      36,    -1,    -1,    -1,    40,    41,    -1,    43,    44,   116,
      -1,    47,    48,   120,   121,    51,    52,    53,    54,    55,
      56,    -1,    58,    -1,    -1,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    -1,     1,    -1,    -1,     4,
       5,     6,     7,    -1,    -1,    10,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    36,    -1,    -1,    -1,    40,    41,    -1,    43,    44,
      -1,    -1,    47,    48,   120,   121,    51,    52,    53,    54,
      55,    56,    -1,    58,    30,    -1,    61,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    -1,    -1,    -1,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    71,    72,    73,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,   121,    -1,    94,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   123,   124,     0,    50,   125,   126,    68,     1,     3,
       4,     5,     6,     7,    10,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    26,    27,    31,    34,
      36,    40,    41,    42,    43,    44,    47,    48,    51,    52,
      53,    54,    55,    56,    58,    61,    62,    63,    64,    65,
      66,    68,    70,   114,   115,   120,   121,   127,   128,   130,
     131,   135,   138,   139,   140,   141,   148,   151,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   173,
     176,   111,    68,    99,   113,   116,     1,    68,    70,   111,
     138,     1,     7,    36,   105,   111,   138,   164,     1,   111,
     138,     1,   111,   138,     1,    40,    70,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   114,
     117,   118,   119,   150,   152,   153,   173,    97,    74,   182,
      97,    76,   113,   142,   143,   142,   136,   137,   177,   151,
     111,   168,    89,   111,   168,   111,   169,   111,   111,   111,
     111,   151,   118,   126,     1,    99,   112,   168,   112,   138,
     138,   111,   138,   164,   168,    89,   165,   165,   112,   169,
     112,   168,    68,   115,   116,   177,   152,   152,     7,    36,
      57,   166,    77,    95,   181,   149,   150,   152,   136,   137,
     119,   142,    68,    91,    94,   105,   139,     1,    37,    38,
      39,   113,   129,   130,   135,     7,    36,    37,    38,    39,
      70,   167,   129,   129,   168,   168,   170,   170,   138,   112,
     129,   170,   165,   165,     1,   135,     6,    10,    16,    22,
      43,    47,    70,   129,   129,    68,   114,   178,   138,    30,
      45,    46,    68,    71,    72,    73,    75,    94,   103,   104,
     105,   117,   118,   119,   192,   194,   195,   196,   197,   198,
     199,   200,   192,    99,   177,   142,   172,   178,   179,   113,
      89,    89,    89,   129,   112,   129,   113,   138,   138,   167,
     167,   167,   111,   112,   112,   135,   135,   135,   135,   112,
     135,    76,   171,   112,   112,   178,   115,   192,    99,   119,
     199,   199,   199,   199,   199,   199,   191,   192,    88,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   119,     1,   144,
     145,   146,   152,   182,   132,   133,   134,   131,   129,   129,
     171,   171,   171,   171,   171,   112,   178,   115,    36,   150,
      76,   116,   191,   193,   196,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   172,    68,    76,   116,    76,   177,    59,   184,
     185,   129,   129,   129,   129,   112,   112,   112,   112,   112,
     112,   178,   138,   116,   191,    89,   144,   174,   145,    68,
     147,   179,   111,   180,   181,    75,   186,   192,   116,    20,
      61,    62,    77,   175,   179,   181,   192,    71,    72,    73,
      89,    97,   103,   104,   187,   190,    71,   182,   112,    97,
     187,   187,    89,    97,   188,   189,   187,   183,   185,    97,
      89,   187,   181,    71,    89,    97,    89,    71,    71
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   122,   123,   124,   125,   125,   126,   126,   127,   127,
     127,   127,   127,   128,   129,   129,   129,   129,   129,   129,
     129,   129,   130,   131,   132,   133,   134,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   136,   137,   138,
     138,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   140,
     141,   142,   143,   144,   144,   145,   145,   145,   145,   146,
     147,   147,   148,   149,   149,   150,   150,   151,   151,   151,
     152,   152,   152,   152,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   164,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   166,   166,   166,   167,   167,   167,   167,   167,
     167,   168,   169,   170,   171,   171,   172,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   174,   174,   174,   174,   175,
     175,   176,   176,   177,   177,   177,   177,   178,   178,   178,
     179,   180,   180,   181,   181,   181,   182,   182,   183,   183,
     183,   183,   183,   184,   184,   184,   184,   185,   185,   186,
     186,   187,   187,   187,   187,   187,   188,   188,   188,   188,
     189,   189,   189,   189,   189,   190,   190,   190,   191,   191,
     192,   192,   193,   194,   194,   195,   196,   196,   197,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   199,   199,   199,   199,
     199,   199,   199,   199,   200,   200,   200,   200,   200,   200,
     200,   200
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     5,     1,     0,     2,     2,     1,
       1,     1,     2,     1,     0,     3,     4,     4,     4,     4,
       2,     2,     1,     1,     0,     0,     0,     1,     2,     3,
       2,     2,     1,     3,     4,     2,     2,     6,     2,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     2,     1,
       3,     7,     0,     0,     1,     1,     3,     2,     2,     3,
       2,     5,     3,     1,     6,     3,     4,     1,     2,     2,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     7,     5,     4,     6,     1,     5,     4,
       2,     5,     4,     2,     6,     7,     6,     6,     6,     6,
       2,     2,     1,     4,     3,     3,     2,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     2,     3,     3,     4,
       4,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     0,     1,     1,     1,     2,     2,     2,     1,     2,
       2,     0,     0,     0,     0,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     2,     2,     0,
       2,     0,     1,     0,     2,     2,     2,     0,     4,     3,
       1,     1,     3,     0,     2,     2,     0,     1,     1,     2,
       3,     4,     3,     2,     4,     5,     4,     0,     1,     0,
       1,     1,     1,     1,     2,     2,     0,     1,     2,     1,
       1,     2,     2,     3,     1,     1,     2,     1,     3,     1,
       5,     1,     1,     3,     1,     1,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     2,     2,     2,     2,
       2,     2,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* prog: s1 exts  */
#line 223 "soapcpp2_yacc.y"
                        {
                          if (lflag)
                          {
                            custom_header = 0;
                            custom_fault = 0;
                          }
                          else
                          {
                            add_header();
                            add_fault();
                          }
                          compile(sp->table);
                          freetable(classtable);
                          freetable(enumtable);
                          freetable(typetable);
                          freetable(booltable);
                          freetable(templatetable);
                          yylineno = 0;
                        }
#line 1976 "soapcpp2_yacc.tab.c"
    break;

  case 3: /* s1: %empty  */
#line 243 "soapcpp2_yacc.y"
                        {
                          classtable = mktable(NULL);
                          enumtable = mktable(NULL);
                          typetable = mktable(NULL);
                          booltable = mktable(NULL);
                          templatetable = mktable(NULL);
                          p = enter(booltable, lookup("false"));
                          p->info.typ = mkint();
                          p->info.val.i = 0;
                          p = enter(booltable, lookup("true"));
                          p->info.typ = mkint();
                          p->info.val.i = 1;
                          mkscope(mktable(mktable(NULL)), 0);
                        }
#line 1995 "soapcpp2_yacc.tab.c"
    break;

  case 4: /* exts: NAMESPACE ID '{' exts1 '}'  */
#line 259 "soapcpp2_yacc.y"
                        { set_namespace((yyvsp[-3].sym)->name); }
#line 2001 "soapcpp2_yacc.tab.c"
    break;

  case 5: /* exts: exts1  */
#line 260 "soapcpp2_yacc.y"
                        { }
#line 2007 "soapcpp2_yacc.tab.c"
    break;

  case 6: /* exts1: %empty  */
#line 262 "soapcpp2_yacc.y"
                        {
                          add_soap();
                          add_XML();
                          add_qname();
                        }
#line 2017 "soapcpp2_yacc.tab.c"
    break;

  case 7: /* exts1: exts1 ext  */
#line 267 "soapcpp2_yacc.y"
                        { }
#line 2023 "soapcpp2_yacc.tab.c"
    break;

  case 8: /* ext: dclrs ';'  */
#line 269 "soapcpp2_yacc.y"
                        { }
#line 2029 "soapcpp2_yacc.tab.c"
    break;

  case 9: /* ext: pragma  */
#line 270 "soapcpp2_yacc.y"
                        { }
#line 2035 "soapcpp2_yacc.tab.c"
    break;

  case 10: /* ext: t1  */
#line 271 "soapcpp2_yacc.y"
                        { }
#line 2041 "soapcpp2_yacc.tab.c"
    break;

  case 11: /* ext: t2  */
#line 272 "soapcpp2_yacc.y"
                        { }
#line 2047 "soapcpp2_yacc.tab.c"
    break;

  case 12: /* ext: error ';'  */
#line 273 "soapcpp2_yacc.y"
                        {
                          synerror("input before ; skipped");
                          while (sp > stack)
                          {
                            freetable(sp->table);
                            exitscope();
                          }
                          yyerrok;
                        }
#line 2061 "soapcpp2_yacc.tab.c"
    break;

  case 13: /* pragma: PRAGMA  */
#line 283 "soapcpp2_yacc.y"
                        { add_pragma((yyvsp[0].s)); }
#line 2067 "soapcpp2_yacc.tab.c"
    break;

  case 14: /* decls: %empty  */
#line 292 "soapcpp2_yacc.y"
                        {
                          transient &= ~6;
                          permission = 0;
                        }
#line 2076 "soapcpp2_yacc.tab.c"
    break;

  case 15: /* decls: dclrs ';' decls  */
#line 297 "soapcpp2_yacc.y"
                        { }
#line 2082 "soapcpp2_yacc.tab.c"
    break;

  case 16: /* decls: PRIVATE ':' t3 decls  */
#line 299 "soapcpp2_yacc.y"
                        { }
#line 2088 "soapcpp2_yacc.tab.c"
    break;

  case 17: /* decls: PROTECTED ':' t4 decls  */
#line 301 "soapcpp2_yacc.y"
                        { }
#line 2094 "soapcpp2_yacc.tab.c"
    break;

  case 18: /* decls: PUBLIC ':' t5 decls  */
#line 303 "soapcpp2_yacc.y"
                        { }
#line 2100 "soapcpp2_yacc.tab.c"
    break;

  case 19: /* decls: t1 decls t2 decls  */
#line 305 "soapcpp2_yacc.y"
                        { }
#line 2106 "soapcpp2_yacc.tab.c"
    break;

  case 20: /* decls: ';' decls  */
#line 306 "soapcpp2_yacc.y"
                        { }
#line 2112 "soapcpp2_yacc.tab.c"
    break;

  case 21: /* decls: error ';'  */
#line 307 "soapcpp2_yacc.y"
                        {
                          synerror("declaration expected");
                          yyerrok;
                        }
#line 2121 "soapcpp2_yacc.tab.c"
    break;

  case 22: /* t1: '['  */
#line 312 "soapcpp2_yacc.y"
                        { transient |= 1; }
#line 2127 "soapcpp2_yacc.tab.c"
    break;

  case 23: /* t2: ']'  */
#line 314 "soapcpp2_yacc.y"
                        { transient &= ~1; }
#line 2133 "soapcpp2_yacc.tab.c"
    break;

  case 24: /* t3: %empty  */
#line 316 "soapcpp2_yacc.y"
                        { permission = (int)Sprivate; }
#line 2139 "soapcpp2_yacc.tab.c"
    break;

  case 25: /* t4: %empty  */
#line 318 "soapcpp2_yacc.y"
                        { permission = (int)Sprotected; }
#line 2145 "soapcpp2_yacc.tab.c"
    break;

  case 26: /* t5: %empty  */
#line 320 "soapcpp2_yacc.y"
                        { permission = 0; }
#line 2151 "soapcpp2_yacc.tab.c"
    break;

  case 27: /* dclrs: spec  */
#line 322 "soapcpp2_yacc.y"
                        { }
#line 2157 "soapcpp2_yacc.tab.c"
    break;

  case 28: /* dclrs: spec dclr  */
#line 323 "soapcpp2_yacc.y"
                        { }
#line 2163 "soapcpp2_yacc.tab.c"
    break;

  case 29: /* dclrs: spec fdclr func  */
#line 325 "soapcpp2_yacc.y"
                        { }
#line 2169 "soapcpp2_yacc.tab.c"
    break;

  case 30: /* dclrs: ctor func  */
#line 326 "soapcpp2_yacc.y"
                        { }
#line 2175 "soapcpp2_yacc.tab.c"
    break;

  case 31: /* dclrs: dtor func  */
#line 327 "soapcpp2_yacc.y"
                        { }
#line 2181 "soapcpp2_yacc.tab.c"
    break;

  case 32: /* dclrs: sym  */
#line 328 "soapcpp2_yacc.y"
                        { }
#line 2187 "soapcpp2_yacc.tab.c"
    break;

  case 33: /* dclrs: dclrs ',' dclr  */
#line 330 "soapcpp2_yacc.y"
                        { }
#line 2193 "soapcpp2_yacc.tab.c"
    break;

  case 34: /* dclrs: dclrs ',' fdclr func  */
#line 332 "soapcpp2_yacc.y"
                        { }
#line 2199 "soapcpp2_yacc.tab.c"
    break;

  case 35: /* dclrs: error ID  */
#line 333 "soapcpp2_yacc.y"
                        {
                          sprintf(errbuf, "incomplete type in declaration of '%s'", (yyvsp[0].sym)->name);
                          synerror(errbuf);
                          yyerrok;
                        }
#line 2209 "soapcpp2_yacc.tab.c"
    break;

  case 36: /* dclrs: error ')'  */
#line 338 "soapcpp2_yacc.y"
                        {
                          synerror("function declaration?");
                          yyerrok;
                        }
#line 2218 "soapcpp2_yacc.tab.c"
    break;

  case 37: /* dclr: ptrs ID arrayck tag bounds brinit  */
#line 344 "soapcpp2_yacc.y"
                        {
                          if (((int)(yyvsp[-3].rec).sto & (int)Stypedef) && sp->table->level == GLOBAL)
                          {
                            if (((yyvsp[-3].rec).typ->type != Tstruct &&
                                  (yyvsp[-3].rec).typ->type != Tclass &&
                                  (yyvsp[-3].rec).typ->type != Tunion &&
                                  (yyvsp[-3].rec).typ->type != Tenum &&
                                  (yyvsp[-3].rec).typ->type != Tenumsc) ||
                                ((is_binary((yyvsp[-3].rec).typ) || is_stdstr((yyvsp[-3].rec).typ)) && strcmp((yyvsp[-4].sym)->name, (yyvsp[-3].rec).typ->id->name)) ||
                                strcmp((yyvsp[-4].sym)->name, (yyvsp[-3].rec).typ->id->name))
                            {
                              p = enter(typetable, (yyvsp[-4].sym));
                              p->info.typ = mksymtype((yyvsp[-3].rec).typ, (yyvsp[-4].sym));
                              if (((int)(yyvsp[-3].rec).sto & (int)Sextern))
                              {
                                p->info.typ->transient = -1;
                                p->info.typ->extsym = (yyvsp[-4].sym);
                              }
                              else if (is_external((yyvsp[-3].rec).typ))
                              {
                                p->info.typ->transient = -3; /* extern and volatile */
                              }
                              else
                              {
                                p->info.typ->transient = (yyvsp[-3].rec).typ->transient;
                              }
                              if (p->info.typ->width == 0)
                                p->info.typ->width = 8;
                              p->info.sto = (yyvsp[-3].rec).sto;
                              p->info.typ->restriction = (yyvsp[-3].rec).typ->sym;
                              p->info.typ->synonym = (yyvsp[-3].rec).typ->sym;
                              if ((yyvsp[-1].rec).hasmin)
                              {
                                p->info.typ->hasmin = (yyvsp[-1].rec).hasmin;
                                p->info.typ->incmin = (yyvsp[-1].rec).incmin;
                                p->info.typ->imin = (yyvsp[-1].rec).imin;
                                p->info.typ->rmin = (yyvsp[-1].rec).rmin;
                                p->info.typ->synonym = NULL;
                              }
                              else
                              {
                                p->info.typ->hasmin = (yyvsp[-3].rec).typ->hasmin;
                                p->info.typ->incmin = (yyvsp[-3].rec).typ->incmin;
                                p->info.typ->imin = (yyvsp[-3].rec).typ->imin;
                                p->info.typ->rmin = (yyvsp[-3].rec).typ->rmin;
                              }
                              if ((yyvsp[-1].rec).hasmax)
                              {
                                p->info.typ->hasmax = (yyvsp[-1].rec).hasmax;
                                p->info.typ->incmax = (yyvsp[-1].rec).incmax;
                                p->info.typ->imax = (yyvsp[-1].rec).imax;
                                p->info.typ->rmax = (yyvsp[-1].rec).rmax;
                                p->info.typ->synonym = NULL;
                              }
                              else
                              {
                                p->info.typ->hasmax = (yyvsp[-3].rec).typ->hasmax;
                                p->info.typ->incmax = (yyvsp[-3].rec).typ->incmax;
                                p->info.typ->imax = (yyvsp[-3].rec).typ->imax;
                                p->info.typ->rmax = (yyvsp[-3].rec).typ->rmax;
                              }
                              if (p->info.typ->property == 1)
                                p->info.typ->property = (yyvsp[-3].rec).typ->property;
                              if ((yyvsp[-1].rec).pattern)
                              {
                                p->info.typ->pattern = (yyvsp[-1].rec).pattern;
                                p->info.typ->synonym = NULL;
                              }
                              else if (!p->info.typ->pattern)
                              {
                                p->info.typ->pattern = (yyvsp[-3].rec).typ->pattern;
                              }
                            }
                            if ((yyvsp[0].rec).hasval)
                              set_value(p, (yyvsp[-3].rec).typ, &(yyvsp[0].rec));
                            (yyvsp[-4].sym)->token = TYPE;
                          }
                          else
                          {
                            p = enter(sp->table, (yyvsp[-4].sym));
                            p->tag = (yyvsp[-2].s);
                            p->info.typ = (yyvsp[-3].rec).typ;
                            p->info.sto = (Storage)((int)(yyvsp[-3].rec).sto | permission);
                            if ((yyvsp[0].rec).hasval)
                              set_value(p, (yyvsp[-3].rec).typ, &(yyvsp[0].rec));
                            else
                              p->info.val.i = sp->val;
                            if ((yyvsp[-1].rec).minOccurs < 0)
                            {
                              if ((yyvsp[0].rec).hasval ||
                                  ((int)(yyvsp[-3].rec).sto & (int)Sattribute) ||
                                  ((int)(yyvsp[-3].rec).sto & (int)Sspecial) ||
                                  (yyvsp[-3].rec).typ->type == Tpointer ||
                                  (yyvsp[-3].rec).typ->type == Ttemplate ||
                                  is_anyAttribute((yyvsp[-3].rec).typ) ||
                                  !strncmp((yyvsp[-4].sym)->name, "__size", 6))
                                p->info.minOccurs = 0;
                              else
                                p->info.minOccurs = 1;
                            }
                            else
                            {
                              p->info.minOccurs = (yyvsp[-1].rec).minOccurs;
                            }
                            p->info.maxOccurs = (yyvsp[-1].rec).maxOccurs;
                            p->info.nillable = (yyvsp[-1].rec).nillable;
                            if (sp->mask)
                              sp->val <<= 1;
                            else
                              sp->val++;
                            p->info.offset = sp->offset;
                            if (((int)(yyvsp[-3].rec).sto & (int)Sextern))
                              p->level = GLOBAL;
                            else if (((int)(yyvsp[-3].rec).sto & (int)Stypedef))
                              ;
                            else if (sp->grow)
                              sp->offset += p->info.typ->width;
                            else if (p->info.typ->width > sp->offset)
                              sp->offset = p->info.typ->width;
                          }
                          sp->entry = p;
                        }
#line 2345 "soapcpp2_yacc.tab.c"
    break;

  case 38: /* fdclr: ptrs name  */
#line 467 "soapcpp2_yacc.y"
                        {
                          if (((int)(yyvsp[-1].rec).sto & (int)Stypedef))
                          {
                            sprintf(errbuf, "invalid typedef qualifier for '%s'", (yyvsp[0].sym)->name);
                            semwarn(errbuf);
                          }
                          p = enter(sp->table, (yyvsp[0].sym));
                          p->info.typ = (yyvsp[-1].rec).typ;
                          p->info.sto = (yyvsp[-1].rec).sto;
                          p->info.hasval = False;
                          p->info.offset = sp->offset;
                          if (sp->grow)
                            sp->offset += p->info.typ->width;
                          else if (p->info.typ->width > sp->offset)
                            sp->offset = p->info.typ->width;
                          sp->entry = p;
                        }
#line 2367 "soapcpp2_yacc.tab.c"
    break;

  case 39: /* id: ID  */
#line 485 "soapcpp2_yacc.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 2373 "soapcpp2_yacc.tab.c"
    break;

  case 40: /* id: TYPE  */
#line 486 "soapcpp2_yacc.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 2379 "soapcpp2_yacc.tab.c"
    break;

  case 41: /* name: id  */
#line 488 "soapcpp2_yacc.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 2385 "soapcpp2_yacc.tab.c"
    break;

  case 42: /* name: OPERATOR '!'  */
#line 489 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator!"); }
#line 2391 "soapcpp2_yacc.tab.c"
    break;

  case 43: /* name: OPERATOR '~'  */
#line 490 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator~"); }
#line 2397 "soapcpp2_yacc.tab.c"
    break;

  case 44: /* name: OPERATOR '='  */
#line 491 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator="); }
#line 2403 "soapcpp2_yacc.tab.c"
    break;

  case 45: /* name: OPERATOR PA  */
#line 492 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator+="); }
#line 2409 "soapcpp2_yacc.tab.c"
    break;

  case 46: /* name: OPERATOR NA  */
#line 493 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator-="); }
#line 2415 "soapcpp2_yacc.tab.c"
    break;

  case 47: /* name: OPERATOR TA  */
#line 494 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator*="); }
#line 2421 "soapcpp2_yacc.tab.c"
    break;

  case 48: /* name: OPERATOR DA  */
#line 495 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator/="); }
#line 2427 "soapcpp2_yacc.tab.c"
    break;

  case 49: /* name: OPERATOR MA  */
#line 496 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator%="); }
#line 2433 "soapcpp2_yacc.tab.c"
    break;

  case 50: /* name: OPERATOR AA  */
#line 497 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator&="); }
#line 2439 "soapcpp2_yacc.tab.c"
    break;

  case 51: /* name: OPERATOR XA  */
#line 498 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator^="); }
#line 2445 "soapcpp2_yacc.tab.c"
    break;

  case 52: /* name: OPERATOR OA  */
#line 499 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator|="); }
#line 2451 "soapcpp2_yacc.tab.c"
    break;

  case 53: /* name: OPERATOR LA  */
#line 500 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator<<="); }
#line 2457 "soapcpp2_yacc.tab.c"
    break;

  case 54: /* name: OPERATOR RA  */
#line 501 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator>>="); }
#line 2463 "soapcpp2_yacc.tab.c"
    break;

  case 55: /* name: OPERATOR OR  */
#line 502 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator||"); }
#line 2469 "soapcpp2_yacc.tab.c"
    break;

  case 56: /* name: OPERATOR AN  */
#line 503 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator&&"); }
#line 2475 "soapcpp2_yacc.tab.c"
    break;

  case 57: /* name: OPERATOR '|'  */
#line 504 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator|"); }
#line 2481 "soapcpp2_yacc.tab.c"
    break;

  case 58: /* name: OPERATOR '^'  */
#line 505 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator^"); }
#line 2487 "soapcpp2_yacc.tab.c"
    break;

  case 59: /* name: OPERATOR '&'  */
#line 506 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator&"); }
#line 2493 "soapcpp2_yacc.tab.c"
    break;

  case 60: /* name: OPERATOR EQ  */
#line 507 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator=="); }
#line 2499 "soapcpp2_yacc.tab.c"
    break;

  case 61: /* name: OPERATOR NE  */
#line 508 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator!="); }
#line 2505 "soapcpp2_yacc.tab.c"
    break;

  case 62: /* name: OPERATOR '<'  */
#line 509 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator<"); }
#line 2511 "soapcpp2_yacc.tab.c"
    break;

  case 63: /* name: OPERATOR LE  */
#line 510 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator<="); }
#line 2517 "soapcpp2_yacc.tab.c"
    break;

  case 64: /* name: OPERATOR '>'  */
#line 511 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator>"); }
#line 2523 "soapcpp2_yacc.tab.c"
    break;

  case 65: /* name: OPERATOR GE  */
#line 512 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator>="); }
#line 2529 "soapcpp2_yacc.tab.c"
    break;

  case 66: /* name: OPERATOR LS  */
#line 513 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator<<"); }
#line 2535 "soapcpp2_yacc.tab.c"
    break;

  case 67: /* name: OPERATOR RS  */
#line 514 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator>>"); }
#line 2541 "soapcpp2_yacc.tab.c"
    break;

  case 68: /* name: OPERATOR '+'  */
#line 515 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator+"); }
#line 2547 "soapcpp2_yacc.tab.c"
    break;

  case 69: /* name: OPERATOR '-'  */
#line 516 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator-"); }
#line 2553 "soapcpp2_yacc.tab.c"
    break;

  case 70: /* name: OPERATOR '*'  */
#line 517 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator*"); }
#line 2559 "soapcpp2_yacc.tab.c"
    break;

  case 71: /* name: OPERATOR '/'  */
#line 518 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator/"); }
#line 2565 "soapcpp2_yacc.tab.c"
    break;

  case 72: /* name: OPERATOR '%'  */
#line 519 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator%"); }
#line 2571 "soapcpp2_yacc.tab.c"
    break;

  case 73: /* name: OPERATOR PP  */
#line 520 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator++"); }
#line 2577 "soapcpp2_yacc.tab.c"
    break;

  case 74: /* name: OPERATOR NN  */
#line 521 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator--"); }
#line 2583 "soapcpp2_yacc.tab.c"
    break;

  case 75: /* name: OPERATOR AR  */
#line 522 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator->"); }
#line 2589 "soapcpp2_yacc.tab.c"
    break;

  case 76: /* name: OPERATOR '[' ']'  */
#line 523 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator[]"); }
#line 2595 "soapcpp2_yacc.tab.c"
    break;

  case 77: /* name: OPERATOR '(' ')'  */
#line 524 "soapcpp2_yacc.y"
                        { (yyval.sym) = lookup("operator()"); }
#line 2601 "soapcpp2_yacc.tab.c"
    break;

  case 78: /* name: OPERATOR texp  */
#line 525 "soapcpp2_yacc.y"
                        {
                          s1 = c_storage((yyvsp[0].rec).sto);
                          s2 = c_type((yyvsp[0].rec).typ);
                          s = (char*)emalloc(strlen(s1) + strlen(s2) + 10);
                          strcpy(s, "operator ");
                          strcat(s, s1);
                          strcat(s, s2);
                          (yyval.sym) = lookup(s);
                          if (!(yyval.sym))
                            (yyval.sym) = install(s, ID);
                        }
#line 2617 "soapcpp2_yacc.tab.c"
    break;

  case 79: /* ctor: name  */
#line 537 "soapcpp2_yacc.y"
                        {
                          sp->entry = enter(sp->table, (yyvsp[0].sym));
                          sp->entry->info.typ = mknone();
                          sp->entry->info.sto = permission;
                          sp->entry->info.offset = sp->offset;
                          sp->node.typ = mkvoid();
                          sp->node.sto = Snone;
                          if ((yyvsp[0].sym) != sp->table->sym)
                          {
                            if (sp->table->level == GLOBAL)
                            {
                              sp->entry->info.typ = mkint();
                              sp->node.typ = mkint();
                            }
                            else if (strncmp((yyvsp[0].sym)->name, "operator ", 9))
                            {
                              sprintf(errbuf, "invalid constructor function '%s' or missing return type", (yyvsp[0].sym)->name);
                              semerror(errbuf);
                            }
                          }
                        }
#line 2643 "soapcpp2_yacc.tab.c"
    break;

  case 80: /* dtor: virtual '~' id  */
#line 560 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[0].sym) != sp->table->sym)
                          {
                            sprintf(errbuf, "invalid destructor function '%s'", (yyvsp[0].sym)->name);
                            semerror(errbuf);
                          }
                          else
                          {
                            s = (char*)emalloc(strlen((yyvsp[0].sym)->name) + 2);
                            s2 = strrchr((yyvsp[0].sym)->name, ':');
                            if (s2 && *(s2+1) && (s2 == (yyvsp[0].sym)->name || *(s2-1) != ':'))
                            {
                              strncpy(s, (yyvsp[0].sym)->name, s2 - (yyvsp[0].sym)->name + 1);
                              strcat(s, "~");
                              strcat(s, s2 + 1);
                            }
                            else
                            {
                              strcpy(s, "~");
                              strcat(s, (yyvsp[0].sym)->name);
                            }
                            sym = lookup(s);
                            if (!sym)
                              sym = install(s, ID);
                            sp->entry = enter(sp->table, sym);
                            sp->entry->info.typ = mknone();
                            sp->entry->info.sto = (yyvsp[-2].sto);
                            sp->entry->info.offset = sp->offset;
                          }
                          sp->node.typ = mkvoid();
                          sp->node.sto = Snone;
                        }
#line 2680 "soapcpp2_yacc.tab.c"
    break;

  case 81: /* func: fname '(' s6 fargso ')' const abstract  */
#line 594 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[-6].e)->level == GLOBAL)
                          {
                            if (!((int)(yyvsp[-6].e)->info.sto & (int)Sextern) &&
                                sp->entry && sp->entry->info.typ->type == Tpointer &&
                                ((Tnode*)sp->entry->info.typ->ref)->type == Tchar)
                            {
                              sprintf(errbuf, "last output parameter of service operation function prototype '%s' is a pointer to a char which will only return one byte: use char** instead to return a string", (yyvsp[-6].e)->sym->name);
                              semwarn(errbuf);
                            }
                            if (((int)(yyvsp[-6].e)->info.sto & (int)Sextern))
                            {
                              (yyvsp[-6].e)->info.typ = mkmethod((yyvsp[-6].e)->info.typ, sp->table);
                            }
                            else if (sp->entry &&
                                (sp->entry->info.typ->type == Tpointer ||
                                 sp->entry->info.typ->type == Treference ||
                                 sp->entry->info.typ->type == Tarray ||
                                 is_transient(sp->entry->info.typ)))
                            {
                              if ((yyvsp[-6].e)->info.typ->type == Tint)
                              {
                                sp->entry->info.sto = (Storage)((int)sp->entry->info.sto | (int)Sreturn);
                                (yyvsp[-6].e)->info.typ = mkfun(sp->entry);
                                (yyvsp[-6].e)->info.typ->id = (yyvsp[-6].e)->sym;
                                if (!is_transient(sp->entry->info.typ))
                                {
                                  if (!is_response(sp->entry->info.typ))
                                  {
                                    if (!is_XML(sp->entry->info.typ) && !is_stdXML(sp->entry->info.typ))
                                      add_response((yyvsp[-6].e), sp->entry);
                                  }
                                  else
                                  {
                                    add_result(sp->entry->info.typ);
                                  }
                                }
                                add_request((yyvsp[-6].e)->sym, sp);
                              }
                              else
                              {
                                sprintf(errbuf, "return type of service operation function prototype '%s' must be integer", (yyvsp[-6].e)->sym->name);
                                semerror(errbuf);
                              }
                            }
                            else
                            {
                              sprintf(errbuf, "last output parameter of service operation function prototype '%s' is a return parameter and must be a pointer or reference, or use %s(..., void) for one-way sends", (yyvsp[-6].e)->sym->name, (yyvsp[-6].e)->sym->name);
                              semerror(errbuf);
                            }
                          }
                          else if ((yyvsp[-6].e)->level == INTERNAL)
                          {
                            (yyvsp[-6].e)->info.typ = mkmethod((yyvsp[-6].e)->info.typ, sp->table);
                            (yyvsp[-6].e)->info.sto = (Storage)((int)(yyvsp[-6].e)->info.sto | (int)(yyvsp[-1].sto) | (int)(yyvsp[0].sto));
                            transient &= ~1;
                          }
                          exitscope();
                        }
#line 2744 "soapcpp2_yacc.tab.c"
    break;

  case 82: /* fname: %empty  */
#line 654 "soapcpp2_yacc.y"
                        { (yyval.e) = sp->entry; }
#line 2750 "soapcpp2_yacc.tab.c"
    break;

  case 83: /* fargso: %empty  */
#line 656 "soapcpp2_yacc.y"
                        { }
#line 2756 "soapcpp2_yacc.tab.c"
    break;

  case 84: /* fargso: fargs  */
#line 657 "soapcpp2_yacc.y"
                        { }
#line 2762 "soapcpp2_yacc.tab.c"
    break;

  case 85: /* fargs: farg  */
#line 659 "soapcpp2_yacc.y"
                        { }
#line 2768 "soapcpp2_yacc.tab.c"
    break;

  case 86: /* fargs: farg ',' fargs  */
#line 661 "soapcpp2_yacc.y"
                        { }
#line 2774 "soapcpp2_yacc.tab.c"
    break;

  case 87: /* fargs: error ID  */
#line 662 "soapcpp2_yacc.y"
                        {
                          sprintf(errbuf, "undefined '%s'", (yyvsp[0].sym)->name);
                          synerror(errbuf);
                        }
#line 2783 "soapcpp2_yacc.tab.c"
    break;

  case 88: /* fargs: error ','  */
#line 666 "soapcpp2_yacc.y"
                        {
                          synerror("formal argument expected");
                          yyerrok;
                        }
#line 2792 "soapcpp2_yacc.tab.c"
    break;

  case 89: /* farg: tspec ptrs arg  */
#line 672 "soapcpp2_yacc.y"
                        { }
#line 2798 "soapcpp2_yacc.tab.c"
    break;

  case 90: /* arg: arrayck init  */
#line 674 "soapcpp2_yacc.y"
                       {
                          if (sp->table->level != PARAM)
                            p = enter(sp->table, gensymidx("param", (int)++sp->val));
                          else if (eflag || zflag == 0 || zflag > 3)
                            p = enter(sp->table, gensymidx("_param", (int)++sp->val));
                          else
                            p = enter(sp->table, gensym("_param"));
                          if (((int)(yyvsp[-1].rec).sto & (int)Stypedef))
                            semwarn("typedef in function argument");
                          p->info.typ = (yyvsp[-1].rec).typ;
                          p->info.sto = (yyvsp[-1].rec).sto;
                          p->info.offset = sp->offset;
                          if ((yyvsp[0].rec).hasval)
                            set_value(p, (yyvsp[-1].rec).typ, &(yyvsp[0].rec));
                          if (((int)(yyvsp[-1].rec).sto & (int)Sextern))
                            p->level = GLOBAL;
                          else if (sp->grow)
                            sp->offset += p->info.typ->width;
                          else if (p->info.typ->width > sp->offset)
                            sp->offset = p->info.typ->width;
                          sp->entry = p;
                        }
#line 2825 "soapcpp2_yacc.tab.c"
    break;

  case 91: /* arg: ID arrayck tag occurs init  */
#line 697 "soapcpp2_yacc.y"
                        {
                          if (soap_version == 2 && *(yyvsp[-4].sym)->name == '_' && sp->table->level == GLOBAL)
                          {
                            sprintf(errbuf, "SOAP 1.2 does not support anonymous parameters '%s'", (yyvsp[-4].sym)->name);
                            semwarn(errbuf);
                          }
                          if (((int)(yyvsp[-3].rec).sto & (int)Stypedef))
                            semwarn("typedef in function argument");
                          p = enter(sp->table, (yyvsp[-4].sym));
                          p->info.typ = (yyvsp[-3].rec).typ;
                          p->info.sto = (yyvsp[-3].rec).sto;
			  p->tag = (yyvsp[-2].s);
                          if ((yyvsp[-1].rec).minOccurs < 0)
                          {
                            if ((yyvsp[0].rec).hasval ||
                                ((int)(yyvsp[-3].rec).sto & (int)Sattribute) ||
                                ((int)(yyvsp[-3].rec).sto & (int)Sspecial) ||
                                (yyvsp[-3].rec).typ->type == Tpointer ||
                                (yyvsp[-3].rec).typ->type == Ttemplate ||
                                is_anyAttribute((yyvsp[-3].rec).typ) ||
                                !strncmp((yyvsp[-4].sym)->name, "__size", 6))
                              p->info.minOccurs = 0;
                            else
                              p->info.minOccurs = 1;
                          }
                          else
                          {
                            p->info.minOccurs = (yyvsp[-1].rec).minOccurs;
                          }
                          p->info.maxOccurs = (yyvsp[-1].rec).maxOccurs;
                          p->info.nillable = (yyvsp[-1].rec).nillable;
                          p->info.offset = sp->offset;
                          if ((yyvsp[0].rec).hasval)
                            set_value(p, (yyvsp[-3].rec).typ, &(yyvsp[0].rec));
                          if (((int)(yyvsp[-3].rec).sto & (int)Sextern))
                            p->level = GLOBAL;
                          else if (sp->grow)
                            sp->offset += p->info.typ->width;
                          else if (p->info.typ->width > sp->offset)
                            sp->offset = p->info.typ->width;
                          sp->entry = p;
                        }
#line 2872 "soapcpp2_yacc.tab.c"
    break;

  case 92: /* sym: ID tag init  */
#line 740 "soapcpp2_yacc.y"
                        {
                          tmp = sp->node;
                          p = enter(sp->table, (yyvsp[-2].sym));
                          p->info.typ = mkint();
                          p->info.sto = permission;
			  p->tag = (yyvsp[-1].s);
                          p->info.hasval = True;
                          p->info.ptrval = False;
                          p->info.fixed = (yyvsp[0].rec).fixed;
                          p->info.val.i = sp->val;
                          if ((yyvsp[0].rec).hasval)
                          {
                            set_value(p, p->info.typ, &(yyvsp[0].rec));
                            sp->val = p->info.val.i;
                          }
                          if (sp->mask)
                            sp->val <<= 1;
                          else
                            sp->val++;
                          p->info.offset = sp->offset;
                          sp->entry = p;
                        }
#line 2899 "soapcpp2_yacc.tab.c"
    break;

  case 93: /* texpf: texp  */
#line 772 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 2905 "soapcpp2_yacc.tab.c"
    break;

  case 94: /* texpf: tspec ptrs '(' s6 fargso ')'  */
#line 774 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkmethod(tmp.typ, sp->table);
                          transient &= ~1;
                          exitscope();
                        }
#line 2915 "soapcpp2_yacc.tab.c"
    break;

  case 95: /* texp: tspec ptrs array  */
#line 781 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 2921 "soapcpp2_yacc.tab.c"
    break;

  case 96: /* texp: tspec ptrs ID array  */
#line 783 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 2927 "soapcpp2_yacc.tab.c"
    break;

  case 97: /* spec: type  */
#line 790 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = (yyvsp[0].typ);
                          (yyval.rec).sto = Snone;
                          sp->node = (yyval.rec);
                        }
#line 2937 "soapcpp2_yacc.tab.c"
    break;

  case 98: /* spec: store spec  */
#line 795 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = (yyvsp[0].rec).typ;
                          (yyval.rec).sto = (Storage)((int)(yyvsp[-1].sto) | (int)(yyvsp[0].rec).sto);
                          if (((int)(yyval.rec).sto & (int)Sattribute))
                          {
                            if (is_smart((yyvsp[0].rec).typ))
                            {
                              if (!is_primitive_or_string((yyvsp[0].rec).typ->ref) &&
                                  !is_stdstr((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_binary((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_external((Tnode*)(yyvsp[0].rec).typ->ref))
                              {
                                semwarn("invalid attribute smart pointer @type");
                                (yyval.rec).sto = (Storage)((int)(yyval.rec).sto & ~(int)Sattribute);
                              }
                            }
                            else if ((yyvsp[0].rec).typ->type == Tpointer)
                            {
                              if (!is_primitive_or_string((yyvsp[0].rec).typ->ref) &&
                                  !is_stdstr((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_binary((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_external((Tnode*)(yyvsp[0].rec).typ->ref))
                              {
                                semwarn("invalid attribute pointer @type");
                                (yyval.rec).sto = (Storage)((int)(yyval.rec).sto & ~(int)Sattribute);
                              }
                            }
                            else if (
                                !is_primitive_or_string((yyvsp[0].rec).typ) &&
                                !is_stdstr((yyvsp[0].rec).typ) &&
                                !is_binary((yyvsp[0].rec).typ) &&
                                !is_external((yyvsp[0].rec).typ))
                            {
                              semwarn("invalid attribute @type");
                              (yyval.rec).sto = (Storage)((int)(yyval.rec).sto & ~(int)Sattribute);
                            }
                          }
                          sp->node = (yyval.rec);
                          if (((int)(yyvsp[-1].sto) & (int)Sextern))
                            transient = 0;
                        }
#line 2983 "soapcpp2_yacc.tab.c"
    break;

  case 99: /* spec: type spec  */
#line 836 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[-1].typ)->type == Tint)
                            switch ((yyvsp[0].rec).typ->type)
                            {
                              case Tchar:       (yyval.rec).typ = (yyvsp[0].rec).typ; break;
                              case Tshort:      (yyval.rec).typ = (yyvsp[0].rec).typ; break;
                              case Tint:        (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tlong:       (yyval.rec).typ = (yyvsp[0].rec).typ; break;
                              case Tllong:      (yyval.rec).typ = (yyvsp[0].rec).typ; break;
                              default:          semwarn("invalid int type specified");
                                                (yyval.rec).typ = (yyvsp[0].rec).typ;
                            }
                          else if ((yyvsp[-1].typ)->type == Tuint)
                            switch ((yyvsp[0].rec).typ->type)
                            {
                              case Tchar:       (yyval.rec).typ = mkuchar(); break;
                              case Tshort:      (yyval.rec).typ = mkushort(); break;
                              case Tint:        (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tlong:       (yyval.rec).typ = mkulong(); break;
                              case Tllong:      (yyval.rec).typ = mkullong(); break;
                              default:          semwarn("invalid unsigned type specified");
                                                (yyval.rec).typ = (yyvsp[0].rec).typ;
                            }
                          else if ((yyvsp[-1].typ)->type == Tlong)
                            switch ((yyvsp[0].rec).typ->type)
                            {
                              case Tint:        (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tlong:       (yyval.rec).typ = mkllong(); break;
                              case Tuint:       (yyval.rec).typ = mkulong(); break;
                              case Tulong:      (yyval.rec).typ = mkullong(); break;
                              case Tdouble:     (yyval.rec).typ = mkldouble(); break;
                              default:          semwarn("invalid use of 'long'");
                                                (yyval.rec).typ = (yyvsp[0].rec).typ;
                            }
                          else if ((yyvsp[-1].typ)->type == Tulong)
                            switch ((yyvsp[0].rec).typ->type)
                            {
                              case Tint:        (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tlong:       (yyval.rec).typ = mkullong(); break;
                              case Tuint:       (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tulong:      (yyval.rec).typ = mkullong(); break;
                              default:          semwarn("invalid use of 'long'");
                                                (yyval.rec).typ = (yyvsp[0].rec).typ;
                            }
                          else if ((yyvsp[0].rec).typ->type == Tint)
                            (yyval.rec).typ = (yyvsp[-1].typ);
                          else
                            semwarn("invalid type specified (missing ';' or type name used as non-type identifier?)");
                          (yyval.rec).sto = (yyvsp[0].rec).sto;
                          sp->node = (yyval.rec);
                        }
#line 3039 "soapcpp2_yacc.tab.c"
    break;

  case 100: /* tspec: store  */
#line 888 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkint();
                          (yyval.rec).sto = (yyvsp[0].sto);
                          sp->node = (yyval.rec);
                          if (((int)(yyvsp[0].sto) & (int)Sextern))
                            transient = 0;
                        }
#line 3051 "soapcpp2_yacc.tab.c"
    break;

  case 101: /* tspec: type  */
#line 895 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = (yyvsp[0].typ);
                          (yyval.rec).sto = Snone;
                          sp->node = (yyval.rec);
                        }
#line 3061 "soapcpp2_yacc.tab.c"
    break;

  case 102: /* tspec: store tspec  */
#line 900 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = (yyvsp[0].rec).typ;
                          (yyval.rec).sto = (Storage)((int)(yyvsp[-1].sto) | (int)(yyvsp[0].rec).sto);
                          if (((int)(yyval.rec).sto & (int)Sattribute))
                          {
                            if (is_smart((yyvsp[0].rec).typ))
                            {
                              if (!is_primitive_or_string((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_stdstr((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_binary((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_external((Tnode*)(yyvsp[0].rec).typ->ref))
                              {
                                semwarn("invalid attribute smart pointer @type");
                                (yyval.rec).sto = (Storage)((int)(yyval.rec).sto & ~(int)Sattribute);
                              }
                            }
                            else if ((yyvsp[0].rec).typ->type == Tpointer)
                            {
                              if (!is_primitive_or_string((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_stdstr((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_binary((Tnode*)(yyvsp[0].rec).typ->ref) &&
                                  !is_external((Tnode*)(yyvsp[0].rec).typ->ref))
                              {
                                semwarn("invalid attribute pointer @type");
                                (yyval.rec).sto = (Storage)((int)(yyval.rec).sto & ~(int)Sattribute);
                              }
                            }
                            else if (
                                !is_primitive_or_string((yyvsp[0].rec).typ) &&
                                !is_stdstr((yyvsp[0].rec).typ) &&
                                !is_binary((yyvsp[0].rec).typ) &&
                                !is_external((yyvsp[0].rec).typ))
                            {
                              semwarn("invalid attribute @type");
                              (yyval.rec).sto = (Storage)((int)(yyval.rec).sto & ~(int)Sattribute);
                            }
                          }
                          sp->node = (yyval.rec);
                          if (((int)(yyvsp[-1].sto) & (int)Sextern))
                            transient = 0;
                        }
#line 3107 "soapcpp2_yacc.tab.c"
    break;

  case 103: /* tspec: type tspec  */
#line 941 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[-1].typ)->type == Tint)
                            switch ((yyvsp[0].rec).typ->type)
                            {
                              case Tchar:       (yyval.rec).typ = (yyvsp[0].rec).typ; break;
                              case Tshort:      (yyval.rec).typ = (yyvsp[0].rec).typ; break;
                              case Tint:        (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tlong:       (yyval.rec).typ = (yyvsp[0].rec).typ; break;
                              case Tllong:      (yyval.rec).typ = (yyvsp[0].rec).typ; break;
                              default:  semwarn("invalid int type specified");
                                        (yyval.rec).typ = (yyvsp[0].rec).typ;
                            }
                          else if ((yyvsp[-1].typ)->type == Tuint)
                            switch ((yyvsp[0].rec).typ->type)
                            {
                              case Tchar:       (yyval.rec).typ = mkuchar(); break;
                              case Tshort:      (yyval.rec).typ = mkushort(); break;
                              case Tint:        (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tlong:       (yyval.rec).typ = mkulong(); break;
                              case Tllong:      (yyval.rec).typ = mkullong(); break;
                              default:  semwarn("invalid unsigned type specified");
                                        (yyval.rec).typ = (yyvsp[0].rec).typ;
                            }
                          else if ((yyvsp[-1].typ)->type == Tlong)
                            switch ((yyvsp[0].rec).typ->type)
                            {
                              case Tint:        (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tlong:       (yyval.rec).typ = mkllong(); break;
                              case Tuint:       (yyval.rec).typ = mkulong(); break;
                              case Tulong:      (yyval.rec).typ = mkullong(); break;
                              case Tdouble:     (yyval.rec).typ = mkldouble(); break;
                              default:  semwarn("invalid use of 'long'");
                                        (yyval.rec).typ = (yyvsp[0].rec).typ;
                            }
                          else if ((yyvsp[-1].typ)->type == Tulong)
                            switch ((yyvsp[0].rec).typ->type)
                            {
                              case Tint:        (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tlong:       (yyval.rec).typ = mkullong(); break;
                              case Tuint:       (yyval.rec).typ = (yyvsp[-1].typ); break;
                              case Tulong:      (yyval.rec).typ = mkullong(); break;
                              default:  semwarn("invalid use of 'long'");
                                        (yyval.rec).typ = (yyvsp[0].rec).typ;
                            }
                          else if ((yyvsp[0].rec).typ->type == Tint)
                            (yyval.rec).typ = (yyvsp[-1].typ);
                          else
                            semwarn("invalid type specified (missing ';' or type name used as non-type identifier?)");
                          (yyval.rec).sto = (yyvsp[0].rec).sto;
                          sp->node = (yyval.rec);
                        }
#line 3163 "soapcpp2_yacc.tab.c"
    break;

  case 104: /* type: VOID  */
#line 993 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkvoid(); }
#line 3169 "soapcpp2_yacc.tab.c"
    break;

  case 105: /* type: BOOL  */
#line 994 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkbool(); }
#line 3175 "soapcpp2_yacc.tab.c"
    break;

  case 106: /* type: CHAR  */
#line 995 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkchar(); }
#line 3181 "soapcpp2_yacc.tab.c"
    break;

  case 107: /* type: WCHAR  */
#line 996 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkwchart(); }
#line 3187 "soapcpp2_yacc.tab.c"
    break;

  case 108: /* type: SHORT  */
#line 997 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkshort(); }
#line 3193 "soapcpp2_yacc.tab.c"
    break;

  case 109: /* type: INT  */
#line 998 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkint(); }
#line 3199 "soapcpp2_yacc.tab.c"
    break;

  case 110: /* type: LONG  */
#line 999 "soapcpp2_yacc.y"
                        { (yyval.typ) = mklong(); }
#line 3205 "soapcpp2_yacc.tab.c"
    break;

  case 111: /* type: LLONG  */
#line 1000 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkllong(); }
#line 3211 "soapcpp2_yacc.tab.c"
    break;

  case 112: /* type: ULLONG  */
#line 1001 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkullong(); }
#line 3217 "soapcpp2_yacc.tab.c"
    break;

  case 113: /* type: SIZE  */
#line 1002 "soapcpp2_yacc.y"
                        { (yyval.typ) = mksize(); }
#line 3223 "soapcpp2_yacc.tab.c"
    break;

  case 114: /* type: FLOAT  */
#line 1003 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkfloat(); }
#line 3229 "soapcpp2_yacc.tab.c"
    break;

  case 115: /* type: DOUBLE  */
#line 1004 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkdouble(); }
#line 3235 "soapcpp2_yacc.tab.c"
    break;

  case 116: /* type: SIGNED  */
#line 1005 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkint(); }
#line 3241 "soapcpp2_yacc.tab.c"
    break;

  case 117: /* type: UNSIGNED  */
#line 1006 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkuint(); }
#line 3247 "soapcpp2_yacc.tab.c"
    break;

  case 118: /* type: UCHAR  */
#line 1007 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkuchar(); }
#line 3253 "soapcpp2_yacc.tab.c"
    break;

  case 119: /* type: USHORT  */
#line 1008 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkushort(); }
#line 3259 "soapcpp2_yacc.tab.c"
    break;

  case 120: /* type: UINT  */
#line 1009 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkuint(); }
#line 3265 "soapcpp2_yacc.tab.c"
    break;

  case 121: /* type: ULONG  */
#line 1010 "soapcpp2_yacc.y"
                        { (yyval.typ) = mkulong(); }
#line 3271 "soapcpp2_yacc.tab.c"
    break;

  case 122: /* type: TIME  */
#line 1011 "soapcpp2_yacc.y"
                        { (yyval.typ) = mktimet(); }
#line 3277 "soapcpp2_yacc.tab.c"
    break;

  case 123: /* type: TEMPLATE '<' tname id '>' CLASS id  */
#line 1013 "soapcpp2_yacc.y"
                        {
                          if (!(p = entry(templatetable, (yyvsp[0].sym))))
                          {
                            p = enter(templatetable, (yyvsp[0].sym));
                            p->info.typ = mktemplate(NULL, (yyvsp[0].sym));
                            (yyvsp[0].sym)->token = TYPE;
                          }
                          (yyval.typ) = p->info.typ;
                        }
#line 3291 "soapcpp2_yacc.tab.c"
    break;

  case 124: /* type: CLASS '{' s2 decls '}'  */
#line 1023 "soapcpp2_yacc.y"
                        {
                          sym = gensym("_Struct");
                          sprintf(errbuf, "anonymous class will be named '%s'", sym->name);
                          semwarn(errbuf);
                          if ((p = entry(classtable, sym)))
                          {
                            if (p->info.typ->ref || p->info.typ->type != Tclass)
                            {
                              sprintf(errbuf, "class '%s' already declared at %s:%d", sym->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                          }
                          else
                          {
                            p = enter(classtable, sym);
                            p->info.typ = mkclass(NULL, 0);
                          }
                          sym->token = TYPE;
                          sp->table->sym = sym;
                          p->info.typ->ref = sp->table;
                          p->info.typ->width = sp->offset;
                          p->info.typ->id = sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3321 "soapcpp2_yacc.tab.c"
    break;

  case 125: /* type: classid '{' decls '}'  */
#line 1049 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(classtable, (yyvsp[-3].e)->sym)) && p->info.typ->ref)
                          {
                            if (is_mutable(p))
                            {
                              if (merge((Table*)p->info.typ->ref, sp->table))
                              {
                                sprintf(errbuf, "member name clash in class '%s' declared at %s:%d", (yyvsp[-3].e)->sym->name, p->filename, p->lineno);
                                semerror(errbuf);
                              }
                              p->info.typ->width += sp->offset;
                            }
                          }
                          else
                          {
                            p = reenter(classtable, (yyvsp[-3].e)->sym);
                            p->info.typ->ref = sp->table;
                            p->info.typ->width = sp->offset;
                            p->info.typ->id = p->sym;
                            if (p->info.typ->baseid)
                              sp->table->prev = (Table*)entry(classtable, p->info.typ->baseid)->info.typ->ref;
                          }
                          base_of_derived(p);
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3352 "soapcpp2_yacc.tab.c"
    break;

  case 126: /* type: classid ':' base '{' decls '}'  */
#line 1076 "soapcpp2_yacc.y"
                        {
                          p = reenter(classtable, (yyvsp[-5].e)->sym);
                          if (!(yyvsp[-3].e))
                          {
                            semerror("invalid base class");
                          }
                          else
                          {
                            sp->table->prev = (Table*)(yyvsp[-3].e)->info.typ->ref;
                            if (!sp->table->prev && !(yyvsp[-3].e)->info.typ->transient)
                            {
                              sprintf(errbuf, "class '%s' has incomplete type (if this class is not serializable then declare 'extern class %s')'", (yyvsp[-3].e)->sym->name, (yyvsp[-3].e)->sym->name);
                              semerror(errbuf);
                            }
                            p->info.typ->baseid = (yyvsp[-3].e)->info.typ->id;
                          }
                          p->info.typ->ref = sp->table;
                          p->info.typ->width = sp->offset;
                          p->info.typ->id = p->sym;
                          base_of_derived(p);
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3380 "soapcpp2_yacc.tab.c"
    break;

  case 127: /* type: class  */
#line 1099 "soapcpp2_yacc.y"
                        {
                          (yyvsp[0].e)->info.typ->id = (yyvsp[0].e)->sym;
                          (yyval.typ) = (yyvsp[0].e)->info.typ;
                        }
#line 3389 "soapcpp2_yacc.tab.c"
    break;

  case 128: /* type: STRUCT '{' s2 decls '}'  */
#line 1104 "soapcpp2_yacc.y"
                        {
                          sym = gensym("_Struct");
                          sprintf(errbuf, "anonymous struct will be named '%s'", sym->name);
                          semwarn(errbuf);
                          if ((p = entry(classtable, sym)))
                          {
                            if (p->info.typ->ref || p->info.typ->type != Tstruct)
                            {
                              sprintf(errbuf, "struct '%s' already declared at %s:%d", sym->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                            else
                            {
                              p->info.typ->ref = sp->table;
                              p->info.typ->width = sp->offset;
                            }
                          }
                          else
                          {
                            p = enter(classtable, sym);
                            p->info.typ = mkstruct(sp->table, sp->offset);
                          }
                          sp->table->sym = sym;
                          p->info.typ->id = sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3421 "soapcpp2_yacc.tab.c"
    break;

  case 129: /* type: structid '{' decls '}'  */
#line 1132 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(classtable, (yyvsp[-3].e)->sym)) && p->info.typ->ref)
                          {
                            if (is_mutable(p))
                            {
                              if (merge((Table*)p->info.typ->ref, sp->table))
                              {
                                sprintf(errbuf, "member name clash in struct '%s' declared at %s:%d", (yyvsp[-3].e)->sym->name, p->filename, p->lineno);
                                semerror(errbuf);
                              }
                              p->info.typ->width += sp->offset;
                            }
                          }
                          else
                          {
                            p = reenter(classtable, (yyvsp[-3].e)->sym);
                            p->info.typ->ref = sp->table;
                            p->info.typ->width = sp->offset;
                            p->info.typ->id = p->sym;
                          }
                          base_of_derived(p);
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3450 "soapcpp2_yacc.tab.c"
    break;

  case 130: /* type: STRUCT id  */
#line 1156 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(classtable, (yyvsp[0].sym))))
                          {
                            if (p->info.typ->type == Tstruct)
                            {
                              (yyval.typ) = p->info.typ;
                            }
                            else
                            {
                              sprintf(errbuf, "'struct '%s' redeclaration (line %d)", (yyvsp[0].sym)->name, p->lineno);
                              semerror(errbuf);
                              (yyval.typ) = mkint();
                            }
                          }
                          else
                          {
                            p = enter(classtable, (yyvsp[0].sym));
                            (yyval.typ) = p->info.typ = mkstruct(NULL, 0);
                            p->info.typ->id = (yyvsp[0].sym);
                          }
                        }
#line 3476 "soapcpp2_yacc.tab.c"
    break;

  case 131: /* type: UNION '{' s3 decls '}'  */
#line 1178 "soapcpp2_yacc.y"
                        {
                          sym = gensym("_Union");
                          sprintf(errbuf, "anonymous union will be named '%s'", sym->name);
                          semwarn(errbuf);
                          if ((p = entry(classtable, sym)))
                          {
                            if (p->info.typ->ref)
                            {
                              sprintf(errbuf, "union or struct '%s' already declared at %s:%d", sym->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                            else
                            {
                              p->info.typ->ref = sp->table;
                              p->info.typ->width = sp->offset;
                            }
                          }
                          else
                          {
                            p = enter(classtable, sym);
                            p->info.typ = mkunion(sp->table, sp->offset);
                          }
                          sp->table->sym = sym;
                          p->info.typ->id = sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3508 "soapcpp2_yacc.tab.c"
    break;

  case 132: /* type: unionid '{' decls '}'  */
#line 1206 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(classtable, (yyvsp[-3].e)->sym)) && p->info.typ->ref)
                          {
                            if (is_mutable(p))
                            {
                              if (merge((Table*)p->info.typ->ref, sp->table))
                              {
                                sprintf(errbuf, "member name clash in union '%s' declared at line %d", (yyvsp[-3].e)->sym->name, p->lineno);
                                semerror(errbuf);
                              }
                              if (p->info.typ->width < sp->offset)
                                p->info.typ->width = sp->offset;
                            }
                          }
                          else
                          {
                            p = reenter(classtable, (yyvsp[-3].e)->sym);
                            p->info.typ->ref = sp->table;
                            p->info.typ->width = sp->offset;
                            p->info.typ->id = p->sym;
                          }
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3537 "soapcpp2_yacc.tab.c"
    break;

  case 133: /* type: UNION id  */
#line 1230 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(classtable, (yyvsp[0].sym))))
                          {
                            if (p->info.typ->type == Tunion)
                            {
                              (yyval.typ) = p->info.typ;
                            }
                            else
                            {
                              sprintf(errbuf, "'union %s' redeclaration (line %d)", (yyvsp[0].sym)->name, p->lineno);
                              semerror(errbuf);
                              (yyval.typ) = mkint();
                            }
                          }
                          else
                          {
                            p = enter(classtable, (yyvsp[0].sym));
                            (yyval.typ) = p->info.typ = mkunion(NULL, 0);
                            p->info.typ->id = (yyvsp[0].sym);
                          }
                        }
#line 3563 "soapcpp2_yacc.tab.c"
    break;

  case 134: /* type: ENUM '{' s2 dclrs s5 '}'  */
#line 1252 "soapcpp2_yacc.y"
                        {
                          sym = gensym("_Enum");
                          sprintf(errbuf, "anonymous enum will be named '%s'", sym->name);
                          semwarn(errbuf);
                          if ((p = entry(enumtable, sym)))
                          {
                            if (p->info.typ->ref)
                            {
                              sprintf(errbuf, "enum '%s' already declared at %s:%d", sym->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                            else
                            {
                              p->info.typ->ref = sp->table;
                              p->info.typ->width = 4; /* 4 = enum */
                            }
                          }
                          else
                          {
                            p = enter(enumtable, sym);
                            p->info.typ = mkenum(sp->table);
                          }
                          p->info.typ->id = sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3594 "soapcpp2_yacc.tab.c"
    break;

  case 135: /* type: ENUM '*' '{' s4 dclrs s5 '}'  */
#line 1279 "soapcpp2_yacc.y"
                        {
                          sym = gensym("_Enum");
                          sprintf(errbuf, "anonymous enum will be named '%s'", sym->name);
                          semwarn(errbuf);
                          if ((p = entry(enumtable, sym)))
                          {
                            if (p->info.typ->ref)
                            {
                              sprintf(errbuf, "enum '%s' already declared at %s:%d", sym->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                            else
                            {
                              p->info.typ->ref = sp->table;
                              p->info.typ->width = 9; /* 9 = mask */
                            }
                          }
                          else
                          {
                            p = enter(enumtable, sym);
                            p->info.typ = mkmask(sp->table);
                          }
                          p->info.typ->id = sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3625 "soapcpp2_yacc.tab.c"
    break;

  case 136: /* type: enum '{' s2 dclrs s5 '}'  */
#line 1306 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[-5].e)->sym)))
                            if (!p->info.typ->ref)
                              p->info.typ->ref = sp->table;
                          p->info.typ->id = (yyvsp[-5].e)->sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3638 "soapcpp2_yacc.tab.c"
    break;

  case 137: /* type: enumsc '{' s2 dclrs s5 '}'  */
#line 1315 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[-5].e)->sym)))
                            if (!p->info.typ->ref)
                              p->info.typ->ref = sp->table;
                          p->info.typ->id = (yyvsp[-5].e)->sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3651 "soapcpp2_yacc.tab.c"
    break;

  case 138: /* type: mask '{' s4 dclrs s5 '}'  */
#line 1324 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[-5].e)->sym)))
                          {
                            if (!p->info.typ->ref)
                            {
                              p->info.typ->ref = sp->table;
                              p->info.typ->width = 9; /* 9 = mask */
                            }
                          }
                          p->info.typ->id = (yyvsp[-5].e)->sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3669 "soapcpp2_yacc.tab.c"
    break;

  case 139: /* type: masksc '{' s4 dclrs s5 '}'  */
#line 1338 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[-5].e)->sym)))
                          {
                            if (!p->info.typ->ref)
                            {
                              p->info.typ->ref = sp->table;
                              p->info.typ->width = 9; /* 9 = mask */
                            }
                          }
                          p->info.typ->id = (yyvsp[-5].e)->sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3687 "soapcpp2_yacc.tab.c"
    break;

  case 140: /* type: ENUM id  */
#line 1351 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[0].sym))))
                          {
                            if (p->info.typ->type != Tenum)
                            {
                              sprintf(errbuf, "'enum %s' used where enum class is expected", (yyvsp[0].sym)->name);
                              semwarn(errbuf);
                            }
                            (yyval.typ) = p->info.typ;
                          }
                          else
                          {
                            p = enter(enumtable, (yyvsp[0].sym));
                            (yyval.typ) = p->info.typ = mkenum(NULL);
                            p->info.typ->id = (yyvsp[0].sym);
                          }
                        }
#line 3709 "soapcpp2_yacc.tab.c"
    break;

  case 141: /* type: ENUM sc  */
#line 1368 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[0].sym))))
                          {
                            if (p->info.typ->type != Tenumsc)
                            {
                              sprintf(errbuf, "'enum class %s' used where enum is expected", (yyvsp[0].sym)->name);
                              semwarn(errbuf);
                            }
                            (yyval.typ) = p->info.typ;
                          }
                          else
                          {
                            p = enter(enumtable, (yyvsp[0].sym));
                            (yyval.typ) = p->info.typ = mkenumsc(NULL);
                            p->info.typ->id = (yyvsp[0].sym);
                            (yyvsp[0].sym)->token = TYPE;
                          }
                        }
#line 3732 "soapcpp2_yacc.tab.c"
    break;

  case 142: /* type: TYPE  */
#line 1386 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(typetable, (yyvsp[0].sym))))
                          {
                            (yyval.typ) = p->info.typ;
                          }
                          else if ((p = entry(classtable, (yyvsp[0].sym))))
                          {
                            (yyval.typ) = p->info.typ;
                          }
                          else if ((p = entry(enumtable, (yyvsp[0].sym))))
                          {
                            (yyval.typ) = p->info.typ;
                          }
                          else if ((yyvsp[0].sym) == lookup("std::string") || (yyvsp[0].sym) == lookup("std::wstring"))
                          {
                            p = enter(classtable, (yyvsp[0].sym));
                            (yyval.typ) = p->info.typ = mkclass(NULL, 8);
                            p->info.typ->id = (yyvsp[0].sym);
                            if (cflag)
                              p->info.typ->transient = 1;       /* make std::string transient in C */
                            else
                              p->info.typ->transient = -2;      /* otherwise volatile in C++ */
                          }
                          else
                          {
                            sprintf(errbuf, "unknown type '%s'", (yyvsp[0].sym)->name);
                            semerror(errbuf);
                            (yyval.typ) = mkint();
                          }
                        }
#line 3767 "soapcpp2_yacc.tab.c"
    break;

  case 143: /* type: TYPE '<' texpf '>'  */
#line 1417 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(templatetable, (yyvsp[-3].sym))))
                          {
                            (yyval.typ) = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                            if (p->info.typ->transient)
                              (yyval.typ)->transient = p->info.typ->transient;
                          }
                          else if ((yyvsp[-3].sym) == lookup("std::deque"))
                          {
                            add_pragma("#include <deque>");
                            p = enter(templatetable, (yyvsp[-3].sym));
                            (yyval.typ) = p->info.typ = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                          }
                          else if ((yyvsp[-3].sym) == lookup("std::list"))
                          {
                            add_pragma("#include <list>");
                            p = enter(templatetable, (yyvsp[-3].sym));
                            (yyval.typ) = p->info.typ = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                          }
                          else if ((yyvsp[-3].sym) == lookup("std::vector"))
                          {
                            add_pragma("#include <vector>");
                            p = enter(templatetable, (yyvsp[-3].sym));
                            (yyval.typ) = p->info.typ = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                          }
                          else if ((yyvsp[-3].sym) == lookup("std::set"))
                          {
                            add_pragma("#include <set>");
                            p = enter(templatetable, (yyvsp[-3].sym));
                            (yyval.typ) = p->info.typ = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                          }
                          else if ((yyvsp[-3].sym) == lookup("std::queue"))
                          {
                            add_pragma("#include <queue>");
                            p = enter(templatetable, (yyvsp[-3].sym));
                            (yyval.typ) = p->info.typ = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                            (yyval.typ)->transient = 1; /* not serializable */
                          }
                          else if ((yyvsp[-3].sym) == lookup("std::stack"))
                          {
                            add_pragma("#include <stack>");
                            p = enter(templatetable, (yyvsp[-3].sym));
                            (yyval.typ) = p->info.typ = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                            (yyval.typ)->transient = 1; /* not serializable */
                          }
                          else if ((yyvsp[-3].sym) == lookup("std::shared_ptr") ||
                              (yyvsp[-3].sym) == lookup("std::unique_ptr") ||
                              (yyvsp[-3].sym) == lookup("std::auto_ptr"))
                          {
                            (yyval.typ) = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                            (yyval.typ)->transient = -2; /* volatile indicates smart pointer template */
                            if (!c11flag)
                              semwarn("To use smart pointers you should also use wsdl2h and soapcpp2 with option -c++11 or -c++14 or -c++17");
                          }
                          else if ((yyvsp[-3].sym) == lookup("std::optional"))
                          {
                            (yyval.typ) = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                            (yyval.typ)->transient = -2; /* volatile indicates smart pointer or optional template */
                            if (!c11flag)
                              semwarn("To use std::optional you should also use wsdl2h and soapcpp2 with option -c++17");
                          }
                          else if ((yyvsp[-3].sym) == lookup("std::weak_ptr") ||
                              (yyvsp[-3].sym) == lookup("std::function"))
                          {
                            (yyval.typ) = mktemplate((yyvsp[-1].rec).typ, (yyvsp[-3].sym));
                            (yyval.typ)->transient = 1; /* not serializable */
                          }
                          else
                          {
                            semerror("undefined template");
                            (yyval.typ) = mkint();
                          }
                        }
#line 3845 "soapcpp2_yacc.tab.c"
    break;

  case 144: /* type: error ID error  */
#line 1491 "soapcpp2_yacc.y"
                        {
                          sprintf(errbuf, "undeclared '%s'", (yyvsp[-1].sym)->name);
                          synerror(errbuf);
                          (yyval.typ) = mkint();
                        }
#line 3855 "soapcpp2_yacc.tab.c"
    break;

  case 145: /* type: error ID '>'  */
#line 1496 "soapcpp2_yacc.y"
                        {
                          sprintf(errbuf, "perhaps trying to use a template with an undefined type parameter '%s'?", (yyvsp[-1].sym)->name);
                          synerror(errbuf);
                          (yyval.typ) = mkint();
                        }
#line 3865 "soapcpp2_yacc.tab.c"
    break;

  case 146: /* type: error '>'  */
#line 1501 "soapcpp2_yacc.y"
                        {
                          synerror("perhaps trying to use an undefined template or template with a non-type template parameter? Declare 'template <typename T> class name'");
                          (yyval.typ) = mkint();
                        }
#line 3874 "soapcpp2_yacc.tab.c"
    break;

  case 147: /* type: CLASS error '}'  */
#line 1506 "soapcpp2_yacc.y"
                        {
                          synerror("malformed class definition (use spacing around ':' to separate derived : base)");
                          yyerrok;
                          (yyval.typ) = mkint();
                        }
#line 3884 "soapcpp2_yacc.tab.c"
    break;

  case 148: /* type: STRUCT error '}'  */
#line 1512 "soapcpp2_yacc.y"
                        {
                          synerror("malformed struct definition");
                          yyerrok;
                          (yyval.typ) = mkint();
                        }
#line 3894 "soapcpp2_yacc.tab.c"
    break;

  case 149: /* type: UNION error '}'  */
#line 1518 "soapcpp2_yacc.y"
                        {
                          synerror("malformed union definition");
                          yyerrok;
                          (yyval.typ) = mkint();
                        }
#line 3904 "soapcpp2_yacc.tab.c"
    break;

  case 150: /* type: ENUM error '}'  */
#line 1524 "soapcpp2_yacc.y"
                        {
                          synerror("malformed enum definition");
                          yyerrok;
                          (yyval.typ) = mkint();
                        }
#line 3914 "soapcpp2_yacc.tab.c"
    break;

  case 151: /* structid: struct s2  */
#line 1530 "soapcpp2_yacc.y"
                        {
                          sp->table->sym = (yyvsp[-1].e)->sym;
                          (yyval.e) = (yyvsp[-1].e);
                        }
#line 3923 "soapcpp2_yacc.tab.c"
    break;

  case 152: /* struct: STRUCT id  */
#line 1535 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(classtable, (yyvsp[0].sym))))
                          {
                            if (p->info.typ->ref)
                            {
                              if (!is_mutable(p))
                              {
                                sprintf(errbuf, "struct '%s' already declared at %s:%d", (yyvsp[0].sym)->name, p->filename, p->lineno);
                                semerror(errbuf);
                              }
                            }
                            else
                            {
                              p = reenter(classtable, (yyvsp[0].sym));
                            }
                            p->info.typ->transient = transient;
                          }
                          else
                          {
                            p = enter(classtable, (yyvsp[0].sym));
                            p->info.typ = mkstruct(NULL, 0);
                          }
                          (yyval.e) = p;
                        }
#line 3952 "soapcpp2_yacc.tab.c"
    break;

  case 153: /* classid: class s2  */
#line 1560 "soapcpp2_yacc.y"
                        {
                          sp->table->sym = (yyvsp[-1].e)->sym;
                          (yyval.e) = (yyvsp[-1].e);
                        }
#line 3961 "soapcpp2_yacc.tab.c"
    break;

  case 154: /* class: CLASS id  */
#line 1565 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(classtable, (yyvsp[0].sym))))
                          {
                            if (p->info.typ->ref)
                            {
                              if (!is_mutable(p))
                              {
                                sprintf(errbuf, "class '%s' already declared at %s:%d (redundant 'class' specifier here?)", (yyvsp[0].sym)->name, p->filename, p->lineno);
                                semerror(errbuf);
                              }
                            }
                            else
                            {
                              p = reenter(classtable, (yyvsp[0].sym));
                            }
                            p->info.typ->transient = transient;
                          }
                          else
                          {
                            p = enter(classtable, (yyvsp[0].sym));
                            p->info.typ = mkclass(NULL, 0);
                            p->info.typ->id = p->sym;
                          }
                          (yyvsp[0].sym)->token = TYPE;
                          (yyval.e) = p;
                        }
#line 3992 "soapcpp2_yacc.tab.c"
    break;

  case 155: /* unionid: union s3  */
#line 1592 "soapcpp2_yacc.y"
                        {
                          sp->table->sym = (yyvsp[-1].e)->sym;
                          (yyval.e) = (yyvsp[-1].e);
                        }
#line 4001 "soapcpp2_yacc.tab.c"
    break;

  case 156: /* union: UNION id  */
#line 1597 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(classtable, (yyvsp[0].sym))))
                          {
                            if (p->info.typ->ref)
                            {
                              if (!is_mutable(p))
                              {
                                sprintf(errbuf, "union '%s' already declared at %s:%d", (yyvsp[0].sym)->name, p->filename, p->lineno);
                                semerror(errbuf);
                              }
                            }
                            else
                            {
                              p = reenter(classtable, (yyvsp[0].sym));
                            }
                            p->info.typ->transient = transient;
                          }
                          else
                          {
                            p = enter(classtable, (yyvsp[0].sym));
                            p->info.typ = mkunion(NULL, 0);
                          }
                          (yyval.e) = p;
                        }
#line 4030 "soapcpp2_yacc.tab.c"
    break;

  case 157: /* enum: ENUM id utype  */
#line 1622 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[-1].sym))))
                          {
                            if (p->info.typ->ref)
                            {
                              sprintf(errbuf, "enum '%s' already declared at %s:%d", (yyvsp[-1].sym)->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                          }
                          else
                          {
                            p = enter(enumtable, (yyvsp[-1].sym));
                            p->info.typ = mkenum(0);
                          }
                          p->info.typ->width = (int)(yyvsp[0].i);
                          (yyval.e) = p;
                        }
#line 4052 "soapcpp2_yacc.tab.c"
    break;

  case 158: /* enumsc: ENUM sc utype  */
#line 1640 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[-1].sym))))
                          {
                            if (p->info.typ->ref)
                            {
                              sprintf(errbuf, "enum '%s' already declared at %s:%d", (yyvsp[-1].sym)->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                          }
                          else
                          {
                            p = enter(enumtable, (yyvsp[-1].sym));
                            p->info.typ = mkenumsc(0);
                          }
                          p->info.typ->width = (int)(yyvsp[0].i);
                          (yyvsp[-1].sym)->token = TYPE;
                          (yyval.e) = p;
                        }
#line 4075 "soapcpp2_yacc.tab.c"
    break;

  case 159: /* mask: ENUM '*' id utype  */
#line 1660 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[-1].sym))))
                          {
                            if (p->info.typ->ref)
                            {
                              sprintf(errbuf, "enum '%s' already declared at %s:%d", (yyvsp[-1].sym)->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                            else
                            {
                              p->info.typ = mkmask(0);
                            }
                          }
                          else
                          {
                            p = enter(enumtable, (yyvsp[-1].sym));
                            p->info.typ = mkmask(0);
                          }
                          (yyval.e) = p;
                        }
#line 4100 "soapcpp2_yacc.tab.c"
    break;

  case 160: /* masksc: ENUM '*' sc utype  */
#line 1682 "soapcpp2_yacc.y"
                        {
                          if ((p = entry(enumtable, (yyvsp[-1].sym))))
                          {
                            if (p->info.typ->ref)
                            {
                              sprintf(errbuf, "enum '%s' already declared at %s:%d", (yyvsp[-1].sym)->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                            else
                            {
                              p->info.typ = mkmasksc(0);
                            }
                          }
                          else
                          {
                            p = enter(enumtable, (yyvsp[-1].sym));
                            p->info.typ = mkmasksc(0);
                          }
                          (yyvsp[-1].sym)->token = TYPE;
                          (yyval.e) = p;
                        }
#line 4126 "soapcpp2_yacc.tab.c"
    break;

  case 161: /* sc: STRUCT id  */
#line 1704 "soapcpp2_yacc.y"
                        {
                          (yyval.sym) = (yyvsp[0].sym);
                          if (!c11flag)
                            semwarn("To use scoped enumerations (enum class) you should also use wsdl2h and soapcpp2 with option -c++11 or -c++14 or -c++17");
                        }
#line 4136 "soapcpp2_yacc.tab.c"
    break;

  case 162: /* sc: CLASS id  */
#line 1709 "soapcpp2_yacc.y"
                        {
                          (yyval.sym) = (yyvsp[0].sym);
                          if (!c11flag)
                            semwarn("To use scoped enumerations (enum class) you must also use wsdl2h and soapcpp2 with option -c++11 or -c++14 or -c++17");
                        }
#line 4146 "soapcpp2_yacc.tab.c"
    break;

  case 163: /* utype: ':' CHAR  */
#line 1715 "soapcpp2_yacc.y"
                        { (yyval.i) = 1; }
#line 4152 "soapcpp2_yacc.tab.c"
    break;

  case 164: /* utype: ':' WCHAR  */
#line 1716 "soapcpp2_yacc.y"
                        { (yyval.i) = 4; }
#line 4158 "soapcpp2_yacc.tab.c"
    break;

  case 165: /* utype: ':' SHORT  */
#line 1717 "soapcpp2_yacc.y"
                        { (yyval.i) = 2; }
#line 4164 "soapcpp2_yacc.tab.c"
    break;

  case 166: /* utype: ':' INT  */
#line 1718 "soapcpp2_yacc.y"
                        { (yyval.i) = 4; }
#line 4170 "soapcpp2_yacc.tab.c"
    break;

  case 167: /* utype: ':' LONG  */
#line 1719 "soapcpp2_yacc.y"
                        { (yyval.i) = 4; }
#line 4176 "soapcpp2_yacc.tab.c"
    break;

  case 168: /* utype: ':' LLONG  */
#line 1720 "soapcpp2_yacc.y"
                        { (yyval.i) = 8; }
#line 4182 "soapcpp2_yacc.tab.c"
    break;

  case 169: /* utype: ':' TYPE  */
#line 1721 "soapcpp2_yacc.y"
                        {
                          (yyval.i) = 4;
                          p = entry(typetable, (yyvsp[0].sym));
                          if (!p)
                            p = entry(enumtable, (yyvsp[0].sym));
                          if (!p)
                            semerror("enum underlying type must be one of int8_t, int16_t, int32_t, int64_t");
                          else
                            (yyval.i) = p->info.typ->width;
                        }
#line 4197 "soapcpp2_yacc.tab.c"
    break;

  case 170: /* utype: ':'  */
#line 1731 "soapcpp2_yacc.y"
                        {
                          semerror("enum underlying type must be one of int8_t, int16_t, int32_t, int64_t");
                          (yyval.i) = 4;
                        }
#line 4206 "soapcpp2_yacc.tab.c"
    break;

  case 171: /* utype: %empty  */
#line 1735 "soapcpp2_yacc.y"
                        { (yyval.i) = 4; /* 4 = enum */ }
#line 4212 "soapcpp2_yacc.tab.c"
    break;

  case 172: /* tname: CLASS  */
#line 1737 "soapcpp2_yacc.y"
                        { }
#line 4218 "soapcpp2_yacc.tab.c"
    break;

  case 173: /* tname: STRUCT  */
#line 1738 "soapcpp2_yacc.y"
                        { }
#line 4224 "soapcpp2_yacc.tab.c"
    break;

  case 174: /* tname: TYPENAME  */
#line 1739 "soapcpp2_yacc.y"
                        { }
#line 4230 "soapcpp2_yacc.tab.c"
    break;

  case 175: /* base: PROTECTED base  */
#line 1742 "soapcpp2_yacc.y"
                        { (yyval.e) = (yyvsp[0].e); }
#line 4236 "soapcpp2_yacc.tab.c"
    break;

  case 176: /* base: PRIVATE base  */
#line 1743 "soapcpp2_yacc.y"
                        { (yyval.e) = (yyvsp[0].e); }
#line 4242 "soapcpp2_yacc.tab.c"
    break;

  case 177: /* base: PUBLIC base  */
#line 1744 "soapcpp2_yacc.y"
                        { (yyval.e) = (yyvsp[0].e); }
#line 4248 "soapcpp2_yacc.tab.c"
    break;

  case 178: /* base: TYPE  */
#line 1745 "soapcpp2_yacc.y"
                        {
                          (yyval.e) = entry(classtable, (yyvsp[0].sym));
                          if (!(yyval.e))
                          {
                            p = entry(typetable, (yyvsp[0].sym));
                            if (p && (p->info.typ->type == Tclass || p->info.typ->type == Tstruct))
                              (yyval.e) = p;
                          }
                        }
#line 4262 "soapcpp2_yacc.tab.c"
    break;

  case 179: /* base: STRUCT id  */
#line 1754 "soapcpp2_yacc.y"
                        { (yyval.e) = entry(classtable, (yyvsp[0].sym)); }
#line 4268 "soapcpp2_yacc.tab.c"
    break;

  case 180: /* base: CLASS id  */
#line 1755 "soapcpp2_yacc.y"
                        { (yyval.e) = entry(classtable, (yyvsp[0].sym)); }
#line 4274 "soapcpp2_yacc.tab.c"
    break;

  case 181: /* s2: %empty  */
#line 1757 "soapcpp2_yacc.y"
                        {
                          if (transient <= -2)
                            transient = 0;
                          permission = 0;
                          enterscope(mktable(NULL), 0);
                          sp->entry = NULL;
                        }
#line 4286 "soapcpp2_yacc.tab.c"
    break;

  case 182: /* s3: %empty  */
#line 1765 "soapcpp2_yacc.y"
                        {
                          if (transient <= -2)
                            transient = 0;
                          permission = 0;
                          enterscope(mktable(NULL), 0);
                          sp->entry = NULL;
                          sp->grow = False;
                        }
#line 4299 "soapcpp2_yacc.tab.c"
    break;

  case 183: /* s4: %empty  */
#line 1774 "soapcpp2_yacc.y"
                        {
                          enterscope(mktable(NULL), 0);
                          sp->entry = NULL;
                          sp->mask = True;
                          sp->val = 1;
                        }
#line 4310 "soapcpp2_yacc.tab.c"
    break;

  case 184: /* s5: %empty  */
#line 1781 "soapcpp2_yacc.y"
                        { }
#line 4316 "soapcpp2_yacc.tab.c"
    break;

  case 185: /* s5: ','  */
#line 1782 "soapcpp2_yacc.y"
                        { }
#line 4322 "soapcpp2_yacc.tab.c"
    break;

  case 186: /* s6: %empty  */
#line 1784 "soapcpp2_yacc.y"
                        {
                          if (sp->table->level == INTERNAL)
                            transient |= 1;
                          permission = 0;
                          enterscope(mktable(NULL), 0);
                          sp->entry = NULL;
                          sp->table->level = PARAM;
                        }
#line 4335 "soapcpp2_yacc.tab.c"
    break;

  case 187: /* store: AUTO  */
#line 1793 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sauto; }
#line 4341 "soapcpp2_yacc.tab.c"
    break;

  case 188: /* store: REGISTER  */
#line 1794 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sregister; }
#line 4347 "soapcpp2_yacc.tab.c"
    break;

  case 189: /* store: STATIC  */
#line 1795 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sstatic; }
#line 4353 "soapcpp2_yacc.tab.c"
    break;

  case 190: /* store: EXPLICIT  */
#line 1796 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sexplicit; }
#line 4359 "soapcpp2_yacc.tab.c"
    break;

  case 191: /* store: EXTERN  */
#line 1797 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sextern; transient = 1; }
#line 4365 "soapcpp2_yacc.tab.c"
    break;

  case 192: /* store: TYPEDEF  */
#line 1798 "soapcpp2_yacc.y"
                        { (yyval.sto) = Stypedef; }
#line 4371 "soapcpp2_yacc.tab.c"
    break;

  case 193: /* store: VIRTUAL  */
#line 1799 "soapcpp2_yacc.y"
                        { (yyval.sto) = Svirtual; }
#line 4377 "soapcpp2_yacc.tab.c"
    break;

  case 194: /* store: CONST  */
#line 1800 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sconst; }
#line 4383 "soapcpp2_yacc.tab.c"
    break;

  case 195: /* store: FINAL  */
#line 1801 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sfinal; }
#line 4389 "soapcpp2_yacc.tab.c"
    break;

  case 196: /* store: OVERRIDE  */
#line 1802 "soapcpp2_yacc.y"
                        { (yyval.sto) = Soverride; }
#line 4395 "soapcpp2_yacc.tab.c"
    break;

  case 197: /* store: FRIEND  */
#line 1803 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sfriend; }
#line 4401 "soapcpp2_yacc.tab.c"
    break;

  case 198: /* store: INLINE  */
#line 1804 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sinline; }
#line 4407 "soapcpp2_yacc.tab.c"
    break;

  case 199: /* store: MUSTUNDERSTAND  */
#line 1806 "soapcpp2_yacc.y"
                        { (yyval.sto) = SmustUnderstand; }
#line 4413 "soapcpp2_yacc.tab.c"
    break;

  case 200: /* store: RETURN  */
#line 1807 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sreturn; }
#line 4419 "soapcpp2_yacc.tab.c"
    break;

  case 201: /* store: '@'  */
#line 1808 "soapcpp2_yacc.y"
                        {
                          (yyval.sto) = Sattribute;
                          if (eflag)
                            semwarn("SOAP RPC encoding does not support XML attributes");
                        }
#line 4429 "soapcpp2_yacc.tab.c"
    break;

  case 202: /* store: '$'  */
#line 1813 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sspecial; }
#line 4435 "soapcpp2_yacc.tab.c"
    break;

  case 203: /* store: VOLATILE  */
#line 1814 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sextern; transient = -2; }
#line 4441 "soapcpp2_yacc.tab.c"
    break;

  case 204: /* store: MUTABLE  */
#line 1815 "soapcpp2_yacc.y"
                        { (yyval.sto) = Smutable; transient = -4; }
#line 4447 "soapcpp2_yacc.tab.c"
    break;

  case 205: /* const: %empty  */
#line 1817 "soapcpp2_yacc.y"
                        { (yyval.sto) = Snone; }
#line 4453 "soapcpp2_yacc.tab.c"
    break;

  case 206: /* const: const CONST  */
#line 1818 "soapcpp2_yacc.y"
                        { (yyval.sto) = (Storage)((int)(yyvsp[-1].sto) | (int)Sconstobj); }
#line 4459 "soapcpp2_yacc.tab.c"
    break;

  case 207: /* const: const FINAL  */
#line 1819 "soapcpp2_yacc.y"
                        { (yyval.sto) = (Storage)((int)(yyvsp[-1].sto) | (int)Sfinal); }
#line 4465 "soapcpp2_yacc.tab.c"
    break;

  case 208: /* const: const OVERRIDE  */
#line 1821 "soapcpp2_yacc.y"
                        { (yyval.sto) = (Storage)((int)(yyvsp[-1].sto) | (int)Soverride); }
#line 4471 "soapcpp2_yacc.tab.c"
    break;

  case 209: /* abstract: %empty  */
#line 1823 "soapcpp2_yacc.y"
                        { (yyval.sto) = Snone; }
#line 4477 "soapcpp2_yacc.tab.c"
    break;

  case 210: /* abstract: '=' LNG  */
#line 1824 "soapcpp2_yacc.y"
                        { (yyval.sto) = Sabstract; }
#line 4483 "soapcpp2_yacc.tab.c"
    break;

  case 211: /* virtual: %empty  */
#line 1826 "soapcpp2_yacc.y"
                        { (yyval.sto) = Snone; }
#line 4489 "soapcpp2_yacc.tab.c"
    break;

  case 212: /* virtual: VIRTUAL  */
#line 1827 "soapcpp2_yacc.y"
                        { (yyval.sto) = Svirtual; }
#line 4495 "soapcpp2_yacc.tab.c"
    break;

  case 213: /* ptrs: %empty  */
#line 1829 "soapcpp2_yacc.y"
                        { (yyval.rec) = tmp = sp->node; }
#line 4501 "soapcpp2_yacc.tab.c"
    break;

  case 214: /* ptrs: ptrs '*'  */
#line 1830 "soapcpp2_yacc.y"
                        {
                          /* handle const pointers, such as const char* */
                          if (((int)tmp.sto & (int)Sconst))
                            tmp.sto = (Storage)(((int)tmp.sto & ~(int)Sconst) | (int)Sconstptr);
                          tmp.typ = mkpointer(tmp.typ);
                          tmp.typ->transient = transient;
                          (yyval.rec) = tmp;
                        }
#line 4514 "soapcpp2_yacc.tab.c"
    break;

  case 215: /* ptrs: ptrs '&'  */
#line 1838 "soapcpp2_yacc.y"
                        {
                          tmp.typ = mkreference(tmp.typ);
                          tmp.typ->transient = transient;
                          (yyval.rec) = tmp;
                        }
#line 4524 "soapcpp2_yacc.tab.c"
    break;

  case 216: /* ptrs: ptrs AN  */
#line 1843 "soapcpp2_yacc.y"
                        {
                          tmp.typ = mkrvalueref(tmp.typ);
                          tmp.typ->transient = transient;
                          (yyval.rec) = tmp;
                        }
#line 4534 "soapcpp2_yacc.tab.c"
    break;

  case 217: /* array: %empty  */
#line 1849 "soapcpp2_yacc.y"
                        { (yyval.rec) = tmp; }
#line 4540 "soapcpp2_yacc.tab.c"
    break;

  case 218: /* array: '[' cexp ']' array  */
#line 1851 "soapcpp2_yacc.y"
                        {
                          if (!bflag && (yyvsp[0].rec).typ->type == Tchar)
                          {
                            sprintf(errbuf, "char[" SOAP_LONG_FORMAT "] will be serialized as an array of " SOAP_LONG_FORMAT " bytes: use soapcpp2 option -b to enable char[] string serialization or use char* for strings", (yyvsp[-2].rec).val.i, (yyvsp[-2].rec).val.i);
                            semwarn(errbuf);
                          }
                          if ((yyvsp[-2].rec).hasval && (yyvsp[-2].rec).typ->type == Tint && (yyvsp[-2].rec).val.i > 0 && (yyvsp[0].rec).typ->width > 0)
                          {
                            (yyval.rec).typ = mkarray((yyvsp[0].rec).typ, (int) (yyvsp[-2].rec).val.i * (yyvsp[0].rec).typ->width);
                          }
                          else
                          {
                            (yyval.rec).typ = mkarray((yyvsp[0].rec).typ, 0);
                            semerror("undetermined array size");
                          }
                          (yyval.rec).sto = (yyvsp[0].rec).sto;
                        }
#line 4562 "soapcpp2_yacc.tab.c"
    break;

  case 219: /* array: '[' ']' array  */
#line 1868 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkpointer((yyvsp[0].rec).typ); /* zero size array = pointer */
                          (yyval.rec).sto = (yyvsp[0].rec).sto;
                        }
#line 4571 "soapcpp2_yacc.tab.c"
    break;

  case 220: /* arrayck: array  */
#line 1873 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[0].rec).typ->type == Tstruct || (yyvsp[0].rec).typ->type == Tclass)
                          {
                            if (!(yyvsp[0].rec).typ->ref && !(yyvsp[0].rec).typ->transient && !((int)(yyvsp[0].rec).sto & (int)Stypedef))
                            {
                              if ((yyvsp[0].rec).typ->type == Tstruct)
                                sprintf(errbuf, "struct '%s' has incomplete type (if this struct is not serializable then declare 'extern struct %s')", (yyvsp[0].rec).typ->id->name, (yyvsp[0].rec).typ->id->name);
                              else
                                sprintf(errbuf, "class '%s' has incomplete type (if this class is not serializable then declare 'extern class %s')", (yyvsp[0].rec).typ->id->name, (yyvsp[0].rec).typ->id->name);
                              semerror(errbuf);
                            }
                          }
                          (yyval.rec) = (yyvsp[0].rec);
                        }
#line 4590 "soapcpp2_yacc.tab.c"
    break;

  case 221: /* brinit: init  */
#line 1888 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 4596 "soapcpp2_yacc.tab.c"
    break;

  case 222: /* brinit: '{' cexp '}'  */
#line 1889 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[-1].rec).hasval)
                          {
                            (yyval.rec).typ = (yyvsp[-1].rec).typ;
                            (yyval.rec).hasval = True;
                            (yyval.rec).fixed = False;
                            (yyval.rec).val = (yyvsp[-1].rec).val;
                          }
                          else
                          {
                            (yyval.rec).hasval = False;
                            semerror("initialization expression not constant");
                          }
                        }
#line 4615 "soapcpp2_yacc.tab.c"
    break;

  case 223: /* init: %empty  */
#line 1904 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).hasval = False;
                          (yyval.rec).fixed = False;
                        }
#line 4624 "soapcpp2_yacc.tab.c"
    break;

  case 224: /* init: '=' cexp  */
#line 1908 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[0].rec).hasval)
                          {
                            (yyval.rec).typ = (yyvsp[0].rec).typ;
                            (yyval.rec).hasval = True;
                            (yyval.rec).fixed = False;
                            (yyval.rec).val = (yyvsp[0].rec).val;
                          }
                          else
                          {
                            (yyval.rec).hasval = False;
                            semerror("initialization expression not constant");
                          }
                        }
#line 4643 "soapcpp2_yacc.tab.c"
    break;

  case 225: /* init: EQ cexp  */
#line 1922 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[0].rec).hasval)
                          {
                            (yyval.rec).typ = (yyvsp[0].rec).typ;
                            (yyval.rec).hasval = True;
                            (yyval.rec).fixed = True;
                            (yyval.rec).val = (yyvsp[0].rec).val;
                          }
                          else
                          {
                            (yyval.rec).hasval = False;
                            semerror("initialization expression not constant");
                          }
                        }
#line 4662 "soapcpp2_yacc.tab.c"
    break;

  case 226: /* tag: %empty  */
#line 1937 "soapcpp2_yacc.y"
                        { (yyval.s) = NULL; }
#line 4668 "soapcpp2_yacc.tab.c"
    break;

  case 227: /* tag: TAG  */
#line 1938 "soapcpp2_yacc.y"
                        { (yyval.s) = (yyvsp[0].s); }
#line 4674 "soapcpp2_yacc.tab.c"
    break;

  case 228: /* occurs: nullptr  */
#line 1940 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).minOccurs = -1;
                          (yyval.rec).maxOccurs = 1;
                          (yyval.rec).hasmin = False;
                          (yyval.rec).hasmax = False;
                          (yyval.rec).imin = 0;
                          (yyval.rec).imax = 0;
                          (yyval.rec).rmin = 0.0;
                          (yyval.rec).rmax = 0.0;
                          (yyval.rec).incmin = True;
                          (yyval.rec).incmax = True;
                          (yyval.rec).nillable = (yyvsp[0].i);
                          (yyval.rec).pattern = NULL;
                        }
#line 4693 "soapcpp2_yacc.tab.c"
    break;

  case 229: /* occurs: nullptr LNG  */
#line 1954 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).minOccurs = (yyvsp[0].i);
                          (yyval.rec).maxOccurs = 1;
                          if ((yyval.rec).minOccurs < 0)
                            (yyval.rec).minOccurs = -1;
                          (yyval.rec).hasmin = False;
                          (yyval.rec).hasmax = False;
                          (yyval.rec).imin = 0;
                          (yyval.rec).imax = 0;
                          (yyval.rec).rmin = 0.0;
                          (yyval.rec).rmax = 0.0;
                          (yyval.rec).incmin = True;
                          (yyval.rec).incmax = True;
                          (yyval.rec).nillable = (yyvsp[-1].i);
                          (yyval.rec).pattern = NULL;
                        }
#line 4714 "soapcpp2_yacc.tab.c"
    break;

  case 230: /* occurs: nullptr LNG ':'  */
#line 1971 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).minOccurs = (yyvsp[-1].i);
                          (yyval.rec).maxOccurs = 1;
                          if ((yyval.rec).minOccurs < 0)
                            (yyval.rec).minOccurs = -1;
                          (yyval.rec).hasmin = False;
                          (yyval.rec).hasmax = False;
                          (yyval.rec).imin = 0;
                          (yyval.rec).imax = 0;
                          (yyval.rec).rmin = 0.0;
                          (yyval.rec).rmax = 0.0;
                          (yyval.rec).incmin = True;
                          (yyval.rec).incmax = True;
                          (yyval.rec).nillable = (yyvsp[-2].i);
                          (yyval.rec).pattern = NULL;
                        }
#line 4735 "soapcpp2_yacc.tab.c"
    break;

  case 231: /* occurs: nullptr LNG ':' LNG  */
#line 1988 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).minOccurs = (yyvsp[-2].i);
                          (yyval.rec).maxOccurs = (yyvsp[0].i);
                          if ((yyval.rec).minOccurs < 0 || (yyval.rec).maxOccurs < 0)
                          {
                            (yyval.rec).minOccurs = -1;
                            (yyval.rec).maxOccurs = 1;
                          }
                          else if ((yyval.rec).minOccurs > (yyval.rec).maxOccurs)
                          {
                            (yyval.rec).minOccurs = -1;
                            (yyval.rec).maxOccurs = 1;
                          }
                          (yyval.rec).hasmin = False;
                          (yyval.rec).hasmax = False;
                          (yyval.rec).imin = 0;
                          (yyval.rec).imax = 0;
                          (yyval.rec).rmin = 0.0;
                          (yyval.rec).rmax = 0.0;
                          (yyval.rec).incmin = True;
                          (yyval.rec).incmax = True;
                          (yyval.rec).nillable = (yyvsp[-3].i);
                          (yyval.rec).pattern = NULL;
                        }
#line 4764 "soapcpp2_yacc.tab.c"
    break;

  case 232: /* occurs: nullptr ':' LNG  */
#line 2013 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).minOccurs = -1;
                          (yyval.rec).maxOccurs = (yyvsp[0].i);
                          if ((yyval.rec).maxOccurs < 0)
                          {
                            (yyval.rec).minOccurs = -1;
                            (yyval.rec).maxOccurs = 1;
                          }
                          (yyval.rec).hasmin = False;
                          (yyval.rec).hasmax = False;
                          (yyval.rec).imin = 0;
                          (yyval.rec).imax = 0;
                          (yyval.rec).rmin = 0.0;
                          (yyval.rec).rmax = 0.0;
                          (yyval.rec).incmin = True;
                          (yyval.rec).incmax = True;
                          (yyval.rec).nillable = (yyvsp[-2].i);
                          (yyval.rec).pattern = NULL;
                        }
#line 4788 "soapcpp2_yacc.tab.c"
    break;

  case 233: /* bounds: nullptr patt  */
#line 2034 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).hasmin = False;
                          (yyval.rec).hasmax = False;
                          (yyval.rec).minOccurs = -1;
                          (yyval.rec).maxOccurs = 1;
                          (yyval.rec).imin = 0;
                          (yyval.rec).imax = 0;
                          (yyval.rec).rmin = 0.0;
                          (yyval.rec).rmax = 0.0;
                          (yyval.rec).incmin = True;
                          (yyval.rec).incmax = True;
                          (yyval.rec).nillable = (yyvsp[-1].i);
                          (yyval.rec).pattern = (yyvsp[0].s);
                        }
#line 4807 "soapcpp2_yacc.tab.c"
    break;

  case 234: /* bounds: nullptr patt value min  */
#line 2049 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).hasmin = True;
                          (yyval.rec).hasmax = False;
                          (yyval.rec).incmin = (yyvsp[0].rec).incmin;
                          (yyval.rec).incmax = (yyvsp[0].rec).incmax;
                          (yyval.rec).minOccurs = (yyvsp[-1].ir).i;
                          (yyval.rec).maxOccurs = 1;
                          if ((yyval.rec).minOccurs < 0)
                            (yyval.rec).minOccurs = -1;
                          (yyval.rec).imin = (yyvsp[-1].ir).i;
                          (yyval.rec).imax = 0;
                          (yyval.rec).rmin = (yyvsp[-1].ir).r;
                          (yyval.rec).rmax = 0.0;
                          (yyval.rec).nillable = (yyvsp[-3].i);
                          (yyval.rec).pattern = (yyvsp[-2].s);
                        }
#line 4828 "soapcpp2_yacc.tab.c"
    break;

  case 235: /* bounds: nullptr patt value minmax value  */
#line 2066 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).hasmin = True;
                          (yyval.rec).hasmax = True;
                          (yyval.rec).incmin = (yyvsp[-1].rec).incmin;
                          (yyval.rec).incmax = (yyvsp[-1].rec).incmax;
                          (yyval.rec).minOccurs = (yyvsp[-2].ir).i;
                          (yyval.rec).maxOccurs = (yyvsp[0].ir).i;
                          if ((yyval.rec).minOccurs < 0 || (yyval.rec).maxOccurs < 0)
                          {
                            (yyval.rec).minOccurs = -1;
                            (yyval.rec).maxOccurs = 1;
                          }
                          else if ((yyval.rec).minOccurs > (yyval.rec).maxOccurs)
                          {
                            (yyval.rec).minOccurs = -1;
                            (yyval.rec).maxOccurs = 1;
                          }
                          (yyval.rec).imin = (yyvsp[-2].ir).i;
                          (yyval.rec).imax = (yyvsp[0].ir).i;
                          (yyval.rec).rmin = (yyvsp[-2].ir).r;
                          (yyval.rec).rmax = (yyvsp[0].ir).r;
                          (yyval.rec).nillable = (yyvsp[-4].i);
                          (yyval.rec).pattern = (yyvsp[-3].s);
                        }
#line 4857 "soapcpp2_yacc.tab.c"
    break;

  case 236: /* bounds: nullptr patt max value  */
#line 2090 "soapcpp2_yacc.y"
                                 {
                          (yyval.rec).hasmin = False;
                          (yyval.rec).hasmax = True;
                          (yyval.rec).incmin = (yyvsp[-1].rec).incmin;
                          (yyval.rec).incmax = (yyvsp[-1].rec).incmax;
                          (yyval.rec).minOccurs = -1;
                          (yyval.rec).maxOccurs = (yyvsp[0].ir).i;
                          if ((yyval.rec).maxOccurs < 0)
                          {
                            (yyval.rec).minOccurs = -1;
                            (yyval.rec).maxOccurs = 1;
                          }
                          (yyval.rec).imin = 0;
                          (yyval.rec).imax = (yyvsp[0].ir).i;
                          (yyval.rec).rmin = 0.0;
                          (yyval.rec).rmax = (yyvsp[0].ir).r;
                          (yyval.rec).nillable = (yyvsp[-3].i);
                          (yyval.rec).pattern = (yyvsp[-2].s);
                        }
#line 4881 "soapcpp2_yacc.tab.c"
    break;

  case 237: /* nullptr: %empty  */
#line 2110 "soapcpp2_yacc.y"
                        { (yyval.i) = zflag >= 1 && zflag <= 3; /* False, unless version 2.8.30 or earlier */ }
#line 4887 "soapcpp2_yacc.tab.c"
    break;

  case 238: /* nullptr: null  */
#line 2111 "soapcpp2_yacc.y"
                        { (yyval.i) = True; }
#line 4893 "soapcpp2_yacc.tab.c"
    break;

  case 239: /* patt: %empty  */
#line 2113 "soapcpp2_yacc.y"
                        { (yyval.s) = NULL; }
#line 4899 "soapcpp2_yacc.tab.c"
    break;

  case 240: /* patt: STR  */
#line 2114 "soapcpp2_yacc.y"
                        { (yyval.s) = (yyvsp[0].s); }
#line 4905 "soapcpp2_yacc.tab.c"
    break;

  case 241: /* value: DBL  */
#line 2116 "soapcpp2_yacc.y"
                        { (yyval.ir).i = (LONG64)((yyval.ir).r = (yyvsp[0].r)); }
#line 4911 "soapcpp2_yacc.tab.c"
    break;

  case 242: /* value: LNG  */
#line 2117 "soapcpp2_yacc.y"
                        { (yyval.ir).r = (double)((yyval.ir).i = (yyvsp[0].i)); }
#line 4917 "soapcpp2_yacc.tab.c"
    break;

  case 243: /* value: CHR  */
#line 2118 "soapcpp2_yacc.y"
                        { (yyval.ir).r = (double)((yyval.ir).i = (yyvsp[0].c)); }
#line 4923 "soapcpp2_yacc.tab.c"
    break;

  case 244: /* value: '+' value  */
#line 2119 "soapcpp2_yacc.y"
                        { (yyval.ir).i = +(yyvsp[0].ir).i; (yyval.ir).r = +(yyvsp[0].ir).r; }
#line 4929 "soapcpp2_yacc.tab.c"
    break;

  case 245: /* value: '-' value  */
#line 2120 "soapcpp2_yacc.y"
                        { (yyval.ir).i = -(yyvsp[0].ir).i; (yyval.ir).r = -(yyvsp[0].ir).r; }
#line 4935 "soapcpp2_yacc.tab.c"
    break;

  case 246: /* min: %empty  */
#line 2122 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = (yyval.rec).incmax = True; }
#line 4941 "soapcpp2_yacc.tab.c"
    break;

  case 247: /* min: ':'  */
#line 2123 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = (yyval.rec).incmax = True; }
#line 4947 "soapcpp2_yacc.tab.c"
    break;

  case 248: /* min: '<' ':'  */
#line 2124 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = False; (yyval.rec).incmax = True; }
#line 4953 "soapcpp2_yacc.tab.c"
    break;

  case 249: /* min: '<'  */
#line 2125 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = False; (yyval.rec).incmax = True; }
#line 4959 "soapcpp2_yacc.tab.c"
    break;

  case 250: /* minmax: ':'  */
#line 2127 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = (yyval.rec).incmax = True; }
#line 4965 "soapcpp2_yacc.tab.c"
    break;

  case 251: /* minmax: '<' ':'  */
#line 2128 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = False; (yyval.rec).incmax = True; }
#line 4971 "soapcpp2_yacc.tab.c"
    break;

  case 252: /* minmax: ':' '<'  */
#line 2129 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = True; (yyval.rec).incmax = False; }
#line 4977 "soapcpp2_yacc.tab.c"
    break;

  case 253: /* minmax: '<' ':' '<'  */
#line 2130 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = False; (yyval.rec).incmax = False; }
#line 4983 "soapcpp2_yacc.tab.c"
    break;

  case 254: /* minmax: '<'  */
#line 2131 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = False; (yyval.rec).incmax = False; }
#line 4989 "soapcpp2_yacc.tab.c"
    break;

  case 255: /* max: ':'  */
#line 2133 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = (yyval.rec).incmax = True; }
#line 4995 "soapcpp2_yacc.tab.c"
    break;

  case 256: /* max: ':' '<'  */
#line 2134 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = True; (yyval.rec).incmax = False; }
#line 5001 "soapcpp2_yacc.tab.c"
    break;

  case 257: /* max: '<'  */
#line 2135 "soapcpp2_yacc.y"
                        { (yyval.rec).incmin = True; (yyval.rec).incmax = False; }
#line 5007 "soapcpp2_yacc.tab.c"
    break;

  case 258: /* expr: expr ',' expr  */
#line 2144 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5013 "soapcpp2_yacc.tab.c"
    break;

  case 259: /* expr: cexp  */
#line 2145 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5019 "soapcpp2_yacc.tab.c"
    break;

  case 260: /* cexp: obex '?' qexp ':' cexp  */
#line 2149 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = (yyvsp[-2].rec).typ;
                          (yyval.rec).sto = Snone;
                          (yyval.rec).hasval = False;
                        }
#line 5029 "soapcpp2_yacc.tab.c"
    break;

  case 262: /* qexp: expr  */
#line 2157 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5035 "soapcpp2_yacc.tab.c"
    break;

  case 263: /* oexp: obex OR aexp  */
#line 2160 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).hasval = False;
                          (yyval.rec).typ = mkint();
                        }
#line 5044 "soapcpp2_yacc.tab.c"
    break;

  case 264: /* oexp: aexp  */
#line 2164 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5050 "soapcpp2_yacc.tab.c"
    break;

  case 265: /* obex: oexp  */
#line 2166 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5056 "soapcpp2_yacc.tab.c"
    break;

  case 266: /* aexp: abex AN rexp  */
#line 2169 "soapcpp2_yacc.y"
                        { (yyval.rec).hasval = False;
                          (yyval.rec).typ = mkint();
                        }
#line 5064 "soapcpp2_yacc.tab.c"
    break;

  case 267: /* aexp: rexp  */
#line 2172 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5070 "soapcpp2_yacc.tab.c"
    break;

  case 268: /* abex: aexp  */
#line 2174 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5076 "soapcpp2_yacc.tab.c"
    break;

  case 269: /* rexp: rexp '|' rexp  */
#line 2177 "soapcpp2_yacc.y"
                        { (yyval.rec) = iop("|", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5082 "soapcpp2_yacc.tab.c"
    break;

  case 270: /* rexp: rexp '^' rexp  */
#line 2178 "soapcpp2_yacc.y"
                        { (yyval.rec) = iop("^", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5088 "soapcpp2_yacc.tab.c"
    break;

  case 271: /* rexp: rexp '&' rexp  */
#line 2179 "soapcpp2_yacc.y"
                        { (yyval.rec) = iop("&", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5094 "soapcpp2_yacc.tab.c"
    break;

  case 272: /* rexp: rexp EQ rexp  */
#line 2180 "soapcpp2_yacc.y"
                        { (yyval.rec) = relop("==", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5100 "soapcpp2_yacc.tab.c"
    break;

  case 273: /* rexp: rexp NE rexp  */
#line 2181 "soapcpp2_yacc.y"
                        { (yyval.rec) = relop("!=", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5106 "soapcpp2_yacc.tab.c"
    break;

  case 274: /* rexp: rexp '<' rexp  */
#line 2182 "soapcpp2_yacc.y"
                        { (yyval.rec) = relop("<", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5112 "soapcpp2_yacc.tab.c"
    break;

  case 275: /* rexp: rexp LE rexp  */
#line 2183 "soapcpp2_yacc.y"
                        { (yyval.rec) = relop("<=", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5118 "soapcpp2_yacc.tab.c"
    break;

  case 276: /* rexp: rexp '>' rexp  */
#line 2184 "soapcpp2_yacc.y"
                        { (yyval.rec) = relop(">", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5124 "soapcpp2_yacc.tab.c"
    break;

  case 277: /* rexp: rexp GE rexp  */
#line 2185 "soapcpp2_yacc.y"
                        { (yyval.rec) = relop(">=", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5130 "soapcpp2_yacc.tab.c"
    break;

  case 278: /* rexp: rexp LS rexp  */
#line 2186 "soapcpp2_yacc.y"
                        { (yyval.rec) = iop("<<", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5136 "soapcpp2_yacc.tab.c"
    break;

  case 279: /* rexp: rexp RS rexp  */
#line 2187 "soapcpp2_yacc.y"
                        { (yyval.rec) = iop(">>", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5142 "soapcpp2_yacc.tab.c"
    break;

  case 280: /* rexp: rexp '+' rexp  */
#line 2188 "soapcpp2_yacc.y"
                        { (yyval.rec) = op("+", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5148 "soapcpp2_yacc.tab.c"
    break;

  case 281: /* rexp: rexp '-' rexp  */
#line 2189 "soapcpp2_yacc.y"
                        { (yyval.rec) = op("-", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5154 "soapcpp2_yacc.tab.c"
    break;

  case 282: /* rexp: rexp '*' rexp  */
#line 2190 "soapcpp2_yacc.y"
                        { (yyval.rec) = op("*", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5160 "soapcpp2_yacc.tab.c"
    break;

  case 283: /* rexp: rexp '/' rexp  */
#line 2191 "soapcpp2_yacc.y"
                        { (yyval.rec) = op("/", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5166 "soapcpp2_yacc.tab.c"
    break;

  case 284: /* rexp: rexp '%' rexp  */
#line 2192 "soapcpp2_yacc.y"
                        { (yyval.rec) = iop("%", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5172 "soapcpp2_yacc.tab.c"
    break;

  case 285: /* rexp: lexp  */
#line 2193 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5178 "soapcpp2_yacc.tab.c"
    break;

  case 286: /* lexp: '!' lexp  */
#line 2196 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[0].rec).hasval)
                            (yyval.rec).val.i = !(yyvsp[0].rec).val.i;
                          (yyval.rec).typ = (yyvsp[0].rec).typ;
                          (yyval.rec).hasval = (yyvsp[0].rec).hasval;
                        }
#line 5189 "soapcpp2_yacc.tab.c"
    break;

  case 287: /* lexp: '~' lexp  */
#line 2202 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[0].rec).hasval)
                            (yyval.rec).val.i = ~(yyvsp[0].rec).val.i;
                          (yyval.rec).typ = (yyvsp[0].rec).typ;
                          (yyval.rec).hasval = (yyvsp[0].rec).hasval;
                        }
#line 5200 "soapcpp2_yacc.tab.c"
    break;

  case 288: /* lexp: '-' lexp  */
#line 2208 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[0].rec).hasval)
                          {
                            if (integer((yyvsp[0].rec).typ))
                              (yyval.rec).val.i = -(yyvsp[0].rec).val.i;
                            else if (real((yyvsp[0].rec).typ))
                              (yyval.rec).val.r = -(yyvsp[0].rec).val.r;
                            else
                              typerror("string?");
                          }
                          (yyval.rec).typ = (yyvsp[0].rec).typ;
                          (yyval.rec).hasval = (yyvsp[0].rec).hasval;
                        }
#line 5218 "soapcpp2_yacc.tab.c"
    break;

  case 289: /* lexp: '+' lexp  */
#line 2221 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5224 "soapcpp2_yacc.tab.c"
    break;

  case 290: /* lexp: '*' lexp  */
#line 2222 "soapcpp2_yacc.y"
                        {
                          if ((yyvsp[0].rec).typ->type == Tpointer)
                            (yyval.rec).typ = (Tnode*)(yyvsp[0].rec).typ->ref;
                          else
                          {
                            typerror("dereference of non-pointer type");
                            (yyval.rec).typ = (yyvsp[0].rec).typ;
                          }
                          (yyval.rec).sto = Snone;
                          (yyval.rec).hasval = False;
                        }
#line 5240 "soapcpp2_yacc.tab.c"
    break;

  case 291: /* lexp: '&' lexp  */
#line 2233 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkpointer((yyvsp[0].rec).typ);
                          (yyval.rec).sto = Snone;
                          (yyval.rec).hasval = False;
                        }
#line 5250 "soapcpp2_yacc.tab.c"
    break;

  case 292: /* lexp: SIZEOF '(' texp ')'  */
#line 2239 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).typ = mkint();
                          (yyval.rec).val.i = (yyvsp[-1].rec).typ->width;
                        }
#line 5261 "soapcpp2_yacc.tab.c"
    break;

  case 293: /* lexp: pexp  */
#line 2245 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[0].rec); }
#line 5267 "soapcpp2_yacc.tab.c"
    break;

  case 294: /* pexp: '(' expr ')'  */
#line 2248 "soapcpp2_yacc.y"
                        { (yyval.rec) = (yyvsp[-1].rec); }
#line 5273 "soapcpp2_yacc.tab.c"
    break;

  case 295: /* pexp: ID  */
#line 2249 "soapcpp2_yacc.y"
                        {
                          if (!(p = enumentry((yyvsp[0].sym))))
                            p = undefined((yyvsp[0].sym));
                          else
                            (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).typ = p->info.typ;
                          (yyval.rec).val = p->info.val;
                        }
#line 5287 "soapcpp2_yacc.tab.c"
    break;

  case 296: /* pexp: LNG  */
#line 2258 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkint();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.i = (yyvsp[0].i);
                        }
#line 5298 "soapcpp2_yacc.tab.c"
    break;

  case 297: /* pexp: DBL  */
#line 2264 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkfloat();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.r = (yyvsp[0].r);
                        }
#line 5309 "soapcpp2_yacc.tab.c"
    break;

  case 298: /* pexp: CHR  */
#line 2270 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkchar();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.i = (yyvsp[0].c);
                        }
#line 5320 "soapcpp2_yacc.tab.c"
    break;

  case 299: /* pexp: STR  */
#line 2276 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkstring();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.s = (yyvsp[0].s);
                        }
#line 5331 "soapcpp2_yacc.tab.c"
    break;

  case 300: /* pexp: CFALSE  */
#line 2282 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkbool();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.i = 0;
                        }
#line 5342 "soapcpp2_yacc.tab.c"
    break;

  case 301: /* pexp: CTRUE  */
#line 2288 "soapcpp2_yacc.y"
                        {
                          (yyval.rec).typ = mkbool();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.i = 1;
                        }
#line 5353 "soapcpp2_yacc.tab.c"
    break;


#line 5357 "soapcpp2_yacc.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2296 "soapcpp2_yacc.y"


int
yywrap(void)
{
  return 1;
}

/**************************************\

        Support routines

\**************************************/

static Node
op(const char *op, Node p, Node q)
{
  Node  r;
  r.typ = p.typ;
  r.sto = Snone;
  if (p.hasval && q.hasval)
  {
    if (integer(p.typ) && integer(q.typ))
      switch (op[0])
      {
        case '|': r.val.i = p.val.i |  q.val.i; break;
        case '^': r.val.i = p.val.i ^  q.val.i; break;
        case '&': r.val.i = p.val.i &  q.val.i; break;
        case '<': r.val.i = p.val.i << q.val.i; break;
        case '>': r.val.i = p.val.i >> q.val.i; break;
        case '+': r.val.i = p.val.i +  q.val.i; break;
        case '-': r.val.i = p.val.i -  q.val.i; break;
        case '*': r.val.i = p.val.i *  q.val.i; break;
        case '/': r.val.i = q.val.i != 0 ? p.val.i / q.val.i : 0; break;
        case '%': r.val.i = q.val.i != 0 ? p.val.i % q.val.i : 0; break;
        default:  typerror(op);
      }
    else if (real(p.typ) && real(q.typ))
      switch (op[0])
      {
        case '+': r.val.r = p.val.r + q.val.r; break;
        case '-': r.val.r = p.val.r - q.val.r; break;
        case '*': r.val.r = p.val.r * q.val.r; break;
        case '/': r.val.r = q.val.r != 0 ? p.val.r / q.val.r : 0.0; break;
        default:  typerror(op);
      }
    else
      semerror("invalid constant operation");
    r.hasval = True;
    r.fixed = False;
  }
  else
  {
    r.typ = mgtype(p.typ, q.typ);
    r.hasval = False;
  }
  return r;
}

static Node
iop(const char *iop, Node p, Node q)
{
  if (integer(p.typ) && integer(q.typ))
    return op(iop, p, q);
  typerror("integer operands only");
  return p;
}

static Node
relop(const char *op, Node p, Node q)
{
  Node  r;
  r.typ = mkint();
  r.sto = Snone;
  r.hasval = True;
  r.fixed = False;
  r.val.i = 1;
  sprintf(errbuf, "comparison '%s' not evaluated and considered true", op);
  semwarn(errbuf);
  if (p.typ->type != Tpointer || p.typ != q.typ)
    r.typ = mgtype(p.typ, q.typ);
  return r;
}

/**************************************\

        Scope management

\**************************************/

/*
mkscope - initialize scope stack with a new table and offset
*/
static void
mkscope(Table *table, int offset)
{
  sp = stack-1;
  enterscope(table, offset);
}

/*
enterscope - enter a new scope by pushing a new table and offset on the stack
*/
static void
enterscope(Table *table, int offset)
{
  if (++sp == stack + MAXNEST)
    execerror("maximum scope nesting depth exceeded");
  sp->table = table;
  sp->entry = NULL;
  sp->node.typ = mkint();
  sp->node.sto = Snone;
  sp->val = 0;
  sp->offset = offset;
  sp->grow = True;      /* by default, offset grows */
  sp->mask = False;
}

/*
exitscope - exit a scope by popping the table and offset from the stack
*/
static void
exitscope(void)
{
  check(sp-- != stack, "exitscope() has no matching enterscope()");
}

/**************************************\

        Undefined symbol

\**************************************/

static Entry*
undefined(Symbol *sym)
{
  Entry *p;
  sprintf(errbuf, "undefined identifier '%s'", sym->name);
  semwarn(errbuf);
  p = enter(sp->table, sym);
  p->level = GLOBAL;
  p->info.typ = mkint();
  p->info.sto = Sextern;
  p->info.hasval = False;
  return p;
}

/*
mgtype - return most general type among two numerical types
*/
Tnode*
mgtype(Tnode *typ1, Tnode *typ2)
{
  if (numeric(typ1) && numeric(typ2))
  {
    if (typ1->type < typ2->type)
      return typ2;
  }
  else
  {
    typerror("non-numeric type");
  }
  return typ1;
}

/**************************************\

        Type checks

\**************************************/

static int
integer(Tnode *typ)
{
  switch (typ->type)
  {
    case Tchar:
    case Tshort:
    case Tint:
    case Tlong: return True;
    default:    break;
  }
  return False;
}

static int
real(Tnode *typ)
{
  switch (typ->type)
  {
    case Tfloat:
    case Tdouble:
    case Tldouble: return True;
    default:       break;
  }
  return False;
}

static int
numeric(Tnode *typ)
{
  return integer(typ) || real(typ);
}

static void
set_value(Entry *p, Tnode *t, Node *n)
{
  p->info.hasval = True;
  p->info.ptrval = False;
  p->info.fixed = n->fixed;
  if (is_smart(t) || (t->type == Tpointer && !is_string(t) && !is_wstring(t)))
  {
    p->info.hasval = False;
    p->info.ptrval = True;
    t = t->ref;
  }
  switch (t->type)
  {
    case Tchar:
    case Tuchar:
    case Tshort:
    case Tushort:
    case Tint:
    case Tuint:
    case Tlong:
    case Tulong:
    case Tllong:
    case Tullong:
    case Tenum:
    case Tenumsc:
    case Ttime:
    case Tsize:
      if (n->typ->type == Tint ||
          n->typ->type == Tchar ||
          n->typ->type == Tenum ||
          n->typ->type == Tenumsc)
      {
        sp->val = p->info.val.i = n->val.i;
        if ((t->hasmin && t->imin > n->val.i) ||
            (t->hasmin && !t->incmin && t->imin == n->val.i) ||
            (t->hasmax && t->imax < n->val.i) ||
            (t->hasmax && !t->incmax && t->imax == n->val.i))
          semerror("initialization constant outside value range");
      }
      else
      {
        semerror("type error in initialization constant");
        p->info.hasval = False;
        p->info.ptrval = False;
      }
      break;
    case Tfloat:
    case Tdouble:
    case Tldouble:
      if (n->typ->type == Tfloat ||
          n->typ->type == Tdouble ||
          n->typ->type == Tldouble)
      {
        p->info.val.r = n->val.r;
        if ((t->hasmin && t->rmin > n->val.r) ||
            (t->hasmin && !t->incmin && t->rmin == n->val.r) ||
            (t->hasmax && t->rmax < n->val.r) ||
            (t->hasmax && !t->incmax && t->rmax == n->val.r))
          semerror("initialization constant outside value range");
      }
      else if (n->typ->type == Tint)
      {
        p->info.val.r = (double)n->val.i;
        if ((t->hasmin && t->imin > n->val.i) ||
            (t->hasmin && !t->incmin && t->imin == n->val.i) ||
            (t->hasmax && t->imax < n->val.i) ||
            (t->hasmax && !t->incmax && t->imax == n->val.i))
          semerror("initialization constant outside value range");
      }
      else
      {
        semerror("type error in initialization constant");
        p->info.hasval = False;
        p->info.ptrval = False;
      }
      break;
    default:
      if (t->type == Tpointer &&
          (((Tnode*)t->ref)->type == Tchar ||
           ((Tnode*)t->ref)->type == Twchar) &&
          n->typ->type == Tpointer &&
          ((Tnode*)n->typ->ref)->type == Tchar)
      {
        p->info.val.s = n->val.s;
      }
      else if (bflag &&
               t->type == Tarray &&
               ((Tnode*)t->ref)->type == Tchar &&
               n->typ->type == Tpointer &&
               ((Tnode*)n->typ->ref)->type == Tchar)
      {
        if (t->width / ((Tnode*)t->ref)->width - 1 < (int)strlen(n->val.s))
        {
          semerror("char[] initialization constant too long");
          p->info.val.s = "";
        }
        else
        {
          p->info.val.s = n->val.s;
        }

      }
      else if (t->id == lookup("std::string") ||
               t->id == lookup("std::wstring"))
      {
        p->info.val.s = n->val.s;
      }
      else
      {
        semerror("type error in initialization constant");
        p->info.hasval = False;
        p->info.ptrval = False;
      }
      break;
  }
}

/**************************************\

        Type additions

\**************************************/

static void
add_fault(void)
{
  Table *t;
  Entry *p1, *p2, *p3, *p4, *p5;
  Symbol *s1, *s2, *s3, *s4;
  imported = NULL;
  s1 = lookup("SOAP_ENV__Code");
  p1 = entry(classtable, s1);
  if (!p1 || !p1->info.typ->ref)
  {
    t = mktable(NULL);
    if (!p1)
    {
      p1 = enter(classtable, s1);
      p1->info.typ = mkstruct(t, 3*4);
      p1->info.typ->id = s1;
    }
    else
    {
      p1->info.typ->ref = t;
    }
    p2 = enter(t, lookup("SOAP_ENV__Value"));
    p2->info.typ = qname;
    p2->info.minOccurs = 0;
    p2 = enter(t, lookup("SOAP_ENV__Subcode"));
    p2->info.typ = mkpointer(p1->info.typ);
    p2->info.minOccurs = 0;
  }
  else
  {
    t = p1->info.typ->ref;
    p2 = entry(t, lookup("SOAP_ENV__Value"));
    if (!p2)
    {
      sprintf(errbuf, "SOAP_ENV__Value member missing in SOAP_ENV__Code declared at %s:%d", p1->filename, p1->lineno);
      semerror(errbuf);
    }
    else if (p2->info.typ != qname)
    {
      sprintf(errbuf, "SOAP_ENV__Value member of SOAP_ENV__Code is not a _QName type declared at %s:%d", p2->filename, p2->lineno);
      semerror(errbuf);
    }
    p2 = entry(t, lookup("SOAP_ENV__Subcode"));
    if (!p2)
    {
      sprintf(errbuf, "SOAP_ENV__Subcode member missing in SOAP_ENV__Code declared at %s:%d", p1->filename, p1->lineno);
      semerror(errbuf);
    }
    else if (p2->info.typ->type != Tpointer || (Tnode*)p2->info.typ->ref != p1->info.typ)
    {
      sprintf(errbuf, "SOAP_ENV__Subcode member of SOAP_ENV__Code is not a SOAP_ENV__Subcode * type declared at %s:%d", p2->filename, p2->lineno);
      semerror(errbuf);
    }
  }
  s2 = lookup("SOAP_ENV__Detail");
  p2 = entry(classtable, s2);
  if (!p2 || !p2->info.typ->ref)
  {
    t = mktable(NULL);
    if (!p2)
    {
      p2 = enter(classtable, s2);
      p2->info.typ = mkstruct(t, 3*4);
      p2->info.typ->id = s2;
    }
    else
    {
      p2->info.typ->ref = t;
    }
    p3 = enter(t, lookup("__any"));
    p3->info.typ = xml;
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("__type"));
    p3->info.typ = mkint();
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("fault"));
    p3->info.typ = mkpointer(mkvoid());
    p3->info.minOccurs = 0;
    custom_fault = 0;
  }
  s4 = lookup("SOAP_ENV__Reason");
  p4 = entry(classtable, s4);
  if (!p4 || !p4->info.typ->ref)
  {
    t = mktable(NULL);
    if (!p4)
    {
      p4 = enter(classtable, s4);
      p4->info.typ = mkstruct(t, 4);
      p4->info.typ->id = s4;
    }
    else
    {
      p4->info.typ->ref = t;
    }
    p3 = enter(t, lookup("SOAP_ENV__Text"));
    p3->info.typ = mkstring();
    p3->info.minOccurs = 0;
  }
  else
  {
    t = p4->info.typ->ref;
    p3 = entry(t, lookup("SOAP_ENV__Text"));
    if (!p3)
    {
      sprintf(errbuf, "SOAP_ENV__Text member missing in SOAP_ENV__Reason declared at %s:%d", p4->filename, p4->lineno);
      semerror(errbuf);
    }
    else if (!is_string(p3->info.typ))
    {
      sprintf(errbuf, "SOAP_ENV__Text member of SOAP_ENV__Reason is not a char * type declared at %s:%d", p3->filename, p3->lineno);
      semerror(errbuf);
    }
  }
  s3 = lookup("SOAP_ENV__Fault");
  p3 = entry(classtable, s3);
  if (!p3 || !p3->info.typ->ref)
  {
    t = mktable(NULL);
    if (!p3)
    {
      p3 = enter(classtable, s3);
      p3->info.typ = mkstruct(t, 9*4);
      p3->info.typ->id = s3;
    }
    else
    {
      p3->info.typ->ref = t;
    }
    p5 = enter(t, lookup("faultcode"));
    p5->info.typ = qname;
    p5->info.minOccurs = 0;
    p5 = enter(t, lookup("faultstring"));
    p5->info.typ = mkstring();
    p5->info.minOccurs = 0;
    p5 = enter(t, lookup("faultactor"));
    p5->info.typ = mkstring();
    p5->info.minOccurs = 0;
    p5 = enter(t, lookup("detail"));
    p5->info.typ = mkpointer(p2->info.typ);
    p5->info.minOccurs = 0;
    p5 = enter(t, s1);
    p5->info.typ = mkpointer(p1->info.typ);
    p5->info.minOccurs = 0;
    p5 = enter(t, s4);
    p5->info.typ = mkpointer(p4->info.typ);
    p5->info.minOccurs = 0;
    p5 = enter(t, lookup("SOAP_ENV__Node"));
    p5->info.typ = mkstring();
    p5->info.minOccurs = 0;
    p5 = enter(t, lookup("SOAP_ENV__Role"));
    p5->info.typ = mkstring();
    p5->info.minOccurs = 0;
    p5 = enter(t, lookup("SOAP_ENV__Detail"));
    p5->info.typ = mkpointer(p2->info.typ);
    p5->info.minOccurs = 0;
  }
  else
  {
    t = p3->info.typ->ref;
    p5 = entry(t, lookup("faultcode"));
    if (!p5)
    {
      sprintf(errbuf, "faultcode member missing in SOAP_ENV__Fault declared at %s:%d", p3->filename, p3->lineno);
      semerror(errbuf);
    }
    else if (p5->info.typ != qname)
    {
      sprintf(errbuf, "faultcode member of SOAP_ENV__Fault is not a _QName type declared at %s:%d", p5->filename, p5->lineno);
      semerror(errbuf);
    }
    p5 = entry(t, lookup("faultstring"));
    if (!p5)
    {
      sprintf(errbuf, "faultstring member missing in SOAP_ENV__Fault declared at %s:%d", p3->filename, p3->lineno);
      semerror(errbuf);
    }
    else if (!is_string(p5->info.typ))
    {
      sprintf(errbuf, "faultstring member of SOAP_ENV__Fault is not a char * type declared at %s:%d", p5->filename, p5->lineno);
      semerror(errbuf);
    }
    p5 = entry(t, lookup("faultdetail"));
    if (p5 && (p5->info.typ->type != Tpointer || (Tnode*)p5->info.typ->ref != p2->info.typ))
    {
      sprintf(errbuf, "faultdetail member of SOAP_ENV__Fault is not a SOAP_ENV__Detail * type declared at %s:%d", p5->filename, p5->lineno);
      semerror(errbuf);
    }
    p5 = entry(t, s1);
    if (!p5)
    {
      sprintf(errbuf, "SOAP_ENV__Code member missing in SOAP_ENV__Fault declared at %s:%d", p3->filename, p3->lineno);
      semerror(errbuf);
    }
    else if (p5->info.typ->type != Tpointer || (Tnode*)p5->info.typ->ref != p1->info.typ)
    {
      sprintf(errbuf, "SOAP_ENV__Code member of SOAP_ENV__Fault is not a SOAP_ENV__Code * type declared at %s:%d", p5->filename, p5->lineno);
      semerror(errbuf);
    }
    p5 = entry(t, s4);
    if (!p5)
    {
      sprintf(errbuf, "SOAP_ENV__Reason member missing in SOAP_ENV__Fault declared at %s:%d", p3->filename, p3->lineno);
      semerror(errbuf);
    }
    else if (p5->info.typ->type != Tpointer || (Tnode*)p5->info.typ->ref != p4->info.typ)
    {
      sprintf(errbuf, "SOAP_ENV__Reason member of SOAP_ENV__Fault is not a SOAP_ENV__Reason * type declared at %s:%d", p5->filename, p5->lineno);
      semerror(errbuf);
    }
    p5 = entry(t, lookup("SOAP_ENV__Node"));
    if (!p5)
    {
      sprintf(errbuf, "SOAP_ENV__Node member missing in SOAP_ENV__Fault declared at %s:%d", p3->filename, p3->lineno);
      semerror(errbuf);
    }
    else if (!is_string(p5->info.typ))
    {
      sprintf(errbuf, "SOAP_ENV__Node member of SOAP_ENV__Fault is not a char * type declared at %s:%d", p5->filename, p5->lineno);
      semerror(errbuf);
    }
    p5 = entry(t, lookup("SOAP_ENV__Role"));
    if (!p5)
    {
      sprintf(errbuf, "SOAP_ENV__Role member missing in SOAP_ENV__Fault declared at %s:%d", p3->filename, p3->lineno);
      semerror(errbuf);
    }
    else if (!is_string(p5->info.typ))
    {
      sprintf(errbuf, "SOAP_ENV__Role member of SOAP_ENV__Fault is not a char * type declared at %s:%d", p5->filename, p5->lineno);
      semerror(errbuf);
    }
    p5 = entry(t, lookup("SOAP_ENV__Detail"));
    if (p5 && (p5->info.typ->type != Tpointer || (Tnode*)p5->info.typ->ref != p2->info.typ))
    {
      sprintf(errbuf, "SOAP_ENV__Detail member of SOAP_ENV__Fault is not a SOAP_ENV__Detail * type declared at %s:%d", p5->filename, p5->lineno);
      semerror(errbuf);
    }
  }
}

static void
add_soap(void)
{
  Symbol *s = lookup("soap");
  p = enter(classtable, s);
  p->info.typ = mkstruct(NULL, 0);
  p->info.typ->transient = -2;
  p->info.typ->id = s;
  p->filename = "(built-in)";
  p->lineno = 0;
}

static void
add_XML(void)
{
  Symbol *s = lookup("_XML");
  s->token = TYPE;
  p = enter(typetable, s);
  xml = p->info.typ = mksymtype(mkstring(), s);
  p->info.sto = Stypedef;
  p->filename = "(built-in)";
  p->lineno = 0;
}

static void
add_qname(void)
{
  Symbol *s = lookup("_QName");
  s->token = TYPE;
  p = enter(typetable, s);
  qname = p->info.typ = mksymtype(mkstring(), s);
  p->info.sto = Stypedef;
  p->filename = "(built-in)";
  p->lineno = 0;
}

static void
add_header(void)
{
  Table *t;
  Entry *p;
  Symbol *s = lookup("SOAP_ENV__Header");
  imported = NULL;
  p = entry(classtable, s);
  if (!p || !p->info.typ->ref)
  {
    t = mktable(NULL);
    if (!p)
      p = enter(classtable, s);
    p->info.typ = mkstruct(t, 0);
    p->info.typ->id = s;
    custom_header = 0;
  }
}

static void
add_response(Entry *fun, Entry *ret)
{
  Table *t;
  Entry *p, *q;
  Symbol *s;
  size_t i = 0, j, n = strlen(fun->sym->name);
  char *r = (char*)emalloc(n+100);
  strcpy(r, fun->sym->name);
  strcat(r, "Response");
  do
  {
    for (j = 0; j < i; j++)
      r[n+j+8] = '_';
    r[n+i+8] = '\0';
    if (!(s = lookup(r)))
      s = install(r, ID);
    i++;
  }
  while (entry(classtable, s));
  free(r);
  t = mktable(NULL);
  q = enter(t, ret->sym);
  q->info = ret->info;
  if (q->info.typ->type == Treference)
    q->info.typ = (Tnode*)q->info.typ->ref;
  p = enter(classtable, s);
  p->info.typ = mkstruct(t, 4);
  p->info.typ->id = s;
  fun->info.typ->response = p;
}

static void
add_result(Tnode *typ)
{
  Entry *p;
  if (!typ->ref || !((Tnode*)typ->ref)->ref)
  {
    semwarn("response struct/class must be declared before used in function prototype");
    return;
  }
  for (p = ((Table*)((Tnode*)typ->ref)->ref)->list; p; p = p->next)
    if (((int)p->info.sto & (int)Sreturn))
      return;
  for (p = ((Table*)((Tnode*)typ->ref)->ref)->list; p; p = p->next)
  {
    if (p->info.typ->type != Tfun &&
        !((int)p->info.sto & (int)Sattribute) &&
        !is_transient(p->info.typ) &&
        !((int)p->info.sto & ((int)Sprivate | (int)Sprotected)))
      p->info.sto = (Storage)((int)p->info.sto | (int)Sreturn);
    return;
  }
}

static void
add_request(Symbol *sym, Scope *sp)
{
  Entry *p;
  unlinklast(sp->table);
  if ((p = entry(classtable, sym)))
  {
    if (p->info.typ->ref)
    {
      sprintf(errbuf, "service operation name clash: struct/class '%s' already declared at %s:%d", sym->name, p->filename, p->lineno);
      semerror(errbuf);
    }
    else
    {
      p->info.typ->ref = sp->table;
      p->info.typ->width = sp->offset;
    }
  }
  else
  {
    p = enter(classtable, sym);
    p->info.typ = mkstruct(sp->table, sp->offset);
    p->info.typ->id = sym;
  }
  if (p->info.typ->ref)
  {
    for (q = ((Table*)p->info.typ->ref)->list; q; q = q->next)
    {
      if (q->info.typ->type == Treference || q->info.typ->type == Trvalueref)
      {
        sprintf(errbuf, "parameter '%s' of service operation function '%s()' in %s:%d cannot be passed by reference: use a pointer instead", q->sym->name, sym->name, q->filename, q->lineno);
        semwarn(errbuf);
      }
      else if (((int)q->info.sto & ((int)Sconst | (int)Sconstptr)))
      {
        if (!is_string(q->info.typ) && !is_wstring(q->info.typ))
        {
          sprintf(errbuf, "parameter '%s' of service operation function '%s()' in %s:%d cannot be declared const", q->sym->name, sym->name, q->filename, q->lineno);
          semwarn(errbuf);
        }
      }
      else if (((int)q->info.sto & ~((int)Sattribute | (int)Sextern | (int)Sspecial)))
      {
        sprintf(errbuf, "invalid parameter '%s' of service operation function '%s()' in %s:%d", q->sym->name, sym->name, q->filename, q->lineno);
        semwarn(errbuf);
      }
    }
  }
}

/**************************************\

        Add pragma

\**************************************/

static void
add_pragma(const char *s)
{
  Pragma **pp;
  for (pp = &pragmas; *pp; pp = &(*pp)->next)
    ;
  *pp = (Pragma*)emalloc(sizeof(Pragma));
  (*pp)->pragma = s;
  (*pp)->next = NULL;
}
