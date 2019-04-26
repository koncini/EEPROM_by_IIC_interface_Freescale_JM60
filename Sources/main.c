 /****************************************************************************
 Companie: Universidad Catolica de Oriente
 Developed by: Juan sebastian Rincón Manrique - Jhon jairo montolla gallo
 Date: 08/09/2016
 Description: This code uses the matrix keyboard, 2X16 LCD and IIC libraries,
 to show a menu that allows you to: watch, log and change a four digit password.
 Dependencies: DataType.h, LCD.h, LCD.c, keyboard.h,IIC.h,IIC.c,main.h y keyboard.c
 ****************************************************************************/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "DataType.h" /* include types */
#include "Events.h" /* include interruptions */
#include "Keyboard.h" /* include peripheral declarations */
#include "LCD.h" /* include peripheral declarations */
#include "IIC.h" /* include peripheral declarations */
#include "menu.h" /* include menu */
#include "convfunc.h"/* include convert functions */


/* variables declarations*/
UINT8 u8Tecla[2]={0,0};                         //Variable with info from the pressed key
UINT8 menu=0,paso=0,bandera=0,aux=0;            //Control variables "Menu number", "key number", "flag number", "auxiliary flag"
UINT8 Contrasena[4];                            //Password joined by the user from keyboard
UINT8 ContrasenaMem[4];                         //Password read from the EEPROM
UINT8 ContrasenaMem2[4];                        //*
UINT8 ContrasenaMem3[4];                        //*
UINT8 ContrasenaMem4[4];                        //*
UINT8 ContrasenaDefecto[4]={'0','0','0','0'};   //Password read from the EEPROM
UINT8 c,c2,c3,c4;						        //Password decimal digits variables       

void main(void) {
	SOPT1=0x02; /* KILL THE WATCHDOG */

	/*************************************************************************/
	//                 PORTS AND FUNCTIONS INITIALIZATION                    //
	EnableInterrupts;
	Init_I2C ();
	MCGTRM=NVMCGTRM;
	LCD_Init();
	Keyboard_Init();
	ConvertoAscci(IIC_read_byte(0x0001),4,ContrasenaMem);   
	ConvertoAscci(IIC_read_byte(0x0003),4,ContrasenaMem2);
	ConvertoAscci(IIC_read_byte(0x0005),4,ContrasenaMem3);
	ConvertoAscci(IIC_read_byte(0x0007),4,ContrasenaMem4);
	///************************************************************************

	for(;;) {
		if (Keyboardflag==1 && menu==PrimeraPantalla){//Welcome message
			u8Tecla[0]=keydecoder();
			if (u8Tecla[0]=='*'){//Access to the password confirmation
				menu=1;
				bandera=1;
			}
		}
		
		if (Keyboardflag==1 && menu==TerceraPantalla){ //Password menu
			Keyboardflag=0;
			u8Tecla[0]=keydecoder();
			if (u8Tecla[0]=='1'){//Change password
				menu=4;
				bandera=4;
			}
			else if (u8Tecla[0]=='2'){//Return to welcome screen
				menu=0;
				bandera=0;
			}
		}
		
		if (Keyboardflag==1 && menu==CuartaPantalla){//Incorrect password message
			Keyboardflag=0;
			u8Tecla[0]=keydecoder();
			if (u8Tecla[0]=='D'){//It takes you to the welcome screen
				menu=0;
				bandera=0;
			}
		}
		
		if (Keyboardflag==1 && menu==QuintaPantalla){ //Change password menu
			Keyboardflag=0;
			u8Tecla[0]=keydecoder();
		}
		
		if (Keyboardflag==1 && menu==SextaPantalla){ //Confirmation screen that loads new password
			Keyboardflag=0;
			u8Tecla[0]=keydecoder();
			if (u8Tecla[0]=='1'){//Confirm and load new password
				menu=0;
				bandera=0;
				c=Contrasena[0]-0x30;      //Converts the user loged password digit to decimal from ascii
				c2=Contrasena[1]-0x30;     //*
				c3=Contrasena[2]-0x30;     //*
				c4=Contrasena[3]-0x30;     //*
				IIC_write_byte(0x0001, c); // Writhes first digit
				LCDWaitLong(20);           //Wait
				IIC_write_byte(0x0003, c2);//writhes second digit
				LCDWaitLong(20);           //Wait
				IIC_write_byte(0x0005, c3);//writhes third digit
				LCDWaitLong(20);           //wait
				IIC_write_byte(0x0007, c4);//writhes fourth digit
			} else if (u8Tecla[0]=='2'){   //Cancel password update,it takes you to the change password menu
				menu=4;
				bandera=4;
			}
		}
		
		// * * * * * * * * * * Menus * * * * * * * * * * *
		escribirMenu();
	}
}
