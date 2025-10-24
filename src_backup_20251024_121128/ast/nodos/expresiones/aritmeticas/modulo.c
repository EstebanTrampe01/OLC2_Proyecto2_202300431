// Modulo con soporte CHAR
#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "aritmeticas.h"
#include "ast/nodos/expresiones/expresiones.h"

#include <stdlib.h>
#include <math.h>

Result moduloIntInt(ExpresionLenguaje* self) {
    int* res = malloc(sizeof(int));
    *res = *((int*)self->izquierda.valor) % *((int*)self->derecha.valor);
    return nuevoValorResultado(res, INT);
}

Result moduloFloatFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = fmodf(*((float*)self->izquierda.valor), *((float*)self->derecha.valor));
    return nuevoValorResultado(res, FLOAT);
}

Result moduloIntFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = fmodf((float)*((int*)self->izquierda.valor), *((float*)self->derecha.valor));
    return nuevoValorResultado(res, FLOAT);
}

Result moduloFloatInt(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = fmodf(*((float*)self->izquierda.valor), (float)*((int*)self->derecha.valor));
    return nuevoValorResultado(res, FLOAT);
}
// DOUBLE handlers (usando fmod)
static Result moduloIntDouble(ExpresionLenguaje* self){ double a=(double)(*((int*)self->izquierda.valor)); double b=*((double*)self->derecha.valor); double* r=malloc(sizeof(double)); *r = (b==0)?0:fmod(a,b); return nuevoValorResultado(r, DOUBLE);} 
static Result moduloDoubleInt(ExpresionLenguaje* self){ double a=*((double*)self->izquierda.valor); double b=(double)(*((int*)self->derecha.valor)); double* r=malloc(sizeof(double)); *r = (b==0)?0:fmod(a,b); return nuevoValorResultado(r, DOUBLE);} 
static Result moduloFloatDouble(ExpresionLenguaje* self){ double a=(double)(*((float*)self->izquierda.valor)); double b=*((double*)self->derecha.valor); double* r=malloc(sizeof(double)); *r = (b==0)?0:fmod(a,b); return nuevoValorResultado(r, DOUBLE);} 
static Result moduloDoubleFloat(ExpresionLenguaje* self){ double a=*((double*)self->izquierda.valor); double b=(double)(*((float*)self->derecha.valor)); double* r=malloc(sizeof(double)); *r = (b==0)?0:fmod(a,b); return nuevoValorResultado(r, DOUBLE);} 
static Result moduloDoubleDouble(ExpresionLenguaje* self){ double a=*((double*)self->izquierda.valor); double b=*((double*)self->derecha.valor); double* r=malloc(sizeof(double)); *r = (b==0)?0:fmod(a,b); return nuevoValorResultado(r, DOUBLE);} 
static Result moduloCharDouble(ExpresionLenguaje* self){ double a=(double)(*((char*)self->izquierda.valor)); double b=*((double*)self->derecha.valor); double* r=malloc(sizeof(double)); *r=(b==0)?0:fmod(a,b); return nuevoValorResultado(r, DOUBLE);} 
static Result moduloDoubleChar(ExpresionLenguaje* self){ double a=*((double*)self->izquierda.valor); double b=(double)(*((char*)self->derecha.valor)); double* r=malloc(sizeof(double)); *r=(b==0)?0:fmod(a,b); return nuevoValorResultado(r, DOUBLE);} 

// Wrappers CHAR
static Result moduloCharChar(ExpresionLenguaje* self){ int a=(int)(*((char*)self->izquierda.valor)); int b=(int)(*((char*)self->derecha.valor)); int* r=malloc(sizeof(int)); *r = (b==0)?0:(a % b); return nuevoValorResultado(r, INT);} 
static Result moduloCharInt(ExpresionLenguaje* self){ int a=(int)(*((char*)self->izquierda.valor)); int b=*((int*)self->derecha.valor); int* r=malloc(sizeof(int)); *r = (b==0)?0:(a % b); return nuevoValorResultado(r, INT);} 
static Result moduloIntChar(ExpresionLenguaje* self){ int a=*((int*)self->izquierda.valor); int b=(int)(*((char*)self->derecha.valor)); int* r=malloc(sizeof(int)); *r = (b==0)?0:(a % b); return nuevoValorResultado(r, INT);} 
static Result moduloCharFloat(ExpresionLenguaje* self){ float a=(float)(*((char*)self->izquierda.valor)); float b=*((float*)self->derecha.valor); float* r=malloc(sizeof(float)); *r = (b==0)?0.0f:fmodf(a,b); return nuevoValorResultado(r, FLOAT);} 
static Result moduloFloatChar(ExpresionLenguaje* self){ float a=*((float*)self->izquierda.valor); float b=(float)(*((char*)self->derecha.valor)); float* r=malloc(sizeof(float)); *r = (b==0)?0.0f:fmodf(a,b); return nuevoValorResultado(r, FLOAT);} 
// Nota: versiones que retornan DOUBLE ya declaradas arriba (moduloCharDouble/moduloDoubleChar)

Operacion tablaOperacionesModulo[TIPO_COUNT][TIPO_COUNT] = {
    [INT][INT] = moduloIntInt,
    [FLOAT][FLOAT] = moduloFloatFloat,
    [INT][FLOAT] = moduloIntFloat,
    [FLOAT][INT] = moduloFloatInt,
    // Aliases enteros
    [BYTE][BYTE] = moduloIntInt,
    [BYTE][SHORT] = moduloIntInt,
    [BYTE][INT] = moduloIntInt,
    [BYTE][LONG] = moduloIntInt,
    [SHORT][BYTE] = moduloIntInt,
    [SHORT][SHORT] = moduloIntInt,
    [SHORT][INT] = moduloIntInt,
    [SHORT][LONG] = moduloIntInt,
    [LONG][BYTE] = moduloIntInt,
    [LONG][SHORT] = moduloIntInt,
    [LONG][INT] = moduloIntInt,
    [LONG][LONG] = moduloIntInt,
    // Enteros con FLOAT
    [BYTE][FLOAT] = moduloIntFloat,
    [SHORT][FLOAT] = moduloIntFloat,
    [INT][FLOAT] = moduloIntFloat,
    [LONG][FLOAT] = moduloIntFloat,
    [FLOAT][BYTE] = moduloFloatInt,
    [FLOAT][SHORT] = moduloFloatInt,
    [FLOAT][INT] = moduloFloatInt,
    [FLOAT][LONG] = moduloFloatInt,
    // DOUBLE combinaciones
    [INT][DOUBLE] = moduloIntDouble,
    [BYTE][DOUBLE] = moduloIntDouble,
    [SHORT][DOUBLE] = moduloIntDouble,
    [LONG][DOUBLE] = moduloIntDouble,
    [FLOAT][DOUBLE] = moduloFloatDouble,
    [DOUBLE][INT] = moduloDoubleInt,
    [DOUBLE][BYTE] = moduloDoubleInt,
    [DOUBLE][SHORT] = moduloDoubleInt,
    [DOUBLE][LONG] = moduloDoubleInt,
    [DOUBLE][FLOAT] = moduloDoubleFloat,
    [DOUBLE][DOUBLE] = moduloDoubleDouble,
    // CHAR
    [CHAR][CHAR] = moduloCharChar,
    [CHAR][INT] = moduloCharInt,
    [INT][CHAR] = moduloIntChar,
    [CHAR][FLOAT] = moduloCharFloat,
    [FLOAT][CHAR] = moduloFloatChar,
    [CHAR][DOUBLE] = moduloCharDouble,
    [DOUBLE][CHAR] = moduloDoubleChar,
};

AbstractExpresion* nuevoModuloExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha) {
    ExpresionLenguaje* moduloExpresion = nuevoExpresionLenguaje(interpretExpresionLenguaje, izquierda, derecha);
    moduloExpresion->tablaOperaciones = &tablaOperacionesModulo;
    return (AbstractExpresion*) moduloExpresion;
}
