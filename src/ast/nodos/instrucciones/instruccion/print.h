#ifndef PRINT_H
#define PRINT_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef struct {
    AbstractExpresion base;
    int newline; /* 1 = println (agrega salto al final), 0 = print (sin salto) */
} PrintExpresion;

Result interpretPrintExpresion(AbstractExpresion*, Context*);
/* Builder actualizado: recibe lista expresiones y flag newline */
AbstractExpresion* nuevoPrintExpresion(AbstractExpresion* listaExpresiones, int newline);

#endif
