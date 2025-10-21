#ifndef CAST_H
#define CAST_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef struct {
    AbstractExpresion base;
    TipoDato tipoDestino;
} CastExpresion;

Result interpretCastExpresion(AbstractExpresion*, Context*);

#endif
