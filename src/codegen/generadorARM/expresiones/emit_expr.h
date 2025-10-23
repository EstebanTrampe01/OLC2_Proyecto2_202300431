#ifndef GENERADOR_ARM_EMIT_EXPR_H
#define GENERADOR_ARM_EMIT_EXPR_H

#include <stdio.h>
#include "codegen/codegen.h"

// Evalúa una expresión y deja el resultado en x<target_reg>
void arm_emit_eval_expr(CodegenContext* ctx, AbstractExpresion* expr, int target_reg, FILE* f);

#endif


