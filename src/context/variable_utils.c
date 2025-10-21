#include <stdio.h>
#include "variable_utils.h"
#include "error_reporting.h"

int obtener_variable_modificable(AbstractExpresion* nodo, Context* ctx, const char* nombre, Symbol** outSymbol){
    if(!outSymbol) return 0;
    *outSymbol=NULL;
    Symbol* s = buscarTablaSimbolos(ctx, (char*)nombre);
    if(!s){ report_runtime_error(nodo, ctx, "Variable '%s' no declarada", nombre); return 0; }
    if(s->isFinal){ report_runtime_error(nodo, ctx, "No se puede reasignar la constante 'final' '%s'", nombre); return 0; }
    *outSymbol = s; return 1;
}
