#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "asignacion_resta.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Result interpretAsignacionRestaExpresion(AbstractExpresion* self, Context* context) {
    AsignacionRestaExpresion* nodo = (AsignacionRestaExpresion*) self;
    return realizarAsignacionCompuesta(self, context, nodo->nombre, &tablaOperacionesResta, "-=");
}

AbstractExpresion* nuevoAsignacionRestaExpresion(char* nombre, AbstractExpresion* expresion) {
    AsignacionRestaExpresion* nodo = malloc(sizeof(AsignacionRestaExpresion));
    if (!nodo) return NULL;
    buildAbstractExpresion(&nodo->base, interpretAsignacionRestaExpresion);

    nodo->nombre = nombre;
    if (expresion) agregarHijo((AbstractExpresion*) nodo, expresion);
    return (AbstractExpresion*) nodo;
}