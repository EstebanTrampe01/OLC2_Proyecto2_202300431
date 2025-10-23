#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// type_tag values
#define SV_TAG_INT 1
#define SV_TAG_DOUBLE 2
#define SV_TAG_FLOAT 3
#define SV_TAG_BOOLEAN 4
#define SV_TAG_CHAR 5
#define SV_TAG_STRING 6

// Generic helper: receives a tag and a 64-bit value. If tag==SV_TAG_STRING,
// value_bits is interpreted as a pointer to a NUL-terminated char* and the
// function returns a strdup of it. For numeric types the value_bits is reinterpreted
// and formatted into a malloc'd string which the caller must free.

char* string_value_of_any(int type_tag, unsigned long long value_bits) {
    char buf[128];
    char* out = NULL;
    switch (type_tag) {
        case SV_TAG_INT: {
            long v = (long) value_bits;
            snprintf(buf, sizeof(buf), "%ld", v);
            out = strdup(buf);
            break;
        }
        case SV_TAG_DOUBLE: {
            double d; memcpy(&d, &value_bits, sizeof(double));
            snprintf(buf, sizeof(buf), "%.10g", d);
            out = strdup(buf);
            break;
        }
        case SV_TAG_FLOAT: {
            // lower 32 bits contain float
            uint32_t fv = (uint32_t) value_bits;
            float f; memcpy(&f, &fv, sizeof(float));
            snprintf(buf, sizeof(buf), "%.7g", f);
            out = strdup(buf);
            break;
        }
        case SV_TAG_BOOLEAN: {
            int b = (int) value_bits;
            out = strdup(b ? "true" : "false");
            break;
        }
        case SV_TAG_CHAR: {
            char c = (char) value_bits;
            buf[0] = c; buf[1] = '\0';
            out = strdup(buf);
            break;
        }
        case SV_TAG_STRING: {
            const char* s = (const char*) (uintptr_t) value_bits;
            if (!s) return strdup("");
            return strdup(s);
        }
        default:
            return strdup("");
    }
    return out;
}
