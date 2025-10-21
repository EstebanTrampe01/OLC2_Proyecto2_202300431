#include "continue.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../../../context/result.h"
#include "../../../../context/error_reporting.h"

Result interpretContinueExpresion(AbstractExpresion* self, Context* context);

AbstractExpresion* nuevoContinueExpresion(void) {
    AbstractExpresion* expr = (AbstractExpresion*)malloc(sizeof(AbstractExpresion));
    buildAbstractExpresion(expr, interpretContinueExpresion);
    return expr;
}

Result interpretContinueExpresion(AbstractExpresion* self, Context* context) {
    if (!context || context->dentroLoop <= 0) {
        report_runtime_error(self, context, "'continue' fuera de un bucle");
        return nuevoValorResultadoVacio();
    }
    Result result = nuevoValorResultadoVacio();
    result.tipo = CONTINUE;
    return result;
}