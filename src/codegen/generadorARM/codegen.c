#include "../codegen.h"
#include "../../ast/AbstractExpresion.h"
#include "../../ast/nodos/instrucciones/instruccion/print.h"
#include "../../ast/nodos/instrucciones/instrucciones.h"
#include "../../ast/nodos/instrucciones/instruccion/funcion.h"
#include "../../ast/nodos/instrucciones/bloque.h"

// Función principal para generar código desde el AST
void codegen_programa(CodegenContext* ctx, struct AbstractExpresion* ast_root) {
    if (!ast_root) return;

    // Recorrer recursivamente el AST
    codegen_node(ctx, ast_root);

    // Al final, exit syscall
    emit(ctx, "add sp, sp, #64");  // restore stack
    emit(ctx, "mov x0, #0");
    emit(ctx, "mov x8, #93");  // syscall exit
    emit(ctx, "svc #0");

    // Función strcmp para strings
    emit(ctx, "strcmp:");
    emit(ctx, "    mov x2, #0");
    emit(ctx, "strcmp_loop:");
    emit(ctx, "    ldrb w3, [x0], #1");
    emit(ctx, "    ldrb w4, [x1], #1");
    emit(ctx, "    cmp w3, w4");
    emit(ctx, "    bne strcmp_not_equal");
    emit(ctx, "    cmp w3, #0");
    emit(ctx, "    bne strcmp_loop");
    emit(ctx, "    mov x0, #0");
    emit(ctx, "    ret");
    emit(ctx, "strcmp_not_equal:");
    emit(ctx, "    mov x0, #1");
    emit(ctx, "    ret");

    // Función itoa para convertir int a string
    emit(ctx, "itoa:");
    emit(ctx, "    mov x2, x1");
    emit(ctx, "    cmp x0, #0");
    emit(ctx, "    bge itoa_positive");
    emit(ctx, "    neg x0, x0");
    emit(ctx, "    mov w3, #'-'");
    emit(ctx, "    strb w3, [x2], #1");
    emit(ctx, "itoa_positive:");
    emit(ctx, "    mov x3, #10");
    emit(ctx, "    mov x4, x0");
    emit(ctx, "    cmp x4, #0");
    emit(ctx, "    beq itoa_zero");
    emit(ctx, "    mov x5, #0");
    emit(ctx, "itoa_loop:");
    emit(ctx, "    udiv x6, x4, x3");
    emit(ctx, "    msub x7, x6, x3, x4");
    emit(ctx, "    add w7, w7, #'0'");
    emit(ctx, "    strb w7, [x2, x5]");
    emit(ctx, "    add x5, x5, #1");
    emit(ctx, "    mov x4, x6");
    emit(ctx, "    cmp x4, #0");
    emit(ctx, "    bne itoa_loop");
    emit(ctx, "    sub x5, x5, #1");
    emit(ctx, "    mov x6, #0");
    emit(ctx, "itoa_reverse:");
    emit(ctx, "    cmp x6, x5");
    emit(ctx, "    bge itoa_end");
    emit(ctx, "    ldrb w7, [x2, x6]");
    emit(ctx, "    ldrb w8, [x2, x5]");
    emit(ctx, "    strb w8, [x2, x6]");
    emit(ctx, "    strb w7, [x2, x5]");
    emit(ctx, "    add x6, x6, #1");
    emit(ctx, "    sub x5, x5, #1");
    emit(ctx, "    b itoa_reverse");
    emit(ctx, "itoa_zero:");
    emit(ctx, "    mov w3, #'0'");
    emit(ctx, "    strb w3, [x2], #1");
    emit(ctx, "itoa_end:");
    emit(ctx, "    strb wzr, [x2]");
    emit(ctx, "    mov x0, x1");
    emit(ctx, "    ret");

    // Función ftoa para convertir float/double a string (simplificada: convierte a int)
    emit(ctx, "ftoa:");
    emit(ctx, "    fcvtzs x0, d0");  // assume double in d0
    emit(ctx, "    ldr x1, =buffer");
    emit(ctx, "    bl itoa");
    emit(ctx, "    ret");

    // Función concat para concatenar strings
    emit(ctx, "concat:");
    emit(ctx, "    mov x3, x0");
    emit(ctx, "    mov x4, x2");
    emit(ctx, "concat_loop1:");
    emit(ctx, "    ldrb w5, [x3], #1");
    emit(ctx, "    strb w5, [x4], #1");
    emit(ctx, "    cmp w5, #0");
    emit(ctx, "    bne concat_loop1");
    emit(ctx, "    sub x4, x4, #1");
    emit(ctx, "concat_loop2:");
    emit(ctx, "    ldrb w5, [x1], #1");
    emit(ctx, "    strb w5, [x4], #1");
    emit(ctx, "    cmp w5, #0");
    emit(ctx, "    bne concat_loop2");
    emit(ctx, "    mov x0, x2");
    emit(ctx, "    ret");

    // Función print_int
    emit(ctx, "print_int:");
    emit(ctx, "    ldr x1, =buffer");
    emit(ctx, "    add x1, x1, #31");
    emit(ctx, "    strb wzr, [x1]");
    emit(ctx, "    mov x2, x0");
    emit(ctx, "    cmp x2, #0");
    emit(ctx, "    bge print_int_positive");
    emit(ctx, "    neg x2, x2");
    emit(ctx, "    mov x3, #1");
    emit(ctx, "    b print_int_loop");
    emit(ctx, "print_int_positive:");
    emit(ctx, "    mov x3, #0");
    emit(ctx, "print_int_loop:");
    emit(ctx, "    cmp x2, #0");
    emit(ctx, "    beq print_int_end_loop");
    emit(ctx, "    sub x1, x1, #1");
    emit(ctx, "    mov x4, #10");
    emit(ctx, "    udiv x5, x2, x4");
    emit(ctx, "    msub x6, x5, x4, x2");
    emit(ctx, "    add w6, w6, #'0'");
    emit(ctx, "    strb w6, [x1]");
    emit(ctx, "    mov x2, x5");
    emit(ctx, "    b print_int_loop");
    emit(ctx, "print_int_end_loop:");
    emit(ctx, "    cmp x3, #0");
    emit(ctx, "    beq print_int_print");
    emit(ctx, "    sub x1, x1, #1");
    emit(ctx, "    mov w4, #'-'");
    emit(ctx, "    strb w4, [x1]");
    emit(ctx, "print_int_print:");
    emit(ctx, "    mov x0, #1");
    emit(ctx, "    ldr x1, =buffer");
    emit(ctx, "    add x1, x1, #31");
    emit(ctx, "    sub x1, x1, x2");  // approximate
    emit(ctx, "    mov x2, #32");
    emit(ctx, "    mov x8, #64");
    emit(ctx, "    svc #0");
    emit(ctx, "    ret");

    // Función print_string
    emit(ctx, "print_string:");
    emit(ctx, "    mov x1, x0");
    emit(ctx, "    mov x2, #0");
    emit(ctx, "print_string_count:");
    emit(ctx, "    ldrb w3, [x1, x2]");
    emit(ctx, "    cmp w3, #0");
    emit(ctx, "    beq print_string_write");
    emit(ctx, "    add x2, x2, #1");
    emit(ctx, "    b print_string_count");
    emit(ctx, "print_string_write:");
    emit(ctx, "    mov x0, #1");
    emit(ctx, "    mov x1, x0");
    emit(ctx, "    mov x8, #64");
    emit(ctx, "    svc #0");
    emit(ctx, "    ret");

    // Sección de datos
    emit(ctx, ".data");
    emit(ctx, "msg: .ascii \"Hello\\n\"");
}

// Función recursiva para procesar un nodo
void codegen_node(CodegenContext* ctx, AbstractExpresion* node) {
    if (!node) return;

    // Si es una instrucción, procesarla
    codegen_instr(ctx, node);

    // Procesar hijos recursivamente solo si no es instrucción
    if (node->interpret != interpretPrintExpresion && node->interpret != interpretFuncionDeclaracion && node->interpret != interpretBloqueExpresion) {
        for (size_t i = 0; i < node->numHijos; i++) {
            codegen_node(ctx, node->hijos[i]);
        }
    }
}