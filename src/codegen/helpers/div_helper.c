#include <stdio.h>

// Simple integer division helper that expects two 64-bit integers in x0 and x1
// and returns quotient in x0. This is compiled for AArch64 and linked into final binary.
long div_helper(long a, long b) {
    if (b == 0) return 0; // simple guard
    return a / b;
}

// Modulo helper that returns remainder in x0
long mod_helper(long a, long b) {
    if (b == 0) return 0; // simple guard
    return a % b;
}
