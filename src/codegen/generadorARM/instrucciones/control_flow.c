#include "control_flow.h"
#include "../../codegen.h"
#include "../../../ast/nodos/instrucciones/instruccion/if.h"
#include "../../../ast/nodos/instrucciones/instruccion/while.h"
#include "../../../ast/nodos/instrucciones/instruccion/for.h"
#include "../expresiones/emit_expr.h"
#include <stdio.h>
#include <stdlib.h>

static int label_counter = 0;

// Generar una etiqueta única
static char* generate_label(const char* prefix) {
    char* label = malloc(32);
    snprintf(label, 32, "%s_%d", prefix, label_counter++);
    return label;
}

void arm_emit_if_statement(CodegenContext* ctx, AbstractExpresion* ifNode, FILE* f, 
                          AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
                          char** emitted_names, int* emitted_types, int emitted_count) {
    if (!ifNode || ifNode->interpret != interpretIfExpresion) {
        return;
    }
    
    IfExpresion* ifExpr = (IfExpresion*)ifNode;
    
    // Generar etiquetas únicas
    char* else_label = generate_label("else");
    char* end_label = generate_label("endif");
    
    fprintf(f, "    // IF statement\n");
    
    // Evaluar condición y poner resultado en x9
    arm_emit_eval_expr(ctx, ifExpr->condicion, 9, f);
    
    // Comparar condición con 0 (false)
    fprintf(f, "    cmp x9, #0\n");
    
    // Saltar al else si la condición es falsa
    if (ifExpr->bloqueElse) {
        fprintf(f, "    b.eq %s\n", else_label);
    } else {
        fprintf(f, "    b.eq %s\n", end_label);
    }
    
    // Bloque IF (condición verdadera)
    fprintf(f, "    // Bloque IF\n");
    // Procesar el bloque IF completo
    arm_emit_runtime_nodes(ifExpr->bloqueIf, ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
    
    // Saltar al final si hay else
    if (ifExpr->bloqueElse) {
        fprintf(f, "    b %s\n", end_label);
        
        // Bloque ELSE
        fprintf(f, "%s:\n", else_label);
        fprintf(f, "    // Bloque ELSE\n");
        // Procesar el bloque ELSE completo
        arm_emit_runtime_nodes(ifExpr->bloqueElse, ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
    }
    
    // Etiqueta de fin
    fprintf(f, "%s:\n", end_label);
    fprintf(f, "    // Fin IF\n");
    
    // Liberar memoria de las etiquetas
    free(else_label);
    free(end_label);
}

void arm_emit_while_statement(CodegenContext* ctx, AbstractExpresion* whileNode, FILE* f, 
                              AbstractExpresion** label_nodes, int* label_ids, int label_map_size,
                              char** emitted_names, int* emitted_types, int emitted_count) {
    if (!whileNode || whileNode->interpret != interpretWhileExpresion) {
        return;
    }
    
    WhileExpresion* whileExpr = (WhileExpresion*)whileNode;
    
    // Generar etiquetas únicas
    char* loop_label = generate_label("while_loop");
    char* end_label = generate_label("while_end");
    
    fprintf(f, "    // WHILE statement\n");
    
    // Etiqueta de inicio del bucle
    fprintf(f, "%s:\n", loop_label);
    
    // Evaluar condición y poner resultado en x9
    arm_emit_eval_expr(ctx, whileExpr->condition, 9, f);
    
    // Comparar condición con 0 (false)
    fprintf(f, "    cmp x9, #0\n");
    
    // Saltar al final si la condición es falsa
    fprintf(f, "    b.eq %s\n", end_label);
    
    // Bloque del bucle
    fprintf(f, "    // Bloque WHILE\n");
    arm_emit_runtime_nodes(whileExpr->body, ctx, f, label_nodes, label_ids, label_map_size, emitted_names, emitted_types, emitted_count);
    
    // Saltar de vuelta al inicio del bucle
    fprintf(f, "    b %s\n", loop_label);
    
    // Etiqueta de fin
    fprintf(f, "%s:\n", end_label);
    fprintf(f, "    // Fin WHILE\n");
    
    // Liberar memoria de las etiquetas
    free(loop_label);
    free(end_label);
}

void arm_emit_for_statement(CodegenContext* ctx, AbstractExpresion* forNode, FILE* f) {
    if (!forNode || forNode->interpret != interpretForExpresion) {
        return;
    }
    
    ForExpresion* forExpr = (ForExpresion*)forNode;
    
    // Generar etiquetas únicas
    char* loop_label = generate_label("for_loop");
    char* end_label = generate_label("for_end");
    
    fprintf(f, "    // FOR statement\n");
    
    // Inicialización (si existe)
    if (forExpr->initialization) {
        fprintf(f, "    // Inicialización FOR\n");
        arm_emit_runtime_nodes(forExpr->initialization, ctx, f, NULL, NULL, 0, NULL, NULL, 0);
    }
    
    // Etiqueta de inicio del bucle
    fprintf(f, "%s:\n", loop_label);
    
    // Condición (si existe)
    if (forExpr->condition) {
        // Evaluar condición y poner resultado en x9
        arm_emit_eval_expr(ctx, forExpr->condition, 9, f);
        
        // Comparar condición con 0 (false)
        fprintf(f, "    cmp x9, #0\n");
        
        // Saltar al final si la condición es falsa
        fprintf(f, "    b.eq %s\n", end_label);
    }
    
    // Bloque del bucle
    fprintf(f, "    // Bloque FOR\n");
    arm_emit_runtime_nodes(forExpr->body, ctx, f, NULL, NULL, 0, NULL, NULL, 0);
    
    // Incremento (si existe)
    if (forExpr->increment) {
        fprintf(f, "    // Incremento FOR\n");
        arm_emit_runtime_nodes(forExpr->increment, ctx, f, NULL, NULL, 0, NULL, NULL, 0);
    }
    
    // Saltar de vuelta al inicio del bucle
    fprintf(f, "    b %s\n", loop_label);
    
    // Etiqueta de fin
    fprintf(f, "%s:\n", end_label);
    fprintf(f, "    // Fin FOR\n");
    
    // Liberar memoria de las etiquetas
    free(loop_label);
    free(end_label);
}
