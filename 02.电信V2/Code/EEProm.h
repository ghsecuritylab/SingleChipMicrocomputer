
#ifndef EEPROM_H
#define EEPROM_H




typedef union
{
   uint16 All;
   struct
   {
	 uint16  Enable  :1; //ʹ��
	 uint16  WR1RD0  :1; //1:д 0:��
	 uint16  NoScan  :1;
	 uint16  Step    :4; //����
	 uint16  BadSave :1; //������
	 uint16  Timer   :8; //��ʱʱ��
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

void EEpromSaveInit();
void EEpromTimeOut();
void EEpromWrite();



#endif


