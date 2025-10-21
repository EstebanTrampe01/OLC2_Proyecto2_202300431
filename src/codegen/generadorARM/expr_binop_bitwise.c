#include "../codegen.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/expresiones/expresiones.h"
#include "../../ast/nodos/expresiones/aritmeticas/aritmeticas.h"

// Función para compilar operaciones bitwise binarias
const char* codegen_binop_bitwise(CodegenContext* ctx, ExpresionLenguaje* binop, const char* left_reg, const char* right_reg) {
    if (binop->tablaOperaciones == tablaOperacionesBitAnd) {
        emit(ctx, "and %s, %s, %s", left_reg, left_reg, right_reg);
    } else if (binop->tablaOperaciones == tablaOperacionesBitOr) {
        emit(ctx, "orr %s, %s, %s", left_reg, left_reg, right_reg);
    } else if (binop->tablaOperaciones == tablaOperacionesBitXor) {
        emit(ctx, "eor %s, %s, %s", left_reg, left_reg, right_reg);
    } else if (binop->tablaOperaciones == tablaOperacionesShiftLeft) {
        emit(ctx, "lsl %s, %s, %s", left_reg, left_reg, right_reg);
    } else if (binop->tablaOperaciones == tablaOperacionesShiftRight) {
        emit(ctx, "lsr %s, %s, %s", left_reg, left_reg, right_reg);
    } else {
        // Por ahora, asumir suma si no es reconocido
        emit(ctx, "add %s, %s, %s", left_reg, left_reg, right_reg);
    }
    if (right_reg[0] == 'd') {
        free_temp_d_reg(ctx, right_reg);
    } else if (right_reg[0] == 's') {
        free_temp_s_reg(ctx, right_reg);
    } else {
        free_temp_reg(ctx, right_reg);
    }
    return left_reg;
}