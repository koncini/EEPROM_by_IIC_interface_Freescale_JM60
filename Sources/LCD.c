 /********************************************************
 Compañia: Universidad Catolica de Oriente
 Diseñado por: Luis Felipe Echeverri 
 Fecha: 05/10/2012
 Descripcion: Este codigo incluye las funciones necesarias
              para operar un LCD de 16x2 mediante 4 lineas
              (D4,D5,D6,D7))de datos y 2 lineas de control
              (RS,E) 
 Dependencias: LCD.h

 *********************************************************/

//////////////////////////////////////////////////////////////
//Librerias
//////////////////////////////////////////////////////////////
#include "LCD.h"
#define BACKLIGTH
//////////////////////////////////////////////////////////////
//Funciones: se encuentran las siguientes disponibles
/* 
   LCD_Init()
   LCDGotoXY(UINT8 x,UINT8 y)
   LCDClearDisplay(void)
   LCDWriteString(UINT8 x,UINT8 y, UINT8 *str)
   LCDWriteChar(UINT8 ch)
   LCDEnableCursor(UINT8 x,UINT8 y)
   LCDDisableCursor()
*/
// Usted debe implementar la funcion que permite escribir un caracter en CGRAM 
// para lo cual la funcion requiere los argumentos de (0-7) para el caracter que
// se va a crear o editar y un apuntador donde se encuentre los valores de los cuales
// esta hecho el caracter,luego de hacer esto deben de hacer un icono de cargando
// bateria que estara compuesto por un flecha bajando hacia la bateria 
//
//

//////////////////////////////////////////////////////////////
void LCDGotoXY( UINT8 x,UINT8 y )
{
UINT8 pos;
    /*  Setup the R/W for writing (PTGD), Initialize EN and RS to 0   */
    if(y==2){
    pos=0xC0;
    } 
    else{
     pos=0x80;
    }
    pos=(UINT8)(pos+x);
    
    //LCD_RW = 0;     
    LCD_REG_SEL = 0;     

    /* DD Ram Address Set - 1st Digit */
    LCDWrite4bits(pos);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits((UINT8)(pos<<4));
    LCDToggleEN();
    LCDWaitShort(4);
}

void LCDEnableCursor(UINT8 x,UINT8 y)
{
    LCDGotoXY(x,y);
	LCD_REG_SEL = 0;  
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0xF0);
    LCDToggleEN();
    LCDWaitShort(5);
}

void LCDDisableCursor(void)
{
    /* Setup the R/W for writing (PTGD), Initialize EN and RS to 0 */
    LCD_REG_SEL = 0;
    //LCD_RW = 0; 
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0xC0);
    LCDToggleEN();
    LCDWaitShort(5);
}
void LCDClearDisplay(void)
{
    /* Setup the R/W for writing (PTGD), Initialize EN and RS to 0 */
    LCD_REG_SEL = 0;
    //LCD_RW = 0; 
  
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0x10);
    LCDToggleEN();
    LCDWaitLong(3);
}

void LCDWaitLong(UINT16 w)
{
    UINT16 x;
    UINT16 y;
      
    for ( y = 0; y < w; y++ )
    {
        for ( x = 0; x < 0xFFF; x++ ){};
    }
}

void LCDWaitShort(UINT8 w )
{
    UINT8 x;
    UINT8 y;
      
    for ( y = 0; y < w; y++ )
    {
        for ( x = 0; x < 0xFF; x++ ){};
    }
}

void LCDToggleEN( void )
{

LCD_EN = 1;
LCD_EN = 0; 

}

void LCD_Init(void)
{
    LCDWaitLong(5);
  
  
    LCD_INIT_MACRO;
      
    /* Initialize data port */
    
    LCD_DATA1 = 0;
    LCD_DATA2 = 0;
    LCD_DATA3 = 0;
    LCD_DATA4 = 0;// PTBD = PTBD & 0x0F;    

    /* Setup the R/W for writing (PTBD) */
    
    //LCD_RW = 0; 

    /* Initialize EN and RS to 0 */
    
    LCD_REG_SEL = 0;
    LCD_EN = 0;
    
    /* Send the reset sequence */
    LCDWrite4bits(0x30);
    LCDToggleEN();
      
    LCDWaitLong(5);
  
    LCDWrite4bits(0x30);
    LCDToggleEN();
  
    LCDWaitShort(2);
  
    LCDWrite4bits(0x30);
    LCDToggleEN();
  
    LCDWaitShort(2);

    LCDWrite4bits(0x20);
    LCDToggleEN();
  
    LCDWaitShort(1);
  
    /* Function, 4 bit data length */
    LCDWrite4bits(0x20);
    LCDToggleEN();
  
    LCDWaitShort(1);
  
    /*  2 lines, 5x7 dot format  */
    LCDWrite4bits(0x80);
    LCDToggleEN();
  
    LCDWaitShort(4);
  
    // Entry Mode Inc, No Shift
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0x60);
    LCDToggleEN();
    LCDWaitShort(5);
  
    // Display ON/OFF Control - Display On, Cursor Off, Blink Off
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0xC0);
    LCDToggleEN();
    LCDWaitShort(5);
  
    // Display Clear
    LCDClearDisplay();
  
    //LCDFirstLine();
}

void LCDWrite4bits(UINT8 bdata)
{
    if (bdata & 0x80)        //todo esto permite que aunque los pines sean de diferente puerto 
                            //se pueda llevar el dato
    {
        LCD_DATA4 = 1;//PTBD = PTBD | bdata; 
    }
    else
    {
        LCD_DATA4 = 0;//PTBD = PTBD & 0x7F; 
    }
        
    if (bdata & 0x40)
    {
        LCD_DATA3 = 1;//PTBD = PTBD | bdata; 
    }
      else
    {
        LCD_DATA3 = 0;//PTBD = PTBD & 0xBF; 
    }
        
    if (bdata & 0x20)
    {
        LCD_DATA2 = 1;//PTBD = PTBD | bdata; 
    }
    else
    {
        LCD_DATA2 = 0;//PTBD = PTBD & 0xDF; 

    }
        
    if (bdata & 0x10)
    {
        LCD_DATA1 = 1;//PTBD = PTBD | bdata; 
    }
    else
    {
        LCD_DATA1 = 0;//PTBD = PTBD & 0xEF; 
    }  
}

void LCDWriteCommand(UINT8 cmd)
{
    
    //LCD_RW = 0;
    LCD_REG_SEL = 0;
    LCD_EN = 0; 

    LCDWrite4bits(cmd);  /* cmd bits 4-7 */
  
    LCDToggleEN();

    LCDWrite4bits((UINT8)(cmd << 4));  /* cmd bits 0-3 */
    
    LCDToggleEN();
  
    LCDWaitLong(5);
}


void LCDWriteString(UINT8 x,UINT8 y, UINT8 *str)
{
    UINT8 len;
    UINT8 i;
  
    LCDGotoXY(x,y);
  
    len = (UINT8)strlen(str);

    /* Check boundries  */
    if (len > MAX_LCD_CHARS)
        len = MAX_LCD_CHARS;
      
    for (i = 0; i < len; i++)
    {
        LCDWriteChar(str[i]);
    }
  
    /* Clear the rest of the line */
    //------------------------------
    for (; i < 16; i++)
    {
        LCDWriteChar(' ');
    }
    //--------------------------------
}

void LCDWriteChar(UINT8 ch)
{
    
   // LCD_RW = 0;
    LCD_EN = 0;
    LCD_REG_SEL = 1;
      
    LCDWrite4bits(ch);
    
    LCDToggleEN();
      
    LCDWrite4bits((UINT8)(ch << 4));
      
    LCDToggleEN();
      
    LCDWaitShort(2);
}

void LCDClearDisplayOFF(void)
{
    /* Setup the R/W for writing , Initialize EN and RS to 0 */
    LCD_REG_SEL = 0;
    //LCD_RW = 0; 
  
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0x80);
    LCDToggleEN();
    LCDWaitLong(3);
}
void LCDClearDisplayON(void)
{
    /* Setup the R/W for writing , Initialize EN and RS to 0 */
    LCD_REG_SEL = 0;
    //LCD_RW = 0; 
  
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0xC0);
    LCDToggleEN();
    LCDWaitLong(3);
}
void LCDDisableBackLigth(void){
#ifdef BACKLIGTH
	LCD_BACKLIGTH=0;
#endif
}
void LCDEnableBackLigth(void){
#ifdef BACKLIGTH
	LCD_BACKLIGTH=1;
#endif
}

