#include "asignacion_util.h"
#include "ast/AbstractExpresion.h"
#include "context/context.h"
#include "context/result.h"
#include "context/tipo_utils.h"
#include "context/conversion_utils.h"
#include "context/variable_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "context/error_reporting.h"

// Función auxiliar para verificar compatibilidad de tipos en asignación compuesta
int verificarCompatibilidadTiposAsignacion(TipoDato tipoVariable, TipoDato tipoResultado) {
    int dummy=0; return tipos_compatibles_asignacion(tipoVariable, tipoResultado, &dummy);
}

// Función auxiliar para realizar asignación compuesta
Result realizarAsignacionCompuesta(AbstractExpresion* self, Context* context, char* nombreVariable, Operacion (*tablaOperaciones)[TIPO_COUNT][TIPO_COUNT], char* operador) {
    // Variable existente y modificable
    Symbol* symbol=NULL; if(!obtener_variable_modificable(self, context, nombreVariable, &symbol)) return nuevoValorResultadoVacio();

    // Interpretar la expresión
    Result resultado = self->hijos[0]->interpret(self->hijos[0], context);

    // Crear expresión temporal: variable op expresión
    Result valorVariable;
    valorVariable.tipo = symbol->tipo;
    valorVariable.valor = symbol->valor;

    // Usar la tabla de operaciones correspondiente
    ExpresionLenguaje tempExpresion;
    tempExpresion.izquierda = valorVariable;
    tempExpresion.derecha = resultado;
    tempExpresion.tablaOperaciones = tablaOperaciones;

    Operacion op = (*tempExpresion.tablaOperaciones)[valorVariable.tipo][resultado.tipo];
    if (op == NULL) {
        report_runtime_error(self, context, "Operación no soportada para tipos %d y %d en %s", valorVariable.tipo, resultado.tipo, operador);
        return nuevoValorResultadoVacio();
    }

    Result resultadoOperacion = op(&tempExpresion);

    // Compatibilidad y conversión centralizada
    int requiereValidacion = 0;
    if(!tipos_compatibles_asignacion(symbol->tipo, resultadoOperacion.tipo, &requiereValidacion)){
        report_runtime_error(self, context, "Tipos incorrectos en asignación %s para '%s'", operador, nombreVariable);
        return nuevoValorResultadoVacio();
    }
    void* nuevo=NULL; char err[128];
    if(!convertir_valor(symbol->tipo, resultadoOperacion, 1, requiereValidacion, 0, &nuevo, err, sizeof(err))){
        report_runtime_error(self, context, "Error de conversión en %s para '%s': %s", operador, nombreVariable, err);
        return nuevoValorResultadoVacio();
    }
    // liberar valor intermedio de la operación (si fue heap y distinto al nuevo)
    if(resultadoOperacion.valor && resultadoOperacion.valor!=nuevo && resultadoOperacion.tipo!=STRING && resultadoOperacion.tipo!=NULO)
        free(resultadoOperacion.valor);
    resultadoOperacion.valor = nuevo;

    // Liberar valor previo (excepto strings/nulos que podrían reutilizarse según diseño)
    if (symbol->valor && symbol->tipo != STRING && symbol->tipo != NULO) {
        free(symbol->valor);
    }
    symbol->valor = resultadoOperacion.valor;
    return nuevoValorResultadoVacio();
}
