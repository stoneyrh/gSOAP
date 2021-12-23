/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SOAPCPP2_YACC_TAB_H_INCLUDED
# define YY_YY_SOAPCPP2_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PRAGMA = 258,                  /* PRAGMA  */
    AUTO = 259,                    /* AUTO  */
    DOUBLE = 260,                  /* DOUBLE  */
    INT = 261,                     /* INT  */
    STRUCT = 262,                  /* STRUCT  */
    BREAK = 263,                   /* BREAK  */
    ELSE = 264,                    /* ELSE  */
    LONG = 265,                    /* LONG  */
    SWITCH = 266,                  /* SWITCH  */
    CASE = 267,                    /* CASE  */
    ENUM = 268,                    /* ENUM  */
    REGISTER = 269,                /* REGISTER  */
    TYPEDEF = 270,                 /* TYPEDEF  */
    CHAR = 271,                    /* CHAR  */
    EXTERN = 272,                  /* EXTERN  */
    RETURN = 273,                  /* RETURN  */
    UNION = 274,                   /* UNION  */
    CONST = 275,                   /* CONST  */
    FLOAT = 276,                   /* FLOAT  */
    SHORT = 277,                   /* SHORT  */
    UNSIGNED = 278,                /* UNSIGNED  */
    CONTINUE = 279,                /* CONTINUE  */
    FOR = 280,                     /* FOR  */
    SIGNED = 281,                  /* SIGNED  */
    VOID = 282,                    /* VOID  */
    DEFAULT = 283,                 /* DEFAULT  */
    GOTO = 284,                    /* GOTO  */
    SIZEOF = 285,                  /* SIZEOF  */
    VOLATILE = 286,                /* VOLATILE  */
    DO = 287,                      /* DO  */
    IF = 288,                      /* IF  */
    STATIC = 289,                  /* STATIC  */
    WHILE = 290,                   /* WHILE  */
    CLASS = 291,                   /* CLASS  */
    PRIVATE = 292,                 /* PRIVATE  */
    PROTECTED = 293,               /* PROTECTED  */
    PUBLIC = 294,                  /* PUBLIC  */
    VIRTUAL = 295,                 /* VIRTUAL  */
    INLINE = 296,                  /* INLINE  */
    OPERATOR = 297,                /* OPERATOR  */
    LLONG = 298,                   /* LLONG  */
    BOOL = 299,                    /* BOOL  */
    CFALSE = 300,                  /* CFALSE  */
    CTRUE = 301,                   /* CTRUE  */
    WCHAR = 302,                   /* WCHAR  */
    TIME = 303,                    /* TIME  */
    USING = 304,                   /* USING  */
    NAMESPACE = 305,               /* NAMESPACE  */
    ULLONG = 306,                  /* ULLONG  */
    MUSTUNDERSTAND = 307,          /* MUSTUNDERSTAND  */
    SIZE = 308,                    /* SIZE  */
    FRIEND = 309,                  /* FRIEND  */
    TEMPLATE = 310,                /* TEMPLATE  */
    EXPLICIT = 311,                /* EXPLICIT  */
    TYPENAME = 312,                /* TYPENAME  */
    MUTABLE = 313,                 /* MUTABLE  */
    null = 314,                    /* null  */
    RESTRICT = 315,                /* RESTRICT  */
    FINAL = 316,                   /* FINAL  */
    OVERRIDE = 317,                /* OVERRIDE  */
    UCHAR = 318,                   /* UCHAR  */
    USHORT = 319,                  /* USHORT  */
    UINT = 320,                    /* UINT  */
    ULONG = 321,                   /* ULONG  */
    NONE = 322,                    /* NONE  */
    ID = 323,                      /* ID  */
    LAB = 324,                     /* LAB  */
    TYPE = 325,                    /* TYPE  */
    LNG = 326,                     /* LNG  */
    DBL = 327,                     /* DBL  */
    CHR = 328,                     /* CHR  */
    TAG = 329,                     /* TAG  */
    STR = 330,                     /* STR  */
    PA = 331,                      /* PA  */
    NA = 332,                      /* NA  */
    TA = 333,                      /* TA  */
    DA = 334,                      /* DA  */
    MA = 335,                      /* MA  */
    AA = 336,                      /* AA  */
    XA = 337,                      /* XA  */
    OA = 338,                      /* OA  */
    LA = 339,                      /* LA  */
    RA = 340,                      /* RA  */
    OR = 341,                      /* OR  */
    AN = 342,                      /* AN  */
    EQ = 343,                      /* EQ  */
    NE = 344,                      /* NE  */
    LE = 345,                      /* LE  */
    GE = 346,                      /* GE  */
    LS = 347,                      /* LS  */
    RS = 348,                      /* RS  */
    AR = 349,                      /* AR  */
    PP = 350,                      /* PP  */
    NN = 351                       /* NN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 146 "soapcpp2_yacc.y"

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

#line 173 "soapcpp2_yacc.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SOAPCPP2_YACC_TAB_H_INCLUDED  */
