

#ifndef AVR_EEPROM_H
#define AVR_EEPROM_H
void AvrEeWrite(uint16 Addr,void *pdata,uint16 len);
void AvrEeRead(uint16 Addr,void *pdata,uint16 len);


#define CRC_LEN 2 //CRC16

typedef union
{
   uint16 All;
   struct
   {
	 uint16 Enable:1;
	 uint16 WR1RD0:1;
	 uint16 NoScan:1;
	 uint16 Step:4;
	 uint16 BadSave:1;
	 uint16 Timer:8;
   }Solo;
}EeSave_Def;


extern EeSave_Def EeSave1;






void EePromDeal(void *P2Save, uint16 len,EeSave_Def *EeSave);
void EeReadTrg(EeSave_Def *EeSave);
void EeWriteTrg(EeSave_Def *EeSave);








#endif









