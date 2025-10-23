#include "emit_expr.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "codegen/literals.h"

// Declaraciones externas utilizadas para identificar tipos de nodos
extern Result interpretPrimitivoExpresion(AbstractExpresion*, Context*);
extern Result interpretIdentificadorExpresion(AbstractExpresion*, Context*);
extern Result interpretExpresionLenguaje(AbstractExpresion*, Context*);
extern Result interpretLlamadaFuncion(AbstractExpresion*, Context*);

void arm_emit_eval_expr(CodegenContext* ctx, AbstractExpresion* expr, int target_reg, FILE* f) {
    if (!expr || !f) return;

    // Primitivos: INT, STRING, DOUBLE
    if (expr->interpret == interpretPrimitivoExpresion) {
        typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr;
        Pr* p = (Pr*) expr;
        if (p && p->valor) {
            if (p->tipo == STRING) {
                int id = codegen_register_strlit(NULL, p->valor);
                fprintf(f, "    adrp x%d, STRLIT_%d\n", target_reg, id);
                fprintf(f, "    add x%d, x%d, :lo12:STRLIT_%d\n", target_reg, target_reg, id);
                return;
            } else if (p->tipo == INT) {
                fprintf(f, "    mov x%d, #%s\n", target_reg, p->valor);
                return;
            } else if (p->tipo == DOUBLE) {
                int id = codegen_register_numlit(NULL, p->valor);
                fprintf(f, "    adrp x%d, NUMLIT_%d\n", target_reg, id);
                fprintf(f, "    ldr x%d, [x%d, :lo12:NUMLIT_%d]\n", target_reg, target_reg, id);
                return;
            }
        }
        fprintf(f, "    mov x%d, #0\n", target_reg);
        return;
    }

    // Identificadores globales
    if (expr->interpret == interpretIdentificadorExpresion) {
        typedef struct { AbstractExpresion base; char* nombre; } Id;
        Id* id = (Id*) expr;
        if (id && id->nombre) {
            fprintf(f, "    adrp x%d, GV_%s\n", target_reg, id->nombre);
            fprintf(f, "    add x%d, x%d, :lo12:GV_%s\n", target_reg, target_reg, id->nombre);
            fprintf(f, "    ldr x%d, [x%d]\n", target_reg, target_reg);
            return;
        }
        fprintf(f, "    mov x%d, #0\n", target_reg);
        return;
    }

    // Expresiones unarias (como NOT)
    if (expr->interpret == interpretUnarioLenguaje) {
        ExpresionLenguaje* el = (ExpresionLenguaje*) expr;
        extern Operacion tablaOperacionesNot[TIPO_COUNT][TIPO_COUNT];
        
        if (el->tablaOperaciones == &tablaOperacionesNot) {
            arm_emit_eval_expr(ctx, el->base.hijos ? el->base.hijos[0] : NULL, 9, f);
            fprintf(f, "    cmp x9, #0\n");
            fprintf(f, "    cset x%d, eq\n", target_reg); // 1 si x9==0, 0 si x9!=0
            return;
        }
    }

    // Expresiones básicas aritméticas (enteros)
    if (expr->interpret == interpretExpresionLenguaje) {
        ExpresionLenguaje* el = (ExpresionLenguaje*) expr;
        
        // Verificar si es una operación aritmética o relacional usando tablaOperaciones
        extern Operacion tablaOperacionesSuma[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesResta[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesMultiplicacion[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesDivision[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesModulo[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesIgualdad[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesDesigualdad[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesMayorQue[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesMenorQue[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesMayorIgualQue[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesMenorIgualQue[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesAnd[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesOr[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesNot[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesBitAnd[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesBitOr[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesBitXor[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesShiftLeft[TIPO_COUNT][TIPO_COUNT];
        extern Operacion tablaOperacionesShiftRight[TIPO_COUNT][TIPO_COUNT];
        
        if (el->tablaOperaciones == &tablaOperacionesSuma ||
            el->tablaOperaciones == &tablaOperacionesResta ||
            el->tablaOperaciones == &tablaOperacionesMultiplicacion ||
            el->tablaOperaciones == &tablaOperacionesDivision ||
            el->tablaOperaciones == &tablaOperacionesModulo ||
            el->tablaOperaciones == &tablaOperacionesIgualdad ||
            el->tablaOperaciones == &tablaOperacionesDesigualdad ||
            el->tablaOperaciones == &tablaOperacionesMayorQue ||
            el->tablaOperaciones == &tablaOperacionesMenorQue ||
            el->tablaOperaciones == &tablaOperacionesMayorIgualQue ||
            el->tablaOperaciones == &tablaOperacionesMenorIgualQue ||
            el->tablaOperaciones == &tablaOperacionesAnd ||
            el->tablaOperaciones == &tablaOperacionesOr ||
            el->tablaOperaciones == &tablaOperacionesNot ||
            el->tablaOperaciones == &tablaOperacionesBitAnd ||
            el->tablaOperaciones == &tablaOperacionesBitOr ||
            el->tablaOperaciones == &tablaOperacionesBitXor ||
            el->tablaOperaciones == &tablaOperacionesShiftLeft ||
            el->tablaOperaciones == &tablaOperacionesShiftRight) {
            
            arm_emit_eval_expr(ctx, el->base.hijos ? el->base.hijos[0] : NULL, 9, f);
            arm_emit_eval_expr(ctx, el->base.hijos && el->base.hijos[1] ? el->base.hijos[1] : NULL, 10, f);
            
            if (el->tablaOperaciones == &tablaOperacionesSuma) {
                fprintf(f, "    add x%d, x9, x10\n", target_reg);
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesResta) {
                fprintf(f, "    sub x%d, x9, x10\n", target_reg);
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMultiplicacion) {
                fprintf(f, "    mul x%d, x9, x10\n", target_reg);
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesDivision) {
                fprintf(f, "    mov x0, x9\n");
                fprintf(f, "    mov x1, x10\n");
                fprintf(f, "    bl div_helper\n");
                fprintf(f, "    mov x%d, x0\n", target_reg);
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesModulo) {
                fprintf(f, "    mov x0, x9\n");
                fprintf(f, "    mov x1, x10\n");
                fprintf(f, "    bl mod_helper\n");
                fprintf(f, "    mov x%d, x0\n", target_reg); // El módulo está en x0
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesIgualdad) {
                fprintf(f, "    cmp x9, x10\n");
                fprintf(f, "    cset x%d, eq\n", target_reg); // 1 si igual, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesDesigualdad) {
                fprintf(f, "    cmp x9, x10\n");
                fprintf(f, "    cset x%d, ne\n", target_reg); // 1 si diferente, 0 si igual
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMayorQue) {
                fprintf(f, "    cmp x9, x10\n");
                fprintf(f, "    cset x%d, gt\n", target_reg); // 1 si mayor, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMenorQue) {
                fprintf(f, "    cmp x9, x10\n");
                fprintf(f, "    cset x%d, lt\n", target_reg); // 1 si menor, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMayorIgualQue) {
                fprintf(f, "    cmp x9, x10\n");
                fprintf(f, "    cset x%d, ge\n", target_reg); // 1 si mayor o igual, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMenorIgualQue) {
                fprintf(f, "    cmp x9, x10\n");
                fprintf(f, "    cset x%d, le\n", target_reg); // 1 si menor o igual, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesAnd) {
                // AND lógico: si x9 es 0, resultado es 0; si no, resultado es x10
                fprintf(f, "    cmp x9, #0\n");
                fprintf(f, "    csel x%d, xzr, x10, eq\n", target_reg); // si x9==0, resultado=0, sino x10
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesOr) {
                // OR lógico: si x9 es != 0, resultado es 1; si no, resultado es x10
                fprintf(f, "    cmp x9, #0\n");
                fprintf(f, "    cset x%d, ne\n", target_reg); // 1 si x9 != 0, 0 si x9 == 0
                fprintf(f, "    cmp x9, #0\n");
                fprintf(f, "    csel x%d, x%d, x10, ne\n", target_reg, target_reg); // si x9!=0, usar 1, sino x10
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesNot) {
                // NOT lógico: solo evaluar el primer operando
                arm_emit_eval_expr(ctx, el->base.hijos ? el->base.hijos[0] : NULL, 9, f);
                fprintf(f, "    cmp x9, #0\n");
                fprintf(f, "    cset x%d, eq\n", target_reg); // 1 si x9==0, 0 si x9!=0
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesBitAnd) {
                // Bitwise AND: x9 & x10
                fprintf(f, "    and x%d, x9, x10\n", target_reg);
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesBitOr) {
                // Bitwise OR: x9 | x10
                fprintf(f, "    orr x%d, x9, x10\n", target_reg);
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesBitXor) {
                // Bitwise XOR: x9 ^ x10
                fprintf(f, "    eor x%d, x9, x10\n", target_reg);
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesShiftLeft) {
                // Shift Left: x9 << x10
                fprintf(f, "    lsl x%d, x9, x10\n", target_reg);
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesShiftRight) {
                // Shift Right: x9 >> x10
                fprintf(f, "    asr x%d, x9, x10\n", target_reg);
                return;
            }
        }
    }

    // Fallback
    fprintf(f, "    mov x%d, #0\n", target_reg);
}


