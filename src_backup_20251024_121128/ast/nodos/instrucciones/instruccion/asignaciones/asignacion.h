#ifndef ASIGNACION_H
#define ASIGNACION_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef struct {
    AbstractExpresion base;
    char* nombre;
} AsignacionExpresion;

Result interpretAsignacionExpresion(AbstractExpresion*, Context*);

#endif
