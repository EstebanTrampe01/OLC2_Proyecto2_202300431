#ifndef CONTEXT_H
#define CONTEXT_H

#include "result.h"

typedef enum {
    VARIABLE,
    FUNCION,
    STRUCT,
} Clase;

typedef struct Symbol Symbol;
typedef struct Context Context;

struct Symbol{
    char* nombre;
    void* valor;
    TipoDato tipo;
    Clase clase;
    int isFinal;
    int linea;   // línea de declaración
    int columna; // columna de declaración
    Symbol* anterior;
};

struct Context {
    int nombre;
    Context* anterior;
    Symbol* ultimoSymbol; //tabla de simbolos
    int dentroLoop; // contador de anidamiento de loops
    int dentroSwitch; // contador de anidamiento de switch
    // Estructura de árbol para recorrer todos los ámbitos
    struct Context* firstChild;
    struct Context* nextSibling;
};

Context* nuevoContext(Context* anterior);
Symbol* nuevoVariable(char* nombre, void* valor, TipoDato tipo, int isFinal);
void agregarSymbol(Context* actual, Symbol*);
Symbol* buscarSymbol(Symbol* actual, char* nombre);
Symbol* buscarTablaSimbolos(Context* actual, char* nombre);

/* Utilidades de reporte para GUI: imprimen con prefijos de parseo */
void print_context_symbols(Context* ctx, const char* ambitoName);
void print_all_contexts_symbols(Context* root);

//cambiar la lista de symbol con una tabla hash donde la funcion hash esta dada por el nombre del symbol + la linea + columna inicio + columna final + tipo + clase

#endif