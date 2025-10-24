#include "matrix.h"
#include "array.h"
#include "context/context.h"
#include "context/result.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "context/error_reporting.h"
#include "context/default_values.h"
#include "context/conversion_utils.h"
#include "context/dim_utils.h"

static void resolver_pos_matrix(AbstractExpresion* nodo, int* l, int* c){
    if(!nodo || (l && *l>0)) return;
    if(nodo->linea>0){ if(l) *l=nodo->linea; if(c) *c=nodo->columna; return; }
    for(size_t i=0;i<nodo->numHijos;i++) resolver_pos_matrix(nodo->hijos[i], l, c);
}

// Declaración: tipo[][] id = new tipo[filas][cols];
typedef struct { AbstractExpresion base; TipoDato elemTipo; char* nombre; AbstractExpresion* filasExpr; AbstractExpresion* colsExpr; } MatrixDecl;
// Literal: tipo[][] id = { {..}, {..} } ; cada fila es listaExpresiones
typedef struct { AbstractExpresion base; TipoDato elemTipo; char* nombre; AbstractExpresion* filasLista; } MatrixLiteralDecl;
// Asignación elemento: id[f][c] = valor; (soporta compound)
typedef struct { AbstractExpresion base; char* nombre; AbstractExpresion* fila; AbstractExpresion* col; AbstractExpresion* valor; CompoundOp op; } MatrixAsignacionElem;
// Multi-dimension generic new decl
typedef struct { AbstractExpresion base; TipoDato elemTipo; char* nombre; int dims; AbstractExpresion** dimExprs; } MultiArrayDecl;
// 3D literal: tipo[][][] id = { bloque2D, bloque2D, ... }
typedef struct { AbstractExpresion base; TipoDato elemTipo; char* nombre; AbstractExpresion* bloques2DLista; } Array3DLiteralDecl;

static ArrayValue* crearMatrizVacia(TipoDato elemTipo, int filas, int cols) {
    ArrayValue* outer = nuevoArrayValue(ARRAY, filas);
    for (int i=0;i<filas;i++) {
        outer->items[i] = nuevoArrayValue(elemTipo, cols);
    }
    return outer;
}

static Result interpretMatrixDecl(AbstractExpresion* self, Context* context) {
    MatrixDecl* n = (MatrixDecl*)self;
    Result fR = n->filasExpr->interpret(n->filasExpr, context);
    Result cR = n->colsExpr->interpret(n->colsExpr, context);
    if (fR.tipo != INT || cR.tipo != INT) { report_runtime_error(self, context, "Dimensiones de matriz deben ser enteras"); return nuevoValorResultadoVacio(); }
    int filas = *((int*)fR.valor); int cols = *((int*)cR.valor);
    int dims2[2] = { filas, cols }; char derr[64];
    if(!validar_dimensiones(dims2,2,derr,sizeof(derr))){ report_runtime_error(self, context, "%s", derr); return nuevoValorResultadoVacio(); }
    ArrayValue* m = crearMatrizVacia(n->elemTipo, filas, cols);
    Symbol* s = nuevoVariable(n->nombre, m, ARRAY, 0); s->linea=self->linea; s->columna=self->columna; if(s->linea==0){ int l=0,c=0; resolver_pos_matrix(self,&l,&c); if(l>0){ s->linea=l; s->columna=c; }} agregarSymbol(context, s);
    return nuevoValorResultadoVacio(); }


static Result interpretMatrixLiteralDecl(AbstractExpresion* self, Context* context) {
    MatrixLiteralDecl* n = (MatrixLiteralDecl*)self;
    AbstractExpresion* filasLista = n->filasLista;
    int filas = (int)filasLista->numHijos;
    if (filas == 0) { report_runtime_error(self, context, "Matriz literal vacía"); return nuevoValorResultadoVacio(); }
    AbstractExpresion* fila0 = filasLista->hijos[0];
    int cols = (int)fila0->numHijos;
    ArrayValue* outer = nuevoArrayValue(ARRAY, filas);
    for (int r=0;r<filas;r++) {
        AbstractExpresion* filaNodo = filasLista->hijos[r];
        if ((int)filaNodo->numHijos != cols) {
            report_runtime_error(self, context, "Filas de distinta longitud en matriz literal");
        }
        ArrayValue* row = nuevoArrayValue(n->elemTipo, cols);
        for (int c=0;c<cols && c<(int)filaNodo->numHijos;c++) {
            Result vr = filaNodo->hijos[c]->interpret(filaNodo->hijos[c], context);
            void* convertido=NULL; char err[64]; int ok = convertir_valor(n->elemTipo, vr, (n->elemTipo==STRING)?1:0, 1, 0, &convertido, err, sizeof(err));
            if(!ok){
                report_runtime_error(self, context, "Tipo incompatible en matriz literal (%d,%d)", r, c);
                void* defv=NULL; TipoDato tr=n->elemTipo; if(valor_por_defecto(n->elemTipo,&defv,&tr)) convertido=defv; else convertido=NULL;
            }
            if(row->items[c]) free(row->items[c]);
            row->items[c]=convertido;
        }
        outer->items[r] = row;
    }
    Symbol* s = nuevoVariable(n->nombre, outer, ARRAY, 0); s->linea=self->linea; s->columna=self->columna; if(s->linea==0){ int l=0,c=0; resolver_pos_matrix(self,&l,&c); if(l>0){ s->linea=l; s->columna=c; }} agregarSymbol(context, s);
    return nuevoValorResultadoVacio();
}

static void aplicar_compound_matrix(void** slot, TipoDato elemTipo, CompoundOp op, Result rhs, Result old){
    if(op==COP_NONE) return;
    if(!old.valor || !rhs.valor) return;
    double lhs=0, rv=0;
    if(old.tipo==INT) lhs=*(int*)old.valor; else if(old.tipo==DOUBLE) lhs=*(double*)old.valor; else return;
    if(rhs.tipo==INT) rv=*(int*)rhs.valor; else if(rhs.tipo==DOUBLE) rv=*(double*)rhs.valor; else return;
    double res=lhs;
    switch(op){ case COP_ADD: res=lhs+rv; break; case COP_SUB: res=lhs-rv; break; case COP_MUL: res=lhs*rv; break; case COP_DIV: if(rv!=0) res=lhs/rv; break; case COP_MOD: if(rv!=0) res=(int)lhs % (int)rv; break; default: break; }
    if(elemTipo==INT){ int* nv=malloc(sizeof(int)); *nv=(int)res; if(*slot) free(*slot); *slot=nv; }
    else if(elemTipo==DOUBLE){ double* dv=malloc(sizeof(double)); *dv=res; if(*slot) free(*slot); *slot=dv; }
}

static Result interpretMatrixAsignacionElem(AbstractExpresion* self, Context* context) {
    MatrixAsignacionElem* n = (MatrixAsignacionElem*)self;
    Symbol* s = buscarTablaSimbolos(context, n->nombre);
    if (!s || s->tipo != ARRAY) { report_runtime_error(self, context, "'%s' no es matriz", n->nombre); return nuevoValorResultadoVacio(); }
    ArrayValue* outer = (ArrayValue*)s->valor;
    if (outer->elementType != ARRAY) { report_runtime_error(self, context, "'%s' no es matriz 2D", n->nombre); return nuevoValorResultadoVacio(); }
    Result fR = n->fila->interpret(n->fila, context);
    Result cR = n->col->interpret(n->col, context);
    if (fR.tipo != INT || cR.tipo != INT) { report_runtime_error(self, context, "Índices de matriz deben ser enteros"); return nuevoValorResultadoVacio(); }
    int f = *((int*)fR.valor); int c = *((int*)cR.valor);
    int filas = outer->length;
    int cols = (filas>0 && outer->items[0]) ? ((ArrayValue*)outer->items[0])->length : 0;
    // Mantener mensajes originales para compatibilidad con pruebas existentes
    if(f < 0 || f >= filas) { report_runtime_error(self, context, "Índice de fila fuera de rango"); return nuevoValorResultadoVacio(); }
    if(c < 0 || c >= cols) { report_runtime_error(self, context, "Índice de columna fuera de rango"); return nuevoValorResultadoVacio(); }
    ArrayValue* row = (ArrayValue*)outer->items[f];
    Result oldR = nuevoValorResultado(row->items[c], row->elementType);
    Result valR = n->valor->interpret(n->valor, context);
    void* convertido=NULL; char err[64]; int ok = convertir_valor(row->elementType, valR, 1, 1, 0, &convertido, err, sizeof(err));
    if(!ok){ report_runtime_error(self, context, "Tipo incompatible en asignación de matriz"); return nuevoValorResultadoVacio(); }
    if(n->op!=COP_NONE){ aplicar_compound_matrix(&row->items[c], row->elementType, n->op, valR, oldR); if(convertido) free(convertido); }
    else { if(row->items[c]) free(row->items[c]); row->items[c]=convertido; }
    return nuevoValorResultadoVacio(); }


static ArrayValue* crearMultiArrayVacio(TipoDato elemTipo, int dims, int* sizes, int nivel) {
    if (nivel == dims-1) {
        return nuevoArrayValue(elemTipo, sizes[nivel]);
    }
    ArrayValue* arr = nuevoArrayValue(ARRAY, sizes[nivel]);
    for (int i=0;i<sizes[nivel];i++) {
        arr->items[i] = crearMultiArrayVacio(elemTipo, dims, sizes, nivel+1);
    }
    return arr;
}

static Result interpretMultiArrayDecl(AbstractExpresion* self, Context* context) {
    MultiArrayDecl* n = (MultiArrayDecl*)self;
    if (n->dims > 6) { report_runtime_error(self, context, "Máximo 6 dimensiones soportadas (se dio %d)", n->dims); return nuevoValorResultadoVacio(); }
    int* sizes = malloc(sizeof(int)*n->dims);
    for (int i=0;i<n->dims;i++) {
        Result r = n->dimExprs[i]->interpret(n->dimExprs[i], context);
        if (r.tipo != INT) { report_runtime_error(self, context, "Dimensión %d debe ser entera", i); free(sizes); return nuevoValorResultadoVacio(); }
        sizes[i] = *((int*)r.valor);
    }
    char derr[64];
    if(!validar_dimensiones(sizes, n->dims, derr, sizeof(derr))){ report_runtime_error(self, context, "%s", derr); free(sizes); return nuevoValorResultadoVacio(); }
    ArrayValue* root = crearMultiArrayVacio(n->elemTipo, n->dims, sizes, 0);
    free(sizes);
    Symbol* s2 = nuevoVariable(n->nombre, root, ARRAY, 0); s2->linea=self->linea; s2->columna=self->columna; if(s2->linea==0){ int l=0,c=0; resolver_pos_matrix(self,&l,&c); if(l>0){ s2->linea=l; s2->columna=c; }} agregarSymbol(context, s2);
    return nuevoValorResultadoVacio();
}

static Result interpretArray3DLiteralDecl(AbstractExpresion* self, Context* context) {
    Array3DLiteralDecl* n = (Array3DLiteralDecl*)self;
    AbstractExpresion* bloques = n->bloques2DLista; // lista de 2D blocks
    int depth = (int)bloques->numHijos;
    if (depth==0){ report_runtime_error(self, context, "Literal 3D vacío"); return nuevoValorResultadoVacio(); }
    // inferir filas y cols del primer bloque
    AbstractExpresion* primer2D = bloques->hijos[0];
    int filas = (int)primer2D->numHijos;
    if (filas==0){ report_runtime_error(self, context, "Bloque 2D vacío en literal 3D"); return nuevoValorResultadoVacio(); }
    AbstractExpresion* fila0 = primer2D->hijos[0];
    int cols = (int)fila0->numHijos;
    int sizes[3] = { depth, filas, cols }; char derr[64];
    if(!validar_dimensiones(sizes,3,derr,sizeof(derr))){ report_runtime_error(self, context, "%s", derr); return nuevoValorResultadoVacio(); }
    ArrayValue* root = crearMultiArrayVacio(n->elemTipo, 3, sizes, 0);
    // Rellenar
    for (int d=0; d<depth; d++) {
        AbstractExpresion* bloque2D = bloques->hijos[d];
    if ((int)bloque2D->numHijos != filas) report_runtime_error(self, context, "Inconsistencia de filas en bloque %d", d);
        ArrayValue* arr2D = (ArrayValue*)root->items[d];
    for (int f=0; f<filas && f<(int)bloque2D->numHijos; f++) {
            AbstractExpresion* filaNodo = bloque2D->hijos[f];
            if ((int)filaNodo->numHijos != cols) report_runtime_error(self, context, "Inconsistencia de columnas en bloque %d fila %d", d,f);
            ArrayValue* filaArr = (ArrayValue*)arr2D->items[f];
            for (int c=0; c<cols && c<(int)filaNodo->numHijos; c++) {
                Result vr = filaNodo->hijos[c]->interpret(filaNodo->hijos[c], context);
                void* convertido=NULL; char err[64]; int ok = convertir_valor(n->elemTipo, vr, (n->elemTipo==STRING)?1:0, 1, 0, &convertido, err, sizeof(err));
                if(!ok){
                    report_runtime_error(self, context, "Tipo incompatible literal 3D (%d,%d,%d)", d,f,c);
                    void* defv=NULL; TipoDato tr=n->elemTipo; if(valor_por_defecto(n->elemTipo,&defv,&tr)) convertido=defv; else convertido=NULL;
                }
                if(filaArr->items[c]) free(filaArr->items[c]);
                filaArr->items[c]=convertido;
            }
        }
    }
    Symbol* s3 = nuevoVariable(n->nombre, root, ARRAY, 0); s3->linea=self->linea; s3->columna=self->columna; if(s3->linea==0){ int l=0,c=0; resolver_pos_matrix(self,&l,&c); if(l>0){ s3->linea=l; s3->columna=c; }} agregarSymbol(context, s3);
    return nuevoValorResultadoVacio();
}

AbstractExpresion* nuevoMatrixDeclaracion(TipoDato tipoElem, char* nombre, AbstractExpresion* filasExpr, AbstractExpresion* colsExpr) {
    MatrixDecl* n = malloc(sizeof(MatrixDecl));
    n->elemTipo=tipoElem; n->nombre=nombre; n->filasExpr=filasExpr; n->colsExpr=colsExpr;
    buildAbstractExpresion(&n->base, interpretMatrixDecl);
    if (filasExpr) agregarHijo((AbstractExpresion*)n, filasExpr);
    if (colsExpr) agregarHijo((AbstractExpresion*)n, colsExpr);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoMatrixLiteralDeclaracion(TipoDato tipoElem, char* nombre, AbstractExpresion* filasLista) {
    MatrixLiteralDecl* n = malloc(sizeof(MatrixLiteralDecl));
    n->elemTipo=tipoElem; n->nombre=nombre; n->filasLista=filasLista;
    buildAbstractExpresion(&n->base, interpretMatrixLiteralDecl);
    if (filasLista) agregarHijo((AbstractExpresion*)n, filasLista);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoMatrixAsignacionElemento(char* nombre, AbstractExpresion* filaExpr, AbstractExpresion* colExpr, AbstractExpresion* valorExpr) {
    MatrixAsignacionElem* n = malloc(sizeof(MatrixAsignacionElem));
    n->nombre=nombre; n->fila=filaExpr; n->col=colExpr; n->valor=valorExpr; n->op = COP_NONE;
    buildAbstractExpresion(&n->base, interpretMatrixAsignacionElem);
    if (filaExpr) agregarHijo((AbstractExpresion*)n, filaExpr);
    if (colExpr) agregarHijo((AbstractExpresion*)n, colExpr);
    if (valorExpr) agregarHijo((AbstractExpresion*)n, valorExpr);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoMatrixAsignacionElementoCompound(char* nombre, AbstractExpresion* filaExpr, AbstractExpresion* colExpr, AbstractExpresion* valorExpr, CompoundOp op){
    MatrixAsignacionElem* n = malloc(sizeof(MatrixAsignacionElem));
    n->nombre=nombre; n->fila=filaExpr; n->col=colExpr; n->valor=valorExpr; n->op=op;
    buildAbstractExpresion(&n->base, interpretMatrixAsignacionElem);
    if (filaExpr) agregarHijo((AbstractExpresion*)n, filaExpr);
    if (colExpr) agregarHijo((AbstractExpresion*)n, colExpr);
    if (valorExpr) agregarHijo((AbstractExpresion*)n, valorExpr);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoMultiArrayDeclaracion(TipoDato tipoElem, char* nombre, int dims, AbstractExpresion** dimExprs) {
    MultiArrayDecl* n = malloc(sizeof(MultiArrayDecl));
    n->elemTipo=tipoElem; n->nombre=nombre; n->dims=dims; n->dimExprs=dimExprs;
    buildAbstractExpresion(&n->base, interpretMultiArrayDecl);
    for (int i=0;i<dims;i++) if (dimExprs[i]) agregarHijo((AbstractExpresion*)n, dimExprs[i]);
    return (AbstractExpresion*)n;
}

AbstractExpresion* nuevoArray3DLiteralDeclaracion(TipoDato tipoElem, char* nombre, AbstractExpresion* bloques2DLista) {
    Array3DLiteralDecl* n = malloc(sizeof(Array3DLiteralDecl));
    n->elemTipo=tipoElem; n->nombre=nombre; n->bloques2DLista=bloques2DLista;
    buildAbstractExpresion(&n->base, interpretArray3DLiteralDecl);
    if (bloques2DLista) agregarHijo((AbstractExpresion*)n, bloques2DLista);
    return (AbstractExpresion*)n;
}