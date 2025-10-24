#include "result.h"

#include <stddef.h>
#include <stdio.h>

char* labelTipoDato[TIPO_COUNT] = {
    [VOID] = "void",
    [BOOLEAN] = "boolean",
    [CHAR] = "char",
    [BYTE] = "byte",
    [SHORT] = "short",
    [INT] = "int",
    [LONG] = "long",
    [FLOAT] = "float",
    [DOUBLE] = "double",
    [STRING] = "string",
    [NULO] = "null",
    [BREAK] = "break",
    [CONTINUE] = "continue",
    [RETURN] = "return",
    [ARRAY] = "array"
};

Result nuevoValorResultado(void* valor, TipoDato tipo) {
    Result resultado;
    resultado.tipo = tipo;
    resultado.valor = valor;
    return resultado;
}

Result nuevoValorResultadoVacio() {
    Result resultado;
    resultado.tipo = NULO;
    resultado.valor = NULL;
    return resultado;
}

//Sin usar
TipoDato tipoResultante(Result valor1, Result valor2) {
    if (valor1.tipo >= valor2.tipo) {
        return valor1.tipo;
    } else {
        return valor2.tipo;
    }
}

/* ================= Manejo simple de lista de errores acumulados ================= */
#include <stdlib.h>
#include <string.h>

ErrorList g_error_list = { NULL, 0, 0 };

void init_error_list(){
    if(!g_error_list.mensajes){
        g_error_list.capacity = 16;
        g_error_list.mensajes = (char**)malloc(sizeof(char*) * g_error_list.capacity);
        g_error_list.count = 0;
    }
}

void add_error_msg(const char* msg){
    if(!msg) return;
    if(!g_error_list.mensajes) init_error_list();
    if(g_error_list.count >= g_error_list.capacity){
        g_error_list.capacity *= 2;
        g_error_list.mensajes = (char**)realloc(g_error_list.mensajes, sizeof(char*) * g_error_list.capacity);
    }
    g_error_list.mensajes[g_error_list.count++] = strdup(msg);
}

void clear_error_list(){
    for(int i=0;i<g_error_list.count;i++) free(g_error_list.mensajes[i]);
    g_error_list.count = 0;
}

void print_error_list(){
    for(int i=0;i<g_error_list.count;i++){
        fputs(g_error_list.mensajes[i], stderr);
        fputc('\n', stderr);
    }
}

/* Liberar valor según tipo básico; arrays u otros se manejarán después */
void liberarValor(TipoDato tipo, void* valor){
    if(!valor) return;
    switch(tipo){
        case INT: case LONG: case SHORT: case BYTE: case BOOLEAN:
        case FLOAT: case DOUBLE: case CHAR:
            free(valor); break;
        case STRING:
            free(valor); break; // asumimos cadena duplicada/propia
        default:
            // VOID, NULO, BREAK, CONTINUE, RETURN, ARRAY (pendiente) -> no liberar aquí
            break;
    }
}