#ifndef __FLASH_IAP_H__
#define __FLASH_IAP_H__

#include "stm32f10x.h"
#include "stm32f10x_flash.h"


#if defined (STM32F10X_HD)|| defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
#define FLASH_PAGE_SIZE ((uint16_t)0x800)
#else
#define FLASH_PAGE_SIZE ((uint16_t)0x400)
#endif

uint16_t Flash_Read(uint32_t iAddress, uint8_t*buf, int32_t iNbrToRead);
uint16_t Flash_Write_Without_check(uint32_t iAddress, uint8_t*buf, uint16_t iNumByteToWrite);
uint16_t Flash_Check_ERASE_Write(uint32_t iAddress, uint8_t*buf, uint16_t iNumByteToWrite);
#endif
