#ifndef REGS_H
#define REGS_H

#include "../codegen.h"

// Funciones para asignar registros temporales
const char* alloc_temp_reg(CodegenContext* ctx);
void free_temp_reg(CodegenContext* ctx, const char* reg);

const char* alloc_temp_s_reg(CodegenContext* ctx);
void free_temp_s_reg(CodegenContext* ctx, const char* reg);

const char* alloc_temp_d_reg(CodegenContext* ctx);
void free_temp_d_reg(CodegenContext* ctx, const char* reg);

#endif