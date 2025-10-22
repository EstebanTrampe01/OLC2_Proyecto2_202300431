    .section .data
    .align 3
msg:
    .asciz "Hola Mundo\n"

    .section .text
    .global _start
_start:
    // write(1, msg, 11)
    mov x0, #1
    adrp x1, msg
    add x1, x1, :lo12:msg
    mov x2, #11
    mov x8, #64
    svc #0

    // exit(0)
    mov x0, #0
    mov x8, #93
    svc #0
