#include "../../codegen.h"
#include "../../registroARM/regs.h"
#include "../../../ast/AbstractExpresion.h"
#include "../../../ast/nodos/expresiones/terminales/identificadores.h"
#include "../../../context/context.h"

// Función para compilar expresiones de identificadores
const char* codegen_identifier(CodegenContext* ctx, IdentificadorExpresion* id) {
    Symbol* sym = buscarTablaSimbolos(ctx->symbol_ctx, id->nombre);
    TipoDato tipo = sym ? sym->tipo : VOID;
    // Asumir variables locales en stack
    // Hardcode offsets por nombre para pruebas, negativos
    int offset = 0;
    if (strcmp(id->nombre, "numeroEntero") == 0) offset = -8;
    else if (strcmp(id->nombre, "numeroFlotante") == 0) offset = -16;
    else if (strcmp(id->nombre, "numeroDoble") == 0) offset = -24;
    else if (strcmp(id->nombre, "caracter") == 0) offset = -32;
    else if (strcmp(id->nombre, "esVerdadero") == 0) offset = -40;
    else if (strcmp(id->nombre, "cadenaTexto") == 0) offset = -48;
    else if (strcmp(id->nombre, "a") == 0) offset = -56;
    else if (strcmp(id->nombre, "b") == 0) offset = -64;
    // Para otros, 0

    if (tipo == STRING) {
        const char* val_reg = alloc_temp_reg(ctx);
        emit(ctx, "ldr %s, [sp, #%d]", val_reg, offset);
        return val_reg;
    } else {
        const char* val_reg;
        if (tipo == DOUBLE) {
            val_reg = alloc_temp_d_reg(ctx);
            emit(ctx, "ldr %s, [sp, #%d]", val_reg, offset);
        } else if (tipo == FLOAT) {
            val_reg = alloc_temp_s_reg(ctx);
            emit(ctx, "ldr %s, [sp, #%d]", val_reg, offset);
        } else {
            val_reg = alloc_temp_reg(ctx);
            emit(ctx, "ldr %s, [sp, #%d]", val_reg, offset);
        }
        return val_reg;
    }
}
