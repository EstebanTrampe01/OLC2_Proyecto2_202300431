#include "common.h"
#include "../codegen.h"

// Stack de variables FOR activas (alcance por bloque)
typedef struct {
    char* name;
    int is_active;
} ForVariable;

static ForVariable for_variables[26]; // a-z
static int for_stack_top = -1;

// Variables para el sistema de mapeo (mantener para compatibilidad)
typedef struct {
    char* original;
    char* unique;
} NameMapping;

static NameMapping* name_mappings = NULL;
static int mapping_count = 0;
static int mapping_capacity = 0;

// Función para activar una variable FOR (entrar al bloque)
void arm_activate_for_variable(const char* name) {
    if (!name || strlen(name) != 1) return;
    
    char var = name[0];
    if (var < 'a' || var > 'z') return;
    
    int index = var - 'a';
    for_variables[index].name = strdup(name);
    for_variables[index].is_active = 1;
    
    debug_printf("DEBUG: Variable FOR '%s' ACTIVADA (alcance por bloque)\n", name);
}

// Función para desactivar una variable FOR (salir del bloque)
void arm_deactivate_for_variable(const char* name) {
    if (!name || strlen(name) != 1) return;
    
    char var = name[0];
    if (var < 'a' || var > 'z') return;
    
    int index = var - 'a';
    if (for_variables[index].name) {
        free(for_variables[index].name);
        for_variables[index].name = NULL;
    }
    for_variables[index].is_active = 0;
    
    debug_printf("DEBUG: Variable FOR '%s' DESACTIVADA (fin de alcance)\n", name);
}

// Función para verificar si una variable FOR está activa
int arm_is_for_variable_active(const char* name) {
    if (!name || strlen(name) != 1) return 0;
    
    char var = name[0];
    if (var < 'a' || var > 'z') return 0;
    
    int index = var - 'a';
    return for_variables[index].is_active;
}

// Función para agregar un mapeo de nombres
static void add_name_mapping(const char* original, const char* unique) {
    if (mapping_count >= mapping_capacity) {
        mapping_capacity = (mapping_capacity == 0) ? 32 : mapping_capacity * 2;
        name_mappings = realloc(name_mappings, sizeof(NameMapping) * mapping_capacity);
    }
    
    name_mappings[mapping_count].original = strdup(original);
    name_mappings[mapping_count].unique = strdup(unique);
    mapping_count++;
}

void arm_add_emitted_name(char*** names_ptr, int* count_ptr, int* cap_ptr, const char* name) {
    if (!name || !names_ptr || !count_ptr || !cap_ptr) return;
    char** names = *names_ptr;
    int count = *count_ptr;
    int cap = *cap_ptr;
    
    // Para variables de FOR, usar alcance por bloque
    char* unique_name = NULL;
    if (strlen(name) == 1 && ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z'))) {
        // Es una variable de una sola letra (probablemente de FOR)
        // Activar la variable en el stack de alcance
        arm_activate_for_variable(name);
        
        // Usar nombre original (alcance por bloque)
        unique_name = strdup(name);
        debug_printf("DEBUG: Variable FOR '%s' registrada con ALCANCE POR BLOQUE\n", name);
    } else {
        // Variable normal, usar nombre original
        unique_name = strdup(name);
    }
    
    // Verificar si ya existe
    for (int i = 0; i < count; ++i) {
        if (names[i] && strcmp(names[i], unique_name) == 0) {
            free(unique_name);
            return;
        }
    }
    
    if (count >= cap) {
        cap = (cap == 0) ? 32 : cap * 2;  // Aumentar capacidad inicial de 16 a 32 para test4.usl
        char** new_names = (char**)realloc(names, sizeof(char*) * cap);
        if (!new_names) {
            fprintf(stderr, "ERROR: No se pudo asignar memoria para nombres de variables\n");
            exit(1);
        }
        names = new_names;
        *names_ptr = names;
        *cap_ptr = cap;
    }
    
    names[count] = unique_name;
    if (!names[count]) {
        fprintf(stderr, "ERROR: No se pudo duplicar el nombre de variable '%s'\n", name);
        exit(1);
    }
    count++;
    *count_ptr = count;
}

// Función para obtener el nombre de una variable FOR (alcance por bloque)
char* arm_get_unique_var_name(const char* original_name) {
    if (!original_name) return NULL;
    
    debug_printf("DEBUG: arm_get_unique_var_name llamado con '%s'\n", original_name);
    
    // Para variables de FOR, verificar si están activas
    if (strlen(original_name) == 1 && ((original_name[0] >= 'a' && original_name[0] <= 'z') || (original_name[0] >= 'A' && original_name[0] <= 'Z'))) {
        if (arm_is_for_variable_active(original_name)) {
            // Variable FOR activa, usar nombre original
            char* result = strdup(original_name);
            debug_printf("DEBUG: Variable FOR activa '%s' -> '%s'\n", original_name, result);
            return result;
        } else {
            // Variable FOR no activa, usar nombre original (se reiniciará)
            char* result = strdup(original_name);
            debug_printf("DEBUG: Variable FOR no activa '%s' -> '%s'\n", original_name, result);
            return result;
        }
    }
    
    // Variable normal, usar nombre original
    char* result = strdup(original_name);
    debug_printf("DEBUG: Variable normal '%s' -> '%s'\n", original_name, result);
    return result;
}


