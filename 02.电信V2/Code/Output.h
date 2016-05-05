

#ifndef OUTPUT_H
#define OUTPUT_H

#define _164SCK_HIGH()  SetBit(PORTA, 5)
#define _164SCK_LOW()   ClrBit(PORTA, 5)
#define _164DATA_HIGH() SetBit(PORTA, 4)
#define _164DATA_LOW()  ClrBit(PORTA, 4)
#define LEDCOM1_OFF()   SetBit(PORTA, 6)
#define LEDCOM1_ON()    ClrBit(PORTA, 6)
#define LEDCOM2_OFF()   SetBit(PORTA, 7)
#define LEDCOM2_ON()    ClrBit(PORTA, 7)

void OutputDeal(DianXin_All_Def *pData);
void _164Output(uint08 Data);



void LedDispSet(DianXin_All_Def *pData);

void LedScan(DianXin_All_Def *pData);
#endif
