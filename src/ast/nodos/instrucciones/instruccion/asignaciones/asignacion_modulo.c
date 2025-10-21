#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "asignacion_modulo.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Result interpretAsignacionModuloExpresion(AbstractExpresion* self, Context* context) {
    AsignacionModuloExpresion* nodo = (AsignacionModuloExpresion*) self;
    return realizarAsignacionCompuesta(self, context, nodo->nombre, &tablaOperacionesModulo, "%=");
}

AbstractExpresion* nuevoAsignacionModuloExpresion(char* nombre, AbstractExpresion* expresion) {
    AsignacionModuloExpresion* nodo = malloc(sizeof(AsignacionModuloExpresion));
    if (!nodo) return NULL;
    buildAbstractExpresion(&nodo->base, interpretAsignacionModuloExpresion);

    nodo->nombre = nombre;
    if (expresion) agregarHijo((AbstractExpresion*) nodo, expresion);
    return (AbstractExpresion*) nodo;
}
