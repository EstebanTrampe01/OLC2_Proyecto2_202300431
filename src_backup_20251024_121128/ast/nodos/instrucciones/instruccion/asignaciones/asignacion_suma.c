#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "asignacion_suma.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Result interpretAsignacionSumaExpresion(AbstractExpresion* self, Context* context) {
    AsignacionSumaExpresion* nodo = (AsignacionSumaExpresion*) self;
    return realizarAsignacionCompuesta(self, context, nodo->nombre, &tablaOperacionesSuma, "+=");
}

AbstractExpresion* nuevoAsignacionSumaExpresion(char* nombre, AbstractExpresion* expresion) {
    AsignacionSumaExpresion* nodo = malloc(sizeof(AsignacionSumaExpresion));
    if (!nodo) return NULL;
    buildAbstractExpresion(&nodo->base, interpretAsignacionSumaExpresion);

    nodo->nombre = nombre;
    if (expresion) agregarHijo((AbstractExpresion*) nodo, expresion);
    return (AbstractExpresion*) nodo;
}