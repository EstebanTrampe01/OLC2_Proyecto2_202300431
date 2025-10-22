#ifndef GENERADOR_PRINT_H
#define GENERADOR_PRINT_H

#include "../../codegen.h"
#include "../../../ast/AbstractExpresion.h"

// Emite la sección .data para el nodo print y retorna un id de etiqueta (>=1)
int emit_print_data(CodegenContext* ctx, AbstractExpresion* printNode);

// Emite el código .text (write) asociado a la etiqueta retornada por emit_print_data
void emit_print_text(CodegenContext* ctx, AbstractExpresion* printNode, int label_id);

#endif
