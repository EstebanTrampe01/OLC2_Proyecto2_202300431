#include <stdio.h>
#include <string.h>

// Helper para detectar si un valor es un entero pequeño o bits de double
static int is_small_integer(long val) {
    // Si el valor está en el rango de enteros pequeños (menos de ~1 millón),
    // probablemente es un entero y no bits de double
    return (val >= -1000000 && val <= 1000000);
}

// Helper para convertir un valor que puede ser entero o bits de double a double
static double to_double(long val) {
    if (is_small_integer(val)) {
        // Es un entero pequeño, convertir directamente
        return (double)val;
    } else {
        // Es probablemente bits de double, convertir usando memcpy
        double d;
        memcpy(&d, &val, sizeof(double));
        return d;
    }
}

// Helper para suma de doubles
// Recibe operandos como long (pueden ser enteros o bits de double) y devuelve resultado como long long (bits de double)
long long double_add(long a_bits, long b_bits) {
    double a = to_double(a_bits);
    double b = to_double(b_bits);
    double result = a + b;
    long long result_bits;
    memcpy(&result_bits, &result, sizeof(double));
    return result_bits;
}

// Helper para resta de doubles  
// Recibe operandos como long (pueden ser enteros o bits de double) y devuelve resultado como long long (bits de double)
long long double_sub(long a_bits, long b_bits) {
    double a = to_double(a_bits);
    double b = to_double(b_bits);
    double result = a - b;
    long long result_bits;
    memcpy(&result_bits, &result, sizeof(double));
    return result_bits;
}

// Helper para multiplicación de doubles
// Recibe operandos como long (pueden ser enteros o bits de double) y devuelve resultado como long long (bits de double)
long long double_mul(long a_bits, long b_bits) {
    double a = to_double(a_bits);
    double b = to_double(b_bits);
    double result = a * b;
    long long result_bits;
    memcpy(&result_bits, &result, sizeof(double));
    return result_bits;
}

// Helper para división de doubles
// Recibe operandos como long (pueden ser enteros o bits de double) y devuelve resultado como long long (bits de double)
long long double_div(long a_bits, long b_bits) {
    double a = to_double(a_bits);
    double b = to_double(b_bits);
    if (b == 0.0) return 0;
    double result = a / b;
    long long result_bits;
    memcpy(&result_bits, &result, sizeof(double));
    return result_bits;
}

// Helper para convertir int a double
double int_to_double(long int_val) {
    return (double)int_val;
}

// Helper para convertir double a int (truncar)
long double_to_int(double double_val) {
    return (long)double_val;
}
