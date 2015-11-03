#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include <string>
#include <memory>

#include "hiddev.h"
#include "flashmem.h"
#include "programmer.h"
#include "progress.h"
#include "utils.h"

#include "../firmware/bootloader/usbconfig.h"

#pragma pack(push, 2)

struct DeviceInfo
{
    uint16_t	pageSize;
	uint32_t	flashSize;
};

struct DeviceData
{
	uint8_t		address[3];
	uint8_t		flash[0x80];
	
	void SetAddr(const int addr)
	{
		address[0] = addr & 0xff;
		address[1] = (addr >> 8) & 0xff;
		address[2] = (addr >> 16) & 0xff;
	}
};

#pragma pack(pop)

void DoBootload(const std::string& HexForBootloader)
{
	HIDDevice bootloader;
	
	uint8_t raw_vendor_id[2] = {USB_CFG_VENDOR_ID};
	uint8_t raw_device_id[2] = {USB_CFG_DEVICE_ID};
	char vendor_name[] = {USB_CFG_VENDOR_NAME, 0};
	char device_name[] = {USB_CFG_DEVICE_NAME, 0};
	uint16_t* pvid = (uint16_t*)raw_vendor_id;
	uint16_t* pdid = (uint16_t*)raw_device_id;
	
	printf("\nOpening bootloader\n");
	
	// open the programmer
	if (!bootloader.Open(*pvid, vendor_name, *pdid, device_name))
		throw std::string("Unable to open programmer bootloader.");

	printf("Loading firmware from HEX file %s\n", HexForBootloader.c_str());
	FlashMemory mem(6 * 1024);
	mem.LoadHex(HexForBootloader);

	const int lastFlashByte = mem.GetFlashLastByte();
	printf("Firmware size %i bytes\n\n", lastFlashByte + 1);
	
	DeviceInfo devInfo;
	bootloader.GetReport((uint8_t*) &devInfo, sizeof devInfo, 1);

	if (devInfo.pageSize != 0x40  ||  devInfo.flashSize != 0x2000)
		throw std::string("Incorrect page of flash size. Page size equals " + int2str(devInfo.pageSize) + ", should be 64.");

	ProgressBar pb("Bootloading");
	
	DeviceData data;
	for (int addr = 0; addr <= lastFlashByte  &&  addr < mem.GetFlashSize(); addr += sizeof data.flash)
	{
		data.SetAddr(addr);
		memcpy(data.flash, mem.GetFlash() + addr, sizeof data.flash);
		
		bootloader.SetReport((const uint8_t*) &data, sizeof data, sizeof data, 2);

		pb.Refresh(addr / double(6*1024));
	}

	pb.Refresh(1);
	
	// leave boot loader
	bootloader.SetReport((const uint8_t*) &devInfo, sizeof devInfo, sizeof devInfo, 1);
	// Ignore errors here. If the device reboots before we poll the response,
	// this request fails.
	
	printf("\n\nnrfburner firmware updated successfully.");
}
