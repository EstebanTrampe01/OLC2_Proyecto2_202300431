// función y return
#ifndef FUNCION_NODO_H
#define FUNCION_NODO_H

#include "../../../AbstractExpresion.h"
#include "context/context.h"

typedef struct {
    AbstractExpresion base;
    char* nombre;
    TipoDato retorno;
    int returnDims;        // Nuevo: número de dimensiones del retorno (0 = primitivo, 1+ = array)
    char** paramNombres;
    TipoDato* paramTipos;
    int paramCount;
    AbstractExpresion* cuerpo; // bloque
    int linea;
    int columna;
} FuncionDecl;

typedef struct {
    AbstractExpresion base;
    AbstractExpresion* valor; // puede ser NULL para void
} ReturnExpresion;

typedef struct {
    AbstractExpresion base;
    char* nombre;
    AbstractExpresion* args; // lista expresiones
} LlamadaFuncion;

AbstractExpresion* nuevoFuncionDeclaracion(TipoDato retorno, char* nombre, char** paramNombres, TipoDato* paramTipos, int paramCount, AbstractExpresion* cuerpo, int returnDims);
AbstractExpresion* nuevoReturnExpresion(AbstractExpresion* valor);
AbstractExpresion* nuevoLlamadaFuncion(char* nombre, AbstractExpresion* args);

Result interpretFuncionDeclaracion(AbstractExpresion*, Context*);
Result interpretReturnExpresion(AbstractExpresion*, Context*);
Result interpretLlamadaFuncion(AbstractExpresion*, Context*);

/* Utilidad: imprimir funciones declaradas en formato SYM| */
void print_function_registry_symbols(void);

#endif