#pragma once

// handles the flash memory with loading and saving from/to HEX files
class FlashMemory
{
private:
	enum {
		MAX_HEX_FILE_SIZE	= 0x20000,	// 128kByte for the Intel HEX format file
		BYTES_PER_ROW		= 0x10,		// how bay data bytes per row in HEX output
	};

	static uint8_t GetHexByte(const char*& pHex, uint8_t& checksum);
	static std::string ByteToHex(const uint8_t b);
	static std::string WordToHex(const uint16_t b);

	const int				flashSize;
	std::auto_ptr<uint8_t>	flashBuffer;

public:
	explicit FlashMemory(const int fs);

	void LoadHex(const std::string& filename);
	void SaveHex(const std::string& filename) const;

	// set every byte in the buffer to 0xff
	void Clear();

	uint8_t* GetFlash()
	{
		return flashBuffer.get();
	}
	
	const uint8_t* GetFlash() const
	{
		return flashBuffer.get();
	}
	
	int GetFlashSize() const
	{
		return flashSize;
	}

	int GetFlashLastByte() const;
	
	// compare flashes - used for verification
	const bool operator == (const FlashMemory& lhs) const;
	const bool operator != (const FlashMemory& lhs) const
	{
		return !(operator == (lhs));
	}
};
