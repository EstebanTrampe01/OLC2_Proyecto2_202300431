    .section .data
    .align 3
L1:
    .asciz "Test desde GTK\n"

L1_end:

STRLIT_1:
    .asciz "Test desde GTK"

    .section .text
    .global _start
_start:
    // Inicializar pila para operaciones complejas
    mov x0, sp
    sub sp, sp, #1024
    // REPEAT statement
    // Evaluar número de repeticiones
    // Cargar entero literal 2 en registro x10
    mov x10, #2
    mov x11, #0
repeat_loop_0:
    cmp x11, x10
    b.ge repeat_end_1
    // Bloque REPEAT
    // ===== System.out.println =====
# interpret_map:
#   PRIMITIVO=0x55b2a778b6be
#   IDENTIFICADOR=0x55b2a778b5c1
#   EXPRESION_LENGUAJE=0x55b2a778af2b
#   LLAMADA_FUNCION=0x55b2a7793b61
#   LISTA_EXPRESIONES=0x55b2a7784ef7
#   CAST=0x55b2a778a8d6
#   UNARIO_LENGUAJE=0x55b2a778b38b
#   BUILTIN_STRING_VALUEOF=0x55b2a778655c
#   PRINT_EXPR=0x55b2a77932ea
# AST node: PRIMITIVO iptr=0x55b2a778b6be children=0
#   prim tipo=9 valor=Test desde GTK
    // Imprimir string literal 'Test desde GTK'
    adrp x0, STRLIT_1
    add x0, x0, :lo12:STRLIT_1
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    add x11, x11, #1
    b repeat_loop_0
repeat_end_1:
    // Fin REPEAT
    .section .data
    .section .text
    mov x0, #0
    mov x8, #93
    svc #0
