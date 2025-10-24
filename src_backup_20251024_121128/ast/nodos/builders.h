#ifndef BUILDERS_H
#define BUILDERS_H

#include "ast/AbstractExpresion.h"


/*
    Estructura de un builder:
    AbstractExpresion* nombreExpresionNodo a construir (datos iniciales)
*/

AbstractExpresion* nuevoInstruccionesExpresion(void);
AbstractExpresion* nuevoPrintExpresion(AbstractExpresion* listaExpresiones, int newline);
AbstractExpresion* nuevoPrimitivoExpresion(char* valor, TipoDato tipo);
AbstractExpresion* nuevoListaExpresiones(void);
AbstractExpresion* nuevoDeclaracionVariables(TipoDato, char* nombre, AbstractExpresion* expresion, int isFinal);
AbstractExpresion* nuevoIdentificadorExpresion(char* nombre);
AbstractExpresion* nuevoBloqueExpresion(AbstractExpresion* instrucciones);
AbstractExpresion* nuevoBloqueExpresionConContextoPadre(AbstractExpresion* instrucciones);
AbstractExpresion* nuevoSumaExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoRestaExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoMultiplicacionExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoDivisionExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoModuloExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoBitAndExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoBitOrExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoBitXorExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoShiftLeftExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoShiftRightExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoAsignacionExpresion(char* nombre, AbstractExpresion* expresion);
AbstractExpresion* nuevoAsignacionSumaExpresion(char* nombre, AbstractExpresion* expresion);
AbstractExpresion* nuevoAsignacionRestaExpresion(char* nombre, AbstractExpresion* expresion);
AbstractExpresion* nuevoAsignacionMultiplicacionExpresion(char* nombre, AbstractExpresion* expresion);
AbstractExpresion* nuevoAsignacionDivisionExpresion(char* nombre, AbstractExpresion* expresion);
AbstractExpresion* nuevoAsignacionModuloExpresion(char* nombre, AbstractExpresion* expresion);
AbstractExpresion* nuevoCastExpresion(TipoDato tipoDestino, AbstractExpresion* expresion);

/* Builders para expresiones relacionales */
AbstractExpresion* nuevoIgualdadExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoDesigualdadExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoMayorQueExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoMenorQueExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoMayorIgualQueExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoMenorIgualQueExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);

/* Builders para expresiones lógicas */
AbstractExpresion* nuevoAndExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoOrExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoNotExpresion(AbstractExpresion* expresion);

/* Builders para instrucciones de control */
AbstractExpresion* nuevoIfExpresion(AbstractExpresion* condicion, AbstractExpresion* bloqueIf, AbstractExpresion* bloqueElse);
AbstractExpresion* nuevoWhileExpresion(AbstractExpresion* condition, AbstractExpresion* body);
AbstractExpresion* nuevoForExpresion(AbstractExpresion* initialization, AbstractExpresion* condition, AbstractExpresion* increment, AbstractExpresion* body);
AbstractExpresion* nuevoSwitchExpresion(AbstractExpresion* expresion, AbstractExpresion* casos, AbstractExpresion* casoDefault);
AbstractExpresion* nuevoCaseExpresion(AbstractExpresion* valor, AbstractExpresion* instrucciones, int tieneBreak);
AbstractExpresion* nuevoBreakExpresion(void);

/*
    Builds expresiones
*/
AbstractExpresion* nuevoSumaExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoRestaExpresion(AbstractExpresion* izquierda, AbstractExpresion* derecha);
AbstractExpresion* nuevoUnarioExpresion(AbstractExpresion* expresion);


#endif