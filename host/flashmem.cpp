#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <string>
#include <memory>

#include "flashmem.h"
#include "utils.h"

uint8_t FlashMemory::GetHexByte(const char*& pHex, uint8_t& checksum)
{
	char c1 = pHex[0];
	char c2 = pHex[1];
	if (!isxdigit(c1)  ||  !isxdigit(c2))
		throw std::string("Invalid HEX file. ") + pHex[0] + pHex[1] + " is not a hex digit.";

	uint8_t retVal;

	// more significant nibble
	if (isdigit(c1))
		retVal = c1 - '0';
	else
		retVal = 10 + (tolower(c1) - 'a');

	retVal <<= 4;

	// less significant nibble
	if (isdigit(c2))
		retVal |= c2 - '0';
	else
		retVal |= 10 + (tolower(c2) - 'a');

	pHex += 2;

	checksum += retVal;

	return retVal;
}

std::string FlashMemory::ByteToHex(const uint8_t b)
{
	char buff[3];
	snprintf(buff, sizeof buff, "%02X", b);
	return buff;
}

std::string FlashMemory::WordToHex(const uint16_t b)
{
	char buff[5];
	snprintf(buff, sizeof buff, "%04X", b);
	return buff;
}

FlashMemory::FlashMemory(const int fs)
: flashSize(fs)
{
	flashBuffer.reset(new uint8_t[flashSize]);

	Clear();
}

void FlashMemory::Clear()
{
	memset(flashBuffer.get(), 0xff, flashSize);
}

void FlashMemory::LoadHex(const std::string& filename)
{
	errno = 0;
	FILE* fhex = fopen(filename.c_str(), "rb");
	if (fhex == NULL)
		throw std::string("Unable to open HEX file. ") + strerror(errno);

	// get the file size
	fseek(fhex, 0, SEEK_END);
	long int file_size = ftell(fhex);
	if (file_size > MAX_HEX_FILE_SIZE)
	{
		fclose(fhex);
		throw std::string("HEX file too large. Max file size is " + int2str(MAX_HEX_FILE_SIZE) + "kByte");
	}

	// make a buffer large enough for the entire file
	std::auto_ptr<char> fbuff(new char[file_size + 1]);

	// load the entire hex file in one chunk
	fseek(fhex, 0, SEEK_SET);
	int bytes_read = fread(fbuff.get(), 1, file_size, fhex);

	fclose(fhex);

	if (bytes_read != file_size)
		throw std::string("Unable to read HEX file.");

	fbuff.get()[bytes_read] = '\0';

	// reset before loading
	Clear();

	bool eof_reached = false;
	const char* pHex = fbuff.get();
	uint8_t* pFlash = flashBuffer.get();
	int line_num = 0;
	do {
		// check the colon
		uint8_t checksum = 0;

		++line_num;
		
		if (*pHex++ != ':')
			throw std::string("Invalid HEX file. Line " + int2str(line_num) + " not starting with :");

		uint8_t num_data_bytes = GetHexByte(pHex, checksum);
		uint16_t address = (uint16_t(GetHexByte(pHex, checksum)) << 8) | GetHexByte(pHex, checksum);

		uint8_t record_type = GetHexByte(pHex, checksum);

		if (record_type == 0)	// data record
		{
			if (address + num_data_bytes > flashSize)
				throw std::string("Invalid HEX file. Address points outside flash memory. " + int2hex(address + num_data_bytes) + " of " + int2hex(flashSize));

			while (num_data_bytes--)
				pFlash[address++] = GetHexByte(pHex, checksum);
		} else if (record_type != 1) {	// not eof record
			throw std::string("Invalid HEX file. Unknown record type " + int2str(record_type) + " in line " + int2str(line_num));
		}

		checksum = ~checksum + 1;

		uint8_t dummy;
		uint8_t checksum_file = GetHexByte(pHex, dummy);

		if (checksum_file != checksum)
			throw std::string("Invalid HEX file. Bad checksum.");

		if (record_type > 1)
			throw std::string("Invalid HEX file. Unsupported record type.");

		// EOF?
		eof_reached = record_type == 1;

		while (isspace(*pHex))
			pHex++;

	} while (!eof_reached  &&  *pHex);

	if (!eof_reached)
		throw std::string("Invalid HEX file. End-of-file record not found.");
}

void FlashMemory::SaveHex(const std::string& filename) const
{
	std::string hex;

	int address = 0;
	const uint8_t* pFlash = flashBuffer.get();
	while (address < flashSize)
	{
		int rec_bytes = flashSize - address;
		if (rec_bytes > BYTES_PER_ROW)
			rec_bytes = BYTES_PER_ROW;

		// find the last non-0xff
		int c, non_empty_bytes = 0;
		for (c = 0; c < BYTES_PER_ROW; ++c)
		{
			if (pFlash[address + c] != 0xff)
				non_empty_bytes = c + 1;
		}

		// output the line if we have non-0xff data bytes
		if (non_empty_bytes)
		{
			// make the line
			hex += ":" + ByteToHex(non_empty_bytes);
			hex += WordToHex(address);
			hex += "00";	// record type

			uint8_t checksum = non_empty_bytes + (address & 0xff) + (address >> 8);
			for (c = 0; c < non_empty_bytes; c++)
			{
				checksum += pFlash[address + c];
				hex += ByteToHex(pFlash[address + c]);
			}

			checksum = ~checksum + 1;

			hex += ByteToHex(checksum);
			hex += '\n';
		}

		address += rec_bytes;
	}

	// add EOF
	hex += ":00000001FF\n";

	// now save everything in one go
	errno = 0;
	FILE* fhex = fopen(filename.c_str(), "wb");
	if (fhex == NULL)
		throw std::string("Unable to open ") + filename + "  " + strerror(errno);

	errno = 0;
	size_t written = fwrite(hex.c_str(), 1, hex.length(), fhex);
	if (written != hex.length())
	{
		int e = errno;
		fclose(fhex);
		throw std::string("Unable to write HEX file ") + filename + "  " + strerror(e);
	}

	fclose(fhex);
}

int FlashMemory::GetFlashLastByte() const
{
	const uint8_t* pBuff = flashBuffer.get();
	int cnt;
	for (cnt = GetFlashSize() - 1; cnt > 0; --cnt)
	{
		if (pBuff[cnt] != 0xff)
			return cnt;
	}
	
	return 0;
}

// compare flashes - used for verification
const bool FlashMemory::operator == (const FlashMemory& lhs) const
{
	if (flashSize != lhs.flashSize)
		return false;
	
	return memcmp(flashBuffer.get(), lhs.flashBuffer.get(), flashSize) == 0;
}
