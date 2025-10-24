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

// Funciones para alcance por bloque de variables FOR
void arm_activate_for_variable(const char* name);
void arm_deactivate_for_variable(const char* name);
int arm_is_for_variable_active(const char* name);

// Función para obtener el nombre de una variable FOR (alcance por bloque)
char* arm_get_unique_var_name(const char* original_name);

#endif


