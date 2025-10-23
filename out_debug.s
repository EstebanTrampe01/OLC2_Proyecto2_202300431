    .section .data
    .align 3
L1:
    .asciz "=== TEST FLOAT DEBUG ===\n"

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

STRLIT_1:
    .asciz "=== TEST FLOAT DEBUG ==="

STRLIT_2:
    .asciz "Valor inicial: "

STRLIT_3:
    .asciz "Valor después de reasignación: "

STRLIT_4:
    .asciz "Valor double: "

NUMLIT_1:
    .quad 0x40091eb851eb851f

NUMLIT_2:
    .quad 0x4005bf0a8b04919b

GV_numeroFlotante: .quad 0

GV_numeroDoble: .double 2.718281828

GV_numeroDoble_str:
    .asciz "2.718281828"

GV_numeroDoble_str_end:

    .section .text
    .global _start
_start:
    // ===== System.out.println =====
# interpret_map:
#   PRIMITIVO=0x6335844cc281
#   IDENTIFICADOR=0x6335844cc184
#   EXPRESION_LENGUAJE=0x6335844cbaee
#   LLAMADA_FUNCION=0x6335844d4556
#   LISTA_EXPRESIONES=0x6335844c5aba
#   CAST=0x6335844cb499
#   UNARIO_LENGUAJE=0x6335844cbf4e
#   BUILTIN_STRING_VALUEOF=0x6335844c711f
#   PRINT_EXPR=0x6335844d3cdf
# AST node: PRIMITIVO iptr=0x6335844cc281 children=0
#   prim tipo=9 valor==== TEST FLOAT DEBUG ===
    // Imprimir string literal '=== TEST FLOAT DEBUG ==='
    adrp x0, STRLIT_1
    add x0, x0, :lo12:STRLIT_1
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x6335844cbaee children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x6335844cc281 children=0
# #   prim tipo=9 valor=Valor inicial: 
# # AST node: UNKNOWN iptr=0x6335844c711f children=0
    // Imprimir string literal 'Valor inicial: '
    adrp x0, STRLIT_2
    add x0, x0, :lo12:STRLIT_2
    mov x1, #0
    bl print_string

    adrp x1, GV_numeroFlotante
    add x1, x1, :lo12:GV_numeroFlotante
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

    // ===== Fin System.out.println =====

    // Asignar flotante 5.670000 a variable global 'numeroFlotante'
    adrp x1, GV_numeroFlotante
    add x1, x1, :lo12:GV_numeroFlotante
    mov w2, #0
    fmov s2, w2
    str s2, [x1]

    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x6335844cbaee children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x6335844cc281 children=0
# #   prim tipo=9 valor=Valor después de reasignación: 
# # AST node: UNKNOWN iptr=0x6335844c711f children=0
    // Imprimir string literal 'Valor despu\xC3\xA9s de reasignaci\xC3\xB3n: '
    adrp x0, STRLIT_3
    add x0, x0, :lo12:STRLIT_3
    mov x1, #0
    bl print_string

    adrp x1, GV_numeroFlotante
    add x1, x1, :lo12:GV_numeroFlotante
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

    // ===== Fin System.out.println =====

    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x6335844cbaee children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x6335844cc281 children=0
# #   prim tipo=9 valor=Valor double: 
# # AST node: UNKNOWN iptr=0x6335844c711f children=0
    // Imprimir string literal 'Valor double: '
    adrp x0, STRLIT_4
    add x0, x0, :lo12:STRLIT_4
    mov x1, #0
    bl print_string

    adrp x1, GV_numeroDoble
    add x1, x1, :lo12:GV_numeroDoble
    ldr x1, [x1]
    mov w0, #2
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

    // ===== Fin System.out.println =====

    mov x0, #0
    mov x8, #93
    svc #0
