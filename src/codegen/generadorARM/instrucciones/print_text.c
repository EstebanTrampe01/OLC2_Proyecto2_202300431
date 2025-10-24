#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "codegen/literals.h"

#include "ast/nodos/expresiones/listaExpresiones.h"
#include "ast/nodos/expresiones/cast.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/expresiones/builtins.h"
#include "ast/nodos/expresiones/terminales/primitivos.h"
#include "ast/nodos/expresiones/terminales/identificadores.h"
#include "ast/nodos/instrucciones/instruccion/print.h"
#include "ast/nodos/instrucciones/instruccion/funcion.h"
#include "../expresiones/emit_expr.h"

extern Result interpretListaExpresiones(AbstractExpresion*, Context*);
extern Result interpretCastExpresion(AbstractExpresion*, Context*);
extern Result interpretUnarioLenguaje(AbstractExpresion*, Context*);
extern Result interpretStringValueOf(AbstractExpresion*, Context*);

typedef struct { AbstractExpresion base; AbstractExpresion* a; } UnaryWrapLocal;

static void dump_print_ast_recursive(CodegenContext* ctx, AbstractExpresion* n, int depth) {
    if (!ctx || !ctx->out || !n) return;
    static int printed_map = 0;
    if (!printed_map && depth == 0) {
        printed_map = 1;
        fprintf(ctx->out, "# interpret_map:\n");
        fprintf(ctx->out, "#   PRIMITIVO=0x%lx\n", (unsigned long)(uintptr_t) interpretPrimitivoExpresion);
        fprintf(ctx->out, "#   IDENTIFICADOR=0x%lx\n", (unsigned long)(uintptr_t) interpretIdentificadorExpresion);
        fprintf(ctx->out, "#   EXPRESION_LENGUAJE=0x%lx\n", (unsigned long)(uintptr_t) interpretExpresionLenguaje);
        fprintf(ctx->out, "#   LLAMADA_FUNCION=0x%lx\n", (unsigned long)(uintptr_t) interpretLlamadaFuncion);
        fprintf(ctx->out, "#   LISTA_EXPRESIONES=0x%lx\n", (unsigned long)(uintptr_t) interpretListaExpresiones);
        fprintf(ctx->out, "#   CAST=0x%lx\n", (unsigned long)(uintptr_t) interpretCastExpresion);
        fprintf(ctx->out, "#   UNARIO_LENGUAJE=0x%lx\n", (unsigned long)(uintptr_t) interpretUnarioLenguaje);
        fprintf(ctx->out, "#   BUILTIN_STRING_VALUEOF=0x%lx\n", (unsigned long)(uintptr_t) interpretStringValueOf);
        fprintf(ctx->out, "#   PRINT_EXPR=0x%lx\n", (unsigned long)(uintptr_t) interpretPrintExpresion);
    }
    for (int i = 0; i < depth; ++i) fprintf(ctx->out, "# ");
    const char* itname = "UNKNOWN";
    uintptr_t iptr = (uintptr_t) n->interpret;
    if (n->interpret == interpretPrimitivoExpresion) itname = "PRIMITIVO";
    else if (n->interpret == interpretIdentificadorExpresion) itname = "IDENTIFICADOR";
    else if (n->interpret == interpretExpresionLenguaje) itname = "EXPRESION_LENGUAJE";
    else if (n->interpret == interpretLlamadaFuncion) itname = "LLAMADA_FUNCION";
    else if (n->interpret == interpretPrintExpresion) itname = "PRINT_EXPR";
    fprintf(ctx->out, "# AST node: %s iptr=0x%lx children=%zu\n", itname, (unsigned long)iptr, n->numHijos);
    if (n->interpret == interpretPrimitivoExpresion) {
        PrimitivoExpresion* p = (PrimitivoExpresion*) n;
        for (int i = 0; i < depth; ++i) fprintf(ctx->out, "# ");
        const char* raw = p->valor ? p->valor : "(null)";
        size_t L = strlen(raw);
        char* esc = (char*)malloc(L*2 + 1);
        size_t k = 0;
        for (size_t j = 0; j < L; ++j) {
            char c = raw[j];
            if (c == '\n') { esc[k++] = '\\'; esc[k++] = 'n'; }
            else if (c == '\t') { esc[k++] = '\\'; esc[k++] = 't'; }
            else if (c == '\r') { esc[k++] = '\\'; esc[k++] = 'r'; }
            else esc[k++] = c;
        }
        esc[k] = '\0';
        fprintf(ctx->out, "#   prim tipo=%d valor=%s\n", p->tipo, esc);
        free(esc);
    } else if (n->interpret == interpretIdentificadorExpresion) {
        IdentificadorExpresion* id = (IdentificadorExpresion*) n;
        for (int i = 0; i < depth; ++i) fprintf(ctx->out, "# ");
        const char* iname = id->nombre ? id->nombre : "(null)";
        size_t Li = strlen(iname);
        char* iesc = (char*)malloc(Li*2 + 1);
        size_t ki = 0;
        for (size_t j = 0; j < Li; ++j) { char c = iname[j]; if (c=='\n') {iesc[ki++]='\\';iesc[ki++]='n';} else iesc[ki++]=c; }
        iesc[ki]='\0';
        fprintf(ctx->out, "#   id nombre=%s\n", iesc);
        free(iesc);
    } else if (n->interpret == interpretLlamadaFuncion) {
        LlamadaFuncion* lf = (LlamadaFuncion*) n;
        for (int i = 0; i < depth; ++i) fprintf(ctx->out, "# ");
        const char* lname = lf->nombre ? lf->nombre : "(null)";
        size_t Ll = strlen(lname);
        char* lesc = (char*)malloc(Ll*2 + 1);
        size_t kl = 0;
        for (size_t j = 0; j < Ll; ++j) { char c = lname[j]; if (c=='\n') {lesc[kl++]='\\';lesc[kl++]='n';} else lesc[kl++]=c; }
        lesc[kl]='\0';
        fprintf(ctx->out, "#   llamada nombre=%s\n", lesc);
        free(lesc);
    } else if (n->interpret == interpretExpresionLenguaje) {
        ExpresionLenguaje* el = (ExpresionLenguaje*) n;
        for (int i = 0; i < depth; ++i) fprintf(ctx->out, "# ");
        fprintf(ctx->out, "#   expresion tipo=%d\n", el->tipo);
    }
    for (size_t i = 0; i < n->numHijos; ++i) dump_print_ast_recursive(ctx, n->hijos[i], depth+1);
}

static char* escape_string_for_comment(const char* str) {
    if (!str) return strdup("(null)");
    
    size_t len = strlen(str);
    char* result = malloc(len * 4 + 1); // Espacio suficiente para escapes
    size_t j = 0;
    
    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        switch (c) {
            case '\n': 
                result[j++] = '\\'; 
                result[j++] = 'n'; 
                break;
            case '\r': 
                result[j++] = '\\'; 
                result[j++] = 'r'; 
                break;
            case '\t': 
                result[j++] = '\\'; 
                result[j++] = 't'; 
                break;
            case '\\': 
                result[j++] = '\\'; 
                result[j++] = '\\'; 
                break;
            case '"': 
                result[j++] = '\\'; 
                result[j++] = '"'; 
                break;
            case '\'': 
                result[j++] = '\\'; 
                result[j++] = '\''; 
                break;
            default:
                if (c >= 32 && c <= 126) {
                    result[j++] = c; // Carácter imprimible
                } else {
                    // Carácter de control - mostrar como \xXX
                    result[j++] = '\\';
                    result[j++] = 'x';
                    result[j++] = "0123456789ABCDEF"[(c >> 4) & 0xF];
                    result[j++] = "0123456789ABCDEF"[c & 0xF];
                }
                break;
        }
    }
    result[j] = '\0';
    return result;
}

static int emit_print_part(CodegenContext* ctx, AbstractExpresion* n, int nl, char** emitted_names, int* emitted_types, int emitted_count) {
    if (!ctx || !ctx->out || !n) return 0;
    AbstractExpresion* cur = n;
    while (cur && cur->numHijos == 1 && cur->interpret != interpretPrimitivoExpresion
           && cur->interpret != interpretIdentificadorExpresion && cur->interpret != interpretLlamadaFuncion) {
        cur = cur->hijos[0];
    }
    if (!cur) return 0;
    if (cur->interpret == interpretPrimitivoExpresion) {
        PrimitivoExpresion* p = (PrimitivoExpresion*) cur;
        const char* raw = p->valor ? p->valor : "";
        size_t L = strlen(raw);
        char* stripped = NULL;
        if (L>=2 && raw[0]=='"' && raw[L-1]=='"') stripped = strndup(raw+1, L-2);
        else stripped = strdup(raw);
        int sId = codegen_find_strlit(stripped);
        if (sId <= 0) {
            // ERROR: STRLIT no encontrado - debería haber sido registrado en fase .data
            fprintf(stderr, "ERROR: STRLIT no encontrado para '%s'\n", stripped);
            fprintf(ctx->out, "    // ERROR: STRLIT no encontrado para '%s'\n", stripped);
            free(stripped);
            return 0;
        }
        
        // Crear representación legible para el comentario
        char* escaped = escape_string_for_comment(stripped);
        fprintf(ctx->out, "    // Imprimir string literal '%s'\n", escaped);
        free(escaped);
        free(stripped);
        
        fprintf(ctx->out, "    adrp x0, STRLIT_%d\n", sId);  // Cargar dirección alta del string literal
        fprintf(ctx->out, "    add x0, x0, :lo12:STRLIT_%d\n", sId);  // Completar dirección del string literal
        fprintf(ctx->out, "    mov x1, #%d\n", nl);  // Parámetro: agregar nueva línea (0 o 1)
        fprintf(ctx->out, "    bl print_string\n\n");  // Llamar función helper para imprimir string
        return 1;
    }
    if (cur->interpret == interpretIdentificadorExpresion) {
        IdentificadorExpresion* id = (IdentificadorExpresion*) cur;
        
        // Obtener nombre único para variables FOR
        extern char* arm_get_unique_var_name(const char* original_name);
        char* unique_name = arm_get_unique_var_name(id->nombre);
        
        fprintf(ctx->out, "    // Imprimir variable global '%s' (única: '%s')\n", id->nombre, unique_name);
        fprintf(ctx->out, "    adrp x0, GV_%s\n", unique_name);  // Cargar dirección alta de la variable
        fprintf(ctx->out, "    add x0, x0, :lo12:GV_%s\n", unique_name);  // Completar dirección de la variable
        
        free(unique_name);
        int tag = 0;
        if (emitted_names && emitted_types) {
            for (int ii = 0; ii < emitted_count; ++ii) {
                if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) { tag = emitted_types[ii]; break; }
            }
        }
        fprintf(ctx->out, "    // tipo tag=%d\n", tag);  // Tag del tipo de dato
        fprintf(ctx->out, "    mov x1, #%d\n", tag);  // Parámetro: tipo de dato
        fprintf(ctx->out, "    mov x2, #%d\n", nl);  // Parámetro: agregar nueva línea (0 o 1)
        fprintf(ctx->out, "    bl print_any_gv\n\n");  // Llamar función helper para imprimir variable global
        return 1;
    }
    if (cur->interpret == interpretExpresionLenguaje) {
        if (cur->numHijos == 2) {
            if (!emit_print_part(ctx, cur->hijos[0], 0, emitted_names, emitted_types, emitted_count)) return 0;
            if (!emit_print_part(ctx, cur->hijos[1], nl, emitted_names, emitted_types, emitted_count)) return 0;
            return 1;
        }
    }
    // String.valueOf viene como builtin wrapper, no como LlamadaFuncion
    if (cur->interpret == interpretStringValueOf) {
        UnaryWrapLocal* uw = (UnaryWrapLocal*) cur;
        AbstractExpresion* a = uw->a;
        int tag = 1;
        if (a && a->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* p = (PrimitivoExpresion*) a;
            if (p) {
                if (p->tipo == STRING) tag = 6; else if (p->tipo == INT) tag = 1; else if (p->tipo == DOUBLE) tag = 2; else if (p->tipo == FLOAT) tag = 3; else if (p->tipo == BOOLEAN) tag = 4; else if (p->tipo == CHAR) tag = 5;
            }
        } else if (a && a->interpret == interpretIdentificadorExpresion) {
            IdentificadorExpresion* id = (IdentificadorExpresion*) a;
            for (int ii = 0; ii < emitted_count; ++ii) if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) { tag = emitted_types[ii]; break; }
            if (tag == STRING) tag = 6; else if (tag == DOUBLE) tag = 2; else if (tag == FLOAT) tag = 3; else if (tag == BOOLEAN) tag = 4; else if (tag == CHAR) tag = 5; else tag = 1;
            if (id && id->nombre) {
                // Obtener nombre único para variables FOR
                extern char* arm_get_unique_var_name(const char* original_name);
                char* unique_name = arm_get_unique_var_name(id->nombre);
                
                fprintf(ctx->out, "    adrp x1, GV_%s\n", unique_name);
                fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", unique_name);
                fprintf(ctx->out, "    ldr x1, [x1]\n");
                
                free(unique_name);
            }
        } else if (a && a->interpret == interpretExpresionLenguaje) {
            // Expresiones aritméticas o relacionales: evaluar y poner resultado en x1
            arm_emit_eval_expr(ctx, a, 1, ctx->out);
            
            // Determinar el tag basado en el tipo de operación
            ExpresionLenguaje* el = (ExpresionLenguaje*) a;
            extern Operacion tablaOperacionesIgualdad[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesDesigualdad[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesMayorQue[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesMenorQue[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesMayorIgualQue[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesMenorIgualQue[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesAnd[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesOr[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesNot[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesModulo[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesBitAnd[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesBitOr[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesBitXor[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesShiftLeft[TIPO_COUNT][TIPO_COUNT];
            extern Operacion tablaOperacionesShiftRight[TIPO_COUNT][TIPO_COUNT];
            
            if (el->tablaOperaciones == &tablaOperacionesIgualdad ||
                el->tablaOperaciones == &tablaOperacionesDesigualdad ||
                el->tablaOperaciones == &tablaOperacionesMayorQue ||
                el->tablaOperaciones == &tablaOperacionesMenorQue ||
                el->tablaOperaciones == &tablaOperacionesMayorIgualQue ||
                el->tablaOperaciones == &tablaOperacionesMenorIgualQue ||
                el->tablaOperaciones == &tablaOperacionesAnd ||
                el->tablaOperaciones == &tablaOperacionesOr ||
                el->tablaOperaciones == &tablaOperacionesNot) {
                tag = 4; // BOOLEAN para operaciones relacionales y lógicas
            } else if (el->tablaOperaciones == &tablaOperacionesBitAnd ||
                       el->tablaOperaciones == &tablaOperacionesBitOr ||
                       el->tablaOperaciones == &tablaOperacionesBitXor ||
                       el->tablaOperaciones == &tablaOperacionesShiftLeft ||
                       el->tablaOperaciones == &tablaOperacionesShiftRight ||
                       el->tablaOperaciones == &tablaOperacionesModulo) {
                tag = 1; // INT para operaciones de bits y módulo
            } else {
                tag = 2; // DOUBLE para operaciones aritméticas (suma, resta, multiplicación, división)
            }
        } else if (a && a->interpret == interpretUnarioLenguaje) {
            // Expresiones unarias (como NOT): evaluar y poner resultado en x1
            arm_emit_eval_expr(ctx, a, 1, ctx->out);
            tag = 4; // BOOLEAN para operaciones unarias lógicas
        }
        if (a && a->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* p = (PrimitivoExpresion*) a;
            if (p && p->valor) {
                if (p->tipo == STRING) {
                    const char* raw = p->valor; size_t L = strlen(raw);
                    char* stripped = NULL;
                    if (L>=2 && raw[0]=='"' && raw[L-1]=='"') stripped = strndup(raw+1, L-2);
                    else stripped = strdup(raw);
                    int sId = codegen_find_strlit(stripped);
                    if (sId <= 0) {
                        fprintf(stderr, "ERROR: STRLIT no encontrado para '%s' en concatenación\n", stripped);
                        fprintf(ctx->out, "    // ERROR: STRLIT no encontrado\n");
                        tag = -1; // Indicar error
                    } else {
                        fprintf(ctx->out, "    adrp x1, STRLIT_%d\n", sId);
                        fprintf(ctx->out, "    add x1, x1, :lo12:STRLIT_%d\n", sId);
                    }
                    free(stripped);
                } else if (p->tipo == INT) {
                    fprintf(ctx->out, "    mov x1, #%s\n", p->valor);
                } else if (p->tipo == DOUBLE) {
                    int id = codegen_register_numlit(NULL, p->valor);
                    fprintf(ctx->out, "    adrp x1, NUMLIT_%d\n", id);
                    fprintf(ctx->out, "    ldr x1, [x1, :lo12:NUMLIT_%d]\n", id);
                } else if (p->tipo == FLOAT) {
                    fprintf(ctx->out, "    mov w1, #%s\n", p->valor);
                } else if (p->tipo == BOOLEAN) {
                    fprintf(ctx->out, "    mov x1, #%s\n", (p->valor && strcmp(p->valor, "true")==0)?"1":"0");
                } else if (p->tipo == CHAR) {
                    int ch = (p->valor && strlen(p->valor)>0) ? (int)p->valor[0] : 0;
                    fprintf(ctx->out, "    mov w1, #%d\n", ch);
                }
            }
        }
        fprintf(ctx->out, "    mov w0, #%d\n", tag);
        fprintf(ctx->out, "    bl string_value_of_any\n");
        fprintf(ctx->out, "    mov x9, x0\n");
        fprintf(ctx->out, "    mov x0, x9\n");
        fprintf(ctx->out, "    mov x1, #%d\n", nl);
        fprintf(ctx->out, "    bl print_string\n");
        fprintf(ctx->out, "    mov x0, x9\n");
        fprintf(ctx->out, "    bl free\n\n");
        return 1;
    }
    return 0;
}

static void collect_string_valueof_calls(AbstractExpresion* n, AbstractExpresion*** out_calls, int* out_count, int* out_cap) {
    if (!n) return;
    if (n->interpret == interpretStringValueOf) {
        if (*out_count >= *out_cap) { *out_cap = (*out_cap==0)?8:(*out_cap)*2; *out_calls = (AbstractExpresion**)realloc(*out_calls, sizeof(AbstractExpresion*) * (*out_cap)); }
        (*out_calls)[(*out_count)++] = n;
        return;
    }
    for (size_t i = 0; i < n->numHijos; ++i) collect_string_valueof_calls(n->hijos[i], out_calls, out_count, out_cap);
}

// Recorrido in-order: emite imprimibles (primitivos, identificadores y String.valueOf)
static int emit_print_traverse_and_emit(CodegenContext* ctx, AbstractExpresion* n, int nl, char** emitted_names, int* emitted_types, int emitted_count) {
    if (!ctx || !ctx->out || !n) return 0;
    int emitted = 0;
    if (n->interpret == interpretPrimitivoExpresion) {
        if (emit_print_part(ctx, n, nl, emitted_names, emitted_types, emitted_count)) return 1;
        return 0;
    }
    if (n->interpret == interpretIdentificadorExpresion) {
        if (emit_print_part(ctx, n, nl, emitted_names, emitted_types, emitted_count)) return 1;
        return 0;
    }
    if (n->interpret == interpretStringValueOf) {
        if (emit_print_part(ctx, n, nl, emitted_names, emitted_types, emitted_count)) return 1;
        return 0;
    }
    for (size_t i = 0; i < n->numHijos; ++i) {
        int is_last_child = (i == n->numHijos - 1);
        int child_nl = is_last_child ? nl : 0;
        emitted += emit_print_traverse_and_emit(ctx, n->hijos[i], child_nl, emitted_names, emitted_types, emitted_count);
    }
    return emitted;
}

void emit_print_text(CodegenContext* ctx, AbstractExpresion* printNode, int label_id, char** emitted_names, int* emitted_types, int emitted_count) {
    if (!ctx || !ctx->out) return;
    if (printNode && printNode->numHijos>0) {
        AbstractExpresion* lista = printNode->hijos[0];
        int add_newline = 1;
        if (printNode->interpret == interpretPrintExpresion) { PrintExpresion* p = (PrintExpresion*) printNode; add_newline = p->newline ? 1 : 0; }
        
        fprintf(ctx->out, "    // ===== System.out.println =====\n");
        for (size_t i = 0; i < lista->numHijos; ++i) dump_print_ast_recursive(ctx, lista->hijos[i], 0);
        for (size_t i = 0; i < lista->numHijos; ++i) {
            int is_last = (i == (lista->numHijos - 1));
            int want_nl = is_last ? add_newline : 0;
            emit_print_traverse_and_emit(ctx, lista->hijos[i], want_nl, emitted_names, emitted_types, emitted_count);
        }
        fprintf(ctx->out, "    // ===== Fin System.out.println =====\n\n");
    }
}


