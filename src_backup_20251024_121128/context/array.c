#include "array.h"
#include <stdlib.h>
#include <stdio.h>
#include "default_values.h"

ArrayValue* nuevoArrayValue(TipoDato elementType, int length) {
    if (length < 0) return NULL;
    ArrayValue* a = malloc(sizeof(ArrayValue));
    a->elementType = elementType;
    a->length = length;
    a->items = malloc(sizeof(void*) * length);
    for (int i=0;i<length;i++) { void* v=NULL; TipoDato tr=elementType; if(valor_por_defecto(elementType,&v,&tr)) a->items[i]=v; else a->items[i]=NULL; }
    return a;
}

void liberarArrayValue(ArrayValue* arr) {
    if (!arr) return;
    for (int i=0;i<arr->length;i++) {
    if (arr->items[i]) { free(arr->items[i]); arr->items[i]=NULL; }
    }
    free(arr->items);
    free(arr);
}