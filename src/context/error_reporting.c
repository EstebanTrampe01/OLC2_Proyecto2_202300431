#include "error_reporting.h"
#include "result.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static const char* scope_name(Context* ctx){
    if(!ctx) return "AmbitoGlobal";
    // Recorremos hacia atrás hasta raíz para contar profundidad
    int depth=0; Context* c=ctx; while(c->anterior){ depth++; c=c->anterior; }
    if(depth==0) return "AmbitoGlobal";
    static char buf[32]; snprintf(buf,sizeof(buf),"Ambito%d", depth);
    return buf;
}

static void resolve_pos(AbstractExpresion* n, int* l, int* c, int depth){
    if(!n || depth>8) return; // evitar recursión profunda
    if(n->linea>0){ *l = n->linea; *c = n->columna; return; }
    for(size_t i=0;i<n->numHijos;i++){
        resolve_pos(n->hijos[i], l, c, depth+1);
        if(*l>0) return;
    }
}

/* Nuevo formato: ERR|mensaje|Ambito|linea|columna|Tipo */

static void emit_error(const char* tipo, const char* msg, const char* amb, int linea, int columna){
    char line[480];
    snprintf(line,sizeof(line),"ERR|%s|%s|%d|%d|%s", msg, amb, linea, columna, tipo?tipo:"?");
    fprintf(stderr, "%s\n", line);
    add_error_msg(line);
}

void report_categorized_error(const char* tipo, AbstractExpresion* nodo, Context* ctx, const char* fmt, ...){
    char msg[256]; va_list ap; va_start(ap, fmt); vsnprintf(msg,sizeof(msg),fmt,ap); va_end(ap);
    int linea = nodo? nodo->linea : 0; int columna = nodo? nodo->columna : 0;
    if(nodo && linea==0){ resolve_pos(nodo, &linea, &columna, 0); }
    const char* amb = scope_name(ctx);
    emit_error(tipo, msg, amb, linea, columna);
}

void report_semantic_error(AbstractExpresion* nodo, Context* ctx, const char* fmt, ...){
    char msg[256]; va_list ap; va_start(ap, fmt); vsnprintf(msg,sizeof(msg),fmt,ap); va_end(ap);
    int linea = nodo? nodo->linea : 0; int columna = nodo? nodo->columna : 0;
    if(nodo && linea==0){ resolve_pos(nodo, &linea, &columna, 0); }
    const char* amb = scope_name(ctx);
    emit_error("Semantico", msg, amb, linea, columna);
}

/* Compatibilidad: runtime error = semántico */
void report_runtime_error(AbstractExpresion* nodo, Context* ctx, const char* fmt, ...){
    char msg[256]; va_list ap; va_start(ap, fmt); vsnprintf(msg,sizeof(msg),fmt,ap); va_end(ap);
    int linea = nodo? nodo->linea : 0; int columna = nodo? nodo->columna : 0;
    if(nodo && linea==0){ resolve_pos(nodo, &linea, &columna, 0); }
    const char* amb = scope_name(ctx);
    emit_error("Semantico", msg, amb, linea, columna);
}

/* Para léxicos / sintácticos: dependemos de yylloc y AmbitoGlobal */
/* Declaración débil de YYLTYPE si aún no está visible (evita dependencia cíclica) */
#ifndef YYLTYPE
typedef struct YYLTYPE { int first_line; int first_column; int last_line; int last_column; } YYLTYPE;
#endif
extern YYLTYPE yylloc; /* declarado por Bison */

static void report_loc_simple(const char* tipo, const char* fmt, va_list ap){
    char msg[256]; vsnprintf(msg,sizeof(msg),fmt,ap);
    emit_error(tipo, msg, "AmbitoGlobal", yylloc.first_line, yylloc.first_column);
}

void report_lexical_error(const char* fmt, ...){ va_list ap; va_start(ap,fmt); report_loc_simple("Lexico", fmt, ap); va_end(ap);} 
void report_syntax_error(const char* fmt, ...){ va_list ap; va_start(ap,fmt); report_loc_simple("Sintactico", fmt, ap); va_end(ap);} 