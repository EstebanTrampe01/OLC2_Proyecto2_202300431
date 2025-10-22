#define _POSIX_C_SOURCE 200809L
#include "codegen.h"
#include <stdlib.h>
#include <string.h>
// AST node headers used by codegen
#include "../ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"
#include "../ast/nodos/expresiones/terminales/primitivos.h"
#include "../ast/nodos/expresiones/terminales/identificadores.h"

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
    ctx->out = out;
    ctx->symbol_ctx = NULL;
    const char* dbg = getenv("CODEGEN_DEBUG");
    ctx->debug = (dbg && dbg[0] != '\0') ? 1 : 0;

    // register some default native helpers (phase1)
    extern void codegen_register_native(const char*, const char*, int);
    codegen_register_native("print", "print_string", 0);
    codegen_register_native("concat", "concat_string_string", 0);
    codegen_register_native("cmp_int_lt", "cmp_int_lt", 0);
    codegen_register_native("string_to_boolean", "string_to_boolean", 0);
    return ctx;
}

// Simple registry for string literals emitted in .data during PASADA1
static char** _strlit_values = NULL;
static int _strlit_count = 0;
static int _strlit_cap = 0;
static int _strlit_next_id = 0;

// Register a string literal value into the registry (no file emission). Returns id (>0).
static int codegen_register_strlit_value_internal(const char* val) {
    if (!val) return -1;
    // check existing
    for (int i = 0; i < _strlit_count; ++i) {
        if (_strlit_values[i] && strcmp(_strlit_values[i], val) == 0) return i+1;
    }
    if (_strlit_count >= _strlit_cap) {
        _strlit_cap = (_strlit_cap == 0) ? 8 : _strlit_cap * 2;
        _strlit_values = realloc(_strlit_values, sizeof(char*) * _strlit_cap);
    }
    char* copy = strdup(val);
    _strlit_values[_strlit_count++] = copy;
    int id = ++_strlit_next_id;
    return id;
}

static int codegen_find_strlit_internal(const char* val) {
    if (!val) return -1;
    for (int i = 0; i < _strlit_count; ++i) if (_strlit_values[i] && strcmp(_strlit_values[i], val) == 0) return i+1;
    return -1;
}

// Public wrappers used by other emitters (non-static)
int codegen_find_strlit(const char* val) {
    return codegen_find_strlit_internal(val);
}

int codegen_register_strlit(FILE* f, const char* val) {
    (void)f; // keep signature compatible with earlier callers; registration is independent of file
    return codegen_register_strlit_value_internal(val);
}

// Emit all registered string literals into the given file. Called during PASADA1
static void codegen_emit_all_strlits(FILE* f) {
    if (!f) return;
    for (int i = 0; i < _strlit_count; ++i) {
        if (!_strlit_values[i]) continue;
        fprintf(f, "STRLIT_%d:\n", i+1);
        fprintf(f, "    .asciz \"");
        for (size_t j = 0; j < strlen(_strlit_values[i]); ++j) {
            char c = _strlit_values[i][j];
            if (c == '\\') fprintf(f, "\\\\");
            else if (c == '"') fprintf(f, "\\\"");
            else if (c == '\n') fprintf(f, "\\n");
            else fprintf(f, "%c", c);
        }
        fprintf(f, "\"\n\n");
    }
}

// External emitters implemented in instrucciones/print.c
extern int emit_print_data(CodegenContext*, AbstractExpresion*);
extern void emit_print_text(CodegenContext*, AbstractExpresion*, int);
extern void emit_asignacion_text(CodegenContext*, AbstractExpresion*);

// utility: add name to emitted list if not present
static void add_emitted_name(char*** names_ptr, int* count_ptr, int* cap_ptr, const char* name) {
    if (!name) return;
    char** names = *names_ptr;
    int count = *count_ptr;
    int cap = *cap_ptr;
    for (int i=0;i<count;++i) if (names[i] && strcmp(names[i], name) == 0) return;
    if (count >= cap) {
        cap = (cap==0)? 8 : cap*2;
        names = realloc(names, sizeof(char*) * cap);
        *names_ptr = names; *cap_ptr = cap;
    }
    names[count++] = strdup(name);
    *count_ptr = count;
}

// Collect nodes: call emit_print_data for prints (so they emit Lx labels into .data),
// record assign nodes and GV names; if assignment RHS is a direct string primitive,
// register STRLIT and remember initializer id for the GV name.
static void collect_nodes(AbstractExpresion* n, CodegenContext* ctx,
    AbstractExpresion*** label_nodes_ptr, int** label_ids_ptr, int* label_map_size_ptr, int* label_map_capacity_ptr,
    AbstractExpresion*** assign_nodes_ptr, int* assign_size_ptr, int* assign_cap_ptr,
    char*** emitted_names_ptr, int* emitted_count_ptr, int* emitted_cap_ptr,
    int** emitted_init_ids_ptr,
    FILE* f) {

    if (!n) return;
    extern Result interpretPrintExpresion(AbstractExpresion*, Context*);
    extern Result interpretIdentificadorExpresion(AbstractExpresion*, Context*);
    extern Result interpretAsignacionExpresion(AbstractExpresion*, Context*);

    if (n->interpret == interpretPrintExpresion) {
        if (*label_map_size_ptr >= *label_map_capacity_ptr) {
            *label_map_capacity_ptr *= 2;
            *label_nodes_ptr = realloc(*label_nodes_ptr, sizeof(AbstractExpresion*) * (*label_map_capacity_ptr));
            *label_ids_ptr = realloc(*label_ids_ptr, sizeof(int) * (*label_map_capacity_ptr));
        }
        int id = emit_print_data(ctx, n);
        (*label_nodes_ptr)[*label_map_size_ptr] = n;
        (*label_ids_ptr)[*label_map_size_ptr] = id;
        (*label_map_size_ptr)++;
        // scan children for identifiers to pre-emit GV_
        if (n->numHijos>0 && n->hijos[0]) {
            for (size_t i=0;i<n->hijos[0]->numHijos;++i) {
                AbstractExpresion* e = n->hijos[0]->hijos[i];
                if (e && e->interpret == interpretIdentificadorExpresion) {
                    typedef struct { AbstractExpresion base; char* nombre; } IdentificadorExpresion;
                    IdentificadorExpresion* idexp = (IdentificadorExpresion*) e;
                    if (idexp->nombre) add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, idexp->nombre);
                }
            }
        }
    }

    if (n->interpret == interpretAsignacionExpresion) {
        if (*assign_size_ptr >= *assign_cap_ptr) {
            *assign_cap_ptr *= 2;
            *assign_nodes_ptr = realloc(*assign_nodes_ptr, sizeof(AbstractExpresion*) * (*assign_cap_ptr));
        }
        (*assign_nodes_ptr)[*assign_size_ptr] = n; (*assign_size_ptr)++;
        AsignacionExpresion* an = (AsignacionExpresion*) n;
        if (an && an->nombre) add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, an->nombre);
        // if RHS is direct primitive string literal, register STRLIT and set initializer
        if (n->numHijos>0) {
            AbstractExpresion* rhs = n->hijos[0];
            if (rhs->interpret == interpretPrimitivoExpresion) {
                typedef struct { AbstractExpresion base; TipoDato tipo; char* valor; } PrimitivoExpresion;
                PrimitivoExpresion* p = (PrimitivoExpresion*) rhs;
                if (p && p->valor && p->tipo == STRING) {
                    // remove surrounding quotes if present
                    const char* raw = p->valor;
                    size_t L = strlen(raw);
                    char* stripped = NULL;
                    if (L>=2 && raw[0]=='\"' && raw[L-1]=='\"') {
                        stripped = strndup(raw+1, L-2);
                    } else stripped = strdup(raw);
                    int id = codegen_register_strlit_value_internal(stripped);
                    free(stripped);
                    // find emitted_names index and set init id
                    for (int ii=0; ii<*emitted_count_ptr; ++ii) {
                        if ((*emitted_names_ptr)[ii] && strcmp((*emitted_names_ptr)[ii], an->nombre) == 0) { (*emitted_init_ids_ptr)[ii] = id; break; }
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < n->numHijos; ++i) collect_nodes(n->hijos[i], ctx, label_nodes_ptr, label_ids_ptr, label_map_size_ptr, label_map_capacity_ptr, assign_nodes_ptr, assign_size_ptr, assign_cap_ptr, emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, emitted_init_ids_ptr, f);
}

// Emit runtime nodes in program order by traversing AST and calling emit_print_text or emit_asignacion_text
static void emit_runtime_nodes(AbstractExpresion* n, CodegenContext* ctx, FILE* f, AbstractExpresion** label_nodes, int* label_ids, int label_map_size) {
    if (!n) return;
    extern Result interpretPrintExpresion(AbstractExpresion*, Context*);
    extern Result interpretAsignacionExpresion(AbstractExpresion*, Context*);
    if (n->interpret == interpretPrintExpresion) {
        int id = -1;
        for (int i=0;i<label_map_size;++i) if (label_nodes[i]==n) { id = label_ids[i]; break; }
        if (ctx->debug) fprintf(f, "# debug: emit runtime print label %d\n", id);
        if (id>0) emit_print_text(ctx, n, id);
        return;
    }
    if (n->interpret == interpretAsignacionExpresion) {
        if (ctx->debug) fprintf(f, "# debug: emit runtime asignacion\n");
        emit_asignacion_text(ctx, n);
        return;
    }
    for (size_t i = 0; i < n->numHijos; ++i) emit_runtime_nodes(n->hijos[i], ctx, f, label_nodes, label_ids, label_map_size);
}


void codegen_programa(CodegenContext* ctx, AbstractExpresion* root) {
    if (!ctx || !ctx->out) return;
    FILE* f = ctx->out;

    // PASADA 1: .data
    fprintf(f, "    .section .data\n");
    fprintf(f, "    .align 3\n");

    int label_map_capacity = 16; int label_map_size = 0;
    AbstractExpresion** label_nodes = malloc(sizeof(AbstractExpresion*) * label_map_capacity);
    int* label_ids = malloc(sizeof(int) * label_map_capacity);

    int assign_cap = 16; int assign_size = 0;
    AbstractExpresion** assign_nodes = malloc(sizeof(AbstractExpresion*) * assign_cap);

    int emitted_cap = 16; int emitted_count = 0;
    char** emitted_names = malloc(sizeof(char*) * emitted_cap);
    int* emitted_init_ids = malloc(sizeof(int) * emitted_cap);
    for (int i=0;i<emitted_cap;++i) emitted_init_ids[i]=0;

    // Collect nodes: this will call emit_print_data for prints (emits L labels) and register GV names
    collect_nodes(root, ctx, &label_nodes, &label_ids, &label_map_size, &label_map_capacity, &assign_nodes, &assign_size, &assign_cap, &emitted_names, &emitted_count, &emitted_cap, &emitted_init_ids, f);

    // Emit STRLITs registered during collection
    codegen_emit_all_strlits(f);

    // Emit GV_ symbols now
    for (int i = 0; i < emitted_count; ++i) {
        if (!emitted_names[i]) continue;
        if (emitted_init_ids[i] > 0) fprintf(f, "GV_%s: .quad STRLIT_%d\n\n", emitted_names[i], emitted_init_ids[i]);
        else fprintf(f, "GV_%s: .quad 0\n\n", emitted_names[i]);
    }

    // PASADA 2: .text
    fprintf(f, "    .section .text\n");
    fprintf(f, "    .global _start\n");
    fprintf(f, "_start:\n");

    emit_runtime_nodes(root, ctx, f, label_nodes, label_ids, label_map_size);

    // exit
    fprintf(f, "    mov x0, #0\n");
    fprintf(f, "    mov x8, #93\n");
    fprintf(f, "    svc #0\n");

    // cleanup
    free(label_nodes); free(label_ids);
    free(assign_nodes);
    for (int i=0;i<emitted_count;++i) if (emitted_names[i]) free(emitted_names[i]);
    free(emitted_names);
    free(emitted_init_ids);
    fflush(f);
}

void liberar_codegen_context(CodegenContext* ctx) {
    if (!ctx) return;
    // NO cerramos ctx->out porque el llamador puede cerrarlo
    free(ctx);
}
