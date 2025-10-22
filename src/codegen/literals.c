#define _POSIX_C_SOURCE 200809L
#include "literals.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Simple registry for string literals
static char** _strlit_values = NULL;
static int _strlit_count = 0;
static int _strlit_cap = 0;
static int _strlit_next_id = 0;

// Numeric literal registry (for doubles)
static unsigned long long* _numlit_bits = NULL;
static int _numlit_count = 0;
static int _numlit_cap = 0;
static int _numlit_next_id = 0;

static int codegen_register_strlit_value_internal(const char* val) {
    if (!val) return -1;
    for (int i = 0; i < _strlit_count; ++i) if (_strlit_values[i] && strcmp(_strlit_values[i], val) == 0) return i+1;
    if (_strlit_count >= _strlit_cap) {
        _strlit_cap = (_strlit_cap==0)?8:_strlit_cap*2;
        _strlit_values = realloc(_strlit_values, sizeof(char*) * _strlit_cap);
    }
    _strlit_values[_strlit_count++] = strdup(val);
    return ++_strlit_next_id;
}

static int codegen_find_strlit_internal(const char* val) {
    if (!val) return -1;
    for (int i = 0; i < _strlit_count; ++i) if (_strlit_values[i] && strcmp(_strlit_values[i], val) == 0) return i+1;
    return -1;
}

int codegen_find_strlit(const char* val) { return codegen_find_strlit_internal(val); }
int codegen_register_strlit(FILE* f, const char* val) { (void)f; return codegen_register_strlit_value_internal(val); }

void codegen_emit_all_strlits(FILE* f) {
    if (!f) return;
    for (int i = 0; i < _strlit_count; ++i) {
        if (!_strlit_values[i]) continue;
        fprintf(f, "STRLIT_%d:\n", i+1);
        fprintf(f, "    .asciz \"");
        for (size_t j = 0; j < strlen(_strlit_values[i]); ++j) {
            char c = _strlit_values[i][j];
            if (c=='\\') fprintf(f, "\\\\");
            else if (c=='\"') fprintf(f, "\\\"");
            else if (c=='\n') fprintf(f, "\\n");
            else fprintf(f, "%c", c);
        }
        fprintf(f, "\"\n\n");
    }
}

// Numeric literals
static int codegen_register_numlit_value_internal(const char* sval) {
    if (!sval) return -1;
    char* end = NULL; double v = strtod(sval, &end); unsigned long long bits=0; memcpy(&bits,&v,sizeof(bits));
    for (int i=0;i<_numlit_count;++i) if (_numlit_bits[i]==bits) return i+1;
    if (_numlit_count >= _numlit_cap) { _numlit_cap = (_numlit_cap==0)?8:_numlit_cap*2; _numlit_bits = realloc(_numlit_bits, sizeof(unsigned long long)*_numlit_cap); }
    _numlit_bits[_numlit_count++] = bits;
    return ++_numlit_next_id;
}

int codegen_register_numlit(FILE* f, const char* val) { (void)f; return codegen_register_numlit_value_internal(val); }
int codegen_find_numlit(const char* val) { if (!val) return -1; char* end=NULL; double v=strtod(val,&end); unsigned long long bits=0; memcpy(&bits,&v,sizeof(bits)); for (int i=0;i<_numlit_count;++i) if (_numlit_bits[i]==bits) return i+1; return -1; }

void codegen_emit_all_numlits(FILE* f) {
    if (!f) return;
    for (int i=0;i<_numlit_count;++i) {
        unsigned long long bits = _numlit_bits[i];
        fprintf(f, "NUMLIT_%d:\n", i+1);
        fprintf(f, "    .quad 0x%016llx\n\n", (unsigned long long)bits);
    }
}
