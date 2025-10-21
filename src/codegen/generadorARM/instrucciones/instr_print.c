#include "../../codegen.h"
#include "../../registroARM/regs.h"
#include "../../../ast/AbstractExpresion.h"
#include "../../../ast/nodos/instrucciones/instruccion/print.h"
#include "../../../ast/nodos/expresiones/terminales/primitivos.h"
#include "../../../ast/nodos/expresiones/expresiones.h"
#include "../../../ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "../../../ast/nodos/expresiones/relacionales/relacionales.h"
#include "../../../ast/nodos/expresiones/logicas/logicas.h"
#include "../../../ast/nodos/instrucciones/instruccion/funcion.h"
#include "../../../ast/nodos/expresiones/terminales/identificadores.h"
#include "../../../ast/nodos/expresiones/builtins.h"
#include "../../../context/result.h"
#include "../../../context/context.h"
#include <stdlib.h>
#include <string.h>

// Typedef for UnaryWrap (if needed)
typedef struct {
    AbstractExpresion base;
    AbstractExpresion* a;
} UnaryWrap;

void codegen_print_instr(CodegenContext* ctx, PrintExpresion* print) {
    emit(ctx, "# debug: entering codegen_print_instr");
    if (!print) return;
    if (print->base.numHijos > 0) {
        AbstractExpresion* lista = print->base.hijos[0];
        if (lista && lista->numHijos > 0) {
            AbstractExpresion* expr = lista->hijos[0];
            if (expr->interpret == interpretPrimitivoExpresion) {
                PrimitivoExpresion* prim = (PrimitivoExpresion*)expr;
                if (prim->tipo == STRING) {
                    emit_print_string(ctx, prim->valor);
                    return;
                } else if (prim->tipo == INT) {
                    int val = atoi(prim->valor);
                    emit_print_int_literal(ctx, val);
                    return;
                } else if (prim->tipo == FLOAT || prim->tipo == DOUBLE) {
                    int val = (int)atof(prim->valor);
                    emit_print_int_literal(ctx, val);
                    return;
                }
            }
            // Fallback: evaluate expression and print based on inferred type
            const char* reg = codegen_expr(ctx, expr);
            if (reg) {
                TipoDato tipo = get_expr_type(expr, ctx->symbol_ctx);
                if (tipo == STRING) {
                    emit_print_string_reg(ctx, reg);
                    free_temp_reg(ctx, reg);
                } else if (tipo == DOUBLE && reg[0] == 'd') {
                    const char* int_reg = alloc_temp_reg(ctx);
                    emit(ctx, "fcvtzs %s, %s", int_reg, reg);
                    free_temp_d_reg(ctx, reg);
                    emit_print_int(ctx, int_reg);
                    free_temp_reg(ctx, int_reg);
                } else if (tipo == FLOAT && reg[0] == 's') {
                    const char* int_reg = alloc_temp_reg(ctx);
                    emit(ctx, "fcvtzs %s, %s", int_reg, reg);
                    free_temp_s_reg(ctx, reg);
                    emit_print_int(ctx, int_reg);
                    free_temp_reg(ctx, int_reg);
                } else {
                    emit_print_int(ctx, reg);
                    free_temp_reg(ctx, reg);
                }
            }
        }
    }
}
