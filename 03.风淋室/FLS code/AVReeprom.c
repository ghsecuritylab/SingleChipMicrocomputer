
#include "includes.h"
unsigned char AvrEeReadOne(unsigned int uiAddress)
{
   /* 等待上一次写操作结束 */
   while (EECR_EEWE);
   /* 设置地址寄存器*/
   EEAR = uiAddress;
   /* 设置EERE 以启动读操作*/
   EECR_EERE = 1;
   /* 自数据寄存器返回数据 */
   return EEDR;
}
void AvrEeWriteOne(unsigned int uiAddress, unsigned char ucData)
{
   /* 等待上一次写操作结束 */
   while (EECR_EEWE);
   /* 设置地址和数据寄存器*/
   EEAR = uiAddress;
   EEDR = ucData;
   /* 置位EEMWE */
   /* 同时清零EEWE */
   EECR = 0x04;
   /* 置位EEWE 以启动写操作*/
   EECR_EEWE = 1;
}


void AvrEeWrite(uint16 Addr, void *pdata, uint16 len)
{
   uint08 *dataScr = pdata;
   uint08 buff;
   uint16 tmp;
   for (tmp = 0; tmp < len; tmp++)
   {
      buff = AvrEeReadOne(Addr + tmp);
      if (buff != dataScr[tmp])
      {
         AvrEeWriteOne(Addr + tmp, dataScr[tmp]);
      }
   }
}

void AvrEeRead(uint16 Addr, void *pdata, uint16 len)
{
   uint08 *dataScr = pdata;
   uint16 tmp;
   for (tmp = 0; tmp < len; tmp++)
   {
      __EEGET(dataScr[tmp], Addr + tmp);
   }
}



EeSave_Def EeSave1 = { 0 };
#define EEPROM_SAVE_ADDR0 0x0000
#define EEPROM_SAVE_ADDR1 0x0200

uint08 CrcCheck(void *P2Data, uint16 len)
{
   uint16 *Pcrc = P2Data;
   uint16 ReadCrc = 0;
   uint16 CRC = GetCRC16((uint08 *)P2Data, len);
   ReadCrc = Pcrc[len / 2];
   if (ReadCrc == CRC)
   {
      return 1;
   }
   return 0;
}
void CrcAppend(void *P2Data, uint16 len)
{
   uint16 *Pcrc = P2Data;
   uint16 CRC = GetCRC16((uint08 *)P2Data, len);
   Pcrc = &Pcrc[len / 2];
   *Pcrc = CRC;
}


void EeReadTrg(EeSave_Def *EeSave)
{
   EeSave->All = 0;
   EeSave->Solo.Enable = 1;
}
void EeWriteTrg(EeSave_Def *EeSave)
{
   EeSave->All = 0;
   EeSave->Solo.WR1RD0 = 1;
   EeSave->Solo.Enable = 1;
}



void EePromDeal(void *P2Save, uint16 len, EeSave_Def *EeSave)
{
   if (EeSave->Solo.Enable)
   {
      if (!EeSave->Solo.WR1RD0) //reading
      {
         EeSave->Solo.Enable = 0;
         AvrEeRead(EEPROM_SAVE_ADDR0, P2Save, len + CRC_LEN);
         if (CrcCheck(P2Save, len) == 0)
         {
            EeSave->Solo.BadSave = 1;
            AvrEeRead(EEPROM_SAVE_ADDR1, P2Save, len + CRC_LEN);
            if (CrcCheck(P2Save, len) == 0)
            {
               EeSave->All = 0;
               EeSave->Solo.BadSave = 1;
               return;
            }
            else
            {
               EeSave->All = 0;
               return;
            }
         }
         else
         {
            EeSave->All = 0;
         }
      }
      else //Saving
      {
         if (EeSave->Solo.Step == 0)
         {
            EeSave->Solo.Step++;
            EeSave->Solo.Timer = 20;
         }
         else if (EeSave->Solo.Step == 1)
         {
            if (EeSave->Solo.Timer == 0)
            {
               CrcAppend(P2Save, len);
               AvrEeWrite(EEPROM_SAVE_ADDR0, P2Save, len + CRC_LEN);
               EeSave->Solo.Timer = 20;
               EeSave->Solo.Step++;
            }
         }
         else if (EeSave->Solo.Step == 2)
         {
            if (EeSave->Solo.Timer == 0)
            {
               CrcAppend(P2Save, len);
               AvrEeWrite(EEPROM_SAVE_ADDR1, P2Save, len + CRC_LEN);
               EeSave->Solo.Step++;
            }
         }
         else
         {
            if (EeSave->Solo.Timer == 0)
            {
               EeSave->All = 0;
            }
         }
      }
   }
}





















