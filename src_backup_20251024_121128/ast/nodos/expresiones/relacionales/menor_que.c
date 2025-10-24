// Menor que <
#include "relacionales.h"
#include <stdlib.h>

Result menorQueIntInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) < *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorQueIntFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) < *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorQueFloatInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) < *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorQueFloatFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) < *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorQueIntDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) < *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorQueDoubleInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) < *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorQueFloatDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) < *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorQueDoubleFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) < *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorQueDoubleDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) < *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorQueCharChar(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((char*)s->izquierda.valor) < *((char*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 

Operacion tablaOperacionesMenorQue[TIPO_COUNT][TIPO_COUNT]={
	[INT][INT]=menorQueIntInt,
	[INT][FLOAT]=menorQueIntFloat,
	[INT][DOUBLE]=menorQueIntDouble,
	[FLOAT][INT]=menorQueFloatInt,
	[FLOAT][FLOAT]=menorQueFloatFloat,
	[FLOAT][DOUBLE]=menorQueFloatDouble,
	[DOUBLE][INT]=menorQueDoubleInt,
	[DOUBLE][FLOAT]=menorQueDoubleFloat,
	[DOUBLE][DOUBLE]=menorQueDoubleDouble,
	[CHAR][CHAR]=menorQueCharChar,
};

AbstractExpresion* nuevoMenorQueExpresion(AbstractExpresion* izq, AbstractExpresion* der){
	ExpresionLenguaje* n = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der);
	n->tablaOperaciones=&tablaOperacionesMenorQue;return (AbstractExpresion*)n; }
