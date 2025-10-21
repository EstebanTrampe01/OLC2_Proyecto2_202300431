#ifndef ARRAY_ELEMENT_UTILS_H
#define ARRAY_ELEMENT_UTILS_H

#include "result.h"

/*
 * Convierte (o copia) un valor (Result origen) para almacenarlo como elemento de array/matriz.
 * - destino: tipo de elemento del array.
 * - deepCopySameType: cuando origen.tipo == destino, forzar copia profunda (primitivos) / duplicado (STRING)
 *   para evitar aliasing y manejar propiedad de memoria. Si es 0 y tipos iguales se transfiere puntero.
 * Devuelve 1 si compatible (y *outValor listo). 0 si incompatible (outValor queda NULL).
 * En caso de conversión o copia, la función LIBERA el origen.valor cuando procede (primitivos) para evitar fugas.
 * Para STRING:
 *   - Si deepCopySameType==1 y tipos iguales: duplica y libera original.
 *   - Si deepCopySameType==0: transfiere puntero sin duplicar.
 */
int convertir_elemento_array(TipoDato destino, Result origen, int deepCopySameType, void** outValor);

#endif /* ARRAY_ELEMENT_UTILS_H */
