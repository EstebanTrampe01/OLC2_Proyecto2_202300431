.global _start
.text
_start:
ldr x0, =L0
mov x2, x0
mov x1, #0
L1:
ldrb w9, [x2]
cbz w9, L2
add x1, x1, #1
add x2, x2, #1
b L1
L2:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =x
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L3
neg x2, x2
mov x3, #1
b L4
L3:
mov x3, #0
L4:
cmp x2, #0
beq L5
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L4
L5:
cmp x3, #0
beq L6
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L6:
mov x0, x1
mov x2, x0
mov x1, #0
L7:
ldrb w9, [x2]
cbz w9, L8
add x1, x1, #1
add x2, x2, #1
b L7
L8:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L9
mov x2, x0
mov x1, #0
L10:
ldrb w9, [x2]
cbz w9, L11
add x1, x1, #1
add x2, x2, #1
b L10
L11:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L12
mov x2, x0
mov x1, #0
L13:
ldrb w9, [x2]
cbz w9, L14
add x1, x1, #1
add x2, x2, #1
b L13
L14:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L15
mov x2, x0
mov x1, #0
L16:
ldrb w9, [x2]
cbz w9, L17
add x1, x1, #1
add x2, x2, #1
b L16
L17:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L18
mov x2, x0
mov x1, #0
L19:
ldrb w9, [x2]
cbz w9, L20
add x1, x1, #1
add x2, x2, #1
b L19
L20:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L21
mov x2, x0
mov x1, #0
L22:
ldrb w9, [x2]
cbz w9, L23
add x1, x1, #1
add x2, x2, #1
b L22
L23:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L24
mov x2, x0
mov x1, #0
L25:
ldrb w9, [x2]
cbz w9, L26
add x1, x1, #1
add x2, x2, #1
b L25
L26:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L27
mov x2, x0
mov x1, #0
L28:
ldrb w9, [x2]
cbz w9, L29
add x1, x1, #1
add x2, x2, #1
b L28
L29:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L30
mov x2, x0
mov x1, #0
L31:
ldrb w9, [x2]
cbz w9, L32
add x1, x1, #1
add x2, x2, #1
b L31
L32:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L33
mov x2, x0
mov x1, #0
L34:
ldrb w9, [x2]
cbz w9, L35
add x1, x1, #1
add x2, x2, #1
b L34
L35:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L36
ldr x1, =x
mov x0, x1
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L37
neg x2, x2
mov x3, #1
b L38
L37:
mov x3, #0
L38:
cmp x2, #0
beq L39
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L38
L39:
cmp x3, #0
beq L40
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L40:
mov x1, x1
add x0, x0, x1
mov x2, x0
mov x1, #0
L41:
ldrb w9, [x2]
cbz w9, L42
add x1, x1, #1
add x2, x2, #1
b L41
L42:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L43
mov x2, x0
mov x1, #0
L44:
ldrb w9, [x2]
cbz w9, L45
add x1, x1, #1
add x2, x2, #1
b L44
L45:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L46
mov x2, x0
mov x1, #0
L47:
ldrb w9, [x2]
cbz w9, L48
add x1, x1, #1
add x2, x2, #1
b L47
L48:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L49
mov x2, x0
mov x1, #0
L50:
ldrb w9, [x2]
cbz w9, L51
add x1, x1, #1
add x2, x2, #1
b L50
L51:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L52
mov x2, x0
mov x1, #0
L53:
ldrb w9, [x2]
cbz w9, L54
add x1, x1, #1
add x2, x2, #1
b L53
L54:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L55
mov x2, x0
mov x1, #0
L56:
ldrb w9, [x2]
cbz w9, L57
add x1, x1, #1
add x2, x2, #1
b L56
L57:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L58
mov x2, x0
mov x1, #0
L59:
ldrb w9, [x2]
cbz w9, L60
add x1, x1, #1
add x2, x2, #1
b L59
L60:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L61
mov x2, x0
mov x1, #0
L62:
ldrb w9, [x2]
cbz w9, L63
add x1, x1, #1
add x2, x2, #1
b L62
L63:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L64
mov x2, x0
mov x1, #0
L65:
ldrb w9, [x2]
cbz w9, L66
add x1, x1, #1
add x2, x2, #1
b L65
L66:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L67
mov x2, x0
mov x1, #0
L68:
ldrb w9, [x2]
cbz w9, L69
add x1, x1, #1
add x2, x2, #1
b L68
L69:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L70
mov x2, x0
mov x1, #0
L71:
ldrb w9, [x2]
cbz w9, L72
add x1, x1, #1
add x2, x2, #1
b L71
L72:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L73
mov x2, x0
mov x1, #0
L74:
ldrb w9, [x2]
cbz w9, L75
add x1, x1, #1
add x2, x2, #1
b L74
L75:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L76
mov x2, x0
mov x1, #0
L77:
ldrb w9, [x2]
cbz w9, L78
add x1, x1, #1
add x2, x2, #1
b L77
L78:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L79
mov x2, x0
mov x1, #0
L80:
ldrb w9, [x2]
cbz w9, L81
add x1, x1, #1
add x2, x2, #1
b L80
L81:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L82
mov x2, x0
mov x1, #0
L83:
ldrb w9, [x2]
cbz w9, L84
add x1, x1, #1
add x2, x2, #1
b L83
L84:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L85
mov x2, x0
mov x1, #0
L86:
ldrb w9, [x2]
cbz w9, L87
add x1, x1, #1
add x2, x2, #1
b L86
L87:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L88
mov x2, x0
mov x1, #0
L89:
ldrb w9, [x2]
cbz w9, L90
add x1, x1, #1
add x2, x2, #1
b L89
L90:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L91
mov x2, x0
mov x1, #0
L92:
ldrb w9, [x2]
cbz w9, L93
add x1, x1, #1
add x2, x2, #1
b L92
L93:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L94
mov x2, x0
mov x1, #0
L95:
ldrb w9, [x2]
cbz w9, L96
add x1, x1, #1
add x2, x2, #1
b L95
L96:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L97
mov x2, x0
mov x1, #0
L98:
ldrb w9, [x2]
cbz w9, L99
add x1, x1, #1
add x2, x2, #1
b L98
L99:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
cmp x0, #0
beq L0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
b L0
L0:
L0:
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
cmp x0, #0
beq L0
b L0
L0:
ldr x0, =x
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L0
neg x2, x2
mov x3, #1
b L0
L0:
mov x3, #0
L0:
cmp x2, #0
beq L0
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L0
L0:
cmp x3, #0
beq L0
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L0:
mov x0, x1
ldr x1, =resultado
str x0, [x1]
L0:
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =x
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L0
neg x2, x2
mov x3, #1
b L0
L0:
mov x3, #0
L0:
cmp x2, #0
beq L0
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L0
L0:
cmp x3, #0
beq L0
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L0:
mov x0, x1
ldr x1, =codigoAscii
str x0, [x1]
ldr x0, =x
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L0
neg x2, x2
mov x3, #1
b L0
L0:
mov x3, #0
L0:
cmp x2, #0
beq L0
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L0
L0:
cmp x3, #0
beq L0
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L0:
mov x0, x1
ldr x1, =codigoFloat
str x0, [x1]
ldr x0, =x
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L0
neg x2, x2
mov x3, #1
b L0
L0:
mov x3, #0
L0:
cmp x2, #0
beq L0
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L0
L0:
cmp x3, #0
beq L0
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L0:
mov x0, x1
ldr x1, =codigoDouble
str x0, [x1]
ldr x0, =L0
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
ldr x1, =x
mov x0, x1
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L0
neg x2, x2
mov x3, #1
b L0
L0:
mov x3, #0
L0:
cmp x2, #0
beq L0
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L0
L0:
cmp x3, #0
beq L0
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L0:
mov x1, x1
add x0, x0, x1
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
ldr x1, =x
mov x0, x1
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L0
neg x2, x2
mov x3, #1
b L0
L0:
mov x3, #0
L0:
cmp x2, #0
beq L0
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L0
L0:
cmp x3, #0
beq L0
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L0:
mov x1, x1
add x0, x0, x1
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2, x1
mov x1, x0
mov x0, #1
mov x8, #64
svc #0
ldr x0, =L0
ldr x1, =x
mov x0, x1
ldr x1, =buffer
add x1, x1, #31
strb wzr, [x1]
mov x2, x0
cmp x2, #0
bge L0
neg x2, x2
mov x3, #1
b L0
L0:
mov x3, #0
L0:
cmp x2, #0
beq L0
sub x1, x1, #1
mov x4, #10
udiv x5, x2, x4
msub x6, x5, x4, x2
add w6, w6, #'0'
strb w6, [x1]
mov x2, x5
b L0
L0:
cmp x3, #0
beq L0
sub x1, x1, #1
mov w4, #'-'
strb w4, [x1]
L0:
mov x1, x1
add x0, x0, x1
mov x2, x0
mov x1, #0
L0:
ldrb w9, [x2]
cbz w9, L0
add x1, x1, #1
add x2, x2, #1
b L0
L0:
mov x2,