#include "ast/AbstractExpresion.h"
#include "ast/nodos/builders.h"
#include "context/context.h"
#include "context/result.h"
#include "primitivos.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    CREAR SIEMPRE NUEVO ESPACIO DE MEMORIA PARA ESTE ESCENARIO CON malloc
    porque si usamos la direccion de memoria de esa variable, es posible que el garbage
    collector la elimine por ser variable local
*/
Result interpretPrimitivoExpresion(AbstractExpresion* self, Context* context) {
    (void)context; /* no se usa en primitivo */
    PrimitivoExpresion* nodo = (PrimitivoExpresion*) self;
    // Debug temporal
    // fprintf(stderr, "[DEBUG primitivo] tipo=%d valor=%s\n", nodo->tipo, nodo->valor?nodo->valor:"NULL");
    switch (nodo->tipo) {
        case INT:
            int* valorint = malloc(sizeof(int));
            *valorint = atoi(nodo->valor);
            return nuevoValorResultado((void*) valorint, nodo->tipo);
        case FLOAT: {
            float* valorfloat = malloc(sizeof(float));
            *valorfloat = (float)atof(nodo->valor);
            return nuevoValorResultado((void*) valorfloat, FLOAT);
        }
        case DOUBLE: {
            double* vd = malloc(sizeof(double)); *vd = strtod(nodo->valor, NULL); return nuevoValorResultado(vd, DOUBLE);
        }
        case STRING:
        {
            if(!nodo->valor){ return nuevoValorResultado(NULL, NULO); }
            char* dup = strdup(nodo->valor); /* asegurar heap para liberación segura */
            if(!dup) return nuevoValorResultadoVacio();
            return nuevoValorResultado((void*) dup, nodo->tipo);
        }
        case BOOLEAN:
            int* valorbool = malloc(sizeof(int));
            if (strcmp(nodo->valor, "true") == 0) {
                *valorbool = 1;
            } else {
                *valorbool = 0;
            }
            return nuevoValorResultado((void*) valorbool, nodo->tipo);
    case CHAR: {
            char* valorchar = malloc(sizeof(char));
            size_t len = strlen(nodo->valor);
            if(len==1){ *valorchar = nodo->valor[0]; }
            else if(len==2 && nodo->valor[0]=='\\'){
                switch(nodo->valor[1]){ case 'n': *valorchar='\n'; break; case 't': *valorchar='\t'; break; case 'r': *valorchar='\r'; break; case '\\': *valorchar='\\'; break; case '\'': *valorchar='\''; break; case '"': *valorchar='"'; break; default: *valorchar=nodo->valor[1]; }
            } else if(len==6 && nodo->valor[0]=='\\' && nodo->valor[1]=='u'){ /* ya decodificado en lexer si <=255, pero por si acaso */
                char hex[5]; memcpy(hex, nodo->valor+2,4); hex[4]='\0'; long code=strtol(hex,NULL,16); if(code>=0 && code<=255) *valorchar=(char)code; else *valorchar='?';
            } else { *valorchar = nodo->valor[0]; }
            return nuevoValorResultado((void*) valorchar, CHAR);
        }
        case NULO: {
            /* Literal null */
            return nuevoValorResultado(NULL, NULO);
        }
        default:
            printf("Tipo de dato primitivo no implementado\n");
    }
    return nuevoValorResultadoVacio();
}

AbstractExpresion* nuevoPrimitivoExpresion(char* v, TipoDato tipo) { //, int lengthValor) {
    //reservar el espacio en memoria y obtener el puntero a este
    PrimitivoExpresion* nodo = malloc(sizeof(PrimitivoExpresion));
    if (!nodo) return NULL;
    //asignar valores
    buildAbstractExpresion(&nodo->base, interpretPrimitivoExpresion);

    nodo->valor = v;
    nodo->tipo = tipo;
    return (AbstractExpresion*) nodo;
}