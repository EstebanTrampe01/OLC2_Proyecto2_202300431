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

#ifndef YY_YY_BUILD_PARSER_TAB_H_INCLUDED
# define YY_YY_BUILD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 49 "src/entriesTools/parser.y"

    #include "ast/AbstractExpresion.h"
    #include "ast/nodos/expresiones/expresiones.h"
    #define YYLTYPE_IS_DECLARED 1
    typedef struct YYLTYPE { int first_line; int first_column; int last_line; int last_column; } YYLTYPE;
    typedef struct ParamList { int count; char** names; TipoDato* types; } ParamList;

#line 57 "build/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_PRINT = 258,             /* TOKEN_PRINT  */
    TOKEN_DINT = 259,              /* TOKEN_DINT  */
    TOKEN_DFLOAT = 260,            /* TOKEN_DFLOAT  */
    TOKEN_DBYTE = 261,             /* TOKEN_DBYTE  */
    TOKEN_DSHORT = 262,            /* TOKEN_DSHORT  */
    TOKEN_DLONG = 263,             /* TOKEN_DLONG  */
    TOKEN_DDOUBLE = 264,           /* TOKEN_DDOUBLE  */
    TOKEN_DSTRING = 265,           /* TOKEN_DSTRING  */
    TOKEN_UNSIGNED_INTEGER = 266,  /* TOKEN_UNSIGNED_INTEGER  */
    TOKEN_REAL = 267,              /* TOKEN_REAL  */
    TOKEN_REAL_FLOAT = 268,        /* TOKEN_REAL_FLOAT  */
    TOKEN_STRING = 269,            /* TOKEN_STRING  */
    TOKEN_IDENTIFIER = 270,        /* TOKEN_IDENTIFIER  */
    TOKEN_TRUE = 271,              /* TOKEN_TRUE  */
    TOKEN_FALSE = 272,             /* TOKEN_FALSE  */
    TOKEN_DBOOLEAN = 273,          /* TOKEN_DBOOLEAN  */
    TOKEN_DCHAR = 274,             /* TOKEN_DCHAR  */
    TOKEN_CHAR_LITERAL = 275,      /* TOKEN_CHAR_LITERAL  */
    TOKEN_FINAL = 276,             /* TOKEN_FINAL  */
    TOKEN_SYSTEM_OUT_PRINTLN = 277, /* TOKEN_SYSTEM_OUT_PRINTLN  */
    TOKEN_SYSTEM_OUT_PRINT = 278,  /* TOKEN_SYSTEM_OUT_PRINT  */
    TOKEN_DVOID = 279,             /* TOKEN_DVOID  */
    TOKEN_COMMENT_LINE = 280,      /* TOKEN_COMMENT_LINE  */
    TOKEN_COMMENT_MULTI = 281,     /* TOKEN_COMMENT_MULTI  */
    TOKEN_NULL = 282,              /* TOKEN_NULL  */
    TOKEN_SHIFT_LEFT = 283,        /* TOKEN_SHIFT_LEFT  */
    TOKEN_SHIFT_RIGHT = 284,       /* TOKEN_SHIFT_RIGHT  */
    TOKEN_INTEGER_CLASS = 285,     /* TOKEN_INTEGER_CLASS  */
    TOKEN_DOUBLE_CLASS = 286,      /* TOKEN_DOUBLE_CLASS  */
    TOKEN_FLOAT_CLASS = 287,       /* TOKEN_FLOAT_CLASS  */
    TOKEN_ARRAYS = 288,            /* TOKEN_ARRAYS  */
    TOKEN_PARSE_INT = 289,         /* TOKEN_PARSE_INT  */
    TOKEN_PARSE_DOUBLE = 290,      /* TOKEN_PARSE_DOUBLE  */
    TOKEN_PARSE_FLOAT = 291,       /* TOKEN_PARSE_FLOAT  */
    TOKEN_VALUE_OF = 292,          /* TOKEN_VALUE_OF  */
    TOKEN_JOIN = 293,              /* TOKEN_JOIN  */
    TOKEN_LENGTH = 294,            /* TOKEN_LENGTH  */
    TOKEN_ADD = 295,               /* TOKEN_ADD  */
    TOKEN_INDEXOF = 296,           /* TOKEN_INDEXOF  */
    TOKEN_PLUS_PLUS = 297,         /* TOKEN_PLUS_PLUS  */
    TOKEN_MINUS_MINUS = 298,       /* TOKEN_MINUS_MINUS  */
    TOKEN_PLUS_ASSIGN = 299,       /* TOKEN_PLUS_ASSIGN  */
    TOKEN_MINUS_ASSIGN = 300,      /* TOKEN_MINUS_ASSIGN  */
    TOKEN_MUL_ASSIGN = 301,        /* TOKEN_MUL_ASSIGN  */
    TOKEN_DIV_ASSIGN = 302,        /* TOKEN_DIV_ASSIGN  */
    TOKEN_MOD_ASSIGN = 303,        /* TOKEN_MOD_ASSIGN  */
    TOKEN_AND_ASSIGN = 304,        /* TOKEN_AND_ASSIGN  */
    TOKEN_OR_ASSIGN = 305,         /* TOKEN_OR_ASSIGN  */
    TOKEN_XOR_ASSIGN = 306,        /* TOKEN_XOR_ASSIGN  */
    TOKEN_SHL_ASSIGN = 307,        /* TOKEN_SHL_ASSIGN  */
    TOKEN_SHR_ASSIGN = 308,        /* TOKEN_SHR_ASSIGN  */
    TOKEN_EQUAL = 309,             /* TOKEN_EQUAL  */
    TOKEN_NOT_EQUAL = 310,         /* TOKEN_NOT_EQUAL  */
    TOKEN_GREATER = 311,           /* TOKEN_GREATER  */
    TOKEN_LESS = 312,              /* TOKEN_LESS  */
    TOKEN_GREATER_EQUAL = 313,     /* TOKEN_GREATER_EQUAL  */
    TOKEN_LESS_EQUAL = 314,        /* TOKEN_LESS_EQUAL  */
    TOKEN_AND = 315,               /* TOKEN_AND  */
    TOKEN_OR = 316,                /* TOKEN_OR  */
    TOKEN_NOT = 317,               /* TOKEN_NOT  */
    TOKEN_IF = 318,                /* TOKEN_IF  */
    TOKEN_ELSE = 319,              /* TOKEN_ELSE  */
    TOKEN_SWITCH = 320,            /* TOKEN_SWITCH  */
    TOKEN_CASE = 321,              /* TOKEN_CASE  */
    TOKEN_DEFAULT = 322,           /* TOKEN_DEFAULT  */
    TOKEN_BREAK = 323,             /* TOKEN_BREAK  */
    TOKEN_WHILE = 324,             /* TOKEN_WHILE  */
    TOKEN_FOR = 325,               /* TOKEN_FOR  */
    TOKEN_CONTINUE = 326,          /* TOKEN_CONTINUE  */
    TOKEN_NEW = 327,               /* TOKEN_NEW  */
    TOKEN_RETURN = 328,            /* TOKEN_RETURN  */
    TOKEN_PUBLIC = 329,            /* TOKEN_PUBLIC  */
    TOKEN_STATIC = 330,            /* TOKEN_STATIC  */
    NEG = 331,                     /* NEG  */
    CAST = 332                     /* CAST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 78 "src/entriesTools/parser.y"

    AbstractExpresion* nodo;
    char* string;
    int boolean;
    ParamList* paramList;
    TipoDato tipoDato;

#line 159 "build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_H_INCLUDED  */
