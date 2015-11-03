#pragma once

// setup the programming interface (SPI + PROG) pins
void ProgSpiInit(void);

// drives PROG low and enables the SPI pins
void ProgSpiBegin(void);

// drives PROG high and disables the SPI pins
void ProgSpiEnd(void);

// reads FSR until FSR.RDYN is clear
bool ProgSpiWaitForRDYN(uint8_t timeout_ms);

// default timeouts - should be more than enough for a 16MHz CLK
#define ERASE_ALL_TIMEOUT		150
#define ERASE_PAGE_TIMEOUT		150
#define PROGRAM_CHUNK_TIMEOUT	50

// write enable/disable - datasheet 17.7.1.1
void ProgSpiWREN(void);
void ProgSpiWRDIS(void);

// read the contents of the flash status register (FSR) - datasheet 17.7.1.2
uint8_t ProgSpiRDSR(void);

// write flash status register (FSR) - datasheet 17.7.1.3
void ProgSpiWRSR(const uint8_t fsr_val);

// reads 256 bytes from flash - datasheet 17.7.1.4
void ProgSpiREAD(const uint16_t addr, uint8_t* data);

// writes 256 bytes from flash - datasheet 17.7.1.5
void ProgSpiPROGRAM(const uint16_t addr, const uint8_t* data);

// erases all content of the flash MainBlock memory to value 0xFF - datasheet 17.7.1.6
void ProgSpiERASE_PAGE(const uint8_t page_num);

// erases all content of the flash MainBlock memory to value 0xFF - datasheet 17.7.1.7
void ProgSpiERASE_ALL(void);

// read the contents of the flash project configuration register (FPCR) - datasheet 17.7.1.8
uint8_t ProgSpiRDFPCR(void);

// disable InfoPage readback - datasheet 17.7.1.9
void ProgSpiRDISIP(void);

// disable MainBlock readback - datasheet 17.7.1.10
void ProgSpiRDISMB(void);

// pulls low the target reset line for 10ms
void ProgSpiResetTarget(void);
