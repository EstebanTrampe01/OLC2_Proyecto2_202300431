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
        cap = (cap == 0) ? 8 : cap * 2;
        names = (char**)realloc(names, sizeof(char*) * cap);
        *names_ptr = names;
        *cap_ptr = cap;
    }
    names[count] = strdup(name);
    count++;
    *count_ptr = count;
}


