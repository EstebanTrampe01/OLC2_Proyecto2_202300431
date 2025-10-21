#include "array.h"
#include "context/context.h"
#include "context/result.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "context/error_reporting.h"
#include "context/conversion_utils.h"
#include "context/default_values.h"

// Declaración: tipo[] nombre = new tipo[exprLength]
typedef struct { AbstractExpresion base; TipoDato elemTipo; char* nombre; AbstractExpresion* lengthExpr; } ArrayDecl;
// Literal: tipo[] nombre = { listaValores }
typedef struct { AbstractExpresion base; TipoDato elemTipo; char* nombre; AbstractExpresion* listaValores; } ArrayLiteralDecl;
// Acceso: arreglo[indice]
typedef struct { AbstractExpresion base; AbstractExpresion* arreglo; AbstractExpresion* indice; } ArrayAcceso;
// Asignación elemento: nombre[indice] = valor (o compound)
typedef struct { AbstractExpresion base; char* nombre; AbstractExpresion* indice; AbstractExpresion* valor; CompoundOp op; } ArrayAsignacionElem;
// Asignación multi-d genérica (soporta compound): nombre[i][j][k]... op= valor (indicesLista es listaExpresiones)
typedef struct { AbstractExpresion base; char* nombre; AbstractExpresion* indicesLista; AbstractExpresion* valor; CompoundOp op; } MultiArrayAsignacionElem;
// Acceso linealizado: dado array (que puede ser multi-d) y un índice lineal, devolver el n-ésimo elemento hoja
typedef struct { AbstractExpresion base; AbstractExpresion* arreglo; AbstractExpresion* linearIndex; } ArrayLinearAccess;

static void resolver_pos_array(AbstractExpresion* nodo, int* l, int* c){
    if(!nodo || *l>0) return;
    if(nodo->linea>0){ *l=nodo->linea; *c=nodo->columna; return; }
    for(size_t i=0;i<nodo->numHijos;i++){
        resolver_pos_array(nodo->hijos[i], l, c);
        if(*l>0) return;
    }
}

Result interpretArrayDecl(AbstractExpresion* self, Context* context) {
    ArrayDecl* n = (ArrayDecl*)self;
    Result lenR = n->lengthExpr->interpret(n->lengthExpr, context);
    if (lenR.tipo != INT) { report_runtime_error(self, context, "Tamaño de array debe ser int"); return nuevoValorResultadoVacio(); }
    int len = *((int*)lenR.valor);
    if (len < 0) { report_runtime_error(self, context, "Tamaño negativo de array"); return nuevoValorResultadoVacio(); }
    ArrayValue* arr = nuevoArrayValue(n->elemTipo, len);
    Symbol* s = nuevoVariable(n->nombre, arr, ARRAY, 0);
    s->linea = self->linea; s->columna = self->columna;
    if(s->linea==0){ int l=0,c=0; resolver_pos_array(self,&l,&c); if(l>0){ s->linea=l; s->columna=c; } }
    agregarSymbol(context, s);
    return nuevoValorResultadoVacio();
}

Result interpretArrayLiteralDecl(AbstractExpresion* self, Context* context) {
    ArrayLiteralDecl* n = (ArrayLiteralDecl*)self;
    // listaValores es un nodo listaExpresiones
    AbstractExpresion* lista = n->listaValores;
    int len = (int)lista->numHijos;
    ArrayValue* arr = nuevoArrayValue(n->elemTipo, len);
    for (int i=0;i<len;i++) {
        Result vr = lista->hijos[i]->interpret(lista->hijos[i], context);
    void* convertido=NULL; char err[64]; int ok = convertir_valor(n->elemTipo, vr, (n->elemTipo==STRING)?1:0, 1, 0, &convertido, err, sizeof(err));
        if(!ok){
            report_runtime_error(self, context, "Tipo incompatible en literal de array (pos %d)", i);
            void* defv=NULL; TipoDato tr=n->elemTipo; if(valor_por_defecto(n->elemTipo,&defv,&tr)) convertido=defv; else convertido=NULL;
        }
        if (arr->items[i]) free(arr->items[i]);
        arr->items[i] = convertido;
    }
    Symbol* s = nuevoVariable(n->nombre, arr, ARRAY, 0);
    s->linea = self->linea; s->columna = self->columna;
    if(s->linea==0){ int l=0,c=0; resolver_pos_array(self,&l,&c); if(l>0){ s->linea=l; s->columna=c; } }
    agregarSymbol(context, s);
    return nuevoValorResultadoVacio();
}

Result interpretArrayAcceso(AbstractExpresion* self, Context* context) {
    ArrayAcceso* n = (ArrayAcceso*)self;
    Result arrR = n->arreglo->interpret(n->arreglo, context);
    if (arrR.tipo != ARRAY) { report_runtime_error(self, context, "Intento de indexar algo que no es array"); return nuevoValorResultadoVacio(); }
    ArrayValue* arr = (ArrayValue*)arrR.valor;
    Result idxR = n->indice->interpret(n->indice, context);
    if (idxR.tipo != INT) { report_runtime_error(self, context, "Índice debe ser int"); return nuevoValorResultadoVacio(); }
    int idx = *((int*)idxR.valor);
    if (idx < 0 || idx >= arr->length) { report_runtime_error(self, context, "Índice fuera de rango"); return nuevoValorResultadoVacio(); }
    // devolver valor del elemento sin copiar
    return nuevoValorResultado(arr->items[idx], arr->elementType);
}

static void aplicar_compound_simple(void** slot, TipoDato elementoTipo, CompoundOp op, Result rhs, Result old){
    if(op==COP_NONE) return; // nada especial
    if(!old.valor || !rhs.valor) return;
    // Sólo soportamos numéricos básicos INT/DOUBLE por ahora
    double lhs=0, rv=0; int lhsInt=0, rhsInt=0; int esInt= (elementoTipo==INT || elementoTipo==LONG || elementoTipo==SHORT || elementoTipo==BYTE || elementoTipo==BOOLEAN || elementoTipo==CHAR);
    // obtener lhs
    if(old.tipo==INT) lhs = *(int*)old.valor; else if(old.tipo==DOUBLE) lhs=*(double*)old.valor; else return;
    if(rhs.tipo==INT) rv=*(int*)rhs.valor; else if(rhs.tipo==DOUBLE) rv=*(double*)rhs.valor; else return;
    double res=lhs;
    switch(op){
        case COP_ADD: res=lhs+rv; break;
        case COP_SUB: res=lhs-rv; break;
        case COP_MUL: res=lhs*rv; break;
        case COP_DIV: if(rv!=0) res=lhs/rv; break;
        case COP_MOD: if(rv!=0) res=(int)lhs % (int)rv; break;
        default: break;
    }
    if(esInt){ int* nv=malloc(sizeof(int)); *nv=(int)res; if(*slot) free(*slot); *slot=nv; }
    else if(elementoTipo==DOUBLE){ double* dv=malloc(sizeof(double)); *dv=res; if(*slot) free(*slot); *slot=dv; }
}

Result interpretArrayAsignacionElem(AbstractExpresion* self, Context* context) {
    ArrayAsignacionElem* n = (ArrayAsignacionElem*)self;
    Symbol* s = buscarTablaSimbolos(context, n->nombre);
    if (!s || s->tipo != ARRAY) { report_runtime_error(self, context, "'%s' no es un array", n->nombre); return nuevoValorResultadoVacio(); }
    ArrayValue* arr = (ArrayValue*)s->valor;
    Result idxR = n->indice->interpret(n->indice, context);
    if (idxR.tipo != INT) { report_runtime_error(self, context, "Índice debe ser int"); return nuevoValorResultadoVacio(); }
    int idx = *((int*)idxR.valor);
    if (idx < 0 || idx >= arr->length) { report_runtime_error(self, context, "Índice fuera de rango"); return nuevoValorResultadoVacio(); }
    Result oldR = nuevoValorResultado(arr->items[idx], arr->elementType);
    Result valR = n->valor->interpret(n->valor, context);
    void* convertido=NULL; char err[64]; int ok = convertir_valor(arr->elementType, valR, 1, 1, 0, &convertido, err, sizeof(err));
    if(!ok){ report_runtime_error(self, context, "Tipo incompatible en asignación de elemento"); return nuevoValorResultadoVacio(); }
    if(n->op!=COP_NONE){
        // aplicar compound usando el valor convertido como RHS pero la operación se basa en oldR
        // Para consistencia, usamos valR original (ya convertido para compatibilidad)
        aplicar_compound_simple(&arr->items[idx], arr->elementType, n->op, valR, oldR);
        if(convertido) free(convertido);
    } else {
        if(arr->items[idx]) free(arr->items[idx]);
        arr->items[idx]=convertido;
    }
    return nuevoValorResultadoVacio();
}

static int flattenFetch(ArrayValue* arr, int* targetIdx, void** out, TipoDato* outType){
    if(!arr) return 0;
    if(arr->elementType!=ARRAY){
        for(int i=0;i<arr->length;i++){
            if(*targetIdx==0){ *out=arr->items[i]; *outType=arr->elementType; return 1; }
            (*targetIdx)--;
        }
        return 0;
    } else {
        for(int i=0;i<arr->length;i++){
            ArrayValue* inner=(ArrayValue*)arr->items[i];
            if(flattenFetch(inner,targetIdx,out,outType)) return 1;
        }
        return 0;
    }
}

Result interpretArrayLinearAccess(AbstractExpresion* self, Context* context){
    ArrayLinearAccess* n=(ArrayLinearAccess*)self; Result arrR=n->arreglo->interpret(n->arreglo,context); if(arrR.tipo!=ARRAY||!arrR.valor){ report_runtime_error(self, context, "Acceso lineal sobre no-array"); return nuevoValorResultadoVacio(); }
    Result idxR=n->linearIndex->interpret(n->linearIndex,context); if(idxR.tipo!=INT){ report_runtime_error(self, context, "Índice lineal debe ser int"); return nuevoValorResultadoVacio(); }
    int idx = *((int*)idxR.valor); if(idx<0){ report_runtime_error(self, context, "Índice lineal negativo"); return nuevoValorResultadoVacio(); }
    ArrayValue* arr=(ArrayValue*)arrR.valor; void* out=NULL; TipoDato t=NULO; int ti=idx; if(!flattenFetch(arr,&ti,&out,&t)){ report_runtime_error(self, context, "Índice lineal fuera de rango"); return nuevoValorResultadoVacio(); }
    return nuevoValorResultado(out,t);
}

Result interpretMultiArrayAsignacionElem(AbstractExpresion* self, Context* context) {
    MultiArrayAsignacionElem* n = (MultiArrayAsignacionElem*)self;
    Symbol* s = buscarTablaSimbolos(context, n->nombre);
    if (!s || s->tipo != ARRAY) { report_runtime_error(self, context, "'%s' no es un array", n->nombre) ; return nuevoValorResultadoVacio(); }
    ArrayValue* current = (ArrayValue*)s->valor;
    size_t dims = n->indicesLista->numHijos;
    if (dims==0) { report_runtime_error(self, context, "Sin índices en asignación multi-d"); return nuevoValorResultadoVacio(); }
    if (dims > 6) { report_runtime_error(self, context, "Máximo 6 dimensiones soportadas (se dio %zu)", dims); return nuevoValorResultadoVacio(); }
    // Navegar hasta el penúltimo nivel
    for (size_t i=0;i<dims;i++) {
        AbstractExpresion* idxExpr = n->indicesLista->hijos[i];
        Result idxR = idxExpr->interpret(idxExpr, context);
    if (idxR.tipo != INT) { report_runtime_error(self, context, "Índice %zu debe ser int", i); return nuevoValorResultadoVacio(); }
        int idx = *((int*)idxR.valor);
    if (idx < 0 || idx >= current->length) { report_runtime_error(self, context, "Índice %zu fuera de rango", i); return nuevoValorResultadoVacio(); }
        if (i == dims-1) {
            // nivel final
            Result oldR = nuevoValorResultado(current->items[idx], current->elementType);
            Result valR = n->valor->interpret(n->valor, context);
            void* convertido=NULL; char err[64]; int ok = convertir_valor(current->elementType, valR, 1, 1, 0, &convertido, err, sizeof(err));
            if(!ok){ report_runtime_error(self, context, "Tipo incompatible en asignación multi-d"); return nuevoValorResultadoVacio(); }
            if(n->op!=COP_NONE){
                aplicar_compound_simple(&current->items[idx], current->elementType, n->op, valR, oldR);
                if(convertido) free(convertido);
            } else {
                if (current->items[idx]) free(current->items[idx]);
                current->items[idx]=convertido;
            }
            return nuevoValorResultadoVacio();
        } else {
            // descender un nivel
            if (current->elementType != ARRAY) { report_runtime_error(self, context, "Demasiados índices para array base"); return nuevoValorResultadoVacio(); }
            current = (ArrayValue*)current->items[idx];
            if (!current) { report_runtime_error(self, context, "Sub-array nulo en nivel %zu", i); return nuevoValorResultadoVacio(); }
        }
    }
    return nuevoValorResultadoVacio();
}

AbstractExpresion* nuevoArrayDeclaracion(TipoDato tipoElemento, char* nombre, AbstractExpresion* exprLength) {
    ArrayDecl* n = malloc(sizeof(ArrayDecl));
    n->elemTipo = tipoElemento; n->nombre = nombre; n->lengthExpr = exprLength;
    buildAbstractExpresion(&n->base, interpretArrayDecl);
    if (exprLength) agregarHijo((AbstractExpresion*)n, exprLength); // no usado directamente pero para liberar
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoArrayLiteralDeclaracion(TipoDato tipoElemento, char* nombre, AbstractExpresion* listaValores) {
    ArrayLiteralDecl* n = malloc(sizeof(ArrayLiteralDecl));
    n->elemTipo = tipoElemento; n->nombre = nombre; n->listaValores = listaValores;
    buildAbstractExpresion(&n->base, interpretArrayLiteralDecl);
    if (listaValores) agregarHijo((AbstractExpresion*)n, listaValores);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoArrayAcceso(AbstractExpresion* arregloExpr, AbstractExpresion* indiceExpr) {
    ArrayAcceso* n = malloc(sizeof(ArrayAcceso));
    n->arreglo = arregloExpr; n->indice = indiceExpr;
    buildAbstractExpresion(&n->base, interpretArrayAcceso);
    if (arregloExpr) agregarHijo((AbstractExpresion*)n, arregloExpr);
    if (indiceExpr) agregarHijo((AbstractExpresion*)n, indiceExpr);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoArrayAsignacionElemento(char* nombre, AbstractExpresion* indiceExpr, AbstractExpresion* valorExpr) {
    ArrayAsignacionElem* n = malloc(sizeof(ArrayAsignacionElem));
    n->nombre = nombre; n->indice = indiceExpr; n->valor = valorExpr; n->op = COP_NONE;
    buildAbstractExpresion(&n->base, interpretArrayAsignacionElem);
    if (indiceExpr) agregarHijo((AbstractExpresion*)n, indiceExpr);
    if (valorExpr) agregarHijo((AbstractExpresion*)n, valorExpr);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoArrayLinearAccess(AbstractExpresion* arregloExpr, AbstractExpresion* linearIdx){
    ArrayLinearAccess* n=malloc(sizeof(ArrayLinearAccess)); n->arreglo=arregloExpr; n->linearIndex=linearIdx; buildAbstractExpresion(&n->base, interpretArrayLinearAccess); if(arregloExpr) agregarHijo((AbstractExpresion*)n,arregloExpr); if(linearIdx) agregarHijo((AbstractExpresion*)n,linearIdx); return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoMultiArrayAsignacionElemento(char* nombre, AbstractExpresion* indicesLista, AbstractExpresion* valorExpr) {
    MultiArrayAsignacionElem* n = malloc(sizeof(MultiArrayAsignacionElem));
    n->nombre = nombre; n->indicesLista = indicesLista; n->valor = valorExpr; n->op = COP_NONE;
    buildAbstractExpresion(&n->base, interpretMultiArrayAsignacionElem);
    if (indicesLista) agregarHijo((AbstractExpresion*)n, indicesLista);
    if (valorExpr) agregarHijo((AbstractExpresion*)n, valorExpr);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoArrayAsignacionElementoCompound(char* nombre, AbstractExpresion* indiceExpr, AbstractExpresion* valorExpr, CompoundOp op){
    ArrayAsignacionElem* n = malloc(sizeof(ArrayAsignacionElem));
    n->nombre = nombre; n->indice = indiceExpr; n->valor = valorExpr; n->op = op;
    buildAbstractExpresion(&n->base, interpretArrayAsignacionElem);
    if (indiceExpr) agregarHijo((AbstractExpresion*)n, indiceExpr);
    if (valorExpr) agregarHijo((AbstractExpresion*)n, valorExpr);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoMultiArrayAsignacionElementoCompound(char* nombre, AbstractExpresion* indicesLista, AbstractExpresion* valorExpr, CompoundOp op){
    MultiArrayAsignacionElem* n = malloc(sizeof(MultiArrayAsignacionElem));
    n->nombre = nombre; n->indicesLista = indicesLista; n->valor = valorExpr; n->op = op;
    buildAbstractExpresion(&n->base, interpretMultiArrayAsignacionElem);
    if (indicesLista) agregarHijo((AbstractExpresion*)n, indicesLista);
    if (valorExpr) agregarHijo((AbstractExpresion*)n, valorExpr);
    return (AbstractExpresion*)n;
}

/* Declaración de array a partir de una expresión que en runtime debe retornar ARRAY.
   Se interpreta evaluando la expresión y validando que sea ARRAY; si no lo es, se crea vacío. */
typedef struct { AbstractExpresion base; TipoDato elemTipo; char* nombre; AbstractExpresion* origen; } ArrayDeclFromExpr;
Result interpretArrayDeclFromExpr(AbstractExpresion* self, Context* ctx){
    ArrayDeclFromExpr* n=(ArrayDeclFromExpr*)self; Result r=n->origen->interpret(n->origen, ctx);
    if (r.tipo!=ARRAY || !r.valor){ report_semantic_error(self, ctx, "Tipos incompatibles en asignación a arreglo '%s'", n->nombre); agregarSymbol(ctx, nuevoVariable(n->nombre, NULL, NULO, 0)); return nuevoValorResultadoVacio(); }
    ArrayValue* arr=(ArrayValue*)r.valor; /* opcional: validar elemento */
    agregarSymbol(ctx, nuevoVariable(n->nombre, arr, ARRAY, 0));
    return nuevoValorResultadoVacio(); }

AbstractExpresion* nuevoArrayDeclaracionDesdeExpr(TipoDato tipoElem, char* nombre, AbstractExpresion* exprArray){
    ArrayDeclFromExpr* n = malloc(sizeof(ArrayDeclFromExpr));
    n->elemTipo=tipoElem; n->nombre=nombre; n->origen=exprArray; buildAbstractExpresion(&n->base, interpretArrayDeclFromExpr);
    if (exprArray) agregarHijo((AbstractExpresion*)n, exprArray);
    return (AbstractExpresion*)n; }