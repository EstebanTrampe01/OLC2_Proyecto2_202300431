// Exportador DOT con etiquetas enriquecidas segun el tipo real de nodo
#include "ast_to_dot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipos y funciones específicas para identificar nodos
#include "context/result.h"

// Terminales
#include "ast/nodos/expresiones/terminales/identificadores.h"
#include "ast/nodos/expresiones/terminales/primitivos.h"

// Expresiones y operaciones (para identificar operadores via tablaOperaciones)
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/expresiones/listaExpresiones.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "ast/nodos/expresiones/logicas/logicas.h"
#include "ast/nodos/expresiones/relacionales/relacionales.h"
#include "ast/nodos/expresiones/cast.h"

// Instrucciones y control de flujo
#include "ast/nodos/instrucciones/instrucciones.h"
#include "ast/nodos/instrucciones/bloque.h"
#include "ast/nodos/instrucciones/instruccion/print.h"
#include "ast/nodos/instrucciones/instruccion/declaracion.h"
#include "ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"
#include "ast/nodos/instrucciones/instruccion/if.h"
#include "ast/nodos/instrucciones/instruccion/while.h"
#include "ast/nodos/instrucciones/instruccion/for.h"
#include "ast/nodos/instrucciones/instruccion/switch.h"
#include "ast/nodos/instrucciones/instruccion/funcion.h"
// Arrays
#include "ast/nodos/instrucciones/instruccion/array.h"

static void fmt_escape_label(char* dst, size_t dstsz, const char* src){
    // Copia y escapa comillas dobles, limita longitud
    size_t j=0; if(!src){ snprintf(dst,dstsz,"(null)"); return; }
    for(size_t i=0; src[i] && j+1<dstsz; ++i){
        char c = src[i];
        if(c=='\"') c='\''; // reemplazar comillas por comilla simple para DOT
        if(c=='\n' || c=='\r' || c=='\t') c=' ';
        dst[j++] = c;
        if(j>200){ // truncar cadenas largas
            if(j+3<dstsz){ dst[j++]='.'; dst[j++]='.'; dst[j++]='.'; }
            break;
        }
    }
    dst[j]='\0';
}

static void build_label(AbstractExpresion* n, char* out, size_t outsz){
    if(!n || !n->interpret){ snprintf(out,outsz,"Nodo"); return; }

    // Identificador
    if(n->interpret == interpretIdentificadorExpresion){
        IdentificadorExpresion* id = (IdentificadorExpresion*)n;
        char name[256]; fmt_escape_label(name,sizeof(name), id->nombre);
        snprintf(out,outsz,"Identificador: %s", name); return;
    }
    // Literal/primitivo
    if(n->interpret == interpretPrimitivoExpresion){
        PrimitivoExpresion* p = (PrimitivoExpresion*)n;
        extern char* labelTipoDato[];
        char val[256]; fmt_escape_label(val,sizeof(val), p->valor);
    snprintf(out,outsz,"Literal %s: %s", (p->tipo>=0?labelTipoDato[p->tipo]:"?"), val); return;
    }
    // Cast
    if(n->interpret == interpretCastExpresion){
        CastExpresion* c=(CastExpresion*)n; extern char* labelTipoDato[];
    snprintf(out,outsz,"Conversión(%s)", (c->tipoDestino>=0?labelTipoDato[c->tipoDestino]:"?")); return;
    }
    // Asignación simple
    if(n->interpret == interpretAsignacionExpresion){
        AsignacionExpresion* a=(AsignacionExpresion*)n; char name[256]; fmt_escape_label(name,sizeof(name), a->nombre);
    snprintf(out,outsz,"Asignación: %s", name); return;
    }
    // Print
    if(n->interpret == interpretPrintExpresion){ snprintf(out,outsz,"Imprimir"); return; }
    // Bloque/Lista
    if(n->interpret == interpretBloqueExpresion){ snprintf(out,outsz,"Bloque"); return; }
    if(n->interpret == interpretInstrucciones){ snprintf(out,outsz,"ListaInstrucciones"); return; }
    if(n->interpret == interpretListaExpresiones){ snprintf(out,outsz,"ListaExpresiones"); return; }
    // Control de flujo
    if(n->interpret == interpretIfExpresion){ snprintf(out,outsz,"Si"); return; }
    if(n->interpret == interpretWhileExpresion){ snprintf(out,outsz,"Mientras"); return; }
    if(n->interpret == interpretForExpresion){ snprintf(out,outsz,"Para"); return; }
    if(n->interpret == interpretSwitchExpresion){ snprintf(out,outsz,"Segun"); return; }
    // Funciones
    if(n->interpret == interpretFuncionDeclaracion){
        FuncionDecl* f=(FuncionDecl*)n; extern char* labelTipoDato[]; char name[256]; fmt_escape_label(name,sizeof(name), f->nombre);
        const char* tret = (f->retorno>=0?labelTipoDato[f->retorno]:"?");
        if(f->linea>0 || f->columna>0)
            snprintf(out,outsz,"Función %s: %s (%d:%d)", name, tret, f->linea, f->columna);
        else
            snprintf(out,outsz,"Función %s: %s", name, tret);
        return;
    }
    if(n->interpret == interpretLlamadaFuncion){
        LlamadaFuncion* l=(LlamadaFuncion*)n; char name[256]; fmt_escape_label(name,sizeof(name), l->nombre);
        snprintf(out,outsz,"Llamada %s", name); return;
    }
    if(n->interpret == interpretReturnExpresion){ snprintf(out,outsz,"Retornar"); return; }

    // Arrays
    if(n->interpret == interpretArrayDecl){
        // No tenemos acceso directo a campos privados; solo etiqueta genérica
        snprintf(out,outsz,"DeclArreglo"); return;
    }
    if(n->interpret == interpretArrayLiteralDecl){ snprintf(out,outsz,"DeclArreglo{literal}"); return; }
    if(n->interpret == interpretArrayDeclFromExpr){ snprintf(out,outsz,"DeclArreglo(expr)"); return; }
    if(n->interpret == interpretArrayAcceso){ snprintf(out,outsz,"ArrayAcceso"); return; }
    if(n->interpret == interpretArrayAsignacionElem){ snprintf(out,outsz,"ArrayAsignaciónElem"); return; }
    if(n->interpret == interpretMultiArrayAsignacionElem){ snprintf(out,outsz,"MultiArrayAsignaciónElem"); return; }
    if(n->interpret == interpretArrayLinearAccess){ snprintf(out,outsz,"ArrayAcceso(lineal)"); return; }

    // Operadores binarios/unarios genéricos (ExpresionLenguaje)
    if(n->interpret == interpretExpresionLenguaje || n->interpret == interpretUnarioLenguaje){
        ExpresionLenguaje* e = (ExpresionLenguaje*)n;
        const char* op = NULL;
        if(e->tablaOperaciones == &tablaOperacionesSuma) op = "+";
        else if(e->tablaOperaciones == &tablaOperacionesResta) op = "-";
        else if(e->tablaOperaciones == &tablaOperacionesMultiplicacion) op = "*";
        else if(e->tablaOperaciones == &tablaOperacionesDivision) op = "/";
        else if(e->tablaOperaciones == &tablaOperacionesModulo) op = "%";
        else if(e->tablaOperaciones == &tablaOperacionesBitAnd) op = "&";
        else if(e->tablaOperaciones == &tablaOperacionesBitOr) op = "|";
        else if(e->tablaOperaciones == &tablaOperacionesBitXor) op = "^";
        else if(e->tablaOperaciones == &tablaOperacionesShiftLeft) op = "<<";
        else if(e->tablaOperaciones == &tablaOperacionesShiftRight) op = ">>";
        else if(e->tablaOperaciones == &tablaOperacionesAnd) op = "&&";
        else if(e->tablaOperaciones == &tablaOperacionesOr) op = "||";
        else if(e->tablaOperaciones == &tablaOperacionesNot) op = "!";
        else if(e->tablaOperaciones == &tablaOperacionesIgualdad) op = "==";
        else if(e->tablaOperaciones == &tablaOperacionesDesigualdad) op = "!=";
        else if(e->tablaOperaciones == &tablaOperacionesMayorQue) op = ">";
        else if(e->tablaOperaciones == &tablaOperacionesMenorQue) op = "<";
        else if(e->tablaOperaciones == &tablaOperacionesMayorIgualQue) op = ">=";
        else if(e->tablaOperaciones == &tablaOperacionesMenorIgualQue) op = "<=";
    if(op){ snprintf(out,outsz,"Operador %s", op); return; }
        // fallback por aridad
    switch(n->numHijos){ case 1: snprintf(out,outsz,"Operador(unario)"); break; case 2: snprintf(out,outsz,"Operador(binario)"); break; default: snprintf(out,outsz,"Operador"); }
        return;
    }

    // Declaración de variable (nombre y tipo)
    if(n->interpret == interpretDeclaracionVariable){
        DeclaracionVariable* d=(DeclaracionVariable*)n; extern char* labelTipoDato[]; char name[256]; fmt_escape_label(name,sizeof(name), d->nombre);
        const char* t = (d->tipo>=0?labelTipoDato[d->tipo]:"?");
        if(d->linea>0 || d->columna>0)
            snprintf(out,outsz,"Declaración %s: %s (%d:%d)%s", name, t, d->linea, d->columna, d->isFinal?" final":"");
        else
            snprintf(out,outsz,"Declaración %s: %s%s", name, t, d->isFinal?" final":"");
        return;
    }

    // Case de switch (no tiene header publico de struct, pero si la función)
    if(n->interpret == interpretCaseExpresion){ snprintf(out,outsz,"Caso"); return; }

    // Fallback por aridad
    switch(n->numHijos){
        case 0: snprintf(out,outsz,"Terminal"); break;
        case 1: snprintf(out,outsz,"Unario"); break;
        case 2: snprintf(out,outsz,"Binario"); break;
        default: snprintf(out,outsz,"N-ario"); break;
    }
}

static void emit_node(FILE* f, size_t id, const char* label){
    // Escapar label básico
    char buf[256];
    snprintf(buf, sizeof(buf), "%s", label?label:"Nodo");
    for(char* p=buf; *p; ++p){ if(*p=='\"') *p='\''; }
    fprintf(f, "  n%zu [label=\"%s\"];\n", id, buf);
}

static void walk_emit(AbstractExpresion* n, FILE* f, size_t* nextId, size_t parentId, int hasParent){
    if(!n) return;
    size_t myId = (*nextId)++;
    char lbl[256]; build_label(n, lbl, sizeof(lbl));
    emit_node(f, myId, lbl);
    if(hasParent){ fprintf(f, "  n%zu -> n%zu;\n", parentId, myId); }
    for(size_t i=0;i<n->numHijos;i++){
        walk_emit(n->hijos[i], f, nextId, myId, 1);
    }
}

int ast_export_to_dot(AbstractExpresion* root, const char* path){
    if(!root || !path) return -1;
    FILE* f = fopen(path, "w"); if(!f) return -1;
    fprintf(f, "digraph AST {\n");
    fprintf(f, "  node [shape=box, fontname=Helvetica];\n");
    fprintf(f, "  rankdir=TB;\n");
    size_t nextId=0; walk_emit(root, f, &nextId, 0, 0);
    fprintf(f, "}\n");
    fclose(f);
    return 0;
}
