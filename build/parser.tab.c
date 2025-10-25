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
#line 1 "src/entriesTools/parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include "ast/AbstractExpresion.h"

    int yylex(void);
    extern AbstractExpresion* ast_root;
    extern char* comments[];
    extern int comment_count;
    void yyerror(const char *s);
#line 14 "src/entriesTools/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "ast/nodos/builders.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/expresiones/listaExpresiones.h"
#include "ast/nodos/instrucciones/instrucciones.h"
#include "ast/nodos/instrucciones/bloque.h"
#include "ast/nodos/instrucciones/instruccion/print.h"
#include "ast/nodos/instrucciones/instruccion/declaracion.h"
#include "ast/nodos/instrucciones/instruccion/array.h"
#include "ast/nodos/instrucciones/instruccion/matrix.h"
#include "ast/nodos/instrucciones/instruccion/funcion.h"
#include "ast/nodos/instrucciones/instruccion/if.h"
#include "ast/nodos/instrucciones/instruccion/while.h"
#include "ast/nodos/instrucciones/instruccion/for.h"
#include "ast/nodos/instrucciones/instruccion/repeat.h"
#include "ast/nodos/instrucciones/instruccion/switch.h"
#include "ast/nodos/instrucciones/instruccion/break.h"
#include "ast/nodos/instrucciones/instruccion/continue.h"
#include "ast/nodos/expresiones/relacionales/relacionales.h"
#include "ast/nodos/expresiones/logicas/logicas.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "ast/nodos/expresiones/cast.h"
#include "ast/nodos/expresiones/terminales/identificadores.h"
#include "ast/nodos/expresiones/terminales/primitivos.h"
#include "ast/nodos/expresiones/builtins.h"
#include "context/error_reporting.h"


#line 115 "build/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_PRINT = 3,                /* TOKEN_PRINT  */
  YYSYMBOL_TOKEN_DINT = 4,                 /* TOKEN_DINT  */
  YYSYMBOL_TOKEN_DFLOAT = 5,               /* TOKEN_DFLOAT  */
  YYSYMBOL_TOKEN_DBYTE = 6,                /* TOKEN_DBYTE  */
  YYSYMBOL_TOKEN_DSHORT = 7,               /* TOKEN_DSHORT  */
  YYSYMBOL_TOKEN_DLONG = 8,                /* TOKEN_DLONG  */
  YYSYMBOL_TOKEN_DDOUBLE = 9,              /* TOKEN_DDOUBLE  */
  YYSYMBOL_TOKEN_DSTRING = 10,             /* TOKEN_DSTRING  */
  YYSYMBOL_TOKEN_UNSIGNED_INTEGER = 11,    /* TOKEN_UNSIGNED_INTEGER  */
  YYSYMBOL_TOKEN_REAL = 12,                /* TOKEN_REAL  */
  YYSYMBOL_TOKEN_REAL_FLOAT = 13,          /* TOKEN_REAL_FLOAT  */
  YYSYMBOL_TOKEN_STRING = 14,              /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_IDENTIFIER = 15,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_TRUE = 16,                /* TOKEN_TRUE  */
  YYSYMBOL_TOKEN_FALSE = 17,               /* TOKEN_FALSE  */
  YYSYMBOL_TOKEN_DBOOLEAN = 18,            /* TOKEN_DBOOLEAN  */
  YYSYMBOL_TOKEN_DCHAR = 19,               /* TOKEN_DCHAR  */
  YYSYMBOL_TOKEN_CHAR_LITERAL = 20,        /* TOKEN_CHAR_LITERAL  */
  YYSYMBOL_TOKEN_FINAL = 21,               /* TOKEN_FINAL  */
  YYSYMBOL_TOKEN_SYSTEM_OUT_PRINTLN = 22,  /* TOKEN_SYSTEM_OUT_PRINTLN  */
  YYSYMBOL_TOKEN_SYSTEM_OUT_PRINT = 23,    /* TOKEN_SYSTEM_OUT_PRINT  */
  YYSYMBOL_TOKEN_DVOID = 24,               /* TOKEN_DVOID  */
  YYSYMBOL_TOKEN_COMMENT_LINE = 25,        /* TOKEN_COMMENT_LINE  */
  YYSYMBOL_TOKEN_COMMENT_MULTI = 26,       /* TOKEN_COMMENT_MULTI  */
  YYSYMBOL_TOKEN_NULL = 27,                /* TOKEN_NULL  */
  YYSYMBOL_TOKEN_SHIFT_LEFT = 28,          /* TOKEN_SHIFT_LEFT  */
  YYSYMBOL_TOKEN_SHIFT_RIGHT = 29,         /* TOKEN_SHIFT_RIGHT  */
  YYSYMBOL_TOKEN_INTEGER_CLASS = 30,       /* TOKEN_INTEGER_CLASS  */
  YYSYMBOL_TOKEN_DOUBLE_CLASS = 31,        /* TOKEN_DOUBLE_CLASS  */
  YYSYMBOL_TOKEN_FLOAT_CLASS = 32,         /* TOKEN_FLOAT_CLASS  */
  YYSYMBOL_TOKEN_ARRAYS = 33,              /* TOKEN_ARRAYS  */
  YYSYMBOL_TOKEN_PARSE_INT = 34,           /* TOKEN_PARSE_INT  */
  YYSYMBOL_TOKEN_PARSE_DOUBLE = 35,        /* TOKEN_PARSE_DOUBLE  */
  YYSYMBOL_TOKEN_PARSE_FLOAT = 36,         /* TOKEN_PARSE_FLOAT  */
  YYSYMBOL_TOKEN_VALUE_OF = 37,            /* TOKEN_VALUE_OF  */
  YYSYMBOL_TOKEN_JOIN = 38,                /* TOKEN_JOIN  */
  YYSYMBOL_TOKEN_LENGTH = 39,              /* TOKEN_LENGTH  */
  YYSYMBOL_TOKEN_ADD = 40,                 /* TOKEN_ADD  */
  YYSYMBOL_TOKEN_INDEXOF = 41,             /* TOKEN_INDEXOF  */
  YYSYMBOL_TOKEN_PLUS_PLUS = 42,           /* TOKEN_PLUS_PLUS  */
  YYSYMBOL_TOKEN_MINUS_MINUS = 43,         /* TOKEN_MINUS_MINUS  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 44,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 45,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_MUL_ASSIGN = 46,          /* TOKEN_MUL_ASSIGN  */
  YYSYMBOL_TOKEN_DIV_ASSIGN = 47,          /* TOKEN_DIV_ASSIGN  */
  YYSYMBOL_TOKEN_MOD_ASSIGN = 48,          /* TOKEN_MOD_ASSIGN  */
  YYSYMBOL_TOKEN_AND_ASSIGN = 49,          /* TOKEN_AND_ASSIGN  */
  YYSYMBOL_TOKEN_OR_ASSIGN = 50,           /* TOKEN_OR_ASSIGN  */
  YYSYMBOL_TOKEN_XOR_ASSIGN = 51,          /* TOKEN_XOR_ASSIGN  */
  YYSYMBOL_TOKEN_SHL_ASSIGN = 52,          /* TOKEN_SHL_ASSIGN  */
  YYSYMBOL_TOKEN_SHR_ASSIGN = 53,          /* TOKEN_SHR_ASSIGN  */
  YYSYMBOL_TOKEN_EQUAL = 54,               /* TOKEN_EQUAL  */
  YYSYMBOL_TOKEN_NOT_EQUAL = 55,           /* TOKEN_NOT_EQUAL  */
  YYSYMBOL_TOKEN_GREATER = 56,             /* TOKEN_GREATER  */
  YYSYMBOL_TOKEN_LESS = 57,                /* TOKEN_LESS  */
  YYSYMBOL_TOKEN_GREATER_EQUAL = 58,       /* TOKEN_GREATER_EQUAL  */
  YYSYMBOL_TOKEN_LESS_EQUAL = 59,          /* TOKEN_LESS_EQUAL  */
  YYSYMBOL_TOKEN_AND = 60,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 61,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_NOT = 62,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_IF = 63,                  /* TOKEN_IF  */
  YYSYMBOL_TOKEN_ELSE = 64,                /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_SWITCH = 65,              /* TOKEN_SWITCH  */
  YYSYMBOL_TOKEN_CASE = 66,                /* TOKEN_CASE  */
  YYSYMBOL_TOKEN_DEFAULT = 67,             /* TOKEN_DEFAULT  */
  YYSYMBOL_TOKEN_BREAK = 68,               /* TOKEN_BREAK  */
  YYSYMBOL_TOKEN_WHILE = 69,               /* TOKEN_WHILE  */
  YYSYMBOL_TOKEN_FOR = 70,                 /* TOKEN_FOR  */
  YYSYMBOL_TOKEN_CONTINUE = 71,            /* TOKEN_CONTINUE  */
  YYSYMBOL_TOKEN_NEW = 72,                 /* TOKEN_NEW  */
  YYSYMBOL_TOKEN_RETURN = 73,              /* TOKEN_RETURN  */
  YYSYMBOL_TOKEN_PUBLIC = 74,              /* TOKEN_PUBLIC  */
  YYSYMBOL_TOKEN_STATIC = 75,              /* TOKEN_STATIC  */
  YYSYMBOL_TOKEN_REPEAT = 76,              /* TOKEN_REPEAT  */
  YYSYMBOL_77_ = 77,                       /* '+'  */
  YYSYMBOL_78_ = 78,                       /* '-'  */
  YYSYMBOL_79_ = 79,                       /* '&'  */
  YYSYMBOL_80_ = 80,                       /* '^'  */
  YYSYMBOL_81_ = 81,                       /* '|'  */
  YYSYMBOL_82_ = 82,                       /* '*'  */
  YYSYMBOL_83_ = 83,                       /* '/'  */
  YYSYMBOL_84_ = 84,                       /* '%'  */
  YYSYMBOL_NEG = 85,                       /* NEG  */
  YYSYMBOL_CAST = 86,                      /* CAST  */
  YYSYMBOL_87_ = 87,                       /* '.'  */
  YYSYMBOL_88_ = 88,                       /* '}'  */
  YYSYMBOL_89_ = 89,                       /* ';'  */
  YYSYMBOL_90_ = 90,                       /* '('  */
  YYSYMBOL_91_ = 91,                       /* ')'  */
  YYSYMBOL_92_ = 92,                       /* '{'  */
  YYSYMBOL_93_ = 93,                       /* ':'  */
  YYSYMBOL_94_ = 94,                       /* '='  */
  YYSYMBOL_95_ = 95,                       /* ','  */
  YYSYMBOL_96_ = 96,                       /* '['  */
  YYSYMBOL_97_ = 97,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 98,                  /* $accept  */
  YYSYMBOL_s = 99,                         /* s  */
  YYSYMBOL_lSentencia = 100,               /* lSentencia  */
  YYSYMBOL_comentario = 101,               /* comentario  */
  YYSYMBOL_instruccion = 102,              /* instruccion  */
  YYSYMBOL_if_statement = 103,             /* if_statement  */
  YYSYMBOL_switch_statement = 104,         /* switch_statement  */
  YYSYMBOL_while_statement = 105,          /* while_statement  */
  YYSYMBOL_for_statement = 106,            /* for_statement  */
  YYSYMBOL_repeat_statement = 107,         /* repeat_statement  */
  YYSYMBOL_incremento = 108,               /* incremento  */
  YYSYMBOL_case_list = 109,                /* case_list  */
  YYSYMBOL_case_labels = 110,              /* case_labels  */
  YYSYMBOL_case_item = 111,                /* case_item  */
  YYSYMBOL_instrucciones_case = 112,       /* instrucciones_case  */
  YYSYMBOL_instruccion_case = 113,         /* instruccion_case  */
  YYSYMBOL_default_case = 114,             /* default_case  */
  YYSYMBOL_break_statement = 115,          /* break_statement  */
  YYSYMBOL_continue_statement = 116,       /* continue_statement  */
  YYSYMBOL_instruccion_simple = 117,       /* instruccion_simple  */
  YYSYMBOL_asignacion = 118,               /* asignacion  */
  YYSYMBOL_lista_Expr = 119,               /* lista_Expr  */
  YYSYMBOL_imprimir = 120,                 /* imprimir  */
  YYSYMBOL_bloque = 121,                   /* bloque  */
  YYSYMBOL_bloque_for = 122,               /* bloque_for  */
  YYSYMBOL_declaracion_var = 123,          /* declaracion_var  */
  YYSYMBOL_array_decl_local = 124,         /* array_decl_local  */
  YYSYMBOL_brackets_seq = 125,             /* brackets_seq  */
  YYSYMBOL_var_decl = 126,                 /* var_decl  */
  YYSYMBOL_final_var_decl = 127,           /* final_var_decl  */
  YYSYMBOL_dims_expr_list = 128,           /* dims_expr_list  */
  YYSYMBOL_lista_bloques2D = 129,          /* lista_bloques2D  */
  YYSYMBOL_bloque2D = 130,                 /* bloque2D  */
  YYSYMBOL_filas_lista = 131,              /* filas_lista  */
  YYSYMBOL_fila_matriz = 132,              /* fila_matriz  */
  YYSYMBOL_asignacion_elemento = 133,      /* asignacion_elemento  */
  YYSYMBOL_indices_una = 134,              /* indices_una  */
  YYSYMBOL_indices_multi = 135,            /* indices_multi  */
  YYSYMBOL_expr = 136,                     /* expr  */
  YYSYMBOL_postfix = 137,                  /* postfix  */
  YYSYMBOL_unary = 138,                    /* unary  */
  YYSYMBOL_atom = 139,                     /* atom  */
  YYSYMBOL_join_variadic_args = 140,       /* join_variadic_args  */
  YYSYMBOL_primitivo = 141,                /* primitivo  */
  YYSYMBOL_tipoPrimitivo = 142,            /* tipoPrimitivo  */
  YYSYMBOL_funcion_declaracion = 143,      /* funcion_declaracion  */
  YYSYMBOL_main_declaracion = 144,         /* main_declaracion  */
  YYSYMBOL_main_params_opt = 145,          /* main_params_opt  */
  YYSYMBOL_main_params = 146,              /* main_params  */
  YYSYMBOL_main_param = 147,               /* main_param  */
  YYSYMBOL_main_param_array_brackets = 148, /* main_param_array_brackets  */
  YYSYMBOL_param_opt = 149,                /* param_opt  */
  YYSYMBOL_param_array_brackets = 150,     /* param_array_brackets  */
  YYSYMBOL_lista_parametros = 151,         /* lista_parametros  */
  YYSYMBOL_return_stmt = 152,              /* return_stmt  */
  YYSYMBOL_for_each_statement = 153,       /* for_each_statement  */
  YYSYMBOL_argumentos_opt = 154,           /* argumentos_opt  */
  YYSYMBOL_llamada_funcion = 155           /* llamada_funcion  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 58 "src/entriesTools/parser.y"

// Helper para reportar errores semánticos tempranos (declaraciones) desde el parser.
// Crea un nodo lista vacío, asigna posición y usa report_runtime_error con ctx NULL (scope Global).
static AbstractExpresion* parser_error_node(YYLTYPE loc, const char* fmt, ...){
    static int last_line=-1, last_col=-1; static char last_msg[256];
    AbstractExpresion* n = nuevoListaExpresiones();
    SET_POS(n, loc);
    char msg[256];
    va_list ap; va_start(ap, fmt); vsnprintf(msg,sizeof(msg),fmt,ap); va_end(ap);
    // De-dup: si es el mismo mensaje en la misma ubicación, no volver a reportar
    if(!(last_line==loc.first_line && last_col==loc.first_column && strncmp(last_msg,msg,sizeof(last_msg))==0)){
        // Reusar API central (nodo y contexto NULL -> Global)
    report_syntax_error("%s", msg);
        last_line = loc.first_line; last_col = loc.first_column; strncpy(last_msg,msg,sizeof(last_msg)); last_msg[sizeof(last_msg)-1]='\0';
    }
    return n;
}


#line 325 "build/parser.tab.c"

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  112
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2140

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  205
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  438

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   333


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
       2,     2,     2,     2,     2,     2,     2,    84,    79,     2,
      90,    91,    82,    77,    95,    78,    87,    83,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    93,    89,
       2,    94,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    96,     2,    97,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,    81,    88,     2,     2,     2,     2,
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
      75,    76,    85,    86
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   133,   133,   137,   138,   139,   145,   146,   149,   150,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   171,   172,   175,
     176,   177,   178,   183,   188,   195,   196,   199,   200,   208,
     209,   210,   211,   212,   213,   217,   221,   222,   223,   234,
     238,   245,   250,   256,   268,   280,   285,   291,   292,   293,
     294,   297,   298,   301,   304,   307,   308,   309,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   324,
     325,   332,   333,   334,   335,   336,   339,   340,   342,   347,
     348,   349,   357,   375,   380,   385,   390,   395,   396,   399,
     400,   403,   410,   411,   419,   420,   422,   424,   425,   427,
     429,   431,   434,   435,   436,   437,   438,   440,   441,   442,
     443,   444,   448,   449,   450,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   490,   491,   492,   493,
     494,   495,   496,   502,   510,   514,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   530,   538,   539,
     540,   541,   542,   543,   544,   545,   548,   549,   550,   551,
     552,   553,   554,   559,   564,   576,   577,   577,   578,   578,
     579,   580,   580,   582,   583,   586,   587,   589,   593,   598,
     599,   604,   634,   658,   659,   661
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
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_PRINT",
  "TOKEN_DINT", "TOKEN_DFLOAT", "TOKEN_DBYTE", "TOKEN_DSHORT",
  "TOKEN_DLONG", "TOKEN_DDOUBLE", "TOKEN_DSTRING",
  "TOKEN_UNSIGNED_INTEGER", "TOKEN_REAL", "TOKEN_REAL_FLOAT",
  "TOKEN_STRING", "TOKEN_IDENTIFIER", "TOKEN_TRUE", "TOKEN_FALSE",
  "TOKEN_DBOOLEAN", "TOKEN_DCHAR", "TOKEN_CHAR_LITERAL", "TOKEN_FINAL",
  "TOKEN_SYSTEM_OUT_PRINTLN", "TOKEN_SYSTEM_OUT_PRINT", "TOKEN_DVOID",
  "TOKEN_COMMENT_LINE", "TOKEN_COMMENT_MULTI", "TOKEN_NULL",
  "TOKEN_SHIFT_LEFT", "TOKEN_SHIFT_RIGHT", "TOKEN_INTEGER_CLASS",
  "TOKEN_DOUBLE_CLASS", "TOKEN_FLOAT_CLASS", "TOKEN_ARRAYS",
  "TOKEN_PARSE_INT", "TOKEN_PARSE_DOUBLE", "TOKEN_PARSE_FLOAT",
  "TOKEN_VALUE_OF", "TOKEN_JOIN", "TOKEN_LENGTH", "TOKEN_ADD",
  "TOKEN_INDEXOF", "TOKEN_PLUS_PLUS", "TOKEN_MINUS_MINUS",
  "TOKEN_PLUS_ASSIGN", "TOKEN_MINUS_ASSIGN", "TOKEN_MUL_ASSIGN",
  "TOKEN_DIV_ASSIGN", "TOKEN_MOD_ASSIGN", "TOKEN_AND_ASSIGN",
  "TOKEN_OR_ASSIGN", "TOKEN_XOR_ASSIGN", "TOKEN_SHL_ASSIGN",
  "TOKEN_SHR_ASSIGN", "TOKEN_EQUAL", "TOKEN_NOT_EQUAL", "TOKEN_GREATER",
  "TOKEN_LESS", "TOKEN_GREATER_EQUAL", "TOKEN_LESS_EQUAL", "TOKEN_AND",
  "TOKEN_OR", "TOKEN_NOT", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_SWITCH",
  "TOKEN_CASE", "TOKEN_DEFAULT", "TOKEN_BREAK", "TOKEN_WHILE", "TOKEN_FOR",
  "TOKEN_CONTINUE", "TOKEN_NEW", "TOKEN_RETURN", "TOKEN_PUBLIC",
  "TOKEN_STATIC", "TOKEN_REPEAT", "'+'", "'-'", "'&'", "'^'", "'|'", "'*'",
  "'/'", "'%'", "NEG", "CAST", "'.'", "'}'", "';'", "'('", "')'", "'{'",
  "':'", "'='", "','", "'['", "']'", "$accept", "s", "lSentencia",
  "comentario", "instruccion", "if_statement", "switch_statement",
  "while_statement", "for_statement", "repeat_statement", "incremento",
  "case_list", "case_labels", "case_item", "instrucciones_case",
  "instruccion_case", "default_case", "break_statement",
  "continue_statement", "instruccion_simple", "asignacion", "lista_Expr",
  "imprimir", "bloque", "bloque_for", "declaracion_var",
  "array_decl_local", "brackets_seq", "var_decl", "final_var_decl",
  "dims_expr_list", "lista_bloques2D", "bloque2D", "filas_lista",
  "fila_matriz", "asignacion_elemento", "indices_una", "indices_multi",
  "expr", "postfix", "unary", "atom", "join_variadic_args", "primitivo",
  "tipoPrimitivo", "funcion_declaracion", "main_declaracion",
  "main_params_opt", "main_params", "main_param",
  "main_param_array_brackets", "param_opt", "param_array_brackets",
  "lista_parametros", "return_stmt", "for_each_statement",
  "argumentos_opt", "llamada_funcion", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-348)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-88)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     643,    13,   -15,  -348,  -348,  -348,    56,  -348,  -348,  -348,
    -348,  2044,  -348,  -348,  -348,  -348,  -348,   229,    31,    48,
    -348,  -348,    58,    86,    89,    94,    75,   119,   100,   127,
     134,   137,  1130,   132,  1130,   827,   727,   228,   379,  -348,
    -348,  -348,  -348,  -348,  -348,  -348,  -348,   142,   146,  -348,
     151,  -348,  -348,  -348,   152,   -20,  -348,  -348,  -348,   -10,
    -348,  -348,   157,  -348,  -348,  -348,  -348,  1130,   103,  -348,
    -348,  1130,  1130,  1130,  1130,  1130,  1130,  1130,  1130,  1130,
    1130,  1130,  1130,  1130,   149,   175,  -348,   235,  1013,  1037,
     220,   222,   219,   217,  1130,  1130,  -348,  1130,   882,  -348,
      56,   -18,  1130,  1130,  2024,   -58,   238,  1495,  1534,   168,
      99,   463,  -348,   110,  -348,  -348,  -348,  -348,  -348,  -348,
    -348,  -348,    34,  -348,  1130,    78,   170,    -6,  -348,   -59,
    2024,   178,   180,  2024,  2024,  2024,  2024,  2024,  2024,  2024,
    2024,  2024,  2024,   179,   174,  2024,  1189,  1130,  1130,  1130,
    1130,  1130,  1130,  -348,  1130,  1130,  1130,  1130,  1130,  1130,
    -348,   181,  -348,   -35,  -348,    91,   183,   188,   190,   191,
    1572,  1610,  1648,   268,   195,   196,    -5,  -348,  -348,  1130,
    1130,  1130,  1130,  1130,  1130,  1130,  1130,  1130,  1130,  1130,
    1130,  1130,  1130,  1130,  1130,  1130,  1130,   274,   643,  -348,
    -348,  1199,    16,  -348,  -348,   201,  -348,   202,  1223,   229,
    1130,  -348,   118,   197,  -348,  1130,  1130,  1130,  -348,  -348,
    2024,  2024,  2024,  2024,  2024,  2024,  2024,  2024,  2024,  2024,
    2024,  2024,  1130,  -348,  -348,  1130,  1130,  1130,  1130,   410,
     203,   410,  1130,  1130,   120,   204,    -3,   -49,   -49,  1096,
    1096,    30,    30,    30,    30,  1030,   937,    50,    50,   108,
     108,   108,  -348,  -348,  -348,   209,   553,   -58,  1106,  1130,
    -348,  -348,   211,   198,  2024,   229,   851,  -348,  2024,  1686,
    1358,  2024,  1724,  1762,  1800,  1368,   214,  -348,  -348,   236,
    -348,    -2,   239,  -348,  -348,  1952,  1988,   289,   291,   215,
     229,  -348,  -348,  1838,  1876,     0,   230,   229,   233,   229,
     920,  -348,  2024,  -348,  1130,  -348,  -348,  -348,  1130,   261,
     -26,   241,  1130,   -36,   495,  -348,   314,    -4,   246,   237,
    -348,   247,   244,  -348,  -348,  -348,  -348,   243,  -348,  -348,
     230,   248,   944,   -31,    -7,  -348,    10,  -348,  1311,   251,
    1914,   -26,  -348,  -348,  1415,   252,  -348,  -348,   258,  1130,
     758,  -348,   259,   260,  -348,   263,   640,   262,  -348,   585,
     264,   230,   317,     3,   230,   229,  -348,     4,  -348,  1130,
     254,  1130,    51,  -348,  -348,   265,  -348,   266,  -348,  1130,
    -348,  -348,  -348,  -348,  -348,   410,  -348,  1455,   267,  -348,
    -348,  -348,  -348,  -348,  -348,   410,  -348,  -348,   585,  -348,
     269,  -348,   257,  -348,  -348,  -348,  1267,  1130,  -348,   266,
    -348,  -348,   179,   806,  -348,  -348,  -348,  -348,  -348,  -348,
     230,  -348,  -348,  1301,   272,  -348,  -348,  -348
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   176,   177,   178,   179,   168,   171,   170,
     169,   158,   173,   174,   180,   181,   172,     0,     0,     0,
     182,   175,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   199,     0,     0,     0,     0,     0,     0,     5,
      10,    11,    13,    14,    16,    12,    26,     0,     0,    18,
       0,    89,    90,    91,     0,     0,   146,   154,   156,     0,
      20,    21,     0,    15,   159,     7,    27,     0,     0,   152,
     153,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,     0,     0,     0,     0,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,     0,     0,    64,
       0,   158,     0,     0,   200,   145,     0,     0,     0,     0,
       0,     0,     1,     0,     8,     9,     4,     3,    23,    17,
      19,    24,     0,    25,     0,   100,     0,     0,    22,     0,
      80,     0,     0,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,   204,     0,    68,     0,     0,     0,     0,
       0,     0,     0,   123,     0,     0,     0,     0,     0,     0,
     124,     0,    83,     0,    85,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   143,   144,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
     157,     0,     7,    86,     6,     0,   148,     0,     0,   193,
       0,    97,     0,     0,    81,     0,     0,     0,   205,   122,
     112,   113,   114,   115,   116,   110,   117,   118,   119,   120,
     121,   111,     0,    82,    84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   100,     0,     0,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   125,   126,   130,
     132,   131,   127,   128,   129,     0,     0,   155,     0,     0,
     147,   195,     0,   194,    99,   193,     0,    98,    79,     0,
       0,   101,     0,     0,     0,     0,     0,    67,    65,    29,
      66,     0,     0,    38,    37,     0,     0,     0,    97,     0,
     186,    88,   151,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    96,   164,     0,   161,   162,   163,     0,    32,
       0,   100,     0,     0,     0,    49,     0,     0,     0,     0,
     191,     0,   187,   188,   150,   149,   197,     0,   183,   195,
       0,     0,     0,     0,     0,   104,     0,   107,     0,     0,
       0,     0,    31,    30,     0,     0,    35,    50,     0,     0,
      53,    55,     0,     0,    58,     0,     0,     0,    46,     0,
       0,     0,     0,     0,     0,     0,   196,     0,   184,     0,
      92,     0,     0,    93,    95,     0,   106,     0,   165,     0,
     166,   160,    34,    33,    51,     0,    36,     0,     0,    56,
      60,    57,    59,    47,    48,     0,    42,    41,     0,   201,
       0,   190,     0,   185,   189,   198,     0,     0,   109,     0,
     105,   108,   167,    61,    52,    54,    44,    43,    40,    39,
       0,   192,   102,     0,     0,   202,   103,    62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -348,  -348,   -28,  -348,   -34,  -297,  -348,  -348,  -348,  -348,
      36,  -348,  -348,    41,   -30,  -339,  -348,  -348,  -348,  -234,
     -97,   -61,  -144,   -64,  -347,   -72,  -348,   308,  -348,  -348,
    -348,  -348,  -296,  -348,   -17,  -348,   117,  -348,   -32,    17,
    -348,  -348,  -348,  -348,    68,  -348,  -348,  -348,  -348,    -1,
    -348,    96,    33,  -348,  -348,  -348,  -348,  -348
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    37,    38,   116,    39,    40,    41,    42,    43,    44,
     367,   323,   324,   325,   360,   361,   358,    45,    46,   286,
      47,   382,    48,    49,   199,    50,    51,   246,    52,    53,
     380,   344,   311,   346,   347,    54,    84,    85,   130,   105,
      56,    57,   349,    58,   291,    60,    61,   331,   332,   333,
     373,   272,   305,   273,    62,    63,   144,    64
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     104,   174,   107,   108,   117,   125,   129,   293,   111,   212,
     244,   366,   299,   321,   345,   336,   -87,    55,   411,   415,
     143,   399,   407,   352,    69,    70,   175,   163,   165,   122,
     322,   355,   214,   194,   195,   196,   215,    26,   124,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   205,
     145,   146,   356,    55,   392,    55,   233,   383,   179,   180,
     215,   429,   170,   171,   215,   172,    36,   122,    59,   123,
     177,   178,    81,   206,   207,    67,   124,   117,   179,   180,
     -87,   384,   -87,   -87,   399,    87,   126,   369,   385,   420,
     213,   245,   208,   213,   126,   288,   337,   288,   386,   412,
     337,    65,    66,   109,    59,   387,    59,   189,   190,   191,
     192,   193,   194,   195,   196,   220,   221,   222,   223,   224,
     225,    88,   226,   227,   228,   229,   230,   231,    55,   191,
     192,   193,   194,   195,   196,   406,   179,   180,    89,   418,
     131,   132,   287,    68,   287,    90,   215,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    94,   176,   290,   209,   290,
     266,   426,   210,    91,   428,   289,    92,   294,   274,    59,
     363,    93,   234,   278,   279,   280,   215,   202,    66,    96,
     194,   195,   196,   147,   148,   149,   150,   151,   204,    66,
     281,   153,   160,   282,   283,   284,   285,   106,   275,    95,
     295,   296,   276,   297,   210,    55,   363,    97,   267,   154,
     155,   156,   157,   158,    98,   288,    99,   362,   112,   368,
     368,   118,   117,     3,     4,   119,   303,   304,     5,    86,
     120,   121,   338,   152,   312,    83,   128,    14,    15,   343,
     161,   363,   365,    20,   166,   168,   353,   167,   169,   201,
     364,   288,   197,   362,   288,   218,    59,   211,   216,   159,
     217,    83,   287,   235,   215,   232,   378,   271,   236,   363,
     237,   238,   348,    55,   242,   243,   350,   393,   365,   265,
     354,   268,   269,   307,   277,   292,   364,   290,   362,   300,
     320,   298,   306,   319,   328,   322,   329,   409,   287,   276,
     413,   287,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    36,   365,   340,   351,   362,   397,   422,   366,
     372,   364,   410,   290,    59,   210,   290,   371,   374,   375,
     376,   427,   390,   271,   379,   395,   396,   416,   400,   401,
     417,   365,   402,   405,   431,   408,   425,   419,   381,   364,
     430,   437,    82,   370,   357,   423,   435,   127,   330,     0,
     421,   308,   377,     0,   414,   339,     0,   341,     0,    -2,
     113,     0,     2,     3,     4,   433,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,   114,   115,    21,     0,     0,    22,
      23,    24,    25,     2,     3,     4,     0,     0,     0,     5,
      86,     0,     0,     0,     0,   173,     0,     0,    14,    15,
       0,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,     0,    26,   330,    27,     0,     0,    28,    29,    30,
      31,     0,    32,    33,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,   113,     0,     2,     3,     4,    35,
       0,    36,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,   114,   115,
      21,     0,     0,    22,    23,    24,    25,     0,     2,     3,
       4,     0,    36,     0,     5,    86,     0,     0,     0,     0,
     173,     0,     0,    14,    15,     0,    17,    18,    19,    20,
       0,     0,     0,     0,     0,     0,    26,     0,    27,     0,
       0,    28,    29,    30,    31,     0,    32,    33,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,     0,    35,   113,    36,     2,     3,     4,     0,
       0,   359,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,   114,   115,
      21,     0,     0,    22,    23,    24,    25,    36,     2,     3,
       4,     0,     0,     0,     5,    86,     0,     0,     0,     0,
     173,     0,     0,    14,    15,     0,    17,    18,    19,    20,
       0,     0,     0,     0,     0,     0,    26,     0,    27,     0,
       0,    28,    29,    30,    31,     0,    32,    33,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   301,     0,    35,     1,    36,     2,     3,     4,     0,
       0,     0,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,     0,     0,
      21,     0,     0,    22,    23,    24,    25,   198,     0,     0,
       0,     0,   403,   404,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,     0,    27,     0,
       0,    28,    29,    30,    31,     0,    32,    33,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,   110,     0,
       2,     3,     4,    35,    82,    36,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     0,     0,    21,     0,     0,    22,    23,    24,
      25,     2,     3,     4,     0,     0,     0,     5,    86,     0,
       0,     0,     0,   173,     0,     0,    14,    15,     0,    17,
      18,    19,    20,     0,     0,     0,     0,     0,     0,     0,
      26,     0,    27,     0,     0,    28,    29,    30,    31,     0,
      32,    33,     0,    34,     0,     0,     0,     0,     0,     2,
       3,     4,     0,     0,     0,     5,    86,    35,     0,    36,
       0,   173,     0,     0,    14,    15,   398,    17,    18,    19,
      20,     3,     4,     0,     0,     0,     5,     6,     7,     8,
       9,    10,   101,    12,    13,    14,    15,    16,     0,     0,
      36,    20,     0,     0,    21,     0,     0,    22,    23,    24,
      25,   100,     7,     8,     9,    10,   101,    12,    13,     0,
       0,    16,     0,     0,   434,     0,     0,     0,    21,     0,
       0,    22,    23,    24,    25,     0,     3,     4,     0,   102,
       0,     5,    86,     0,     0,     0,     0,   173,    36,     0,
      14,    15,     0,    17,     0,   103,    20,     0,     0,     0,
       0,     0,     0,   102,     0,     0,     0,    35,     0,     0,
       0,     0,     0,   309,     0,     0,     0,     0,     0,   103,
     100,     7,     8,     9,    10,   101,    12,    13,     0,     0,
      16,    35,     0,   310,     0,     0,     0,    21,     0,     0,
      22,    23,    24,    25,   100,     7,     8,     9,    10,   101,
      12,    13,     0,     0,    16,   179,   180,     0,     0,     0,
       0,    21,     0,     0,    22,    23,    24,    25,     0,     0,
       0,     0,   102,     0,     0,     0,     0,     0,     0,     0,
       0,   181,   182,   183,   184,   185,   186,   187,   103,     0,
       0,     0,     0,     0,     0,     0,   102,     0,     0,     0,
      35,     0,   342,     0,   189,   190,   191,   192,   193,   194,
     195,   196,   103,   100,     7,     8,     9,    10,   101,    12,
      13,     0,     0,    16,    35,     0,   381,     0,     0,     0,
      21,     0,     0,    22,    23,    24,    25,   100,     7,     8,
       9,    10,   101,    12,    13,     0,     0,    16,   179,   180,
       0,     0,     0,     0,    21,     0,     0,    22,    23,    24,
      25,     0,     0,     0,     0,   102,     0,     0,     0,     0,
       0,     0,     0,     0,   181,   182,   183,   184,   185,   186,
       0,   103,     0,     0,     0,     0,     0,     0,     0,   102,
       0,     0,     0,    35,   162,     0,     0,   189,   190,   191,
     192,   193,   194,   195,   196,   103,   100,     7,     8,     9,
      10,   101,    12,    13,   179,   180,    16,    35,   164,     0,
       0,     0,     0,    21,     0,     0,    22,    23,    24,    25,
     100,     7,     8,     9,    10,   101,    12,    13,     0,     0,
      16,     0,   183,   184,   185,   186,     0,    21,     0,     0,
      22,    23,    24,    25,     0,     0,     0,     0,   102,     0,
       0,     0,     0,   189,   190,   191,   192,   193,   194,   195,
     196,     0,     0,     0,   103,     0,     0,     0,     0,     0,
       0,     0,   102,     0,     0,     0,    35,   302,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   103,   100,
       7,     8,     9,    10,   101,    12,    13,   179,   180,    16,
      35,     0,     0,     0,     0,     0,    21,     0,     0,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   181,   182,   183,   184,   185,   186,   187,
     188,   179,   180,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   189,   190,   191,   192,
     193,   194,   195,   196,     0,     0,     0,   181,   182,   183,
     184,   185,   186,   187,   188,     0,   219,     0,     0,    35,
       0,     0,     0,     0,     0,   179,   180,     0,     0,     0,
     189,   190,   191,   192,   193,   194,   195,   196,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     270,   181,   182,   183,   184,   185,   186,   187,   188,   179,
     180,     0,     0,     0,     0,     0,     0,     0,     0,   179,
     180,     0,     0,     0,   189,   190,   191,   192,   193,   194,
     195,   196,     0,     0,     0,   181,   182,   183,   184,   185,
     186,   187,   188,     0,   432,   181,   182,   183,   184,   185,
     186,   187,   188,     0,     0,     0,     0,     0,   189,   190,
     191,   192,   193,   194,   195,   196,   179,   180,   189,   190,
     191,   192,   193,   194,   195,   196,   179,   180,   436,     0,
       0,     0,   388,     0,     0,     0,   389,     0,     0,     0,
       0,     0,   181,   182,   183,   184,   185,   186,   187,   188,
       0,     0,   181,   182,   183,   184,   185,   186,   187,   188,
       0,     0,     0,     0,     0,   189,   190,   191,   192,   193,
     194,   195,   196,   179,   180,   189,   190,   191,   192,   193,
     194,   195,   196,   314,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   318,     0,     0,     0,     0,     0,   181,
     182,   183,   184,   185,   186,   187,   188,     0,     0,     0,
       0,     0,     0,   179,   180,     0,     0,     0,     0,     0,
       0,     0,   189,   190,   191,   192,   193,   194,   195,   196,
       0,     0,     0,     0,     0,     0,     0,     0,   394,   181,
     182,   183,   184,   185,   186,   187,   188,     0,     0,     0,
       0,     0,     0,   179,   180,     0,     0,     0,     0,     0,
       0,     0,   189,   190,   191,   192,   193,   194,   195,   196,
       0,     0,     0,     0,     0,     0,     0,     0,   424,   181,
     182,   183,   184,   185,   186,   187,   188,     0,     0,     0,
       0,     0,   179,   180,     0,     0,     0,     0,     0,     0,
       0,     0,   189,   190,   191,   192,   193,   194,   195,   196,
       0,     0,     0,     0,     0,     0,     0,   198,   181,   182,
     183,   184,   185,   186,   187,   188,     0,     0,     0,     0,
     179,   180,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   189,   190,   191,   192,   193,   194,   195,   196,     0,
       0,     0,     0,     0,     0,   200,   181,   182,   183,   184,
     185,   186,   187,   188,     0,     0,     0,     0,   179,   180,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   189,
     190,   191,   192,   193,   194,   195,   196,     0,     0,     0,
       0,     0,     0,   239,   181,   182,   183,   184,   185,   186,
     187,   188,     0,     0,     0,     0,   179,   180,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   189,   190,   191,
     192,   193,   194,   195,   196,     0,     0,     0,     0,     0,
       0,   240,   181,   182,   183,   184,   185,   186,   187,   188,
       0,     0,     0,     0,   179,   180,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   189,   190,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,     0,     0,   241,
     181,   182,   183,   184,   185,   186,   187,   188,     0,     0,
       0,     0,   179,   180,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   189,   190,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,     0,     0,   313,   181,   182,
     183,   184,   185,   186,   187,   188,     0,     0,     0,     0,
     179,   180,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   189,   190,   191,   192,   193,   194,   195,   196,     0,
       0,     0,     0,     0,     0,   315,   181,   182,   183,   184,
     185,   186,   187,   188,     0,     0,     0,     0,   179,   180,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   189,
     190,   191,   192,   193,   194,   195,   196,     0,     0,     0,
       0,     0,     0,   316,   181,   182,   183,   184,   185,   186,
     187,   188,     0,     0,     0,     0,   179,   180,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   189,   190,   191,
     192,   193,   194,   195,   196,     0,     0,     0,     0,     0,
       0,   317,   181,   182,   183,   184,   185,   186,   187,   188,
       0,     0,     0,     0,   179,   180,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   189,   190,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,     0,     0,   334,
     181,   182,   183,   184,   185,   186,   187,   188,     0,     0,
       0,     0,   179,   180,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   189,   190,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,     0,     0,   335,   181,   182,
     183,   184,   185,   186,   187,   188,     0,     0,     0,     0,
     179,   180,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   189,   190,   191,   192,   193,   194,   195,   196,     0,
       0,     0,     0,     0,     0,   391,   181,   182,   183,   184,
     185,   186,   187,   188,     0,     0,   179,   180,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   189,
     190,   191,   192,   193,   194,   195,   196,     0,     0,     0,
       0,   326,   181,   182,   183,   184,   185,   186,   187,   188,
       0,     0,   179,   180,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   189,   190,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,   327,   181,   182,
     183,   184,   185,   186,   187,   188,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,     0,     0,
       0,   189,   190,   191,   192,   193,   194,   195,   196,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,     0,     0,     0,    82,     0,
      83
};

static const yytype_int16 yycheck[] =
{
      32,    98,    34,    35,    38,    15,    67,   241,    36,    15,
      15,    15,    15,    15,   310,    15,     0,     0,    15,    15,
      81,   360,   369,   320,    42,    43,    98,    88,    89,    87,
      66,    67,    91,    82,    83,    84,    95,    63,    96,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    15,
      82,    83,    88,    36,   351,    38,    91,    88,    28,    29,
      95,   408,    94,    95,    95,    97,    92,    87,     0,    89,
     102,   103,    90,    39,    40,    90,    96,   111,    28,    29,
      64,    88,    66,    67,   423,    17,    96,    91,    95,   385,
      96,    96,   124,    96,    96,   239,    96,   241,    88,    96,
      96,    88,    89,    35,    36,    95,    38,    77,    78,    79,
      80,    81,    82,    83,    84,   147,   148,   149,   150,   151,
     152,    90,   154,   155,   156,   157,   158,   159,   111,    79,
      80,    81,    82,    83,    84,   369,    28,    29,    90,    88,
      37,    38,   239,    87,   241,    87,    95,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,    90,    98,   239,    90,   241,
     198,   405,    94,    87,   408,   239,    87,   241,   210,   111,
     324,    87,    91,   215,   216,   217,    95,    88,    89,    89,
      82,    83,    84,    44,    45,    46,    47,    48,    88,    89,
     232,    84,    85,   235,   236,   237,   238,    75,    90,    90,
     242,   243,    94,    93,    94,   198,   360,    90,   201,    44,
      45,    46,    47,    48,    90,   369,    89,   324,     0,   326,
     327,    89,   266,     4,     5,    89,   268,   269,     9,    10,
      89,    89,   306,    94,   276,    96,    89,    18,    19,   310,
      15,   395,   324,    24,    34,    36,   320,    35,    41,    91,
     324,   405,    24,   360,   408,    91,   198,    97,    90,    94,
      90,    96,   369,    90,    95,    94,   340,   209,    90,   423,
      90,    90,   314,   266,    89,    89,   318,   351,   360,    15,
     322,    90,    90,    95,    97,    92,   360,   369,   395,    90,
      64,    97,    91,    89,    15,    66,    15,   371,   405,    94,
     374,   408,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    92,   395,    91,    64,   423,   359,   389,    15,
      93,   395,    15,   405,   266,    94,   408,    91,    91,    95,
      97,   405,    91,   275,    96,    93,    88,   379,    89,    89,
      96,   423,    89,    91,    97,    91,    89,    92,    92,   423,
      91,    89,    94,   327,   323,   395,   430,    59,   300,    -1,
     387,   275,   339,    -1,   375,   307,    -1,   309,    -1,     0,
       1,    -1,     3,     4,     5,   417,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    33,     3,     4,     5,    -1,    -1,    -1,     9,
      10,    -1,    -1,    -1,    -1,    15,    -1,    -1,    18,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,   375,    65,    -1,    -1,    68,    69,    70,
      71,    -1,    73,    74,    -1,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,    90,
      -1,    92,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,     3,     4,
       5,    -1,    92,    -1,     9,    10,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    18,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,
      -1,    68,    69,    70,    71,    -1,    73,    74,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,     1,    92,     3,     4,     5,    -1,
      -1,    66,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    92,     3,     4,
       5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    18,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,
      -1,    68,    69,    70,    71,    -1,    73,    74,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,     1,    92,     3,     4,     5,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      27,    -1,    -1,    30,    31,    32,    33,    92,    -1,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,
      -1,    68,    69,    70,    71,    -1,    73,    74,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       3,     4,     5,    90,    94,    92,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    27,    -1,    -1,    30,    31,    32,
      33,     3,     4,     5,    -1,    -1,    -1,     9,    10,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    18,    19,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    65,    -1,    -1,    68,    69,    70,    71,    -1,
      73,    74,    -1,    76,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,    -1,    -1,     9,    10,    90,    -1,    92,
      -1,    15,    -1,    -1,    18,    19,    68,    21,    22,    23,
      24,     4,     5,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    -1,
      92,    24,    -1,    -1,    27,    -1,    -1,    30,    31,    32,
      33,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    20,    -1,    -1,    68,    -1,    -1,    -1,    27,    -1,
      -1,    30,    31,    32,    33,    -1,     4,     5,    -1,    62,
      -1,     9,    10,    -1,    -1,    -1,    -1,    15,    92,    -1,
      18,    19,    -1,    21,    -1,    78,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,    78,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      20,    90,    -1,    92,    -1,    -1,    -1,    27,    -1,    -1,
      30,    31,    32,    33,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    20,    28,    29,    -1,    -1,    -1,
      -1,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      90,    -1,    92,    -1,    77,    78,    79,    80,    81,    82,
      83,    84,    78,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    20,    90,    -1,    92,    -1,    -1,    -1,
      27,    -1,    -1,    30,    31,    32,    33,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    20,    28,    29,
      -1,    -1,    -1,    -1,    27,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    90,    91,    -1,    -1,    77,    78,    79,
      80,    81,    82,    83,    84,    78,    10,    11,    12,    13,
      14,    15,    16,    17,    28,    29,    20,    90,    91,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      20,    -1,    56,    57,    58,    59,    -1,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    77,    78,    79,    80,    81,    82,    83,
      84,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    90,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    10,
      11,    12,    13,    14,    15,    16,    17,    28,    29,    20,
      90,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,
      81,    82,    83,    84,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    97,    -1,    -1,    90,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      97,    54,    55,    56,    57,    58,    59,    60,    61,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    -1,    -1,    -1,    77,    78,    79,    80,    81,    82,
      83,    84,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    97,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    -1,    77,    78,
      79,    80,    81,    82,    83,    84,    28,    29,    77,    78,
      79,    80,    81,    82,    83,    84,    28,    29,    97,    -1,
      -1,    -1,    91,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      82,    83,    84,    28,    29,    77,    78,    79,    80,    81,
      82,    83,    84,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    80,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    78,    79,    80,    81,    82,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    91,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    78,    79,    80,    81,    82,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    91,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    89,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    89,    54,    55,
      56,    57,    58,    59,    60,    61,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    -1,    -1,
      -1,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    94,    -1,
      96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    27,    30,    31,    32,    33,    63,    65,    68,    69,
      70,    71,    73,    74,    76,    90,    92,    99,   100,   102,
     103,   104,   105,   106,   107,   115,   116,   118,   120,   121,
     123,   124,   126,   127,   133,   137,   138,   139,   141,   142,
     143,   144,   152,   153,   155,    88,    89,    90,    87,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    90,    94,    96,   134,   135,    10,   142,    90,    90,
      87,    87,    87,    87,    90,    90,    89,    90,    90,    89,
      10,    15,    62,    78,   136,   137,    75,   136,   136,   142,
       1,   100,     0,     1,    25,    26,   101,   102,    89,    89,
      89,    89,    87,    89,    96,    15,    96,   125,    89,   119,
     136,    37,    38,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   119,   154,   136,   136,    44,    45,    46,
      47,    48,    94,   134,    44,    45,    46,    47,    48,    94,
     134,    15,    91,   119,    91,   119,    34,    35,    36,    41,
     136,   136,   136,    15,   118,   123,   142,   136,   136,    28,
      29,    54,    55,    56,    57,    58,    59,    60,    61,    77,
      78,    79,    80,    81,    82,    83,    84,    24,    92,   122,
      91,    91,    88,    88,    88,    15,    39,    40,   136,    90,
      94,    97,    15,    96,    91,    95,    90,    90,    91,    97,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,    94,    91,    91,    90,    90,    90,    90,    91,
      91,    91,    89,    89,    15,    96,   125,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,    15,   100,   137,    90,    90,
      97,   142,   149,   151,   136,    90,    94,    97,   136,   136,
     136,   136,   136,   136,   136,   136,   117,   118,   120,   121,
     123,   142,    92,   117,   121,   136,   136,    93,    97,    15,
      90,    88,    91,   136,   136,   150,    91,    95,   149,    72,
      92,   130,   136,    91,    95,    91,    91,    91,    95,    89,
      64,    15,    66,   109,   110,   111,    89,    89,    15,    15,
     142,   145,   146,   147,    91,    91,    15,    96,   121,   142,
      91,   142,    92,   119,   129,   130,   131,   132,   136,   140,
     136,    64,   103,   121,   136,    67,    88,   111,   114,    66,
     112,   113,   118,   120,   121,   123,    15,   108,   118,    91,
     108,    91,    93,   148,    91,    95,    97,   150,   121,    96,
     128,    92,   119,    88,    88,    95,    88,    95,    91,    95,
      91,    91,   103,   121,    93,    93,    88,   136,    68,   113,
      89,    89,    89,    42,    43,    91,   117,   122,    91,   121,
      15,    15,    96,   121,   147,    15,   136,    96,    88,    92,
     130,   132,   119,   112,    93,    89,   117,   121,   117,   122,
      91,    97,    97,   136,    68,   121,    97,    89
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,   100,   100,   100,   100,   100,   101,   101,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   103,
     103,   103,   103,   103,   103,   104,   104,   105,   105,   106,
     106,   106,   106,   106,   106,   107,   108,   108,   108,   109,
     109,   110,   110,   111,   111,   112,   112,   113,   113,   113,
     113,   114,   114,   115,   116,   117,   117,   117,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   119,
     119,   120,   120,   120,   120,   120,   121,   121,   122,   123,
     123,   123,   124,   124,   124,   124,   124,   125,   125,   126,
     126,   127,   128,   128,   129,   129,   130,   131,   131,   132,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   134,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   137,   137,   137,   137,
     137,   137,   137,   137,   138,   138,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   140,   141,   141,
     141,   141,   141,   141,   141,   141,   142,   142,   142,   142,
     142,   142,   142,   143,   143,   144,   145,   145,   146,   146,
     147,   148,   148,   149,   149,   150,   150,   151,   151,   152,
     152,   153,   153,   154,   154,   155
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     1,     2,     2,     2,     2,     1,     2,     2,     5,
       7,     7,     6,     8,     8,     7,     8,     5,     5,     9,
       9,     8,     8,     9,     9,     3,     1,     2,     2,     1,
       2,     3,     4,     2,     4,     1,     2,     2,     1,     2,
       2,     3,     5,     2,     2,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     4,     4,     3,     4,     3,     3,     3,     3,     1,
       1,     1,     7,     7,     5,     7,     5,     2,     3,     4,
       2,     5,     3,     4,     1,     3,     3,     1,     3,     3,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     1,     1,     4,     3,     6,
       6,     5,     2,     2,     1,     4,     1,     3,     1,     1,
       8,     6,     6,     6,     6,     8,     8,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     7,     8,     0,     1,     1,     3,
       3,     0,     3,     0,     1,     0,     3,     3,     5,     1,
       2,     8,    10,     0,     1,     4
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* s: lSentencia  */
#line 133 "src/entriesTools/parser.y"
               { ast_root = (yyvsp[0].nodo); (yyval.nodo) = (yyvsp[0].nodo); }
#line 2053 "build/parser.tab.c"
    break;

  case 3: /* lSentencia: lSentencia instruccion  */
#line 137 "src/entriesTools/parser.y"
                                   { agregarHijo((yyvsp[-1].nodo), (yyvsp[0].nodo)); (yyval.nodo) = (yyvsp[-1].nodo);}
#line 2059 "build/parser.tab.c"
    break;

  case 4: /* lSentencia: lSentencia comentario  */
#line 138 "src/entriesTools/parser.y"
                            { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 2065 "build/parser.tab.c"
    break;

  case 5: /* lSentencia: instruccion  */
#line 139 "src/entriesTools/parser.y"
                  {
                        AbstractExpresion* b = nuevoInstruccionesExpresion();
                        agregarHijo(b, (yyvsp[0].nodo));
                        (yyval.nodo) =  b;
                    }
#line 2075 "build/parser.tab.c"
    break;

  case 6: /* lSentencia: lSentencia error '}'  */
#line 145 "src/entriesTools/parser.y"
                           { yyerrok; (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2081 "build/parser.tab.c"
    break;

  case 7: /* lSentencia: error '}'  */
#line 146 "src/entriesTools/parser.y"
                { yyerrok; (yyval.nodo) = nuevoInstruccionesExpresion(); }
#line 2087 "build/parser.tab.c"
    break;

  case 8: /* comentario: TOKEN_COMMENT_LINE  */
#line 149 "src/entriesTools/parser.y"
                               { comments[comment_count++] = (yyvsp[0].string); }
#line 2093 "build/parser.tab.c"
    break;

  case 9: /* comentario: TOKEN_COMMENT_MULTI  */
#line 150 "src/entriesTools/parser.y"
                          { comments[comment_count++] = (yyvsp[0].string); }
#line 2099 "build/parser.tab.c"
    break;

  case 10: /* instruccion: if_statement  */
#line 153 "src/entriesTools/parser.y"
                          {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2105 "build/parser.tab.c"
    break;

  case 11: /* instruccion: switch_statement  */
#line 154 "src/entriesTools/parser.y"
                       {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2111 "build/parser.tab.c"
    break;

  case 12: /* instruccion: break_statement  */
#line 155 "src/entriesTools/parser.y"
                      {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2117 "build/parser.tab.c"
    break;

  case 13: /* instruccion: while_statement  */
#line 156 "src/entriesTools/parser.y"
                      {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2123 "build/parser.tab.c"
    break;

  case 14: /* instruccion: for_statement  */
#line 157 "src/entriesTools/parser.y"
                    {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2129 "build/parser.tab.c"
    break;

  case 15: /* instruccion: for_each_statement  */
#line 158 "src/entriesTools/parser.y"
                         {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2135 "build/parser.tab.c"
    break;

  case 16: /* instruccion: repeat_statement  */
#line 159 "src/entriesTools/parser.y"
                       {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2141 "build/parser.tab.c"
    break;

  case 17: /* instruccion: imprimir ';'  */
#line 160 "src/entriesTools/parser.y"
                   {(yyval.nodo) = (yyvsp[-1].nodo); }
#line 2147 "build/parser.tab.c"
    break;

  case 18: /* instruccion: bloque  */
#line 161 "src/entriesTools/parser.y"
             {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2153 "build/parser.tab.c"
    break;

  case 19: /* instruccion: declaracion_var ';'  */
#line 162 "src/entriesTools/parser.y"
                          {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2159 "build/parser.tab.c"
    break;

  case 20: /* instruccion: funcion_declaracion  */
#line 163 "src/entriesTools/parser.y"
                          {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2165 "build/parser.tab.c"
    break;

  case 21: /* instruccion: main_declaracion  */
#line 164 "src/entriesTools/parser.y"
                       {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2171 "build/parser.tab.c"
    break;

  case 22: /* instruccion: return_stmt ';'  */
#line 165 "src/entriesTools/parser.y"
                      {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2177 "build/parser.tab.c"
    break;

  case 23: /* instruccion: asignacion ';'  */
#line 166 "src/entriesTools/parser.y"
                     {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2183 "build/parser.tab.c"
    break;

  case 24: /* instruccion: asignacion_elemento ';'  */
#line 167 "src/entriesTools/parser.y"
                              {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2189 "build/parser.tab.c"
    break;

  case 25: /* instruccion: postfix ';'  */
#line 168 "src/entriesTools/parser.y"
                  { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 2195 "build/parser.tab.c"
    break;

  case 26: /* instruccion: continue_statement  */
#line 169 "src/entriesTools/parser.y"
                         {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2201 "build/parser.tab.c"
    break;

  case 27: /* instruccion: error ';'  */
#line 171 "src/entriesTools/parser.y"
                { (yyval.nodo) = parser_error_node((yylsp[-1]), "Se esperaba ';'"); yyerrok; }
#line 2207 "build/parser.tab.c"
    break;

  case 28: /* instruccion: error '}'  */
#line 172 "src/entriesTools/parser.y"
                { (yyval.nodo) = parser_error_node((yylsp[-1]), "Se esperaba '}'"); yyerrok; }
#line 2213 "build/parser.tab.c"
    break;

  case 29: /* if_statement: TOKEN_IF '(' expr ')' bloque  */
#line 175 "src/entriesTools/parser.y"
                                           { (yyval.nodo) = nuevoIfExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo), NULL); }
#line 2219 "build/parser.tab.c"
    break;

  case 30: /* if_statement: TOKEN_IF '(' expr ')' bloque TOKEN_ELSE bloque  */
#line 176 "src/entriesTools/parser.y"
                                                     { (yyval.nodo) = nuevoIfExpresion((yyvsp[-4].nodo), (yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2225 "build/parser.tab.c"
    break;

  case 31: /* if_statement: TOKEN_IF '(' expr ')' bloque TOKEN_ELSE if_statement  */
#line 177 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoIfExpresion((yyvsp[-4].nodo), (yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2231 "build/parser.tab.c"
    break;

  case 32: /* if_statement: TOKEN_IF '(' expr ')' instruccion_simple ';'  */
#line 178 "src/entriesTools/parser.y"
                                                   { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, (yyvsp[-1].nodo));
        (yyval.nodo) = nuevoIfExpresion((yyvsp[-3].nodo), nuevoBloqueExpresion(b), NULL); 
    }
#line 2241 "build/parser.tab.c"
    break;

  case 33: /* if_statement: TOKEN_IF '(' expr ')' instruccion_simple ';' TOKEN_ELSE bloque  */
#line 183 "src/entriesTools/parser.y"
                                                                     { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, (yyvsp[-3].nodo));
        (yyval.nodo) = nuevoIfExpresion((yyvsp[-5].nodo), nuevoBloqueExpresion(b), (yyvsp[0].nodo)); 
    }
#line 2251 "build/parser.tab.c"
    break;

  case 34: /* if_statement: TOKEN_IF '(' expr ')' instruccion_simple ';' TOKEN_ELSE if_statement  */
#line 188 "src/entriesTools/parser.y"
                                                                           { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, (yyvsp[-3].nodo));
        (yyval.nodo) = nuevoIfExpresion((yyvsp[-5].nodo), nuevoBloqueExpresion(b), (yyvsp[0].nodo)); 
    }
#line 2261 "build/parser.tab.c"
    break;

  case 35: /* switch_statement: TOKEN_SWITCH '(' expr ')' '{' case_list '}'  */
#line 195 "src/entriesTools/parser.y"
                                                              { (yyval.nodo) = nuevoSwitchExpresion((yyvsp[-4].nodo), (yyvsp[-1].nodo), NULL); }
#line 2267 "build/parser.tab.c"
    break;

  case 36: /* switch_statement: TOKEN_SWITCH '(' expr ')' '{' case_list default_case '}'  */
#line 196 "src/entriesTools/parser.y"
                                                               { (yyval.nodo) = nuevoSwitchExpresion((yyvsp[-5].nodo), (yyvsp[-2].nodo), (yyvsp[-1].nodo)); }
#line 2273 "build/parser.tab.c"
    break;

  case 37: /* while_statement: TOKEN_WHILE '(' expr ')' bloque  */
#line 199 "src/entriesTools/parser.y"
                                                 { (yyval.nodo) = nuevoWhileExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2279 "build/parser.tab.c"
    break;

  case 38: /* while_statement: TOKEN_WHILE '(' expr ')' instruccion_simple  */
#line 200 "src/entriesTools/parser.y"
                                                  { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, (yyvsp[0].nodo));
        (yyval.nodo) = nuevoWhileExpresion((yyvsp[-2].nodo), nuevoBloqueExpresion(b)); 
    }
#line 2289 "build/parser.tab.c"
    break;

  case 39: /* for_statement: TOKEN_FOR '(' declaracion_var ';' expr ';' incremento ')' bloque_for  */
#line 208 "src/entriesTools/parser.y"
                                                                         { (yyval.nodo)=nuevoForExpresion((yyvsp[-6].nodo),(yyvsp[-4].nodo),(yyvsp[-2].nodo),(yyvsp[0].nodo)); }
#line 2295 "build/parser.tab.c"
    break;

  case 40: /* for_statement: TOKEN_FOR '(' declaracion_var ';' expr ';' incremento ')' instruccion_simple  */
#line 209 "src/entriesTools/parser.y"
                                                                               { AbstractExpresion* b=nuevoListaExpresiones(); agregarHijo(b,(yyvsp[0].nodo)); (yyval.nodo)=nuevoForExpresion((yyvsp[-6].nodo),(yyvsp[-4].nodo),(yyvsp[-2].nodo),nuevoBloqueExpresionConContextoPadre(b)); }
#line 2301 "build/parser.tab.c"
    break;

  case 41: /* for_statement: TOKEN_FOR '(' declaracion_var ';' expr ';' ')' bloque_for  */
#line 210 "src/entriesTools/parser.y"
                                                            { (yyval.nodo)=nuevoForExpresion((yyvsp[-5].nodo),(yyvsp[-3].nodo),NULL,(yyvsp[0].nodo)); }
#line 2307 "build/parser.tab.c"
    break;

  case 42: /* for_statement: TOKEN_FOR '(' declaracion_var ';' expr ';' ')' instruccion_simple  */
#line 211 "src/entriesTools/parser.y"
                                                                    { AbstractExpresion* b=nuevoListaExpresiones(); agregarHijo(b,(yyvsp[0].nodo)); (yyval.nodo)=nuevoForExpresion((yyvsp[-5].nodo),(yyvsp[-3].nodo),NULL,nuevoBloqueExpresionConContextoPadre(b)); }
#line 2313 "build/parser.tab.c"
    break;

  case 43: /* for_statement: TOKEN_FOR '(' asignacion ';' expr ';' incremento ')' bloque  */
#line 212 "src/entriesTools/parser.y"
                                                              { (yyval.nodo)=nuevoForExpresion((yyvsp[-6].nodo),(yyvsp[-4].nodo),(yyvsp[-2].nodo),(yyvsp[0].nodo)); }
#line 2319 "build/parser.tab.c"
    break;

  case 44: /* for_statement: TOKEN_FOR '(' asignacion ';' expr ';' incremento ')' instruccion_simple  */
#line 213 "src/entriesTools/parser.y"
                                                                          { AbstractExpresion* b=nuevoListaExpresiones(); agregarHijo(b,(yyvsp[0].nodo)); (yyval.nodo)=nuevoForExpresion((yyvsp[-6].nodo),(yyvsp[-4].nodo),(yyvsp[-2].nodo),nuevoBloqueExpresion(b)); }
#line 2325 "build/parser.tab.c"
    break;

  case 45: /* repeat_statement: TOKEN_REPEAT expr bloque_for  */
#line 217 "src/entriesTools/parser.y"
                                 { (yyval.nodo)=nuevoRepeatExpresion((yyvsp[-1].nodo),(yyvsp[0].nodo)); }
#line 2331 "build/parser.tab.c"
    break;

  case 46: /* incremento: asignacion  */
#line 221 "src/entriesTools/parser.y"
                   { (yyval.nodo) = (yyvsp[0].nodo); }
#line 2337 "build/parser.tab.c"
    break;

  case 47: /* incremento: TOKEN_IDENTIFIER TOKEN_PLUS_PLUS  */
#line 222 "src/entriesTools/parser.y"
                                       { AbstractExpresion* id= nuevoIdentificadorExpresion((yyvsp[-1].string)); SET_POS(id,(yylsp[-1])); AbstractExpresion* uno=nuevoPrimitivoExpresion(strdup("1"),INT); SET_POS(uno,(yylsp[0])); AbstractExpresion* sum=nuevoSumaExpresion(id,uno); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-1].string),sum); SET_POS(asg,(yylsp[-1])); (yyval.nodo)=asg;}
#line 2343 "build/parser.tab.c"
    break;

  case 48: /* incremento: TOKEN_IDENTIFIER TOKEN_MINUS_MINUS  */
#line 223 "src/entriesTools/parser.y"
                                         { AbstractExpresion* id= nuevoIdentificadorExpresion((yyvsp[-1].string)); SET_POS(id,(yylsp[-1])); AbstractExpresion* uno=nuevoPrimitivoExpresion(strdup("1"),INT); SET_POS(uno,(yylsp[0])); AbstractExpresion* res=nuevoRestaExpresion(id,uno); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-1].string),res); SET_POS(asg,(yylsp[-1])); (yyval.nodo)=asg;}
#line 2349 "build/parser.tab.c"
    break;

  case 49: /* case_list: case_item  */
#line 234 "src/entriesTools/parser.y"
                     { 
        /* case_item ya retorna una lista de CaseExpresion; la usamos directamente */
        (yyval.nodo) = (yyvsp[0].nodo);
    }
#line 2358 "build/parser.tab.c"
    break;

  case 50: /* case_list: case_list case_item  */
#line 238 "src/entriesTools/parser.y"
                          {
        /* aplanar: anexar todos los hijos de $2 a la lista existente */
        for(size_t i=0;i<(yyvsp[0].nodo)->numHijos;i++){ agregarHijo((yyvsp[-1].nodo), (yyvsp[0].nodo)->hijos[i]); }
        (yyval.nodo) = (yyvsp[-1].nodo);
    }
#line 2368 "build/parser.tab.c"
    break;

  case 51: /* case_labels: TOKEN_CASE expr ':'  */
#line 245 "src/entriesTools/parser.y"
                                 {
        AbstractExpresion* etiquetas = nuevoListaExpresiones();
        agregarHijo(etiquetas, (yyvsp[-1].nodo));
        (yyval.nodo) = etiquetas;
    }
#line 2378 "build/parser.tab.c"
    break;

  case 52: /* case_labels: case_labels TOKEN_CASE expr ':'  */
#line 250 "src/entriesTools/parser.y"
                                      {
        agregarHijo((yyvsp[-3].nodo), (yyvsp[-1].nodo));
        (yyval.nodo) = (yyvsp[-3].nodo);
    }
#line 2387 "build/parser.tab.c"
    break;

  case 53: /* case_item: case_labels instrucciones_case  */
#line 256 "src/entriesTools/parser.y"
                                          {
        /* Construir lista de CaseExpresion: uno por cada etiqueta */
        AbstractExpresion* lista = nuevoListaExpresiones();
        for(size_t i=0;i<(yyvsp[-1].nodo)->numHijos;i++){
            AbstractExpresion* etiqueta = (yyvsp[-1].nodo)->hijos[i];
            AbstractExpresion* c = nuevoCaseExpresion(etiqueta, (yyvsp[0].nodo), 0);
            agregarHijo(lista, c);
        }
    /* Asignar propiedad única del bloque de instrucciones al primer CaseExpresion */
    if(lista->numHijos>0){ agregarHijo(lista->hijos[0], (yyvsp[0].nodo)); }
        (yyval.nodo) = lista;
    }
#line 2404 "build/parser.tab.c"
    break;

  case 54: /* case_item: case_labels instrucciones_case TOKEN_BREAK ';'  */
#line 268 "src/entriesTools/parser.y"
                                                     {
        AbstractExpresion* lista = nuevoListaExpresiones();
        for(size_t i=0;i<(yyvsp[-3].nodo)->numHijos;i++){
            AbstractExpresion* etiqueta = (yyvsp[-3].nodo)->hijos[i];
            AbstractExpresion* c = nuevoCaseExpresion(etiqueta, (yyvsp[-2].nodo), 1);
            agregarHijo(lista, c);
        }
    if(lista->numHijos>0){ agregarHijo(lista->hijos[0], (yyvsp[-2].nodo)); }
        (yyval.nodo) = lista;
    }
#line 2419 "build/parser.tab.c"
    break;

  case 55: /* instrucciones_case: instruccion_case  */
#line 280 "src/entriesTools/parser.y"
                                     {
        AbstractExpresion* lista = nuevoListaExpresiones();
        agregarHijo(lista, (yyvsp[0].nodo));
        (yyval.nodo) = lista;
    }
#line 2429 "build/parser.tab.c"
    break;

  case 56: /* instrucciones_case: instrucciones_case instruccion_case  */
#line 285 "src/entriesTools/parser.y"
                                          {
        agregarHijo((yyvsp[-1].nodo), (yyvsp[0].nodo));
        (yyval.nodo) = (yyvsp[-1].nodo);
    }
#line 2438 "build/parser.tab.c"
    break;

  case 57: /* instruccion_case: imprimir ';'  */
#line 291 "src/entriesTools/parser.y"
                               {(yyval.nodo) = (yyvsp[-1].nodo); }
#line 2444 "build/parser.tab.c"
    break;

  case 58: /* instruccion_case: bloque  */
#line 292 "src/entriesTools/parser.y"
             {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2450 "build/parser.tab.c"
    break;

  case 59: /* instruccion_case: declaracion_var ';'  */
#line 293 "src/entriesTools/parser.y"
                          {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2456 "build/parser.tab.c"
    break;

  case 60: /* instruccion_case: asignacion ';'  */
#line 294 "src/entriesTools/parser.y"
                     {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2462 "build/parser.tab.c"
    break;

  case 61: /* default_case: TOKEN_DEFAULT ':' instrucciones_case  */
#line 297 "src/entriesTools/parser.y"
                                                   { (yyval.nodo) = (yyvsp[0].nodo); }
#line 2468 "build/parser.tab.c"
    break;

  case 62: /* default_case: TOKEN_DEFAULT ':' instrucciones_case TOKEN_BREAK ';'  */
#line 298 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2474 "build/parser.tab.c"
    break;

  case 63: /* break_statement: TOKEN_BREAK ';'  */
#line 301 "src/entriesTools/parser.y"
                                 { (yyval.nodo) = nuevoBreakExpresion(); SET_POS((yyval.nodo), (yylsp[-1])); }
#line 2480 "build/parser.tab.c"
    break;

  case 64: /* continue_statement: TOKEN_CONTINUE ';'  */
#line 304 "src/entriesTools/parser.y"
                                       { (yyval.nodo) = nuevoContinueExpresion(); SET_POS((yyval.nodo), (yylsp[-1])); }
#line 2486 "build/parser.tab.c"
    break;

  case 65: /* instruccion_simple: imprimir  */
#line 307 "src/entriesTools/parser.y"
                             {(yyval.nodo) = (yyvsp[0].nodo); }
#line 2492 "build/parser.tab.c"
    break;

  case 66: /* instruccion_simple: declaracion_var  */
#line 308 "src/entriesTools/parser.y"
                      {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2498 "build/parser.tab.c"
    break;

  case 67: /* instruccion_simple: asignacion  */
#line 309 "src/entriesTools/parser.y"
                 {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2504 "build/parser.tab.c"
    break;

  case 68: /* asignacion: TOKEN_IDENTIFIER '=' expr  */
#line 312 "src/entriesTools/parser.y"
                                      { (yyval.nodo) = nuevoAsignacionExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); SET_POS((yyval.nodo), (yylsp[-2])); }
#line 2510 "build/parser.tab.c"
    break;

  case 69: /* asignacion: TOKEN_IDENTIFIER TOKEN_PLUS_ASSIGN expr  */
#line 313 "src/entriesTools/parser.y"
                                              { (yyval.nodo) = nuevoAsignacionSumaExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2516 "build/parser.tab.c"
    break;

  case 70: /* asignacion: TOKEN_IDENTIFIER TOKEN_MINUS_ASSIGN expr  */
#line 314 "src/entriesTools/parser.y"
                                               { (yyval.nodo) = nuevoAsignacionRestaExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2522 "build/parser.tab.c"
    break;

  case 71: /* asignacion: TOKEN_IDENTIFIER TOKEN_MUL_ASSIGN expr  */
#line 315 "src/entriesTools/parser.y"
                                             { (yyval.nodo) = nuevoAsignacionMultiplicacionExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2528 "build/parser.tab.c"
    break;

  case 72: /* asignacion: TOKEN_IDENTIFIER TOKEN_DIV_ASSIGN expr  */
#line 316 "src/entriesTools/parser.y"
                                             { (yyval.nodo) = nuevoAsignacionDivisionExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2534 "build/parser.tab.c"
    break;

  case 73: /* asignacion: TOKEN_IDENTIFIER TOKEN_MOD_ASSIGN expr  */
#line 317 "src/entriesTools/parser.y"
                                             { (yyval.nodo) = nuevoAsignacionModuloExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2540 "build/parser.tab.c"
    break;

  case 74: /* asignacion: TOKEN_IDENTIFIER TOKEN_AND_ASSIGN expr  */
#line 318 "src/entriesTools/parser.y"
                                             { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoBitAndExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2546 "build/parser.tab.c"
    break;

  case 75: /* asignacion: TOKEN_IDENTIFIER TOKEN_OR_ASSIGN expr  */
#line 319 "src/entriesTools/parser.y"
                                            { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoBitOrExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2552 "build/parser.tab.c"
    break;

  case 76: /* asignacion: TOKEN_IDENTIFIER TOKEN_XOR_ASSIGN expr  */
#line 320 "src/entriesTools/parser.y"
                                             { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoBitXorExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2558 "build/parser.tab.c"
    break;

  case 77: /* asignacion: TOKEN_IDENTIFIER TOKEN_SHL_ASSIGN expr  */
#line 321 "src/entriesTools/parser.y"
                                             { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoShiftLeftExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2564 "build/parser.tab.c"
    break;

  case 78: /* asignacion: TOKEN_IDENTIFIER TOKEN_SHR_ASSIGN expr  */
#line 322 "src/entriesTools/parser.y"
                                             { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoShiftRightExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2570 "build/parser.tab.c"
    break;

  case 79: /* lista_Expr: lista_Expr ',' expr  */
#line 324 "src/entriesTools/parser.y"
                                 { agregarHijo((yyvsp[-2].nodo), (yyvsp[0].nodo)); (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2576 "build/parser.tab.c"
    break;

  case 80: /* lista_Expr: expr  */
#line 325 "src/entriesTools/parser.y"
           { 
                AbstractExpresion* b = nuevoListaExpresiones();
                agregarHijo(b, (yyvsp[0].nodo));
                (yyval.nodo) =  b;
            }
#line 2586 "build/parser.tab.c"
    break;

  case 81: /* imprimir: TOKEN_PRINT '(' lista_Expr ')'  */
#line 332 "src/entriesTools/parser.y"
                                         { (yyval.nodo) =  nuevoPrintExpresion((yyvsp[-1].nodo), 0); }
#line 2592 "build/parser.tab.c"
    break;

  case 82: /* imprimir: TOKEN_SYSTEM_OUT_PRINTLN '(' lista_Expr ')'  */
#line 333 "src/entriesTools/parser.y"
                                                  { (yyval.nodo) =  nuevoPrintExpresion((yyvsp[-1].nodo), 1); }
#line 2598 "build/parser.tab.c"
    break;

  case 83: /* imprimir: TOKEN_SYSTEM_OUT_PRINTLN '(' ')'  */
#line 334 "src/entriesTools/parser.y"
                                       { (yyval.nodo) = nuevoPrintExpresion(nuevoListaExpresiones(), 1); }
#line 2604 "build/parser.tab.c"
    break;

  case 84: /* imprimir: TOKEN_SYSTEM_OUT_PRINT '(' lista_Expr ')'  */
#line 335 "src/entriesTools/parser.y"
                                                { (yyval.nodo) =  nuevoPrintExpresion((yyvsp[-1].nodo), 0); }
#line 2610 "build/parser.tab.c"
    break;

  case 85: /* imprimir: TOKEN_SYSTEM_OUT_PRINT '(' ')'  */
#line 336 "src/entriesTools/parser.y"
                                     { (yyval.nodo) = nuevoPrintExpresion(nuevoListaExpresiones(), 0); }
#line 2616 "build/parser.tab.c"
    break;

  case 86: /* bloque: '{' lSentencia '}'  */
#line 339 "src/entriesTools/parser.y"
                           { (yyval.nodo) = nuevoBloqueExpresion((yyvsp[-1].nodo)); }
#line 2622 "build/parser.tab.c"
    break;

  case 87: /* bloque: '{' error '}'  */
#line 340 "src/entriesTools/parser.y"
                    { (yyval.nodo) = nuevoBloqueExpresion(nuevoListaExpresiones()); yyerrok; }
#line 2628 "build/parser.tab.c"
    break;

  case 88: /* bloque_for: '{' lSentencia '}'  */
#line 342 "src/entriesTools/parser.y"
                               { (yyval.nodo) = nuevoBloqueExpresionConContextoPadre((yyvsp[-1].nodo)); }
#line 2634 "build/parser.tab.c"
    break;

  case 92: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' TOKEN_NEW tipoPrimitivo dims_expr_list  */
#line 357 "src/entriesTools/parser.y"
                                                                                           {
        int declaredDims = (yyvsp[-5].boolean); int newDims = (int)(yyvsp[0].nodo)->numHijos;
        if(declaredDims != newDims){ (yyval.nodo) = parser_error_node((yylsp[-4]), "Número de brackets (%d) no coincide con dimensiones new (%d)", declaredDims, newDims); }
        else if((yyvsp[-6].tipoDato) != (yyvsp[-1].tipoDato)){ (yyval.nodo) = parser_error_node((yylsp[-6]), "Tipo en new (%d) difiere del declarado (%d)", (yyvsp[-1].tipoDato), (yyvsp[-6].tipoDato)); }
        else {
            AbstractExpresion* nodo=NULL; 
            if(newDims==1){ nodo = nuevoArrayDeclaracion((yyvsp[-6].tipoDato), (yyvsp[-4].string), (yyvsp[0].nodo)->hijos[0]); }
            else if(newDims==2){ nodo = nuevoMatrixDeclaracion((yyvsp[-6].tipoDato), (yyvsp[-4].string), (yyvsp[0].nodo)->hijos[0], (yyvsp[0].nodo)->hijos[1]); }
            else {
                AbstractExpresion** dims = malloc(sizeof(AbstractExpresion*)*newDims);
                for(int i=0;i<newDims;i++) dims[i] = (yyvsp[0].nodo)->hijos[i];
                nodo = nuevoMultiArrayDeclaracion((yyvsp[-6].tipoDato), (yyvsp[-4].string), newDims, dims);
            }
            /* Propagar posición del identificador */
            nodo->linea = (yylsp[-4]).first_line; nodo->columna = (yylsp[-4]).first_column; (yyval.nodo) = nodo;
        }
    }
#line 2656 "build/parser.tab.c"
    break;

  case 93: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' '{' lista_Expr '}'  */
#line 375 "src/entriesTools/parser.y"
                                                                       {
        if((yyvsp[-5].boolean) != 1){ (yyval.nodo) = parser_error_node((yylsp[-4]), "Literal 1D usado pero se declararon %d dimensiones", (yyvsp[-5].boolean)); }
    else { AbstractExpresion* nodo = nuevoArrayLiteralDeclaracion((yyvsp[-6].tipoDato), (yyvsp[-4].string), (yyvsp[-1].nodo)); nodo->linea=(yylsp[-4]).first_line; nodo->columna=(yylsp[-4]).first_column; (yyval.nodo)=nodo; }
    }
#line 2665 "build/parser.tab.c"
    break;

  case 94: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' bloque2D  */
#line 380 "src/entriesTools/parser.y"
                                                             {
        if((yyvsp[-3].boolean) != 2){ (yyval.nodo) = parser_error_node((yylsp[-2]), "Literal 2D usado pero se declararon %d dimensiones", (yyvsp[-3].boolean)); }
    else { AbstractExpresion* nodo = nuevoMatrixLiteralDeclaracion((yyvsp[-4].tipoDato), (yyvsp[-2].string), (yyvsp[0].nodo)); nodo->linea=(yylsp[-2]).first_line; nodo->columna=(yylsp[-2]).first_column; (yyval.nodo)=nodo; }
    }
#line 2674 "build/parser.tab.c"
    break;

  case 95: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' '{' lista_bloques2D '}'  */
#line 385 "src/entriesTools/parser.y"
                                                                            {
        if((yyvsp[-5].boolean) != 3){ (yyval.nodo) = parser_error_node((yylsp[-4]), "Literal 3D usado pero se declararon %d dimensiones", (yyvsp[-5].boolean)); }
    else { AbstractExpresion* nodo = nuevoArray3DLiteralDeclaracion((yyvsp[-6].tipoDato), (yyvsp[-4].string), (yyvsp[-1].nodo)); nodo->linea=(yylsp[-4]).first_line; nodo->columna=(yylsp[-4]).first_column; (yyval.nodo)=nodo; }
    }
#line 2683 "build/parser.tab.c"
    break;

  case 96: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' expr  */
#line 390 "src/entriesTools/parser.y"
                                                         {
    AbstractExpresion* nodo = nuevoArrayDeclaracionDesdeExpr((yyvsp[-4].tipoDato), (yyvsp[-2].string), (yyvsp[0].nodo)); nodo->linea=(yylsp[-2]).first_line; nodo->columna=(yylsp[-2]).first_column; (yyval.nodo) = nodo; }
#line 2690 "build/parser.tab.c"
    break;

  case 97: /* brackets_seq: '[' ']'  */
#line 395 "src/entriesTools/parser.y"
                      { (yyval.boolean) = 1; }
#line 2696 "build/parser.tab.c"
    break;

  case 98: /* brackets_seq: brackets_seq '[' ']'  */
#line 396 "src/entriesTools/parser.y"
                           { (yyval.boolean) = (yyvsp[-2].boolean) + 1; }
#line 2702 "build/parser.tab.c"
    break;

  case 99: /* var_decl: tipoPrimitivo TOKEN_IDENTIFIER '=' expr  */
#line 399 "src/entriesTools/parser.y"
                                                { (yyval.nodo) = nuevoDeclaracionVariables((yyvsp[-3].tipoDato),(yyvsp[-2].string),(yyvsp[0].nodo),0); ((DeclaracionVariable*)(yyval.nodo))->linea = (yylsp[-2]).first_line; ((DeclaracionVariable*)(yyval.nodo))->columna = (yylsp[-2]).first_column; }
#line 2708 "build/parser.tab.c"
    break;

  case 100: /* var_decl: tipoPrimitivo TOKEN_IDENTIFIER  */
#line 400 "src/entriesTools/parser.y"
                                     { (yyval.nodo) = nuevoDeclaracionVariables((yyvsp[-1].tipoDato),(yyvsp[0].string),NULL,0); ((DeclaracionVariable*)(yyval.nodo))->linea = (yylsp[0]).first_line; ((DeclaracionVariable*)(yyval.nodo))->columna = (yylsp[0]).first_column; }
#line 2714 "build/parser.tab.c"
    break;

  case 101: /* final_var_decl: TOKEN_FINAL tipoPrimitivo TOKEN_IDENTIFIER '=' expr  */
#line 403 "src/entriesTools/parser.y"
                                                        { (yyval.nodo) = nuevoDeclaracionVariables((yyvsp[-3].tipoDato),(yyvsp[-2].string),(yyvsp[0].nodo),1); ((DeclaracionVariable*)(yyval.nodo))->linea = (yylsp[-2]).first_line; ((DeclaracionVariable*)(yyval.nodo))->columna = (yylsp[-2]).first_column; }
#line 2720 "build/parser.tab.c"
    break;

  case 102: /* dims_expr_list: '[' expr ']'  */
#line 410 "src/entriesTools/parser.y"
                             { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l,(yyvsp[-1].nodo)); (yyval.nodo) = l; }
#line 2726 "build/parser.tab.c"
    break;

  case 103: /* dims_expr_list: dims_expr_list '[' expr ']'  */
#line 411 "src/entriesTools/parser.y"
                                      { agregarHijo((yyvsp[-3].nodo),(yyvsp[-1].nodo)); (yyval.nodo) = (yyvsp[-3].nodo); }
#line 2732 "build/parser.tab.c"
    break;

  case 104: /* lista_bloques2D: bloque2D  */
#line 419 "src/entriesTools/parser.y"
                          { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l, (yyvsp[0].nodo)); (yyval.nodo) = l; }
#line 2738 "build/parser.tab.c"
    break;

  case 105: /* lista_bloques2D: lista_bloques2D ',' bloque2D  */
#line 420 "src/entriesTools/parser.y"
                                   { agregarHijo((yyvsp[-2].nodo), (yyvsp[0].nodo)); (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2744 "build/parser.tab.c"
    break;

  case 106: /* bloque2D: '{' filas_lista '}'  */
#line 422 "src/entriesTools/parser.y"
                              { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 2750 "build/parser.tab.c"
    break;

  case 107: /* filas_lista: fila_matriz  */
#line 424 "src/entriesTools/parser.y"
                         { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l, (yyvsp[0].nodo)); (yyval.nodo) = l; }
#line 2756 "build/parser.tab.c"
    break;

  case 108: /* filas_lista: filas_lista ',' fila_matriz  */
#line 425 "src/entriesTools/parser.y"
                                  { agregarHijo((yyvsp[-2].nodo), (yyvsp[0].nodo)); (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2762 "build/parser.tab.c"
    break;

  case 109: /* fila_matriz: '{' lista_Expr '}'  */
#line 427 "src/entriesTools/parser.y"
                                { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 2768 "build/parser.tab.c"
    break;

  case 110: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una '=' expr  */
#line 429 "src/entriesTools/parser.y"
                                                           {
    AbstractExpresion* idx = (yyvsp[-2].nodo)->hijos[0]; (yyval.nodo) = nuevoArrayAsignacionElemento((yyvsp[-3].string), idx, (yyvsp[0].nodo)); }
#line 2775 "build/parser.tab.c"
    break;

  case 111: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi '=' expr  */
#line 431 "src/entriesTools/parser.y"
                                              {
        size_t n=(yyvsp[-2].nodo)->numHijos; if (n==2) (yyval.nodo)=nuevoMatrixAsignacionElemento((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[-2].nodo)->hijos[1], (yyvsp[0].nodo)); else (yyval.nodo)=nuevoMultiArrayAsignacionElemento((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo)); }
#line 2782 "build/parser.tab.c"
    break;

  case 112: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_PLUS_ASSIGN expr  */
#line 434 "src/entriesTools/parser.y"
                                                          { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_ADD); }
#line 2788 "build/parser.tab.c"
    break;

  case 113: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_MINUS_ASSIGN expr  */
#line 435 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_SUB); }
#line 2794 "build/parser.tab.c"
    break;

  case 114: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_MUL_ASSIGN expr  */
#line 436 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_MUL); }
#line 2800 "build/parser.tab.c"
    break;

  case 115: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_DIV_ASSIGN expr  */
#line 437 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_DIV); }
#line 2806 "build/parser.tab.c"
    break;

  case 116: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_MOD_ASSIGN expr  */
#line 438 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_MOD); }
#line 2812 "build/parser.tab.c"
    break;

  case 117: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_PLUS_ASSIGN expr  */
#line 440 "src/entriesTools/parser.y"
                                                            { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_ADD); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_ADD); }
#line 2818 "build/parser.tab.c"
    break;

  case 118: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_MINUS_ASSIGN expr  */
#line 441 "src/entriesTools/parser.y"
                                                             { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_SUB); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_SUB); }
#line 2824 "build/parser.tab.c"
    break;

  case 119: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_MUL_ASSIGN expr  */
#line 442 "src/entriesTools/parser.y"
                                                           { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_MUL); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_MUL); }
#line 2830 "build/parser.tab.c"
    break;

  case 120: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_DIV_ASSIGN expr  */
#line 443 "src/entriesTools/parser.y"
                                                           { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_DIV); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_DIV); }
#line 2836 "build/parser.tab.c"
    break;

  case 121: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_MOD_ASSIGN expr  */
#line 444 "src/entriesTools/parser.y"
                                                           { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_MOD); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_MOD); }
#line 2842 "build/parser.tab.c"
    break;

  case 122: /* indices_una: '[' expr ']'  */
#line 448 "src/entriesTools/parser.y"
                          { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l,(yyvsp[-1].nodo)); (yyval.nodo)=l; }
#line 2848 "build/parser.tab.c"
    break;

  case 123: /* indices_multi: indices_una indices_una  */
#line 449 "src/entriesTools/parser.y"
                                       { /* concat */ for(size_t i=0;i<(yyvsp[0].nodo)->numHijos;i++) agregarHijo((yyvsp[-1].nodo),(yyvsp[0].nodo)->hijos[i]); (yyval.nodo)=(yyvsp[-1].nodo); }
#line 2854 "build/parser.tab.c"
    break;

  case 124: /* indices_multi: indices_multi indices_una  */
#line 450 "src/entriesTools/parser.y"
                                { for(size_t i=0;i<(yyvsp[0].nodo)->numHijos;i++) agregarHijo((yyvsp[-1].nodo),(yyvsp[0].nodo)->hijos[i]); (yyval.nodo)=(yyvsp[-1].nodo); }
#line 2860 "build/parser.tab.c"
    break;

  case 125: /* expr: expr '+' expr  */
#line 467 "src/entriesTools/parser.y"
                      { (yyval.nodo) =  nuevoSumaExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo));  }
#line 2866 "build/parser.tab.c"
    break;

  case 126: /* expr: expr '-' expr  */
#line 468 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoRestaExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2872 "build/parser.tab.c"
    break;

  case 127: /* expr: expr '*' expr  */
#line 469 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoMultiplicacionExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2878 "build/parser.tab.c"
    break;

  case 128: /* expr: expr '/' expr  */
#line 470 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoDivisionExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2884 "build/parser.tab.c"
    break;

  case 129: /* expr: expr '%' expr  */
#line 471 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoModuloExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2890 "build/parser.tab.c"
    break;

  case 130: /* expr: expr '&' expr  */
#line 472 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoBitAndExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2896 "build/parser.tab.c"
    break;

  case 131: /* expr: expr '|' expr  */
#line 473 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoBitOrExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2902 "build/parser.tab.c"
    break;

  case 132: /* expr: expr '^' expr  */
#line 474 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoBitXorExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2908 "build/parser.tab.c"
    break;

  case 133: /* expr: expr TOKEN_SHIFT_LEFT expr  */
#line 475 "src/entriesTools/parser.y"
                                 { (yyval.nodo) =  nuevoShiftLeftExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2914 "build/parser.tab.c"
    break;

  case 134: /* expr: expr TOKEN_SHIFT_RIGHT expr  */
#line 476 "src/entriesTools/parser.y"
                                  { (yyval.nodo) =  nuevoShiftRightExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2920 "build/parser.tab.c"
    break;

  case 135: /* expr: expr TOKEN_EQUAL expr  */
#line 477 "src/entriesTools/parser.y"
                            { (yyval.nodo) =  nuevoIgualdadExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2926 "build/parser.tab.c"
    break;

  case 136: /* expr: expr TOKEN_NOT_EQUAL expr  */
#line 478 "src/entriesTools/parser.y"
                                { (yyval.nodo) =  nuevoDesigualdadExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2932 "build/parser.tab.c"
    break;

  case 137: /* expr: expr TOKEN_GREATER expr  */
#line 479 "src/entriesTools/parser.y"
                              { (yyval.nodo) =  nuevoMayorQueExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2938 "build/parser.tab.c"
    break;

  case 138: /* expr: expr TOKEN_LESS expr  */
#line 480 "src/entriesTools/parser.y"
                           { (yyval.nodo) =  nuevoMenorQueExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2944 "build/parser.tab.c"
    break;

  case 139: /* expr: expr TOKEN_GREATER_EQUAL expr  */
#line 481 "src/entriesTools/parser.y"
                                    { (yyval.nodo) =  nuevoMayorIgualQueExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2950 "build/parser.tab.c"
    break;

  case 140: /* expr: expr TOKEN_LESS_EQUAL expr  */
#line 482 "src/entriesTools/parser.y"
                                 { (yyval.nodo) =  nuevoMenorIgualQueExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2956 "build/parser.tab.c"
    break;

  case 141: /* expr: expr TOKEN_AND expr  */
#line 483 "src/entriesTools/parser.y"
                          { (yyval.nodo) =  nuevoAndExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2962 "build/parser.tab.c"
    break;

  case 142: /* expr: expr TOKEN_OR expr  */
#line 484 "src/entriesTools/parser.y"
                         { (yyval.nodo) =  nuevoOrExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2968 "build/parser.tab.c"
    break;

  case 143: /* expr: TOKEN_NOT expr  */
#line 485 "src/entriesTools/parser.y"
                     { (yyval.nodo) =  nuevoNotExpresion((yyvsp[0].nodo)); }
#line 2974 "build/parser.tab.c"
    break;

  case 144: /* expr: '-' expr  */
#line 486 "src/entriesTools/parser.y"
                          { (yyval.nodo) =  nuevoUnarioExpresion((yyvsp[0].nodo));  }
#line 2980 "build/parser.tab.c"
    break;

  case 145: /* expr: postfix  */
#line 487 "src/entriesTools/parser.y"
              { (yyval.nodo) = (yyvsp[0].nodo); }
#line 2986 "build/parser.tab.c"
    break;

  case 146: /* postfix: unary  */
#line 490 "src/entriesTools/parser.y"
               { (yyval.nodo) = (yyvsp[0].nodo); }
#line 2992 "build/parser.tab.c"
    break;

  case 147: /* postfix: postfix '[' expr ']'  */
#line 491 "src/entriesTools/parser.y"
                           { (yyval.nodo) = nuevoArrayAcceso((yyvsp[-3].nodo), (yyvsp[-1].nodo)); }
#line 2998 "build/parser.tab.c"
    break;

  case 148: /* postfix: postfix '.' TOKEN_LENGTH  */
#line 492 "src/entriesTools/parser.y"
                               { (yyval.nodo) = nuevoArrayLength((yyvsp[-2].nodo)); }
#line 3004 "build/parser.tab.c"
    break;

  case 149: /* postfix: postfix '.' TOKEN_ADD '(' expr ')'  */
#line 493 "src/entriesTools/parser.y"
                                         { (yyval.nodo) = nuevoArrayAdd((yyvsp[-5].nodo), (yyvsp[-1].nodo)); }
#line 3010 "build/parser.tab.c"
    break;

  case 150: /* postfix: postfix '.' TOKEN_IDENTIFIER '(' expr ')'  */
#line 494 "src/entriesTools/parser.y"
                                                { if(strcmp((yyvsp[-3].string),"equals")==0){ (yyval.nodo) = nuevoIgualdadExpresion((yyvsp[-5].nodo),(yyvsp[-1].nodo));} else { (yyval.nodo)=(yyvsp[-5].nodo); } }
#line 3016 "build/parser.tab.c"
    break;

  case 151: /* postfix: postfix '.' TOKEN_IDENTIFIER '(' ')'  */
#line 495 "src/entriesTools/parser.y"
                                           { if(strcmp((yyvsp[-2].string),"equals")==0){ AbstractExpresion* e=parser_error_node((yylsp[-2]),"método equals requiere un argumento"); (yyval.nodo)=(yyvsp[-4].nodo); (void)e; } else { (yyval.nodo)=(yyvsp[-4].nodo); } }
#line 3022 "build/parser.tab.c"
    break;

  case 152: /* postfix: TOKEN_IDENTIFIER TOKEN_PLUS_PLUS  */
#line 496 "src/entriesTools/parser.y"
                                       {
        AbstractExpresion* id1 = nuevoIdentificadorExpresion((yyvsp[-1].string));
        AbstractExpresion* uno1 = nuevoPrimitivoExpresion(strdup("1"), INT);
        AbstractExpresion* sum1 = nuevoSumaExpresion(id1, uno1);
        (yyval.nodo) = nuevoAsignacionExpresion((yyvsp[-1].string), sum1);
    }
#line 3033 "build/parser.tab.c"
    break;

  case 153: /* postfix: TOKEN_IDENTIFIER TOKEN_MINUS_MINUS  */
#line 502 "src/entriesTools/parser.y"
                                         {
        AbstractExpresion* id2 = nuevoIdentificadorExpresion((yyvsp[-1].string));
        AbstractExpresion* uno2 = nuevoPrimitivoExpresion(strdup("1"), INT);
        AbstractExpresion* res2 = nuevoRestaExpresion(id2, uno2);
        (yyval.nodo) = nuevoAsignacionExpresion((yyvsp[-1].string), res2);
    }
#line 3044 "build/parser.tab.c"
    break;

  case 154: /* unary: atom  */
#line 510 "src/entriesTools/parser.y"
            { (yyval.nodo) = (yyvsp[0].nodo); }
#line 3050 "build/parser.tab.c"
    break;

  case 155: /* unary: '(' tipoPrimitivo ')' postfix  */
#line 514 "src/entriesTools/parser.y"
                                                { (yyval.nodo) = nuevoCastExpresion((yyvsp[-2].tipoDato), (yyvsp[0].nodo)); }
#line 3056 "build/parser.tab.c"
    break;

  case 156: /* atom: primitivo  */
#line 517 "src/entriesTools/parser.y"
                { (yyval.nodo) = (yyvsp[0].nodo); }
#line 3062 "build/parser.tab.c"
    break;

  case 157: /* atom: '(' expr ')'  */
#line 518 "src/entriesTools/parser.y"
                   { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 3068 "build/parser.tab.c"
    break;

  case 158: /* atom: TOKEN_IDENTIFIER  */
#line 519 "src/entriesTools/parser.y"
                       { (yyval.nodo) = nuevoIdentificadorExpresion((yyvsp[0].string)); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3074 "build/parser.tab.c"
    break;

  case 159: /* atom: llamada_funcion  */
#line 520 "src/entriesTools/parser.y"
                      { (yyval.nodo) = (yyvsp[0].nodo); /* la llamada ya debería heredar pos de su identificador interno */ }
#line 3080 "build/parser.tab.c"
    break;

  case 160: /* atom: TOKEN_ARRAYS '.' TOKEN_INDEXOF '(' expr ',' expr ')'  */
#line 521 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoArraysIndexOf((yyvsp[-3].nodo), (yyvsp[-1].nodo)); }
#line 3086 "build/parser.tab.c"
    break;

  case 161: /* atom: TOKEN_INTEGER_CLASS '.' TOKEN_PARSE_INT '(' expr ')'  */
#line 522 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoParseEntero((yyvsp[-1].nodo)); }
#line 3092 "build/parser.tab.c"
    break;

  case 162: /* atom: TOKEN_DOUBLE_CLASS '.' TOKEN_PARSE_DOUBLE '(' expr ')'  */
#line 523 "src/entriesTools/parser.y"
                                                             { (yyval.nodo) = nuevoParseDouble((yyvsp[-1].nodo)); }
#line 3098 "build/parser.tab.c"
    break;

  case 163: /* atom: TOKEN_FLOAT_CLASS '.' TOKEN_PARSE_FLOAT '(' expr ')'  */
#line 524 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoParseFloat((yyvsp[-1].nodo)); }
#line 3104 "build/parser.tab.c"
    break;

  case 164: /* atom: TOKEN_DSTRING '.' TOKEN_VALUE_OF '(' expr ')'  */
#line 525 "src/entriesTools/parser.y"
                                                    { (yyval.nodo) = nuevoStringValueOf((yyvsp[-1].nodo)); }
#line 3110 "build/parser.tab.c"
    break;

  case 165: /* atom: TOKEN_DSTRING '.' TOKEN_JOIN '(' expr ',' expr ')'  */
#line 526 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoStringJoin((yyvsp[-3].nodo), (yyvsp[-1].nodo), 1); }
#line 3116 "build/parser.tab.c"
    break;

  case 166: /* atom: TOKEN_DSTRING '.' TOKEN_JOIN '(' expr ',' join_variadic_args ')'  */
#line 527 "src/entriesTools/parser.y"
                                                                       { (yyval.nodo) = nuevoStringJoin((yyvsp[-3].nodo), (yyvsp[-1].nodo), 0); }
#line 3122 "build/parser.tab.c"
    break;

  case 167: /* join_variadic_args: expr ',' lista_Expr  */
#line 530 "src/entriesTools/parser.y"
                                        {
        /* crear lista que contenga primer expr y luego los de lista_Expr */
        AbstractExpresion* l = nuevoListaExpresiones();
        agregarHijo(l, (yyvsp[-2].nodo));
        for(size_t i=0;i<(yyvsp[0].nodo)->numHijos;i++){ agregarHijo(l, (yyvsp[0].nodo)->hijos[i]); }
        (yyval.nodo) = l;
    }
#line 3134 "build/parser.tab.c"
    break;

  case 168: /* primitivo: TOKEN_UNSIGNED_INTEGER  */
#line 538 "src/entriesTools/parser.y"
                                  { (yyval.nodo) = nuevoPrimitivoExpresion((yyvsp[0].string), INT); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3140 "build/parser.tab.c"
    break;

  case 169: /* primitivo: TOKEN_STRING  */
#line 539 "src/entriesTools/parser.y"
                   { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), STRING); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3146 "build/parser.tab.c"
    break;

  case 170: /* primitivo: TOKEN_REAL_FLOAT  */
#line 540 "src/entriesTools/parser.y"
                       { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), FLOAT); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3152 "build/parser.tab.c"
    break;

  case 171: /* primitivo: TOKEN_REAL  */
#line 541 "src/entriesTools/parser.y"
                 { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), DOUBLE); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3158 "build/parser.tab.c"
    break;

  case 172: /* primitivo: TOKEN_CHAR_LITERAL  */
#line 542 "src/entriesTools/parser.y"
                         { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), CHAR); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3164 "build/parser.tab.c"
    break;

  case 173: /* primitivo: TOKEN_TRUE  */
#line 543 "src/entriesTools/parser.y"
                 { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), BOOLEAN); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3170 "build/parser.tab.c"
    break;

  case 174: /* primitivo: TOKEN_FALSE  */
#line 544 "src/entriesTools/parser.y"
                  { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), BOOLEAN); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3176 "build/parser.tab.c"
    break;

  case 175: /* primitivo: TOKEN_NULL  */
#line 545 "src/entriesTools/parser.y"
                 { (yyval.nodo) = nuevoPrimitivoExpresion(NULL, NULO); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3182 "build/parser.tab.c"
    break;

  case 176: /* tipoPrimitivo: TOKEN_DINT  */
#line 548 "src/entriesTools/parser.y"
                          { (yyval.tipoDato) = INT; }
#line 3188 "build/parser.tab.c"
    break;

  case 177: /* tipoPrimitivo: TOKEN_DFLOAT  */
#line 549 "src/entriesTools/parser.y"
                   { (yyval.tipoDato) = FLOAT; }
#line 3194 "build/parser.tab.c"
    break;

  case 178: /* tipoPrimitivo: TOKEN_DDOUBLE  */
#line 550 "src/entriesTools/parser.y"
                    { (yyval.tipoDato) = DOUBLE; }
#line 3200 "build/parser.tab.c"
    break;

  case 179: /* tipoPrimitivo: TOKEN_DSTRING  */
#line 551 "src/entriesTools/parser.y"
                    { (yyval.tipoDato) = STRING; }
#line 3206 "build/parser.tab.c"
    break;

  case 180: /* tipoPrimitivo: TOKEN_DBOOLEAN  */
#line 552 "src/entriesTools/parser.y"
                     { (yyval.tipoDato) = BOOLEAN; }
#line 3212 "build/parser.tab.c"
    break;

  case 181: /* tipoPrimitivo: TOKEN_DCHAR  */
#line 553 "src/entriesTools/parser.y"
                  { (yyval.tipoDato) = CHAR; }
#line 3218 "build/parser.tab.c"
    break;

  case 182: /* tipoPrimitivo: TOKEN_DVOID  */
#line 554 "src/entriesTools/parser.y"
                  { (yyval.tipoDato) = VOID; }
#line 3224 "build/parser.tab.c"
    break;

  case 183: /* funcion_declaracion: tipoPrimitivo TOKEN_IDENTIFIER '(' param_opt ')' bloque  */
#line 559 "src/entriesTools/parser.y"
                                                                    { 
        if((yyvsp[-2].paramList)){ (yyval.nodo) = nuevoFuncionDeclaracion((yyvsp[-5].tipoDato), (yyvsp[-4].string), (yyvsp[-2].paramList)->names, (yyvsp[-2].paramList)->types, (yyvsp[-2].paramList)->count, (yyvsp[0].nodo), 0); }
        else { (yyval.nodo) = nuevoFuncionDeclaracion((yyvsp[-5].tipoDato), (yyvsp[-4].string), NULL, NULL, 0, (yyvsp[0].nodo), 0); }
        ((FuncionDecl*)(yyval.nodo))->linea = (yylsp[-4]).first_line; ((FuncionDecl*)(yyval.nodo))->columna = (yylsp[-4]).first_column;
            }
#line 3234 "build/parser.tab.c"
    break;

  case 184: /* funcion_declaracion: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '(' param_opt ')' bloque  */
#line 564 "src/entriesTools/parser.y"
                                                                               {
                /* Retorno array: int[][] nombre(...) */
                if((yyvsp[-5].boolean) < 1){ (yyval.nodo) = parser_error_node((yylsp[-4]), "Número de brackets de retorno inválido"); }
                else {
                        if((yyvsp[-2].paramList)){ (yyval.nodo) = nuevoFuncionDeclaracion(ARRAY, (yyvsp[-4].string), (yyvsp[-2].paramList)->names, (yyvsp[-2].paramList)->types, (yyvsp[-2].paramList)->count, (yyvsp[0].nodo), (yyvsp[-5].boolean)); }
                        else { (yyval.nodo) = nuevoFuncionDeclaracion(ARRAY, (yyvsp[-4].string), NULL, NULL, 0, (yyvsp[0].nodo), (yyvsp[-5].boolean)); }
                        ((FuncionDecl*)(yyval.nodo))->linea = (yylsp[-4]).first_line; ((FuncionDecl*)(yyval.nodo))->columna = (yylsp[-4]).first_column;
                }
            }
#line 3248 "build/parser.tab.c"
    break;

  case 185: /* main_declaracion: TOKEN_PUBLIC TOKEN_STATIC TOKEN_DVOID TOKEN_IDENTIFIER '(' main_params_opt ')' bloque  */
#line 576 "src/entriesTools/parser.y"
                                                                                                        { (yyval.nodo) = (yyvsp[0].nodo); }
#line 3254 "build/parser.tab.c"
    break;

  case 191: /* main_param_array_brackets: %empty  */
#line 580 "src/entriesTools/parser.y"
                                       { /* 0 dims */ }
#line 3260 "build/parser.tab.c"
    break;

  case 192: /* main_param_array_brackets: main_param_array_brackets '[' ']'  */
#line 580 "src/entriesTools/parser.y"
                                                                                            { /* accum dims ignored */ }
#line 3266 "build/parser.tab.c"
    break;

  case 193: /* param_opt: %empty  */
#line 582 "src/entriesTools/parser.y"
                       { (yyval.paramList) = NULL; }
#line 3272 "build/parser.tab.c"
    break;

  case 194: /* param_opt: lista_parametros  */
#line 583 "src/entriesTools/parser.y"
                       { (yyval.paramList) = (yyvsp[0].paramList); }
#line 3278 "build/parser.tab.c"
    break;

  case 195: /* param_array_brackets: %empty  */
#line 586 "src/entriesTools/parser.y"
                                  { (yyval.boolean) = 0; }
#line 3284 "build/parser.tab.c"
    break;

  case 196: /* param_array_brackets: param_array_brackets '[' ']'  */
#line 587 "src/entriesTools/parser.y"
                                   { (yyval.boolean) = (yyvsp[-2].boolean) + 1; }
#line 3290 "build/parser.tab.c"
    break;

  case 197: /* lista_parametros: tipoPrimitivo param_array_brackets TOKEN_IDENTIFIER  */
#line 589 "src/entriesTools/parser.y"
                                                                      { 
        ParamList* pl = malloc(sizeof(ParamList));
        pl->count=1; pl->names=malloc(sizeof(char*)); pl->types=malloc(sizeof(TipoDato));
        pl->names[0]=(yyvsp[0].string); pl->types[0]= ((yyvsp[-1].boolean)>0 ? ARRAY : (yyvsp[-2].tipoDato)); (yyval.paramList)=pl; }
#line 3299 "build/parser.tab.c"
    break;

  case 198: /* lista_parametros: lista_parametros ',' tipoPrimitivo param_array_brackets TOKEN_IDENTIFIER  */
#line 593 "src/entriesTools/parser.y"
                                                                               { 
        (yyvsp[-4].paramList)->names = realloc((yyvsp[-4].paramList)->names, sizeof(char*)*((yyvsp[-4].paramList)->count+1));
        (yyvsp[-4].paramList)->types = realloc((yyvsp[-4].paramList)->types, sizeof(TipoDato)*((yyvsp[-4].paramList)->count+1));
        (yyvsp[-4].paramList)->names[(yyvsp[-4].paramList)->count]=(yyvsp[0].string); (yyvsp[-4].paramList)->types[(yyvsp[-4].paramList)->count]= ((yyvsp[-1].boolean)>0 ? ARRAY : (yyvsp[-2].tipoDato)); (yyvsp[-4].paramList)->count++; (yyval.paramList)=(yyvsp[-4].paramList); }
#line 3308 "build/parser.tab.c"
    break;

  case 199: /* return_stmt: TOKEN_RETURN  */
#line 598 "src/entriesTools/parser.y"
                          { (yyval.nodo) = nuevoReturnExpresion(NULL); }
#line 3314 "build/parser.tab.c"
    break;

  case 200: /* return_stmt: TOKEN_RETURN expr  */
#line 599 "src/entriesTools/parser.y"
                        { (yyval.nodo) = nuevoReturnExpresion((yyvsp[0].nodo)); }
#line 3320 "build/parser.tab.c"
    break;

  case 201: /* for_each_statement: TOKEN_FOR '(' tipoPrimitivo TOKEN_IDENTIFIER ':' TOKEN_IDENTIFIER ')' bloque  */
#line 604 "src/entriesTools/parser.y"
                                                                                 {
          /* Desazucar: soportar flatten para arrays >=2D usando pila de índices
              Estrategia: generar bucles anidados según profundidad dinámica medida en runtime: iteramos cada nivel si el elemento actual aún es ARRAY.
              Simplificación: generamos un for principal sobre el arreglo original; si el elemento es ARRAY, usamos Array.length recursivo que ya suma todos los internos y hacemos un acceso lineal simulando flatten: i recorre 0..lengthTotal-1 y para each recuperamos elemento linealizado.
              Implementación minimal: length recursivo ya devuelve total; acceso lineal: creamos builtin que recorre y avanza un contador global oculto. Aquí haremos workaround: reemplazar for-each multi-dimension por for simple sobre length total y acceso mediante función auxiliar equals sobre índice lineal -> no disponible; alternativa: iterar superficialmente y si elemento es ARRAY, insertar otro for-each recursivo construido aquí. */
          /* Construcción básica 1D y fallback recursivo: si el cuerpo usa variable, queremos consistente para multidim -> generamos verificación y si elemento es ARRAY, no declaramos var primitiva (se imprimirá error si se intenta usar). */
          char bufIdx[64]; snprintf(bufIdx,sizeof(bufIdx),"__idx_fe_%s", (yyvsp[-4].string)); char* idxName=strdup(bufIdx);
          AbstractExpresion* cero = nuevoPrimitivoExpresion(strdup("0"), INT);
          AbstractExpresion* declIdx = nuevoDeclaracionVariables(INT, idxName, cero, 0);
          /* Propagar ubicación al índice sintético (usamos la posición del identificador de la variable foreach) */
          ((DeclaracionVariable*)declIdx)->linea = (yylsp[-4]).first_line; ((DeclaracionVariable*)declIdx)->columna = (yylsp[-4]).first_column;
          AbstractExpresion* idIdx1 = nuevoIdentificadorExpresion(idxName);
          AbstractExpresion* arrId1 = nuevoIdentificadorExpresion((yyvsp[-2].string));
          /* Usar longitud total (flatten) para iteración sobre arreglos potencialmente multidimensionales */
          AbstractExpresion* lenAcc = nuevoArrayTotalLength(arrId1);
          AbstractExpresion* cond = nuevoMenorQueExpresion(idIdx1, lenAcc);
          AbstractExpresion* idIdx2 = nuevoIdentificadorExpresion(idxName);
          AbstractExpresion* uno = nuevoPrimitivoExpresion(strdup("1"), INT);
          AbstractExpresion* sum = nuevoSumaExpresion(idIdx2, uno);
          AbstractExpresion* inc = nuevoAsignacionExpresion(idxName, sum);
    AbstractExpresion* arrId2 = nuevoIdentificadorExpresion((yyvsp[-2].string));
    AbstractExpresion* idIdx3 = nuevoIdentificadorExpresion(idxName);
    /* Acceso linealizado: soporta multi-d devolviendo elemento hoja en orden */
    AbstractExpresion* acceso = nuevoArrayLinearAccess(arrId2, idIdx3);
          AbstractExpresion* declVar = nuevoDeclaracionVariables((yyvsp[-5].tipoDato), (yyvsp[-4].string), acceso, 0);
          ((DeclaracionVariable*)declVar)->linea = (yylsp[-4]).first_line; ((DeclaracionVariable*)declVar)->columna = (yylsp[-4]).first_column;
          AbstractExpresion* lista = nuevoListaExpresiones(); agregarHijo(lista, declVar); agregarHijo(lista, (yyvsp[0].nodo));
          AbstractExpresion* cuerpo = nuevoBloqueExpresion(lista);
          (yyval.nodo) = nuevoForExpresion(declIdx, cond, inc, cuerpo);
    }
#line 3355 "build/parser.tab.c"
    break;

  case 202: /* for_each_statement: TOKEN_FOR '(' tipoPrimitivo '[' ']' TOKEN_IDENTIFIER ':' TOKEN_IDENTIFIER ')' bloque  */
#line 634 "src/entriesTools/parser.y"
                                                                                           {
        /* for-each de arrays: itera sobre primer nivel y declara variable de tipo arreglo */
        char bufIdx[64]; snprintf(bufIdx,sizeof(bufIdx),"__idx_fe_%s", (yyvsp[-4].string)); char* idxName=strdup(bufIdx);
        AbstractExpresion* cero = nuevoPrimitivoExpresion(strdup("0"), INT);
        AbstractExpresion* declIdx = nuevoDeclaracionVariables(INT, idxName, cero, 0);
        ((DeclaracionVariable*)declIdx)->linea = (yylsp[-4]).first_line; ((DeclaracionVariable*)declIdx)->columna = (yylsp[-4]).first_column;
        AbstractExpresion* idIdx1 = nuevoIdentificadorExpresion(idxName);
        AbstractExpresion* arrId1 = nuevoIdentificadorExpresion((yyvsp[-2].string));
        AbstractExpresion* lenTop = nuevoArrayTopLength(arrId1);
        AbstractExpresion* cond = nuevoMenorQueExpresion(idIdx1, lenTop);
        AbstractExpresion* idIdx2 = nuevoIdentificadorExpresion(idxName);
        AbstractExpresion* uno = nuevoPrimitivoExpresion(strdup("1"), INT);
        AbstractExpresion* sum = nuevoSumaExpresion(idIdx2, uno);
        AbstractExpresion* inc = nuevoAsignacionExpresion(idxName, sum);
        AbstractExpresion* arrId2 = nuevoIdentificadorExpresion((yyvsp[-2].string));
        AbstractExpresion* idIdx3 = nuevoIdentificadorExpresion(idxName);
        AbstractExpresion* acceso = nuevoArrayAcceso(arrId2, idIdx3);
        AbstractExpresion* declVar = nuevoDeclaracionVariables(ARRAY, (yyvsp[-4].string), acceso, 0);
        ((DeclaracionVariable*)declVar)->linea = (yylsp[-4]).first_line; ((DeclaracionVariable*)declVar)->columna = (yylsp[-4]).first_column;
        AbstractExpresion* lista = nuevoListaExpresiones(); agregarHijo(lista, declVar); agregarHijo(lista, (yyvsp[0].nodo));
        AbstractExpresion* cuerpo = nuevoBloqueExpresion(lista);
        (yyval.nodo) = nuevoForExpresion(declIdx, cond, inc, cuerpo);
    }
#line 3383 "build/parser.tab.c"
    break;

  case 203: /* argumentos_opt: %empty  */
#line 658 "src/entriesTools/parser.y"
                            { (yyval.nodo) = nuevoListaExpresiones(); }
#line 3389 "build/parser.tab.c"
    break;

  case 204: /* argumentos_opt: lista_Expr  */
#line 659 "src/entriesTools/parser.y"
                 { (yyval.nodo) = (yyvsp[0].nodo); }
#line 3395 "build/parser.tab.c"
    break;

  case 205: /* llamada_funcion: TOKEN_IDENTIFIER '(' argumentos_opt ')'  */
#line 661 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoLlamadaFuncion((yyvsp[-3].string), (yyvsp[-1].nodo)); }
#line 3401 "build/parser.tab.c"
    break;


#line 3405 "build/parser.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 662 "src/entriesTools/parser.y"


/* definición de yyerror, usa el yylloc global para ubicación */
void yyerror(const char *s) {
    // Traducir mensajes comunes de Bison al español de forma ligera
    const char* msg = s;
    if (strcmp(s, "syntax error") == 0) msg = "Error de sintaxis";
    else if (strstr(s, "unexpected") && strstr(s, "expecting")) msg = s; // dejar tal cual si es detallado
    /* Deduplicación básica: mismo mensaje en la misma posición */
    static int last_line = -1, last_col = -1; static char last_msg[128] = "";
    if (last_line == yylloc.first_line && last_col == yylloc.first_column && strcmp(last_msg, msg) == 0) {
        return;
    }
    last_line = yylloc.first_line; last_col = yylloc.first_column; strncpy(last_msg, msg, sizeof(last_msg)-1); last_msg[sizeof(last_msg)-1]='\0';
    report_syntax_error("%s", msg);
    /* En modo GLR, la recuperación estándar es limitada; evitamos macros no disponibles aquí. */
}
