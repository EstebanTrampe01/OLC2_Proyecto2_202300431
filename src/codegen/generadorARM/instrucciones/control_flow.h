#ifndef CONTROL_FLOW_H
#define CONTROL_FLOW_H

#include "../../codegen.h"
#include "../../../ast/AbstractExpresion.h"
#include <stdio.h>

// Declaración externa de arm_emit_runtime_nodes
void arm_emit_runtime_nodes(AbstractExpresion* n, CodegenContext* ctx, FILE* f, 
                           AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
                           char** emitted_names, int* emitted_types, int emitted_count);

// Funciones para generar código ARM64 para estructuras de control
void arm_emit_if_statement(CodegenContext* ctx, AbstractExpresion* ifNode, FILE* f, 
                          AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
                          char** emitted_names, int* emitted_types, int emitted_count);
void arm_emit_while_statement(CodegenContext* ctx, AbstractExpresion* whileNode, FILE* f, 
                              AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
                              char** emitted_names, int* emitted_types, int emitted_count);
void arm_emit_for_statement(CodegenContext* ctx, AbstractExpresion* forNode, FILE* f,
                            AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
                            char** emitted_names, int* emitted_types, int emitted_count);
void arm_emit_repeat_statement(CodegenContext* ctx, AbstractExpresion* repeatNode, FILE* f,
                               AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
                               char** emitted_names, int* emitted_types, int emitted_count);
void arm_emit_switch_statement(CodegenContext* ctx, AbstractExpresion* switchNode, FILE* f, 
                               AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
                               char** emitted_names, int* emitted_types, int emitted_count);

#endif
