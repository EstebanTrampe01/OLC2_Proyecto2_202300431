// Representación de un arreglo
#ifndef ARRAY_VALUE_H
#define ARRAY_VALUE_H

#include "result.h"

typedef struct {
    TipoDato elementType;
    int length;
    void** items; // cada elemento es un puntero a valor primitivo
} ArrayValue;

ArrayValue* nuevoArrayValue(TipoDato elementType, int length);
void liberarArrayValue(ArrayValue* arr); // (no usado aún)
/* Eliminado wrapper legacy valorPorDefecto: usar valor_por_defecto (default_values.h). */

#endif