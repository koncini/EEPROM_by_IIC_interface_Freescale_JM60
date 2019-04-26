/*"File Comment""***************************************************************
 *   Universidad Catolica de Oriente
 *   Beerware license
 *******************************************************************************
 *  Project Name : 	
 *  File Name    : 	IIC.h
 *  Content      : 	
 *  CPU          : 	MC9S08JM60
 *  Compiler     : 	CodeWarrior for HCS08 10.6
 *  License		 : 	This code is public domain but you buy me a beer if you use this and we meet someday 
 *  			   	(Beerware license).
 *  OS           :  None           
 *  Description  :  This code implements the IIC functions
 *					                  
 *  UPDATED HISTORY:
 *  REV   YYYY.MM.DD  AUTHOR            DESCRIPTION OF CHANGE        Company
 *  ---   ----------  ----------------  ---------------------        -------------------------------
 *  0.1   2015.02.04  Felipe Echeverri  Created						 Universidad Catolica de Oriente
*/

#ifndef IIC_H_
#define IIC_H_
#include "derivative.h"

//#define IIC_SlaveT 0b10100000
//#define IIC_SlaveR 0b10100000

void Init_I2C (void);

void IIC_write_byte(word addr, byte data);

void IIC_read_block(word addr,byte len);

byte IIC_read_byte(word addr);

void IIC_write_block(word addr, byte len);

#endif /* IIC_H_ */
