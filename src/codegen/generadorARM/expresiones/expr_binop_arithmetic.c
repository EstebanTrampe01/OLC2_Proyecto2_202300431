#include "../../codegen.h"
#include "../../registroARM/regs.h"
#include "../../../ast/AbstractExpresion.h"
#include "../../../ast/nodos/expresiones/expresiones.h"
#include "../../../ast/nodos/expresiones/aritmeticas/aritmeticas.h"

// Función para compilar operaciones aritméticas binarias
const char* codegen_binop_arithmetic(CodegenContext* ctx, ExpresionLenguaje* binop, const char* left_reg, const char* right_reg) {
    if (binop->tablaOperaciones == &tablaOperacionesSuma) {
        bool is_float_op = left_reg[0] == 'd' || left_reg[0] == 's' || right_reg[0] == 'd' || right_reg[0] == 's';
        if (is_float_op) {
            if (left_reg[0] == 'x') {
                const char* temp = alloc_temp_d_reg(ctx);
                emit(ctx, "scvtf %s, %s", temp, left_reg);
                free_temp_reg(ctx, left_reg);
                left_reg = temp;
            }
            if (right_reg[0] == 'x') {
                const char* temp = alloc_temp_d_reg(ctx);
                emit(ctx, "scvtf %s, %s", temp, right_reg);
                free_temp_reg(ctx, right_reg);
                right_reg = temp;
            }
            emit(ctx, "fadd %s, %s, %s", left_reg, left_reg, right_reg);
            free_temp_d_reg(ctx, right_reg);
        } else {
            emit(ctx, "add %s, %s, %s", left_reg, left_reg, right_reg);
            free_temp_reg(ctx, right_reg);
        }
        return left_reg;
    } else if (binop->tablaOperaciones == &tablaOperacionesResta) {
        bool is_float_op = left_reg[0] == 'd' || left_reg[0] == 's' || right_reg[0] == 'd' || right_reg[0] == 's';
        if (is_float_op) {
            if (left_reg[0] == 'x') {
                const char* temp = alloc_temp_d_reg(ctx);
                emit(ctx, "scvtf %s, %s", temp, left_reg);
                free_temp_reg(ctx, left_reg);
                left_reg = temp;
            }
            if (right_reg[0] == 'x') {
                const char* temp = alloc_temp_d_reg(ctx);
                emit(ctx, "scvtf %s, %s", temp, right_reg);
                free_temp_reg(ctx, right_reg);
                right_reg = temp;
            }
            emit(ctx, "fsub %s, %s, %s", left_reg, left_reg, right_reg);
            free_temp_d_reg(ctx, right_reg);
        } else {
            emit(ctx, "sub %s, %s, %s", left_reg, left_reg, right_reg);
            free_temp_reg(ctx, right_reg);
        }
        return left_reg;
    } else if (binop->tablaOperaciones == &tablaOperacionesMultiplicacion) {
        bool is_float_op = left_reg[0] == 'd' || left_reg[0] == 's' || right_reg[0] == 'd' || right_reg[0] == 's';
        if (is_float_op) {
            if (left_reg[0] == 'x') {
                const char* temp = alloc_temp_d_reg(ctx);
                emit(ctx, "scvtf %s, %s", temp, left_reg);
                free_temp_reg(ctx, left_reg);
                left_reg = temp;
            }
            if (right_reg[0] == 'x') {
                const char* temp = alloc_temp_d_reg(ctx);
                emit(ctx, "scvtf %s, %s", temp, right_reg);
                free_temp_reg(ctx, right_reg);
                right_reg = temp;
            }
            emit(ctx, "fmul %s, %s, %s", left_reg, left_reg, right_reg);
            free_temp_d_reg(ctx, right_reg);
        } else {
            emit(ctx, "mul %s, %s, %s", left_reg, left_reg, right_reg);
            free_temp_reg(ctx, right_reg);
        }
        return left_reg;
    } else if (binop->tablaOperaciones == &tablaOperacionesDivision) {
        bool is_float_op = left_reg[0] == 'd' || left_reg[0] == 's' || right_reg[0] == 'd' || right_reg[0] == 's';
        if (is_float_op) {
            if (left_reg[0] == 'x') {
                const char* temp = alloc_temp_d_reg(ctx);
                emit(ctx, "scvtf %s, %s", temp, left_reg);
                free_temp_reg(ctx, left_reg);
                left_reg = temp;
            }
            if (right_reg[0] == 'x') {
                const char* temp = alloc_temp_d_reg(ctx);
                emit(ctx, "scvtf %s, %s", temp, right_reg);
                free_temp_reg(ctx, right_reg);
                right_reg = temp;
            }
            emit(ctx, "fdiv %s, %s, %s", left_reg, left_reg, right_reg);
            free_temp_d_reg(ctx, right_reg);
        } else {
            emit(ctx, "sdiv %s, %s, %s", left_reg, left_reg, right_reg);
            free_temp_reg(ctx, right_reg);
        }
        return left_reg;
    }
    return left_reg;
}
