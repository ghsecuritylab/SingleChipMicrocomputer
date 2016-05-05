
#include  "includes.h"



FlashSave_def ParSave;
const char ParToken[] = "KyjPars";
#define FLASH_SAVE_DEBUG 1



uint08 ParSaveInit()
{
    ParSave.Flash_StartAddr  =   PARSAVE_FLASH_FIRST_PAGE_ADDRESS;
    ParSave.Flash_EndAddr   =    PARSAVE_FLASH_LAST_PAGE_ADDRESS;
    ParSave.ShiftLen   =  PARSAVE_SHIFT_LEN;
    ParSave.TokenStr =             ParToken;
    ParSave.Data_Len = sizeof(YYJ_OPTIONS);
    ParSave.MaxIndex = (PARSAVE_FLASH_LAST_PAGE_ADDRESS-PARSAVE_FLASH_FIRST_PAGE_ADDRESS)/PARSAVE_SHIFT_LEN;
    ParSave.Data_Addr = (uint8_t *)&YYJ1.OP;
    ParSave.SaveIndex = GetFlashIndexHalf(&ParSave);
    if(ParSave.SaveIndex > ParSave.MaxIndex)
    {

        ParSave.SaveIndex = 0;
        return 1;
    }
    else
    {
        ParSave.ReadIndex = ParSave.SaveIndex;
        ParSave.SaveIndex++;
        while (ParSave.ReadIndex>0)
        {
            if(ReadPreSetIndex(&ParSave)==0)
            {
                break;
            }
            ParSave.ReadIndex--;
        }
        if (ParSave.ReadIndex==0)
        {
            if(ReadPreSetIndex(&ParSave)>0)
            {
                ParSave.SaveIndex = 0;
            }
        }
        return 0;
    }
}





void ParSaveTest(uint16 Times)
{
    uint16 tmp;
//    PRINTF((0,"Start of ParSaveTest %04d!!!\r\n",Times));
    for (tmp=0;tmp<Times;tmp++)
    {
        DoFlashSave(&ParSave);
        IWDG_ReloadCounter();/* Î¹¹·*/
    }
//    PRINTF((0,"End of ParSaveTest %04d\r\n",Times));
}




uint08 CrcCheck(void *P2Data, uint16 len)
{
   uint16 *Pcrc   = P2Data;
   uint16 ReadCrc = Pcrc[len / 2];
   uint16 crc     = GetCRC16((uint08 *)P2Data, len);
   if (ReadCrc != crc)
   {
      Pcrc[len / 2] = crc;
      return 1;
   }
   return 0;
}



void YYJ_ParSave()
{
   if ( CrcCheck(ParSave.Data_Addr, ParSave.Data_Len-2) )
   {
      DoFlashSave(&ParSave);
   }
//      if (YYJ1.OP.FlashCRC != GetCRC16((uint08 *)&YYJ1.OP, ParSave.Data_Len - 2))
//      {
//         DoFlashSave(&ParSave);
//      }

}








