#include "../codegen.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/expresiones/expresiones.h"

// Función para compilar operaciones unarias
const char* codegen_unop(CodegenContext* ctx, ExpresionLenguaje* unop, const char* operand_reg) {
    if (unop->tipo == NOT) {
        // !
        emit(ctx, "cmp %s, #0", operand_reg);
        emit(ctx, "cset %s, eq", operand_reg);
        return operand_reg;
    } else if (unop->tipo == MENOS) {
        // -
        emit(ctx, "neg %s, %s", operand_reg, operand_reg);
        return operand_reg;
    } else {
        // Otro unario, por ahora devolver operand
        return operand_reg;
    }
}