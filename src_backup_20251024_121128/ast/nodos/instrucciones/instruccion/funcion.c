#define _POSIX_C_SOURCE 200809L
#include "funcion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "context/error_reporting.h"

typedef struct FunctionRegistryNode {
    FuncionDecl* decl;
    struct FunctionRegistryNode* next;
} FunctionRegistryNode;

static FunctionRegistryNode* functionRegistry = NULL;

static FuncionDecl* buscarFuncion(char* nombre) {
    FunctionRegistryNode* cur = functionRegistry;
    while(cur){
        if(strcmp(cur->decl->nombre, nombre)==0) return cur->decl;
        cur = cur->next;
    }
    return NULL;
}

Result interpretFuncionDeclaracion(AbstractExpresion* self, Context* context) {
    FuncionDecl* f = (FuncionDecl*) self;
    if(buscarFuncion(f->nombre)) {
        report_runtime_error(self, context, "Función '%s' ya declarada", f->nombre);
        return nuevoValorResultadoVacio();
    }
    FunctionRegistryNode* node = malloc(sizeof(FunctionRegistryNode));
    node->decl = f;
    node->next = functionRegistry;
    functionRegistry = node;
    return nuevoValorResultadoVacio();
}

Result interpretReturnExpresion(AbstractExpresion* self, Context* context) {
    ReturnExpresion* r = (ReturnExpresion*) self;
    if(r->valor){
        Result v = r->valor->interpret(r->valor, context);
        // Clonar valores primitivos para evitar aliasing con variables locales en stack de contextos
        void* copia = v.valor;
        switch(v.tipo){
            case INT: case BYTE: case SHORT: case LONG: {
                int* nv = malloc(sizeof(int)); *nv = *(int*)v.valor; copia = nv; break; }
            case FLOAT: {
                float* nv = malloc(sizeof(float)); *nv = *(float*)v.valor; copia = nv; break; }
            case DOUBLE: {
                double* nv = malloc(sizeof(double)); *nv = *(double*)v.valor; copia = nv; break; }
            case BOOLEAN: {
                int* nv = malloc(sizeof(int)); *nv = *(int*)v.valor; copia = nv; break; }
            case CHAR: {
                char* nv = malloc(sizeof(char)); *nv = *(char*)v.valor; copia = nv; break; }
            case STRING: /* reutiliza */ break;
            case ARRAY: /* NUEVO: soportar retorno de arrays sin clonar (alias aceptado) */ break;
            default: break;
        }
        return nuevoValorResultado(copia, RETURN);
    }
    return nuevoValorResultado(NULL, RETURN);
}

Result interpretLlamadaFuncion(AbstractExpresion* self, Context* context) {
    LlamadaFuncion* call = (LlamadaFuncion*) self;
    FuncionDecl* decl = buscarFuncion(call->nombre);
    if(!decl){
        report_runtime_error(self, context, "Función '%s' no encontrada", call->nombre);
        return nuevoValorResultadoVacio();
    }
    // crear contexto nuevo para ejecución
    Context* local = nuevoContext(context);
    // parámetros
    if(decl->paramCount != (int)call->args->numHijos){
        report_runtime_error(self, context, "Número de argumentos no coincide en llamada a '%s'", decl->nombre);
        return nuevoValorResultadoVacio();
    }
    for(int i=0;i<decl->paramCount;i++){
        Result argR = call->args->hijos[i]->interpret(call->args->hijos[i], context);
        void* copia = argR.valor;
        // Clonar primitivos para evitar aliasing entre frames recursivos
        switch(argR.tipo){
            case INT: case BYTE: case SHORT: case LONG: { int* nv=malloc(sizeof(int)); *nv=*(int*)argR.valor; copia=nv; break; }
            case FLOAT: { float* nv=malloc(sizeof(float)); *nv=*(float*)argR.valor; copia=nv; break; }
            case DOUBLE: { double* nv=malloc(sizeof(double)); *nv=*(double*)argR.valor; copia=nv; break; }
            case BOOLEAN: { int* nv=malloc(sizeof(int)); *nv=*(int*)argR.valor; copia=nv; break; }
            case CHAR: { char* nv=malloc(sizeof(char)); *nv=*(char*)argR.valor; copia=nv; break; }
            default: break; // STRING, ARRAY etc: alias aceptado provisionalmente
        }
        Symbol* sym = nuevoVariable(decl->paramNombres[i], copia, decl->paramTipos[i], 0);
        sym->clase = VARIABLE;
        agregarSymbol(local, sym);
    }
    // ejecutar cuerpo: decl->cuerpo es un bloque con hijos (listaSentencias)
    for(size_t i=0;i<decl->cuerpo->numHijos;i++){
        AbstractExpresion* instr = decl->cuerpo->hijos[i];
        Result r = instr->interpret(instr, local);
        if(r.tipo == RETURN){
            // validar tipo
            if(decl->retorno == VOID){
                if(r.valor != NULL){
                    report_runtime_error(self, context, "Función '%s' es void y retorna valor", decl->nombre);
                }
                return nuevoValorResultado(NULL, VOID);
            } else {
                // No forzamos cast aquí; asumimos que el parser garantiza tipo correcto
                return nuevoValorResultado(r.valor, decl->retorno);
            }
        } else if(r.tipo == BREAK || r.tipo == CONTINUE){
            report_runtime_error(self, context, "'break'/'continue' fuera de un bucle en función '%s'", decl->nombre);
            return nuevoValorResultadoVacio();
        }
    }
    // si no hubo return explícito
    if(decl->retorno == VOID) return nuevoValorResultado(NULL, VOID);
    // NUEVO: Si la función retorna ARRAY, devolver NULL si no hay return explícito
    if(decl->retorno == ARRAY) {
        report_runtime_error(self, context, "Función '%s' debe retornar un array", decl->nombre);
        return nuevoValorResultadoVacio();
    }
    // Para evitar abortar recursiones silenciosas: devolver 0 para tipos numéricos si falta return
    switch(decl->retorno){
        case INT: case BYTE: case SHORT: case LONG: {
            int* v = malloc(sizeof(int)); *v=0; return nuevoValorResultado(v, INT); }
        case FLOAT: { float* v=malloc(sizeof(float)); *v=0; return nuevoValorResultado(v, FLOAT);} 
        case DOUBLE: { double* v=malloc(sizeof(double)); *v=0; return nuevoValorResultado(v, DOUBLE);} 
        case BOOLEAN: { int* v=malloc(sizeof(int)); *v=0; return nuevoValorResultado(v, BOOLEAN);} 
        case CHAR: { char* v=malloc(sizeof(char)); *v='\0'; return nuevoValorResultado(v, CHAR);} 
        case STRING: return nuevoValorResultado(strdup(""), STRING);
    default: report_runtime_error(self, context, "Función '%s' sin return", decl->nombre); return nuevoValorResultadoVacio();
    }
}

void print_function_registry_symbols(void){
    FunctionRegistryNode* cur=functionRegistry;
    while(cur){
        const char* tipo="?";
        extern char* labelTipoDato[];
        if(cur->decl->retorno>=0) tipo = labelTipoDato[cur->decl->retorno];
        printf("SYM|%s|Funcion|%s|Global|%d|%d\n", cur->decl->nombre, tipo, cur->decl->linea, cur->decl->columna);
        cur = cur->next;
    }
}

AbstractExpresion* nuevoFuncionDeclaracion(TipoDato retorno, char* nombre, char** paramNombres, TipoDato* paramTipos, int paramCount, AbstractExpresion* cuerpo, int returnDims){
    FuncionDecl* f = malloc(sizeof(FuncionDecl));
    buildAbstractExpresion(&f->base, interpretFuncionDeclaracion);
    f->nombre = nombre;
    f->retorno = retorno;
    f->returnDims = returnDims;  // Nuevo: guardar dimensiones del tipo de retorno
    f->paramNombres = paramNombres;
    f->paramTipos = paramTipos;
    f->paramCount = paramCount;
    f->cuerpo = cuerpo; // bloque (lista de instrucciones dentro)
    f->linea = 0; f->columna = 0;
    return (AbstractExpresion*) f;
}

AbstractExpresion* nuevoReturnExpresion(AbstractExpresion* valor){
    ReturnExpresion* r = malloc(sizeof(ReturnExpresion));
    buildAbstractExpresion(&r->base, interpretReturnExpresion);
    r->valor = valor;
    return (AbstractExpresion*) r;
}

AbstractExpresion* nuevoLlamadaFuncion(char* nombre, AbstractExpresion* args){
    LlamadaFuncion* l = malloc(sizeof(LlamadaFuncion));
    buildAbstractExpresion(&l->base, interpretLlamadaFuncion);
    l->nombre = nombre;
    l->args = args ? args : nuevoListaExpresiones();
    /* If this function name is a registered native helper, mark for codegen */
    extern int codegen_is_native(const char*);
    if (codegen_is_native(nombre)) {
        l->base.gen_strategy = GEN_CALL_HELPER;
    }
    return (AbstractExpresion*) l;
}
