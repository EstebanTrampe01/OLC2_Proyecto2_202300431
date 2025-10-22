#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
// Local copy of TipoDato constants (must match src/context/result.h order)
#define BOOLEAN 1
#define CHAR 2
#define FLOAT 7
#define INT 5
#define DOUBLE 8
#define STRING 9

// Print a global variable given its storage address (pointer to storage), a TipoDato tag and newline flag.
// This is compiled for AArch64 and linked into the emitted binary.

void print_any_gv(void* gv_addr, int tipo, int newline) {
    if (!gv_addr) return;
    // gv_addr points to the storage (where value is stored as 8-byte for most types)
    switch (tipo) {
        case STRING: {
            const char* s = *(const char**)gv_addr;
            if (s) fputs(s, stdout);
            if (newline) putchar('\n');
            break;
        }
        case INT: {
            long long v = *(long long*)gv_addr;
            printf("%lld", v);
            if (newline) putchar('\n');
            break;
        }
        case DOUBLE: {
            double d = *(double*)gv_addr;
            char buf[64]; snprintf(buf, sizeof(buf), "%.10g", d);
            fputs(buf, stdout);
            if (newline) putchar('\n');
            break;
        }
        case FLOAT: {
            float fv = *(float*)gv_addr;
            char buff[64]; snprintf(buff, sizeof(buff), "%.7g", fv);
            fputs(buff, stdout);
            if (newline) putchar('\n');
            break;
        }
        case CHAR: {
            char c = *(char*)gv_addr;
            putchar(c);
            if (newline) putchar('\n');
            break;
        }
        case BOOLEAN: {
            int b = *(int*)gv_addr;
            fputs(b?"true":"false", stdout);
            if (newline) putchar('\n');
            break;
        }
        default: {
            const char* s = *(const char**)gv_addr;
            if (s) fputs(s, stdout);
            if (newline) putchar('\n');
            break;
        }
    }
    fflush(stdout);
}
