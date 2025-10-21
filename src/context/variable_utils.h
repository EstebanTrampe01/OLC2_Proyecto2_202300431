/** Utilidades para obtención/validación de variables antes de asignar. */
#ifndef VARIABLE_UTILS_H
#define VARIABLE_UTILS_H

#include "context.h"
#include "error_reporting.h"

/*
 * Busca una variable y valida que exista y no sea final.
 * Retorna 1 si OK y coloca el puntero en *outSymbol; en caso contrario reporta error y retorna 0.
 */
int obtener_variable_modificable(AbstractExpresion* nodo, Context* ctx, const char* nombre, Symbol** outSymbol);

#endif /* VARIABLE_UTILS_H */
