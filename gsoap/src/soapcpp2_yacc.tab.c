/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 51 "soapcpp2_yacc.y" /* yacc.c:339  */


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
static void       add_soap(void),
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


#line 164 "soapcpp2_yacc.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "soapcpp2_yacc.tab.h".  */
#ifndef YY_YY_SOAPCPP2_YACC_TAB_H_INCLUDED
# define YY_YY_SOAPCPP2_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    MUTABLE = 313,
    FINAL = 314,
    null = 315,
    RESTRICT = 316,
    OVERRIDE = 317,
    UCHAR = 318,
    USHORT = 319,
    UINT = 320,
    ULONG = 321,
    NONE = 322,
    ID = 323,
    LAB = 324,
    TYPE = 325,
    LNG = 326,
    DBL = 327,
    CHR = 328,
    TAG = 329,
    STR = 330,
    PA = 331,
    NA = 332,
    TA = 333,
    DA = 334,
    MA = 335,
    AA = 336,
    XA = 337,
    OA = 338,
    LA = 339,
    RA = 340,
    OR = 341,
    AN = 342,
    EQ = 343,
    NE = 344,
    LE = 345,
    GE = 346,
    LS = 347,
    RS = 348,
    AR = 349,
    PP = 350,
    NN = 351
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 154 "soapcpp2_yacc.y" /* yacc.c:355  */

  Symbol  *sym;
  LONG64  i;
  double  r;
  char    c;
  char    *s;
  Tnode   *typ;
  Storage sto;
  Node    rec;
  Entry   *e;
  IR      ir;

#line 314 "soapcpp2_yacc.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SOAPCPP2_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 331 "soapcpp2_yacc.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   1766

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  122
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  293
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  452

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   351

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyrline[] =
{
       0,   231,   231,   251,   266,   268,   270,   275,   277,   278,
     279,   280,   281,   291,   300,   304,   306,   308,   310,   312,
     314,   319,   321,   323,   325,   327,   329,   330,   331,   333,
     334,   335,   336,   338,   343,   348,   580,   598,   599,   601,
     602,   603,   604,   605,   606,   607,   608,   609,   610,   611,
     612,   613,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   631,
     632,   633,   634,   635,   636,   637,   638,   650,   661,   689,
     750,   752,   753,   755,   756,   757,   761,   766,   899,   907,
     924,   925,   932,   934,   937,   942,   983,  1035,  1042,  1047,
    1088,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,
    1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
    1159,  1169,  1195,  1222,  1246,  1250,  1268,  1295,  1319,  1340,
    1367,  1392,  1413,  1440,  1467,  1476,  1485,  1499,  1513,  1530,
    1548,  1578,  1645,  1651,  1656,  1660,  1666,  1672,  1678,  1685,
    1710,  1737,  1755,  1774,  1796,  1819,  1824,  1830,  1831,  1832,
    1833,  1834,  1835,  1836,  1846,  1850,  1852,  1853,  1855,  1856,
    1857,  1858,  1867,  1869,  1877,  1886,  1893,  1894,  1896,  1905,
    1906,  1907,  1908,  1909,  1910,  1911,  1912,  1913,  1914,  1915,
    1916,  1917,  1918,  1919,  1924,  1925,  1926,  1928,  1929,  1930,
    1931,  1933,  1934,  1936,  1937,  1939,  1940,  1948,  1953,  1959,
    1960,  1978,  1983,  1998,  1999,  2014,  2018,  2032,  2047,  2048,
    2050,  2063,  2078,  2093,  2116,  2135,  2150,  2167,  2192,  2212,
    2213,  2215,  2216,  2218,  2219,  2220,  2221,  2222,  2224,  2225,
    2226,  2227,  2229,  2230,  2231,  2232,  2233,  2235,  2236,  2237,
    2246,  2247,  2250,  2256,  2259,  2262,  2266,  2268,  2271,  2274,
    2276,  2279,  2280,  2281,  2282,  2283,  2284,  2285,  2286,  2287,
    2288,  2289,  2290,  2291,  2292,  2293,  2294,  2295,  2298,  2304,
    2310,  2323,  2324,  2335,  2340,  2347,  2350,  2351,  2360,  2366,
    2372,  2378,  2384,  2390
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "EXPLICIT", "TYPENAME", "MUTABLE", "FINAL", "null", "RESTRICT",
  "OVERRIDE", "UCHAR", "USHORT", "UINT", "ULONG", "NONE", "ID", "LAB",
  "TYPE", "LNG", "DBL", "CHR", "TAG", "STR", "','", "'='", "PA", "NA",
  "TA", "DA", "MA", "AA", "XA", "OA", "LA", "RA", "'?'", "':'", "OR", "AN",
  "'|'", "'^'", "'&'", "EQ", "NE", "'<'", "LE", "'>'", "GE", "LS", "RS",
  "'+'", "'-'", "'*'", "'/'", "'%'", "AR", "PP", "NN", "'{'", "'}'", "';'",
  "'['", "']'", "')'", "'!'", "'~'", "'('", "'@'", "'$'", "$accept",
  "prog", "s1", "exts", "exts1", "ext", "pragma", "decls", "t1", "t2",
  "t3", "t4", "t5", "dclrs", "dclr", "fdclr", "id", "name", "ctor", "dtor",
  "func", "fname", "fargso", "fargs", "farg", "arg", "texpf", "texp",
  "spec", "tspec", "type", "struct", "class", "enum", "enumsc", "mask",
  "masksc", "sc", "utype", "tname", "base", "s2", "s3", "s4", "s5", "s6",
  "store", "const", "abstract", "virtual", "ptrs", "array", "arrayck",
  "brinit", "init", "tag", "occurs", "bounds", "nullptr", "patt", "value",
  "min", "minmax", "max", "expr", "cexp", "qexp", "oexp", "obex", "aexp",
  "abex", "rexp", "lexp", "pexp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,    44,    61,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,    63,    58,
     341,   342,   124,    94,    38,   343,   344,    60,   345,    62,
     346,   347,   348,    43,    45,    42,    47,    37,   349,   350,
     351,   123,   125,    59,    91,    93,    41,    33,   126,    40,
      64,    36
};
# endif

#define YYPACT_NINF -291

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-291)))

#define YYTABLE_NINF -261

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -291,    26,   -20,  -291,     7,  -291,   236,   -17,   -28,  -291,
    -291,  -291,  -291,    12,  -291,    41,  -291,  -291,  -291,  -291,
    -291,    19,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
      23,   -23,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,    51,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
     -74,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,   -30,
    -291,  -291,     5,  1192,    50,    30,    56,    86,    92,   108,
    1192,   104,  -291,    16,  -291,  -291,  -291,   115,  -291,  -291,
    -291,   119,   132,   -41,   -41,    54,  -291,    66,    66,   133,
    -291,   136,   148,  -291,  -291,    85,  1490,  -291,  -291,  -291,
     129,  -291,  -291,  -291,   105,    77,  -291,   164,  -291,  -291,
      28,  -291,  -291,  -291,  -291,  -291,  -291,   194,  1074,  -291,
    -291,  -291,   835,  -291,  -291,  -291,  -291,   176,   176,  1310,
      90,  -291,  -291,  -291,   835,  -291,  -291,   835,  -291,  -291,
     -41,   167,  -291,  -291,   475,   596,  -291,  -291,  -291,  -291,
     354,    97,  -291,  -291,  -291,  -291,    15,   835,   200,    28,
      28,    28,  -291,   158,   835,  1310,  1310,  1310,  1310,  -291,
    -291,    37,   182,   192,   196,   174,   953,     3,  1310,  -291,
    -291,    33,   217,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
     184,   835,   185,   208,  -291,   107,  -291,  -291,  -291,  1419,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,  -291,   195,  -291,  -291,   193,  -291,  -291,  1591,  -291,
     237,   204,  -291,  -291,  -291,  -291,  -291,   205,   217,   217,
     217,   217,  -291,  -291,  -291,  -291,  -291,   203,   717,   217,
     213,   228,  -291,   230,  -291,   284,   212,  -291,  -291,    67,
     227,  -291,   253,  -291,  -291,  -291,   214,   225,  -291,  -291,
    -291,  -291,  -291,  -291,  -291,  1599,  1599,  1599,  1599,   212,
    1599,  1599,  1599,   233,   -47,   145,   256,   261,  1644,  -291,
    -291,  -291,   293,  -291,   835,  -291,   250,   251,   254,   266,
     717,   717,   717,   717,  -291,   267,  -291,  -291,   -41,  -291,
    1419,    11,  -291,  -291,  1561,     8,  1490,  -291,  -291,  -291,
    -291,  -291,  -291,  -291,   -62,  -291,   212,  1599,  1599,  1599,
    1599,  1599,  1599,  1599,  1599,  1599,  1599,  1599,  1599,  1599,
    1599,  1599,  1599,  1599,  1599,  1599,  -291,    43,   290,   270,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
     268,     1,  -291,  -291,   212,   273,  1599,  -291,  -291,   307,
     297,   256,  1644,  1659,   700,   817,   577,   577,   232,   232,
     232,   232,   322,   322,    52,    52,  -291,  -291,  -291,  1599,
    1599,  1599,  -291,  -291,  -291,   120,  -291,  -291,  -291,  -291,
    -291,   316,  -291,   237,  -291,  -291,  1599,  -291,  -291,   279,
    -291,  -291,  -291,   295,  -291,    91,    91,   -58,    91,  -291,
     131,  -291,  -291,  -291,  -291,  -291,   111,   242,  -291,    91,
    -291,   304,   325,    79,  -291,   482,  -291,   328,  -291,  -291,
    -291,  -291
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     0,     6,     1,     0,     2,     0,     0,     0,    13,
     179,   112,   106,     0,   107,     0,   180,   184,   103,   183,
     192,     0,   186,   111,   105,   114,   113,   101,   195,   181,
       0,   185,   190,   108,   102,   104,   119,   109,   191,   110,
     189,     0,   182,   196,   187,   188,   115,   116,   117,   118,
     140,    21,    22,   193,   194,     7,     9,    10,    11,     0,
      80,    80,   205,     0,     0,   124,     0,     0,     0,     0,
       0,     0,     6,     0,   144,    12,    34,     0,    37,    38,
     173,   128,     0,     0,     0,     0,   173,   138,   139,     0,
     174,   131,     0,   173,   150,     0,     0,   205,     8,    29,
       0,    30,    27,    80,     0,     0,   185,   140,    96,   173,
       0,   173,   173,   173,   175,   175,    95,     0,     0,   142,
     143,   146,     0,   148,   155,   156,   173,   165,   165,     0,
     164,   151,   152,   147,     0,   174,   145,     0,   166,   167,
       0,     0,    90,   205,     0,     0,    31,    80,   178,    28,
       0,   209,   208,   207,   206,    36,     0,     0,     0,     0,
       0,     0,   171,   125,     0,     0,     0,     0,     0,    78,
       4,     0,     0,     0,     0,     0,     0,     0,     0,   153,
     154,     0,   176,   160,   161,   157,   159,   162,   158,   163,
       0,     0,     0,     0,   141,   209,   100,    99,    32,     0,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    73,
      71,    72,     0,    40,    41,     0,    76,   205,     0,   212,
     218,     0,   172,   169,   168,   170,   173,     0,   176,   176,
     176,   176,    20,    23,    24,    25,   126,     0,     0,   176,
     205,     0,   129,     0,   121,     0,   209,   178,    92,     0,
       0,    82,    83,   205,    74,    75,   209,     0,   292,   293,
     287,   288,   289,   290,   291,     0,     0,     0,     0,   209,
       0,     0,     0,     0,   253,     0,   256,     0,   259,   277,
     285,   219,   229,   127,     0,   122,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,   132,   130,     0,    93,
       0,     0,    86,   197,     0,    88,     0,   283,   281,   280,
     282,   211,   278,   279,     0,   251,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   230,   215,   231,     0,
     134,   135,   136,   137,    16,    17,    18,    19,   133,   120,
       0,   201,    84,    89,   209,     0,     0,   286,   210,   254,
       0,   255,   258,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,     0,
       0,     0,    35,   213,   232,   225,   123,    91,   198,   199,
     200,     0,    79,   218,   284,   250,     0,   216,   217,     0,
     234,   233,   235,   247,   249,     0,     0,   238,     0,   202,
     220,   252,   214,   248,   236,   237,   239,   241,   226,     0,
     228,   221,     0,   215,   244,   240,   227,   222,   224,    87,
     245,   223
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -291,  -291,  -291,  -291,   331,  -291,  -291,  -132,    13,   147,
    -291,  -291,  -291,    22,   338,   349,   -15,  -291,  -291,  -291,
     -39,  -291,    94,    98,  -291,  -291,  -291,  -140,   143,   -88,
     -95,  -291,  -291,  -291,  -291,  -291,  -291,   330,   -55,  -291,
     114,   -75,   286,   308,    73,   163,   -92,  -291,  -291,  -291,
    -134,  -192,    68,  -291,     0,    53,  -291,  -291,  -291,  -291,
    -221,  -291,  -291,  -291,  -290,  -231,  -291,  -291,  -291,   127,
    -291,  1380,   271,  -291
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,    55,    56,   175,   176,    58,
     310,   311,   312,   177,   146,   147,    81,   155,    60,    61,
      99,   100,   270,   271,   272,   374,   141,   142,    62,   273,
      63,    64,    65,    66,    67,    68,    69,    88,   131,   140,
     163,   122,   134,   167,   261,   199,    70,   371,   412,    71,
     104,   239,   240,   402,   403,   302,   443,   357,   358,   405,
     427,   438,   439,   428,   334,   335,   380,   294,   295,   296,
     297,   298,   299,   300
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      87,   144,   190,   268,   145,   192,    91,   293,   143,   195,
     236,   129,   119,    77,   376,    94,   119,   119,   137,    57,
      89,   408,   101,    96,    92,   241,     3,    78,    59,    79,
       4,   436,   247,   132,   157,   158,   164,   165,   166,   437,
      73,  -257,    82,  -257,   257,   -77,    97,   379,    83,   144,
     144,   178,   145,   145,   377,   144,   196,   197,   145,   263,
     409,    83,   237,   410,   149,   159,   160,   161,   124,   125,
     127,    74,   179,   180,   319,     7,   373,    84,   411,    97,
      78,   -26,    79,    98,   268,    75,   415,    78,    76,    79,
      84,    78,   -33,    79,    72,  -204,   183,   331,   162,   152,
     184,    73,   153,   276,   144,    73,   185,   145,   198,    78,
     120,    79,   186,   154,   120,   120,   258,   -26,   -26,   110,
     399,   138,    78,    80,    79,   193,   314,   -85,   -33,   -33,
      90,    57,    74,   187,    93,   321,    74,   188,   400,   325,
      59,   111,   139,   322,   378,   156,    85,   150,    95,    76,
     252,   182,    86,    76,   401,   130,   399,   353,   354,   355,
     189,   109,   420,   421,   422,   126,    74,   112,   417,   418,
     419,   304,   359,   151,   400,   266,    74,  -165,   364,   365,
     366,   367,  -242,  -242,  -242,   431,   375,   248,   249,   250,
     251,   420,   421,   422,   425,   426,   152,   113,   152,   153,
     259,   153,   441,   114,   434,   435,   108,   440,   444,   423,
     154,   238,   154,   116,  -242,  -242,   -39,   424,   446,   115,
     442,   238,   117,   425,   426,   144,   267,   121,   145,   144,
    -149,   144,   145,   337,   145,   338,    -5,     8,   237,     9,
      10,    11,    12,    13,   123,   133,    14,   135,   148,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
     136,    96,    26,    27,   169,   130,   194,    28,   242,   246,
      29,   253,    30,   243,   244,   245,    31,    32,   -94,    33,
      34,   254,   266,    35,    36,   255,   256,    37,    38,    39,
      40,    41,    42,   260,    43,    44,   262,   264,    45,    46,
      47,    48,    49,   369,   -94,   152,    50,   265,   153,   275,
     274,   301,   -94,  -246,  -246,  -246,   303,   305,    52,   154,
     318,   306,   307,   308,   309,  -177,   238,   -94,   238,   324,
     -94,   445,   315,   349,   350,   351,   352,   353,   354,   355,
     316,   -94,   317,   323,   326,  -246,  -246,  -260,   336,   -94,
      51,    52,   339,   356,  -203,   105,    53,    54,    10,    11,
      12,    13,   360,   361,    14,   404,   362,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,   363,   368,
      26,    27,   406,   376,   407,    28,   416,   429,    29,   414,
      30,   432,   433,   447,   106,    32,   448,    33,    34,   451,
     102,    35,    36,   118,   313,    37,    38,    39,    40,    41,
      42,   103,    43,    44,   370,   128,    45,    46,    47,    48,
      49,   191,   372,   168,   107,   351,   352,   353,   354,   355,
     320,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   413,   449,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   381,   430,     0,   232,     0,
       0,   233,   234,   235,    53,    54,   105,     0,     0,    10,
      11,    12,    13,     0,     0,    14,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
       0,    26,    27,     0,     0,     0,    28,     0,     0,    29,
       0,    30,     0,     0,     0,   106,    32,     0,    33,    34,
       0,     0,    35,    36,     0,     0,    37,    38,    39,    40,
      41,    42,     0,    43,    44,     0,     0,    45,    46,    47,
      48,    49,     0,   -98,     0,   107,   -98,     0,     0,   -98,
       0,   -98,   -98,  -243,  -243,  -243,   327,   328,   329,   330,
       0,   332,   333,     0,   -98,     0,   -98,     0,     0,   -98,
     -98,     0,     0,     0,   -98,     0,     0,     0,     0,   450,
     -98,     0,     0,     0,     0,  -243,  -243,     0,     0,   -98,
       0,   -98,     0,     0,   -98,    53,    54,   105,     0,     0,
      10,    11,    12,    13,     0,     0,    14,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       0,     0,    26,    27,     0,     0,     0,    28,     0,     0,
      29,     0,    30,     0,     0,     0,   106,    32,     0,    33,
      34,     0,     0,    35,    36,     0,     0,    37,    38,    39,
      40,    41,    42,     0,    43,    44,     0,     0,    45,    46,
      47,    48,    49,     0,   -97,     0,   107,   -97,     0,     0,
     -97,     0,   -97,   -97,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   -97,     0,   -97,     0,     0,
     -97,   -97,     0,     0,     0,   -97,     0,     0,     0,     0,
       0,   -97,     0,     0,     0,     0,     0,     0,     0,     0,
     -97,     0,   -97,     0,     0,   -97,    53,    54,   171,     0,
       0,    10,    11,    12,    13,     0,     0,    14,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     0,     0,    26,    27,     0,     0,     0,    28,     0,
       0,    29,     0,    30,   172,   173,   174,    31,    32,   -94,
      33,    34,     0,     0,    35,    36,     0,     0,    37,    38,
      39,    40,    41,    42,     0,    43,    44,     0,     0,    45,
      46,    47,    48,    49,     0,   -94,     0,    50,     0,     0,
       0,     0,     0,   -94,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   -94,     0,
       0,   -94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -94,     0,     0,     0,     0,     0,     0,   -14,
     -94,    51,   -14,     0,     0,  -203,   171,    53,    54,    10,
      11,    12,    13,     0,     0,    14,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
       0,    26,    27,     0,     0,     0,    28,     0,     0,    29,
       0,    30,   172,   173,   174,    31,    32,   -94,    33,    34,
       0,     0,    35,    36,     0,     0,    37,    38,    39,    40,
      41,    42,     0,    43,    44,     0,     0,    45,    46,    47,
      48,    49,     0,   -94,     0,    50,     0,     0,     0,     0,
       0,   -94,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,     0,   -94,     0,     0,   -94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -94,     0,     0,     0,     0,     0,     0,   -14,   -94,    51,
       0,     0,     0,  -203,   171,    53,    54,    10,    11,    12,
      13,     0,     0,    14,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,     0,    26,
      27,     0,     0,     0,    28,     0,     0,    29,     0,    30,
     172,   173,   174,    31,    32,   -94,    33,    34,     0,     0,
      35,    36,     0,     0,    37,    38,    39,    40,    41,    42,
       0,    43,    44,     0,     0,    45,    46,    47,    48,    49,
       0,   -94,     0,    50,     0,     0,     0,     0,     0,   -94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -94,     0,     0,   -94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -94,     0,
       0,     0,     0,     0,     0,     0,   -94,    51,   -14,     0,
       0,  -203,     0,    53,    54,     8,     0,     9,    10,    11,
      12,    13,     0,     0,    14,     0,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     0,     0,
      26,    27,     0,     0,     0,    28,     0,     0,    29,     0,
      30,     0,     0,     0,    31,    32,   -94,    33,    34,     0,
       0,    35,    36,     0,     0,    37,    38,    39,    40,    41,
      42,     0,    43,    44,     0,     0,    45,    46,    47,    48,
      49,     0,   -94,     0,    50,     0,     0,     0,     0,     0,
     -94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -94,     0,     0,   -94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -94,
       0,     0,     0,     0,     0,     0,   170,   -94,    51,    52,
       0,     0,  -203,   105,    53,    54,    10,    11,    12,    13,
       0,     0,    14,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,     0,    26,    27,
       0,     0,     0,    28,     0,     0,    29,     0,    30,     0,
       0,     0,   106,    32,   -94,    33,    34,     0,     0,    35,
      36,     0,     0,    37,    38,    39,    40,    41,    42,     0,
      43,    44,     0,     0,    45,    46,    47,    48,    49,     0,
     -94,     0,   107,     0,     0,     0,     0,     0,   -94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -94,     0,     0,   -94,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -94,     0,     0,
       0,     0,     0,     0,   -94,   -94,     0,     0,     0,     0,
       0,   181,    53,    54,    10,    11,    12,    13,     0,     0,
      14,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,    26,    27,     0,     0,
       0,    28,     0,     0,    29,     0,    30,     0,     0,     0,
      31,    32,   -94,    33,    34,     0,     0,    35,    36,     0,
       0,    37,    38,    39,    40,    41,    42,     0,    43,    44,
       0,     0,    45,    46,    47,    48,    49,     0,   -94,     0,
      50,     0,     0,     0,     0,     0,   -94,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -94,     0,     0,   -94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -94,     0,     0,     0,     0,
     269,     0,   -94,    10,    11,    12,    13,     0,  -203,    14,
      53,    54,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,     0,     0,    26,    27,     0,     0,     0,
      28,     0,     0,    29,     0,    30,     0,     0,     0,   106,
      32,     0,    33,    34,     0,     0,    35,    36,     0,     0,
      37,    38,    39,    40,    41,    42,     0,    43,    44,     0,
       0,    45,    46,    47,    48,    49,     0,     0,     0,   107,
       0,   105,     0,     0,    10,    11,    12,    13,     0,     0,
      14,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,    26,    27,     0,     0,
       0,    28,     0,     0,    29,     0,    30,     0,     0,     0,
     106,    32,     0,    33,    34,   -81,     0,    35,    36,    53,
      54,    37,    38,    39,    40,    41,    42,     0,    43,    44,
       0,     0,    45,    46,    47,    48,    49,     0,     0,     0,
     107,     0,   269,     0,     0,    10,    11,    12,    13,     0,
       0,    14,     0,     0,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,     0,    26,    27,     0,
       0,     0,    28,     0,     0,    29,     0,    30,     0,     0,
       0,   106,    32,     0,    33,    34,     0,     0,    35,    36,
      53,    54,    37,    38,    39,    40,    41,    42,     0,    43,
      44,   277,     0,    45,    46,    47,    48,    49,     0,   277,
       0,   107,     0,     0,     0,     0,   278,   279,     0,     0,
       0,     0,     0,     0,   278,   279,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   280,
       0,     0,   281,   282,   283,     0,   284,   280,     0,     0,
     281,   282,   283,     0,   284,     0,     0,     0,     0,     0,
       0,    53,    54,     0,     0,   285,     0,     0,     0,     0,
       0,     0,     0,   285,   286,   287,   288,     0,     0,     0,
       0,     0,   286,   287,   288,     0,   289,     0,   290,   291,
     292,     0,     0,     0,     0,     0,   290,   291,   292,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355
};

static const yytype_int16 yycheck[] =
{
      15,    96,   134,   195,    96,   137,    21,   238,    96,   143,
     150,    86,     1,     1,    76,    30,     1,     1,    93,     6,
       1,    20,    61,    97,     1,   157,     0,    68,     6,    70,
      50,    89,   164,    88,   109,     7,   111,   112,   113,    97,
      68,    88,     1,    90,   176,   119,    76,   337,     7,   144,
     145,   126,   144,   145,   116,   150,   144,   145,   150,   191,
      59,     7,   150,    62,   103,    37,    38,    39,    83,    84,
      85,    99,   127,   128,   266,    68,    68,    36,    77,    76,
      68,    76,    70,   113,   276,   113,   376,    68,   116,    70,
      36,    68,    76,    70,   111,   118,     6,   289,    70,    91,
      10,    68,    94,   237,   199,    68,    16,   199,   147,    68,
      99,    70,    22,   105,    99,    99,   113,   112,   113,    89,
      77,    36,    68,   111,    70,   140,   258,   116,   112,   113,
     111,   118,    99,    43,   111,    68,    99,    47,    95,   273,
     118,   111,    57,    76,   336,    68,   105,    42,    97,   116,
     113,   129,   111,   116,   111,    89,    77,   105,   106,   107,
      70,   111,    71,    72,    73,   111,    99,   111,   399,   400,
     401,   246,   304,    68,    95,    68,    99,   111,   310,   311,
     312,   313,    71,    72,    73,   416,   326,   165,   166,   167,
     168,    71,    72,    73,   103,   104,    91,   111,    91,    94,
     178,    94,    71,   111,   425,   426,    63,   428,    97,    89,
     105,   114,   105,    70,   103,   104,   119,    97,   439,   111,
      89,   114,   118,   103,   104,   320,   119,   112,   320,   324,
     111,   326,   324,    88,   326,    90,     0,     1,   326,     3,
       4,     5,     6,     7,   112,   112,    10,   111,   119,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     112,    97,    26,    27,    70,    89,    99,    31,    68,   111,
      34,    89,    36,   159,   160,   161,    40,    41,    42,    43,
      44,    89,    68,    47,    48,    89,   112,    51,    52,    53,
      54,    55,    56,    76,    58,    59,   112,   112,    62,    63,
      64,    65,    66,   318,    68,    91,    70,    99,    94,   116,
     115,    74,    76,    71,    72,    73,   112,   112,   115,   105,
      36,   248,   249,   250,   251,   112,   114,    91,   114,    76,
      94,    89,   259,   101,   102,   103,   104,   105,   106,   107,
     112,   105,   112,   116,   119,   103,   104,    91,   115,   113,
     114,   115,    91,    60,   118,     1,   120,   121,     4,     5,
       6,     7,   112,   112,    10,    75,   112,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,   112,   112,
      26,    27,   112,    76,   116,    31,    89,    71,    34,   116,
      36,   112,    97,    89,    40,    41,    71,    43,    44,    71,
      62,    47,    48,    72,   257,    51,    52,    53,    54,    55,
      56,    62,    58,    59,   320,    85,    62,    63,    64,    65,
      66,   135,   324,   115,    70,   103,   104,   105,   106,   107,
     267,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,   374,   443,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   338,   413,    -1,   114,    -1,
      -1,   117,   118,   119,   120,   121,     1,    -1,    -1,     4,
       5,     6,     7,    -1,    -1,    10,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    36,    -1,    -1,    -1,    40,    41,    -1,    43,    44,
      -1,    -1,    47,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    68,    -1,    70,    71,    -1,    -1,    74,
      -1,    76,    77,    71,    72,    73,   285,   286,   287,   288,
      -1,   290,   291,    -1,    89,    -1,    91,    -1,    -1,    94,
      95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    97,
     105,    -1,    -1,    -1,    -1,   103,   104,    -1,    -1,   114,
      -1,   116,    -1,    -1,   119,   120,   121,     1,    -1,    -1,
       4,     5,     6,     7,    -1,    -1,    10,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,
      34,    -1,    36,    -1,    -1,    -1,    40,    41,    -1,    43,
      44,    -1,    -1,    47,    48,    -1,    -1,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    68,    -1,    70,    71,    -1,    -1,
      74,    -1,    76,    77,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,    89,    -1,    91,    -1,    -1,
      94,    95,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     114,    -1,   116,    -1,    -1,   119,   120,   121,     1,    -1,
      -1,     4,     5,     6,     7,    -1,    -1,    10,    -1,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,    -1,
      -1,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    -1,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    68,    -1,    70,    -1,    -1,
      -1,    -1,    -1,    76,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,    91,    -1,
      -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,
     113,   114,   115,    -1,    -1,   118,     1,   120,   121,     4,
       5,     6,     7,    -1,    -1,    10,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    68,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    76,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,    -1,    91,    -1,    -1,    94,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,
      -1,    -1,    -1,   118,     1,   120,   121,     4,     5,     6,
       7,    -1,    -1,    10,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    26,
      27,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      47,    48,    -1,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    68,    -1,    70,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    -1,    -1,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,    -1,
      -1,   118,    -1,   120,   121,     1,    -1,     3,     4,     5,
       6,     7,    -1,    -1,    10,    -1,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      26,    27,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,
      36,    -1,    -1,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    -1,    -1,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    68,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,   115,
      -1,    -1,   118,     1,   120,   121,     4,     5,     6,     7,
      -1,    -1,    10,    -1,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    36,    -1,
      -1,    -1,    40,    41,    42,    43,    44,    -1,    -1,    47,
      48,    -1,    -1,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      68,    -1,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    94,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,   112,   113,    -1,    -1,    -1,    -1,
      -1,     1,   120,   121,     4,     5,     6,     7,    -1,    -1,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    26,    27,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    -1,
      -1,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      -1,    -1,    62,    63,    64,    65,    66,    -1,    68,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,
       1,    -1,   112,     4,     5,     6,     7,    -1,   118,    10,
     120,   121,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    26,    27,    -1,    -1,    -1,
      31,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,    40,
      41,    -1,    43,    44,    -1,    -1,    47,    48,    -1,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    -1,
      -1,    62,    63,    64,    65,    66,    -1,    -1,    -1,    70,
      -1,     1,    -1,    -1,     4,     5,     6,     7,    -1,    -1,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    26,    27,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      40,    41,    -1,    43,    44,   116,    -1,    47,    48,   120,
     121,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    -1,     1,    -1,    -1,     4,     5,     6,     7,    -1,
      -1,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    -1,    26,    27,    -1,
      -1,    -1,    31,    -1,    -1,    34,    -1,    36,    -1,    -1,
      -1,    40,    41,    -1,    43,    44,    -1,    -1,    47,    48,
     120,   121,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    30,    -1,    62,    63,    64,    65,    66,    -1,    30,
      -1,    70,    -1,    -1,    -1,    -1,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    71,    72,    73,    -1,    75,    68,    -1,    -1,
      71,    72,    73,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,    -1,    -1,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    94,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,    -1,   115,    -1,   117,   118,
     119,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   123,   124,     0,    50,   125,   126,    68,     1,     3,
       4,     5,     6,     7,    10,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    26,    27,    31,    34,
      36,    40,    41,    43,    44,    47,    48,    51,    52,    53,
      54,    55,    56,    58,    59,    62,    63,    64,    65,    66,
      70,   114,   115,   120,   121,   127,   128,   130,   131,   135,
     140,   141,   150,   152,   153,   154,   155,   156,   157,   158,
     168,   171,   111,    68,    99,   113,   116,     1,    68,    70,
     111,   138,     1,     7,    36,   105,   111,   138,   159,     1,
     111,   138,     1,   111,   138,    97,    97,    76,   113,   142,
     143,   142,   136,   137,   172,     1,    40,    70,   150,   111,
      89,   111,   111,   111,   111,   111,   150,   118,   126,     1,
      99,   112,   163,   112,   138,   138,   111,   138,   159,   163,
      89,   160,   160,   112,   164,   111,   112,   163,    36,    57,
     161,   148,   149,   151,   152,   168,   136,   137,   119,   142,
      42,    68,    91,    94,   105,   139,    68,   163,     7,    37,
      38,    39,    70,   162,   163,   163,   163,   165,   165,    70,
     112,     1,    37,    38,    39,   129,   130,   135,   163,   160,
     160,     1,   135,     6,    10,    16,    22,    43,    47,    70,
     129,   164,   129,   138,    99,   172,   151,   151,   142,   167,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   114,   117,   118,   119,   149,   151,   114,   173,
     174,   129,    68,   162,   162,   162,   111,   129,   135,   135,
     135,   135,   113,    89,    89,    89,   112,   129,   113,   135,
      76,   166,   112,   129,   112,    99,    68,   119,   173,     1,
     144,   145,   146,   151,   115,   116,   172,    30,    45,    46,
      68,    71,    72,    73,    75,    94,   103,   104,   105,   115,
     117,   118,   119,   187,   189,   190,   191,   192,   193,   194,
     195,    74,   177,   112,   163,   112,   166,   166,   166,   166,
     132,   133,   134,   131,   129,   166,   112,   112,    36,   173,
     167,    68,    76,   116,    76,   172,   119,   194,   194,   194,
     194,   173,   194,   194,   186,   187,   115,    88,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,    60,   179,   180,   129,
     112,   112,   112,   112,   129,   129,   129,   129,   112,   138,
     144,   169,   145,    68,   147,   149,    76,   116,   173,   186,
     188,   191,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,    77,
      95,   111,   175,   176,    75,   181,   112,   116,    20,    59,
      62,    77,   170,   174,   116,   186,    89,   187,   187,   187,
      71,    72,    73,    89,    97,   103,   104,   182,   185,    71,
     177,   187,   112,    97,   182,   182,    89,    97,   183,   184,
     182,    71,    89,   178,    97,    89,   182,    89,    71,   176,
      97,    71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   122,   123,   124,   125,   125,   126,   126,   127,   127,
     127,   127,   127,   128,   129,   129,   129,   129,   129,   129,
     129,   130,   131,   132,   133,   134,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   136,   137,   138,   138,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   140,   141,   142,
     143,   144,   144,   145,   145,   145,   145,   146,   147,   147,
     148,   148,   149,   149,   150,   150,   150,   151,   151,   151,
     151,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   153,
     154,   155,   156,   157,   158,   159,   159,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   161,   161,   162,   162,
     162,   162,   162,   163,   164,   165,   166,   166,   167,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   169,   169,   169,
     169,   170,   170,   171,   171,   172,   172,   172,   172,   173,
     173,   173,   174,   175,   175,   176,   176,   176,   177,   177,
     178,   178,   178,   178,   178,   179,   179,   179,   179,   180,
     180,   181,   181,   182,   182,   182,   182,   182,   183,   183,
     183,   183,   184,   184,   184,   184,   184,   185,   185,   185,
     186,   186,   187,   187,   188,   189,   189,   190,   191,   191,
     192,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   194,   194,
     194,   194,   194,   194,   194,   194,   195,   195,   195,   195,
     195,   195,   195,   195
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     5,     1,     0,     2,     2,     1,
       1,     1,     2,     1,     0,     3,     4,     4,     4,     4,
       2,     1,     1,     0,     0,     0,     1,     2,     3,     2,
       2,     3,     4,     2,     2,     6,     2,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     3,     2,     1,     3,     7,
       0,     0,     1,     1,     3,     2,     2,     7,     0,     1,
       1,     6,     3,     4,     0,     2,     2,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       7,     5,     5,     7,     1,     3,     5,     5,     2,     5,
       6,     2,     6,     7,     6,     6,     6,     6,     2,     2,
       1,     4,     3,     3,     2,     3,     3,     3,     3,     2,
       2,     3,     3,     4,     4,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     0,     1,     1,     2,     2,
       2,     1,     2,     0,     0,     0,     0,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     2,     2,
       2,     0,     2,     0,     1,     0,     2,     2,     2,     0,
       4,     3,     1,     1,     3,     0,     2,     2,     0,     1,
       0,     1,     2,     3,     2,     2,     4,     5,     4,     0,
       1,     0,     1,     1,     1,     1,     2,     2,     0,     1,
       2,     1,     1,     2,     2,     3,     1,     1,     2,     1,
       3,     1,     5,     1,     1,     3,     1,     1,     3,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     2,     2,
       2,     2,     2,     2,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 231 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 2047 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 3:
#line 251 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 2066 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 4:
#line 267 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { set_namespace((yyvsp[-3].sym)->name); }
#line 2072 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 5:
#line 268 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2078 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 6:
#line 270 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          add_soap();
                          add_XML();
                          add_qname();
                        }
#line 2088 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 7:
#line 275 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2094 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 8:
#line 277 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2100 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 9:
#line 278 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2106 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 10:
#line 279 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2112 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 11:
#line 280 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2118 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 12:
#line 281 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          synerror("input before ; skipped");
                          while (sp > stack)
                          {
                            freetable(sp->table);
                            exitscope();
                          }
                          yyerrok;
                        }
#line 2132 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 13:
#line 291 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { add_pragma((yyvsp[0].s)); }
#line 2138 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 14:
#line 300 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          transient &= ~6;
                          permission = 0;
                        }
#line 2147 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 15:
#line 305 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2153 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 16:
#line 307 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2159 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 17:
#line 309 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2165 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 18:
#line 311 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2171 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 19:
#line 313 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2177 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 20:
#line 314 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          synerror("declaration expected");
                          yyerrok;
                        }
#line 2186 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 21:
#line 319 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { transient |= 1; }
#line 2192 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 22:
#line 321 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { transient &= ~1; }
#line 2198 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 23:
#line 323 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { permission = (int)Sprivate; }
#line 2204 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 24:
#line 325 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { permission = (int)Sprotected; }
#line 2210 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 25:
#line 327 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { permission = 0; }
#line 2216 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 26:
#line 329 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2222 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 27:
#line 330 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2228 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 28:
#line 332 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2234 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 29:
#line 333 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2240 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 30:
#line 334 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2246 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 31:
#line 335 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2252 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 32:
#line 337 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2258 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 33:
#line 338 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          sprintf(errbuf, "undefined type in declaration of '%s'", (yyvsp[0].sym)->name);
                          synerror(errbuf);
                          yyerrok;
                        }
#line 2268 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 34:
#line 343 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          synerror("function declaration?");
                          yyerrok;
                        }
#line 2277 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 35:
#line 349 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
                                p->info.typ->transient = -3; /* extern and volatile */
                              else
                                p->info.typ->transient = (yyvsp[-3].rec).typ->transient;
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
                            (yyvsp[-4].sym)->token = TYPE;
                          }
                          else
                          {
                            p = enter(sp->table, (yyvsp[-4].sym));
                            p->tag = (yyvsp[-2].s);
                            p->info.typ = (yyvsp[-3].rec).typ;
                            p->info.sto = (Storage)((int)(yyvsp[-3].rec).sto | permission);
                            if ((yyvsp[0].rec).hasval)
                            {
                              Tnode *t = (yyvsp[-3].rec).typ;
                              p->info.hasval = True;
                              p->info.ptrval = False;
                              p->info.fixed = (yyvsp[0].rec).fixed;
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
                                  if ((yyvsp[0].rec).typ->type == Tint ||
                                      (yyvsp[0].rec).typ->type == Tchar ||
                                      (yyvsp[0].rec).typ->type == Tenum ||
                                      (yyvsp[0].rec).typ->type == Tenumsc)
                                  {
                                    sp->val = p->info.val.i = (yyvsp[0].rec).val.i;
                                    if ((t->hasmin && t->imin > (yyvsp[0].rec).val.i) ||
                                        (t->hasmin && !t->incmin && t->imin == (yyvsp[0].rec).val.i) ||
                                        (t->hasmax && t->imax < (yyvsp[0].rec).val.i) ||
                                        (t->hasmax && !t->incmax && t->imax == (yyvsp[0].rec).val.i))
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
                                  if ((yyvsp[0].rec).typ->type == Tfloat ||
                                      (yyvsp[0].rec).typ->type == Tdouble ||
                                      (yyvsp[0].rec).typ->type == Tldouble)
                                  {
                                    p->info.val.r = (yyvsp[0].rec).val.r;
                                    if ((t->hasmin && t->rmin > (yyvsp[0].rec).val.r) ||
                                        (t->hasmin && !t->incmin && t->rmin == (yyvsp[0].rec).val.r) ||
                                        (t->hasmax && t->rmax < (yyvsp[0].rec).val.r) ||
                                        (t->hasmax && !t->incmax && t->rmax == (yyvsp[0].rec).val.r))
                                      semerror("initialization constant outside value range");
                                  }
                                  else if ((yyvsp[0].rec).typ->type == Tint)
                                  {
                                    p->info.val.r = (double)(yyvsp[0].rec).val.i;
                                    if ((t->hasmin && t->imin > (yyvsp[0].rec).val.i) ||
                                        (t->hasmin && !t->incmin && t->imin == (yyvsp[0].rec).val.i) ||
                                        (t->hasmax && t->imax < (yyvsp[0].rec).val.i) ||
                                        (t->hasmax && !t->incmax && t->imax == (yyvsp[0].rec).val.i))
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
                                      (yyvsp[0].rec).typ->type == Tpointer &&
                                      ((Tnode*)(yyvsp[0].rec).typ->ref)->type == Tchar)
                                    p->info.val.s = (yyvsp[0].rec).val.s;
                                  else if (bflag &&
                                      t->type == Tarray &&
                                      ((Tnode*)t->ref)->type == Tchar &&
                                      (yyvsp[0].rec).typ->type == Tpointer &&
                                      ((Tnode*)(yyvsp[0].rec).typ->ref)->type == Tchar)
                                  {
                                    if (t->width / ((Tnode*)t->ref)->width - 1 < (int)strlen((yyvsp[0].rec).val.s))
                                    {
                                      semerror("char[] initialization constant too long");
                                      p->info.val.s = "";
                                    }
                                    else
                                    {
                                      p->info.val.s = (yyvsp[0].rec).val.s;
                                    }

                                  }
                                  else if (t->id == lookup("std::string") ||
                                      t->id == lookup("std::wstring"))
                                  {
                                    p->info.val.s = (yyvsp[0].rec).val.s;
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
                            else
                            {
                              p->info.val.i = sp->val;
                            }
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
#line 2512 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 36:
#line 580 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 2534 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 37:
#line 598 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 2540 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 38:
#line 599 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 2546 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 39:
#line 601 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 2552 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 40:
#line 602 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator!"); }
#line 2558 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 41:
#line 603 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator~"); }
#line 2564 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 42:
#line 604 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator="); }
#line 2570 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 43:
#line 605 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator+="); }
#line 2576 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 44:
#line 606 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator-="); }
#line 2582 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 45:
#line 607 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator*="); }
#line 2588 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 46:
#line 608 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator/="); }
#line 2594 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 47:
#line 609 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator%="); }
#line 2600 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 48:
#line 610 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator&="); }
#line 2606 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 49:
#line 611 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator^="); }
#line 2612 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 50:
#line 612 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator|="); }
#line 2618 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 51:
#line 613 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator<<="); }
#line 2624 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 52:
#line 614 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator>>="); }
#line 2630 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 53:
#line 615 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator||"); }
#line 2636 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 54:
#line 616 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator&&"); }
#line 2642 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 55:
#line 617 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator|"); }
#line 2648 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 56:
#line 618 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator^"); }
#line 2654 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 57:
#line 619 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator&"); }
#line 2660 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 58:
#line 620 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator=="); }
#line 2666 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 59:
#line 621 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator!="); }
#line 2672 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 60:
#line 622 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator<"); }
#line 2678 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 61:
#line 623 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator<="); }
#line 2684 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 62:
#line 624 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator>"); }
#line 2690 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 63:
#line 625 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator>="); }
#line 2696 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 64:
#line 626 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator<<"); }
#line 2702 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 65:
#line 627 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator>>"); }
#line 2708 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 66:
#line 628 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator+"); }
#line 2714 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 67:
#line 629 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator-"); }
#line 2720 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 68:
#line 630 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator*"); }
#line 2726 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 69:
#line 631 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator/"); }
#line 2732 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 70:
#line 632 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator%"); }
#line 2738 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 71:
#line 633 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator++"); }
#line 2744 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 72:
#line 634 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator--"); }
#line 2750 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 73:
#line 635 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator->"); }
#line 2756 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 74:
#line 636 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator[]"); }
#line 2762 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 75:
#line 637 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sym) = lookup("operator()"); }
#line 2768 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 76:
#line 638 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 2784 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 77:
#line 650 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (!(p = entry(classtable, (yyvsp[0].sym))))
                            semerror("invalid constructor");
                          sp->entry = enter(sp->table, (yyvsp[0].sym));
                          sp->entry->info.typ = mknone();
                          sp->entry->info.sto = Snone;
                          sp->entry->info.offset = sp->offset;
                          sp->node.typ = mkvoid();
                          sp->node.sto = Snone;
                        }
#line 2799 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 78:
#line 662 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (!(p = entry(classtable, (yyvsp[0].sym))))
                                semerror("invalid destructor");
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
                          sp->node.typ = mkvoid();
                          sp->node.sto = Snone;
                        }
#line 2830 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 79:
#line 690 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 2894 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 80:
#line 750 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.e) = sp->entry; }
#line 2900 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 81:
#line 752 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2906 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 82:
#line 753 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2912 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 83:
#line 755 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2918 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 84:
#line 756 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 2924 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 85:
#line 757 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          sprintf(errbuf, "undefined '%s'", (yyvsp[0].sym)->name);
                          synerror(errbuf);
                        }
#line 2933 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 86:
#line 761 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          synerror("formal argument expected");
                          yyerrok;
                        }
#line 2942 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 87:
#line 767 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (((int)(yyvsp[-3].rec).sto & (int)Stypedef))
                            semwarn("typedef in function argument");
                          p = enter(sp->table, (yyvsp[-4].sym));
                          p->info.typ = (yyvsp[-3].rec).typ;
                          p->info.sto = (yyvsp[-3].rec).sto;
			  p->tag = (yyvsp[-2].s);
                          if ((yyvsp[-1].rec).minOccurs < 0)
                          {
                            if ((yyvsp[-1].rec).hasval ||
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
                          if ((yyvsp[0].rec).hasval)
                          {
                            Tnode *t = (yyvsp[-3].rec).typ;
                            p->info.hasval = True;
                            p->info.ptrval = False;
                            p->info.fixed = (yyvsp[0].rec).fixed;
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
                              case Tenum:
                              case Tenumsc:
                              case Ttime:
                                if ((yyvsp[0].rec).typ->type == Tint ||
                                    (yyvsp[0].rec).typ->type == Tchar ||
                                    (yyvsp[0].rec).typ->type == Tenum ||
                                    (yyvsp[0].rec).typ->type == Tenumsc)
                                {
                                  sp->val = p->info.val.i = (yyvsp[0].rec).val.i;
                                  if ((t->hasmin && t->imin > (yyvsp[0].rec).val.i) ||
                                      (t->hasmin && !t->incmin && t->imin == (yyvsp[0].rec).val.i) ||
                                      (t->hasmax && t->imax < (yyvsp[0].rec).val.i) ||
                                      (t->hasmax && !t->incmax && t->imax == (yyvsp[0].rec).val.i))
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
                                if ((yyvsp[0].rec).typ->type == Tfloat ||
                                    (yyvsp[0].rec).typ->type == Tdouble ||
                                    (yyvsp[0].rec).typ->type == Tldouble)
                                {
                                  p->info.val.r = (yyvsp[0].rec).val.r;
                                  if ((t->hasmin && t->rmin > (yyvsp[0].rec).val.r) ||
                                      (t->hasmin && !t->incmin && t->rmin == (yyvsp[0].rec).val.r) ||
                                      (t->hasmax && t->rmax < (yyvsp[0].rec).val.r) ||
                                      (t->hasmax && !t->incmax && t->rmax == (yyvsp[0].rec).val.r))
                                    semerror("initialization constant outside value range");
                                }
                                else if ((yyvsp[0].rec).typ->type == Tint)
                                {
                                  p->info.val.r = (double)(yyvsp[0].rec).val.i;
                                  if ((t->hasmin && t->imin > (yyvsp[0].rec).val.i) ||
                                      (t->hasmin && !t->incmin && t->imin == (yyvsp[0].rec).val.i) ||
                                      (t->hasmax && t->imax < (yyvsp[0].rec).val.i) ||
                                      (t->hasmax && !t->incmax && t->imax == (yyvsp[0].rec).val.i))
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
                                    (yyvsp[0].rec).typ->type == Tpointer &&
                                    ((Tnode*)(yyvsp[0].rec).typ->ref)->type == Tchar)
                                {
                                  p->info.val.s = (yyvsp[0].rec).val.s;
                                }
                                else if (t->id == lookup("std::string") ||
                                    t->id == lookup("std::wstring"))
                                {
                                  p->info.val.s = (yyvsp[0].rec).val.s;
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
                          p->info.offset = sp->offset;
                          if (((int)(yyvsp[-3].rec).sto & (int)Sextern))
                            p->level = GLOBAL;
                          else if (sp->grow)
                            sp->offset += p->info.typ->width;
                          else if (p->info.typ->width > sp->offset)
                            sp->offset = p->info.typ->width;
                          sp->entry = p;
                        }
#line 3078 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 88:
#line 899 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (sp->table->level != PARAM)
                            (yyval.sym) = gensymidx("param", (int)++sp->val);
                          else if (eflag || zflag == 0 || zflag > 3)
                            (yyval.sym) = gensymidx("_param", (int)++sp->val);
                          else
                            (yyval.sym) = gensym("_param");
                        }
#line 3091 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 89:
#line 907 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (soap_version == 2 && *(yyvsp[0].sym)->name == '_' && sp->table->level == GLOBAL)
                          {
                            sprintf(errbuf, "SOAP 1.2 does not support anonymous parameters '%s'", (yyvsp[0].sym)->name);
                            semwarn(errbuf);
                          }
                          (yyval.sym) = (yyvsp[0].sym);
                        }
#line 3104 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 90:
#line 924 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 3110 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 91:
#line 926 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkmethod(tmp.typ, sp->table);
                          transient &= ~1;
                          exitscope();
                        }
#line 3120 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 92:
#line 933 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 3126 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 93:
#line 935 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 3132 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 94:
#line 937 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkint();
                          (yyval.rec).sto = Snone;
                          sp->node = (yyval.rec);
                        }
#line 3142 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 95:
#line 942 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3188 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 96:
#line 983 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3244 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 97:
#line 1035 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkint();
                          (yyval.rec).sto = (yyvsp[0].sto);
                          sp->node = (yyval.rec);
                          if (((int)(yyvsp[0].sto) & (int)Sextern))
                            transient = 0;
                        }
#line 3256 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 98:
#line 1042 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = (yyvsp[0].typ);
                          (yyval.rec).sto = Snone;
                          sp->node = (yyval.rec);
                        }
#line 3266 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 99:
#line 1047 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3312 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 100:
#line 1088 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3368 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 101:
#line 1140 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkvoid(); }
#line 3374 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 102:
#line 1141 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkbool(); }
#line 3380 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 103:
#line 1142 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkchar(); }
#line 3386 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 104:
#line 1143 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkwchart(); }
#line 3392 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 105:
#line 1144 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkshort(); }
#line 3398 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 106:
#line 1145 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkint(); }
#line 3404 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 107:
#line 1146 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mklong(); }
#line 3410 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 108:
#line 1147 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkllong(); }
#line 3416 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 109:
#line 1148 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkullong(); }
#line 3422 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 110:
#line 1149 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mksize(); }
#line 3428 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 111:
#line 1150 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkfloat(); }
#line 3434 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 112:
#line 1151 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkdouble(); }
#line 3440 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 113:
#line 1152 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkint(); }
#line 3446 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 114:
#line 1153 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkuint(); }
#line 3452 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 115:
#line 1154 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkuchar(); }
#line 3458 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 116:
#line 1155 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkushort(); }
#line 3464 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 117:
#line 1156 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkuint(); }
#line 3470 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 118:
#line 1157 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mkulong(); }
#line 3476 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 119:
#line 1158 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.typ) = mktimet(); }
#line 3482 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 120:
#line 1160 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (!(p = entry(templatetable, (yyvsp[0].sym))))
                          {
                            p = enter(templatetable, (yyvsp[0].sym));
                            p->info.typ = mktemplate(NULL, (yyvsp[0].sym));
                            (yyvsp[0].sym)->token = TYPE;
                          }
                          (yyval.typ) = p->info.typ;
                        }
#line 3496 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 121:
#line 1170 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3526 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 122:
#line 1196 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if ((p = entry(classtable, (yyvsp[-4].e)->sym)) && p->info.typ->ref)
                          {
                            if (is_mutable(p))
                            {
                              if (merge((Table*)p->info.typ->ref, sp->table))
                              {
                                sprintf(errbuf, "member name clash in class '%s' declared at line %d", (yyvsp[-4].e)->sym->name, p->lineno);
                                semerror(errbuf);
                              }
                              p->info.typ->width += sp->offset;
                            }
                          }
                          else
                          {
                            p = reenter(classtable, (yyvsp[-4].e)->sym);
                            sp->table->sym = p->sym;
                            p->info.typ->ref = sp->table;
                            p->info.typ->width = sp->offset;
                            p->info.typ->id = p->sym;
                            if (p->info.typ->base)
                              sp->table->prev = (Table*)entry(classtable, p->info.typ->base)->info.typ->ref;
                          }
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3557 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 123:
#line 1223 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          p = reenter(classtable, (yyvsp[-6].e)->sym);
                          sp->table->sym = p->sym;
                          if (!(yyvsp[-4].e))
                          {
                            semerror("invalid base class");
                          }
                          else
                          {
                            sp->table->prev = (Table*)(yyvsp[-4].e)->info.typ->ref;
                            if (!sp->table->prev && !(yyvsp[-4].e)->info.typ->transient)
                            {
                              sprintf(errbuf, "class '%s' has incomplete type (if this class is not serializable then declare 'extern class %s')'", (yyvsp[-4].e)->sym->name, (yyvsp[-4].e)->sym->name);
                              semerror(errbuf);
                            }
                            p->info.typ->base = (yyvsp[-4].e)->info.typ->id;
                          }
                          p->info.typ->ref = sp->table;
                          p->info.typ->width = sp->offset;
                          p->info.typ->id = p->sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3585 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 124:
#line 1246 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyvsp[0].e)->info.typ->id = (yyvsp[0].e)->sym;
                          (yyval.typ) = (yyvsp[0].e)->info.typ;
                        }
#line 3594 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 125:
#line 1251 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (!(yyvsp[0].e))
                          {
                            semerror("invalid base class");
                          }
                          else
                          {
                            if (!(yyvsp[0].e)->info.typ->ref && !(yyvsp[0].e)->info.typ->transient)
                            {
                              sprintf(errbuf, "class '%s' has incomplete type (if this class is not serializable then declare 'extern class %s')'", (yyvsp[0].e)->sym->name, (yyvsp[0].e)->sym->name);
                              semerror(errbuf);
                            }
                            (yyvsp[-2].e)->info.typ->base = (yyvsp[0].e)->info.typ->id;
                          }
                          (yyvsp[-2].e)->info.typ->id = (yyvsp[-2].e)->sym;
                          (yyval.typ) = (yyvsp[-2].e)->info.typ;
                        }
#line 3616 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 126:
#line 1269 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
                          p->info.typ->id = sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3647 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 127:
#line 1296 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if ((p = entry(classtable, (yyvsp[-4].e)->sym)) && p->info.typ->ref)
                          {
                            if (is_mutable(p))
                            {
                              if (merge((Table*)p->info.typ->ref, sp->table))
                              {
                                sprintf(errbuf, "member name clash in struct '%s' declared at line %d", (yyvsp[-4].e)->sym->name, p->lineno);
                                semerror(errbuf);
                              }
                              p->info.typ->width += sp->offset;
                            }
                          }
                          else
                          {
                            p = reenter(classtable, (yyvsp[-4].e)->sym);
                            p->info.typ->ref = sp->table;
                            p->info.typ->width = sp->offset;
                            p->info.typ->id = p->sym;
                          }
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3675 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 128:
#line 1319 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if ((p = entry(classtable, (yyvsp[0].sym))))
                          {
                            if (p->info.typ->type == Tstruct)
                            {
                              (yyval.typ) = p->info.typ;
                            }
                            else
                            {
                              sprintf(errbuf, "'struct %s' redeclaration (line %d)", (yyvsp[0].sym)->name, p->lineno);
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
#line 3701 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 129:
#line 1341 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
                          p->info.typ->id = sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3732 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 130:
#line 1368 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if ((p = entry(classtable, (yyvsp[-4].sym))))
                          {
                            if (p->info.typ->ref || p->info.typ->type != Tunion)
                            {
                              sprintf(errbuf, "union '%s' already declared at %s:%d", (yyvsp[-4].sym)->name, p->filename, p->lineno);
                              semerror(errbuf);
                            }
                            else
                            {
                              p = reenter(classtable, (yyvsp[-4].sym));
                              p->info.typ->ref = sp->table;
                              p->info.typ->width = sp->offset;
                            }
                          }
                          else
                          {
                            p = enter(classtable, (yyvsp[-4].sym));
                            p->info.typ = mkunion(sp->table, sp->offset);
                          }
                          p->info.typ->id = (yyvsp[-4].sym);
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3761 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 131:
#line 1392 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3787 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 132:
#line 1414 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3818 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 133:
#line 1441 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3849 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 134:
#line 1468 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if ((p = entry(enumtable, (yyvsp[-5].e)->sym)))
                            if (!p->info.typ->ref)
                              p->info.typ->ref = sp->table;
                          p->info.typ->id = (yyvsp[-5].e)->sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3862 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 135:
#line 1477 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if ((p = entry(enumtable, (yyvsp[-5].e)->sym)))
                            if (!p->info.typ->ref)
                              p->info.typ->ref = sp->table;
                          p->info.typ->id = (yyvsp[-5].e)->sym;
                          (yyval.typ) = p->info.typ;
                          exitscope();
                        }
#line 3875 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 136:
#line 1486 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3893 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 137:
#line 1500 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3911 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 138:
#line 1513 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3933 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 139:
#line 1530 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3956 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 140:
#line 1548 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 3991 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 141:
#line 1579 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
                              semwarn("To use smart pointers you should also use wsdl2h and soapcpp2 with option -c++11 or -c++14");
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
#line 4062 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 142:
#line 1646 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          sprintf(errbuf, "undeclared '%s'", (yyvsp[-1].sym)->name);
                          synerror(errbuf);
                          (yyval.typ) = mkint();
                        }
#line 4072 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 143:
#line 1651 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          sprintf(errbuf, "perhaps trying to use a template with an undefined type parameter '%s'?", (yyvsp[-1].sym)->name);
                          synerror(errbuf);
                          (yyval.typ) = mkint();
                        }
#line 4082 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 144:
#line 1656 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          synerror("perhaps trying to use an undefined template or template with a non-type template parameter? Declare 'template <typename T> class name'");
                          (yyval.typ) = mkint();
                        }
#line 4091 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 145:
#line 1661 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          synerror("malformed class definition (use spacing around ':' to separate derived : base)");
                          yyerrok;
                          (yyval.typ) = mkint();
                        }
#line 4101 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 146:
#line 1667 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          synerror("malformed struct definition");
                          yyerrok;
                          (yyval.typ) = mkint();
                        }
#line 4111 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 147:
#line 1673 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          synerror("malformed union definition");
                          yyerrok;
                          (yyval.typ) = mkint();
                        }
#line 4121 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 148:
#line 1679 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          synerror("malformed enum definition");
                          yyerrok;
                          (yyval.typ) = mkint();
                        }
#line 4131 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 149:
#line 1685 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4160 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 150:
#line 1710 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4191 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 151:
#line 1737 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4213 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 152:
#line 1755 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4236 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 153:
#line 1775 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4261 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 154:
#line 1797 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4287 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 155:
#line 1819 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.sym) = (yyvsp[0].sym);
                          if (!c11flag)
                            semwarn("To use scoped enumerations (enum class) you should also use wsdl2h and soapcpp2 with option -c++11 or -c++14");
                        }
#line 4297 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 156:
#line 1824 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.sym) = (yyvsp[0].sym);
                          if (!c11flag)
                            semwarn("To use scoped enumerations (enum class) you must also use wsdl2h and soapcpp2 with option -c++11 or -c++14");
                        }
#line 4307 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 157:
#line 1830 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.i) = 1; }
#line 4313 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 158:
#line 1831 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.i) = 4; }
#line 4319 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 159:
#line 1832 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.i) = 2; }
#line 4325 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 160:
#line 1833 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.i) = 4; }
#line 4331 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 161:
#line 1834 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.i) = 4; }
#line 4337 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 162:
#line 1835 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.i) = 8; }
#line 4343 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 163:
#line 1836 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4358 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 164:
#line 1846 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          semerror("enum underlying type must be one of int8_t, int16_t, int32_t, int64_t");
                          (yyval.i) = 4;
                        }
#line 4367 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 165:
#line 1850 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.i) = 4; /* 4 = enum */ }
#line 4373 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 166:
#line 1852 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 4379 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 167:
#line 1853 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 4385 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 168:
#line 1855 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.e) = (yyvsp[0].e); }
#line 4391 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 169:
#line 1856 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.e) = (yyvsp[0].e); }
#line 4397 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 170:
#line 1857 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.e) = (yyvsp[0].e); }
#line 4403 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 171:
#line 1858 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.e) = entry(classtable, (yyvsp[0].sym));
                          if (!(yyval.e))
                          {
                            p = entry(typetable, (yyvsp[0].sym));
                            if (p && (p->info.typ->type == Tclass || p->info.typ->type == Tstruct))
                              (yyval.e) = p;
                          }
                        }
#line 4417 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 172:
#line 1867 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.e) = entry(classtable, (yyvsp[0].sym)); }
#line 4423 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 173:
#line 1869 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (transient <= -2)
                            transient = 0;
                          permission = 0;
                          enterscope(mktable(NULL), 0);
                          sp->entry = NULL;
                        }
#line 4435 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 174:
#line 1877 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (transient <= -2)
                            transient = 0;
                          permission = 0;
                          enterscope(mktable(NULL), 0);
                          sp->entry = NULL;
                          sp->grow = False;
                        }
#line 4448 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 175:
#line 1886 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          enterscope(mktable(NULL), 0);
                          sp->entry = NULL;
                          sp->mask = True;
                          sp->val = 1;
                        }
#line 4459 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 176:
#line 1893 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 4465 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 177:
#line 1894 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { }
#line 4471 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 178:
#line 1896 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (sp->table->level == INTERNAL)
                            transient |= 1;
                          permission = 0;
                          enterscope(mktable(NULL), 0);
                          sp->entry = NULL;
                          sp->table->level = PARAM;
                        }
#line 4484 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 179:
#line 1905 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sauto; }
#line 4490 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 180:
#line 1906 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sregister; }
#line 4496 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 181:
#line 1907 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sstatic; }
#line 4502 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 182:
#line 1908 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sexplicit; }
#line 4508 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 183:
#line 1909 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sextern; transient = 1; }
#line 4514 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 184:
#line 1910 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Stypedef; }
#line 4520 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 185:
#line 1911 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Svirtual; }
#line 4526 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 186:
#line 1912 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sconst; }
#line 4532 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 187:
#line 1913 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sfinal; }
#line 4538 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 188:
#line 1914 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Soverride; }
#line 4544 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 189:
#line 1915 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sfriend; }
#line 4550 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 190:
#line 1916 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sinline; }
#line 4556 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 191:
#line 1917 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = SmustUnderstand; }
#line 4562 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 192:
#line 1918 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sreturn; }
#line 4568 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 193:
#line 1919 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.sto) = Sattribute;
                          if (eflag)
                            semwarn("SOAP RPC encoding does not support XML attributes");
                        }
#line 4578 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 194:
#line 1924 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sspecial; }
#line 4584 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 195:
#line 1925 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sextern; transient = -2; }
#line 4590 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 196:
#line 1926 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Smutable; transient = -4; }
#line 4596 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 197:
#line 1928 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Snone; }
#line 4602 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 198:
#line 1929 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = (Storage)((int)(yyvsp[-1].sto) | (int)Sconstobj); }
#line 4608 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 199:
#line 1930 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = (Storage)((int)(yyvsp[-1].sto) | (int)Sfinal); }
#line 4614 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 200:
#line 1931 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = (Storage)((int)(yyvsp[-1].sto) | (int)Soverride); }
#line 4620 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 201:
#line 1933 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Snone; }
#line 4626 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 202:
#line 1934 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Sabstract; }
#line 4632 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 203:
#line 1936 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Snone; }
#line 4638 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 204:
#line 1937 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.sto) = Svirtual; }
#line 4644 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 205:
#line 1939 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = tmp = sp->node; }
#line 4650 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 206:
#line 1940 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          /* handle const pointers, such as const char* */
                          if (((int)tmp.sto & (int)Sconst))
                            tmp.sto = (Storage)(((int)tmp.sto & ~(int)Sconst) | (int)Sconstptr);
                          tmp.typ = mkpointer(tmp.typ);
                          tmp.typ->transient = transient;
                          (yyval.rec) = tmp;
                        }
#line 4663 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 207:
#line 1948 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          tmp.typ = mkreference(tmp.typ);
                          tmp.typ->transient = transient;
                          (yyval.rec) = tmp;
                        }
#line 4673 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 208:
#line 1953 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          tmp.typ = mkrvalueref(tmp.typ);
                          tmp.typ->transient = transient;
                          (yyval.rec) = tmp;
                        }
#line 4683 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 209:
#line 1959 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = tmp; }
#line 4689 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 210:
#line 1961 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4711 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 211:
#line 1978 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkpointer((yyvsp[0].rec).typ); /* zero size array = pointer */
                          (yyval.rec).sto = (yyvsp[0].rec).sto;
                        }
#line 4720 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 212:
#line 1983 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4739 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 213:
#line 1998 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 4745 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 214:
#line 1999 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4764 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 215:
#line 2014 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).hasval = False;
                          (yyval.rec).fixed = False;
                        }
#line 4773 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 216:
#line 2018 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4792 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 217:
#line 2032 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4811 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 218:
#line 2047 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.s) = NULL; }
#line 4817 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 219:
#line 2048 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.s) = (yyvsp[0].s); }
#line 4823 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 220:
#line 2050 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
                          (yyval.rec).pattern = NULL;
                        }
#line 4841 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 221:
#line 2063 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
                          (yyval.rec).pattern = NULL;
                        }
#line 4861 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 222:
#line 2078 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
                          (yyval.rec).pattern = NULL;
                        }
#line 4881 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 223:
#line 2093 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
                          (yyval.rec).pattern = NULL;
                        }
#line 4909 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 224:
#line 2116 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
                          (yyval.rec).pattern = NULL;
                        }
#line 4932 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 225:
#line 2136 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4951 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 226:
#line 2151 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 4972 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 227:
#line 2168 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 5001 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 228:
#line 2192 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 5025 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 229:
#line 2212 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.i) = zflag >= 1 && zflag <= 3; /* False, unless version 2.8.30 or earlier */ }
#line 5031 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 230:
#line 2213 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.i) = True; }
#line 5037 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 231:
#line 2215 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.s) = NULL; }
#line 5043 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 232:
#line 2216 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.s) = (yyvsp[0].s); }
#line 5049 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 233:
#line 2218 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.ir).i = (LONG64)((yyval.ir).r = (yyvsp[0].r)); }
#line 5055 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 234:
#line 2219 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.ir).r = (double)((yyval.ir).i = (yyvsp[0].i)); }
#line 5061 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 235:
#line 2220 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.ir).r = (double)((yyval.ir).i = (yyvsp[0].c)); }
#line 5067 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 236:
#line 2221 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.ir).i = +(yyvsp[0].ir).i; (yyval.ir).r = +(yyvsp[0].ir).r; }
#line 5073 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 237:
#line 2222 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.ir).i = -(yyvsp[0].ir).i; (yyval.ir).r = -(yyvsp[0].ir).r; }
#line 5079 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 238:
#line 2224 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = (yyval.rec).incmax = True; }
#line 5085 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 239:
#line 2225 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = (yyval.rec).incmax = True; }
#line 5091 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 240:
#line 2226 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = False; (yyval.rec).incmax = True; }
#line 5097 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 241:
#line 2227 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = False; (yyval.rec).incmax = True; }
#line 5103 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 242:
#line 2229 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = (yyval.rec).incmax = True; }
#line 5109 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 243:
#line 2230 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = False; (yyval.rec).incmax = True; }
#line 5115 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 244:
#line 2231 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = True; (yyval.rec).incmax = False; }
#line 5121 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 245:
#line 2232 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = False; (yyval.rec).incmax = False; }
#line 5127 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 246:
#line 2233 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = False; (yyval.rec).incmax = False; }
#line 5133 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 247:
#line 2235 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = (yyval.rec).incmax = True; }
#line 5139 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 248:
#line 2236 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = True; (yyval.rec).incmax = False; }
#line 5145 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 249:
#line 2237 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).incmin = True; (yyval.rec).incmax = False; }
#line 5151 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 250:
#line 2246 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5157 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 251:
#line 2247 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5163 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 252:
#line 2251 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = (yyvsp[-2].rec).typ;
                          (yyval.rec).sto = Snone;
                          (yyval.rec).hasval = False;
                        }
#line 5173 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 254:
#line 2259 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5179 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 255:
#line 2262 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).hasval = False;
                          (yyval.rec).typ = mkint();
                        }
#line 5188 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 256:
#line 2266 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5194 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 257:
#line 2268 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5200 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 258:
#line 2271 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec).hasval = False;
                          (yyval.rec).typ = mkint();
                        }
#line 5208 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 259:
#line 2274 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5214 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 260:
#line 2276 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5220 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 261:
#line 2279 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = iop("|", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5226 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 262:
#line 2280 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = iop("^", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5232 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 263:
#line 2281 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = iop("&", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5238 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 264:
#line 2282 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = relop("==", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5244 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 265:
#line 2283 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = relop("!=", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5250 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 266:
#line 2284 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = relop("<", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5256 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 267:
#line 2285 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = relop("<=", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5262 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 268:
#line 2286 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = relop(">", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5268 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 269:
#line 2287 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = relop(">=", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5274 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 270:
#line 2288 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = iop("<<", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5280 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 271:
#line 2289 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = iop(">>", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5286 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 272:
#line 2290 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = op("+", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5292 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 273:
#line 2291 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = op("-", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5298 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 274:
#line 2292 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = op("*", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5304 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 275:
#line 2293 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = op("/", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5310 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 276:
#line 2294 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = iop("%", (yyvsp[-2].rec), (yyvsp[0].rec)); }
#line 5316 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 277:
#line 2295 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5322 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 278:
#line 2298 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if ((yyvsp[0].rec).hasval)
                            (yyval.rec).val.i = !(yyvsp[0].rec).val.i;
                          (yyval.rec).typ = (yyvsp[0].rec).typ;
                          (yyval.rec).hasval = (yyvsp[0].rec).hasval;
                        }
#line 5333 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 279:
#line 2304 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if ((yyvsp[0].rec).hasval)
                            (yyval.rec).val.i = ~(yyvsp[0].rec).val.i;
                          (yyval.rec).typ = (yyvsp[0].rec).typ;
                          (yyval.rec).hasval = (yyvsp[0].rec).hasval;
                        }
#line 5344 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 280:
#line 2310 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 5362 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 281:
#line 2323 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5368 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 282:
#line 2324 "soapcpp2_yacc.y" /* yacc.c:1663  */
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
#line 5384 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 283:
#line 2335 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkpointer((yyvsp[0].rec).typ);
                          (yyval.rec).sto = Snone;
                          (yyval.rec).hasval = False;
                        }
#line 5394 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 284:
#line 2341 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).typ = mkint();
                          (yyval.rec).val.i = (yyvsp[-1].rec).typ->width;
                        }
#line 5405 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 285:
#line 2347 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[0].rec); }
#line 5411 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 286:
#line 2350 "soapcpp2_yacc.y" /* yacc.c:1663  */
    { (yyval.rec) = (yyvsp[-1].rec); }
#line 5417 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 287:
#line 2351 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          if (!(p = enumentry((yyvsp[0].sym))))
                            p = undefined((yyvsp[0].sym));
                          else
                            (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).typ = p->info.typ;
                          (yyval.rec).val = p->info.val;
                        }
#line 5431 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 288:
#line 2360 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkint();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.i = (yyvsp[0].i);
                        }
#line 5442 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 289:
#line 2366 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkfloat();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.r = (yyvsp[0].r);
                        }
#line 5453 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 290:
#line 2372 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkchar();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.i = (yyvsp[0].c);
                        }
#line 5464 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 291:
#line 2378 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkstring();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.s = (yyvsp[0].s);
                        }
#line 5475 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 292:
#line 2384 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkbool();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.i = 0;
                        }
#line 5486 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;

  case 293:
#line 2390 "soapcpp2_yacc.y" /* yacc.c:1663  */
    {
                          (yyval.rec).typ = mkbool();
                          (yyval.rec).hasval = True;
                          (yyval.rec).fixed = False;
                          (yyval.rec).val.i = 1;
                        }
#line 5497 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
    break;


#line 5501 "soapcpp2_yacc.tab.c" /* yacc.c:1663  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
  return yyresult;
}
#line 2398 "soapcpp2_yacc.y" /* yacc.c:1907  */


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

/**************************************\

        Type additions

\**************************************/

static void
add_fault(void)
{
  Table *t;
  Entry *p1, *p2, *p3, *p4;
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
