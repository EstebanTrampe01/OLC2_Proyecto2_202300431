#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "codegen/literals.h"

#include "ast/nodos/expresiones/terminales/primitivos.h"
#include "ast/nodos/expresiones/terminales/identificadores.h"
#include "ast/nodos/instrucciones/instruccion/asignaciones/asignacion.h"

// Emitir una asignación simple a una variable global GV_<name>
// Solo maneja RHS literal (PrimitivoExpresion) por ahora
void emit_asignacion_text(CodegenContext* ctx, AbstractExpresion* asignNode) {
    if (!ctx || !ctx->out || !asignNode) return;
    AsignacionExpresion* a = (AsignacionExpresion*) asignNode;
    if (asignNode->numHijos == 0) return;
    AbstractExpresion* rhs = asignNode->hijos[0];
    if (rhs->interpret != interpretPrimitivoExpresion) {
        if (ctx->debug) fprintf(ctx->out, "# debug: asignación RHS no es primitivo, ignorando\n");
        return;
    }
    PrimitivoExpresion* p = (PrimitivoExpresion*) rhs;
    if (!p) { if (ctx->debug) fprintf(ctx->out, "# debug: primitivo NULL\n"); return; }
    switch (p->tipo) {
        case INT: {
            long ival = atol(p->valor ? p->valor : "0");
            fprintf(ctx->out, "    // store integer %ld into GV_%s\n", ival, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);
            fprintf(ctx->out, "    mov x2, #%ld\n", ival);
            fprintf(ctx->out, "    str x2, [x1]\n\n");
            break;
        }
        case BOOLEAN: {
            int b = (p->valor && strcmp(p->valor, "true") == 0) ? 1 : 0;
            fprintf(ctx->out, "    // store boolean %d into GV_%s\n", b, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);
            fprintf(ctx->out, "    mov x2, #%d\n", b);
            fprintf(ctx->out, "    str x2, [x1]\n\n");
            break;
        }
        case CHAR: {
            char ch = (p->valor && strlen(p->valor)>0) ? p->valor[0] : '\0';
            int c = (int) ch;
            fprintf(ctx->out, "    // store char %c into GV_%s\n", ch, a->nombre);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);
            fprintf(ctx->out, "    mov w2, #%d\n", c);
            fprintf(ctx->out, "    strb w2, [x1]\n\n");
            break;
        }
        case STRING: {
            const char* tmpval = p->valor ? p->valor : "";
            size_t L = strlen(tmpval);
            char* stripped = NULL;
            if (L >= 2 && tmpval[0] == '"' && tmpval[L-1] == '"') {
                stripped = strndup(tmpval+1, L-2);
            } else {
                stripped = strdup(tmpval);
            }
            int existing = codegen_find_strlit(stripped);
            int sId = existing > 0 ? existing : codegen_register_strlit(ctx->out, stripped);
            free(stripped);
            fprintf(ctx->out, "    adrp x1, GV_%s\n", a->nombre);
            fprintf(ctx->out, "    add x1, x1, :lo12:GV_%s\n", a->nombre);
            fprintf(ctx->out, "    adrp x2, STRLIT_%d\n", sId);
            fprintf(ctx->out, "    add x2, x2, :lo12:STRLIT_%d\n", sId);
            fprintf(ctx->out, "    str x2, [x1]\n\n");
            break;
        }
        default:
            if (ctx->debug) fprintf(ctx->out, "# debug: asignación literal tipo no reconocido (tipo=%d)\n", p->tipo);
            break;
    }
}
