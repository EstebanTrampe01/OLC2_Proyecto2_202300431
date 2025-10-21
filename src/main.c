#include "ast/AbstractExpresion.h"
#include "ast/nodos/instrucciones/instrucciones.h"
#include "context/context.h"
#include "ast/nodos/instrucciones/instruccion/funcion.h"
#include "ast/nodos/instrucciones/instruccion/declaracion.h"
#include "ast/ast_to_dot.h"
#include "context/error_reporting.h"
#include "codegen/codegen.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Declaraciones generadas por Bison/Flex */
int yyparse(void);
extern FILE* yyin;

AbstractExpresion* ast_root = NULL;

char* comments[1000];
int comment_count = 0;

int main(int argc, char** argv) {
    const char* inputPath = NULL;
    const char* astOut = NULL;
    const char* codegenOut = NULL;
    int silent = 0;
    for(int i=1;i<argc;i++){
        if(strncmp(argv[i], "--ast-out=", 10)==0){ astOut = argv[i]+10; }
        else if(strncmp(argv[i], "--codegen-out=", 14)==0){ codegenOut = argv[i]+14; }
        else if(strcmp(argv[i], "--silent")==0){ silent = 1; }
        else if(!inputPath){ inputPath = argv[i]; }
    }
    if (inputPath) {
        yyin = fopen(inputPath, "r");
        if (!yyin) { perror("fopen"); return 1; }
    }

    if (yyparse() == 0) {
        if (ast_root) {
            if(astOut){
                if(ast_export_to_dot(ast_root, astOut)==0){
                    fprintf(stderr, "AST exportado a %s\n", astOut);
                } else {
                    report_semantic_error(ast_root, NULL, "No se pudo exportar AST");
                }
            }
            printf("Inicio, cantidad de instrucciones: %zu \n", ast_root->numHijos);
            Context* contextPadre = nuevoContext(NULL);
            
            // PASADA 1: Registrar todas las declaraciones de funciones primero
            for(size_t i = 0; i < ast_root->numHijos; i++) {
                AbstractExpresion* instruccion = ast_root->hijos[i];
                // Si es una función, interpretarla para registrarla
                // Las funciones tienen un interpretador específico que solo registra
                if(instruccion && instruccion->interpret == interpretFuncionDeclaracion) {
                    instruccion->interpret(instruccion, contextPadre);
                }
            }
            
            // PASADA 2: Registrar declaraciones de variables
            for(size_t i = 0; i < ast_root->numHijos; i++) {
                AbstractExpresion* instruccion = ast_root->hijos[i];
                if(instruccion && instruccion->interpret == interpretDeclaracionVariable) {
                    instruccion->interpret(instruccion, contextPadre);
                }
            }
            
            if (codegenOut) {
                // Modo compilador: generar código ARM64
                FILE* out = fopen(codegenOut, "w");
                if (!out) {
                    perror("fopen codegen");
                    return 1;
                }
                CodegenContext* ctx = nuevo_codegen_context(out);
                ctx->symbol_ctx = contextPadre;
                codegen_programa(ctx, ast_root);
                liberar_codegen_context(ctx);
                fprintf(stderr, "Código ARM64 generado en %s\n", codegenOut);
            } else {
                // Modo intérprete: ejecutar el código
                // PASADA 2: Ejecutar todo el código EXCEPTO declaraciones de funciones
                for(size_t i = 0; i < ast_root->numHijos; i++) {
                    AbstractExpresion* instruccion = ast_root->hijos[i];
                    // Saltar declaraciones de funciones (ya fueron procesadas)
                    if(instruccion && instruccion->interpret == interpretFuncionDeclaracion) {
                        continue;
                    }
                    if(instruccion) {
                        instruccion->interpret(instruccion, contextPadre);
                    }
                }
                
                printf("Fin, archivo validado.\n");
                if(!silent){
                    // Reporte de símbolos: funciones y variables
                    print_function_registry_symbols();
                    print_all_contexts_symbols(contextPadre);
                }
            }
            
            // Liberaciones básicas para evitar fugas (no se libera cada valor interno aún)
            liberarAST(ast_root);
            ast_root = NULL;
            // TODO: liberar recursivamente contextos y symbols (por ahora sólo estructura en cadena)
            Context* ctx = contextPadre; // liberar árbol de contexts
            // Estrategia: DFS iterativa liberando symbols (sin liberar 'valor' porque puede ser compartido)
            // Primero liberar hijos vía stack simple
            struct CtxStack { Context* c; struct CtxStack* next; } *stack=NULL;
            if(ctx){
                struct CtxStack* n = malloc(sizeof(*n)); n->c=ctx; n->next=NULL; stack=n;
            }
            while(stack){
                struct CtxStack* top=stack; stack=top->next; Context* c=top->c; free(top);
                // push children
                for(Context* child=c->firstChild; child; child=child->nextSibling){
                    struct CtxStack* n = malloc(sizeof(*n)); n->c=child; n->next=stack; stack=n;
                }
                // free symbols
                Symbol* s=c->ultimoSymbol; while(s){ Symbol* prev=s->anterior; if(s->nombre) free(s->nombre); if(s->valor){ liberarValor(s->tipo, s->valor); s->valor=NULL; } free(s); s=prev; }
                free(c);
            }
        } else {
            printf("No input parsed.\n");
        }
    } else {
        fprintf(stderr, "Parsing failed.\n");
    }

    if (yyin && yyin != stdin) fclose(yyin);

    return 0;
}