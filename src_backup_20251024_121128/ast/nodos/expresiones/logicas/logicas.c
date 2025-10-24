#include "logicas.h"
#include "../expresiones.h"
#include "../../../AbstractExpresion.h"
#include <stdlib.h>
#include <stdio.h>

/* AND LÓGICO (short-circuit manual, operandos ya evaluados) */
Result andBooleanBoolean(ExpresionLenguaje* self) {
    int* res = malloc(sizeof(int));
    int l = *((int*)self->izquierda.valor);
    if(!l){ *res = 0; return nuevoValorResultado(res, BOOLEAN);} // short-circuit
    int r = *((int*)self->derecha.valor);
    *res = (l && r);
    return nuevoValorResultado(res, BOOLEAN);
}

/* OR LÓGICO (short-circuit) */
Result orBooleanBoolean(ExpresionLenguaje* self) {
    int* res = malloc(sizeof(int));
    int l = *((int*)self->izquierda.valor);
    if(l){ *res = 1; return nuevoValorResultado(res, BOOLEAN);} // short-circuit
    int r = *((int*)self->derecha.valor);
    *res = (l || r);
    return nuevoValorResultado(res, BOOLEAN);
}

/* NOT LÓGICO */
Result notBoolean(ExpresionLenguaje* self) {
    int* res = malloc(sizeof(int));
    *res = !(*((int*)self->izquierda.valor));
    return nuevoValorResultado(res, BOOLEAN);
}

/* Tablas de operaciones para expresiones lógicas */

/* AND */
Operacion tablaOperacionesAnd[TIPO_COUNT][TIPO_COUNT] = {
    [BOOLEAN][BOOLEAN] = andBooleanBoolean,
};

/* OR */
Operacion tablaOperacionesOr[TIPO_COUNT][TIPO_COUNT] = {
    [BOOLEAN][BOOLEAN] = orBooleanBoolean,
};

/* NOT */
Operacion tablaOperacionesNot[TIPO_COUNT][TIPO_COUNT] = {
    [BOOLEAN][NULO] = notBoolean,
    /* int tratado como boolean */
    [INT][NULO] = notBoolean,
};

/* Constructores para expresiones lógicas */
AbstractExpresion* nuevoAndExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha) {
    ExpresionLenguaje* andExpresion = nuevoExpresionLenguaje(interpretExpresionLenguaje, izquierda, derecha);
    andExpresion->tablaOperaciones = &tablaOperacionesAnd;
    return (AbstractExpresion*) andExpresion;
}

AbstractExpresion* nuevoOrExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha) {
    ExpresionLenguaje* orExpresion = nuevoExpresionLenguaje(interpretExpresionLenguaje, izquierda, derecha);
    orExpresion->tablaOperaciones = &tablaOperacionesOr;
    return (AbstractExpresion*) orExpresion;
}

AbstractExpresion* nuevoNotExpresion(AbstractExpresion* expresion) {
    ExpresionLenguaje* notExpresion = nuevoExpresionLenguaje(interpretUnarioLenguaje, expresion, NULL);
    notExpresion->tablaOperaciones = &tablaOperacionesNot;
    return (AbstractExpresion*) notExpresion;
}
