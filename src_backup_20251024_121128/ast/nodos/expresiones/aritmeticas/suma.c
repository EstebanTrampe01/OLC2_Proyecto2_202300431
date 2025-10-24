#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "aritmeticas.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "context/format_utils.h"
#include "context/format_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Result sumarIntInt(ExpresionLenguaje* self) {
    int* res = malloc(sizeof(int));
    *res =  *((int*)self->izquierda.valor) + *((int*)self->derecha.valor);
    // fprintf(stderr, "[DBG SUM] %d + %d = %d\n", *((int*)self->izquierda.valor), *((int*)self->derecha.valor), *res);
    return nuevoValorResultado(res, INT);
}

Result sumarFloatFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((float*)self->izquierda.valor) + *((float*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}

Result sumarIntFloat(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((int*)self->izquierda.valor) + *((float*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}

Result sumarFloatInt(ExpresionLenguaje* self) {
    float* res = malloc(sizeof(float));
    *res = *((float*)self->izquierda.valor) + *((int*)self->derecha.valor);
    return nuevoValorResultado(res, FLOAT);
}
// --- NUEVAS FUNCIONES DOUBLE ---
static Result sumarIntDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = (double)(*((int*)self->izquierda.valor)) + *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result sumarDoubleInt(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = *((double*)self->izquierda.valor) + (double)(*((int*)self->derecha.valor)); return nuevoValorResultado(r, DOUBLE);} 
static Result sumarFloatDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = (double)(*((float*)self->izquierda.valor)) + *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 
static Result sumarDoubleFloat(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = *((double*)self->izquierda.valor) + (double)(*((float*)self->derecha.valor)); return nuevoValorResultado(r, DOUBLE);} 
static Result sumarDoubleDouble(ExpresionLenguaje* self){ double* r=malloc(sizeof(double)); *r = *((double*)self->izquierda.valor) + *((double*)self->derecha.valor); return nuevoValorResultado(r, DOUBLE);} 

Result sumarStringString(ExpresionLenguaje* self) {
    char* left = (char*)self->izquierda.valor;
    char* right = (char*)self->derecha.valor;
    if(!left) { left = "null"; }
    if(!right) { right = "null"; }
    size_t len = strlen(left) + strlen(right) + 1;
    char* res = malloc(len);
    strcpy(res, left);
    strcat(res, right);
    return nuevoValorResultado(res, STRING);
}

Result sumarStringInt(ExpresionLenguaje* self) {
    char* left = (char*)self->izquierda.valor;
    int right = *(int*)self->derecha.valor;
    char buf[32];
    sprintf(buf, "%d", right);
    if(!left) { left = "null"; }
    size_t len = strlen(left) + strlen(buf) + 1;
    char* res = malloc(len);
    strcpy(res, left);
    strcat(res, buf);
    return nuevoValorResultado(res, STRING);
}

Result sumarStringFloat(ExpresionLenguaje* self) {
    char* left = (char*)self->izquierda.valor;
    if(!left) left = "null";
    float right = *(float*)self->derecha.valor;
    const char* num = format_trim_float(right, 6);
    size_t len = strlen(left) + strlen(num) + 1;
    char* res = malloc(len);
    strcpy(res, left);
    strcat(res, num);
    return nuevoValorResultado(res, STRING);
}
Result sumarStringDouble(ExpresionLenguaje* self) {
    char* left = (char*)self->izquierda.valor;
    if(!left) left = "null";
    double right = *(double*)self->derecha.valor;
    const char* num = format_trim_double(right, 10);
    size_t len = strlen(left) + strlen(num) + 1;
    char* res = malloc(len);
    strcpy(res, left);
    strcat(res, num);
    return nuevoValorResultado(res, STRING);
}

Result sumarStringBoolean(ExpresionLenguaje* self) {
    char* left = (char*)self->izquierda.valor;
    int right = *(int*)self->derecha.valor;
    char* boolStr = right ? "true" : "false";
    size_t len = strlen(left) + strlen(boolStr) + 1;
    char* res = malloc(len);
    strcpy(res, left);
    strcat(res, boolStr);
    return nuevoValorResultado(res, STRING);
}

Result sumarStringChar(ExpresionLenguaje* self) {
    char* left = (char*)self->izquierda.valor;
    unsigned char right = *(unsigned char*)self->derecha.valor;
    const char* rep = format_char(right);
    size_t len = strlen(left) + strlen(rep) + 1;
    char* res = malloc(len);
    strcpy(res, left);
    strcat(res, rep);
    return nuevoValorResultado(res, STRING);
}

Result sumarIntString(ExpresionLenguaje* self) {
    int left = *(int*)self->izquierda.valor;
    char* right = (char*)self->derecha.valor;
    if(!right) { right = "null"; }
    char buf[32];
    sprintf(buf, "%d", left);
    size_t len = strlen(buf) + strlen(right) + 1;
    char* res = malloc(len);
    strcpy(res, buf);
    strcat(res, right);
    return nuevoValorResultado(res, STRING);
}

Result sumarFloatString(ExpresionLenguaje* self) {
    float left = *(float*)self->izquierda.valor;
    char* right = (char*)self->derecha.valor;
    if(!right) right = "null";
    const char* num = format_trim_float(left, 6);
    size_t len = strlen(num) + strlen(right) + 1;
    char* res = malloc(len);
    strcpy(res, num);
    strcat(res, right);
    return nuevoValorResultado(res, STRING);
}
Result sumarDoubleString(ExpresionLenguaje* self) {
    double left = *(double*)self->izquierda.valor;
    char* right = (char*)self->derecha.valor; 
    if(!right) right = "null";
    const char* num = format_trim_double(left, 10);
    size_t len = strlen(num) + strlen(right) + 1;
    char* res = malloc(len);
    strcpy(res, num);
    strcat(res, right);
    return nuevoValorResultado(res, STRING);
}

Result sumarBooleanString(ExpresionLenguaje* self) {
    int left = *(int*)self->izquierda.valor;
    char* right = (char*)self->derecha.valor;
    char* boolStr = left ? "true" : "false";
    size_t len = strlen(boolStr) + strlen(right) + 1;
    char* res = malloc(len);
    strcpy(res, boolStr);
    strcat(res, right);
    return nuevoValorResultado(res, STRING);
}

Result sumarCharString(ExpresionLenguaje* self) {
    unsigned char left = *(unsigned char*)self->izquierda.valor;
    char* right = (char*)self->derecha.valor;
    const char* rep = format_char(left);
    size_t len = strlen(rep) + strlen(right) + 1;
    char* res = malloc(len);
    strcpy(res, rep);
    strcat(res, right);
    return nuevoValorResultado(res, STRING);
}

static Result sumarCharChar(ExpresionLenguaje* self){
    /* Ahora permitimos overflow natural del tipo char (comportamiento implícito C) y valores intermedios fuera de 0-255.
       Se conserva almacenamiento como char; impresión mostrará el código numérico bruto. */
    int a = (int)(*((unsigned char*)self->izquierda.valor));
    int b = (int)(*((unsigned char*)self->derecha.valor));
    int s = a + b; /* se truncará al guardar en char */
    char* res = malloc(sizeof(char));
    *res = (char)s;
    return nuevoValorResultado(res, CHAR);
} 
static Result sumarCharInt(ExpresionLenguaje* self){ int* res=malloc(sizeof(int)); *res = (int)(*((char*)self->izquierda.valor)) + *((int*)self->derecha.valor); return nuevoValorResultado(res, INT);} 
static Result sumarIntChar(ExpresionLenguaje* self){ int* res=malloc(sizeof(int)); *res = *((int*)self->izquierda.valor) + (int)(*((char*)self->derecha.valor)); return nuevoValorResultado(res, INT);} 
static Result sumarCharFloat(ExpresionLenguaje* self){ float* res=malloc(sizeof(float)); *res = (float)(*((char*)self->izquierda.valor)) + *((float*)self->derecha.valor); return nuevoValorResultado(res, FLOAT);} 
static Result sumarFloatChar(ExpresionLenguaje* self){ float* res=malloc(sizeof(float)); *res = *((float*)self->izquierda.valor) + (float)(*((char*)self->derecha.valor)); return nuevoValorResultado(res, FLOAT);} 
static Result sumarCharDouble(ExpresionLenguaje* self){ double* res=malloc(sizeof(double)); *res = (double)(*((char*)self->izquierda.valor)) + *((double*)self->derecha.valor); return nuevoValorResultado(res, DOUBLE);} 
static Result sumarDoubleChar(ExpresionLenguaje* self){ double* res=malloc(sizeof(double)); *res = *((double*)self->izquierda.valor) + (double)(*((char*)self->derecha.valor)); return nuevoValorResultado(res, DOUBLE);} 

Operacion tablaOperacionesSuma[TIPO_COUNT][TIPO_COUNT] = {
    [INT][INT] = sumarIntInt,
    [FLOAT][FLOAT] = sumarFloatFloat,
    [INT][FLOAT] = sumarIntFloat,
    [FLOAT][INT] = sumarFloatInt,
    [STRING][STRING] = sumarStringString,
    [STRING][INT] = sumarStringInt,
    [STRING][FLOAT] = sumarStringFloat,
    [STRING][DOUBLE] = sumarStringDouble,
    [STRING][BOOLEAN] = sumarStringBoolean,
    [STRING][CHAR] = sumarStringChar,
    [INT][STRING] = sumarIntString,
    [FLOAT][STRING] = sumarFloatString,
    [BOOLEAN][STRING] = sumarBooleanString,
    [CHAR][STRING] = sumarCharString,
    [CHAR][CHAR] = sumarCharChar,
    [CHAR][INT] = sumarCharInt,
    [INT][CHAR] = sumarIntChar,
    [CHAR][FLOAT] = sumarCharFloat,
    [FLOAT][CHAR] = sumarFloatChar,
    [CHAR][DOUBLE] = sumarCharDouble,
    [DOUBLE][CHAR] = sumarDoubleChar,
    // Mapeo de tipos conceptuales a tipos internos
    [BYTE][BYTE] = sumarIntInt,
    [BYTE][SHORT] = sumarIntInt,
    [BYTE][INT] = sumarIntInt,
    [BYTE][LONG] = sumarIntInt,
    [BYTE][FLOAT] = sumarIntFloat,
    [BYTE][DOUBLE] = sumarIntDouble,
    [SHORT][BYTE] = sumarIntInt,
    [SHORT][SHORT] = sumarIntInt,
    [SHORT][INT] = sumarIntInt,
    [SHORT][LONG] = sumarIntInt,
    [SHORT][FLOAT] = sumarIntFloat,
    [SHORT][DOUBLE] = sumarIntDouble,
    [LONG][BYTE] = sumarIntInt,
    [LONG][SHORT] = sumarIntInt,
    [LONG][INT] = sumarIntInt,
    [LONG][LONG] = sumarIntInt,
    [LONG][FLOAT] = sumarIntFloat,
    [LONG][DOUBLE] = sumarIntDouble,
    [DOUBLE][BYTE] = sumarDoubleInt,
    [DOUBLE][SHORT] = sumarDoubleInt,
    [DOUBLE][INT] = sumarDoubleInt,
    [DOUBLE][LONG] = sumarDoubleInt,
    [DOUBLE][FLOAT] = sumarDoubleFloat,
    [DOUBLE][DOUBLE] = sumarDoubleDouble,
    [INT][BYTE] = sumarIntInt,
    [INT][SHORT] = sumarIntInt,
    [INT][LONG] = sumarIntInt,
    [INT][DOUBLE] = sumarIntDouble,
    [FLOAT][BYTE] = sumarFloatInt,
    [FLOAT][SHORT] = sumarFloatInt,
    [FLOAT][LONG] = sumarFloatInt,
    [FLOAT][DOUBLE] = sumarFloatDouble,
    [DOUBLE][STRING] = sumarDoubleString,
    // (ya cubierto arriba) [DOUBLE][LONG] duplicado eliminado
    [STRING][BYTE] = sumarStringInt,
    [STRING][SHORT] = sumarStringInt,
    [STRING][LONG] = sumarStringInt,
    [BYTE][STRING] = sumarIntString,
    [SHORT][STRING] = sumarIntString,
    [LONG][STRING] = sumarIntString,
};

//builders.h
AbstractExpresion* nuevoSumaExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha) {
    ExpresionLenguaje* sumaExpresion = nuevoExpresionLenguaje(interpretExpresionLenguaje, izquierda, derecha);
    sumaExpresion->tablaOperaciones = &tablaOperacionesSuma;
    return (AbstractExpresion*) sumaExpresion;
}
