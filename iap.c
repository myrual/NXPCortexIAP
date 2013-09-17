#define IAP_C_INCOMPILE
#include "iap.h"
#include "chip.h"

static unsigned int command_param[5];
static unsigned int status_result[4];


static IAP iap_entry;

#if 0
IAP_RESULT_TYPE updateFlashWith(unsigned int dstAddress, unsigned int *srcAddress, unsigned int content_size)
{
    unsigned int sector_start, sector_end;
    unsigned int *ptr;

    ptr = (unsigned int *)dstAddress;
    sector_start = dstAddress/0x400;
    sector_end = sector_start + content_size/0x400;
    return CMD_SUCCESS;
}
#endif

IAP_RESULT_TYPE iap_erasePage(unsigned int start_page, unsigned int end_page)
{
    command_param[0] = IAP_COMMANDID_ERASE_PAGE;
    command_param[1] = start_page;
    command_param[2] = end_page;
    command_param[3] = SystemCoreClock/1000;//thanks for http://www.lpcware.com/content/blog/application-programming-iap-code-example
    iap_entry=(IAP) IAP_LOCATION;
    iap_entry(command_param, status_result);
    var_iapResultStatus = (IAP_RESULT_TYPE)status_result[0];
    return var_iapResultStatus;
}

IAP_RESULT_TYPE iap_eraseSector(unsigned int start_sector, unsigned int end_sector)
{
    command_param[0] = IAP_COMMANDID_ERASE_SECTOR;
    command_param[1] = start_sector;
    command_param[2] = end_sector;
    command_param[3] = SystemCoreClock/1000;//thanks for http://www.lpcware.com/content/blog/application-programming-iap-code-example
    iap_entry=(IAP) IAP_LOCATION;
    iap_entry(command_param, status_result);
    var_iapResultStatus = (IAP_RESULT_TYPE)status_result[0];
    return var_iapResultStatus;
}

IAP_RESULT_TYPE iap_prepareWrite(unsigned int start_sector, unsigned int end_sector)
{
    command_param[0] = IAP_COMMANDID_PREPARE_WRITE;
    command_param[1] = start_sector;
    command_param[2] = end_sector;
    iap_entry=(IAP) IAP_LOCATION;
    iap_entry(command_param, status_result);
    var_iapResultStatus = (IAP_RESULT_TYPE)status_result[0];
    return var_iapResultStatus;
}




IAP_RESULT_TYPE iap_update2Flash(unsigned int dstAddress, unsigned int srcAddress, unsigned int content_size, unsigned int sys_clock_divide)
{
    if(content_size == 64 || content_size == 128 || content_size == 256 || content_size == 512 || content_size == 1024) {
        //based on UM10601_LPC800_UserManual, 22.5.2.2, content size must be 64,128,256,512,1024
        command_param[0] = IAP_COMMANDID_UPDATE_2FLASH;
        command_param[1] = dstAddress;
        command_param[2] = srcAddress;

        command_param[3] = content_size;
        command_param[4] = SystemCoreClock/sys_clock_divide;//thanks for http://www.lpcware.com/content/blog/application-programming-iap-code-example

        iap_entry=(IAP) IAP_LOCATION;
        status_result[0] = status_result[1] = status_result[2] = 0x00;
        iap_entry(command_param, status_result);
        var_iapResultStatus = (IAP_RESULT_TYPE)(status_result[0]);
    } else {
        var_iapResultStatus = COUNT_ERROR;
    }
    return var_iapResultStatus;
}

IAP_RESULT_TYPE iap_readUUID(unsigned int *resultPtr)
{
    unsigned char i;
    command_param[0] = IAP_COMMANDID_READ_UUID;
    iap_entry=(IAP) IAP_LOCATION;
    iap_entry(command_param, status_result);
    var_iapResultStatus = (IAP_RESULT_TYPE)status_result[0];
    for(i = 0; i < 4; i++) {
        resultPtr[i] = status_result[i];
    }
    return var_iapResultStatus;
}

IAP_RESULT_TYPE iap_readPARTID(unsigned int *resultPtr)
{
    unsigned char i;
    command_param[0] = IAP_COMMANDID_READ_PARTID;
    iap_entry=(IAP) IAP_LOCATION;
    iap_entry(command_param, status_result);
    var_iapResultStatus = (IAP_RESULT_TYPE)status_result[0];
    for(i = 0; i < 4; i++) {
        resultPtr[i] = status_result[i];
    }
    return var_iapResultStatus;

}

IAP_RESULT_TYPE iap_readBOOTCode(unsigned int *resultPtr)
{
    unsigned char i;
    command_param[0] = IAP_COMMANDID_READ_BOOTCODE;
    iap_entry=(IAP) IAP_LOCATION;
    iap_entry(command_param, status_result);
    var_iapResultStatus = (IAP_RESULT_TYPE)status_result[0];
    for(i = 0; i < 4; i++) {
        resultPtr[i] = status_result[i];
    }
    return var_iapResultStatus;

}
#undef IAP_C_INCOMPILE
