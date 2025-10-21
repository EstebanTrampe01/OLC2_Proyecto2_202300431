#ifndef RELACIONALES_H
#define RELACIONALES_H

#include "../expresiones.h"

/* IGUALDAD */
Result igualdadIntInt(ExpresionLenguaje* self);
Result igualdadFloatFloat(ExpresionLenguaje* self);
Result igualdadIntFloat(ExpresionLenguaje* self);
Result igualdadFloatInt(ExpresionLenguaje* self);
Result igualdadBooleanBoolean(ExpresionLenguaje* self);
Result igualdadCharChar(ExpresionLenguaje* self);
Result igualdadStringString(ExpresionLenguaje* self);

/* DESIGUALDAD */
Result desigualdadIntInt(ExpresionLenguaje* self);
Result desigualdadFloatFloat(ExpresionLenguaje* self);
Result desigualdadIntFloat(ExpresionLenguaje* self);
Result desigualdadFloatInt(ExpresionLenguaje* self);
Result desigualdadBooleanBoolean(ExpresionLenguaje* self);
Result desigualdadCharChar(ExpresionLenguaje* self);
Result desigualdadStringString(ExpresionLenguaje* self);

/* MAYOR QUE */
Result mayorQueIntInt(ExpresionLenguaje* self);
Result mayorQueFloatFloat(ExpresionLenguaje* self);
Result mayorQueIntFloat(ExpresionLenguaje* self);
Result mayorQueFloatInt(ExpresionLenguaje* self);
Result mayorQueCharChar(ExpresionLenguaje* self);
Result mayorQueIntDouble(ExpresionLenguaje* self);
Result mayorQueDoubleInt(ExpresionLenguaje* self);
Result mayorQueFloatDouble(ExpresionLenguaje* self);
Result mayorQueDoubleFloat(ExpresionLenguaje* self);
Result mayorQueDoubleDouble(ExpresionLenguaje* self);

/* MENOR QUE */
Result menorQueIntInt(ExpresionLenguaje* self);
Result menorQueFloatFloat(ExpresionLenguaje* self);
Result menorQueIntFloat(ExpresionLenguaje* self);
Result menorQueFloatInt(ExpresionLenguaje* self);
Result menorQueCharChar(ExpresionLenguaje* self);
Result menorQueIntDouble(ExpresionLenguaje* self);
Result menorQueDoubleInt(ExpresionLenguaje* self);
Result menorQueFloatDouble(ExpresionLenguaje* self);
Result menorQueDoubleFloat(ExpresionLenguaje* self);
Result menorQueDoubleDouble(ExpresionLenguaje* self);

/* MAYOR O IGUAL QUE */
Result mayorIgualQueIntInt(ExpresionLenguaje* self);
Result mayorIgualQueFloatFloat(ExpresionLenguaje* self);
Result mayorIgualQueIntFloat(ExpresionLenguaje* self);
Result mayorIgualQueFloatInt(ExpresionLenguaje* self);
Result mayorIgualQueCharChar(ExpresionLenguaje* self);

/* MENOR O IGUAL QUE */
Result menorIgualQueIntInt(ExpresionLenguaje* self);
Result menorIgualQueFloatFloat(ExpresionLenguaje* self);
Result menorIgualQueIntFloat(ExpresionLenguaje* self);
Result menorIgualQueFloatInt(ExpresionLenguaje* self);
Result menorIgualQueCharChar(ExpresionLenguaje* self);

/* Tablas de operaciones */
extern Operacion tablaOperacionesIgualdad[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesDesigualdad[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesMayorQue[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesMenorQue[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesMayorIgualQue[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesMenorIgualQue[TIPO_COUNT][TIPO_COUNT];

/* Constructores */
AbstractExpresion* nuevoIgualdadExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoDesigualdadExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoMayorQueExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoMenorQueExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoMayorIgualQueExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoMenorIgualQueExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);

#endif