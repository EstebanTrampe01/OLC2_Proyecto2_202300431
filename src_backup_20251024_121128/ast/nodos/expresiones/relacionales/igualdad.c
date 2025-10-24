// Igualdad ==
#include "relacionales.h"
#include <stdlib.h>
#include <string.h>

// INT / FLOAT / DOUBLE cross
Result igualdadIntInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor)==*((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadIntFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor)==*((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadFloatInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor)==*((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadFloatFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor)==*((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadIntDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor)==*((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadDoubleInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor)==*((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadFloatDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor)==*((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadDoubleFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor)==*((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadDoubleDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor)==*((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 

Result igualdadBooleanBoolean(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor)==*((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadCharChar(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((char*)s->izquierda.valor)==*((char*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result igualdadStringString(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=(strcmp((char*)s->izquierda.valor,(char*)s->derecha.valor)==0);return nuevoValorResultado(r,BOOLEAN);} 

Operacion tablaOperacionesIgualdad[TIPO_COUNT][TIPO_COUNT]={
	[INT][INT]=igualdadIntInt,
	[INT][FLOAT]=igualdadIntFloat,
	[INT][DOUBLE]=igualdadIntDouble,
	[FLOAT][INT]=igualdadFloatInt,
	[FLOAT][FLOAT]=igualdadFloatFloat,
	[FLOAT][DOUBLE]=igualdadFloatDouble,
	[DOUBLE][INT]=igualdadDoubleInt,
	[DOUBLE][FLOAT]=igualdadDoubleFloat,
	[DOUBLE][DOUBLE]=igualdadDoubleDouble,
	[BOOLEAN][BOOLEAN]=igualdadBooleanBoolean,
	[CHAR][CHAR]=igualdadCharChar,
	[STRING][STRING]=igualdadStringString,
};

AbstractExpresion* nuevoIgualdadExpresion(AbstractExpresion* izq, AbstractExpresion* der){
	ExpresionLenguaje* n = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der);
	n->tablaOperaciones=&tablaOperacionesIgualdad;return (AbstractExpresion*)n; }
