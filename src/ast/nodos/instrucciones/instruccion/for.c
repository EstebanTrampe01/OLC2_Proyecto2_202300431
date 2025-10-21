#include "for.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../../../context/result.h"
#include "../../../../context/error_reporting.h"

Result interpretForExpresion(AbstractExpresion* self, Context* context);

AbstractExpresion* nuevoForExpresion(AbstractExpresion* initialization, AbstractExpresion* condition, AbstractExpresion* increment, AbstractExpresion* body) {
    ForExpresion* expr = (ForExpresion*)malloc(sizeof(ForExpresion));
    expr->initialization = initialization;
    expr->condition = condition;
    expr->increment = increment;
    expr->body = body;
    buildAbstractExpresion(&expr->base, interpretForExpresion);
    if (initialization) agregarHijo((AbstractExpresion*)expr, initialization);
    if (condition) agregarHijo((AbstractExpresion*)expr, condition);
    if (increment) agregarHijo((AbstractExpresion*)expr, increment);
    if (body) agregarHijo((AbstractExpresion*)expr, body);
    return (AbstractExpresion*)expr;
}

Result interpretForExpresion(AbstractExpresion* self, Context* context) {
    /* Semántica estilo Java:
       - El for introduce un scope (contexto) propio donde vive la variable de inicialización.
       - Ese scope persiste durante todas las iteraciones.
       - El cuerpo (si es un bloque) puede crear scopes internos adicionales (ya manejado por BloqueExpresion).
       - Al finalizar el for, las variables declaradas en la inicialización NO existen fuera.
    */
    ForExpresion* forExpr = (ForExpresion*)self;

    // Crear el contexto del for (hijo del contexto actual)
    Context* forContext = nuevoContext(context);

    // Inicialización (si existe) en el contexto del for
    if (forExpr->initialization != NULL) {
        (void)forExpr->initialization->interpret(forExpr->initialization, forContext);
    }

    // Marcar que estamos dentro de un loop
    forContext->dentroLoop++;
    while (1) {
        // Condición (si no hay, se asume verdadera)
        if (forExpr->condition != NULL) {
            Result conditionResult = forExpr->condition->interpret(forExpr->condition, forContext);
            // fprintf(stderr, "[DEBUG for cond tipo=%s]\n", labelTipoDato[conditionResult.tipo]);
            if (conditionResult.tipo != BOOLEAN) {
                report_runtime_error(self, context, "La condición del for debe ser booleana");
                break; // abortar el for
            }
            if (!*((int*)conditionResult.valor)) break; // salir del for
        }

        // Cuerpo (se interpreta en el contexto del for; BloqueExpresion decidirá si crea sub‑contexto)
        Result bodyResult = forExpr->body->interpret(forExpr->body, forContext);
        if (bodyResult.tipo == BREAK) {
            break;
        } else if (bodyResult.tipo == CONTINUE) {
            // Ejecutar incremento y continuar
            if (forExpr->increment != NULL) {
                (void)forExpr->increment->interpret(forExpr->increment, forContext);
            }
            continue; // siguiente iteración
        }

        // Incremento (si existe) en el contexto del for
        if (forExpr->increment != NULL) {
            (void)forExpr->increment->interpret(forExpr->increment, forContext);
        }
    }
    forContext->dentroLoop--;

    return nuevoValorResultadoVacio();
}
