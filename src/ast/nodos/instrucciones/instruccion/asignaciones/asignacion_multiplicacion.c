#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "asignacion_multiplicacion.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Result interpretAsignacionMultiplicacionExpresion(AbstractExpresion* self, Context* context) {
    AsignacionMultiplicacionExpresion* nodo = (AsignacionMultiplicacionExpresion*) self;
    return realizarAsignacionCompuesta(self, context, nodo->nombre, &tablaOperacionesMultiplicacion, "*=");
}

AbstractExpresion* nuevoAsignacionMultiplicacionExpresion(char* nombre, AbstractExpresion* expresion) {
    AsignacionMultiplicacionExpresion* nodo = malloc(sizeof(AsignacionMultiplicacionExpresion));
    if (!nodo) return NULL;
    buildAbstractExpresion(&nodo->base, interpretAsignacionMultiplicacionExpresion);

    nodo->nombre = nombre;
    if (expresion) agregarHijo((AbstractExpresion*) nodo, expresion);
    return (AbstractExpresion*) nodo;
}
