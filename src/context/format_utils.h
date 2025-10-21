#ifndef FORMAT_UTILS_H
#define FORMAT_UTILS_H

#include <stddef.h>
#include "result.h"

/* Formatea un double con hasta maxDecimals, recorta ceros y punto final. Devuelve puntero a buffer estático (no reentrante). */
const char* format_trim_double(double v, int maxDecimals);
/* Igual para float (convierte a double internamente) */
static inline const char* format_trim_float(float f, int maxDecimals){ return format_trim_double((double)f, maxDecimals); }

/* Formato genérico según tipo primitivo (usado en unificaciones de impresión y concatenación) */
const char* format_number(TipoDato tipo, const void* value);
/* Formateo dedicado para char según política de impresión */
const char* format_char(unsigned char c);

#endif