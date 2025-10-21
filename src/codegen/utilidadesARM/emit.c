#include "../codegen.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "../../entriesTools/comments.h"

static char* labels[100000];

static int label_used = 0;

// Inicializar contexto de codegen e imprimir header básico
CodegenContext* nuevo_codegen_context(FILE* out) {
    CodegenContext* ctx = (CodegenContext*)malloc(sizeof(CodegenContext));
    if (!ctx) return NULL;
    ctx->out = out;
    ctx->reg_counter = 0;
    ctx->s_reg_counter = 0;
    ctx->d_reg_counter = 0;
    ctx->label_counter = 0;
    ctx->stack_offset = 0;
    ctx->data_count = 0;
    ctx->symbol_ctx = NULL;
    // Emitir header básico del archivo .s
    fprintf(out, ".global _start\n");
    fprintf(out, ".text\n");
    fprintf(out, "_start:\n");
    // Reservar stack para variables locales
    fprintf(out, "sub sp, sp, #64\n");
    // Emitir comentarios
    for (int i = 0; i < comment_count; i++) {
        if (strstr(comments[i], "//")) {
            char* text = strstr(comments[i], "//") + 2;
            fprintf(out, "#%s\n", text);
        } else if (strstr(comments[i], "/*")) {
            fprintf(out, "%s\n", comments[i]);
        }
    }
    // Agregar buffer para prints
    add_data(ctx, "buffer: .space 32");
    add_data(ctx, "temp_str: .space 64");
    add_data(ctx, "true_str: .asciz \"true\"");
    add_data(ctx, "false_str: .asciz \"false\"");
    return ctx;
}

void liberar_codegen_context(CodegenContext* ctx) {
    if (ctx) {
        // Emitir .data
        fprintf(ctx->out, ".data\n");
        for (int i = 0; i < ctx->data_count; i++) {
            fprintf(ctx->out, "%s\n", ctx->data_lines[i]);
            free(ctx->data_lines[i]);
        }
        fclose(ctx->out);
        for (int i = 0; i < label_used; i++) {
            free(labels[i]);
        }
        free(ctx);
    }
}

void emit(CodegenContext* ctx, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(ctx->out, fmt, args);
    fprintf(ctx->out, "\n");
    va_end(args);
}

const char* new_label(CodegenContext* ctx) {
    if (label_used < 100000) {
        char* label = (char*)malloc(32);
        if (label) {
            snprintf(label, 32, "L%d", ctx->label_counter++);
            labels[label_used] = label;
            label_used++;
            return label;
        }
    }
    return "L0";
}

void add_data(CodegenContext* ctx, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    // Chequear si ya existe
    char* colon = strchr(buffer, ':');
    if (colon) {
        *colon = '\0';
        const char* label = buffer;
        for (int i = 0; i < ctx->data_count; i++) {
            char* existing_colon = strchr(ctx->data_lines[i], ':');
            if (existing_colon) {
                *existing_colon = '\0';
                if (strcmp(ctx->data_lines[i], label) == 0) {
                    *existing_colon = ':';
                    *colon = ':';
                    return; // Ya existe
                }
                *existing_colon = ':';
            }
        }
        *colon = ':';
    }
    if (ctx->data_count < 20000) {
        ctx->data_lines[ctx->data_count] = strdup(buffer);
        ctx->data_count++;
    }
}

void emit_print_string(CodegenContext* ctx, const char* str) {
    const char* label = new_label(ctx);
    add_data(ctx, "%s: .ascii \"%s\\n\"", label, str);
    emit(ctx, "mov x0, #1");
    emit(ctx, "adr x1, %s", label);
    emit(ctx, "mov x2, #%d", (int)strlen(str) + 1);
    emit(ctx, "mov x8, #64");
    emit(ctx, "svc #0");
}

void emit_print_char_literal(CodegenContext* ctx, char c) {
    char buf[4];
    sprintf(buf, "%c\n", c);
    const char* label = new_label(ctx);
    add_data(ctx, "%s: .ascii \"%s\"", label, buf);
    emit(ctx, "mov x0, #1");
    emit(ctx, "adr x1, %s", label);
    emit(ctx, "mov x2, #%d", (int)strlen(buf));
    emit(ctx, "mov x8, #64");
    emit(ctx, "svc #0");
}

void emit_print_int(CodegenContext* ctx, const char* reg) {
    // Generar código para itoa del valor en reg
    // Asumir reg es x0 para simplificar
    if (strcmp(reg, "x0") != 0) {
        emit(ctx, "mov x0, %s", reg);
    }
    // ptr = buffer + 31
    emit(ctx, "adr x1, buffer");
    emit(ctx, "add x1, x1, #31");
    // *ptr = 0
    emit(ctx, "strb wzr, [x1]");
    // val = x0
    emit(ctx, "mov x2, x0");
    // if val >= 0 goto positive
    const char* positive_label = new_label(ctx);
    const char* loop_label = new_label(ctx);
    const char* end_loop_label = new_label(ctx);
    const char* no_neg_label = new_label(ctx);
    emit(ctx, "cmp x2, #0");
    emit(ctx, "bge %s", positive_label);
    // neg
    emit(ctx, "neg x2, x2");
    emit(ctx, "mov x3, #1"); // flag neg
    emit(ctx, "b %s", loop_label);
    emit(ctx, "%s:", positive_label);
    emit(ctx, "mov x3, #0");
    emit(ctx, "%s:", loop_label);
    emit(ctx, "cmp x2, #0");
    emit(ctx, "beq %s", end_loop_label);
    emit(ctx, "sub x1, x1, #1");
    emit(ctx, "mov x4, #10");
    emit(ctx, "udiv x5, x2, x4");
    emit(ctx, "msub x6, x5, x4, x2");
    emit(ctx, "add w6, w6, #'0'");
    emit(ctx, "strb w6, [x1]");
    emit(ctx, "mov x2, x5");
    emit(ctx, "b %s", loop_label);
    emit(ctx, "%s:", end_loop_label);
    emit(ctx, "cmp x3, #0");
    emit(ctx, "beq %s", no_neg_label);
    emit(ctx, "sub x1, x1, #1");
    emit(ctx, "mov w4, #'-'");
    emit(ctx, "strb w4, [x1]");
    emit(ctx, "%s:", no_neg_label);
    // len = buffer +32 - ptr
    emit(ctx, "adr x2, buffer");
    emit(ctx, "add x2, x2, #32");
    emit(ctx, "sub x2, x2, x1");
    // write
    emit(ctx, "mov x0, #1");
    // x1 ptr
    // x2 len
    emit(ctx, "mov x8, #64");
    emit(ctx, "svc #0");
}

void emit_print_bool_literal(CodegenContext* ctx, int val) {
    const char* str = val ? "true\n" : "false\n";
    const char* label = new_label(ctx);
    add_data(ctx, "%s: .ascii \"%s\"", label, str);
    emit(ctx, "mov x0, #1");
    emit(ctx, "adr x1, %s", label);
    emit(ctx, "mov x2, #%d", (int)strlen(str));
    emit(ctx, "mov x8, #64");
    emit(ctx, "svc #0");
}

void emit_print_int_literal(CodegenContext* ctx, int val) {
    // Para literal, mover a x0 y llamar a emit_print_int
    emit(ctx, "mov x0, #%d", val);
    emit_print_int(ctx, "x0");
}

void emit_print_string_reg(CodegenContext* ctx, const char* reg) {
    // reg has address of null-terminated string
    // Calculate length
    const char* len_reg = alloc_temp_reg(ctx);
    const char* ptr_reg = alloc_temp_reg(ctx);
    emit(ctx, "mov %s, %s", ptr_reg, reg);
    emit(ctx, "mov %s, #0", len_reg);
    const char* loop_label = new_label(ctx);
    const char* end_label = new_label(ctx);
    emit(ctx, "%s:", loop_label);
    emit(ctx, "ldrb w9, [%s]", ptr_reg);
    emit(ctx, "cbz w9, %s", end_label);
    emit(ctx, "add %s, %s, #1", len_reg, len_reg);
    emit(ctx, "add %s, %s, #1", ptr_reg, ptr_reg);
    emit(ctx, "b %s", loop_label);
    emit(ctx, "%s:", end_label);
    // Now write
    emit(ctx, "mov x2, %s", len_reg);
    emit(ctx, "mov x1, %s", reg);
    emit(ctx, "mov x0, #1");
    emit(ctx, "mov x8, #64");
    emit(ctx, "svc #0");
    free_temp_reg(ctx, len_reg);
    free_temp_reg(ctx, ptr_reg);
}
