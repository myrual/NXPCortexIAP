#ifndef GUARD_IAP_H
#define GUARD_IAP_H
#ifdef IAP_C_INCOMPILE
#define EXTERN_HEADER_PREFIX  
#else
#define EXTERN_HEADER_PREFIX extern
#endif

#define IAP_LOCATION 0x1fff1ff1
#define IAP_COMMANDID_READ_UUID 58
#define IAP_COMMANDID_PREPARE_WRITE 50
#define IAP_COMMANDID_UPDATE_2FLASH 51
#define IAP_COMMANDID_READ_PARTID 54
#define IAP_COMMANDID_READ_BOOTCODE 55

#define IAP_COMMANDID_ERASE_SECTOR 52
#define IAP_COMMANDID_ERASE_PAGE 59

#define IAP_COMMAND_DEFAULT_CLOCK_DIVIDER 1000



typedef enum {
	CMD_SUCCESS = 0,
	INVALID_COMMAND = 1,
	SRC_ADDR_ERROR = 2,
	DST_ADDR_ERROR = 3,
	SRC_ADDR_NOT_MAPPED = 4,
	DST_ADDR_NOT_MAPPED = 5,
	COUNT_ERROR = 6,
	INVALID_SECTOR = 7,
	SECTOR_NOT_BLANK = 8,
	SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION = 9,
	COMPARE_ERROR = 10,
	BUSY = 11
}IAP_RESULT_TYPE;

EXTERN_HEADER_PREFIX IAP_RESULT_TYPE var_iapResultStatus;

typedef void (*IAP)(unsigned int [],unsigned int[]); 

EXTERN_HEADER_PREFIX IAP_RESULT_TYPE iap_prepareWrite(unsigned int start_sector, unsigned int end_sector);
EXTERN_HEADER_PREFIX IAP_RESULT_TYPE iap_update2Flash(unsigned int dst_inFlash, unsigned int src_inRam, unsigned int content_size, unsigned int sys_clock_divide);
EXTERN_HEADER_PREFIX IAP_RESULT_TYPE iap_readUUID(unsigned int *resultPtr);
EXTERN_HEADER_PREFIX IAP_RESULT_TYPE iap_readPARTID(unsigned int *resultPtr);
EXTERN_HEADER_PREFIX IAP_RESULT_TYPE iap_erasePage(unsigned int start_page, unsigned int end_page);
EXTERN_HEADER_PREFIX IAP_RESULT_TYPE iap_eraseSector(unsigned int start_sector, unsigned int end_sector);

#undef EXTERN_HEADER_PREFIX
#endif
