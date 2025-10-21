#include "../../codegen.h"
#include "../../registroARM/regs.h"
#include "../../../ast/AbstractExpresion.h"
#include "../../../ast/nodos/instrucciones/instruccion/declaracion.h"
#include "../../../ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"
#include "../../../ast/nodos/expresiones/terminales/primitivos.h"

// Función para compilar instrucciones de declaraciones y asignaciones
void codegen_declaration_instr(CodegenContext* ctx, AbstractExpresion* instr) {
    if (instr->interpret == interpretDeclaracionVariable) {
        DeclaracionVariable* decl = (DeclaracionVariable*)instr;
        // Asumir variables locales, usar stack
        int size = 8; // por ahora 8 bytes para todo
        ctx->stack_offset += size;
        int offset = -ctx->stack_offset;
        // Si tiene inicialización
        if (instr->numHijos > 0) {
            AbstractExpresion* init = instr->hijos[0];
            const char* init_reg = codegen_expr(ctx, init);
            if (init_reg) {
                emit(ctx, "str %s, [sp, #%d]", init_reg, offset);
                if (init_reg[0] == 'd') {
                    free_temp_d_reg(ctx, init_reg);
                } else if (init_reg[0] == 's') {
                    free_temp_s_reg(ctx, init_reg);
                } else {
                    free_temp_reg(ctx, init_reg);
                }
            }
        }
        // Registrar en tabla de símbolos con offset
        // Por ahora, no se hace nada más
    } else if (instr->interpret == interpretAsignacionExpresion) {
        // Assignment, similar
        AsignacionExpresion* asign = (AsignacionExpresion*)instr;
        const char* reg = codegen_expr(ctx, instr->hijos[0]);
        if (reg) {
            // Asumir offset conocido, por ahora hardcode o buscar
            // Para simplificar, asumir offset 0 para pruebas
            emit(ctx, "str %s, [sp, #0]", reg);
            if (reg[0] == 'd') {
                free_temp_d_reg(ctx, reg);
            } else if (reg[0] == 's') {
                free_temp_s_reg(ctx, reg);
            } else {
                free_temp_reg(ctx, reg);
            }
        }
    }
}
