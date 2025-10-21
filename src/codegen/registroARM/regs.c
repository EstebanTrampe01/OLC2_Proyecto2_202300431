#include "../codegen.h"
#include <string.h>
#include <stdio.h>

// Lista de registros temporales disponibles (x0-x18, evitando x19-x28 callee-saved)
static const char* temp_regs[] = {"x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15", "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28"};
#define NUM_TEMP_REGS (sizeof(temp_regs) / sizeof(temp_regs[0]))

const char* alloc_temp_reg(CodegenContext* ctx) {
    if ((size_t)ctx->reg_counter >= NUM_TEMP_REGS) {
        // TODO: Spill a pila si no hay registros libres
        fprintf(stderr, "Error: No hay registros temporales libres\n");
        return NULL;
    }
    return temp_regs[ctx->reg_counter++];
}

void free_temp_reg(CodegenContext* ctx, const char* reg) {
    if (ctx->reg_counter > 0) ctx->reg_counter--;
}

void push_stack(CodegenContext* ctx, const char* reg) {
    emit(ctx, "str %s, [sp, -16]!", reg);
    ctx->stack_offset += 16;
}

void pop_stack(CodegenContext* ctx, const char* reg) {
    emit(ctx, "ldr %s, [sp], 16", reg);
    ctx->stack_offset -= 16;
}

// Lista de registros float temporales (s0-s7 para float)
static const char* temp_s_regs[] = {"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7"};
#define NUM_TEMP_S_REGS (sizeof(temp_s_regs) / sizeof(temp_s_regs[0]))

const char* alloc_temp_s_reg(CodegenContext* ctx) {
    if (ctx->s_reg_counter >= (int)NUM_TEMP_S_REGS) {
        fprintf(stderr, "Error: No hay registros s temporales libres\n");
        return NULL;
    }
    return temp_s_regs[ctx->s_reg_counter++];
}

void free_temp_s_reg(CodegenContext* ctx, const char* reg) {
    if (ctx->s_reg_counter > 0) ctx->s_reg_counter--;
}

// Lista de registros double temporales (d0-d7 para double)
static const char* temp_d_regs[] = {"d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7"};
#define NUM_TEMP_D_REGS (sizeof(temp_d_regs) / sizeof(temp_d_regs[0]))

const char* alloc_temp_d_reg(CodegenContext* ctx) {
    if (ctx->d_reg_counter >= (int)NUM_TEMP_D_REGS) {
        fprintf(stderr, "Error: No hay registros d temporales libres\n");
        return NULL;
    }
    return temp_d_regs[ctx->d_reg_counter++];
}

void free_temp_d_reg(CodegenContext* ctx, const char* reg) {
    if (ctx->d_reg_counter > 0) ctx->d_reg_counter--;
}
