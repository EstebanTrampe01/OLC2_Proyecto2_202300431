#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "bloque.h"

#include <stdlib.h>
#include <stdio.h>

Result interpretBloqueExpresion(AbstractExpresion* self, Context* context) {
    BloqueExpresion* bloque = (BloqueExpresion*)self;
    
    if (bloque->useParentContext) {
        // Usar el contexto padre directamente
        for (size_t i = 0; i < self->numHijos; ++i) {
            Result r = self->hijos[i]->interpret(self->hijos[i], context);
            if (r.tipo == BREAK || r.tipo == CONTINUE || r.tipo == RETURN) {
                return r; // propagar inmediatamente (incluye RETURN)
            }
        }
    } else {
        // Crear un nuevo contexto para el bloque (ámbito local)
        Context* newContext = nuevoContext(context);
        
        // Interpretar las instrucciones dentro del nuevo contexto
        for (size_t i = 0; i < self->numHijos; ++i) {
            Result r = self->hijos[i]->interpret(self->hijos[i], newContext);
            if (r.tipo == BREAK || r.tipo == CONTINUE || r.tipo == RETURN) {
                return r; // propagar (incluye RETURN)
            }
        }
    }
    
    return nuevoValorResultadoVacio();
}

AbstractExpresion* nuevoBloqueExpresion(AbstractExpresion* instrucciones) {
    BloqueExpresion* nodo = malloc(sizeof(BloqueExpresion));
    if (!nodo) return NULL;
    buildAbstractExpresion(&nodo->base, interpretBloqueExpresion);
    nodo->useParentContext = 0;  // Por defecto, crear nuevo contexto
    if (instrucciones) agregarHijo((AbstractExpresion*) nodo, instrucciones);
    return (AbstractExpresion*) nodo;
}

AbstractExpresion* nuevoBloqueExpresionConContextoPadre(AbstractExpresion* instrucciones) {
    BloqueExpresion* nodo = malloc(sizeof(BloqueExpresion));
    if (!nodo) return NULL;
    buildAbstractExpresion(&nodo->base, interpretBloqueExpresion);
    nodo->useParentContext = 1;  // Usar contexto padre
    if (instrucciones) agregarHijo((AbstractExpresion*) nodo, instrucciones);
    return (AbstractExpresion*) nodo;
}
