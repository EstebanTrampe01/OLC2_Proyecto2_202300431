#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "aritmeticas.h"
#include "ast/nodos/expresiones/expresiones.h"

#include <stdlib.h>
#include <stdio.h>

Result restaIntInt(ExpresionLenguaje* self) {
    int* res = malloc(sizeof(int));
    *res = *((int*)self->izquierda.valor) - *((int*)self->derecha.valor);
    return nuevoValorResultado(res, INT);
}

Result restaFloatFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((float*)self->izquierda.valor) - *((float*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}

Result restaIntFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((int*)self->izquierda.valor) - *((float*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}

Result restaFloatInt(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((float*)self->izquierda.valor) - *((int*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}
// DOUBLE handlers (resultados siempre DOUBLE si participa DOUBLE)
static Result restaIntDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = (double)(*((int*)self->izquierda.valor)) - *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result restaDoubleInt(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = *((double*)self->izquierda.valor) - (double)(*((int*)self->derecha.valor)); return nuevoValorResultado(r, DOUBLE);} 
static Result restaFloatDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = (double)(*((float*)self->izquierda.valor)) - *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result restaDoubleFloat(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = *((double*)self->izquierda.valor) - (double)(*((float*)self->derecha.valor)); return nuevoValorResultado(r, DOUBLE);} 
static Result restaDoubleDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = *((double*)self->izquierda.valor) - *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result restaCharDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = (double)(*((char*)self->izquierda.valor)) - *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result restaDoubleChar(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = *((double*)self->izquierda.valor) - (double)(*((char*)self->derecha.valor)); return nuevoValorResultado(r, DOUBLE);} 


// CHAR wrappers (similar a suma) ---------------------
static Result restaCharChar(ExpresionLenguaje* self){
    /* Se elimina validación de rango; resultado se trunca al rango del char subyacente. */
    int left  = (int)(*((unsigned char*)self->izquierda.valor));
    int right = (int)(*((unsigned char*)self->derecha.valor));
    int diff = left - right;
    char* r = malloc(sizeof(char));
    *r = (char)diff;
    return nuevoValorResultado(r, CHAR);
} 
static Result restaCharInt(ExpresionLenguaje* self){ int* r = malloc(sizeof(int)); *r = (int)(*((char*)self->izquierda.valor)) - *((int*)self->derecha.valor); return nuevoValorResultado(r, INT);} 
static Result restaIntChar(ExpresionLenguaje* self){ int* r = malloc(sizeof(int)); *r = *((int*)self->izquierda.valor) - (int)(*((char*)self->derecha.valor)); return nuevoValorResultado(r, INT);} 
static Result restaCharFloat(ExpresionLenguaje* self){ float* r = malloc(sizeof(float)); *r = (float)(*((char*)self->izquierda.valor)) - *((float*)self->derecha.valor); return nuevoValorResultado(r, FLOAT);} 
static Result restaFloatChar(ExpresionLenguaje* self){ float* r = malloc(sizeof(float)); *r = *((float*)self->izquierda.valor) - (float)(*((char*)self->derecha.valor)); return nuevoValorResultado(r, FLOAT);} 
// Nota: char+double ya definido arriba devolviendo DOUBLE

// Reinsert table with CHAR mappings at end to avoid large mid-table edit
Operacion tablaOperacionesResta[TIPO_COUNT][TIPO_COUNT] = {
    // Base INT/FLOAT
    [INT][INT] = restaIntInt,
    [FLOAT][FLOAT] = restaFloatFloat,
    [INT][FLOAT] = restaIntFloat,
    [FLOAT][INT] = restaFloatInt,
    // Aliases numéricos (BYTE/SHORT/LONG se tratan como INT)
    [BYTE][BYTE] = restaIntInt,
    [BYTE][SHORT] = restaIntInt,
    [BYTE][INT] = restaIntInt,
    [BYTE][LONG] = restaIntInt,
    [SHORT][BYTE] = restaIntInt,
    [SHORT][SHORT] = restaIntInt,
    [SHORT][INT] = restaIntInt,
    [SHORT][LONG] = restaIntInt,
    [LONG][BYTE] = restaIntInt,
    [LONG][SHORT] = restaIntInt,
    [LONG][INT] = restaIntInt,
    [LONG][LONG] = restaIntInt,
    // INT family con FLOAT
    [BYTE][FLOAT] = restaIntFloat,
    [SHORT][FLOAT] = restaIntFloat,
    [INT][FLOAT] = restaIntFloat,
    [LONG][FLOAT] = restaIntFloat,
    [FLOAT][BYTE] = restaFloatInt,
    [FLOAT][SHORT] = restaFloatInt,
    [FLOAT][INT] = restaFloatInt,
    [FLOAT][LONG] = restaFloatInt,
    // DOUBLE combinaciones
    [INT][DOUBLE] = restaIntDouble,
    [BYTE][DOUBLE] = restaIntDouble,
    [SHORT][DOUBLE] = restaIntDouble,
    [LONG][DOUBLE] = restaIntDouble,
    [FLOAT][DOUBLE] = restaFloatDouble,
    [DOUBLE][INT] = restaDoubleInt,
    [DOUBLE][BYTE] = restaDoubleInt,
    [DOUBLE][SHORT] = restaDoubleInt,
    [DOUBLE][LONG] = restaDoubleInt,
    [DOUBLE][FLOAT] = restaDoubleFloat,
    [DOUBLE][DOUBLE] = restaDoubleDouble,
    // CHAR combinaciones
    [CHAR][CHAR] = restaCharChar,
    [CHAR][INT] = restaCharInt,
    [INT][CHAR] = restaIntChar,
    [CHAR][FLOAT] = restaCharFloat,
    [FLOAT][CHAR] = restaFloatChar,
    [CHAR][DOUBLE] = restaCharDouble,
    [DOUBLE][CHAR] = restaDoubleChar,
};

//builders.h
AbstractExpresion* nuevoRestaExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha) {
    ExpresionLenguaje* restaExpresion = nuevoExpresionLenguaje(interpretExpresionLenguaje, izquierda, derecha);
    restaExpresion->tablaOperaciones = &tablaOperacionesResta;
    return (AbstractExpresion*) restaExpresion;
}
