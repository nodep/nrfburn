/* Name: main.c
 * Project: AVR bootloader HID
 * Author: Christian Starkjohann
 * Creation Date: 2007-03-19
 * Tabsize: 4
 * Copyright: (c) 2007 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt)
 * This Revision: $Id$
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/boot.h>
#include <util/delay.h>

#include "usbdrv.h"
#include "avrutils.h"
#include "../hw_setup.h"

/* ------------------------------------------------------------------------ */

#define addr_t	uint16_t

addr_t	currentAddress;		// in bytes
uint8_t	offset;				// data already processed in current transfer
uint8_t	exitMainloop;

const PROGMEM char usbHidReportDescriptor[33] =
{
	0x06, 0x00, 0xff,		// USAGE_PAGE (Generic Desktop)
	0x09, 0x01,				// USAGE (Vendor Usage 1)
	0xa1, 0x01,				// COLLECTION (Application)
	0x15, 0x00,				//	LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,		//	LOGICAL_MAXIMUM (255)
	0x75, 0x08,				//	REPORT_SIZE (8)

	0x85, 0x01,				//	REPORT_ID (1)
	0x95, 0x06,				//	REPORT_COUNT (6)
	0x09, 0x00,				//	USAGE (Undefined)
	0xb2, 0x02, 0x01,		//	FEATURE (Data,Var,Abs,Buf)

	0x85, 0x02,				//	REPORT_ID (2)
	0x95, 0x83,				//	REPORT_COUNT (131)
	0x09, 0x00,				//	USAGE (Undefined)
	0xb2, 0x02, 0x01,		//	FEATURE (Data,Var,Abs,Buf)
	0xc0					// END_COLLECTION
};

void (*nullVector)(void) __attribute__((__noreturn__)) = 0;

void leaveBootloader(void)
{
	DDR(LED_PROG_PORT) = 0;
	//ClrBit(DDR(LED_PROG_PORT), LED_PROG_BIT);
	//ClrBit(DDR(LED1_PORT), LED1_BIT);
	//ClrBit(DDR(LED2_PORT), LED2_BIT);

	PORT(LED_PROG_PORT) = 0;
	//ClrBit(PORT(LED_PROG_PORT), LED_PROG_BIT);
	//ClrBit(PORT(LED1_PORT), LED1_BIT);
	//ClrBit(PORT(LED2_PORT), LED2_BIT);

	cli();
	boot_rww_enable();
	USB_INTR_ENABLE = 0;
	USB_INTR_CFG = 0;		// also reset config bits
	MCUCR = _B1(IVCE);		// enable change of interrupt vectors
	MCUCR = _B0(IVSEL);		// move interrupts to application flash section
	
	// We must go through a global function pointer variable instead of writing
	// ((void (*)(void))0)();
	// because the compiler optimizes a constant 0 to "rcall 0" which is not
	// handled correctly by the assembler.

	nullVector();
}

uint8_t usbFunctionSetup(uint8_t data[8])
{
	usbRequest_t* rq = (void*) data;
	static uint8_t replyBuffer[7] =
	{
		1,		// report ID
		SPM_PAGESIZE & 0xff,
		SPM_PAGESIZE >> 8,
		((long)FLASHEND + 1) & 0xff,
		(((long)FLASHEND + 1) >> 8) & 0xff,
		(((long)FLASHEND + 1) >> 16) & 0xff,
		(((long)FLASHEND + 1) >> 24) & 0xff
	};

	if (rq->bRequest == USBRQ_HID_SET_REPORT)
	{
		if (rq->wValue.bytes[0] == 2)
		{
			offset = 0;
			return USB_NO_MSG;
		} else {
			exitMainloop = 1;
		}
	} else if (rq->bRequest == USBRQ_HID_GET_REPORT) {
		usbMsgPtr = (usbMsgPtr_t)replyBuffer;
		return 7;
	}

	return 0;
}

uint8_t usbFunctionWrite(uint8_t *data, uint8_t len)
{
	union {
		addr_t		l;
		uint16_t	s[sizeof(addr_t)/2];
		uint8_t		c[sizeof(addr_t)];
	} address;
	uint8_t	isLast;

	address.l = currentAddress;
	if (offset == 0)
	{
		address.c[0] = data[1];
		address.c[1] = data[2];
		data += 4;
		len -= 4;
	}

	offset += len;
	isLast = offset & 0x80; // != 0 if last block received
	do {
		addr_t prevAddr;
#if SPM_PAGESIZE > 256
		uint16_t pageAddr;
#else
		uint8_t pageAddr;
#endif
		pageAddr = address.s[0] & (SPM_PAGESIZE - 1);
		if (pageAddr == 0)
		{
			// if page start: erase

			cli();
			boot_page_erase(address.l);	// erase page
			sei();
			boot_spm_busy_wait();		// wait until page is erased
		}
		cli();
		boot_page_fill(address.l, *(short *)data);
		sei();
		prevAddr = address.l;
		address.l += 2;
		data += 2;
		// write page when we cross page boundary
		pageAddr = address.s[0] & (SPM_PAGESIZE - 1);
		if (pageAddr == 0)
		{
			cli();
			boot_page_write(prevAddr);
			sei();
			boot_spm_busy_wait();
		}

		len -= 2;
	} while(len);

	currentAddress = address.l;

	return isLast;
}

void initForUsbConnectivity(void)
{
	usbInit();

	// enforce USB re-enumerate
	usbDeviceDisconnect();	// do this while interrupts are disabled
	_delay_ms(260);			// fake USB disconnect for > 250 ms
	usbDeviceConnect();

	sei();
}

inline uint8_t bootloaderCondition(void)
{
	return PIN(PROG_PORT) & _B1(PROG_BIT);
}

int main(void)
{
	_delay_ms(50);
	
	// jump to application if jumper is set
	if (bootloaderCondition())
	{
		// LEDs are output
		DDR(LED_USB_PORT) = _B1(LED_USB_BIT) | _B1(LED_PROG_BIT) | _B1(LED_ERR_BIT);

		MCUCR = _B1(IVCE);	// enable change of interrupt vectors
		MCUCR = _B1(IVSEL);	// move interrupts to boot flash section 

		initForUsbConnectivity();

		// main event loop
		uint16_t cntloop = 0;
		uint8_t i = 0, j = 0, led_cnt = 0;
		do {
			usbPoll();

			// do the LEDs
			if (--cntloop == 0)
			{
				if ((led_cnt & 1) == 0)
					PORT(LED_PROG_PORT) = _B1(LED_PROG_BIT);
				else if (led_cnt == 1)
					PORT(LED_USB_PORT) = _B1(LED_USB_BIT);
				else if (led_cnt == 3)
					PORT(LED_ERR_PORT) = _B1(LED_ERR_BIT);

				led_cnt = (led_cnt + 1) & 3;
			}
			
			if (exitMainloop)
			{
				if (--i == 0)
				{
					if (--j == 0)
						break;
				}
			}
			
		} while (bootloaderCondition());
	}

	leaveBootloader();
	
	return 0;
}
