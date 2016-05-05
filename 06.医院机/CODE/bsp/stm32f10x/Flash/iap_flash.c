


#include "includes.h"
//#include "iap_flash.h"

uint16_t Flash_Check_ERASE_Write(uint32_t iAddress, uint8_t*buf, uint16_t iNumByteToWrite)
{
    uint16_t tmp=0; 
    uint16_t tmpdata=0; 
    uint32_t tmpAddress = iAddress;
    //1 Check
    while ( tmp < iNumByteToWrite )
    {
        tmpdata = *(__IO uint8_t *)tmpAddress++;
        if (tmpdata != 0xFF)
        {
            tmp=0;
            break;
        }
        tmp++;
    }

    if (tmp == 0)
    {
    //2 ERASE
        FLASH_Unlock(); //  Unlock the Flash Bank1 ProgramErase controller 
        FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
        FLASH_ErasePage(iAddress);//²Á³ýÕû¸öÉÈÇø
        FLASH_Lock(); // Locks the FLASH Program Erase Controller
    }
    //3 Write
    tmp=Flash_Write_Without_check(iAddress,buf,iNumByteToWrite);
    return tmp;
}


uint16_t Flash_Write_Without_check(uint32_t iAddress, uint8_t*buf, uint16_t iNumByteToWrite)
{
    uint16_t tmp = 0;
    volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
    FLASH_Unlock(); //  Unlock the Flash Bank1 ProgramErase controller 
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

    while ( ( tmp < iNumByteToWrite ) && ( FLASHStatus == FLASH_COMPLETE ) )
    {
        FLASHStatus = FLASH_ProgramHalfWord(iAddress, *(uint16_t*)buf);
        tmp += 2;
        iAddress += 2;
        buf += 2;
        //reset_iwdt();
        //reset_wwdt();
    }
    FLASH_Lock(); // Locks the FLASH Program Erase Controller
    return( iNumByteToWrite );
}

uint16_t Flash_Read(uint32_t iAddress, uint8_t*buf, int32_t iNbrToRead)
{
    int tmp = 0;
    while ( tmp < iNbrToRead )
    {
        *(buf+ tmp) = *(__IO uint8_t*) iAddress++;
        tmp++;
    }
    return( tmp );
}











