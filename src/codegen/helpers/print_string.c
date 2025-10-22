#include <stdio.h>

// Minimal helper for printing a NUL-terminated string from x0 (char*).
// This file will be compiled for AArch64 and linked into the final binary.

void print_string(const char* s, int newline) {
    if (!s) return;
    fputs(s, stdout);
    if (newline) putchar('\n');
}
