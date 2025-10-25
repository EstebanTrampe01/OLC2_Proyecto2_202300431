#include "repeat.h"
#include "../../../AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"
#include <stdio.h>
#include <stdlib.h>

AbstractExpresion* nuevoRepeatExpresion(AbstractExpresion* count, AbstractExpresion* body) {
    RepeatExpresion* repeat = malloc(sizeof(RepeatExpresion));
    buildAbstractExpresion(&repeat->base, interpretRepeatExpresion);
    repeat->count = count;
    repeat->body = body;
    repeat->base.linea = 0;
    repeat->base.columna = 0;
    if (count) agregarHijo((AbstractExpresion*)repeat, count);
    if (body) agregarHijo((AbstractExpresion*)repeat, body);
    return (AbstractExpresion*) repeat;
}

Result interpretRepeatExpresion(AbstractExpresion* n, Context* ctx) {
    RepeatExpresion* repeat = (RepeatExpresion*) n;
    
    if (!repeat || !repeat->count || !repeat->body) {
        return nuevoValorResultadoVacio();
    }
    
    // Evaluar el número de repeticiones
    Result countResult = repeat->count->interpret(repeat->count, ctx);
    
    // Convertir a entero
    int iterations = 0;
    if (countResult.tipo == INT) {
        iterations = *(int*)countResult.valor;
    } else if (countResult.tipo == FLOAT) {
        iterations = (int)*(float*)countResult.valor;
    } else {
        return nuevoValorResultadoVacio();
    }
    
    if (iterations < 0) {
        return nuevoValorResultadoVacio();
    }
    
    // Ejecutar el cuerpo n veces
    for (int i = 0; i < iterations; i++) {
        Result bodyResult = repeat->body->interpret(repeat->body, ctx);
        // No necesitamos verificar errores aquí, solo ejecutar
    }
    
    return nuevoValorResultadoVacio();
}
