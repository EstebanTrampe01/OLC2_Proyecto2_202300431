#include "../../codegen.h"
#include "../../registroARM/regs.h"
#include "../../../ast/AbstractExpresion.h"
#include "../../../ast/nodos/expresiones/builtins.h"
#include "../../../ast/nodos/instrucciones/instruccion/funcion.h"
#include "../../../ast/nodos/expresiones/expresiones.h"
#include "../../../ast/nodos/expresiones/terminales/primitivos.h"
#include "../../../ast/nodos/expresiones/terminales/identificadores.h"
#include "../../../ast/nodos/expresiones/aritmeticas/aritmeticas.h"
#include "../../../ast/nodos/expresiones/relacionales/relacionales.h"
#include "../../../ast/nodos/expresiones/logicas/logicas.h"
#include "../../../context/context.h"
#include <stdlib.h>
#include <string.h>

// Forward declaration
extern TipoDato get_expr_type(AbstractExpresion* expr, Context* ctx);

// (Contenido adaptado del original...)

// Aquí irán las funciones para String.valueOf y similares

// Helper: create a .asciz data label with given text and return a reg holding its address
static const char* make_data_string_and_return_reg(CodegenContext* ctx, const char* text) {
	const char* label = new_label(ctx);
	add_data(ctx, "%s: .asciz \"%s\"", label, text);
	const char* reg = alloc_temp_reg(ctx);
	emit(ctx, "ldr %s, =%s", reg, label);
	return reg;
}

// Convert a primitive expression (if literal) to a string at compile time.
// If the expression is not a primitive literal, emit a runtime conversion using helper functions.
const char* codegen_string_value_of(CodegenContext* ctx, AbstractExpresion* arg) {
	if (!arg) return NULL;
	// If it's a primitive literal, we can inline the value
	if (arg->interpret == interpretPrimitivoExpresion) {
		PrimitivoExpresion* prim = (PrimitivoExpresion*)arg;
		if (prim->tipo == STRING) {
			return make_data_string_and_return_reg(ctx, prim->valor ? prim->valor : "");
		} else if (prim->tipo == INT) {
			char buf[64];
			sprintf(buf, "%d", atoi(prim->valor));
			return make_data_string_and_return_reg(ctx, buf);
		} else if (prim->tipo == BOOLEAN) {
			const char* s = (strcmp(prim->valor, "true") == 0) ? "true" : "false";
			return make_data_string_and_return_reg(ctx, s);
		} else if (prim->tipo == CHAR) {
			char buf[2] = {prim->valor[0], 0};
			return make_data_string_and_return_reg(ctx, buf);
		} else if (prim->tipo == FLOAT || prim->tipo == DOUBLE) {
			char buf[128];
			double v = atof(prim->valor);
			// default formatting
			snprintf(buf, sizeof(buf), "%f", v);
			return make_data_string_and_return_reg(ctx, buf);
		}
	}

	// For non-literal arguments, generate runtime conversion.
	// We'll assume helper functions exist: itoa (int->string) and ftoa (float/double->string)
	// Evaluate the argument and place into x0, then call the helper which returns pointer in x0.
	const char* arg_reg = codegen_expr(ctx, arg);
	if (!arg_reg) return NULL;

	TipoDato tipo = get_expr_type(arg, ctx->symbol_ctx);
	if (tipo == BOOLEAN) {
		const char* out = alloc_temp_reg(ctx);
		int label_id = ctx->label_counter++;
		emit(ctx, "cmp %s, #0", arg_reg);
		emit(ctx, "b.eq .L_false_%d", label_id);
		emit(ctx, "ldr %s, =true_str", out);
		emit(ctx, "b .L_end_bool_%d", label_id);
		emit(ctx, ".L_false_%d:", label_id);
		emit(ctx, "ldr %s, =false_str", out);
		emit(ctx, ".L_end_bool_%d:", label_id);
		free_temp_reg(ctx, arg_reg);
		return out;
	} else if (tipo == CHAR) {
		const char* out = alloc_temp_reg(ctx);
		emit(ctx, "ldr %s, =buffer", out);
		emit(ctx, "strb w%s, [%s]", arg_reg, out);
		emit(ctx, "strb wzr, [%s, #1]", out);
		free_temp_reg(ctx, arg_reg);
		return out;
	} else {
		// Move argument into x0 depending on register type
		if (arg_reg[0] == 'x' || arg_reg[0] == 'r') {
			emit(ctx, "mov x0, %s", arg_reg);
			free_temp_reg(ctx, arg_reg);
			emit(ctx, "ldr x1, =buffer");
			emit(ctx, "bl itoa");
		} else if (arg_reg[0] == 'd' || arg_reg[0] == 's') {
			// For floating regs, move to a known float passing reg and call ftoa
			// Assume ftoa reads from s0/d0 and returns pointer in x0
			if (arg_reg[0] == 's') {
				emit(ctx, "fmov s0, %s", arg_reg);
				free_temp_s_reg(ctx, arg_reg);
			} else {
				emit(ctx, "fmov d0, %s", arg_reg);
				free_temp_d_reg(ctx, arg_reg);
			}
			emit(ctx, "ldr x1, =buffer");
			emit(ctx, "bl ftoa");
		} else {
			// fallback: move to x0 and call itoa
			emit(ctx, "mov x0, %s", arg_reg);
			free_temp_reg(ctx, arg_reg);
			emit(ctx, "ldr x1, =buffer");
			emit(ctx, "bl itoa");
		}

		// The helper returns pointer in x0; move it to a temp reg to follow convention
		const char* out = alloc_temp_reg(ctx);
		emit(ctx, "mov %s, x0", out);
		return out;
	}
}

// Simple builtin dispatcher: for now only String.valueOf is supported
const char* codegen_builtin_call(CodegenContext* ctx, LlamadaFuncion* call) {
	if (!call) return NULL;
	if (strcmp(call->nombre, "String.valueOf") == 0 && call->args && call->args->numHijos == 1) {
		return codegen_string_value_of(ctx, call->args->hijos[0]);
	}
	// unknown builtin
	return NULL;
}
