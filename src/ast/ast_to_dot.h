#ifndef AST_TO_DOT_H
#define AST_TO_DOT_H

#include "ast/AbstractExpresion.h"

/* Exporta el AST a un archivo DOT (Graphviz). Devuelve 0 en éxito, -1 en error. */
int ast_export_to_dot(AbstractExpresion* root, const char* path);

#endif
