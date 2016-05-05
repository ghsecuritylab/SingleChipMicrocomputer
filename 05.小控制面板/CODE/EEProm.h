
#ifndef EEPROM_H
#define EEPROM_H




typedef union
{
   uint All;
   struct
   {
	 uint  Enable  :1; //ʹ��
	 uint  WR1RD0  :1; //1:д 0:��
	 uint  NoScan  :1;
	 uint  Step    :4; //����
	 uint  BadSave :1; //������
	 uint  Timer   :8; //��ʱʱ��
   }Solo;
}EeSave_Def;


extern EeSave_Def EeSave1;
unsigned char AvrEeReadOne(unsigned int uiAddress);
void AvrEeWriteOne(unsigned int uiAddress, unsigned char ucData);
void AvrEeWrite(uint16 Addr, void *pdata, uint16 len);
void AvrEeRead(uint16 Addr, void *pdata, uint16 len);
uint08 CrcCheck(void *P2Data, uint16 len);
void CrcAppend(void *P2Data, uint16 len);
void EeReadTrg(EeSave_Def *EeSave);
void EeWriteTrg(EeSave_Def *EeSave);
void EePromDeal(void *P2Save, uint16 len, EeSave_Def *EeSave);



#endif


