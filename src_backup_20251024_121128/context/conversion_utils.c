/* Implementación sólo de convertir_valor (API unificada) */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "conversion_utils.h"
#include "tipo_utils.h"

int convertir_valor(TipoDato destino, Result origen, int deepCopySameType, int validaPrecisionEnteros,
                    int liberaOrigenEnExito, void** outValor, char* errorMsg, size_t errorMsgLen){
    if(!outValor) return 0;
    *outValor = NULL;
    if(errorMsg && errorMsgLen>0) errorMsg[0]='\0';

    // Igual tipo
    if(destino == origen.tipo){
        if(destino==STRING){
            if(deepCopySameType && origen.valor){ char* dup=strdup((char*)origen.valor); if(!dup){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0;} *outValor=dup; if(liberaOrigenEnExito && origen.valor) free(origen.valor); return 1; }
            *outValor = origen.valor; return 1;
        }
        if(destino==ARRAY){ *outValor = origen.valor; return 1; }
        // primitivos / char / boolean
        if(destino==BOOLEAN||destino==INT||destino==BYTE||destino==SHORT||destino==LONG||destino==FLOAT||destino==DOUBLE||destino==CHAR){
            if(!deepCopySameType){ *outValor = origen.valor; return 1; }
            // deep copy
            if(destino==INT||destino==BYTE||destino==SHORT||destino==LONG||destino==BOOLEAN){ int* v=malloc(sizeof(int)); if(!v){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0;} *v=*(int*)origen.valor; *outValor=v; if(liberaOrigenEnExito) free(origen.valor); return 1; }
            if(destino==FLOAT){ float* f=malloc(sizeof(float)); if(!f){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0;} *f=*(float*)origen.valor; *outValor=f; if(liberaOrigenEnExito) free(origen.valor); return 1; }
            if(destino==DOUBLE){ double* d=malloc(sizeof(double)); if(!d){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0;} *d=*(double*)origen.valor; *outValor=d; if(liberaOrigenEnExito) free(origen.valor); return 1; }
            if(destino==CHAR){ char* c=malloc(sizeof(char)); if(!c){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0;} *c=*(char*)origen.valor; *outValor=c; if(liberaOrigenEnExito) free(origen.valor); return 1; }
        }
        // fallback
        *outValor = origen.valor; return 1;
    }

    // Reglas de rechazo rápido (excepto CHAR que ahora admite INT->CHAR con validación)
    if(destino==STRING || destino==ARRAY){
        if(errorMsg) snprintf(errorMsg,errorMsgLen,"Asignación inválida a tipo destino");
        return 0;
    }

    if(destino==BOOLEAN){
        if(origen.tipo==BOOLEAN || origen.tipo==INT){
            int* b = malloc(sizeof(int));
            if(!b){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0; }
            *b = (origen.tipo==BOOLEAN)? *(int*)origen.valor : (*(int*)origen.valor!=0);
            *outValor = b;
            if(liberaOrigenEnExito) free(origen.valor);
            return 1;
        }
        if(errorMsg) snprintf(errorMsg,errorMsgLen,"Tipo no permitido para BOOLEAN");
        return 0;
    }

    if(destino==CHAR && es_numerico(origen.tipo)){
        /* Permitir INT/CHAR -> CHAR, y también otros numéricos si ya pasaron compatibilidad general como INT */
        int value;
        switch(origen.tipo){
            case CHAR: value = (int)*(char*)origen.valor; break;
            case INT: case BYTE: case SHORT: case LONG: value = *(int*)origen.valor; break;
            case FLOAT: value = (int)*(float*)origen.valor; break; /* ya se permitió por compatibilidad numérica general */
            case DOUBLE: value = (int)*(double*)origen.valor; break;
            default: value = 0; break;
        }
        if(value < 0 || value > 255){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Valor fuera de rango para char (0-255)"); return 0; }
        char* c = malloc(sizeof(char)); if(!c){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0; }
        *c = (char)value; *outValor = c; if(liberaOrigenEnExito && origen.valor) free(origen.valor); return 1;
    }

    if(es_numerico(destino) && es_numerico(origen.tipo)){
        if(destino==INT||destino==BYTE||destino==SHORT||destino==LONG){
            int* v = malloc(sizeof(int));
            if(!v){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0; }
            if(origen.tipo==FLOAT){
                float f = *(float*)origen.valor;
                if(validaPrecisionEnteros && f!=(int)f){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Pérdida de precisión float->entero"); free(v); return 0; }
                *v = (int)f;
            } else if(origen.tipo==DOUBLE){
                double d = *(double*)origen.valor;
                if(validaPrecisionEnteros && d!=(long long)d){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Pérdida de precisión double->entero"); free(v); return 0; }
                *v = (int)d;
            } else if(origen.tipo==CHAR){
                *v = (int)*(char*)origen.valor;
            } else {
                *v = *(int*)origen.valor;
            }
            *outValor = v;
            if(liberaOrigenEnExito) free(origen.valor);
            return 1;
        }
        if(destino==FLOAT){
            float* f = malloc(sizeof(float));
            if(!f){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0; }
            if(origen.tipo==DOUBLE) *f = (float)*(double*)origen.valor;
            else if(origen.tipo==FLOAT) *f = *(float*)origen.valor;
            else if(origen.tipo==CHAR) *f = (float)*(char*)origen.valor;
            else *f = (float)*(int*)origen.valor;
            *outValor = f;
            if(liberaOrigenEnExito) free(origen.valor);
            return 1;
        }
        if(destino==DOUBLE){
            double* d = malloc(sizeof(double));
            if(!d){ if(errorMsg) snprintf(errorMsg,errorMsgLen,"Sin memoria"); return 0; }
            if(origen.tipo==FLOAT) *d = (double)*(float*)origen.valor;
            else if(origen.tipo==DOUBLE) *d = *(double*)origen.valor;
            else if(origen.tipo==CHAR) *d = (double)*(char*)origen.valor;
            else *d = (double)*(int*)origen.valor;
            *outValor = d;
            if(liberaOrigenEnExito) free(origen.valor);
            return 1;
        }
    }

    if(errorMsg) snprintf(errorMsg,errorMsgLen,"Conversión no soportada");
    return 0;
}
