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


#line 114 "build/parser.tab.c"

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
  YYSYMBOL_76_ = 76,                       /* '+'  */
  YYSYMBOL_77_ = 77,                       /* '-'  */
  YYSYMBOL_78_ = 78,                       /* '&'  */
  YYSYMBOL_79_ = 79,                       /* '^'  */
  YYSYMBOL_80_ = 80,                       /* '|'  */
  YYSYMBOL_81_ = 81,                       /* '*'  */
  YYSYMBOL_82_ = 82,                       /* '/'  */
  YYSYMBOL_83_ = 83,                       /* '%'  */
  YYSYMBOL_NEG = 84,                       /* NEG  */
  YYSYMBOL_CAST = 85,                      /* CAST  */
  YYSYMBOL_86_ = 86,                       /* '.'  */
  YYSYMBOL_87_ = 87,                       /* '}'  */
  YYSYMBOL_88_ = 88,                       /* ';'  */
  YYSYMBOL_89_ = 89,                       /* '('  */
  YYSYMBOL_90_ = 90,                       /* ')'  */
  YYSYMBOL_91_ = 91,                       /* '{'  */
  YYSYMBOL_92_ = 92,                       /* ':'  */
  YYSYMBOL_93_ = 93,                       /* '='  */
  YYSYMBOL_94_ = 94,                       /* ','  */
  YYSYMBOL_95_ = 95,                       /* '['  */
  YYSYMBOL_96_ = 96,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 97,                  /* $accept  */
  YYSYMBOL_s = 98,                         /* s  */
  YYSYMBOL_lSentencia = 99,                /* lSentencia  */
  YYSYMBOL_comentario = 100,               /* comentario  */
  YYSYMBOL_instruccion = 101,              /* instruccion  */
  YYSYMBOL_if_statement = 102,             /* if_statement  */
  YYSYMBOL_switch_statement = 103,         /* switch_statement  */
  YYSYMBOL_while_statement = 104,          /* while_statement  */
  YYSYMBOL_for_statement = 105,            /* for_statement  */
  YYSYMBOL_incremento = 106,               /* incremento  */
  YYSYMBOL_case_list = 107,                /* case_list  */
  YYSYMBOL_case_labels = 108,              /* case_labels  */
  YYSYMBOL_case_item = 109,                /* case_item  */
  YYSYMBOL_instrucciones_case = 110,       /* instrucciones_case  */
  YYSYMBOL_instruccion_case = 111,         /* instruccion_case  */
  YYSYMBOL_default_case = 112,             /* default_case  */
  YYSYMBOL_break_statement = 113,          /* break_statement  */
  YYSYMBOL_continue_statement = 114,       /* continue_statement  */
  YYSYMBOL_instruccion_simple = 115,       /* instruccion_simple  */
  YYSYMBOL_asignacion = 116,               /* asignacion  */
  YYSYMBOL_lista_Expr = 117,               /* lista_Expr  */
  YYSYMBOL_imprimir = 118,                 /* imprimir  */
  YYSYMBOL_bloque = 119,                   /* bloque  */
  YYSYMBOL_bloque_for = 120,               /* bloque_for  */
  YYSYMBOL_declaracion_var = 121,          /* declaracion_var  */
  YYSYMBOL_array_decl_local = 122,         /* array_decl_local  */
  YYSYMBOL_brackets_seq = 123,             /* brackets_seq  */
  YYSYMBOL_var_decl = 124,                 /* var_decl  */
  YYSYMBOL_final_var_decl = 125,           /* final_var_decl  */
  YYSYMBOL_dims_expr_list = 126,           /* dims_expr_list  */
  YYSYMBOL_lista_bloques2D = 127,          /* lista_bloques2D  */
  YYSYMBOL_bloque2D = 128,                 /* bloque2D  */
  YYSYMBOL_filas_lista = 129,              /* filas_lista  */
  YYSYMBOL_fila_matriz = 130,              /* fila_matriz  */
  YYSYMBOL_asignacion_elemento = 131,      /* asignacion_elemento  */
  YYSYMBOL_indices_una = 132,              /* indices_una  */
  YYSYMBOL_indices_multi = 133,            /* indices_multi  */
  YYSYMBOL_expr = 134,                     /* expr  */
  YYSYMBOL_postfix = 135,                  /* postfix  */
  YYSYMBOL_unary = 136,                    /* unary  */
  YYSYMBOL_atom = 137,                     /* atom  */
  YYSYMBOL_join_variadic_args = 138,       /* join_variadic_args  */
  YYSYMBOL_primitivo = 139,                /* primitivo  */
  YYSYMBOL_tipoPrimitivo = 140,            /* tipoPrimitivo  */
  YYSYMBOL_funcion_declaracion = 141,      /* funcion_declaracion  */
  YYSYMBOL_main_declaracion = 142,         /* main_declaracion  */
  YYSYMBOL_main_params_opt = 143,          /* main_params_opt  */
  YYSYMBOL_main_params = 144,              /* main_params  */
  YYSYMBOL_main_param = 145,               /* main_param  */
  YYSYMBOL_main_param_array_brackets = 146, /* main_param_array_brackets  */
  YYSYMBOL_param_opt = 147,                /* param_opt  */
  YYSYMBOL_param_array_brackets = 148,     /* param_array_brackets  */
  YYSYMBOL_lista_parametros = 149,         /* lista_parametros  */
  YYSYMBOL_return_stmt = 150,              /* return_stmt  */
  YYSYMBOL_for_each_statement = 151,       /* for_each_statement  */
  YYSYMBOL_argumentos_opt = 152,           /* argumentos_opt  */
  YYSYMBOL_llamada_funcion = 153           /* llamada_funcion  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 57 "src/entriesTools/parser.y"

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


#line 322 "build/parser.tab.c"

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
#define YYFINAL  109
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2038

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  203
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  434

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   332


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
       2,     2,     2,     2,     2,     2,     2,    83,    78,     2,
      89,    90,    81,    76,    94,    77,    86,    82,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    92,    88,
       2,    93,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    95,     2,    96,    79,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,    80,    87,     2,     2,     2,     2,
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
      75,    84,    85
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   132,   132,   136,   137,   138,   144,   145,   148,   149,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   169,   170,   173,   174,
     175,   176,   181,   186,   193,   194,   197,   198,   206,   207,
     208,   209,   210,   211,   215,   216,   217,   228,   232,   239,
     244,   250,   262,   274,   279,   285,   286,   287,   288,   291,
     292,   295,   298,   301,   302,   303,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   318,   319,   326,
     327,   328,   329,   330,   333,   334,   336,   341,   342,   343,
     351,   369,   374,   379,   384,   389,   390,   393,   394,   397,
     404,   405,   413,   414,   416,   418,   419,   421,   423,   425,
     428,   429,   430,   431,   432,   434,   435,   436,   437,   438,
     442,   443,   444,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   484,   485,   486,   487,   488,   489,
     490,   496,   504,   508,   511,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   524,   532,   533,   534,   535,
     536,   537,   538,   539,   542,   543,   544,   545,   546,   547,
     548,   553,   558,   570,   571,   571,   572,   572,   573,   574,
     574,   576,   577,   580,   581,   583,   587,   592,   593,   598,
     628,   652,   653,   655
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
  "TOKEN_STATIC", "'+'", "'-'", "'&'", "'^'", "'|'", "'*'", "'/'", "'%'",
  "NEG", "CAST", "'.'", "'}'", "';'", "'('", "')'", "'{'", "':'", "'='",
  "','", "'['", "']'", "$accept", "s", "lSentencia", "comentario",
  "instruccion", "if_statement", "switch_statement", "while_statement",
  "for_statement", "incremento", "case_list", "case_labels", "case_item",
  "instrucciones_case", "instruccion_case", "default_case",
  "break_statement", "continue_statement", "instruccion_simple",
  "asignacion", "lista_Expr", "imprimir", "bloque", "bloque_for",
  "declaracion_var", "array_decl_local", "brackets_seq", "var_decl",
  "final_var_decl", "dims_expr_list", "lista_bloques2D", "bloque2D",
  "filas_lista", "fila_matriz", "asignacion_elemento", "indices_una",
  "indices_multi", "expr", "postfix", "unary", "atom",
  "join_variadic_args", "primitivo", "tipoPrimitivo",
  "funcion_declaracion", "main_declaracion", "main_params_opt",
  "main_params", "main_param", "main_param_array_brackets", "param_opt",
  "param_array_brackets", "lista_parametros", "return_stmt",
  "for_each_statement", "argumentos_opt", "llamada_funcion", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-333)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-86)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     676,   -43,   -66,  -333,  -333,  -333,   -61,  -333,  -333,  -333,
    -333,   863,  -333,  -333,  -333,  -333,  -333,   393,   -50,   -47,
    -333,  -333,   -58,   -20,   -10,     8,    13,    16,    52,    54,
      67,    95,  1142,     4,   842,   759,    81,   415,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,   113,   120,  -333,   123,  -333,
    -333,  -333,   138,    94,  -333,  -333,  -333,    -9,  -333,  -333,
     146,  -333,  -333,  -333,  -333,  1142,   108,  -333,  -333,  1142,
    1142,  1142,  1142,  1142,  1142,  1142,  1142,  1142,  1142,  1142,
    1142,  1142,   -15,   107,  -333,    69,  1026,  1050,    55,   150,
     162,   201,  1142,  1142,  -333,  1142,   706,  -333,   -61,    68,
    1142,  1142,  1947,   110,   224,  1470,   159,   129,   498,  -333,
     136,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,     9,
    -333,  1142,   114,   155,    -8,  -333,   116,  1947,   165,   166,
    1947,  1947,  1947,  1947,  1947,  1947,  1947,  1947,  1947,  1947,
     163,   168,  1947,  1200,  1142,  1142,  1142,  1142,  1142,  1142,
    -333,  1142,  1142,  1142,  1142,  1142,  1142,  -333,   167,  -333,
     128,  -333,   139,   170,   173,   174,   175,  1507,  1544,  1581,
     233,   177,   180,    -7,  -333,  -333,  1142,  1142,  1142,  1142,
    1142,  1142,  1142,  1142,  1142,  1142,  1142,  1142,  1142,  1142,
    1142,  1142,  1142,  1142,   241,  -333,  1210,    40,  -333,  -333,
     183,  -333,   184,  1234,   393,  1142,  -333,   143,   178,  -333,
    1142,  1142,  1142,  -333,  -333,  1947,  1947,  1947,  1947,  1947,
    1947,  1947,  1947,  1947,  1947,  1947,  1947,  1142,  -333,  -333,
    1142,  1142,  1142,  1142,   446,   185,   446,  1142,  1142,   148,
     192,    -5,   156,   156,   280,   280,    36,    36,    36,    36,
     951,  1955,    42,    42,    18,    18,    18,  -333,  -333,  -333,
     202,   110,  1118,  1142,  -333,  -333,   200,   198,  1947,   393,
     866,  -333,  1947,  1618,  1336,  1947,  1655,  1692,  1729,  1346,
     207,  -333,  -333,   235,  -333,    -4,   237,  -333,  -333,  1877,
    1912,   289,   290,   219,   393,  -333,  1766,  1803,    -3,   222,
     393,   226,   393,   934,  -333,  1947,  -333,  1142,  -333,  -333,
    -333,  1142,   250,    85,   227,  1142,   112,   386,  -333,   302,
       5,   229,   231,  -333,   234,   238,  -333,  -333,  -333,  -333,
     232,  -333,  -333,   222,   236,   958,   -44,   -26,  -333,    45,
    -333,  1290,   239,  1840,    85,  -333,  -333,  1392,   243,  -333,
    -333,   240,  1142,   555,  -333,   245,   252,  -333,   253,   582,
     254,  -333,   530,   255,   222,   328,    -2,   222,   393,  -333,
       3,  -333,  1142,   251,  1142,    97,  -333,  -333,   256,  -333,
     257,  -333,  1142,  -333,  -333,  -333,  -333,  -333,   446,  -333,
    1431,   261,  -333,  -333,  -333,  -333,  -333,  -333,   446,   676,
    -333,  -333,   530,  -333,   260,  -333,   259,  -333,  -333,  -333,
    1246,  1142,  -333,   257,  -333,  -333,   163,   644,  -333,  -333,
    -333,  -333,   587,  -333,  -333,   222,  -333,  -333,  1280,   263,
    -333,  -333,  -333,  -333
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   174,   175,   176,   177,   166,   169,   168,
     167,   156,   171,   172,   178,   179,   170,     0,     0,     0,
     180,   173,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   197,     0,     0,     0,     0,     0,     5,    10,
      11,    13,    14,    12,    25,     0,     0,    17,     0,    87,
      88,    89,     0,     0,   144,   152,   154,     0,    19,    20,
       0,    15,   157,     7,    26,     0,     0,   150,   151,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
       0,     0,     0,     0,   177,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,     0,     0,    62,     0,   156,
       0,     0,   198,   143,     0,     0,     0,     0,     0,     1,
       0,     8,     9,     4,     3,    22,    16,    18,    23,     0,
      24,     0,    98,     0,     0,    21,     0,    78,     0,     0,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     202,     0,    66,     0,     0,     0,     0,     0,     0,     0,
     121,     0,     0,     0,     0,     0,     0,   122,     0,    81,
       0,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   141,   142,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   155,     0,     7,    84,     6,
       0,   146,     0,     0,   191,     0,    95,     0,     0,    79,
       0,     0,     0,   203,   120,   110,   111,   112,   113,   114,
     108,   115,   116,   117,   118,   119,   109,     0,    80,    82,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    98,
       0,     0,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   123,   124,   128,   130,   129,   125,   126,   127,
       0,   153,     0,     0,   145,   193,     0,   192,    97,   191,
       0,    96,    77,     0,     0,    99,     0,     0,     0,     0,
       0,    65,    63,    28,    64,     0,     0,    37,    36,     0,
       0,     0,    95,     0,   184,   149,     0,     0,     0,     0,
       0,     0,     0,     0,    92,    94,   162,     0,   159,   160,
     161,     0,    31,     0,    98,     0,     0,     0,    47,     0,
       0,     0,     0,   189,     0,   185,   186,   148,   147,   195,
       0,   181,   193,     0,     0,     0,     0,     0,   102,     0,
     105,     0,     0,     0,     0,    30,    29,     0,     0,    34,
      48,     0,     0,    51,    53,     0,     0,    56,     0,     0,
       0,    44,     0,     0,     0,     0,     0,     0,     0,   194,
       0,   182,     0,    90,     0,     0,    91,    93,     0,   104,
       0,   163,     0,   164,   158,    33,    32,    49,     0,    35,
       0,     0,    54,    58,    55,    57,    45,    46,     0,     0,
      41,    40,     0,   199,     0,   188,     0,   183,   187,   196,
       0,     0,   107,     0,   103,   106,   165,    59,    50,    52,
      43,    42,     0,    39,    38,     0,   190,   100,     0,     0,
      86,   200,   101,    60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -333,  -333,   -32,  -333,   -35,  -272,  -333,  -333,  -333,    33,
    -333,  -333,    48,   -23,  -332,  -333,  -333,  -333,  -221,   -92,
     -60,  -167,   -46,   -36,   -87,  -333,   312,  -333,  -333,  -333,
    -333,  -281,  -333,    -6,  -333,   164,  -333,   -18,     1,  -333,
    -333,  -333,  -333,     0,  -333,  -333,  -333,  -333,     2,  -333,
     103,    41,  -333,  -333,  -333,  -333,  -333
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    36,    37,   113,    38,    39,    40,    41,    42,   360,
     316,   317,   318,   353,   354,   351,    43,    44,   280,    45,
     375,    46,    47,   401,    48,    49,   241,    50,    51,   373,
     337,   304,   339,   340,    52,    82,    83,   127,   103,    54,
      55,   342,    56,   285,    58,    59,   324,   325,   326,   366,
     266,   298,   267,    60,    61,   141,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    53,   114,   108,   171,   126,   122,   207,   239,   172,
     293,   314,   329,   405,   102,   287,   105,    85,   409,   140,
     359,   392,   338,    65,   200,    66,   160,   162,    88,   144,
     145,   146,   147,   148,   106,    57,    53,    57,    53,    86,
     -85,   345,    87,   376,    63,    64,   176,   177,   201,   202,
     210,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   377,   142,   143,   176,   177,    89,   282,   378,   282,
     176,   177,   385,   114,   167,   168,    90,   169,   149,   104,
      81,   109,   174,   175,   158,   392,   123,   208,   240,   163,
     208,   123,   330,   406,    91,   362,   173,   414,   330,   191,
     192,   193,    92,   203,   -85,    93,   -85,   -85,    57,    53,
      67,    68,   186,   187,   188,   189,   190,   191,   192,   193,
     188,   189,   190,   191,   192,   193,   215,   216,   217,   218,
     219,   220,   379,   221,   222,   223,   224,   225,   226,   380,
      94,   400,   281,    95,   281,   128,   129,   284,    26,   284,
     356,   151,   152,   153,   154,   155,    96,    79,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,    35,   420,   315,   348,
     119,   423,   120,    97,   412,   164,   356,   268,   283,   121,
     288,   210,   272,   273,   274,   282,   119,   261,   165,   349,
     156,   115,    81,   204,   265,   121,   209,   205,   116,   275,
     210,   117,   276,   277,   278,   279,   197,    64,   228,   289,
     290,   356,   210,   199,    64,   355,   118,   361,   361,   229,
     358,   282,   269,   210,   125,   282,   270,   191,   192,   193,
     291,   205,   166,   336,   296,   297,   150,   157,   194,   196,
     356,   206,   305,   331,   211,   212,   260,   210,   213,   230,
     227,   355,   231,   232,   233,   237,   358,   346,   238,   265,
     281,   357,   262,   263,   271,   284,   286,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,   371,   292,   341,
     299,   294,   300,   343,   323,   312,   355,   347,   386,   313,
     332,   358,   334,   315,   321,   322,   281,   357,   176,   177,
     281,   284,   270,    35,   344,   284,   333,   359,   403,   364,
     205,   407,   416,   365,   367,   355,    80,   389,   369,   383,
     358,   372,   368,   393,   390,   388,   180,   181,   182,   183,
     394,   395,   357,   404,   398,   402,   411,   413,   374,   419,
     425,   433,   421,   363,   410,   426,   186,   187,   188,   189,
     190,   191,   192,   193,   350,   417,   424,   422,   323,   124,
     408,   357,   301,   370,   415,     0,     0,     0,     0,   431,
       0,     0,     0,     0,     0,     0,     0,   114,     0,     2,
       3,     4,     0,   428,     0,     5,    84,     3,     4,    57,
      53,   170,     5,    84,    14,    15,     0,    17,    18,    19,
      20,    14,    15,     0,     0,    -2,   110,    20,     2,     3,
       4,     0,    57,    53,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
     111,   112,    21,     0,     0,    22,    23,    24,    25,     2,
       3,     4,   352,     0,     0,     5,    84,     0,     0,     0,
       0,   170,     0,     0,    14,    15,     0,    17,    18,    19,
      20,     0,     0,     0,     0,     0,     0,    35,    26,     0,
      27,     0,     0,    28,    29,    30,    31,     0,    32,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
       0,     2,     3,     4,    34,     0,    35,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,   111,   112,    21,     0,     0,    22,    23,
      24,    25,     0,     2,     3,     4,     0,    35,     0,     5,
      84,     0,     0,     0,     0,   170,     0,     0,    14,    15,
       0,    17,    18,    19,    20,     0,     0,     0,     2,     3,
       4,    26,     0,    27,     5,    84,    28,    29,    30,    31,
     170,    32,    33,    14,    15,     0,    17,    18,    19,    20,
       0,     0,     0,     0,     0,   198,     0,    34,   110,    35,
       2,     3,     4,     0,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,   111,   112,    21,     0,     0,    22,    23,    24,
      25,   399,     0,   391,   396,   397,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,     2,     3,     4,
      26,     0,    27,     5,    84,    28,    29,    30,    31,   170,
      32,    33,    14,    15,     0,    17,    18,    19,    20,     0,
       0,     0,     0,     0,   430,    80,    34,     1,    35,     2,
       3,     4,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,     0,     0,    21,     0,     0,    22,    23,    24,    25,
       3,     4,   429,     0,     0,     5,    84,     0,     0,     0,
       0,   170,     0,     0,    14,    15,     0,    17,     0,     0,
      20,     0,     0,     0,     0,    35,     0,     0,     0,    26,
       0,    27,     0,     0,    28,    29,    30,    31,     0,    32,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     107,     0,     2,     3,     4,    34,     0,    35,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,     0,    21,     0,     0,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    26,     0,    27,     0,     0,    28,    29,    30,
      31,     0,    32,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     4,    34,     0,
      35,     5,     6,     7,     8,     9,    10,    99,    12,    13,
      14,    15,    16,     0,     0,     0,    20,     0,     0,    21,
       0,     0,    22,    23,    24,    25,    98,     7,     8,     9,
      10,    99,    12,    13,     0,     0,    16,     0,     0,     0,
       0,     0,     0,    21,     0,     0,    22,    23,    24,    25,
       0,     0,     0,     0,   100,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,   101,
       0,     0,     0,     0,     0,     0,     0,     0,   100,     0,
       0,    34,     0,     0,     0,     0,     0,     0,   302,     0,
       0,     0,     0,   101,    98,     7,     8,     9,    10,    99,
      12,    13,    79,     0,    16,    34,    80,   303,    81,     0,
       0,    21,     0,     0,    22,    23,    24,    25,    98,     7,
       8,     9,    10,    99,    12,    13,     0,     0,    16,   176,
     177,     0,     0,     0,     0,    21,     0,     0,    22,    23,
      24,    25,     0,     0,     0,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,   178,   179,   180,   181,   182,
     183,   101,     0,     0,     0,     0,     0,     0,     0,     0,
     100,     0,     0,    34,     0,   335,     0,   186,   187,   188,
     189,   190,   191,   192,   193,   101,    98,     7,     8,     9,
      10,    99,    12,    13,     0,     0,    16,    34,     0,   374,
       0,     0,     0,    21,     0,     0,    22,    23,    24,    25,
      98,     7,     8,     9,    10,    99,    12,    13,     0,     0,
      16,     0,     0,     0,     0,     0,     0,    21,     0,     0,
      22,    23,    24,    25,     0,     0,     0,     0,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,     0,     0,     0,     0,     0,     0,
       0,     0,   100,     0,     0,    34,   159,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,    98,     7,
       8,     9,    10,    99,    12,    13,     0,     0,    16,    34,
     161,     0,     0,     0,     0,    21,     0,     0,    22,    23,
      24,    25,    98,     7,     8,     9,    10,    99,    12,    13,
       0,     0,    16,     0,     0,     0,     0,     0,     0,    21,
       0,     0,    22,    23,    24,    25,     0,     0,     0,     0,
     100,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,     0,     0,     0,     0,
       0,     0,     0,     0,   100,     0,     0,    34,   295,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
      98,     7,     8,     9,    10,    99,    12,    13,   176,   177,
      16,    34,     0,     0,     0,     0,     0,    21,     0,     0,
      22,    23,    24,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   176,   177,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,   177,   186,   187,   188,   189,
     190,   191,   192,   193,     0,     0,     0,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   214,     0,     0,    34,
     178,   179,   180,   181,   182,   183,   184,   185,   176,   177,
     186,   187,   188,   189,   190,   191,   192,   193,   176,   177,
       0,     0,   186,   187,   188,   189,   190,   191,   192,   193,
     264,     0,     0,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   427,     0,   178,   179,   180,   181,   182,   183,
     184,   185,     0,     0,     0,     0,   186,   187,   188,   189,
     190,   191,   192,   193,   176,   177,   186,   187,   188,   189,
     190,   191,   192,   193,   176,   177,   432,     0,     0,     0,
     381,     0,     0,     0,   382,     0,     0,     0,     0,     0,
     178,   179,   180,   181,   182,   183,   184,   185,     0,     0,
     178,   179,   180,   181,   182,   183,   184,   185,     0,     0,
       0,     0,   186,   187,   188,   189,   190,   191,   192,   193,
     176,   177,   186,   187,   188,   189,   190,   191,   192,   193,
     307,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     311,     0,     0,     0,     0,     0,   178,   179,   180,   181,
     182,   183,   184,   185,     0,     0,     0,     0,     0,   176,
     177,     0,     0,     0,     0,     0,     0,     0,   186,   187,
     188,   189,   190,   191,   192,   193,     0,     0,     0,     0,
       0,     0,     0,     0,   387,   178,   179,   180,   181,   182,
     183,   184,   185,     0,     0,     0,     0,     0,   176,   177,
       0,     0,     0,     0,     0,     0,     0,   186,   187,   188,
     189,   190,   191,   192,   193,     0,     0,     0,     0,     0,
       0,     0,     0,   418,   178,   179,   180,   181,   182,   183,
     184,   185,     0,     0,     0,   176,   177,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,   188,   189,
     190,   191,   192,   193,     0,     0,     0,     0,     0,     0,
     195,   178,   179,   180,   181,   182,   183,   184,   185,     0,
       0,     0,   176,   177,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   186,   187,   188,   189,   190,   191,   192,
     193,     0,     0,     0,     0,     0,     0,   234,   178,   179,
     180,   181,   182,   183,   184,   185,     0,     0,     0,   176,
     177,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     186,   187,   188,   189,   190,   191,   192,   193,     0,     0,
       0,     0,     0,     0,   235,   178,   179,   180,   181,   182,
     183,   184,   185,     0,     0,     0,   176,   177,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   186,   187,   188,
     189,   190,   191,   192,   193,     0,     0,     0,     0,     0,
       0,   236,   178,   179,   180,   181,   182,   183,   184,   185,
       0,     0,     0,   176,   177,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   186,   187,   188,   189,   190,   191,
     192,   193,     0,     0,     0,     0,     0,     0,   306,   178,
     179,   180,   181,   182,   183,   184,   185,     0,     0,     0,
     176,   177,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   186,   187,   188,   189,   190,   191,   192,   193,     0,
       0,     0,     0,     0,     0,   308,   178,   179,   180,   181,
     182,   183,   184,   185,     0,     0,     0,   176,   177,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   186,   187,
     188,   189,   190,   191,   192,   193,     0,     0,     0,     0,
       0,     0,   309,   178,   179,   180,   181,   182,   183,   184,
     185,     0,     0,     0,   176,   177,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   186,   187,   188,   189,   190,
     191,   192,   193,     0,     0,     0,     0,     0,     0,   310,
     178,   179,   180,   181,   182,   183,   184,   185,     0,     0,
       0,   176,   177,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   186,   187,   188,   189,   190,   191,   192,   193,
       0,     0,     0,     0,     0,     0,   327,   178,   179,   180,
     181,   182,   183,   184,   185,     0,     0,     0,   176,   177,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   186,
     187,   188,   189,   190,   191,   192,   193,     0,     0,     0,
       0,     0,     0,   328,   178,   179,   180,   181,   182,   183,
     184,   185,     0,     0,     0,   176,   177,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,   188,   189,
     190,   191,   192,   193,     0,     0,     0,     0,     0,     0,
     384,   178,   179,   180,   181,   182,   183,   184,   185,     0,
     176,   177,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   186,   187,   188,   189,   190,   191,   192,
     193,     0,     0,     0,     0,   319,   178,   179,   180,   181,
     182,   183,   184,   185,     0,   176,   177,     0,     0,     0,
       0,     0,     0,   176,   177,     0,     0,     0,   186,   187,
     188,   189,   190,   191,   192,   193,     0,     0,     0,     0,
     320,   178,   179,   180,   181,   182,   183,   184,   185,   178,
     179,   180,   181,   182,   183,   184,     0,     0,     0,     0,
       0,     0,     0,   186,   187,   188,   189,   190,   191,   192,
     193,   186,   187,   188,   189,   190,   191,   192,   193
};

static const yytype_int16 yycheck[] =
{
       0,     0,    37,    35,    96,    65,    15,    15,    15,    96,
      15,    15,    15,    15,    32,   236,    34,    17,    15,    79,
      15,   353,   303,    89,    15,    86,    86,    87,    86,    44,
      45,    46,    47,    48,    34,    35,    35,    37,    37,    89,
       0,   313,    89,    87,    87,    88,    28,    29,    39,    40,
      94,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    87,    80,    81,    28,    29,    86,   234,    94,   236,
      28,    29,   344,   108,    92,    93,    86,    95,    93,    75,
      95,     0,   100,   101,    15,   417,    95,    95,    95,    34,
      95,    95,    95,    95,    86,    90,    96,   378,    95,    81,
      82,    83,    89,   121,    64,    89,    66,    67,   108,   108,
      42,    43,    76,    77,    78,    79,    80,    81,    82,    83,
      78,    79,    80,    81,    82,    83,   144,   145,   146,   147,
     148,   149,    87,   151,   152,   153,   154,   155,   156,    94,
      88,   362,   234,    89,   236,    37,    38,   234,    63,   236,
     317,    44,    45,    46,    47,    48,    89,    89,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,    91,   398,    66,    67,
      86,   402,    88,    88,    87,    35,   353,   205,   234,    95,
     236,    94,   210,   211,   212,   362,    86,   196,    36,    87,
      93,    88,    95,    89,   204,    95,    90,    93,    88,   227,
      94,    88,   230,   231,   232,   233,    87,    88,    90,   237,
     238,   388,    94,    87,    88,   317,    88,   319,   320,    90,
     317,   398,    89,    94,    88,   402,    93,    81,    82,    83,
      92,    93,    41,   303,   262,   263,    82,    83,    24,    90,
     417,    96,   270,   299,    89,    89,    15,    94,    90,    89,
      93,   353,    89,    89,    89,    88,   353,   313,    88,   269,
     362,   317,    89,    89,    96,   362,    91,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,   333,    96,   307,
      90,    89,    94,   311,   294,    88,   388,   315,   344,    64,
     300,   388,   302,    66,    15,    15,   398,   353,    28,    29,
     402,   398,    93,    91,    64,   402,    90,    15,   364,    90,
      93,   367,   382,    92,    90,   417,    93,    87,    96,    90,
     417,    95,    94,    88,   352,    92,    56,    57,    58,    59,
      88,    88,   388,    15,    90,    90,    95,    91,    91,    88,
      90,    88,   398,   320,   372,    96,    76,    77,    78,    79,
      80,    81,    82,    83,   316,   388,   402,   399,   368,    57,
     368,   417,   269,   332,   380,    -1,    -1,    -1,    -1,   425,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   422,    -1,     3,
       4,     5,    -1,   411,    -1,     9,    10,     4,     5,   399,
     399,    15,     9,    10,    18,    19,    -1,    21,    22,    23,
      24,    18,    19,    -1,    -1,     0,     1,    24,     3,     4,
       5,    -1,   422,   422,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,     3,
       4,     5,    66,    -1,    -1,     9,    10,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    18,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    91,    63,    -1,
      65,    -1,    -1,    68,    69,    70,    71,    -1,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,    89,    -1,    91,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    33,    -1,     3,     4,     5,    -1,    91,    -1,     9,
      10,    -1,    -1,    -1,    -1,    15,    -1,    -1,    18,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,     3,     4,
       5,    63,    -1,    65,     9,    10,    68,    69,    70,    71,
      15,    73,    74,    18,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    87,    -1,    89,     1,    91,
       3,     4,     5,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      33,    91,    -1,    68,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    91,     3,     4,     5,
      63,    -1,    65,     9,    10,    68,    69,    70,    71,    15,
      73,    74,    18,    19,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    87,    93,    89,     1,    91,     3,
       4,     5,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,
       4,     5,    68,    -1,    -1,     9,    10,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    18,    19,    -1,    21,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    63,
      -1,    65,    -1,    -1,    68,    69,    70,    71,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,     3,     4,     5,    89,    -1,    91,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    27,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    65,    -1,    -1,    68,    69,    70,
      71,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,    89,    -1,
      91,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    -1,    -1,    -1,    24,    -1,    -1,    27,
      -1,    -1,    30,    31,    32,    33,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    62,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,
      -1,    -1,    -1,    77,    10,    11,    12,    13,    14,    15,
      16,    17,    89,    -1,    20,    89,    93,    91,    95,    -1,
      -1,    27,    -1,    -1,    30,    31,    32,    33,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    20,    28,
      29,    -1,    -1,    -1,    -1,    27,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    89,    -1,    91,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    77,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    20,    89,    -1,    91,
      -1,    -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    20,    89,
      90,    -1,    -1,    -1,    -1,    27,    -1,    -1,    30,    31,
      32,    33,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    89,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      10,    11,    12,    13,    14,    15,    16,    17,    28,    29,
      20,    89,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    96,    -1,    -1,    89,
      54,    55,    56,    57,    58,    59,    60,    61,    28,    29,
      76,    77,    78,    79,    80,    81,    82,    83,    28,    29,
      -1,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      96,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    96,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,    83,    28,    29,    76,    77,    78,    79,
      80,    81,    82,    83,    28,    29,    96,    -1,    -1,    -1,
      90,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      28,    29,    76,    77,    78,    79,    80,    81,    82,    83,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    92,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    90,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78,    79,    80,    81,    82,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    -1,    -1,    -1,    -1,    -1,    90,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    88,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      88,    54,    55,    56,    57,    58,    59,    60,    61,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    76,    77,    78,    79,    80,    81,    82,    83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    27,    30,    31,    32,    33,    63,    65,    68,    69,
      70,    71,    73,    74,    89,    91,    98,    99,   101,   102,
     103,   104,   105,   113,   114,   116,   118,   119,   121,   122,
     124,   125,   131,   135,   136,   137,   139,   140,   141,   142,
     150,   151,   153,    87,    88,    89,    86,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    89,
      93,    95,   132,   133,    10,   140,    89,    89,    86,    86,
      86,    86,    89,    89,    88,    89,    89,    88,    10,    15,
      62,    77,   134,   135,    75,   134,   140,     1,    99,     0,
       1,    25,    26,   100,   101,    88,    88,    88,    88,    86,
      88,    95,    15,    95,   123,    88,   117,   134,    37,    38,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     117,   152,   134,   134,    44,    45,    46,    47,    48,    93,
     132,    44,    45,    46,    47,    48,    93,   132,    15,    90,
     117,    90,   117,    34,    35,    36,    41,   134,   134,   134,
      15,   116,   121,   140,   134,   134,    28,    29,    54,    55,
      56,    57,    58,    59,    60,    61,    76,    77,    78,    79,
      80,    81,    82,    83,    24,    90,    90,    87,    87,    87,
      15,    39,    40,   134,    89,    93,    96,    15,    95,    90,
      94,    89,    89,    90,    96,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,    93,    90,    90,
      89,    89,    89,    89,    90,    90,    90,    88,    88,    15,
      95,   123,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
      15,   135,    89,    89,    96,   140,   147,   149,   134,    89,
      93,    96,   134,   134,   134,   134,   134,   134,   134,   134,
     115,   116,   118,   119,   121,   140,    91,   115,   119,   134,
     134,    92,    96,    15,    89,    90,   134,   134,   148,    90,
      94,   147,    72,    91,   128,   134,    90,    94,    90,    90,
      90,    94,    88,    64,    15,    66,   107,   108,   109,    88,
      88,    15,    15,   140,   143,   144,   145,    90,    90,    15,
      95,   119,   140,    90,   140,    91,   117,   127,   128,   129,
     130,   134,   138,   134,    64,   102,   119,   134,    67,    87,
     109,   112,    66,   110,   111,   116,   118,   119,   121,    15,
     106,   116,    90,   106,    90,    92,   146,    90,    94,    96,
     148,   119,    95,   126,    91,   117,    87,    87,    94,    87,
      94,    90,    94,    90,    90,   102,   119,    92,    92,    87,
     134,    68,   111,    88,    88,    88,    42,    43,    90,    91,
     115,   120,    90,   119,    15,    15,    95,   119,   145,    15,
     134,    95,    87,    91,   128,   130,   117,   110,    92,    88,
     115,   119,    99,   115,   120,    90,    96,    96,   134,    68,
      87,   119,    96,    88
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    99,    99,    99,    99,    99,   100,   100,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   102,   102,
     102,   102,   102,   102,   103,   103,   104,   104,   105,   105,
     105,   105,   105,   105,   106,   106,   106,   107,   107,   108,
     108,   109,   109,   110,   110,   111,   111,   111,   111,   112,
     112,   113,   114,   115,   115,   115,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   117,   117,   118,
     118,   118,   118,   118,   119,   119,   120,   121,   121,   121,
     122,   122,   122,   122,   122,   123,   123,   124,   124,   125,
     126,   126,   127,   127,   128,   129,   129,   130,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     132,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   135,   135,   135,   135,   135,   135,
     135,   135,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   139,   139,   139,   139,
     139,   139,   139,   139,   140,   140,   140,   140,   140,   140,
     140,   141,   141,   142,   143,   143,   144,   144,   145,   146,
     146,   147,   147,   148,   148,   149,   149,   150,   150,   151,
     151,   152,   152,   153
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     2,     2,     2,     2,     1,     2,     2,     5,     7,
       7,     6,     8,     8,     7,     8,     5,     5,     9,     9,
       8,     8,     9,     9,     1,     2,     2,     1,     2,     3,
       4,     2,     4,     1,     2,     2,     1,     2,     2,     3,
       5,     2,     2,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     4,
       4,     3,     4,     3,     3,     3,     3,     1,     1,     1,
       7,     7,     5,     7,     5,     2,     3,     4,     2,     5,
       3,     4,     1,     3,     3,     1,     3,     3,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     1,     4,     3,     6,     6,     5,
       2,     2,     1,     4,     1,     3,     1,     1,     8,     6,
       6,     6,     6,     8,     8,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     6,     7,     8,     0,     1,     1,     3,     3,     0,
       3,     0,     1,     0,     3,     3,     5,     1,     2,     8,
      10,     0,     1,     4
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
#line 132 "src/entriesTools/parser.y"
               { ast_root = (yyvsp[0].nodo); (yyval.nodo) = (yyvsp[0].nodo); }
#line 2027 "build/parser.tab.c"
    break;

  case 3: /* lSentencia: lSentencia instruccion  */
#line 136 "src/entriesTools/parser.y"
                                   { agregarHijo((yyvsp[-1].nodo), (yyvsp[0].nodo)); (yyval.nodo) = (yyvsp[-1].nodo);}
#line 2033 "build/parser.tab.c"
    break;

  case 4: /* lSentencia: lSentencia comentario  */
#line 137 "src/entriesTools/parser.y"
                            { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 2039 "build/parser.tab.c"
    break;

  case 5: /* lSentencia: instruccion  */
#line 138 "src/entriesTools/parser.y"
                  {
                        AbstractExpresion* b = nuevoInstruccionesExpresion();
                        agregarHijo(b, (yyvsp[0].nodo));
                        (yyval.nodo) =  b;
                    }
#line 2049 "build/parser.tab.c"
    break;

  case 6: /* lSentencia: lSentencia error '}'  */
#line 144 "src/entriesTools/parser.y"
                           { yyerrok; (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2055 "build/parser.tab.c"
    break;

  case 7: /* lSentencia: error '}'  */
#line 145 "src/entriesTools/parser.y"
                { yyerrok; (yyval.nodo) = nuevoInstruccionesExpresion(); }
#line 2061 "build/parser.tab.c"
    break;

  case 8: /* comentario: TOKEN_COMMENT_LINE  */
#line 148 "src/entriesTools/parser.y"
                               { comments[comment_count++] = (yyvsp[0].string); }
#line 2067 "build/parser.tab.c"
    break;

  case 9: /* comentario: TOKEN_COMMENT_MULTI  */
#line 149 "src/entriesTools/parser.y"
                          { comments[comment_count++] = (yyvsp[0].string); }
#line 2073 "build/parser.tab.c"
    break;

  case 10: /* instruccion: if_statement  */
#line 152 "src/entriesTools/parser.y"
                          {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2079 "build/parser.tab.c"
    break;

  case 11: /* instruccion: switch_statement  */
#line 153 "src/entriesTools/parser.y"
                       {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2085 "build/parser.tab.c"
    break;

  case 12: /* instruccion: break_statement  */
#line 154 "src/entriesTools/parser.y"
                      {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2091 "build/parser.tab.c"
    break;

  case 13: /* instruccion: while_statement  */
#line 155 "src/entriesTools/parser.y"
                      {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2097 "build/parser.tab.c"
    break;

  case 14: /* instruccion: for_statement  */
#line 156 "src/entriesTools/parser.y"
                    {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2103 "build/parser.tab.c"
    break;

  case 15: /* instruccion: for_each_statement  */
#line 157 "src/entriesTools/parser.y"
                         {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2109 "build/parser.tab.c"
    break;

  case 16: /* instruccion: imprimir ';'  */
#line 158 "src/entriesTools/parser.y"
                   {(yyval.nodo) = (yyvsp[-1].nodo); }
#line 2115 "build/parser.tab.c"
    break;

  case 17: /* instruccion: bloque  */
#line 159 "src/entriesTools/parser.y"
             {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2121 "build/parser.tab.c"
    break;

  case 18: /* instruccion: declaracion_var ';'  */
#line 160 "src/entriesTools/parser.y"
                          {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2127 "build/parser.tab.c"
    break;

  case 19: /* instruccion: funcion_declaracion  */
#line 161 "src/entriesTools/parser.y"
                          {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2133 "build/parser.tab.c"
    break;

  case 20: /* instruccion: main_declaracion  */
#line 162 "src/entriesTools/parser.y"
                       {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2139 "build/parser.tab.c"
    break;

  case 21: /* instruccion: return_stmt ';'  */
#line 163 "src/entriesTools/parser.y"
                      {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2145 "build/parser.tab.c"
    break;

  case 22: /* instruccion: asignacion ';'  */
#line 164 "src/entriesTools/parser.y"
                     {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2151 "build/parser.tab.c"
    break;

  case 23: /* instruccion: asignacion_elemento ';'  */
#line 165 "src/entriesTools/parser.y"
                              {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2157 "build/parser.tab.c"
    break;

  case 24: /* instruccion: postfix ';'  */
#line 166 "src/entriesTools/parser.y"
                  { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 2163 "build/parser.tab.c"
    break;

  case 25: /* instruccion: continue_statement  */
#line 167 "src/entriesTools/parser.y"
                         {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2169 "build/parser.tab.c"
    break;

  case 26: /* instruccion: error ';'  */
#line 169 "src/entriesTools/parser.y"
                { (yyval.nodo) = parser_error_node((yylsp[-1]), "Se esperaba ';'"); yyerrok; }
#line 2175 "build/parser.tab.c"
    break;

  case 27: /* instruccion: error '}'  */
#line 170 "src/entriesTools/parser.y"
                { (yyval.nodo) = parser_error_node((yylsp[-1]), "Se esperaba '}'"); yyerrok; }
#line 2181 "build/parser.tab.c"
    break;

  case 28: /* if_statement: TOKEN_IF '(' expr ')' bloque  */
#line 173 "src/entriesTools/parser.y"
                                           { (yyval.nodo) = nuevoIfExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo), NULL); }
#line 2187 "build/parser.tab.c"
    break;

  case 29: /* if_statement: TOKEN_IF '(' expr ')' bloque TOKEN_ELSE bloque  */
#line 174 "src/entriesTools/parser.y"
                                                     { (yyval.nodo) = nuevoIfExpresion((yyvsp[-4].nodo), (yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2193 "build/parser.tab.c"
    break;

  case 30: /* if_statement: TOKEN_IF '(' expr ')' bloque TOKEN_ELSE if_statement  */
#line 175 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoIfExpresion((yyvsp[-4].nodo), (yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2199 "build/parser.tab.c"
    break;

  case 31: /* if_statement: TOKEN_IF '(' expr ')' instruccion_simple ';'  */
#line 176 "src/entriesTools/parser.y"
                                                   { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, (yyvsp[-1].nodo));
        (yyval.nodo) = nuevoIfExpresion((yyvsp[-3].nodo), nuevoBloqueExpresion(b), NULL); 
    }
#line 2209 "build/parser.tab.c"
    break;

  case 32: /* if_statement: TOKEN_IF '(' expr ')' instruccion_simple ';' TOKEN_ELSE bloque  */
#line 181 "src/entriesTools/parser.y"
                                                                     { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, (yyvsp[-3].nodo));
        (yyval.nodo) = nuevoIfExpresion((yyvsp[-5].nodo), nuevoBloqueExpresion(b), (yyvsp[0].nodo)); 
    }
#line 2219 "build/parser.tab.c"
    break;

  case 33: /* if_statement: TOKEN_IF '(' expr ')' instruccion_simple ';' TOKEN_ELSE if_statement  */
#line 186 "src/entriesTools/parser.y"
                                                                           { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, (yyvsp[-3].nodo));
        (yyval.nodo) = nuevoIfExpresion((yyvsp[-5].nodo), nuevoBloqueExpresion(b), (yyvsp[0].nodo)); 
    }
#line 2229 "build/parser.tab.c"
    break;

  case 34: /* switch_statement: TOKEN_SWITCH '(' expr ')' '{' case_list '}'  */
#line 193 "src/entriesTools/parser.y"
                                                              { (yyval.nodo) = nuevoSwitchExpresion((yyvsp[-4].nodo), (yyvsp[-1].nodo), NULL); }
#line 2235 "build/parser.tab.c"
    break;

  case 35: /* switch_statement: TOKEN_SWITCH '(' expr ')' '{' case_list default_case '}'  */
#line 194 "src/entriesTools/parser.y"
                                                               { (yyval.nodo) = nuevoSwitchExpresion((yyvsp[-5].nodo), (yyvsp[-2].nodo), (yyvsp[-1].nodo)); }
#line 2241 "build/parser.tab.c"
    break;

  case 36: /* while_statement: TOKEN_WHILE '(' expr ')' bloque  */
#line 197 "src/entriesTools/parser.y"
                                                 { (yyval.nodo) = nuevoWhileExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2247 "build/parser.tab.c"
    break;

  case 37: /* while_statement: TOKEN_WHILE '(' expr ')' instruccion_simple  */
#line 198 "src/entriesTools/parser.y"
                                                  { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, (yyvsp[0].nodo));
        (yyval.nodo) = nuevoWhileExpresion((yyvsp[-2].nodo), nuevoBloqueExpresion(b)); 
    }
#line 2257 "build/parser.tab.c"
    break;

  case 38: /* for_statement: TOKEN_FOR '(' declaracion_var ';' expr ';' incremento ')' bloque_for  */
#line 206 "src/entriesTools/parser.y"
                                                                         { (yyval.nodo)=nuevoForExpresion((yyvsp[-6].nodo),(yyvsp[-4].nodo),(yyvsp[-2].nodo),(yyvsp[0].nodo)); }
#line 2263 "build/parser.tab.c"
    break;

  case 39: /* for_statement: TOKEN_FOR '(' declaracion_var ';' expr ';' incremento ')' instruccion_simple  */
#line 207 "src/entriesTools/parser.y"
                                                                               { AbstractExpresion* b=nuevoListaExpresiones(); agregarHijo(b,(yyvsp[0].nodo)); (yyval.nodo)=nuevoForExpresion((yyvsp[-6].nodo),(yyvsp[-4].nodo),(yyvsp[-2].nodo),nuevoBloqueExpresionConContextoPadre(b)); }
#line 2269 "build/parser.tab.c"
    break;

  case 40: /* for_statement: TOKEN_FOR '(' declaracion_var ';' expr ';' ')' bloque_for  */
#line 208 "src/entriesTools/parser.y"
                                                            { (yyval.nodo)=nuevoForExpresion((yyvsp[-5].nodo),(yyvsp[-3].nodo),NULL,(yyvsp[0].nodo)); }
#line 2275 "build/parser.tab.c"
    break;

  case 41: /* for_statement: TOKEN_FOR '(' declaracion_var ';' expr ';' ')' instruccion_simple  */
#line 209 "src/entriesTools/parser.y"
                                                                    { AbstractExpresion* b=nuevoListaExpresiones(); agregarHijo(b,(yyvsp[0].nodo)); (yyval.nodo)=nuevoForExpresion((yyvsp[-5].nodo),(yyvsp[-3].nodo),NULL,nuevoBloqueExpresionConContextoPadre(b)); }
#line 2281 "build/parser.tab.c"
    break;

  case 42: /* for_statement: TOKEN_FOR '(' asignacion ';' expr ';' incremento ')' bloque  */
#line 210 "src/entriesTools/parser.y"
                                                              { (yyval.nodo)=nuevoForExpresion((yyvsp[-6].nodo),(yyvsp[-4].nodo),(yyvsp[-2].nodo),(yyvsp[0].nodo)); }
#line 2287 "build/parser.tab.c"
    break;

  case 43: /* for_statement: TOKEN_FOR '(' asignacion ';' expr ';' incremento ')' instruccion_simple  */
#line 211 "src/entriesTools/parser.y"
                                                                          { AbstractExpresion* b=nuevoListaExpresiones(); agregarHijo(b,(yyvsp[0].nodo)); (yyval.nodo)=nuevoForExpresion((yyvsp[-6].nodo),(yyvsp[-4].nodo),(yyvsp[-2].nodo),nuevoBloqueExpresion(b)); }
#line 2293 "build/parser.tab.c"
    break;

  case 44: /* incremento: asignacion  */
#line 215 "src/entriesTools/parser.y"
                   { (yyval.nodo) = (yyvsp[0].nodo); }
#line 2299 "build/parser.tab.c"
    break;

  case 45: /* incremento: TOKEN_IDENTIFIER TOKEN_PLUS_PLUS  */
#line 216 "src/entriesTools/parser.y"
                                       { AbstractExpresion* id= nuevoIdentificadorExpresion((yyvsp[-1].string)); SET_POS(id,(yylsp[-1])); AbstractExpresion* uno=nuevoPrimitivoExpresion(strdup("1"),INT); SET_POS(uno,(yylsp[0])); AbstractExpresion* sum=nuevoSumaExpresion(id,uno); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-1].string),sum); SET_POS(asg,(yylsp[-1])); (yyval.nodo)=asg;}
#line 2305 "build/parser.tab.c"
    break;

  case 46: /* incremento: TOKEN_IDENTIFIER TOKEN_MINUS_MINUS  */
#line 217 "src/entriesTools/parser.y"
                                         { AbstractExpresion* id= nuevoIdentificadorExpresion((yyvsp[-1].string)); SET_POS(id,(yylsp[-1])); AbstractExpresion* uno=nuevoPrimitivoExpresion(strdup("1"),INT); SET_POS(uno,(yylsp[0])); AbstractExpresion* res=nuevoRestaExpresion(id,uno); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-1].string),res); SET_POS(asg,(yylsp[-1])); (yyval.nodo)=asg;}
#line 2311 "build/parser.tab.c"
    break;

  case 47: /* case_list: case_item  */
#line 228 "src/entriesTools/parser.y"
                     { 
        /* case_item ya retorna una lista de CaseExpresion; la usamos directamente */
        (yyval.nodo) = (yyvsp[0].nodo);
    }
#line 2320 "build/parser.tab.c"
    break;

  case 48: /* case_list: case_list case_item  */
#line 232 "src/entriesTools/parser.y"
                          {
        /* aplanar: anexar todos los hijos de $2 a la lista existente */
        for(size_t i=0;i<(yyvsp[0].nodo)->numHijos;i++){ agregarHijo((yyvsp[-1].nodo), (yyvsp[0].nodo)->hijos[i]); }
        (yyval.nodo) = (yyvsp[-1].nodo);
    }
#line 2330 "build/parser.tab.c"
    break;

  case 49: /* case_labels: TOKEN_CASE expr ':'  */
#line 239 "src/entriesTools/parser.y"
                                 {
        AbstractExpresion* etiquetas = nuevoListaExpresiones();
        agregarHijo(etiquetas, (yyvsp[-1].nodo));
        (yyval.nodo) = etiquetas;
    }
#line 2340 "build/parser.tab.c"
    break;

  case 50: /* case_labels: case_labels TOKEN_CASE expr ':'  */
#line 244 "src/entriesTools/parser.y"
                                      {
        agregarHijo((yyvsp[-3].nodo), (yyvsp[-1].nodo));
        (yyval.nodo) = (yyvsp[-3].nodo);
    }
#line 2349 "build/parser.tab.c"
    break;

  case 51: /* case_item: case_labels instrucciones_case  */
#line 250 "src/entriesTools/parser.y"
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
#line 2366 "build/parser.tab.c"
    break;

  case 52: /* case_item: case_labels instrucciones_case TOKEN_BREAK ';'  */
#line 262 "src/entriesTools/parser.y"
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
#line 2381 "build/parser.tab.c"
    break;

  case 53: /* instrucciones_case: instruccion_case  */
#line 274 "src/entriesTools/parser.y"
                                     {
        AbstractExpresion* lista = nuevoListaExpresiones();
        agregarHijo(lista, (yyvsp[0].nodo));
        (yyval.nodo) = lista;
    }
#line 2391 "build/parser.tab.c"
    break;

  case 54: /* instrucciones_case: instrucciones_case instruccion_case  */
#line 279 "src/entriesTools/parser.y"
                                          {
        agregarHijo((yyvsp[-1].nodo), (yyvsp[0].nodo));
        (yyval.nodo) = (yyvsp[-1].nodo);
    }
#line 2400 "build/parser.tab.c"
    break;

  case 55: /* instruccion_case: imprimir ';'  */
#line 285 "src/entriesTools/parser.y"
                               {(yyval.nodo) = (yyvsp[-1].nodo); }
#line 2406 "build/parser.tab.c"
    break;

  case 56: /* instruccion_case: bloque  */
#line 286 "src/entriesTools/parser.y"
             {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2412 "build/parser.tab.c"
    break;

  case 57: /* instruccion_case: declaracion_var ';'  */
#line 287 "src/entriesTools/parser.y"
                          {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2418 "build/parser.tab.c"
    break;

  case 58: /* instruccion_case: asignacion ';'  */
#line 288 "src/entriesTools/parser.y"
                     {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2424 "build/parser.tab.c"
    break;

  case 59: /* default_case: TOKEN_DEFAULT ':' instrucciones_case  */
#line 291 "src/entriesTools/parser.y"
                                                   { (yyval.nodo) = (yyvsp[0].nodo); }
#line 2430 "build/parser.tab.c"
    break;

  case 60: /* default_case: TOKEN_DEFAULT ':' instrucciones_case TOKEN_BREAK ';'  */
#line 292 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2436 "build/parser.tab.c"
    break;

  case 61: /* break_statement: TOKEN_BREAK ';'  */
#line 295 "src/entriesTools/parser.y"
                                 { (yyval.nodo) = nuevoBreakExpresion(); SET_POS((yyval.nodo), (yylsp[-1])); }
#line 2442 "build/parser.tab.c"
    break;

  case 62: /* continue_statement: TOKEN_CONTINUE ';'  */
#line 298 "src/entriesTools/parser.y"
                                       { (yyval.nodo) = nuevoContinueExpresion(); SET_POS((yyval.nodo), (yylsp[-1])); }
#line 2448 "build/parser.tab.c"
    break;

  case 63: /* instruccion_simple: imprimir  */
#line 301 "src/entriesTools/parser.y"
                             {(yyval.nodo) = (yyvsp[0].nodo); }
#line 2454 "build/parser.tab.c"
    break;

  case 64: /* instruccion_simple: declaracion_var  */
#line 302 "src/entriesTools/parser.y"
                      {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2460 "build/parser.tab.c"
    break;

  case 65: /* instruccion_simple: asignacion  */
#line 303 "src/entriesTools/parser.y"
                 {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2466 "build/parser.tab.c"
    break;

  case 66: /* asignacion: TOKEN_IDENTIFIER '=' expr  */
#line 306 "src/entriesTools/parser.y"
                                      { (yyval.nodo) = nuevoAsignacionExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); SET_POS((yyval.nodo), (yylsp[-2])); }
#line 2472 "build/parser.tab.c"
    break;

  case 67: /* asignacion: TOKEN_IDENTIFIER TOKEN_PLUS_ASSIGN expr  */
#line 307 "src/entriesTools/parser.y"
                                              { (yyval.nodo) = nuevoAsignacionSumaExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2478 "build/parser.tab.c"
    break;

  case 68: /* asignacion: TOKEN_IDENTIFIER TOKEN_MINUS_ASSIGN expr  */
#line 308 "src/entriesTools/parser.y"
                                               { (yyval.nodo) = nuevoAsignacionRestaExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2484 "build/parser.tab.c"
    break;

  case 69: /* asignacion: TOKEN_IDENTIFIER TOKEN_MUL_ASSIGN expr  */
#line 309 "src/entriesTools/parser.y"
                                             { (yyval.nodo) = nuevoAsignacionMultiplicacionExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2490 "build/parser.tab.c"
    break;

  case 70: /* asignacion: TOKEN_IDENTIFIER TOKEN_DIV_ASSIGN expr  */
#line 310 "src/entriesTools/parser.y"
                                             { (yyval.nodo) = nuevoAsignacionDivisionExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2496 "build/parser.tab.c"
    break;

  case 71: /* asignacion: TOKEN_IDENTIFIER TOKEN_MOD_ASSIGN expr  */
#line 311 "src/entriesTools/parser.y"
                                             { (yyval.nodo) = nuevoAsignacionModuloExpresion((yyvsp[-2].string), (yyvsp[0].nodo)); }
#line 2502 "build/parser.tab.c"
    break;

  case 72: /* asignacion: TOKEN_IDENTIFIER TOKEN_AND_ASSIGN expr  */
#line 312 "src/entriesTools/parser.y"
                                             { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoBitAndExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2508 "build/parser.tab.c"
    break;

  case 73: /* asignacion: TOKEN_IDENTIFIER TOKEN_OR_ASSIGN expr  */
#line 313 "src/entriesTools/parser.y"
                                            { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoBitOrExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2514 "build/parser.tab.c"
    break;

  case 74: /* asignacion: TOKEN_IDENTIFIER TOKEN_XOR_ASSIGN expr  */
#line 314 "src/entriesTools/parser.y"
                                             { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoBitXorExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2520 "build/parser.tab.c"
    break;

  case 75: /* asignacion: TOKEN_IDENTIFIER TOKEN_SHL_ASSIGN expr  */
#line 315 "src/entriesTools/parser.y"
                                             { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoShiftLeftExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2526 "build/parser.tab.c"
    break;

  case 76: /* asignacion: TOKEN_IDENTIFIER TOKEN_SHR_ASSIGN expr  */
#line 316 "src/entriesTools/parser.y"
                                             { AbstractExpresion* id=nuevoIdentificadorExpresion((yyvsp[-2].string)); SET_POS(id,(yylsp[-2])); AbstractExpresion* op=nuevoShiftRightExpresion(id,(yyvsp[0].nodo)); AbstractExpresion* asg=nuevoAsignacionExpresion((yyvsp[-2].string),op); SET_POS(asg,(yylsp[-2])); (yyval.nodo)=asg;}
#line 2532 "build/parser.tab.c"
    break;

  case 77: /* lista_Expr: lista_Expr ',' expr  */
#line 318 "src/entriesTools/parser.y"
                                 { agregarHijo((yyvsp[-2].nodo), (yyvsp[0].nodo)); (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2538 "build/parser.tab.c"
    break;

  case 78: /* lista_Expr: expr  */
#line 319 "src/entriesTools/parser.y"
           { 
                AbstractExpresion* b = nuevoListaExpresiones();
                agregarHijo(b, (yyvsp[0].nodo));
                (yyval.nodo) =  b;
            }
#line 2548 "build/parser.tab.c"
    break;

  case 79: /* imprimir: TOKEN_PRINT '(' lista_Expr ')'  */
#line 326 "src/entriesTools/parser.y"
                                         { (yyval.nodo) =  nuevoPrintExpresion((yyvsp[-1].nodo), 0); }
#line 2554 "build/parser.tab.c"
    break;

  case 80: /* imprimir: TOKEN_SYSTEM_OUT_PRINTLN '(' lista_Expr ')'  */
#line 327 "src/entriesTools/parser.y"
                                                  { (yyval.nodo) =  nuevoPrintExpresion((yyvsp[-1].nodo), 1); }
#line 2560 "build/parser.tab.c"
    break;

  case 81: /* imprimir: TOKEN_SYSTEM_OUT_PRINTLN '(' ')'  */
#line 328 "src/entriesTools/parser.y"
                                       { (yyval.nodo) = nuevoPrintExpresion(nuevoListaExpresiones(), 1); }
#line 2566 "build/parser.tab.c"
    break;

  case 82: /* imprimir: TOKEN_SYSTEM_OUT_PRINT '(' lista_Expr ')'  */
#line 329 "src/entriesTools/parser.y"
                                                { (yyval.nodo) =  nuevoPrintExpresion((yyvsp[-1].nodo), 0); }
#line 2572 "build/parser.tab.c"
    break;

  case 83: /* imprimir: TOKEN_SYSTEM_OUT_PRINT '(' ')'  */
#line 330 "src/entriesTools/parser.y"
                                     { (yyval.nodo) = nuevoPrintExpresion(nuevoListaExpresiones(), 0); }
#line 2578 "build/parser.tab.c"
    break;

  case 84: /* bloque: '{' lSentencia '}'  */
#line 333 "src/entriesTools/parser.y"
                           { (yyval.nodo) = nuevoBloqueExpresion((yyvsp[-1].nodo)); }
#line 2584 "build/parser.tab.c"
    break;

  case 85: /* bloque: '{' error '}'  */
#line 334 "src/entriesTools/parser.y"
                    { (yyval.nodo) = nuevoBloqueExpresion(nuevoListaExpresiones()); yyerrok; }
#line 2590 "build/parser.tab.c"
    break;

  case 86: /* bloque_for: '{' lSentencia '}'  */
#line 336 "src/entriesTools/parser.y"
                               { (yyval.nodo) = nuevoBloqueExpresionConContextoPadre((yyvsp[-1].nodo)); }
#line 2596 "build/parser.tab.c"
    break;

  case 90: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' TOKEN_NEW tipoPrimitivo dims_expr_list  */
#line 351 "src/entriesTools/parser.y"
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
#line 2618 "build/parser.tab.c"
    break;

  case 91: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' '{' lista_Expr '}'  */
#line 369 "src/entriesTools/parser.y"
                                                                       {
        if((yyvsp[-5].boolean) != 1){ (yyval.nodo) = parser_error_node((yylsp[-4]), "Literal 1D usado pero se declararon %d dimensiones", (yyvsp[-5].boolean)); }
    else { AbstractExpresion* nodo = nuevoArrayLiteralDeclaracion((yyvsp[-6].tipoDato), (yyvsp[-4].string), (yyvsp[-1].nodo)); nodo->linea=(yylsp[-4]).first_line; nodo->columna=(yylsp[-4]).first_column; (yyval.nodo)=nodo; }
    }
#line 2627 "build/parser.tab.c"
    break;

  case 92: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' bloque2D  */
#line 374 "src/entriesTools/parser.y"
                                                             {
        if((yyvsp[-3].boolean) != 2){ (yyval.nodo) = parser_error_node((yylsp[-2]), "Literal 2D usado pero se declararon %d dimensiones", (yyvsp[-3].boolean)); }
    else { AbstractExpresion* nodo = nuevoMatrixLiteralDeclaracion((yyvsp[-4].tipoDato), (yyvsp[-2].string), (yyvsp[0].nodo)); nodo->linea=(yylsp[-2]).first_line; nodo->columna=(yylsp[-2]).first_column; (yyval.nodo)=nodo; }
    }
#line 2636 "build/parser.tab.c"
    break;

  case 93: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' '{' lista_bloques2D '}'  */
#line 379 "src/entriesTools/parser.y"
                                                                            {
        if((yyvsp[-5].boolean) != 3){ (yyval.nodo) = parser_error_node((yylsp[-4]), "Literal 3D usado pero se declararon %d dimensiones", (yyvsp[-5].boolean)); }
    else { AbstractExpresion* nodo = nuevoArray3DLiteralDeclaracion((yyvsp[-6].tipoDato), (yyvsp[-4].string), (yyvsp[-1].nodo)); nodo->linea=(yylsp[-4]).first_line; nodo->columna=(yylsp[-4]).first_column; (yyval.nodo)=nodo; }
    }
#line 2645 "build/parser.tab.c"
    break;

  case 94: /* array_decl_local: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' expr  */
#line 384 "src/entriesTools/parser.y"
                                                         {
    AbstractExpresion* nodo = nuevoArrayDeclaracionDesdeExpr((yyvsp[-4].tipoDato), (yyvsp[-2].string), (yyvsp[0].nodo)); nodo->linea=(yylsp[-2]).first_line; nodo->columna=(yylsp[-2]).first_column; (yyval.nodo) = nodo; }
#line 2652 "build/parser.tab.c"
    break;

  case 95: /* brackets_seq: '[' ']'  */
#line 389 "src/entriesTools/parser.y"
                      { (yyval.boolean) = 1; }
#line 2658 "build/parser.tab.c"
    break;

  case 96: /* brackets_seq: brackets_seq '[' ']'  */
#line 390 "src/entriesTools/parser.y"
                           { (yyval.boolean) = (yyvsp[-2].boolean) + 1; }
#line 2664 "build/parser.tab.c"
    break;

  case 97: /* var_decl: tipoPrimitivo TOKEN_IDENTIFIER '=' expr  */
#line 393 "src/entriesTools/parser.y"
                                                { (yyval.nodo) = nuevoDeclaracionVariables((yyvsp[-3].tipoDato),(yyvsp[-2].string),(yyvsp[0].nodo),0); ((DeclaracionVariable*)(yyval.nodo))->linea = (yylsp[-2]).first_line; ((DeclaracionVariable*)(yyval.nodo))->columna = (yylsp[-2]).first_column; }
#line 2670 "build/parser.tab.c"
    break;

  case 98: /* var_decl: tipoPrimitivo TOKEN_IDENTIFIER  */
#line 394 "src/entriesTools/parser.y"
                                     { (yyval.nodo) = nuevoDeclaracionVariables((yyvsp[-1].tipoDato),(yyvsp[0].string),NULL,0); ((DeclaracionVariable*)(yyval.nodo))->linea = (yylsp[0]).first_line; ((DeclaracionVariable*)(yyval.nodo))->columna = (yylsp[0]).first_column; }
#line 2676 "build/parser.tab.c"
    break;

  case 99: /* final_var_decl: TOKEN_FINAL tipoPrimitivo TOKEN_IDENTIFIER '=' expr  */
#line 397 "src/entriesTools/parser.y"
                                                        { (yyval.nodo) = nuevoDeclaracionVariables((yyvsp[-3].tipoDato),(yyvsp[-2].string),(yyvsp[0].nodo),1); ((DeclaracionVariable*)(yyval.nodo))->linea = (yylsp[-2]).first_line; ((DeclaracionVariable*)(yyval.nodo))->columna = (yylsp[-2]).first_column; }
#line 2682 "build/parser.tab.c"
    break;

  case 100: /* dims_expr_list: '[' expr ']'  */
#line 404 "src/entriesTools/parser.y"
                             { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l,(yyvsp[-1].nodo)); (yyval.nodo) = l; }
#line 2688 "build/parser.tab.c"
    break;

  case 101: /* dims_expr_list: dims_expr_list '[' expr ']'  */
#line 405 "src/entriesTools/parser.y"
                                      { agregarHijo((yyvsp[-3].nodo),(yyvsp[-1].nodo)); (yyval.nodo) = (yyvsp[-3].nodo); }
#line 2694 "build/parser.tab.c"
    break;

  case 102: /* lista_bloques2D: bloque2D  */
#line 413 "src/entriesTools/parser.y"
                          { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l, (yyvsp[0].nodo)); (yyval.nodo) = l; }
#line 2700 "build/parser.tab.c"
    break;

  case 103: /* lista_bloques2D: lista_bloques2D ',' bloque2D  */
#line 414 "src/entriesTools/parser.y"
                                   { agregarHijo((yyvsp[-2].nodo), (yyvsp[0].nodo)); (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2706 "build/parser.tab.c"
    break;

  case 104: /* bloque2D: '{' filas_lista '}'  */
#line 416 "src/entriesTools/parser.y"
                              { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 2712 "build/parser.tab.c"
    break;

  case 105: /* filas_lista: fila_matriz  */
#line 418 "src/entriesTools/parser.y"
                         { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l, (yyvsp[0].nodo)); (yyval.nodo) = l; }
#line 2718 "build/parser.tab.c"
    break;

  case 106: /* filas_lista: filas_lista ',' fila_matriz  */
#line 419 "src/entriesTools/parser.y"
                                  { agregarHijo((yyvsp[-2].nodo), (yyvsp[0].nodo)); (yyval.nodo) = (yyvsp[-2].nodo); }
#line 2724 "build/parser.tab.c"
    break;

  case 107: /* fila_matriz: '{' lista_Expr '}'  */
#line 421 "src/entriesTools/parser.y"
                                { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 2730 "build/parser.tab.c"
    break;

  case 108: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una '=' expr  */
#line 423 "src/entriesTools/parser.y"
                                                           {
    AbstractExpresion* idx = (yyvsp[-2].nodo)->hijos[0]; (yyval.nodo) = nuevoArrayAsignacionElemento((yyvsp[-3].string), idx, (yyvsp[0].nodo)); }
#line 2737 "build/parser.tab.c"
    break;

  case 109: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi '=' expr  */
#line 425 "src/entriesTools/parser.y"
                                              {
        size_t n=(yyvsp[-2].nodo)->numHijos; if (n==2) (yyval.nodo)=nuevoMatrixAsignacionElemento((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[-2].nodo)->hijos[1], (yyvsp[0].nodo)); else (yyval.nodo)=nuevoMultiArrayAsignacionElemento((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo)); }
#line 2744 "build/parser.tab.c"
    break;

  case 110: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_PLUS_ASSIGN expr  */
#line 428 "src/entriesTools/parser.y"
                                                          { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_ADD); }
#line 2750 "build/parser.tab.c"
    break;

  case 111: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_MINUS_ASSIGN expr  */
#line 429 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_SUB); }
#line 2756 "build/parser.tab.c"
    break;

  case 112: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_MUL_ASSIGN expr  */
#line 430 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_MUL); }
#line 2762 "build/parser.tab.c"
    break;

  case 113: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_DIV_ASSIGN expr  */
#line 431 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_DIV); }
#line 2768 "build/parser.tab.c"
    break;

  case 114: /* asignacion_elemento: TOKEN_IDENTIFIER indices_una TOKEN_MOD_ASSIGN expr  */
#line 432 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoArrayAsignacionElementoCompound((yyvsp[-3].string), (yyvsp[-2].nodo)->hijos[0], (yyvsp[0].nodo), COP_MOD); }
#line 2774 "build/parser.tab.c"
    break;

  case 115: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_PLUS_ASSIGN expr  */
#line 434 "src/entriesTools/parser.y"
                                                            { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_ADD); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_ADD); }
#line 2780 "build/parser.tab.c"
    break;

  case 116: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_MINUS_ASSIGN expr  */
#line 435 "src/entriesTools/parser.y"
                                                             { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_SUB); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_SUB); }
#line 2786 "build/parser.tab.c"
    break;

  case 117: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_MUL_ASSIGN expr  */
#line 436 "src/entriesTools/parser.y"
                                                           { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_MUL); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_MUL); }
#line 2792 "build/parser.tab.c"
    break;

  case 118: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_DIV_ASSIGN expr  */
#line 437 "src/entriesTools/parser.y"
                                                           { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_DIV); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_DIV); }
#line 2798 "build/parser.tab.c"
    break;

  case 119: /* asignacion_elemento: TOKEN_IDENTIFIER indices_multi TOKEN_MOD_ASSIGN expr  */
#line 438 "src/entriesTools/parser.y"
                                                           { size_t n=(yyvsp[-2].nodo)->numHijos; if(n==2) (yyval.nodo)=nuevoMatrixAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo)->hijos[0],(yyvsp[-2].nodo)->hijos[1],(yyvsp[0].nodo),COP_MOD); else (yyval.nodo)=nuevoMultiArrayAsignacionElementoCompound((yyvsp[-3].string),(yyvsp[-2].nodo),(yyvsp[0].nodo),COP_MOD); }
#line 2804 "build/parser.tab.c"
    break;

  case 120: /* indices_una: '[' expr ']'  */
#line 442 "src/entriesTools/parser.y"
                          { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l,(yyvsp[-1].nodo)); (yyval.nodo)=l; }
#line 2810 "build/parser.tab.c"
    break;

  case 121: /* indices_multi: indices_una indices_una  */
#line 443 "src/entriesTools/parser.y"
                                       { /* concat */ for(size_t i=0;i<(yyvsp[0].nodo)->numHijos;i++) agregarHijo((yyvsp[-1].nodo),(yyvsp[0].nodo)->hijos[i]); (yyval.nodo)=(yyvsp[-1].nodo); }
#line 2816 "build/parser.tab.c"
    break;

  case 122: /* indices_multi: indices_multi indices_una  */
#line 444 "src/entriesTools/parser.y"
                                { for(size_t i=0;i<(yyvsp[0].nodo)->numHijos;i++) agregarHijo((yyvsp[-1].nodo),(yyvsp[0].nodo)->hijos[i]); (yyval.nodo)=(yyvsp[-1].nodo); }
#line 2822 "build/parser.tab.c"
    break;

  case 123: /* expr: expr '+' expr  */
#line 461 "src/entriesTools/parser.y"
                      { (yyval.nodo) =  nuevoSumaExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo));  }
#line 2828 "build/parser.tab.c"
    break;

  case 124: /* expr: expr '-' expr  */
#line 462 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoRestaExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2834 "build/parser.tab.c"
    break;

  case 125: /* expr: expr '*' expr  */
#line 463 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoMultiplicacionExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2840 "build/parser.tab.c"
    break;

  case 126: /* expr: expr '/' expr  */
#line 464 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoDivisionExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2846 "build/parser.tab.c"
    break;

  case 127: /* expr: expr '%' expr  */
#line 465 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoModuloExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2852 "build/parser.tab.c"
    break;

  case 128: /* expr: expr '&' expr  */
#line 466 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoBitAndExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2858 "build/parser.tab.c"
    break;

  case 129: /* expr: expr '|' expr  */
#line 467 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoBitOrExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2864 "build/parser.tab.c"
    break;

  case 130: /* expr: expr '^' expr  */
#line 468 "src/entriesTools/parser.y"
                    { (yyval.nodo) =  nuevoBitXorExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2870 "build/parser.tab.c"
    break;

  case 131: /* expr: expr TOKEN_SHIFT_LEFT expr  */
#line 469 "src/entriesTools/parser.y"
                                 { (yyval.nodo) =  nuevoShiftLeftExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2876 "build/parser.tab.c"
    break;

  case 132: /* expr: expr TOKEN_SHIFT_RIGHT expr  */
#line 470 "src/entriesTools/parser.y"
                                  { (yyval.nodo) =  nuevoShiftRightExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2882 "build/parser.tab.c"
    break;

  case 133: /* expr: expr TOKEN_EQUAL expr  */
#line 471 "src/entriesTools/parser.y"
                            { (yyval.nodo) =  nuevoIgualdadExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2888 "build/parser.tab.c"
    break;

  case 134: /* expr: expr TOKEN_NOT_EQUAL expr  */
#line 472 "src/entriesTools/parser.y"
                                { (yyval.nodo) =  nuevoDesigualdadExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2894 "build/parser.tab.c"
    break;

  case 135: /* expr: expr TOKEN_GREATER expr  */
#line 473 "src/entriesTools/parser.y"
                              { (yyval.nodo) =  nuevoMayorQueExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2900 "build/parser.tab.c"
    break;

  case 136: /* expr: expr TOKEN_LESS expr  */
#line 474 "src/entriesTools/parser.y"
                           { (yyval.nodo) =  nuevoMenorQueExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2906 "build/parser.tab.c"
    break;

  case 137: /* expr: expr TOKEN_GREATER_EQUAL expr  */
#line 475 "src/entriesTools/parser.y"
                                    { (yyval.nodo) =  nuevoMayorIgualQueExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2912 "build/parser.tab.c"
    break;

  case 138: /* expr: expr TOKEN_LESS_EQUAL expr  */
#line 476 "src/entriesTools/parser.y"
                                 { (yyval.nodo) =  nuevoMenorIgualQueExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2918 "build/parser.tab.c"
    break;

  case 139: /* expr: expr TOKEN_AND expr  */
#line 477 "src/entriesTools/parser.y"
                          { (yyval.nodo) =  nuevoAndExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2924 "build/parser.tab.c"
    break;

  case 140: /* expr: expr TOKEN_OR expr  */
#line 478 "src/entriesTools/parser.y"
                         { (yyval.nodo) =  nuevoOrExpresion((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2930 "build/parser.tab.c"
    break;

  case 141: /* expr: TOKEN_NOT expr  */
#line 479 "src/entriesTools/parser.y"
                     { (yyval.nodo) =  nuevoNotExpresion((yyvsp[0].nodo)); }
#line 2936 "build/parser.tab.c"
    break;

  case 142: /* expr: '-' expr  */
#line 480 "src/entriesTools/parser.y"
                          { (yyval.nodo) =  nuevoUnarioExpresion((yyvsp[0].nodo));  }
#line 2942 "build/parser.tab.c"
    break;

  case 143: /* expr: postfix  */
#line 481 "src/entriesTools/parser.y"
              { (yyval.nodo) = (yyvsp[0].nodo); }
#line 2948 "build/parser.tab.c"
    break;

  case 144: /* postfix: unary  */
#line 484 "src/entriesTools/parser.y"
               { (yyval.nodo) = (yyvsp[0].nodo); }
#line 2954 "build/parser.tab.c"
    break;

  case 145: /* postfix: postfix '[' expr ']'  */
#line 485 "src/entriesTools/parser.y"
                           { (yyval.nodo) = nuevoArrayAcceso((yyvsp[-3].nodo), (yyvsp[-1].nodo)); }
#line 2960 "build/parser.tab.c"
    break;

  case 146: /* postfix: postfix '.' TOKEN_LENGTH  */
#line 486 "src/entriesTools/parser.y"
                               { (yyval.nodo) = nuevoArrayLength((yyvsp[-2].nodo)); }
#line 2966 "build/parser.tab.c"
    break;

  case 147: /* postfix: postfix '.' TOKEN_ADD '(' expr ')'  */
#line 487 "src/entriesTools/parser.y"
                                         { (yyval.nodo) = nuevoArrayAdd((yyvsp[-5].nodo), (yyvsp[-1].nodo)); }
#line 2972 "build/parser.tab.c"
    break;

  case 148: /* postfix: postfix '.' TOKEN_IDENTIFIER '(' expr ')'  */
#line 488 "src/entriesTools/parser.y"
                                                { if(strcmp((yyvsp[-3].string),"equals")==0){ (yyval.nodo) = nuevoIgualdadExpresion((yyvsp[-5].nodo),(yyvsp[-1].nodo));} else { (yyval.nodo)=(yyvsp[-5].nodo); } }
#line 2978 "build/parser.tab.c"
    break;

  case 149: /* postfix: postfix '.' TOKEN_IDENTIFIER '(' ')'  */
#line 489 "src/entriesTools/parser.y"
                                           { if(strcmp((yyvsp[-2].string),"equals")==0){ AbstractExpresion* e=parser_error_node((yylsp[-2]),"método equals requiere un argumento"); (yyval.nodo)=(yyvsp[-4].nodo); (void)e; } else { (yyval.nodo)=(yyvsp[-4].nodo); } }
#line 2984 "build/parser.tab.c"
    break;

  case 150: /* postfix: TOKEN_IDENTIFIER TOKEN_PLUS_PLUS  */
#line 490 "src/entriesTools/parser.y"
                                       {
        AbstractExpresion* id1 = nuevoIdentificadorExpresion((yyvsp[-1].string));
        AbstractExpresion* uno1 = nuevoPrimitivoExpresion(strdup("1"), INT);
        AbstractExpresion* sum1 = nuevoSumaExpresion(id1, uno1);
        (yyval.nodo) = nuevoAsignacionExpresion((yyvsp[-1].string), sum1);
    }
#line 2995 "build/parser.tab.c"
    break;

  case 151: /* postfix: TOKEN_IDENTIFIER TOKEN_MINUS_MINUS  */
#line 496 "src/entriesTools/parser.y"
                                         {
        AbstractExpresion* id2 = nuevoIdentificadorExpresion((yyvsp[-1].string));
        AbstractExpresion* uno2 = nuevoPrimitivoExpresion(strdup("1"), INT);
        AbstractExpresion* res2 = nuevoRestaExpresion(id2, uno2);
        (yyval.nodo) = nuevoAsignacionExpresion((yyvsp[-1].string), res2);
    }
#line 3006 "build/parser.tab.c"
    break;

  case 152: /* unary: atom  */
#line 504 "src/entriesTools/parser.y"
            { (yyval.nodo) = (yyvsp[0].nodo); }
#line 3012 "build/parser.tab.c"
    break;

  case 153: /* unary: '(' tipoPrimitivo ')' postfix  */
#line 508 "src/entriesTools/parser.y"
                                                { (yyval.nodo) = nuevoCastExpresion((yyvsp[-2].tipoDato), (yyvsp[0].nodo)); }
#line 3018 "build/parser.tab.c"
    break;

  case 154: /* atom: primitivo  */
#line 511 "src/entriesTools/parser.y"
                { (yyval.nodo) = (yyvsp[0].nodo); }
#line 3024 "build/parser.tab.c"
    break;

  case 155: /* atom: '(' expr ')'  */
#line 512 "src/entriesTools/parser.y"
                   { (yyval.nodo) = (yyvsp[-1].nodo); }
#line 3030 "build/parser.tab.c"
    break;

  case 156: /* atom: TOKEN_IDENTIFIER  */
#line 513 "src/entriesTools/parser.y"
                       { (yyval.nodo) = nuevoIdentificadorExpresion((yyvsp[0].string)); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3036 "build/parser.tab.c"
    break;

  case 157: /* atom: llamada_funcion  */
#line 514 "src/entriesTools/parser.y"
                      { (yyval.nodo) = (yyvsp[0].nodo); /* la llamada ya debería heredar pos de su identificador interno */ }
#line 3042 "build/parser.tab.c"
    break;

  case 158: /* atom: TOKEN_ARRAYS '.' TOKEN_INDEXOF '(' expr ',' expr ')'  */
#line 515 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoArraysIndexOf((yyvsp[-3].nodo), (yyvsp[-1].nodo)); }
#line 3048 "build/parser.tab.c"
    break;

  case 159: /* atom: TOKEN_INTEGER_CLASS '.' TOKEN_PARSE_INT '(' expr ')'  */
#line 516 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoParseEntero((yyvsp[-1].nodo)); }
#line 3054 "build/parser.tab.c"
    break;

  case 160: /* atom: TOKEN_DOUBLE_CLASS '.' TOKEN_PARSE_DOUBLE '(' expr ')'  */
#line 517 "src/entriesTools/parser.y"
                                                             { (yyval.nodo) = nuevoParseDouble((yyvsp[-1].nodo)); }
#line 3060 "build/parser.tab.c"
    break;

  case 161: /* atom: TOKEN_FLOAT_CLASS '.' TOKEN_PARSE_FLOAT '(' expr ')'  */
#line 518 "src/entriesTools/parser.y"
                                                           { (yyval.nodo) = nuevoParseFloat((yyvsp[-1].nodo)); }
#line 3066 "build/parser.tab.c"
    break;

  case 162: /* atom: TOKEN_DSTRING '.' TOKEN_VALUE_OF '(' expr ')'  */
#line 519 "src/entriesTools/parser.y"
                                                    { (yyval.nodo) = nuevoStringValueOf((yyvsp[-1].nodo)); }
#line 3072 "build/parser.tab.c"
    break;

  case 163: /* atom: TOKEN_DSTRING '.' TOKEN_JOIN '(' expr ',' expr ')'  */
#line 520 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoStringJoin((yyvsp[-3].nodo), (yyvsp[-1].nodo), 1); }
#line 3078 "build/parser.tab.c"
    break;

  case 164: /* atom: TOKEN_DSTRING '.' TOKEN_JOIN '(' expr ',' join_variadic_args ')'  */
#line 521 "src/entriesTools/parser.y"
                                                                       { (yyval.nodo) = nuevoStringJoin((yyvsp[-3].nodo), (yyvsp[-1].nodo), 0); }
#line 3084 "build/parser.tab.c"
    break;

  case 165: /* join_variadic_args: expr ',' lista_Expr  */
#line 524 "src/entriesTools/parser.y"
                                        {
        /* crear lista que contenga primer expr y luego los de lista_Expr */
        AbstractExpresion* l = nuevoListaExpresiones();
        agregarHijo(l, (yyvsp[-2].nodo));
        for(size_t i=0;i<(yyvsp[0].nodo)->numHijos;i++){ agregarHijo(l, (yyvsp[0].nodo)->hijos[i]); }
        (yyval.nodo) = l;
    }
#line 3096 "build/parser.tab.c"
    break;

  case 166: /* primitivo: TOKEN_UNSIGNED_INTEGER  */
#line 532 "src/entriesTools/parser.y"
                                  { (yyval.nodo) = nuevoPrimitivoExpresion((yyvsp[0].string), INT); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3102 "build/parser.tab.c"
    break;

  case 167: /* primitivo: TOKEN_STRING  */
#line 533 "src/entriesTools/parser.y"
                   { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), STRING); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3108 "build/parser.tab.c"
    break;

  case 168: /* primitivo: TOKEN_REAL_FLOAT  */
#line 534 "src/entriesTools/parser.y"
                       { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), FLOAT); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3114 "build/parser.tab.c"
    break;

  case 169: /* primitivo: TOKEN_REAL  */
#line 535 "src/entriesTools/parser.y"
                 { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), DOUBLE); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3120 "build/parser.tab.c"
    break;

  case 170: /* primitivo: TOKEN_CHAR_LITERAL  */
#line 536 "src/entriesTools/parser.y"
                         { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), CHAR); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3126 "build/parser.tab.c"
    break;

  case 171: /* primitivo: TOKEN_TRUE  */
#line 537 "src/entriesTools/parser.y"
                 { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), BOOLEAN); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3132 "build/parser.tab.c"
    break;

  case 172: /* primitivo: TOKEN_FALSE  */
#line 538 "src/entriesTools/parser.y"
                  { (yyval.nodo) =  nuevoPrimitivoExpresion((yyvsp[0].string), BOOLEAN); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3138 "build/parser.tab.c"
    break;

  case 173: /* primitivo: TOKEN_NULL  */
#line 539 "src/entriesTools/parser.y"
                 { (yyval.nodo) = nuevoPrimitivoExpresion(NULL, NULO); SET_POS((yyval.nodo), (yylsp[0])); }
#line 3144 "build/parser.tab.c"
    break;

  case 174: /* tipoPrimitivo: TOKEN_DINT  */
#line 542 "src/entriesTools/parser.y"
                          { (yyval.tipoDato) = INT; }
#line 3150 "build/parser.tab.c"
    break;

  case 175: /* tipoPrimitivo: TOKEN_DFLOAT  */
#line 543 "src/entriesTools/parser.y"
                   { (yyval.tipoDato) = FLOAT; }
#line 3156 "build/parser.tab.c"
    break;

  case 176: /* tipoPrimitivo: TOKEN_DDOUBLE  */
#line 544 "src/entriesTools/parser.y"
                    { (yyval.tipoDato) = DOUBLE; }
#line 3162 "build/parser.tab.c"
    break;

  case 177: /* tipoPrimitivo: TOKEN_DSTRING  */
#line 545 "src/entriesTools/parser.y"
                    { (yyval.tipoDato) = STRING; }
#line 3168 "build/parser.tab.c"
    break;

  case 178: /* tipoPrimitivo: TOKEN_DBOOLEAN  */
#line 546 "src/entriesTools/parser.y"
                     { (yyval.tipoDato) = BOOLEAN; }
#line 3174 "build/parser.tab.c"
    break;

  case 179: /* tipoPrimitivo: TOKEN_DCHAR  */
#line 547 "src/entriesTools/parser.y"
                  { (yyval.tipoDato) = CHAR; }
#line 3180 "build/parser.tab.c"
    break;

  case 180: /* tipoPrimitivo: TOKEN_DVOID  */
#line 548 "src/entriesTools/parser.y"
                  { (yyval.tipoDato) = VOID; }
#line 3186 "build/parser.tab.c"
    break;

  case 181: /* funcion_declaracion: tipoPrimitivo TOKEN_IDENTIFIER '(' param_opt ')' bloque  */
#line 553 "src/entriesTools/parser.y"
                                                                    { 
        if((yyvsp[-2].paramList)){ (yyval.nodo) = nuevoFuncionDeclaracion((yyvsp[-5].tipoDato), (yyvsp[-4].string), (yyvsp[-2].paramList)->names, (yyvsp[-2].paramList)->types, (yyvsp[-2].paramList)->count, (yyvsp[0].nodo), 0); }
        else { (yyval.nodo) = nuevoFuncionDeclaracion((yyvsp[-5].tipoDato), (yyvsp[-4].string), NULL, NULL, 0, (yyvsp[0].nodo), 0); }
        ((FuncionDecl*)(yyval.nodo))->linea = (yylsp[-4]).first_line; ((FuncionDecl*)(yyval.nodo))->columna = (yylsp[-4]).first_column;
            }
#line 3196 "build/parser.tab.c"
    break;

  case 182: /* funcion_declaracion: tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '(' param_opt ')' bloque  */
#line 558 "src/entriesTools/parser.y"
                                                                               {
                /* Retorno array: int[][] nombre(...) */
                if((yyvsp[-5].boolean) < 1){ (yyval.nodo) = parser_error_node((yylsp[-4]), "Número de brackets de retorno inválido"); }
                else {
                        if((yyvsp[-2].paramList)){ (yyval.nodo) = nuevoFuncionDeclaracion(ARRAY, (yyvsp[-4].string), (yyvsp[-2].paramList)->names, (yyvsp[-2].paramList)->types, (yyvsp[-2].paramList)->count, (yyvsp[0].nodo), (yyvsp[-5].boolean)); }
                        else { (yyval.nodo) = nuevoFuncionDeclaracion(ARRAY, (yyvsp[-4].string), NULL, NULL, 0, (yyvsp[0].nodo), (yyvsp[-5].boolean)); }
                        ((FuncionDecl*)(yyval.nodo))->linea = (yylsp[-4]).first_line; ((FuncionDecl*)(yyval.nodo))->columna = (yylsp[-4]).first_column;
                }
            }
#line 3210 "build/parser.tab.c"
    break;

  case 183: /* main_declaracion: TOKEN_PUBLIC TOKEN_STATIC TOKEN_DVOID TOKEN_IDENTIFIER '(' main_params_opt ')' bloque  */
#line 570 "src/entriesTools/parser.y"
                                                                                                        { (yyval.nodo) = (yyvsp[0].nodo); }
#line 3216 "build/parser.tab.c"
    break;

  case 189: /* main_param_array_brackets: %empty  */
#line 574 "src/entriesTools/parser.y"
                                       { /* 0 dims */ }
#line 3222 "build/parser.tab.c"
    break;

  case 190: /* main_param_array_brackets: main_param_array_brackets '[' ']'  */
#line 574 "src/entriesTools/parser.y"
                                                                                            { /* accum dims ignored */ }
#line 3228 "build/parser.tab.c"
    break;

  case 191: /* param_opt: %empty  */
#line 576 "src/entriesTools/parser.y"
                       { (yyval.paramList) = NULL; }
#line 3234 "build/parser.tab.c"
    break;

  case 192: /* param_opt: lista_parametros  */
#line 577 "src/entriesTools/parser.y"
                       { (yyval.paramList) = (yyvsp[0].paramList); }
#line 3240 "build/parser.tab.c"
    break;

  case 193: /* param_array_brackets: %empty  */
#line 580 "src/entriesTools/parser.y"
                                  { (yyval.boolean) = 0; }
#line 3246 "build/parser.tab.c"
    break;

  case 194: /* param_array_brackets: param_array_brackets '[' ']'  */
#line 581 "src/entriesTools/parser.y"
                                   { (yyval.boolean) = (yyvsp[-2].boolean) + 1; }
#line 3252 "build/parser.tab.c"
    break;

  case 195: /* lista_parametros: tipoPrimitivo param_array_brackets TOKEN_IDENTIFIER  */
#line 583 "src/entriesTools/parser.y"
                                                                      { 
        ParamList* pl = malloc(sizeof(ParamList));
        pl->count=1; pl->names=malloc(sizeof(char*)); pl->types=malloc(sizeof(TipoDato));
        pl->names[0]=(yyvsp[0].string); pl->types[0]= ((yyvsp[-1].boolean)>0 ? ARRAY : (yyvsp[-2].tipoDato)); (yyval.paramList)=pl; }
#line 3261 "build/parser.tab.c"
    break;

  case 196: /* lista_parametros: lista_parametros ',' tipoPrimitivo param_array_brackets TOKEN_IDENTIFIER  */
#line 587 "src/entriesTools/parser.y"
                                                                               { 
        (yyvsp[-4].paramList)->names = realloc((yyvsp[-4].paramList)->names, sizeof(char*)*((yyvsp[-4].paramList)->count+1));
        (yyvsp[-4].paramList)->types = realloc((yyvsp[-4].paramList)->types, sizeof(TipoDato)*((yyvsp[-4].paramList)->count+1));
        (yyvsp[-4].paramList)->names[(yyvsp[-4].paramList)->count]=(yyvsp[0].string); (yyvsp[-4].paramList)->types[(yyvsp[-4].paramList)->count]= ((yyvsp[-1].boolean)>0 ? ARRAY : (yyvsp[-2].tipoDato)); (yyvsp[-4].paramList)->count++; (yyval.paramList)=(yyvsp[-4].paramList); }
#line 3270 "build/parser.tab.c"
    break;

  case 197: /* return_stmt: TOKEN_RETURN  */
#line 592 "src/entriesTools/parser.y"
                          { (yyval.nodo) = nuevoReturnExpresion(NULL); }
#line 3276 "build/parser.tab.c"
    break;

  case 198: /* return_stmt: TOKEN_RETURN expr  */
#line 593 "src/entriesTools/parser.y"
                        { (yyval.nodo) = nuevoReturnExpresion((yyvsp[0].nodo)); }
#line 3282 "build/parser.tab.c"
    break;

  case 199: /* for_each_statement: TOKEN_FOR '(' tipoPrimitivo TOKEN_IDENTIFIER ':' TOKEN_IDENTIFIER ')' bloque  */
#line 598 "src/entriesTools/parser.y"
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
#line 3317 "build/parser.tab.c"
    break;

  case 200: /* for_each_statement: TOKEN_FOR '(' tipoPrimitivo '[' ']' TOKEN_IDENTIFIER ':' TOKEN_IDENTIFIER ')' bloque  */
#line 628 "src/entriesTools/parser.y"
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
#line 3345 "build/parser.tab.c"
    break;

  case 201: /* argumentos_opt: %empty  */
#line 652 "src/entriesTools/parser.y"
                            { (yyval.nodo) = nuevoListaExpresiones(); }
#line 3351 "build/parser.tab.c"
    break;

  case 202: /* argumentos_opt: lista_Expr  */
#line 653 "src/entriesTools/parser.y"
                 { (yyval.nodo) = (yyvsp[0].nodo); }
#line 3357 "build/parser.tab.c"
    break;

  case 203: /* llamada_funcion: TOKEN_IDENTIFIER '(' argumentos_opt ')'  */
#line 655 "src/entriesTools/parser.y"
                                                         { (yyval.nodo) = nuevoLlamadaFuncion((yyvsp[-3].string), (yyvsp[-1].nodo)); }
#line 3363 "build/parser.tab.c"
    break;


#line 3367 "build/parser.tab.c"

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

#line 656 "src/entriesTools/parser.y"


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
