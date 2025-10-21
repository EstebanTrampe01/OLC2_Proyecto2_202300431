#include "../codegen.h"
#include "../registroARM/regs.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/expresiones/terminales/identificadores.h"
#include "../../context/context.h"

// Función para compilar expresiones de identificadores
const char* codegen_identifier(CodegenContext* ctx, IdentificadorExpresion* id) {
    Symbol* sym = buscarTablaSimbolos(ctx->symbol_ctx, id->nombre);
    TipoDato tipo = sym ? sym->tipo : VOID;
    const char* addr_reg = alloc_temp_reg(ctx);
    emit(ctx, "ldr %s, =%s", addr_reg, id->nombre);
    if (tipo == STRING) {
        // Para strings, cargar el puntero guardado en la variable
        const char* val_reg = alloc_temp_reg(ctx);
        emit(ctx, "ldr %s, [%s]", val_reg, addr_reg);
        free_temp_reg(ctx, addr_reg);
        return val_reg;
    } else {
        // Para otros, cargar el valor
        const char* val_reg;
        if (tipo == DOUBLE) {
            val_reg = alloc_temp_d_reg(ctx);
            emit(ctx, "ldr %s, [%s]", val_reg, addr_reg);
        } else if (tipo == FLOAT) {
            val_reg = alloc_temp_s_reg(ctx);
            emit(ctx, "ldr %s, [%s]", val_reg, addr_reg);
        } else {
            val_reg = alloc_temp_reg(ctx);
            emit(ctx, "ldr %s, [%s]", val_reg, addr_reg);
        }
        free_temp_reg(ctx, addr_reg);
        return val_reg;
    }
}