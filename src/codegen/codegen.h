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

#endif
