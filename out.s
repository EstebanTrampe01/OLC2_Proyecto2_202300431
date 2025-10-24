    .section .data
    .align 3
L1:
    .asciz "=== SISTEMA DE GESTION DE NOTAS INDIVIDUAL ===\n"

L1_end:

L2:
    .asciz "Procesando 5 estudiantes individuales\n"

L2_end:

L3:
    .asciz "\n--- EVALUACION CON IF/ELSE ---\n"

L3_end:

L4:
    .asciz "\n"

L4_end:

L5:
    .asciz "Clasificacion: SOBRESALIENTE\n"

L5_end:

L6:
    .asciz "Clasificacion: NOTABLE\n"

L6_end:

L7:
    .asciz "Clasificacion: BIEN\n"

L7_end:

L8:
    .asciz "Clasificacion: SUFICIENTE\n"

L8_end:

L9:
    .asciz "Clasificacion: INSUFICIENTE\n"

L9_end:

L10:
    .asciz "Estado: Mayor de edad completa\n"

L10_end:

L11:
    .asciz "Resultado: Apto para beca\n"

L11_end:

L12:
    .asciz "Resultado: No apto para beca\n"

L12_end:

L13:
    .asciz "\n"

L13_end:

L14:
    .asciz "Clasificacion: SOBRESALIENTE\n"

L14_end:

L15:
    .asciz "Clasificacion: NOTABLE\n"

L15_end:

L16:
    .asciz "Clasificacion: REGULAR\n"

L16_end:

L17:
    .asciz "Resultado: Apto para beca\n"

L17_end:

L18:
    .asciz "Resultado: No apto para beca\n"

L18_end:

L19:
    .asciz "\n"

L19_end:

L20:
    .asciz "Clasificacion: NOTABLE\n"

L20_end:

L21:
    .asciz "Clasificacion: BIEN\n"

L21_end:

L22:
    .asciz "Clasificacion: REGULAR\n"

L22_end:

L23:
    .asciz "\n--- PROCESAMIENTO CON WHILE ---\n"

L23_end:

L24:
    .asciz "Buscando estudiantes con nota >= 90:\n"

L24_end:

L25:
    .asciz "\n"

L25_end:

L26:
    .asciz "\n"

L26_end:

L27:
    .asciz "\n"

L27_end:

L28:
    .asciz "\nContador regresivo:\n"

L28_end:

L29:
    .asciz "\n"

L29_end:

L30:
    .asciz "\nBusqueda de estudiante joven con buena nota:\n"

L30_end:

L31:
    .asciz "\n"

L31_end:

STRLIT_1:
    .asciz "=== SISTEMA DE GESTION DE NOTAS INDIVIDUAL ==="

STRLIT_2:
    .asciz "Ana"

STRLIT_3:
    .asciz "Luis"

STRLIT_4:
    .asciz "Maria"

STRLIT_5:
    .asciz "Carlos"

STRLIT_6:
    .asciz "Sofia"

STRLIT_7:
    .asciz "Procesando 5 estudiantes individuales"

STRLIT_8:
    .asciz "\n--- EVALUACION CON IF/ELSE ---"

STRLIT_9:
    .asciz "Evaluando: "

STRLIT_10:
    .asciz "Clasificacion: SOBRESALIENTE"

STRLIT_11:
    .asciz "Clasificacion: NOTABLE"

STRLIT_12:
    .asciz "Clasificacion: BIEN"

STRLIT_13:
    .asciz "Clasificacion: SUFICIENTE"

STRLIT_14:
    .asciz "Clasificacion: INSUFICIENTE"

STRLIT_15:
    .asciz "Estado: Mayor de edad completa"

STRLIT_16:
    .asciz "Resultado: Apto para beca"

STRLIT_17:
    .asciz "Resultado: No apto para beca"

STRLIT_18:
    .asciz "\nEvaluando: "

STRLIT_19:
    .asciz "Clasificacion: REGULAR"

STRLIT_20:
    .asciz "\n--- PROCESAMIENTO CON WHILE ---"

STRLIT_21:
    .asciz "Buscando estudiantes con nota >= 90:"

STRLIT_22:
    .asciz ""

STRLIT_23:
    .asciz "Revisando estudiante "

STRLIT_24:
    .asciz ": "

STRLIT_25:
    .asciz "Destacado encontrado: "

STRLIT_26:
    .asciz " con "

STRLIT_27:
    .asciz "Total de estudiantes destacados: "

STRLIT_28:
    .asciz "\nContador regresivo:"

STRLIT_29:
    .asciz "Quedan: "

STRLIT_30:
    .asciz " estudiantes por procesar"

STRLIT_31:
    .asciz "\nBusqueda de estudiante joven con buena nota:"

STRLIT_32:
    .asciz "Estudiante joven destacado: "

STRLIT_33:
    .asciz " (Edad: "

STRLIT_34:
    .asciz ", Nota: "

STRLIT_35:
    .asciz ")"

GV_estudiante1: .quad STRLIT_2

GV_estudiante2: .quad STRLIT_3

GV_estudiante3: .quad STRLIT_4

GV_estudiante4: .quad STRLIT_5

GV_estudiante5: .quad STRLIT_6

GV_nota1: .quad 85

GV_nota2: .quad 92

GV_nota3: .quad 78

GV_nota4: .quad 95

GV_nota5: .quad 88

GV_edad1: .quad 20

GV_edad2: .quad 19

GV_edad3: .quad 21

GV_edad4: .quad 20

GV_edad5: .quad 22

GV_estudianteActual: .quad 1

GV_estudiantesDestacados: .quad 0

GV_nombreActual: .quad STRLIT_22

GV_notaActual: .quad 0

GV_contador: .quad 5

GV_indice: .quad 1

GV_nombre: .quad STRLIT_22

GV_nota: .quad 0

GV_edad: .quad 0

GV_estudiante1_str:
    .asciz "Ana"

GV_estudiante1_str_end:

GV_estudiante2_str:
    .asciz "Luis"

GV_estudiante2_str_end:

GV_estudiante3_str:
    .asciz "Maria"

GV_estudiante3_str_end:

GV_estudiante4_str:
    .asciz "Carlos"

GV_estudiante4_str_end:

GV_estudiante5_str:
    .asciz "Sofia"

GV_estudiante5_str_end:

GV_nota1_str:
    .asciz "85"

GV_nota1_str_end:

GV_nota2_str:
    .asciz "92"

GV_nota2_str_end:

GV_nota3_str:
    .asciz "78"

GV_nota3_str_end:

GV_nota4_str:
    .asciz "95"

GV_nota4_str_end:

GV_nota5_str:
    .asciz "88"

GV_nota5_str_end:

GV_edad1_str:
    .asciz "20"

GV_edad1_str_end:

GV_edad2_str:
    .asciz "19"

GV_edad2_str_end:

GV_edad3_str:
    .asciz "21"

GV_edad3_str_end:

GV_edad4_str:
    .asciz "20"

GV_edad4_str_end:

GV_edad5_str:
    .asciz "22"

GV_edad5_str_end:

GV_estudianteActual_str:
    .asciz "1"

GV_estudianteActual_str_end:

GV_estudiantesDestacados_str:
    .asciz "0"

GV_estudiantesDestacados_str_end:

GV_nombreActual_str:
    .asciz ""

GV_nombreActual_str_end:

GV_notaActual_str:
    .asciz "0"

GV_notaActual_str_end:

GV_contador_str:
    .asciz "5"

GV_contador_str_end:

GV_indice_str:
    .asciz "1"

GV_indice_str_end:

GV_nombre_str:
    .asciz ""

GV_nombre_str_end:

GV_nota_str:
    .asciz "0"

GV_nota_str_end:

GV_edad_str:
    .asciz "0"

GV_edad_str_end:

    .section .text
    .global _start
_start:
    // Inicializar pila para operaciones complejas
    mov x0, sp
    sub sp, sp, #1024
    // ===== System.out.println =====
# interpret_map:
#   PRIMITIVO=0x57ece99279ce
#   IDENTIFICADOR=0x57ece99278d1
#   EXPRESION_LENGUAJE=0x57ece992723b
#   LLAMADA_FUNCION=0x57ece992fca3
#   LISTA_EXPRESIONES=0x57ece9921207
#   CAST=0x57ece9926be6
#   UNARIO_LENGUAJE=0x57ece992769b
#   BUILTIN_STRING_VALUEOF=0x57ece992286c
#   PRINT_EXPR=0x57ece992f42c
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor==== SISTEMA DE GESTION DE NOTAS INDIVIDUAL ===
    // Imprimir string literal '=== SISTEMA DE GESTION DE NOTAS INDIVIDUAL ==='
    adrp x0, STRLIT_1
    add x0, x0, :lo12:STRLIT_1
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Procesando 5 estudiantes individuales
    // Imprimir string literal 'Procesando 5 estudiantes individuales'
    adrp x0, STRLIT_7
    add x0, x0, :lo12:STRLIT_7
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=\n--- EVALUACION CON IF/ELSE ---
    // Imprimir string literal '\n--- EVALUACION CON IF/ELSE ---'
    adrp x0, STRLIT_8
    add x0, x0, :lo12:STRLIT_8
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
#   expresion tipo=659906400
# # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# #   prim tipo=9 valor=Evaluando: 
# # AST node: IDENTIFICADOR iptr=0x57ece99278d1 children=0
# #   id nombre=estudiante1
    // Imprimir string literal 'Evaluando: '
    adrp x0, STRLIT_9
    add x0, x0, :lo12:STRLIT_9
    mov x1, #0
    bl print_string

    // Imprimir variable global 'estudiante1'
    adrp x0, GV_estudiante1
    add x0, x0, :lo12:GV_estudiante1
    // tipo tag=9
    mov x1, #9
    mov x2, #1
    bl print_any_gv

    // ===== Fin System.out.println =====

    // IF statement
    // Cargar entero literal 95 en registro x8
    mov x8, #95
    str x8, [sp, #-16]!
    // Cargar variable global 'nota1' en registro x9
    adrp x9, GV_nota1
    add x9, x9, :lo12:GV_nota1
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_0
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: SOBRESALIENTE
    // Imprimir string literal 'Clasificacion: SOBRESALIENTE'
    adrp x0, STRLIT_10
    add x0, x0, :lo12:STRLIT_10
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_1
else_0:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 85 en registro x8
    mov x8, #85
    str x8, [sp, #-16]!
    // Cargar variable global 'nota1' en registro x9
    adrp x9, GV_nota1
    add x9, x9, :lo12:GV_nota1
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_2
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: NOTABLE
    // Imprimir string literal 'Clasificacion: NOTABLE'
    adrp x0, STRLIT_11
    add x0, x0, :lo12:STRLIT_11
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_3
else_2:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 75 en registro x8
    mov x8, #75
    str x8, [sp, #-16]!
    // Cargar variable global 'nota1' en registro x9
    adrp x9, GV_nota1
    add x9, x9, :lo12:GV_nota1
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_4
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: BIEN
    // Imprimir string literal 'Clasificacion: BIEN'
    adrp x0, STRLIT_12
    add x0, x0, :lo12:STRLIT_12
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_5
else_4:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 65 en registro x8
    mov x8, #65
    str x8, [sp, #-16]!
    // Cargar variable global 'nota1' en registro x9
    adrp x9, GV_nota1
    add x9, x9, :lo12:GV_nota1
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_6
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: SUFICIENTE
    // Imprimir string literal 'Clasificacion: SUFICIENTE'
    adrp x0, STRLIT_13
    add x0, x0, :lo12:STRLIT_13
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_7
else_6:
    // Bloque ELSE
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: INSUFICIENTE
    // Imprimir string literal 'Clasificacion: INSUFICIENTE'
    adrp x0, STRLIT_14
    add x0, x0, :lo12:STRLIT_14
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

endif_7:
    // Fin IF
endif_5:
    // Fin IF
endif_3:
    // Fin IF
endif_1:
    // Fin IF
    // IF statement
    // Cargar entero literal 21 en registro x8
    mov x8, #21
    str x8, [sp, #-16]!
    // Cargar variable global 'edad1' en registro x9
    adrp x9, GV_edad1
    add x9, x9, :lo12:GV_edad1
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq endif_9
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Estado: Mayor de edad completa
    // Imprimir string literal 'Estado: Mayor de edad completa'
    adrp x0, STRLIT_15
    add x0, x0, :lo12:STRLIT_15
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

endif_9:
    // Fin IF
    // IF statement
    // Cargar entero literal 90 en registro x8
    mov x8, #90
    str x8, [sp, #-16]!
    // Cargar variable global 'nota1' en registro x9
    adrp x9, GV_nota1
    add x9, x9, :lo12:GV_nota1
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_10
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Resultado: Apto para beca
    // Imprimir string literal 'Resultado: Apto para beca'
    adrp x0, STRLIT_16
    add x0, x0, :lo12:STRLIT_16
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_11
else_10:
    // Bloque ELSE
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Resultado: No apto para beca
    // Imprimir string literal 'Resultado: No apto para beca'
    adrp x0, STRLIT_17
    add x0, x0, :lo12:STRLIT_17
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

endif_11:
    // Fin IF
    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# #   prim tipo=9 valor=\nEvaluando: 
# # AST node: IDENTIFICADOR iptr=0x57ece99278d1 children=0
# #   id nombre=estudiante2
    // Imprimir string literal '\nEvaluando: '
    adrp x0, STRLIT_18
    add x0, x0, :lo12:STRLIT_18
    mov x1, #0
    bl print_string

    // Imprimir variable global 'estudiante2'
    adrp x0, GV_estudiante2
    add x0, x0, :lo12:GV_estudiante2
    // tipo tag=9
    mov x1, #9
    mov x2, #1
    bl print_any_gv

    // ===== Fin System.out.println =====

    // IF statement
    // Cargar entero literal 95 en registro x8
    mov x8, #95
    str x8, [sp, #-16]!
    // Cargar variable global 'nota2' en registro x9
    adrp x9, GV_nota2
    add x9, x9, :lo12:GV_nota2
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_12
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: SOBRESALIENTE
    // Imprimir string literal 'Clasificacion: SOBRESALIENTE'
    adrp x0, STRLIT_10
    add x0, x0, :lo12:STRLIT_10
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_13
else_12:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 85 en registro x8
    mov x8, #85
    str x8, [sp, #-16]!
    // Cargar variable global 'nota2' en registro x9
    adrp x9, GV_nota2
    add x9, x9, :lo12:GV_nota2
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_14
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: NOTABLE
    // Imprimir string literal 'Clasificacion: NOTABLE'
    adrp x0, STRLIT_11
    add x0, x0, :lo12:STRLIT_11
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_15
else_14:
    // Bloque ELSE
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: REGULAR
    // Imprimir string literal 'Clasificacion: REGULAR'
    adrp x0, STRLIT_19
    add x0, x0, :lo12:STRLIT_19
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

endif_15:
    // Fin IF
endif_13:
    // Fin IF
    // IF statement
    // Cargar entero literal 90 en registro x8
    mov x8, #90
    str x8, [sp, #-16]!
    // Cargar variable global 'nota2' en registro x9
    adrp x9, GV_nota2
    add x9, x9, :lo12:GV_nota2
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_16
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Resultado: Apto para beca
    // Imprimir string literal 'Resultado: Apto para beca'
    adrp x0, STRLIT_16
    add x0, x0, :lo12:STRLIT_16
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_17
else_16:
    // Bloque ELSE
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Resultado: No apto para beca
    // Imprimir string literal 'Resultado: No apto para beca'
    adrp x0, STRLIT_17
    add x0, x0, :lo12:STRLIT_17
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

endif_17:
    // Fin IF
    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# #   prim tipo=9 valor=\nEvaluando: 
# # AST node: IDENTIFICADOR iptr=0x57ece99278d1 children=0
# #   id nombre=estudiante3
    // Imprimir string literal '\nEvaluando: '
    adrp x0, STRLIT_18
    add x0, x0, :lo12:STRLIT_18
    mov x1, #0
    bl print_string

    // Imprimir variable global 'estudiante3'
    adrp x0, GV_estudiante3
    add x0, x0, :lo12:GV_estudiante3
    // tipo tag=9
    mov x1, #9
    mov x2, #1
    bl print_any_gv

    // ===== Fin System.out.println =====

    // IF statement
    // Cargar entero literal 85 en registro x8
    mov x8, #85
    str x8, [sp, #-16]!
    // Cargar variable global 'nota3' en registro x9
    adrp x9, GV_nota3
    add x9, x9, :lo12:GV_nota3
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_18
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: NOTABLE
    // Imprimir string literal 'Clasificacion: NOTABLE'
    adrp x0, STRLIT_11
    add x0, x0, :lo12:STRLIT_11
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_19
else_18:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 75 en registro x8
    mov x8, #75
    str x8, [sp, #-16]!
    // Cargar variable global 'nota3' en registro x9
    adrp x9, GV_nota3
    add x9, x9, :lo12:GV_nota3
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq else_20
    // Bloque IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: BIEN
    // Imprimir string literal 'Clasificacion: BIEN'
    adrp x0, STRLIT_12
    add x0, x0, :lo12:STRLIT_12
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    b endif_21
else_20:
    // Bloque ELSE
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Clasificacion: REGULAR
    // Imprimir string literal 'Clasificacion: REGULAR'
    adrp x0, STRLIT_19
    add x0, x0, :lo12:STRLIT_19
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

endif_21:
    // Fin IF
endif_19:
    // Fin IF
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=\n--- PROCESAMIENTO CON WHILE ---
    // Imprimir string literal '\n--- PROCESAMIENTO CON WHILE ---'
    adrp x0, STRLIT_20
    add x0, x0, :lo12:STRLIT_20
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=Buscando estudiantes con nota >= 90:
    // Imprimir string literal 'Buscando estudiantes con nota >= 90:'
    adrp x0, STRLIT_21
    add x0, x0, :lo12:STRLIT_21
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    // WHILE statement
while_loop_22:
    // Cargar entero literal 5 en registro x8
    mov x8, #5
    str x8, [sp, #-16]!
    // Cargar variable global 'estudianteActual' en registro x9
    adrp x9, GV_estudianteActual
    add x9, x9, :lo12:GV_estudianteActual
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MENOR O IGUAL: comparar x9 <= x8
    cmp x9, x8
    cset x9, le
    cmp x9, #0
    b.eq while_end_23
    // Bloque WHILE
    // IF statement
    // Cargar entero literal 1 en registro x8
    mov x8, #1
    str x8, [sp, #-16]!
    // Cargar variable global 'estudianteActual' en registro x9
    adrp x9, GV_estudianteActual
    add x9, x9, :lo12:GV_estudianteActual
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq else_24
    // Bloque IF
    // Asignar identificador 'estudiante1' a variable 'nombreActual'
    adrp x1, GV_estudiante1
    add x1, x1, :lo12:GV_estudiante1
    ldr x2, [x1]
    adrp x3, GV_nombreActual
    add x3, x3, :lo12:GV_nombreActual
    str x2, [x3]

    // Asignar identificador 'nota1' a variable 'notaActual'
    adrp x1, GV_nota1
    add x1, x1, :lo12:GV_nota1
    ldr x2, [x1]
    adrp x3, GV_notaActual
    add x3, x3, :lo12:GV_notaActual
    str x2, [x3]

    b endif_25
else_24:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 2 en registro x8
    mov x8, #2
    str x8, [sp, #-16]!
    // Cargar variable global 'estudianteActual' en registro x9
    adrp x9, GV_estudianteActual
    add x9, x9, :lo12:GV_estudianteActual
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq else_26
    // Bloque IF
    // Asignar identificador 'estudiante2' a variable 'nombreActual'
    adrp x1, GV_estudiante2
    add x1, x1, :lo12:GV_estudiante2
    ldr x2, [x1]
    adrp x3, GV_nombreActual
    add x3, x3, :lo12:GV_nombreActual
    str x2, [x3]

    // Asignar identificador 'nota2' a variable 'notaActual'
    adrp x1, GV_nota2
    add x1, x1, :lo12:GV_nota2
    ldr x2, [x1]
    adrp x3, GV_notaActual
    add x3, x3, :lo12:GV_notaActual
    str x2, [x3]

    b endif_27
else_26:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 3 en registro x8
    mov x8, #3
    str x8, [sp, #-16]!
    // Cargar variable global 'estudianteActual' en registro x9
    adrp x9, GV_estudianteActual
    add x9, x9, :lo12:GV_estudianteActual
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq else_28
    // Bloque IF
    // Asignar identificador 'estudiante3' a variable 'nombreActual'
    adrp x1, GV_estudiante3
    add x1, x1, :lo12:GV_estudiante3
    ldr x2, [x1]
    adrp x3, GV_nombreActual
    add x3, x3, :lo12:GV_nombreActual
    str x2, [x3]

    // Asignar identificador 'nota3' a variable 'notaActual'
    adrp x1, GV_nota3
    add x1, x1, :lo12:GV_nota3
    ldr x2, [x1]
    adrp x3, GV_notaActual
    add x3, x3, :lo12:GV_notaActual
    str x2, [x3]

    b endif_29
else_28:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 4 en registro x8
    mov x8, #4
    str x8, [sp, #-16]!
    // Cargar variable global 'estudianteActual' en registro x9
    adrp x9, GV_estudianteActual
    add x9, x9, :lo12:GV_estudianteActual
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq else_30
    // Bloque IF
    // Asignar identificador 'estudiante4' a variable 'nombreActual'
    adrp x1, GV_estudiante4
    add x1, x1, :lo12:GV_estudiante4
    ldr x2, [x1]
    adrp x3, GV_nombreActual
    add x3, x3, :lo12:GV_nombreActual
    str x2, [x3]

    // Asignar identificador 'nota4' a variable 'notaActual'
    adrp x1, GV_nota4
    add x1, x1, :lo12:GV_nota4
    ldr x2, [x1]
    adrp x3, GV_notaActual
    add x3, x3, :lo12:GV_notaActual
    str x2, [x3]

    b endif_31
else_30:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 5 en registro x8
    mov x8, #5
    str x8, [sp, #-16]!
    // Cargar variable global 'estudianteActual' en registro x9
    adrp x9, GV_estudianteActual
    add x9, x9, :lo12:GV_estudianteActual
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq endif_33
    // Bloque IF
    // Asignar identificador 'estudiante5' a variable 'nombreActual'
    adrp x1, GV_estudiante5
    add x1, x1, :lo12:GV_estudiante5
    ldr x2, [x1]
    adrp x3, GV_nombreActual
    add x3, x3, :lo12:GV_nombreActual
    str x2, [x3]

    // Asignar identificador 'nota5' a variable 'notaActual'
    adrp x1, GV_nota5
    add x1, x1, :lo12:GV_nota5
    ldr x2, [x1]
    adrp x3, GV_notaActual
    add x3, x3, :lo12:GV_notaActual
    str x2, [x3]

endif_33:
    // Fin IF
endif_31:
    // Fin IF
endif_29:
    // Fin IF
endif_27:
    // Fin IF
endif_25:
    // Fin IF
    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
#   expresion tipo=0
# # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# #   expresion tipo=0
# # # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# # #   expresion tipo=0
# # # # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# # # #   prim tipo=9 valor=Revisando estudiante 
# # # # AST node: UNKNOWN iptr=0x57ece992286c children=0
# # # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# # #   prim tipo=9 valor=: 
# # AST node: IDENTIFICADOR iptr=0x57ece99278d1 children=0
# #   id nombre=nombreActual
    // Imprimir string literal 'Revisando estudiante '
    adrp x0, STRLIT_23
    add x0, x0, :lo12:STRLIT_23
    mov x1, #0
    bl print_string

    adrp x1, GV_estudianteActual
    add x1, x1, :lo12:GV_estudianteActual
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #0
    bl print_string
    mov x0, x9
    bl free

    // Imprimir string literal ': '
    adrp x0, STRLIT_24
    add x0, x0, :lo12:STRLIT_24
    mov x1, #0
    bl print_string

    // Imprimir variable global 'nombreActual'
    adrp x0, GV_nombreActual
    add x0, x0, :lo12:GV_nombreActual
    // tipo tag=9
    mov x1, #9
    mov x2, #1
    bl print_any_gv

    // ===== Fin System.out.println =====

    // IF statement
    // Cargar entero literal 90 en registro x8
    mov x8, #90
    str x8, [sp, #-16]!
    // Cargar variable global 'notaActual' en registro x9
    adrp x9, GV_notaActual
    add x9, x9, :lo12:GV_notaActual
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    cmp x9, #0
    b.eq endif_35
    // Bloque IF
    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
#   expresion tipo=0
# # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# #   expresion tipo=0
# # # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# # #   expresion tipo=0
# # # # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# # # #   prim tipo=9 valor=Destacado encontrado: 
# # # # AST node: IDENTIFICADOR iptr=0x57ece99278d1 children=0
# # # #   id nombre=nombreActual
# # # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# # #   prim tipo=9 valor= con 
# # AST node: UNKNOWN iptr=0x57ece992286c children=0
    // Imprimir string literal 'Destacado encontrado: '
    adrp x0, STRLIT_25
    add x0, x0, :lo12:STRLIT_25
    mov x1, #0
    bl print_string

    // Imprimir variable global 'nombreActual'
    adrp x0, GV_nombreActual
    add x0, x0, :lo12:GV_nombreActual
    // tipo tag=9
    mov x1, #9
    mov x2, #0
    bl print_any_gv

    // Imprimir string literal ' con '
    adrp x0, STRLIT_26
    add x0, x0, :lo12:STRLIT_26
    mov x1, #0
    bl print_string

    adrp x1, GV_notaActual
    add x1, x1, :lo12:GV_notaActual
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

    // Evaluar expresión compleja para 'estudiantesDestacados'
    adrp x11, GV_estudiantesDestacados
    add x11, x11, :lo12:GV_estudiantesDestacados
    // Cargar entero literal 1 en registro x8
    mov x8, #1
    str x8, [sp, #-16]!
    // Cargar variable global 'estudiantesDestacados' en registro x9
    adrp x9, GV_estudiantesDestacados
    add x9, x9, :lo12:GV_estudiantesDestacados
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación SUMA de enteros
    add x2, x9, x8
    str x2, [x11]

endif_35:
    // Fin IF
    // Evaluar expresión compleja para 'estudianteActual'
    adrp x11, GV_estudianteActual
    add x11, x11, :lo12:GV_estudianteActual
    // Cargar entero literal 1 en registro x8
    mov x8, #1
    str x8, [sp, #-16]!
    // Cargar variable global 'estudianteActual' en registro x9
    adrp x9, GV_estudianteActual
    add x9, x9, :lo12:GV_estudianteActual
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación SUMA de enteros
    add x2, x9, x8
    str x2, [x11]

    b while_loop_22
while_end_23:
    // Fin WHILE
    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
#   expresion tipo=0
# # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# #   prim tipo=9 valor=Total de estudiantes destacados: 
# # AST node: UNKNOWN iptr=0x57ece992286c children=0
    // Imprimir string literal 'Total de estudiantes destacados: '
    adrp x0, STRLIT_27
    add x0, x0, :lo12:STRLIT_27
    mov x1, #0
    bl print_string

    adrp x1, GV_estudiantesDestacados
    add x1, x1, :lo12:GV_estudiantesDestacados
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
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=\nContador regresivo:
    // Imprimir string literal '\nContador regresivo:'
    adrp x0, STRLIT_28
    add x0, x0, :lo12:STRLIT_28
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    // WHILE statement
while_loop_36:
    // Cargar entero literal 0 en registro x8
    mov x8, #0
    str x8, [sp, #-16]!
    // Cargar variable global 'contador' en registro x9
    adrp x9, GV_contador
    add x9, x9, :lo12:GV_contador
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR QUE: comparar x9 > x8
    cmp x9, x8
    cset x9, gt
    cmp x9, #0
    b.eq while_end_37
    // Bloque WHILE
    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
#   expresion tipo=0
# # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# #   expresion tipo=0
# # # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# # #   prim tipo=9 valor=Quedan: 
# # # AST node: UNKNOWN iptr=0x57ece992286c children=0
# # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# #   prim tipo=9 valor= estudiantes por procesar
    // Imprimir string literal 'Quedan: '
    adrp x0, STRLIT_29
    add x0, x0, :lo12:STRLIT_29
    mov x1, #0
    bl print_string

    adrp x1, GV_contador
    add x1, x1, :lo12:GV_contador
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #0
    bl print_string
    mov x0, x9
    bl free

    // Imprimir string literal ' estudiantes por procesar'
    adrp x0, STRLIT_30
    add x0, x0, :lo12:STRLIT_30
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    // Evaluar expresión compleja para 'contador'
    adrp x11, GV_contador
    add x11, x11, :lo12:GV_contador
    // Cargar entero literal 1 en registro x8
    mov x8, #1
    str x8, [sp, #-16]!
    // Cargar variable global 'contador' en registro x9
    adrp x9, GV_contador
    add x9, x9, :lo12:GV_contador
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación RESTA de enteros
    sub x2, x9, x8
    str x2, [x11]

    b while_loop_36
while_end_37:
    // Fin WHILE
    // ===== System.out.println =====
# AST node: PRIMITIVO iptr=0x57ece99279ce children=0
#   prim tipo=9 valor=\nBusqueda de estudiante joven con buena nota:
    // Imprimir string literal '\nBusqueda de estudiante joven con buena nota:'
    adrp x0, STRLIT_31
    add x0, x0, :lo12:STRLIT_31
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

    // WHILE statement
while_loop_38:
    // Cargar entero literal 0 en registro x8
    mov x8, #0
    str x8, [sp, #-16]!
    // Cargar variable global 'estudiantesDestacados' en registro x9
    adrp x9, GV_estudiantesDestacados
    add x9, x9, :lo12:GV_estudiantesDestacados
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR QUE: comparar x9 > x8
    cmp x9, x8
    cset x8, gt
    str x8, [sp, #-16]!
    // Cargar entero literal 5 en registro x8
    mov x8, #5
    str x8, [sp, #-16]!
    // Cargar variable global 'indice' en registro x9
    adrp x9, GV_indice
    add x9, x9, :lo12:GV_indice
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MENOR O IGUAL: comparar x9 <= x8
    cmp x9, x8
    cset x9, le
    ldr x8, [sp], #16
    // Operación AND LÓGICO: x9 && x8
    cmp x9, #0
    csel x9, xzr, x8, eq
    cmp x9, #0
    cset x9, ne
    cmp x9, #0
    b.eq while_end_39
    // Bloque WHILE
    // IF statement
    // Cargar entero literal 1 en registro x8
    mov x8, #1
    str x8, [sp, #-16]!
    // Cargar variable global 'indice' en registro x9
    adrp x9, GV_indice
    add x9, x9, :lo12:GV_indice
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq else_40
    // Bloque IF
    // Asignar identificador 'estudiante1' a variable 'nombre'
    adrp x1, GV_estudiante1
    add x1, x1, :lo12:GV_estudiante1
    ldr x2, [x1]
    adrp x3, GV_nombre
    add x3, x3, :lo12:GV_nombre
    str x2, [x3]

    // Asignar identificador 'nota1' a variable 'nota'
    adrp x1, GV_nota1
    add x1, x1, :lo12:GV_nota1
    ldr x2, [x1]
    adrp x3, GV_nota
    add x3, x3, :lo12:GV_nota
    str x2, [x3]

    // Asignar identificador 'edad1' a variable 'edad'
    adrp x1, GV_edad1
    add x1, x1, :lo12:GV_edad1
    ldr x2, [x1]
    adrp x3, GV_edad
    add x3, x3, :lo12:GV_edad
    str x2, [x3]

    b endif_41
else_40:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 2 en registro x8
    mov x8, #2
    str x8, [sp, #-16]!
    // Cargar variable global 'indice' en registro x9
    adrp x9, GV_indice
    add x9, x9, :lo12:GV_indice
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq else_42
    // Bloque IF
    // Asignar identificador 'estudiante2' a variable 'nombre'
    adrp x1, GV_estudiante2
    add x1, x1, :lo12:GV_estudiante2
    ldr x2, [x1]
    adrp x3, GV_nombre
    add x3, x3, :lo12:GV_nombre
    str x2, [x3]

    // Asignar identificador 'nota2' a variable 'nota'
    adrp x1, GV_nota2
    add x1, x1, :lo12:GV_nota2
    ldr x2, [x1]
    adrp x3, GV_nota
    add x3, x3, :lo12:GV_nota
    str x2, [x3]

    // Asignar identificador 'edad2' a variable 'edad'
    adrp x1, GV_edad2
    add x1, x1, :lo12:GV_edad2
    ldr x2, [x1]
    adrp x3, GV_edad
    add x3, x3, :lo12:GV_edad
    str x2, [x3]

    b endif_43
else_42:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 3 en registro x8
    mov x8, #3
    str x8, [sp, #-16]!
    // Cargar variable global 'indice' en registro x9
    adrp x9, GV_indice
    add x9, x9, :lo12:GV_indice
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq else_44
    // Bloque IF
    // Asignar identificador 'estudiante3' a variable 'nombre'
    adrp x1, GV_estudiante3
    add x1, x1, :lo12:GV_estudiante3
    ldr x2, [x1]
    adrp x3, GV_nombre
    add x3, x3, :lo12:GV_nombre
    str x2, [x3]

    // Asignar identificador 'nota3' a variable 'nota'
    adrp x1, GV_nota3
    add x1, x1, :lo12:GV_nota3
    ldr x2, [x1]
    adrp x3, GV_nota
    add x3, x3, :lo12:GV_nota
    str x2, [x3]

    // Asignar identificador 'edad3' a variable 'edad'
    adrp x1, GV_edad3
    add x1, x1, :lo12:GV_edad3
    ldr x2, [x1]
    adrp x3, GV_edad
    add x3, x3, :lo12:GV_edad
    str x2, [x3]

    b endif_45
else_44:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 4 en registro x8
    mov x8, #4
    str x8, [sp, #-16]!
    // Cargar variable global 'indice' en registro x9
    adrp x9, GV_indice
    add x9, x9, :lo12:GV_indice
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq else_46
    // Bloque IF
    // Asignar identificador 'estudiante4' a variable 'nombre'
    adrp x1, GV_estudiante4
    add x1, x1, :lo12:GV_estudiante4
    ldr x2, [x1]
    adrp x3, GV_nombre
    add x3, x3, :lo12:GV_nombre
    str x2, [x3]

    // Asignar identificador 'nota4' a variable 'nota'
    adrp x1, GV_nota4
    add x1, x1, :lo12:GV_nota4
    ldr x2, [x1]
    adrp x3, GV_nota
    add x3, x3, :lo12:GV_nota
    str x2, [x3]

    // Asignar identificador 'edad4' a variable 'edad'
    adrp x1, GV_edad4
    add x1, x1, :lo12:GV_edad4
    ldr x2, [x1]
    adrp x3, GV_edad
    add x3, x3, :lo12:GV_edad
    str x2, [x3]

    b endif_47
else_46:
    // Bloque ELSE
    // IF statement
    // Cargar entero literal 5 en registro x8
    mov x8, #5
    str x8, [sp, #-16]!
    // Cargar variable global 'indice' en registro x9
    adrp x9, GV_indice
    add x9, x9, :lo12:GV_indice
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación IGUALDAD: comparar x9 == x8
    cmp x9, x8
    cset x9, eq
    cmp x9, #0
    b.eq endif_49
    // Bloque IF
    // Asignar identificador 'estudiante5' a variable 'nombre'
    adrp x1, GV_estudiante5
    add x1, x1, :lo12:GV_estudiante5
    ldr x2, [x1]
    adrp x3, GV_nombre
    add x3, x3, :lo12:GV_nombre
    str x2, [x3]

    // Asignar identificador 'nota5' a variable 'nota'
    adrp x1, GV_nota5
    add x1, x1, :lo12:GV_nota5
    ldr x2, [x1]
    adrp x3, GV_nota
    add x3, x3, :lo12:GV_nota
    str x2, [x3]

    // Asignar identificador 'edad5' a variable 'edad'
    adrp x1, GV_edad5
    add x1, x1, :lo12:GV_edad5
    ldr x2, [x1]
    adrp x3, GV_edad
    add x3, x3, :lo12:GV_edad
    str x2, [x3]

endif_49:
    // Fin IF
endif_47:
    // Fin IF
endif_45:
    // Fin IF
endif_43:
    // Fin IF
endif_41:
    // Fin IF
    // IF statement
    // Cargar entero literal 20 en registro x8
    mov x8, #20
    str x8, [sp, #-16]!
    // Cargar variable global 'edad' en registro x9
    adrp x9, GV_edad
    add x9, x9, :lo12:GV_edad
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MENOR O IGUAL: comparar x9 <= x8
    cmp x9, x8
    cset x8, le
    str x8, [sp, #-16]!
    // Cargar entero literal 90 en registro x8
    mov x8, #90
    str x8, [sp, #-16]!
    // Cargar variable global 'nota' en registro x9
    adrp x9, GV_nota
    add x9, x9, :lo12:GV_nota
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación MAYOR O IGUAL: comparar x9 >= x8
    cmp x9, x8
    cset x9, ge
    ldr x8, [sp], #16
    // Operación AND LÓGICO: x9 && x8
    cmp x9, #0
    csel x9, xzr, x8, eq
    cmp x9, #0
    cset x9, ne
    cmp x9, #0
    b.eq endif_51
    // Bloque IF
    // ===== System.out.println =====
# AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
#   expresion tipo=0
# # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# #   expresion tipo=0
# # # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# # #   expresion tipo=0
# # # # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# # # #   expresion tipo=0
# # # # # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# # # # #   expresion tipo=0
# # # # # # AST node: EXPRESION_LENGUAJE iptr=0x57ece992723b children=2
# # # # # #   expresion tipo=0
# # # # # # # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# # # # # # #   prim tipo=9 valor=Estudiante joven destacado: 
# # # # # # # AST node: IDENTIFICADOR iptr=0x57ece99278d1 children=0
# # # # # # #   id nombre=nombre
# # # # # # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# # # # # #   prim tipo=9 valor= (Edad: 
# # # # # AST node: UNKNOWN iptr=0x57ece992286c children=0
# # # # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# # # #   prim tipo=9 valor=, Nota: 
# # # AST node: UNKNOWN iptr=0x57ece992286c children=0
# # AST node: PRIMITIVO iptr=0x57ece99279ce children=0
# #   prim tipo=9 valor=)
    // Imprimir string literal 'Estudiante joven destacado: '
    adrp x0, STRLIT_32
    add x0, x0, :lo12:STRLIT_32
    mov x1, #0
    bl print_string

    // Imprimir variable global 'nombre'
    adrp x0, GV_nombre
    add x0, x0, :lo12:GV_nombre
    // tipo tag=9
    mov x1, #9
    mov x2, #0
    bl print_any_gv

    // Imprimir string literal ' (Edad: '
    adrp x0, STRLIT_33
    add x0, x0, :lo12:STRLIT_33
    mov x1, #0
    bl print_string

    adrp x1, GV_edad
    add x1, x1, :lo12:GV_edad
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #0
    bl print_string
    mov x0, x9
    bl free

    // Imprimir string literal ', Nota: '
    adrp x0, STRLIT_34
    add x0, x0, :lo12:STRLIT_34
    mov x1, #0
    bl print_string

    adrp x1, GV_nota
    add x1, x1, :lo12:GV_nota
    ldr x1, [x1]
    mov w0, #1
    bl string_value_of_any
    mov x9, x0
    mov x0, x9
    mov x1, #0
    bl print_string
    mov x0, x9
    bl free

    // Imprimir string literal ')'
    adrp x0, STRLIT_35
    add x0, x0, :lo12:STRLIT_35
    mov x1, #1
    bl print_string

    // ===== Fin System.out.println =====

endif_51:
    // Fin IF
    // Evaluar expresión compleja para 'indice'
    adrp x11, GV_indice
    add x11, x11, :lo12:GV_indice
    // Cargar entero literal 1 en registro x8
    mov x8, #1
    str x8, [sp, #-16]!
    // Cargar variable global 'indice' en registro x9
    adrp x9, GV_indice
    add x9, x9, :lo12:GV_indice
    ldr x9, [x9]
    ldr x8, [sp], #16
    // Operación SUMA de enteros
    add x2, x9, x8
    str x2, [x11]

    b while_loop_38
while_end_39:
    // Fin WHILE
    .section .data
    .section .text
    mov x0, #0
    mov x8, #93
    svc #0
