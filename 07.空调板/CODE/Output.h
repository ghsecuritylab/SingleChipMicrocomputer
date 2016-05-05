
#ifndef OUTPUT_H
#define OUTPUT_H


#define TMEP_100_BIT_OFF()  SetBit(PORTA, 0); 
#define TMEP_10_BIT_OFF()   SetBit(PORTA, 1); 
#define TMEP_1_BIT_OFF()    SetBit(PORTA, 2); 
#define TMEP_100_BIT_ON()   ClrBit(PORTA, 0);  
#define TMEP_10_BIT_ON()    ClrBit(PORTA, 1);  
#define TMEP_1_BIT_ON()     ClrBit(PORTA, 2);  
#define RH_100_BIT_OFF()   SetBit(PORTG, 1);
#define RH_10_BIT_OFF()    SetBit(PORTG, 0);
#define RH_1_BIT_OFF()     SetBit(PORTD, 7);
#define RH_100_BIT_ON()    ClrBit(PORTG, 1);
#define RH_10_BIT_ON()     ClrBit(PORTG, 0);
#define RH_1_BIT_ON()      ClrBit(PORTD, 7);


void NumberDisplayScan(AHU_DEF *Ahu);
void LedOutputScan(AHU_DEF *Ahu);

void DisplayNumber(uint16 num);
void TmepDisplayScan(AHU_DEF *Ahu);
void RhDisplayScan(AHU_DEF *Ahu);
#endif 








