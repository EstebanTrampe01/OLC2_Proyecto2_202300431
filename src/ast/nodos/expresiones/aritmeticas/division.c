#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "aritmeticas.h"
#include "ast/nodos/expresiones/expresiones.h"

#include <stdlib.h>
#include <stdio.h>

Result dividirIntInt(ExpresionLenguaje* self) {
    int left = *((int*)self->izquierda.valor);
    int right = *((int*)self->derecha.valor);
    if(right==0){ int* z=malloc(sizeof(int)); *z=0; return nuevoValorResultado(z, INT);} /* evitar división por cero */
    int* res = malloc(sizeof(int));
    *res = left / right; /* división entera */
    return nuevoValorResultado(res, INT);
}

Result dividirFloatFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((float*)self->izquierda.valor) / *((float*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}

Result dividirIntFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((int*)self->izquierda.valor) / *((float*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}

Result dividirFloatInt(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((float*)self->izquierda.valor) / *((int*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}
// DOUBLE handlers
static Result dividirIntDouble(ExpresionLenguaje* self){ double a = (double)(*((int*)self->izquierda.valor)); double b = *((double*)self->derecha.valor); double* r=malloc(sizeof(double)); *r = b==0?0:a/b; return nuevoValorResultado(r, DOUBLE);} 
static Result dividirDoubleInt(ExpresionLenguaje* self){ double a = *((double*)self->izquierda.valor); double b = (double)(*((int*)self->derecha.valor)); double* r=malloc(sizeof(double)); *r = b==0?0:a/b; return nuevoValorResultado(r, DOUBLE);} 
static Result dividirFloatDouble(ExpresionLenguaje* self){ double a = (double)(*((float*)self->izquierda.valor)); double b = *((double*)self->derecha.valor); double* r=malloc(sizeof(double)); *r = b==0?0:a/b; return nuevoValorResultado(r, DOUBLE);} 
static Result dividirDoubleFloat(ExpresionLenguaje* self){ double a = *((double*)self->izquierda.valor); double b = (double)(*((float*)self->derecha.valor)); double* r=malloc(sizeof(double)); *r = b==0?0:a/b; return nuevoValorResultado(r, DOUBLE);} 
static Result dividirDoubleDouble(ExpresionLenguaje* self){ double a = *((double*)self->izquierda.valor); double b = *((double*)self->derecha.valor); if(b==0){ float* r=malloc(sizeof(float)); *r=0; return nuevoValorResultado(r, FLOAT);} double* r=malloc(sizeof(double)); *r=a/b; return nuevoValorResultado(r, DOUBLE);} 
static Result dividirCharDouble(ExpresionLenguaje* self){ double a=(double)(*((char*)self->izquierda.valor)); double b=*((double*)self->derecha.valor); double* r=malloc(sizeof(double)); *r=b==0?0:a/b; return nuevoValorResultado(r, DOUBLE);} 
static Result dividirDoubleChar(ExpresionLenguaje* self){ double a=*((double*)self->izquierda.valor); double b=(double)(*((char*)self->derecha.valor)); double* r=malloc(sizeof(double)); *r=b==0?0:a/b; return nuevoValorResultado(r, DOUBLE);} 


// Wrappers CHAR division
static Result dividirCharChar(ExpresionLenguaje* self){
    int a = (int)(*((unsigned char*)self->izquierda.valor));
    int b = (int)(*((unsigned char*)self->derecha.valor));
    if(b==0){
        add_error_msg("División char-char por cero");
        return nuevoValorResultadoVacio();
    }
    int q = a / b; /* truncamiento posterior */
    char* r = malloc(sizeof(char));
    *r = (char)q;
    return nuevoValorResultado(r, CHAR);
} 
static Result dividirCharInt(ExpresionLenguaje* self){ int a=(int)(*((char*)self->izquierda.valor)); int b=*((int*)self->derecha.valor); int* r=malloc(sizeof(int)); *r = b==0 ? 0 : a/b; return nuevoValorResultado(r, INT);} 
static Result dividirIntChar(ExpresionLenguaje* self){ int a=*((int*)self->izquierda.valor); int b=(int)(*((char*)self->derecha.valor)); int* r=malloc(sizeof(int)); *r = b==0 ? 0 : a/b; return nuevoValorResultado(r, INT);} 
static Result dividirCharFloat(ExpresionLenguaje* self){ float a=(float)(*((char*)self->izquierda.valor)); float b=*((float*)self->derecha.valor); float* r=malloc(sizeof(float)); *r = b==0 ? 0.0f : a/b; return nuevoValorResultado(r, FLOAT);} 
static Result dividirFloatChar(ExpresionLenguaje* self){ float a=*((float*)self->izquierda.valor); float b=(float)(*((char*)self->derecha.valor)); float* r=malloc(sizeof(float)); *r = b==0 ? 0.0f : a/b; return nuevoValorResultado(r, FLOAT);} 
// Nota: versiones CHAR/DOBLE ya definidas retornando DOUBLE arriba.

Operacion tablaOperacionesDivision[TIPO_COUNT][TIPO_COUNT] = {
    [INT][INT] = dividirIntInt,
    [FLOAT][FLOAT] = dividirFloatFloat,
    [INT][FLOAT] = dividirIntFloat,
    [FLOAT][INT] = dividirFloatInt,
    [BYTE][BYTE] = dividirIntInt,
    [BYTE][SHORT] = dividirIntInt,
    [BYTE][INT] = dividirIntInt,
    [BYTE][LONG] = dividirIntInt,
    [BYTE][FLOAT] = dividirIntFloat,
    /* BYTE con DOUBLE se maneja al final con [BYTE][DOUBLE]=dividirIntDouble para DOUBLE */
    [SHORT][BYTE] = dividirIntInt,
    [SHORT][SHORT] = dividirIntInt,
    [SHORT][INT] = dividirIntInt,
    [SHORT][LONG] = dividirIntInt,
    [SHORT][FLOAT] = dividirIntFloat,
    /* SHORT con DOUBLE mapeado a dividirIntDouble */
    [LONG][BYTE] = dividirIntInt,
    [LONG][SHORT] = dividirIntInt,
    [LONG][INT] = dividirIntInt,
    [LONG][LONG] = dividirIntInt,
    [LONG][FLOAT] = dividirIntFloat,
    /* LONG con DOUBLE mapeado a dividirIntDouble */
    [DOUBLE][BYTE] = dividirDoubleInt,
    [DOUBLE][SHORT] = dividirDoubleInt,
    [DOUBLE][INT] = dividirDoubleInt,
    [DOUBLE][LONG] = dividirDoubleInt,
    [DOUBLE][FLOAT] = dividirDoubleFloat,
    [DOUBLE][DOUBLE] = dividirDoubleDouble,
    [INT][BYTE] = dividirIntInt,
    [INT][SHORT] = dividirIntInt,
    [INT][LONG] = dividirIntInt,
    [FLOAT][BYTE] = dividirFloatInt,
    [FLOAT][SHORT] = dividirFloatInt,
    [FLOAT][LONG] = dividirFloatInt,
    [FLOAT][DOUBLE] = dividirFloatDouble,
    // CHAR
    [CHAR][CHAR] = dividirCharChar,
    [CHAR][INT] = dividirCharInt,
    [INT][CHAR] = dividirIntChar,
    [CHAR][FLOAT] = dividirCharFloat,
    [FLOAT][CHAR] = dividirFloatChar,
    [CHAR][DOUBLE] = dividirCharDouble,
    [DOUBLE][CHAR] = dividirDoubleChar,
    [INT][DOUBLE] = dividirIntDouble,
    [BYTE][DOUBLE] = dividirIntDouble,
    [SHORT][DOUBLE] = dividirIntDouble,
    [LONG][DOUBLE] = dividirIntDouble,
};

//builders.h
AbstractExpresion* nuevoDivisionExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha) {
    ExpresionLenguaje* divisionExpresion = nuevoExpresionLenguaje(interpretExpresionLenguaje, izquierda, derecha);
    divisionExpresion->tablaOperaciones = &tablaOperacionesDivision;
    return (AbstractExpresion*) divisionExpresion;
}
