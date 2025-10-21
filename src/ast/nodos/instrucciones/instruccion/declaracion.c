#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "context/tipo_utils.h"
#include "context/conversion_utils.h"
#include "context/default_values.h"
#include "declaracion.h"

#include <stdlib.h>
#include <stdio.h>
#include "context/error_reporting.h"
#include "ast/nodos/expresiones/terminales/primitivos.h"

Result interpretDeclaracionVariable(AbstractExpresion* nodo, Context* context) {
    DeclaracionVariable* self = (DeclaracionVariable*) nodo;
    
    if (nodo->numHijos > 0) {
        Result resultado = nodo->hijos[0]->interpret(nodo->hijos[0], context);

        int requiereValidacion = 0; 
        if (!tipos_compatibles_asignacion(self->tipo, resultado.tipo, &requiereValidacion)) {
            report_runtime_error(nodo, context, "Tipos incompatibles al inicializar '%s'", self->nombre);
            return nuevoValorResultadoVacio();
        }
    void* almacen = NULL; char err[128];
    /* Usar API unificada: deepCopySameType=1 para replicar semántica previa de copia */
    if(!convertir_valor(self->tipo, resultado, 1, requiereValidacion, 0, &almacen, err, sizeof(err))){
            report_runtime_error(nodo, context, "Error de conversión inicializando '%s': %s", self->nombre, err);
            return nuevoValorResultadoVacio();
        }
        if(nodo->hijos[0]->interpret == interpretPrimitivoExpresion && resultado.tipo != STRING){
            free(resultado.valor);
        }
        Symbol* s = nuevoVariable(self->nombre, almacen, self->tipo, self->isFinal);
        s->linea = self->linea; s->columna = self->columna; agregarSymbol(context, s);
        return nuevoValorResultadoVacio();
    }
    
    if (self->isFinal) {
    report_runtime_error(nodo, context, "La constante 'final' '%s' debe inicializarse", self->nombre);
        return nuevoValorResultadoVacio();
    }
    
    void* defaultValue = NULL; TipoDato defaultTipo;
    if(!valor_por_defecto(self->tipo, &defaultValue, &defaultTipo)){
        report_runtime_error(nodo, context, "No se puede determinar valor por defecto para tipo");
        return nuevoValorResultadoVacio();
    }
    Symbol* s = nuevoVariable(self->nombre, defaultValue, defaultTipo, self->isFinal);
    s->linea = self->linea;
    s->columna = self->columna;
    agregarSymbol(context, s);
    return nuevoValorResultadoVacio();
}

AbstractExpresion* nuevoDeclaracionVariables(TipoDato tipo, char* nombre, AbstractExpresion* expresion, int isFinal) {
    //reservar el espacio en memoria y obtener el puntero a este
    DeclaracionVariable* nodo = malloc(sizeof(DeclaracionVariable));
    if (!nodo) return NULL;
    //asignar valores
    buildAbstractExpresion(&nodo->base, interpretDeclaracionVariable);
    nodo->tipo = tipo;
    nodo->nombre = nombre;
    nodo->isFinal = isFinal;
    nodo->linea = 0;
    nodo->columna = 0;

    if (expresion) agregarHijo((AbstractExpresion*) nodo, expresion);
    return (AbstractExpresion*) nodo;
}
