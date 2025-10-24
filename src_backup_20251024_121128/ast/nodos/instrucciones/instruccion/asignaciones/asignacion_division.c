#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "asignacion_division.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Result interpretAsignacionDivisionExpresion(AbstractExpresion* self, Context* context) {
    AsignacionDivisionExpresion* nodo = (AsignacionDivisionExpresion*) self;
    return realizarAsignacionCompuesta(self, context, nodo->nombre, &tablaOperacionesDivision, "/=");
}

AbstractExpresion* nuevoAsignacionDivisionExpresion(char* nombre, AbstractExpresion* expresion) {
    AsignacionDivisionExpresion* nodo = malloc(sizeof(AsignacionDivisionExpresion));
    if (!nodo) return NULL;
    buildAbstractExpresion(&nodo->base, interpretAsignacionDivisionExpresion);

    nodo->nombre = nombre;
    if (expresion) agregarHijo((AbstractExpresion*) nodo, expresion);
    return (AbstractExpresion*) nodo;
}
