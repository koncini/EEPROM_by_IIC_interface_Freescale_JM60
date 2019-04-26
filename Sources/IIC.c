/*"File Comment""***************************************************************
 *   Universidad Catolica de Oriente
 *   Beerware license
 *******************************************************************************
 *  Project Name : 	
 *  File Name    : 	IIC.c
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

// Maximum frequency allowed by the IIC peripheral
// The DS1338 have  400kHz maximum clock rate
// The DS1307 have  100KHz maximum clock rate 
// The HTU21D have  400kHz maximum clock rate
#include "IIC.h"

typedef union{
	word EE_Address;
	struct{
		byte Address_H;
		byte Address_L;
	}Bytes;
}tAddr;

extern volatile tAddr Add;

#define Address Add.EE_Address
#define Addr_L Add.Bytes.Address_L
#define Addr_H Add.Bytes.Address_H
#define IIC_SlaveT 0b10100000
#define IIC_SlaveR 0b10100000
#define MAX_LENGTH 8
#define MAX_PAGE 8
byte temp;

void Init_I2C (void){
	IICC1_IICEN = 1; // Enable I2C;
	IICC1_TXAK = 0; // not generate ACK by master after transfer;	
	IICC1_MST = 1; // Master mode actually;
	IICF = 0x22;// 12.5k->0x39; 50k->0x99; 100k->0x59;
	IICS_SRW = 0; // R/W bit = 0;
}

byte IIC_read_byte(word addr){
	 byte RD_data;
	 Address = addr;
	 temp = (Addr_H & 0x07) << 1;
	 IICC1_TXAK = 0; // RX/TX = 1; MS/SL = 1; TXAK = 0;
	 IICC1 |= 0x30; // And generate START condition;
	 IICD = IIC_SlaveR | temp; // Address the slave and set up for master transmit;
	 while (!IICS_IICIF); // wait until IBIF;
	 IICS_IICIF=1; // clear the interrupt event flag;
	 while(IICS_RXAK); // check for RXAK;
	 //-----Slave ACK occurred------------
	 IICD = Addr_L; // Send low byte of word address;
	 while (!IICS_IICIF); // wait until IBIF;
	 IICS_IICIF=1; // clear the interrupt event flag;
	 while(IICS_RXAK); // check for RXAK;
	 //-----Slave ACK occurred------------
	 IICC1_RSTA = 1; // set up repeated start;
	 IICD = IIC_SlaveR | temp | 1; // (slave_address) | (RW = 1);
	 while (!IICS_IICIF); // wait until IBIF;
	 IICS_IICIF=1; // clear the interrupt event flag;
	  while (IICS_RXAK); // check for RXAK;
	  //-----Slave ACK occurred------------
	  IICC1_TX = 0; // set up to receive;
	  IICC1_TXAK = 1; // acknowledge disable;
	  RD_data = IICD; // dummy read;
	  while (!IICS_IICIF); // wait until IBIF;
	  IICS_IICIF=1; // clear the interrupt event flag;
	  IICC1_MST = 0; // generate stop signal;
	  RD_data = IICD; // read right data;
	  return RD_data;
}

void IIC_write_byte(word addr, byte data){
	 Address = addr; // load address;
	 temp = (Addr_H & 0x07) << 1;
	 IICC1_TXAK = 0; // RX/TX = 1; MS/SL = 1; TXAK = 0;
	 IICC1 |= 0x30; // And generate START condition;
	 //-------start of transmit first byte to IIC bus-----
	 IICD = IIC_SlaveT | temp; // Address the slave and set up for master transmit;
	 while (!IICS_IICIF); // wait until IBIF;
	 IICS_IICIF=1; // clear the interrupt event flag;
	 while(IICS_RXAK); // check for RXAK;
	 //-----Slave ACK occurred------------
	 IICD = Addr_L; // Send low byte of the word address;
	 while (!IICS_IICIF); // wait until IBIF;
	 IICS_IICIF=1; // clear the interrupt event flag;
	 while(IICS_RXAK); // check for RXAK;
	 //-----Slave ACK occurred------------
	 IICD = data;
	 while (!IICS_IICIF); // wait until IBIF;
	 IICS_IICIF=1; // clear the interrupt event flag;
	 while(IICS_RXAK); // check for RXAK;
	 //-----Slave ACK occurred------------
	 IICS_IICIF=1; // clear the interrupt event flag;
	 IICC1_MST = 0; // generate STOP condition;
}

void IIC_read_block(word addr,byte len){
	 byte length;
	 Address = addr;
	 length = len;
	 //i = 0; // for interrupt only;
	 //IIC_Res_flg = 0; // for interrupt only;
	 //flag = 10; // defines receive function in the interrupt service routine;
	 if(length > MAX_LENGTH) length = MAX_LENGTH;
	 IICC1_TXAK = 0; // RX/TX = 1; MS/SL = 1, TXAK = 0;
	 IICC1 |= 0x30; // And generate START condition;
	 IICD = IIC_SlaveR; // Address the slave and set up for master transmit;
}

void IIC_write_block(word addr, byte len){
	 byte length;
	 Address = addr; // load address;
	 length = len; // load length of data pack to be written;
	 //i = 0; // for interrupt only;
	 //IIC_Res_flg = 0; // for interrupt only;
	 //flag = 2; // defines transmit function in the interrupt service routine;
	 if(length > MAX_PAGE) length = MAX_PAGE; // set limit;
	 IICC1_TXAK = 0; // RX/TX = 1; MS/SL = 1; TXAK = 0;
	 IICC1 |= 0x30; // And generate START condition;
	 IICD = IIC_SlaveT; // Address the slave and set up for master transmit;
}
/*Tabla 11.2              
 ______________________ 
|   MUL    |  factor   |
|----------|-----------|
|    00    |     1     |
|    01    |     2     |
|    10    |     4     |
|    11    | Reserved  |
|__________|___________|

tabla 11.3
_______________________________________________     _______________________________________________
|  ICR   |  SCL    |SDA Hold|SCL Hold |SCL Hold|   |  ICR   |  SCL    |SDA Hold|SCL Hold |SCL Hold|
| (Hex)  | Divider | Value  |(start)  | (stop) |   | (Hex)  | Divider | Value  |(start)  | (stop) |
|________|_________|________|_________|________|   |________|_________|________|_________|________|
|  00    |   20    |   7    |    6    |   11   |   |  20    |   160   |   17   |    78   |   81   |
|  01    |   22    |   7    |    7    |   12   |   |  21    |   192   |   17   |    94   |   97   |
|  02    |   24    |   8    |    8    |   13   |   |  22    |   224   |   33   |    110  |   113  |
|  03    |   26    |   8    |    9    |   14   |   |  23    |   256   |   33   |    126  |   129  |
|  04    |   28    |   9    |    10   |   15   |   |  24    |   288   |   49   |    142  |   145  |
|  05    |   30    |   9    |    11   |   16   |   |  25    |   320   |   49   |    158  |   161  |
|  06    |   34    |   10   |    13   |   18   |   |  26    |   384   |   65   |    190  |   193  |
|  07    |   40    |   10   |    16   |   21   |   |  27    |   480   |   65   |    238  |   241  |
|  08    |   28    |   7    |    10   |   15   |   |  28    |   320   |   33   |    158  |   161  |
|  09    |   32    |   7    |    12   |   17   |   |  29    |   384   |   33   |    190  |   193  |
|  0A    |   36    |   9    |    14   |   19   |   |  2A    |   448   |   65   |    222  |   225  |
|  0B    |   40    |   9    |    16   |   21   |   |  2B    |   512   |   65   |    254  |   257  |
|  0C    |   44    |   11   |    18   |   23   |   |  2C    |   576   |   97   |    286  |   289  |
|  0D    |   48    |   11   |    20   |   25   |   |  2D    |   640   |   97   |    318  |   321  |
|  0E    |   56    |   13   |    24   |   29   |   |  2E    |   768   |   129  |    382  |   385  |
|  0F    |   68    |   13   |    30   |   35   |   |  2F    |   960   |   129  |    478  |   481  |
|  10    |   48    |   9    |    18   |   25   |   |  30    |   640   |   65   |    318  |   321  |
|  11    |   56    |   9    |    22   |   29   |   |  31    |   768   |   65   |    382  |   385  |
|  12    |   64    |   13   |    26   |   33   |   |  32    |   896   |   129  |    446  |   449  |
|  13    |   72    |   13   |    30   |   37   |   |  33    |   1024  |   129  |    510  |   513  |
|  14    |   80    |   17   |    34   |   41   |   |  34    |   1152  |   193  |    574  |   577  |
|  15    |   88    |   17   |    38   |   45   |   |  35    |   1280  |   193  |    638  |   641  |
|  16    |   104   |   21   |    46   |   53   |   |  36    |   1536  |   257  |    766  |   769  |
|  17    |   128   |   21   |    58   |   65   |   |  37    |   1920  |   257  |    958  |   961  |
|  18    |   80    |   9    |    38   |   41   |   |  38    |   1280  |   129  |    638  |   641  |
|  19    |   96    |   9    |    46   |   49   |   |  39    |   1536  |   129  |    766  |   769  |
|  1A    |   112   |   17   |    54   |   57   |   |  3A    |   1792  |   257  |    894  |   897  |
|  1B    |   128   |   17   |    62   |   65   |   |  3B    |   2048  |   257  |    1022 |   1025 |
|  1C    |   144   |   25   |    70   |   73   |   |  3C    |   2304  |   385  |    1150 |   1153 |
|  1D    |   160   |   25   |    78   |   81   |   |  3D    |   2560  |   385  |    1278 |   1281 |
|  1E    |   192   |   33   |    94   |   97   |   |  3E    |   3072  |   513  |    1534 |   1537 |
|  1F    |   204   |   33   |    118  |   121  |   |  3F    |   3840  |   513  |    1918 |   1921 | 
|________|_________|________|_________|________|   |________|_________|________|_________|________|
*/
