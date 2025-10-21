#include "../codegen.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/expresiones/terminales/primitivos.h"
#include "../../ast/nodos/expresiones/terminales/identificadores.h"
#include "../../ast/nodos/instrucciones/instruccion/print.h"
#include "../../ast/nodos/instrucciones/instrucciones.h"
#include "../../ast/nodos/instrucciones/instruccion/funcion.h"
#include "../../ast/nodos/instrucciones/bloque.h"
#include "../../ast/nodos/expresiones/expresiones.h"
#include "../../ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include <string.h>
#include "../../context/result.h"

// Function to get type of expression without executing
TipoDato get_expr_type(AbstractExpresion* expr, Context* ctx) {
    if (!expr) return VOID;
    if (expr->interpret == interpretPrimitivoExpresion) {
        return ((PrimitivoExpresion*)expr)->tipo;
    } else if (expr->interpret == interpretIdentificadorExpresion) {
        IdentificadorExpresion* id = (IdentificadorExpresion*)expr;
        Symbol* sym = buscarTablaSimbolos(ctx, id->nombre);
        return sym ? sym->tipo : VOID;
    } else if (expr->interpret == interpretExpresionLenguaje) {
        ExpresionLenguaje* binop = (ExpresionLenguaje*)expr;
        TipoDato left_type = get_expr_type(expr->hijos[0], ctx);
        TipoDato right_type = get_expr_type(expr->hijos[1], ctx);
        if (binop->tablaOperaciones == &tablaOperacionesSuma && (left_type == STRING || right_type == STRING)) {
            return STRING;
        }
        // For other binops, return left type or VOID
        return left_type != VOID ? left_type : right_type;
    } else if (expr->interpret == interpretLlamadaFuncion) {
        // For builtin String.valueOf, return STRING
        LlamadaFuncion* call = (LlamadaFuncion*)expr;
        if (strcmp(call->nombre, "String.valueOf") == 0) {
            return STRING;
        }
        return VOID;
    } else {
        // for other expressions, assume VOID
        return VOID;
    }
}

// Prototypes for register functions
#include "../registroARM/regs.h"
#include "../../ast/nodos/instrucciones/instruccion/declaracion.h"
#include "../../ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"
#include "../../ast/nodos/instrucciones/instruccion/if.h"
#include "../../ast/nodos/instrucciones/instruccion/while.h"
#include "../../ast/nodos/expresiones/relacionales/relacionales.h"
#include "../../ast/nodos/expresiones/logicas/logicas.h"
#include "../../ast/nodos/expresiones/cast.h"
#include "../../ast/nodos/expresiones/builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Typedef for UnaryWrap
typedef struct {
    AbstractExpresion base;
    AbstractExpresion* a;
} UnaryWrap;

// Declarations for split functions
const char* codegen_primitive(CodegenContext* ctx, PrimitivoExpresion* prim);
const char* codegen_binop_arithmetic(CodegenContext* ctx, ExpresionLenguaje* binop, const char* left_reg, const char* right_reg);
const char* codegen_binop_relational(CodegenContext* ctx, ExpresionLenguaje* binop, const char* left_reg, const char* right_reg);
const char* codegen_binop_logical(CodegenContext* ctx, ExpresionLenguaje* binop, const char* left_reg, const char* right_reg);
const char* codegen_binop_bitwise(CodegenContext* ctx, ExpresionLenguaje* binop, const char* left_reg, const char* right_reg);
const char* codegen_unop(CodegenContext* ctx, ExpresionLenguaje* unop, const char* operand_reg);
const char* codegen_cast(CodegenContext* ctx, CastExpresion* cast, const char* operand_reg);
const char* codegen_builtin_call(CodegenContext* ctx, LlamadaFuncion* call);
const char* codegen_string_value_of(CodegenContext* ctx, UnaryWrap* wrap);
const char* codegen_identifier(CodegenContext* ctx, IdentificadorExpresion* id);
void codegen_print_instr(CodegenContext* ctx, PrintExpresion* print);
void codegen_control_instr(CodegenContext* ctx, AbstractExpresion* instr);
void codegen_declaration_instr(CodegenContext* ctx, AbstractExpresion* instr);
#include "../../ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"
#include "../../ast/nodos/instrucciones/instruccion/if.h"
#include "../../ast/nodos/instrucciones/instruccion/while.h"
#include "../../ast/nodos/expresiones/relacionales/relacionales.h"
#include "../../ast/nodos/expresiones/logicas/logicas.h"
#include "../../ast/nodos/expresiones/cast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función auxiliar para compilar una expresión y devolver el registro con el resultado
const char* codegen_expr(CodegenContext* ctx, AbstractExpresion* expr) {
    if (!expr) return NULL;
    // printf("DEBUG codegen_expr: interpret = %p\n", expr->interpret);

    // Verificar si es un primitivo
    if (expr->interpret == interpretPrimitivoExpresion) {
        PrimitivoExpresion* prim = (PrimitivoExpresion*)expr;
        return codegen_primitive(ctx, prim);
    } else if (expr->interpret == interpretExpresionLenguaje) {
        ExpresionLenguaje* binop = (ExpresionLenguaje*)expr;
        if (binop->tablaOperaciones == &tablaOperacionesSuma) {
            TipoDato left_type = get_expr_type(expr->hijos[0], ctx->symbol_ctx);
            TipoDato right_type = get_expr_type(expr->hijos[1], ctx->symbol_ctx);
            if (left_type == STRING || right_type == STRING) {
                // String concat
                const char* left_reg;
                if (left_type == STRING) {
                    left_reg = codegen_expr(ctx, expr->hijos[0]);
                } else {
                    left_reg = codegen_string_value_of(ctx, expr->hijos[0]);
                }
                const char* right_reg;
                if (right_type == STRING) {
                    right_reg = codegen_expr(ctx, expr->hijos[1]);
                } else {
                    right_reg = codegen_string_value_of(ctx, expr->hijos[1]);
                }
                emit(ctx, "mov x0, %s", left_reg);
                emit(ctx, "mov x1, %s", right_reg);
                emit(ctx, "ldr x2, =temp_str");
                emit(ctx, "bl concat");
                const char* out = alloc_temp_reg(ctx);
                emit(ctx, "mov %s, x0", out);
                free_temp_reg(ctx, left_reg);
                free_temp_reg(ctx, right_reg);
                return out;
            }
        }
        // Handle string + expr or expr + string
        if (expr->hijos[0]->interpret == interpretPrimitivoExpresion && ((PrimitivoExpresion*)expr->hijos[0])->tipo == STRING) {
            if (expr->hijos[1]->interpret == interpretIdentificadorExpresion) {
                IdentificadorExpresion* id = (IdentificadorExpresion*)expr->hijos[1];
                Symbol* sym = buscarTablaSimbolos(ctx->symbol_ctx, id->nombre);
                if (sym && sym->valor) {
                    PrimitivoExpresion* left_prim = (PrimitivoExpresion*)expr->hijos[0];
                    char right_str[32];
                    if (sym->tipo == INT) {
                        sprintf(right_str, "%d", *(int*)sym->valor);
                    } else if (sym->tipo == FLOAT) {
                        sprintf(right_str, "%f", *(float*)sym->valor);
                    } else if (sym->tipo == DOUBLE) {
                        sprintf(right_str, "%f", *(double*)sym->valor);
                    } else if (sym->tipo == BOOLEAN) {
                        strcpy(right_str, *(int*)sym->valor ? "true" : "false");
                    } else {
                        strcpy(right_str, "unknown");
                    }
                    size_t len1 = strlen(left_prim->valor);
                    size_t len2 = strlen(right_str);
                    char* concat = (char*)malloc(len1 + len2 + 1);
                    strcpy(concat, left_prim->valor);
                    strcpy(concat + len1, right_str);
                    const char* label = new_label(ctx);
                    add_data(ctx, "%s: .asciz \"%s\\n\"", label, concat);
                    free(concat);
                    const char* reg = alloc_temp_reg(ctx);
                    emit(ctx, "ldr %s, =%s", reg, label);
                    return reg;
                }
            } else if (expr->hijos[1]->interpret == interpretLlamadaFuncion) {
                LlamadaFuncion* call = (LlamadaFuncion*)expr->hijos[1];
                if (strcmp(call->nombre, "String.valueOf") == 0 && call->args->numHijos == 1) {
                    AbstractExpresion* arg = call->args->hijos[0];
                    if (arg->interpret == interpretIdentificadorExpresion) {
                        IdentificadorExpresion* id = (IdentificadorExpresion*)arg;
                        Symbol* sym = buscarTablaSimbolos(ctx->symbol_ctx, id->nombre);
                        if (sym && sym->valor && sym->tipo == INT) {
                            PrimitivoExpresion* left_prim = (PrimitivoExpresion*)expr->hijos[0];
                            char right_str[32];
                            sprintf(right_str, "%d", *(int*)sym->valor);
                            size_t len1 = strlen(left_prim->valor);
                            size_t len2 = strlen(right_str);
                            char* concat = (char*)malloc(len1 + len2 + 1);
                            strcpy(concat, left_prim->valor);
                            strcpy(concat + len1, right_str);
                            const char* label = new_label(ctx);
                            add_data(ctx, "%s: .asciz \"%s\\n\"", label, concat);
                            free(concat);
                            const char* reg = alloc_temp_reg(ctx);
                            emit(ctx, "ldr %s, =%s", reg, label);
                            return reg;
                        }
                    }
                }
            }
            const char* left_reg = codegen_expr(ctx, expr->hijos[0]);
            return left_reg;
        } else if (expr->hijos[1]->interpret == interpretPrimitivoExpresion && ((PrimitivoExpresion*)expr->hijos[1])->tipo == STRING) {
            const char* right_reg = codegen_expr(ctx, expr->hijos[1]);
            return right_reg;
        }
        // Check types for general concat
        TipoDato left_type = get_expr_type(expr->hijos[0], ctx->symbol_ctx);
        TipoDato right_type = get_expr_type(expr->hijos[1], ctx->symbol_ctx);
        if (left_type == STRING && right_type == STRING) {
            // string + string
            const char* left_reg = codegen_expr(ctx, expr->hijos[0]);
            const char* right_reg = codegen_expr(ctx, expr->hijos[1]);
            // Concat
            emit(ctx, "ldr x2, =temp_str");
            emit(ctx, "mov x0, %s", left_reg);
            emit(ctx, "mov x1, %s", right_reg);
            emit(ctx, "bl concat");
            const char* result_reg = alloc_temp_reg(ctx);
            emit(ctx, "mov %s, x0", result_reg);
            free_temp_reg(ctx, left_reg);
            free_temp_reg(ctx, right_reg);
            return result_reg;
        } else if (left_type == STRING && right_type != STRING) {
            // string + non-string
            const char* left_reg = codegen_expr(ctx, expr->hijos[0]);
            const char* right_reg = codegen_expr(ctx, expr->hijos[1]);
            // Convert right to string
            emit(ctx, "ldr x1, =temp_str");
            emit(ctx, "mov x0, %s", right_reg);
            emit(ctx, "bl itoa");
            // Concat
            emit(ctx, "mov x0, %s", left_reg);
            emit(ctx, "mov x1, x0");  // result of itoa
            emit(ctx, "ldr x2, =temp_str");
            emit(ctx, "bl concat");
            const char* result_reg = alloc_temp_reg(ctx);
            emit(ctx, "mov %s, x0", result_reg);
            free_temp_reg(ctx, left_reg);
            free_temp_reg(ctx, right_reg);
            return result_reg;
        } else if (left_type != STRING && right_type == STRING) {
            // non-string + string, return right
            return codegen_expr(ctx, expr->hijos[1]);
        }
        // Normal binop
        const char* left_reg = codegen_expr(ctx, expr->hijos[0]);
        const char* right_reg = codegen_expr(ctx, expr->hijos[1]);
        if (binop->tablaOperaciones == &tablaOperacionesSuma || binop->tablaOperaciones == &tablaOperacionesResta || binop->tablaOperaciones == &tablaOperacionesMultiplicacion || binop->tablaOperaciones == &tablaOperacionesDivision) {
            return codegen_binop_arithmetic(ctx, binop, left_reg, right_reg);
        } else if (binop->tablaOperaciones == &tablaOperacionesMayorQue || binop->tablaOperaciones == &tablaOperacionesMenorQue || binop->tablaOperaciones == &tablaOperacionesMayorIgualQue || binop->tablaOperaciones == &tablaOperacionesMenorIgualQue || binop->tablaOperaciones == &tablaOperacionesIgualdad || binop->tablaOperaciones == &tablaOperacionesDesigualdad) {
            // Get types
            TipoDato left_type = get_expr_type(expr->hijos[0], ctx->symbol_ctx);
            TipoDato right_type = get_expr_type(expr->hijos[1], ctx->symbol_ctx);
            if (left_type == STRING || right_type == STRING) {
                if (binop->tablaOperaciones == &tablaOperacionesIgualdad) {
                    // string ==
                    emit(ctx, "mov x0, %s", left_reg);
                    emit(ctx, "mov x1, %s", right_reg);
                    emit(ctx, "bl strcmp");
                    emit(ctx, "cmp x0, #0");
                    emit(ctx, "cset %s, eq", left_reg);
                    free_temp_reg(ctx, right_reg);
                    return left_reg;
                } else if (binop->tablaOperaciones == &tablaOperacionesDesigualdad) {
                    // string !=
                    emit(ctx, "mov x0, %s", left_reg);
                    emit(ctx, "mov x1, %s", right_reg);
                    emit(ctx, "bl strcmp");
                    emit(ctx, "cmp x0, #0");
                    emit(ctx, "cset %s, ne", left_reg);
                    free_temp_reg(ctx, right_reg);
                    return left_reg;
                } else {
                    // error, no > < for strings
                    return NULL;
                }
            } else {
                return codegen_binop_relational(ctx, binop, left_reg, right_reg);
            }
        } else if (binop->tablaOperaciones == &tablaOperacionesAnd || binop->tablaOperaciones == &tablaOperacionesOr) {
            return codegen_binop_logical(ctx, binop, left_reg, right_reg);
        } else {
            return codegen_binop_bitwise(ctx, binop, left_reg, right_reg);
        }
    } else if (expr->interpret == interpretUnarioLenguaje) {
        ExpresionLenguaje* unop = (ExpresionLenguaje*)expr;
        const char* operand_reg = codegen_expr(ctx, expr->hijos[0]);
        return codegen_unop(ctx, unop, operand_reg);
    } else if (expr->interpret == interpretCastExpresion) {
        CastExpresion* cast = (CastExpresion*)expr;
        const char* operand_reg = codegen_expr(ctx, expr->hijos[0]);
        return codegen_cast(ctx, cast, operand_reg);
    } else if (expr->interpret == interpretLlamadaFuncion) {
        LlamadaFuncion* call = (LlamadaFuncion*)expr;
        return codegen_builtin_call(ctx, call);
    } else if (1) { // expr->interpret == interpretStringValueOf
        UnaryWrap* wrap = (UnaryWrap*)expr;
        return codegen_string_value_of(ctx, wrap);
    } else if (expr->interpret == interpretIdentificadorExpresion) {
        IdentificadorExpresion* id = (IdentificadorExpresion*)expr;
        return codegen_identifier(ctx, id);
    }

    return NULL;
}

// Placeholder para compilar una instrucción
void codegen_instr(CodegenContext* ctx, AbstractExpresion* instr) {
    // printf("DEBUG codegen_instr: interpret = %p\n", instr->interpret);
    if (instr->interpret == interpretPrintExpresion) {
        codegen_print_instr(ctx, (PrintExpresion*)instr);
    } else if (instr->interpret == interpretInstrucciones) {
        // Procesar lista de instrucciones
        for (size_t i = 0; i < instr->numHijos; i++) {
            codegen_instr(ctx, instr->hijos[i]);
        }
    } else if (instr->interpret == interpretFuncionDeclaracion) {
        // Procesar declaración de función (por ahora solo main)
        FuncionDecl* f = (FuncionDecl*)instr;
        codegen_node(ctx, f->cuerpo);
    } else if (instr->interpret == interpretBloqueExpresion) {
        // Procesar bloque
        for (size_t i = 0; i < instr->numHijos; i++) {
            codegen_instr(ctx, instr->hijos[i]);
        }
    } else if (instr->interpret == interpretDeclaracionVariable || instr->interpret == interpretAsignacionExpresion) {
        codegen_declaration_instr(ctx, instr);
    } else if (instr->interpret == interpretIfExpresion || instr->interpret == interpretWhileExpresion) {
        codegen_control_instr(ctx, instr);
    }
    // TODO: otras instrucciones
}