#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

// Simple double helpers for AArch64 codegen.
// These functions follow the simplified calling convention:
// - add_double: receives two doubles in x0/x1 as bitpatterns (we'll accept them in FP registers if compiler uses FP ABI),
//   but to be portable we'll accept as doubles in the usual C ABI.

double add_double(double a, double b) {
    return a + b;
}

void print_double(double d) {
    // print with trimmed formatting similar to interpreter's format_trim_double
    char buf[64];
    // use %.10g to match typical precision trimming
    snprintf(buf, sizeof(buf), "%.10g", d);
    printf("%s", buf);
    fflush(stdout);
}
