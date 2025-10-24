#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "expresiones.h"
#include "ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "ast/nodos/expresiones/logicas/logicas.h"
#include "ast/nodos/expresiones/relacionales/relacionales.h"

#include <stdlib.h>
#include <stdio.h>

Result interpretExpresionLenguaje(AbstractExpresion* self, Context* context) {
    ExpresionLenguaje* nodo = (ExpresionLenguaje*) self;
    // Evaluar primero derecha (para soportar recursión reentrante) luego izquierda
    Result derecha = self->hijos[1]->interpret(self->hijos[1], context);
    Result izquierda = self->hijos[0]->interpret(self->hijos[0], context);

    // Validación bitwise (requiere INT)
    if (nodo->tablaOperaciones==&tablaOperacionesBitAnd || nodo->tablaOperaciones==&tablaOperacionesBitOr || nodo->tablaOperaciones==&tablaOperacionesBitXor || nodo->tablaOperaciones==&tablaOperacionesShiftLeft || nodo->tablaOperaciones==&tablaOperacionesShiftRight) {
        if (izquierda.tipo!=INT || derecha.tipo!=INT) {
            printf("Operación bitwise requiere operandos int\n");
            return nuevoValorResultadoVacio();
        }
    }

    // Coerción: si la tabla es lógica (AND/OR) y recibimos INT, tratarlo como BOOLEAN
    // Coerción previa para lógicas: convertir INT a BOOLEAN antes de buscar operación
    if (nodo->tablaOperaciones==&tablaOperacionesAnd || nodo->tablaOperaciones==&tablaOperacionesOr) {
        if (izquierda.tipo==INT) {
            int* coerced = malloc(sizeof(int)); *coerced = (*((int*)izquierda.valor)!=0); izquierda.tipo=BOOLEAN; izquierda.valor=coerced;
        }
        if (derecha.tipo==INT) {
            int* coerced = malloc(sizeof(int)); *coerced = (*((int*)derecha.valor)!=0); derecha.tipo=BOOLEAN; derecha.valor=coerced;
        }
    }
    // Soporte especial: comparaciones con null para igualdad/desigualdad
    if (nodo->tablaOperaciones==&tablaOperacionesIgualdad || nodo->tablaOperaciones==&tablaOperacionesDesigualdad) {
        int leftIsNull = (izquierda.tipo==NULO) || ((izquierda.tipo==STRING || izquierda.tipo==ARRAY) && izquierda.valor==NULL);
        int rightIsNull = (derecha.tipo==NULO) || ((derecha.tipo==STRING || derecha.tipo==ARRAY) && derecha.valor==NULL);
        if (leftIsNull || rightIsNull) {
            int* r = (int*)malloc(sizeof(int));
            if (nodo->tablaOperaciones==&tablaOperacionesIgualdad) {
                *r = (leftIsNull == rightIsNull);
            } else {
                *r = (leftIsNull != rightIsNull);
            }
            return nuevoValorResultado(r, BOOLEAN);
        }
    }

    Operacion op = (*nodo->tablaOperaciones)[izquierda.tipo][derecha.tipo];
    if (op == NULL) {
        printf("Operación no soportada para los tipos %s, %s\n", labelTipoDato[izquierda.tipo], labelTipoDato[derecha.tipo]);
        return nuevoValorResultadoVacio();
    }
    // Estructura temporal para no pisar campos del nodo compartido en recursión
    ExpresionLenguaje temp; temp.izquierda = izquierda; temp.derecha = derecha; temp.tablaOperaciones = nodo->tablaOperaciones;
    return op(&temp);
}

Result interpretUnarioLenguaje(AbstractExpresion* self, Context* context) {
    ExpresionLenguaje* nodo = (ExpresionLenguaje*) self;
    calcularResultadoIzquierdo(nodo, context);

    Operacion op = (*nodo->tablaOperaciones)[nodo->izquierda.tipo][NULO];
    if (op == NULL) {
        printf("Operación no soportada para el tipo %s\n", 
            labelTipoDato[nodo->izquierda.tipo]);
        return nuevoValorResultadoVacio();
    }
    return op(nodo);
}

ExpresionLenguaje* nuevoExpresionLenguaje(Interpret funcionEspecifica, AbstractExpresion* izquierda, AbstractExpresion* derecha) {
    // reservar el espacio en memoria y obtener el puntero a este
    ExpresionLenguaje* nodo = malloc(sizeof(ExpresionLenguaje));
    if (!nodo) return NULL;

    //asignar valores
    buildAbstractExpresion(&nodo->base, funcionEspecifica);

    //guardar los punteros en lo hijos de este arbol a los lados de la expresion
    if (izquierda) agregarHijo((AbstractExpresion*) nodo, izquierda);
    if (derecha) agregarHijo((AbstractExpresion*) nodo, derecha);
    
    return nodo;
}

void calcularResultadoIzquierdo(ExpresionLenguaje* self, Context* context) {
    self->izquierda = self->base.hijos[0]->interpret(self->base.hijos[0], context);
}

void calcularResultadoDerecho(ExpresionLenguaje* self, Context* context) {
    self->derecha = self->base.hijos[1]->interpret(self->base.hijos[1], context);
}

void calcularResultados(ExpresionLenguaje* self, Context* context) {
    calcularResultadoIzquierdo(self, context);
    calcularResultadoDerecho(self, context);
}