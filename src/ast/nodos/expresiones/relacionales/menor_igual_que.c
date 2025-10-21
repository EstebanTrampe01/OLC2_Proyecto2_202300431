// Menor o igual <=
#include "relacionales.h"
#include <stdlib.h>

Result menorIgualQueIntInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) <= *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorIgualQueIntFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) <= *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorIgualQueFloatInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) <= *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorIgualQueFloatFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) <= *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorIgualQueIntDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) <= *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorIgualQueDoubleInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) <= *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorIgualQueFloatDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) <= *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorIgualQueDoubleFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) <= *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorIgualQueDoubleDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) <= *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result menorIgualQueCharChar(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((char*)s->izquierda.valor) <= *((char*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 

Operacion tablaOperacionesMenorIgualQue[TIPO_COUNT][TIPO_COUNT]={
	[INT][INT]=menorIgualQueIntInt,
	[INT][FLOAT]=menorIgualQueIntFloat,
	[INT][DOUBLE]=menorIgualQueIntDouble,
	[FLOAT][INT]=menorIgualQueFloatInt,
	[FLOAT][FLOAT]=menorIgualQueFloatFloat,
	[FLOAT][DOUBLE]=menorIgualQueFloatDouble,
	[DOUBLE][INT]=menorIgualQueDoubleInt,
	[DOUBLE][FLOAT]=menorIgualQueDoubleFloat,
	[DOUBLE][DOUBLE]=menorIgualQueDoubleDouble,
	[CHAR][CHAR]=menorIgualQueCharChar,
};

AbstractExpresion* nuevoMenorIgualQueExpresion(AbstractExpresion* izq, AbstractExpresion* der){
	ExpresionLenguaje* n = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der);
	n->tablaOperaciones=&tablaOperacionesMenorIgualQue;return (AbstractExpresion*)n; }
