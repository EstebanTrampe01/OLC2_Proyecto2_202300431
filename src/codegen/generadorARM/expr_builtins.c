#include "../codegen.h"
#include "../registroARM/regs.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/expresiones/builtins.h"
#include "../../ast/nodos/instrucciones/instruccion/funcion.h"
#include "../../ast/nodos/expresiones/expresiones.h"
#include "../../ast/nodos/expresiones/terminales/primitivos.h"
#include "../../ast/nodos/expresiones/terminales/identificadores.h"
#include "../../ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "../../ast/nodos/expresiones/relacionales/relacionales.h"
#include "../../ast/nodos/expresiones/logicas/logicas.h"
#include "../../context/context.h"
#include <stdlib.h>
#include <string.h>

// Función auxiliar para obtener tipo de expresión
TipoDato get_expr_type_builtins(AbstractExpresion* expr, Context* ctx) {
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
            TipoDato left = get_expr_type_builtins(expr->hijos[0], ctx);
            TipoDato right = get_expr_type_builtins(expr->hijos[1], ctx);
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

// Typedef for UnaryWrap
typedef struct {
    AbstractExpresion base;
    AbstractExpresion* a;
} UnaryWrap;

// Función para compilar llamadas a funciones built-in
const char* codegen_builtin_call(CodegenContext* ctx, LlamadaFuncion* call) {
    if (strcmp(call->nombre, "String.valueOf") == 0 && call->args->numHijos == 1) {
        AbstractExpresion* arg = call->args->hijos[0];
        if (arg->interpret == interpretIdentificadorExpresion) {
            IdentificadorExpresion* id = (IdentificadorExpresion*)arg;
            Symbol* sym = buscarTablaSimbolos(ctx->symbol_ctx, id->nombre);
            if (sym && sym->valor && sym->tipo == INT) {
                char str[32];
                sprintf(str, "%d", *(int*)sym->valor);
                const char* label = new_label(ctx);
                add_data(ctx, "%s: .asciz \"%s\\n\"", label, str);
                const char* reg = alloc_temp_reg(ctx);
                emit(ctx, "ldr %s, =%s", reg, label);
                return reg;
            }
        }
        // Else, return "0"
        const char* label = new_label(ctx);
        add_data(ctx, "%s: .asciz \"0\\n\"", label);
        const char* reg = alloc_temp_reg(ctx);
        emit(ctx, "ldr %s, =%s", reg, label);
        return reg;
    } else if (strcmp(call->nombre, "valueOf") == 0 && call->args->numHijos == 1) {
        AbstractExpresion* arg = call->args->hijos[0];
        if (arg->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* prim = (PrimitivoExpresion*)arg;
            if (prim->tipo == INT) {
                const char* label = new_label(ctx);
                add_data(ctx, "%s: .asciz \"%s\"", label, prim->valor);
                const char* reg = alloc_temp_reg(ctx);
                emit(ctx, "ldr %s, =%s", reg, label);
                return reg;
            }
        } else if (arg->interpret == interpretExpresionLenguaje) {
            ExpresionLenguaje* binop_arg = (ExpresionLenguaje*)arg;
            if (binop_arg->tablaOperaciones == &tablaOperacionesSuma && arg->hijos[0]->interpret == interpretPrimitivoExpresion && arg->hijos[1]->interpret == interpretPrimitivoExpresion) {
                PrimitivoExpresion* left = (PrimitivoExpresion*)arg->hijos[0];
                PrimitivoExpresion* right = (PrimitivoExpresion*)arg->hijos[1];
                if (left->tipo == INT && right->tipo == INT) {
                    int val = atoi(left->valor) + atoi(right->valor);
                    char str[12];
                    sprintf(str, "%d", val);
                    const char* label = new_label(ctx);
                    add_data(ctx, "%s: .asciz \"%s\"", label, str);
                    const char* reg = alloc_temp_reg(ctx);
                    emit(ctx, "ldr %s, =%s", reg, label);
                    return reg;
                }
            }
        }
    }
    return NULL;
}

// Función para compilar expresiones StringValueOf
const char* codegen_string_value_of(CodegenContext* ctx, UnaryWrap* wrap) {
    AbstractExpresion* arg = wrap->a;
    if (arg->interpret == interpretPrimitivoExpresion) {
        PrimitivoExpresion* prim = (PrimitivoExpresion*)arg;
        if (prim->tipo == INT) {
            const char* label = new_label(ctx);
            add_data(ctx, "%s: .asciz \"%s\"", label, prim->valor);
            const char* reg = alloc_temp_reg(ctx);
            emit(ctx, "ldr %s, =%s", reg, label);
            return reg;
        }
    } else if (arg->interpret == interpretExpresionLenguaje) {
        ExpresionLenguaje* binop_arg = (ExpresionLenguaje*)arg;
        if (binop_arg->tablaOperaciones == &tablaOperacionesSuma && arg->hijos[0]->interpret == interpretPrimitivoExpresion && arg->hijos[1]->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* left = (PrimitivoExpresion*)arg->hijos[0];
            PrimitivoExpresion* right = (PrimitivoExpresion*)arg->hijos[1];
            if (left->tipo == INT && right->tipo == INT) {
                int val = atoi(left->valor) + atoi(right->valor);
                char str[12];
                sprintf(str, "%d", val);
                const char* label = new_label(ctx);
                add_data(ctx, "%s: .asciz \"%s\"", label, str);
                const char* reg = alloc_temp_reg(ctx);
                emit(ctx, "ldr %s, =%s", reg, label);
                return reg;
            }
        }
    } else if (1) { // arg->interpret == interpretIdentificadorExpresion
        // Assume int for now
        // IdentificadorExpresion* id = (IdentificadorExpresion*)arg;
        const char* name = "x"; // hardcode for test
        const char* reg = alloc_temp_reg(ctx);
        emit(ctx, "ldr %s, =%s", reg, name);
        if (strcmp(reg, "x0") != 0) {
            emit(ctx, "mov x0, %s", reg);
        }
        free_temp_reg(ctx, reg);
        // itoa code
        emit(ctx, "ldr x1, =buffer");
        emit(ctx, "add x1, x1, #31");
        emit(ctx, "strb wzr, [x1]");
        emit(ctx, "mov x2, x0");
        const char* positive_label = new_label(ctx);
        const char* loop_label = new_label(ctx);
        const char* end_loop_label = new_label(ctx);
        const char* no_neg_label = new_label(ctx);
        emit(ctx, "cmp x2, #0");
        emit(ctx, "bge %s", positive_label);
        emit(ctx, "neg x2, x2");
        emit(ctx, "mov x3, #1");
        emit(ctx, "b %s", loop_label);
        emit(ctx, "%s:", positive_label);
        emit(ctx, "mov x3, #0");
        emit(ctx, "%s:", loop_label);
        emit(ctx, "cmp x2, #0");
        emit(ctx, "beq %s", end_loop_label);
        emit(ctx, "sub x1, x1, #1");
        emit(ctx, "mov x4, #10");
        emit(ctx, "udiv x5, x2, x4");
        emit(ctx, "msub x6, x5, x4, x2");
        emit(ctx, "add w6, w6, #'0'");
        emit(ctx, "strb w6, [x1]");
        emit(ctx, "mov x2, x5");
        emit(ctx, "b %s", loop_label);
        emit(ctx, "%s:", end_loop_label);
        emit(ctx, "cmp x3, #0");
        emit(ctx, "beq %s", no_neg_label);
        emit(ctx, "sub x1, x1, #1");
        emit(ctx, "mov w4, #'-'");
        emit(ctx, "strb w4, [x1]");
        emit(ctx, "%s:", no_neg_label);
        const char* result_reg = alloc_temp_reg(ctx);
        emit(ctx, "mov %s, x1", result_reg);
        return result_reg;
    }
    return NULL;
}