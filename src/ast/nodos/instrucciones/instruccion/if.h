#ifndef IF_H
#define IF_H

#include "../../../AbstractExpresion.h"
#include "../../../../context/context.h"

typedef struct IfExpresion {
    AbstractExpresion base;
    AbstractExpresion* condicion;
    AbstractExpresion* bloqueIf;
    AbstractExpresion* bloqueElse; // NULL si no hay else
} IfExpresion;

AbstractExpresion* nuevoIfExpresion(AbstractExpresion* condicion, AbstractExpresion* bloqueIf, AbstractExpresion* bloqueElse);
Result interpretIfExpresion(AbstractExpresion* self, Context* context);

#endif
