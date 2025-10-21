#include "../../codegen.h"
#include "../../registroARM/regs.h"
#include "../../../ast/AbstractExpresion.h"
#include "../../../ast/nodos/expresiones/cast.h"

// Función para compilar expresiones de cast
const char* codegen_cast(CodegenContext* ctx, CastExpresion* cast, const char* operand_reg) {
    if (cast->tipoDestino == INT && operand_reg[0] == 'd') {
        // float to int
        const char* int_reg = alloc_temp_reg(ctx);
        emit(ctx, "fcvtzs %s, %s", int_reg, operand_reg);
        free_temp_d_reg(ctx, operand_reg);
        return int_reg;
    } else if (cast->tipoDestino == DOUBLE && operand_reg[0] == 'x') {
        // int to double
        const char* double_reg = alloc_temp_d_reg(ctx);
        emit(ctx, "scvtf %s, %s", double_reg, operand_reg);
        free_temp_reg(ctx, operand_reg);
        return double_reg;
    } else if (cast->tipoDestino == FLOAT && operand_reg[0] == 'x') {
        // int to float
        const char* float_reg = alloc_temp_s_reg(ctx);
        emit(ctx, "scvtf %s, %s", float_reg, operand_reg);
        free_temp_reg(ctx, operand_reg);
        return float_reg;
    } else if (cast->tipoDestino == INT && operand_reg[0] == 'd') {
        // double to int
        const char* int_reg = alloc_temp_reg(ctx);
        emit(ctx, "fcvtzs %s, %s", int_reg, operand_reg);
        free_temp_d_reg(ctx, operand_reg);
        return int_reg;
    } else if (cast->tipoDestino == INT && operand_reg[0] == 's') {
        // float to int
        const char* int_reg = alloc_temp_reg(ctx);
        emit(ctx, "fcvtzs %s, %s", int_reg, operand_reg);
        free_temp_s_reg(ctx, operand_reg);
        return int_reg;
    } else if (cast->tipoDestino == FLOAT && operand_reg[0] == 'd') {
        // double to float
        const char* float_reg = alloc_temp_s_reg(ctx);
        emit(ctx, "fcvt %s, %s", float_reg, operand_reg);
        free_temp_d_reg(ctx, operand_reg);
        return float_reg;
    } else if (cast->tipoDestino == DOUBLE && operand_reg[0] == 's') {
        // float to double
        const char* double_reg = alloc_temp_d_reg(ctx);
        emit(ctx, "fcvt %s, %s", double_reg, operand_reg);
        free_temp_s_reg(ctx, operand_reg);
        return double_reg;
    } else if (cast->tipoDestino == CHAR && operand_reg[0] == 'x') {
        // int to char
        emit(ctx, "and %s, %s, #255", operand_reg, operand_reg);
        return operand_reg;
    } else {
        // Sin cambio
        return operand_reg;
    }
}
