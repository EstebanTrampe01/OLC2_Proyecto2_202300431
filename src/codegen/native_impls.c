#define _POSIX_C_SOURCE 200809L
#include "native_impls.h"
#include <stdlib.h>
#include <string.h>

typedef struct NativeEntry {
    char* name;
    char* helper;
    int kind;
} NativeEntry;

static NativeEntry* _native_table = NULL;
static int _native_count = 0;
static int _native_cap = 0;

void codegen_register_native(const char* name, const char* helper_name, int kind) {
    if (!name) return;
    // check existing
    for (int i = 0; i < _native_count; ++i) {
        if (strcmp(_native_table[i].name, name) == 0) {
            // update
            if (_native_table[i].helper) free(_native_table[i].helper);
            _native_table[i].helper = helper_name ? strdup(helper_name) : NULL;
            _native_table[i].kind = kind;
            return;
        }
    }
    if (_native_count >= _native_cap) {
        _native_cap = (_native_cap == 0) ? 8 : _native_cap * 2;
        _native_table = (NativeEntry*)realloc(_native_table, sizeof(NativeEntry) * _native_cap);
    }
    _native_table[_native_count].name = strdup(name);
    _native_table[_native_count].helper = helper_name ? strdup(helper_name) : NULL;
    _native_table[_native_count].kind = kind;
    _native_count++;
}

const char* codegen_get_native_helper(const char* name) {
    if (!name) return NULL;
    for (int i = 0; i < _native_count; ++i) if (strcmp(_native_table[i].name, name) == 0) return _native_table[i].helper;
    return NULL;
}

int codegen_is_native(const char* name) {
    if (!name) return 0;
    for (int i = 0; i < _native_count; ++i) if (strcmp(_native_table[i].name, name) == 0) return 1;
    return 0;
}
