#include "break.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../../../context/result.h"

Result interpretBreakExpresion(AbstractExpresion* self, Context* context);

AbstractExpresion* nuevoBreakExpresion(void) {
    BreakExpresion* expr = (BreakExpresion*)malloc(sizeof(BreakExpresion));
    buildAbstractExpresion(&expr->base, interpretBreakExpresion);
    return (AbstractExpresion*)expr;
}

Result interpretBreakExpresion(AbstractExpresion* self, Context* context) {
    // Validar contexto: permitido dentro de while/for o dentro de switch
    if (!context || (context->dentroLoop <= 0 && context->dentroSwitch <= 0)) {
        report_runtime_error(self, context, "'break' fuera de un bucle o switch");
        return nuevoValorResultadoVacio();
    }
    Result result = nuevoValorResultadoVacio();
    result.tipo = BREAK;
    return result;
}