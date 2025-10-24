/** Helper para obtener valor por defecto de un tipo. */
#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H

#include "result.h"

/*
 * Crea (malloc) un valor por defecto para 'tipo'.
 * Para STRING devuelve NULL y tipoReal se marca NULO.
 * Devuelve 1 si se creó correctamente, 0 si tipo no soportado.
 * outValor recibe el puntero (o NULL para STRING/NULO).
 * outTipoReal permite ajustar el tipo almacenado (ej: STRING -> NULO inicial).
 */
int valor_por_defecto(TipoDato tipo, void** outValor, TipoDato* outTipoReal);

#endif /* DEFAULT_VALUES_H */
