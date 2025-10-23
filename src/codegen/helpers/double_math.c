#include <stdio.h>
#include <string.h>

// Helper para multiplicación de doubles
// Recibe operandos como long (bits de double) y los convierte a double
double double_mul_helper(long a_bits, long b_bits) {
    double a, b;
    memcpy(&a, &a_bits, sizeof(double));
    memcpy(&b, &b_bits, sizeof(double));
    return a * b;
}

// Helper para división de doubles
// Recibe operandos como long (bits de double) y los convierte a double
double double_div_helper(long a_bits, long b_bits) {
    double a, b;
    memcpy(&a, &a_bits, sizeof(double));
    memcpy(&b, &b_bits, sizeof(double));
    if (b == 0) return 0;
    return a / b;
}

// Helper para suma de doubles
// Recibe operandos como long (bits de double) y los convierte a double
double double_add_helper(long a_bits, long b_bits) {
    double a, b;
    memcpy(&a, &a_bits, sizeof(double));
    memcpy(&b, &b_bits, sizeof(double));
    return a + b;
}

// Helper para resta de doubles
// Recibe operandos como long (bits de double) y los convierte a double
double double_sub_helper(long a_bits, long b_bits) {
    double a, b;
    memcpy(&a, &a_bits, sizeof(double));
    memcpy(&b, &b_bits, sizeof(double));
    return a - b;
}
