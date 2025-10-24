#ifndef GENERADOR_ARM_RUNTIME_NODES_H
#define GENERADOR_ARM_RUNTIME_NODES_H

#include <stdio.h>
#include "codegen/codegen.h"

// Pasada de recolección (.data) y runtime (.text)
void arm_collect_nodes(AbstractExpresion* n, CodegenContext* ctx,
    AbstractExpresion*** label_nodes_ptr, int** label_ids_ptr, int* label_map_size_ptr, int* label_map_capacity_ptr,
    AbstractExpresion*** assign_nodes_ptr, int* assign_size_ptr, int* assign_cap_ptr,
    char*** emitted_names_ptr, int* emitted_count_ptr, int* emitted_cap_ptr,
    int** emitted_init_ids_ptr, char*** emitted_init_values_ptr, int* emitted_types_ptr,
    FILE* f);

void arm_emit_runtime_nodes(AbstractExpresion* n, CodegenContext* ctx, FILE* f,
    AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
    char** emitted_names, int* emitted_types, int emitted_count);

#endif


