

#include "includes.h"

static    uint8_t flash_page_buff[FLASH_PAGE_SIZE];

uint16_t Flash_Write_Without_check(uint32_t iAddress, uint8_t*buf, uint16_t iNumByteToWrite)
{
	uint16_t i = 0;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

	while( ( i < iNumByteToWrite ) && ( FLASHStatus == FLASH_COMPLETE ) )
	{
		FLASHStatus = FLASH_ProgramHalfWord(iAddress, *(uint16_t*)buf);
		i += 2;
		iAddress += 2;
		buf += 2;
		//reset_iwdt();
		//reset_wwdt();
	}

	return( iNumByteToWrite );
}

/**
* @brief Programs a half word at a specifiedOption Byte Data address.
* @note This function can be usedfor all STM32F10x devices.
* @param Address: specifies the addressto be programmed.
* @param buf: specifies the datato be programmed.
* @param iNbrToWrite: the numberto write into flash
* @retval if success return the numberto write, -1 if error
* */

int Flash_Write(uint32_t iAddress, uint8_t*buf, uint32_t iNbrToWrite)
{
	uint32_t secpos;
	uint32_t iNumByteToWrite = iNbrToWrite;
	uint16_t secoff;
	uint16_t secremain; 
	uint16_t i = 0;

	//WWDG_DeInit();

	FLASH_Unlock(); //  Unlock the Flash Bank1 ProgramErase controller 
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

	secpos = iAddress & ( ~( FLASH_PAGE_SIZE - 1 ) ); //扇区地址
	secoff = iAddress & ( FLASH_PAGE_SIZE - 1 ); //在扇区内的偏移
	secremain = FLASH_PAGE_SIZE - secoff; //扇区剩余空间大小 
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

	if(iNumByteToWrite <= secremain) //不大于4096个字节
	{
		secremain = iNumByteToWrite;
	}

	while( 1 ) 
	{
		Flash_Read( secpos, flash_page_buff, FLASH_PAGE_SIZE );//读出整个扇区

		for( i = 0; i < FLASH_PAGE_SIZE; i++ )
		{ //校验数据
			if(flash_page_buff[i] != 0xFF)
			{
				break;//需要擦除
			}
		}

		if( i < secremain )
		{ //需要擦除
			FLASHStatus = FLASH_ErasePage(secpos); //擦除这个扇区
			if(FLASHStatus != FLASH_COMPLETE)
			{
				return(-1);
			}
		}

		for( i = 0; i < secremain; i++ ) //复制
		{ 
			flash_page_buff[i+secoff] = buf[i];
		}
		Flash_Write_Without_check( secpos, flash_page_buff, FLASH_PAGE_SIZE ); //写入整个扇区

		if(iNumByteToWrite == secremain) //写入结束了
		{
			break;
		}else {
			secpos += FLASH_PAGE_SIZE;
			secoff = 0; //偏移位置为0
			buf += secremain; //指针偏移
			iNumByteToWrite -= secremain; //字节数递减
			if(iNumByteToWrite > FLASH_PAGE_SIZE)
			{
				secremain = FLASH_PAGE_SIZE; //下一个扇区还是写不完
			}
			else
			{
				secremain = iNumByteToWrite; //下一个扇区可以写完了
			}
		}
	}

	FLASH_Lock(); // Locks the FLASH Program Erase Controller
	return( iNbrToWrite );
}



/**
* @brief Programs a half word at a specifiedOption Byte Data address.
* @note This function can be usedfor all STM32F10x devices.
* @param Address: specifies the addressto be programmed.
* @param buf: specifies the datato be programmed.
* @param iNbrToWrite: the numberto read from flash
* @retval if success return the numberto write, withouterror
* */


int Flash_Read(uint32_t iAddress, uint8_t*buf, int32_t iNbrToRead)
{
	int i = 0;

	while(i < iNbrToRead)
	{
		*(buf+ i) = *(__IO uint8_t*) iAddress++;
		i++;
	}

	return( i );
}

