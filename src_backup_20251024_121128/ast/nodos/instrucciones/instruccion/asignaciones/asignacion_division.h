#ifndef ASIGNACION_DIVISION_H
#define ASIGNACION_DIVISION_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "asignacion_util.h"

typedef struct AsignacionDivisionExpresion AsignacionDivisionExpresion;

struct AsignacionDivisionExpresion {
    AbstractExpresion base;
    char* nombre;
};

#endif
