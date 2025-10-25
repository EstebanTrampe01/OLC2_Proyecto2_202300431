%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast/AbstractExpresion.h"

    int yylex(void);
    extern AbstractExpresion* ast_root;
    extern char* comments[];
    extern int comment_count;
    void yyerror(const char *s);
%}

/* Esto va al parser.tab.h */
%{
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

%}

/* Eliminadas variables globales de soporte a declaraciones de arrays antiguas */

// Definición auxiliar para parámetros de funciones (visible en parser.tab.h antes de %union)
%code requires {
    #include "ast/AbstractExpresion.h"
    #include "ast/nodos/expresiones/expresiones.h"
    #define YYLTYPE_IS_DECLARED 1
    typedef struct YYLTYPE { int first_line; int first_column; int last_line; int last_column; } YYLTYPE;
    typedef struct ParamList { int count; char** names; TipoDato* types; } ParamList;
}

%code {
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

}

/* Definición del %union para valores semánticos */
%union {
    AbstractExpresion* nodo;
    char* string;
    int boolean;
    ParamList* paramList;
    TipoDato tipoDato;
}

/* Tokens tipados */
%token <string> TOKEN_PRINT TOKEN_DINT TOKEN_DFLOAT TOKEN_DBYTE TOKEN_DSHORT TOKEN_DLONG TOKEN_DDOUBLE
TOKEN_DSTRING TOKEN_UNSIGNED_INTEGER TOKEN_REAL TOKEN_REAL_FLOAT TOKEN_STRING TOKEN_IDENTIFIER
%token <string> TOKEN_TRUE TOKEN_FALSE TOKEN_DBOOLEAN TOKEN_DCHAR TOKEN_CHAR_LITERAL TOKEN_FINAL TOKEN_SYSTEM_OUT_PRINTLN TOKEN_SYSTEM_OUT_PRINT TOKEN_DVOID
%token <string> TOKEN_COMMENT_LINE TOKEN_COMMENT_MULTI
%token TOKEN_NULL
%token TOKEN_SHIFT_LEFT TOKEN_SHIFT_RIGHT
%token TOKEN_INTEGER_CLASS TOKEN_DOUBLE_CLASS TOKEN_FLOAT_CLASS TOKEN_ARRAYS
%token TOKEN_PARSE_INT TOKEN_PARSE_DOUBLE TOKEN_PARSE_FLOAT TOKEN_VALUE_OF TOKEN_JOIN TOKEN_LENGTH TOKEN_ADD TOKEN_INDEXOF
%token TOKEN_PLUS_PLUS TOKEN_MINUS_MINUS
%token TOKEN_PLUS_ASSIGN TOKEN_MINUS_ASSIGN TOKEN_MUL_ASSIGN TOKEN_DIV_ASSIGN TOKEN_MOD_ASSIGN
%token TOKEN_AND_ASSIGN TOKEN_OR_ASSIGN TOKEN_XOR_ASSIGN TOKEN_SHL_ASSIGN TOKEN_SHR_ASSIGN
%token TOKEN_EQUAL TOKEN_NOT_EQUAL TOKEN_GREATER TOKEN_LESS TOKEN_GREATER_EQUAL TOKEN_LESS_EQUAL
%token TOKEN_AND TOKEN_OR TOKEN_NOT
%token TOKEN_IF TOKEN_ELSE TOKEN_SWITCH TOKEN_CASE TOKEN_DEFAULT TOKEN_BREAK TOKEN_WHILE TOKEN_FOR TOKEN_CONTINUE TOKEN_NEW TOKEN_RETURN TOKEN_PUBLIC TOKEN_STATIC TOKEN_REPEAT

/* Tipo de los no-terminales que llevan valor */
%type <nodo> s lSentencia instruccion expr imprimir lista_Expr bloque bloque_for declaracion_var primitivo asignacion if_statement switch_statement break_statement continue_statement case_list case_item instrucciones_case instruccion_case default_case instruccion_simple while_statement for_statement repeat_statement asignacion_elemento filas_lista fila_matriz lista_bloques2D bloque2D funcion_declaracion return_stmt llamada_funcion argumentos_opt join_variadic_args dims_expr_list atom unary postfix indices_una indices_multi main_declaracion case_labels
%type <nodo> var_decl final_var_decl for_each_statement incremento array_decl_local
/* Eliminados head_nonfinal/head_final y dims_*; nueva estrategia centrada en prefix */
%type <boolean> brackets_seq
%type <paramList> lista_parametros param_opt
%type <boolean> param_array_brackets

%type <tipoDato> tipoPrimitivo
/* removidos dims_new_list y bracket_list_plus definitvamente */

// Precedencias (menor a mayor): OR < AND < igualdad < relacionales < aditivas < bitwise < shifts < multiplicativas < NEG < CAST < acceso '.' < NOT
// Ajuste: AND/OR ahora tienen menor precedencia que comparaciones para que expr: a >= 0 && a < b se agrupe como (a>=0) && (a<b)
%left TOKEN_OR
%left TOKEN_AND
%left TOKEN_EQUAL TOKEN_NOT_EQUAL
%left TOKEN_GREATER TOKEN_LESS TOKEN_GREATER_EQUAL TOKEN_LESS_EQUAL
%left '+' '-'
%left '&' '^' '|'
%left TOKEN_SHIFT_LEFT TOKEN_SHIFT_RIGHT
%left '*' '/' '%'
%left NEG
%left CAST
%left '.'
%right TOKEN_NOT

%%

%start s;

s: lSentencia  { ast_root = $1; $$ = $1; }
    //| error '\n'  { yyerrok; }
    ;
//                                               Padre, hijo;
lSentencia: lSentencia instruccion { agregarHijo($1, $2); $$ = $1;}
    | lSentencia comentario { $$ = $1; }
    | instruccion {
                        AbstractExpresion* b = nuevoInstruccionesExpresion();
                        agregarHijo(b, $1);
                        $$ =  b;
                    }
    /* Sincronizar si hay error antes de cerrar bloque: conserva lo ya acumulado */
    | lSentencia error '}' { yyerrok; $$ = $1; }
    | error '}' { yyerrok; $$ = nuevoInstruccionesExpresion(); }
    ;

comentario: TOKEN_COMMENT_LINE { comments[comment_count++] = $1; }
    | TOKEN_COMMENT_MULTI { comments[comment_count++] = $1; }
    ;

instruccion: if_statement {$$ = $1;}
    | switch_statement {$$ = $1;}
    | break_statement {$$ = $1;}
    | while_statement {$$ = $1;}
    | for_statement {$$ = $1;}
    | for_each_statement {$$ = $1;}
    | repeat_statement {$$ = $1;}
    | imprimir ';' {$$ = $1; }
    | bloque {$$ = $1;}
    | declaracion_var ';' {$$ = $1;}
    | funcion_declaracion {$$ = $1;}
    | main_declaracion {$$ = $1;}
    | return_stmt ';' {$$ = $1;}
    | asignacion ';' {$$ = $1;}
    | asignacion_elemento ';' {$$ = $1;}
    | postfix ';' { $$ = $1; }
    | continue_statement {$$ = $1;}
    /* Recuperación de errores: reportar y seguir sincronizando en ';' o '}' */
    | error ';' { $$ = parser_error_node(@1, "Se esperaba ';'"); yyerrok; }
    | error '}' { $$ = parser_error_node(@1, "Se esperaba '}'"); yyerrok; }
    ;

if_statement: TOKEN_IF '(' expr ')' bloque { $$ = nuevoIfExpresion($3, $5, NULL); }
    | TOKEN_IF '(' expr ')' bloque TOKEN_ELSE bloque { $$ = nuevoIfExpresion($3, $5, $7); }
    | TOKEN_IF '(' expr ')' bloque TOKEN_ELSE if_statement { $$ = nuevoIfExpresion($3, $5, $7); }
    | TOKEN_IF '(' expr ')' instruccion_simple ';' { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, $5);
        $$ = nuevoIfExpresion($3, nuevoBloqueExpresion(b), NULL); 
    }
    | TOKEN_IF '(' expr ')' instruccion_simple ';' TOKEN_ELSE bloque { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, $5);
        $$ = nuevoIfExpresion($3, nuevoBloqueExpresion(b), $8); 
    }
    | TOKEN_IF '(' expr ')' instruccion_simple ';' TOKEN_ELSE if_statement { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, $5);
        $$ = nuevoIfExpresion($3, nuevoBloqueExpresion(b), $8); 
    }
    ;

switch_statement: TOKEN_SWITCH '(' expr ')' '{' case_list '}' { $$ = nuevoSwitchExpresion($3, $6, NULL); }
    | TOKEN_SWITCH '(' expr ')' '{' case_list default_case '}' { $$ = nuevoSwitchExpresion($3, $6, $7); }
    ;

while_statement: TOKEN_WHILE '(' expr ')' bloque { $$ = nuevoWhileExpresion($3, $5); }
    | TOKEN_WHILE '(' expr ')' instruccion_simple { 
        AbstractExpresion* b = nuevoListaExpresiones();
        agregarHijo(b, $5);
        $$ = nuevoWhileExpresion($3, nuevoBloqueExpresion(b)); 
    }
    ;

for_statement:
    TOKEN_FOR '(' declaracion_var ';' expr ';' incremento ')' bloque_for { $$=nuevoForExpresion($3,$5,$7,$9); }
| TOKEN_FOR '(' declaracion_var ';' expr ';' incremento ')' instruccion_simple { AbstractExpresion* b=nuevoListaExpresiones(); agregarHijo(b,$9); $$=nuevoForExpresion($3,$5,$7,nuevoBloqueExpresionConContextoPadre(b)); }
| TOKEN_FOR '(' declaracion_var ';' expr ';' ')' bloque_for { $$=nuevoForExpresion($3,$5,NULL,$8); }
| TOKEN_FOR '(' declaracion_var ';' expr ';' ')' instruccion_simple { AbstractExpresion* b=nuevoListaExpresiones(); agregarHijo(b,$8); $$=nuevoForExpresion($3,$5,NULL,nuevoBloqueExpresionConContextoPadre(b)); }
| TOKEN_FOR '(' asignacion ';' expr ';' incremento ')' bloque { $$=nuevoForExpresion($3,$5,$7,$9); }
| TOKEN_FOR '(' asignacion ';' expr ';' incremento ')' instruccion_simple { AbstractExpresion* b=nuevoListaExpresiones(); agregarHijo(b,$9); $$=nuevoForExpresion($3,$5,$7,nuevoBloqueExpresion(b)); }
;

repeat_statement:
    TOKEN_REPEAT expr bloque_for { $$=nuevoRepeatExpresion($2,$3); }
;

incremento:
        asignacion { $$ = $1; }
    | TOKEN_IDENTIFIER TOKEN_PLUS_PLUS { AbstractExpresion* id= nuevoIdentificadorExpresion($1); SET_POS(id,@1); AbstractExpresion* uno=nuevoPrimitivoExpresion(strdup("1"),INT); SET_POS(uno,@2); AbstractExpresion* sum=nuevoSumaExpresion(id,uno); AbstractExpresion* asg=nuevoAsignacionExpresion($1,sum); SET_POS(asg,@1); $$=asg;} 
    | TOKEN_IDENTIFIER TOKEN_MINUS_MINUS { AbstractExpresion* id= nuevoIdentificadorExpresion($1); SET_POS(id,@1); AbstractExpresion* uno=nuevoPrimitivoExpresion(strdup("1"),INT); SET_POS(uno,@2); AbstractExpresion* res=nuevoRestaExpresion(id,uno); AbstractExpresion* asg=nuevoAsignacionExpresion($1,res); SET_POS(asg,@1); $$=asg;} ;

/*
   Reescritura de switch/case para soportar etiquetas apiladas (fall-through de etiquetas
   hacia un único bloque de instrucciones), por ejemplo:
       case 1:
       case 2:
       case 3:
           instruccion; break;
   Generamos un CaseExpresion por cada etiqueta, todos compartiendo el mismo bloque y flag break.
*/
case_list: case_item { 
        /* case_item ya retorna una lista de CaseExpresion; la usamos directamente */
        $$ = $1;
    }
    | case_list case_item {
        /* aplanar: anexar todos los hijos de $2 a la lista existente */
        for(size_t i=0;i<$2->numHijos;i++){ agregarHijo($1, $2->hijos[i]); }
        $$ = $1;
    }
    ;

case_labels: TOKEN_CASE expr ':' {
        AbstractExpresion* etiquetas = nuevoListaExpresiones();
        agregarHijo(etiquetas, $2);
        $$ = etiquetas;
    }
    | case_labels TOKEN_CASE expr ':' {
        agregarHijo($1, $3);
        $$ = $1;
    }
    ;

case_item: case_labels instrucciones_case {
        /* Construir lista de CaseExpresion: uno por cada etiqueta */
        AbstractExpresion* lista = nuevoListaExpresiones();
        for(size_t i=0;i<$1->numHijos;i++){
            AbstractExpresion* etiqueta = $1->hijos[i];
            AbstractExpresion* c = nuevoCaseExpresion(etiqueta, $2, 0);
            agregarHijo(lista, c);
        }
    /* Asignar propiedad única del bloque de instrucciones al primer CaseExpresion */
    if(lista->numHijos>0){ agregarHijo(lista->hijos[0], $2); }
        $$ = lista;
    }
    | case_labels instrucciones_case TOKEN_BREAK ';' {
        AbstractExpresion* lista = nuevoListaExpresiones();
        for(size_t i=0;i<$1->numHijos;i++){
            AbstractExpresion* etiqueta = $1->hijos[i];
            AbstractExpresion* c = nuevoCaseExpresion(etiqueta, $2, 1);
            agregarHijo(lista, c);
        }
    if(lista->numHijos>0){ agregarHijo(lista->hijos[0], $2); }
        $$ = lista;
    }
    ;

instrucciones_case: instruccion_case {
        AbstractExpresion* lista = nuevoListaExpresiones();
        agregarHijo(lista, $1);
        $$ = lista;
    }
    | instrucciones_case instruccion_case {
        agregarHijo($1, $2);
        $$ = $1;
    }
    ;

instruccion_case: imprimir ';' {$$ = $1; }
    | bloque {$$ = $1;}
    | declaracion_var ';' {$$ = $1;}
    | asignacion ';' {$$ = $1;}
    ;

default_case: TOKEN_DEFAULT ':' instrucciones_case { $$ = $3; }
    | TOKEN_DEFAULT ':' instrucciones_case TOKEN_BREAK ';' { $$ = $3; }
    ;

break_statement: TOKEN_BREAK ';' { $$ = nuevoBreakExpresion(); SET_POS($$, @1); }
    ;

continue_statement: TOKEN_CONTINUE ';' { $$ = nuevoContinueExpresion(); SET_POS($$, @1); }
    ;

instruccion_simple: imprimir {$$ = $1; }
    | declaracion_var {$$ = $1;}
    | asignacion {$$ = $1;}
    ;

asignacion: TOKEN_IDENTIFIER '=' expr { $$ = nuevoAsignacionExpresion($1, $3); SET_POS($$, @1); }
    | TOKEN_IDENTIFIER TOKEN_PLUS_ASSIGN expr { $$ = nuevoAsignacionSumaExpresion($1, $3); }
    | TOKEN_IDENTIFIER TOKEN_MINUS_ASSIGN expr { $$ = nuevoAsignacionRestaExpresion($1, $3); }
    | TOKEN_IDENTIFIER TOKEN_MUL_ASSIGN expr { $$ = nuevoAsignacionMultiplicacionExpresion($1, $3); }
    | TOKEN_IDENTIFIER TOKEN_DIV_ASSIGN expr { $$ = nuevoAsignacionDivisionExpresion($1, $3); }
    | TOKEN_IDENTIFIER TOKEN_MOD_ASSIGN expr { $$ = nuevoAsignacionModuloExpresion($1, $3); }
    | TOKEN_IDENTIFIER TOKEN_AND_ASSIGN expr { AbstractExpresion* id=nuevoIdentificadorExpresion($1); SET_POS(id,@1); AbstractExpresion* op=nuevoBitAndExpresion(id,$3); AbstractExpresion* asg=nuevoAsignacionExpresion($1,op); SET_POS(asg,@1); $$=asg;} 
    | TOKEN_IDENTIFIER TOKEN_OR_ASSIGN expr { AbstractExpresion* id=nuevoIdentificadorExpresion($1); SET_POS(id,@1); AbstractExpresion* op=nuevoBitOrExpresion(id,$3); AbstractExpresion* asg=nuevoAsignacionExpresion($1,op); SET_POS(asg,@1); $$=asg;} 
    | TOKEN_IDENTIFIER TOKEN_XOR_ASSIGN expr { AbstractExpresion* id=nuevoIdentificadorExpresion($1); SET_POS(id,@1); AbstractExpresion* op=nuevoBitXorExpresion(id,$3); AbstractExpresion* asg=nuevoAsignacionExpresion($1,op); SET_POS(asg,@1); $$=asg;} 
    | TOKEN_IDENTIFIER TOKEN_SHL_ASSIGN expr { AbstractExpresion* id=nuevoIdentificadorExpresion($1); SET_POS(id,@1); AbstractExpresion* op=nuevoShiftLeftExpresion(id,$3); AbstractExpresion* asg=nuevoAsignacionExpresion($1,op); SET_POS(asg,@1); $$=asg;} 
    | TOKEN_IDENTIFIER TOKEN_SHR_ASSIGN expr { AbstractExpresion* id=nuevoIdentificadorExpresion($1); SET_POS(id,@1); AbstractExpresion* op=nuevoShiftRightExpresion(id,$3); AbstractExpresion* asg=nuevoAsignacionExpresion($1,op); SET_POS(asg,@1); $$=asg;} 

lista_Expr: lista_Expr ','  expr { agregarHijo($1, $3); $$ = $1; }
    | expr { 
                AbstractExpresion* b = nuevoListaExpresiones();
                agregarHijo(b, $1);
                $$ =  b;
            }
    ;

imprimir: TOKEN_PRINT '(' lista_Expr ')' { $$ =  nuevoPrintExpresion($3, 0); }
    | TOKEN_SYSTEM_OUT_PRINTLN '(' lista_Expr ')' { $$ =  nuevoPrintExpresion($3, 1); }
    | TOKEN_SYSTEM_OUT_PRINTLN '(' ')' { $$ = nuevoPrintExpresion(nuevoListaExpresiones(), 1); }
    | TOKEN_SYSTEM_OUT_PRINT '(' lista_Expr ')' { $$ =  nuevoPrintExpresion($3, 0); }
    | TOKEN_SYSTEM_OUT_PRINT '(' ')' { $$ = nuevoPrintExpresion(nuevoListaExpresiones(), 0); }
    ;

bloque: '{' lSentencia '}' { $$ = nuevoBloqueExpresion($2); }
    | '{' error '}' { $$ = nuevoBloqueExpresion(nuevoListaExpresiones()); yyerrok; }

bloque_for: '{' lSentencia '}' { $$ = nuevoBloqueExpresionConContextoPadre($2); }

/* =================== DECLARACIONES (simplificadas) =================== */

declaracion_var:
    array_decl_local
    | var_decl
    | final_var_decl
    ;

/* Nueva regla: declaración de arrays sin variables globales (para uso dentro de funciones) */
/* Versiones específicas para 1D, 2D, 3D, 4D, 5D para evitar ambigüedad */
/* Nueva implementación directa: crea el nodo final sin casteos inseguros */
array_decl_local:
    /* NEW: tipo[]... id = new tipo[dim][dim]... */
    tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' TOKEN_NEW tipoPrimitivo dims_expr_list {
        int declaredDims = $2; int newDims = (int)$7->numHijos;
        if(declaredDims != newDims){ $$ = parser_error_node(@3, "Número de brackets (%d) no coincide con dimensiones new (%d)", declaredDims, newDims); }
        else if($1 != $6){ $$ = parser_error_node(@1, "Tipo en new (%d) difiere del declarado (%d)", $6, $1); }
        else {
            AbstractExpresion* nodo=NULL; 
            if(newDims==1){ nodo = nuevoArrayDeclaracion($1, $3, $7->hijos[0]); }
            else if(newDims==2){ nodo = nuevoMatrixDeclaracion($1, $3, $7->hijos[0], $7->hijos[1]); }
            else {
                AbstractExpresion** dims = malloc(sizeof(AbstractExpresion*)*newDims);
                for(int i=0;i<newDims;i++) dims[i] = $7->hijos[i];
                nodo = nuevoMultiArrayDeclaracion($1, $3, newDims, dims);
            }
            /* Propagar posición del identificador */
            nodo->linea = @3.first_line; nodo->columna = @3.first_column; $$ = nodo;
        }
    }
    /* Literales 1D: tipo[] id = { a, b, c } */
  | tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' '{' lista_Expr '}' {
        if($2 != 1){ $$ = parser_error_node(@3, "Literal 1D usado pero se declararon %d dimensiones", $2); }
    else { AbstractExpresion* nodo = nuevoArrayLiteralDeclaracion($1, $3, $6); nodo->linea=@3.first_line; nodo->columna=@3.first_column; $$=nodo; }
    }
    /* Literales 2D: tipo[][] id = { { .. }, { .. } }  reutilizando bloque2D == '{' filas_lista '}' */
  | tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' bloque2D {
        if($2 != 2){ $$ = parser_error_node(@3, "Literal 2D usado pero se declararon %d dimensiones", $2); }
    else { AbstractExpresion* nodo = nuevoMatrixLiteralDeclaracion($1, $3, $5); nodo->linea=@3.first_line; nodo->columna=@3.first_column; $$=nodo; }
    }
    /* Literales 3D: tipo[][][] id = { bloque2D, bloque2D, ... } */
  | tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' '{' lista_bloques2D '}' {
        if($2 != 3){ $$ = parser_error_node(@3, "Literal 3D usado pero se declararon %d dimensiones", $2); }
    else { AbstractExpresion* nodo = nuevoArray3DLiteralDeclaracion($1, $3, $6); nodo->linea=@3.first_line; nodo->columna=@3.first_column; $$=nodo; }
    }
    /* Desde expresión existente que produce ARRAY */
  | tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '=' expr {
    AbstractExpresion* nodo = nuevoArrayDeclaracionDesdeExpr($1, $3, $5); nodo->linea=@3.first_line; nodo->columna=@3.first_column; $$ = nodo; }
  ;

/* Secuencia de brackets vacíos antes del identificador (int[][] a ...) */
brackets_seq: '[' ']' { $$ = 1; }
    | brackets_seq '[' ']' { $$ = $1 + 1; };

var_decl:
        tipoPrimitivo TOKEN_IDENTIFIER '=' expr { $$ = nuevoDeclaracionVariables($1,$2,$4,0); ((DeclaracionVariable*)$$)->linea = @2.first_line; ((DeclaracionVariable*)$$)->columna = @2.first_column; }
    | tipoPrimitivo TOKEN_IDENTIFIER { $$ = nuevoDeclaracionVariables($1,$2,NULL,0); ((DeclaracionVariable*)$$)->linea = @2.first_line; ((DeclaracionVariable*)$$)->columna = @2.first_column; };

final_var_decl:
    TOKEN_FINAL tipoPrimitivo TOKEN_IDENTIFIER '=' expr { $$ = nuevoDeclaracionVariables($2,$3,$5,1); ((DeclaracionVariable*)$$)->linea = @3.first_line; ((DeclaracionVariable*)$$)->columna = @3.first_column; };

/* Eliminadas array_prefix_init_opt / array_postfix_init_opt */

/* Reglas antiguas de declaraciones de arrays eliminadas */

/* Lista de dimensiones en NEW */
dims_expr_list: '[' expr ']' { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l,$2); $$ = l; }
        | dims_expr_list '[' expr ']' { agregarHijo($1,$3); $$ = $1; };

/* (Sintaxis prefija eliminada para reducir ambigüedad) */

/* Secuencias de brackets para contar dimensiones (>=1) */

/* multi_array_declaracion original eliminada */

lista_bloques2D: bloque2D { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l, $1); $$ = l; }
    | lista_bloques2D ',' bloque2D { agregarHijo($1, $3); $$ = $1; };

bloque2D: '{' filas_lista '}' { $$ = $2; };

filas_lista: fila_matriz { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l, $1); $$ = l; }
    | filas_lista ',' fila_matriz { agregarHijo($1, $3); $$ = $1; };

fila_matriz: '{' lista_Expr '}' { $$ = $2; };

asignacion_elemento: TOKEN_IDENTIFIER indices_una '=' expr {
    AbstractExpresion* idx = $2->hijos[0]; $$ = nuevoArrayAsignacionElemento($1, idx, $4); }
    | TOKEN_IDENTIFIER indices_multi '=' expr {
        size_t n=$2->numHijos; if (n==2) $$=nuevoMatrixAsignacionElemento($1, $2->hijos[0], $2->hijos[1], $4); else $$=nuevoMultiArrayAsignacionElemento($1,$2,$4); }
    /* Compound direct (nativo) 1D */
    | TOKEN_IDENTIFIER indices_una TOKEN_PLUS_ASSIGN expr { $$ = nuevoArrayAsignacionElementoCompound($1, $2->hijos[0], $4, COP_ADD); }
    | TOKEN_IDENTIFIER indices_una TOKEN_MINUS_ASSIGN expr { $$ = nuevoArrayAsignacionElementoCompound($1, $2->hijos[0], $4, COP_SUB); }
    | TOKEN_IDENTIFIER indices_una TOKEN_MUL_ASSIGN expr { $$ = nuevoArrayAsignacionElementoCompound($1, $2->hijos[0], $4, COP_MUL); }
    | TOKEN_IDENTIFIER indices_una TOKEN_DIV_ASSIGN expr { $$ = nuevoArrayAsignacionElementoCompound($1, $2->hijos[0], $4, COP_DIV); }
    | TOKEN_IDENTIFIER indices_una TOKEN_MOD_ASSIGN expr { $$ = nuevoArrayAsignacionElementoCompound($1, $2->hijos[0], $4, COP_MOD); }
    /* Compound multi-d */
    | TOKEN_IDENTIFIER indices_multi TOKEN_PLUS_ASSIGN expr { size_t n=$2->numHijos; if(n==2) $$=nuevoMatrixAsignacionElementoCompound($1,$2->hijos[0],$2->hijos[1],$4,COP_ADD); else $$=nuevoMultiArrayAsignacionElementoCompound($1,$2,$4,COP_ADD); }
    | TOKEN_IDENTIFIER indices_multi TOKEN_MINUS_ASSIGN expr { size_t n=$2->numHijos; if(n==2) $$=nuevoMatrixAsignacionElementoCompound($1,$2->hijos[0],$2->hijos[1],$4,COP_SUB); else $$=nuevoMultiArrayAsignacionElementoCompound($1,$2,$4,COP_SUB); }
    | TOKEN_IDENTIFIER indices_multi TOKEN_MUL_ASSIGN expr { size_t n=$2->numHijos; if(n==2) $$=nuevoMatrixAsignacionElementoCompound($1,$2->hijos[0],$2->hijos[1],$4,COP_MUL); else $$=nuevoMultiArrayAsignacionElementoCompound($1,$2,$4,COP_MUL); }
    | TOKEN_IDENTIFIER indices_multi TOKEN_DIV_ASSIGN expr { size_t n=$2->numHijos; if(n==2) $$=nuevoMatrixAsignacionElementoCompound($1,$2->hijos[0],$2->hijos[1],$4,COP_DIV); else $$=nuevoMultiArrayAsignacionElementoCompound($1,$2,$4,COP_DIV); }
    | TOKEN_IDENTIFIER indices_multi TOKEN_MOD_ASSIGN expr { size_t n=$2->numHijos; if(n==2) $$=nuevoMatrixAsignacionElementoCompound($1,$2->hijos[0],$2->hijos[1],$4,COP_MOD); else $$=nuevoMultiArrayAsignacionElementoCompound($1,$2,$4,COP_MOD); }
    ;

/* Para diferenciar a[i] (simple) de a[i][j]... usamos indices_multi (>=2) */
indices_una: '[' expr ']' { AbstractExpresion* l = nuevoListaExpresiones(); agregarHijo(l,$2); $$=l; };
indices_multi: indices_una indices_una { /* concat */ for(size_t i=0;i<$2->numHijos;i++) agregarHijo($1,$2->hijos[i]); $$=$1; }
    | indices_multi indices_una { for(size_t i=0;i<$2->numHijos;i++) agregarHijo($1,$2->hijos[i]); $$=$1; };


/* 
TODO: para mejorar la legibilidad en lugar de guardar la operacion por incumplir
el principio de responsabilidad única y también el Principio de abierto/cerrado (SOLID)
la accion semantica fungirá como factoría abstracta y cada expresión tendra su método interpret
para hacer la operación además de utilizar otros métodos "heredados".

expr: expr '+' expr   { $$ =  nuevoExpresionLenguaje('+', $1, $3);  }
    | expr '-' expr { $$ =  nuevoExpresionLenguaje('-', $1, $3); }
    | '(' expr ')' { $$ = $2; }
    | '-' expr %prec NEG  { $$ =  nuevoExpresionLenguaje('U', $2, NULL);  }
    | primitivo { $$ = $1; }
    ; 
*/

expr: expr '+' expr   { $$ =  nuevoSumaExpresion($1, $3);  }
    | expr '-' expr { $$ =  nuevoRestaExpresion($1, $3); }
    | expr '*' expr { $$ =  nuevoMultiplicacionExpresion($1, $3); }
    | expr '/' expr { $$ =  nuevoDivisionExpresion($1, $3); }
    | expr '%' expr { $$ =  nuevoModuloExpresion($1, $3); }
    | expr '&' expr { $$ =  nuevoBitAndExpresion($1, $3); }
    | expr '|' expr { $$ =  nuevoBitOrExpresion($1, $3); }
    | expr '^' expr { $$ =  nuevoBitXorExpresion($1, $3); }
    | expr TOKEN_SHIFT_LEFT expr { $$ =  nuevoShiftLeftExpresion($1, $3); }
    | expr TOKEN_SHIFT_RIGHT expr { $$ =  nuevoShiftRightExpresion($1, $3); }
    | expr TOKEN_EQUAL expr { $$ =  nuevoIgualdadExpresion($1, $3); }
    | expr TOKEN_NOT_EQUAL expr { $$ =  nuevoDesigualdadExpresion($1, $3); }
    | expr TOKEN_GREATER expr { $$ =  nuevoMayorQueExpresion($1, $3); }
    | expr TOKEN_LESS expr { $$ =  nuevoMenorQueExpresion($1, $3); }
    | expr TOKEN_GREATER_EQUAL expr { $$ =  nuevoMayorIgualQueExpresion($1, $3); }
    | expr TOKEN_LESS_EQUAL expr { $$ =  nuevoMenorIgualQueExpresion($1, $3); }
    | expr TOKEN_AND expr { $$ =  nuevoAndExpresion($1, $3); }
    | expr TOKEN_OR expr { $$ =  nuevoOrExpresion($1, $3); }
    | TOKEN_NOT expr { $$ =  nuevoNotExpresion($2); }
    | '-' expr %prec NEG  { $$ =  nuevoUnarioExpresion($2);  }
    | postfix { $$ = $1; }
    ;

postfix: unary { $$ = $1; }
    | postfix '[' expr ']' { $$ = nuevoArrayAcceso($1, $3); }
    | postfix '.' TOKEN_LENGTH { $$ = nuevoArrayLength($1); }
    | postfix '.' TOKEN_ADD '(' expr ')' { $$ = nuevoArrayAdd($1, $5); }
    | postfix '.' TOKEN_IDENTIFIER '(' expr ')' { if(strcmp($3,"equals")==0){ $$ = nuevoIgualdadExpresion($1,$5);} else { $$=$1; } }
    | postfix '.' TOKEN_IDENTIFIER '(' ')' { if(strcmp($3,"equals")==0){ AbstractExpresion* e=parser_error_node(@3,"método equals requiere un argumento"); $$=$1; (void)e; } else { $$=$1; } }
    | TOKEN_IDENTIFIER TOKEN_PLUS_PLUS {
        AbstractExpresion* id1 = nuevoIdentificadorExpresion($1);
        AbstractExpresion* uno1 = nuevoPrimitivoExpresion(strdup("1"), INT);
        AbstractExpresion* sum1 = nuevoSumaExpresion(id1, uno1);
        $$ = nuevoAsignacionExpresion($1, sum1);
    }
    | TOKEN_IDENTIFIER TOKEN_MINUS_MINUS {
        AbstractExpresion* id2 = nuevoIdentificadorExpresion($1);
        AbstractExpresion* uno2 = nuevoPrimitivoExpresion(strdup("1"), INT);
        AbstractExpresion* res2 = nuevoRestaExpresion(id2, uno2);
        $$ = nuevoAsignacionExpresion($1, res2);
    }
    ;

unary: atom { $$ = $1; }
     /* Hacer que el cast tome como operando una expresión postfix completa,
         para que (double)a[i] se interprete como cast del elemento indexado
         y no como cast del arreglo seguido de indexación sobre double. */
     | '(' tipoPrimitivo ')' postfix %prec CAST { $$ = nuevoCastExpresion($2, $4); }
    ;

atom: primitivo { $$ = $1; }
    | '(' expr ')' { $$ = $2; }
    | TOKEN_IDENTIFIER { $$ = nuevoIdentificadorExpresion($1); SET_POS($$, @1); }
    | llamada_funcion { $$ = $1; /* la llamada ya debería heredar pos de su identificador interno */ }
    | TOKEN_ARRAYS '.' TOKEN_INDEXOF '(' expr ',' expr ')' { $$ = nuevoArraysIndexOf($5, $7); }
    | TOKEN_INTEGER_CLASS '.' TOKEN_PARSE_INT '(' expr ')' { $$ = nuevoParseEntero($5); }
    | TOKEN_DOUBLE_CLASS '.' TOKEN_PARSE_DOUBLE '(' expr ')' { $$ = nuevoParseDouble($5); }
    | TOKEN_FLOAT_CLASS '.' TOKEN_PARSE_FLOAT '(' expr ')' { $$ = nuevoParseFloat($5); }
    | TOKEN_DSTRING '.' TOKEN_VALUE_OF '(' expr ')' { $$ = nuevoStringValueOf($5); }
    | TOKEN_DSTRING '.' TOKEN_JOIN '(' expr ',' expr ')' { $$ = nuevoStringJoin($5, $7, 1); }
    | TOKEN_DSTRING '.' TOKEN_JOIN '(' expr ',' join_variadic_args ')' { $$ = nuevoStringJoin($5, $7, 0); }
    ;

join_variadic_args: expr ',' lista_Expr {
        /* crear lista que contenga primer expr y luego los de lista_Expr */
        AbstractExpresion* l = nuevoListaExpresiones();
        agregarHijo(l, $1);
        for(size_t i=0;i<$3->numHijos;i++){ agregarHijo(l, $3->hijos[i]); }
        $$ = l;
    };

primitivo: TOKEN_UNSIGNED_INTEGER { $$ = nuevoPrimitivoExpresion($1, INT); SET_POS($$, @1); }
    | TOKEN_STRING { $$ =  nuevoPrimitivoExpresion($1, STRING); SET_POS($$, @1); }
    | TOKEN_REAL_FLOAT { $$ =  nuevoPrimitivoExpresion($1, FLOAT); SET_POS($$, @1); }
    | TOKEN_REAL { $$ =  nuevoPrimitivoExpresion($1, DOUBLE); SET_POS($$, @1); }
    | TOKEN_CHAR_LITERAL { $$ =  nuevoPrimitivoExpresion($1, CHAR); SET_POS($$, @1); }
    | TOKEN_TRUE { $$ =  nuevoPrimitivoExpresion($1, BOOLEAN); SET_POS($$, @1); }
    | TOKEN_FALSE { $$ =  nuevoPrimitivoExpresion($1, BOOLEAN); SET_POS($$, @1); }
    | TOKEN_NULL { $$ = nuevoPrimitivoExpresion(NULL, NULO); SET_POS($$, @1); }
    ;

tipoPrimitivo: TOKEN_DINT { $$ = INT; }
    | TOKEN_DFLOAT { $$ = FLOAT; }
    | TOKEN_DDOUBLE { $$ = DOUBLE; }
    | TOKEN_DSTRING { $$ = STRING; }
    | TOKEN_DBOOLEAN { $$ = BOOLEAN; }
    | TOKEN_DCHAR { $$ = CHAR; }
    | TOKEN_DVOID { $$ = VOID; }
    ;

/* Permitir funciones que retornan tipos primitivos o arreglos */
funcion_declaracion:
            tipoPrimitivo TOKEN_IDENTIFIER '(' param_opt ')' bloque { 
        if($4){ $$ = nuevoFuncionDeclaracion($1, $2, $4->names, $4->types, $4->count, $6, 0); }
        else { $$ = nuevoFuncionDeclaracion($1, $2, NULL, NULL, 0, $6, 0); }
        ((FuncionDecl*)$$)->linea = @2.first_line; ((FuncionDecl*)$$)->columna = @2.first_column;
            }
        | tipoPrimitivo brackets_seq TOKEN_IDENTIFIER '(' param_opt ')' bloque {
                /* Retorno array: int[][] nombre(...) */
                if($2 < 1){ $$ = parser_error_node(@3, "Número de brackets de retorno inválido"); }
                else {
                        if($5){ $$ = nuevoFuncionDeclaracion(ARRAY, $3, $5->names, $5->types, $5->count, $7, $2); }
                        else { $$ = nuevoFuncionDeclaracion(ARRAY, $3, NULL, NULL, 0, $7, $2); }
                        ((FuncionDecl*)$$)->linea = @3.first_line; ((FuncionDecl*)$$)->columna = @3.first_column;
                }
            }
        ;

/* public static void main(String[] args){ ... } soporte mínimo: ignoramos params */
main_declaracion: TOKEN_PUBLIC TOKEN_STATIC TOKEN_DVOID TOKEN_IDENTIFIER '(' main_params_opt ')' bloque { $$ = $8; };
main_params_opt: /* empty */ | main_params;
main_params: main_param | main_params ',' main_param;
main_param: tipoPrimitivo main_param_array_brackets TOKEN_IDENTIFIER;
main_param_array_brackets: /* empty */ { /* 0 dims */ } | main_param_array_brackets '[' ']' { /* accum dims ignored */ };

param_opt: /* empty */ { $$ = NULL; }
    | lista_parametros { $$ = $1; };

/* Permitir parámetros arreglo: tipoPrimitivo '[]'... identificador -> tipo ARRAY */
param_array_brackets: /* empty */ { $$ = 0; }
    | param_array_brackets '[' ']' { $$ = $1 + 1; };

lista_parametros: tipoPrimitivo param_array_brackets TOKEN_IDENTIFIER { 
        ParamList* pl = malloc(sizeof(ParamList));
        pl->count=1; pl->names=malloc(sizeof(char*)); pl->types=malloc(sizeof(TipoDato));
        pl->names[0]=$3; pl->types[0]= ($2>0 ? ARRAY : $1); $$=pl; }
    | lista_parametros ',' tipoPrimitivo param_array_brackets TOKEN_IDENTIFIER { 
        $1->names = realloc($1->names, sizeof(char*)*($1->count+1));
        $1->types = realloc($1->types, sizeof(TipoDato)*($1->count+1));
        $1->names[$1->count]=$5; $1->types[$1->count]= ($4>0 ? ARRAY : $3); $1->count++; $$=$1; };

return_stmt: TOKEN_RETURN { $$ = nuevoReturnExpresion(NULL); }
    | TOKEN_RETURN expr { $$ = nuevoReturnExpresion($2); }
    ;

/* for-each desazucarado */
for_each_statement:
    TOKEN_FOR '(' tipoPrimitivo TOKEN_IDENTIFIER ':' TOKEN_IDENTIFIER ')' bloque {
          /* Desazucar: soportar flatten para arrays >=2D usando pila de índices
              Estrategia: generar bucles anidados según profundidad dinámica medida en runtime: iteramos cada nivel si el elemento actual aún es ARRAY.
              Simplificación: generamos un for principal sobre el arreglo original; si el elemento es ARRAY, usamos Array.length recursivo que ya suma todos los internos y hacemos un acceso lineal simulando flatten: i recorre 0..lengthTotal-1 y para each recuperamos elemento linealizado.
              Implementación minimal: length recursivo ya devuelve total; acceso lineal: creamos builtin que recorre y avanza un contador global oculto. Aquí haremos workaround: reemplazar for-each multi-dimension por for simple sobre length total y acceso mediante función auxiliar equals sobre índice lineal -> no disponible; alternativa: iterar superficialmente y si elemento es ARRAY, insertar otro for-each recursivo construido aquí. */
          /* Construcción básica 1D y fallback recursivo: si el cuerpo usa variable, queremos consistente para multidim -> generamos verificación y si elemento es ARRAY, no declaramos var primitiva (se imprimirá error si se intenta usar). */
          char bufIdx[64]; snprintf(bufIdx,sizeof(bufIdx),"__idx_fe_%s", $4); char* idxName=strdup(bufIdx);
          AbstractExpresion* cero = nuevoPrimitivoExpresion(strdup("0"), INT);
          AbstractExpresion* declIdx = nuevoDeclaracionVariables(INT, idxName, cero, 0);
          /* Propagar ubicación al índice sintético (usamos la posición del identificador de la variable foreach) */
          ((DeclaracionVariable*)declIdx)->linea = @4.first_line; ((DeclaracionVariable*)declIdx)->columna = @4.first_column;
          AbstractExpresion* idIdx1 = nuevoIdentificadorExpresion(idxName);
          AbstractExpresion* arrId1 = nuevoIdentificadorExpresion($6);
          /* Usar longitud total (flatten) para iteración sobre arreglos potencialmente multidimensionales */
          AbstractExpresion* lenAcc = nuevoArrayTotalLength(arrId1);
          AbstractExpresion* cond = nuevoMenorQueExpresion(idIdx1, lenAcc);
          AbstractExpresion* idIdx2 = nuevoIdentificadorExpresion(idxName);
          AbstractExpresion* uno = nuevoPrimitivoExpresion(strdup("1"), INT);
          AbstractExpresion* sum = nuevoSumaExpresion(idIdx2, uno);
          AbstractExpresion* inc = nuevoAsignacionExpresion(idxName, sum);
    AbstractExpresion* arrId2 = nuevoIdentificadorExpresion($6);
    AbstractExpresion* idIdx3 = nuevoIdentificadorExpresion(idxName);
    /* Acceso linealizado: soporta multi-d devolviendo elemento hoja en orden */
    AbstractExpresion* acceso = nuevoArrayLinearAccess(arrId2, idIdx3);
          AbstractExpresion* declVar = nuevoDeclaracionVariables($3, $4, acceso, 0);
          ((DeclaracionVariable*)declVar)->linea = @4.first_line; ((DeclaracionVariable*)declVar)->columna = @4.first_column;
          AbstractExpresion* lista = nuevoListaExpresiones(); agregarHijo(lista, declVar); agregarHijo(lista, $8);
          AbstractExpresion* cuerpo = nuevoBloqueExpresion(lista);
          $$ = nuevoForExpresion(declIdx, cond, inc, cuerpo);
    }
    | TOKEN_FOR '(' tipoPrimitivo '[' ']' TOKEN_IDENTIFIER ':' TOKEN_IDENTIFIER ')' bloque {
        /* for-each de arrays: itera sobre primer nivel y declara variable de tipo arreglo */
        char bufIdx[64]; snprintf(bufIdx,sizeof(bufIdx),"__idx_fe_%s", $6); char* idxName=strdup(bufIdx);
        AbstractExpresion* cero = nuevoPrimitivoExpresion(strdup("0"), INT);
        AbstractExpresion* declIdx = nuevoDeclaracionVariables(INT, idxName, cero, 0);
        ((DeclaracionVariable*)declIdx)->linea = @6.first_line; ((DeclaracionVariable*)declIdx)->columna = @6.first_column;
        AbstractExpresion* idIdx1 = nuevoIdentificadorExpresion(idxName);
        AbstractExpresion* arrId1 = nuevoIdentificadorExpresion($8);
        AbstractExpresion* lenTop = nuevoArrayTopLength(arrId1);
        AbstractExpresion* cond = nuevoMenorQueExpresion(idIdx1, lenTop);
        AbstractExpresion* idIdx2 = nuevoIdentificadorExpresion(idxName);
        AbstractExpresion* uno = nuevoPrimitivoExpresion(strdup("1"), INT);
        AbstractExpresion* sum = nuevoSumaExpresion(idIdx2, uno);
        AbstractExpresion* inc = nuevoAsignacionExpresion(idxName, sum);
        AbstractExpresion* arrId2 = nuevoIdentificadorExpresion($8);
        AbstractExpresion* idIdx3 = nuevoIdentificadorExpresion(idxName);
        AbstractExpresion* acceso = nuevoArrayAcceso(arrId2, idIdx3);
        AbstractExpresion* declVar = nuevoDeclaracionVariables(ARRAY, $6, acceso, 0);
        ((DeclaracionVariable*)declVar)->linea = @6.first_line; ((DeclaracionVariable*)declVar)->columna = @6.first_column;
        AbstractExpresion* lista = nuevoListaExpresiones(); agregarHijo(lista, declVar); agregarHijo(lista, $10);
        AbstractExpresion* cuerpo = nuevoBloqueExpresion(lista);
        $$ = nuevoForExpresion(declIdx, cond, inc, cuerpo);
    };

argumentos_opt: /* empty */ { $$ = nuevoListaExpresiones(); }
    | lista_Expr { $$ = $1; };

llamada_funcion: TOKEN_IDENTIFIER '(' argumentos_opt ')' { $$ = nuevoLlamadaFuncion($1, $3); };
%%

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
