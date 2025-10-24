#include "tipo_utils.h"

int es_numerico(TipoDato t){
    switch(t){
        case BYTE: case SHORT: case INT: case LONG:
        case FLOAT: case DOUBLE: case CHAR:
            return 1;
        default: return 0;
    }
}

int tipos_compatibles_asignacion(TipoDato destino, TipoDato origen, int* requiereValidacionPrecision){
    if(requiereValidacionPrecision) *requiereValidacionPrecision = 0;
    if(destino == origen) return 1; // mismo tipo directo

    // STRING solo acepta STRING
    if(destino == STRING) return origen == STRING;
    // BOOLEAN: permitir boolean y (opcional) INT como truthy/falsy
    if(destino == BOOLEAN){
        return (origen == BOOLEAN || origen == INT); // se podría ampliar a numéricos
    }
    // CHAR: permitir desde CHAR o INT (como entero base) -> validación de rango en conversión
    if(destino == CHAR){
        return (origen == CHAR || origen == INT); }

    // VOID / control / ARRAY: no se asignan valores regulares implícitamente
    switch(destino){
        case VOID: case BREAK: case CONTINUE: case RETURN: case ARRAY: case NULO:
            return 0;
        default: break;
    }

    // Numéricos generales
    if(es_numerico(destino) && es_numerico(origen)){
        // Widenings siempre permitidos: entero menor -> entero mayor / float / double; float -> double
        // Narrowings que necesitan validación de valor: float/double -> entero; double -> float
        if(destino == FLOAT && origen == DOUBLE){
            if(requiereValidacionPrecision) *requiereValidacionPrecision = 1; // posible pérdida al reducir
            return 1;
        }
        // destino entero
        if(destino == BYTE || destino == SHORT || destino == INT || destino == LONG){
            if(origen == FLOAT || origen == DOUBLE){
                if(requiereValidacionPrecision) *requiereValidacionPrecision = 1;
                return 1; // validar luego valor entero exacto
            }
        }
        // General: permitir cualquier combinación numérica (promociones) excepto casos ya manejados; char se trata como entero pequeño
        return 1;
    }

    return 0; // por defecto incompatible
}
