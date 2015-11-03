#pragma once

#include "hiddev.h"
#include "flashmem.h"
#include "../firmware/prg_common.h"


#define CHIP_ID_BYTES	5

#define DISABLE_NONE	0
#define DISABLE_MB		1
#define DISABLE_IP		2

class Programmer
{
private:
	HIDDevice	hidBurn;		// the programmer communication

	uint8_t		fsr;
	uint8_t		fpcr;
	int			flashSize;

	bool		needsProgEnd;
	
	void CheckProgrammerVer();
	void ReadFlashRegisters();

	void ProgBegin();
	void ProgEnd();

	void WriteChunk(const bool isInfoPage, const FlashMemory& flash, const int offset);
	void ReadChunk(const bool isInfoPage, FlashMemory& flash, const int offset);

	void ReadResponseRaw(uint8_t* buff, size_t buff_size);
	
	template <class Resp>
	void ReadResponse1(Resp& resp);

	template <class Resp1, class Resp2>
	size_t ReadResponse2(Resp1& resp1, Resp2& resp2);
	
	enum { InfoPageSize = 512 };
	
	void SendRequestRaw(const uint8_t* buffer, const int bytes);
	
	template <class T>
	void SendRequest(const T& request)
	{
		SendRequestRaw((const uint8_t*) &request, sizeof request);
	}
	
public:
	Programmer(const int fs)
	:	fsr(0), fpcr(0), flashSize(fs), needsProgEnd(false)
	{}

	~Programmer();

	// opens the programmer device, checks the programmer version,
	// starts the programming, reads the flash status registers
	void Open();
	void BeginProgramming();

	uint8_t GetFSR() const		{ return fsr; }
	uint8_t GetFPCR() const		{ return fpcr; }

	bool CanReadMainBlock() const	{ return (fsr & (1<<FSR_RDISMB)) == 0; }
	bool CanReadInfoPage() const	{ return (fsr & (1<<FSR_RDISIP)) == 0; }
	bool IsTargetPresent() const	{ return (fsr & 1) == 0; }

	void EraseAll();

	void ReadMainBlock(const std::string& hexfilename);
	void WriteMainBlock(const std::string& hexfilename);
	void VerifyMainBlock(const std::string& hexfilename, const bool ignoreCheck = false);

	void ReadInfoPage(const std::string& hexfilename);
	void WriteInfoPage(const uint8_t chipID[CHIP_ID_BYTES]);
	
	void DisableReadback(const int region);
	
	void ResetTarget();
};
