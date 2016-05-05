
#include "includes.h"

uchar mSTimeCnt = 0;
uchar KeyStartFlag = 0;
uint msTick = 0;
RunFlag_Def RunFlag;
uchar TestMe = 15;
uchar NUMshow;

const uchar Tab0[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; //ÇåÆÁ

void  Pin_init(void)
{
   DDRC  |=  BIT(7) | BIT(6) | BIT(5);                                   //1621Òý½ÅÅäÖÃ
   PORTC |=  BIT(7) | BIT(6) | BIT(5);

   DDRB  |=  BIT(5);                                                     //±³¹âLEDÒý½ÅÅäÖÃ
   PORTB |=  BIT(5);

   DDRC  &= (~BIT(0));                                                         //Îå¸ö°´¼üÒý½ÅÅäÖÃ
   DDRC  &= (~BIT(1));
   DDRC  &= (~BIT(2));
   DDRC  &= (~BIT(3));
   DDRC  &= (~BIT(4));
   PORTC |=  BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4);

   DDRB  |=  BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4);                 //5¸ö¼ÌµçÆ÷Òý½ÅÅäÖÃ
   PORTB |=  BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4);

   DDRA  &= (~BIT(4));                                                   //ºìÍâÄÚÍâÃÅ´ÅÒý½ÅÅäÖÃ
   DDRA  &= (~BIT(5));
   DDRA  &= (~BIT(6));
   PORTA |=  BIT(4) | BIT(5) | BIT(6);

   DDRA  &= (~BIT(0));                                                   //4¸ö¹ÊÕÏ¼ì²âÅäÖÃ
   DDRA  &= (~BIT(1));
   DDRA  &= (~BIT(2));
   DDRA  &= (~BIT(3));
   PORTA |=  BIT(0) | BIT(1) | BIT(2) | BIT(3);

   DDRD  |=  BIT(2);                                                     //485¿ØÖÆÒý½ÅÅäÖÃ
   PORTD  &= (~BIT(2));

   DDRD  |=  BIT(6) | BIT(7);                                            //WTV040Ð¾Æ¬¿ØÖÆÒý½ÅÅäÖÃ
   PORTD |=  BIT(6) | BIT(7);

   DDRD  |=  BIT(3) | BIT(4);                                            //74LS165¿ØÖÆÒý½ÅÅäÖÃ
   DDRD  &= (~BIT(5));
   PORTD |=  BIT(3) | BIT(4) | BIT(5);
}

void Ctrl_init(void)
{
   FAN_OFF;
   WORKLED_OFF;
   LIGHT_OFF;
   OUTDOOR_OFF;
   INDOOR_OFF;
}

void  T1_Init(void)
{
   SREG |= BIT(7);
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L = (65535 - 8000) % 256;
   TIMSK_TOIE1 = 1;
   TCCR1A = 0;
   TCCR1B_CS10 = 1;
}

#pragma vector = TIMER1_OVF_vect
__interrupt void T1_OVF_ISR(void)
{
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L  = (65535 - 8000) % 256;
   mSTimeCnt = 1;
}

void TimeDeal(void)
{
   if (mSTimeCnt != 0)
   {
      mSTimeCnt = 0;
      msTick++;
      KeyStartFlag++;
      RunFlag.Solo._1ms = 1;

      if (msTick % 1000 == 999)
      {
         RunFlag.Solo._1000ms = 1;
      }
      if (msTick % 10 == 9)
      {
         RunFlag.Solo._10ms = 1;
      }
      if (msTick % 10000 == 9999)
      {
         RunFlag.Solo._10000ms = 1;
      }
      if (msTick % 400 == 399)
      {
         RunFlag.Solo.FastBlink ^= 1;
      }

      if (RunFlag.Solo._1000ms)
      {
         uint16 tmpCrc = FLS1.Par.Crc;
         uint16 tmpCrcNew = GetCRC16((uint08 *)&FLS1.Par, sizeof(FLS_PARS_DEF) - CRC_LEN);
         if (tmpCrc != tmpCrcNew)
         {
            EeWriteTrg(&EeSave1);
         } //´¥·¢Ð´
      }
      if (RunFlag.Solo._10ms)
      {
	 if(EeSave1.Solo.Timer > 0)
	 {
	    EeSave1.Solo.Timer--;
	 }
	 EePromDeal(&FLS1.Par, sizeof(FLS_PARS_DEF) - CRC_LEN, &EeSave1);
      }
   }
}
void DelayMs(uint i)                
{
    while(i--)
    {                          
	uint j;                
        for(j=1;j<=613;j++);               
    }                       
}


void main(void)
{
   Pin_init();
   TM1621_init();
   Ctrl_init();
   T1_Init();
   Uart_Init();
   Uart_AppInit();
   MdTcbInit();
   LCDDispWord(&SHOWBuff);
   FLS1.Status.All = 0;
   FLS1.Status.Solo.Idle = 1;
   {
      EeSave1.Solo.BadSave = 0;
      EeReadTrg(&EeSave1);
      EePromDeal(&FLS1.Par, sizeof(FLS_PARS_DEF) - CRC_LEN, &EeSave1);
      if (EeSave1.Solo.BadSave)
      {

         EeSave1.Solo.BadSave = 0;

         FLS1.Par.FanRunningTime = 15;
      }
      EeWriteTrg(&EeSave1);
   }
  
//   FLS1.Voice.Solo.WelcomeUseCanlend = 1;

   while (1)
   {

      TimeDeal();
      KeyScanDeal(KeyGet());
      Scan_165_Deal(Read_165Data());
      FlsDealAll(&FLS1);
      DispOneFls(&SHOWBuff, &FLS1);
      FlsVoice(&WTV1, &FLS1); 
      LCDShowAll(SHOWBuff.All);
      MdPoll();
      if (RunFlag.Solo._1ms)
      {
	 UartTimeOut(&UartAppData1);
      }
      RunFlag.Solo._1ms = 0;
      RunFlag.Solo._10ms = 0;
      RunFlag.Solo._1000ms = 0;
      RunFlag.Solo._10000ms = 0;
   }
}


