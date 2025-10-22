#include "codegen.h"
#include <stdlib.h>
#include <string.h>

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
    return ctx;
}

void codegen_programa(CodegenContext* ctx, AbstractExpresion* root) {
    if (!ctx || !ctx->out) return;
    char* msg = extract_first_string(root);
    if (!msg) msg = strdup("hola mundo\n");
    // Asegurar newline
    if (strchr(msg, '\n') == NULL) {
        size_t l = strlen(msg);
        char* tmp = malloc(l + 2);
        strcpy(tmp, msg);
        tmp[l] = '\n'; tmp[l+1] = '\0'; free(msg); msg = tmp;
    }
    size_t len = strlen(msg);

    FILE* f = ctx->out;
    fprintf(f, "    .section .data\n");
    fprintf(f, "    .align 3\n");
    fprintf(f, "msg:\n");
    // Escapar comillas y backslash
    fprintf(f, "    .asciz \"");
    for (size_t i = 0; i < len; ++i) {
        char c = msg[i];
        if (c == '\\') fprintf(f, "\\\\");
        else if (c == '"') fprintf(f, "\\\"");
        else if (c == '\n') fprintf(f, "\\n");
        else fprintf(f, "%c", c);
    }
    fprintf(f, "\"\n\n");

    fprintf(f, "    .section .text\n");
    fprintf(f, "    .global _start\n");
    fprintf(f, "_start:\n");
    if (ctx->debug) fprintf(f, "# debug: entering codegen_print_instr\n");
    fprintf(f, "    // write(1, msg, %zu)\n", len);
    fprintf(f, "    mov x0, #1\n");
    fprintf(f, "    adrp x1, msg\n");
    fprintf(f, "    add x1, x1, :lo12:msg\n");
    fprintf(f, "    mov x2, #%zu\n", len);
    fprintf(f, "    mov x8, #64\n");
    fprintf(f, "    svc #0\n\n");
    if (ctx->debug) fprintf(f, "# debug: leaving codegen_print_instr\n");

    fprintf(f, "    // exit(0)\n");
    fprintf(f, "    mov x0, #0\n");
    fprintf(f, "    mov x8, #93\n");
    fprintf(f, "    svc #0\n");

    fflush(f);
    free(msg);
}

void liberar_codegen_context(CodegenContext* ctx) {
    if (!ctx) return;
    // NO cerramos ctx->out porque el llamador puede cerrarlo
    free(ctx);
}
