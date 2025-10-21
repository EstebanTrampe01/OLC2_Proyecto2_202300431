#include "../codegen.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/instrucciones/instruccion/funcion.h"
#include "../../ast/nodos/instrucciones/instruccion/print.h"

// Minimal placeholder implementations to satisfy the linker after reorganization.
// These should be replaced by the full implementations from the reorganized files.

const char* codegen_builtin_call(CodegenContext* ctx, LlamadaFuncion* call) {
    // Fallback: return NULL (no generated string). Real impl lives in expr_builtins.c
    (void)ctx; (void)call;
    return NULL;
}

const char* codegen_string_value_of(CodegenContext* ctx, void* wrap) {
    (void)ctx; (void)wrap;
    return NULL;
}

void codegen_print_instr(CodegenContext* ctx, PrintExpresion* print) {
    // Minimal no-op print to allow linking; proper printing implemented elsewhere.
    (void)ctx; (void)print;
}
