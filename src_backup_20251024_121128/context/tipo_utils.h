/** Utilidades centralizadas para compatibilidad y clasificación de tipos */
#ifndef TIPO_UTILS_H
#define TIPO_UTILS_H

#include "result.h"

/* Devuelve 1 si el tipo es numérico (incluye char como entero pequeño). */
int es_numerico(TipoDato t);

/*
 * Reglas de compatibilidad de asignación (incluye widenings implícitos y algunos narrowings controlados).
 * destino: tipo de la variable / lugar que recibe.
 * origen: tipo del valor producido.
 * requiereValidacionPrecision: (salida) se marca 1 cuando la operación puede implicar pérdida de precisión
 *   y debería validarse el valor concreto (ej. float/double -> entero, double -> float).
 * Retorna 1 si se permite la asignación (antes de validar el valor), 0 si es incompatible.
 */
int tipos_compatibles_asignacion(TipoDato destino, TipoDato origen, int* requiereValidacionPrecision);

#endif /* TIPO_UTILS_H */
