#ifndef DECLARACION_H
#define DECLARACION_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef struct {
    AbstractExpresion base;
    char* nombre;
    TipoDato tipo;
    int isFinal;
    int linea;
    int columna;
} DeclaracionVariable;

Result interpretDeclaracionVariable(AbstractExpresion*, Context*);


#endif
