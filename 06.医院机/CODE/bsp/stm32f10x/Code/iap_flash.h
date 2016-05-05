#ifndef __FLASH_IAP_H__
#define __FLASH_IAP_H__

#include "stm32f10x.h"
#include "stm32f10x_flash.h"

#if defined (STM32F10X_HD)|| defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
#define FLASH_PAGE_SIZE ((uint16_t)0x800)
#else
#define FLASH_PAGE_SIZE ((uint16_t)0x400)
#endif


//#define WARNNING_MAX_CODE 32
//#pragma pack (4) /*指定按4字节对齐*/
//typedef struct
//{
//    uint32 AckTime;
//    uint32 ReturnTime;
//    uint32 ErrTime;
//    uint32 FlashIndex;
//    uint16 ErrRec;
//    uint16 AckOrReturnRec;
//    uint08 ErrCode;
//    ErrorFlag_Def Flags;
//}WarningManagerType;
//#pragma pack()
//extern WarningManagerType Wmngr[WARNNING_MAX_CODE];


int Flash_Read(uint32_t iAddress, uint8_t*buf, int32_t iNbrToRead);
int Flash_Write(uint32_t iAddress, uint8_t*buf, uint32_t iNbrToWrite);

#endif
