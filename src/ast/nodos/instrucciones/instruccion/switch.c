#include "switch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../../context/result.h"

typedef struct {
    AbstractExpresion base;
    AbstractExpresion* valor;      // Valor del case
    AbstractExpresion* instrucciones; // Instrucciones del case
    int tieneBreak;                // Si tiene break
} CaseExpresion;

AbstractExpresion* nuevoCaseExpresion(AbstractExpresion* valor, AbstractExpresion* instrucciones, int tieneBreak);
Result interpretCaseExpresion(AbstractExpresion* self, Context* context);
Result interpretSwitchExpresion(AbstractExpresion* self, Context* context);

// Función auxiliar para comparar resultados
int sonIguales(Result a, Result b) {
    if (a.tipo != b.tipo) return 0;
    
    switch (a.tipo) {
        case INT:
            return *((int*)a.valor) == *((int*)b.valor);
        case FLOAT:
            return *((float*)a.valor) == *((float*)b.valor);
        case BOOLEAN:
            return *((int*)a.valor) == *((int*)b.valor);
        case STRING:
            return strcmp((char*)a.valor, (char*)b.valor) == 0;
        case CHAR:
            return *((char*)a.valor) == *((char*)b.valor);
        default:
            return 0;
    }
}

AbstractExpresion* nuevoSwitchExpresion(AbstractExpresion* expresion, AbstractExpresion* casos, AbstractExpresion* casoDefault) {
    SwitchExpresion* expr = (SwitchExpresion*)malloc(sizeof(SwitchExpresion));
    expr->expresion = expresion;
    expr->casos = casos;
    expr->casoDefault = casoDefault;
    buildAbstractExpresion(&expr->base, interpretSwitchExpresion);
    if (expresion) agregarHijo((AbstractExpresion*)expr, expresion);
    if (casos) agregarHijo((AbstractExpresion*)expr, casos);
    if (casoDefault) agregarHijo((AbstractExpresion*)expr, casoDefault);
    return (AbstractExpresion*)expr;
}

Result interpretSwitchExpresion(AbstractExpresion* self, Context* context) {
    SwitchExpresion* expr = (SwitchExpresion*)self;

    // Evaluar la expresión del switch
    Result switchResult = expr->expresion->interpret(expr->expresion, context);
    context->dentroSwitch++;
    
    // Evaluar cada caso
    if (expr->casos != NULL) {
        for (size_t i = 0; i < expr->casos->numHijos; i++) {
            CaseExpresion* caso = (CaseExpresion*)expr->casos->hijos[i];
            
            // Comparar el valor del case con el resultado del switch
            Result caseResult = caso->valor->interpret(caso->valor, context);
            
            // Si coinciden, ejecutar las instrucciones del caso
            if (sonIguales(switchResult, caseResult)) {
                Result result = caso->instrucciones->interpret(caso->instrucciones, context);
                
                // Si tiene break, terminar
                if (caso->tieneBreak) {
                    context->dentroSwitch--;
                    return result;
                }
                // Si no tiene break, continuar con el siguiente caso
            }
        }
    }
    
    // Si no encontró ningún caso coincidente, ejecutar default si existe
    if (expr->casoDefault != NULL) {
        Result r = expr->casoDefault->interpret(expr->casoDefault, context);
        context->dentroSwitch--;
        return r;
    }
    
    context->dentroSwitch--;
    return nuevoValorResultadoVacio();
}

AbstractExpresion* nuevoCaseExpresion(AbstractExpresion* valor, AbstractExpresion* instrucciones, int tieneBreak) {
    CaseExpresion* expr = (CaseExpresion*)malloc(sizeof(CaseExpresion));
    expr->valor = valor;
    expr->instrucciones = instrucciones;
    expr->tieneBreak = tieneBreak;
    buildAbstractExpresion(&expr->base, interpretCaseExpresion);
    if (valor) agregarHijo((AbstractExpresion*)expr, valor);
     /* Importante: NO agregamos 'instrucciones' como hijo aquí.
         En presencia de 'case' apilados que comparten el mismo bloque de instrucciones,
         varios CaseExpresion apuntarán al mismo nodo 'instrucciones'. Si todos lo agregaran
         como hijo, el liberador de AST intentaría liberarlo múltiples veces.
         El parser asignará la propiedad a exactamente UNO de los CaseExpresion creados.
     */
    return (AbstractExpresion*)expr;
}

Result interpretCaseExpresion(AbstractExpresion* self, Context* context) {
    // Los casos individuales no se interpretan directamente
    return nuevoValorResultadoVacio();
}
