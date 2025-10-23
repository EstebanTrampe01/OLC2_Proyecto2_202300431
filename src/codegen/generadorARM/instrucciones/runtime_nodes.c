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
extern Result interpretInstrucciones(AbstractExpresion*, Context*);
extern Result interpretBloqueExpresion(AbstractExpresion*, Context*);
extern Result interpretIfExpresion(AbstractExpresion*, Context*);
extern Result interpretCastExpresion(AbstractExpresion*, Context*);

void arm_collect_nodes(AbstractExpresion* n, CodegenContext* ctx,
    AbstractExpresion*** label_nodes_ptr, int** label_ids_ptr, int* label_map_size_ptr, int* label_map_capacity_ptr,
    AbstractExpresion*** assign_nodes_ptr, int* assign_size_ptr, int* assign_cap_ptr,
    char*** emitted_names_ptr, int* emitted_count_ptr, int* emitted_cap_ptr,
    int** emitted_init_ids_ptr, char*** emitted_init_values_ptr, int* emitted_types_ptr,
    FILE* f) {

    // Debug: imprimir información del nodo actual
    if (ctx && ctx->debug) {
        fprintf(f, "# DEBUG arm_collect_nodes: procesando nodo con %zu hijos\n", n ? n->numHijos : 0);
        if (n && n->interpret) {
            fprintf(f, "# DEBUG: función interpret = %p\n", n->interpret);
        }
    }

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
                    if (idexp && idexp->nombre) {
                        arm_add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, idexp->nombre);
                        // Inicializar los arrays correspondientes para la nueva variable (solo si no tiene inicialización)
                        if (*emitted_count_ptr > 0) {
                            int new_index = *emitted_count_ptr - 1;
                            if (new_index < *emitted_cap_ptr) {
                                // Solo inicializar si no se ha establecido ya (evitar sobrescribir tipos de variables con inicialización)
                                if ((*emitted_init_values_ptr)[new_index] == NULL && emitted_types_ptr[new_index] == -1) {
                                    (*emitted_init_values_ptr)[new_index] = NULL;
                                    emitted_types_ptr[new_index] = -1;
                                    (*emitted_init_ids_ptr)[new_index] = 0;
                                }
                            }
                        }
                    }
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
        if (an && an->nombre) {
            arm_add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, an->nombre);
            // Inicializar los arrays correspondientes para la nueva variable (solo si no tiene tipo establecido)
            if (*emitted_count_ptr > 0) {
                int new_index = *emitted_count_ptr - 1;
                if (new_index < *emitted_cap_ptr) {
                    (*emitted_init_values_ptr)[new_index] = NULL;
                    if (emitted_types_ptr[new_index] == -1) {  // Solo establecer -1 si no se ha establecido ya
                        emitted_types_ptr[new_index] = -1;
                    }
                    (*emitted_init_ids_ptr)[new_index] = 0;
                }
            }
        }
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
                } else if (p && p->valor && (p->tipo == FLOAT || p->tipo == DOUBLE)) {
                    // Registrar literales numéricos durante asignaciones
                    codegen_register_numlit(NULL, p->valor);
                }
            }
        }
    }

    if (n->interpret == interpretDeclaracionVariable) {
        typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclaracionLocal;
        DeclaracionLocal* dv = (DeclaracionLocal*) n;
        if (dv && dv->nombre) {
            // Debug: información de la declaración de variable
            if (ctx && ctx->debug) {
                fprintf(f, "# DEBUG: procesando declaración de variable '%s' tipo=%d\n", dv->nombre, dv->tipo);
            }
            printf("DEBUG: PROCESANDO declaración de variable '%s' tipo=%d\n", dv->nombre, dv->tipo);
            
            if (*emitted_count_ptr >= *emitted_cap_ptr) {
                *emitted_cap_ptr *= 2;
                *emitted_names_ptr = (char**)realloc(*emitted_names_ptr, sizeof(char*) * (*emitted_cap_ptr));
                *emitted_init_ids_ptr = (int*)realloc(*emitted_init_ids_ptr, sizeof(int) * (*emitted_cap_ptr));
                *emitted_init_values_ptr = (char**)realloc(*emitted_init_values_ptr, sizeof(char*) * (*emitted_cap_ptr));
            }
            arm_add_emitted_name(emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, dv->nombre);
            
            // Inicializar los arrays correspondientes para la nueva variable
            if (*emitted_count_ptr > 0) {
                int new_index = *emitted_count_ptr - 1;
                if (new_index < *emitted_cap_ptr) {
                    (*emitted_init_values_ptr)[new_index] = NULL;
                    emitted_types_ptr[new_index] = -1;
                    (*emitted_init_ids_ptr)[new_index] = 0;
                }
            }
            
            if (n->numHijos>0 && n->hijos[0] && n->hijos[0]->interpret == interpretPrimitivoExpresion) {
                typedef struct { AbstractExpresion base; int tipo; char* valor; } Pr;
                Pr* p = (Pr*) n->hijos[0];
                if (ctx && ctx->debug) {
                    fprintf(f, "# DEBUG: procesando primitivo tipo=%d valor='%s'\n", p ? p->tipo : -1, p && p->valor ? p->valor : "NULL");
                }
                if (p && p->valor && emitted_names_ptr && emitted_count_ptr && *emitted_count_ptr > 0) {
                    for (int ii=0; ii<*emitted_count_ptr; ++ii) {
                        if ((*emitted_names_ptr)[ii] && strcmp((*emitted_names_ptr)[ii], dv->nombre) == 0) {
                            // Verificar si ya se asignó un valor para evitar sobrescritura
                            if (!(*emitted_init_values_ptr)[ii]) {
                                if (ctx && ctx->debug) {
                                    fprintf(f, "# DEBUG: asignando valor inicial para '%s' en índice %d\n", dv->nombre, ii);
                                }
                                if (p->tipo == STRING) {
                                    const char* raw = p->valor; size_t L = strlen(raw);
                                    if (L>=2 && raw[0]=='"' && raw[L-1]=='"') {
                                        (*emitted_init_values_ptr)[ii] = strndup(raw+1, L-2);
                                        printf("DEBUG: asignando STRING strndup para '%s' -> %p\n", dv->nombre, (*emitted_init_values_ptr)[ii]);
                                    } else {
                                        (*emitted_init_values_ptr)[ii] = strdup(raw);
                                        printf("DEBUG: asignando STRING strdup para '%s' -> %p\n", dv->nombre, (*emitted_init_values_ptr)[ii]);
                                    }
                                    emitted_types_ptr[ii] = STRING;
                                    int id = codegen_register_strlit(NULL, (*emitted_init_values_ptr)[ii]);
                                    (*emitted_init_ids_ptr)[ii] = id;
                                } else if (p->tipo == CHAR) {
                                    const char* rawc = p->valor; char tmp[4] = ""; if (rawc && strlen(rawc)>=1) { tmp[0]=rawc[0]; tmp[1]='\0'; }
                                    (*emitted_init_values_ptr)[ii] = strdup(tmp);
                                    printf("DEBUG: asignando CHAR strdup para '%s' -> %p\n", dv->nombre, (*emitted_init_values_ptr)[ii]);
                                    emitted_types_ptr[ii] = CHAR;
                                } else if (p->tipo == INT) {
                                    (*emitted_init_values_ptr)[ii] = strdup(p->valor);
                                    printf("DEBUG: asignando INT strdup para '%s' -> %p\n", dv->nombre, (*emitted_init_values_ptr)[ii]);
                                    emitted_types_ptr[ii] = INT;
                                } else if (p->tipo == DOUBLE) {
                                    (*emitted_init_values_ptr)[ii] = strdup(p->valor);
                                    printf("DEBUG: asignando DOUBLE strdup para '%s' -> %p\n", dv->nombre, (*emitted_init_values_ptr)[ii]);
                                    codegen_register_numlit(NULL, p->valor);  // Registrar literal numérico
                                    emitted_types_ptr[ii] = dv->tipo;  // Usar tipo de la variable declarada
                                } else if (p->tipo == FLOAT) {
                                    const char* rawf = p->valor; size_t Lf = rawf ? strlen(rawf) : 0;
                                    if (Lf > 0 && (rawf[Lf-1] == 'f' || rawf[Lf-1] == 'F')) {
                                        (*emitted_init_values_ptr)[ii] = strndup(rawf, Lf-1);
                                        printf("DEBUG: asignando FLOAT strndup para '%s' -> %p\n", dv->nombre, (*emitted_init_values_ptr)[ii]);
                                    } else {
                                        (*emitted_init_values_ptr)[ii] = strdup(rawf ? rawf : "0.0");
                                        printf("DEBUG: asignando FLOAT strdup para '%s' -> %p\n", dv->nombre, (*emitted_init_values_ptr)[ii]);
                                    }
                                    codegen_register_numlit(NULL, (*emitted_init_values_ptr)[ii]);  // Registrar literal numérico
                                    emitted_types_ptr[ii] = dv->tipo;  // Usar tipo de la variable declarada
                                    printf("DEBUG: estableciendo tipo %d para variable '%s' en índice %d\n", dv->tipo, dv->nombre, ii);
                                    printf("DEBUG: emitted_types_ptr[%d] = %d\n", ii, emitted_types_ptr[ii]);
                                } else if (p->tipo == BOOLEAN) {
                                    if (p->valor && strcmp(p->valor, "true") == 0) (*emitted_init_values_ptr)[ii] = strdup("1");
                                    else (*emitted_init_values_ptr)[ii] = strdup("0");
                                    emitted_types_ptr[ii] = BOOLEAN;
                                } else {
                                    (*emitted_init_values_ptr)[ii] = strdup(p->valor);
                                    emitted_types_ptr[ii] = dv->tipo;  // Usar el tipo de la variable declarada
                                }
                            }
                            break;
                        } else {
                            if (ctx && ctx->debug) {
                                fprintf(f, "# DEBUG: variable '%s' ya tiene valor asignado, saltando\n", dv->nombre);
                            }
                        }
                    }
                }
            }
            
            // Registrar el tipo de la variable declarada para variables sin primitivo (casting, etc.)
            if (ctx && ctx->debug) {
                fprintf(f, "# DEBUG: registrando tipo para variable '%s', emitted_count=%d\n", dv->nombre, *emitted_count_ptr);
            }
            if (emitted_types_ptr && emitted_names_ptr && emitted_count_ptr && *emitted_count_ptr > 0) {
                for (int ii=0; ii<*emitted_count_ptr; ++ii) {
                    if ((*emitted_names_ptr)[ii] && strcmp((*emitted_names_ptr)[ii], dv->nombre) == 0) {
                        if (ctx && ctx->debug) {
                            fprintf(f, "# DEBUG: variable '%s' encontrada en índice %d, tipo actual=%d\n", dv->nombre, ii, emitted_types_ptr[ii]);
                        }
                        if (emitted_types_ptr[ii] == 0 || emitted_types_ptr[ii] == -1) {  // Solo si no se ha registrado ya
                            emitted_types_ptr[ii] = dv->tipo;  // Usar el tipo de la variable declarada
                            if (ctx && ctx->debug) {
                                fprintf(f, "# DEBUG: tipo registrado como %d para variable '%s'\n", dv->tipo, dv->nombre);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    
    // Manejar expresiones complejas para registrar literales numéricos
    if (n->interpret == interpretExpresionLenguaje) {
        ExpresionLenguaje* el = (ExpresionLenguaje*) n;
        printf("DEBUG: arm_collect_nodes procesando expresión lenguaje tipo=%d\n", el ? el->tipo : -1);
        
        // Procesar recursivamente los hijos para registrar literales
        for (size_t i = 0; i < n->numHijos; ++i) {
            arm_collect_nodes(n->hijos[i], ctx, label_nodes_ptr, label_ids_ptr, label_map_size_ptr, label_map_capacity_ptr, assign_nodes_ptr, assign_size_ptr, assign_cap_ptr, emitted_names_ptr, emitted_count_ptr, emitted_cap_ptr, emitted_init_ids_ptr, emitted_init_values_ptr, emitted_types_ptr, f);
        }
        return;
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
    
    // Debug básico para ver qué nodos se están procesando
    if (ctx->debug) fprintf(f, "# debug: procesando nodo con %zu hijos\n", n->numHijos);
    
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
        // Manejar otras operaciones aritméticas usando arm_emit_eval_expr
        extern void arm_emit_eval_expr(CodegenContext*, AbstractExpresion*, int, FILE*);
        if (ctx->debug) fprintf(f, "# debug: emit runtime expresión lenguaje tipo=%d\n", el ? el->tipo : -1);
        // Las expresiones complejas se evalúan pero no se almacenan aquí
        // Solo se procesan recursivamente los hijos
        for (size_t i = 0; i < n->numHijos; ++i) {
            arm_emit_runtime_nodes(n->hijos[i], ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
        }
        return;
    }
    if (n->interpret == interpretAsignacionExpresion) {
        if (ctx->debug) fprintf(f, "# debug: emit runtime asignacion\n");
        emit_asignacion_text(ctx, n);
        return;
    }
    if (n->interpret == interpretDeclaracionVariable) {
        if (ctx->debug) fprintf(f, "# debug: emit runtime declaracion variable\n");
        
        // Manejar declaraciones de variables con inicialización
        if (n->numHijos > 0) {
            AbstractExpresion* initExpr = n->hijos[0];
            
            // Si la inicialización es una expresión compleja
            if (initExpr->interpret == interpretExpresionLenguaje) {
                typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclVar;
                DeclVar* decl = (DeclVar*) n;
                
                fprintf(f, "    // Declaración con expresión compleja: %s = expresión\n", decl->nombre);
                fprintf(f, "    adrp x11, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                fprintf(f, "    add x11, x11, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                
                // Evaluar la expresión compleja usando arm_emit_eval_expr
                extern void arm_emit_eval_expr(CodegenContext*, AbstractExpresion*, int, FILE*);
                arm_emit_eval_expr(ctx, initExpr, 2, f);  // Evaluar en registro x2
                
                fprintf(f, "    str x2, [x11]\n\n");  // Almacenar resultado en la variable destino
                return;
            }
            
            // Si la inicialización es un identificador (casting automático)
            if (initExpr->interpret == interpretIdentificadorExpresion) {
                typedef struct { AbstractExpresion base; char* nombre; } Id;
                typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclVar;
                Id* id = (Id*) initExpr;
                DeclVar* decl = (DeclVar*) n;
                
                // Detectar el tipo de la variable origen
                int tipoOrigen = INT; // Default
                if (emitted_names && emitted_types && emitted_count > 0) {
                    for (int ii = 0; ii < emitted_count; ++ii) {
                        if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) {
                            tipoOrigen = emitted_types[ii];
                            break;
                        }
                    }
                }
                
                // Casting automático de char a int
                if (decl->tipo == INT) {
                    fprintf(f, "    // Declaración con casting automático: %s = %s (char->int)\n", 
                           decl->nombre, id->nombre);
                    fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                    fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                    fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                    fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                    fprintf(f, "    ldrb w2, [x2]\n");  // Cargar byte (char) de la variable origen
                    fprintf(f, "    sxtb x2, w2\n");  // Extender signo de byte a entero
                    fprintf(f, "    str x2, [x1]\n\n");  // Almacenar entero en la variable destino
                    return;
                }
                
                // Casting automático de int a float
                if (decl->tipo == FLOAT) {
                    fprintf(f, "    // Declaración con casting automático: %s = %s (int->float)\n", 
                           decl->nombre, id->nombre);
                    fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                    fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                    fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                    fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                    fprintf(f, "    ldr x2, [x2]\n");  // Cargar entero de la variable origen
                    fprintf(f, "    scvtf s2, x2\n");  // Convertir entero a float
                    fprintf(f, "    str s2, [x1]\n\n");  // Almacenar float en la variable destino
                    return;
                }
                
                // Casting automático de float a double
                if (decl->tipo == DOUBLE && tipoOrigen == FLOAT) {
                    fprintf(f, "    // Declaración con casting automático: %s = %s (float->double)\n", 
                           decl->nombre, id->nombre);
                    fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                    fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                    fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                    fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                    fprintf(f, "    ldr s2, [x2]\n");  // Cargar float de la variable origen
                    fprintf(f, "    fcvt d2, s2\n");  // Convertir float a double
                    fprintf(f, "    str d2, [x1]\n\n");  // Almacenar double en la variable destino
                    return;
                }
                
                // Casting automático de int a double
                if (decl->tipo == DOUBLE && tipoOrigen == INT) {
                    fprintf(f, "    // Declaración con casting automático: %s = %s (int->double)\n", 
                           decl->nombre, id->nombre);
                    fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                    fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                    fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                    fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                    fprintf(f, "    ldr x2, [x2]\n");  // Cargar entero de la variable origen
                    fprintf(f, "    scvtf d2, x2\n");  // Convertir entero a double
                    fprintf(f, "    str d2, [x1]\n\n");  // Almacenar double en la variable destino
                    return;
                }
                
                // Casting automático de float a double
                if (decl->tipo == DOUBLE && tipoOrigen == FLOAT) {
                    fprintf(f, "    // Declaración con casting automático: %s = %s (float->double)\n", 
                           decl->nombre, id->nombre);
                    fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                    fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                    fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                    fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                    fprintf(f, "    ldr s2, [x2]\n");  // Cargar float de la variable origen
                    fprintf(f, "    fcvt d2, s2\n");  // Convertir float a double
                    fprintf(f, "    str d2, [x1]\n\n");  // Almacenar double en la variable destino
                    return;
                }
            }
            
            // Si la inicialización es un casting explícito
            if (initExpr->interpret == interpretCastExpresion) {
                typedef struct { AbstractExpresion base; int tipoDestino; } CastExpresion;
                CastExpresion* cast = (CastExpresion*) initExpr;
                
                if (cast && cast->base.numHijos > 0) {
                    AbstractExpresion* innerExpr = cast->base.hijos[0];
                    
                    // Si el casting es a float/double (con detección de tipo origen)
                    if (innerExpr->interpret == interpretIdentificadorExpresion && 
                        (cast->tipoDestino == FLOAT || cast->tipoDestino == DOUBLE)) {
                        
                        typedef struct { AbstractExpresion base; char* nombre; } Id;
                        typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclVar;
                        Id* id = (Id*) innerExpr;
                        DeclVar* decl = (DeclVar*) n;
                        
                        // Detectar el tipo de la variable origen
                        int tipoOrigen = INT; // Default
                        if (emitted_names && emitted_types && emitted_count > 0) {
                            for (int ii = 0; ii < emitted_count; ++ii) {
                                if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) {
                                    tipoOrigen = emitted_types[ii];
                                    break;
                                }
                            }
                        }
                        
                        fprintf(f, "    // Declaración con casting: %s = (%s) %s (origen tipo=%d)\n", 
                               decl->nombre, 
                               cast->tipoDestino == FLOAT ? "float" : "double", 
                               id->nombre, tipoOrigen);
                        fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                        fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                        fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                        fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                        
                        if (cast->tipoDestino == FLOAT) {
                            if (tipoOrigen == DOUBLE) {
                                fprintf(f, "    ldr d2, [x2]\n");  // Cargar double de la variable origen
                                fprintf(f, "    fcvt s2, d2\n");  // Convertir double a float
                            } else {
                                fprintf(f, "    ldr x2, [x2]\n");  // Cargar entero de la variable origen
                                fprintf(f, "    scvtf s2, x2\n");  // Convertir entero a float
                            }
                            fprintf(f, "    str s2, [x1]\n\n");  // Almacenar float en la variable destino
                        } else {
                            if (tipoOrigen == FLOAT) {
                                fprintf(f, "    ldr s2, [x2]\n");  // Cargar float de la variable origen
                                fprintf(f, "    fcvt d2, s2\n");  // Convertir float a double
                            } else {
                                fprintf(f, "    ldr x2, [x2]\n");  // Cargar entero de la variable origen
                                fprintf(f, "    scvtf d2, x2\n");  // Convertir entero a double
                            }
                            fprintf(f, "    str d2, [x1]\n\n");  // Almacenar double en la variable destino
                        }
                        return;
                    }
                    
                    // Si el casting es a int (con detección de tipo origen)
                    if (innerExpr->interpret == interpretIdentificadorExpresion && 
                        cast->tipoDestino == INT) {
                        
                        typedef struct { AbstractExpresion base; char* nombre; } Id;
                        typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclVar;
                        Id* id = (Id*) innerExpr;
                        DeclVar* decl = (DeclVar*) n;
                        
                        // Detectar el tipo de la variable origen
                        int tipoOrigen = INT; // Default
                        if (emitted_names && emitted_types && emitted_count > 0) {
                            for (int ii = 0; ii < emitted_count; ++ii) {
                                if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) {
                                    tipoOrigen = emitted_types[ii];
                                    break;
                                }
                            }
                        }
                        
                        fprintf(f, "    // Declaración con casting: %s = (int) %s (origen tipo=%d)\n", 
                               decl->nombre, id->nombre, tipoOrigen);
                        fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                        fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                        fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                        fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                        
                        if (tipoOrigen == FLOAT) {
                            fprintf(f, "    ldr s2, [x2]\n");  // Cargar float de la variable origen
                            fprintf(f, "    fcvtzs x2, s2\n");  // Convertir float a entero con signo
                        } else if (tipoOrigen == DOUBLE) {
                            fprintf(f, "    ldr d2, [x2]\n");  // Cargar double de la variable origen
                            fprintf(f, "    fcvtzs x2, d2\n");  // Convertir double a entero con signo
                        } else if (tipoOrigen == CHAR) {
                            fprintf(f, "    ldrb w2, [x2]\n");  // Cargar byte (char) de la variable origen
                            fprintf(f, "    sxtb x2, w2\n");  // Extender signo de byte a entero
                        } else {
                            fprintf(f, "    ldr x2, [x2]\n");  // Cargar entero de la variable origen
                        }
                        fprintf(f, "    str x2, [x1]\n\n");  // Almacenar entero en la variable destino
                        return;
                    }
                    
                    // Si el casting es de double a float
                    if (innerExpr->interpret == interpretIdentificadorExpresion && 
                        cast->tipoDestino == FLOAT) {
                        
                        typedef struct { AbstractExpresion base; char* nombre; } Id;
                        typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclVar;
                        Id* id = (Id*) innerExpr;
                        DeclVar* decl = (DeclVar*) n;
                        
                        // Detectar el tipo de la variable origen
                        int tipoOrigen = INT; // Default
                        if (emitted_names && emitted_types && emitted_count > 0) {
                            for (int ii = 0; ii < emitted_count; ++ii) {
                                if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) {
                                    tipoOrigen = emitted_types[ii];
                                    break;
                                }
                            }
                        }
                        
                        fprintf(f, "    // Declaración con casting: %s = (float) %s (origen tipo=%d)\n", 
                               decl->nombre, id->nombre, tipoOrigen);
                        fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                        fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                        fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                        fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                        
                        if (tipoOrigen == DOUBLE) {
                            fprintf(f, "    ldr d2, [x2]\n");  // Cargar double de la variable origen
                            fprintf(f, "    fcvt s2, d2\n");  // Convertir double a float
                        } else {
                            fprintf(f, "    ldr x2, [x2]\n");  // Cargar entero de la variable origen
                            fprintf(f, "    scvtf s2, x2\n");  // Convertir entero a float
                        }
                        fprintf(f, "    str s2, [x1]\n\n");  // Almacenar float en la variable destino
                        return;
                    }
                    
                    // Si el casting es de float a int
                    if (innerExpr->interpret == interpretIdentificadorExpresion && 
                        cast->tipoDestino == INT) {
                        
                        typedef struct { AbstractExpresion base; char* nombre; } Id;
                        typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclVar;
                        Id* id = (Id*) innerExpr;
                        DeclVar* decl = (DeclVar*) n;
                        
                        // Detectar el tipo de la variable origen
                        int tipoOrigen = INT; // Default
                        if (emitted_names && emitted_types && emitted_count > 0) {
                            for (int ii = 0; ii < emitted_count; ++ii) {
                                if (emitted_names[ii] && strcmp(emitted_names[ii], id->nombre) == 0) {
                                    tipoOrigen = emitted_types[ii];
                                    break;
                                }
                            }
                        }
                        
                        fprintf(f, "    // Declaración con casting: %s = (int) %s (origen tipo=%d)\n", 
                               decl->nombre, id->nombre, tipoOrigen);
                        fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                        fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                        fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                        fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                        
                        if (tipoOrigen == FLOAT) {
                            fprintf(f, "    ldr s2, [x2]\n");  // Cargar float de la variable origen
                            fprintf(f, "    fcvtzs x2, s2\n");  // Convertir float a entero con signo
                        } else if (tipoOrigen == DOUBLE) {
                            fprintf(f, "    ldr d2, [x2]\n");  // Cargar double de la variable origen
                            fprintf(f, "    fcvtzs x2, d2\n");  // Convertir double a entero con signo
                        } else {
                            fprintf(f, "    ldr x2, [x2]\n");  // Cargar entero de la variable origen
                        }
                        fprintf(f, "    str x2, [x1]\n\n");  // Almacenar entero en la variable destino
                        return;
                    }
                    
                    // Si el casting es de int a char
                    if (innerExpr->interpret == interpretIdentificadorExpresion && 
                        cast->tipoDestino == CHAR) {
                        
                        typedef struct { AbstractExpresion base; char* nombre; } Id;
                        typedef struct { AbstractExpresion base; char* nombre; int tipo; } DeclVar;
                        Id* id = (Id*) innerExpr;
                        DeclVar* decl = (DeclVar*) n;
                        
                        fprintf(f, "    // Declaración con casting: %s = (char) %s\n", 
                               decl->nombre, id->nombre);
                        fprintf(f, "    adrp x1, GV_%s\n", decl->nombre);  // Cargar dirección alta de la variable destino
                        fprintf(f, "    add x1, x1, :lo12:GV_%s\n", decl->nombre);  // Completar dirección de la variable destino
                        fprintf(f, "    adrp x2, GV_%s\n", id->nombre);  // Cargar dirección alta de la variable origen
                        fprintf(f, "    add x2, x2, :lo12:GV_%s\n", id->nombre);  // Completar dirección de la variable origen
                        fprintf(f, "    ldr x2, [x2]\n");  // Cargar entero de la variable origen
                        fprintf(f, "    strb w2, [x1]\n\n");  // Almacenar byte (char) en la variable destino
                        return;
                    }
                }
            }
        }
        
        // Las declaraciones de variables ya fueron procesadas en arm_collect_nodes
        // Solo necesitamos procesar recursivamente los hijos si los hay
        for (size_t i = 0; i < n->numHijos; ++i) {
            arm_emit_runtime_nodes(n->hijos[i], ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
        }
        return;
    }
    if (n->interpret == interpretInstrucciones) {
        if (ctx->debug) fprintf(f, "# debug: emit runtime lista instrucciones\n");
        // Procesar recursivamente todas las instrucciones
        for (size_t i = 0; i < n->numHijos; ++i) {
            arm_emit_runtime_nodes(n->hijos[i], ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
        }
        return;
    }
    if (n->interpret == interpretBloqueExpresion) {
        if (ctx->debug) fprintf(f, "# debug: emit runtime bloque\n");
        // Procesar recursivamente el contenido del bloque
        for (size_t i = 0; i < n->numHijos; ++i) {
            arm_emit_runtime_nodes(n->hijos[i], ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
        }
        return;
    }
    if (n->interpret == interpretIfExpresion) {
        if (ctx->debug) fprintf(f, "# debug: emit runtime if statement\n");
        // Procesar recursivamente la condición y los bloques del if
        for (size_t i = 0; i < n->numHijos; ++i) {
            arm_emit_runtime_nodes(n->hijos[i], ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
        }
        return;
    }
    if (n->interpret == interpretCastExpresion) {
        if (ctx->debug) fprintf(f, "# debug: emit runtime cast expression\n");
        // Procesar recursivamente la expresión que se está casteando
        for (size_t i = 0; i < n->numHijos; ++i) {
            arm_emit_runtime_nodes(n->hijos[i], ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
        }
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


