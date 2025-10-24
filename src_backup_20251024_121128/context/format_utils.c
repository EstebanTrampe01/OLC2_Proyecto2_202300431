#include "format_utils.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

const char* format_trim_double(double v, int maxDecimals){
    static char buf[64];
    if(maxDecimals<0) maxDecimals=0;
    if(maxDecimals>15) maxDecimals=15;
    if (v == 0.0) v = 0.0; // normalizar -0.0
    double intpart; double frac = modf(v, &intpart);
    if(fabs(frac) < 1e-12){ // entero
        snprintf(buf, sizeof(buf), "%.1f", intpart); // fuerza .0
        return buf;
    }
    // formateo provisional con precisión fija
    char fmt[16]; snprintf(fmt,sizeof(fmt),"%%.%df", maxDecimals);
    snprintf(buf,sizeof(buf),fmt,v);
    // recorte de ceros a la derecha
    size_t len=strlen(buf);
    while(len>0 && buf[len-1]=='0'){ buf[--len]='\0'; }
    if(len>0 && buf[len-1]=='.'){ buf[--len]='\0'; }
    return buf;
}

const char* format_number(TipoDato tipo, const void* value){
    // Buffer estático separado para evitar colisión con formato anidado (no reentrante).
    static char buf[96];
    switch(tipo){
        case INT: case BYTE: case SHORT: case LONG:
            snprintf(buf,sizeof(buf),"%d", *((const int*)value)); return buf;
        case FLOAT: {
            const char* t = format_trim_float(*((const float*)value), 6);
            snprintf(buf,sizeof(buf),"%s", t); return buf; }
        case DOUBLE: {
            const char* t = format_trim_double(*((const double*)value), 10);
            snprintf(buf,sizeof(buf),"%s", t); return buf; }
        case BOOLEAN:
            snprintf(buf,sizeof(buf),"%s", *((const int*)value)?"true":"false"); return buf;
        case CHAR: {
            unsigned char c = *((const unsigned char*)value);
            if( (c>=32 && c<=126) || c>=160){
                // imprimible latino/ASCII extendido
                snprintf(buf,sizeof(buf),"%c", c);
            } else {
                snprintf(buf,sizeof(buf),"%u", (unsigned)c);
            }
            return buf; }
        default:
            snprintf(buf,sizeof(buf),"?"); return buf;
    }
}

/* Helper específico para impresión de char en distintos módulos */
const char* format_char(unsigned char c){
    static char cbuf[8];
    // Imprimible ASCII básico
    if(c>=32 && c<=126){ cbuf[0]=(char)c; cbuf[1]='\0'; return cbuf; }
    // Rango extendido Latin-1 (mostrar como UTF-8 2 bytes)
    if(c>=160){
        cbuf[0] = (char)(0xC0 | (c >> 6));        // 110xxxxx
        cbuf[1] = (char)(0x80 | (c & 0x3F));      // 10xxxxxx
        cbuf[2] = '\0';
        return cbuf;
    }
    // Otros (control u otros 128-159 ambiguos) -> número decimal
    snprintf(cbuf,sizeof(cbuf),"%u", (unsigned)c);
    return cbuf;
}