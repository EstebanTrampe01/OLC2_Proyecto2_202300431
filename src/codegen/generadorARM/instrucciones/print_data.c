#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "codegen/literals.h"

#include "ast/nodos/expresiones/listaExpresiones.h"
#include "ast/nodos/expresiones/cast.h"
#include "ast/nodos/expresiones/expresiones.h"
#include "ast/nodos/expresiones/builtins.h"
#include "ast/nodos/expresiones/terminales/primitivos.h"
#include "ast/nodos/instrucciones/instruccion/print.h"

extern Result interpretListaExpresiones(AbstractExpresion*, Context*);
extern Result interpretCastExpresion(AbstractExpresion*, Context*);
extern Result interpretUnarioLenguaje(AbstractExpresion*, Context*);
extern Result interpretStringValueOf(AbstractExpresion*, Context*);

// Counter simple para etiquetas de mensajes
static int next_label_id = 0;

// Helper para concatenar literales de la lista de expresiones (si existen)
static char* collect_print_message(AbstractExpresion* listaExpr, int add_newline) {
    if (!listaExpr) {
        if (!add_newline) return NULL;
        char* out = (char*)malloc(2);
        out[0] = '\n'; out[1] = '\0';
        return out;
    }
    size_t total = 0;
    for (size_t i = 0; i < listaExpr->numHijos; ++i) {
        AbstractExpresion* e = listaExpr->hijos[i];
        if (e->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* p = (PrimitivoExpresion*) e;
            if (p->valor) total += strlen(p->valor);
        }
    }
    if (total == 0) {
        if (!add_newline) return NULL;
        char* out = (char*)malloc(2);
        out[0] = '\n'; out[1] = '\0';
        return out;
    }
    char* out = (char*)malloc(total + (add_newline ? 2 : 1));
    size_t pos = 0;
    for (size_t i = 0; i < listaExpr->numHijos; ++i) {
        AbstractExpresion* e = listaExpr->hijos[i];
        if (e->interpret == interpretPrimitivoExpresion) {
            PrimitivoExpresion* p = (PrimitivoExpresion*) e;
            if (p->valor) {
                size_t l = strlen(p->valor);
                memcpy(out + pos, p->valor, l);
                pos += l;
            }
        }
    }
    if (add_newline) out[pos++] = '\n';
    out[pos] = '\0';
    return out;
}

// Registrar string primitives dentro de la lista
static void register_print_strlits(AbstractExpresion* n) {
    if (!n) return;
    if (n->interpret == interpretPrimitivoExpresion) {
        PrimitivoExpresion* p = (PrimitivoExpresion*) n;
        if (p && p->valor && p->tipo == STRING) {
            const char* raw = p->valor; size_t L = strlen(raw);
            char* stripped = NULL;
            if (L>=2 && raw[0]=='"' && raw[L-1]=='"') stripped = strndup(raw+1, L-2);
            else stripped = strdup(raw);
            codegen_register_strlit(NULL, stripped);
            free(stripped);
        }
        return;
    }
    for (size_t i = 0; i < n->numHijos; ++i) register_print_strlits(n->hijos[i]);
}

int emit_print_data(CodegenContext* ctx, AbstractExpresion* printNode) {
    if (!ctx || !ctx->out || !printNode) return -1;
    AbstractExpresion* lista = (printNode->numHijos>0)? printNode->hijos[0] : NULL;
    int add_newline = 1;
    if (printNode->interpret == interpretPrintExpresion) {
        PrintExpresion* p = (PrintExpresion*) printNode;
        add_newline = p->newline ? 1 : 0;
    }
    register_print_strlits(lista);
    char* msg = collect_print_message(lista, add_newline);
    if (!msg) return -1;
    int id = ++next_label_id;
    fprintf(ctx->out, "L%u:\n", id);
    fprintf(ctx->out, "    .asciz \"");
    for (size_t i = 0; i < strlen(msg); ++i) {
        char c = msg[i];
        if (c == '\\') fprintf(ctx->out, "\\\\");
        else if (c == '"') fprintf(ctx->out, "\\\"");
        else if (c == '\n') fprintf(ctx->out, "\\n");
        else fprintf(ctx->out, "%c", c);
    }
    fprintf(ctx->out, "\"\n\n");
    fprintf(ctx->out, "L%u_end:\n\n", id);
    free(msg);
    return id;
}


