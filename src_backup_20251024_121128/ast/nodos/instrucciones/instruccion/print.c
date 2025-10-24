#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "print.h"
#include "context/array.h"

#include <stdlib.h>
#include <stdio.h>
#include "context/format_utils.h"


static void printArrayRec(ArrayValue* arr) {
    printf("[");
    for (int i=0;i<arr->length;i++) {
        if (i) printf(", ");
        if (!arr->items[i]) { printf("null"); continue; }
        if (arr->elementType == ARRAY) {
            printArrayRec((ArrayValue*)arr->items[i]);
        } else {
            switch (arr->elementType) {
                case INT: case BYTE: case SHORT: case LONG: printf("%d", *((int*)arr->items[i])); break;
                case FLOAT: printf("%s", format_trim_float(*((float*)arr->items[i]), 6)); break;
                case DOUBLE: printf("%s", format_trim_double(*((double*)arr->items[i]), 10)); break;
                case BOOLEAN: printf("%s", *((int*)arr->items[i])?"true":"false"); break;
                case CHAR: printf("%s", format_char((unsigned char)(*((char*)arr->items[i])))); break;
                case STRING: printf("\"%s\"", (char*)arr->items[i]); break;
                default: printf("?");
            }
        }
    }
    printf("]");
}

Result interpretPrintExpresion(AbstractExpresion* self, Context* context) {
    // interpretar la lista de expresiones
    // recorremos  cada expresion y lo que nos devuelva imprimimos el valor
    AbstractExpresion* listaExpresiones = self->hijos[0];
    if (!listaExpresiones) return nuevoValorResultadoVacio();
    PrintExpresion* pe = (PrintExpresion*)self;
    // Limpieza: se eliminaron hacks de transformación contextual
    for (size_t i = 0; i < listaExpresiones->numHijos; ++i) {
        if (!listaExpresiones->hijos[i]) continue;
        Result result = listaExpresiones->hijos[i]->interpret(listaExpresiones->hijos[i], context);
        int last = (i == listaExpresiones->numHijos - 1);
        switch (result.tipo) {
            case STRING: { const char* s=(const char*)result.valor; printf("%s", s? s: "null"); fflush(stdout); break; }
            case INT:      printf("%d", *(int*)result.valor); fflush(stdout); break;
            case ARRAY: {  ArrayValue* arr = (ArrayValue*)result.valor; printArrayRec(arr); fflush(stdout); break; }
            case FLOAT:    printf("%s", format_trim_float(*(float*)result.valor, 6)); fflush(stdout); break;
            case DOUBLE: { double dv=*(double*)result.valor; printf("%s", format_trim_double(dv, 10)); fflush(stdout); break; }
            case BOOLEAN:  printf("%s", *(int*)result.valor ? "true" : "false"); fflush(stdout); break;
            case CHAR: printf("%s", format_char((unsigned char)(*(unsigned char*)result.valor))); fflush(stdout); break;
            case NULO:     printf("NULL"); fflush(stdout); break;
            default:       printf("<tipo %d>", result.tipo); fflush(stdout); break;
        }
    // evitamos segunda impresión de cadenas (antes duplicaba)
        /* Separador entre expresiones: espacio como Java cuando concatenas: aquí conservamos sin espacio; el usuario controla via String.valueOf en su código */
    }
    if (pe->newline) printf("\n");
    return nuevoValorResultadoVacio();
}

AbstractExpresion* nuevoPrintExpresion(AbstractExpresion* listaExpresiones, int newline) {
    PrintExpresion* nodo = malloc(sizeof(PrintExpresion));
    if (!nodo) return NULL; 
    buildAbstractExpresion(&nodo->base, interpretPrintExpresion);
    // mark for codegen: print can be implemented by helper
    nodo->base.gen_strategy = GEN_CALL_HELPER;
    nodo->newline = newline;
    if (listaExpresiones) agregarHijo((AbstractExpresion*) nodo, listaExpresiones);
    else agregarHijo((AbstractExpresion*) nodo, nuevoListaExpresiones());
    return (AbstractExpresion*) nodo; }