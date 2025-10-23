#include <stdio.h>
#include <string.h>

// Declaración forward
long long div_mixed_helper(long a, long long b_bits);

// Simple integer division helper that expects two 64-bit integers in x0 and x1
// and returns quotient in x0. This is compiled for AArch64 and linked into final binary.
long div_helper(long a, long b) {
    if (b == 0) return 0; // simple guard
    
    // Si ambos operandos son enteros pequeños, hacer división entera
    if (a < 1000000 && b < 1000000 && a > -1000000 && b > -1000000) {
        return a / b;
    }
    
    // Si los operandos son grandes (posiblemente bits de double), usar división mixta
    return div_mixed_helper(a, b);
}

// Mixed-type division helper that handles int/double division
// x0: integer value, x1: double value (as bits)
// Returns double result (as bits)
long long div_mixed_helper(long a, long long b_bits) {
    if (b_bits == 0) return 0; // simple guard
    
    // Convert b_bits to double
    double b;
    memcpy(&b, &b_bits, sizeof(double));
    
    // Perform division: a / b
    double result = (double)a / b;
    
    // Convert result back to bits
    long long result_bits;
    memcpy(&result_bits, &result, sizeof(double));
    
    return result_bits;
}

// Modulo helper that returns remainder in x0
long mod_helper(long a, long b) {
    if (b == 0) return 0; // simple guard
    return a % b;
}
