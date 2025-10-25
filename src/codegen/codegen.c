#define _POSIX_C_SOURCE 200809L
#include "codegen.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "literals.h"
#include "native_impls.h"
#include "codegen/generadorARM/common.h"
#include "codegen/generadorARM/expresiones/emit_expr.h"
#include "codegen/generadorARM/instrucciones/runtime_nodes.h"

// Función de debug condicional
static int debug_enabled = 0;

void enable_debug_output() {
    debug_enabled = 1;
}

void debug_printf(const char* format, ...) {
    if (!debug_enabled) return;
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
// AST node headers used by codegen
#include "../ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"
#include "../ast/nodos/expresiones/terminales/primitivos.h"
#include "../ast/nodos/expresiones/terminales/identificadores.h"
// include expression node type for detection
#include "../ast/nodos/expresiones/expresiones.h"

// Buscar el primer literal/string dentro del AST (print o primitivo) para demo
static char* extract_first_string(AbstractExpresion* n) {
    if (!n) return NULL;
    // Comparar por puntero a función (conocido en AST)
    extern Result interpretPrintExpresion(AbstractExpresion*, Context*);
    extern Result interpretPrimitivoExpresion(AbstractExpresion*, Context*);

    if (n->interpret == interpretPrintExpresion) {
        // print: primer hijo puede ser lista de expresiones
        if (n->numHijos > 0 && n->hijos[0]) {
            // buscar recursivamente en la lista
            for (size_t i = 0; i < n->hijos[0]->numHijos; ++i) {
                char* s = extract_first_string(n->hijos[0]->hijos[i]);
                if (s) return s;
            }
        }
    }
    if (n->interpret == interpretPrimitivoExpresion) {
        // casteo seguro: buscar header de primitvo
        typedef struct { AbstractExpresion base; int tipo; char* valor; } PrimitivoExpresion;
        PrimitivoExpresion* p = (PrimitivoExpresion*) n;
        if (p->valor) return strdup(p->valor);
    }
    for (size_t i = 0; i < n->numHijos; ++i) {
        char* s = extract_first_string(n->hijos[i]);
        if (s) return s;
    }
    return NULL;
}

CodegenContext* nuevo_codegen_context(FILE* out) {
    CodegenContext* ctx = malloc(sizeof(CodegenContext));
    if (!ctx) return NULL;
    ctx->out = out;
    ctx->debug = 0;
    
    // Inicializar sistema de pila de etiquetas para break
    ctx->break_stack_capacity = 10;
    ctx->break_stack_size = 0;
    ctx->break_labels = malloc(sizeof(char*) * ctx->break_stack_capacity);
    if (!ctx->break_labels) {
        free(ctx);
        return NULL;
    }
    
    // Inicializar sistema de pila de etiquetas para continue
    ctx->continue_stack_capacity = 10;
    ctx->continue_stack_size = 0;
    ctx->continue_labels = malloc(sizeof(char*) * ctx->continue_stack_capacity);
    if (!ctx->continue_labels) {
        free(ctx->break_labels);
        free(ctx);
        return NULL;
    }
    ctx->symbol_ctx = NULL;
    // Debug solo se activa con variable de entorno CODEGEN_DEBUG=1
    ctx->debug = (getenv("CODEGEN_DEBUG") && strcmp(getenv("CODEGEN_DEBUG"), "1") == 0) ? 1 : 0;
    return ctx;
}
// Recursively emit code to evaluate an expression and place its result in x<target_reg>.
// Supports: primitive INT/STRING, identifier (GV_), and simple integer arithmetic (SUMA, RESTA, MULTIPLICACION, DIVISION).
// Uses x9/x10 as temporaries for sub-expression evaluation.
// emit_eval_expr fue extraído a arm_emit_eval_expr en generadorARM/expresiones/emit_expr.c


// External emitters implemented in instrucciones/print.c
extern int emit_print_data(CodegenContext*, AbstractExpresion*);
extern void emit_print_text(CodegenContext*, AbstractExpresion*, int, char**, int*, int);
extern void emit_asignacion_text(CodegenContext*, AbstractExpresion*);
// Generador ARM emitters (scaffold)
extern void emit_division_text(CodegenContext*, AbstractExpresion*, int);

// utility: add name to emitted list if not present
// add_emitted_name fue extraído a arm_add_emitted_name en common.c

// Collect nodes: call emit_print_data for prints (so they emit Lx labels into .data),
// record assign nodes and GV names; if assignment RHS is a direct string primitive,
// register STRLIT and remember initializer id for the GV name.
// collect_nodes fue extraído a arm_collect_nodes en instrucciones/runtime_nodes.c

// Emit runtime nodes in program order by traversing AST and calling emit_print_text or emit_asignacion_text
// emit_runtime_nodes fue extraído a arm_emit_runtime_nodes en instrucciones/runtime_nodes.c


void codegen_programa(CodegenContext* ctx, AbstractExpresion* root) {
    if (!ctx || !ctx->out) return;
    FILE* f = ctx->out;

    // PASADA 1: .data
    fprintf(f, "    .section .data\n");
    fprintf(f, "    .align 3\n");

    int label_map_capacity = 16; int label_map_size = 0;
    AbstractExpresion** label_nodes = malloc(sizeof(AbstractExpresion*) * label_map_capacity);
    int* label_ids = malloc(sizeof(int) * label_map_capacity);
    memset(label_nodes, 0, sizeof(AbstractExpresion*) * label_map_capacity);
    memset(label_ids, 0, sizeof(int) * label_map_capacity);

    int assign_cap = 16; int assign_size = 0;
    AbstractExpresion** assign_nodes = malloc(sizeof(AbstractExpresion*) * assign_cap);

    int emitted_cap = 64; int emitted_count = 0;  // Aumentar de 32 a 64 para test4.usl
    char** emitted_names = malloc(sizeof(char*) * emitted_cap);
    int* emitted_init_ids = malloc(sizeof(int) * emitted_cap);
    char** emitted_init_values = malloc(sizeof(char*) * emitted_cap); // store textual initializer for GV_<name>_str emission
    int* emitted_types = malloc(sizeof(int) * emitted_cap);
    
    // Verificar que todas las asignaciones de memoria fueron exitosas
    if (!emitted_names || !emitted_init_ids || !emitted_init_values || !emitted_types) {
        fprintf(stderr, "ERROR: No se pudo asignar memoria inicial para variables\n");
        exit(1);
    }
    for (int i=0;i<emitted_cap;++i) { emitted_init_ids[i]=0; emitted_names[i]=NULL; emitted_init_values[i]=NULL; emitted_types[i] = -1; }

    // Collect nodes: this will call emit_print_data for prints (emits L labels) and register GV names
    arm_collect_nodes(root, ctx, &label_nodes, &label_ids, &label_map_size, &label_map_capacity, &assign_nodes, &assign_size, &assign_cap, &emitted_names, &emitted_count, &emitted_cap, &emitted_init_ids, &emitted_init_values, emitted_types, f);

    // Emit STRLITs registered during collection
    codegen_emit_all_strlits(f);
    // NO emitir numeric literals aquí - se emitirán después de la fase .text

    // Emit GV_ symbols now, using emitted_types to choose directive
    for (int i = 0; i < emitted_count; ++i) {
        if (!emitted_names[i]) continue;
        int t = (emitted_types && i>=0) ? emitted_types[i] : -1;
        debug_printf("DEBUG: generando variable '%s' tipo=%d (emitted_types[%d]=%d)\n", emitted_names[i], t, i, emitted_types ? emitted_types[i] : -999);
        if (t == DOUBLE) {
            // if we have a textual initializer, use .double, else emit zero
            fprintf(f, "    .align 8\n");  // Alinear variables double en límite de 8 bytes
            if (emitted_init_values[i]) fprintf(f, "GV_%s: .double %s\n\n", emitted_names[i], emitted_init_values[i]);
            else fprintf(f, "GV_%s: .double 0.0\n\n", emitted_names[i]);
        } else if (t == FLOAT) {
            if (emitted_init_values[i]) fprintf(f, "GV_%s: .single %s\n\n", emitted_names[i], emitted_init_values[i]);
            else fprintf(f, "GV_%s: .single 0.0\n\n", emitted_names[i]);
        } else if (t == STRING && emitted_init_ids[i] > 0) {
            fprintf(f, "GV_%s: .quad STRLIT_%d\n\n", emitted_names[i], emitted_init_ids[i]);
        } else if (t == CHAR) {
            // store as 8-bit value in a quad for simplicity
            if (emitted_init_values[i]) fprintf(f, "GV_%s: .byte %d\n\n", emitted_names[i], (int)emitted_init_values[i][0]);
            else fprintf(f, "GV_%s: .byte 0\n\n", emitted_names[i]);
        } else if (t == INT || t == BOOLEAN) {
            if (t == BOOLEAN) {
                if (emitted_init_values[i]) {
                    if (strcmp(emitted_init_values[i], "true") == 0) fprintf(f, "GV_%s: .quad 1\n\n", emitted_names[i]);
                    else if (strcmp(emitted_init_values[i], "false") == 0) fprintf(f, "GV_%s: .quad 0\n\n", emitted_names[i]);
                    else fprintf(f, "GV_%s: .quad %s\n\n", emitted_names[i], emitted_init_values[i]);
                } else {
                    fprintf(f, "GV_%s: .quad 0\n\n", emitted_names[i]);
                }
            } else {
                if (emitted_init_values[i]) fprintf(f, "GV_%s: .quad %s\n\n", emitted_names[i], emitted_init_values[i]);
                else fprintf(f, "GV_%s: .quad 0\n\n", emitted_names[i]);
            }
        } else {
            if (emitted_init_ids[i] > 0) fprintf(f, "GV_%s: .quad STRLIT_%d\n\n", emitted_names[i], emitted_init_ids[i]);
            else if (emitted_init_values[i]) fprintf(f, "GV_%s: .quad 0\n\n", emitted_names[i]);
            else fprintf(f, "GV_%s: .quad 0\n\n", emitted_names[i]);
        }
    }

    // Emit textual representations for initialized globals (GV_<name>_str) so print emitter can use them
    for (int i = 0; i < emitted_count; ++i) {
        if (!emitted_names[i]) continue;
        if (emitted_init_values[i]) {
            // emitted_init_values contains a NUL-terminated C string ready to emit
            fprintf(f, "GV_%s_str:\n", emitted_names[i]);
            fprintf(f, "    .asciz \"");
            for (size_t j = 0; j < strlen(emitted_init_values[i]); ++j) {
                char c = emitted_init_values[i][j];
                if (c=='\\') fprintf(f, "\\\\");
                else if (c=='\"') fprintf(f, "\\\"");
                else if (c=='\n') fprintf(f, "\\n");
                else fprintf(f, "%c", c);
            }
            fprintf(f, "\"\n\n");
            fprintf(f, "GV_%s_str_end:\n\n", emitted_names[i]);
        }
    }

    fprintf(f, "    .section .text\n");
    fprintf(f, "    .global _start\n");
    fprintf(f, "_start:\n");
    
    // Inicializar la pila para operaciones con expresiones complejas
    fprintf(f, "    // Inicializar pila para operaciones complejas\n");
    fprintf(f, "    mov x0, sp\n");  // Guardar stack pointer inicial
    fprintf(f, "    sub sp, sp, #1024\n");  // Reservar espacio en la pila

    arm_emit_runtime_nodes(root, ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);

    // Volver a la sección .data para emitir literales numéricos registrados durante la fase .text
    fprintf(f, "    .section .data\n");
    codegen_emit_all_numlits(f);

    // Volver a la sección .text para el exit
    fprintf(f, "    .section .text\n");
    
    // exit
    fprintf(f, "    mov x0, #0\n");
    fprintf(f, "    mov x8, #93\n");
    fprintf(f, "    svc #0\n");

    // cleanup
    free(label_nodes); free(label_ids);
    free(assign_nodes);
    
    // NO liberar emitted_init_values[i] aquí porque apuntan a memoria que fue asignada
    // por el AST y será liberada cuando se libere el AST completo
    // Solo liberamos los arrays en sí
    for (int i=0;i<emitted_count;++i) { 
        if (emitted_names[i]) {
            debug_printf("DEBUG: liberando emitted_names[%d] = %p\n", i, emitted_names[i]);
            free(emitted_names[i]); 
        }
        // NO liberar emitted_init_values[i] - estos punteros apuntan a memoria del AST
        if (emitted_init_values[i]) {
            debug_printf("DEBUG: NO liberando emitted_init_values[%d] = %p (es memoria del AST o ya liberada)\n", i, emitted_init_values[i]);
        }
    }
    free(emitted_names);
    free(emitted_init_ids);
    free(emitted_init_values);
    free(emitted_types);
    fflush(f);
}

void liberar_codegen_context(CodegenContext* ctx) {
    if (!ctx) return;
    
    // Liberar pila de etiquetas break
    if (ctx->break_labels) {
        for (int i = 0; i < ctx->break_stack_size; i++) {
            if (ctx->break_labels[i]) {
                free(ctx->break_labels[i]);
            }
        }
        free(ctx->break_labels);
    }
    
    // Liberar pila de etiquetas continue
    if (ctx->continue_labels) {
        for (int i = 0; i < ctx->continue_stack_size; i++) {
            if (ctx->continue_labels[i]) {
                free(ctx->continue_labels[i]);
            }
        }
        free(ctx->continue_labels);
    }
    
    // NO cerramos ctx->out porque el llamador puede cerrarlo
    free(ctx);
}

// Sistema de pila de etiquetas para break
void codegen_push_break_label(CodegenContext* ctx, const char* label) {
    if (!ctx || !label) return;
    
    // Redimensionar si es necesario
    if (ctx->break_stack_size >= ctx->break_stack_capacity) {
        ctx->break_stack_capacity *= 2;
        ctx->break_labels = realloc(ctx->break_labels, sizeof(char*) * ctx->break_stack_capacity);
    }
    
    // Agregar la etiqueta a la pila
    ctx->break_labels[ctx->break_stack_size] = strdup(label);
    ctx->break_stack_size++;
}

void codegen_pop_break_label(CodegenContext* ctx) {
    if (!ctx || ctx->break_stack_size <= 0) return;
    
    // Liberar la etiqueta del tope
    ctx->break_stack_size--;
    if (ctx->break_labels[ctx->break_stack_size]) {
        free(ctx->break_labels[ctx->break_stack_size]);
        ctx->break_labels[ctx->break_stack_size] = NULL;
    }
}

const char* codegen_get_current_break_label(CodegenContext* ctx) {
    if (!ctx || ctx->break_stack_size <= 0) return NULL;
    return ctx->break_labels[ctx->break_stack_size - 1];
}

// Sistema de pila de etiquetas para continue
void codegen_push_continue_label(CodegenContext* ctx, const char* label) {
    if (!ctx || !label) return;
    if (ctx->continue_stack_size >= ctx->continue_stack_capacity) {
        ctx->continue_stack_capacity *= 2;
        ctx->continue_labels = realloc(ctx->continue_labels, sizeof(char*) * ctx->continue_stack_capacity);
    }
    ctx->continue_labels[ctx->continue_stack_size] = strdup(label);
    ctx->continue_stack_size++;
}

void codegen_pop_continue_label(CodegenContext* ctx) {
    if (!ctx || ctx->continue_stack_size <= 0) return;
    ctx->continue_stack_size--;
    if (ctx->continue_labels[ctx->continue_stack_size]) {
        free(ctx->continue_labels[ctx->continue_stack_size]);
        ctx->continue_labels[ctx->continue_stack_size] = NULL;
    }
}

const char* codegen_get_current_continue_label(CodegenContext* ctx) {
    if (!ctx || ctx->continue_stack_size <= 0) return NULL;
    return ctx->continue_labels[ctx->continue_stack_size - 1];
}
