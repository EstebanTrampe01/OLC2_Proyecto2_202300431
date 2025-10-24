#include "common.h"

void arm_add_emitted_name(char*** names_ptr, int* count_ptr, int* cap_ptr, const char* name) {
    if (!name || !names_ptr || !count_ptr || !cap_ptr) return;
    char** names = *names_ptr;
    int count = *count_ptr;
    int cap = *cap_ptr;
    for (int i = 0; i < count; ++i) {
        if (names[i] && strcmp(names[i], name) == 0) return;
    }
    if (count >= cap) {
        cap = (cap == 0) ? 16 : cap * 2;  // Aumentar capacidad inicial de 8 a 16
        char** new_names = (char**)realloc(names, sizeof(char*) * cap);
        if (!new_names) {
            fprintf(stderr, "ERROR: No se pudo asignar memoria para nombres de variables\n");
            exit(1);
        }
        names = new_names;
        *names_ptr = names;
        *cap_ptr = cap;
    }
    names[count] = strdup(name);
    if (!names[count]) {
        fprintf(stderr, "ERROR: No se pudo duplicar el nombre de variable '%s'\n", name);
        exit(1);
    }
    count++;
    *count_ptr = count;
}


