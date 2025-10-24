#include "builtins.h"
#include "context/result.h"
#include "context/array.h"
#include "context/format_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "context/error_reporting.h"

typedef struct { AbstractExpresion base; AbstractExpresion* a; } UnaryWrap;
typedef struct { AbstractExpresion base; AbstractExpresion* a; AbstractExpresion* b; } BinaryWrap;
typedef struct { AbstractExpresion base; AbstractExpresion* a; AbstractExpresion* b; int flag; } BinaryFlagWrap;

static int totalElementsRecursive(ArrayValue* arr){
    if(!arr) return 0;
    if(arr->elementType!=ARRAY) return arr->length; /* plano */
    int total=0;
    for(int i=0;i<arr->length;i++){
        ArrayValue* inner = (ArrayValue*)arr->items[i];
        if(inner) total += totalElementsRecursive(inner);
    }
    return total;
}
Result interpretArrayLength(AbstractExpresion* self, Context* ctx){
    UnaryWrap* n=(UnaryWrap*)self; Result r=n->a->interpret(n->a, ctx);
    int* v=malloc(sizeof(int)); *v=0;
    if(r.tipo!=ARRAY||!r.valor){ return nuevoValorResultado(v,INT);} 
    ArrayValue* arr=(ArrayValue*)r.valor; 
    /* Semántica: .length devuelve SIEMPRE la longitud del primer nivel */
    *v = arr->length;
    return nuevoValorResultado(v,INT);
} 

/* Longitud total (flatten) de todos los elementos hoja de un arreglo potencialmente multidimensional */
Result interpretArrayTotalLength(AbstractExpresion* self, Context* ctx){
    UnaryWrap* n=(UnaryWrap*)self; Result r=n->a->interpret(n->a, ctx);
    int* v=malloc(sizeof(int)); *v=0;
    if(r.tipo!=ARRAY||!r.valor){ return nuevoValorResultado(v,INT);} 
    ArrayValue* arr=(ArrayValue*)r.valor; 
    *v = totalElementsRecursive(arr);
    return nuevoValorResultado(v,INT);
}

static Result interpretArrayAdd(AbstractExpresion* self, Context* ctx){
    BinaryWrap* n=(BinaryWrap*)self; Result r=n->a->interpret(n->a,ctx);
    if(r.tipo!=ARRAY||!r.valor){return nuevoValorResultadoVacio();}
    ArrayValue* orig=(ArrayValue*)r.valor; Result val=n->b->interpret(n->b,ctx);

    // Determinar tipo final (promoción a FLOAT o DOUBLE si necesario)
    TipoDato finalType = orig->elementType;
    if((finalType==INT||finalType==BYTE||finalType==SHORT||finalType==LONG) && (val.tipo==FLOAT)) finalType=FLOAT;
    if((finalType==INT||finalType==BYTE||finalType==SHORT||finalType==LONG) && (val.tipo==DOUBLE)) finalType=DOUBLE;
    if(finalType==FLOAT && val.tipo==DOUBLE) finalType=DOUBLE; // promover más

    // Crear nuevo arreglo (copia profunda de valores primitivos / duplicado de cadenas)
    ArrayValue* nuevo = malloc(sizeof(ArrayValue));
    if(!nuevo){ report_runtime_error(self, ctx, "Fallo de memoria (nuevo arreglo)"); return nuevoValorResultadoVacio(); }
    nuevo->length = orig->length + 1;
    nuevo->elementType = finalType;
    nuevo->items = calloc(nuevo->length, sizeof(void*));
    if(!nuevo->items){ free(nuevo); report_runtime_error(self, ctx, "Fallo de memoria (items)"); return nuevoValorResultadoVacio(); }

    // Copiar elementos existentes con conversión si hubo promoción
    for(int i=0;i<orig->length;i++){
        void* src = orig->items[i];
        if(!src){ nuevo->items[i]=NULL; continue; }
        switch(finalType){
            case INT: case BYTE: case SHORT: case LONG: {
                int* v = malloc(sizeof(int)); *v = *((int*)src); nuevo->items[i]=v; break; }
            case FLOAT: {
                float* v = malloc(sizeof(float));
                if(orig->elementType==FLOAT) *v = *((float*)src);
                else *v = (float)(*((int*)src));
                nuevo->items[i]=v; break; }
            case DOUBLE: {
                double* v = malloc(sizeof(double));
                if(orig->elementType==DOUBLE) *v = *((double*)src);
                else if(orig->elementType==FLOAT) *v = (double)(*((float*)src));
                else *v = (double)(*((int*)src));
                nuevo->items[i]=v; break; }
            case BOOLEAN: {
                int* v = malloc(sizeof(int)); *v = *((int*)src); nuevo->items[i]=v; break; }
            case CHAR: {
                char* v = malloc(sizeof(char)); *v = *((char*)src); nuevo->items[i]=v; break; }
            case STRING: {
                if(src){ char* dup=strdup((char*)src); nuevo->items[i]=dup; } else nuevo->items[i]=NULL; break; }
            case ARRAY: default: nuevo->items[i]=NULL; break; // no se soporta add sobre nested arrays aquí
        }
    }

    // Convertir nuevo elemento
    void* convertido=NULL; int compatible=0;
    switch(finalType){
        case INT: case BYTE: case SHORT: case LONG:
            if(val.tipo==INT){ int* v=malloc(sizeof(int)); *v=*(int*)val.valor; convertido=v; compatible=1; }
            break;
        case FLOAT:
            if(val.tipo==FLOAT){ float* v=malloc(sizeof(float)); *v=*(float*)val.valor; convertido=v; compatible=1; }
            else if(val.tipo==INT){ float* v=malloc(sizeof(float)); *v=(float)(*(int*)val.valor); convertido=v; compatible=1; }
            break;
        case DOUBLE:
            if(val.tipo==DOUBLE){ double* v=malloc(sizeof(double)); *v=*(double*)val.valor; convertido=v; compatible=1; }
            else if(val.tipo==FLOAT){ double* v=malloc(sizeof(double)); *v=(double)(*(float*)val.valor); convertido=v; compatible=1; }
            else if(val.tipo==INT){ double* v=malloc(sizeof(double)); *v=(double)(*(int*)val.valor); convertido=v; compatible=1; }
            break;
        case BOOLEAN:
            if(val.tipo==BOOLEAN||val.tipo==INT){ int* v=malloc(sizeof(int)); *v=*(int*)val.valor; convertido=v; compatible=1; }
            break;
        case CHAR:
            if(val.tipo==CHAR){ char* v=malloc(sizeof(char)); *v=*(char*)val.valor; convertido=v; compatible=1; }
            break;
        case STRING:
            if(val.tipo==STRING){ if(val.valor){ char* dup=strdup((char*)val.valor); convertido=dup;} compatible=1; }
            break;
        default: break;
    }
    if(!compatible){ report_runtime_error(self, ctx, "tipo incompatible al agregar elemento a arreglo");
        // liberar nuevo parcial
        for(int i=0;i<orig->length;i++){ if(nuevo->items[i]) free(nuevo->items[i]); }
        free(nuevo->items); free(nuevo); return nuevoValorResultadoVacio(); }
    nuevo->items[nuevo->length-1]=convertido;
    return nuevoValorResultado(nuevo, ARRAY);
}

Result interpretArrayTopLength(AbstractExpresion* self, Context* ctx){
    UnaryWrap* n=(UnaryWrap*)self; Result r=n->a->interpret(n->a, ctx);
    int* v=malloc(sizeof(int)); *v=0;
    if(r.tipo!=ARRAY||!r.valor){ return nuevoValorResultado(v,INT);} 
    ArrayValue* arr=(ArrayValue*)r.valor; 
    *v = arr->length;
    return nuevoValorResultado(v,INT);
}

static Result interpretArraysIndexOf(AbstractExpresion* self, Context* ctx){ BinaryWrap* n=(BinaryWrap*)self; Result r=n->a->interpret(n->a,ctx); Result key=n->b->interpret(n->b,ctx); int* out=malloc(sizeof(int)); *out=-1; if(r.tipo!=ARRAY||!r.valor){ return nuevoValorResultado(out, INT);} ArrayValue* arr=(ArrayValue*)r.valor; for(int i=0;i<arr->length;i++){ if(!arr->items[i]) continue; switch(arr->elementType){ case INT: case BYTE: case SHORT: case LONG: if(key.tipo==INT && *((int*)arr->items[i])==*((int*)key.valor)) { *out=i; i=arr->length; } break; case BOOLEAN: if(key.tipo==BOOLEAN && *((int*)arr->items[i])==*((int*)key.valor)){ *out=i; i=arr->length;} break; case CHAR: if(key.tipo==CHAR && *((char*)arr->items[i])==*((char*)key.valor)){ *out=i; i=arr->length;} break; case STRING: if(key.tipo==STRING && key.valor && arr->items[i] && strcmp((char*)arr->items[i], (char*)key.valor)==0){ *out=i; i=arr->length;} break; default: break; } }
    return nuevoValorResultado(out, INT);
}

static int isAllDigits(const char* s){ if(!s||!*s) return 0; if(*s=='-') { s++; if(!*s) return 0; } for(const char* p=s; *p; ++p) if(*p<'0'||*p>'9') return 0; return 1; }

static Result interpretParseEntero(AbstractExpresion* self, Context* ctx){ UnaryWrap* n=(UnaryWrap*)self; Result r=n->a->interpret(n->a,ctx); if(r.tipo!=STRING||!r.valor||!isAllDigits((char*)r.valor)){ int* v=malloc(sizeof(int)); *v=0; report_runtime_error(self, ctx, "parseInt requiere cadena numérica"); return nuevoValorResultado(v,INT);} int* v=malloc(sizeof(int)); *v=atoi((char*)r.valor); return nuevoValorResultado(v,INT);} 

static Result interpretParseDouble(AbstractExpresion* self, Context* ctx){
    UnaryWrap* n=(UnaryWrap*)self; Result r=n->a->interpret(n->a,ctx);
    if(r.tipo!=STRING||!r.valor){ double* d=malloc(sizeof(double)); *d=0; report_runtime_error(self, ctx, "parseDouble requiere cadena válida"); return nuevoValorResultado(d,DOUBLE);} 
    double* d=malloc(sizeof(double)); *d=strtod((char*)r.valor,NULL); return nuevoValorResultado(d,DOUBLE);
}

static Result interpretParseFloat(AbstractExpresion* self, Context* ctx){
    UnaryWrap* n=(UnaryWrap*)self; Result r=n->a->interpret(n->a,ctx);
    if(r.tipo!=STRING||!r.valor){ float* f=malloc(sizeof(float)); *f=0; report_runtime_error(self, ctx, "parseFloat requiere cadena válida"); return nuevoValorResultado(f,FLOAT);} 
    float* f=malloc(sizeof(float)); *f=strtof((char*)r.valor,NULL); return nuevoValorResultado(f,FLOAT);
}

Result interpretStringValueOf(AbstractExpresion* self, Context* ctx){
    UnaryWrap* n=(UnaryWrap*)self; Result r=n->a->interpret(n->a,ctx);
    char buf[128]; char* out=NULL;
    switch(r.tipo){
        case INT: case BYTE: case SHORT: case LONG:
            snprintf(buf,sizeof(buf),"%d", *((int*)r.valor)); out=strdup(buf); break;
        case FLOAT: {
            const char* f = format_trim_float(*((float*)r.valor), 6);
            out=strdup(f); break; }
        case DOUBLE: {
            const char* d = format_trim_double(*((double*)r.valor), 10);
            out=strdup(d); break; }
        case BOOLEAN:
            out=strdup(*((int*)r.valor)?"true":"false"); break;
        case CHAR: {
            unsigned char cv=*((unsigned char*)r.valor);
            const char* rep = format_char(cv);
            out = strdup(rep); break; }
        case STRING:
            out = r.valor? strdup((char*)r.valor) : strdup("null"); break;
        default:
            out=strdup("null");
    }
    return nuevoValorResultado(out, STRING);
}

static Result interpretStringJoin(AbstractExpresion* self, Context* ctx){ BinaryFlagWrap* n=(BinaryFlagWrap*)self; Result d = n->a->interpret(n->a, ctx); if(d.tipo!=STRING){ char* z=strdup(""); report_runtime_error(self, ctx, "delimitador debe ser cadena"); return nuevoValorResultado(z, STRING);} char* delim = d.valor? (char*)d.valor : ""; if(n->flag){ // array mode
        Result arrR = n->b->interpret(n->b, ctx); if(arrR.tipo!=ARRAY || !arrR.valor){ char* z=strdup(""); return nuevoValorResultado(z, STRING);} ArrayValue* arr=(ArrayValue*)arrR.valor; size_t total=1; for(int i=0;i<arr->length;i++){ if(arr->items[i]) total+=strlen((char*)arr->items[i]); if(i<arr->length-1) total+=strlen(delim); }
    char* res=malloc(total+1); res[0]='\0'; for(int i=0;i<arr->length;i++){ if(arr->items[i]) strcat(res,(char*)arr->items[i]); if(i<arr->length-1) strcat(res,delim);} return nuevoValorResultado(res, STRING);
    } else { // variadic simple: n->b es lista_Expr
    AbstractExpresion* lista = n->b; size_t total=1; for(size_t i=0;i<lista->numHijos;i++){ Result it=lista->hijos[i]->interpret(lista->hijos[i], ctx); if(it.tipo==STRING && it.valor) total+=strlen((char*)it.valor); if(i<lista->numHijos-1) total+=strlen(delim);} char* res=malloc(total+1); res[0]='\0'; for(size_t i=0;i<lista->numHijos;i++){ Result it=lista->hijos[i]->interpret(lista->hijos[i], ctx); if(it.tipo==STRING && it.valor) strcat(res,(char*)it.valor); if(i<lista->numHijos-1) strcat(res,delim);} return nuevoValorResultado(res, STRING); }
}

static void build(AbstractExpresion* b, Result (*fn)(AbstractExpresion*, Context*)) { buildAbstractExpresion(b, fn); }

AbstractExpresion* nuevoArrayLength(AbstractExpresion* a){ UnaryWrap* n=malloc(sizeof(UnaryWrap)); build(&n->base, interpretArrayLength); n->a=a; return (AbstractExpresion*)n; }
AbstractExpresion* nuevoArrayTotalLength(AbstractExpresion* a){ UnaryWrap* n=malloc(sizeof(UnaryWrap)); build(&n->base, interpretArrayTotalLength); n->a=a; return (AbstractExpresion*)n; }
AbstractExpresion* nuevoArrayTopLength(AbstractExpresion* a){ UnaryWrap* n=malloc(sizeof(UnaryWrap)); build(&n->base, interpretArrayTopLength); n->a=a; return (AbstractExpresion*)n; }
AbstractExpresion* nuevoArrayAdd(AbstractExpresion* a, AbstractExpresion* v){ BinaryWrap* n=malloc(sizeof(BinaryWrap)); build(&n->base, interpretArrayAdd); n->a=a; n->b=v; return (AbstractExpresion*)n; }
AbstractExpresion* nuevoArraysIndexOf(AbstractExpresion* a, AbstractExpresion* k){ BinaryWrap* n=malloc(sizeof(BinaryWrap)); build(&n->base, interpretArraysIndexOf); n->a=a; n->b=k; return (AbstractExpresion*)n; }
AbstractExpresion* nuevoParseEntero(AbstractExpresion* s){ UnaryWrap* n=malloc(sizeof(UnaryWrap)); build(&n->base, interpretParseEntero); n->a=s; return (AbstractExpresion*)n; }
AbstractExpresion* nuevoParseDouble(AbstractExpresion* s){ UnaryWrap* n=malloc(sizeof(UnaryWrap)); build(&n->base, interpretParseDouble); n->a=s; return (AbstractExpresion*)n; }
AbstractExpresion* nuevoParseFloat(AbstractExpresion* s){ UnaryWrap* n=malloc(sizeof(UnaryWrap)); build(&n->base, interpretParseFloat); n->a=s; return (AbstractExpresion*)n; }
AbstractExpresion* nuevoStringValueOf(AbstractExpresion* s){ UnaryWrap* n=malloc(sizeof(UnaryWrap)); build(&n->base, interpretStringValueOf); n->a=s; return (AbstractExpresion*)n; }
AbstractExpresion* nuevoStringJoin(AbstractExpresion* d, AbstractExpresion* src, int isArray){ BinaryFlagWrap* n=malloc(sizeof(BinaryFlagWrap)); build(&n->base, interpretStringJoin); n->a=d; n->b=src; n->flag=isArray; return (AbstractExpresion*)n; }
