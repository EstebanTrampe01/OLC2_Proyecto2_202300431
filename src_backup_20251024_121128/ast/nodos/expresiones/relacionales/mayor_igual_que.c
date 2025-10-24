// Mayor o igual >=
#include "relacionales.h"
#include <stdlib.h>

Result mayorIgualQueIntInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) >= *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorIgualQueIntFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) >= *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorIgualQueFloatInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) >= *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorIgualQueFloatFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) >= *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorIgualQueIntDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) >= *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorIgualQueDoubleInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) >= *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorIgualQueFloatDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) >= *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorIgualQueDoubleFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) >= *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorIgualQueDoubleDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) >= *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorIgualQueCharChar(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((char*)s->izquierda.valor) >= *((char*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 

Operacion tablaOperacionesMayorIgualQue[TIPO_COUNT][TIPO_COUNT]={
	[INT][INT]=mayorIgualQueIntInt,
	[INT][FLOAT]=mayorIgualQueIntFloat,
	[INT][DOUBLE]=mayorIgualQueIntDouble,
	[FLOAT][INT]=mayorIgualQueFloatInt,
	[FLOAT][FLOAT]=mayorIgualQueFloatFloat,
	[FLOAT][DOUBLE]=mayorIgualQueFloatDouble,
	[DOUBLE][INT]=mayorIgualQueDoubleInt,
	[DOUBLE][FLOAT]=mayorIgualQueDoubleFloat,
	[DOUBLE][DOUBLE]=mayorIgualQueDoubleDouble,
	[CHAR][CHAR]=mayorIgualQueCharChar,
};

AbstractExpresion* nuevoMayorIgualQueExpresion(AbstractExpresion* izq, AbstractExpresion* der){
	ExpresionLenguaje* n = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der);
	n->tablaOperaciones=&tablaOperacionesMayorIgualQue;return (AbstractExpresion*)n; }
