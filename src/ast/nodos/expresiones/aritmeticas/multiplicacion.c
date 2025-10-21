#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "aritmeticas.h"
#include "ast/nodos/expresiones/expresiones.h"

#include <stdlib.h>
#include <stdio.h>

Result multiplicarIntInt(ExpresionLenguaje* self) {
    int* res = malloc(sizeof(int));
    *res =  *((int*)self->izquierda.valor) * *((int*)self->derecha.valor);
    // debug temporal
    // fprintf(stderr, "[DBG MUL] %d * %d = %d\n", *((int*)self->izquierda.valor), *((int*)self->derecha.valor), *res);
    return nuevoValorResultado(res, INT);
}

Result multiplicarFloatFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((float*)self->izquierda.valor) * *((float*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}

Result multiplicarIntFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((int*)self->izquierda.valor) * *((float*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}

Result multiplicarFloatInt(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((float*)self->izquierda.valor) * *((int*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}
// DOUBLE handlers
static Result multiplicarIntDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r=(double)(*((int*)self->izquierda.valor))* *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result multiplicarDoubleInt(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r=* ((double*)self->izquierda.valor) * (double)(*((int*)self->derecha.valor)); return nuevoValorResultado(r, DOUBLE);} 
static Result multiplicarFloatDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r=(double)(*((float*)self->izquierda.valor))* *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result multiplicarDoubleFloat(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r=* ((double*)self->izquierda.valor) * (double)(*((float*)self->derecha.valor)); return nuevoValorResultado(r, DOUBLE);} 
static Result multiplicarDoubleDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r=* ((double*)self->izquierda.valor) * *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result multiplicarCharDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r=(double)(*((char*)self->izquierda.valor))* *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result multiplicarDoubleChar(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r=* ((double*)self->izquierda.valor) * (double)(*((char*)self->derecha.valor)); return nuevoValorResultado(r, DOUBLE);} 


// Wrappers CHAR multiplicación
static Result multiplicarCharChar(ExpresionLenguaje* self){
    /* Sin validación de rango: comportamiento de overflow definido por truncamiento a char. */
    int a = (int)(*((unsigned char*)self->izquierda.valor));
    int b = (int)(*((unsigned char*)self->derecha.valor));
    int prod = a * b;
    char* r = malloc(sizeof(char));
    *r = (char)prod;
    return nuevoValorResultado(r, CHAR);
} 
static Result multiplicarCharInt(ExpresionLenguaje* self){ int* r=malloc(sizeof(int)); *r=(int)(*((char*)self->izquierda.valor)) * *((int*)self->derecha.valor); return nuevoValorResultado(r, INT);} 
static Result multiplicarIntChar(ExpresionLenguaje* self){ int* r=malloc(sizeof(int)); *r= *((int*)self->izquierda.valor) * (int)(*((char*)self->derecha.valor)); return nuevoValorResultado(r, INT);} 
static Result multiplicarCharFloat(ExpresionLenguaje* self){ float* r=malloc(sizeof(float)); *r=(float)(*((char*)self->izquierda.valor)) * *((float*)self->derecha.valor); return nuevoValorResultado(r, FLOAT);} 
static Result multiplicarFloatChar(ExpresionLenguaje* self){ float* r=malloc(sizeof(float)); *r= *((float*)self->izquierda.valor) * (float)(*((char*)self->derecha.valor)); return nuevoValorResultado(r, FLOAT);} 

Operacion tablaOperacionesMultiplicacion[TIPO_COUNT][TIPO_COUNT] = {
    [INT][INT] = multiplicarIntInt,
    [FLOAT][FLOAT] = multiplicarFloatFloat,
    [INT][FLOAT] = multiplicarIntFloat,
    [FLOAT][INT] = multiplicarFloatInt,
    [BYTE][BYTE] = multiplicarIntInt,
    [BYTE][SHORT] = multiplicarIntInt,
    [BYTE][INT] = multiplicarIntInt,
    [BYTE][LONG] = multiplicarIntInt,
    [BYTE][FLOAT] = multiplicarIntFloat,
    /* BYTE/SHORT/LONG con DOUBLE pasan a rama explícita [INT][DOUBLE] abajo para resultado DOUBLE */
    [SHORT][BYTE] = multiplicarIntInt,
    [SHORT][SHORT] = multiplicarIntInt,
    [SHORT][INT] = multiplicarIntInt,
    [SHORT][LONG] = multiplicarIntInt,
    [SHORT][FLOAT] = multiplicarIntFloat,
    /* handled by [INT][DOUBLE] mapping below */
    [LONG][BYTE] = multiplicarIntInt,
    [LONG][SHORT] = multiplicarIntInt,
    [LONG][INT] = multiplicarIntInt,
    [LONG][LONG] = multiplicarIntInt,
    [LONG][FLOAT] = multiplicarIntFloat,
    /* handled by [INT][DOUBLE] mapping below */
    [DOUBLE][BYTE] = multiplicarDoubleInt,
    [DOUBLE][SHORT] = multiplicarDoubleInt,
    [DOUBLE][INT] = multiplicarDoubleInt,
    [DOUBLE][LONG] = multiplicarDoubleInt,
    [DOUBLE][FLOAT] = multiplicarDoubleFloat,
    [DOUBLE][DOUBLE] = multiplicarDoubleDouble,
    [INT][BYTE] = multiplicarIntInt,
    [INT][SHORT] = multiplicarIntInt,
    [INT][LONG] = multiplicarIntInt,
    [FLOAT][BYTE] = multiplicarFloatInt,
    [FLOAT][SHORT] = multiplicarFloatInt,
    [FLOAT][LONG] = multiplicarFloatInt,
    [FLOAT][DOUBLE] = multiplicarFloatDouble,
    // CHAR
    [CHAR][CHAR] = multiplicarCharChar,
    [CHAR][INT] = multiplicarCharInt,
    [INT][CHAR] = multiplicarIntChar,
    [CHAR][FLOAT] = multiplicarCharFloat,
    [FLOAT][CHAR] = multiplicarFloatChar,
    [CHAR][DOUBLE] = multiplicarCharDouble,
    [DOUBLE][CHAR] = multiplicarDoubleChar,
    [INT][DOUBLE] = multiplicarIntDouble,
    [BYTE][DOUBLE] = multiplicarIntDouble,
    [SHORT][DOUBLE] = multiplicarIntDouble,
    [LONG][DOUBLE] = multiplicarIntDouble,
};

//builders.h
AbstractExpresion* nuevoMultiplicacionExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha) {
    ExpresionLenguaje* multiplicacionExpresion = nuevoExpresionLenguaje(interpretExpresionLenguaje, izquierda, derecha);
    multiplicacionExpresion->tablaOperaciones = &tablaOperacionesMultiplicacion;
    return (AbstractExpresion*) multiplicacionExpresion;
}
