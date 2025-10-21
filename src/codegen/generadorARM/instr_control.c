#include "../codegen.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/instrucciones/instruccion/if.h"
#include "../../ast/nodos/instrucciones/instruccion/while.h"

// Función para compilar instrucciones de control (if, while)
void codegen_control_instr(CodegenContext* ctx, AbstractExpresion* instr) {
    if (instr->interpret == interpretIfExpresion) {
        // If statement
        IfExpresion* if_stmt = (IfExpresion*)instr;
        const char* cond_reg = codegen_expr(ctx, if_stmt->condicion);
        const char* else_label = new_label(ctx);
        const char* end_label = new_label(ctx);
        emit(ctx, "cmp %s, #0", cond_reg);
        emit(ctx, "beq %s", else_label);
        free_temp_reg(ctx, cond_reg);
        codegen_instr(ctx, if_stmt->bloqueIf);
        emit(ctx, "b %s", end_label);
        emit(ctx, "%s:", else_label);
        if (if_stmt->bloqueElse) {
            codegen_instr(ctx, if_stmt->bloqueElse);
        }
        emit(ctx, "%s:", end_label);
    } else if (instr->interpret == interpretWhileExpresion) {
        WhileExpresion* while_stmt = (WhileExpresion*)instr;
        const char* loop_label = new_label(ctx);
        const char* end_label = new_label(ctx);
        emit(ctx, "%s:", loop_label);
        const char* cond_reg = codegen_expr(ctx, while_stmt->condition);
        emit(ctx, "cmp %s, #0", cond_reg);
        emit(ctx, "beq %s", end_label);
        free_temp_reg(ctx, cond_reg);
        codegen_instr(ctx, while_stmt->body);
        emit(ctx, "b %s", loop_label);
        emit(ctx, "%s:", end_label);
    }
}