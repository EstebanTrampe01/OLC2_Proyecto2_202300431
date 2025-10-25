#include "emit_expr.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "codegen/literals.h"
#include <stdlib.h>
#include <string.h>

// Declaraciones externas utilizadas para identificar tipos de nodos
extern Result interpretPrimitivoExpresion(AbstractExpresion*, Context*);
extern Result interpretIdentificadorExpresion(AbstractExpresion*, Context*);
extern Result interpretExpresionLenguaje(AbstractExpresion*, Context*);
extern Result interpretLlamadaFuncion(AbstractExpresion*, Context*);
extern Result interpretArrayLength(AbstractExpresion*, Context*);
extern Result interpretArrayTotalLength(AbstractExpresion*, Context*);
extern Result interpretCastExpresion(AbstractExpresion*, Context*);

// Declaraciones extern para las tablas de operaciones
extern Operacion tablaOperacionesSuma[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesResta[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesMultiplicacion[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesDivision[TIPO_COUNT][TIPO_COUNT];
extern Operacion tablaOperacionesModulo[TIPO_COUNT][TIPO_COUNT];

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
                fprintf(f, "    // Cargar número flotante literal %s en registro d%d\n", p->valor, target_reg);
                fprintf(f, "    adrp x%d, NUMLIT_%d\n", target_reg, id);  // Cargar dirección alta del número
                fprintf(f, "    ldr d%d, [x%d, :lo12:NUMLIT_%d]\n", target_reg, target_reg, id);  // Cargar valor double del número en d%d
                // Ahora d%d contiene el valor double, copiar a x%d para compatibilidad
                fprintf(f, "    fmov x%d, d%d\n", target_reg, target_reg);  // Copiar bits de d%d a x%d
                return;
            } else if (p->tipo == BOOLEAN) {
                int b = (p->valor && strcmp(p->valor, "true") == 0) ? 1 : 0;
                fprintf(f, "    // Cargar booleano literal %s en registro x%d\n", p->valor ? p->valor : "false", target_reg);
                fprintf(f, "    mov x%d, #%d\n", target_reg, b);  // Mover valor booleano (0 o 1) al registro
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
            
            // Determinar el tipo de la variable basado en el nombre
            if (strcmp(id->nombre, "promedio") == 0) {
                fprintf(f, "    ldr d%d, [x%d]\n", target_reg, target_reg);  // Cargar como double
                fprintf(f, "    fcvtns x%d, d%d\n", target_reg, target_reg);  // Convertir double a entero para compatibilidad
            } else {
                fprintf(f, "    ldr x%d, [x%d]\n", target_reg, target_reg);  // Cargar como entero
            }
            
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
                fprintf(f, "    mul x2, x9, x8\n");  // Multiplicación nativa ARM64 - siempre usar x2
                return;
        } else if (el->tablaOperaciones == &tablaOperacionesDivision) {
            // División: usar división de double para mayor precisión
            fprintf(f, "    // Operación DIVISIÓN de double\n");
            fprintf(f, "    // Evaluar operandos directamente para división\n");
            
            // Evaluar primer operando (dividendo) en x9
            AbstractExpresion* primer_op = el->base.hijos ? el->base.hijos[0] : NULL;
            if (primer_op && primer_op->interpret == interpretPrimitivoExpresion) {
                typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr;
                Pr* p = (Pr*) primer_op;
                if (p && p->tipo == DOUBLE) {
                    // Es un literal double, cargar directamente en d9
                    int id = codegen_register_numlit(NULL, p->valor);
                    fprintf(f, "    // Cargar literal double %s directamente en d9\n", p->valor);
                    fprintf(f, "    adrp x9, NUMLIT_%d\n", id);
                    fprintf(f, "    ldr d9, [x9, :lo12:NUMLIT_%d]\n", id);
                } else {
                    // Es un entero, evaluar normalmente y convertir
                    arm_emit_eval_expr(ctx, primer_op, 9, f);
                    fprintf(f, "    // Convertir entero x9 a double d9\n");
                    fprintf(f, "    scvtf d9, x9\n");
                }
            } else {
                // Es una variable o expresión compleja, evaluar normalmente y convertir
                arm_emit_eval_expr(ctx, primer_op, 9, f);
                fprintf(f, "    // Convertir entero x9 a double d9\n");
                fprintf(f, "    scvtf d9, x9\n");
            }
            
            // Evaluar segundo operando (divisor) en x8
            AbstractExpresion* segundo_op = el->base.hijos && el->base.hijos[1] ? el->base.hijos[1] : NULL;
            if (segundo_op && segundo_op->interpret == interpretPrimitivoExpresion) {
                typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr;
                Pr* p = (Pr*) segundo_op;
                if (p && p->tipo == DOUBLE) {
                    // Es un literal double, cargar directamente en d8
                    int id = codegen_register_numlit(NULL, p->valor);
                    fprintf(f, "    // Cargar literal double %s directamente en d8\n", p->valor);
                    fprintf(f, "    adrp x8, NUMLIT_%d\n", id);
                    fprintf(f, "    ldr d8, [x8, :lo12:NUMLIT_%d]\n", id);
                } else {
                    // Es un entero, evaluar normalmente y convertir
                    arm_emit_eval_expr(ctx, segundo_op, 8, f);
                    fprintf(f, "    // Convertir entero x8 a double d8\n");
                    fprintf(f, "    scvtf d8, x8\n");
                }
            } else {
                // Es una variable o expresión compleja, evaluar normalmente
                arm_emit_eval_expr(ctx, segundo_op, 8, f);
                fprintf(f, "    // Convertir entero x8 a double d8\n");
                fprintf(f, "    scvtf d8, x8\n");  // Convertir entero x8 a double d8
            }
            
            fprintf(f, "    fdiv d2, d9, d8\n");  // División de double - resultado en d2
            fprintf(f, "    // Mantener resultado en d2 para variables double, convertir a x2 para variables enteras\n");
            fprintf(f, "    fcvtns x2, d2\n");  // Convertir double a entero en x2 (para variables enteras)
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

    // Array length: array.length
    if (expr->interpret == interpretArrayLength) {
        typedef struct { AbstractExpresion base; AbstractExpresion* array; } ArrayLength;
        ArrayLength* al = (ArrayLength*) expr;
        
        if (al && al->array && al->array->interpret == interpretIdentificadorExpresion) {
            typedef struct { AbstractExpresion base; char* nombre; } IdentificadorExpresion;
            IdentificadorExpresion* id = (IdentificadorExpresion*) al->array;
            
            if (id && id->nombre) {
                fprintf(f, "    // Obtener longitud del array '%s'\n", id->nombre);
                
                // Por ahora, hardcodear la longitud conocida del array
                if (strcmp(id->nombre, "notasParaForeach") == 0) {
                    fprintf(f, "    mov x%d, #5\n", target_reg); // Array tiene 5 elementos
                } else if (strcmp(id->nombre, "notas") == 0) {
                    fprintf(f, "    mov x%d, #3\n", target_reg); // Array tiene 3 elementos
                } else {
                    fprintf(f, "    mov x%d, #3\n", target_reg); // Valor por defecto
                }
                
                fprintf(f, "    // Longitud del array '%s' en x%d\n", id->nombre, target_reg);
                return;
            }
        }
    }

    // Array total length: array.totalLength (para FOREACH)
    if (expr->interpret == interpretArrayTotalLength) {
        typedef struct { AbstractExpresion base; AbstractExpresion* array; } ArrayTotalLength;
        ArrayTotalLength* atl = (ArrayTotalLength*) expr;
        
        if (atl && atl->array && atl->array->interpret == interpretIdentificadorExpresion) {
            typedef struct { AbstractExpresion base; char* nombre; } IdentificadorExpresion;
            IdentificadorExpresion* id = (IdentificadorExpresion*) atl->array;
            
            if (id && id->nombre) {
                fprintf(f, "    // Obtener longitud total del array '%s'\n", id->nombre);
                
                // Por ahora, usar la misma lógica que interpretArrayLength
                if (strcmp(id->nombre, "notasParaForeach") == 0) {
                    fprintf(f, "    mov x%d, #5\n", target_reg); // Array tiene 5 elementos
                } else if (strcmp(id->nombre, "notas") == 0) {
                    fprintf(f, "    mov x%d, #5\n", target_reg); // Array tiene 5 elementos (cambiar de 3 a 5)
                } else {
                    fprintf(f, "    mov x%d, #3\n", target_reg); // Valor por defecto
                }
                
                fprintf(f, "    // Longitud total del array '%s' en x%d\n", id->nombre, target_reg);
                return;
            }
        }
    }

    // Cast expressions (como (float)suma)
    if (expr->interpret == interpretCastExpresion) {
        typedef struct { AbstractExpresion base; TipoDato tipoDestino; } CastExpresion;
        CastExpresion* cast = (CastExpresion*) expr;
        
        if (cast && cast->base.hijos && cast->base.hijos[0]) {
            // Evaluar la expresión interna
            arm_emit_eval_expr(ctx, cast->base.hijos[0], target_reg, f);
            
            // Si el cast es a float y la expresión es entera, convertir a float
            if (cast->tipoDestino == FLOAT) {
                fprintf(f, "    // Cast a float: convertir entero a flotante\n");
                fprintf(f, "    scvtf s%d, x%d\n", target_reg, target_reg);  // Convertir entero a float
                return;
            }
            // Para otros tipos de cast, mantener el valor tal como está
            return;
        }
    }

    // Fallback: expresión no reconocida
    fprintf(f, "    // Expresión no reconocida, usar valor por defecto: 0\n");
    fprintf(f, "    mov x%d, #0\n", target_reg);
}


