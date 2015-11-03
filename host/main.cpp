#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <string>
#include <memory>

#include "programmer.h"
#include "flashmem.h"
#include "utils.h"
#include "bootloader.h"

void PrintVer()
{
	puts("nrfburn v0.1  build " __DATE__ " " __TIME__);
}

void PrintHelp()
{
	PrintVer();
	puts("Usage: nrfburn [options]");	puts("Options:");	puts("  -f 16|32       Specify flash size in kilobytes. Only 16 or 32 are valid.");	puts("  -w <filename>  Write contents of HEX file to nRF target MainBlock flash.");	puts("                 Automatically performs a chip erase before programming.");	puts("                 Runs a verification pass after writing is complete.");	puts("  -v <filename>  Verify nRF target MainBlock with contents of HEX file.");	puts("  -r <filename>  Read nRF target MainBlock into HEX file.");	puts("  -p <filename>  Read nRF target InfoPage into HEX file.");	puts("  -e             Perform a chip erase. This erases only the MainBlock, ");	puts("                 and leaves the InfoPage intact.");	puts("  -i <chipID>    Erase the InfoPage and write the specified chip ID.");	puts("                 This also performs a chip erase. chipID must be in the");	puts("                 the format xx-xx-xx-xx-xx where x is a hex digit.");	puts("                 WARNING!");
	puts("                 Don't do this unless you know exactly what you're doing!");
	puts("                 Erasing the InfoPage on a nRF24LE1 will erase the chip's");
	puts("                 calibration information which you do not want.");
	puts("  -d mb|ip       Disable SPI reading of MainBlock or InfoPage.");
	puts("  -s             Reset the target nRF chip.");
	puts("  -b <filename>  Update programmer firmware from HEX.");
	puts("");
}

struct Options
{
	std::string		WriteMBFrom;	// HEX -> MainBlock
	std::string		ReadMBInto;		// MainBlock -> HEX
	std::string		VerifyMBWith;	// HEX with MainBlock
	std::string		ReadIPInto;		// InfoPage -> HEX
	uint8_t			ChipID[CHIP_ID_BYTES];
	uint8_t			ChipID_len;
	int				DisableReadback;
	int				FlashSize;
	bool			EraseAll;
	bool			ResetTarget;
	std::string		HexForBootloader;	// HEX to send to programmer bootloader

	Options()
		: ChipID_len(0), DisableReadback(DISABLE_NONE), FlashSize(0), EraseAll(false), ResetTarget(false)
	{}

	void ParseArgs(const int argc, const char* argv[]);
};

void Options::ParseArgs(const int argc, const char* argv[])
{
	int c = 1;
	while (c < argc)
	{
		if (argv[c] == NULL  ||  *argv[c] != '-'  ||  strlen(argv[c]) < 2)
			throw std::string("Invalid argument.");

		switch (argv[c][1])
		{
		case 'w':
			++c;

			if (c < argc)
				WriteMBFrom = argv[c];
			else
				throw std::string("Invalid HEX file name.");

			break;
		case 'r':
			++c;

			if (c < argc)
				ReadMBInto = argv[c];
			else
				throw std::string("Invalid HEX file name.");

			break;
		case 'p':
			++c;

			if (c < argc)
				ReadIPInto = argv[c];
			else
				throw std::string("Invalid HEX file name.");

			break;
		case 'e':
			EraseAll = true;
			break;
		case 'f':
			++c;

			FlashSize = 0;
			
			if (c < argc)
			{
				if (strcmp(argv[c], "16") == 0)
					FlashSize = 16*1024;
				else if (strcmp(argv[c], "32") == 0)
					FlashSize = 32*1024;
			}
			
			if (FlashSize == 0)
				throw std::string("Invalid flash size. Only 16 or 32 are valid.");
			
			break;
		case 'i':
			++c;

			if (c < argc)
			{
				const char* pEnd = argv[c];
				ChipID_len = 0;
				while (*pEnd)
				{
					long int res = strtol(pEnd, (char**) &pEnd, 16);
					if (res < 0  ||  res > 0xff  ||  (*pEnd != '\0'  &&  *pEnd != '-'))
						throw std::string("Incorrect ChipID format.");

					ChipID[ChipID_len++] = uint8_t(res);
					
					if (*pEnd)	// skip the dash
						pEnd++;
				}
				
				if (ChipID_len != CHIP_ID_BYTES)
					throw std::string("Incorrect ChipID length.");
				
			} else {
				throw std::string("ChipID not specified.");
			}

			break;
		case 'v':
			++c;

			if (c < argc)
				VerifyMBWith = argv[c];
			else
				throw std::string("Invalid HEX file name.");
				
			break;
			
		case 'd':
			++c;
			
			DisableReadback = DISABLE_NONE;
			
			if (c < argc)
			{
				if (strcasecmp(argv[c], "mb") == 0)
					DisableReadback = DISABLE_MB;
				else if (strcasecmp(argv[c], "ip") == 0)
					DisableReadback = DISABLE_IP;
			}

			if (DisableReadback == DISABLE_NONE)
				throw std::string("Invalid -d argument. Only mb or ip are allowed.");
			
			break;
			
		case 's':
			ResetTarget = true;
			break;
			
		case 'b':
			++c;

			if (c < argc)
				HexForBootloader = argv[c];
			else
				throw std::string("Invalid HEX file name.");

			break;
			
		default:
			throw std::string("Invalid command line option: -") + argv[c][1];
			break;
		}

		++c;
	}
	
	//
	// validate the args
	//

	if ((!WriteMBFrom.empty()  ||  !ReadMBInto.empty() ||  !VerifyMBWith.empty())  &&  FlashSize == 0)
		throw std::string("Flash size not specified");
	
	int cnt = 0;
	
	cnt += WriteMBFrom.empty() ? 0 : 1;
	cnt += ReadMBInto.empty() ? 0 : 1;
	cnt += VerifyMBWith.empty() ? 0 : 1;
	cnt += ReadIPInto.empty() ? 0 : 1;
	cnt += ChipID_len ? 1 : 0;
	cnt += EraseAll ? 1 : 0;
	cnt += ResetTarget ? 1 : 0;
	cnt += DisableReadback != DISABLE_NONE ? 1 : 0;
	cnt += HexForBootloader.empty() ? 0 : 1;
	
	if (cnt > 1)
		throw std::string("Mutually exclusive options selected.");
}

std::string int2str(const int i)
{
	char buff[32];
	snprintf(buff, sizeof buff, "%d", i);
	return buff;
}

std::string int2hex(const unsigned short i)
{
	char buff[32];
	snprintf(buff, sizeof buff, "0x%04x", i);
	return buff;
}

void DoProg(const Options& opt)
{
	// open the programmer
	Programmer prg(opt.FlashSize);

	printf("\nOpening programmer\n");
	prg.Open();
	
	// just reset the target and return
	if (opt.ResetTarget)
	{
		puts("");
		prg.ResetTarget();
		puts("\nTarget has been reset.");
		return;
	}	
	
	puts("Reading Flash registers");
	prg.BeginProgramming();
	
	// print the FSR and FPCR
	printf("\nnRF device flash registers:\n");
	printf("FPCR = 0x%02x\n", prg.GetFPCR());
	printf("FSR  = 0x%02x    DBG=%i  STP=%i  RDISMB=%i  RDISIP=%i\n",
					prg.GetFSR(),
					prg.GetFSR() & (1<<FSR_DBG) ? 1 : 0,
					prg.GetFSR() & (1<<FSR_STP) ? 1 : 0,
					prg.GetFSR() & (1<<FSR_RDISMB) ? 1 : 0,
					prg.GetFSR() & (1<<FSR_RDISIP) ? 1 : 0);

	printf("\nMainBlock readback %s\nInfoPage readback %s\n\n",
					prg.CanReadMainBlock() ? "enabled" : "disabled",
					prg.CanReadInfoPage() ? "enabled" : "disabled");

	// check if the target nRF device is present.
	// if the nRF is not present, we will read the FSR register as 0xff.
	// 0xff is not a valid value on a powered nRF, because bit 0 is always
	// read as 0.
	if (!prg.IsTargetPresent())
		throw std::string("FSR == 0xff. Target device not found.");
	
	if (opt.EraseAll)
	{
		prg.EraseAll();
	} else if (!opt.WriteMBFrom.empty()) {
		prg.WriteMainBlock(opt.WriteMBFrom);
		prg.VerifyMainBlock(opt.WriteMBFrom, true);
		printf("\nMainBlock flash written from %s\n", opt.WriteMBFrom.c_str());
	} else if (!opt.ReadMBInto.empty()) {
		prg.ReadMainBlock(opt.ReadMBInto);
		printf("\nMainBlock contents saved into %s\n", opt.ReadMBInto.c_str());
	} else if (!opt.VerifyMBWith.empty()) {
		prg.VerifyMainBlock(opt.VerifyMBWith);
		printf("\nMainBlock flash verified with %s\n", opt.VerifyMBWith.c_str());
	} else if (!opt.ReadIPInto.empty()) {
		prg.ReadInfoPage(opt.ReadIPInto);
		printf("\nInfoPage contents saved into %s\n", opt.ReadIPInto.c_str());
	} else if (opt.DisableReadback != DISABLE_NONE) {
		prg.DisableReadback(opt.DisableReadback);
		printf("\nSPI readback of %s disabled.\n", opt.DisableReadback == DISABLE_MB ? "MainBlock" : "InfoPage");
	} else if (opt.ChipID_len) {
		prg.WriteInfoPage(opt.ChipID);
		printf("\nChipID %02x-%02x-%02x-%02x-%02x written.\n",	opt.ChipID[0],
																opt.ChipID[1],
																opt.ChipID[2],
																opt.ChipID[3],
																opt.ChipID[4]);
	}
}

int main(const int argc, const char* argv[])
{
	try {
		Options opt;
		if (argc == 1)
		{
			PrintHelp();
			return 1;
		}

		PrintVer();
		
		opt.ParseArgs(argc, argv);

		if (!opt.HexForBootloader.empty())
			DoBootload(opt.HexForBootloader);
		else
			DoProg(opt);

	} catch (std::string& e) {
		fprintf(stderr, "\nError: %s\n", e.c_str());
		return 1;
	}

	return 0;
}
