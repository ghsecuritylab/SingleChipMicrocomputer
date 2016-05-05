
#include "includes.h"

FFUDataBaseDef FFU1;
FFU_KEY_Enum FUKey;


void FFU_LED_01_ON() { ClrBit(PORTD, 3);}
void FFU_LED_02_ON() { ClrBit(PORTD, 4);}
void FFU_LED_03_ON() { ClrBit(PORTD, 5);}
void FFU_LED_04_ON() { ClrBit(PORTD, 6);}
void FFU_LED_05_ON() { ClrBit(PORTD, 7);}
void FFU_LED_06_ON() { ClrBit(PORTC, 0);}
void FFU_LED_07_ON() { ClrBit(PORTC, 1);}
void FFU_LED_08_ON() { ClrBit(PORTC, 2);}
void FFU_LED_09_ON() { ClrBit(PORTC, 3);}
void FFU_LED_10_ON() { ClrBit(PORTC, 4);}

void FFU_LED_01_OFF() { SetBit(PORTD, 3);}   
void FFU_LED_02_OFF() { SetBit(PORTD, 4);}   
void FFU_LED_03_OFF() { SetBit(PORTD, 5);}   
void FFU_LED_04_OFF() { SetBit(PORTD, 6);}   
void FFU_LED_05_OFF() { SetBit(PORTD, 7);}   
void FFU_LED_06_OFF() { SetBit(PORTC, 0);}   
void FFU_LED_07_OFF() { SetBit(PORTC, 1);}   
void FFU_LED_08_OFF() { SetBit(PORTC, 2);}   
void FFU_LED_09_OFF() { SetBit(PORTC, 3);}   
void FFU_LED_10_OFF() { SetBit(PORTC, 4);}   


void (*__flash LedOnOffs[10][2])() =
{
   FFU_LED_01_OFF, FFU_LED_01_ON,
   FFU_LED_02_OFF, FFU_LED_02_ON,
   FFU_LED_03_OFF, FFU_LED_03_ON,
   FFU_LED_04_OFF, FFU_LED_04_ON,
   FFU_LED_05_OFF, FFU_LED_05_ON,
   FFU_LED_06_OFF, FFU_LED_06_ON,
   FFU_LED_07_OFF, FFU_LED_07_ON,
   FFU_LED_08_OFF, FFU_LED_08_ON,
   FFU_LED_09_OFF, FFU_LED_09_ON,
   FFU_LED_10_OFF, FFU_LED_10_ON,
};







void FFU_RL_01_ON() { SetBit(PORTB, 2);}
void FFU_RL_02_ON() { SetBit(PORTB, 1);}
void FFU_RL_03_ON() { SetBit(PORTB, 0);}
void FFU_RL_04_ON() { SetBit(PORTA, 0);}
void FFU_RL_05_ON() { SetBit(PORTA, 1);}

void FFU_RL_01_OFF()  { ClrBit(PORTB, 2);}  
void FFU_RL_02_OFF()  { ClrBit(PORTB, 1);}  
void FFU_RL_03_OFF()  { ClrBit(PORTB, 0);}  
void FFU_RL_04_OFF()  { ClrBit(PORTA, 0);}  
void FFU_RL_05_OFF()  { ClrBit(PORTA, 1);}  


void (*__flash RLOnOffs[5][2])() =
{
   FFU_RL_01_OFF, FFU_RL_01_ON,
   FFU_RL_02_OFF, FFU_RL_02_ON,
   FFU_RL_03_OFF, FFU_RL_03_ON,
   FFU_RL_04_OFF, FFU_RL_04_ON,
   FFU_RL_05_OFF, FFU_RL_05_ON,
};


#define TIME_START 252
#define TIME_STEP 6
__flash uint08 BT139_Lvl_Table[12] =
#if 1
{
   (TIME_START - 8 * TIME_STEP),
   (TIME_START - 8 * TIME_STEP),
   (TIME_START - 7 * TIME_STEP),
   (TIME_START - 6 * TIME_STEP),
   (TIME_START - 5 * TIME_STEP),
   (TIME_START - 4 * TIME_STEP),
   (TIME_START - 3 * TIME_STEP),
   (TIME_START - 2 * TIME_STEP),
   (TIME_START - 1 * TIME_STEP),
   (TIME_START - 0 * TIME_STEP),


   //254,
   //221,
   //216,
   //211,
   //206,
   //201,
   //196,
   //191,
   //186,
   //181,
};
#else
{
   0,
   217,
   213,
   209,
   205,
   201,
   197,
   193,
   189,
   185,
   181,
};
#endif

__flash uint08 RL_Lvl_Table[11] =
{
   RL_LV00,
   RL_LV01,
   RL_LV02,
   RL_LV03,
   RL_LV04,
   RL_LV05,
   RL_LV06,
   RL_LV07,
   RL_LV08,
   RL_LV09,
   RL_LV10,
};



void FFUKeyDeal(FFUDataBaseDef *FFU, FFU_KEY_Enum Key)
{
   if (Key == FFU_KeyOnOff)
   {
      if (FFU->Run.Now_Status == 0)
      {
         FFU->Run.Now_Status = 1;
         if (FFU->Run.Now_FanRelayLvl == 0)
         {
            FFU->Run.Now_FanRelayLvl = 1;
         }
      }
      else
      {
         FFU->Run.Now_Status = 0;
      }
      FFU->Run.LastCtrl = FFU_ManualCtrl;
   }
   if (Key == FFU_KeyAdd)
   {
      if (FFU->Run.Now_Status != 0)
      {
         if (FFU->Run.Now_FanRelayLvl++ >= 10)
         {
            FFU->Run.Now_FanRelayLvl = 10;
         }
      }
      else
      {
         FFU->Run.Now_Status = 1;
         if (FFU->Run.Now_FanRelayLvl == 0)
         {
            FFU->Run.Now_FanRelayLvl = 1;
         }
      }
      FFU->Run.LastCtrl = FFU_ManualCtrl;

   }
   if (Key == FFU_KeySub)
   {
      if (FFU->Run.Now_Status != 0)
      {
         FFU->Run.Now_FanRelayLvl--;
         if (FFU->Run.Now_FanRelayLvl > 10 || FFU->Run.Now_FanRelayLvl == 0)
         {
            FFU->Run.Now_Status = 0;
         }
         FFU->Run.LastCtrl = FFU_ManualCtrl;
      }
   }
}
void FFUKeyScan(FFUDataBaseDef *FFU)
{
   static uint16 ReDealCnt;
   //KeyReDeal
   if (RunFlag.Solo._1msFlag)
   {
      if (FFU->Buff.DiTreat.Solo.KeyAdd ^ FFU->Buff.DiTreat.Solo.KeySub)
      {
         ReDealCnt++;
         if (ReDealCnt > 300)
         {
            ReDealCnt = 0;
            FFU->Buff.DiTreat.Solo.KeyAdd = 0;
            FFU->Buff.DiTreat.Solo.KeySub = 0;
         }
      }
      else
      {
         ReDealCnt = 0;
      }
   }



   //KeyOnOff
   if (FFU->Buff.DiIn.Solo.KeyOnOff &&  !FFU->Buff.DiTreat.Solo.KeyOnOff)
   {
      FFU->Buff.DiTreat.Solo.KeyOnOff = 1;
      FFUKeyDeal(FFU, FFU_KeyOnOff);
   }
   else if (!FFU->Buff.DiIn.Solo.KeyOnOff)
   {
      FFU->Buff.DiTreat.Solo.KeyOnOff = 0;
   }


   //KeyAdd
   if (FFU->Buff.DiIn.Solo.KeyAdd &&  !FFU->Buff.DiTreat.Solo.KeyAdd)
   {
      FFU->Buff.DiTreat.Solo.KeyAdd = 1;
      FFUKeyDeal(FFU, FFU_KeyAdd);
   }
   else if (!FFU->Buff.DiIn.Solo.KeyAdd)
   {
      FFU->Buff.DiTreat.Solo.KeyAdd = 0;
   }

   //KeySub
   if (FFU->Buff.DiIn.Solo.KeySub &&  !FFU->Buff.DiTreat.Solo.KeySub)
   {
      FFU->Buff.DiTreat.Solo.KeySub = 1;
      FFUKeyDeal(FFU, FFU_KeySub);
   }
   else if (!FFU->Buff.DiIn.Solo.KeySub)
   {
      FFU->Buff.DiTreat.Solo.KeySub = 0;
   }
}

__flash uint08 LightStep[40] =
{
   0x00,
   0x01,
   0x02,
   0x03,
   0x04,
   0x05,
   0x06,
   0x07,
   0x08,
   0x09,
   0x09,
   0x08,
   0x07,
   0x06,
   0x05,
   0x04,
   0x03,
   0x02,
   0x01,
   0x00,
   0x20,
   0x21,
   0x22,
   0x23,
   0x24,
   0x25,
   0x26,
   0x27,
   0x28,
   0x29,
   0x30,
   0x31,
   0x32,
   0x33,
   0x34,
   0x35,
   0x36,
   0x37,
   0x38,
   0x39,
};

void DispError(FFUDataBaseDef *FFU)
{
   if (RunFlag.Solo.FastBlink)
   {
      FFU->Run.LED.All = 0x3FF;
   }
   else
   {
      FFU->Run.LED.All = 0x000;
   }

}


void DispOff(FFUDataBaseDef *FFU)
{
   uint08 tmpLed = LightStep[(msTick / 100 % 40)];
   FFU->Run.LED.All = 0;
   if (tmpLed<=10)
   {
      SetBit(FFU->Run.LED.All, tmpLed);
   }
   if (FFU->Run.LED.All > 0)
   {
      if (UartAppData1.LivingTime>0)
      {
         FFU->Run.LED.Solo.LEV_LED_01 = RunFlag.Solo.FastBlink;
      }
   }
}


void DispLvl(FFUDataBaseDef *FFU)
{
   uint08 tmp;
   uint08 Lvl = FFU->Run.Now_FanRelayLvl;
   for (tmp = 0; tmp < 10; tmp++)
   {
      if (tmp < Lvl)
      {
         SetBit(FFU->Run.LED.All, tmp);
      }
      else
      {
         ClrBit(FFU->Run.LED.All, tmp);
      }
   }
}
void LedBuffToIO(uint16 buff)
{
   uint08 tmp;
   for (tmp = 0; tmp < 10; tmp++)
   {
      if (GetBit(buff, tmp) != 0x00)
      {
         Run_void(LedOnOffs[tmp][1]);
      }
      else
      {
         Run_void(LedOnOffs[tmp][0]);
      }
   }
}



void DispFFULed(FFUDataBaseDef *FFU)
{
   if (!RunFlag.Solo._1msFlag)
   {
      return;
   }

   if ((msTick / 100 % 40)> 20 && (FFU->Run.Now_FanError != 0))
   {
      DispError(FFU);
   }
   else
   {
      if (FFU->Run.Now_Status != 0)
      {
         DispLvl(FFU);
      }
      else
      {
         DispOff(FFU);
      }
   }
   LedBuffToIO(FFU->Run.LED.All);
// LedBuffToIO(FFU->Run.DIState.Solo.Addr);

}




void RelayLvl(uint08 Lvl)
{
   uint08 tmp;
   uint08 tmpLoad;

   if (Lvl > 10)
   {
      Lvl = 10;
   }
   tmpLoad = RL_Lvl_Table[Lvl];
   for (tmp = 0; tmp < 5; tmp++)
   {
      if ((tmpLoad & (1 << tmp)) != 0)
      {
         Run_void(RLOnOffs[tmp][1]);
         SetBit(FFU1.Run.RL.All, tmp);
      }
      else
      {
         Run_void(RLOnOffs[tmp][0]);
         ClrBit(FFU1.Run.RL.All, tmp);
      }
   }
}

void FFUErrorStop(FFUDataBaseDef *FFU)
{
   if (!RunFlag.Solo._1msFlag)
   {
      return;
   }
   
   if (FFU->Run.Now_FanError!=0)
   {
      FFU->Buff.ErrStopTimer++;
      if (FFU->Buff.ErrStopTimer > 10000)
      {
         FFU->Buff.ErrStopTimer = 0;
         FFU->Run.Now_Status = 1;
         FFU->Run.LastCtrl = 2; //ERROR STOP
      }
      else
      {
          FFU->Buff.ErrStopTimer++;
      }
   }
   else
   {
          FFU->Buff.ErrStopTimer=0;
   }
}





void FFUInitOne()
{
// uint08 retry = 5;
// while (retry--)
// {
//    AvrEeRead(FFU1_EE_ADDR, &FFU->Run.Now_FanRelayLvl, FFU_EE_LEN);
//    if (FFU->Run.Now_FanRelayLvl <= 10)
//    {
//       break;
//    }
// }
   //FFU->Run.READ_SPARE[1] = FFU->Run.Now_FanRelayLvl;
   //FFU->Run.READ_SPARE[2] = FFU->Run.Now_Status;
   //FFU->Run.READ_SPARE[3] = FFU->Run.Now_FanBTLvl;

    FC1.State.Sys.All = 0;
    FC1.Run.FanLvlDelay = 1000;
    FC1.Run.TempCtrlDelay = 2000;
    FC1.Run.FanLvlSet = 0;
    FC1.Run.SetTemp = 260;
    FC1.Run.SetTime2Start = 0;
    FC1.Run.SetTime2Stop = 0;

// if (FFU->Run.Now_Status != 1)
// {
//    FFU->Run.Now_Status = 0;
// }
// if (FFU->Run.Now_FanRelayLvl > 10)
// {
//    FFU->Run.Now_FanRelayLvl = 10;
// }
// if (FFU->Run.Now_FanBTLvl > 10)
// {
//    FFU->Run.Now_FanBTLvl = 10;
// }
}


void FFUDealOne(FFUDataBaseDef *FFU)
{

   //FFU->Run.Now_FanError = 1;
   //按键处理
   FFUKeyScan(FFU);
   //故障处理
   FFUErrorStop(FFU);
   //显示
   DispFFULed(FFU);


   //继电器输出
   if (msStartUpCnt < 2000)
   {
      RelayLvl(0);
   }
   else if (FFU->Run.Now_Status != 0)
   {
      RelayLvl(FFU->Run.Now_FanRelayLvl);
   }
   else
   {
      RelayLvl(0);
   }
   //EEPROM
   if (RunFlag.Solo.Eeprom)
   {
      RunFlag.Solo.Eeprom = 0;
      AvrEeWrite(FFU1_EE_ADDR, &FFU->Run.Now_FanRelayLvl, FFU_EE_LEN);
   }


}

uint16 FF_MD_READ(FFUDataBaseDef *FFU, uint16 Index)
{
   uint16 *p2data = (uint16 *)FFU;

   if (Index == FFU_TEL_LVL)
   {
       return p2data[FFU_TEL_LVL_FEEDBACK];
   }
   if (Index == FFU_TEL_RUN)
   {
       return p2data[FFU_TEL_RUN_FEEDBACK];
   }
   if (Index == FFU_TEL_BTLVL)
   {
       return p2data[FFU_TEL_BTLVL_FEEDBACK];
   }
   if (Index < 50)
   {
      return p2data[Index];
   }
   return (0);
}




void FFU_MD_CTRL(FFUDataBaseDef *FFU, uint16 Index, uint16 Data)
{
   if (Index == FFU_TEL_LVL)
   {
      if (Data <= 10 && Data != FFU->Run.Tel_Lvl_Set)
      {
         FFU->Run.Now_FanRelayLvl = Data;
         FFU->Run.Tel_Lvl_Set = Data;
         FFU->Run.LastCtrl = FFU_TelCtrl;

      }
   }

   if (Index == FFU_TEL_RUN)
   {
      if (Data != FFU->Run.Tel_FFU_Run)
      {
         if (Data > 0)
         {
            FFU->Run.Now_Status = 1;
         }
         else
         {
            FFU->Run.Now_Status = 0;
         }
         FFU->Run.Tel_FFU_Run = Data;
         FFU->Run.LastCtrl = FFU_TelCtrl;
      }
   }

   if (Index == FFU_TEL_BTLVL)
   {
      if (Data != FFU->Run.Tel_BTLvl_Set)
      {
         if (Data > 10)
         {
            FFU->Run.Now_FanBTLvl = 10;
         }
         else
         {
            FFU->Run.Now_FanBTLvl = Data;
         }
         FFU->Run.Tel_BTLvl_Set = Data;
         FFU->Run.LastCtrl = FFU_TelCtrl;
      }
   }
}


void ExtIntInit()
{
   GICR_INT0 = 0;
   MCUCR |= 0x03;
   GIFR = 0x40;
   GICR_INT0 = 1;
   Global_EI();
}



/*定时器0初始化*/
void T0_Init(void)
{
   TCCR0 = 0x0B;
   TCNT0 = 0;            //给定时器赋初值
   OCR0 = 10;            //给定时器赋初值
   TIFR_TOV0 = 1;
   TIMSK_TOIE0 = 1;   //使能T0溢出中断
                      // Global_EI();
}

#pragma vector = TIMER0_OVF_vect
__interrupt void T0_OVF_ISR(void)
{
   FFU_BT139_REV();
   TIMSK_TOIE0 = 0;   //使能T0溢出中断
}

#pragma vector = INT0_vect
__interrupt void INT0_ISR(void)
{
   GIFR = 0x40;
   FFU1.Run.Now_FanBTLvl = FFU1.Run.Now_FanRelayLvl;
   if (msStartUpCnt < 3000)
   {
      FFU_BT139_OFF();
      return;
   }
   if (FFU1.Run.Now_Status > 0)
   {
      if (FFU1.Run.Now_FanBTLvl > 0)
      {
         if (FFU1.Run.Now_FanBTLvl <= 9)
         {
            FFU_BT139_OFF();
            TCCR0 = 0x05;         //配置定时器工作普通模式
            TCNT0 = BT139_Lvl_Table[FFU1.Run.Now_FanBTLvl];            //给定时器赋初值
            TIFR_TOV0 = 1;
            TIMSK_TOIE0 = 1;   //使能T0溢出中断
         }
         else
         {
            FFU_BT139_ON();
         }
      }
   }
   else
   {
      FFU_BT139_OFF();
   }
}











