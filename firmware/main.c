#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "hw_setup.h"
#include "avrdbg.h"
#include "avrutils.h"
#include "prg_spi.h"
#include "prg_parse.h"
#include "usbdrv.h"

void init_hw(void)
{
	// the LEDs
	SetBit(DDR(LED_ERR_PORT), LED_ERR_BIT);
	ClrBit(PORT(LED_ERR_PORT), LED_ERR_BIT);

	SetBit(DDR(LED_PROG_PORT), LED_PROG_BIT);
	ClrBit(PORT(LED_PROG_PORT), LED_PROG_BIT);

	SetBit(DDR(LED_USB_PORT), LED_USB_BIT);
	ClrBit(PORT(LED_USB_PORT), LED_USB_BIT);

#ifndef	ON_USBASP
	dbgInit();			// init the UART debug output (only possible on the nrfBurn board)
#endif
	
	progParseInit();	// init the programming protocol interface

	ProgSpiInit();		// init the programming hardware (SPI and the rest of the pins)
	
	// setup v-usb
	usbInit();
	usbDeviceDisconnect();	// enforce re-enumeration, do this while interrupts are disabled!
	_delay_ms(260);
	usbDeviceConnect();

	// enable interrupts
	sei();
}

/*
void swdLineReset(void)
{
	// drive 1
	SetBit(PORT(SWDIO_PORT), SWDIO_BIT);

	int i;
	for (i = 0; i < 100; i++)
	{
		TogBit(PORT(SWDCLK_PORT), SWDCLK_BIT);
		TogBit(PORT(SWDIO_PORT), SWDIO_BIT);
	}
}

typedef union swd_packet_t
{
	uint8_t		val;
	struct {
		unsigned int	start : 1;		// always 1
		unsigned int	is_ap : 1;		// 1 == APACC, 0 == DPACC
		unsigned int	is_read : 1;	// 1 == read, 0 = write
		unsigned int	reg_addr2 : 1;	// bits 2 & 3 of DP or AP register address
		unsigned int	reg_addr3 : 1;	//
		unsigned int	parity : 1;		//
		unsigned int	stop : 1;		//
		unsigned int	park : 1;		//
	} bits;
} swd_packet_t;

const uint8_t parity_calc[] = 
{
	0b100,		// 0b10000
	0b000,		// 0b10001
	0b000,		// 0b10010
	0b100,		// 0b10011
	0b000,		// 0b10100
	0b100,		// 0b10101
	0b100,		// 0b10110
	0b000,		// 0b10111
	0b000,		// 0b11000
	0b100,		// 0b11001
	0b100,		// 0b11010
	0b000,		// 0b11011
	0b100,		// 0b11100
	0b000,		// 0b11101
	0b000,		// 0b11110
	0b100,		// 0b11111
};

#define _NOP() do { __asm__ __volatile__ ("nop"); } while (0) 

void swdSendPacket(swd_packet_t pckt)
{
	SWDIO_OUT();
	
	uint8_t out_val = (pckt.val & 0b11111011) | 0b10000010;

	out_val |= parity_calc[(out_val >> 3) & 0x0f];
	
	SWDCLK_LO();
	
	out_val & 0x80 ? SWDIO_HI() : SWDIO_LO();
	
	SWDCLK_HI();
	_NOP();_NOP();_NOP();_NOP();_NOP();
	SWDCLK_LO();

	out_val & 0x40 ? SWDIO_HI() : SWDIO_LO();
	
	SWDCLK_HI();
	_NOP();_NOP();_NOP();_NOP();_NOP();
	SWDCLK_LO();
	
	out_val & 0x20 ? SWDIO_HI() : SWDIO_LO();

	SWDCLK_HI();
	_NOP();_NOP();_NOP();_NOP();_NOP();
	SWDCLK_LO();
	
	out_val & 0x10 ? SWDIO_HI() : SWDIO_LO();

	SWDCLK_HI();
	_NOP();_NOP();_NOP();_NOP();_NOP();
	SWDCLK_LO();

	out_val & 0x08 ? SWDIO_HI() : SWDIO_LO();
	
	SWDCLK_HI();
	_NOP();_NOP();_NOP();_NOP();_NOP();
	SWDCLK_LO();
	
	out_val & 0x04 ? SWDIO_HI() : SWDIO_LO();

	SWDCLK_HI();
	_NOP();_NOP();_NOP();_NOP();_NOP();
	SWDCLK_LO();
	
	out_val & 0x02 ? SWDIO_HI() : SWDIO_LO();
	_NOP();_NOP();

	SWDCLK_HI();
	_NOP();_NOP();_NOP();_NOP();_NOP();
	SWDCLK_LO();

	SWDIO_PU_ON();	
	SWDIO_IN();		// park
	_NOP();_NOP();_NOP();
	
	SWDCLK_HI();
}

struct swd_operation_t
{
	swd_packet_t	packet;
	uint8_t			ack;
	uint32_t		data;
};

int main(void)
{
	SetBit(DDR(SWDCLK_PORT), SWDCLK_BIT);
	SetBit(DDR(SWDIO_PORT), SWDIO_BIT);

	while (1)
	{
		swdLineReset();
		_delay_ms(1);
		
		swd_packet_t pckt;
		pckt.bits.is_ap = 1;
		pckt.bits.is_read = 0;
		pckt.bits.reg_addr2 = 1;
		pckt.bits.reg_addr3 = 0;
		swdSendPacket(pckt);

		_delay_ms(10);
	}

	return 0;
}
*/

int main(void)
{
	init_hw();
	
	for (;;)
	{
		// poll the V-USB library
		usbPoll();

		// turn the USB LED on if we are configured
		if (usbConfiguration != 0)
			SetBit(PORT(LED_USB_PORT), LED_USB_BIT);
		else
			ClrBit(PORT(LED_USB_PORT), LED_USB_BIT);
		
		// handle the requests, and create responses
		progParsePoll();
	}
}
