#ifndef ASIGNACION_MULTIPLICACION_H
#define ASIGNACION_MULTIPLICACION_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "asignacion_util.h"

typedef struct AsignacionMultiplicacionExpresion AsignacionMultiplicacionExpresion;

struct AsignacionMultiplicacionExpresion {
    AbstractExpresion base;
    char* nombre;
};

#endif
