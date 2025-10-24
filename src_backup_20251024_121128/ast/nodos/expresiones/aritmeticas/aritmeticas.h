#ifndef ARITMETICAS_H
#define ARITMETICAS_H

#include "ast/AbstractExpresion.h"
#include "context/result.h"
#include "context/context.h"
#include "ast/nodos/expresiones/expresiones.h"

/* SUMA */
Result sumarIntInt(ExpresionLenguaje* self);
Result sumarFloatFloat(ExpresionLenguaje* self);
Result sumarIntFloat(ExpresionLenguaje* self);
Result sumarFloatInt(ExpresionLenguaje* self);
Result sumarStringString(ExpresionLenguaje* self);
Result sumarStringInt(ExpresionLenguaje* self);
Result sumarStringFloat(ExpresionLenguaje* self);
Result sumarStringBoolean(ExpresionLenguaje* self);
Result sumarStringChar(ExpresionLenguaje* self);
Result sumarIntString(ExpresionLenguaje* self);
Result sumarFloatString(ExpresionLenguaje* self);
Result sumarBooleanString(ExpresionLenguaje* self);
Result sumarCharString(ExpresionLenguaje* self);

extern Operacion tablaOperacionesSuma[TIPO_COUNT][TIPO_COUNT];

/* RESTA */
Result restaIntInt(ExpresionLenguaje* self);
Result restaFloatFloat(ExpresionLenguaje* self);
Result restaIntFloat(ExpresionLenguaje* self);
Result restaFloatInt(ExpresionLenguaje* self);

extern Operacion tablaOperacionesResta[TIPO_COUNT][TIPO_COUNT];

/* MULTIPLICACION */
Result multiplicarIntInt(ExpresionLenguaje* self);
Result multiplicarFloatFloat(ExpresionLenguaje* self);
Result multiplicarIntFloat(ExpresionLenguaje* self);
Result multiplicarFloatInt(ExpresionLenguaje* self);

extern Operacion tablaOperacionesMultiplicacion[TIPO_COUNT][TIPO_COUNT];

/* DIVISION */
Result dividirIntInt(ExpresionLenguaje* self);
Result dividirFloatFloat(ExpresionLenguaje* self);
Result dividirIntFloat(ExpresionLenguaje* self);
Result dividirFloatInt(ExpresionLenguaje* self);

extern Operacion tablaOperacionesDivision[TIPO_COUNT][TIPO_COUNT];

/* MODULO */
Result moduloIntInt(ExpresionLenguaje* self);
Result moduloFloatFloat(ExpresionLenguaje* self);
Result moduloIntFloat(ExpresionLenguaje* self);
Result moduloFloatInt(ExpresionLenguaje* self);

extern Operacion tablaOperacionesModulo[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesBitAnd[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesBitOr[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesBitXor[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesShiftLeft[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesShiftRight[TIPO_COUNT][TIPO_COUNT];

#endif