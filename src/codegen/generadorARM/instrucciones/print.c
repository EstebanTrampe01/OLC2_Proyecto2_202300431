#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../../../../src/ast/nodos/expresiones/listaExpresiones.h"
#include "../../../../src/ast/nodos/expresiones/cast.h"
#include "../../../../src/ast/nodos/expresiones/expresiones.h" // for unario
#include "../../../../src/ast/nodos/expresiones/builtins.h" // for interpretStringValueOf

// externs so we can print their addresses for debugging
extern Result interpretListaExpresiones(AbstractExpresion*, Context*);
extern Result interpretCastExpresion(AbstractExpresion*, Context*);
extern Result interpretUnarioLenguaje(AbstractExpresion*, Context*);
extern Result interpretStringValueOf(AbstractExpresion*, Context*);
#include "../../../../src/ast/nodos/expresiones/terminales/primitivos.h"
#include "../../../../src/ast/nodos/instrucciones/instruccion/print.h" // for PrintExpresion
#include "../../../../src/ast/nodos/expresiones/terminales/identificadores.h"
#include "../../../../src/ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"
#include "../../../../src/ast/nodos/expresiones/expresiones.h"
#include "../../../../src/ast/nodos/instrucciones/instruccion/funcion.h"

/* Local view of unary wrapper nodes used by builtins so we can access the
 * inner expression when the AST node doesn't use hijos[] (many builtin
 * wrappers store their child in an `a` field). This mirrors the layout in
 * src/ast/nodos/expresiones/builtins.c: typedef struct { AbstractExpresion base; AbstractExpresion* a; } UnaryWrap;
*/
typedef struct { AbstractExpresion base; AbstractExpresion* a; } UnaryWrapLocal;

// Counter simple para etiquetas de mensajes
static int next_label_id = 0;

// Helper para concatenar literales de la lista de expresiones (si existen)
static char* collect_print_message(AbstractExpresion* listaExpr, int add_newline) {
    if (!listaExpr) {
        if (!add_newline) return NULL;
        char* out = malloc(2);
        out[0] = '\n'; out[1] = '\0';
        return out;
    }
    // listaExpr es ListaExpresiones: hijos son las expresiones
    size_t total = 0;
    // Primera pasada: calcular tamaño
    for (size_t i = 0; i < listaExpr->numHijos; ++i) {
        AbstractExpresion* e = listaExpr->hijos[i];
        if (e->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* p = (PrimitivoExpresion*) e;
            if (p->valor) total += strlen(p->valor);
        }
    }
    if (total == 0) {
        if (!add_newline) return NULL;
        /* Only a newline requested (e.g., println() with no args) */
        char* out = malloc(2);
        out[0] = '\n'; out[1] = '\0';
        return out;
    }
    /* Reserve extra byte if newline requested */
    char* out = malloc(total + (add_newline ? 2 : 1));
    size_t pos = 0;
    for (size_t i = 0; i < listaExpr->numHijos; ++i) {
        AbstractExpresion* e = listaExpr->hijos[i];
        if (e->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* p = (PrimitivoExpresion*) e;
            if (p->valor) {
                size_t l = strlen(p->valor);
                memcpy(out + pos, p->valor, l);
                pos += l;
            }
        }
    }
    if (add_newline) out[pos++] = '\n';
    out[pos] = '\0';
    return out;
}

// Recursively register any string primitive literals found inside an expression list
// so they appear in the global STRLIT registry during PASADA1.
static void register_print_strlits(AbstractExpresion* n) {
    if (!n) return;
    // primitive
    if (n->interpret == interpretPrimitivoExpresion) {
        PrimitivoExpresion* p = (PrimitivoExpresion*) n;
        if (p && p->valor && p->tipo == STRING) {
            const char* raw = p->valor; size_t L = strlen(raw);
            char* stripped = NULL;
            if (L>=2 && raw[0]=='"' && raw[L-1]=='"') stripped = strndup(raw+1, L-2);
            else stripped = strdup(raw);
            codegen_register_strlit(NULL, stripped);
            free(stripped);
        }
        return;
    }
    // recurse children
    for (size_t i = 0; i < n->numHijos; ++i) register_print_strlits(n->hijos[i]);
}

// Diagnostic: dump AST nodes for a print argument list as comments in the assembly
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
    // basic info: interpret pointer is a function pointer — print a human-friendly tag
    const char* itname = "UNKNOWN";
    // print interpret pointer address to help correlate unknown nodes
    uintptr_t iptr = (uintptr_t) n->interpret;
    if (n->interpret == interpretPrimitivoExpresion) itname = "PRIMITIVO";
    else if (n->interpret == interpretIdentificadorExpresion) itname = "IDENTIFICADOR";
    else if (n->interpret == interpretExpresionLenguaje) itname = "EXPRESION_LENGUAJE";
    else if (n->interpret == interpretLlamadaFuncion) itname = "LLAMADA_FUNCION";
    else if (n->interpret == interpretPrintExpresion) itname = "PRINT_EXPR";
    fprintf(ctx->out, "# AST node: %s iptr=0x%lx children=%zu\n", itname, (unsigned long)iptr, n->numHijos);
    // show details for some node types
    if (n->interpret == interpretPrimitivoExpresion) {
        PrimitivoExpresion* p = (PrimitivoExpresion*) n;
        for (int i = 0; i < depth; ++i) fprintf(ctx->out, "# ");
        const char* raw = p->valor ? p->valor : "(null)";
        // escape newlines and tabs to keep the comment as a single line
        size_t L = strlen(raw);
        char* esc = malloc(L*2 + 1);
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
        char* iesc = malloc(Li*2 + 1);
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
        char* lesc = malloc(Ll*2 + 1);
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
    // recurse
    for (size_t i = 0; i < n->numHijos; ++i) dump_print_ast_recursive(ctx, n->hijos[i], depth+1);
}

// Collect all LlamadaFuncion nodes with name "String.valueOf" into a dynamic array.
static void collect_string_valueof_calls(AbstractExpresion* n, AbstractExpresion*** out_calls, int* out_count, int* out_cap) {
    if (!n) return;
    if (n->interpret == interpretLlamadaFuncion) {
        LlamadaFuncion* lf = (LlamadaFuncion*) n;
        if (lf && lf->nombre && strcmp(lf->nombre, "String.valueOf") == 0) {
            if (*out_count >= *out_cap) { *out_cap = (*out_cap==0)?8:(*out_cap)*2; *out_calls = realloc(*out_calls, sizeof(AbstractExpresion*) * (*out_cap)); }
            (*out_calls)[(*out_count)++] = n;
            return;
        }
    }
    for (size_t i = 0; i < n->numHijos; ++i) collect_string_valueof_calls(n->hijos[i], out_calls, out_count, out_cap);
}



    #include "../../../../src/context/result.h" // for TipoDato
int emit_print_data(CodegenContext* ctx, AbstractExpresion* printNode) {
    if (!ctx || !ctx->out || !printNode) return -1;
    // printNode->hijos[0] es la lista de expresiones
    AbstractExpresion* lista = (printNode->numHijos>0)? printNode->hijos[0] : NULL;
    /* Determine newline behavior from PrintExpresion */
    int add_newline = 1; /* default to println to preserve previous behavior */
    if (printNode->interpret == interpretPrintExpresion) {
        PrintExpresion* p = (PrintExpresion*) printNode;
        add_newline = p->newline ? 1 : 0;
    }
    // Ensure any sub-primitive string literals are registered globally before we emit STRLITs
    register_print_strlits(lista);
    char* msg = collect_print_message(lista, add_newline);
    if (!msg) return -1;
    int id = ++next_label_id;
    // emitir etiqueta y .asciz
    fprintf(ctx->out, "L%u:\n", id);
    // escapado mínimo
    fprintf(ctx->out, "    .asciz \"");
    for (size_t i = 0; i < strlen(msg); ++i) {
        char c = msg[i];
        if (c == '\\') fprintf(ctx->out, "\\\\");
        else if (c == '"') fprintf(ctx->out, "\\\"");
        else if (c == '\n') fprintf(ctx->out, "\\n");
        else fprintf(ctx->out, "%c", c);
    }
    fprintf(ctx->out, "\"\n\n");
    // Emitir etiqueta de fin para calcular longitud en tiempo de ejecución via sub
    fprintf(ctx->out, "L%u_end:\n", id);
    fprintf(ctx->out, "\n");
    free(msg);
    return id;
}

// Emit a single printable part recursively. Returns 1 if handled, 0 otherwise.
static int emit_print_part(CodegenContext* ctx, AbstractExpresion* n, int nl, char** emitted_names, int* emitted_types, int emitted_count) {
    if (!ctx || !ctx->out || !n) return 0;
    // Unwrap single-child wrapper nodes produced by the parser so we can
    // reach the underlying primitive/identifier/function call used in concatenations.
    AbstractExpresion* cur = n;
    while (cur && cur->numHijos == 1 && cur->interpret != interpretPrimitivoExpresion
           && cur->interpret != interpretIdentificadorExpresion && cur->interpret != interpretLlamadaFuncion) {
        cur = cur->hijos[0];
    }
    if (!cur) return 0;
    // primitive literal
    if (cur->interpret == interpretPrimitivoExpresion) {
        PrimitivoExpresion* p = (PrimitivoExpresion*) cur;
        const char* raw = p->valor ? p->valor : "";
        size_t L = strlen(raw);
        char* stripped = NULL;
        if (L>=2 && raw[0]=='"' && raw[L-1]=='"') stripped = strndup(raw+1, L-2);
        else stripped = strdup(raw);
        int sId = codegen_find_strlit(stripped);
        if (sId <= 0) sId = codegen_register_strlit(NULL, stripped);
        free(stripped);
        fprintf(ctx->out, "    adrp x0, STRLIT_%d\n", sId);
        fprintf(ctx->out, "    add x0, x0, :lo12:STRLIT_%d\n", sId);
        fprintf(ctx->out, "    mov x1, #%d\n", nl);
        fprintf(ctx->out, "    bl print_string\n\n");
        return 1;
    }
    // identifier
    if (cur->interpret == interpretIdentificadorExpresion) {
        IdentificadorExpresion* id = (IdentificadorExpresion*) cur;
        fprintf(ctx->out, "    adrp x0, GV_%s\n", id->nombre);
        fprintf(ctx->out, "    add x0, x0, :lo12:GV_%s\n", id->nombre);
        int tag = 0;
        if (emitted_names && emitted_types) {
            for (int ii = 0; ii < emitted_count; ++ii) {
                if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) { tag = emitted_types[ii]; break; }
            }
        }
        fprintf(ctx->out, "    // tipo tag=%d\n", tag);
        fprintf(ctx->out, "    mov x1, #%d\n", tag);
        fprintf(ctx->out, "    mov x2, #%d\n", nl);
        fprintf(ctx->out, "    bl print_any_gv\n\n");
        return 1;
    }
    // SUMA (binary) flattening
    if (cur->interpret == interpretExpresionLenguaje) {
        // Treat any binary ExpresionLenguaje as concatenation.
        if (cur->numHijos == 2) {
            if (!emit_print_part(ctx, cur->hijos[0], 0, emitted_names, emitted_types, emitted_count)) return 0;
            if (!emit_print_part(ctx, cur->hijos[1], nl, emitted_names, emitted_types, emitted_count)) return 0;
            return 1;
        }
    }
    // LlamadaFuncion: handle String.valueOf(...) anywhere
    if (cur->interpret == interpretLlamadaFuncion) {
        LlamadaFuncion* call = (LlamadaFuncion*) cur;
        if (!call || !call->nombre) return 0;
        if (strcmp(call->nombre, "String.valueOf") != 0) return 0;
        AbstractExpresion* a = (call->args && call->args->numHijos>0) ? call->args->hijos[0] : NULL;
        int tag = 1; // default INT
        // primitive arg
        if (a && a->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* p = (PrimitivoExpresion*) a;
            if (p) {
                if (p->tipo == STRING) tag = 6; else if (p->tipo == INT) tag = 1; else if (p->tipo == DOUBLE) tag = 2; else if (p->tipo == FLOAT) tag = 3; else if (p->tipo == BOOLEAN) tag = 4; else if (p->tipo == CHAR) tag = 5;
            }
        } else if (a && a->interpret == interpretIdentificadorExpresion) {
            IdentificadorExpresion* id = (IdentificadorExpresion*) a;
            for (int ii = 0; ii < emitted_count; ++ii) if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) { tag = emitted_types[ii]; break; }
            if (tag == STRING) tag = 6; else if (tag == DOUBLE) tag = 2; else if (tag == FLOAT) tag = 3; else if (tag == BOOLEAN) tag = 4; else if (tag == CHAR) tag = 5; else tag = 1;
            // load value into x1
            fprintf(ctx->out, "    adrp x1, GV_%s\n", id->nombre);
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", id->nombre);
            fprintf(ctx->out, "    ldr x1, [x1]\n");
        }
        // primitive literal arg handling (place into x1)
        if (a && a->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* p = (PrimitivoExpresion*) a;
            if (p && p->valor) {
                if (p->tipo == STRING) {
                    const char* raw = p->valor; size_t L = strlen(raw);
                    char* stripped = NULL;
                    if (L>=2 && raw[0]=='"' && raw[L-1]=='"') stripped = strndup(raw+1, L-2);
                    else stripped = strdup(raw);
                    int sId = codegen_find_strlit(stripped);
                    if (sId <= 0) sId = codegen_register_strlit(NULL, stripped);
                    free(stripped);
                    fprintf(ctx->out, "    adrp x1, STRLIT_%d\n", sId);
                    fprintf(ctx->out, "    add x1, x1, :lo12:STRLIT_%d\n", sId);
                } else if (p->tipo == INT) {
                    fprintf(ctx->out, "    mov x1, #%s\n", p->valor);
                } else if (p->tipo == DOUBLE) {
                    int id = codegen_register_numlit(NULL, p->valor);
                    fprintf(ctx->out, "    adrp x1, NUMLIT_%d@PAGE\n", id);
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
        // call helper
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
    // Builtin unary wrapper: interpretStringValueOf may be represented as a UnaryWrap
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
                fprintf(ctx->out, "    adrp x1, GV_%s\n", id->nombre);
                fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", id->nombre);
                fprintf(ctx->out, "    ldr x1, [x1]\n");
            }
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
                    if (sId <= 0) sId = codegen_register_strlit(NULL, stripped);
                    free(stripped);
                    fprintf(ctx->out, "    adrp x1, STRLIT_%d\n", sId);
                    fprintf(ctx->out, "    add x1, x1, :lo12:STRLIT_%d\n", sId);
                } else if (p->tipo == INT) {
                    fprintf(ctx->out, "    mov x1, #%s\n", p->valor);
                } else if (p->tipo == DOUBLE) {
                    int id = codegen_register_numlit(NULL, p->valor);
                    fprintf(ctx->out, "    adrp x1, NUMLIT_%d@PAGE\n", id);
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

// Fallback: traverse the tree in-order and emit printers for primitives, identifiers,
// and String.valueOf(...) calls as they appear. Returns number of emitted parts.
static int emit_print_traverse_and_emit(CodegenContext* ctx, AbstractExpresion* n, int nl, char** emitted_names, int* emitted_types, int emitted_count) {
    if (!ctx || !ctx->out || !n) return 0;
    int emitted = 0;
    // If node is primitive/ident/llamada, try to emit directly
    if (n->interpret == interpretPrimitivoExpresion) {
        if (emit_print_part(ctx, n, nl, emitted_names, emitted_types, emitted_count)) return 1;
        return 0;
    }
    if (n->interpret == interpretIdentificadorExpresion) {
        if (emit_print_part(ctx, n, nl, emitted_names, emitted_types, emitted_count)) return 1;
        return 0;
    }
    if (n->interpret == interpretLlamadaFuncion) {
        // Try to handle String.valueOf here
        LlamadaFuncion* call = (LlamadaFuncion*) n;
        if (call && call->nombre && strcmp(call->nombre, "String.valueOf") == 0) {
            if (emit_print_part(ctx, n, nl, emitted_names, emitted_types, emitted_count)) return 1;
            return 0;
        }
    }
    // Otherwise traverse children in order
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

        // Diagnostic dump of AST for each argument
        for (size_t i = 0; i < lista->numHijos; ++i) dump_print_ast_recursive(ctx, lista->hijos[i], 0);

        // Try to emit each top-level argument deterministically
        int all_handled = 1;
        for (size_t ei = 0; ei < lista->numHijos; ++ei) {
            int is_last = (ei == (lista->numHijos - 1));
            int want_nl = is_last ? add_newline : 0;
            if (!emit_print_part(ctx, lista->hijos[ei], want_nl, emitted_names, emitted_types, emitted_count)) { all_handled = 0; break; }
        }
        if (all_handled) return;
        // else fallthrough to legacy behavior below
    }
    // Fallback: even if we fall back to legacy printing of the precomputed label,
    // some parts of the expression may be function calls like String.valueOf(...).
    // Emit calls for each such function after printing the label so values appear.
    if (printNode && printNode->numHijos>0) {
        AbstractExpresion* lista2 = printNode->hijos[0];
        // collect calls
        AbstractExpresion** calls = NULL; int calls_count = 0; int calls_cap = 0;
        collect_string_valueof_calls(lista2, &calls, &calls_count, &calls_cap);
        if (calls_count > 0) {
            for (int ci = 0; ci < calls_count; ++ci) {
                LlamadaFuncion* call = (LlamadaFuncion*) calls[ci];
                AbstractExpresion* a = (call->args && call->args->numHijos>0) ? call->args->hijos[0] : NULL;
                int tag = 0;
                if (a && a->interpret == interpretPrimitivoExpresion) {
                    PrimitivoExpresion* p = (PrimitivoExpresion*) a;
                    if (p) {
                        if (p->tipo == STRING) tag = 6;
                        else if (p->tipo == INT) tag = 1;
                        else if (p->tipo == DOUBLE) tag = 2;
                        else if (p->tipo == FLOAT) tag = 3;
                        else if (p->tipo == BOOLEAN) tag = 4;
                        else if (p->tipo == CHAR) tag = 5;
                    }
                } else if (a && a->interpret == interpretIdentificadorExpresion) {
                    IdentificadorExpresion* id = (IdentificadorExpresion*) a;
                    if (id && id->nombre) {
                        for (int ii = 0; ii < emitted_count; ++ii) {
                            if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) { tag = emitted_types[ii]; break; }
                        }
                        if (tag == STRING) tag = 6; else if (tag == DOUBLE) tag = 2; else if (tag == FLOAT) tag = 3; else if (tag == BOOLEAN) tag = 4; else if (tag == CHAR) tag = 5; else tag = 1;
                        fprintf(ctx->out, "    adrp x1, GV_%s\n", id->nombre);
                        fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", id->nombre);
                        fprintf(ctx->out, "    ldr x1, [x1]\n");
                    }
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
                            if (sId <= 0) sId = codegen_register_strlit(NULL, stripped);
                            free(stripped);
                            fprintf(ctx->out, "    adrp x1, STRLIT_%d\n", sId);
                            fprintf(ctx->out, "    add x1, x1, :lo12:STRLIT_%d\n", sId);
                        } else if (p->tipo == INT) {
                            fprintf(ctx->out, "    mov x1, #%s\n", p->valor);
                        } else if (p->tipo == DOUBLE) {
                            int id = codegen_register_numlit(NULL, p->valor);
                            fprintf(ctx->out, "    adrp x1, NUMLIT_%d@PAGE\n", id);
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
                // newline only on last call; compute newline from printNode if available
                int nlflag = 0;
                if (ci == calls_count-1) {
                    if (printNode && printNode->interpret == interpretPrintExpresion) {
                        PrintExpresion* pp = (PrintExpresion*) printNode;
                        nlflag = pp->newline ? 1 : 0;
                    } else nlflag = 1;
                }
                fprintf(ctx->out, "    mov x1, #%d\n", nlflag);
                fprintf(ctx->out, "    bl print_string\n");
                fprintf(ctx->out, "    mov x0, x9\n");
                fprintf(ctx->out, "    bl free\n\n");
            }
            if (calls) free(calls);
        }
    }
    // compute length by printing a comment (length must be known by caller ideally)
    // For simplicity, we will load address and rely on null-terminated string and compute length at runtime is expensive.
    // Here we assume short messages and hardcode mov x2,#len by calculating from symbol label (not possible here).
    // Simpler: use write with strlen at runtime: call a small helper that computes strlen and writes. But to keep it simple,
    // we'll emit the same pattern used previously but with a placeholder length 0 (not portable).
    // For now we emit ADRP/ADD and a fixed mov x2, #0 comment; this is a placeholder until we compute the length earlier.
    if (ctx->debug) fprintf(ctx->out, "# debug: entering codegen_print_instr\n");
    // Load start and end addresses, compute len = end - start, then syscall write
    fprintf(ctx->out, "    adrp x1, L%d\n", label_id);
    fprintf(ctx->out, "    add x1, x1, :lo12:L%d\n", label_id);
    fprintf(ctx->out, "    adrp x2, L%d_end\n", label_id);
    fprintf(ctx->out, "    add x2, x2, :lo12:L%d_end\n", label_id);
    fprintf(ctx->out, "    sub x2, x2, x1\n");
    fprintf(ctx->out, "    mov x0, #1\n");
    fprintf(ctx->out, "    mov x8, #64\n");
    fprintf(ctx->out, "    svc #0\n\n");
    if (ctx->debug) fprintf(ctx->out, "# debug: leaving codegen_print_instr\n");
}

// Emitir una asignaci f3n simple a una variable global GV_<name>
// Solo maneja RHS literal (PrimitivoExpresion) por ahora
void emit_asignacion_text(CodegenContext* ctx, AbstractExpresion* asignNode) {
    if (!ctx || !ctx->out || !asignNode) return;
    // asignNode es AsignacionExpresion; hijos[0] es la expresi f3n RHS
    AsignacionExpresion* a = (AsignacionExpresion*) asignNode;
    if (asignNode->numHijos == 0) return;
    AbstractExpresion* rhs = asignNode->hijos[0];
    // Solo manejar primitivos por ahora
    if (rhs->interpret != interpretPrimitivoExpresion) {
        if (ctx->debug) fprintf(ctx->out, "# debug: asignaci\u00f3n RHS no es primitivo, ignorando\n");
        return;
    }
    PrimitivoExpresion* p = (PrimitivoExpresion*) rhs;
    // Use AST type information from PrimitivoExpresion->tipo to decide emission
    if (!p) { if (ctx->debug) fprintf(ctx->out, "# debug: primitivo NULL\n"); return; }
    switch (p->tipo) {
        case INT: {
            long ival = atol(p->valor ? p->valor : "0");
            fprintf(ctx->out, "    // store integer %ld into GV_%s\n", ival, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);
            fprintf(ctx->out, "    mov x2, #%ld\n", ival);
            fprintf(ctx->out, "    str x2, [x1]\n\n");
            break;
        }
        case BOOLEAN: {
            int b = (p->valor && strcmp(p->valor, "true") == 0) ? 1 : 0;
            fprintf(ctx->out, "    // store boolean %d into GV_%s\n", b, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);
            fprintf(ctx->out, "    mov x2, #%d\n", b);
            fprintf(ctx->out, "    str x2, [x1]\n\n");
            break;
        }
        case CHAR: {
            char ch = (p->valor && strlen(p->valor)>0) ? p->valor[0] : '\0';
            int c = (int) ch;
            fprintf(ctx->out, "    // store char %c into GV_%s\n", ch, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);
            fprintf(ctx->out, "    mov w2, #%d\n", c);
            fprintf(ctx->out, "    strb w2, [x1]\n\n");
            break;
        }
        case STRING: {
            const char* tmpval = p->valor ? p->valor : "";
            // If value is quoted, strip quotes for storage
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
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);
            fprintf(ctx->out, "    adrp x2, STRLIT_%d\n", sId);
            fprintf(ctx->out, "    add x2, x2, :lo12:STRLIT_%d\n", sId);
            fprintf(ctx->out, "    str x2, [x1]\n\n");
            break;
        }
        default:
            if (ctx->debug) fprintf(ctx->out, "# debug: asignaci\u00f3n literal tipo no reconocido (tipo=%d)\n", p->tipo);
            break;
    }
}
