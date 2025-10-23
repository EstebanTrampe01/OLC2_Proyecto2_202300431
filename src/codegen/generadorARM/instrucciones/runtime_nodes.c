#include "runtime_nodes.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"
#include "ast/nodos/expresiones/terminales/identificadores.h"

#include "codegen/generadorARM/common.h"
#include "codegen/generadorARM/expresiones/emit_expr.h"
#include "codegen/native_impls.h"
#include "codegen/literals.h"

// Declaraciones externas usadas en detección/emisión
extern int emit_print_data(CodegenContext*, AbstractExpresion*);
extern void emit_print_text(CodegenContext*, AbstractExpresion*, int, char**, int*, int);
extern void emit_asignacion_text(CodegenContext*, AbstractExpresion*);
extern void emit_division_text(CodegenContext*, AbstractExpresion*, int);

extern Result interpretPrintExpresion(AbstractExpresion*, Context*);
extern Result interpretIdentificadorExpresion(AbstractExpresion*, Context*);
extern Result interpretAsignacionExpresion(AbstractExpresion*, Context*);
extern Result interpretDeclaracionVariable(AbstractExpresion*, Context*);
extern Result interpretExpresionLenguaje(AbstractExpresion*, Context*);
extern Result interpretLlamadaFuncion(AbstractExpresion*, Context*);
extern Result interpretPrimitivoExpresion(AbstractExpresion*, Context*);

void arm_collect_nodes(AbstractExpresion* n, CodegenContext* ctx,
    AbstractExpresion*** label_nodes_ptr, int** label_ids_ptr, int* label_map_size_ptr, int* label_map_capacity_ptr,
    AbstractExpresion*** assign_nodes_ptr, int* assign_size_ptr, int* assign_cap_ptr,
    char*** emitted_names_ptr, int* emitted_count_ptr, int* emitted_cap_ptr,
    int** emitted_init_ids_ptr, char*** emitted_init_values_ptr, int* emitted_types_ptr,
    FILE* f) {

    if (!n) return;

    if (n->interpret == interpretPrintExpresion) {
        if (*label_map_size_ptr >= *label_map_capacity_ptr) {
            *label_map_capacity_ptr *= 2;
            *label_nodes_ptr = (AbstractExpresion**)realloc(*label_nodes_ptr, sizeof(AbstractExpresion*) * (*label_map_capacity_ptr));
            *label_ids_ptr = (int*)realloc(*label_ids_ptr, sizeof(int) * (*label_map_capacity_ptr));
        }
        int id = emit_print_data(ctx, n);
        (*label_nodes_ptr)[*label_map_size_ptr] = n;
        (*label_ids_ptr)[*label_map_size_ptr] = id;
        (*label_map_size_ptr)++;
        if (n->numHijos>0 && n->hijos[0]) {
            for (size_t i=0;i<n->hijos[0]->numHijos;++i) {
                AbstractExpresion* e = n->hijos[0]->hijos[i];
                if (e && e->interpret == interpretIdentificadorExpresion) {
                    typedef struct { AbstractExpresion base; char* nombre; } IdentificadorExpresion;
                    IdentificadorExpresion* idexp = (IdentificadorExpresion*) e;
                    if (idexp && idexp->nombre) arm_add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, idexp->nombre);
                }
            }
        }
    }

    if (n->interpret == interpretAsignacionExpresion) {
        if (*assign_size_ptr >= *assign_cap_ptr) {
            *assign_cap_ptr *= 2;
            *assign_nodes_ptr = (AbstractExpresion**)realloc(*assign_nodes_ptr, sizeof(AbstractExpresion*) * (*assign_cap_ptr));
        }
        (*assign_nodes_ptr)[*assign_size_ptr] = n; (*assign_size_ptr)++;
        AsignacionExpresion* an = (AsignacionExpresion*) n;
        if (an && an->nombre) arm_add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, an->nombre);
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

    if (n->interpret == interpretDeclaracionVariable) {
        typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclaracionLocal;
        DeclaracionLocal* dv = (DeclaracionLocal*) n;
        if (dv && dv->nombre) {
            if (*emitted_count_ptr >= *emitted_cap_ptr) {
                *emitted_cap_ptr *= 2;
                *emitted_names_ptr = (char**)realloc(*emitted_names_ptr, sizeof(char*) * (*emitted_cap_ptr));
                *emitted_init_ids_ptr = (int*)realloc(*emitted_init_ids_ptr, sizeof(int) * (*emitted_cap_ptr));
                *emitted_init_values_ptr = (char**)realloc(*emitted_init_values_ptr, sizeof(char*) * (*emitted_cap_ptr));
            }
            arm_add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, dv->nombre);
            if (n->numHijos>0 && n->hijos[0] && n->hijos[0]->interpret == interpretPrimitivoExpresion) {
                typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr;
                Pr* p = (Pr*) n->hijos[0];
                if (p && p->valor) {
                    for (int ii=0; ii<*emitted_count_ptr; ++ii) {
                        if ((*emitted_names_ptr)[ii] && strcmp((*emitted_names_ptr)[ii], dv->nombre) == 0) {
                            if (!(*emitted_init_values_ptr)[ii]) {
                                if (p->tipo == STRING) {
                                    const char* raw = p->valor; size_t L = strlen(raw);
                                    if (L>=2 && raw[0]=='"' && raw[L-1]=='"') (*emitted_init_values_ptr)[ii] = strndup(raw+1, L-2);
                                    else (*emitted_init_values_ptr)[ii] = strdup(raw);
                                    emitted_types_ptr[ii] = STRING;
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
                                    const char* rawf = p->valor; size_t Lf = rawf ? strlen(rawf) : 0;
                                    if (Lf > 0 && (rawf[Lf-1] == 'f' || rawf[Lf-1] == 'F')) {
                                        (*emitted_init_values_ptr)[ii] = strndup(rawf, Lf-1);
                                    } else {
                                        (*emitted_init_values_ptr)[ii] = strdup(rawf ? rawf : "0.0");
                                    }
                                    emitted_types_ptr[ii] = FLOAT;
                                } else if (p->tipo == BOOLEAN) {
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

    for (size_t i = 0; i < n->numHijos; ++i) {
        arm_collect_nodes(n->hijos[i], ctx, label_nodes_ptr, label_ids_ptr, label_map_size_ptr, label_map_capacity_ptr,
            assign_nodes_ptr, assign_size_ptr, assign_cap_ptr,
            emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr,
            emitted_init_ids_ptr, emitted_init_values_ptr, emitted_types_ptr, f);
    }
}

void arm_emit_runtime_nodes(AbstractExpresion* n, CodegenContext* ctx, FILE* f,
    AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
    char** emitted_names, int* emitted_types, int emitted_count) {
    if (!n) return;
    if (n->interpret == interpretPrintExpresion) {
        int id = -1;
        for (int i=0;i<label_map_size;++i) if (label_nodes[i]==n) { id = label_ids[i]; break; }
        if (ctx->debug) fprintf(f, "# debug: emit runtime print label %d\n", id);
        if (id>0) emit_print_text(ctx, n, id, emitted_names, emitted_types, emitted_count);
        return;
    }
    if (n->interpret == interpretExpresionLenguaje) {
        ExpresionLenguaje* el = (ExpresionLenguaje*) n;
        if (el && el->tipo == DIVISION) {
            emit_division_text(ctx, n, -1);
            return;
        }
    }
    if (n->interpret == interpretAsignacionExpresion) {
        if (ctx->debug) fprintf(f, "# debug: emit runtime asignacion\n");
        emit_asignacion_text(ctx, n);
        return;
    }
    if (n->interpret == interpretLlamadaFuncion) {
        typedef struct { AbstractExpresion base; char* nombre; AbstractExpresion* args; } LlamadaFuncionLocal;
        LlamadaFuncionLocal* call = (LlamadaFuncionLocal*) n;
        if (call && call->nombre && codegen_is_native(call->nombre)) {
            const char* helper = codegen_get_native_helper(call->nombre);
            if (!helper) helper = call->nombre;
            if (ctx->debug) fprintf(f, "# debug: emit helper call %s\n", helper);
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
                                fprintf(f, "    adrp x%zu, STRLIT_%d\n", ai, id);
                                fprintf(f, "    add x%zu, x%zu, :lo12:STRLIT_%d\n", ai, ai, id);
                            } else if (p->tipo == INT) {
                                fprintf(f, "    mov x%zu, #%s\n", ai, p->valor);
                            } else if (p->tipo == DOUBLE) {
                                int id = codegen_register_numlit(NULL, p->valor);
                                fprintf(f, "    adrp x%zu, NUMLIT_%d\n", ai, id);
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
                            fprintf(f, "    adrp x%zu, GV_%s\n", ai, id->nombre);
                            fprintf(f, "    add x%zu, x%zu, :lo12:GV_%s\n", ai, ai, id->nombre);
                            fprintf(f, "    ldr x%zu, [x%zu]\n", ai, ai);
                            if (akind == ARG_KIND_DOUBLE) fprintf(f, "    fmov d%zu, x%zu\n", ai, ai);
                        } else {
                            fprintf(f, "    mov x%zu, #0\n", ai);
                        }
                    } else {
                        arm_emit_eval_expr(ctx, a, (int)ai, f);
                        if (akind == ARG_KIND_DOUBLE) fprintf(f, "    fmov d%zu, x%zu\n", ai, ai);
                    }
                }
            }
            fprintf(f, "    bl %s\n", helper);
            return;
        }
    }
    for (size_t i = 0; i < n->numHijos; ++i) arm_emit_runtime_nodes(n->hijos[i], ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
}


