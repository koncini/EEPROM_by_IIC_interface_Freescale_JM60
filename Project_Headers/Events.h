#ifndef _EVENTS_H
#define _EVENTS_H
#include "DataType.h"
 

typedef union {
	UINT32 Flag;	    	// Access all register
	struct {
		UINT32 IRQ	    :1;	// Access to bit 0
		UINT32 LVD	    :1;	// Access to bit 1
		UINT32 LOL	    :1;	// Access to bit 2
		UINT32 SPI1     :1; // Access to bit 3
		UINT32 SPI2	    :1;	// Access to bit 4
		UINT32 USB	    :1;	// Access to bit 5
		UINT32 TPM1Ch0  :1;	// Access to bit 6
		UINT32 TPM1Ch1	:1;	// Access to bit 7
		UINT32 TPM1Ch2	:1;	// Access to bit 8
		UINT32 TPM1Ch3	:1;	// Access to bit 9
		UINT32 TPM1Ch4	:1;	// Access to bit 10
		UINT32 TPM1Ch5	:1;	// Access to bit 11
		UINT32 TPM1Ov	:1;	// Access to bit 12
		UINT32 TPM2Ch0  :1;	// Access to bit 13
		UINT32 TPM2Ch1	:1;	// Access to bit 14
		UINT32 TPM2Ov	:1;	// Access to bit 15
		UINT32 SCI1Err  :1;	// Access to bit 16
		UINT32 SCI1Rx   :1;	// Access to bit 17
		UINT32 SCI1Tx   :1;	// Access to bit 18
		UINT32 SCI2Err  :1; // Access to bit 19
		UINT32 SCI2Rx	:1;	// Access to bit 20
		UINT32 SCI2Tx	:1;	// Access to bit 21
		UINT32 Keyboard :1;	// Access to bit 22
		UINT32 ADC	    :1;	// Access to bit 23
		UINT32 ACMP	    :1;	// Access to bit 24
		UINT32 IIC   	:1;	// Access to bit 25
		UINT32 RTC	    :1;	// Access to bit 26

} Bits;
} STR_FLAGS;

extern volatile STR_FLAGS _INT_Events;
 
#define INT_EVENTS	   _INT_Events.Flag          // All register
#define	IRQflag        _INT_Events.Bits.IRQ      // Bit 0
#define	LVDflag        _INT_Events.Bits.LVD      // Bit 1
#define	LOLflag        _INT_Events.Bits.LOL      // Bit 2
#define	SPI1flag       _INT_Events.Bits.SPI1     // Bit 3
#define	SPI2flag       _INT_Events.Bits.SPI2     // Bit 4
#define	USBflag        _INT_Events.Bits.USB      // Bit 5
#define	TPM1Ch0flag    _INT_Events.Bits.TPM1Ch0  // Bit 6
#define	TPM1Ch1flag    _INT_Events.Bits.TPM1Ch1  // Bit 7
#define	TPM1Ch2flag    _INT_Events.Bits.TPM1Ch2  // Bit 8
#define	TPM1Ch3flag    _INT_Events.Bits.TPM1Ch3  // Bit 9
#define	TPM1Ch4flag    _INT_Events.Bits.TPM1Ch4  // Bit 10
#define	TPM1Ch5flag    _INT_Events.Bits.TPM1Ch5  // Bit 11
#define	TPM1Ovflag     _INT_Events.Bits.TPM1Ov   // Bit 12
#define	TPM2Ch0flag    _INT_Events.Bits.TPM2Ch0  // Bit 13
#define	TPM2Ch1flag    _INT_Events.Bits.TPM2Ch1  // Bit 14
#define	TPM2Ovflag     _INT_Events.Bits.TPM2Ov   // Bit 15
#define	SCI1Errflag    _INT_Events.Bits.SCI1Err  // Bit 16
#define	SCI1Rxflag     _INT_Events.Bits.SCI1Rx   // Bit 17
#define	SCI1Txflag     _INT_Events.Bits.SCI1Tx   // Bit 18
#define	SCI2Errflag    _INT_Events.Bits.SCI2Err  // Bit 19
#define	SCI2Rxflag     _INT_Events.Bits.SCI2Rx   // Bit 20
#define	SCI2Txflag     _INT_Events.Bits.SCI2Tx   // Bit 21
#define	Keyboardflag   _INT_Events.Bits.Keyboard // Bit 22
#define	ADCflag        _INT_Events.Bits.ADC      // Bit 23
#define	ACMPflag       _INT_Events.Bits.ACMP     // Bit 24
#define	IICflag        _INT_Events.Bits.IIC      // Bit 25
#define	RTCflag        _INT_Events.Bits.RTC      // Bit 26
 
#endif
