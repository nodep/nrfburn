#pragma once

#include "prg_common.h"

// interface for the functions that read and parse the input stream from USB
// and execute the commands. this is inpired by AVR-Doper :)

// initializes the parser
void progParseInit(void);

// resets the request parser
void progParseResetRx(void);

// stores the byte received into the buffer and tries to parse it.
// it checks if the buffer has a valid message and sets reqComplete to true if it is
void progParseSetRxByte(uint8_t byte);

// executes the request if reqComplete is true
// it creates a response which can be read with progParseGetTxByte
void progParsePoll();

// returns the number of bytes to send if we have a response ready
int progParseGetTxCount(void);

// reads the next byte from the response buffer
int progParseGetTxByte(void);
