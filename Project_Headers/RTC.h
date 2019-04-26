 /********************************************************
 Company: Universidad Catolica de Oriente
 Desing by: Luis Felipe Echeverri 
 Date: 12/09/2013
 Description: Este codigo contiene la cabecera de la funcion
			  para inicializar el modulo RTC
 segment driver
 Dependences: events.h

 *********************************************************/

#ifndef _RTC_H
#define _RTC_H
#include "events.h"
/**************************************************
* Cabeceras de funciones
**************************************************/
void RTC_Init(UINT8 Module, UINT8 Prescaler); 

#endif

