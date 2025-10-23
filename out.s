    .section .data
    .align 3
L1:
    .asciz "=== SISTEMA DE CALCULO CIENTIFICO ===\n"

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
    .asciz "\n--- VALORES ASIGNADOS ---\n"

L5_end:

L6:
    .asciz "\n"

L6_end:

L7:
    .asciz "\n"

L7_end:

L8:
    .asciz "\n"

L8_end:

L9:
    .asciz "\n"

L9_end:

L10:
    .asciz "\n"

L10_end:

STRLIT_1:
    .asciz "=== SISTEMA DE CALCULO CIENTIFICO ==="

STRLIT_2:
    .asciz "Resultado"

STRLIT_3:
    .asciz "Calculadora Científica v1.0"

STRLIT_4:
    .asciz "Constante PI: "

STRLIT_5:
    .asciz "Constante máxima: "

STRLIT_6:
    .asciz "Nuevo resultado"

STRLIT_7:
    .asciz "\n--- VALORES ASIGNADOS ---"

STRLIT_8:
    .asciz "Entero: "

STRLIT_9:
    .asciz "Flotante: "

STRLIT_10:
    .asciz "Carácter: "

STRLIT_11:
    .asciz "Booleano: "

STRLIT_12:
    .asciz "Cadena: "

GV_numeroEntero: .quad 42

GV_numeroFlotante: .float 3.14

GV_numeroDoble: .double 2.718281828

GV_caracter: .byte 65

GV_esVerdadero: .quad 1

GV_cadenaTexto: .quad STRLIT_2

GV_PI: .quad 3

GV_CONSTANTE_MAXIMA: .quad 100

GV_MENSAJE_SISTEMA: .quad STRLIT_3

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
    .asciz "Resultado"

GV_cadenaTexto_str_end:

GV_PI_str:
    .asciz "3"

GV_PI_str_end:

GV_CONSTANTE_MAXIMA_str:
    .asciz "100"

GV_CONSTANTE_MAXIMA_str_end:

GV_MENSAJE_SISTEMA_str:
    .asciz "Calculadora Científica v1.0"

GV_MENSAJE_SISTEMA_str_end:

    .section .text
    .global _start
_start:
# interpret_map:
#   PRIMITIVO=0x5e0164f28acb
#   IDENTIFICADOR=0x5e0164f289ce
#   EXPRESION_LENGUAJE=0x5e0164f28338
#   LLAMADA_FUNCION=0x5e0164f30da0
#   LISTA_EXPRESIONES=0x5e0164f22304
#   CAST=0x5e0164f27ce3
#   UNARIO_LENGUAJE=0x5e0164f28798
#   BUILTIN_STRING_VALUEOF=0x5e0164f23969
#   PRINT_EXPR=0x5e0164f30529
# AST node: PRIMITIVO iptr=0x5e0164f28acb children=0
#   prim tipo=9 valor==== SISTEMA DE CALCULO CIENTIFICO ===
    adrp x0, STRLIT_1
    add x0, x0, :lo12:STRLIT_1
    mov x1, #1
    bl print_string

# AST node: IDENTIFICADOR iptr=0x5e0164f289ce children=0
#   id nombre=MENSAJE_SISTEMA
    adrp x0, GV_MENSAJE_SISTEMA
    add x0, x0, :lo12:GV_MENSAJE_SISTEMA
    // tipo tag=9
    mov x1, #9
    mov x2, #1
    bl print_any_gv

# AST node: EXPRESION_LENGUAJE iptr=0x5e0164f28338 children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x5e0164f28acb children=0
# #   prim tipo=9 valor=Constante PI: 
# # AST node: IDENTIFICADOR iptr=0x5e0164f289ce children=0
# #   id nombre=PI
    adrp x0, STRLIT_4
    add x0, x0, :lo12:STRLIT_4
    mov x1, #0
    bl print_string

    adrp x0, GV_PI
    add x0, x0, :lo12:GV_PI
    // tipo tag=5
    mov x1, #5
    mov x2, #1
    bl print_any_gv

# AST node: EXPRESION_LENGUAJE iptr=0x5e0164f28338 children=2
#   expresion tipo=-2076142960
# # AST node: PRIMITIVO iptr=0x5e0164f28acb children=0
# #   prim tipo=9 valor=Constante máxima: 
# # AST node: UNKNOWN iptr=0x5e0164f23969 children=0
    adrp x0, STRLIT_5
    add x0, x0, :lo12:STRLIT_5
    mov x1, #0
    bl print_string

    adrp x1, GV_CONSTANTE_MAXIMA
    add x1, x1, :lo12:GV_CONSTANTE_MAXIMA
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

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
    adrp x2, STRLIT_6
    add x2, x2, :lo12:STRLIT_6
    str x2, [x1]

# AST node: PRIMITIVO iptr=0x5e0164f28acb children=0
#   prim tipo=9 valor=\n--- VALORES ASIGNADOS ---
    adrp x0, STRLIT_7
    add x0, x0, :lo12:STRLIT_7
    mov x1, #1
    bl print_string

# AST node: EXPRESION_LENGUAJE iptr=0x5e0164f28338 children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x5e0164f28acb children=0
# #   prim tipo=9 valor=Entero: 
# # AST node: UNKNOWN iptr=0x5e0164f23969 children=0
    adrp x0, STRLIT_8
    add x0, x0, :lo12:STRLIT_8
    mov x1, #0
    bl print_string

    adrp x1, GV_numeroEntero
    add x1, x1, :lo12:GV_numeroEntero
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x5e0164f28338 children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x5e0164f28acb children=0
# #   prim tipo=9 valor=Flotante: 
# # AST node: UNKNOWN iptr=0x5e0164f23969 children=0
    adrp x0, STRLIT_9
    add x0, x0, :lo12:STRLIT_9
    mov x1, #0
    bl print_string

    adrp x1, GV_numeroFlotante
    add x1, x1, :lo12:GV_numeroFlotante
    ldr x1, [x1]
    mov w0, #3
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x5e0164f28338 children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x5e0164f28acb children=0
# #   prim tipo=9 valor=Carácter: 
# # AST node: IDENTIFICADOR iptr=0x5e0164f289ce children=0
# #   id nombre=caracter
    adrp x0, STRLIT_10
    add x0, x0, :lo12:STRLIT_10
    mov x1, #0
    bl print_string

    adrp x0, GV_caracter
    add x0, x0, :lo12:GV_caracter
    // tipo tag=2
    mov x1, #2
    mov x2, #1
    bl print_any_gv

# AST node: EXPRESION_LENGUAJE iptr=0x5e0164f28338 children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x5e0164f28acb children=0
# #   prim tipo=9 valor=Booleano: 
# # AST node: UNKNOWN iptr=0x5e0164f23969 children=0
    adrp x0, STRLIT_11
    add x0, x0, :lo12:STRLIT_11
    mov x1, #0
    bl print_string

    adrp x1, GV_esVerdadero
    add x1, x1, :lo12:GV_esVerdadero
    ldr x1, [x1]
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x5e0164f28338 children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x5e0164f28acb children=0
# #   prim tipo=9 valor=Cadena: 
# # AST node: IDENTIFICADOR iptr=0x5e0164f289ce children=0
# #   id nombre=cadenaTexto
    adrp x0, STRLIT_12
    add x0, x0, :lo12:STRLIT_12
    mov x1, #0
    bl print_string

    adrp x0, GV_cadenaTexto
    add x0, x0, :lo12:GV_cadenaTexto
    // tipo tag=9
    mov x1, #9
    mov x2, #1
    bl print_any_gv

    mov x0, #0
    mov x8, #93
    svc #0
