#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "aritmeticas.h"
#include "ast/nodos/expresiones/expresiones.h"

#include <stdlib.h>
#include <stdio.h>

/* Bitwise AND */
Result bitAndIntInt(ExpresionLenguaje* self){ int* r=malloc(sizeof(int)); *r=*((int*)self->izquierda.valor) & *((int*)self->derecha.valor); return nuevoValorResultado(r, INT);} 
/* Bitwise OR */
Result bitOrIntInt(ExpresionLenguaje* self){ int* r=malloc(sizeof(int)); *r=*((int*)self->izquierda.valor) | *((int*)self->derecha.valor); return nuevoValorResultado(r, INT);} 
/* Bitwise XOR */
Result bitXorIntInt(ExpresionLenguaje* self){ int* r=malloc(sizeof(int)); *r=*((int*)self->izquierda.valor) ^ *((int*)self->derecha.valor); return nuevoValorResultado(r, INT);} 
/* Shift Left */
Result shiftLeftIntInt(ExpresionLenguaje* self){ int* r=malloc(sizeof(int)); *r=*((int*)self->izquierda.valor) << (*((int*)self->derecha.valor)&31); return nuevoValorResultado(r, INT);} 
/* Shift Right (aritmético) */
Result shiftRightIntInt(ExpresionLenguaje* self){ int left=*((int*)self->izquierda.valor); int right=(*((int*)self->derecha.valor)&31); int* r=malloc(sizeof(int)); *r= left >> right; return nuevoValorResultado(r, INT);} 

Operacion tablaOperacionesBitAnd[TIPO_COUNT][TIPO_COUNT] = {
    [INT][INT] = bitAndIntInt,
};
Operacion tablaOperacionesBitOr[TIPO_COUNT][TIPO_COUNT] = {
    [INT][INT] = bitOrIntInt,
};
Operacion tablaOperacionesBitXor[TIPO_COUNT][TIPO_COUNT] = {
    [INT][INT] = bitXorIntInt,
};
Operacion tablaOperacionesShiftLeft[TIPO_COUNT][TIPO_COUNT] = {
    [INT][INT] = shiftLeftIntInt,
};
Operacion tablaOperacionesShiftRight[TIPO_COUNT][TIPO_COUNT] = {
    [INT][INT] = shiftRightIntInt,
};

AbstractExpresion* nuevoBitAndExpresion(AbstractExpresion* izq, AbstractExpresion* der){ ExpresionLenguaje* e = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der); e->tablaOperaciones=&tablaOperacionesBitAnd; return (AbstractExpresion*)e; }
AbstractExpresion* nuevoBitOrExpresion(AbstractExpresion* izq, AbstractExpresion* der){ ExpresionLenguaje* e = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der); e->tablaOperaciones=&tablaOperacionesBitOr; return (AbstractExpresion*)e; }
AbstractExpresion* nuevoBitXorExpresion(AbstractExpresion* izq, AbstractExpresion* der){ ExpresionLenguaje* e = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der); e->tablaOperaciones=&tablaOperacionesBitXor; return (AbstractExpresion*)e; }
AbstractExpresion* nuevoShiftLeftExpresion(AbstractExpresion* izq, AbstractExpresion* der){ ExpresionLenguaje* e = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der); e->tablaOperaciones=&tablaOperacionesShiftLeft; return (AbstractExpresion*)e; }
AbstractExpresion* nuevoShiftRightExpresion(AbstractExpresion* izq, AbstractExpresion* der){ ExpresionLenguaje* e = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der); e->tablaOperaciones=&tablaOperacionesShiftRight; return (AbstractExpresion*)e; }
