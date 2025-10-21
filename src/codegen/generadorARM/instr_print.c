#include "../codegen.h"
#include "../registroARM/regs.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/instrucciones/instruccion/print.h"
#include "../../ast/nodos/expresiones/terminales/primitivos.h"
#include "../../ast/nodos/expresiones/expresiones.h"
#include "../../ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "../../ast/nodos/expresiones/relacionales/relacionales.h"
#include "../../ast/nodos/expresiones/logicas/logicas.h"
#include "../../ast/nodos/instrucciones/instruccion/funcion.h"
#include "../../ast/nodos/expresiones/terminales/identificadores.h"
#include "../../ast/nodos/expresiones/builtins.h"
#include "../../context/result.h"
#include "../../context/context.h"
#include <stdlib.h>
#include <string.h>

// Función auxiliar para obtener tipo de expresión
TipoDato get_expr_type_instr(AbstractExpresion* expr, Context* ctx) {
    if (!expr) return VOID;
    if (expr->interpret == interpretPrimitivoExpresion) {
        return ((PrimitivoExpresion*)expr)->tipo;
    } else if (expr->interpret == interpretIdentificadorExpresion) {
        IdentificadorExpresion* id = (IdentificadorExpresion*)expr;
        Symbol* sym = buscarTablaSimbolos(ctx, id->nombre);
        return sym ? sym->tipo : VOID;
    } else if (expr->interpret == interpretExpresionLenguaje) {
        ExpresionLenguaje* binop = (ExpresionLenguaje*)expr;
        if (binop->tablaOperaciones == &tablaOperacionesSuma) {
            TipoDato left = get_expr_type_instr(expr->hijos[0], ctx);
            TipoDato right = get_expr_type_instr(expr->hijos[1], ctx);
            if (left == STRING || right == STRING) return STRING;
            // Para aritméticas, asumir el tipo dominante
            if (left == DOUBLE || right == DOUBLE) return DOUBLE;
            if (left == FLOAT || right == FLOAT) return FLOAT;
            return INT;
        } else if (binop->tablaOperaciones == &tablaOperacionesIgualdad || binop->tablaOperaciones == &tablaOperacionesDesigualdad ||
                   binop->tablaOperaciones == &tablaOperacionesMayorQue || binop->tablaOperaciones == &tablaOperacionesMenorQue ||
                   binop->tablaOperaciones == &tablaOperacionesMayorIgualQue || binop->tablaOperaciones == &tablaOperacionesMenorIgualQue) {
            return BOOLEAN;
        }
        // Otras operaciones, asumir INT
        return INT;
    } else if (expr->interpret == interpretLlamadaFuncion) {
        LlamadaFuncion* call = (LlamadaFuncion*)expr;
        if (strcmp(call->nombre, "String.valueOf") == 0) {
            return STRING;
        }
        // Otras funciones, asumir VOID
        return VOID;
    } else {
        // Para otras expresiones, asumir VOID
        return VOID;
    }
}

// Función para compilar instrucciones de print
void codegen_print_instr(CodegenContext* ctx, PrintExpresion* print) {
    emit(ctx, "# debug: entering codegen_print_instr");
    // Asumir lista expresiones
    if (print->base.numHijos > 0) {
        AbstractExpresion* lista = print->base.hijos[0];
        if (lista->numHijos > 0) {
            AbstractExpresion* expr = lista->hijos[0];
            if (expr->interpret == interpretPrimitivoExpresion) {
                PrimitivoExpresion* prim = (PrimitivoExpresion*)expr;
                if (prim->tipo == STRING) {
                    emit_print_string(ctx, prim->valor);
                } else if (prim->tipo == INT) {
                    int val = atoi(prim->valor);
                    emit_print_int_literal(ctx, val);
                } else if (prim->tipo == FLOAT || prim->tipo == DOUBLE) {
                    // Convertir a int y print
                    int val = (int)atof(prim->valor);
                    emit_print_int_literal(ctx, val);
                }
            } else {
                // Evaluar expresión
                const char* reg = codegen_expr(ctx, expr);
                if (reg) {
                    TipoDato tipo = get_expr_type_instr(expr, ctx->symbol_ctx);
                    if (tipo == STRING || expr->interpret == interpretLlamadaFuncion || (expr->interpret == interpretExpresionLenguaje && ((ExpresionLenguaje*)expr)->tablaOperaciones == &tablaOperacionesSuma) || expr->interpret == interpretIdentificadorExpresion || expr->interpret == interpretStringValueOf) {
                        emit_print_string_reg(ctx, reg);
                        free_temp_reg(ctx, reg);
                    } else if (tipo == DOUBLE && reg[0] == 'd') {
                        // Double, convertir a int
                        const char* int_reg = alloc_temp_reg(ctx);
                        emit(ctx, "fcvtzs %s, %s", int_reg, reg);
                        free_temp_d_reg(ctx, reg);
                        emit_print_int(ctx, int_reg);
                        free_temp_reg(ctx, int_reg);
                    } else if (tipo == FLOAT && reg[0] == 's') {
                        // Float, convertir a int
                        const char* int_reg = alloc_temp_reg(ctx);
                        emit(ctx, "fcvtzs %s, %s", int_reg, reg);
                        free_temp_s_reg(ctx, reg);
                        emit_print_int(ctx, int_reg);
                        free_temp_reg(ctx, int_reg);
                    } else {
                        // Asumir int o boolean
                        emit_print_int(ctx, reg);
                        free_temp_reg(ctx, reg);
                    }
                }
            }
        }
    }
}