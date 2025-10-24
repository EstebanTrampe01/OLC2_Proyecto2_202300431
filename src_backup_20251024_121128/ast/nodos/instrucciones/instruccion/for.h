#ifndef FOR_EXPRESION_H
#define FOR_EXPRESION_H

#include "../../../AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef struct {
    AbstractExpresion base;
    AbstractExpresion* initialization;  // Puede ser NULL
    AbstractExpresion* condition;       // Puede ser NULL
    AbstractExpresion* increment;        // Puede ser NULL
    AbstractExpresion* body;
} ForExpresion;

AbstractExpresion* nuevoForExpresion(AbstractExpresion* initialization, AbstractExpresion* condition, AbstractExpresion* increment, AbstractExpresion* body);

// Intérprete del nodo For (declarado para identificación en AST DOT)
Result interpretForExpresion(AbstractExpresion*, Context*);

#endif
