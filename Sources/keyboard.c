 /****************************************************************************
 Compañia: Universidad Catolica de Oriente
 Diseñado por: Luis Felipe Echeverri 
 Fecha: 05/10/2012
 Descripcion: Este codigo permite la inicializacion y gestion
              de un teclado matricial de 4x4 teclas, el cual entregara
              el ASCCI correspondiente a la tecla presionada mediante la
              funcion keydecoder(), recuerde inicializar el modulo mediante
              Keyboard_Init() y llamar al keydecoder() una vez FlagKBI=1 con 
			  el fin de identificar la tecla presionada. Este codigo permite 
			  elegir dos opciones para esperar el tiempo de rebote, la primera 
			  mediante la habilitacion de la macro --#define  WITH_RTC--
			  la cual peritirá generar una interrupcion cada 64 mseg despues de la 
			  deteccion de un flanco de KBI, si no se elige esta opción el sistema 
			  hará un ciclo largo de espera en el keydecoder bloqueando la CPU mientras 
			  pasa el tiempo de rebote mecanico de los pulsadores    
			  
 Dependencias: Events.h, keyboard.h

 *****************************************************************************/
//////////////////////////////////////////////////////////////
//Librerias
//////////////////////////////////////////////////////////////
#include "keyboard.h" 
#ifdef  WITH_RTC
#include "RTC.h"    // habilita bandera para gestionar en el main el llamado al keydecoder
#endif    
//////////////////////////////////////////////////////////////
//cabecera de funciones con uso exclusivo para este archivo
//////////////////////////////////////////////////////////////
static void KBIWaitLong(UINT16 w);

//////////////////////////////////////////////////////////////
//Interrupciones para el manejo del teclado matricial
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
interrupt VectorNumber_Vkeyboard void ISR_KBI(void){
KBISC_KBIE=0;  //desactiva interrupciones por kbi
KBISC_KBACK=1; //reconocimiento de la interrupcion

#ifdef  WITH_RTC
//reinicia el RTCNT
	RTC_Init(1,2);//64ms
#else
   Keyboardflag=1;      // habilita bandera para gestionar en el main el llamado al keydecoder
#endif
}
//////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////
#ifdef  WITH_RTC
interrupt VectorNumber_Vrtc void Isr_RTC(){
  Keyboardflag=1;        // habilita bandera para gestionar en el main el llamado al keydecoder 
  RTCSC_RTIF=1;     // reconocimiento de la interrupcion
  RTCSC_RTIE=0;     // deshabilita interrupciones
}
#endif
//////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//  retardo para garantizar que el tiempo del rebote ha transcurrido
//  la mayoria de los switches presentan un rebote de a 1/6 de segundo
//  segun http://www.eng.utah.edu/~cs5780/debouncing.pdf

//////////////////////////////////////////////////////////////
// KBIWaitLong este retardo hace uso de aproximadamente 86148 
// ciclos de BusCLK, si se le pasa como argumento el numero 6 
// consumira 64.6ms paara  un reloj de bus de 8MHZ 
///////////////////////////////////////////////////////////////
static void KBIWaitLong(UINT16 w){
    UINT16 x;
    UINT16 y;
      
    for ( y = 0; y < w; y++ )
    {
        for ( x = 0; x < 0xFFF; x++ ){};   
    }
}
//////////////////////////////////////////////////////////////
// Pequeño retardo para garantizar que el valor leido del puerto
// se actualice debido a los retardos generados por las capacitancias
// internas del pin
//
//////////////////////////////////////////////////////////////

void PINWaitShort(void) //este retardo hace uso de 137 ciclos de BusCLK
{
    UINT16 x;
        for ( x = 0; x < 0x05; x++ ){};
}

////////////////////////////////
//Inicializacion del keyboard
////////////////////////////////
void Keyboard_Init(void){
COLOUT();       //se configuran los pines de las columnas como salidas
COLCERO();      //se coloca un cero en las columnas 
ROWIN();        //se habilitan las filas como entradas
ROWPE();        //se habilitan las resistencias de pull-up para las filas 
ROWKBIEN();     //se habilitan el modulo de kbi para las filas
ROWKBIEDG();     //deteccion de flanco de bajada
KBISC_KBACK=1;  //se limpia cualquier interrupcion por senales espurias
KBISC_KBMOD=0;  //detecta flanco solamente
KBISC_KBIE=1;   //habilita interrupciones por kbi
}

//////////////////////////////////////////////////////////////
// funcion para detectar la tecla presionada
//////////////////////////////////////////////////////////////
UINT8 keydecoder(void){
 UINT8 keypress='N';
 volatile UINT8 dato=0x00;
//------------------------------------------------
//realiza la espera si no esta operando con el RTC 
 #ifndef  WITH_RTC
   KBIWaitLong(6);
 #endif
 //-----------------------------------------------
 
dato=dato | ROW1D| (ROW2D<<1)| (ROW3D<<2)|(ROW4D<<3);

ROWKBIDIS();  //deshabilita el kbi de las filas
COLIN();      //se configuran las columnas como entradas
COLPE();      //se habilitan el pull-up para las columnas
ROWOUT();     //se configuran las filas como salidas
ROWCERO();    //se coloca un cero en las filas
PINWaitShort();  // Espera para que el pin se estabilice por las capacitancias internas de este  
dato=dato | (COL1D<<4)| (COL2D<<5)| (COL3D<<6)| (COL4D<<7);


  switch (dato){
    
  case 0b11101110: 
  keypress='1';
  break;
  case 0b11101101:
  keypress='4';
  break;
  case 0b11101011:
  keypress='7';
  break;
  case 0b11100111:
  keypress='*';
  break;


  case 0b11011110: 
  keypress='2';
  break;
  case 0b11011101:
  keypress='5';
  break;
  case 0b11011011:
  keypress='8';
  break;
  case 0b11010111:
  keypress='0';
  break;
  
  case 0b10111110: 
  keypress='3';
  break;
  case 0b10111101:
  keypress='6';
  break;
  case 0b10111011:
  keypress='9';
  break;
  case 0b10110111:
  keypress='#';
  break;
  
  case 0b01111110: 
  keypress='A';
  break;
  case 0b01111101:
  keypress='B';
  break;
  case 0b01111011:
  keypress='C';
  break;
  case 0b01110111:
  keypress='D';
  break;
  
  default:
  keypress='N';    //indica la no deteccion de la tecla debido a una 
  break;           //pulsacion rápida o se presionaron al tiempo mas de una.
}
Keyboard_Init();   //se vuelve habilitar el modulo KBI 
return keypress;
}
