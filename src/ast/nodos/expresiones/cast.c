#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "context/tipo_utils.h"
#include "context/conversion_utils.h"
#include "cast.h"

#include <stdlib.h>
#include <stdio.h>
#include "context/error_reporting.h"

Result interpretCastExpresion(AbstractExpresion* self, Context* context) {
    CastExpresion* nodo = (CastExpresion*) self;
    
    Result resultado = self->hijos[0]->interpret(self->hijos[0], context);
    
    if (resultado.tipo == nodo->tipoDestino) return resultado;

    int requiereValidacion = 0;
    int compatible = tipos_compatibles_asignacion(nodo->tipoDestino, resultado.tipo, &requiereValidacion);
    int permitidoExtra = 0;
    if(!compatible){
        // Cast explícito adicional permitido: numérico <-> boolean, numérico <-> char
        if( (nodo->tipoDestino == BOOLEAN && es_numerico(resultado.tipo)) ||
            (es_numerico(nodo->tipoDestino) && resultado.tipo == BOOLEAN) ||
            (nodo->tipoDestino == CHAR && es_numerico(resultado.tipo)) ||
            (es_numerico(nodo->tipoDestino) && resultado.tipo == CHAR)){
            permitidoExtra = 1;
        }
        if(!permitidoExtra){
            report_runtime_error(self, context, "Casting no soportado de %s a %s", labelTipoDato[resultado.tipo], labelTipoDato[nodo->tipoDestino]);
            return nuevoValorResultadoVacio();
        }
    }

    // Caso compatible normal: usar API unificada (deepCopySameType=1 para evitar aliasing inesperado)
    if(compatible && nodo->tipoDestino != CHAR && !(nodo->tipoDestino==BOOLEAN && resultado.tipo!=BOOLEAN && resultado.tipo!=INT)){
        void* nuevo=NULL; char err[128];
        /* Política: en cast explícito, permitir truncamiento numérico (float/double->int)
           sin marcar error de precisión. Por eso pasamos validaPrecisionEnteros=0. */
        int validaPrecisionEnteros = 0;
        if(!convertir_valor(nodo->tipoDestino, resultado, 1, validaPrecisionEnteros, 0, &nuevo, err, sizeof(err))){
            report_runtime_error(self, context, "Error en cast: %s", err);
            return nuevoValorResultadoVacio();
        }
        return nuevoValorResultado(nuevo, nodo->tipoDestino);
    }

    // Rutas especiales (permitidoExtra) o CHAR / BOOLEAN con reglas extendidas
    switch(nodo->tipoDestino){
        case CHAR: {
            char* c = malloc(sizeof(char)); if(!c){ report_runtime_error(self, context, "Memoria insuficiente en cast CHAR"); return nuevoValorResultadoVacio(); }
            if(resultado.tipo == CHAR) *c = *(char*)resultado.valor;
            else if(es_numerico(resultado.tipo)){
                if(resultado.tipo==FLOAT) *c = (char)(*(float*)resultado.valor);
                else if(resultado.tipo==DOUBLE) *c = (char)(*(double*)resultado.valor);
                else *c = (char)(*(int*)resultado.valor);
            } else { free(c); report_runtime_error(self, context, "Casting a CHAR inválido"); return nuevoValorResultadoVacio(); }
            return nuevoValorResultado(c, CHAR); }
        case BOOLEAN: {
            int* b = malloc(sizeof(int)); if(!b){ report_runtime_error(self, context, "Memoria insuficiente en cast BOOLEAN"); return nuevoValorResultadoVacio(); }
            if(resultado.tipo == BOOLEAN) *b = (*(int*)resultado.valor)!=0;
            else if(es_numerico(resultado.tipo)) *b = (*(int*)resultado.valor)!=0;
            else { free(b); report_runtime_error(self, context, "Casting a BOOLEAN inválido"); return nuevoValorResultadoVacio(); }
            return nuevoValorResultado(b, BOOLEAN); }
        default:
            report_runtime_error(self, context, "Casting no soportado a %s", labelTipoDato[nodo->tipoDestino]);
            return nuevoValorResultadoVacio();
    }
}

AbstractExpresion* nuevoCastExpresion(TipoDato tipoDestino, AbstractExpresion* expresion) {
    CastExpresion* nodo = malloc(sizeof(CastExpresion));
    if (!nodo) return NULL;
    buildAbstractExpresion(&nodo->base, interpretCastExpresion);
    
    nodo->tipoDestino = tipoDestino;
    if (expresion) agregarHijo((AbstractExpresion*) nodo, expresion);
    return (AbstractExpresion*) nodo;
}
