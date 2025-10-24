#ifndef NATIVE_IMPLS_H
#define NATIVE_IMPLS_H

#include <stdbool.h>

// Kind values reserved for future: 0 = helper function, 1 = ARM snippet file
#define NATIVE_KIND_HELPER 0
#define NATIVE_KIND_SNIPPET 1

// Return type enums for native helpers
#define NATIVE_RET_VOID 0
#define NATIVE_RET_INT 1
#define NATIVE_RET_DOUBLE 2
#define NATIVE_RET_STRING 3

// Argument kinds for helper signatures
#define ARG_KIND_INT 1
#define ARG_KIND_PTR 2
#define ARG_KIND_DOUBLE 3
#define ARG_KIND_STRING ARG_KIND_PTR

void codegen_register_native(const char* name, const char* helper_name, int kind);
const char* codegen_get_native_helper(const char* name);
int codegen_is_native(const char* name);
// optional: set/get return type metadata for a native
void codegen_set_native_return(const char* name, int ret_type);
int codegen_get_native_return(const char* name);
// Register a native with explicit argument signature. arg_types is an array of length arg_count.
void codegen_register_native_signature(const char* name, int arg_count, const int* arg_types);
// Get the registered argument kind for helper 'name' at index 'arg_index', or -1 if unknown.
int codegen_get_native_arg_kind(const char* name, int arg_index);

#endif
