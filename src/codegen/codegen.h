#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "ast/AbstractExpresion.h"

typedef struct CodegenContext {
    FILE* out;
    Context* symbol_ctx; // opcional: referencia al contexto de símbolos
    int debug; // si 1, generar comentarios adicionales en el .s
} CodegenContext;

CodegenContext* nuevo_codegen_context(FILE* out);
void codegen_programa(CodegenContext* ctx, AbstractExpresion* root);
void liberar_codegen_context(CodegenContext* ctx);
// Helpers used by emitters
int codegen_find_strlit(const char* val);
int codegen_register_strlit(FILE* f, const char* val);

// Native implementations registry (phase 1)
// name: logical operation or helper key
// helper_name: symbol name to call in runtime (e.g. "print_string")
void codegen_register_native(const char* name, const char* helper_name, int kind);
const char* codegen_get_native_helper(const char* name);
int codegen_is_native(const char* name);

#endif
