#include "../../codegen.h"
#include "../../registroARM/regs.h"
#include "../../../ast/AbstractExpresion.h"
#include "../../../ast/nodos/expresiones/terminales/primitivos.h"
#include <stdlib.h>
#include <string.h>

// Función auxiliar para compilar una expresión primitiva y devolver el registro con el resultado
const char* codegen_primitive(CodegenContext* ctx, PrimitivoExpresion* prim) {
    // printf("DEBUG codegen_primitive: tipo = %d\n", prim->tipo);
    if (prim->tipo == INT) {
        int val = atoi(prim->valor);
        const char* reg = alloc_temp_reg(ctx);
        emit(ctx, "mov %s, #%d", reg, val);
        return reg;
    } else if (prim->tipo == CHAR) {
        int val = prim->valor[0];  // Asumir string de 1 char
        const char* reg = alloc_temp_reg(ctx);
        emit(ctx, "mov %s, #%d", reg, val);
        return reg;
    } else if (prim->tipo == BOOLEAN) {
        int val = strcmp(prim->valor, "true") == 0 ? 1 : 0;
        const char* reg = alloc_temp_reg(ctx);
        emit(ctx, "mov %s, #%d", reg, val);
        return reg;
    } else if (prim->tipo == FLOAT) {
        // Usar registro float
        const char* reg = alloc_temp_s_reg(ctx);
        const char* label = new_label(ctx);
        float val = atof(prim->valor);
        add_data(ctx, "%s: .float %f", label, val);
        const char* addr_reg = alloc_temp_reg(ctx);
        emit(ctx, "ldr %s, =%s", addr_reg, label);
        emit(ctx, "ldr %s, [%s]", reg, addr_reg);
        free_temp_reg(ctx, addr_reg);
        return reg;
    } else if (prim->tipo == DOUBLE) {
        // Usar registro double
        const char* reg = alloc_temp_d_reg(ctx);
        const char* label = new_label(ctx);
        double val = atof(prim->valor);
        add_data(ctx, "%s: .double %f", label, val);
        const char* addr_reg = alloc_temp_reg(ctx);
        emit(ctx, "ldr %s, =%s", addr_reg, label);
        emit(ctx, "ldr %s, [%s]", reg, addr_reg);
        free_temp_reg(ctx, addr_reg);
        return reg;
    } else if (prim->tipo == STRING) {
        if (!prim->valor) {
            fprintf(stderr, "Error: prim->valor is NULL for STRING\n");
            return NULL;
        }
        const char* label = new_label(ctx);
        add_data(ctx, "%s: .asciz \"%s\\n\"", label, prim->valor ? prim->valor : "");
        const char* reg = alloc_temp_reg(ctx);
        emit(ctx, "ldr %s, =%s", reg, label);
        return reg;
    }
    return NULL;
}
