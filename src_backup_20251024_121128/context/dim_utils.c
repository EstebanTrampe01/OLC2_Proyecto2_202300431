#include "dim_utils.h"
#include <stdio.h>

int validar_dimensiones(const int* dims, int n, char* err, size_t errLen){
    if(!dims || n<=0){ if(err&&errLen) snprintf(err,errLen,"Numero de dimensiones invalido"); return 0; }
    if(n>6){ if(err&&errLen) snprintf(err,errLen,"Maximo 6 dimensiones (se recibio %d)", n); return 0; }
    for(int i=0;i<n;i++){
        if(dims[i] <= 0){ if(err&&errLen) snprintf(err,errLen,"Dimension %d invalida (%d)", i, dims[i]); return 0; }
    }
    return 1;
}

int validar_indices(const int* dims, int nDims, const int* indices, int nIdx, char* err, size_t errLen){
    if(!dims || !indices || nDims<=0 || nIdx<=0){ if(err&&errLen) snprintf(err,errLen,"Parametros nulos/invalidos"); return 0; }
    if(nDims != nIdx){ if(err&&errLen) snprintf(err,errLen,"Se esperaban %d indices y se recibieron %d", nDims, nIdx); return 0; }
    for(int i=0;i<nDims;i++){
        int d=dims[i]; int idx=indices[i];
        if(idx<0 || idx>=d){ if(err&&errLen) snprintf(err,errLen,"Indice %d fuera de rango (%d de %d)", i, idx, d); return 0; }
    }
    return 1;
}

int calcular_offset_lineal(const int* dims, int n, const int* indices, int nIdx, long* outOffset, int validate, char* err, size_t errLen){
    if(!outOffset){ if(err&&errLen) snprintf(err,errLen,"outOffset nulo"); return 0; }
    if(validate){ if(!validar_dimensiones(dims,n,err,errLen)) return 0; if(!validar_indices(dims,n,indices,nIdx,err,errLen)) return 0; }
    long offset = 0; long stride = 1;
    for(int i=n-1;i>=0;i--){ offset += indices[i]*stride; stride *= dims[i]; }
    *outOffset = offset;
    return 1;
}
