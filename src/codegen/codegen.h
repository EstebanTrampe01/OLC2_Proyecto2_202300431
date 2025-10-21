#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include <stdbool.h>
#include "../context/context.h"
#include "../context/result.h"

// Forward declaration para evitar incluir todo el AST aquí
struct AbstractExpresion;

// Contexto para generación de código ARM64
typedef struct {
    FILE* out;              // Archivo de salida (.s)
    int reg_counter;        // Contador para asignar registros temporales
    int s_reg_counter;      // Contador para registros float
    int d_reg_counter;      // Contador para registros double
    int label_counter;      // Contador para etiquetas
    int stack_offset;       // Offset en la pila para variables locales
    char* data_lines[100000];  // Líneas para .data
    int data_count;         // Número de líneas en data
    Context* symbol_ctx;    // Contexto de símbolos para tipos
} CodegenContext;

// Inicializar contexto de codegen
CodegenContext* nuevo_codegen_context(FILE* out);

// Liberar contexto
void liberar_codegen_context(CodegenContext* ctx);

// Emitir una instrucción ARM64 (formato printf)
void emit(CodegenContext* ctx, const char* fmt, ...);

// Obtener un registro temporal libre (x0-x18, evitando callee-saved)
const char* alloc_temp_reg(CodegenContext* ctx);

// Liberar un registro temporal
void free_temp_reg(CodegenContext* ctx, const char* reg);

// Generar una nueva etiqueta
const char* new_label(CodegenContext* ctx);

// Push a pila (para salvar registros)
void push_stack(CodegenContext* ctx, const char* reg);

// Pop de pila
void pop_stack(CodegenContext* ctx, const char* reg);

// Agregar línea a .data
void add_data(CodegenContext* ctx, const char* fmt, ...);

// Funciones para print
void emit_print_int_literal(CodegenContext* ctx, int val);
void emit_print_char_literal(CodegenContext* ctx, char c);
void emit_print_bool_literal(CodegenContext* ctx, int val);
void emit_print_int(CodegenContext* ctx, const char* reg);
void emit_print_string(CodegenContext* ctx, const char* str);
void emit_print_string_reg(CodegenContext* ctx, const char* reg);

// Función para obtener tipo de expresión
TipoDato get_expr_type(struct AbstractExpresion* expr, Context* ctx);

// Función principal para generar código desde el AST
void codegen_programa(CodegenContext* ctx, struct AbstractExpresion* ast_root);

// Funciones para compilar expresiones e instrucciones
const char* codegen_expr(CodegenContext* ctx, struct AbstractExpresion* expr);
void codegen_instr(CodegenContext* ctx, struct AbstractExpresion* instr);
void codegen_node(CodegenContext* ctx, struct AbstractExpresion* node);

// Funciones para registros float
const char* alloc_temp_float_reg(CodegenContext* ctx);
void free_temp_float_reg(CodegenContext* ctx, const char* reg);

#endif // CODEGEN_H