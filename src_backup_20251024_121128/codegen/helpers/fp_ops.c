#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

// Simple FP helpers beyond add_double used for testing and to link with codegen.

double sub_double(double a, double b) { return a - b; }

double mul_double(double a, double b) { return a * b; }

double div_double(double a, double b) { return a / b; }

// add_double and print_double are implemented in double_helpers.c
extern double add_double(double a, double b);
extern void print_double(double d);
