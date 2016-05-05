#include  "includes.h"
#include "FC.h"

FCDataBaseDef FC1;

extern ulong currentSpeedsET;

const FC_PAR_Cfg FCParCfg[FC_SETTING_MAX] =
{


   /*	SetTemp	*/	            	260,	0,	400,	1,
   /*	FanLvlSet	*/	            	0,	0,	9,	1,
   /*	ModeSet	*/	            	0,	0,	9,	1,
   /*	SetTime	*/	                	0,	0,	9999,	1,
   /*	ManualHigh	*/	    	210,	0,	999,	1,
   /*	ManualMed	*/	    	220,	0,	999,	1,
   /*	ManualLow	*/	    	230,	0,	999,	1,
   /*	SetTempMax	*/	            	350,	0,	400,	1,
   /*	SetTempMin	*/	            	50,	0,	400,	1,
   /*	SetFanVoltMax	*/	            	100,	0,	100,	1,
   /*	SetFanVoltMin	*/	            	20,	0,	100,	1,
   /*	TempCtrlDelay	*/		300,	0,	9999,	3,
   /*	FanLvlSwDelay	*/		300,	0,	9999,	3,
   /*	ModeSwDelay	*/	    	300,	0,	9999,	3,
   /*	BackLightDelay	*/	   	1500,	0,	9999,	3,
   /*	AutoHighDiffTemp*/		600,	0,	99,	1,
   /*	AutoMedDiffTemp	*/		300,	0,	99,	1,
   /*	AutoLowDiffTemp	*/		0,	0,	99,	1,

   /*	SolenoidValveMax	*/	    	90,	0,	1000,	1,

   /*	Kp*/		2500,	0,	9999,	2,
   /*	Ki	*/		10,	0,	500,	2,
   /*	Kd	*/		0,	0,	500,	2,
   /*	SampleTime	*/	    	4000,	200,	15000,	3,
   /*	DeadBand	*/	    	5,	0,	100,	1,

};

enum STATE
{
   POWERON,
   POWERONSTAY,
   CLOSEIDLE,
   VALVEDEAL,
   FANDEAL
};
enum STATE systemState;

void delay_nms(uint n)
{
   uint i;
   while (n--) for (i = 0; i < 500; i++) ;
}

void FCInitOne()
{


   delay_nms(1000);

   EeSave1.Solo.BadSave = 0;
   EeReadTrg(&EeSave1);
   EePromDeal(&FC1.Run, sizeof(FC_RUNING_Def) - CRC_LEN, &EeSave1);
   if (EeSave1.Solo.BadSave)
   {
      uint08 tmp;

      uint16 *pdata = (uint16 *)&FC1.Run;
      EeSave1.Solo.BadSave = 0;

      for (tmp = 0; tmp < FC_SETTING_MAX; tmp++)
      {
         pdata[tmp] = FCParCfg[tmp].Default;
      }
   }
   EeWriteTrg(&EeSave1);


   FC1.State.Sys.All = 0;


   PID(&FC1.FCpid, &FC1.Run.FCpidPar);

   FC1.Buff.RoomTempAid = 200;
   FC1.Buff.DiTreat.All = 0;

}
void FCKeyState(FCDataBaseDef *FC)
{
   FC->State.Sys.Solo.Cool = (FC->Run.ModeSet == 0) ? 1 : 0;
   FC->State.Sys.Solo.Hot = (FC->Run.ModeSet == 1) ? 1 : 0;
   FC->State.Sys.Solo.Sleep = (FC->Run.ModeSet == 2) ? 1 : 0;

   FC->State.Sys.Solo.FanLvlAuto = (FC->Run.FanLvlSet == 0) ? 1 : 0;
   FC->State.Sys.Solo.FanLvlLow = (FC->Run.FanLvlSet == 1) ? 1 : 0;
   FC->State.Sys.Solo.FanLvlMed = (FC->Run.FanLvlSet == 2) ? 1 : 0;
   FC->State.Sys.Solo.FanLvlHigh = (FC->Run.FanLvlSet == 3) ? 1 : 0;
}

void FCKeyScan(FCDataBaseDef *FC)
{


   //StartDelay
   if (FC->State.Sys.Solo.Started != FC->Buff.DiTreat.Solo.StartStop)
   {
      FC->Buff.DiTreat.Solo.StartStop = FC->State.Sys.Solo.Started;
      FC->Buff.WorkTimer.ModeSwDelayTimer = FC->Run.ModeSwDelay;
      FC->Buff.WorkTimer.FanLvlDelayTimer = FC->Run.FanLvlSwDelay;
      FC->Buff.WorkTimer.TempCtrlDelayTimer = FC->Run.TempCtrlDelay;
      FC->Buff.WorkTimer.OnOffDelayTimer = 300;
      if (!FC->State.Sys.Solo.Started)
      {
         FC->Buff.WorkTimer.CloseTimer = FC->Run.SolenoidValveMax * 100;
         FC->FCpid.ITerm = 0;
      }
//    else if (StartOne == 1)
//    {
//       FC->Buff.WorkTimer.CloseTimer = 0;
//    }
   }
   //ModeSwDelay
   if (FC->Run.ModeSet != FC->Buff.RunTreat.ModeSet)
   {
      FC->Buff.RunTreat.ModeSet = FC->Run.ModeSet;
      FC->Buff.WorkTimer.ModeSwDelayTimer = FC->Run.ModeSwDelay;
   }
   //FanLvlSwDelay
   if (FC->Run.FanLvlSet != FC->Buff.RunTreat.FanLvlSet)
   {
      FC->Buff.RunTreat.FanLvlSet = FC->Run.FanLvlSet;
      FC->Buff.WorkTimer.FanLvlDelayTimer = FC->Run.FanLvlSwDelay;
   }
   //TempCtrlDelay
   if (FC->Run.SetTemp != FC->Buff.RunTreat.SetTemp)
   {
      FC->Buff.RunTreat.SetTemp = FC->Run.SetTemp;
      FC->Buff.WorkTimer.TempCtrlDelayTimer = FC->Run.TempCtrlDelay;
   }

   //ManualDealH
   if (FC->Buff.DiIn.Solo.ManualHigh &&  !FC->Buff.DiTreat.Solo.ManualHigh)
   {
      FC->Buff.DiTreat.Solo.ManualHigh = 1;
      FC->Run.SetTemp = FC->Run.ManualHigh;
      FC->State.Sys.Solo.Started = 1;
   }
   else if (!FC->Buff.DiIn.Solo.ManualHigh && FC->Buff.DiTreat.Solo.ManualHigh)
   {
      FC->Buff.DiTreat.Solo.ManualHigh = 0;
      if (!FC->Buff.DiIn.Solo.ManualMed && !FC->Buff.DiIn.Solo.ManualLow)
      {
         FC->State.Sys.Solo.Started = 0;
      }
   }
   //ManualDealM
   if (FC->Buff.DiIn.Solo.ManualMed &&  !FC->Buff.DiTreat.Solo.ManualMed)
   {
      FC->Buff.DiTreat.Solo.ManualMed = 1;
      FC->Run.SetTemp = FC->Run.ManualMed;
      FC->State.Sys.Solo.Started = 1;
   }
   else if (!FC->Buff.DiIn.Solo.ManualMed && FC->Buff.DiTreat.Solo.ManualMed)
   {
      FC->Buff.DiTreat.Solo.ManualMed = 0;
      if (!FC->Buff.DiIn.Solo.ManualHigh && !FC->Buff.DiIn.Solo.ManualLow)
      {
         FC->State.Sys.Solo.Started = 0;
      }
   }
   //ManualDealL
   if (FC->Buff.DiIn.Solo.ManualLow &&  !FC->Buff.DiTreat.Solo.ManualLow)
   {
      FC->Buff.DiTreat.Solo.ManualLow = 1;
      FC->Run.SetTemp = FC->Run.ManualLow;
      FC->State.Sys.Solo.Started = 1;
   }
   else if (!FC->Buff.DiIn.Solo.ManualLow && FC->Buff.DiTreat.Solo.ManualLow)
   {
      FC->Buff.DiTreat.Solo.ManualLow = 0;
      if (!FC->Buff.DiIn.Solo.ManualHigh && !FC->Buff.DiIn.Solo.ManualMed)
      {
         FC->State.Sys.Solo.Started = 0;
      }
   }


   FCKeyState(FC);

}

void FCWorkTime(FCDataBaseDef *FC)
{
// RelayFanLvlLow ^= 1;
   if (FC->Buff.WorkTimer.FanLvlDelayTimer > 0)
   {
      FC->Buff.WorkTimer.FanLvlDelayTimer--;
   }
   if (FC->Buff.WorkTimer.TempCtrlDelayTimer > 0)
   {
      FC->Buff.WorkTimer.TempCtrlDelayTimer--;
   }
   if (FC->Buff.WorkTimer.ModeSwDelayTimer > 0)
   {
      FC->Buff.WorkTimer.ModeSwDelayTimer--;
   }
   if (FC->Buff.WorkTimer.TempChangeTimer > 0)
   {
      FC->Buff.WorkTimer.TempChangeTimer--;
   }
   if (UartAppData2.MasterTime > 0)
   {
      UartAppData2.MasterTime--;
   }
   if (EeSave1.Solo.Timer > 0)
   {
      EeSave1.Solo.Timer--;
   }
   if (FC->FCpid.lastTime > 0)
   {
      FC->FCpid.lastTime--;
   }
   if (FC->Buff.WorkTimer.CloseTimer > 0)
   {
      FC->Buff.WorkTimer.CloseTimer--;
   }
   if (FC->Buff.WorkTimer.OpenTimer > 0)
   {
      FC->Buff.WorkTimer.OpenTimer--;
   }
   if (FC->Buff.WorkTimer.OnOffDelayTimer > 0)
   {
      FC->Buff.WorkTimer.OnOffDelayTimer--;
   }
}


uint16 nowSolenoidValve = 0;
void FCRelayOutput(FCDataBaseDef *FC)
{
   if (!FC->State.Sys.Solo.Started)
   {
      FC->State.Sys.Solo.RelayH = 0;
      FC->State.Sys.Solo.RelayM = 0;
      FC->State.Sys.Solo.RelayL = 0;
   }

   if ((FC->State.DI.Solo.Addr & 0x0080) != 0 && FC->State.Sys.Solo.Started)
   {
      RelayFanLvlHigh = 1;
      RelayFanLvlMed = 0;
      RelayFanLvlLow = 0;
   }
   else
   {
      RelayFanLvlHigh = (FC->State.Sys.Solo.RelayH) ? 1 : 0;
      RelayFanLvlMed = (FC->State.Sys.Solo.RelayM) ? 1 : 0;
      RelayFanLvlLow = (FC->State.Sys.Solo.RelayL) ? 1 : 0;
   }

   RelayValveOff = (FC->State.Sys.Solo.FloatRelayOff) ? 1 : 0;
   RelayValveOn = (FC->State.Sys.Solo.FloatRelayOn) ? 1 : 0;

}


uint08 StartOne = 0;
void ResetDeal(FCDataBaseDef *FC)
{
// if (FC->Buff.WorkTimer.CloseTimer > 0 && StartOne == 0)
// {
//    RelayValveOn = 1;
//    RelayValveOff = 0;
//    nowSolenoidValve = FC->Run.SolenoidValveMax;
// }
// else
// {
//    StartOne = 1;
// }
   if (FC->Buff.ResetState != 0)
   {
      FC->Buff.ResetState = 0;
      WDTCR = 0x0F;
   }
}


uint08 speedShakeCnt = 0;
uint16 speedCnt = 0;
BOOL swih;
void TestSpeed()
{

   if (!PINB_PINB0)
   {
      if (speedShakeCnt == 1)
      {
         swih ^= 1;
         PORTB_PORTB4 = swih;
         speedShakeCnt++;
         speedCnt++;
      }
      else if (speedShakeCnt < 10)
      {
         speedShakeCnt++;
      }
   }
   else
   {
      speedShakeCnt = 0;
   }
}


void KeyControl(FCDataBaseDef *FC)
{
   if (!FC->Buff.Flag.solo._20msFlag)
   {
      return;
   }
   if (FC->Buff.WorkTimer.TempCtrlDelayTimer == 0)
   {
      //    FC->FCpid.mySetpoint = FC->Buff.RoomTempAid;
      FC->FCpid.mySetpoint = FC->Run.SetTemp;
   }
   if (FC->Buff.WorkTimer.ModeSwDelayTimer == 0)
   {
      if (FC->State.Sys.Solo.Cool)
      {
         FC->FCpid.Flags.controllerDirection = 1;
      }
      if (FC->State.Sys.Solo.Hot)
      {
         FC->FCpid.Flags.controllerDirection = 0;
      }
   }
}

void FanCompute(FCDataBaseDef *FC)
{
   int tmp = FC->FCpid.myOutput;
   if (!FC->Buff.Flag.solo._20msFlag)
   {
      return;
   }
   if (FC->Buff.WorkTimer.FanLvlDelayTimer == 0)
   {
      if (tmp > 10)
      {
         if (tmp <= 300)
         {
            tmp = 300;
         }
         if (FC->State.Sys.Solo.FanLvlAuto)
         {
            ulong t1 =  tmp;
            ulong t2 = t1 * (FC->Run.SetFanVoltMax - FC->Run.SetFanVoltMin) / 100u + FC->Run.SetFanVoltMin * 10u;
            FC->Buff.AnalogOut01 = (uint16)t2;

//          FC->Buff.AnalogOut01 = tmp  * (FC->Run.SetFanVoltMax - FC->Run.SetFanVoltMin) / 100u + FC->Run.SetFanVoltMin * 10u;
            if (tmp <= FC->Run.AutoMedDiffTemp)
            {
               FC->State.Sys.Solo.RelayL = 1;
               FC->State.Sys.Solo.RelayM = 0;
               FC->State.Sys.Solo.RelayH = 0;
            }
            else if (tmp <= FC->Run.AutoHighDiffTemp)
            {
               FC->State.Sys.Solo.RelayL = 0;
               FC->State.Sys.Solo.RelayM = 1;
               FC->State.Sys.Solo.RelayH = 0;
            }
            else
            {
               FC->State.Sys.Solo.RelayL = 0;
               FC->State.Sys.Solo.RelayM = 0;
               FC->State.Sys.Solo.RelayH = 1;
            }
         }
         else if (FC->State.Sys.Solo.FanLvlHigh)
         {
            ulong t1 = 1000u;
            ulong t2 = t1 * (FC->Run.SetFanVoltMax - FC->Run.SetFanVoltMin) / 100u + FC->Run.SetFanVoltMin * 10u;
            //          FC->Buff.AnalogOut01 = 1000u  * (FC->Run.SetFanVoltMax - FC->Run.SetFanVoltMin) / 100u + FC->Run.SetFanVoltMin * 10u;
            FC->Buff.AnalogOut01 = (uint16)t2;
            FC->State.Sys.Solo.RelayL = 0;
            FC->State.Sys.Solo.RelayM = 0;
            FC->State.Sys.Solo.RelayH = 1;
         }
         else if (FC->State.Sys.Solo.FanLvlMed)
         {
            ulong t1 =  FC->Run.AutoHighDiffTemp;
            ulong t2 = t1 * (FC->Run.SetFanVoltMax - FC->Run.SetFanVoltMin) / 100u + FC->Run.SetFanVoltMin * 10u;
            FC->Buff.AnalogOut01 = (uint16)t2;
            //          FC->Buff.AnalogOut01 = FC->Run.AutoHighDiffTemp  * (FC->Run.SetFanVoltMax - FC->Run.SetFanVoltMin) / 100u + FC->Run.SetFanVoltMin * 10u;
            FC->State.Sys.Solo.RelayL = 0;
            FC->State.Sys.Solo.RelayM = 1;
            FC->State.Sys.Solo.RelayH = 0;
         }
         else if (FC->State.Sys.Solo.FanLvlLow)
         {
            ulong t1 =  FC->Run.AutoMedDiffTemp;
            ulong t2 = t1 * (FC->Run.SetFanVoltMax - FC->Run.SetFanVoltMin) / 100u + FC->Run.SetFanVoltMin * 10u;
            FC->Buff.AnalogOut01 = (uint16)t2;
            //          FC->Buff.AnalogOut01 = FC->Run.AutoMedDiffTemp  * (FC->Run.SetFanVoltMax - FC->Run.SetFanVoltMin) / 100u + FC->Run.SetFanVoltMin * 10u;
            FC->State.Sys.Solo.RelayL = 1;
            FC->State.Sys.Solo.RelayM = 0;
            FC->State.Sys.Solo.RelayH = 0;
         }
         
      }
      else
      {
         FC->Buff.AnalogOut01 = 0;
         FC->State.Sys.Solo.RelayL = 0;
         FC->State.Sys.Solo.RelayM = 0;
         FC->State.Sys.Solo.RelayH = 0;
      }
   }
}

void FloatCompute(FCDataBaseDef *FC)
{
   if (!FC->Buff.Flag.solo._1000msFlag)
   {
      return;
   }
   if (FC->FCpid.myOutput / (1000 / FC->Run.SolenoidValveMax) * 2 > (nowSolenoidValve + 1))
   {
      if (nowSolenoidValve < FC->Run.SolenoidValveMax)
      {
         nowSolenoidValve++;
      }
      FC->State.Sys.Solo.FloatRelayOn = 1;
      FC->State.Sys.Solo.FloatRelayOff = 0;
   }
   else
   {
      if (FC->FCpid.myOutput / (1000 / FC->Run.SolenoidValveMax) * 2 < (nowSolenoidValve - 1))
      {
         if (nowSolenoidValve > 1)
         {
            nowSolenoidValve--;
         }
         FC->State.Sys.Solo.FloatRelayOn = 0;
         FC->State.Sys.Solo.FloatRelayOff = 1;
      }
      else
      {
         FC->State.Sys.Solo.FloatRelayOn = 0;
         FC->State.Sys.Solo.FloatRelayOff = 0;
      }
   }
   FC->Buff.AnalogOut02 = currentSpeedsET * (FC->Run.SetFanVoltMax - FC->Run.SetFanVoltMin) / 100u + FC->Run.SetFanVoltMin * 10u;
// FC->Buff.AnalogOut02 = FC->FCpid.myOutput * 33 / 10;
}

void FloatTimerDeal(FCDataBaseDef *FC)
{
   if (!FC->Buff.Flag.solo._1000msFlag)
   {
      return;
   }
   if (FC->Buff.WorkTimer.OpenTimer > 0)
   {
      if (nowSolenoidValve < FC->Run.SolenoidValveMax)
      {
         nowSolenoidValve++;
      }
      FC->Buff.WorkTimer.CloseTimer = 0;
      FC->State.Sys.Solo.FloatRelayOn = 1;
      FC->State.Sys.Solo.FloatRelayOff = 0;
   }
   else if (FC->Buff.WorkTimer.CloseTimer > 0)
   {
      if (nowSolenoidValve > 0)
      {
         nowSolenoidValve--;
      }
      FC->Buff.WorkTimer.OpenTimer = 0;
      FC->State.Sys.Solo.FloatRelayOn = 0;
      FC->State.Sys.Solo.FloatRelayOff = 1;
   }
   else
   {
      if (systemState == POWERONSTAY)
      {
         systemState = CLOSEIDLE;
      }
      FC->State.Sys.Solo.FloatRelayOn = 0;
      FC->State.Sys.Solo.FloatRelayOff = 0;
   }
}


void FCURun(FCDataBaseDef *FC)
{
   switch (systemState)
   {
   case POWERON:        //上电状态
      {
         FC->State.Sys.Solo.Started = 0;
         FC->State.Sys.Solo.RelayH = 0;
         FC->State.Sys.Solo.RelayM = 0;
         FC->State.Sys.Solo.RelayL = 0;
         FC->State.Sys.Solo.FloatRelayOn = 1;
         FC->State.Sys.Solo.FloatRelayOff = 0;
         FC->Buff.AnalogOut01 = 0;
         FC->Buff.AnalogOut02 = 0;
         FC->FCpid.ITerm = 0;
         FC->Buff.WorkTimer.OpenTimer = FC->Run.SolenoidValveMax * 100;
         FC->Buff.WorkTimer.CloseTimer = 0;
         systemState = POWERONSTAY;
      }
      break;
   case POWERONSTAY:          //上电等待状态
      {
         if (!FC->Buff.Flag.solo._1000msFlag)
         {
            return;
         }
         FC->State.Sys.Solo.RelayH = 0;
         FC->State.Sys.Solo.RelayM = 0;
         FC->State.Sys.Solo.RelayL = 0;
         FC->Buff.AnalogOut01 = 0;
         FC->Buff.AnalogOut02 = 0;
         FC->FCpid.ITerm = 0;
         FloatTimerDeal(FC);
      }
      break;
   case CLOSEIDLE:          //关机空闲状态
      {
         if (FC->Buff.WorkTimer.OnOffDelayTimer > 0)
         {
            return;
         }
         FC->State.Sys.Solo.RelayH = 0;
         FC->State.Sys.Solo.RelayM = 0;
         FC->State.Sys.Solo.RelayL = 0;
         FC->Buff.AnalogOut01 = 0;
         FC->Buff.AnalogOut02 = 0;
         FC->FCpid.ITerm = 0;
         if (FC->State.Sys.Solo.Started)
         {
            systemState = VALVEDEAL;
//          FC->FCpid.myOutput =
         }
         FloatTimerDeal(FC);
      }
      break;
   case VALVEDEAL:
      {
         KeyControl(FC);
         PIDCompute(&FC->FCpid);
         FanCompute(FC);
         FloatCompute(FC);
         if (!FC->State.Sys.Solo.Started)
         {
            systemState = CLOSEIDLE;
            FC->Buff.WorkTimer.OpenTimer = 0;
            FC->Buff.WorkTimer.CloseTimer = FC->Run.SolenoidValveMax * 100;
         }
         else if (FC->FCpid.myOutput > FC->FCpid.outMax * 30 / 100)
         {
            FC->Buff.WorkTimer.OpenTimer =  FC1.Run.SolenoidValveMax * 100;
            systemState = FANDEAL;
         }
      }
      break;
   case FANDEAL:
      {
         KeyControl(FC);
         PIDCompute(&FC->FCpid);
         if (!FC->State.Sys.Solo.Started)
         {
            systemState = CLOSEIDLE;
            FC->Buff.WorkTimer.OpenTimer = 0;
            FC->Buff.WorkTimer.CloseTimer = FC->Run.SolenoidValveMax * 100;
         }
         if (FC->FCpid.myOutput <= FC->FCpid.outMax * 30 / 100)
         {
            FC->Buff.WorkTimer.OpenTimer =  0;
            systemState = VALVEDEAL;
         }

         FloatTimerDeal(FC);
         FanCompute(FC);
      }
      break;
   }
}

