#ifndef ASIGNACION_MODULO_H
#define ASIGNACION_MODULO_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "asignacion_util.h"

typedef struct AsignacionModuloExpresion AsignacionModuloExpresion;

struct AsignacionModuloExpresion {
    AbstractExpresion base;
    char* nombre;
};

#endif
