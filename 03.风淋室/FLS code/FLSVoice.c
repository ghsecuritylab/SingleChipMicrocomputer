
#include "includes.h"



WTV040_CONTROL_DEF  WTV1;

void VoiceCtrl(WTV040_CONTROL_DEF *voice)
{
   if (voice->Solo.PinRST)
   {
      WTVRST1;
   }
   else
   {
      WTVRST0;
   }

   if (voice->Solo.PinDATA)
   {
      WTVDATA1;
   }
   else
   {
      WTVDATA0;
   }
}

void VoiceDeal(WTV040_CONTROL_DEF *voice)
{

   if (voice->Solo.Step == 0)
   {
      voice->Solo.Step++;
      voice->Solo.Timer = 5;
      //voice->Solo.Enable = 1;
   }

   else if (voice->Solo.Step == 1)
   {
      voice->Solo.PinRST = 1;
      voice->Solo.PinDATA = 1;
      if (voice->Solo.Timer == 0)
      {
         voice->Solo.Step++;
         voice->Solo.Timer = 5;
      }
   }

   else if (voice->Solo.Step == 2)
   {
      voice->Solo.PinRST = 0;
      voice->Solo.PinDATA = 1;
      if (voice->Solo.Timer == 0)
      {
         voice->Solo.Step++;
         voice->Solo.Timer = 60;
      }
   }

   else if (voice->Solo.Step == 3)
   {
      voice->Solo.PinRST = 1;
      voice->Solo.PinDATA = 1;
      if (voice->Solo.Timer == 0)
      {
         voice->Solo.Step++;
         voice->Solo.Timer = 5;
      }
   }
   else if (voice->Solo.Step == 4)
   {
      voice->Solo.PinRST = 1;
      voice->Solo.PinDATA = 0;
      if (voice->Solo.Timer == 0)
      {
         voice->Solo.Step++;
         if (GetBit(voice->Solo.Cmd, 0))
         {
            voice->Solo.Timer = 3;
         }
         else
         {
            voice->Solo.Timer = 1;
         }
      }
   }

   //BitH
   else if (voice->Solo.Step == 5 ||
            voice->Solo.Step == 7 ||
            voice->Solo.Step == 9 ||
            voice->Solo.Step == 11 ||
            voice->Solo.Step == 13 ||
            voice->Solo.Step == 15 ||
            voice->Solo.Step == 17 ||
            voice->Solo.Step == 19)
   {
      voice->Solo.PinRST = 1;
      voice->Solo.PinDATA = 1;
      if (voice->Solo.Timer == 0)
      {
         voice->Solo.Step++;
         if (GetBit(voice->Solo.Cmd, ((voice->Solo.Step - 5) / 2)))
         {
            voice->Solo.Timer = 1;
         }
         else
         {
            voice->Solo.Timer = 3;
         }
      }

   }
   //Bit0L
   else if (voice->Solo.Step == (2 + 4) ||
            voice->Solo.Step == (2 + 6) ||
            voice->Solo.Step == (2 + 8) ||
            voice->Solo.Step == (2 + 10) ||
            voice->Solo.Step == (2 + 12) ||
            voice->Solo.Step == (2 + 14) ||
            voice->Solo.Step == (2 + 16) ||
            voice->Solo.Step == (2 + 18))
   {
      voice->Solo.PinRST = 1;
      voice->Solo.PinDATA = 0; //
      if (voice->Solo.Timer == 0)
      {
         voice->Solo.Step++;
         if (GetBit(voice->Solo.Cmd, ((voice->Solo.Step - 5) / 2)))
         {
            voice->Solo.Timer = 3;
         }
         else
         {
            voice->Solo.Timer = 1;
         }
      }
   }
   else if (voice->Solo.Step == 21)
   {
      voice->Solo.PinRST = 1;
      voice->Solo.PinDATA = 1; //
      voice->Solo.Timer = 20;
      voice->Solo.Step++;
   }
   else if (voice->Solo.Step == 22)
   {
      voice->Solo.PinRST = 1;
      voice->Solo.PinDATA = 1;
      if (voice->Solo.Timer == 0)
      {
         voice->Solo.Step = 0;
         voice->Solo.Enable = 0;
      }
   }
   else
   {
      voice->Solo.Step = 0;
      voice->Solo.Enable = 0;
   }

}

void FlsVoice(WTV040_CONTROL_DEF *voice, FLS_DEF *Fls)
{
   if (!RunFlag.Solo._1ms)
   {
      return;
   }

   if (voice->Solo.Timer > 0)
   {
      voice->Solo.Timer--;
   }

   {
      if (Fls->Voice.Solo.QingZhanZaiGanYingQu)
      {
         Fls->Voice.Solo.QingZhanZaiGanYingQu = 0;
         voice->Solo.Cmd = 0x00;
         voice->Solo.Enable = 1;
      }
      else if (Fls->Voice.Solo.QingZhuanDongShenTi360Du)
      {
         Fls->Voice.Solo.QingZhuanDongShenTi360Du = 0;
         voice->Solo.Cmd = 0x01;
         voice->Solo.Enable = 1;
      }
      else if (Fls->Voice.Solo.QingBuYaoChuMoKaiGuan)
      {
         Fls->Voice.Solo.QingBuYaoChuMoKaiGuan = 0;
         voice->Solo.Cmd = 0x02;
         voice->Solo.Enable = 1;
      }
      else if (Fls->Voice.Solo.ChuiLinWanBi)
      {
         Fls->Voice.Solo.ChuiLinWanBi = 0;
         voice->Solo.Cmd = 0x03;
         voice->Solo.Enable = 1;
      }
      else if (Fls->Voice.Solo.GongNengZhengChang)
      {
         Fls->Voice.Solo.GongNengZhengChang = 0;
         voice->Solo.Cmd = 0x05;
         voice->Solo.Enable = 1;
      }
      else if (Fls->Voice.Solo.SheBeiGuZhang)
      {
         Fls->Voice.Solo.SheBeiGuZhang = 0;
         voice->Solo.Cmd = 0x06;
         voice->Solo.Enable = 1;
      }

      else if (Fls->Voice.Solo.WelcomeUseCanlend)
      {
         Fls->Voice.Solo.WelcomeUseCanlend = 0;
         voice->Solo.Cmd = 0x07;
         voice->Solo.Enable = 1;
      }
      else if (Fls->Voice.Solo.WelcomeUseJinTian)
      {
         Fls->Voice.Solo.WelcomeUseJinTian = 0;
         voice->Solo.Cmd = 0x08;
         voice->Solo.Enable = 1;
      }
   }

   if (voice->Solo.Enable)
   {
      VoiceDeal(voice);
   }
   VoiceCtrl(voice);

}








