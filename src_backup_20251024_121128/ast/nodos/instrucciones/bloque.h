#ifndef BLOQUE_H
#define BLOQUE_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef struct {
    AbstractExpresion base;
    int useParentContext;  // Flag para indicar si usar el contexto padre
} BloqueExpresion;

Result interpretBloqueExpresion(AbstractExpresion*, Context*);

#endif
