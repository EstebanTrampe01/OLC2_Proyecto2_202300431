#include "while.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../../../context/result.h"
#include "../../../../context/error_reporting.h"

Result interpretWhileExpresion(AbstractExpresion* self, Context* context);

AbstractExpresion* nuevoWhileExpresion(AbstractExpresion* condition, AbstractExpresion* body) {
    WhileExpresion* expr = (WhileExpresion*)malloc(sizeof(WhileExpresion));
    expr->condition = condition;
    expr->body = body;
    buildAbstractExpresion(&expr->base, interpretWhileExpresion);
        if (condition) agregarHijo((AbstractExpresion*)expr, condition);
        if (body) agregarHijo((AbstractExpresion*)expr, body);
    return (AbstractExpresion*)expr;
}

Result interpretWhileExpresion(AbstractExpresion* self, Context* context) {
        // Usar directamente el contexto padre (semántica Java real).
        // Importante: NO liberar los punteros de valores básicos retornados por identificadores o declaraciones,
        // porque esos apuntan al almacenamiento vivo en la tabla de símbolos.
        WhileExpresion* whileExpr = (WhileExpresion*)self;

        context->dentroLoop++;
        while (1) {
                Result conditionResult = whileExpr->condition->interpret(whileExpr->condition, context);
                // debug tipo condición
                // fprintf(stderr, "[DEBUG while cond tipo=%s]\n", labelTipoDato[conditionResult.tipo]);
                if (conditionResult.tipo != BOOLEAN) {
                        report_runtime_error(self, context, "La condición del while debe ser booleana");
                        break; // abortar bucle
                }
                int continuar = *((int*)conditionResult.valor);
                if (!continuar) break;

                Result bodyResult = whileExpr->body->interpret(whileExpr->body, context);
                if (bodyResult.tipo == BREAK) {
                        break; // salir del loop
                } else if (bodyResult.tipo == CONTINUE) {
                        continue; // siguiente iteración (condición reevaluada)
                }
        }
        context->dentroLoop--;

        return nuevoValorResultadoVacio();
}
