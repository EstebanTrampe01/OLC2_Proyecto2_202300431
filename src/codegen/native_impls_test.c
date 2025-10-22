#include <stdio.h>
#include "codegen/native_impls.h"

int main(void) {
    codegen_register_native("print", "print_string", 0);
    codegen_register_native("concat", "concat_string_string", 0);

    printf("is native print: %d\n", codegen_is_native("print"));
    const char* h = codegen_get_native_helper("concat");
    printf("helper for concat: %s\n", h ? h : "NULL");
    printf("is native foo: %d\n", codegen_is_native("foo"));
    return 0;
}
