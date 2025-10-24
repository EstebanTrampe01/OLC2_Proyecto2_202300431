#ifndef ARRAY_NODOS_H
#define ARRAY_NODOS_H

#include "../../../AbstractExpresion.h"
#include "context/array.h"
#include "context/context.h"
#include "context/result.h"

AbstractExpresion* nuevoArrayDeclaracion(TipoDato tipoElemento, char* nombre, AbstractExpresion* exprLength);
AbstractExpresion* nuevoArrayLiteralDeclaracion(TipoDato tipoElemento, char* nombre, AbstractExpresion* listaValores);
AbstractExpresion* nuevoArrayAcceso(AbstractExpresion* arregloExpr, AbstractExpresion* indiceExpr);
AbstractExpresion* nuevoArrayLinearAccess(AbstractExpresion* arregloExpr, AbstractExpresion* linearIdx);
AbstractExpresion* nuevoArrayAsignacionElemento(char* nombre, AbstractExpresion* indiceExpr, AbstractExpresion* valorExpr);
/* Asignación multi-dimensional genérica: nombre[...][...]... = valor */
AbstractExpresion* nuevoMultiArrayAsignacionElemento(char* nombre, AbstractExpresion* indicesLista, AbstractExpresion* valorExpr);
/* Operadores compuestos */
typedef enum { COP_NONE=0, COP_ADD, COP_SUB, COP_MUL, COP_DIV, COP_MOD } CompoundOp;
AbstractExpresion* nuevoArrayAsignacionElementoCompound(char* nombre, AbstractExpresion* indiceExpr, AbstractExpresion* valorExpr, CompoundOp op);
AbstractExpresion* nuevoMultiArrayAsignacionElementoCompound(char* nombre, AbstractExpresion* indicesLista, AbstractExpresion* valorExpr, CompoundOp op);
/* Declaración de array a partir de una expresión que retorna ARRAY */
AbstractExpresion* nuevoArrayDeclaracionDesdeExpr(TipoDato tipoElem, char* nombre, AbstractExpresion* exprArray);

/* Exponer interpretadores para que el exportador de AST pueda identificarlos por puntero */
Result interpretArrayDecl(AbstractExpresion* self, Context* context);
Result interpretArrayLiteralDecl(AbstractExpresion* self, Context* context);
Result interpretArrayAcceso(AbstractExpresion* self, Context* context);
Result interpretArrayAsignacionElem(AbstractExpresion* self, Context* context);
Result interpretMultiArrayAsignacionElem(AbstractExpresion* self, Context* context);
Result interpretArrayLinearAccess(AbstractExpresion* self, Context* context);
Result interpretArrayDeclFromExpr(AbstractExpresion* self, Context* ctx);

#endif