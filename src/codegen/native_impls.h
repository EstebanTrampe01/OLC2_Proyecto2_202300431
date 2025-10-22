#ifndef NATIVE_IMPLS_H
#define NATIVE_IMPLS_H

#include <stdbool.h>

// Kind values reserved for future: 0 = helper function, 1 = ARM snippet file
#define NATIVE_KIND_HELPER 0
#define NATIVE_KIND_SNIPPET 1

void codegen_register_native(const char* name, const char* helper_name, int kind);
const char* codegen_get_native_helper(const char* name);
int codegen_is_native(const char* name);

#endif
