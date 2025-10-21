#include "context.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Context* nuevoContext(Context* anterior) {
    Context* nuevo = malloc(sizeof(Context));
    nuevo->anterior = anterior;
    if (anterior) {
        nuevo->nombre = anterior->nombre + 1;
        nuevo->dentroLoop = anterior->dentroLoop;
    nuevo->dentroSwitch = anterior->dentroSwitch;
        // enlazar en lista de hijos del padre
        nuevo->nextSibling = anterior->firstChild;
        anterior->firstChild = nuevo;
    } else {
        nuevo->dentroLoop = 0;
    nuevo->dentroSwitch = 0;
        nuevo->nextSibling = NULL;
    }
    nuevo->ultimoSymbol = NULL;
    nuevo->firstChild = NULL;

    return nuevo;
}

Symbol* nuevoVariable(char* nombre, void* valor, TipoDato tipo, int isFinal) {
    Symbol* nuevo = malloc(sizeof(Symbol));
    if(nombre){ nuevo->nombre = strdup(nombre); } else nuevo->nombre=NULL;
    nuevo->valor = valor;
    nuevo->tipo = tipo;
    nuevo->clase = VARIABLE;
    nuevo->isFinal = isFinal;
    nuevo->linea = 0;
    nuevo->columna = 0;
    return nuevo;
}

void agregarSymbol(Context* actual, Symbol* symbol) {
    // Permitir sombreado: si ya existe en este mismo contexto, reemplazar
    Symbol* prev=NULL; Symbol* cur=actual->ultimoSymbol;
    while(cur){ if(strcmp(cur->nombre, symbol->nombre)==0){
            // Reemplazar cabeza (si prev==NULL) o enlazar prev->anterior
            if(prev==NULL){ symbol->anterior = cur->anterior; actual->ultimoSymbol = symbol; }
            else { symbol->anterior = cur->anterior; prev->anterior = symbol; }
            // No liberamos valor para evitar liberar memoria potencialmente compartida
            free(cur); return; }
        prev=cur; cur=cur->anterior; }
    symbol->anterior = actual->ultimoSymbol; actual->ultimoSymbol = symbol;
}

Symbol* buscarSymbol(Symbol* actual, char* nombre) {
    while (actual) {
        if (strcmp(actual->nombre, nombre) == 0) {
            return actual;
        }
        actual = actual->anterior;
    }
    return NULL;
}

Symbol* buscarTablaSimbolos(Context* actual, char* nombre) {
    while (actual) {
        Symbol* symbolEncontrado = buscarSymbol(actual->ultimoSymbol, nombre);
        if (symbolEncontrado) {
            return symbolEncontrado;
        }
        actual = actual->anterior;
    }
    return NULL;
}

static const char* clase_to_str(Clase c){
    switch(c){ case VARIABLE: return "Variable"; case FUNCION: return "Función"; case STRUCT: return "Struct"; default: return "?"; }
}

extern char* labelTipoDato[]; // ya declarado en result.c

void print_context_symbols(Context* ctx, const char* ambitoName){
    Symbol* s = ctx? ctx->ultimoSymbol : NULL;
    while(s){
        const char* tipoDato = (s->tipo>=0)? labelTipoDato[s->tipo] : "?";
    printf("SYM|%s|%s|%s|%s|%d|%d\n", s->nombre?s->nombre:"(anon)", clase_to_str(s->clase), tipoDato, ambitoName?ambitoName:"AmbitoGlobal", s->linea, s->columna);
        s = s->anterior;
    }
}

static void dfs_print(Context* ctx, int* id){
    if(!ctx) return;
    char ambname[32]; snprintf(ambname, sizeof(ambname), (ctx->anterior==NULL)?"AmbitoGlobal":"Ambito%d", (*id)++);
    print_context_symbols(ctx, ambname);
    for(Context* child=ctx->firstChild; child; child=child->nextSibling){
        dfs_print(child, id);
    }
}

void print_all_contexts_symbols(Context* root){
    int id=0; dfs_print(root, &id);
}