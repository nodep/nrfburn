#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#include "hw_setup.h"
#include "prg_common.h"
#include "avrutils.h"

// SPI commands
enum {
	WREN		= 0x06,
	WRDIS		= 0x04,
	RDSR		= 0x05,
	WRSR		= 0x01,
	READ		= 0x03,
	PROGRAM		= 0x02,
	ERASE_PAGE	= 0x52,
	ERASE_ALL	= 0x62,
	RDFPCR		= 0x89,
	RDISIP		= 0x84,
	RDISMB		= 0x85,
	ENDEBUG		= 0x86,
};

static void ProgEnableSPI(void)
{
	// config SPI pins as outputs
	SetBit(DDR(MOSI_PORT), MOSI_BIT);
	SetBit(DDR(SCK_PORT), SCK_BIT);
	SetBit(DDR(CSN_PORT), CSN_BIT);

	// MISO is input
	ClrBit(DDR(MISO_PORT), MISO_BIT);
	SetBit(PORT(MISO_PORT), MISO_BIT);	// pullup

	// CSN has to be inactive - meaning hi
	SetBit(PORT(CSN_PORT), CSN_BIT);

	// enable SPI in Master Mode with SCK = F_CPU/16 = 750KHz
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0);

	SPSR;	// clear SPIF bit in SPSR
	SPDR;
}

static void ProgDisableSPI(void)
{
	SPCR = 0;	// disable SPI
	
	// config the SPI pins to input and disable the pullup - leave everything floating
	ClrBit(PORT(MOSI_PORT), MOSI_BIT);		// MOSI
	ClrBit(DDR(MOSI_PORT), MOSI_BIT);
	
	ClrBit(PORT(SCK_PORT), SCK_BIT);		// SCK
	ClrBit(DDR(SCK_PORT), SCK_BIT);
	
	ClrBit(PORT(CSN_PORT), CSN_BIT);		// CSN
	ClrBit(DDR(CSN_PORT), CSN_BIT);

	ClrBit(DDR(MISO_PORT), MISO_BIT);		// MISO
	ClrBit(PORT(MISO_PORT), MISO_BIT);
}

void ProgSpiResetTarget(void)
{
	ClrBit(PORT(TGT_RST_PORT), TGT_RST_BIT);
	_delay_ms(10);
	SetBit(PORT(TGT_RST_PORT), TGT_RST_BIT);
}

// setup the programming interface pins
void ProgSpiInit(void)
{
	// drive the PROG pin low
	ClrBit(PORT(PROG_PORT), PROG_BIT);
	SetBit(DDR(PROG_PORT), PROG_BIT);
	
	// drive the TGT_RST pin high
	SetBit(PORT(TGT_RST_PORT), TGT_RST_BIT);
	SetBit(DDR(TGT_RST_PORT), TGT_RST_BIT);

	ProgDisableSPI();
}

void ProgSpiBegin(void)
{
	// check if we are already in programming mode
	if (bit_is_set(PORT(LED_PROG_PORT), LED_PROG_BIT))
		return;

	// turn on the programming indicator LED
	SetBit(PORT(LED_PROG_PORT), LED_PROG_BIT);

	ProgEnableSPI();
	
	ProgSpiResetTarget();

	// PROG goes high - enable programming
	SetBit(PORT(PROG_PORT), PROG_BIT);
	
	_delay_ms(2);	// wait 2ms
}

void ProgSpiEnd(void)
{
	// check if we are already in programming mode
	if (bit_is_clear(PORT(LED_PROG_PORT), LED_PROG_BIT))
		return;

	// turn off the programming indicator LED
	ClrBit(PORT(LED_PROG_PORT), LED_PROG_BIT);

	// PROG driven low
	ClrBit(PORT(PROG_PORT), PROG_BIT);
	
	ProgDisableSPI();

	ProgSpiResetTarget();
}

static void ProgSpiShiftCommand(uint8_t* pCommand, uint8_t num_bytes)
{
	// start command - CSN goes low
	ClrBit(PORT(CSN_PORT), CSN_BIT);

	while (num_bytes > 0)
	{
		// set character to send the nRF through MOSI
		SPDR = *pCommand;

		// wait until char is sent
		loop_until_bit_is_set(SPSR, SPIF);

		// remember the byte received from nRF through MISO
		*pCommand = SPDR;

		++pCommand;
		--num_bytes;
	}

	// end the command - CSN goes hi
	SetBit(PORT(CSN_PORT), CSN_BIT);
}

static void ProgSimpleCommand(uint8_t command)
{
	// start command - CSN goes low
	ClrBit(PORT(CSN_PORT), CSN_BIT);

	// set character to send the nRF through MOSI
	SPDR = command;

	// wait until char is sent
	loop_until_bit_is_set(SPSR, SPIF);

	// end the command - CSN goes hi
	SetBit(PORT(CSN_PORT), CSN_BIT);
}

static uint8_t ProgShiftByte(const uint8_t b)
{
	// set the byte to send the nRF through MOSI
	SPDR = b;

	// wait until char is sent
	loop_until_bit_is_set(SPSR, SPIF);

	// return the byte received from nRF through MISO
	return SPDR;
}

// write enable - datasheet 17.7.1.1
void ProgSpiWREN(void)
{
	ProgSimpleCommand(WREN);
}

// write disable - datasheet 17.7.1.1
void ProgSpiWRDIS(void)
{
	ProgSimpleCommand(WRDIS);
}

// read the contents of the flash status (FSR) - datasheet 17.7.1.2
uint8_t ProgSpiRDSR(void)
{
	uint8_t cmd[2];
	cmd[0] = RDSR;
	cmd[1] = 0x00;	// dummy
	ProgSpiShiftCommand(cmd, sizeof cmd);
	
	return cmd[1];
}

// write flash status register (FSR) - datasheet 17.7.1.3
// Only bits 5 and 3 (WEN and INFEN) are writable by this command
void ProgSpiWRSR(const uint8_t fsr_val)
{
	uint8_t cmd[2];
	cmd[0] = WRSR;
	cmd[1] = fsr_val;
	ProgSpiShiftCommand(cmd, sizeof cmd);
}

// reads PROG_CHUNK_SIZE bytes of flash memory, starting from the given address - datasheet 17.7.1.4
void ProgSpiREAD(const uint16_t addr, uint8_t* data)
{
	// start command - CSN goes low
	ClrBit(PORT(CSN_PORT), CSN_BIT);

	// send the command and the address
	ProgShiftByte(READ);
	ProgShiftByte(addr >> 8);
	ProgShiftByte(addr & 0xff);

	// read the data
	uint16_t cnt = PROG_CHUNK_SIZE;
	while (cnt--)
		*data++ = ProgShiftByte(0);
	
	// end the command - CSN goes hi
	SetBit(PORT(CSN_PORT), CSN_BIT);
}

// writes PROG_CHUNK_SIZE bytes of flash memory, starting from the given address - datasheet 17.7.1.5
void ProgSpiPROGRAM(const uint16_t addr, const uint8_t* data)
{
	// start command - CSN goes low
	ClrBit(PORT(CSN_PORT), CSN_BIT);

	// send the command and the address
	ProgShiftByte(PROGRAM);
	ProgShiftByte(addr >> 8);
	ProgShiftByte(addr & 0xff);

	// send the data
	uint16_t cnt = PROG_CHUNK_SIZE;
	while (cnt--)
		ProgShiftByte(*data++);
	
	// end the command - CSN goes hi
	SetBit(PORT(CSN_PORT), CSN_BIT);
}

// erases a page in MainBlock or the InfoPage - datasheet 17.7.1.6
void ProgSpiERASE_PAGE(const uint8_t page_num)
{
	uint8_t cmd[2];
	cmd[0] = ERASE_PAGE;
	cmd[1] = page_num;
	ProgSpiShiftCommand(cmd, sizeof cmd);
}

// erases all content of the flash MainBlock by setting it to 0xFF - datasheet 17.7.1.7
void ProgSpiERASE_ALL(void)
{
	ProgSimpleCommand(ERASE_ALL);
}

// read the contents of the flash project configuration register (FPCR) - datasheet 17.7.1.8
uint8_t ProgSpiRDFPCR(void)
{
	uint8_t cmd[2];
	cmd[0] = RDFPCR;
	cmd[1] = 0x00;
	ProgSpiShiftCommand(cmd, sizeof cmd);
	
	return cmd[1];
}

// disable InfoPage readback - datasheet 17.7.1.9
void ProgSpiRDISIP(void)
{
	ProgSimpleCommand(RDISIP);
}

// disable MainBlock readback - datasheet 17.7.1.10
void ProgSpiRDISMB(void)
{
	ProgSimpleCommand(RDISMB);
}

bool ProgSpiWaitForRDYN(uint8_t timeout_ms)
{
	do {
		if ((ProgSpiRDSR() & _BV(FSR_RDYN)) == 0)
			return true;

		if (timeout_ms)
			_delay_ms(1);

	} while (timeout_ms--);
	
	return false;
}
