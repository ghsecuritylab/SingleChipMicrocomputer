

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

	secpos = iAddress & ( ~( FLASH_PAGE_SIZE - 1 ) ); //������ַ
	secoff = iAddress & ( FLASH_PAGE_SIZE - 1 ); //�������ڵ�ƫ��
	secremain = FLASH_PAGE_SIZE - secoff; //����ʣ��ռ��С 
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

	if(iNumByteToWrite <= secremain) //������4096���ֽ�
	{
		secremain = iNumByteToWrite;
	}

	while( 1 ) 
	{
		Flash_Read( secpos, flash_page_buff, FLASH_PAGE_SIZE );//������������

		for( i = 0; i < FLASH_PAGE_SIZE; i++ )
		{ //У������
			if(flash_page_buff[i] != 0xFF)
			{
				break;//��Ҫ����
			}
		}

		if( i < secremain )
		{ //��Ҫ����
			FLASHStatus = FLASH_ErasePage(secpos); //�����������
			if(FLASHStatus != FLASH_COMPLETE)
			{
				return(-1);
			}
		}

		for( i = 0; i < secremain; i++ ) //����
		{ 
			flash_page_buff[i+secoff] = buf[i];
		}
		Flash_Write_Without_check( secpos, flash_page_buff, FLASH_PAGE_SIZE ); //д����������

		if(iNumByteToWrite == secremain) //д�������
		{
			break;
		}else {
			secpos += FLASH_PAGE_SIZE;
			secoff = 0; //ƫ��λ��Ϊ0
			buf += secremain; //ָ��ƫ��
			iNumByteToWrite -= secremain; //�ֽ����ݼ�
			if(iNumByteToWrite > FLASH_PAGE_SIZE)
			{
				secremain = FLASH_PAGE_SIZE; //��һ����������д����
			}
			else
			{
				secremain = iNumByteToWrite; //��һ����������д����
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

