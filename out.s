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

L11:
    .asciz "\n--- OPERACIONES ARITMETICAS ---\n"

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

L15:
    .asciz "\n"

L15_end:

L16:
    .asciz "\n"

L16_end:

L17:
    .asciz "\n"

L17_end:

L18:
    .asciz "\n--- OPERACIONES RELACIONALES ---\n"

L18_end:

L19:
    .asciz "\n"

L19_end:

L20:
    .asciz "\n"

L20_end:

L21:
    .asciz "\n"

L21_end:

L22:
    .asciz "\n"

L22_end:

L23:
    .asciz "\n"

L23_end:

L24:
    .asciz "\n"

L24_end:

L25:
    .asciz "\n--- OPERACIONES LOGICAS ---\n"

L25_end:

L26:
    .asciz "\n"

L26_end:

L27:
    .asciz "\n"

L27_end:

L28:
    .asciz "\n"

L28_end:

L29:
    .asciz "\n"

L29_end:

L30:
    .asciz "\n"

L30_end:

L31:
    .asciz "\n"

L31_end:

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

STRLIT_13:
    .asciz "\n--- OPERACIONES ARITMETICAS ---"

STRLIT_14:
    .asciz "a = "

STRLIT_15:
    .asciz ", b = "

STRLIT_16:
    .asciz "Suma (a + b): "

STRLIT_17:
    .asciz "Resta (a - b): "

STRLIT_18:
    .asciz "Multiplicación (a * b): "

STRLIT_19:
    .asciz "División (a / b): "

STRLIT_20:
    .asciz "Módulo (a % b): "

STRLIT_21:
    .asciz "\n--- OPERACIONES RELACIONALES ---"

STRLIT_22:
    .asciz "a > b: "

STRLIT_23:
    .asciz "a < b: "

STRLIT_24:
    .asciz "a >= b: "

STRLIT_25:
    .asciz "a <= b: "

STRLIT_26:
    .asciz "a == b: "

STRLIT_27:
    .asciz "a != b: "

STRLIT_28:
    .asciz "\n--- OPERACIONES LOGICAS ---"

STRLIT_29:
    .asciz "condicion1 = "

STRLIT_30:
    .asciz "condicion2 = "

STRLIT_31:
    .asciz "condicion1 && condicion2: "

STRLIT_32:
    .asciz "condicion1 || condicion2: "

STRLIT_33:
    .asciz "!condicion1: "

STRLIT_34:
    .asciz "!condicion2: "

GV_numeroEntero: .quad 42

GV_numeroFlotante: .float 3.14

GV_numeroDoble: .double 2.718281828

GV_caracter: .byte 65

GV_esVerdadero: .quad 1

GV_cadenaTexto: .quad STRLIT_2

GV_PI: .quad 3

GV_CONSTANTE_MAXIMA: .quad 100

GV_MENSAJE_SISTEMA: .quad STRLIT_3

GV_a: .quad 25

GV_b: .quad 7

GV_condicion1: .quad 1

GV_condicion2: .quad 0

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

GV_a_str:
    .asciz "25"

GV_a_str_end:

GV_b_str:
    .asciz "7"

GV_b_str_end:

GV_condicion1_str:
    .asciz "1"

GV_condicion1_str_end:

GV_condicion2_str:
    .asciz "0"

GV_condicion2_str_end:

    .section .text
    .global _start
_start:
# interpret_map:
#   PRIMITIVO=0x561e2ecee26d
#   IDENTIFICADOR=0x561e2ecee170
#   EXPRESION_LENGUAJE=0x561e2ecedada
#   LLAMADA_FUNCION=0x561e2ecf6542
#   LISTA_EXPRESIONES=0x561e2ece7aa6
#   CAST=0x561e2eced485
#   UNARIO_LENGUAJE=0x561e2ecedf3a
#   BUILTIN_STRING_VALUEOF=0x561e2ece910b
#   PRINT_EXPR=0x561e2ecf5ccb
# AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
#   prim tipo=9 valor==== SISTEMA DE CALCULO CIENTIFICO ===
    adrp x0, STRLIT_1
    add x0, x0, :lo12:STRLIT_1
    mov x1, #1
    bl print_string

# AST node: IDENTIFICADOR iptr=0x561e2ecee170 children=0
#   id nombre=MENSAJE_SISTEMA
    adrp x0, GV_MENSAJE_SISTEMA
    add x0, x0, :lo12:GV_MENSAJE_SISTEMA
    // tipo tag=9
    mov x1, #9
    mov x2, #1
    bl print_any_gv

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Constante PI: 
# # AST node: IDENTIFICADOR iptr=0x561e2ecee170 children=0
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

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=1505493648
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Constante máxima: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
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

# AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
#   prim tipo=9 valor=\n--- VALORES ASIGNADOS ---
    adrp x0, STRLIT_7
    add x0, x0, :lo12:STRLIT_7
    mov x1, #1
    bl print_string

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Entero: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
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

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Flotante: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
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

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Carácter: 
# # AST node: IDENTIFICADOR iptr=0x561e2ecee170 children=0
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

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Booleano: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
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

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Cadena: 
# # AST node: IDENTIFICADOR iptr=0x561e2ecee170 children=0
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

# AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
#   prim tipo=9 valor=\n--- OPERACIONES ARITMETICAS ---
    adrp x0, STRLIT_13
    add x0, x0, :lo12:STRLIT_13
    mov x1, #1
    bl print_string

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
# #   expresion tipo=0
# # # AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
# # #   expresion tipo=0
# # # # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# # # #   prim tipo=9 valor=a = 
# # # # AST node: UNKNOWN iptr=0x561e2ece910b children=0
# # # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# # #   prim tipo=9 valor=, b = 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_14
    add x0, x0, :lo12:STRLIT_14
    mov x1, #0
    bl print_string

    adrp x1, GV_a
    add x1, x1, :lo12:GV_a
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #0
    bl print_string
    mov x0, x9
    bl free

    adrp x0, STRLIT_15
    add x0, x0, :lo12:STRLIT_15
    mov x1, #0
    bl print_string

    adrp x1, GV_b
    add x1, x1, :lo12:GV_b
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Suma (a + b): 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_16
    add x0, x0, :lo12:STRLIT_16
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    add x1, x9, x10
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Resta (a - b): 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_17
    add x0, x0, :lo12:STRLIT_17
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    sub x1, x9, x10
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Multiplicación (a * b): 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_18
    add x0, x0, :lo12:STRLIT_18
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    mul x1, x9, x10
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=División (a / b): 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_19
    add x0, x0, :lo12:STRLIT_19
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    mov x0, x9
    mov x1, x10
    bl div_helper
    mov x1, x0
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=Módulo (a % b): 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_20
    add x0, x0, :lo12:STRLIT_20
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    mov x0, x9
    mov x1, x10
    bl mod_helper
    mov x1, x0
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
#   prim tipo=9 valor=\n--- OPERACIONES RELACIONALES ---
    adrp x0, STRLIT_21
    add x0, x0, :lo12:STRLIT_21
    mov x1, #1
    bl print_string

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=a > b: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_22
    add x0, x0, :lo12:STRLIT_22
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    cmp x9, x10
    cset x1, gt
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=a < b: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_23
    add x0, x0, :lo12:STRLIT_23
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    cmp x9, x10
    cset x1, lt
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=a >= b: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_24
    add x0, x0, :lo12:STRLIT_24
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    cmp x9, x10
    cset x1, ge
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=a <= b: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_25
    add x0, x0, :lo12:STRLIT_25
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    cmp x9, x10
    cset x1, le
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=a == b: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_26
    add x0, x0, :lo12:STRLIT_26
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    cmp x9, x10
    cset x1, eq
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=a != b: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_27
    add x0, x0, :lo12:STRLIT_27
    mov x1, #0
    bl print_string

    adrp x9, GV_a
    add x9, x9, :lo12:GV_a
    ldr x9, [x9]
    adrp x10, GV_b
    add x10, x10, :lo12:GV_b
    ldr x10, [x10]
    cmp x9, x10
    cset x1, ne
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
#   prim tipo=9 valor=\n--- OPERACIONES LOGICAS ---
    adrp x0, STRLIT_28
    add x0, x0, :lo12:STRLIT_28
    mov x1, #1
    bl print_string

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=condicion1 = 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_29
    add x0, x0, :lo12:STRLIT_29
    mov x1, #0
    bl print_string

    adrp x1, GV_condicion1
    add x1, x1, :lo12:GV_condicion1
    ldr x1, [x1]
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=condicion2 = 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_30
    add x0, x0, :lo12:STRLIT_30
    mov x1, #0
    bl print_string

    adrp x1, GV_condicion2
    add x1, x1, :lo12:GV_condicion2
    ldr x1, [x1]
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=condicion1 && condicion2: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_31
    add x0, x0, :lo12:STRLIT_31
    mov x1, #0
    bl print_string

    adrp x9, GV_condicion1
    add x9, x9, :lo12:GV_condicion1
    ldr x9, [x9]
    adrp x10, GV_condicion2
    add x10, x10, :lo12:GV_condicion2
    ldr x10, [x10]
    cmp x9, #0
    csel x1, xzr, x10, eq
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=condicion1 || condicion2: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_32
    add x0, x0, :lo12:STRLIT_32
    mov x1, #0
    bl print_string

    adrp x9, GV_condicion1
    add x9, x9, :lo12:GV_condicion1
    ldr x9, [x9]
    adrp x10, GV_condicion2
    add x10, x10, :lo12:GV_condicion2
    ldr x10, [x10]
    cmp x9, #0
    cset x1, ne
    cmp x9, #0
    csel x1, x1, x10, ne
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=!condicion1: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_33
    add x0, x0, :lo12:STRLIT_33
    mov x1, #0
    bl print_string

    adrp x9, GV_condicion1
    add x9, x9, :lo12:GV_condicion1
    ldr x9, [x9]
    cmp x9, #0
    cset x1, eq
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

# AST node: EXPRESION_LENGUAJE iptr=0x561e2ecedada children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x561e2ecee26d children=0
# #   prim tipo=9 valor=!condicion2: 
# # AST node: UNKNOWN iptr=0x561e2ece910b children=0
    adrp x0, STRLIT_34
    add x0, x0, :lo12:STRLIT_34
    mov x1, #0
    bl print_string

    adrp x9, GV_condicion2
    add x9, x9, :lo12:GV_condicion2
    ldr x9, [x9]
    cmp x9, #0
    cset x1, eq
    mov w0, #4
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #1
    bl print_string
    mov x0, x9
    bl free

    mov x0, #0
    mov x8, #93
    svc #0
