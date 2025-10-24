// Common helpers for ARM codegen modules
#ifndef GENERADOR_ARM_COMMON_H
#define GENERADOR_ARM_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen/codegen.h"
#include "ast/AbstractExpresion.h"

// Utility shared by modules: maintain unique list of emitted names
void arm_add_emitted_name(char*** names_ptr, int* count_ptr, int* cap_ptr, const char* name);

#endif


