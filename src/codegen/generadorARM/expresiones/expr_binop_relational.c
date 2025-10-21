#include "../../codegen.h"
#include "../../../ast/AbstractExpresion.h"
#include "../../../ast/nodos/expresiones/expresiones.h"
#include "../../../ast/nodos/expresiones/relacionales/relacionales.h"

// Función para compilar operaciones relacionales binarias
const char* codegen_binop_relational(CodegenContext* ctx, ExpresionLenguaje* binop, const char* left_reg, const char* right_reg) {
    if (binop->tablaOperaciones == &tablaOperacionesMayorQue) {
        emit(ctx, "cmp %s, %s", left_reg, right_reg);
        emit(ctx, "cset %s, gt", left_reg);
        free_temp_reg(ctx, right_reg);
        return left_reg;
    } else if (binop->tablaOperaciones == &tablaOperacionesMenorQue) {
        emit(ctx, "cmp %s, %s", left_reg, right_reg);
        emit(ctx, "cset %s, lt", left_reg);
        free_temp_reg(ctx, right_reg);
        return left_reg;
    } else if (binop->tablaOperaciones == &tablaOperacionesMayorIgualQue) {
        emit(ctx, "cmp %s, %s", left_reg, right_reg);
        emit(ctx, "cset %s, ge", left_reg);
        free_temp_reg(ctx, right_reg);
        return left_reg;
    } else if (binop->tablaOperaciones == &tablaOperacionesMenorIgualQue) {
        emit(ctx, "cmp %s, %s", left_reg, right_reg);
        emit(ctx, "cset %s, le", left_reg);
        free_temp_reg(ctx, right_reg);
        return left_reg;
    } else if (binop->tablaOperaciones == &tablaOperacionesIgualdad) {
        emit(ctx, "cmp %s, %s", left_reg, right_reg);
        emit(ctx, "cset %s, eq", left_reg);
        free_temp_reg(ctx, right_reg);
        return left_reg;
    } else if (binop->tablaOperaciones == &tablaOperacionesDesigualdad) {
        emit(ctx, "cmp %s, %s", left_reg, right_reg);
        emit(ctx, "cset %s, ne", left_reg);
        free_temp_reg(ctx, right_reg);
        return left_reg;
    }
    return left_reg;
}
