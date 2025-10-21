#include <stdlib.h>
#include <string.h>
#include "array_element_utils.h"
#include "tipo_utils.h"

int convertir_elemento_array(TipoDato destino, Result origen, int deepCopySameType, void** outValor){
    if(!outValor) return 0;
    *outValor=NULL;
    // Igual tipo
    if(destino == origen.tipo){
        switch(destino){
            case INT: case BYTE: case SHORT: case LONG: case BOOLEAN:
            case FLOAT: case DOUBLE: case CHAR: {
                if(!deepCopySameType){ *outValor = origen.valor; return 1; }
                /* deep copy */
                if(destino==INT||destino==BYTE||destino==SHORT||destino==LONG||destino==BOOLEAN){ int* v=malloc(sizeof(int)); if(!v) return 0; *v=*(int*)origen.valor; *outValor=v; free(origen.valor); return 1; }
                if(destino==FLOAT){ float* f=malloc(sizeof(float)); if(!f) return 0; *f=*(float*)origen.valor; *outValor=f; free(origen.valor); return 1; }
                if(destino==DOUBLE){ double* d=malloc(sizeof(double)); if(!d) return 0; *d=*(double*)origen.valor; *outValor=d; free(origen.valor); return 1; }
                if(destino==CHAR){ char* c=malloc(sizeof(char)); if(!c) return 0; *c=*(char*)origen.valor; *outValor=c; free(origen.valor); return 1; }
                break; }
            case STRING: {
                if(deepCopySameType){ if(origen.valor){ char* dup=strdup((char*)origen.valor); *outValor=dup; free(origen.valor);} else *outValor=NULL; return 1; }
                *outValor = origen.valor; return 1; }
            case ARRAY: { *outValor = origen.valor; return 1; }
            default: return 0;
        }
    }
    // STRING destino solo acepta STRING
    if(destino==STRING) return 0;
    if(destino==ARRAY) return 0;
    if(destino==CHAR) return 0; // no conversiones implícitas
    if(destino==BOOLEAN){
        if(origen.tipo==BOOLEAN || origen.tipo==INT){ int* b=malloc(sizeof(int)); if(!b) return 0; *b = (origen.tipo==BOOLEAN)?*(int*)origen.valor:(*(int*)origen.valor!=0); *outValor=b; if(origen.tipo!=STRING && origen.tipo!=ARRAY) free(origen.valor); return 1; }
        return 0;
    }
    if(es_numerico(destino) && es_numerico(origen.tipo)){
        if(destino==FLOAT){ float* f=malloc(sizeof(float)); if(!f) return 0; if(origen.tipo==DOUBLE) *f=(float)*(double*)origen.valor; else if(origen.tipo==FLOAT) *f=*(float*)origen.valor; else if(origen.tipo==CHAR) *f=(float)*(char*)origen.valor; else *f=(float)*(int*)origen.valor; *outValor=f; if(origen.tipo!=STRING && origen.tipo!=ARRAY) free(origen.valor); return 1; }
        if(destino==DOUBLE){ double* d=malloc(sizeof(double)); if(!d) return 0; if(origen.tipo==FLOAT) *d=(double)*(float*)origen.valor; else if(origen.tipo==DOUBLE) *d=*(double*)origen.valor; else if(origen.tipo==CHAR) *d=(double)*(char*)origen.valor; else *d=(double)*(int*)origen.valor; *outValor=d; if(origen.tipo!=STRING && origen.tipo!=ARRAY) free(origen.valor); return 1; }
        if(destino==INT||destino==BYTE||destino==SHORT||destino==LONG){
            int* v=malloc(sizeof(int)); if(!v) return 0;
            if(origen.tipo==FLOAT){ float f=*(float*)origen.valor; if(f!=(int)f){ free(v); return 0; } *v=(int)f; }
            else if(origen.tipo==DOUBLE){ double d=*(double*)origen.valor; if(d!=(int)d){ free(v); return 0; } *v=(int)d; }
            else if(origen.tipo==CHAR){ *v=(int)*(char*)origen.valor; }
            else *v=*(int*)origen.valor;
            *outValor=v;
            if(origen.tipo!=STRING && origen.tipo!=ARRAY) free(origen.valor);
            return 1; }
    }
    return 0;
}
