#define _POSIX_C_SOURCE 200809L
#include "literals.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "codegen.h"

// Simple registry for string literals
// Usar array estático grande para evitar problemas con realloc
#define MAX_STRLITS 256
static char* _strlit_values[MAX_STRLITS];
static int _strlit_count = 0;
static int _strlit_cap = MAX_STRLITS;
static int _strlit_next_id = 0;
static int _strlit_initialized = 0;

// Numeric literal registry (for doubles)
static unsigned long long* _numlit_bits = NULL;
static int _numlit_count = 0;
static int _numlit_cap = 0;
static int _numlit_next_id = 0;

static int codegen_register_strlit_value_internal(const char* val) {
    if (!val) return -1;
    
    // Inicializar array estático la primera vez
    if (!_strlit_initialized) {
        for (int i = 0; i < MAX_STRLITS; ++i) _strlit_values[i] = NULL;
        _strlit_initialized = 1;
    }
    
    // Buscar si ya existe
    for (int i = 0; i < _strlit_count; ++i) {
        if (_strlit_values[i] && strcmp(_strlit_values[i], val) == 0) return i+1;
    }
    
    // Verificar si hay espacio
    if (_strlit_count >= MAX_STRLITS) {
        fprintf(stderr, "ERROR: demasiados string literals (max=%d)\n", MAX_STRLITS);
        return -1;
    }
    
    // Agregar nuevo literal
    _strlit_values[_strlit_count++] = strdup(val);
    int new_id = ++_strlit_next_id;
    
    // Debug: si acabamos de registrar STRLIT_53 (id=53, index=52)
    if (new_id == 53) {
        debug_printf("DEBUG: registrando STRLIT_53 en índice %d con valor (len=%zu)\n", _strlit_count-1, strlen(_strlit_values[_strlit_count-1]));
    }
    
    return new_id;
}

static int codegen_find_strlit_internal(const char* val) {
    if (!val) return -1;
    int is_problematic = (strstr(val, "compuesto") != NULL);
    if (is_problematic) {
        debug_printf("DEBUG: buscando STRLIT problemático (len=%zu, _strlit_count=%d)\n", strlen(val), _strlit_count);
        debug_printf("DEBUG: bytes de la cadena buscada: ");
        for (size_t j = 0; j < strlen(val) && j < 30; ++j) printf("%02x ", (unsigned char)val[j]);
        printf("\n");
        // Ver específicamente qué hay en _strlit_values[52] (STRLIT_53)
        if (_strlit_count > 52 && _strlit_values[52]) {
            debug_printf("DEBUG: STRLIT_53 (_strlit_values[52]) = '%s' (len=%zu, primeros bytes: ", _strlit_values[52], strlen(_strlit_values[52]));
            for (size_t j = 0; j < strlen(_strlit_values[52]) && j < 30; ++j) printf("%02x ", (unsigned char)_strlit_values[52][j]);
            printf(")\n");
        } else {
            debug_printf("DEBUG: STRLIT_53 no está disponible (_strlit_count=%d)\n", _strlit_count);
        }
    }
    for (int i = 0; i < _strlit_count; ++i) {
        if (_strlit_values[i]) {
            if (is_problematic && strstr(_strlit_values[i], "compuesto")) {
                debug_printf("DEBUG: encontrado STRLIT_%d que contiene 'compuesto' (len=%zu)\n", i+1, strlen(_strlit_values[i]));
                debug_printf("DEBUG: bytes del STRLIT_%d: ", i+1);
                for (size_t j = 0; j < strlen(_strlit_values[i]) && j < 30; ++j) printf("%02x ", (unsigned char)_strlit_values[i][j]);
                printf("\n");
            }
            if (strcmp(_strlit_values[i], val) == 0) {
                if (is_problematic) debug_printf("DEBUG: STRLIT encontrado como STRLIT_%d\n", i+1);
                return i+1;
            }
        }
    }
    if (is_problematic) debug_printf("DEBUG: STRLIT NO encontrado (revisados %d STRLITs)\n", _strlit_count);
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
    debug_printf("DEBUG: registrando literal '%s' -> valor=%f -> bits=0x%016llx\n", sval, v, bits);
    for (int i=0;i<_numlit_count;++i) if (_numlit_bits[i]==bits) return i+1;
    if (_numlit_count >= _numlit_cap) { 
        _numlit_cap = (_numlit_cap==0)?8:_numlit_cap*2; 
        _numlit_bits = realloc(_numlit_bits, sizeof(unsigned long long)*_numlit_cap); 
    }
    _numlit_bits[_numlit_count++] = bits;
    debug_printf("DEBUG: literal registrado como NUMLIT_%d\n", _numlit_next_id+1);
    return ++_numlit_next_id;
}

int codegen_register_numlit(FILE* f, const char* val) { (void)f; return codegen_register_numlit_value_internal(val); }
int codegen_find_numlit(const char* val) { 
    if (!val) return -1; 
    char* end=NULL; 
    double v=strtod(val,&end); 
    unsigned long long bits=0; 
    memcpy(&bits,&v,sizeof(bits)); 
    debug_printf("DEBUG: buscando literal '%s' -> valor=%f -> bits=0x%016llx\n", val, v, bits);
    for (int i=0;i<_numlit_count;++i) {
        debug_printf("DEBUG: comparando con NUMLIT_%d bits=0x%016llx\n", i+1, _numlit_bits[i]);
        if (_numlit_bits[i]==bits) return i+1;
    }
    
    // Si no se encuentra, intentar sin sufijo 'f' o 'F'
    if (strlen(val) > 1 && (val[strlen(val)-1] == 'f' || val[strlen(val)-1] == 'F')) {
        char* val_without_f = strndup(val, strlen(val)-1);
        double v2 = strtod(val_without_f, &end);
        unsigned long long bits2 = 0;
        memcpy(&bits2, &v2, sizeof(bits2));
        debug_printf("DEBUG: intentando sin sufijo '%s' -> valor=%f -> bits=0x%016llx\n", val_without_f, v2, bits2);
        for (int i=0;i<_numlit_count;++i) {
            debug_printf("DEBUG: comparando sin sufijo con NUMLIT_%d bits=0x%016llx\n", i+1, _numlit_bits[i]);
            if (_numlit_bits[i]==bits2) {
                free(val_without_f);
                return i+1;
            }
        }
        free(val_without_f);
    }
    
    return -1; 
}

void codegen_emit_all_numlits(FILE* f) {
    if (!f) return;
    debug_printf("DEBUG: emitiendo %d literales numéricos\n", _numlit_count);
    for (int i=0;i<_numlit_count;++i) {
        unsigned long long bits = _numlit_bits[i];
        debug_printf("DEBUG: emitiendo NUMLIT_%d con bits=0x%016llx\n", i+1, bits);
        fprintf(f, "    .align 8\n");
        fprintf(f, "NUMLIT_%d:\n", i+1);
        fprintf(f, "    .quad 0x%016llx\n\n", (unsigned long long)bits);
    }
}
