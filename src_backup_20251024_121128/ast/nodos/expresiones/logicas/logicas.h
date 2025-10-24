#ifndef LOGICAS_H
#define LOGICAS_H

#include "../expresiones.h"

/* AND LÓGICO */
Result andBooleanBoolean(ExpresionLenguaje* self);

/* OR LÓGICO */
Result orBooleanBoolean(ExpresionLenguaje* self);

/* NOT LÓGICO */
Result notBoolean(ExpresionLenguaje* self);

/* Tablas de operaciones */
extern Operacion tablaOperacionesAnd[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesOr[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesNot[TIPO_COUNT][TIPO_COUNT];

/* Constructores */
AbstractExpresion* nuevoAndExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoOrExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoNotExpresion(AbstractExpresion* expresion);

#endif
