#include "if.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../../../context/result.h"
#include "../../../../context/error_reporting.h"

AbstractExpresion* nuevoIfExpresion(AbstractExpresion* condicion, AbstractExpresion* bloqueIf, AbstractExpresion* bloqueElse) {
    IfExpresion* expr = (IfExpresion*)malloc(sizeof(IfExpresion));
    expr->condicion = condicion;
    expr->bloqueIf = bloqueIf;
    expr->bloqueElse = bloqueElse;
    buildAbstractExpresion(&expr->base, interpretIfExpresion);
    // Exponer hijos para exportar AST
    if (condicion) agregarHijo((AbstractExpresion*)expr, condicion);
    if (bloqueIf) agregarHijo((AbstractExpresion*)expr, bloqueIf);
    if (bloqueElse) agregarHijo((AbstractExpresion*)expr, bloqueElse);
    return (AbstractExpresion*)expr;
}

Result interpretIfExpresion(AbstractExpresion* self, Context* context) {
    IfExpresion* expr = (IfExpresion*)self;

    // Evaluar condición
    Result condResult = expr->condicion->interpret(expr->condicion, context);
    if (condResult.tipo == INT) {
        // Coerción int -> boolean
        int* coerced = malloc(sizeof(int));
        *coerced = *((int*)condResult.valor) != 0;
        condResult.tipo = BOOLEAN;
        condResult.valor = coerced;
    } else if (condResult.tipo != BOOLEAN) {
        report_runtime_error(self, context, "La condición del if debe ser booleana");
        return nuevoValorResultadoVacio();
    }

    // Ejecutar bloque correspondiente
    if (*((int*)condResult.valor)) {
        return expr->bloqueIf->interpret(expr->bloqueIf, context);
    } else if (expr->bloqueElse != NULL) {
        return expr->bloqueElse->interpret(expr->bloqueElse, context);
    }

    // Si no hay else y condición es false, no hacer nada
    return nuevoValorResultadoVacio();
}
