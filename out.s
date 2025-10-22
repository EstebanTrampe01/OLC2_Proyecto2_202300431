    .section .data
    .align 3
L1:
    .asciz "-- Test5 assignment --\n"

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

STRLIT_1:
    .asciz "despues"

GV_numeroEntero: .quad 0

GV_cadena: .quad STRLIT_1

    .section .text
    .global _start
_start:
# debug: emit runtime print label 1
# debug: entering codegen_print_instr
    adrp x1, L1
    add x1, x1, :lo12:L1
    adrp x2, L1_end
    add x2, x2, :lo12:L1_end
    sub x2, x2, x1
    mov x0, #1
    mov x8, #64
    svc #0

# debug: leaving codegen_print_instr
# debug: emit runtime print label 2
# debug: entering codegen_print_instr
    adrp x1, L2
    add x1, x1, :lo12:L2
    adrp x2, L2_end
    add x2, x2, :lo12:L2_end
    sub x2, x2, x1
    mov x0, #1
    mov x8, #64
    svc #0

# debug: leaving codegen_print_instr
# debug: emit runtime asignacion
    // store integer 99 into GV_numeroEntero
    adrp x1, GV_numeroEntero
    add x1, x1, :lo12:GV_numeroEntero
    mov x2, #99
    str x2, [x1]

# debug: emit runtime print label 3
# debug: entering codegen_print_instr
    adrp x1, L3
    add x1, x1, :lo12:L3
    adrp x2, L3_end
    add x2, x2, :lo12:L3_end
    sub x2, x2, x1
    mov x0, #1
    mov x8, #64
    svc #0

# debug: leaving codegen_print_instr
# debug: emit runtime print label 4
# debug: entering codegen_print_instr
    adrp x1, L4
    add x1, x1, :lo12:L4
    adrp x2, L4_end
    add x2, x2, :lo12:L4_end
    sub x2, x2, x1
    mov x0, #1
    mov x8, #64
    svc #0

# debug: leaving codegen_print_instr
# debug: emit runtime asignacion
    adrp x1, GV_cadena
    add x1, x1, :lo12:GV_cadena
    adrp x2, STRLIT_1
    add x2, x2, :lo12:STRLIT_1
    str x2, [x1]

# debug: emit runtime print label 5
# debug: entering codegen_print_instr
    adrp x1, L5
    add x1, x1, :lo12:L5
    adrp x2, L5_end
    add x2, x2, :lo12:L5_end
    sub x2, x2, x1
    mov x0, #1
    mov x8, #64
    svc #0

# debug: leaving codegen_print_instr
    mov x0, #0
    mov x8, #93
    svc #0
