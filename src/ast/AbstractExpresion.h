#ifndef ABSTRACT_EXPRESION_H
#define ABSTRACT_EXPRESION_H

#include "context/result.h"
#include "context/context.h"

#include <stddef.h>

/*
 * se usa para no tener que escribir struct AbstractExpresion* nodo; 
 * se define antes porque se accede a este tipo en el mismo struct
*/
typedef struct AbstractExpresion AbstractExpresion;
/*
 * Link: https://www.geeksforgeeks.org/c/how-to-create-typedef-for-function-pointer-in-c/
 * typedef return_type (*alias_name)(parameter_types and numbers....);
*/
typedef Result (*Interpret)(AbstractExpresion*, Context*);
typedef void (*Graficar)(AbstractExpresion*);

struct AbstractExpresion {
    Interpret interpret; // Método interpretar puntero
    //Graficar graficar; //Método graficar puntero
    AbstractExpresion** hijos; // Array dinámico de hijos
    size_t numHijos;
    int linea;   // línea de inicio (parser)
    int columna; // columna de inicio (parser)
};

void agregarHijo(AbstractExpresion* padre, AbstractExpresion* hijo);
void liberarAST(AbstractExpresion* raiz);
void buildAbstractExpresion(AbstractExpresion* base, Interpret interpretPuntero);

// Macro auxiliar para asignar posición desde una ubicación de Bison
#define SET_POS(node, loc) do { if((node)!=NULL){ (node)->linea = (loc).first_line; (node)->columna = (loc).first_column; } } while(0)

#endif