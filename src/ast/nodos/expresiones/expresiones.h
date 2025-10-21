#ifndef EXPRESIONES_H
#define EXPRESIONES_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef enum {
    SUMA,
    RESTA,
    MULTIPLICACION,
    DIVISION,
    MODULO,
    MENOR_QUE,
    MAYOR_QUE,
    MENOR_IGUAL,
    MAYOR_IGUAL,
    IGUALDAD,
    DESIGUALDAD,
    AND,
    OR,
    NOT,
    BIT_AND,
    BIT_OR,
    BIT_XOR,
    SHIFT_LEFT,
    SHIFT_RIGHT,
    MENOS
} TipoOperacion;

typedef struct ExpresionLenguaje ExpresionLenguaje;
typedef Result (*Operacion)(ExpresionLenguaje*);

struct ExpresionLenguaje{
    AbstractExpresion base;
    Result izquierda;
    Result derecha;
    Operacion (*tablaOperaciones)[TIPO_COUNT][TIPO_COUNT];
    TipoOperacion tipo;
};


//interpret basico de expresiones
Result interpretExpresionLenguaje(AbstractExpresion* self, Context* context);
Result interpretUnarioLenguaje(AbstractExpresion* self, Context* context);
//constructor
ExpresionLenguaje* nuevoExpresionLenguaje(Interpret funcionEspecifica, AbstractExpresion* izquierda, AbstractExpresion* derecha);

void calcularResultadoIzquierdo(ExpresionLenguaje* self, Context* context);
void calcularResultadoDerecho(ExpresionLenguaje* self, Context* context);
void calcularResultados(ExpresionLenguaje* self, Context* context);
#endif