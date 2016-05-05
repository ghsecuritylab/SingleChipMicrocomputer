

#include "includes.h"



#include "stm32f10x_crc.h"

void ClearFlashSave(FlashSave_def *Flash,uint8_t Backup)
{
    //uint32_t secpos;
    uint32_t iAddress;
    FLASH_Unlock(); //  Unlock the Flash Bank1 ProgramErase controller 
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

    volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
     //Earase the first and backup data
     iAddress = Flash->Flash_StartAddr;
     if (Backup !=0 ) 
     {
	     FLASHStatus = FLASH_ErasePage(iAddress);//擦除第一个扇区
	     Flash_Write_Without_check(iAddress+SAVE_TOKEN_LEN,Flash->Data_Addr,Flash->Data_Len);
	     Flash_Write_Without_check(iAddress,(uint8_t *)Flash->TokenStr,SAVE_TOKEN_LEN);
	     iAddress=Flash->Flash_StartAddr+FLASH_PAGE_SIZE;
     }

    
    //OSTimeDlyHMSM(0, 0, 0, 10);
  rt_thread_delay(RT_TICK_PER_SECOND / 100);


    //从第二个扇区开始擦除
    FLASH_Unlock(); //  Unlock the Flash Bank1 ProgramErase controller 
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    for ( iAddress=iAddress;iAddress<Flash->Flash_EndAddr;iAddress+=FLASH_PAGE_SIZE )
    {
        rt_thread_delay(RT_TICK_PER_SECOND / 100);
        FLASHStatus = FLASH_ErasePage(iAddress);//擦除第一个扇区
        if(FLASHStatus!=FLASH_COMPLETE)
        {
          rt_thread_delay(RT_TICK_PER_SECOND / 20);
        }
          
    }
    FLASH_Lock(); // Locks the FLASH Program Erase Controller
    rt_thread_delay(RT_TICK_PER_SECOND / 100);
    
}


void DoFlashSave(FlashSave_def *Flash)
{
    uint32_t iAddress;
    if(Flash->SaveIndex>=Flash->MaxIndex)
    {
        //DataBackUp
        ClearFlashSave(Flash,1);
	Flash->SaveIndex = 1;
    }

    iAddress = Flash->Flash_StartAddr+Flash->SaveIndex*Flash->ShiftLen;
    if(iAddress< (Flash->Flash_EndAddr-Flash->Data_Len))
    {
        Flash_Write_Without_check(iAddress+SAVE_TOKEN_LEN,Flash->Data_Addr,Flash->Data_Len);
        Flash->CRC32 = GetCRC32((uint08 *)Flash->Data_Addr,Flash->Data_Len);
        Flash_Write_Without_check(iAddress+Flash->Data_Len+SAVE_TOKEN_LEN,(uint8_t *)&Flash->CRC32,4);
        Flash_Write_Without_check(iAddress,(uint8_t *)Flash->TokenStr,SAVE_TOKEN_LEN);
    }
    Flash->SaveIndex++;
}

uint16 GetFlashIndexHalf(FlashSave_def *Flash)
{
    uint16 tmp=0;
    uint16 TokenFind =0xFFFF;
    uint32_t iAddress;
    char charBuf[8];

    //2确定在哪一项
    for(tmp=0;tmp<Flash->MaxIndex;tmp++)
    {
        iAddress = Flash->Flash_StartAddr + tmp * Flash->ShiftLen;
        Flash_Read(iAddress,(uint8_t *)&charBuf,SAVE_TOKEN_LEN);
        if ( 0 == strcmp(charBuf,Flash->TokenStr) )
        {
                if(TokenFind>=Flash->MaxIndex)
                {
                    TokenFind = tmp;
                }
                else if(TokenFind<tmp)
                {
                    TokenFind = tmp;
                }
        }
    }

    //没有找到合适的数据头
    if(TokenFind>=Flash->MaxIndex)
    {
        return TokenFind;
    }
        return TokenFind;
}


uint16 ReadPreSetIndex(FlashSave_def *Flash)
{
    uint32_t iAddress;
    //1确定在哪一页
    iAddress = Flash->Flash_StartAddr+Flash->ReadIndex*Flash->ShiftLen+SAVE_TOKEN_LEN;
    Flash_Read(iAddress,(uint8_t *)Flash->Data_Addr,Flash->Data_Len);


    //CRC校对 0xF12EAEC5
    Flash_Read(iAddress+Flash->Data_Len,(uint8_t *)&Flash->CRC32,4);
    iAddress = GetCRC32((uint08 *)Flash->Data_Addr,Flash->Data_Len);
    if (Flash->CRC32 == iAddress)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

















