// Mayor que >
#include "relacionales.h"
#include <stdlib.h>

Result mayorQueIntInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) > *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorQueIntFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) > *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorQueFloatInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) > *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorQueFloatFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) > *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorQueIntDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor) > *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorQueDoubleInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) > *((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorQueFloatDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor) > *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorQueDoubleFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) > *((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorQueDoubleDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor) > *((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result mayorQueCharChar(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((char*)s->izquierda.valor) > *((char*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 

Operacion tablaOperacionesMayorQue[TIPO_COUNT][TIPO_COUNT]={
	[INT][INT]=mayorQueIntInt,
	[INT][FLOAT]=mayorQueIntFloat,
	[INT][DOUBLE]=mayorQueIntDouble,
	[FLOAT][INT]=mayorQueFloatInt,
	[FLOAT][FLOAT]=mayorQueFloatFloat,
	[FLOAT][DOUBLE]=mayorQueFloatDouble,
	[DOUBLE][INT]=mayorQueDoubleInt,
	[DOUBLE][FLOAT]=mayorQueDoubleFloat,
	[DOUBLE][DOUBLE]=mayorQueDoubleDouble,
	[CHAR][CHAR]=mayorQueCharChar,
};

AbstractExpresion* nuevoMayorQueExpresion(AbstractExpresion* izq, AbstractExpresion* der){
	ExpresionLenguaje* n = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der);
	n->tablaOperaciones=&tablaOperacionesMayorQue;return (AbstractExpresion*)n; }
// archivo vacío intencional (implementaciones en relacionales.c)