

#include "includes.h"


FLS_DEF FLS1;




void StatusDeal(FLS_DEF *Fls)
{
   Fls->Output.Solo.Outdoor = 0;   //1:door open 0:door Close
   Fls->Output.Solo.Indoor = 0;
   Fls->Output.Solo.WorkLed = 0;
   Fls->Output.Solo.Light = 0;
   Fls->Output.Solo.Fan = 0;
//----------------¿ÕÏÐ×´Ì¬-------------------
   if (Fls->Status.Solo.Idle)
   {
      if (Fls->Input.Solo.OutsideMagnet)
      {
         Fls->Status.Solo.EnterFls = 1;
         Fls->Status.Solo.Idle = 0;
         Fls->Status.Solo.Step = 0;
      }
      else if (Fls->Input.Solo.InsideMagnet)
      {
         Fls->Status.Solo.LeaveFls = 1;
         Fls->Status.Solo.Idle = 0;
         Fls->Status.Solo.Step = 0;
      }
   }
//-------------½øÈë·çÁÜÊÒ×´Ì¬--------------------
   else if (Fls->Status.Solo.EnterFls)
   {
       FlsEntering(Fls);
   }
//-------------Àë¿ª·çÁÜÊÒ×´Ì¬--------------------
   else if (Fls->Status.Solo.LeaveFls)
   {
       FlsLeaving(Fls);
   }
   else
   {
         Fls->Status.Solo.Idle = 1;
   }
//---------------Ó¦¼±×´Ì¬-----------------------
   if (Fls->Status.Solo.Emc)
   {
      Fls->Status.Solo.Idle = 0;
      Fls->Output.Solo.Outdoor = 0;   //1:door open 0:door Close
      Fls->Output.Solo.Indoor = 0;
      Fls->Output.Solo.WorkLed = 0;
      Fls->Output.Solo.Light = 1;
      Fls->FOutput.Solo.Fan = 0;
   }
// ---------------Ç¿ÖÆ×´Ì¬---------------------
   if (Fls->FOutput.Solo.Fan)
   {
      Fls->Output.Solo.Fan = 1;
      Fls->Output.Solo.WorkLed = 1;
   }
   if (Fls->FOutput.Solo.Light)
   {
      Fls->Output.Solo.Light = 1;
      Fls->Output.Solo.WorkLed = 1;
   }
}

/*********************************************************/
void FlsEntering(FLS_DEF *Fls)
{
//---------------------------------------------------------0
   if (Fls->Status.Solo.Step == 0)
   {
      Fls->Status.Solo.Step++;
      Fls->Time.WorkTimer = __20_000ms;  //
   }
//-----------------------------------------------
   else if (Fls->Status.Solo.Step == 1)
   {
      Fls->Output.Solo.Indoor = 1;
      Fls->Output.Solo.WorkLed = 1;
      Fls->Output.Solo.Light = 1;
      if (!Fls->Input.Solo.OutsideMagnet) //if door closed
      {
         Fls->Status.Solo.Step++;
         Fls->Voice.Solo.QingZhanZaiGanYingQu = 1;
         Fls->Time.WorkTimer = __10_000ms;  //
      }
      //TimeOut Go back to idle
      if (Fls->Time.WorkTimer == 0)
      {
         Fls->Status.Solo.Idle = 1;
         Fls->Status.Solo.EnterFls = 0;
         Fls->Status.Solo.Step = 0;
      }
   }
//---------------------------------------------
   else if (Fls->Status.Solo.Step == 2)
   {
      Fls->Output.Solo.Indoor = 1;
      Fls->Output.Solo.WorkLed = 1;
      Fls->Output.Solo.Light = 1;
      if (Fls->Input.Solo.Infrared)
      {
         Fls->Status.Solo.Step++;
         Fls->Output.Solo.Outdoor = 1;
         Fls->Output.Solo.Indoor = 1;
         Fls->Voice.Solo.QingZhuanDongShenTi360Du = 1;
         Fls->Time.secWorkTimer = Fls->Par.FanRunningTime;
      }
      //TimeOut Go back to idle
      if (Fls->Time.WorkTimer == 0)
      {
         Fls->Status.Solo.Idle = 1;
         Fls->Status.Solo.EnterFls = 0;
         Fls->Status.Solo.Step = 0;
      }
   }
   else if (Fls->Status.Solo.Step == 3)
   {
      //·çÁÜÖÐ
      Fls->Output.Solo.WorkLed = 1;
      Fls->Output.Solo.Light = 1;
      Fls->Output.Solo.Outdoor = 1;
      Fls->Output.Solo.Indoor = 1;
      Fls->Output.Solo.Fan = 1;
      if (Fls->Time.secWorkTimer == 0)
      {
         Fls->Status.Solo.Step++;
         Fls->Voice.Solo.ChuiLinWanBi = 1;
         Fls->Time.WorkTimer = __10_000ms;  //
      }
      //²»ÒªËæ±ã´¥Ãþ
      if (Fls->KeyTreated.Solo.KeyFan   || 
	  Fls->KeyTreated.Solo.KeyLight ||
	  Fls->KeyTreated.Solo.KeyAdd   || 
	  Fls->KeyTreated.Solo.KeySub)
      {
	  Fls->KeyTreated.Solo.KeyFan = 0; 
	  Fls->KeyTreated.Solo.KeyLight = 0;
	  Fls->KeyTreated.Solo.KeyAdd = 0;
	  Fls->KeyTreated.Solo.KeySub = 0;
	  Fls->Voice.Solo.QingBuYaoChuMoKaiGuan = 1;
      }   
   }
   else if (Fls->Status.Solo.Step == 4)
   {
      //·çÁÜ½áÊø
      Fls->Output.Solo.Indoor = 0;
      Fls->Output.Solo.Outdoor = 0;
      Fls->Output.Solo.WorkLed = 1;
      Fls->Output.Solo.Light = 1;
      Fls->Output.Solo.Fan = 0;

      if (Fls->Input.Solo.OutsideMagnet)
      {
         Fls->Status.Solo.Step++;
         Fls->Output.Solo.Indoor = 1;
         Fls->Time.WorkTimer = __20_000ms; //
      }
      if (Fls->Input.Solo.InsideMagnet)
      {
         Fls->Status.Solo.Step++;
         Fls->Output.Solo.Outdoor = 1;
         Fls->Time.WorkTimer = __20_000ms; //
      }
      //TimeOut Go back to idle
      if (Fls->Time.WorkTimer == 0)
      {
         Fls->Status.Solo.Idle = 1;
         Fls->Status.Solo.EnterFls = 0;
         Fls->Status.Solo.Step = 0;
      }
   }
   else if (Fls->Status.Solo.Step == 5)
   {
      //TimeOut Go back to idle
      if (Fls->Time.WorkTimer == 0)
      {
         Fls->Status.Solo.Idle = 1;
         Fls->Status.Solo.EnterFls = 0;
         Fls->Status.Solo.Step = 0;
      }
      if (!Fls->Input.Solo.InsideMagnet && !Fls->Input.Solo.OutsideMagnet)
      {
         Fls->Status.Solo.Idle = 1;
         Fls->Status.Solo.EnterFls = 0;
         Fls->Status.Solo.Step = 0;
      }
   }
}

void FlsLeaving(FLS_DEF *Fls)
{
   if (Fls->Status.Solo.Step == 0)
   {
      Fls->Status.Solo.Step++;
      Fls->Time.WorkTimer = __20_000ms;  //
   }
//---------------------------------------
   else if (Fls->Status.Solo.Step == 1)
   {
      Fls->Output.Solo.Outdoor = 1;
      Fls->Output.Solo.WorkLed = 1;
      Fls->Output.Solo.Light = 1;
      if (!Fls->Input.Solo.InsideMagnet)
      {

         Fls->Status.Solo.Step++;
         Fls->Output.Solo.Indoor = 0;
         Fls->Output.Solo.Outdoor = 0;
         Fls->Output.Solo.Light = 1;
         Fls->Output.Solo.WorkLed = 1;
         Fls->Time.WorkTimer = __10_000ms;  //
      }
      //TimeOut Go back to idle
      if (Fls->Time.WorkTimer == 0)
      {
         Fls->Status.Solo.Idle = 1;
         Fls->Status.Solo.LeaveFls = 0;
         Fls->Status.Solo.Step = 0;
      }
   }
   else if (Fls->Status.Solo.Step == 2)
   {
      Fls->Output.Solo.Outdoor = 1;
      Fls->Output.Solo.WorkLed = 1;
      Fls->Output.Solo.Light = 1;
      if (Fls->Input.Solo.Infrared)
      {
         if (Fls->Input.Solo.OutsideMagnet)
         {
            Fls->Output.Solo.Indoor = 1;
            Fls->Time.WorkTimer = __10_000ms;
            Fls->Status.Solo.Step++;
         }
         if (Fls->Input.Solo.InsideMagnet)
         {
            Fls->Output.Solo.Outdoor = 1;
            Fls->Time.WorkTimer = __10_000ms;
            Fls->Status.Solo.Step++;
         }
      }
      //TimeOut Go back to idle
      if (Fls->Time.WorkTimer == 0)
      {
         Fls->Status.Solo.Idle = 1;
         Fls->Status.Solo.LeaveFls = 0;
         Fls->Status.Solo.Step = 0;
      }
   }
   else if (Fls->Status.Solo.Step == 3)
   {
      if (!Fls->Input.Solo.InsideMagnet && !Fls->Input.Solo.OutsideMagnet)
      {
         if (!Fls->Input.Solo.Infrared)
         {
            Fls->Status.Solo.Idle = 1;
            Fls->Status.Solo.LeaveFls = 0;
            Fls->Status.Solo.Step = 0;
         }
         else
         {
            Fls->Status.Solo.EnterFls = 1;
            Fls->Status.Solo.LeaveFls = 0;
            Fls->Status.Solo.Step = 0;
         }
      }
   }
}

void FlsStartVoice(FLS_DEF *Fls)
{
   if (RunFlag.Solo._1000ms)
   {
      if (Fls->Time.VoiceDelay > 0)
      {
	 Fls->Time.VoiceDelay--;
      }
   }
   Fls->Time.VoiceDelay = 5;
   if (Fls->Time.VoiceDelay == 0)
   {
      Fls->Voice.Solo.WelcomeUseCanlend = 1;
   }
   if (Fls->Input.Solo.TestFan || Fls->Input.Solo.TestIndoor ||
       Fls->Input.Solo.TestLight || Fls->Input.Solo.TestOutdoor != 0)
   {
      Fls->Voice.Solo.GongNengZhengChang = 1;
   }


}
void FlsTimeDeal(FLS_DEF *FLS)
{
   if (RunFlag.Solo._10ms)
   {
      if (FLS->Time.WorkTimer > 0)
      {
         FLS->Time.WorkTimer--;
      }
   }
   if (RunFlag.Solo._1000ms)
   {
      if (FLS->Time.secWorkTimer > 0)
      {
         FLS->Time.secWorkTimer--;
      }
   }

}

void FlsDealAll(FLS_DEF *FLS)
{
   KeyDeal(FLS);
   FlsTimeDeal(FLS);
   if (RunFlag.Solo._10ms)
   {
       StatusDeal(FLS);
       FlsCtrlOutput(FLS);
   }
}
