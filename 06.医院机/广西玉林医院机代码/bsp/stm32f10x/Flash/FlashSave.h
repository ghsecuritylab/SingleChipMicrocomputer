

#ifndef _FLASH_SAVE_H_
#define _FLASH_SAVE_H_


#define SAVE_TOKEN_LEN 8
typedef struct
{
   uint32 Flash_StartAddr;
   uint32 Flash_EndAddr;
   uint8_t *Data_Addr;
   uint32 CRC32;
   const char*TokenStr;
   uint32   SaveIndex;
   uint16   Data_Len;
   uint16   ReadIndex;
   uint16   MaxIndex;
   uint16   ShiftLen;
}FlashSave_def;

void ClearFlashSave(FlashSave_def *Flash,uint8_t Backup);
void DoFlashSave(FlashSave_def *Flash);
uint32 GetMaxFlashIndex(FlashSave_def *Flash);
uint16 GetFlashIndexHalf(FlashSave_def *Flash);
uint16 ReadPreSetIndex(FlashSave_def *Flash);






//void WriteFlash();
//void GetFreeFlash();
//
//void WriteRecord();
//void GetFreeRecord();


#endif
