#ifndef ERROR_REPORTING_H
#define ERROR_REPORTING_H

#include "context.h"
#include "ast/AbstractExpresion.h"
#include <stdarg.h>

/* Reporte existente (semántico); se mantendrá como envoltorio */
void report_runtime_error(AbstractExpresion* nodo, Context* ctx, const char* fmt, ...);

/* Nuevo: reporte categorizado. tipoEsperado: "Lexico", "Sintactico", "Semantico" */
void report_categorized_error(const char* tipo, AbstractExpresion* nodo, Context* ctx, const char* fmt, ...);
void report_lexical_error(const char* fmt, ...);      /* usa yylloc global */
void report_syntax_error(const char* fmt, ...);       /* usa yylloc global */
void report_semantic_error(AbstractExpresion* nodo, Context* ctx, const char* fmt, ...);

#endif