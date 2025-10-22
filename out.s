    .section .data
    .align 3
L1:
    .asciz "-- Test4 globals --\n"

L1_end:

L2:
    .asciz "\n"

L2_end:

L3:
    .asciz "\n"

L3_end:

L4:
    .asciz "\n"

L4_end:

L5:
    .asciz "\n"

L5_end:

L6:
    .asciz "\n"

L6_end:

L7:
    .asciz "\n"

L7_end:

L8:
    .asciz "-- Test4 globals CAMBIADO --\n"

L8_end:

L9:
    .asciz "\n"

L9_end:

L10:
    .asciz "\n"

L10_end:

L11:
    .asciz "\n"

L11_end:

L12:
    .asciz "\n"

L12_end:

L13:
    .asciz "\n"

L13_end:

L14:
    .asciz "\n"

L14_end:

STRLIT_1:
    .asciz "Hola global"

STRLIT_2:
    .asciz "Hola global CAMBIADO"

GV_numeroEntero: .quad 42

GV_numeroFlotante: .float 3.14

GV_numeroDoble: .double 2.718281828

GV_caracter: .byte 65

GV_esVerdadero: .quad 1

GV_cadenaTexto: .quad STRLIT_1

GV_numeroEntero_str:
    .asciz "42"

GV_numeroEntero_str_end:

GV_numeroFlotante_str:
    .asciz "3.14"

GV_numeroFlotante_str_end:

GV_numeroDoble_str:
    .asciz "2.718281828"

GV_numeroDoble_str_end:

GV_caracter_str:
    .asciz "A"

GV_caracter_str_end:

GV_esVerdadero_str:
    .asciz "1"

GV_esVerdadero_str_end:

GV_cadenaTexto_str:
    .asciz "Hola global"

GV_cadenaTexto_str_end:

    .section .text
    .global _start
_start:
    adrp x1, L1
    add x1, x1, :lo12:L1
    adrp x2, L1_end
    add x2, x2, :lo12:L1_end
    sub x2, x2, x1
    mov x0, #1
    mov x8, #64
    svc #0

    adrp x0, GV_numeroEntero
    add x0, x0, :lo12:GV_numeroEntero
    // tipo tag=5
    mov x1, #5
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_numeroFlotante
    add x0, x0, :lo12:GV_numeroFlotante
    // tipo tag=7
    mov x1, #7
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_numeroDoble
    add x0, x0, :lo12:GV_numeroDoble
    // tipo tag=8
    mov x1, #8
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_caracter
    add x0, x0, :lo12:GV_caracter
    // tipo tag=2
    mov x1, #2
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_esVerdadero
    add x0, x0, :lo12:GV_esVerdadero
    // tipo tag=1
    mov x1, #1
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_cadenaTexto
    add x0, x0, :lo12:GV_cadenaTexto
    // tipo tag=9
    mov x1, #9
    mov x2, #1
    bl print_any_gv

    // store integer 100 into GV_numeroEntero
    adrp x1, GV_numeroEntero
    add x1, x1, :lo12:GV_numeroEntero
    mov x2, #100
    str x2, [x1]

    // store char Z into GV_caracter
    adrp x1, GV_caracter
    add x1, x1, :lo12:GV_caracter
    mov w2, #90
    strb w2, [x1]

    // store boolean 0 into GV_esVerdadero
    adrp x1, GV_esVerdadero
    add x1, x1, :lo12:GV_esVerdadero
    mov x2, #0
    str x2, [x1]

    adrp x1, GV_cadenaTexto
    add x1, x1, :lo12:GV_cadenaTexto
    adrp x2, STRLIT_2
    add x2, x2, :lo12:STRLIT_2
    str x2, [x1]

    adrp x1, L8
    add x1, x1, :lo12:L8
    adrp x2, L8_end
    add x2, x2, :lo12:L8_end
    sub x2, x2, x1
    mov x0, #1
    mov x8, #64
    svc #0

    adrp x0, GV_numeroEntero
    add x0, x0, :lo12:GV_numeroEntero
    // tipo tag=5
    mov x1, #5
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_numeroFlotante
    add x0, x0, :lo12:GV_numeroFlotante
    // tipo tag=7
    mov x1, #7
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_numeroDoble
    add x0, x0, :lo12:GV_numeroDoble
    // tipo tag=8
    mov x1, #8
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_caracter
    add x0, x0, :lo12:GV_caracter
    // tipo tag=2
    mov x1, #2
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_esVerdadero
    add x0, x0, :lo12:GV_esVerdadero
    // tipo tag=1
    mov x1, #1
    mov x2, #1
    bl print_any_gv

    adrp x0, GV_cadenaTexto
    add x0, x0, :lo12:GV_cadenaTexto
    // tipo tag=9
    mov x1, #9
    mov x2, #1
    bl print_any_gv

    mov x0, #0
    mov x8, #93
    svc #0
