#ifndef ASIGNACION_SUMA_H
#define ASIGNACION_SUMA_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "asignacion_util.h"

typedef struct AsignacionSumaExpresion AsignacionSumaExpresion;

struct AsignacionSumaExpresion {
    AbstractExpresion base;
    char* nombre;
};

#endif
