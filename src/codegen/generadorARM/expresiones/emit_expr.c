#include "emit_expr.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "codegen/literals.h"
#include <stdlib.h>

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
                fprintf(f, "    // Cargar string literal '%s' en registro x%d\n", p->valor, target_reg);
                fprintf(f, "    adrp x%d, STRLIT_%d\n", target_reg, id);  // Cargar dirección alta del string
                fprintf(f, "    add x%d, x%d, :lo12:STRLIT_%d\n", target_reg, target_reg, id);  // Completar dirección del string
                return;
            } else if (p->tipo == INT) {
                fprintf(f, "    // Cargar entero literal %s en registro x%d\n", p->valor, target_reg);
                fprintf(f, "    mov x%d, #%s\n", target_reg, p->valor);  // Mover valor inmediato al registro
                return;
            } else if (p->tipo == DOUBLE) {
                int id = codegen_register_numlit(NULL, p->valor);
                fprintf(f, "    // Cargar número flotante literal %s en registro x%d\n", p->valor, target_reg);
                fprintf(f, "    adrp x%d, NUMLIT_%d\n", target_reg, id);  // Cargar dirección alta del número
                fprintf(f, "    ldr x%d, [x%d, :lo12:NUMLIT_%d]\n", target_reg, target_reg, id);  // Cargar valor del número
                return;
            }
        }
        fprintf(f, "    // Valor por defecto: 0\n");
        fprintf(f, "    mov x%d, #0\n", target_reg);
        return;
    }

    // Identificadores globales
    if (expr->interpret == interpretIdentificadorExpresion) {
        typedef struct { AbstractExpresion base; char* nombre; } Id;
        Id* id = (Id*) expr;
        if (id && id->nombre) {
            // Obtener nombre único para variables FOR
            extern char* arm_get_unique_var_name(const char* original_name);
            char* unique_name = arm_get_unique_var_name(id->nombre);
            
            fprintf(f, "    // Cargar variable global '%s' (única: '%s') en registro x%d\n", id->nombre, unique_name, target_reg);
            fprintf(f, "    adrp x%d, GV_%s\n", target_reg, unique_name);  // Cargar dirección alta de la variable
            fprintf(f, "    add x%d, x%d, :lo12:GV_%s\n", target_reg, target_reg, unique_name);  // Completar dirección de la variable
            fprintf(f, "    ldr x%d, [x%d]\n", target_reg, target_reg);  // Cargar valor de la variable
            
            free(unique_name);
            return;
        }
        fprintf(f, "    // Variable no encontrada, usar valor por defecto: 0\n");
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
            
            // Evaluar operandos usando la pila para preservar valores temporales
            // Evaluar segundo operando y guardarlo en la pila
            arm_emit_eval_expr(ctx, el->base.hijos && el->base.hijos[1] ? el->base.hijos[1] : NULL, 8, f);  // Evaluar segundo operando en x8
            fprintf(f, "    str x8, [sp, #-16]!\n");  // Guardar segundo operando en la pila
            // Evaluar primer operando
            arm_emit_eval_expr(ctx, el->base.hijos ? el->base.hijos[0] : NULL, 9, f);  // Evaluar primer operando en x9
            // Recuperar segundo operando de la pila
            fprintf(f, "    ldr x8, [sp], #16\n");  // Recuperar segundo operando de la pila
            
            if (el->tablaOperaciones == &tablaOperacionesSuma) {
                // Suma de enteros - usar código ARM64 nativo
                fprintf(f, "    // Operación SUMA de enteros\n");
                fprintf(f, "    add x%d, x9, x8\n", target_reg);  // Suma nativa ARM64
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesResta) {
                // Resta de enteros - usar código ARM64 nativo
                fprintf(f, "    // Operación RESTA de enteros\n");
                fprintf(f, "    sub x%d, x9, x8\n", target_reg);  // Resta nativa ARM64
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMultiplicacion) {
                // Multiplicación de enteros - usar código ARM64 nativo
                fprintf(f, "    // Operación MULTIPLICACIÓN de enteros\n");
                fprintf(f, "    mul x%d, x9, x8\n", target_reg);  // Multiplicación nativa ARM64
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesDivision) {
                // Detectar si es división entera o con decimales
                // Por simplicidad, usar div_helper para enteros y div_mixed_helper para decimales
                fprintf(f, "    // Operación DIVISIÓN: detectar tipo de división\n");
                fprintf(f, "    mov x0, x9\n");  // Pasar primer operando como parámetro
                fprintf(f, "    mov x1, x8\n");  // Pasar segundo operando como parámetro
                fprintf(f, "    bl double_div\n");  // Usar división de double automática
                fprintf(f, "    mov x%d, x0\n", target_reg);  // El resultado está en x0
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesModulo) {
                fprintf(f, "    // Operación MÓDULO: llamar helper C para módulo\n");
                fprintf(f, "    mov x0, x9\n");  // Pasar primer operando como parámetro
                fprintf(f, "    mov x1, x8\n");  // Pasar segundo operando como parámetro
                fprintf(f, "    bl mod_helper\n");  // Llamar función helper de módulo
                fprintf(f, "    mov x%d, x0\n", target_reg);  // El módulo está en x0
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesIgualdad) {
                fprintf(f, "    // Operación IGUALDAD: comparar x9 == x8\n");
                fprintf(f, "    cmp x9, x8\n");  // Comparar operandos
                fprintf(f, "    cset x%d, eq\n", target_reg);  // 1 si igual, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesDesigualdad) {
                fprintf(f, "    // Operación DESIGUALDAD: comparar x9 != x8\n");
                fprintf(f, "    cmp x9, x8\n");  // Comparar operandos
                fprintf(f, "    cset x%d, ne\n", target_reg);  // 1 si diferente, 0 si igual
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMayorQue) {
                fprintf(f, "    // Operación MAYOR QUE: comparar x9 > x8\n");
                fprintf(f, "    cmp x9, x8\n");  // Comparar operandos
                fprintf(f, "    cset x%d, gt\n", target_reg);  // 1 si mayor, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMenorQue) {
                fprintf(f, "    // Operación MENOR QUE: comparar x9 < x8\n");
                fprintf(f, "    cmp x9, x8\n");  // Comparar operandos
                fprintf(f, "    cset x%d, lt\n", target_reg);  // 1 si menor, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMayorIgualQue) {
                fprintf(f, "    // Operación MAYOR O IGUAL: comparar x9 >= x8\n");
                fprintf(f, "    cmp x9, x8\n");  // Comparar operandos
                fprintf(f, "    cset x%d, ge\n", target_reg);  // 1 si mayor o igual, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesMenorIgualQue) {
                fprintf(f, "    // Operación MENOR O IGUAL: comparar x9 <= x8\n");
                fprintf(f, "    cmp x9, x8\n");  // Comparar operandos
                fprintf(f, "    cset x%d, le\n", target_reg);  // 1 si menor o igual, 0 si no
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesAnd) {
                fprintf(f, "    // Operación AND LÓGICO: x9 && x8\n");
                fprintf(f, "    cmp x9, #0\n");  // Verificar si primer operando es 0
                fprintf(f, "    csel x%d, xzr, x8, eq\n", target_reg);  // si x9==0, resultado=0, sino x8
                fprintf(f, "    cmp x%d, #0\n", target_reg);  // Verificar resultado
                fprintf(f, "    cset x%d, ne\n", target_reg);  // 1 si resultado!=0, 0 si resultado==0
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesOr) {
                fprintf(f, "    // Operación OR LÓGICO: x9 || x8\n");
                fprintf(f, "    cmp x9, #0\n");  // Verificar si primer operando es 0
                fprintf(f, "    csel x%d, x8, x9, eq\n", target_reg);  // si x9==0, usar x8, sino x9
                fprintf(f, "    cmp x%d, #0\n", target_reg);  // Verificar resultado
                fprintf(f, "    cset x%d, ne\n", target_reg);  // 1 si resultado!=0, 0 si resultado==0
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesNot) {
                fprintf(f, "    // Operación NOT LÓGICO: !x9\n");
                arm_emit_eval_expr(ctx, el->base.hijos ? el->base.hijos[0] : NULL, 9, f);  // Evaluar operando
                fprintf(f, "    cmp x9, #0\n");  // Comparar con 0
                fprintf(f, "    cset x%d, eq\n", target_reg);  // 1 si x9==0, 0 si x9!=0
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesBitAnd) {
                fprintf(f, "    // Operación AND DE BITS: x%d = x9 & x8\n", target_reg);
                fprintf(f, "    and x%d, x9, x8\n", target_reg);  // AND bitwise
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesBitOr) {
                fprintf(f, "    // Operación OR DE BITS: x%d = x9 | x8\n", target_reg);
                fprintf(f, "    orr x%d, x9, x8\n", target_reg);  // OR bitwise
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesBitXor) {
                fprintf(f, "    // Operación XOR DE BITS: x%d = x9 ^ x8\n", target_reg);
                fprintf(f, "    eor x%d, x9, x8\n", target_reg);  // XOR bitwise
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesShiftLeft) {
                fprintf(f, "    // Operación DESPLAZAMIENTO IZQUIERDA: x%d = x9 << x8\n", target_reg);
                fprintf(f, "    lsl x%d, x9, x8\n", target_reg);  // Shift left
                return;
            } else if (el->tablaOperaciones == &tablaOperacionesShiftRight) {
                fprintf(f, "    // Operación DESPLAZAMIENTO DERECHA: x%d = x9 >> x8\n", target_reg);
                fprintf(f, "    asr x%d, x9, x8\n", target_reg);  // Shift right (arithmetic)
                return;
            }
        }
    }

    // Fallback: expresión no reconocida
    fprintf(f, "    // Expresión no reconocida, usar valor por defecto: 0\n");
    fprintf(f, "    mov x%d, #0\n", target_reg);
}


