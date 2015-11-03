#include <string.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
	
#include "usbdrv.h"
#include "hw_setup.h"
#include "avrutils.h"
#include "avrdbg.h"
#include "prg_parse.h"

// We are defining feature HID reports which, unlike input/outputs reports can travel in both directions:
// host to device and device to host. Feature reports are sent using control transfers and that means
// that the bandwidth is not limited by the 800 bytes/second limitation of the low speed interrupt
// endpoints. It also means that we are not actually using the interrupt in endpoint 1.

// USB report descriptor
PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] =
{
	0x06, 0x00, 0xff,			// USAGE_PAGE (Vendor Defined Page 1)
	0x09, 0x01,					// USAGE (Vendor Usage 1)
	0xa1, 0x01,					// COLLECTION (Application)
	0x15, 0x00,					//	LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,			//	LOGICAL_MAXIMUM (255)
	0x75, 0x08,					//	REPORT_SIZE (8)

	0x85, HIDREP_FIRST_ID,		//	REPORT_ID
	0x95, HIDREP_FIRST_BYTES,	//	REPORT_COUNT
	0x09, 0x00,					//	USAGE (Undefined)
	0xb2, 0x02, 0x01,			//	FEATURE (Data,Var,Abs,Buf)

	0x85, HIDREP_SECOND_ID,		//	REPORT_ID
	0x95, HIDREP_SECOND_BYTES,	//	REPORT_COUNT
	0x09, 0x00,					//	USAGE (Undefined)
	0xb2, 0x02, 0x01,			//	FEATURE (Data,Var,Abs,Buf)

	0xc0						// END_COLLECTION
};

uint8_t bytesRemaining;		// number of bytes to send/read
uint8_t reportId;			// the HID report ID we're working on
bool isFirstPacket;			// if this is true it means the first byte of the packet is the reportID

// usbFunctionRead() is called when the host requests a chunk of data from the device.
uint8_t usbFunctionRead(uint8_t* data, uint8_t len)
{
	// first clear the buffer
	memset(data, 0, len);
	
	// do we have something to send?
	uint8_t bytes2send = progParseGetTxCount();
	if (bytes2send)
	{
		// number of bytes available in this packet minus the reportID
		uint8_t avail2send = isFirstPacket ? len - 1 : len;

		if (bytes2send > avail2send)
			bytes2send = avail2send;

		if (isFirstPacket)
			*data++ = reportId;

		int c;
		for (c = 0; c < bytes2send; ++c)
			data[c] = (uint8_t) progParseGetTxByte();

	} else {
		// set the report ID
		if (isFirstPacket)
			data[0] = reportId;
	}

	isFirstPacket = false;
	
	return len;
}

// usbFunctionWrite() is called when the host sends a chunk of data to the device.
uint8_t usbFunctionWrite(uint8_t* data, uint8_t len)
{
	bytesRemaining -= len;

	if (isFirstPacket)
	{
		*data++ = reportId;
		--len;
	}

	for (; len; len--)
	{
		uint8_t c = *data++;
		progParseSetRxByte(c);
	}

	isFirstPacket = false;
	
	return bytesRemaining == 0;		// return 1 if this was the last chunk
}

usbMsgLen_t usbFunctionSetup(uint8_t data[8])
{
	usbRequest_t* rq = (void*) data;

	if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS)	// HID class request
	{
		if (rq->bRequest == USBRQ_HID_GET_REPORT
				||  rq->bRequest == USBRQ_HID_SET_REPORT)
		{
			isFirstPacket = true;
			reportId = rq->wValue.bytes[0];

			if (reportId == HIDREP_FIRST_ID)
			{
				bytesRemaining = HIDREP_FIRST_BYTES + 1;
				
				// reset the RX buffer on first report
				if (rq->bRequest == USBRQ_HID_SET_REPORT)
					progParseResetRx();
			} else {
				bytesRemaining = HIDREP_SECOND_BYTES + 1;
			}
				
			return USB_NO_MSG;
		}
	}
	
	return 0;
}
