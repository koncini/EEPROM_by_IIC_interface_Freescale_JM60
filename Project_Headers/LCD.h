 /************************************************
 Compañia: Universidad Catolica de Oriente
 Diseñado por: Luis Felipe Echeverri 
 Fecha: 05/10/2012
 Descripcion: se crean las macros para una implementacion
              versatil en el uso de los pines para
              un LCD 16x2
 Dependencias: derivative.h,DataType.h, string.h
 
 *************************************************

 *        __________________________________________________
 *       |   |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |    
 *       |Vss|Vdd|Vo|RS|RW|EN|D0|D1|D2|D3|D4|D5|D6|D7|A |K |
 *       |   |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   
 *        \                                                /
 *          \                                            /
 *            \                                        /
 *              \____________________________________/__________________
 *             |  \ _______________________________/                    |
 *             |   | | | | | | | | | | | | | | | | |                    |
 *             |   |*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|                    |
 *             |   |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|                    |
 *             |   __________________________________________________   |
 *             |  |  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  |  |
 *             |  | | || || || || || || || || || || || || || || || | |  |
 *             |  | |_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_| |  |
 *             |  |  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  |  |
 *             |  | | || || || || || || || || || || || || || || || | |  |
 *             |  | |_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_| |  |
 *             |  |__________________________________________________|  |
 *             |________________________________________________________|
 *
 *
 * 
 */
/* File: LCD.h */
#ifndef _LCD_H
#define _LCD_H
#include "derivative.h"
#include "DataType.h"
#include <string.h>


/***********************************************
LCD Settings
***********************************************/
//DATA
#define LCD_REG_SEL       PTBD_PTBD0
#define LCD_EN            PTBD_PTBD1
//#define LCD_RW            PTAD_PTAD6
    /* Data bits are 4-7 */
#define LCD_DATA1         PTCD_PTCD4
#define LCD_DATA2         PTCD_PTCD5
#define LCD_DATA3         PTCD_PTCD2
#define LCD_DATA4         PTCD_PTCD3
#define LCD_BACKLIGTH 	  PTBD_PTBD6

//DATADIRECTION
#define LCD_REG_SELDD       PTBDD_PTBDD0
#define LCD_ENDD            PTBDD_PTBDD1
//#define LCD_RWDD            PTADD_PTADD6
#define LCD_DATA1DD         PTCDD_PTCDD4
#define LCD_DATA2DD         PTCDD_PTCDD5
#define LCD_DATA3DD         PTCDD_PTCDD2
#define LCD_DATA4DD         PTCDD_PTCDD3
#define LCD_BACKLIGTHD 	  	PTBDD_PTBDD6
                              
#define LCD_INIT_MACRO  LCD_REG_SELDD=1;LCD_ENDD=1;LCD_DATA1DD=1;LCD_DATA2DD=1;LCD_DATA3DD=1; LCD_DATA4DD=1 

#define MAX_LCD_CHARS 16  


/**************************************************
* Cabeceras de funciones
**************************************************/

void LCDWaitLong(UINT16 w);

void LCDWaitShort(UINT8 w );

void LCDToggleEN( void );

void LCD_Init(void);

void LCDWrite4bits(UINT8 bdata);

void LCDGotoXY(UINT8 x,UINT8 y);

void LCDClearDisplay(void);

void LCDEnableCursor(UINT8 x,UINT8 y);

void LCDDisableCursor(void);

void LCDWriteString(UINT8 x,UINT8 y, UINT8 *str);

void LCDWriteChar(UINT8 ch);
void LCDDisableBackLigth(void);
void LCDEnableBackLigth(void);
void LCDClearDisplayON(void);
void LCDClearDisplayOFF(void);
#endif
