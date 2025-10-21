/** Conversión centralizada de valores para asignaciones/declaraciones/casts simples.
 *  Se apoya en tipos_compatibles_asignacion para validar la compatibilidad general.
 */
#ifndef CONVERSION_UTILS_H
#define CONVERSION_UTILS_H

#include "result.h"


/* API unificada: conversión/copia para uso general (asignaciones, arrays, casts)
 * deepCopySameType: si origen.tipo == destino y es primitivo/STRING, fuerza copia/duplicado.
 * liberaOrigenEnExito: si se convierte/copia exitosamente y esta bandera es 1, se libera origen.valor
 *   (pensado para flujos donde el origen ya no se usará, ej. literales de array). */
int convertir_valor(TipoDato destino, Result origen, int deepCopySameType, int validaPrecisionEnteros,
                    int liberaOrigenEnExito, void** outValor, char* errorMsg, size_t errorMsgLen);

#endif /* CONVERSION_UTILS_H */
