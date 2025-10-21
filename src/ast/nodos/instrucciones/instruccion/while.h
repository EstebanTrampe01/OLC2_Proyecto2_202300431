#ifndef WHILE_EXPRESION_H
#define WHILE_EXPRESION_H

#include "../../../AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef struct {
    AbstractExpresion base;
    AbstractExpresion* condition;
    AbstractExpresion* body;
} WhileExpresion;

AbstractExpresion* nuevoWhileExpresion(AbstractExpresion* condition, AbstractExpresion* body);

// Intérprete del nodo While (declarado para identificación en AST DOT)
Result interpretWhileExpresion(AbstractExpresion*, Context*);

#endif
