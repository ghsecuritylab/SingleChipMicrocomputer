


#include "includes.h"


//********************************//判断是否有按键被按下
uchar  KeyGet(void)
{
   uchar KeyOut = 0;
   if (!KEY4)
   {
      SetBit(KeyOut, 0); //远程开机
   }
   if (!KEY3)
   {
      SetBit(KeyOut, 1); //远程值机
   }
   if (!KEY2)
   {
      SetBit(KeyOut, 2); //本地开机
   }
   if (!KEY1)
   {
      SetBit(KeyOut, 3); //本地值机
   }
   return KeyOut;
}
//********************************//按键扫描处理确认按键真的被按下
void  KeyScanDeal(uint Key)
{
   uchar tmp;
   static uchar KeyLastRec;
   static uchar KeyOut;
   static uchar KeyInputCnt[_MAX_DI_];
   if (KeyStartFlag == 0)
   {
      return;
   }
   KeyStartFlag = 0;
   for (tmp = 0; tmp < _MAX_DI_; tmp++)
   {
      if ((GetBit(Key, tmp) ^ GetBit(KeyLastRec, tmp)) != 0)
      {
         ClrBit(KeyOut, tmp);
         KeyInputCnt[tmp] = 0;
      }
      else
      {
         KeyInputCnt[tmp]++;
         if (KeyInputCnt[tmp] >= 20)
         {
            if (GetBit(Key, tmp) != 0)
            {
               SetBit(KeyOut, tmp);
            }
            else
            {
               ClrBit(KeyOut, tmp);
            }
         }
      }
   }
   KeyLastRec = Key;
   CTR1.Input.All = KeyOut;
}
//********************************//按键状态处理
void KeyDeal(CTRL_DEF *Ctr)
{
   //远程控制开机按键
   if (Ctr->Input.Solo.Key_RemotePower && !Ctr->KeyTreated.Solo.Key_RemotePower)
   {
      Ctr->KeyTreated.Solo.Key_RemotePower = 1;
      Ctr->Status.Ctrl.Solo.RemoteORLocal = 1;
      Ctr->Status.Ctrl.Solo.RemotePower ^= 1;
   }
   else if (!Ctr->Input.Solo.Key_RemotePower)
   {
      Ctr->KeyTreated.Solo.Key_RemotePower = 0;
   }
   //远程控制值机按键
   if (Ctr->Input.Solo.Key_RemoteStandby && !Ctr->KeyTreated.Solo.Key_RemoteStandby)
   {
      Ctr->KeyTreated.Solo.Key_RemoteStandby = 1;
      Ctr->Status.Ctrl.Solo.RemoteORLocal = 1;
      Ctr->Status.Ctrl.Solo.RemoteStandby ^= 1;
   }
   else if (!Ctr->Input.Solo.Key_RemoteStandby)
   {
      Ctr->KeyTreated.Solo.Key_RemoteStandby = 0;
   }
   //本地控制开机按键
   if (Ctr->Input.Solo.Key_LocalPower && !Ctr->KeyTreated.Solo.Key_LocalPower)
   {
      Ctr->KeyTreated.Solo.Key_LocalPower = 1;
      Ctr->Status.Ctrl.Solo.RemoteORLocal = 0;
      Ctr->Status.Ctrl.Solo.LocalPower ^= 1;
   }
   else if (!Ctr->Input.Solo.Key_LocalPower)
   {
      Ctr->KeyTreated.Solo.Key_LocalPower = 0;
   }
   //本地控制值机按键
   if (Ctr->Input.Solo.Key_LocalStandby && !Ctr->KeyTreated.Solo.Key_LocalStandby)
   {
      Ctr->KeyTreated.Solo.Key_LocalStandby = 1;
      Ctr->Status.Ctrl.Solo.LocalStandby ^= 1;
      Ctr->Status.Ctrl.Solo.RemoteORLocal = 0;
   }
   else if (!Ctr->Input.Solo.Key_LocalStandby)
   {
      Ctr->KeyTreated.Solo.Key_LocalStandby = 0;
   }
}
//********************************//输出控制20个LED及蜂鸣器
void OutputCtrlDeal(CTRL_DEF *Ctr)
{
   if (Ctr->Output.Solo.Power)
   {
      LED1_ON();
   }
   else
   {
      LED1_OFF();
   }
   if (Ctr->Output.Solo.Run)
   {
      LED2_ON();
   }
   else
   {
      LED2_OFF();
   }
   if (Ctr->Output.Solo.Standby)
   {
      LED3_ON();
   }
   else
   {
      LED3_OFF();
   }
   if (Ctr->Output.Solo.Communication)
   {
      LED4_ON();
   }
   else
   {
      LED4_OFF();
   }
   if (Ctr->Output.Solo.Faultr)
   {
      LED5_ON();
   }
   else
   {
      LED5_OFF();
   }
   if (Ctr->Output.Solo.Inefficient)
   {
      LED6_ON();
   }
   else
   {
      LED6_OFF();
   }
   if (Ctr->Output.Solo.FanFaultr)
   {
      LED7_ON();
   }
   else
   {
      LED7_OFF();
   }
   if (Ctr->Output.Solo.InEeffect)
   {
      LED8_ON();
   }
   else
   {
      LED8_OFF();
   }
   if (Ctr->Output.Solo.LackOfWind)
   {
      LED9_ON();
   }
   else
   {
      LED9_OFF();
   }
   if (Ctr->Output.Solo.Deigo)
   {
      LED10_ON();
   }
   else
   {
      LED10_OFF();
   }
   if (Ctr->Output.Solo.ElectricHeatingTemperature)
   {
      LED11_ON();
   }
   else
   {
      LED11_OFF();
   }
   if (Ctr->Output.Solo.Efficient)
   {
      LED12_ON();
   }
   else
   {
      LED12_OFF();
   }
   if (Ctr->Output.Solo.PreheatingTemperature)
   {
      LED13_ON();
   }
   else
   {
      LED13_OFF();
   }
   if (Ctr->Output.Solo.FreezingStop)
   {
      LED14_ON();
   }
   else
   {
      LED14_OFF();
   }
   if (Ctr->Output.Solo.AntiFreezingAlarm)
   {
      LED15_ON();
   }
   else
   {
      LED15_OFF();
   }
   if (Ctr->Output.Solo.FireControlEmc)
   {
      LED16_ON();
   }
   else
   {
      LED16_OFF();
   }
   if (Ctr->Output.Solo.RemotePower)
   {
      LED17_ON();
   }
   else
   {
      LED17_OFF();
   }
   if (Ctr->Output.Solo.RemoteStandby)
   {
      LED18_ON();
   }
   else
   {
      LED18_OFF();
   }
   if (Ctr->Output.Solo.LocalPower)
   {
      LED19_ON();
   }
   else
   {
      LED19_OFF();
   }
   if (Ctr->Output.Solo.LocalStandby)
   {
      LED20_ON();
   }
   else
   {
      LED20_OFF();
   }
   if (Ctr->Output.Solo.Buzzer)
   {
      Buzzer_ON();
   }
   else
   {
      Buzzer_OFF();
   }
}

//********************************//根据状态处理输出
void StatusDeal(CTRL_DEF *Ctr)
{
//   if (!CTR1.Runflag.Solo._10ms)
//   {
//      return;
//   }
   //*********************************//远程本地控制切换
   if (Ctr->Status.Ctrl.Solo.RemoteORLocal)
   {
      if (Ctr->Status.Ctrl.Solo.RemotePower)
      {
         Ctr->Status.Ctrl.Solo.LocalPower = 0;
      }
      if (Ctr->Status.Ctrl.Solo.RemoteStandby)
      {
         Ctr->Status.Ctrl.Solo.LocalStandby = 0;
      }
   }
   else
   {
      if (Ctr->Status.Ctrl.Solo.LocalPower)
      {
         Ctr->Status.Ctrl.Solo.RemotePower = 0;
      }
      if (Ctr->Status.Ctrl.Solo.LocalStandby)
      {
         Ctr->Status.Ctrl.Solo.RemoteStandby = 0;
      }
   }
   //******************************//4个按键状态
   if (Ctr->Status.Ctrl.Solo.LocalPower)
   {
      Ctr->Output.Solo.LocalPower = 1;
   }
   else
   {
      Ctr->Output.Solo.LocalPower = 0;
   }
   if (Ctr->Status.Ctrl.Solo.LocalStandby)
   {
      Ctr->Output.Solo.LocalStandby = 1;
   }
   else
   {
      Ctr->Output.Solo.LocalStandby = 0;
   }
   if (Ctr->Status.Ctrl.Solo.RemotePower)
   {
      Ctr->Output.Solo.RemotePower = 1;
   }
   else
   {
      Ctr->Output.Solo.RemotePower = 0;
   }
   if (Ctr->Status.Ctrl.Solo.RemoteStandby)
   {
      Ctr->Output.Solo.RemoteStandby = 1;
   }
   else
   {
      Ctr->Output.Solo.RemoteStandby = 0;
   }
   //******************************************//16bitLED控制  
   Ctr->Status.LED_16bit |= BIT(0);
   Ctr->Output.All[0] = Ctr->Status.LED_16bit;
   
   
//   Ctr->Output.Solo.Power                      = (Ctr->Status.LED_16bit & 0x0001 )    ? 1:1;
//   Ctr->Output.Solo.Run                        = (Ctr->Status.LED_16bit & 0x0002 )    ? 1:0;
//   Ctr->Output.Solo.Standby                    = (Ctr->Status.LED_16bit & 0x0004 )    ? 1:0;
//   Ctr->Output.Solo.Communication              = (Ctr->Status.LED_16bit & 0x0008 )    ? 1:0;
//   Ctr->Output.Solo.Faultr                     = (Ctr->Status.LED_16bit & 0x0010 )    ? 1:0;
//   Ctr->Output.Solo.Inefficient                = (Ctr->Status.LED_16bit & 0x0020 )    ? 1:0;
//   Ctr->Output.Solo.FanFaultr                  = (Ctr->Status.LED_16bit & 0x0040 )    ? 1:0;
//   Ctr->Output.Solo.InEeffect                  = (Ctr->Status.LED_16bit & 0x0080 )    ? 1:0;
//   Ctr->Output.Solo.LackOfWind                 = (Ctr->Status.LED_16bit & 0x0100 )    ? 1:0;
//   Ctr->Output.Solo.Deigo                      = (Ctr->Status.LED_16bit & 0x0200 )    ? 1:0;
//   Ctr->Output.Solo.ElectricHeatingTemperature = (Ctr->Status.LED_16bit & 0x0400 )    ? 1:0;
//   Ctr->Output.Solo.Efficient                  = (Ctr->Status.LED_16bit & 0x0800 )    ? 1:0;
//   Ctr->Output.Solo.PreheatingTemperature      = (Ctr->Status.LED_16bit & 0x1000 )    ? 1:0;
//   Ctr->Output.Solo.FreezingStop               = (Ctr->Status.LED_16bit & 0x2000 )    ? 1:0;
//   Ctr->Output.Solo.AntiFreezingAlarm          = (Ctr->Status.LED_16bit & 0x4000 )    ? 1:0;
//   Ctr->Output.Solo.FireControlEmc             = (Ctr->Status.LED_16bit & 0x8000 )    ? 1:0;
}


