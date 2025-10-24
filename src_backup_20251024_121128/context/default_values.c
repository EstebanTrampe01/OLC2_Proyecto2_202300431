#include <stdlib.h>
#include "default_values.h"

int valor_por_defecto(TipoDato tipo, void** outValor, TipoDato* outTipoReal){
    if(!outValor || !outTipoReal) return 0;
    *outValor=NULL; *outTipoReal=tipo;
    switch(tipo){
        case BYTE: case SHORT: case INT: case LONG: {
            int* v = malloc(sizeof(int)); if(!v) return 0; *v=0; *outValor=v; return 1; }
        case FLOAT: { float* f = malloc(sizeof(float)); if(!f) return 0; *f=0.0f; *outValor=f; return 1; }
        case DOUBLE:{ double* d = malloc(sizeof(double)); if(!d) return 0; *d=0.0; *outValor=d; return 1; }
        case BOOLEAN:{ int* b = malloc(sizeof(int)); if(!b) return 0; *b=0; *outValor=b; return 1; }
        case CHAR:  { char* c = malloc(sizeof(char)); if(!c) return 0; *c='\0'; *outValor=c; return 1; }
    case STRING:{ char* s = malloc(1); if(!s) return 0; s[0]='\0'; *outValor=s; *outTipoReal=STRING; return 1; }
        case NULO:  { *outValor=NULL; return 1; }
        default: return 0; // VOID, BREAK, CONTINUE, RETURN, ARRAY u otros no tienen default directo
    }
}
