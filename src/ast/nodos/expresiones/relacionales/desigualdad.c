// Desigualdad !=
#include "relacionales.h"
#include <stdlib.h>
#include <string.h>

Result desigualdadIntInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor)!=*((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadIntFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor)!=*((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadFloatInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor)!=*((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadFloatFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor)!=*((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadIntDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor)!=*((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadDoubleInt(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor)!=*((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadFloatDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((float*)s->izquierda.valor)!=*((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadDoubleFloat(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor)!=*((float*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadDoubleDouble(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((double*)s->izquierda.valor)!=*((double*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadBooleanBoolean(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((int*)s->izquierda.valor)!=*((int*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadCharChar(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=*((char*)s->izquierda.valor)!=*((char*)s->derecha.valor);return nuevoValorResultado(r,BOOLEAN);} 
Result desigualdadStringString(ExpresionLenguaje* s){int* r=malloc(sizeof(int));*r=(strcmp((char*)s->izquierda.valor,(char*)s->derecha.valor)!=0);return nuevoValorResultado(r,BOOLEAN);} 

Operacion tablaOperacionesDesigualdad[TIPO_COUNT][TIPO_COUNT]={
	[INT][INT]=desigualdadIntInt,
	[INT][FLOAT]=desigualdadIntFloat,
	[INT][DOUBLE]=desigualdadIntDouble,
	[FLOAT][INT]=desigualdadFloatInt,
	[FLOAT][FLOAT]=desigualdadFloatFloat,
	[FLOAT][DOUBLE]=desigualdadFloatDouble,
	[DOUBLE][INT]=desigualdadDoubleInt,
	[DOUBLE][FLOAT]=desigualdadDoubleFloat,
	[DOUBLE][DOUBLE]=desigualdadDoubleDouble,
	[BOOLEAN][BOOLEAN]=desigualdadBooleanBoolean,
	[CHAR][CHAR]=desigualdadCharChar,
	[STRING][STRING]=desigualdadStringString,
};

AbstractExpresion* nuevoDesigualdadExpresion(AbstractExpresion* izq, AbstractExpresion* der){
	ExpresionLenguaje* n = nuevoExpresionLenguaje(interpretExpresionLenguaje, izq, der);
	n->tablaOperaciones=&tablaOperacionesDesigualdad;return (AbstractExpresion*)n; }
