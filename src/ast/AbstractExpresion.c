#include "AbstractExpresion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/nodos/expresiones/terminales/primitivos.h"
#include "context/error_reporting.h"

// Añadir hijo al Nodo
void agregarHijo(AbstractExpresion* padre, AbstractExpresion* hijo) {
    if (!padre || !hijo) return;
    if(padre->numHijos >= 100000){
        static int g_reported = 0;
        if(!g_reported){
            g_reported = 1;
            report_semantic_error(padre, NULL, "nodo con demasiados hijos (%zu)", padre->numHijos+1);
        }
        return;
    }
    // reasignar el tamaño del bloque de almacenamiento
    // si tenia 4 espacios de tipo puntero le sumamos 1 espacio más
    // realloc(puntero al principio del bloque, tamaño )
    //TODO: mejorar
    AbstractExpresion** newarr = realloc(padre->hijos, sizeof(AbstractExpresion*) * (padre->numHijos + 1));
    if (!newarr) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    padre->hijos = newarr;
    padre->hijos[padre->numHijos] = hijo;
    padre->numHijos++;
}

/* liberación */
void liberarAST(AbstractExpresion* raiz) {
    if (!raiz) return;
    for (size_t i = 0; i < raiz->numHijos; ++i) {
        liberarAST(raiz->hijos[i]);
    }
    // Liberar payload de primitivas STRING ahora que cada símbolo hará deep copy propio.
    if(raiz->interpret == interpretPrimitivoExpresion){
        PrimitivoExpresion* p = (PrimitivoExpresion*)raiz;
        if(p->tipo == STRING && p->valor){ free(p->valor); p->valor=NULL; }
    }
    free(raiz->hijos);
    free(raiz);
}

void buildAbstractExpresion(AbstractExpresion* base, Interpret interpretPuntero) {
    //asignar valores
    base->interpret = interpretPuntero;
    base->hijos = NULL;
    base->linea = 0; base->columna = 0;
    base->numHijos = 0;
}
