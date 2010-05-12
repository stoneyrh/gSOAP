/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PRAGMA = 258,
     AUTO = 259,
     DOUBLE = 260,
     INT = 261,
     STRUCT = 262,
     BREAK = 263,
     ELSE = 264,
     LONG = 265,
     SWITCH = 266,
     CASE = 267,
     ENUM = 268,
     REGISTER = 269,
     TYPEDEF = 270,
     CHAR = 271,
     EXTERN = 272,
     RETURN = 273,
     UNION = 274,
     CONST = 275,
     FLOAT = 276,
     SHORT = 277,
     UNSIGNED = 278,
     CONTINUE = 279,
     FOR = 280,
     SIGNED = 281,
     VOID = 282,
     DEFAULT = 283,
     GOTO = 284,
     SIZEOF = 285,
     VOLATILE = 286,
     DO = 287,
     IF = 288,
     STATIC = 289,
     WHILE = 290,
     CLASS = 291,
     PRIVATE = 292,
     PROTECTED = 293,
     PUBLIC = 294,
     VIRTUAL = 295,
     INLINE = 296,
     OPERATOR = 297,
     LLONG = 298,
     BOOL = 299,
     CFALSE = 300,
     CTRUE = 301,
     WCHAR = 302,
     TIME = 303,
     USING = 304,
     NAMESPACE = 305,
     ULLONG = 306,
     MUSTUNDERSTAND = 307,
     SIZE = 308,
     FRIEND = 309,
     TEMPLATE = 310,
     EXPLICIT = 311,
     TYPENAME = 312,
     RESTRICT = 313,
     null = 314,
     UCHAR = 315,
     USHORT = 316,
     UINT = 317,
     ULONG = 318,
     NONE = 319,
     ID = 320,
     LAB = 321,
     TYPE = 322,
     LNG = 323,
     DBL = 324,
     CHR = 325,
     STR = 326,
     RA = 327,
     LA = 328,
     OA = 329,
     XA = 330,
     AA = 331,
     MA = 332,
     DA = 333,
     TA = 334,
     NA = 335,
     PA = 336,
     OR = 337,
     AN = 338,
     NE = 339,
     EQ = 340,
     GE = 341,
     LE = 342,
     RS = 343,
     LS = 344,
     AR = 345,
     PP = 346,
     NN = 347
   };
#endif
/* Tokens.  */
#define PRAGMA 258
#define AUTO 259
#define DOUBLE 260
#define INT 261
#define STRUCT 262
#define BREAK 263
#define ELSE 264
#define LONG 265
#define SWITCH 266
#define CASE 267
#define ENUM 268
#define REGISTER 269
#define TYPEDEF 270
#define CHAR 271
#define EXTERN 272
#define RETURN 273
#define UNION 274
#define CONST 275
#define FLOAT 276
#define SHORT 277
#define UNSIGNED 278
#define CONTINUE 279
#define FOR 280
#define SIGNED 281
#define VOID 282
#define DEFAULT 283
#define GOTO 284
#define SIZEOF 285
#define VOLATILE 286
#define DO 287
#define IF 288
#define STATIC 289
#define WHILE 290
#define CLASS 291
#define PRIVATE 292
#define PROTECTED 293
#define PUBLIC 294
#define VIRTUAL 295
#define INLINE 296
#define OPERATOR 297
#define LLONG 298
#define BOOL 299
#define CFALSE 300
#define CTRUE 301
#define WCHAR 302
#define TIME 303
#define USING 304
#define NAMESPACE 305
#define ULLONG 306
#define MUSTUNDERSTAND 307
#define SIZE 308
#define FRIEND 309
#define TEMPLATE 310
#define EXPLICIT 311
#define TYPENAME 312
#define RESTRICT 313
#define null 314
#define UCHAR 315
#define USHORT 316
#define UINT 317
#define ULONG 318
#define NONE 319
#define ID 320
#define LAB 321
#define TYPE 322
#define LNG 323
#define DBL 324
#define CHR 325
#define STR 326
#define RA 327
#define LA 328
#define OA 329
#define XA 330
#define AA 331
#define MA 332
#define DA 333
#define TA 334
#define NA 335
#define PA 336
#define OR 337
#define AN 338
#define NE 339
#define EQ 340
#define GE 341
#define LE 342
#define RS 343
#define LS 344
#define AR 345
#define PP 346
#define NN 347




/* Copy the first part of user declarations.  */
#line 64 "soapcpp2_yacc.y"


#include "soapcpp2.h"

#ifdef WIN32
#ifndef __STDC__
#define __STDC__
#endif
#define YYINCLUDED_STDLIB_H
#ifdef WIN32_WITHOUT_SOLARIS_FLEX
extern int soapcpp2lex();
#else
extern int yylex();
#endif
#else
extern int yylex();
#endif

extern int is_XML(Tnode*);

#define MAXNEST 16	/* max. nesting depth of scopes */

struct Scope
{	Table	*table;
	Entry	*entry;
	Node	node;
	LONG64	val;
	int	offset;
	Bool	grow;	/* true if offset grows with declarations */
	Bool	mask;	/* true if enum is mask */
}	stack[MAXNEST],	/* stack of tables and offsets */
	*sp;		/* current scope stack pointer */

Table	*classtable = (Table*)0,
	*enumtable = (Table*)0,
	*typetable = (Table*)0,
	*booltable = (Table*)0,
	*templatetable = (Table*)0;

char	*namespaceid = NULL;
int	transient = 0;
int	permission = 0;
int	custom_header = 1;
int	custom_fault = 1;
Pragma	*pragmas = NULL;
Tnode	*qname = NULL;
Tnode	*xml = NULL;

/* function prototypes for support routine section */
static Entry	*undefined(Symbol*);
static Tnode	*mgtype(Tnode*, Tnode*);
static Node	op(const char*, Node, Node), iop(const char*, Node, Node), relop(const char*, Node, Node);
static void	mkscope(Table*, int), enterscope(Table*, int), exitscope();
static int	integer(Tnode*), real(Tnode*), numeric(Tnode*);
static void	add_soap(), add_XML(), add_qname(), add_header(Table*), add_fault(Table*), add_response(Entry*, Entry*), add_result(Tnode*);
extern char	*c_storage(Storage), *c_type(Tnode*), *c_ident(Tnode*);
extern int	is_primitive_or_string(Tnode*), is_stdstr(Tnode*), is_binary(Tnode*), is_external(Tnode*), is_mutable(Tnode*);

/* Temporaries used in semantic rules */
int	i;
char	*s, *s1, *s2;
Symbol	*sym;
Entry	*p, *q;
Tnode	*t;
Node	tmp, c;
Pragma	**pp;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 138 "soapcpp2_yacc.y"
{	Symbol	*sym;
	LONG64	i;
	double	r;
	char	c;
	char	*s;
	Tnode	*typ;
	Storage	sto;
	Node	rec;
	Entry	*e;
}
/* Line 193 of yacc.c.  */
#line 360 "soapcpp2_yacc.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 373 "soapcpp2_yacc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1110

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  241
/* YYNRULES -- Number of states.  */
#define YYNSTATES  376

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   347

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   112,     2,     2,   117,   103,    90,     2,
     114,   115,   101,    99,    72,   100,     2,   102,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    85,   109,
      93,    73,    94,    84,   116,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   110,     2,   111,    89,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   107,    88,   108,   113,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    86,    87,    91,
      92,    95,    96,    97,    98,   104,   105,   106
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    13,    15,    16,    19,    22,
      24,    27,    29,    31,    33,    34,    38,    43,    48,    53,
      58,    61,    63,    65,    66,    67,    68,    70,    73,    77,
      80,    83,    87,    92,    99,   102,   104,   106,   108,   111,
     114,   117,   120,   123,   126,   129,   132,   135,   138,   141,
     144,   147,   150,   153,   156,   159,   162,   165,   168,   171,
     174,   177,   180,   183,   186,   189,   192,   195,   198,   201,
     204,   207,   210,   214,   218,   221,   223,   227,   235,   236,
     237,   239,   241,   245,   252,   253,   255,   259,   264,   265,
     268,   271,   273,   275,   278,   281,   283,   285,   287,   289,
     291,   293,   295,   297,   299,   301,   303,   305,   307,   309,
     311,   313,   315,   317,   319,   327,   333,   339,   347,   349,
     353,   359,   365,   368,   371,   377,   384,   387,   390,   397,
     404,   413,   416,   419,   421,   426,   430,   434,   438,   442,
     445,   448,   451,   453,   455,   458,   461,   464,   466,   469,
     470,   471,   472,   473,   475,   476,   478,   480,   482,   484,
     486,   488,   490,   492,   494,   496,   498,   500,   502,   504,
     506,   507,   509,   510,   513,   514,   516,   517,   520,   523,
     524,   529,   533,   535,   536,   539,   540,   544,   546,   549,
     553,   558,   562,   563,   565,   567,   570,   573,   577,   579,
     585,   587,   589,   593,   595,   597,   601,   603,   605,   609,
     613,   617,   621,   625,   629,   633,   637,   641,   645,   649,
     653,   657,   661,   665,   669,   671,   674,   677,   680,   683,
     686,   689,   694,   696,   700,   702,   704,   706,   708,   710,
     712,   714
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     119,     0,    -1,   120,   121,    -1,    -1,    50,    65,   107,
     122,   108,    -1,   122,    -1,    -1,   122,   123,    -1,   131,
     109,    -1,   124,    -1,     1,   109,    -1,   126,    -1,   127,
      -1,     3,    -1,    -1,   131,   109,   125,    -1,    37,    85,
     128,   125,    -1,    38,    85,   129,   125,    -1,    39,    85,
     130,   125,    -1,   126,   125,   127,   125,    -1,     1,   109,
      -1,   110,    -1,   111,    -1,    -1,    -1,    -1,   145,    -1,
     145,   132,    -1,   145,   133,   138,    -1,   136,   138,    -1,
     137,   138,    -1,   131,    72,   132,    -1,   131,    72,   133,
     138,    -1,   162,    65,   164,   166,   167,   165,    -1,   162,
     135,    -1,    65,    -1,    67,    -1,    65,    -1,    42,   112,
      -1,    42,   113,    -1,    42,    73,    -1,    42,    83,    -1,
      42,    82,    -1,    42,    81,    -1,    42,    80,    -1,    42,
      79,    -1,    42,    78,    -1,    42,    77,    -1,    42,    76,
      -1,    42,    75,    -1,    42,    74,    -1,    42,    86,    -1,
      42,    87,    -1,    42,    88,    -1,    42,    89,    -1,    42,
      90,    -1,    42,    92,    -1,    42,    91,    -1,    42,    93,
      -1,    42,    96,    -1,    42,    94,    -1,    42,    95,    -1,
      42,    98,    -1,    42,    97,    -1,    42,    99,    -1,    42,
     100,    -1,    42,   101,    -1,    42,   102,    -1,    42,   103,
      -1,    42,   105,    -1,    42,   106,    -1,    42,   104,    -1,
      42,   110,   111,    -1,    42,   114,   115,    -1,    42,   144,
      -1,    67,    -1,   161,   113,    67,    -1,   139,   114,   157,
     140,   115,   159,   160,    -1,    -1,    -1,   141,    -1,   142,
      -1,   142,    72,   141,    -1,   146,   162,   143,   164,   167,
     165,    -1,    -1,    65,    -1,   146,   162,   163,    -1,   146,
     162,    65,   163,    -1,    -1,   158,   145,    -1,   147,   145,
      -1,   158,    -1,   147,    -1,   158,   146,    -1,   147,   146,
      -1,    27,    -1,    44,    -1,    16,    -1,    47,    -1,    22,
      -1,     6,    -1,    10,    -1,    43,    -1,    51,    -1,    53,
      -1,    21,    -1,     5,    -1,    26,    -1,    23,    -1,    60,
      -1,    61,    -1,    62,    -1,    63,    -1,    48,    -1,    55,
      93,   151,   134,    94,    36,   134,    -1,    36,   107,   153,
     125,   108,    -1,   149,   107,   153,   125,   108,    -1,   149,
      85,   152,   107,   153,   125,   108,    -1,   149,    -1,   149,
      85,   152,    -1,     7,   107,   153,   125,   108,    -1,   148,
     107,   153,   125,   108,    -1,     7,    65,    -1,     7,    67,
      -1,    19,   107,   154,   125,   108,    -1,    19,   134,   107,
     154,   125,   108,    -1,    19,    65,    -1,    19,    67,    -1,
      13,   107,   153,   131,   156,   108,    -1,   150,   107,   153,
     131,   156,   108,    -1,    13,   101,   134,   107,   155,   131,
     156,   108,    -1,    13,    65,    -1,    13,    67,    -1,    67,
      -1,    67,    93,   144,    94,    -1,    36,     1,   108,    -1,
       7,     1,   108,    -1,    19,     1,   108,    -1,    13,     1,
     108,    -1,     7,   134,    -1,    36,   134,    -1,    13,   134,
      -1,    36,    -1,    57,    -1,    38,   152,    -1,    37,   152,
      -1,    39,   152,    -1,    67,    -1,     7,    65,    -1,    -1,
      -1,    -1,    -1,    72,    -1,    -1,     4,    -1,    14,    -1,
      34,    -1,    56,    -1,    17,    -1,    15,    -1,    40,    -1,
      20,    -1,    54,    -1,    41,    -1,    52,    -1,    18,    -1,
     116,    -1,   117,    -1,    31,    -1,    -1,    20,    -1,    -1,
      73,    68,    -1,    -1,    40,    -1,    -1,   162,   101,    -1,
     162,    90,    -1,    -1,   110,   171,   111,   163,    -1,   110,
     111,   163,    -1,   163,    -1,    -1,    73,   171,    -1,    -1,
      93,    65,    94,    -1,   168,    -1,   168,   169,    -1,   168,
     169,    85,    -1,   168,   169,    85,   169,    -1,   168,    85,
     169,    -1,    -1,    71,    -1,    68,    -1,    99,    68,    -1,
     100,    68,    -1,   170,    72,   170,    -1,   171,    -1,   174,
      84,   172,    85,   171,    -1,   173,    -1,   170,    -1,   174,
      86,   175,    -1,   175,    -1,   173,    -1,   176,    87,   177,
      -1,   177,    -1,   175,    -1,   177,    88,   177,    -1,   177,
      89,   177,    -1,   177,    90,   177,    -1,   177,    92,   177,
      -1,   177,    91,   177,    -1,   177,    93,   177,    -1,   177,
      96,   177,    -1,   177,    94,   177,    -1,   177,    95,   177,
      -1,   177,    98,   177,    -1,   177,    97,   177,    -1,   177,
      99,   177,    -1,   177,   100,   177,    -1,   177,   101,   177,
      -1,   177,   102,   177,    -1,   177,   103,   177,    -1,   178,
      -1,   112,   178,    -1,   113,   178,    -1,   100,   178,    -1,
      99,   178,    -1,   101,   178,    -1,    90,   178,    -1,    30,
     114,   144,   115,    -1,   179,    -1,   114,   170,   115,    -1,
      65,    -1,    68,    -1,    59,    -1,    69,    -1,    70,    -1,
      71,    -1,    45,    -1,    46,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   212,   212,   228,   242,   244,   246,   252,   254,   255,
     256,   263,   264,   266,   289,   292,   294,   296,   298,   300,
     302,   304,   307,   310,   313,   316,   319,   320,   321,   323,
     324,   325,   326,   329,   449,   465,   466,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   516,   526,   543,   601,   603,
     604,   606,   607,   609,   688,   695,   710,   712,   715,   719,
     729,   776,   782,   786,   796,   843,   844,   845,   846,   847,
     848,   849,   850,   851,   852,   853,   854,   855,   856,   857,
     858,   859,   860,   861,   862,   870,   892,   903,   922,   925,
     938,   960,   979,   994,  1009,  1032,  1052,  1067,  1082,  1104,
    1123,  1142,  1150,  1158,  1176,  1185,  1190,  1195,  1200,  1206,
    1223,  1242,  1259,  1260,  1262,  1263,  1264,  1265,  1272,  1274,
    1281,  1289,  1295,  1296,  1298,  1306,  1307,  1308,  1309,  1310,
    1311,  1312,  1313,  1314,  1315,  1316,  1317,  1318,  1322,  1323,
    1325,  1326,  1328,  1329,  1331,  1332,  1334,  1335,  1342,  1347,
    1349,  1362,  1366,  1374,  1375,  1386,  1387,  1389,  1394,  1399,
    1404,  1409,  1415,  1416,  1418,  1419,  1420,  1429,  1430,  1433,
    1438,  1441,  1444,  1447,  1449,  1452,  1455,  1457,  1460,  1461,
    1462,  1463,  1464,  1465,  1466,  1467,  1468,  1469,  1470,  1471,
    1472,  1473,  1474,  1475,  1476,  1479,  1484,  1489,  1499,  1500,
    1507,  1511,  1516,  1519,  1520,  1527,  1531,  1535,  1539,  1543,
    1547,  1551
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PRAGMA", "AUTO", "DOUBLE", "INT",
  "STRUCT", "BREAK", "ELSE", "LONG", "SWITCH", "CASE", "ENUM", "REGISTER",
  "TYPEDEF", "CHAR", "EXTERN", "RETURN", "UNION", "CONST", "FLOAT",
  "SHORT", "UNSIGNED", "CONTINUE", "FOR", "SIGNED", "VOID", "DEFAULT",
  "GOTO", "SIZEOF", "VOLATILE", "DO", "IF", "STATIC", "WHILE", "CLASS",
  "PRIVATE", "PROTECTED", "PUBLIC", "VIRTUAL", "INLINE", "OPERATOR",
  "LLONG", "BOOL", "CFALSE", "CTRUE", "WCHAR", "TIME", "USING",
  "NAMESPACE", "ULLONG", "MUSTUNDERSTAND", "SIZE", "FRIEND", "TEMPLATE",
  "EXPLICIT", "TYPENAME", "RESTRICT", "null", "UCHAR", "USHORT", "UINT",
  "ULONG", "NONE", "ID", "LAB", "TYPE", "LNG", "DBL", "CHR", "STR", "','",
  "'='", "RA", "LA", "OA", "XA", "AA", "MA", "DA", "TA", "NA", "PA", "'?'",
  "':'", "OR", "AN", "'|'", "'^'", "'&'", "NE", "EQ", "'<'", "'>'", "GE",
  "LE", "RS", "LS", "'+'", "'-'", "'*'", "'/'", "'%'", "AR", "PP", "NN",
  "'{'", "'}'", "';'", "'['", "']'", "'!'", "'~'", "'('", "')'", "'@'",
  "'$'", "$accept", "prog", "s1", "exts", "exts1", "ext", "pragma",
  "decls", "t1", "t2", "t3", "t4", "t5", "dclrs", "dclr", "fdclr", "id",
  "name", "constr", "destr", "func", "fname", "fargso", "fargs", "farg",
  "arg", "texp", "spec", "tspec", "type", "struct", "class", "enum",
  "tname", "base", "s2", "s3", "s4", "s5", "s6", "store", "constobj",
  "abstract", "virtual", "ptrs", "array", "arrayck", "init", "tag",
  "occurs", "patt", "cint", "expr", "cexp", "qexp", "oexp", "obex", "aexp",
  "abex", "rexp", "lexp", "pexp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,    44,    61,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,    63,    58,   337,   338,   124,    94,
      38,   339,   340,    60,    62,   341,   342,   343,   344,    43,
      45,    42,    47,    37,   345,   346,   347,   123,   125,    59,
      91,    93,    33,   126,    40,    41,    64,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   118,   119,   120,   121,   121,   122,   122,   123,   123,
     123,   123,   123,   124,   125,   125,   125,   125,   125,   125,
     125,   126,   127,   128,   129,   130,   131,   131,   131,   131,
     131,   131,   131,   132,   133,   134,   134,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   136,   137,   138,   139,   140,
     140,   141,   141,   142,   143,   143,   144,   144,   145,   145,
     145,   146,   146,   146,   146,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   148,
     149,   150,   151,   151,   152,   152,   152,   152,   152,   153,
     154,   155,   156,   156,   157,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     159,   159,   160,   160,   161,   161,   162,   162,   162,   163,
     163,   163,   164,   165,   165,   166,   166,   167,   167,   167,
     167,   167,   168,   168,   169,   169,   169,   170,   170,   171,
     171,   172,   173,   173,   174,   175,   175,   176,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   178,   178,   178,   178,   178,
     178,   178,   178,   179,   179,   179,   179,   179,   179,   179,
     179,   179
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     5,     1,     0,     2,     2,     1,
       2,     1,     1,     1,     0,     3,     4,     4,     4,     4,
       2,     1,     1,     0,     0,     0,     1,     2,     3,     2,
       2,     3,     4,     6,     2,     1,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     2,     1,     3,     7,     0,     0,
       1,     1,     3,     6,     0,     1,     3,     4,     0,     2,
       2,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     7,     5,     5,     7,     1,     3,
       5,     5,     2,     2,     5,     6,     2,     2,     6,     6,
       8,     2,     2,     1,     4,     3,     3,     3,     3,     2,
       2,     2,     1,     1,     2,     2,     2,     1,     2,     0,
       0,     0,     0,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     0,     2,     0,     1,     0,     2,     2,     0,
       4,     3,     1,     0,     2,     0,     3,     1,     2,     3,
       4,     3,     0,     1,     1,     2,     2,     3,     1,     5,
       1,     1,     3,     1,     1,     3,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     2,     2,     2,     2,
       2,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     6,     1,     0,     2,     0,     0,     0,    13,
     155,   106,   100,     0,   101,     0,   156,   160,    97,   159,
     166,     0,   162,   105,    99,   108,   107,    95,   169,   157,
       0,   161,   164,   102,    96,    98,   113,   103,   165,   104,
     163,     0,   158,   109,   110,   111,   112,   133,    21,    22,
     167,   168,     7,     9,    11,    12,     0,    78,    78,   176,
      88,     0,   118,     0,    88,     0,     6,    10,     0,   122,
     123,   149,   139,     0,   131,   132,     0,   149,   141,     0,
     126,   127,   150,     0,     0,    35,    36,   149,   140,     0,
       0,   176,     8,    29,     0,    30,    27,    78,     0,   161,
     133,    90,   149,     0,   149,   149,    89,     0,     0,   136,
       0,   138,     0,    88,   137,     0,   150,   135,     0,   142,
     143,     0,     0,   176,    92,    91,    31,    78,   154,    28,
       0,   179,   178,   177,    34,     0,     0,     0,     0,     0,
     147,   119,     0,    88,    76,     4,     0,     0,     0,     0,
       0,     0,     0,   151,   152,     0,     0,     0,     0,   134,
     179,    94,    93,    32,    79,    40,    50,    49,    48,    47,
      46,    45,    44,    43,    42,    41,    51,    52,    53,    54,
      55,    57,    56,    58,    60,    61,    59,    63,    62,    64,
      65,    66,    67,    68,    71,    69,    70,     0,    38,    39,
       0,    74,     0,   182,   185,     0,   148,   145,   144,   146,
     149,     0,   152,    20,    23,    24,    25,   120,     0,     0,
      88,   176,     0,   124,     0,   115,     0,   179,    86,     0,
      80,    81,   176,    72,    73,     0,   240,   241,   236,   234,
     235,   237,   238,   239,     0,     0,     0,     0,   179,     0,
       0,     0,     0,   200,     0,   203,     0,   206,   224,   232,
       0,   192,   121,     0,   116,     0,     0,     0,     0,     0,
      15,   152,   128,   125,     0,    87,   170,     0,    84,     0,
     230,   228,   227,   229,   181,   225,   226,     0,   198,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     193,   183,   187,     0,   129,    16,    17,    18,    19,     0,
     114,   171,   172,    82,    85,   179,     0,     0,   233,   180,
     201,     0,   202,   205,   208,   209,   210,   212,   211,   213,
     215,   216,   214,   218,   217,   219,   220,   221,   222,   223,
     186,     0,    33,   194,     0,     0,     0,   188,   117,   130,
       0,    77,   192,   231,   197,     0,   184,   191,   195,   196,
     189,   173,   183,   199,   190,    83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,    52,    53,   150,   151,    55,
     266,   267,   268,   152,   126,   127,    72,   134,    57,    58,
      93,    94,   229,   230,   231,   325,   122,    59,   123,    60,
      61,    62,    63,   121,   141,   110,   115,   220,   222,   164,
      64,   322,   361,    65,    98,   203,   204,   352,   261,   311,
     312,   357,   287,   288,   331,   253,   254,   255,   256,   257,
     258,   259
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -333
static const yytype_int16 yypact[] =
{
    -333,    35,   -25,  -333,   -13,  -333,   213,   -40,   -54,  -333,
    -333,  -333,  -333,    16,  -333,    13,  -333,  -333,  -333,  -333,
    -333,    17,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
      20,   -16,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,    11,  -333,  -333,  -333,  -333,  -333,   -67,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,   -49,  -333,  -333,   -52,
     967,    -7,   -61,    -2,   967,     0,  -333,  -333,    18,    28,
      29,  -333,  -333,    49,    28,    29,    52,  -333,  -333,    54,
      28,    29,  -333,    64,    82,  -333,  -333,  -333,  -333,    55,
     967,  -333,  -333,  -333,    98,  -333,  -333,  -333,     8,  -333,
      23,  -333,  -333,    25,  -333,  -333,  -333,    58,   672,  -333,
     441,  -333,    86,   900,  -333,   441,  -333,  -333,   441,  -333,
    -333,    52,   127,  -333,   967,   967,  -333,  -333,  -333,  -333,
     786,   -81,  -333,  -333,  -333,   441,   157,    25,    25,    25,
    -333,   117,   441,   900,  -333,  -333,   116,   152,   153,   156,
     134,   555,   -44,  -333,   171,   137,   441,   138,   154,  -333,
     -24,  -333,  -333,  -333,   967,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,   139,  -333,  -333,
     136,  -333,   979,  -333,   159,   150,  -333,  -333,  -333,  -333,
    -333,   155,   171,  -333,  -333,  -333,  -333,  -333,   151,   327,
     900,   162,   163,  -333,   164,  -333,   241,   169,  -333,   166,
    -333,   210,  -333,  -333,  -333,   170,  -333,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,   996,   996,   996,   996,   169,   996,
     996,   996,   172,    70,    79,   215,   222,   198,  -333,  -333,
     245,   240,  -333,   441,  -333,   204,   327,   327,   327,   327,
    -333,   171,  -333,  -333,    52,  -333,   293,   967,     9,   967,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,   -56,  -333,   169,
     996,   996,   996,   996,   996,   996,   996,   996,   996,   996,
     996,   996,   996,   996,   996,   996,   996,   996,   996,   221,
    -333,   243,    22,   209,  -333,  -333,  -333,  -333,  -333,   211,
    -333,  -333,   247,  -333,  -333,   169,   203,   996,  -333,  -333,
     249,   242,   215,   198,   311,   424,    48,    85,    85,    31,
      31,    31,    31,   205,   205,    -8,    -8,  -333,  -333,  -333,
    -333,   996,  -333,  -333,     2,   257,   267,   251,  -333,  -333,
     270,  -333,   240,  -333,  -333,   996,  -333,  -333,  -333,  -333,
       2,  -333,   243,  -333,  -333,  -333
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -333,  -333,  -333,  -333,   273,  -333,  -333,  -108,     7,   133,
    -333,  -333,  -333,    -5,   296,   297,   -15,  -333,  -333,  -333,
     -39,  -333,  -333,    75,  -333,  -333,  -126,   -11,  -113,   -88,
    -333,  -333,  -333,  -333,    37,   -33,   244,  -333,  -182,  -333,
     -85,  -333,  -333,  -333,  -114,  -152,    32,   -10,  -333,    -3,
    -333,  -332,  -259,  -199,  -333,  -333,  -333,    81,  -333,   -97,
     -77,  -333
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -208
static const yytype_int16 yytable[] =
{
      78,    56,   124,   252,   201,   125,    83,   155,   228,   160,
     157,   161,   162,    54,    73,    88,   327,    68,    79,    95,
     -26,    84,   367,    91,   103,     4,    90,   205,    91,   202,
     265,   330,   136,   -37,   211,     3,   124,   124,   374,   125,
     125,   227,   124,   218,   113,   125,   104,   -75,   224,   101,
     130,   232,     7,   106,   118,    67,   -26,   -26,   129,   328,
      92,   112,   137,   138,   139,   219,   132,    66,   364,   135,
     353,   142,   143,   131,   324,   275,   124,   133,    74,   125,
      75,    69,    80,    70,    81,    85,   202,    86,   163,   319,
     353,   119,   140,   306,   307,   308,   284,  -175,   132,   132,
     102,   355,   356,    56,    89,   105,   158,   354,   154,   133,
     133,   270,   120,   107,    76,    54,    90,    85,   278,    86,
      77,   355,   356,    71,    82,   144,   109,    87,   302,   303,
     304,   305,   306,   307,   308,   -35,   -36,   329,   212,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   366,   326,  -204,   313,  -204,   111,   315,   316,
     317,   318,   114,   290,   232,   291,   373,   280,   281,   282,
     283,   116,   285,   286,   207,   208,   209,   263,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   124,
     117,   124,   125,   153,   125,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   128,    -5,     8,   271,     9,    10,    11,    12,
      13,   159,   206,    14,   210,   213,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,   214,   215,    26,
      27,   216,   217,   221,    28,   223,   225,    29,   226,    30,
     233,   234,   260,    31,    32,   -88,    33,    34,   262,   320,
      35,    36,    49,   264,    37,    38,    39,    40,    41,    42,
    -153,   272,   273,    43,    44,    45,    46,   274,   -88,   202,
      47,   276,   277,   289,   279,   -88,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,  -207,   -88,   304,   305,   306,   307,   308,   292,
     309,   310,   314,   321,   -88,   350,   351,   358,   363,   359,
     360,   327,   -88,    48,    49,   368,  -174,   365,   146,    50,
      51,    10,    11,    12,    13,   369,   370,    14,   371,   108,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,   269,   323,    26,    27,    96,    97,   362,    28,   372,
     156,    29,   375,    30,   147,   148,   149,    31,    32,   -88,
      33,    34,   332,     0,    35,    36,     0,     0,    37,    38,
      39,    40,    41,    42,     0,     0,     0,    43,    44,    45,
      46,     0,   -88,     0,    47,     0,     0,     0,     0,   -88,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,     0,     0,   -88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -88,     0,
       0,     0,     0,     0,     0,   -14,   -88,    48,   -14,     0,
    -174,     0,   146,    50,    51,    10,    11,    12,    13,     0,
       0,    14,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,     0,    26,    27,     0,
       0,     0,    28,     0,     0,    29,     0,    30,   147,   148,
     149,    31,    32,   -88,    33,    34,     0,     0,    35,    36,
       0,     0,    37,    38,    39,    40,    41,    42,     0,     0,
       0,    43,    44,    45,    46,     0,   -88,     0,    47,     0,
       0,     0,     0,   -88,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,     0,     0,
       0,   -88,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -88,     0,     0,     0,     0,     0,     0,   -14,
     -88,    48,     0,     0,  -174,     0,   146,    50,    51,    10,
      11,    12,    13,     0,     0,    14,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
       0,    26,    27,     0,     0,     0,    28,     0,     0,    29,
       0,    30,   147,   148,   149,    31,    32,   -88,    33,    34,
       0,     0,    35,    36,     0,     0,    37,    38,    39,    40,
      41,    42,     0,     0,     0,    43,    44,    45,    46,     0,
     -88,     0,    47,     0,     0,     0,     0,   -88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -88,     0,     0,     0,
       0,     0,     0,     0,   -88,    48,   -14,     0,  -174,     0,
       0,    50,    51,     8,     0,     9,    10,    11,    12,    13,
       0,     0,    14,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,     0,    26,    27,
       0,     0,     0,    28,     0,     0,    29,     0,    30,     0,
       0,     0,    31,    32,   -88,    33,    34,     0,     0,    35,
      36,     0,     0,    37,    38,    39,    40,    41,    42,     0,
       0,     0,    43,    44,    45,    46,     0,   -88,     0,    47,
       0,     0,     0,     0,   -88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -88,     0,     0,     0,     0,     0,     0,
     145,   -88,    48,    49,     0,  -174,     0,     0,    50,    51,
      10,    11,    12,    13,     0,     0,    14,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       0,     0,    26,    27,     0,     0,     0,    28,     0,     0,
      29,     0,    30,     0,     0,     0,    99,    32,     0,    33,
      34,     0,     0,    35,    36,     0,     0,    37,    38,    39,
      40,    41,    42,     0,     0,     0,    43,    44,    45,    46,
       0,     0,     0,   100,     0,     0,     0,     0,     0,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
       0,     0,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,     0,     0,     0,   197,     0,   198,   199,
     200,     0,    50,    51,    10,    11,    12,    13,     0,     0,
      14,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,    26,    27,     0,     0,
       0,    28,     0,     0,    29,     0,    30,     0,     0,     0,
      31,    32,     0,    33,    34,     0,     0,    35,    36,     0,
       0,    37,    38,    39,    40,    41,    42,     0,     0,     0,
      43,    44,    45,    46,     0,     0,     0,    47,     0,     0,
       0,    10,    11,    12,    13,     0,     0,    14,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     0,     0,    26,    27,     0,     0,     0,    28,     0,
       0,    29,     0,    30,     0,     0,     0,    99,    32,   235,
      33,    34,     0,  -174,    35,    36,    50,    51,    37,    38,
      39,    40,    41,    42,   236,   237,   235,    43,    44,    45,
      46,     0,     0,     0,   100,     0,     0,     0,   238,     0,
       0,   236,   237,     0,   239,     0,     0,   240,   241,   242,
     243,     0,     0,     0,     0,   238,     0,     0,     0,     0,
       0,   239,     0,     0,   240,   241,   242,   243,     0,   244,
       0,     0,     0,     0,     0,     0,     0,     0,   245,   246,
     247,     0,     0,    50,    51,     0,   244,     0,     0,     0,
     248,   249,   250,   251,     0,   245,   246,   247,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   249,   250,
     251
};

static const yytype_int16 yycheck[] =
{
      15,     6,    90,   202,   130,    90,    21,   115,   160,   123,
     118,   124,   125,     6,     1,    30,    72,     1,     1,    58,
      72,     1,   354,    72,    85,    50,    93,   135,    72,   110,
     212,   290,     7,   114,   142,     0,   124,   125,   370,   124,
     125,    65,   130,   151,    77,   130,   107,   114,   156,    60,
      42,   164,    65,    64,    87,   109,   108,   109,    97,   115,
     109,    76,    37,    38,    39,   109,    90,   107,   327,   102,
      68,   104,   105,    65,    65,   227,   164,   101,    65,   164,
      67,    65,    65,    67,    67,    65,   110,    67,   127,   271,
      68,    36,    67,   101,   102,   103,   248,   113,    90,    90,
     107,    99,   100,   108,    93,   107,   121,    85,   113,   101,
     101,   219,    57,   113,   101,   108,    93,    65,   232,    67,
     107,    99,   100,   107,   107,    67,   108,   107,    97,    98,
      99,   100,   101,   102,   103,   107,   107,   289,   143,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   351,   279,    84,   263,    86,   108,   266,   267,
     268,   269,   108,    84,   277,    86,   365,   244,   245,   246,
     247,   107,   249,   250,   137,   138,   139,   210,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   277,
     108,   279,   277,   107,   279,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   114,     0,     1,   220,     3,     4,     5,     6,
       7,    94,    65,    10,   107,   109,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    85,    85,    26,
      27,    85,   108,    72,    31,   108,   108,    34,    94,    36,
     111,   115,    93,    40,    41,    42,    43,    44,   108,   274,
      47,    48,   111,   108,    51,    52,    53,    54,    55,    56,
     108,   108,   108,    60,    61,    62,    63,    36,    65,   110,
      67,   115,    72,   111,   114,    72,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    87,    90,    99,   100,   101,   102,   103,    87,
      65,    71,   108,    20,   101,    94,    73,   108,   115,   108,
      73,    72,   109,   110,   111,    68,   113,    85,     1,   116,
     117,     4,     5,     6,     7,    68,    85,    10,    68,    66,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,   218,   277,    26,    27,    59,    59,   325,    31,   362,
     116,    34,   372,    36,    37,    38,    39,    40,    41,    42,
      43,    44,   291,    -1,    47,    48,    -1,    -1,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    -1,    65,    -1,    67,    -1,    -1,    -1,    -1,    72,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   109,   110,   111,    -1,
     113,    -1,     1,   116,   117,     4,     5,     6,     7,    -1,
      -1,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    -1,    26,    27,    -1,
      -1,    -1,    31,    -1,    -1,    34,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    47,    48,
      -1,    -1,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    -1,    65,    -1,    67,    -1,
      -1,    -1,    -1,    72,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,   110,    -1,    -1,   113,    -1,     1,   116,   117,     4,
       5,     6,     7,    -1,    -1,    10,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    60,    61,    62,    63,    -1,
      65,    -1,    67,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   109,   110,   111,    -1,   113,    -1,
      -1,   116,   117,     1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    36,    -1,
      -1,    -1,    40,    41,    42,    43,    44,    -1,    -1,    47,
      48,    -1,    -1,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    60,    61,    62,    63,    -1,    65,    -1,    67,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,   110,   111,    -1,   113,    -1,    -1,   116,   117,
       4,     5,     6,     7,    -1,    -1,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,
      34,    -1,    36,    -1,    -1,    -1,    40,    41,    -1,    43,
      44,    -1,    -1,    47,    48,    -1,    -1,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    60,    61,    62,    63,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    -1,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,    -1,    -1,    -1,   110,    -1,   112,   113,
     114,    -1,   116,   117,     4,     5,     6,     7,    -1,    -1,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    26,    27,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      40,    41,    -1,    43,    44,    -1,    -1,    47,    48,    -1,
      -1,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      60,    61,    62,    63,    -1,    -1,    -1,    67,    -1,    -1,
      -1,     4,     5,     6,     7,    -1,    -1,    10,    -1,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,    -1,
      -1,    34,    -1,    36,    -1,    -1,    -1,    40,    41,    30,
      43,    44,    -1,   113,    47,    48,   116,   117,    51,    52,
      53,    54,    55,    56,    45,    46,    30,    60,    61,    62,
      63,    -1,    -1,    -1,    67,    -1,    -1,    -1,    59,    -1,
      -1,    45,    46,    -1,    65,    -1,    -1,    68,    69,    70,
      71,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    70,    71,    -1,    90,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,
     101,    -1,    -1,   116,   117,    -1,    90,    -1,    -1,    -1,
     111,   112,   113,   114,    -1,    99,   100,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,   113,
     114
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   119,   120,     0,    50,   121,   122,    65,     1,     3,
       4,     5,     6,     7,    10,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    26,    27,    31,    34,
      36,    40,    41,    43,    44,    47,    48,    51,    52,    53,
      54,    55,    56,    60,    61,    62,    63,    67,   110,   111,
     116,   117,   123,   124,   126,   127,   131,   136,   137,   145,
     147,   148,   149,   150,   158,   161,   107,   109,     1,    65,
      67,   107,   134,     1,    65,    67,   101,   107,   134,     1,
      65,    67,   107,   134,     1,    65,    67,   107,   134,    93,
      93,    72,   109,   138,   139,   138,   132,   133,   162,    40,
      67,   145,   107,    85,   107,   107,   145,   113,   122,   108,
     153,   108,   134,   153,   108,   154,   107,   108,   153,    36,
      57,   151,   144,   146,   147,   158,   132,   133,   114,   138,
      42,    65,    90,   101,   135,   153,     7,    37,    38,    39,
      67,   152,   153,   153,    67,   108,     1,    37,    38,    39,
     125,   126,   131,   107,   131,   125,   154,   125,   134,    94,
     162,   146,   146,   138,   157,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   110,   112,   113,
     114,   144,   110,   163,   164,   125,    65,   152,   152,   152,
     107,   125,   131,   109,    85,    85,    85,   108,   125,   109,
     155,    72,   156,   108,   125,   108,    94,    65,   163,   140,
     141,   142,   146,   111,   115,    30,    45,    46,    59,    65,
      68,    69,    70,    71,    90,    99,   100,   101,   111,   112,
     113,   114,   171,   173,   174,   175,   176,   177,   178,   179,
      93,   166,   108,   153,   108,   156,   128,   129,   130,   127,
     125,   131,   108,   108,    36,   163,   115,    72,   162,   114,
     178,   178,   178,   178,   163,   178,   178,   170,   171,   111,
      84,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    65,
      71,   167,   168,   125,   108,   125,   125,   125,   125,   156,
     134,    20,   159,   141,    65,   143,   144,    72,   115,   163,
     170,   172,   175,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
      94,    73,   165,    68,    85,    99,   100,   169,   108,   108,
      73,   160,   164,   115,   170,    85,   171,   169,    68,    68,
      85,    68,   167,   171,   169,   165
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 212 "soapcpp2_yacc.y"
    { if (lflag)
    			  {	custom_header = 0;
    			  	custom_fault = 0;
			  }
			  else
			  {	add_header(sp->table);
			  	add_fault(sp->table);
			  }
			  compile(sp->table);
			  freetable(classtable);
			  freetable(enumtable);
			  freetable(typetable);
			  freetable(booltable);
			  freetable(templatetable);
			;}
    break;

  case 3:
#line 228 "soapcpp2_yacc.y"
    { classtable = mktable((Table*)0);
			  enumtable = mktable((Table*)0);
			  typetable = mktable((Table*)0);
			  booltable = mktable((Table*)0);
			  templatetable = mktable((Table*)0);
			  p = enter(booltable, lookup("false"));
			  p->info.typ = mkint();
			  p->info.val.i = 0;
			  p = enter(booltable, lookup("true"));
			  p->info.typ = mkint();
			  p->info.val.i = 1;
			  mkscope(mktable(mktable((Table*)0)), 0);
			;}
    break;

  case 4:
#line 243 "soapcpp2_yacc.y"
    { namespaceid = (yyvsp[(2) - (5)].sym)->name; ;}
    break;

  case 5:
#line 244 "soapcpp2_yacc.y"
    { ;}
    break;

  case 6:
#line 246 "soapcpp2_yacc.y"
    { add_soap();
			  if (!lflag)
			  {	add_qname();
			  	add_XML();
			  }
			;}
    break;

  case 7:
#line 252 "soapcpp2_yacc.y"
    { ;}
    break;

  case 8:
#line 254 "soapcpp2_yacc.y"
    { ;}
    break;

  case 9:
#line 255 "soapcpp2_yacc.y"
    { ;}
    break;

  case 10:
#line 256 "soapcpp2_yacc.y"
    { synerror("input before ; skipped");
			  while (sp > stack)
			  {	freetable(sp->table);
			  	exitscope();
			  }
			  yyerrok;
			;}
    break;

  case 11:
#line 263 "soapcpp2_yacc.y"
    { ;}
    break;

  case 12:
#line 264 "soapcpp2_yacc.y"
    { ;}
    break;

  case 13:
#line 266 "soapcpp2_yacc.y"
    { if ((yyvsp[(1) - (1)].s)[1] >= 'a' && (yyvsp[(1) - (1)].s)[1] <= 'z')
			  {	for (pp = &pragmas; *pp; pp = &(*pp)->next)
			          ;
				*pp = (Pragma*)emalloc(sizeof(Pragma));
				(*pp)->pragma = (char*)emalloc(strlen((yyvsp[(1) - (1)].s))+1);
				strcpy((*pp)->pragma, (yyvsp[(1) - (1)].s));
				(*pp)->next = NULL;
			  }
			  else if ((i = atoi((yyvsp[(1) - (1)].s)+2)) > 0)
				yylineno = i;
			  else
			  {	sprintf(errbuf, "directive '%s' ignored (use #import to import files and/or use option -i)", (yyvsp[(1) - (1)].s));
			  	semwarn(errbuf);
			  }
			;}
    break;

  case 14:
#line 289 "soapcpp2_yacc.y"
    { transient &= ~6;
			  permission = 0;
			;}
    break;

  case 15:
#line 293 "soapcpp2_yacc.y"
    { ;}
    break;

  case 16:
#line 295 "soapcpp2_yacc.y"
    { ;}
    break;

  case 17:
#line 297 "soapcpp2_yacc.y"
    { ;}
    break;

  case 18:
#line 299 "soapcpp2_yacc.y"
    { ;}
    break;

  case 19:
#line 301 "soapcpp2_yacc.y"
    { ;}
    break;

  case 20:
#line 302 "soapcpp2_yacc.y"
    { synerror("declaration expected"); yyerrok; ;}
    break;

  case 21:
#line 304 "soapcpp2_yacc.y"
    { transient |= 1;
			;}
    break;

  case 22:
#line 307 "soapcpp2_yacc.y"
    { transient &= ~1;
			;}
    break;

  case 23:
#line 310 "soapcpp2_yacc.y"
    { permission = Sprivate;
			;}
    break;

  case 24:
#line 313 "soapcpp2_yacc.y"
    { permission = Sprotected;
			;}
    break;

  case 25:
#line 316 "soapcpp2_yacc.y"
    { permission = 0;
			;}
    break;

  case 26:
#line 319 "soapcpp2_yacc.y"
    { ;}
    break;

  case 27:
#line 320 "soapcpp2_yacc.y"
    { ;}
    break;

  case 28:
#line 322 "soapcpp2_yacc.y"
    { ;}
    break;

  case 29:
#line 323 "soapcpp2_yacc.y"
    { ;}
    break;

  case 30:
#line 324 "soapcpp2_yacc.y"
    { ;}
    break;

  case 31:
#line 325 "soapcpp2_yacc.y"
    { ;}
    break;

  case 32:
#line 327 "soapcpp2_yacc.y"
    { ;}
    break;

  case 33:
#line 330 "soapcpp2_yacc.y"
    { if (((yyvsp[(3) - (6)].rec).sto & Stypedef) && sp->table->level == GLOBAL)
			  {	if (((yyvsp[(3) - (6)].rec).typ->type != Tstruct && (yyvsp[(3) - (6)].rec).typ->type != Tunion && (yyvsp[(3) - (6)].rec).typ->type != Tenum) || strcmp((yyvsp[(2) - (6)].sym)->name, (yyvsp[(3) - (6)].rec).typ->id->name))
				{	p = enter(typetable, (yyvsp[(2) - (6)].sym));
					p->info.typ = mksymtype((yyvsp[(3) - (6)].rec).typ, (yyvsp[(2) - (6)].sym));
			  		if ((yyvsp[(3) - (6)].rec).sto & Sextern)
						p->info.typ->transient = -1;
					else
						p->info.typ->transient = (yyvsp[(3) - (6)].rec).typ->transient;
			  		p->info.sto = (yyvsp[(3) - (6)].rec).sto;
					p->info.typ->pattern = (yyvsp[(5) - (6)].rec).pattern;
					if ((yyvsp[(5) - (6)].rec).minOccurs != -1)
					{	p->info.typ->minLength = (yyvsp[(5) - (6)].rec).minOccurs;
					}
					if ((yyvsp[(5) - (6)].rec).maxOccurs > 1)
						p->info.typ->maxLength = (yyvsp[(5) - (6)].rec).maxOccurs;
				}
				(yyvsp[(2) - (6)].sym)->token = TYPE;
			  }
			  else
			  {	p = enter(sp->table, (yyvsp[(2) - (6)].sym));
			  	p->info.typ = (yyvsp[(3) - (6)].rec).typ;
			  	p->info.sto = ((yyvsp[(3) - (6)].rec).sto | permission);
				if ((yyvsp[(6) - (6)].rec).hasval)
				{	p->info.hasval = True;
					switch ((yyvsp[(3) - (6)].rec).typ->type)
					{	case Tchar:
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
						case Ttime:
							if ((yyvsp[(6) - (6)].rec).typ->type == Tint || (yyvsp[(6) - (6)].rec).typ->type == Tchar || (yyvsp[(6) - (6)].rec).typ->type == Tenum)
								sp->val = p->info.val.i = (yyvsp[(6) - (6)].rec).val.i;
							else
							{	semerror("type error in initialization constant");
								p->info.hasval = False;
							}
							break;
						case Tfloat:
						case Tdouble:
						case Tldouble:
							if ((yyvsp[(6) - (6)].rec).typ->type == Tfloat || (yyvsp[(6) - (6)].rec).typ->type == Tdouble || (yyvsp[(6) - (6)].rec).typ->type == Tldouble)
								p->info.val.r = (yyvsp[(6) - (6)].rec).val.r;
							else if ((yyvsp[(6) - (6)].rec).typ->type == Tint)
								p->info.val.r = (double)(yyvsp[(6) - (6)].rec).val.i;
							else
							{	semerror("type error in initialization constant");
								p->info.hasval = False;
							}
							break;
						default:
							if ((yyvsp[(3) - (6)].rec).typ->type == Tpointer
							 && ((Tnode*)(yyvsp[(3) - (6)].rec).typ->ref)->type == Tchar
							 && (yyvsp[(6) - (6)].rec).typ->type == Tpointer
							 && ((Tnode*)(yyvsp[(6) - (6)].rec).typ->ref)->type == Tchar)
								p->info.val.s = (yyvsp[(6) - (6)].rec).val.s;
							else if (bflag
							 && (yyvsp[(3) - (6)].rec).typ->type == Tarray
							 && ((Tnode*)(yyvsp[(3) - (6)].rec).typ->ref)->type == Tchar
							 && (yyvsp[(6) - (6)].rec).typ->type == Tpointer
							 && ((Tnode*)(yyvsp[(6) - (6)].rec).typ->ref)->type == Tchar)
							{	if ((yyvsp[(3) - (6)].rec).typ->width / ((Tnode*)(yyvsp[(3) - (6)].rec).typ->ref)->width - 1 < strlen((yyvsp[(6) - (6)].rec).val.s))
								{	semerror("char[] initialization constant too long");
									p->info.val.s = "";
								}

								else
									p->info.val.s = (yyvsp[(6) - (6)].rec).val.s;
							}
							else if ((yyvsp[(3) - (6)].rec).typ->type == Tpointer
							      && ((Tnode*)(yyvsp[(3) - (6)].rec).typ->ref)->id == lookup("std::string"))
							      	p->info.val.s = (yyvsp[(6) - (6)].rec).val.s;
							else if ((yyvsp[(3) - (6)].rec).typ->id == lookup("std::string"))
							      	p->info.val.s = (yyvsp[(6) - (6)].rec).val.s;
							else if ((yyvsp[(3) - (6)].rec).typ->type == Tpointer
							      && (yyvsp[(6) - (6)].rec).typ->type == Tint
							      && (yyvsp[(6) - (6)].rec).val.i == 0)
								p->info.val.i = 0;
							else
							{	semerror("type error in initialization constant");
								p->info.hasval = False;
							}
							break;
					}
				}
				else
					p->info.val.i = sp->val;
			        if ((yyvsp[(5) - (6)].rec).minOccurs < 0)
			        {	if (((yyvsp[(3) - (6)].rec).sto & Sattribute) || (yyvsp[(3) - (6)].rec).typ->type == Tpointer || (yyvsp[(3) - (6)].rec).typ->type == Ttemplate || !strncmp((yyvsp[(2) - (6)].sym)->name, "__size", 6))
			        		p->info.minOccurs = 0;
			        	else
			        		p->info.minOccurs = 1;
				}
				else
					p->info.minOccurs = (yyvsp[(5) - (6)].rec).minOccurs;
				p->info.maxOccurs = (yyvsp[(5) - (6)].rec).maxOccurs;
				if (sp->mask)
					sp->val <<= 1;
				else
					sp->val++;
			  	p->info.offset = sp->offset;
				if ((yyvsp[(3) - (6)].rec).sto & Sextern)
					p->level = GLOBAL;
				else if ((yyvsp[(3) - (6)].rec).sto & Stypedef)
					;
			  	else if (sp->grow)
					sp->offset += p->info.typ->width;
				else if (p->info.typ->width > sp->offset)
					sp->offset = p->info.typ->width;
			  }
			  sp->entry = p;
			;}
    break;

  case 34:
#line 449 "soapcpp2_yacc.y"
    { if ((yyvsp[(1) - (2)].rec).sto & Stypedef)
			  {	sprintf(errbuf, "invalid typedef qualifier for '%s'", (yyvsp[(2) - (2)].sym)->name);
				semwarn(errbuf);
			  }
			  p = enter(sp->table, (yyvsp[(2) - (2)].sym));
			  p->info.typ = (yyvsp[(1) - (2)].rec).typ;
			  p->info.sto = (yyvsp[(1) - (2)].rec).sto;
			  p->info.hasval = False;
			  p->info.offset = sp->offset;
			  if (sp->grow)
				sp->offset += p->info.typ->width;
			  else if (p->info.typ->width > sp->offset)
				sp->offset = p->info.typ->width;
			  sp->entry = p;
			;}
    break;

  case 35:
#line 465 "soapcpp2_yacc.y"
    { (yyval.sym) = (yyvsp[(1) - (1)].sym); ;}
    break;

  case 36:
#line 466 "soapcpp2_yacc.y"
    { (yyval.sym) = (yyvsp[(1) - (1)].sym); ;}
    break;

  case 37:
#line 468 "soapcpp2_yacc.y"
    { (yyval.sym) = (yyvsp[(1) - (1)].sym); ;}
    break;

  case 38:
#line 469 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator!"); ;}
    break;

  case 39:
#line 470 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator~"); ;}
    break;

  case 40:
#line 471 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator="); ;}
    break;

  case 41:
#line 472 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator+="); ;}
    break;

  case 42:
#line 473 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator-="); ;}
    break;

  case 43:
#line 474 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator*="); ;}
    break;

  case 44:
#line 475 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator/="); ;}
    break;

  case 45:
#line 476 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator%="); ;}
    break;

  case 46:
#line 477 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator&="); ;}
    break;

  case 47:
#line 478 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator^="); ;}
    break;

  case 48:
#line 479 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator|="); ;}
    break;

  case 49:
#line 480 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator<<="); ;}
    break;

  case 50:
#line 481 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator>>="); ;}
    break;

  case 51:
#line 482 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator||"); ;}
    break;

  case 52:
#line 483 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator&&"); ;}
    break;

  case 53:
#line 484 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator|"); ;}
    break;

  case 54:
#line 485 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator^"); ;}
    break;

  case 55:
#line 486 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator&"); ;}
    break;

  case 56:
#line 487 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator=="); ;}
    break;

  case 57:
#line 488 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator!="); ;}
    break;

  case 58:
#line 489 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator<"); ;}
    break;

  case 59:
#line 490 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator<="); ;}
    break;

  case 60:
#line 491 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator>"); ;}
    break;

  case 61:
#line 492 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator>="); ;}
    break;

  case 62:
#line 493 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator<<"); ;}
    break;

  case 63:
#line 494 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator>>"); ;}
    break;

  case 64:
#line 495 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator+"); ;}
    break;

  case 65:
#line 496 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator-"); ;}
    break;

  case 66:
#line 497 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator*"); ;}
    break;

  case 67:
#line 498 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator/"); ;}
    break;

  case 68:
#line 499 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator%"); ;}
    break;

  case 69:
#line 500 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator++"); ;}
    break;

  case 70:
#line 501 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator--"); ;}
    break;

  case 71:
#line 502 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator->"); ;}
    break;

  case 72:
#line 503 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator[]"); ;}
    break;

  case 73:
#line 504 "soapcpp2_yacc.y"
    { (yyval.sym) = lookup("operator()"); ;}
    break;

  case 74:
#line 505 "soapcpp2_yacc.y"
    { s1 = c_storage((yyvsp[(2) - (2)].rec).sto);
			  s2 = c_type((yyvsp[(2) - (2)].rec).typ);
			  s = (char*)emalloc(strlen(s1) + strlen(s2) + 10);
			  strcpy(s, "operator ");
			  strcat(s, s1);
			  strcat(s, s2);
			  (yyval.sym) = lookup(s);
			  if (!(yyval.sym))
				(yyval.sym) = install(s, ID);
			;}
    break;

  case 75:
#line 516 "soapcpp2_yacc.y"
    { if (!(p = entry(classtable, (yyvsp[(1) - (1)].sym))))
			  	semerror("invalid constructor");
			  sp->entry = enter(sp->table, (yyvsp[(1) - (1)].sym));
			  sp->entry->info.typ = mknone();
			  sp->entry->info.sto = Snone;
			  sp->entry->info.offset = sp->offset;
			  sp->node.typ = mkvoid();
			  sp->node.sto = Snone;
			;}
    break;

  case 76:
#line 527 "soapcpp2_yacc.y"
    { if (!(p = entry(classtable, (yyvsp[(3) - (3)].sym))))
			  	semerror("invalid destructor");
			  s = (char*)emalloc(strlen((yyvsp[(3) - (3)].sym)->name) + 2);
			  strcpy(s, "~");
			  strcat(s, (yyvsp[(3) - (3)].sym)->name);
			  sym = lookup(s);
			  if (!sym)
				sym = install(s, ID);
			  sp->entry = enter(sp->table, sym);
			  sp->entry->info.typ = mknone();
			  sp->entry->info.sto = (yyvsp[(1) - (3)].sto);
			  sp->entry->info.offset = sp->offset;
			  sp->node.typ = mkvoid();
			  sp->node.sto = Snone;
			;}
    break;

  case 77:
#line 544 "soapcpp2_yacc.y"
    { if ((yyvsp[(1) - (7)].e)->level == GLOBAL)
			  {	if (!((yyvsp[(1) - (7)].e)->info.sto & Sextern) && sp->entry && sp->entry->info.typ->type == Tpointer && ((Tnode*)sp->entry->info.typ->ref)->type == Tchar)
			  	{	sprintf(errbuf, "last output parameter of remote method function prototype '%s' is a pointer to a char which will only return one byte: use char** instead to return a string", (yyvsp[(1) - (7)].e)->sym->name);
					semwarn(errbuf);
				}
				if ((yyvsp[(1) - (7)].e)->info.sto & Sextern)
				 	(yyvsp[(1) - (7)].e)->info.typ = mkmethod((yyvsp[(1) - (7)].e)->info.typ, sp->table);
			  	else if (sp->entry && (sp->entry->info.typ->type == Tpointer || sp->entry->info.typ->type == Treference || sp->entry->info.typ->type == Tarray || is_transient(sp->entry->info.typ)))
				{	if ((yyvsp[(1) - (7)].e)->info.typ->type == Tint)
					{	sp->entry->info.sto = (Storage)((int)sp->entry->info.sto | (int)Sreturn);
						(yyvsp[(1) - (7)].e)->info.typ = mkfun(sp->entry);
						(yyvsp[(1) - (7)].e)->info.typ->id = (yyvsp[(1) - (7)].e)->sym;
						if (!is_transient(sp->entry->info.typ))
						{	if (!is_response(sp->entry->info.typ))
							{	if (!is_XML(sp->entry->info.typ))
									add_response((yyvsp[(1) - (7)].e), sp->entry);
							}
							else
								add_result(sp->entry->info.typ);
						}
					}
					else
					{	sprintf(errbuf, "return type of remote method function prototype '%s' must be integer", (yyvsp[(1) - (7)].e)->sym->name);
						semerror(errbuf);
					}
				}
			  	else
			  	{	sprintf(errbuf, "last output parameter of remote method function prototype '%s' is a return parameter and must be a pointer or reference, or use %s(void) for no return parameter", (yyvsp[(1) - (7)].e)->sym->name, (yyvsp[(1) - (7)].e)->sym->name);
					semerror(errbuf);
			  	}
				if (!((yyvsp[(1) - (7)].e)->info.sto & Sextern))
			  	{	unlinklast(sp->table);
			  		if ((p = entry(classtable, (yyvsp[(1) - (7)].e)->sym)))
					{	if (p->info.typ->ref)
						{	sprintf(errbuf, "remote method name clash: struct/class '%s' already declared at line %d", (yyvsp[(1) - (7)].e)->sym->name, p->lineno);
							semerror(errbuf);
						}
						else
						{	p->info.typ->ref = sp->table;
							p->info.typ->width = sp->offset;
						}
					}
			  		else
			  		{	p = enter(classtable, (yyvsp[(1) - (7)].e)->sym);
						p->info.typ = mkstruct(sp->table, sp->offset);
						p->info.typ->id = (yyvsp[(1) - (7)].e)->sym;
			  		}
			  	}
			  }
			  else if ((yyvsp[(1) - (7)].e)->level == INTERNAL)
			  {	(yyvsp[(1) - (7)].e)->info.typ = mkmethod((yyvsp[(1) - (7)].e)->info.typ, sp->table);
				(yyvsp[(1) - (7)].e)->info.sto = (Storage)((int)(yyvsp[(1) - (7)].e)->info.sto | (int)(yyvsp[(6) - (7)].sto) | (int)(yyvsp[(7) - (7)].sto));
			  	transient &= ~1;
			  }
			  exitscope();
			;}
    break;

  case 78:
#line 601 "soapcpp2_yacc.y"
    { (yyval.e) = sp->entry; ;}
    break;

  case 79:
#line 603 "soapcpp2_yacc.y"
    { ;}
    break;

  case 80:
#line 604 "soapcpp2_yacc.y"
    { ;}
    break;

  case 81:
#line 606 "soapcpp2_yacc.y"
    { ;}
    break;

  case 82:
#line 607 "soapcpp2_yacc.y"
    { ;}
    break;

  case 83:
#line 610 "soapcpp2_yacc.y"
    { if ((yyvsp[(4) - (6)].rec).sto & Stypedef)
			  	semwarn("typedef in function argument");
			  p = enter(sp->table, (yyvsp[(3) - (6)].sym));
			  p->info.typ = (yyvsp[(4) - (6)].rec).typ;
			  p->info.sto = (yyvsp[(4) - (6)].rec).sto;
			  if ((yyvsp[(5) - (6)].rec).minOccurs < 0)
			  {	if (((yyvsp[(4) - (6)].rec).sto & Sattribute) || (yyvsp[(4) - (6)].rec).typ->type == Tpointer)
			        	p->info.minOccurs = 0;
			       	else
			        	p->info.minOccurs = 1;
			  }
			  else
				p->info.minOccurs = (yyvsp[(5) - (6)].rec).minOccurs;
			  p->info.maxOccurs = (yyvsp[(5) - (6)].rec).maxOccurs;
			  if ((yyvsp[(6) - (6)].rec).hasval)
			  {	p->info.hasval = True;
				switch ((yyvsp[(4) - (6)].rec).typ->type)
				{	case Tchar:
					case Tuchar:
					case Tshort:
					case Tushort:
					case Tint:
					case Tuint:
					case Tlong:
					case Tulong:
					case Tenum:
					case Ttime:
						if ((yyvsp[(6) - (6)].rec).typ->type == Tint || (yyvsp[(6) - (6)].rec).typ->type == Tchar || (yyvsp[(6) - (6)].rec).typ->type == Tenum)
							sp->val = p->info.val.i = (yyvsp[(6) - (6)].rec).val.i;
						else
						{	semerror("type error in initialization constant");
							p->info.hasval = False;
						}
						break;
					case Tfloat:
					case Tdouble:
					case Tldouble:
						if ((yyvsp[(6) - (6)].rec).typ->type == Tfloat || (yyvsp[(6) - (6)].rec).typ->type == Tdouble || (yyvsp[(6) - (6)].rec).typ->type == Tldouble)
							p->info.val.r = (yyvsp[(6) - (6)].rec).val.r;
						else if ((yyvsp[(6) - (6)].rec).typ->type == Tint)
							p->info.val.r = (double)(yyvsp[(6) - (6)].rec).val.i;
						else
						{	semerror("type error in initialization constant");
							p->info.hasval = False;
						}
						break;
					default:
						if ((yyvsp[(4) - (6)].rec).typ->type == Tpointer
						 && ((Tnode*)(yyvsp[(4) - (6)].rec).typ->ref)->type == Tchar
						 && (yyvsp[(6) - (6)].rec).typ->type == Tpointer
						 && ((Tnode*)(yyvsp[(6) - (6)].rec).typ->ref)->type == Tchar)
							p->info.val.s = (yyvsp[(6) - (6)].rec).val.s;
						else if ((yyvsp[(4) - (6)].rec).typ->type == Tpointer
						      && ((Tnode*)(yyvsp[(4) - (6)].rec).typ->ref)->id == lookup("std::string"))
						      	p->info.val.s = (yyvsp[(6) - (6)].rec).val.s;
						else if ((yyvsp[(4) - (6)].rec).typ->id == lookup("std::string"))
						      	p->info.val.s = (yyvsp[(6) - (6)].rec).val.s;
						else if ((yyvsp[(4) - (6)].rec).typ->type == Tpointer
						      && (yyvsp[(6) - (6)].rec).typ->type == Tint
						      && (yyvsp[(6) - (6)].rec).val.i == 0)
							p->info.val.i = 0;
						else
						{	semerror("type error in initialization constant");
							p->info.hasval = False;
						}
						break;
				}
			  }
			  p->info.offset = sp->offset;
			  if ((yyvsp[(4) - (6)].rec).sto & Sextern)
				p->level = GLOBAL;
			  else if (sp->grow)
				sp->offset += p->info.typ->width;
			  else if (p->info.typ->width > sp->offset)
				sp->offset = p->info.typ->width;
			  sp->entry = p;
			;}
    break;

  case 84:
#line 688 "soapcpp2_yacc.y"
    { if (sp->table->level != PARAM)
			    (yyval.sym) = gensymidx("param", (int)++sp->val);
			  else if (eflag)
				(yyval.sym) = gensymidx("_param", (int)++sp->val);
			  else
				(yyval.sym) = gensym("_param");
			;}
    break;

  case 85:
#line 695 "soapcpp2_yacc.y"
    { if (vflag != 1 && *(yyvsp[(1) - (1)].sym)->name == '_' && sp->table->level == GLOBAL)
			  { sprintf(errbuf, "SOAP 1.2 does not support anonymous parameters '%s'", (yyvsp[(1) - (1)].sym)->name);
			    semwarn(errbuf);
			  }
			  (yyval.sym) = (yyvsp[(1) - (1)].sym);
			;}
    break;

  case 86:
#line 711 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(3) - (3)].rec); ;}
    break;

  case 87:
#line 713 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(4) - (4)].rec); ;}
    break;

  case 88:
#line 715 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkint();
			  (yyval.rec).sto = Snone;
			  sp->node = (yyval.rec);
			;}
    break;

  case 89:
#line 719 "soapcpp2_yacc.y"
    { (yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
			  (yyval.rec).sto = (Storage)((int)(yyvsp[(1) - (2)].sto) | (int)(yyvsp[(2) - (2)].rec).sto);
			  if (((yyval.rec).sto & Sattribute) && !is_primitive_or_string((yyvsp[(2) - (2)].rec).typ) && !is_stdstr((yyvsp[(2) - (2)].rec).typ) && !is_binary((yyvsp[(2) - (2)].rec).typ) && !is_external((yyvsp[(2) - (2)].rec).typ))
			  {	semwarn("invalid attribute type");
			  	(yyval.rec).sto &= ~Sattribute;
			  }
			  sp->node = (yyval.rec);
			  if ((yyvsp[(1) - (2)].sto) & Sextern)
				transient = 0;
			;}
    break;

  case 90:
#line 729 "soapcpp2_yacc.y"
    { if ((yyvsp[(1) - (2)].typ)->type == Tint)
				switch ((yyvsp[(2) - (2)].rec).typ->type)
				{ case Tchar:	(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ; break;
				  case Tshort:	(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ; break;
				  case Tint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tlong:	(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ; break;
				  case Tllong:	(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ; break;
				  default:	semwarn("illegal use of 'signed'");
						(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
				}
			  else if ((yyvsp[(1) - (2)].typ)->type == Tuint)
				switch ((yyvsp[(2) - (2)].rec).typ->type)
				{ case Tchar:	(yyval.rec).typ = mkuchar(); break;
				  case Tshort:	(yyval.rec).typ = mkushort(); break;
				  case Tint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tlong:	(yyval.rec).typ = mkulong(); break;
				  case Tllong:	(yyval.rec).typ = mkullong(); break;
				  default:	semwarn("illegal use of 'unsigned'");
						(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
				}
			  else if ((yyvsp[(1) - (2)].typ)->type == Tlong)
				switch ((yyvsp[(2) - (2)].rec).typ->type)
				{ case Tint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tlong:	(yyval.rec).typ = mkllong(); break;
				  case Tuint:	(yyval.rec).typ = mkulong(); break;
				  case Tulong:	(yyval.rec).typ = mkullong(); break;
				  case Tdouble:	(yyval.rec).typ = mkldouble(); break;
				  default:	semwarn("illegal use of 'long'");
						(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
				}
			  else if ((yyvsp[(1) - (2)].typ)->type == Tulong)
				switch ((yyvsp[(2) - (2)].rec).typ->type)
				{ case Tint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tlong:	(yyval.rec).typ = mkullong(); break;
				  case Tuint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tulong:	(yyval.rec).typ = mkullong(); break;
				  default:	semwarn("illegal use of 'long'");
						(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
				}
			  else if ((yyvsp[(2) - (2)].rec).typ->type == Tint)
				(yyval.rec).typ = (yyvsp[(1) - (2)].typ);
			  else
			  	semwarn("invalid type (missing ';' or type name used as non-type identifier?)");
			  (yyval.rec).sto = (yyvsp[(2) - (2)].rec).sto;
			  sp->node = (yyval.rec);
			;}
    break;

  case 91:
#line 776 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkint();
			  (yyval.rec).sto = (yyvsp[(1) - (1)].sto);
			  sp->node = (yyval.rec);
			  if ((yyvsp[(1) - (1)].sto) & Sextern)
				transient = 0;
			;}
    break;

  case 92:
#line 782 "soapcpp2_yacc.y"
    { (yyval.rec).typ = (yyvsp[(1) - (1)].typ);
			  (yyval.rec).sto = Snone;
			  sp->node = (yyval.rec);
			;}
    break;

  case 93:
#line 786 "soapcpp2_yacc.y"
    { (yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
			  (yyval.rec).sto = (Storage)((int)(yyvsp[(1) - (2)].sto) | (int)(yyvsp[(2) - (2)].rec).sto);
			  if (((yyval.rec).sto & Sattribute) && !is_primitive_or_string((yyvsp[(2) - (2)].rec).typ) && !is_stdstr((yyvsp[(2) - (2)].rec).typ) && !is_binary((yyvsp[(2) - (2)].rec).typ) && !is_external((yyvsp[(2) - (2)].rec).typ))
			  {	semwarn("invalid attribute type");
			  	(yyval.rec).sto &= ~Sattribute;
			  }
			  sp->node = (yyval.rec);
			  if ((yyvsp[(1) - (2)].sto) & Sextern)
				transient = 0;
			;}
    break;

  case 94:
#line 796 "soapcpp2_yacc.y"
    { if ((yyvsp[(1) - (2)].typ)->type == Tint)
				switch ((yyvsp[(2) - (2)].rec).typ->type)
				{ case Tchar:	(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ; break;
				  case Tshort:	(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ; break;
				  case Tint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tlong:	(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ; break;
				  case Tllong:	(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ; break;
				  default:	semwarn("illegal use of 'signed'");
						(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
				}
			  else if ((yyvsp[(1) - (2)].typ)->type == Tuint)
				switch ((yyvsp[(2) - (2)].rec).typ->type)
				{ case Tchar:	(yyval.rec).typ = mkuchar(); break;
				  case Tshort:	(yyval.rec).typ = mkushort(); break;
				  case Tint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tlong:	(yyval.rec).typ = mkulong(); break;
				  case Tllong:	(yyval.rec).typ = mkullong(); break;
				  default:	semwarn("illegal use of 'unsigned'");
						(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
				}
			  else if ((yyvsp[(1) - (2)].typ)->type == Tlong)
				switch ((yyvsp[(2) - (2)].rec).typ->type)
				{ case Tint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tlong:	(yyval.rec).typ = mkllong(); break;
				  case Tuint:	(yyval.rec).typ = mkulong(); break;
				  case Tulong:	(yyval.rec).typ = mkullong(); break;
				  case Tdouble:	(yyval.rec).typ = mkldouble(); break;
				  default:	semwarn("illegal use of 'long'");
						(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
				}
			  else if ((yyvsp[(1) - (2)].typ)->type == Tulong)
				switch ((yyvsp[(2) - (2)].rec).typ->type)
				{ case Tint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tlong:	(yyval.rec).typ = mkullong(); break;
				  case Tuint:	(yyval.rec).typ = (yyvsp[(1) - (2)].typ); break;
				  case Tulong:	(yyval.rec).typ = mkullong(); break;
				  default:	semwarn("illegal use of 'long'");
						(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
				}
			  else if ((yyvsp[(2) - (2)].rec).typ->type == Tint)
				(yyval.rec).typ = (yyvsp[(1) - (2)].typ);
			  else
			  	semwarn("invalid type");
			  (yyval.rec).sto = (yyvsp[(2) - (2)].rec).sto;
			  sp->node = (yyval.rec);
			;}
    break;

  case 95:
#line 843 "soapcpp2_yacc.y"
    { (yyval.typ) = mkvoid(); ;}
    break;

  case 96:
#line 844 "soapcpp2_yacc.y"
    { (yyval.typ) = mkbool(); ;}
    break;

  case 97:
#line 845 "soapcpp2_yacc.y"
    { (yyval.typ) = mkchar(); ;}
    break;

  case 98:
#line 846 "soapcpp2_yacc.y"
    { (yyval.typ) = mkwchart(); ;}
    break;

  case 99:
#line 847 "soapcpp2_yacc.y"
    { (yyval.typ) = mkshort(); ;}
    break;

  case 100:
#line 848 "soapcpp2_yacc.y"
    { (yyval.typ) = mkint(); ;}
    break;

  case 101:
#line 849 "soapcpp2_yacc.y"
    { (yyval.typ) = mklong(); ;}
    break;

  case 102:
#line 850 "soapcpp2_yacc.y"
    { (yyval.typ) = mkllong(); ;}
    break;

  case 103:
#line 851 "soapcpp2_yacc.y"
    { (yyval.typ) = mkullong(); ;}
    break;

  case 104:
#line 852 "soapcpp2_yacc.y"
    { (yyval.typ) = mkulong(); ;}
    break;

  case 105:
#line 853 "soapcpp2_yacc.y"
    { (yyval.typ) = mkfloat(); ;}
    break;

  case 106:
#line 854 "soapcpp2_yacc.y"
    { (yyval.typ) = mkdouble(); ;}
    break;

  case 107:
#line 855 "soapcpp2_yacc.y"
    { (yyval.typ) = mkint(); ;}
    break;

  case 108:
#line 856 "soapcpp2_yacc.y"
    { (yyval.typ) = mkuint(); ;}
    break;

  case 109:
#line 857 "soapcpp2_yacc.y"
    { (yyval.typ) = mkuchar(); ;}
    break;

  case 110:
#line 858 "soapcpp2_yacc.y"
    { (yyval.typ) = mkushort(); ;}
    break;

  case 111:
#line 859 "soapcpp2_yacc.y"
    { (yyval.typ) = mkuint(); ;}
    break;

  case 112:
#line 860 "soapcpp2_yacc.y"
    { (yyval.typ) = mkulong(); ;}
    break;

  case 113:
#line 861 "soapcpp2_yacc.y"
    { (yyval.typ) = mktimet(); ;}
    break;

  case 114:
#line 863 "soapcpp2_yacc.y"
    { if (!(p = entry(templatetable, (yyvsp[(7) - (7)].sym))))
			  {	p = enter(templatetable, (yyvsp[(7) - (7)].sym));
			  	p->info.typ = mktemplate(NULL, (yyvsp[(7) - (7)].sym));
			  	(yyvsp[(7) - (7)].sym)->token = TYPE;
			  }
			  (yyval.typ) = p->info.typ;
			;}
    break;

  case 115:
#line 871 "soapcpp2_yacc.y"
    { sym = gensym("_Struct");
			  sprintf(errbuf, "anonymous class will be named '%s'", sym->name);
			  semwarn(errbuf);
			  if ((p = entry(classtable, sym)))
			  {	if (p->info.typ->ref || p->info.typ->type != Tclass)
				{	sprintf(errbuf, "class '%s' already declared at line %d", sym->name, p->lineno);
					semerror(errbuf);
				}
			  }
			  else
			  {	p = enter(classtable, sym);
				p->info.typ = mkclass((Table*)0, 0);
			  }
			  sym->token = TYPE;
			  sp->table->sym = sym;
			  p->info.typ->ref = sp->table;
			  p->info.typ->width = sp->offset;
			  p->info.typ->id = sym;
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 116:
#line 893 "soapcpp2_yacc.y"
    { p = reenter(classtable, (yyvsp[(1) - (5)].e)->sym);
			  sp->table->sym = p->sym;
			  p->info.typ->ref = sp->table;
			  p->info.typ->width = sp->offset;
			  p->info.typ->id = p->sym;
			  if (p->info.typ->base)
			  	sp->table->prev = (Table*)entry(classtable, p->info.typ->base)->info.typ->ref;
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 117:
#line 904 "soapcpp2_yacc.y"
    { p = reenter(classtable, (yyvsp[(1) - (7)].e)->sym);
			  sp->table->sym = p->sym;
			  if (!(yyvsp[(3) - (7)].e))
				semerror("invalid base class");
			  else
			  {	sp->table->prev = (Table*)(yyvsp[(3) - (7)].e)->info.typ->ref;
				if (!sp->table->prev && !(yyvsp[(3) - (7)].e)->info.typ->transient)
				{	sprintf(errbuf, "class '%s' has incomplete type", (yyvsp[(3) - (7)].e)->sym->name);
					semerror(errbuf);
				}
			  	p->info.typ->base = (yyvsp[(3) - (7)].e)->info.typ->id;
			  }
			  p->info.typ->ref = sp->table;
			  p->info.typ->width = sp->offset;
			  p->info.typ->id = p->sym;
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 118:
#line 922 "soapcpp2_yacc.y"
    { (yyvsp[(1) - (1)].e)->info.typ->id = (yyvsp[(1) - (1)].e)->sym;
			  (yyval.typ) = (yyvsp[(1) - (1)].e)->info.typ;
			;}
    break;

  case 119:
#line 926 "soapcpp2_yacc.y"
    { if (!(yyvsp[(3) - (3)].e))
				semerror("invalid base class");
			  else
			  {	if (!(yyvsp[(3) - (3)].e)->info.typ->ref && !(yyvsp[(3) - (3)].e)->info.typ->transient)
				{	sprintf(errbuf, "class '%s' has incomplete type", (yyvsp[(3) - (3)].e)->sym->name);
					semerror(errbuf);
				}
			  	(yyvsp[(1) - (3)].e)->info.typ->base = (yyvsp[(3) - (3)].e)->info.typ->id;
			  }
			  (yyvsp[(1) - (3)].e)->info.typ->id = (yyvsp[(1) - (3)].e)->sym;
			  (yyval.typ) = (yyvsp[(1) - (3)].e)->info.typ;
			;}
    break;

  case 120:
#line 939 "soapcpp2_yacc.y"
    { sym = gensym("_Struct");
			  sprintf(errbuf, "anonymous struct will be named '%s'", sym->name);
			  semwarn(errbuf);
			  if ((p = entry(classtable, sym)))
			  {	if (p->info.typ->ref || p->info.typ->type != Tstruct)
				{	sprintf(errbuf, "struct '%s' already declared at line %d", sym->name, p->lineno);
					semerror(errbuf);
				}
				else
				{	p->info.typ->ref = sp->table;
					p->info.typ->width = sp->offset;
				}
			  }
			  else
			  {	p = enter(classtable, sym);
				p->info.typ = mkstruct(sp->table, sp->offset);
			  }
			  p->info.typ->id = sym;
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 121:
#line 961 "soapcpp2_yacc.y"
    { if ((p = entry(classtable, (yyvsp[(1) - (5)].e)->sym)) && p->info.typ->ref)
			  {	if (is_mutable(p->info.typ))
			  	{	if (merge((Table*)p->info.typ->ref, sp->table))
					{	sprintf(errbuf, "member name clash in struct '%s' declared at line %d", (yyvsp[(1) - (5)].e)->sym->name, p->lineno);
						semerror(errbuf);
					}
			  		p->info.typ->width += sp->offset;
				}
			  }
			  else
			  {	p = reenter(classtable, (yyvsp[(1) - (5)].e)->sym);
			  	p->info.typ->ref = sp->table;
			  	p->info.typ->width = sp->offset;
			  	p->info.typ->id = p->sym;
			  }
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 122:
#line 979 "soapcpp2_yacc.y"
    { if ((p = entry(classtable, (yyvsp[(2) - (2)].sym))))
			  {	if (p->info.typ->type == Tstruct)
			  		(yyval.typ) = p->info.typ;
			  	else
				{	sprintf(errbuf, "'struct %s' redeclaration (line %d)", (yyvsp[(2) - (2)].sym)->name, p->lineno);
			  		semerror(errbuf);
			  		(yyval.typ) = mkint();
				}
			  }
			  else
			  {	p = enter(classtable, (yyvsp[(2) - (2)].sym));
			  	(yyval.typ) = p->info.typ = mkstruct((Table*)0, 0);
				p->info.typ->id = (yyvsp[(2) - (2)].sym);
			  }
			;}
    break;

  case 123:
#line 994 "soapcpp2_yacc.y"
    { if ((p = entry(classtable, (yyvsp[(2) - (2)].sym))))
			  {	if (p->info.typ->type == Tstruct)
					(yyval.typ) = p->info.typ;
			  	else
				{	sprintf(errbuf, "'struct %s' redeclaration (line %d)", (yyvsp[(2) - (2)].sym)->name, p->lineno);
			  		semerror(errbuf);
			  		(yyval.typ) = mkint();
				}
			  }
			  else
			  {	p = enter(classtable, (yyvsp[(2) - (2)].sym));
			  	(yyval.typ) = p->info.typ = mkstruct((Table*)0, 0);
				p->info.typ->id = (yyvsp[(2) - (2)].sym);
			  }
			;}
    break;

  case 124:
#line 1010 "soapcpp2_yacc.y"
    { sym = gensym("_Union");
			  sprintf(errbuf, "anonymous union will be named '%s'", sym->name);
			  semwarn(errbuf);
			  (yyval.typ) = mkunion(sp->table, sp->offset);
			  if ((p = entry(classtable, sym)))
			  {	if (p->info.typ->ref)
				{	sprintf(errbuf, "union or struct '%s' already declared at line %d", sym->name, p->lineno);
					semerror(errbuf);
				}
				else
				{	p->info.typ->ref = sp->table;
					p->info.typ->width = sp->offset;
				}
			  }
			  else
			  {	p = enter(classtable, sym);
				p->info.typ = mkunion(sp->table, sp->offset);
			  }
			  p->info.typ->id = sym;
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 125:
#line 1033 "soapcpp2_yacc.y"
    { if ((p = entry(classtable, (yyvsp[(2) - (6)].sym))))
			  {	if (p->info.typ->ref || p->info.typ->type != Tunion)
			  	{	sprintf(errbuf, "union '%s' already declared at line %d", (yyvsp[(2) - (6)].sym)->name, p->lineno);
					semerror(errbuf);
				}
				else
				{	p = reenter(classtable, (yyvsp[(2) - (6)].sym));
					p->info.typ->ref = sp->table;
					p->info.typ->width = sp->offset;
				}
			  }
			  else
			  {	p = enter(classtable, (yyvsp[(2) - (6)].sym));
				p->info.typ = mkunion(sp->table, sp->offset);
			  }
			  p->info.typ->id = (yyvsp[(2) - (6)].sym);
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 126:
#line 1052 "soapcpp2_yacc.y"
    { if ((p = entry(classtable, (yyvsp[(2) - (2)].sym))))
			  {	if (p->info.typ->type == Tunion)
					(yyval.typ) = p->info.typ;
			  	else
				{	sprintf(errbuf, "'union %s' redeclaration (line %d)", (yyvsp[(2) - (2)].sym)->name, p->lineno);
			  		semerror(errbuf);
			  		(yyval.typ) = mkint();
				}
			  }
			  else
			  {	p = enter(classtable, (yyvsp[(2) - (2)].sym));
			  	(yyval.typ) = p->info.typ = mkunion((Table*) 0, 0);
				p->info.typ->id = (yyvsp[(2) - (2)].sym);
			  }
			;}
    break;

  case 127:
#line 1067 "soapcpp2_yacc.y"
    { if ((p = entry(classtable, (yyvsp[(2) - (2)].sym))))
			  {	if (p->info.typ->type == Tunion)
					(yyval.typ) = p->info.typ;
			  	else
				{	sprintf(errbuf, "'union %s' redeclaration (line %d)", (yyvsp[(2) - (2)].sym)->name, p->lineno);
			  		semerror(errbuf);
			  		(yyval.typ) = mkint();
				}
			  }
			  else
			  {	p = enter(classtable, (yyvsp[(2) - (2)].sym));
			  	(yyval.typ) = p->info.typ = mkunion((Table*) 0, 0);
				p->info.typ->id = (yyvsp[(2) - (2)].sym);
			  }
			;}
    break;

  case 128:
#line 1083 "soapcpp2_yacc.y"
    { sym = gensym("_Enum");
			  sprintf(errbuf, "anonymous enum will be named '%s'", sym->name);
			  semwarn(errbuf);
			  if ((p = entry(enumtable, sym)))
			  {	if (p->info.typ->ref)
				{	sprintf(errbuf, "enum '%s' already declared at line %d", sym->name, p->lineno);
					semerror(errbuf);
				}
				else
				{	p->info.typ->ref = sp->table;
					p->info.typ->width = 4; /* 4 = enum */
				}
			  }
			  else
			  {	p = enter(enumtable, sym);
				p->info.typ = mkenum(sp->table);
			  }
			  p->info.typ->id = sym;
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 129:
#line 1105 "soapcpp2_yacc.y"
    { if ((p = entry(enumtable, (yyvsp[(1) - (6)].e)->sym)))
			  {	if (p->info.typ->ref)
				{	sprintf(errbuf, "enum '%s' already declared at line %d", (yyvsp[(1) - (6)].e)->sym->name, p->lineno);
					semerror(errbuf);
				}
				else
				{	p->info.typ->ref = sp->table;
					p->info.typ->width = 4; /* 4 = enum */
				}
			  }
			  else
			  {	p = enter(enumtable, (yyvsp[(1) - (6)].e)->sym);
				p->info.typ = mkenum(sp->table);
			  }
			  p->info.typ->id = (yyvsp[(1) - (6)].e)->sym;
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 130:
#line 1124 "soapcpp2_yacc.y"
    { if ((p = entry(enumtable, (yyvsp[(3) - (8)].sym))))
			  {	if (p->info.typ->ref)
				{	sprintf(errbuf, "enum '%s' already declared at line %d", (yyvsp[(3) - (8)].sym)->name, p->lineno);
					semerror(errbuf);
				}
				else
				{	p->info.typ->ref = sp->table;
					p->info.typ->width = 8; /* 8 = mask */
				}
			  }
			  else
			  {	p = enter(enumtable, (yyvsp[(3) - (8)].sym));
				p->info.typ = mkmask(sp->table);
			  }
			  p->info.typ->id = (yyvsp[(3) - (8)].sym);
			  (yyval.typ) = p->info.typ;
			  exitscope();
			;}
    break;

  case 131:
#line 1142 "soapcpp2_yacc.y"
    { if ((p = entry(enumtable, (yyvsp[(2) - (2)].sym))))
			  	(yyval.typ) = p->info.typ;
			  else
			  {	p = enter(enumtable, (yyvsp[(2) - (2)].sym));
			  	(yyval.typ) = p->info.typ = mkenum((Table*)0);
				p->info.typ->id = (yyvsp[(2) - (2)].sym);
			  }
			;}
    break;

  case 132:
#line 1150 "soapcpp2_yacc.y"
    { if ((p = entry(enumtable, (yyvsp[(2) - (2)].sym))))
				(yyval.typ) = p->info.typ;
			  else
			  {	p = enter(enumtable, (yyvsp[(2) - (2)].sym));
			  	(yyval.typ) = p->info.typ = mkenum((Table*)0);
				p->info.typ->id = (yyvsp[(2) - (2)].sym);
			  }
			;}
    break;

  case 133:
#line 1158 "soapcpp2_yacc.y"
    { if ((p = entry(typetable, (yyvsp[(1) - (1)].sym))))
				(yyval.typ) = p->info.typ;
			  else if ((p = entry(classtable, (yyvsp[(1) - (1)].sym))))
			  	(yyval.typ) = p->info.typ;
			  else if ((p = entry(enumtable, (yyvsp[(1) - (1)].sym))))
			  	(yyval.typ) = p->info.typ;
			  else if ((yyvsp[(1) - (1)].sym) == lookup("std::string") || (yyvsp[(1) - (1)].sym) == lookup("std::wstring"))
			  {	p = enter(classtable, (yyvsp[(1) - (1)].sym));
				(yyval.typ) = p->info.typ = mkclass((Table*)0, 0);
			  	p->info.typ->id = (yyvsp[(1) - (1)].sym);
			  	p->info.typ->transient = -2;
			  }
			  else
			  {	sprintf(errbuf, "unknown type '%s'", (yyvsp[(1) - (1)].sym)->name);
				semerror(errbuf);
				(yyval.typ) = mkint();
			  }
			;}
    break;

  case 134:
#line 1177 "soapcpp2_yacc.y"
    { if ((p = entry(templatetable, (yyvsp[(1) - (4)].sym))))
				(yyval.typ) = mktemplate((yyvsp[(3) - (4)].rec).typ, (yyvsp[(1) - (4)].sym));
			  else
			  {	sprintf(errbuf, "invalid template '%s'", (yyvsp[(1) - (4)].sym)->name);
				semerror(errbuf);
				(yyval.typ) = mkint();
			  }
			;}
    break;

  case 135:
#line 1186 "soapcpp2_yacc.y"
    { synerror("malformed class definition (use spacing around ':' to separate derived : base)");
			  yyerrok;
			  (yyval.typ) = mkint();
			;}
    break;

  case 136:
#line 1191 "soapcpp2_yacc.y"
    { synerror("malformed struct definition");
			  yyerrok;
			  (yyval.typ) = mkint();
			;}
    break;

  case 137:
#line 1196 "soapcpp2_yacc.y"
    { synerror("malformed union definition");
			  yyerrok;
			  (yyval.typ) = mkint();
			;}
    break;

  case 138:
#line 1201 "soapcpp2_yacc.y"
    { synerror("malformed enum definition");
			  yyerrok;
			  (yyval.typ) = mkint();
			;}
    break;

  case 139:
#line 1206 "soapcpp2_yacc.y"
    { if ((p = entry(classtable, (yyvsp[(2) - (2)].sym))))
			  {	if (p->info.typ->ref)
			   	{	if (!is_mutable(p->info.typ))
					{	sprintf(errbuf, "struct '%s' already declared at line %d", (yyvsp[(2) - (2)].sym)->name, p->lineno);
						semerror(errbuf);
					}
				}
				else
					p = reenter(classtable, (yyvsp[(2) - (2)].sym));
			  }
			  else
			  {	p = enter(classtable, (yyvsp[(2) - (2)].sym));
				p->info.typ = mkstruct((Table*)0, 0);
			  }
			  (yyval.e) = p;
			;}
    break;

  case 140:
#line 1223 "soapcpp2_yacc.y"
    { if ((p = entry(classtable, (yyvsp[(2) - (2)].sym))))
			  {	if (p->info.typ->ref)
			   	{	if (!is_mutable(p->info.typ))
					{	sprintf(errbuf, "class '%s' already declared at line %d", (yyvsp[(2) - (2)].sym)->name, p->lineno);
						semerror(errbuf);
					}
				}
				else
					p = reenter(classtable, (yyvsp[(2) - (2)].sym));
			  }
			  else
			  {	p = enter(classtable, (yyvsp[(2) - (2)].sym));
				p->info.typ = mkclass((Table*)0, 0);
				p->info.typ->id = p->sym;
			  }
			  (yyvsp[(2) - (2)].sym)->token = TYPE;
			  (yyval.e) = p;
			;}
    break;

  case 141:
#line 1242 "soapcpp2_yacc.y"
    { if ((p = entry(enumtable, (yyvsp[(2) - (2)].sym))))
			  {	if (p->info.typ->ref)
				{	sprintf(errbuf, "enum '%s' already declared at line %d", (yyvsp[(2) - (2)].sym)->name, p->lineno);
					semerror(errbuf);
				}
				/*
				else
					p = reenter(classtable, $2);
			  	*/
			  }
			  else
			  {	p = enter(enumtable, (yyvsp[(2) - (2)].sym));
				p->info.typ = mkenum(0);
			  }
			  (yyval.e) = p;
			;}
    break;

  case 142:
#line 1259 "soapcpp2_yacc.y"
    { ;}
    break;

  case 143:
#line 1260 "soapcpp2_yacc.y"
    { ;}
    break;

  case 144:
#line 1262 "soapcpp2_yacc.y"
    { (yyval.e) = (yyvsp[(2) - (2)].e); ;}
    break;

  case 145:
#line 1263 "soapcpp2_yacc.y"
    { (yyval.e) = (yyvsp[(2) - (2)].e); ;}
    break;

  case 146:
#line 1264 "soapcpp2_yacc.y"
    { (yyval.e) = (yyvsp[(2) - (2)].e); ;}
    break;

  case 147:
#line 1265 "soapcpp2_yacc.y"
    { (yyval.e) = entry(classtable, (yyvsp[(1) - (1)].sym));
			  if (!(yyval.e))
			  {	p = entry(typetable, (yyvsp[(1) - (1)].sym));
			  	if (p && (p->info.typ->type == Tclass || p->info.typ->type == Tstruct))
					(yyval.e) = p;
			  }
			;}
    break;

  case 148:
#line 1272 "soapcpp2_yacc.y"
    { (yyval.e) = entry(classtable, (yyvsp[(2) - (2)].sym)); ;}
    break;

  case 149:
#line 1274 "soapcpp2_yacc.y"
    { if (transient == -2)
			  	transient = 0;
			  permission = 0;
			  enterscope(mktable(NULL), 0);
			  sp->entry = NULL;
			;}
    break;

  case 150:
#line 1281 "soapcpp2_yacc.y"
    { if (transient == -2)
			  	transient = 0;
			  permission = 0;
			  enterscope(mktable(NULL), 0);
			  sp->entry = NULL;
			  sp->grow = False;
			;}
    break;

  case 151:
#line 1289 "soapcpp2_yacc.y"
    { enterscope(mktable(NULL), 0);
			  sp->entry = NULL;
			  sp->mask = True;
			  sp->val = 1;
			;}
    break;

  case 152:
#line 1295 "soapcpp2_yacc.y"
    { ;}
    break;

  case 153:
#line 1296 "soapcpp2_yacc.y"
    { ;}
    break;

  case 154:
#line 1298 "soapcpp2_yacc.y"
    { if (sp->table->level == INTERNAL)
			  	transient |= 1;
			  permission = 0;
			  enterscope(mktable(NULL), 0);
			  sp->entry = NULL;
			  sp->table->level = PARAM;
			;}
    break;

  case 155:
#line 1306 "soapcpp2_yacc.y"
    { (yyval.sto) = Sauto; ;}
    break;

  case 156:
#line 1307 "soapcpp2_yacc.y"
    { (yyval.sto) = Sregister; ;}
    break;

  case 157:
#line 1308 "soapcpp2_yacc.y"
    { (yyval.sto) = Sstatic; ;}
    break;

  case 158:
#line 1309 "soapcpp2_yacc.y"
    { (yyval.sto) = Sexplicit; ;}
    break;

  case 159:
#line 1310 "soapcpp2_yacc.y"
    { (yyval.sto) = Sextern; transient = 1; ;}
    break;

  case 160:
#line 1311 "soapcpp2_yacc.y"
    { (yyval.sto) = Stypedef; ;}
    break;

  case 161:
#line 1312 "soapcpp2_yacc.y"
    { (yyval.sto) = Svirtual; ;}
    break;

  case 162:
#line 1313 "soapcpp2_yacc.y"
    { (yyval.sto) = Sconst; ;}
    break;

  case 163:
#line 1314 "soapcpp2_yacc.y"
    { (yyval.sto) = Sfriend; ;}
    break;

  case 164:
#line 1315 "soapcpp2_yacc.y"
    { (yyval.sto) = Sinline; ;}
    break;

  case 165:
#line 1316 "soapcpp2_yacc.y"
    { (yyval.sto) = SmustUnderstand; ;}
    break;

  case 166:
#line 1317 "soapcpp2_yacc.y"
    { (yyval.sto) = Sreturn; ;}
    break;

  case 167:
#line 1318 "soapcpp2_yacc.y"
    { (yyval.sto) = Sattribute;
			  if (eflag)
			   	semwarn("SOAP RPC encoding does not support XML attributes");
			;}
    break;

  case 168:
#line 1322 "soapcpp2_yacc.y"
    { (yyval.sto) = Sspecial; ;}
    break;

  case 169:
#line 1323 "soapcpp2_yacc.y"
    { (yyval.sto) = Sextern; transient = -2; ;}
    break;

  case 170:
#line 1325 "soapcpp2_yacc.y"
    { (yyval.sto) = Snone; ;}
    break;

  case 171:
#line 1326 "soapcpp2_yacc.y"
    { (yyval.sto) = Sconstobj; ;}
    break;

  case 172:
#line 1328 "soapcpp2_yacc.y"
    { (yyval.sto) = Snone; ;}
    break;

  case 173:
#line 1329 "soapcpp2_yacc.y"
    { (yyval.sto) = Sabstract; ;}
    break;

  case 174:
#line 1331 "soapcpp2_yacc.y"
    { (yyval.sto) = Snone; ;}
    break;

  case 175:
#line 1332 "soapcpp2_yacc.y"
    { (yyval.sto) = Svirtual; ;}
    break;

  case 176:
#line 1334 "soapcpp2_yacc.y"
    { (yyval.rec) = tmp = sp->node; ;}
    break;

  case 177:
#line 1335 "soapcpp2_yacc.y"
    { /* handle const pointers, such as const char* */
			  if (/*tmp.typ->type == Tchar &&*/ (tmp.sto & Sconst))
			  	tmp.sto = (tmp.sto & ~Sconst) | Sconstptr;
			  tmp.typ = mkpointer(tmp.typ);
			  tmp.typ->transient = transient;
			  (yyval.rec) = tmp;
			;}
    break;

  case 178:
#line 1342 "soapcpp2_yacc.y"
    { tmp.typ = mkreference(tmp.typ);
			  tmp.typ->transient = transient;
			  (yyval.rec) = tmp;
			;}
    break;

  case 179:
#line 1347 "soapcpp2_yacc.y"
    { (yyval.rec) = tmp;	/* tmp is inherited */
			;}
    break;

  case 180:
#line 1350 "soapcpp2_yacc.y"
    { if (!bflag && (yyvsp[(4) - (4)].rec).typ->type == Tchar)
			  {	sprintf(errbuf, "char["SOAP_LONG_FORMAT"] will be serialized as an array of "SOAP_LONG_FORMAT" bytes: use soapcpp2 option -b to enable char[] string serialization or use char* for strings", (yyvsp[(2) - (4)].rec).val.i, (yyvsp[(2) - (4)].rec).val.i);
			  	semwarn(errbuf);
			  }
			  if ((yyvsp[(2) - (4)].rec).hasval && (yyvsp[(2) - (4)].rec).typ->type == Tint && (yyvsp[(2) - (4)].rec).val.i > 0 && (yyvsp[(4) - (4)].rec).typ->width > 0)
				(yyval.rec).typ = mkarray((yyvsp[(4) - (4)].rec).typ, (int) (yyvsp[(2) - (4)].rec).val.i * (yyvsp[(4) - (4)].rec).typ->width);
			  else
			  {	(yyval.rec).typ = mkarray((yyvsp[(4) - (4)].rec).typ, 0);
			  	semerror("undetermined array size");
			  }
			  (yyval.rec).sto = (yyvsp[(4) - (4)].rec).sto;
			;}
    break;

  case 181:
#line 1362 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkpointer((yyvsp[(3) - (3)].rec).typ); /* zero size array = pointer */
			  (yyval.rec).sto = (yyvsp[(3) - (3)].rec).sto;
			;}
    break;

  case 182:
#line 1366 "soapcpp2_yacc.y"
    { if ((yyvsp[(1) - (1)].rec).typ->type == Tstruct || (yyvsp[(1) - (1)].rec).typ->type == Tclass)
				if (!(yyvsp[(1) - (1)].rec).typ->ref && !(yyvsp[(1) - (1)].rec).typ->transient && !((yyvsp[(1) - (1)].rec).sto & Stypedef))
			   	{	sprintf(errbuf, "struct/class '%s' has incomplete type", (yyvsp[(1) - (1)].rec).typ->id->name);
					semerror(errbuf);
				}
			  (yyval.rec) = (yyvsp[(1) - (1)].rec);
			;}
    break;

  case 183:
#line 1374 "soapcpp2_yacc.y"
    { (yyval.rec).hasval = False; ;}
    break;

  case 184:
#line 1375 "soapcpp2_yacc.y"
    { if ((yyvsp[(2) - (2)].rec).hasval)
			  {	(yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
				(yyval.rec).hasval = True;
				(yyval.rec).val = (yyvsp[(2) - (2)].rec).val;
			  }
			  else
			  {	(yyval.rec).hasval = False;
				semerror("initialization expression not constant");
			  }
			;}
    break;

  case 185:
#line 1386 "soapcpp2_yacc.y"
    { ;}
    break;

  case 186:
#line 1387 "soapcpp2_yacc.y"
    { /* empty for now */ ;}
    break;

  case 187:
#line 1390 "soapcpp2_yacc.y"
    { (yyval.rec).minOccurs = -1;
			  (yyval.rec).maxOccurs = 1;
			  (yyval.rec).pattern = (yyvsp[(1) - (1)].s);
			;}
    break;

  case 188:
#line 1395 "soapcpp2_yacc.y"
    { (yyval.rec).minOccurs = (long)(yyvsp[(2) - (2)].i);
			  (yyval.rec).maxOccurs = 1;
			  (yyval.rec).pattern = (yyvsp[(1) - (2)].s);
			;}
    break;

  case 189:
#line 1400 "soapcpp2_yacc.y"
    { (yyval.rec).minOccurs = (long)(yyvsp[(2) - (3)].i);
			  (yyval.rec).maxOccurs = 1;
			  (yyval.rec).pattern = (yyvsp[(1) - (3)].s);
			;}
    break;

  case 190:
#line 1405 "soapcpp2_yacc.y"
    { (yyval.rec).minOccurs = (long)(yyvsp[(2) - (4)].i);
			  (yyval.rec).maxOccurs = (long)(yyvsp[(4) - (4)].i);
			  (yyval.rec).pattern = (yyvsp[(1) - (4)].s);
			;}
    break;

  case 191:
#line 1410 "soapcpp2_yacc.y"
    { (yyval.rec).minOccurs = -1;
			  (yyval.rec).maxOccurs = (long)(yyvsp[(3) - (3)].i);
			  (yyval.rec).pattern = (yyvsp[(1) - (3)].s);
			;}
    break;

  case 192:
#line 1415 "soapcpp2_yacc.y"
    { (yyval.s) = NULL; ;}
    break;

  case 193:
#line 1416 "soapcpp2_yacc.y"
    { (yyval.s) = (yyvsp[(1) - (1)].s); ;}
    break;

  case 194:
#line 1418 "soapcpp2_yacc.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); ;}
    break;

  case 195:
#line 1419 "soapcpp2_yacc.y"
    { (yyval.i) = (yyvsp[(2) - (2)].i); ;}
    break;

  case 196:
#line 1420 "soapcpp2_yacc.y"
    { (yyval.i) = -(yyvsp[(2) - (2)].i); ;}
    break;

  case 197:
#line 1429 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(3) - (3)].rec); ;}
    break;

  case 198:
#line 1430 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(1) - (1)].rec); ;}
    break;

  case 199:
#line 1434 "soapcpp2_yacc.y"
    { (yyval.rec).typ = (yyvsp[(3) - (5)].rec).typ;
			  (yyval.rec).sto = Snone;
			  (yyval.rec).hasval = False;
			;}
    break;

  case 201:
#line 1441 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(1) - (1)].rec); ;}
    break;

  case 202:
#line 1444 "soapcpp2_yacc.y"
    { (yyval.rec).hasval = False;
			  (yyval.rec).typ = mkint();
			;}
    break;

  case 203:
#line 1447 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(1) - (1)].rec); ;}
    break;

  case 204:
#line 1449 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(1) - (1)].rec); ;}
    break;

  case 205:
#line 1452 "soapcpp2_yacc.y"
    { (yyval.rec).hasval = False;
			  (yyval.rec).typ = mkint();
			;}
    break;

  case 206:
#line 1455 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(1) - (1)].rec); ;}
    break;

  case 207:
#line 1457 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(1) - (1)].rec); ;}
    break;

  case 208:
#line 1460 "soapcpp2_yacc.y"
    { (yyval.rec) = iop("|", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 209:
#line 1461 "soapcpp2_yacc.y"
    { (yyval.rec) = iop("^", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 210:
#line 1462 "soapcpp2_yacc.y"
    { (yyval.rec) = iop("&", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 211:
#line 1463 "soapcpp2_yacc.y"
    { (yyval.rec) = relop("==", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 212:
#line 1464 "soapcpp2_yacc.y"
    { (yyval.rec) = relop("!=", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 213:
#line 1465 "soapcpp2_yacc.y"
    { (yyval.rec) = relop("<", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 214:
#line 1466 "soapcpp2_yacc.y"
    { (yyval.rec) = relop("<=", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 215:
#line 1467 "soapcpp2_yacc.y"
    { (yyval.rec) = relop(">", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 216:
#line 1468 "soapcpp2_yacc.y"
    { (yyval.rec) = relop(">=", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 217:
#line 1469 "soapcpp2_yacc.y"
    { (yyval.rec) = iop("<<", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 218:
#line 1470 "soapcpp2_yacc.y"
    { (yyval.rec) = iop(">>", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 219:
#line 1471 "soapcpp2_yacc.y"
    { (yyval.rec) = op("+", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 220:
#line 1472 "soapcpp2_yacc.y"
    { (yyval.rec) = op("-", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 221:
#line 1473 "soapcpp2_yacc.y"
    { (yyval.rec) = op("*", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 222:
#line 1474 "soapcpp2_yacc.y"
    { (yyval.rec) = op("/", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 223:
#line 1475 "soapcpp2_yacc.y"
    { (yyval.rec) = iop("%", (yyvsp[(1) - (3)].rec), (yyvsp[(3) - (3)].rec)); ;}
    break;

  case 224:
#line 1476 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(1) - (1)].rec); ;}
    break;

  case 225:
#line 1479 "soapcpp2_yacc.y"
    { if ((yyvsp[(2) - (2)].rec).hasval)
				(yyval.rec).val.i = !(yyvsp[(2) - (2)].rec).val.i;
			  (yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
			  (yyval.rec).hasval = (yyvsp[(2) - (2)].rec).hasval;
			;}
    break;

  case 226:
#line 1484 "soapcpp2_yacc.y"
    { if ((yyvsp[(2) - (2)].rec).hasval)
				(yyval.rec).val.i = ~(yyvsp[(2) - (2)].rec).val.i;
			  (yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
			  (yyval.rec).hasval = (yyvsp[(2) - (2)].rec).hasval;
			;}
    break;

  case 227:
#line 1489 "soapcpp2_yacc.y"
    { if ((yyvsp[(2) - (2)].rec).hasval) {
				if (integer((yyvsp[(2) - (2)].rec).typ))
					(yyval.rec).val.i = -(yyvsp[(2) - (2)].rec).val.i;
				else if (real((yyvsp[(2) - (2)].rec).typ))
					(yyval.rec).val.r = -(yyvsp[(2) - (2)].rec).val.r;
				else	typerror("string?");
			  }
			  (yyval.rec).typ = (yyvsp[(2) - (2)].rec).typ;
			  (yyval.rec).hasval = (yyvsp[(2) - (2)].rec).hasval;
			;}
    break;

  case 228:
#line 1499 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(2) - (2)].rec); ;}
    break;

  case 229:
#line 1500 "soapcpp2_yacc.y"
    { if ((yyvsp[(2) - (2)].rec).typ->type == Tpointer) {
			  	(yyval.rec).typ = (Tnode*)(yyvsp[(2) - (2)].rec).typ->ref;
			  } else
			  	typerror("dereference of non-pointer type");
			  (yyval.rec).sto = Snone;
			  (yyval.rec).hasval = False;
			;}
    break;

  case 230:
#line 1507 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkpointer((yyvsp[(2) - (2)].rec).typ);
			  (yyval.rec).sto = Snone;
			  (yyval.rec).hasval = False;
			;}
    break;

  case 231:
#line 1512 "soapcpp2_yacc.y"
    { (yyval.rec).hasval = True;
			  (yyval.rec).typ = mkint();
			  (yyval.rec).val.i = (yyvsp[(3) - (4)].rec).typ->width;
			;}
    break;

  case 232:
#line 1516 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(1) - (1)].rec); ;}
    break;

  case 233:
#line 1519 "soapcpp2_yacc.y"
    { (yyval.rec) = (yyvsp[(2) - (3)].rec); ;}
    break;

  case 234:
#line 1520 "soapcpp2_yacc.y"
    { if ((p = enumentry((yyvsp[(1) - (1)].sym))) == (Entry*) 0)
				p = undefined((yyvsp[(1) - (1)].sym));
			  else
			  	(yyval.rec).hasval = True;
			  (yyval.rec).typ = p->info.typ;
			  (yyval.rec).val = p->info.val;
			;}
    break;

  case 235:
#line 1527 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkint();
			  (yyval.rec).hasval = True;
			  (yyval.rec).val.i = (yyvsp[(1) - (1)].i);
			;}
    break;

  case 236:
#line 1531 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkint();
			  (yyval.rec).hasval = True;
			  (yyval.rec).val.i = 0;
			;}
    break;

  case 237:
#line 1535 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkfloat();
			  (yyval.rec).hasval = True;
			  (yyval.rec).val.r = (yyvsp[(1) - (1)].r);
			;}
    break;

  case 238:
#line 1539 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkchar();
			  (yyval.rec).hasval = True;
			  (yyval.rec).val.i = (yyvsp[(1) - (1)].c);
			;}
    break;

  case 239:
#line 1543 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkstring();
			  (yyval.rec).hasval = True;
			  (yyval.rec).val.s = (yyvsp[(1) - (1)].s);
			;}
    break;

  case 240:
#line 1547 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkbool();
			  (yyval.rec).hasval = True;
			  (yyval.rec).val.i = 0;
			;}
    break;

  case 241:
#line 1551 "soapcpp2_yacc.y"
    { (yyval.rec).typ = mkbool();
			  (yyval.rec).hasval = True;
			  (yyval.rec).val.i = 1;
			;}
    break;


/* Line 1267 of yacc.c.  */
#line 4274 "soapcpp2_yacc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1557 "soapcpp2_yacc.y"


/*
 * ???
 */
int
yywrap()
{	return 1;
}

/******************************************************************************\

	Support routines

\******************************************************************************/

static Node
op(const char *op, Node p, Node q)
{	Node	r;
	Tnode	*typ;
	r.typ = p.typ;
	r.sto = Snone;
	if (p.hasval && q.hasval) {
		if (integer(p.typ) && integer(q.typ))
			switch (op[0]) {
			case '|':	r.val.i = p.val.i |  q.val.i; break;
			case '^':	r.val.i = p.val.i ^  q.val.i; break;
			case '&':	r.val.i = p.val.i &  q.val.i; break;
			case '<':	r.val.i = p.val.i << q.val.i; break;
			case '>':	r.val.i = p.val.i >> q.val.i; break;
			case '+':	r.val.i = p.val.i +  q.val.i; break;
			case '-':	r.val.i = p.val.i -  q.val.i; break;
			case '*':	r.val.i = p.val.i *  q.val.i; break;
			case '/':	r.val.i = p.val.i /  q.val.i; break;
			case '%':	r.val.i = p.val.i %  q.val.i; break;
			default:	typerror(op);
			}
		else if (real(p.typ) && real(q.typ))
			switch (op[0]) {
			case '+':	r.val.r = p.val.r + q.val.r; break;
			case '-':	r.val.r = p.val.r - q.val.r; break;
			case '*':	r.val.r = p.val.r * q.val.r; break;
			case '/':	r.val.r = p.val.r / q.val.r; break;
			default:	typerror(op);
			}
		else	semerror("illegal constant operation");
		r.hasval = True;
	} else {
		typ = mgtype(p.typ, q.typ);
		r.hasval = False;
	}
	return r;
}

static Node
iop(const char *iop, Node p, Node q)
{	if (integer(p.typ) && integer(q.typ))
		return op(iop, p, q);
	typerror("integer operands only");
	return p;
}

static Node
relop(const char *op, Node p, Node q)
{	Node	r;
	Tnode	*typ;
	r.typ = mkint();
	r.sto = Snone;
	r.hasval = False;
	if (p.typ->type != Tpointer || p.typ != q.typ)
		typ = mgtype(p.typ, q.typ);
	return r;
}

/******************************************************************************\

	Scope management

\******************************************************************************/

/*
mkscope - initialize scope stack with a new table and offset
*/
static void
mkscope(Table *table, int offset)
{	sp = stack-1;
	enterscope(table, offset);
}

/*
enterscope - enter a new scope by pushing a new table and offset on the stack
*/
static void
enterscope(Table *table, int offset)
{	if (++sp == stack+MAXNEST)
		execerror("maximum scope depth exceeded");
	sp->table = table;
	sp->val = 0;
	sp->offset = offset;
	sp->grow = True;	/* by default, offset grows */
	sp->mask = False;
}

/*
exitscope - exit a scope by popping the table and offset from the stack
*/
static void
exitscope()
{	check(sp-- != stack, "exitscope() has no matching enterscope()");
}

/******************************************************************************\

	Undefined symbol

\******************************************************************************/

static Entry*
undefined(Symbol *sym)
{	Entry	*p;
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
{	if (numeric(typ1) && numeric(typ2)) {
		if (typ1->type < typ2->type)
			return typ2;
	} else	typerror("non-numeric type");
	return typ1;
}

/******************************************************************************\

	Type checks

\******************************************************************************/

static int
integer(Tnode *typ)
{	switch (typ->type) {
	case Tchar:
	case Tshort:
	case Tint:
	case Tlong:	return True;
	default:	break;
	}
	return False;
}

static int
real(Tnode *typ)
{	switch (typ->type) {
	case Tfloat:
	case Tdouble:
	case Tldouble:	return True;
	default:	break;
	}
	return False;
}

static int
numeric(Tnode *typ)
{	return integer(typ) || real(typ);
}

static void
add_fault(Table *gt)
{ Table *t;
  Entry *p1, *p2, *p3, *p4;
  Symbol *s1, *s2, *s3, *s4;
  imported = NULL;
  s1 = lookup("SOAP_ENV__Code");
  p1 = entry(classtable, s1);
  if (!p1 || !p1->info.typ->ref)
  { t = mktable((Table*)0);
    if (!p1)
    { p1 = enter(classtable, s1);
      p1->info.typ = mkstruct(t, 3*4);
      p1->info.typ->id = s1;
    }
    else
      p1->info.typ->ref = t;
    p2 = enter(t, lookup("SOAP_ENV__Value"));
    p2->info.typ = qname;
    p2->info.minOccurs = 0;
    p2 = enter(t, lookup("SOAP_ENV__Subcode"));
    p2->info.typ = mkpointer(p1->info.typ);
    p2->info.minOccurs = 0;
  }
  s2 = lookup("SOAP_ENV__Detail");
  p2 = entry(classtable, s2);
  if (!p2 || !p2->info.typ->ref)
  { t = mktable((Table*)0);
    if (!p2)
    { p2 = enter(classtable, s2);
      p2->info.typ = mkstruct(t, 3*4);
      p2->info.typ->id = s2;
    }
    else
      p2->info.typ->ref = t;
    p3 = enter(t, lookup("__type"));
    p3->info.typ = mkint();
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("fault"));
    p3->info.typ = mkpointer(mkvoid());
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("__any"));
    p3->info.typ = xml;
    p3->info.minOccurs = 0;
    custom_fault = 0;
  }
  s4 = lookup("SOAP_ENV__Reason");
  p4 = entry(classtable, s4);
  if (!p4 || !p4->info.typ->ref)
  { t = mktable((Table*)0);
    if (!p4)
    { p4 = enter(classtable, s4);
      p4->info.typ = mkstruct(t, 4);
      p4->info.typ->id = s4;
    }
    else
      p4->info.typ->ref = t;
    p3 = enter(t, lookup("SOAP_ENV__Text"));
    p3->info.typ = mkstring();
    p3->info.minOccurs = 0;
  }
  s3 = lookup("SOAP_ENV__Fault");
  p3 = entry(classtable, s3);
  if (!p3 || !p3->info.typ->ref)
  { t = mktable(NULL);
    if (!p3)
    { p3 = enter(classtable, s3);
      p3->info.typ = mkstruct(t, 9*4);
      p3->info.typ->id = s3;
    }
    else
      p3->info.typ->ref = t;
    p3 = enter(t, lookup("faultcode"));
    p3->info.typ = qname;
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("faultstring"));
    p3->info.typ = mkstring();
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("faultactor"));
    p3->info.typ = mkstring();
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("detail"));
    p3->info.typ = mkpointer(p2->info.typ);
    p3->info.minOccurs = 0;
    p3 = enter(t, s1);
    p3->info.typ = mkpointer(p1->info.typ);
    p3->info.minOccurs = 0;
    p3 = enter(t, s4);
    p3->info.typ = mkpointer(p4->info.typ);
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("SOAP_ENV__Node"));
    p3->info.typ = mkstring();
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("SOAP_ENV__Role"));
    p3->info.typ = mkstring();
    p3->info.minOccurs = 0;
    p3 = enter(t, lookup("SOAP_ENV__Detail"));
    p3->info.typ = mkpointer(p2->info.typ);
    p3->info.minOccurs = 0;
  }
}

static void
add_soap()
{ Symbol *s = lookup("soap");
  p = enter(classtable, s);
  p->info.typ = mkstruct(NULL, 0);
  p->info.typ->transient = -2;
  p->info.typ->id = s;
}

static void
add_XML()
{ Symbol *s = lookup("_XML");
  p = enter(typetable, s);
  xml = p->info.typ = mksymtype(mkstring(), s);
  p->info.sto = Stypedef;
}

static void
add_qname()
{ Symbol *s = lookup("_QName");
  p = enter(typetable, s);
  qname = p->info.typ = mksymtype(mkstring(), s);
  p->info.sto = Stypedef;
}

static void
add_header(Table *gt)
{ Table *t;
  Entry *p;
  Symbol *s = lookup("SOAP_ENV__Header");
  imported = NULL;
  p = entry(classtable, s);
  if (!p || !p->info.typ->ref)
  { t = mktable((Table*)0);
    if (!p)
      p = enter(classtable, s);
    p->info.typ = mkstruct(t, 0);
    p->info.typ->id = s;
    custom_header = 0;
  }
}

static void
add_response(Entry *fun, Entry *ret)
{ Table *t;
  Entry *p, *q;
  Symbol *s;
  size_t n = strlen(fun->sym->name);
  char *r = (char*)emalloc(n+9);
  strcpy(r, fun->sym->name);
  strcat(r, "Response");
  if (!(s = lookup(r)))
    s = install(r, ID);
  free(r);
  t = mktable((Table*)0);
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
{ Entry *p;
  if (!typ->ref || !((Tnode*)typ->ref)->ref)
  { semwarn("response struct/class must be declared before used in function prototype");
    return;
  }
  for (p = ((Table*)((Tnode*)typ->ref)->ref)->list; p; p = p->next)
    if (p->info.sto & Sreturn)
      return;
  for (p = ((Table*)((Tnode*)typ->ref)->ref)->list; p; p = p->next)
  { if (p->info.typ->type != Tfun && !(p->info.sto & Sattribute) && !is_transient(p->info.typ) && !(p->info.sto & (Sprivate|Sprotected)))
      p->info.sto = (Storage)((int)p->info.sto | (int)Sreturn);
      return;
  }
}

