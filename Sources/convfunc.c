#include "convfunc.h" 

 /****************************************************************************
 Compañia: Universidad Catolica de Oriente
 Diseñado por: Luis Felipe Echeverri 
 Fecha: 20/04/2013
 Descripcion:
 ConvertoAscci: funcion para convertir un numero entero a ascci, esta funcion  
                recibe como parametros, el entero a convertir mediant u16entero,  
                en u8tamano se recibe la cantidad de bytes que ocupará el numero  
                despues de la conversion, en donde el agregará ceros si el valor  
                resultante tiene menos caracteres que el tamanno recibido, y por  
                ultimo un apuntador a la cadena donde sera almacenada la conversion.
  ejemplo: u16entero=34,u8tamano=8,u8ptrconvascci=&dato[0] 
             dato[0]='0'
             dato[1]='0'
             dato[2]='0'
             dato[3]='0'
             dato[4]='0'
             dato[5]='0'
             dato[6]='3'
             dato[7]='4'

 ****************************************************************************/

  void ConvertoAscci(UINT16 u16entero,UINT8 u8tamano,UINT8 *u8ptrconvascci){
   UINT8 u8i=0;
    u8ptrconvascci+=(u8tamano-1); 
    for(u8i=1;u8i<=u8tamano;u8i++){
    *u8ptrconvascci--= u16entero%10 +0x30;
    u16entero/=10;
    } 
  }
