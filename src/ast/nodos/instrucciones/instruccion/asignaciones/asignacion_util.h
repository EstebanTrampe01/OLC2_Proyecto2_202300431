#ifndef ASIGNACION_UTIL_H
#define ASIGNACION_UTIL_H

#include "context/result.h"
#include "ast/nodos/expresiones/expresiones.h"

// Función auxiliar para verificar compatibilidad de tipos en asignación compuesta
int verificarCompatibilidadTiposAsignacion(TipoDato tipoVariable, TipoDato tipoResultado);

// Función auxiliar para realizar asignación compuesta
Result realizarAsignacionCompuesta(AbstractExpresion* self, Context* context, char* nombreVariable, Operacion (*tablaOperaciones)[TIPO_COUNT][TIPO_COUNT], char* operador);

#endif
