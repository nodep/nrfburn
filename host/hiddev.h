#pragma once

// Opaque data type representing the USB device. This can be a Windows handle
// or a libusb handle, depending on the backend implementation.
struct usbDevice_t;

class HIDDevice
{
private:
	usbDevice_t*	hHIDDev;
	
public:
	HIDDevice();
	~HIDDevice();

	bool Open(uint16_t vendor_id, const char* vendor_name, uint16_t device_id, const char* device_name);
	void Close();

	void GetReport(uint8_t* buffer, int report_size, uint8_t report_id);
	void SetReport(const uint8_t* buffer, int bytes, int report_size, uint8_t report_id);
};
