#pragma once

// LEDs
#define LED_ERR_PORT	C
#define LED_ERR_BIT		1

#define LED_PROG_PORT	C
#define LED_PROG_BIT	2

#define LED_USB_PORT	C
#define LED_USB_BIT		3


// the nRF24LU1+ and nRF24LE1 programming interface
#define PROG_PORT		D
#define PROG_BIT		5

#define MOSI_PORT		B
#define MOSI_BIT		3

#define CSN_PORT		B
#define CSN_BIT			2

#define SCK_PORT		B
#define SCK_BIT			5

#define MISO_PORT		B
#define MISO_BIT		4

#define TGT_RST_PORT	C
#define TGT_RST_BIT		0


// the nRF51822 SWD interface (not yet implemented)
#define SWDCLK_PORT		B
#define SWDCLK_BIT		5

#define SWDIO_PORT		B
#define SWDIO_BIT		3

#define SWDCLK_HI()		SetBit(PORT(SWDCLK_PORT), SWDCLK_BIT)
#define SWDCLK_LO()		ClrBit(PORT(SWDCLK_PORT), SWDCLK_BIT)

#define SWDIO_HI()		SetBit(PORT(SWDIO_PORT), SWDIO_BIT)
#define SWDIO_LO()		ClrBit(PORT(SWDIO_PORT), SWDIO_BIT)

#define SWDIO_OUT(pu)	SetBit(DDR(SWDIO_PORT), SWDIO_BIT); pu
#define SWDIO_IN(pu)	ClrBit(DDR(SWDIO_PORT), SWDIO_BIT); pu

#define SWDIO_PU_ON		SWDIO_HI
#define SWDIO_PU_OFF	SWDIO_LO
