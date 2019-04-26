 /****************************************************************************
 Compañia: Universidad Catolica de Oriente
 Diseñado por: Luis Felipe Echeverri 
 Fecha: 20/04/2013
 Descripcion: Se configura el modulo rtc para generar interrupciones cada xxseg
			  el usuario debera cambiar el prescalador ubicado en el registro 
			  RTCSC y el modulo RTCMOD con el fin de obtener el periodo deseado
 Dependencias: RTC.h
 ****************************************************************************/
 #include "RTC.h"
void RTC_Init(UINT8 Module, UINT8 Prescaler){
RTCMOD=Module;
RTCSC=  0b00010000 | Prescaler;
//RTCSC=0b00011111;
//        ||||||||____(xxxx): prescalador ver tabla 17.3
//        ||||________(1)   : interrup enable: 1) enable , 0)disable
//        |||_________(00)  : clock source: 00 LPO 1KHz, 01 external, 1X internal
//        |___________(0)   : interrupt flag:

}

 interrupt VectorNumber_Vrtc void IsrRTC(void){
  RTCSC_RTIF=1; //interrupt request
  RTCflag =1;

}
/*Table 17-3.
   ___________________________ 
  |     |                     |
  |RTCPS| 1KHz internal clock |
  |     |     (RTCCLKS=00)    |
  |_____|_____________________|
  |     |                     |
  |0000 | Off                 |
  |_____|_____________________|
  |     |                     |
  |0001 | 8ms                 |
  |_____|_____________________|
  |     |                     |
  |0010 | 32ms                |
  |_____|_____________________|
  |     |                     |
  |0011 | 64ms                |
  |_____|_____________________|
  |     |                     |
  |0100 | 128ms               |
  |_____|_____________________|
  |     |                     |
  |0101 | 256ms               |
  |_____|_____________________|
  |     |                     |
  |0110 | 512ms               |
  |_____|_____________________|
  |     |                     |
  |0111 | 1.024s              |
  |_____|_____________________|
  |     |                     |
  |1000 | 1ms                 |
  |_____|_____________________|
  |     |                     |
  |1001 | 2ms                 |
  |_____|_____________________|
  |     |                     |
  |1010 | 4ms                 |
  |_____|_____________________|
  |     |                     |
  |1011 | 10ms                |
  |_____|_____________________|
  |     |                     |
  |1100 | 16ms                |
  |_____|_____________________|
  |     |                     |
  |1101 | 0.1s                |
  |_____|_____________________|
  |     |                     |
  |1110 | 0.5ms               |
  |_____|_____________________|
  |     |                     |
  |1111 | 1s                  |
  |_____|_____________________|

 
*/
