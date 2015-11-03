#pragma once

// this file is included by the both the firmware and host program

// the protocol in brief:

// request: host to programmer

// field name  | bytes  | comment
// ------------+--------+---------
// length      | 2      |
// request     | 1      | enum request_codes
// page_num    | 0 or 2 | optional - used only for erase page request
// address     | 0 or 2 | optional - used only for read and write flash request
// data        | 0-256  | optional - payload for the write request
// checksum    | 1      |

// response: programmer to host

// field name  | bytes  | comment
// ------------+--------+---------
// length      | 2      |
// response    | 1      | enum reponse_codes
// data        | 0-256  | optional - only for read response
// fsr         | 0 or 1 | optional - only for read fsr & fpcr response
// fpcr        | 0 or 1 | optional - only for read fsr & fpcr response
// ver_major   | 0 or 1 | optional - only for version response
// ver_minor   | 0 or 1 | optional - only for version response
// checksum    | 1      |


#define PRG_VER_MAJOR	0x00
#define PRG_VER_MINOR	0x01

enum request_code_e
{
	reqVersion			= 0x01,
	reqProgBegin		= 0x02,
	reqProgEnd			= 0x03,
	reqReadFsrFpcr		= 0x04,
	reqWriteMainBlock	= 0x05,
	reqWriteInfoPage	= 0x06,
	reqReadMainBlock	= 0x07,
	reqReadInfoPage		= 0x08,
	reqErasePageMB		= 0x09,
	reqErasePageIP		= 0x0A,
	reqEraseAll			= 0x0B,
	reqDisReadMainBlock	= 0x0C,
	reqDisReadInfoPage	= 0x0D,
	reqResetTarget		= 0x0E,
};

enum response_code_e
{
	respError = 0x80,
	
	// the other response codes are equal to the request code
	// with the highest bit set. for instance:
	// respWriteInfoPage == reqWriteInfoPage | 0x80
};

enum response_error_codes_e
{
	respErrBadChecksum		= 0x00,
	respErrTimeoutExpired	= 0x01,
	respErrUnknownRequest	= 0x02,
};

// number of bytes to write or read in one chunk
#define PROG_CHUNK_SIZE	128

#pragma pack(push)
#pragma pack(1)

// **************************
// requests
// **************************

// used for requests without parameters and for reading
// the length and request code of incoming requests
typedef struct {
	uint8_t		length;
	uint8_t		request;
	uint8_t		checksum;
} req_simple_t;

// reads both MainBlock and InfoPage
typedef struct {
	uint8_t		length;
	uint8_t		request;
	uint16_t	address;
	uint8_t		checksum;
} req_read_flash_t;

// writes both MainBlock and InfoPage
typedef struct {
	uint8_t		length;
	uint8_t		request;
	uint16_t	address;
	uint8_t		data[PROG_CHUNK_SIZE];
	uint8_t		checksum;
} req_write_flash_t;

// erase page for both MainBlock and InfoPage
typedef struct {
	uint8_t		length;
	uint8_t		request;
	uint8_t		page_num;
	uint8_t		checksum;
} req_erase_page_t;

// **************************
// responses
// **************************

// common response structure for all responses without data
typedef struct {
	uint8_t		length;
	uint8_t		response;
	uint8_t		checksum;
} resp_simple_t;

typedef struct {
	uint8_t		length;
	uint8_t		response;
	uint8_t		ver_major;
	uint8_t		ver_minor;
	uint8_t		checksum;
} resp_version_t;

typedef struct {
	uint8_t		length;
	uint8_t		response;
	uint8_t		data[PROG_CHUNK_SIZE];
	uint8_t		checksum;
} resp_read_flash_t;

typedef struct {
	uint8_t		length;
	uint8_t		response;
	uint8_t		fsr;
	uint8_t		fpcr;
	uint8_t		checksum;
} resp_read_fsr_fpcr_t;

typedef struct {
	uint8_t		length;
	uint8_t		response;
	uint8_t		error_code;
	uint8_t		checksum;
} resp_error_t;

#pragma pack(pop)

// max buffer size
#define MAX_PROT_BUFF_SIZE		(sizeof(req_write_flash_t) > sizeof(resp_read_flash_t) ? sizeof(req_write_flash_t) : sizeof(resp_read_flash_t))

// bits of the FSR (Flash Status Register)
enum {
	FSR_DBG		= 7,
	FSR_STP		= 6,
	FSR_WEN		= 5,
	FSR_RDYN	= 4,
	FSR_INFEN	= 3,
	FSR_RDISMB	= 2,
	FSR_RDISIP	= 1,
};

// The HID report IDs
//
// The first HID report is large enough to contain all the structures shown above except
// the write request (133 bytes) and read response (131 bytes). These two structures need a
// subsequent second report to transfer all the data. In this case the data from the two reports
// is concatinated to form a request or response.

#define HIDREP_FIRST_ID			1
#define HIDREP_SECOND_ID		2

#define HIDREP_FIRST_BYTES		7
#define HIDREP_SECOND_BYTES		127
