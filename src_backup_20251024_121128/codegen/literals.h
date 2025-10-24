#ifndef CODEGEN_LITERALS_H
#define CODEGEN_LITERALS_H

#include <stdio.h>

int codegen_register_strlit(FILE* f, const char* val);
int codegen_find_strlit(const char* val);
void codegen_emit_all_strlits(FILE* f);

int codegen_register_numlit(FILE* f, const char* val);
int codegen_find_numlit(const char* val);
void codegen_emit_all_numlits(FILE* f);

#endif
