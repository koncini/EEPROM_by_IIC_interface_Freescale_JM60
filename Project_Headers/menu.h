/*
 * menu.h
 *
 *  Created on: Nov 11, 2014
 *      Author: Administrator
 */

#ifndef MENU_H_
#define MENU_H_

enum menu{
	PrimeraPantalla=0,
	SegundaPantalla,
	TerceraPantalla,
	CuartaPantalla,
	QuintaPantalla,
	SextaPantalla,
};

void apagarLCD(void);
void despertarLCD(void);
void escribirMenu(void);
void solicitarContrasena(void);
void cambiarContrasena(void);

#endif /* MENU_H_ */
