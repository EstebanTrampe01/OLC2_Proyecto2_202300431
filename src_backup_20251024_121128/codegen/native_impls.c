#define _POSIX_C_SOURCE 200809L
#include "native_impls.h"
#include <stdlib.h>
#include <string.h>

typedef struct NativeEntry {
    char* name;
    char* helper;
    int kind;
    int ret_type;
    int* arg_kinds;
    int arg_count;
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
            _native_table[i].ret_type = NATIVE_RET_VOID;
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
    _native_table[_native_count].ret_type = NATIVE_RET_VOID;
    _native_count++;
}

void codegen_set_native_return(const char* name, int ret_type) {
    if (!name) return;
    for (int i = 0; i < _native_count; ++i) if (strcmp(_native_table[i].name, name) == 0) { _native_table[i].ret_type = ret_type; return; }
}

void codegen_register_native_signature(const char* name, int arg_count, const int* arg_types) {
    if (!name) return;
    for (int i=0;i<_native_count;++i) {
        if (strcmp(_native_table[i].name, name) == 0) {
            if (_native_table[i].arg_kinds) free(_native_table[i].arg_kinds);
            if (arg_count>0 && arg_types) {
                _native_table[i].arg_kinds = (int*) malloc(sizeof(int)*arg_count);
                memcpy(_native_table[i].arg_kinds, arg_types, sizeof(int)*arg_count);
                _native_table[i].arg_count = arg_count;
            } else {
                _native_table[i].arg_kinds = NULL; _native_table[i].arg_count = 0;
            }
            return;
        }
    }
}

int codegen_get_native_arg_kind(const char* name, int arg_index) {
    if (!name) return -1;
    for (int i=0;i<_native_count;++i) {
        if (strcmp(_native_table[i].name, name) == 0) {
            if (_native_table[i].arg_kinds && arg_index >=0 && arg_index < _native_table[i].arg_count) return _native_table[i].arg_kinds[arg_index];
            return -1;
        }
    }
    return -1;
}

int codegen_get_native_return(const char* name) {
    if (!name) return NATIVE_RET_VOID;
    for (int i = 0; i < _native_count; ++i) if (strcmp(_native_table[i].name, name) == 0) return _native_table[i].ret_type;
    return NATIVE_RET_VOID;
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
