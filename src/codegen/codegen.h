#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "ast/AbstractExpresion.h"

typedef struct CodegenContext {
    FILE* out;
    Context* symbol_ctx; // opcional: referencia al contexto de símbolos
    int debug; // si 1, generar comentarios adicionales en el .s
    
    // Sistema de pila de etiquetas para break
    char** break_labels; // Pila de etiquetas de fin de bucle
    int break_stack_size; // Tamaño actual de la pila
    int break_stack_capacity; // Capacidad máxima de la pila
    
    // Sistema de pila de etiquetas para continue
    char** continue_labels; // Pila de etiquetas de continuación de bucle
    int continue_stack_size; // Tamaño actual de la pila
    int continue_stack_capacity; // Capacidad máxima de la pila
} CodegenContext;

CodegenContext* nuevo_codegen_context(FILE* out);
void codegen_programa(CodegenContext* ctx, AbstractExpresion* root);
void liberar_codegen_context(CodegenContext* ctx);

// Funciones de debug condicional
void enable_debug_output();
void debug_printf(const char* format, ...);
// Helpers used by emitters
int codegen_find_strlit(const char* val);
int codegen_register_strlit(FILE* f, const char* val);

// Native implementations registry (phase 1)
// name: logical operation or helper key
// helper_name: symbol name to call in runtime (e.g. "print_string")
void codegen_register_native(const char* name, const char* helper_name, int kind);
const char* codegen_get_native_helper(const char* name);
int codegen_is_native(const char* name);

// Sistema de pila de etiquetas para break
void codegen_push_break_label(CodegenContext* ctx, const char* label);
void codegen_pop_break_label(CodegenContext* ctx);
const char* codegen_get_current_break_label(CodegenContext* ctx);

// Sistema de pila de etiquetas para continue
void codegen_push_continue_label(CodegenContext* ctx, const char* label);
void codegen_pop_continue_label(CodegenContext* ctx);
const char* codegen_get_current_continue_label(CodegenContext* ctx);

#endif
