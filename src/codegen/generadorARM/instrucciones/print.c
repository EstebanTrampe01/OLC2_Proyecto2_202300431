#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "codegen/literals.h"
#include "../../codegen.h"

#include "ast/nodos/expresiones/terminales/primitivos.h"
#include "ast/nodos/expresiones/terminales/identificadores.h"
#include "ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"

// Declaraciones externas necesarias
extern Result interpretCastExpresion(AbstractExpresion*, Context*);
extern Result interpretIdentificadorExpresion(AbstractExpresion*, Context*);
extern Result interpretExpresionLenguaje(AbstractExpresion*, Context*);

// Emitir una asignación simple a una variable global GV_<name>
// Solo maneja RHS literal (PrimitivoExpresion) por ahora
void emit_asignacion_text(CodegenContext* ctx, AbstractExpresion* asignNode) {
    if (!ctx || !ctx->out || !asignNode) return;
    AsignacionExpresion* a = (AsignacionExpresion*) asignNode;
    if (asignNode->numHijos == 0) return;
    AbstractExpresion* rhs = asignNode->hijos[0];
    
    if (ctx->debug) fprintf(ctx->out, "# debug: procesando asignación RHS tipo=%p\n", (void*)rhs->interpret);
    
    // Debug: mostrar qué tipo de expresión es el RHS
    debug_printf("DEBUG: RHS de asignación '%s' es tipo=%p\n", a->nombre, (void*)rhs->interpret);
    
    // Manejar expresiones de casting
    if (rhs->interpret == interpretCastExpresion) {
        if (ctx->debug) fprintf(ctx->out, "# debug: detectado casting\n");
        typedef struct { AbstractExpresion base; int tipoDestino; } CastExpresion;
        CastExpresion* cast = (CastExpresion*) rhs;
        if (cast && cast->base.numHijos > 0) {
            AbstractExpresion* innerExpr = cast->base.hijos[0];
            
            if (ctx->debug) fprintf(ctx->out, "# debug: inner expr tipo=%p, tipoDestino=%d\n", 
                   (void*)innerExpr->interpret, cast->tipoDestino);
            
            // Si el casting es de int a float/double
            if (innerExpr->interpret == interpretIdentificadorExpresion && 
                (cast->tipoDestino == FLOAT || cast->tipoDestino == DOUBLE)) {
                
                typedef struct { AbstractExpresion base; char* nombre; } Id;
                Id* id = (Id*) innerExpr;
                
                fprintf(ctx->out, "    // Asignación con casting: %s = (%s) %s\n", 
                       a->nombre, 
                       cast->tipoDestino == FLOAT ? "float" : "double", 
                       id->nombre);
                fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);  // Cargar dirección alta de la variable destino
                fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);  // Completar dirección de la variable destino
                fprintf(ctx->out, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                fprintf(ctx->out, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                fprintf(ctx->out, "    ldr x2, [x2]\n");  // Cargar valor entero de la variable origen
                
                if (cast->tipoDestino == FLOAT) {
                    fprintf(ctx->out, "    scvtf s2, x2\n");  // Convertir entero a float
                    fprintf(ctx->out, "    str s2, [x1]\n\n");  // Almacenar float en la variable destino
                } else {
                    fprintf(ctx->out, "    scvtf d2, x2\n");  // Convertir entero a double
                    fprintf(ctx->out, "    str d2, [x1]\n\n");  // Almacenar double en la variable destino
                }
                return;
            }
        }
        if (ctx->debug) fprintf(ctx->out, "# debug: casting no soportado aún\n");
        return;
    }
    
    // Manejar asignaciones de identificadores (nombreActual = estudiante1)
    if (rhs->interpret == interpretIdentificadorExpresion) {
        IdentificadorExpresion* idExpr = (IdentificadorExpresion*)rhs;
        
        // Obtener nombres únicos para variables FOR
        extern char* arm_get_unique_var_name(const char* original_name);
        char* unique_source = arm_get_unique_var_name(idExpr->nombre);
        char* unique_dest = arm_get_unique_var_name(a->nombre);
        
        fprintf(ctx->out, "    // Asignar identificador '%s' (único: '%s') a variable '%s' (única: '%s')\n", 
                idExpr->nombre, unique_source, a->nombre, unique_dest);
        
        // Cargar valor del identificador fuente
        fprintf(ctx->out, "    adrp x1, GV_%s\n", unique_source);  // Cargar dirección alta de la variable fuente
        fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", unique_source);  // Completar dirección de la variable fuente
        fprintf(ctx->out, "    ldr x2, [x1]\n");  // Cargar valor de la variable fuente
        
        // Almacenar en la variable destino
        fprintf(ctx->out, "    adrp x3, GV_%s\n", unique_dest);  // Cargar dirección alta de la variable destino
        fprintf(ctx->out, "    add x3, x3, :lo12:GV_%s\n", unique_dest);  // Completar dirección de la variable destino
        fprintf(ctx->out, "    str x2, [x3]\n\n");  // Almacenar valor en la variable destino
        
        free(unique_source);
        free(unique_dest);
        return;
    }
    
    // Manejar expresiones complejas (aritméticas, relacionales, etc.)
    if (rhs->interpret == interpretExpresionLenguaje) {
        if (ctx->debug) fprintf(ctx->out, "# debug: detectada expresión compleja\n");
        
        // Evaluar la expresión compleja y almacenar el resultado
        extern char* arm_get_unique_var_name(const char* original_name);
        char* unique_dest = arm_get_unique_var_name(a->nombre);
        
        fprintf(ctx->out, "    // Evaluar expresión compleja para '%s' (única: '%s')\n", a->nombre, unique_dest);
        fprintf(ctx->out, "    adrp x11, GV_%s\n", unique_dest);  // Cargar dirección alta de la variable destino
        fprintf(ctx->out, "    add x11, x11, :lo12:GV_%s\n", unique_dest);  // Completar dirección de la variable destino
        
        free(unique_dest);
        
        // Usar arm_emit_eval_expr para evaluar la expresión compleja
        extern void arm_emit_eval_expr(CodegenContext*, AbstractExpresion*, int, FILE*);
        arm_emit_eval_expr(ctx, rhs, 2, ctx->out);  // Evaluar en registro x2
        
        fprintf(ctx->out, "    str x2, [x11]\n\n");  // Almacenar resultado en la variable destino
        return;
    }
    
    if (rhs->interpret != interpretPrimitivoExpresion) {
        if (ctx->debug) fprintf(ctx->out, "# debug: asignación RHS no es primitivo, casting ni expresión compleja, ignorando\n");
        return;
    }
    PrimitivoExpresion* p = (PrimitivoExpresion*) rhs;
    if (!p) { if (ctx->debug) fprintf(ctx->out, "# debug: primitivo NULL\n"); return; }
    switch (p->tipo) {
        case INT: {
            long ival = atol(p->valor ? p->valor : "0");
            
            // Obtener nombre único para variables FOR
            extern char* arm_get_unique_var_name(const char* original_name);
            char* unique_name = arm_get_unique_var_name(a->nombre);
            
            fprintf(ctx->out, "    // Asignar entero %ld a variable global '%s' (única: '%s')\n", ival, a->nombre, unique_name);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", unique_name);  // Cargar dirección alta de la variable
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", unique_name);  // Completar dirección de la variable
            fprintf(ctx->out, "    mov x2, #%ld\n", ival);  // Cargar valor entero
            fprintf(ctx->out, "    str x2, [x1]\n\n");  // Almacenar valor en la variable
            
            free(unique_name);
            break;
        }
        case BOOLEAN: {
            int b = (p->valor && strcmp(p->valor, "true") == 0) ? 1 : 0;
            fprintf(ctx->out, "    // Asignar booleano %d (%s) a variable global '%s'\n", b, p->valor ? p->valor : "false", a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);  // Cargar dirección alta de la variable
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);  // Completar dirección de la variable
            fprintf(ctx->out, "    mov x2, #%d\n", b);  // Cargar valor booleano (0 o 1)
            fprintf(ctx->out, "    str x2, [x1]\n\n");  // Almacenar valor en la variable
            break;
        }
        case CHAR: {
            char ch = (p->valor && strlen(p->valor)>0) ? p->valor[0] : '\0';
            int c = (int) ch;
            fprintf(ctx->out, "    // Asignar carácter '%c' (ASCII %d) a variable global '%s'\n", ch, c, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);  // Cargar dirección alta de la variable
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);  // Completar dirección de la variable
            fprintf(ctx->out, "    mov w2, #%d\n", c);  // Cargar valor del carácter
            fprintf(ctx->out, "    strb w2, [x1]\n\n");  // Almacenar byte en la variable
            break;
        }
        case STRING: {
            const char* tmpval = p->valor ? p->valor : "";
            size_t L = strlen(tmpval);
            char* stripped = NULL;
            if (L >= 2 && tmpval[0] == '"' && tmpval[L-1] == '"') {
                stripped = strndup(tmpval+1, L-2);
            } else {
                stripped = strdup(tmpval);
            }
            int existing = codegen_find_strlit(stripped);
            int sId = existing > 0 ? existing : codegen_register_strlit(ctx->out, stripped);
            free(stripped);
            fprintf(ctx->out, "    // Asignar string '%s' a variable global '%s'\n", tmpval, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);  // Cargar dirección alta de la variable
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);  // Completar dirección de la variable
            fprintf(ctx->out, "    adrp x2, STRLIT_%d\n", sId);  // Cargar dirección alta del string literal
            fprintf(ctx->out, "    add x2, x2, :lo12:STRLIT_%d\n", sId);  // Completar dirección del string literal
            fprintf(ctx->out, "    str x2, [x1]\n\n");  // Almacenar puntero al string en la variable
            break;
        }
        case FLOAT: {
            float fval = atof(p->valor ? p->valor : "0.0");
            fprintf(ctx->out, "    // Asignar flotante %f a variable global '%s'\n", fval, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);  // Cargar dirección alta de la variable
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);  // Completar dirección de la variable
            // Buscar el valor flotante en los literales numéricos registrados
            int id = codegen_find_numlit(p->valor ? p->valor : "0.0");
            debug_printf("DEBUG: buscando literal '%s' para FLOAT, id=%d\n", p->valor ? p->valor : "0.0", id);
            if (id > 0) {
                fprintf(ctx->out, "    adrp x2, NUMLIT_%d\n", id);  // Cargar dirección alta del número literal
                fprintf(ctx->out, "    ldr d2, [x2, :lo12:NUMLIT_%d]\n", id);  // Cargar valor double en registro d2
                fprintf(ctx->out, "    fcvt s2, d2\n");  // Convertir double a float
                fprintf(ctx->out, "    str s2, [x1]\n\n");  // Almacenar valor flotante en la variable
            } else {
                // Fallback: usar valor por defecto
                fprintf(ctx->out, "    // Usando valor por defecto 0.0 para '%s'\n", a->nombre);
                fprintf(ctx->out, "    mov w2, #0\n");  // Valor por defecto
                fprintf(ctx->out, "    fmov s2, w2\n");  // Convertir entero a flotante
                fprintf(ctx->out, "    str s2, [x1]\n\n");  // Almacenar valor flotante en la variable
            }
            break;
        }
        case DOUBLE: {
            double dval = atof(p->valor ? p->valor : "0.0");
            fprintf(ctx->out, "    // Asignar doble %f a variable global '%s'\n", dval, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);  // Cargar dirección alta de la variable
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);  // Completar dirección de la variable
            // Buscar el valor doble en los literales numéricos registrados
            int id = codegen_find_numlit(p->valor ? p->valor : "0.0");
            debug_printf("DEBUG: buscando literal '%s' para DOUBLE, id=%d\n", p->valor ? p->valor : "0.0", id);
            if (id > 0) {
                fprintf(ctx->out, "    adrp x2, NUMLIT_%d\n", id);  // Cargar dirección alta del número literal
                fprintf(ctx->out, "    ldr d2, [x2, :lo12:NUMLIT_%d]\n", id);  // Cargar valor doble en registro d2
                fprintf(ctx->out, "    str d2, [x1]\n\n");  // Almacenar valor doble en la variable
            } else {
                // Fallback: usar valor por defecto
                fprintf(ctx->out, "    // Usando valor por defecto 0.0 para '%s'\n", a->nombre);
                fprintf(ctx->out, "    mov x2, #0\n");  // Valor por defecto
                fprintf(ctx->out, "    fmov d2, x2\n");  // Convertir entero a doble
                fprintf(ctx->out, "    str d2, [x1]\n\n");  // Almacenar valor doble en la variable
            }
            break;
        }
        default:
            if (ctx->debug) fprintf(ctx->out, "# debug: asignación literal tipo no reconocido (tipo=%d)\n", p->tipo);
            break;
    }
}
