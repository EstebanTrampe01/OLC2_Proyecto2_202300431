#include "native_impls.h"

void register_core_natives(void) {
    // Register String.valueOf as a generic helper that returns string and expects (tag:int, value:ptr)
    codegen_register_native("String.valueOf", "string_value_of_any", NATIVE_KIND_HELPER);
    codegen_set_native_return("String.valueOf", NATIVE_RET_STRING);
    int sig[2] = { ARG_KIND_INT, ARG_KIND_PTR };
    codegen_register_native_signature("String.valueOf", 2, sig);
}
