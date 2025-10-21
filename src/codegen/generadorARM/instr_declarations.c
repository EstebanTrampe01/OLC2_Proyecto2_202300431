#include "../codegen.h"
#include "../registroARM/regs.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/instrucciones/instruccion/declaracion.h"
#include "../../ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"
#include "../../ast/nodos/expresiones/terminales/primitivos.h"

// Función para compilar instrucciones de declaraciones y asignaciones
void codegen_declaration_instr(CodegenContext* ctx, AbstractExpresion* instr) {
    if (instr->interpret == interpretDeclaracionVariable) {
        DeclaracionVariable* decl = (DeclaracionVariable*)instr;
        // Declaración de variable global
        if (instr->numHijos > 0) {
            // Tiene inicialización
            AbstractExpresion* init = instr->hijos[0];
            if (init->interpret == interpretPrimitivoExpresion) {
                PrimitivoExpresion* prim = (PrimitivoExpresion*)init;
                if (prim->tipo == INT) {
                    int val = atoi(prim->valor);
                    add_data(ctx, "%s: .word %d", decl->nombre, val);
                } else if (prim->tipo == DOUBLE) {
                    double val = atof(prim->valor);
                    add_data(ctx, "%s: .double %f", decl->nombre, val);
                } else if (prim->tipo == FLOAT) {
                    float val = atof(prim->valor);
                    add_data(ctx, "%s: .float %f", decl->nombre, val);
                } else if (prim->tipo == STRING) {
                    add_data(ctx, "%s: .asciz \"%s\"", decl->nombre, prim->valor ? prim->valor : "");
                } else {
                    // Para otros tipos, por ahora .word 0
                    add_data(ctx, "%s: .word 0", decl->nombre);
                }
            } else {
                // Expresión compleja
                if (decl->tipo == DOUBLE) {
                    add_data(ctx, "%s: .double 0.0", decl->nombre);
                } else if (decl->tipo == FLOAT) {
                    add_data(ctx, "%s: .float 0.0", decl->nombre);
                } else {
                    add_data(ctx, "%s: .quad 0", decl->nombre);
                }
                // Generar código para calcular y asignar
                const char* init_reg = codegen_expr(ctx, init);
                if (init_reg) {
                    const char* addr_reg = alloc_temp_reg(ctx);
                    emit(ctx, "ldr %s, =%s", addr_reg, decl->nombre);
                    emit(ctx, "str %s, [%s]", init_reg, addr_reg);
                    free_temp_reg(ctx, addr_reg);
                    if (init_reg[0] == 'd') {
                        free_temp_d_reg(ctx, init_reg);
                    } else if (init_reg[0] == 's') {
                        free_temp_s_reg(ctx, init_reg);
                    } else {
                        free_temp_reg(ctx, init_reg);
                    }
                }
            }
        } else {
            add_data(ctx, "%s: .double 0.0", decl->nombre);
        }
    } else if (instr->interpret == interpretAsignacionExpresion) {
        AsignacionExpresion* asign = (AsignacionExpresion*)instr;
        // Assignment
        const char* reg = codegen_expr(ctx, instr->hijos[0]);
        if (reg) {
            const char* addr_reg = alloc_temp_reg(ctx);
            emit(ctx, "ldr %s, =%s", addr_reg, asign->nombre);
            emit(ctx, "str %s, [%s]", reg, addr_reg);
            free_temp_reg(ctx, addr_reg);
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