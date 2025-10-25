#ifndef REPEAT_EXPRESION_H
#define REPEAT_EXPRESION_H

#include "../../../AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef struct {
    AbstractExpresion base;
    AbstractExpresion* count;          // Número de repeticiones (3)
    AbstractExpresion* body;           // Cuerpo del loop
} RepeatExpresion;

AbstractExpresion* nuevoRepeatExpresion(AbstractExpresion* count, AbstractExpresion* body);

// Intérprete del nodo Repeat (declarado para identificación en AST DOT)
Result interpretRepeatExpresion(AbstractExpresion*, Context*);

#endif
