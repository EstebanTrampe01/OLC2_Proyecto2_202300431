#define _POSIX_C_SOURCE 200809L
#include "codegen.h"
#include <stdlib.h>
#include <string.h>
#include "literals.h"
#include "native_impls.h"
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
    ctx->symbol_ctx = NULL;
    ctx->debug = 0;
    return ctx;
}
// Recursively emit code to evaluate an expression and place its result in x<target_reg>.
// Supports: primitive INT/STRING, identifier (GV_), and simple integer arithmetic (SUMA, RESTA, MULTIPLICACION, DIVISION).
// Uses x9/x10 as temporaries for sub-expression evaluation.
static void emit_eval_expr(CodegenContext* ctx, AbstractExpresion* expr, int target_reg, FILE* f) {
    if (!expr || !f) return;
    extern Result interpretPrimitivoExpresion(AbstractExpresion*, Context*);
    extern Result interpretIdentificadorExpresion(AbstractExpresion*, Context*);
    extern Result interpretExpresionLenguaje(AbstractExpresion*, Context*);
    extern Result interpretLlamadaFuncion(AbstractExpresion*, Context*);

    // Primitives
    if (expr->interpret == interpretPrimitivoExpresion) {
        typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr;
        Pr* p = (Pr*) expr;
        if (p && p->valor) {
            if (p->tipo == STRING) {
                int id = codegen_register_strlit(NULL, p->valor);
                fprintf(f, "    adrp x%d, STRLIT_%d@PAGE\n", target_reg, id);
                fprintf(f, "    add x%d, x%d, STRLIT_%d@PAGEOFF\n", target_reg, target_reg, id);
                return;
            } else if (p->tipo == INT) {
                fprintf(f, "    mov x%d, #%s\n", target_reg, p->valor);
                return;
            } else if (p->tipo == DOUBLE) {
                int id = codegen_register_numlit(NULL, p->valor);
                fprintf(f, "    adrp x%d, NUMLIT_%d@PAGE\n", target_reg, id);
                fprintf(f, "    ldr x%d, [x%d, :lo12:NUMLIT_%d]\n", target_reg, target_reg, id);
                return;
            }
        }
        fprintf(f, "    mov x%d, #0\n", target_reg);
        return;
    }

    // Function call expression (native helper)
    if (expr->interpret == interpretLlamadaFuncion) {
        typedef struct { AbstractExpresion base; char* nombre; AbstractExpresion* args; } LlamadaFuncionLocal;
        LlamadaFuncionLocal* call = (LlamadaFuncionLocal*) expr;
        if (call && call->nombre && codegen_is_native(call->nombre)) {
            const char* helper = codegen_get_native_helper(call->nombre);
            if (!helper) helper = call->nombre;
            if (call->args) {
                for (size_t ai = 0; ai < call->args->numHijos && ai < 8; ++ai) {
                    AbstractExpresion* a = call->args->hijos[ai];
                    extern Result interpretPrimitivoExpresion(AbstractExpresion*, Context*);
                    int akind = codegen_get_native_arg_kind(call->nombre, (int)ai);
                    if (a && a->interpret == interpretPrimitivoExpresion) {
                        typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr2;
                        Pr2* p = (Pr2*) a;
                        if (p && p->valor) {
                            if (p->tipo == STRING) {
                                int id = codegen_register_strlit(NULL, p->valor);
                                // strings always passed as pointers in xN
                                fprintf(f, "    adrp x%zu, STRLIT_%d@PAGE\n", ai, id);
                                fprintf(f, "    add x%zu, x%zu, STRLIT_%d@PAGEOFF\n", ai, ai, id);
                            } else if (p->tipo == INT) {
                                fprintf(f, "    mov x%zu, #%s\n", ai, p->valor);
                            } else if (p->tipo == DOUBLE) {
                                int id = codegen_register_numlit(NULL, p->valor);
                                fprintf(f, "    adrp x%zu, NUMLIT_%d@PAGE\n", ai, id);
                                fprintf(f, "    ldr x%zu, [x%zu, :lo12:NUMLIT_%d]\n", ai, ai, id);
                                // if signature expects double, move into dN
                                if (akind == ARG_KIND_DOUBLE) fprintf(f, "    fmov d%zu, x%zu\n", ai, ai);
                            } else {
                                fprintf(f, "    mov x%zu, #0\n", ai);
                            }
                        } else {
                            fprintf(f, "    mov x%zu, #0\n", ai);
                        }
                    } else if (a && a->interpret == interpretIdentificadorExpresion) {
                        typedef struct { AbstractExpresion base; char* nombre; } IdentificadorExpresionLocal;
                        IdentificadorExpresionLocal* id = (IdentificadorExpresionLocal*) a;
                        if (id && id->nombre) {
                            fprintf(f, "    adrp x%zu, GV_%s@PAGE\n", ai, id->nombre);
                            fprintf(f, "    add x%zu, x%zu, GV_%s@PAGEOFF\n", ai, ai, id->nombre);
                            fprintf(f, "    ldr x%zu, [x%zu]\n", ai, ai);
                        } else {
                            fprintf(f, "    mov x%zu, #0\n", ai);
                        }
                    } else {
                        emit_eval_expr(ctx, a, (int)ai, f);
                    }
                }
            }
            fprintf(f, "    bl %s\n", helper);
            int ret = codegen_get_native_return(call->nombre);
            if (ret == NATIVE_RET_DOUBLE) {
                fprintf(f, "    fmov x%d, d0\n", target_reg);
            } else {
                fprintf(f, "    mov x%d, x0\n", target_reg);
            }
            return;
        }
    }

    if (expr->interpret == interpretIdentificadorExpresion) {
        typedef struct { AbstractExpresion base; char* nombre; } Id;
        Id* id = (Id*) expr;
        if (id && id->nombre) {
            fprintf(f, "    adrp x%d, GV_%s@PAGE\n", target_reg, id->nombre);
            fprintf(f, "    add x%d, x%d, GV_%s@PAGEOFF\n", target_reg, target_reg, id->nombre);
            fprintf(f, "    ldr x%d, [x%d]\n", target_reg, target_reg);
            return;
        }
        fprintf(f, "    mov x%d, #0\n", target_reg);
        return;
    }

    if (expr->interpret == interpretExpresionLenguaje) {
        ExpresionLenguaje* el = (ExpresionLenguaje*) expr;
        if (!el) { fprintf(f, "    mov x%d, #0\n", target_reg); return; }
        // Handle basic integer arithmetic where operands are simple
        switch (el->tipo) {
            case SUMA:
            case RESTA:
            case MULTIPLICACION:
            case DIVISION: {
                // evaluate left into x9, right into x10
                emit_eval_expr(ctx, el->base.hijos ? el->base.hijos[0] : NULL, 9, f);
                emit_eval_expr(ctx, el->base.hijos && el->base.hijos[1] ? el->base.hijos[1] : NULL, 10, f);
                // If operands look like DOUBLE literals (quick heuristic), call FP helper and return double
                int left_is_double = 0, right_is_double = 0;
                if (el->base.hijos && el->base.hijos[0] && el->base.hijos[0]->interpret == interpretPrimitivoExpresion) {
                    typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr2;
                    Pr2* pl = (Pr2*) el->base.hijos[0]; if (pl && pl->tipo == DOUBLE) left_is_double = 1;
                }
                if (el->base.hijos && el->base.hijos[1] && el->base.hijos[1]->interpret == interpretPrimitivoExpresion) {
                    typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr3;
                    Pr3* pr = (Pr3*) el->base.hijos[1]; if (pr && pr->tipo == DOUBLE) right_is_double = 1;
                }
                if (left_is_double || right_is_double) {
                    // prepare FP args in d0/d1
                    fprintf(f, "    fmov d0, x9\n");
                    fprintf(f, "    fmov d1, x10\n");
                    const char* h = NULL;
                    if (el->tipo == SUMA) h = "add_double";
                    else if (el->tipo == RESTA) h = "sub_double";
                    else if (el->tipo == MULTIPLICACION) h = "mul_double";
                    else if (el->tipo == DIVISION) h = "div_double";
                    if (h) {
                        fprintf(f, "    bl %s\n", h);
                        // move result from d0 to x<target_reg>
                        fprintf(f, "    fmov x%d, d0\n", target_reg);
                        return;
                    }
                }
                // fallback to integer path
                if (el->tipo == SUMA) {
                    fprintf(f, "    add x%d, x9, x10\n", target_reg);
                    return;
                } else if (el->tipo == RESTA) {
                    fprintf(f, "    sub x%d, x9, x10\n", target_reg);
                    return;
                } else if (el->tipo == MULTIPLICACION) {
                    fprintf(f, "    mul x%d, x9, x10\n", target_reg);
                    return;
                } else if (el->tipo == DIVISION) {
                    // call div_helper(a,b) returning in x0
                    fprintf(f, "    mov x0, x9\n");
                    fprintf(f, "    mov x1, x10\n");
                    fprintf(f, "    bl div_helper\n");
                    fprintf(f, "    mov x%d, x0\n", target_reg);
                    return;
                }
                break;
            }
            default:
                break;
        }
    }

    // fallback
    fprintf(f, "    mov x%d, #0\n", target_reg);
}


// External emitters implemented in instrucciones/print.c
extern int emit_print_data(CodegenContext*, AbstractExpresion*);
extern void emit_print_text(CodegenContext*, AbstractExpresion*, int, char**, int*, int);
extern void emit_asignacion_text(CodegenContext*, AbstractExpresion*);
// Generador ARM emitters (scaffold)
extern void emit_division_text(CodegenContext*, AbstractExpresion*, int);

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
    int** emitted_init_ids_ptr, char*** emitted_init_values_ptr, int* emitted_types_ptr,
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
                    if (idexp) {
                        if (idexp->nombre) {
                            if (ctx && ctx->debug) fprintf(ctx->out, "# debug: collect_nodes found identifier name='%s'\n", idexp->nombre);
                            add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, idexp->nombre);
                        } else {
                            if (ctx && ctx->debug) fprintf(ctx->out, "# debug: collect_nodes found identifier with NULL nombre\n");
                        }
                    }
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
        if (an) {
            if (an->nombre) {
                if (ctx && ctx->debug) fprintf(ctx->out, "# debug: collect_nodes found asignacion nombre='%s'\n", an->nombre);
                add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, an->nombre);
            } else {
                if (ctx && ctx->debug) fprintf(ctx->out, "# debug: collect_nodes found asignacion with NULL nombre\n");
            }
        }
        // NOTE: Do NOT treat assignment RHS as .data initializers.
        // Assignments must only affect runtime state; initializers for
        // .data are derived from declarations (first-wins). Therefore
        // we don't record emitted_init_ids/values from assignment nodes here.
        // However: if assignment RHS contains a string literal, register it
        // so that STRLIT_N labels will be emitted in PASADA1 (avoid undefined
        // references from runtime code that uses STRLIT_N).
        if (n->numHijos>0) {
            AbstractExpresion* rhs = n->hijos[0];
            if (rhs && rhs->interpret == interpretPrimitivoExpresion) {
                typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr;
                Pr* p = (Pr*) rhs;
                if (p && p->valor && p->tipo == STRING) {
                    const char* raw = p->valor; size_t L = strlen(raw);
                    char* stripped = NULL;
                    if (L>=2 && raw[0]=='"' && raw[L-1]=='"') stripped = strndup(raw+1, L-2);
                    else stripped = strdup(raw);
                    codegen_register_strlit(NULL, stripped);
                    free(stripped);
                }
            }
        }
    }

    // Handle variable declarations with initializer (so we can emit GV_<name> initial values)
    extern Result interpretDeclaracionVariable(AbstractExpresion*, Context*);
    if (n->interpret == interpretDeclaracionVariable) {
        // cast to DeclaracionVariable-like struct to access nombre
        typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclaracionLocal;
        DeclaracionLocal* dv = (DeclaracionLocal*) n;
        if (dv && dv->nombre) {
            if (*emitted_count_ptr >= *emitted_cap_ptr) {
                *emitted_cap_ptr *= 2;
                *emitted_names_ptr = realloc(*emitted_names_ptr, sizeof(char*) * (*emitted_cap_ptr));
                *emitted_init_ids_ptr = realloc(*emitted_init_ids_ptr, sizeof(int) * (*emitted_cap_ptr));
                *emitted_init_values_ptr = realloc(*emitted_init_values_ptr, sizeof(char*) * (*emitted_cap_ptr));
                // emitted_types_ptr is an int* passed by value; we don't resize it here (allocated in caller)
            }
            add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, dv->nombre);
            // If there's an initializer child and it's a primitive, capture it
            if (n->numHijos>0 && n->hijos[0] && n->hijos[0]->interpret == interpretPrimitivoExpresion) {
                typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr;
                Pr* p = (Pr*) n->hijos[0];
                if (p && p->valor) {
                    // find index
                    for (int ii=0; ii<*emitted_count_ptr; ++ii) {
                        if ((*emitted_names_ptr)[ii] && strcmp((*emitted_names_ptr)[ii], dv->nombre) == 0) {
                                // first-wins: if an initializer was already recorded (e.g., earlier declaration), keep it
                                if ((*emitted_init_values_ptr)[ii]) { /* keep existing initializer */ }
                                else {
                                    if (p->tipo == STRING) {
                                        // strip quotes
                                        const char* raw = p->valor; size_t L = strlen(raw);
                                        if (L>=2 && raw[0]=='"' && raw[L-1]=='"') (*emitted_init_values_ptr)[ii] = strndup(raw+1, L-2);
                                        else (*emitted_init_values_ptr)[ii] = strdup(raw);
                                        emitted_types_ptr[ii] = STRING;
                                        // register string literal
                                        int id = codegen_register_strlit(NULL, (*emitted_init_values_ptr)[ii]);
                                        (*emitted_init_ids_ptr)[ii] = id;
                                    } else if (p->tipo == CHAR) {
                                        const char* rawc = p->valor; char tmp[4] = ""; if (rawc && strlen(rawc)>=1) { tmp[0]=rawc[0]; tmp[1]='\0'; }
                                        (*emitted_init_values_ptr)[ii] = strdup(tmp);
                                        emitted_types_ptr[ii] = CHAR;
                                    } else if (p->tipo == INT) {
                                        (*emitted_init_values_ptr)[ii] = strdup(p->valor);
                                        emitted_types_ptr[ii] = INT;
                                    } else if (p->tipo == DOUBLE) {
                                        (*emitted_init_values_ptr)[ii] = strdup(p->valor);
                                        emitted_types_ptr[ii] = DOUBLE;
                                    } else if (p->tipo == FLOAT) {
                                        // strip trailing 'f' or 'F' from float literal if present
                                        const char* rawf = p->valor;
                                        size_t Lf = rawf ? strlen(rawf) : 0;
                                        if (Lf > 0 && (rawf[Lf-1] == 'f' || rawf[Lf-1] == 'F')) {
                                            (*emitted_init_values_ptr)[ii] = strndup(rawf, Lf-1);
                                        } else {
                                            (*emitted_init_values_ptr)[ii] = strdup(rawf ? rawf : "0.0");
                                        }
                                        emitted_types_ptr[ii] = FLOAT;
                                    } else if (p->tipo == BOOLEAN) {
                                        // translate boolean textual into numeric 1/0 for .quad emission
                                        if (p->valor && strcmp(p->valor, "true") == 0) (*emitted_init_values_ptr)[ii] = strdup("1");
                                        else (*emitted_init_values_ptr)[ii] = strdup("0");
                                        emitted_types_ptr[ii] = BOOLEAN;
                                    } else {
                                        (*emitted_init_values_ptr)[ii] = strdup(p->valor);
                                        emitted_types_ptr[ii] = -1;
                                    }
                                }
                            break;
                        }
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < n->numHijos; ++i) collect_nodes(n->hijos[i], ctx, label_nodes_ptr, label_ids_ptr, label_map_size_ptr, label_map_capacity_ptr, assign_nodes_ptr, assign_size_ptr, assign_cap_ptr, emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, emitted_init_ids_ptr, emitted_init_values_ptr, emitted_types_ptr, f);
}

// Emit runtime nodes in program order by traversing AST and calling emit_print_text or emit_asignacion_text
static void emit_runtime_nodes(AbstractExpresion* n, CodegenContext* ctx, FILE* f, AbstractExpresion** label_nodes, int* label_ids, int label_map_size, char** emitted_names, int* emitted_types, int emitted_count) {
    if (!n) return;
    extern Result interpretPrintExpresion(AbstractExpresion*, Context*);
    extern Result interpretAsignacionExpresion(AbstractExpresion*, Context*);
    if (n->interpret == interpretPrintExpresion) {
        int id = -1;
        for (int i=0;i<label_map_size;++i) if (label_nodes[i]==n) { id = label_ids[i]; break; }
        if (ctx->debug) fprintf(f, "# debug: emit runtime print label %d\n", id);
        if (id>0) emit_print_text(ctx, n, id, emitted_names, emitted_types, emitted_count);
        return;
    }
    // Example: detect division expression and delegate to ARM emitter if present
    extern Result interpretExpresionLenguaje(AbstractExpresion*, Context*);
    if (n->interpret == interpretExpresionLenguaje) {
        // crude detection: check node kind via casting to ExpresionLenguaje and its tipo
        typedef struct { AbstractExpresion base; /* ... */ } Any;
        ExpresionLenguaje* el = (ExpresionLenguaje*) n;
        if (el && el->tipo == DIVISION) {
            // emit via ARM emitter (placeholder) — label id not needed here so pass -1
            emit_division_text(ctx, n, -1);
            return;
        }
    }
    if (n->interpret == interpretAsignacionExpresion) {
        if (ctx->debug) fprintf(f, "# debug: emit runtime asignacion\n");
        emit_asignacion_text(ctx, n);
        return;
    }
    // Handle native function calls (GEN_CALL_HELPER) via LlamadaFuncion node
    extern Result interpretLlamadaFuncion(AbstractExpresion*, Context*);
    if (n->interpret == interpretLlamadaFuncion) {
        // cast to LlamadaFuncion
        typedef struct { AbstractExpresion base; char* nombre; AbstractExpresion* args; } LlamadaFuncionLocal;
        LlamadaFuncionLocal* call = (LlamadaFuncionLocal*) n;
        if (call && call->nombre && codegen_is_native(call->nombre)) {
            const char* helper = codegen_get_native_helper(call->nombre);
            if (!helper) helper = call->nombre; // fallback
            if (ctx->debug) fprintf(f, "# debug: emit helper call %s\n", helper);
            // Prepare up to 8 arguments. Use x0..x7 for integer/pointer args and d0..d7 for doubles.
            if (call->args) {
                for (size_t ai = 0; ai < call->args->numHijos && ai < 8; ++ai) {
                    AbstractExpresion* a = call->args->hijos[ai];
                    extern Result interpretPrimitivoExpresion(AbstractExpresion*, Context*);
                    int akind = codegen_get_native_arg_kind(call->nombre, (int)ai);
                    if (a && a->interpret == interpretPrimitivoExpresion) {
                        typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr;
                        Pr* p = (Pr*) a;
                        if (p && p->valor) {
                            if (p->tipo == STRING) {
                                int id = codegen_register_strlit(NULL, p->valor);
                                fprintf(f, "    adrp x%zu, STRLIT_%d@PAGE\n", ai, id);
                                fprintf(f, "    add x%zu, x%zu, STRLIT_%d@PAGEOFF\n", ai, ai, id);
                            } else if (p->tipo == INT) {
                                fprintf(f, "    mov x%zu, #%s\n", ai, p->valor);
                            } else if (p->tipo == DOUBLE) {
                                int id = codegen_register_numlit(NULL, p->valor);
                                fprintf(f, "    adrp x%zu, NUMLIT_%d@PAGE\n", ai, id);
                                fprintf(f, "    ldr x%zu, [x%zu, :lo12:NUMLIT_%d]\n", ai, ai, id);
                                fprintf(f, "    fmov d%zu, x%zu\n", ai, ai);
                            } else {
                                fprintf(f, "    mov x%zu, #0\n", ai);
                            }
                        } else {
                            fprintf(f, "    mov x%zu, #0\n", ai);
                        }
                    } else if (a && a->interpret == interpretIdentificadorExpresion) {
                        typedef struct { AbstractExpresion base; char* nombre; } IdentificadorExpresionLocal;
                        IdentificadorExpresionLocal* id = (IdentificadorExpresionLocal*) a;
                        if (id && id->nombre) {
                            fprintf(f, "    adrp x%zu, GV_%s@PAGE\n", ai, id->nombre);
                            fprintf(f, "    add x%zu, x%zu, GV_%s@PAGEOFF\n", ai, ai, id->nombre);
                            fprintf(f, "    ldr x%zu, [x%zu]\n", ai, ai);
                            if (akind == ARG_KIND_DOUBLE) fprintf(f, "    fmov d%zu, x%zu\n", ai, ai);
                        } else {
                            fprintf(f, "    mov x%zu, #0\n", ai);
                        }
                    } else {
                        // Evaluate expression into x<ai> (bitpattern for doubles)
                        emit_eval_expr(ctx, a, (int)ai, f);
                        // If signature expects double, move x<ai> -> d<ai>
                        if (akind == ARG_KIND_DOUBLE) fprintf(f, "    fmov d%zu, x%zu\n", ai, ai);
                    }
                }
            }
            // Call helper
            fprintf(f, "    bl %s\n", helper);
            return;
        }
    }
    for (size_t i = 0; i < n->numHijos; ++i) emit_runtime_nodes(n->hijos[i], ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
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
    memset(label_nodes, 0, sizeof(AbstractExpresion*) * label_map_capacity);
    memset(label_ids, 0, sizeof(int) * label_map_capacity);

    int assign_cap = 16; int assign_size = 0;
    AbstractExpresion** assign_nodes = malloc(sizeof(AbstractExpresion*) * assign_cap);

    int emitted_cap = 16; int emitted_count = 0;
    char** emitted_names = malloc(sizeof(char*) * emitted_cap);
    int* emitted_init_ids = malloc(sizeof(int) * emitted_cap);
    char** emitted_init_values = malloc(sizeof(char*) * emitted_cap); // store textual initializer for GV_<name>_str emission
    int* emitted_types = malloc(sizeof(int) * emitted_cap);
    for (int i=0;i<emitted_cap;++i) { emitted_init_ids[i]=0; emitted_names[i]=NULL; emitted_init_values[i]=NULL; emitted_types[i] = -1; }

    // Collect nodes: this will call emit_print_data for prints (emits L labels) and register GV names
    collect_nodes(root, ctx, &label_nodes, &label_ids, &label_map_size, &label_map_capacity, &assign_nodes, &assign_size, &assign_cap, &emitted_names, &emitted_count, &emitted_cap, &emitted_init_ids, &emitted_init_values, emitted_types, f);

    // Emit STRLITs registered during collection
    codegen_emit_all_strlits(f);
    // Emit numeric literals (doubles)
    codegen_emit_all_numlits(f);

    // Emit GV_ symbols now, using emitted_types to choose directive
    for (int i = 0; i < emitted_count; ++i) {
        if (!emitted_names[i]) continue;
        int t = (emitted_types && i>=0) ? emitted_types[i] : -1;
        if (t == DOUBLE) {
            // if we have a textual initializer, use .double, else emit zero
            if (emitted_init_values[i]) fprintf(f, "GV_%s: .double %s\n\n", emitted_names[i], emitted_init_values[i]);
            else fprintf(f, "GV_%s: .double 0.0\n\n", emitted_names[i]);
        } else if (t == FLOAT) {
            if (emitted_init_values[i]) fprintf(f, "GV_%s: .float %s\n\n", emitted_names[i], emitted_init_values[i]);
            else fprintf(f, "GV_%s: .float 0.0f\n\n", emitted_names[i]);
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

    // PASADA 2: .text
    fprintf(f, "    .section .text\n");
    fprintf(f, "    .global _start\n");
    fprintf(f, "_start:\n");

    emit_runtime_nodes(root, ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);

    // exit
    fprintf(f, "    mov x0, #0\n");
    fprintf(f, "    mov x8, #93\n");
    fprintf(f, "    svc #0\n");

    // cleanup
    free(label_nodes); free(label_ids);
    free(assign_nodes);
    for (int i=0;i<emitted_count;++i) { if (emitted_names[i]) free(emitted_names[i]); if (emitted_init_values[i]) free(emitted_init_values[i]); }
    free(emitted_names);
    free(emitted_init_ids);
    free(emitted_init_values);
    free(emitted_types);
    fflush(f);
}

void liberar_codegen_context(CodegenContext* ctx) {
    if (!ctx) return;
    // NO cerramos ctx->out porque el llamador puede cerrarlo
    free(ctx);
}
