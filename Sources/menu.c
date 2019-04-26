/*
 * menu.c
 *
 *  Created on: Sep 08, 2016
 *      Author: Sebastián and Jairo
 */

#include "menu.h"
#include "DataType.h"
#include "LCD.h"
#include "keyboard.h"
#include "IIC.h"
#include "convfunc.h"

extern UINT8 aux,bandera,menu,paso; //External control variables 
extern UINT8 u8Tecla[2];            //External variable with info from the pressed key
extern byte Contrasena[4];          //Password from keyboard
extern byte ContrasenaMem[4];       //Password first digit read from EEPROM
extern byte ContrasenaMem2[4];      //Password second digit read from EEPROM
extern byte ContrasenaMem3[4];      //Password third digit read  from EEPROM
extern byte ContrasenaMem4[4];      //Password fourth digit read from EEPROM

void apagarLCD(void){               //Turns off LCD
	RTCSC=0b00000000;
	menu=PrimeraPantalla;
	Keyboard_Init();
	LCDDisableBackLigth();
	LCDDisableCursor();
	LCDClearDisplay();
}

void despertarLCD(void){            //Turns on LCD
	Keyboard_Init();
	bandera=PrimeraPantalla;
	menu=PrimeraPantalla;
	aux=0;
}

void escribirMenu(void){  //Method that according to menu and flag writes the info showed in LCD
	if (menu==PrimeraPantalla && bandera==PrimeraPantalla){  //Welcome screen
		bandera=1;
		LCDClearDisplay();
		LCDEnableBackLigth();
		LCDDisableCursor();
		LCDWriteString(0,1,"SECURITY SYSTEM");
		LCDWriteString(0,2," JAIRO - SEBAS ");
	}
	if (menu==SegundaPantalla && bandera==SegundaPantalla){  //Password join screen
		bandera=2;
		LCDClearDisplay();
		LCDWriteString(0,1,"INGRESE SU CLAVE");
		LCDGotoXY(0,2);
		LCDEnableCursor(0,2);
		solicitarContrasena(); //Here the password confirmation method is called
	}
	if (menu==TerceraPantalla && bandera==TerceraPantalla){  //Password editing screen
		bandera=3;
		LCDClearDisplay();
		LCDDisableCursor();
		LCDWriteString(0,1,"1. CAMBIAR CLAVE");
		LCDWriteString(0,2,"2. CANCELAR");
	}
	if (menu==CuartaPantalla && bandera==CuartaPantalla){  //Wrong password screen
		bandera=4;
		paso=0;
		LCDClearDisplay();
		LCDWriteString(0,1,"ERROR CONTRASENA");
		LCDWriteString(0,2,"PRESIONE D");	
	}
	if (menu==QuintaPantalla && bandera==QuintaPantalla){  //New password join screen
		bandera=5;
		LCDClearDisplay();
		LCDWriteString(0,1,"NUEVA CONTRASENA:");
		LCDGotoXY(0,2);
		LCDEnableCursor(0,2);
		cambiarContrasena(); //Here the password change method is called
	}
	if (menu==SextaPantalla && bandera==SextaPantalla){  //Confirmation screen
		bandera=6;
		LCDClearDisplay();
		LCDWriteString(0,1,"1. CONFIRMAR");
		LCDWriteString(0,2,"2. CANCELAR");
	}
}

//Password change method
void cambiarContrasena(void){ //Reads an four digit code from the keyboard an writes it in EEPROM 
	paso=0;                   //Reset digit counter
	while (paso<=3){          
		if (Keyboardflag==1){
			Keyboardflag=0;   //Reset keyboard flag
			u8Tecla[0]=keydecoder();
			if (u8Tecla[0]!='N' && u8Tecla[0]>0x29 && u8Tecla[0]<0x3A){ //Validates key between 0-9
				Contrasena[paso]=u8Tecla[0];
				LCDWriteChar('*');
				LCDWaitLong(20);
				paso++;
				if (paso==4){
					LCDDisableCursor();
				} 
			}else if (u8Tecla[0]=='C'){//It takes you to the welcome screen
				menu=0;
				bandera=0;
				paso=5;
			}
		}
	}paso=0;
	while (paso<=1){
		if (Keyboardflag==1){
			Keyboardflag=0;
			u8Tecla[0]=keydecoder();
			if (u8Tecla[0]=='D'){	// Confirms password change
				menu=SextaPantalla;
				bandera=SextaPantalla;
				paso=5;
			} else if (u8Tecla[0]=='C'){//It takes you to the welcome screen
				menu=0;
				bandera=0;
				paso=5;
			}
		}
	}
}


//Password confirmation method
void solicitarContrasena(void){  //Reads an four digit code from the keyboard and compares with the stored in EEPROM
	paso=0;                      //Reset digit counter
	while (paso<=3){
		if (Keyboardflag==1){    //Reset keyboard flag
			Keyboardflag=0;
			u8Tecla[0]=keydecoder();
			if (u8Tecla[0]!='N' && u8Tecla[0]>0x29 && u8Tecla[0]<0x3A){		//Validates key between 0-9
				Contrasena[paso]=u8Tecla[0];
				LCDWriteChar('*');
				LCDWaitLong(20);
				paso++;
				if (paso==4){
					LCDDisableCursor();
				}
			}
		}
	}paso=0;
	while (paso<=1){
		if (Keyboardflag==1){
			Keyboardflag=0;
			u8Tecla[0]=keydecoder();
		    if (u8Tecla[0]=='D'){	 // Confirms password and compares
		    	ConvertoAscci(IIC_read_byte(0x0001),4,ContrasenaMem);   //Read password stored in EEPROM and converts it in ascii values
		    	ConvertoAscci(IIC_read_byte(0x0003),4,ContrasenaMem2);  //*
		    	ConvertoAscci(IIC_read_byte(0x0005),4,ContrasenaMem3);  //*
		    	ConvertoAscci(IIC_read_byte(0x0007),4,ContrasenaMem4);  //*
		    	
		    	//Compare password from EEPROM and the password joined by the user//
				if (Contrasena[0]==ContrasenaMem[3] && Contrasena[1]==ContrasenaMem2[3] && Contrasena[2]==ContrasenaMem3[3] && Contrasena[3]==ContrasenaMem4[3]){
					menu=TerceraPantalla;
					bandera=TerceraPantalla;
					paso=5;
				}
				else{ //if the password is not correct it takes you to the wrong screen
					paso=5;
					menu=CuartaPantalla;
					bandera=CuartaPantalla;
				}
			}
		}
	}
}


	
