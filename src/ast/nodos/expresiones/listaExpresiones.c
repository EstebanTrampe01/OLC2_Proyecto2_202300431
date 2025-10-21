#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "listaExpresiones.h"

#include <stdlib.h>

Result interpretListaExpresiones(AbstractExpresion* self, Context* context) {
    Result result = nuevoValorResultadoVacio();
    
    for (size_t i = 0; i < self->numHijos; i++) {
        result = self->hijos[i]->interpret(self->hijos[i], context);
        if(result.tipo == RETURN || result.tipo == BREAK || result.tipo == CONTINUE){
            return result; // Propagar inmediatamente control flow
        }
    }
    
    return result;
}

AbstractExpresion* nuevoListaExpresiones() {
    //reservar el espacio en memoria y obtener el puntero a este
    ListaExpresiones* nodo = malloc(sizeof(ListaExpresiones));
    if (!nodo) return NULL;
    //asignar valores
    buildAbstractExpresion(&nodo->base, interpretListaExpresiones);

    return (AbstractExpresion*) nodo;
}