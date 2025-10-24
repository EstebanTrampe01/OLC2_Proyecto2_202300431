#ifndef RESULT_H
#define RESULT_H

// El orden es la jerarquia del resultado en la operación
typedef enum {
    VOID,
    BOOLEAN,
    CHAR,
    BYTE,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    STRING,
    NULO,
    BREAK,
    CONTINUE,
    RETURN,
    ARRAY,
    TIPO_COUNT
} TipoDato;

extern char* labelTipoDato[];

typedef struct {
    TipoDato tipo;
    void* valor;
} Result;

TipoDato tipoResultante(Result, Result);
/*utilizado para devolver un Result*/
Result nuevoValorResultado(void* valor, TipoDato tipo);
/*Utilizado para devolver una repuesta nula */
/* Registro simple de errores acumulados */
typedef struct {
    char** mensajes;
    int count;
    int capacity;
} ErrorList;

extern ErrorList g_error_list;
void init_error_list();
void add_error_msg(const char* msg);
void clear_error_list();
void print_error_list();
Result nuevoValorResultadoVacio(void);

/* Liberar memoria asociada a un valor según su tipo (excepto estructuras complejas no implementadas aún) */
void liberarValor(TipoDato tipo, void* valor);

#endif