#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "context/tipo_utils.h"
#include "context/conversion_utils.h"
#include "context/variable_utils.h"
#include "asignacion.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "context/error_reporting.h"

Result interpretAsignacionExpresion(AbstractExpresion* self, Context* context) {
    AsignacionExpresion* nodo = (AsignacionExpresion*) self;
    
    // Obtener variable modficable (centralizado)
    Symbol* symbol=NULL; if(!obtener_variable_modificable(self, context, nodo->nombre, &symbol)) return nuevoValorResultadoVacio();
    
    // Interpretar la expresión
    Result resultado = self->hijos[0]->interpret(self->hijos[0], context);
    
    int requiereValidacion=0;
    if(!tipos_compatibles_asignacion(symbol->tipo, resultado.tipo, &requiereValidacion)){
        report_runtime_error(self, context, "Tipos incompatibles en asignación a '%s'", nodo->nombre);
        return nuevoValorResultadoVacio();
    }

    void* nuevo=NULL; char err[128];
    if(!convertir_valor(symbol->tipo, resultado, 1, requiereValidacion, 0, &nuevo, err, sizeof(err))){
        report_runtime_error(self, context, "Error de conversión en asignación a '%s': %s", nodo->nombre, err);
        return nuevoValorResultadoVacio();
    }
    // Evitar liberar arrays aquí: add() muta en sitio y reasignaciones podrían apuntar al mismo bloque
    if(symbol->valor && symbol->tipo!=STRING && symbol->tipo!=NULO && symbol->tipo!=ARRAY) free(symbol->valor);
    symbol->valor = nuevo; return nuevoValorResultadoVacio();
}

AbstractExpresion* nuevoAsignacionExpresion(char* nombre, AbstractExpresion* expresion) {
    AsignacionExpresion* nodo = malloc(sizeof(AsignacionExpresion));
    if (!nodo) return NULL;
    buildAbstractExpresion(&nodo->base, interpretAsignacionExpresion);
    
    nodo->nombre = nombre;
    if (expresion) agregarHijo((AbstractExpresion*) nodo, expresion);
    return (AbstractExpresion*) nodo;
}
