#ifndef ASIGNACION_RESTA_H
#define ASIGNACION_RESTA_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "asignacion_util.h"

typedef struct AsignacionRestaExpresion AsignacionRestaExpresion;

struct AsignacionRestaExpresion {
    AbstractExpresion base;
    char* nombre;
};

#endif
