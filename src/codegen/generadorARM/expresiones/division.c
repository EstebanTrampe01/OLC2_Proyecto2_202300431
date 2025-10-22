#include "ast/AbstractExpresion.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "codegen/codegen.h"
#include <stdio.h>

/*
 Minimal scaffold emitter for division nodes.
 This file is a starting point: it doesn't implement full register allocation
 or evaluation of subexpressions. Instead it demonstrates the structure
 and emits a call to a helper `div_helper` that must be provided as a C function
 compiled for AArch64. Adapt and expand as needed.
*/

void emit_division_text(CodegenContext* ctx, AbstractExpresion* node, int label_id) {
    (void)ctx; (void)node; (void)label_id;
    FILE* f = ctx->out;
    if (!f) return;
    // Example: call helper div_helper(left_ptr, right_ptr) returning result in x0
    // Caller of helper must ensure arguments are proper pointers or values per ABI
    fprintf(f, "    # emit_division_text: placeholder\n");
    fprintf(f, "    // TODO: generate code to evaluate operands into x0/x1 or memory\n");
    fprintf(f, "    bl div_helper\n");
}
