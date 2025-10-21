#ifndef SWITCH_H
#define SWITCH_H

#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"

typedef struct {
    AbstractExpresion base;
    AbstractExpresion* expresion;  // La expresión a evaluar
    AbstractExpresion* casos;      // Lista de casos
    AbstractExpresion* casoDefault; // Caso default (opcional)
} SwitchExpresion;

AbstractExpresion* nuevoSwitchExpresion(AbstractExpresion* expresion, AbstractExpresion* casos, AbstractExpresion* casoDefault);

// Intérpretes de nodos Switch/Case (declarados para identificación en AST DOT)
Result interpretSwitchExpresion(AbstractExpresion*, Context*);
Result interpretCaseExpresion(AbstractExpresion*, Context*);

#endif
