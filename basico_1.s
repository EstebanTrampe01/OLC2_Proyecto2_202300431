.global _start
.text
_start:
mov x0, #1
adr x1, L0
mov x2, #38
mov x8, #64
svc #0
ldr x0, =x
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L1
neg x2, x2
mov x3, #1
b L2
L1:
mov x3, #0
L2:
cmp x2, #0
beq L3
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L2
L3:
cmp x3, #0
beq L4
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L4:
mov x0, x1
mov x2, x0
mov x1, #0
L5:
ldrb w9, [x2]
cbz w9, L6
add x1, x1, #1
add x2, x2, #1
b L5
L6:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L7
mov x2, x0
mov x1, #0
L8:
ldrb w9, [x2]
cbz w9, L9
add x1, x1, #1
add x2, x2, #1
b L8
L9:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L10
mov x2, x0
mov x1, #0
L11:
ldrb w9, [x2]
cbz w9, L12
add x1, x1, #1
add x2, x2, #1
b L11
L12:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
mov x0, #1
adr x1, L13
mov x2, #38
mov x8, #64
svc #0
ldr x0, =x
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L14
neg x2, x2
mov x3, #1
b L15
L14:
mov x3, #0
L15:
cmp x2, #0
beq L16
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L15
L16:
cmp x3, #0
beq L17
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L17:
mov x0, x1
mov x2, x0
mov x1, #0
L18:
ldrb w9, [x2]
cbz w9, L19
add x1, x1, #1
add x2, x2, #1
b L18
L19:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L20
mov x2, x0
mov x1, #0
L21:
ldrb w9, [x2]
cbz w9, L22
add x1, x1, #1
add x2, x2, #1
b L21
L22:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L23
mov x2, x0
mov x1, #0
L24:
ldrb w9, [x2]
cbz w9, L25
add x1, x1, #1
add x2, x2, #1
b L24
L25:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
mov x0, #0
mov x8, #93
svc #0
strcmp:
    mov x2, #0
strcmp_loop:
    ldrb w3, [x0], #1
    ldrb w4, [x1], #1
    cmp w3, w4
    bne strcmp_not_equal
    cmp w3, #0
    bne strcmp_loop
    mov x0, #0
    ret
strcmp_not_equal:
    mov x0, #1
    ret
itoa:
    mov x2, x1
    cmp x0, #0
    bge itoa_positive
    neg x0, x0
    mov w3, #'-'
    strb w3, [x2], #1
itoa_positive:
    mov x3, #10
    mov x4, x0
    cmp x4, #0
    beq itoa_zero
    mov x5, #0
itoa_loop:
    udiv x6, x4, x3
    msub x7, x6, x3, x4
    add w7, w7, #'0'
    strb w7, [x2, x5]
    add x5, x5, #1
    mov x4, x6
    cmp x4, #0
    bne itoa_loop
    sub x5, x5, #1
    mov x6, #0
itoa_reverse:
    cmp x6, x5
    bge itoa_end
    ldrb w7, [x2, x6]
    ldrb w8, [x2, x5]
    strb w8, [x2, x6]
    strb w7, [x2, x5]
    add x6, x6, #1
    sub x5, x5, #1
    b itoa_reverse
itoa_zero:
    mov w3, #'0'
    strb w3, [x2], #1
itoa_end:
    strb wzr, [x2]
    mov x0, x1
    ret
concat:
    mov x3, x0
    mov x4, x2
concat_loop1:
    ldrb w5, [x3], #1
    strb w5, [x4], #1
    cmp w5, #0
    bne concat_loop1
    sub x4, x4, #1
concat_loop2:
    ldrb w5, [x1], #1
    strb w5, [x4], #1
    cmp w5, #0
    bne concat_loop2
    mov x0, x2
    ret
print_int:
    ldr x1, =buffer
    add x1, x1, #31
    strb wzr, [x1]
    mov x2, x0
    cmp x2, #0
    bge print_int_positive
    neg x2, x2
    mov x3, #1
    b print_int_loop
print_int_positive:
    mov x3, #0
print_int_loop:
    cmp x2, #0
    beq print_int_end_loop
    sub x1, x1, #1
    mov x4, #10
    udiv x5, x2, x4
    msub x6, x5, x4, x2
    add w6, w6, #'0'
    strb w6, [x1]
    mov x2, x5
    b print_int_loop
print_int_end_loop:
    cmp x3, #0
    beq print_int_print
    sub x1, x1, #1
    mov w4, #'-'
    strb w4, [x1]
print_int_print:
    mov x0, #1
    ldr x1, =buffer
    add x1, x1, #31
    sub x1, x1, x2
    mov x2, #32
    mov x8, #64
    svc #0
    ret
print_string:
    mov x1, x0
    mov x2, #0
print_string_count:
    ldrb w3, [x1, x2]
    cmp w3, #0
    beq print_string_write
    add x2, x2, #1
    b print_string_count
print_string_write:
    mov x0, #1
    mov x1, x0
    mov x8, #64
    svc #0
    ret
.data
msg: .ascii "Hello\n"
.data
buffer: .space 32
temp_str: .space 64
L0: .ascii "=== SISTEMA DE CALCULO CIENTIFICO ===\n"
numeroEntero: .word 42
numeroFlotante: .float 0.000000
numeroDoble: .double 0.000000
caracter: .word 0
esVerdadero: .word 0
cadenaTexto: .asciz "Resultado"
PI: .word 3
CONSTANTE_MAXIMA: .word 100
MENSAJE_SISTEMA: .asciz "Calculadora Científica v1.0"
L7: .asciz "Constante PI: \n"
L10: .asciz "Constante máxima: \n"
L13: .ascii "=== SISTEMA DE CALCULO CIENTIFICO ===\n"
L20: .asciz "Constante PI: \n"
L23: .asciz "Constante máxima: \n"
