#include "../../codegen.h"
#include "../../../ast/AbstractExpresion.h"
#include "../../../ast/nodos/expresiones/expresiones.h"
#include "../../../ast/nodos/expresiones/logicas/logicas.h"

// Función para compilar operaciones lógicas binarias
const char* codegen_binop_logical(CodegenContext* ctx, ExpresionLenguaje* binop, const char* left_reg, const char* right_reg) {
    if (binop->tablaOperaciones == &tablaOperacionesAnd) {
        // &&
        const char* false_label = new_label(ctx);
        const char* end_label = new_label(ctx);
        emit(ctx, "cmp %s, #0", left_reg);
        emit(ctx, "beq %s", false_label);
        emit(ctx, "cmp %s, #0", right_reg);
        emit(ctx, "beq %s", false_label);
        emit(ctx, "mov %s, #1", left_reg);
        emit(ctx, "b %s", end_label);
        emit(ctx, "%s:", false_label);
        emit(ctx, "mov %s, #0", left_reg);
        emit(ctx, "%s:", end_label);
        free_temp_reg(ctx, right_reg);
        return left_reg;
    } else if (binop->tablaOperaciones == &tablaOperacionesOr) {
        // ||
        const char* true_label = new_label(ctx);
        const char* end_label = new_label(ctx);
        emit(ctx, "cmp %s, #0", left_reg);
        emit(ctx, "bne %s", true_label);
        emit(ctx, "cmp %s, #0", right_reg);
        emit(ctx, "bne %s", true_label);
        emit(ctx, "mov %s, #0", left_reg);
        emit(ctx, "b %s", end_label);
        emit(ctx, "%s:", true_label);
        emit(ctx, "mov %s, #1", left_reg);
        emit(ctx, "%s:", end_label);
        free_temp_reg(ctx, right_reg);
        return left_reg;
    }
    return left_reg;
}
