
#include  "includes.h"

YYJ_ALL_DEF YYJ1;
uint16 SetTemp;
uint16 SetRH;
uint16 NowTemp;
uint16 NowRH;
uint16 NowPress;
uint16 PreTemp;

uint16 TestMe_1;
uint16 TestMe_2;
uint16 TestMe_3;
uint16 TestMe_4;
uint16 TestMe_5;
uint16 TestMe_6;
uint16 TestMe_7;
uint16 TestMe_8;

void YYJ_BaudStopParityInit(YYJ_ALL_DEF *yyj)
{
   if (yyj->DI.Solo.SEL_MODE_SPARE_01 || POL_DI_Block.Solo.SEL_MODE_SPARE_01)
   {
      yyj->OP.BaudSet.COM2 = 4800;
      yyj->OP.BaudSet.COM3 = 9600;
      yyj->OP.BaudSet.COM4 = 9600;
      yyj->OP.StopBitSet.COM2 = 0x0000;
      yyj->OP.StopBitSet.COM3 = 0x0000;
      yyj->OP.StopBitSet.COM4 = 0x0000;
      yyj->OP.ParitySet.COM2 =  0x0000;
      yyj->OP.ParitySet.COM3 =  0x0000;
      yyj->OP.ParitySet.COM4 =  0x0000;
   }
}

void YYJ_Buff_1Set()
{
   YYJ1.DI = POL_DI_Block;
   YYJ1.AI = POL_AI_Block;
   Relays =  YYJ1.DO.Relay;
   Lamps =   YYJ1.DO.Light;
   POL_AO_Block = YYJ1.AO;
}

void YYJ_Buff_2Set()
{
   YYJ1.PID.Coolpid.kp = YYJ1.OP.Coolpid.Kp;
   YYJ1.PID.Coolpid.ki = YYJ1.OP.Coolpid.Ki;
   YYJ1.PID.Coolpid.kd = YYJ1.OP.Coolpid.Kd;
   YYJ1.PID.Coolpid.SampleTime = YYJ1.OP.Coolpid.SampleTime;
   YYJ1.PID.Coolpid.DeadBand = YYJ1.OP.Coolpid.DeadBand;
   YYJ1.PID.Hotpid.kp = YYJ1.OP.Hotpid.Kp;
   YYJ1.PID.Hotpid.ki = YYJ1.OP.Hotpid.Ki;
   YYJ1.PID.Hotpid.kd = YYJ1.OP.Hotpid.Kd;
   YYJ1.PID.Hotpid.SampleTime = YYJ1.OP.Hotpid.SampleTime;
   YYJ1.PID.Hotpid.DeadBand = YYJ1.OP.Hotpid.DeadBand;
   YYJ1.PID.RHpid.kp = YYJ1.OP.RHpid.Kp;
   YYJ1.PID.RHpid.ki = YYJ1.OP.RHpid.Ki;
   YYJ1.PID.RHpid.kd = YYJ1.OP.RHpid.Kd;
   YYJ1.PID.RHpid.SampleTime = YYJ1.OP.RHpid.SampleTime;
   YYJ1.PID.RHpid.DeadBand = YYJ1.OP.RHpid.DeadBand;
   YYJ1.PID.RHpidInv.kp = YYJ1.OP.RHpidInv.Kp;
   YYJ1.PID.RHpidInv.ki = YYJ1.OP.RHpidInv.Ki;
   YYJ1.PID.RHpidInv.kd = YYJ1.OP.RHpidInv.Kd;
   YYJ1.PID.RHpidInv.SampleTime = YYJ1.OP.RHpidInv.SampleTime;
   YYJ1.PID.RHpidInv.DeadBand = YYJ1.OP.RHpidInv.DeadBand;
   YYJ1.PID.Freqpid.kp = YYJ1.OP.Freqpid.Kp;
   YYJ1.PID.Freqpid.ki = YYJ1.OP.Freqpid.Ki;
   YYJ1.PID.Freqpid.kd = YYJ1.OP.Freqpid.Kd;
   YYJ1.PID.Freqpid.SampleTime = YYJ1.OP.Freqpid.SampleTime;
   YYJ1.PID.Freqpid.DeadBand = YYJ1.OP.Freqpid.DeadBand;
}

void YYJ_Buff_SetTimeSize(YYJ_ALL_DEF *yyj)
{
   yyj->OP.SetSize.StartupTimer = _30SEC;
   yyj->OP.SetSize.ShaJunDengTimer = _30MIN;
   yyj->OP.SetSize.NoWindTime = _60SEC;
   yyj->OP.SetSize.NgtPressTime = _10SEC;
   yyj->OP.SetSize.ColdProtectTime = _3MIN;
   yyj->OP.SetSize.StopOffTime = _3MIN;
   yyj->OP.SetSize.StopCntTime = _2HOUR;
   yyj->OP.SetSize.StopDelayTime = _5SEC;
   yyj->OP.SetSize.CloseColdTime = _10MIN;
   yyj->OP.SetSize.OpenColdTime = _3MIN;
   yyj->OP.SetSize.StarTime = 0;

   yyj->OP.SysPar.AirPress = 500;
   yyj->OP.SysPar.PreHotStart = 3;
   yyj->OP.SysPar.PreHotEnd = 10;

   YYJ1.OP.SysPar.SaveBit.Solo.MCU1_PLC0 = 0;
   YYJ1.OP.My485Addr = 33;
   yyj->OP.SmallAddr = 0;

   yyj->OP.SysPar.TmepRange = 50;
   yyj->OP.SysPar.RhRange = 100;
   yyj->OP.SysPar.PreHeatRange = 20;
   yyj->OP.SysPar.PressRange = 500;

   yyj->PanelLogic.TempSet = 25;
   yyj->PanelLogic.RhSet = 50;
   yyj->Panel[0].TempSet = 25;
   yyj->Panel[0].RhSet = 50;
   yyj->Panel[1].TempSet = 25;
   yyj->Panel[1].RhSet = 50;
   yyj->Panel[2].TempSet = 25;
   yyj->Panel[2].RhSet = 50;

   yyj->OP.BaudSet.COM2 = 4800;
   yyj->OP.BaudSet.COM3 = 9600;
   yyj->OP.BaudSet.COM4 = 9600;
   yyj->OP.StopBitSet.COM2 = 0x0000;
   yyj->OP.StopBitSet.COM3 = 0x0000;
   yyj->OP.StopBitSet.COM4 = 0x0000;
   yyj->OP.ParitySet.COM2 =  0x0000;
   yyj->OP.ParitySet.COM3 =  0x0000;
   yyj->OP.ParitySet.COM4 =  0x0000;

   yyj->OP.Check.AIadjust.All[0] = 10000;
   yyj->OP.Check.AIadjust.All[1] = 10000;
   yyj->OP.Check.AIadjust.All[2] = 10000;
   yyj->OP.Check.AIadjust.All[3] = 10000;
   yyj->OP.Check.AIadjust.All[4] = 10000;
   yyj->OP.Check.AIadjust.All[5] = 10000;
   yyj->OP.Check.AIadjust.All[6] = 10000;
   yyj->OP.Check.AOadjust.All[0] = 10000;
   yyj->OP.Check.AOadjust.All[1] = 10000;
   yyj->OP.Check.AOadjust.All[2] = 10000;
   yyj->OP.Check.AOadjust.All[3] = 10000;
   yyj->OP.Check.AOadjust.All[4] = 10000;
   yyj->OP.Check.AOadjust.All[5] = 10000;
   yyj->OP.Check.AOadjust.All[6] = 10000;
   yyj->OP.Check.AOadjust.All[7] = 10000;

   yyj->OP.SysPar.SaveBit.Solo.MCU1_PLC0 = 0;
   yyj->OP.COM4Shield = 0;
   yyj->OP.COM2poll = 1;
}
/**判断下一步是否到运行状态**/
void SysToRun(YYJ_ALL_DEF *yyj)
{
   if (yyj->Small.Solo.LocalPower || yyj->DI.Solo.BOX_PANEL_KEY_RUN) //小控制面板的本地开机 硬接线的本地开机
   {
      yyj->toStatus.Solo.toRuning = 1;
   }
   else if (yyj->Small.Solo.RemotePower || yyj->DI.Solo.BOX_PANEL_KEY_REMOTE_RUN) //小控制面板的远程开机 硬接线的远程开机
   {
      yyj->toStatus.Solo.toRuning = 0;
#define _______________________ExtendPanel
      if (yyj->PanelLogic.Key.Solo.KeyStart) //情报面板的开机
      {
         yyj->toStatus.Solo.toRuning = 1;
      }
      else if (yyj->DI.Solo.PANEL_KEY_RUN)
      {
         yyj->toStatus.Solo.toRuning = 1;
      }
   }
   else
   {
      yyj->toStatus.Solo.toRuning = 0;
   }
}
/**判断下一步是否到值机状态**/
void SysToStandby(YYJ_ALL_DEF *yyj)
{
   if (yyj->Small.Solo.LocalStandby || yyj->DI.Solo.BOX_PANEL_KEY_STANDBY) //小控制面板的本地值机 硬接线的本地值机
   {
      yyj->toStatus.Solo.toStandby = 1;
   }
   else if (yyj->Small.Solo.RemoteStandby || yyj->DI.Solo.BOX_PANEL_KEY_REMOTE_STANDBY) //小控制面板的远程值机 硬接线的远程值机
   {
      yyj->toStatus.Solo.toStandby = 0;
#define _______________________ExtendPanel
      if (yyj->PanelLogic.Key.Solo.KeyStandby) //情报面板的值机
      {
         yyj->toStatus.Solo.toStandby = 1;
      }
      else if (yyj->DI.Solo.PANEL_KEY_STANDBY)
      {
         yyj->toStatus.Solo.toStandby = 1;
      }
   }
   else
   {
      yyj->toStatus.Solo.toStandby = 0;
   }
}
/**判断下一步是否到故障状态**/
void SysToError(YYJ_ALL_DEF *yyj)
{
   if (!yyj->DI.Solo.INPUT_EMC || !yyj->DI.Solo.BOX_PANEL_KEY_EMC_STOP || !yyj->DI.Solo.INPUT_FIRE_EMC) //外急停 门板急停 消防
   {
      yyj->toStatus.Solo.toError = 1;
   }
   else if (yyj->DI.Solo.FC_FEEDBACK_ERROR || yyj->DI.Solo.FF_FEEDBACK_ERR) //变频故障 定频故障
   {
      yyj->toStatus.Solo.toError = 1;
   }
   else
   {
      yyj->toStatus.Solo.toError = 0;
   }
}
/**风机启动60秒后,时间可设置,判断是否仍然缺风**/
void SysToNowind(YYJ_ALL_DEF *yyj)
{
   if (!yyj->DI.Solo.INPUT_NO_WIND && yyj->Flag.Solo.BlowerRunning) //缺风
   {
      yyj->Flag.Solo.NowindFlag = 0;
      if (yyj->Time.NoWindTime == 0)
      {
         yyj->Flag.Solo.NowindFlag = 1;
      }
   }
   else
   {
      yyj->Time.NoWindTime = yyj->OP.SetSize.NoWindTime; //缺风1分钟
      yyj->Flag.Solo.NowindFlag = 0;
   }
}
/**风机启动后,判断防冻时间是否达到3分钟,时间可设置,是否进入防冻停机**/
void SysToColdStop(YYJ_ALL_DEF *yyj)
{
   if (yyj->DI.Solo.INPUT_COLD_PROTECT && yyj->Flag.Solo.BlowerRunning) //防冻停机
   {
      yyj->toStatus.Solo.toColdStop = 0;
      if (yyj->Time.ColdProtectTime == 0)
      {
         yyj->toStatus.Solo.toColdStop = 1;
      }
   }
   else
   {
      yyj->Time.ColdProtectTime = yyj->OP.SetSize.ColdProtectTime; //风机运行3分钟后仍然有防冻进入停机
      yyj->toStatus.Solo.toColdStop = 0;
   }
}
/**风机启动后,判断是否关机,延时3分钟后进入停机,时间可设置**/
void SysToOffStop(YYJ_ALL_DEF *yyj)
{
   if (!yyj->toStatus.Solo.toRuning && yyj->Flag.Solo.BlowerRunning) //运行状态下关机进入停机
   {
      yyj->toStatus.Solo.toOffStop = 0;
      if (yyj->Time.StopOffTime == 0)
      {
         yyj->toStatus.Solo.toOffStop = 1;
      }
   }
   else
   {
      yyj->toStatus.Solo.toOffStop = 0;
      yyj->Time.StopOffTime = yyj->OP.SetSize.StopOffTime; //延时3分钟后进入停机
   }
}
/**判断是否在停机或者故障重新启动进入初始状态**/
void SysToInit(YYJ_ALL_DEF *yyj)
{
   if (!yyj->toStatus.Solo.toRuning && yyj->Status.Solo.Error) //急停时按下关机进入初始
   {
//    if (!yyj->toStatus.Solo.toError)
//    {
         yyj->toStatus.Solo.toInit = 1;
//    }
   }
   else if (!yyj->toStatus.Solo.toRuning && yyj->Status.Solo.Stop)
   {
      yyj->toStatus.Solo.toInit = 1;
   }
   else
   {
      yyj->toStatus.Solo.toInit = 0;
   }
}

void YYJ_StatusToChange(YYJ_ALL_DEF *yyj)
{
   SysToRun(yyj);
   SysToStandby(yyj);
   SysToError(yyj);
   SysToColdStop(yyj);
   SysToOffStop(yyj);
   SysToNowind(yyj);
   SysToInit(yyj);
}

#define ______________________________________________________________________________________

/**初始化进入运行时的启动时间,时间可设置**/
void YYJ_Init_DealyTime(YYJ_ALL_DEF *yyj)
{
   if (yyj->Status.Solo.Runing)
   {
      return;
   }
   yyj->Time.StartupTimer = yyj->OP.SetSize.StartupTimer;
}
/**正常关机停机及防冻停机的延时关闭时间,时间可设置**/
void YYJ_Stop_DelayTime(YYJ_ALL_DEF *yyj)
{
   if (yyj->Status.Solo.Stop)
   {
      return;
   }
   yyj->Time.StopDelayTime = yyj->OP.SetSize.StopDelayTime;
}

/**停机状态下开杀菌灯30分钟,时间可设置,以及停机时间计时**/
void YYJ_Stop_ShaJunDeng(YYJ_ALL_DEF *yyj)
{
   if (yyj->Status.Solo.Stop && yyj->Flag.Solo.StopTimeFlag)
   {
      yyj->DO.Relay.Solo.SHA_JUN_DENG = 1;
      if (yyj->Time.ShaJunDengTimer == 0)
      {
         yyj->DO.Relay.Solo.SHA_JUN_DENG = 0;
         yyj->Flag.Solo.StopTimeFlag = 0;
      }
   }
   else
   {
      yyj->DO.Relay.Solo.SHA_JUN_DENG = 0;
      yyj->Time.ShaJunDengTimer = yyj->OP.SetSize.ShaJunDengTimer;
   }
}
/**停机状态下计时**/
void YYJ_Stop_CntTime(YYJ_ALL_DEF *yyj)
{
   if (yyj->Status.Solo.Stop && !yyj->Flag.Solo.StopTimeFlag)
   {
      if (yyj->Time.StopCntTime == 0)
      {
         yyj->Flag.Solo.StopTimeFlag = 1;
         yyj->Time.StopCntTime = yyj->OP.SetSize.StopCntTime;
      }
   }
   else
   {
      yyj->Time.StopCntTime = yyj->OP.SetSize.StopCntTime;
   }
}
/**防冻停机时,开停机保温**/
void YYJ_Stop_BaoWen(YYJ_ALL_DEF *yyj)
{
   if (yyj->Status.Solo.Stop && yyj->Flag.Solo.ColdStopFlag)
   {
      yyj->DO.Relay.Solo.STOP_WARMING = 1;
   }
   else
   {
      yyj->DO.Relay.Solo.STOP_WARMING = 0;
   }
}
/**在故障状态下,开故障连锁**/
void  YYJ_Err_ErrorChain(YYJ_ALL_DEF *yyj) //故障连锁
{
   if (yyj->Status.Solo.Error)
   {
      yyj->DO.Relay.Solo.NO_WIND_CHAIN = 1;
   }
   else
   {
      yyj->DO.Relay.Solo.NO_WIND_CHAIN = 0;
   }
}
/**判断冬季还是夏季**/
void YYJ_Stop_Sum0Win1(YYJ_ALL_DEF *yyj)
{
   if (!yyj->DI.Solo.SEL_SEASON_WINTER && !yyj->DI.Solo.SEL_SEASON_SUMMER)
   {
      if (yyj->DI.Solo.INPUT_WATER_SENSOR)
      {
         yyj->Flag.Solo.Sum0Win1 = 1;
      }
      else
      {
         yyj->Flag.Solo.Sum0Win1 = 0;
      }
   }
   else if (yyj->DI.Solo.SEL_SEASON_WINTER)
   {
      yyj->Flag.Solo.Sum0Win1 = 1;
   }
   else
   {
      yyj->Flag.Solo.Sum0Win1 = 0;
   }

}
/**在运行缺风状态下,判断是否开启高温连锁**/
void YYJ_Run_HighTmepChain(YYJ_ALL_DEF *yyj) //高温连锁
{
   if (yyj->Flag.Solo.BlowerRunning && yyj->Flag.Solo.NowindFlag)
   {
      yyj->DO.Relay.Solo.HIGH_TEMP_CHAIN = 0;
      if (yyj->DI.Solo.INPUT_HEAT_HIGH_TEMP || yyj->DI.Solo.INPUT_PRE_HEAT_HIGH_TEMP)
      {
         yyj->DO.Relay.Solo.HIGH_TEMP_CHAIN = 1;
      }
   }
   else
   {
      yyj->DO.Relay.Solo.HIGH_TEMP_CHAIN = 0;
   }
}
/**运行状态下判断是否开启负压,停止时延时关闭,时间可设置**/
void YYJ_Run_NgtPress(YYJ_ALL_DEF *yyj)
{
#define _______________________ExtendPanel
   if (yyj->Flag.Solo.BlowerRunning && (yyj->PanelLogic.Key.Solo.KeyNgt || yyj->DI.Solo.PANEL_KEY_NGT)) //情报面板的负压按键
   {
      yyj->DO.Relay.Solo.NGT_PRESS = 1; //负压排风
      if (yyj->Time.NgtPressTime == 0)
      {
         yyj->DO.Relay.Solo.NGT_PRESS = 0;
      }
   }
   else
   {
      yyj->DO.Relay.Solo.NGT_PRESS = 0;
      yyj->Time.NgtPressTime = yyj->OP.SetSize.NgtPressTime; //负压排风延时关闭
   }
}
/**在运行状态下,开散热风扇**/
void YYJ_Run_FanRadiating(YYJ_ALL_DEF *yyj)
{
   if (yyj->Flag.Solo.BlowerRunning)
   {
      yyj->DO.Relay.Solo.FAN_COOLER = 1; //送风机散热风扇
      yyj->DO.Relay.Solo.BOX_COOLER = 1; //电柜自用散热风扇
   }
   else
   {
      yyj->DO.Relay.Solo.FAN_COOLER = 0;
      yyj->DO.Relay.Solo.BOX_COOLER = 0;
   }
}
/**在运行状态下,判断是否开启排风自动门**/
void YYJ_Run_ExhaustFan(YYJ_ALL_DEF *yyj)
{
   if (yyj->Status.Solo.Runing && yyj->Flag.Solo.BlowerRunning)
   {
      yyj->DO.Relay.Solo.AUTO_GATES_01 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_02 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_03 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_04 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_05 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_06 = 0;
      if (yyj->DI.Solo.INPUT_WIND_GATE_01) // #1
      {
         yyj->DO.Relay.Solo.AUTO_GATES_01 = 1;
      }
      if (yyj->DI.Solo.INPUT_WIND_GATE_02) // #2
      {
         yyj->DO.Relay.Solo.AUTO_GATES_02 = 1;
      }
      if (yyj->DI.Solo.INPUT_WIND_GATE_03) // #3
      {
         yyj->DO.Relay.Solo.AUTO_GATES_03 = 1;
      }
      if (yyj->DI.Solo.INPUT_WIND_GATE_04) // #4
      {
         yyj->DO.Relay.Solo.AUTO_GATES_04 = 1;
      }
      if (yyj->DI.Solo.INPUT_WIND_GATE_05) // #5
      {
         yyj->DO.Relay.Solo.AUTO_GATES_05 = 1;
      }
      if (yyj->DI.Solo.INPUT_WIND_GATE_06) // #6
      {
         yyj->DO.Relay.Solo.AUTO_GATES_06 = 1;
      }
   }
   else
   {
      yyj->DO.Relay.Solo.AUTO_GATES_01 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_02 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_03 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_04 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_05 = 0;
      yyj->DO.Relay.Solo.AUTO_GATES_06 = 0;
   }
}
/**在运行不缺风状态下,判断是否开启电加热**/
void YYJ_Run_HeatDeal(YYJ_ALL_DEF *yyj)
{
   if (!yyj->Flag.Solo.NowindFlag && yyj->Flag.Solo.BlowerRunning)
   {
      if (SetTemp * 10 < NowTemp)
      {
         return;
      }
      uint16 tmp = SetTemp * 10 - NowTemp;
      tmp = tmp / 15; //1.5℃ 3℃ 6℃
      if (tmp > 7) //分为三级 0b0000 0111
      {
         tmp = 7;
      }
      yyj->DO.Relay.Solo.EHEAT_LV01 = 0;   //一级再热
      yyj->DO.Relay.Solo.EHEAT_LV02 = 0;   //二级再热
      yyj->DO.Relay.Solo.EHEAT_LV03 = 0;   //三级再热
      if (testbit(tmp, 0))
      {
         yyj->DO.Relay.Solo.EHEAT_LV01 = 1;
      }
      if (testbit(tmp, 1))
      {
         yyj->DO.Relay.Solo.EHEAT_LV02 = 1;
      }
      if (testbit(tmp, 2))
      {
         yyj->DO.Relay.Solo.EHEAT_LV03 = 1;
      }
   }
   else
   {
      yyj->DO.Relay.Solo.EHEAT_LV01 = 0;
      yyj->DO.Relay.Solo.EHEAT_LV02 = 0;
      yyj->DO.Relay.Solo.EHEAT_LV03 = 0;
   }
}
/**在运行不缺风状态下,判断是否开启电预热**/
void YYJ_Run_PreheatDeal(YYJ_ALL_DEF *yyj)
{
   if (!yyj->Flag.Solo.NowindFlag && yyj->Flag.Solo.BlowerRunning)
   {
//    if (!yyj->Flag.Solo.Sum0Win1)
//    {
//       return;
//    }
      if (PreTemp < SetPreStart * 10)
      {
         uint16 tmp = SetPreEnd * 10 - PreTemp;
         tmp = tmp / 10; //1℃ 2℃ 4℃
         if (tmp > 7)
         {
            tmp = 7;
         }
         yyj->DO.Relay.Solo.REHEAT_LV01 = 0;   //一级预热
         yyj->DO.Relay.Solo.REHEAT_LV02 = 0;   //二级预热
         yyj->DO.Relay.Solo.REHEAT_LV03 = 0;   //三级预热
         if (testbit(tmp, 0))
         {
            yyj->DO.Relay.Solo.REHEAT_LV01 = 1;
         }
         if (testbit(tmp, 1))
         {
            yyj->DO.Relay.Solo.REHEAT_LV02 = 1;
         }
         if (testbit(tmp, 2))
         {
            yyj->DO.Relay.Solo.REHEAT_LV03 = 1;
         }
      }
   }
   else
   {
      yyj->DO.Relay.Solo.REHEAT_LV01 = 0;
      yyj->DO.Relay.Solo.REHEAT_LV02 = 0;
      yyj->DO.Relay.Solo.REHEAT_LV03 = 0;
   }
}
/**得到PID运算后的值的AO输出**/
void YYJ_Run_AODeal(YYJ_ALL_DEF *yyj)
{
   if (!yyj->Flag.Solo.BlowerRunning)
   {
      return;
   }
   if (!yyj->Flag.Solo.NowindFlag)
   {
      yyj->AO.Solo.HW_AO_HUMIDIFIER_CTRL = yyj->PID.RHpid.myOutput; //加湿
      yyj->AO.Solo.HW_AO_HOT_GATE = yyj->PID.Hotpid.myOutput; //加热
      if (yyj->PID.Coolpid.myOutput > yyj->PID.RHpidInv.myOutput)
      {
         yyj->AO.Solo.HW_AO_COLD_GATE = yyj->PID.Coolpid.myOutput; //制冷
      }
      else
      {
         yyj->AO.Solo.HW_AO_COLD_GATE = yyj->PID.RHpidInv.myOutput; //除湿
      }

      if (yyj->DI.Solo.SEL_SEASON_WINTER) //手动冬天   冷/热水
      {
         if (yyj->DI.Solo.INPUT_COLD_PROTECT) //防冻开百分百
         {
            yyj->AO.Solo.HW_AO_COLDHOT_GATE = AO_PWM_OUT_100;
         }
         else
         {
            yyj->AO.Solo.HW_AO_COLDHOT_GATE = yyj->PID.Hotpid.myOutput;
         }
      }
      else if (yyj->DI.Solo.SEL_SEASON_SUMMER) //手动夏天
      {
         yyj->AO.Solo.HW_AO_COLDHOT_GATE = yyj->PID.Coolpid.myOutput;
      }
      else //自动
      {
         if (yyj->DI.Solo.INPUT_WATER_SENSOR) //管温 1冬天0夏天
         {
            if (yyj->DI.Solo.INPUT_COLD_PROTECT)
            {
               yyj->AO.Solo.HW_AO_COLDHOT_GATE = AO_PWM_OUT_100;
            }
            else
            {
               yyj->AO.Solo.HW_AO_COLDHOT_GATE = yyj->PID.Hotpid.myOutput;
            }
         }
         else
         {
            yyj->AO.Solo.HW_AO_COLDHOT_GATE = yyj->PID.Coolpid.myOutput;
         }
      }
   }
   else
   {
      yyj->AO.Solo.HW_AO_HUMIDIFIER_CTRL = AO_PWM_OUT_0;
      yyj->AO.Solo.HW_AO_HOT_GATE        = AO_PWM_OUT_0;
      yyj->AO.Solo.HW_AO_COLD_GATE       = AO_PWM_OUT_0;
      yyj->AO.Solo.HW_AO_COLDHOT_GATE    = AO_PWM_OUT_0;
   }
}

void YYJ_Run_PIDDeal(YYJ_ALL_DEF *yyj)
{
   if (yyj->Flag.Solo.BlowerRunning)
   {
      CoolPidCompute(yyj);
      HotPidCompute(yyj);
      RHPidCompute(yyj);
      RHPidInvCompute(yyj);
   }
   if (yyj->Flag.Solo.NowindFlag)
   {
      yyj->DO.Relay.Solo.HUMIDIFIER_GATE = 0;
      yyj->DO.Relay.Solo.HUMIDIFIER_CHAIN = 0;
      yyj->DO.Relay.Solo.HUMIDIFIER_START = 0;
      yyj->Flag.Solo.HumidifierFlag = 0;
   }
}
void YYJ_Run_FreqCtrl(YYJ_ALL_DEF *yyj)
{
   if (!yyj->Flag.Solo.BlowerRunning && !yyj->DI.Solo.SEL_MODE_FRQ_CVT)
   {
      return;
   }
   if (yyj->Flag.Solo.NowindFlag)
   {
      yyj->AO.Solo.HW_AO_FC_FRQ = AO_PWM_OUT_0;
      yyj->AO.Solo.HW_AO_MANUAL_FRQ_SET = AO_PWM_OUT_0;
      return;
   }

   if (yyj->DI.Solo.SEL_MODE_MANUAL_FRQ) //手动
   {
      yyj->AO.Solo.HW_AO_MANUAL_FRQ_SET = NowFreq;
   }
   else
   {
      if (yyj->toStatus.Solo.toStandby) //值机运行
      {
         yyj->AO.Solo.HW_AO_FC_FRQ = AO_PWM_OUT_30;
      }
      else
      {
#if 1
         FreqCompute(yyj);
         yyj->AO.Solo.HW_AO_FC_FRQ = yyj->PID.Freqpid.myOutput * 1000 / 1024; //0~1000
#else
         int tmp;
         tmp = yyj->AI.Solo.HW_AI_PRESS * 1500 / 4096;
         tmp = 300 - tmp;
         if (tmp > 0)
         {
            if (tmp > 50)
            {
               yyj->AO.All[0] += 10;
            }
            else if (tmp > 30)
            {
               yyj->AO.All[0] += 5;
            }
            else if (tmp > 10)
            {
               yyj->AO.All[0] += 2;
            }
            else
            {
               yyj->AO.All[0] += 1;
            }
         }
         else
         {
            tmp = 0 - tmp;
            if (tmp > 50)
            {
               yyj->AO.All[0] -= 10;
            }
            else if (tmp > 30)
            {
               yyj->AO.All[0] -= 5;
            }
            else if (tmp > 10)
            {
               yyj->AO.All[0] -= 2;
            }
            else
            {
               yyj->AO.All[0] -= 1;
            }
         }
#endif
      }

   }
}


void YYJ_Status_OutputCtrl(YYJ_ALL_DEF *yyj)
{
   YYJ_Init_DealyTime(yyj);
   YYJ_Run_NgtPress(yyj);
   YYJ_Run_HighTmepChain(yyj);
   YYJ_Run_FanRadiating(yyj);
   YYJ_Run_ExhaustFan(yyj);
   YYJ_Run_HeatDeal(yyj);
   YYJ_Run_PreheatDeal(yyj);
   YYJ_Run_FreqCtrl(yyj);
   YYJ_Run_AODeal(yyj);
   YYJ_Run_PIDDeal(yyj);
   YYJ_Stop_DelayTime(yyj);
   YYJ_Stop_ShaJunDeng(yyj);
   YYJ_Stop_CntTime(yyj);
   YYJ_Stop_BaoWen(yyj);
   YYJ_Stop_Sum0Win1(yyj);
   YYJ_PanelExtendChange(yyj);
   YYJ_ExtendChange(yyj);
   YYJ_SetTmepOrRh(yyj);
   YYJ_SetRange(yyj);
}

void YYJ_SetTmepOrRh(YYJ_ALL_DEF *yyj)
{
   if (yyj->Small.Solo.LocalPower || yyj->DI.Solo.BOX_PANEL_KEY_RUN)
   {
      if (yyj->ExtendPanel != 0)
      {
         SetTemp = 25;
         SetRH   = 50;
         return;
      }
      else
      {
         SetTemp = (yyj->AI.Solo.HW_AI_HWP_SET_TEMP * 1000 / 4096  / 20);
         SetRH   = (yyj->AI.Solo.HW_AI_HWP_SET_RH * 1000 / 4096 / 10);
      }
   }
   if (yyj->Small.Solo.RemotePower || yyj->DI.Solo.BOX_PANEL_KEY_REMOTE_RUN)
   {
      if (yyj->PanelLogic.Key.Solo.KeyStart)
      {
         SetTemp = (yyj->PanelLogic.TempSet);      //设定温度 0~50
         SetRH   = (yyj->PanelLogic.RhSet);       //设定湿度 0~100
      }
      else if (yyj->DI.Solo.PANEL_KEY_RUN)
      {
         SetTemp = (yyj->AI.Solo.HW_AI_HWP_SET_TEMP * 1000 / 4096  / 20);  //设定温度 0~50
         SetRH   = (yyj->AI.Solo.HW_AI_HWP_SET_RH * 1000 / 4096 / 10);        //设定湿度 0~100
      }
      else
      {
         SetTemp = 25;
         SetRH = 50;
      }
   }
}

void YYJ_SetRange(YYJ_ALL_DEF *yyj)
{
   NowTemp = yyj->AI.Solo.HW_AI_RA_TEMP * 10 * yyj->OP.SysPar.TmepRange / 4096; //默认0~10V代表0~50℃
   NowRH = yyj->AI.Solo.HW_AI_RA_RH * 10 * yyj->OP.SysPar.RhRange / 4096; //默认0~10V代表0~100%RH
   NowPress = yyj->AI.Solo.HW_AI_PRESS * yyj->OP.SysPar.PressRange / 4096; //默认0~10V代表0~500pa
   PreTemp = yyj->AI.Solo.HW_AI_PRE_HEAT_TEMP * yyj->OP.SysPar.PressRange / 4096; //默认0~10V代表0~20℃
}

void YYJ_PanelExtendChange(YYJ_ALL_DEF *yyj)
{
   //
   if ((yyj->AO.Solo.HW_AO_HWP_DISP_TEMP ==  yyj->AI.Solo.HW_AI_RA_TEMP) && (yyj->AO.Solo.HW_AO_HWP_DISP_RH == yyj->AI.Solo.HW_AI_RA_RH))
   {
      yyj->ExtendPanel = 0;
   }
   //浮点阀
   if ((yyj->AI.Solo.HW_AI_HWP_SET_TEMP >= 600) && (yyj->AI.Solo.HW_AI_HWP_SET_RH <= 750)) //682
   {
      if (!(yyj->DI.Solo.PANEL_KEY_RUN || yyj->DI.Solo.PANEL_KEY_STANDBY || yyj->DI.Solo.PANEL_KEY_NGT))
      {
         yyj->ExtendPanel = 1;
      }
   }
   //VI转换
   if ((yyj->AI.Solo.HW_AI_HWP_SET_TEMP < 5) && (yyj->AI.Solo.HW_AI_HWP_SET_RH < 5))
   {
      if (yyj->DI.Solo.PANEL_KEY_RUN && yyj->DI.Solo.PANEL_KEY_STANDBY && yyj->DI.Solo.PANEL_KEY_NGT)
      {
         yyj->ExtendPanel = 2;
      }
   }
}

/**扩展板 1**/
void YYJ_Panel_Extend1(YYJ_ALL_DEF *yyj)
{
   yyj->DO.Relay.Solo.PANEL_RUN = 0;
   yyj->DO.Relay.Solo.PANEL_STANDBY = 0;
   yyj->DO.Relay.Solo.PANEL_FILTER = 0;
   yyj->DO.Relay.Solo.PANEL_ERR = 0;
   if (yyj->Status.Solo.Runing)
   {
      yyj->DO.Relay.Solo.PANEL_RUN = 1;
   }
   if (yyj->Status.Solo.Standby)
   {
      yyj->DO.Relay.Solo.PANEL_STANDBY = 1;
   }
   if (yyj->DI.Solo.INPUT_CHU_XIAO || yyj->DI.Solo.INPUT_ZHONG_XIAO || yyj->DI.Solo.INPUT_YA_GAO_XIAO || yyj->DI.Solo.INPUT_GAO_XIAO)
   {
      yyj->DO.Relay.Solo.PANEL_FILTER = 1;
   }
   if (yyj->Status.Solo.Error)
   {
      yyj->DO.Relay.Solo.PANEL_ERR = 1;
   }
   NowTemp = yyj->AO.Solo.HW_AO_HWP_DISP_TEMP;
   NowRH = yyj->AO.Solo.HW_AO_HWP_DISP_RH;
}

/**扩展板 2**/
void YYJ_Panel_Extend2(YYJ_ALL_DEF *yyj)
{
   if (!yyj->Flag.Solo.BlowerRunning)
   {
      return;
   }
   yyj->OP.SysPar.FloatValve = 100;
//   yyj->PID.Hotpid.myOutput ;
//   yyj->PID.Coolpid.myOutput;
}

/**扩展板 3**/
void YYJ_Panel_Extend3(YYJ_ALL_DEF *yyj)
{
   ;
}

void YYJ_ExtendChange(YYJ_ALL_DEF *yyj)
{
   switch (yyj->ExtendPanel)
   {
   case 0:
      YYJ_Panel_Extend1(yyj); //
      break;
   case 1:
      YYJ_Panel_Extend2(yyj); //浮点阀
      break;
   case 2:
      YYJ_Panel_Extend3(yyj); //VI转换
      break;
   }
}

#define ________________________________________________________________________________________________________

/**关闭所有输出**/
void YYJ_Close_All(YYJ_ALL_DEF *yyj)
{
   yyj->DO.Relay.uint16All[0] = 0;
   yyj->DO.Relay.uint16All[1] = 0;
   yyj->DO.Relay.uint16All[2] = 0;
   yyj->AO.All[0] = AO_PWM_OUT_0;
   yyj->AO.All[1] = AO_PWM_OUT_0;
   yyj->AO.All[2] = AO_PWM_OUT_0;
   yyj->AO.All[3] = AO_PWM_OUT_0;
   yyj->AO.All[4] = AO_PWM_OUT_0;
   yyj->AO.All[5] = AO_PWM_OUT_0;
   yyj->AO.All[6] = AO_PWM_OUT_0;
   yyj->AO.All[7] = AO_PWM_OUT_0;
}

void YYJ_RunMode_FCorFF(YYJ_ALL_DEF *yyj)
{
//定频运行
   if (yyj->DI.Solo.SEL_MODE_FIX_FRQ)
   {
      yyj->DO.Relay.Solo.FAN_FF_START = 1; //送风机定频
      yyj->DO.Relay.Solo.FAN_FC_START = 0;
      yyj->Flag.Solo.BlowerRunning = 1;
      if (yyj->WorkStep == 0)
      {
         if (yyj->DI.Solo.SEL_TRIANGLE_START || (yyj->DI.Solo.TRIANGLE_STAR_TIMESET == 0))
         {
            yyj->DO.Relay.Solo.FAN_STAR_START = 0; //送风机星形
            yyj->WorkStep = 2;
         }
         else
         {
            yyj->DO.Relay.Solo.FAN_STAR_START = 1;
            yyj->Time.StarTime = POL_DI_Block.Solo.TRIANGLE_STAR_TIMESET;
            yyj->WorkStep++;
         }

         rt_kprintf("YYJ__Runing_to__FF: %05d\r\n", __LINE__);
      }
      else if (yyj->WorkStep == 1)
      {
         if (yyj->Time.StarTime == 0)
         {
            yyj->WorkStep++;
            yyj->DO.Relay.Solo.FAN_STAR_START = 0;
         }
      }
      else
      {
         yyj->DO.Relay.Solo.FAN_STAR_START = 0;
      }
   }
//变频运行
   else if (yyj->DI.Solo.SEL_MODE_FRQ_CVT)
   {
      yyj->DO.Relay.Solo.FAN_FC_START = 1; //送风机变频
      yyj->DO.Relay.Solo.FAN_FF_START = 0;
      yyj->DO.Relay.Solo.FC_CTRL_START = 1;  //开启变频器
      yyj->Flag.Solo.BlowerRunning = 1;
      if (yyj->WorkStep == 0)
      {
         yyj->WorkStep++;

         rt_kprintf("YYJ__Runing_to__FC: %05d\r\n", __LINE__);
      }
      if (yyj->WorkStep == 1)
      {
         if (yyj->PanelLogic.Key.Solo.KeyStandby)
         {
            yyj->DO.Relay.Solo.FC_CTRL_STANDBY = 1;  //变频器值机
         }
         else
         {
            yyj->WorkStep++;
         }
      }
      else if (yyj->WorkStep == 2)
      {
         yyj->DO.Relay.Solo.FC_CTRL_STANDBY = 0;  //变频器全速
         if (yyj->PanelLogic.Key.Solo.KeyStandby)
         {
            yyj->WorkStep--;
         }
      }
   }
   else
   {
      yyj->Flag.Solo.BlowerRunning = 0;
   }
}

void YYJ_OffStop_Step(YYJ_ALL_DEF *yyj)
{
   yyj->AO.All[0] = AO_PWM_OUT_0;
   yyj->AO.All[1] = AO_PWM_OUT_0;
   yyj->AO.All[2] = AO_PWM_OUT_0;
   yyj->AO.All[3] = AO_PWM_OUT_0;
   yyj->AO.All[5] = AO_PWM_OUT_0;
//冷热水阀
   if (yyj->Flag.Solo.Sum0Win1)
   {
      if (yyj->WorkStep == 0)
      {
         yyj->Time.CloseColdTime = yyj->OP.SetSize.CloseColdTime;
         yyj->WorkStep++;
      }
      else if (yyj->WorkStep == 1)
      {
         yyj->AO.All[4] = AO_PWM_OUT_30;
         if (yyj->Time.CloseColdTime == 0)
         {
            yyj->Time.OpenColdTime = yyj->OP.SetSize.OpenColdTime;
            yyj->WorkStep++;
         }
      }
      else if (yyj->WorkStep == 2)
      {
         yyj->AO.All[4] = AO_PWM_OUT_0;
         if (yyj->Time.OpenColdTime == 0)
         {
            yyj->WorkStep = 0;
         }
      }
   }
   else
   {
      yyj->AO.All[4] = AO_PWM_OUT_0;
   }

   if (yyj->Time.StopDelayTime < 3)
   {
      yyj->DO.Relay.Solo.FAN_FF_START = 0;     //关闭送风机定频
      yyj->DO.Relay.Solo.FAN_FC_START = 0;     //关闭送风机变频
      yyj->DO.Relay.Solo.FC_CTRL_START = 0;    //关闭变频器
      yyj->DO.Relay.Solo.FAN_STAR_START = 0;   //关闭送风机星形启动
      yyj->DO.Relay.Solo.FAN_COOLER = 0;       //送风机散热风扇
      yyj->DO.Relay.Solo.BOX_COOLER = 0;       //电柜自用散热风扇
   }
   if (yyj->Time.StopDelayTime == 0)
   {
      yyj->DO.Relay.Solo.FRESH_AIR_GATE_FIX = 0; //新风机定量风阀
      yyj->DO.Relay.Solo.FRESH_AIR_GATE_TIGHT = 0; //新风机密闭阀
   }
}

void YYJ_ColdStop_Step(YYJ_ALL_DEF *yyj)
{
   yyj->AO.All[0] = AO_PWM_OUT_0;
   yyj->AO.All[1] = AO_PWM_OUT_0;
   yyj->AO.All[2] = AO_PWM_OUT_0;
   yyj->AO.All[3] = AO_PWM_OUT_0;
   yyj->AO.All[5] = AO_PWM_OUT_0;
//冷,热水阀
   if (yyj->DI.Solo.INPUT_COLD_PROTECT && yyj->Flag.Solo.Sum0Win1)
   {
      yyj->AO.All[4] = AO_PWM_OUT_30;
   }
   else if (yyj->Flag.Solo.Sum0Win1)
   {
      if (yyj->WorkStep == 0)
      {
         yyj->Time.CloseColdTime = yyj->OP.SetSize.CloseColdTime;
         yyj->WorkStep++;
      }
      else if (yyj->WorkStep == 1)
      {
         yyj->AO.All[4] = AO_PWM_OUT_30;
         if (yyj->Time.CloseColdTime == 0)
         {
            yyj->Time.OpenColdTime = yyj->OP.SetSize.OpenColdTime;
            yyj->WorkStep++;
         }
      }
      else if (yyj->WorkStep == 2)
      {
         yyj->AO.All[4] = AO_PWM_OUT_0;
         if (yyj->Time.OpenColdTime == 0)
         {
            yyj->WorkStep = 0;
         }
      }
   }
   else
   {
      yyj->AO.All[4] = AO_PWM_OUT_0;
   }

//----------------
   if (yyj->Time.StopDelayTime < 3)
   {
      yyj->DO.Relay.Solo.FAN_FF_START   =  0;
      yyj->DO.Relay.Solo.FAN_FC_START   =  0;
      yyj->DO.Relay.Solo.FC_CTRL_START  =  0;
      yyj->DO.Relay.Solo.FAN_STAR_START =  0;
      yyj->DO.Relay.Solo.FAN_COOLER     =  0;
      yyj->DO.Relay.Solo.BOX_COOLER     =  0;
   }
   if (yyj->Time.StopDelayTime == 0)
   {
      yyj->DO.Relay.Solo.FRESH_AIR_GATE_FIX   = 0;
      yyj->DO.Relay.Solo.FRESH_AIR_GATE_TIGHT = 0;
   }
}

#define ________________________________________________________________________________________________________


void YYJ_ALL_Alarm(YYJ_ALL_DEF *yyj)
{
   if (yyj->DI.Solo.INPUT_CHU_XIAO) //初效报警灯 #1
   {
      yyj->DO.Light.Solo.LAMP_AHU_CHU_XIAO = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_CHU_XIAO = 0;
   }
   if (yyj->DI.Solo.INPUT_ZHONG_XIAO) //中效报警灯 #2
   {
      yyj->DO.Light.Solo.LAMP_AHU_ZHONG_XIAO = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_ZHONG_XIAO = 0;
   }
   if (yyj->DI.Solo.INPUT_YA_GAO_XIAO) //亚高效报警灯 #3
   {
      yyj->DO.Light.Solo.LAMP_AHU_YA_GAO_XIAO = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_YA_GAO_XIAO = 0;
   }
   if (yyj->DI.Solo.INPUT_GAO_XIAO) //高效报警灯 #4
   {
      yyj->DO.Light.Solo.LAMP_AHU_GAO_XIAO = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_GAO_XIAO = 0;
   }

#define __________NoWind____________

   if (yyj->Flag.Solo.NowindFlag) //缺风报警灯 #5 正常:1 故障:0
   {
      yyj->DO.Light.Solo.LAMP_AHU_NOWIND = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_NOWIND = 0;
   }
   if (!yyj->DI.Solo.INPUT_PRE_HEAT_HIGH_TEMP) //预热高温报警灯关电预热 #6 正常:1 故障:0
   {
      yyj->DO.Light.Solo.LAMP_AHU_PREHEAT_HIGH = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_PREHEAT_HIGH = 0;
   }
   if (!yyj->DI.Solo.INPUT_HEAT_HIGH_TEMP) //电热高温报警灯关电加热 #7 正常:1 故障:0
   {
      yyj->DO.Light.Solo.LAMP_AHU_EHEAT_HIGH = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_EHEAT_HIGH = 0;
   }
   if (yyj->DI.Solo.INPUT_COLD_PROTECT) //防冻报警灯 #8
   {
      yyj->DO.Light.Solo.LAMP_AHU_COLD_ERR = 1;

#define __________ColdStop______________
      yyj->DO.Light.Solo.LAMP_AHU_COLD_STOP_ERR = 0;
      if (yyj->Flag.Solo.ColdStopFlag) //防冻停机报警灯 #9
      {
         yyj->DO.Light.Solo.LAMP_AHU_COLD_STOP_ERR = 1;
      }
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_COLD_ERR = 0;
      yyj->DO.Light.Solo.LAMP_AHU_COLD_STOP_ERR = 0;
   }
   if (!yyj->DI.Solo.INPUT_EMC || !yyj->DI.Solo.BOX_PANEL_KEY_EMC_STOP) //急停报警灯 #10 正常:1 故障:0
   {
      yyj->DO.Light.Solo.LAMP_AHU_EXTERN_EMC_ERR = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_EXTERN_EMC_ERR = 0;
   }
   if (!yyj->DI.Solo.INPUT_FIRE_EMC) //消防报警灯 #11 正常:1 故障:0
   {
      yyj->DO.Light.Solo.LAMP_AHU_FIRE_ERR = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_FIRE_ERR = 0;
   }
   if (yyj->Status.Solo.Error) //故障报警 #12
   {
      yyj->DO.Light.Solo.LAMP_AHU_ERROR = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_ERROR = 0;
   }
   if (yyj->toStatus.Solo.toRuning) //运行灯 #13
   {
      yyj->DO.Light.Solo.LAMP_AHU_RUNNING = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_RUNNING = 0;
   }
   if (yyj->toStatus.Solo.toStandby) //值机灯 #14
   {
      yyj->DO.Light.Solo.LAMP_AHU_STANDBY = 1;
   }
   else
   {
      yyj->DO.Light.Solo.LAMP_AHU_STANDBY = 0;
   }
}



#define ________________________________________________________________________________________________________



void YYJ_Init_Deal(YYJ_ALL_DEF *yyj)
{
   YYJ_Close_All(yyj);
   yyj->DO.Light.uint16All[0] = 0;
   yyj->Flag.All = 0;

   if (yyj->toStatus.Solo.toRuning)
   {
      yyj->Status.Solo.Runing = 1;
      yyj->Status.Solo.Init = 0;
      yyj->Status.Solo.Stop = 0;
      yyj->Status.Solo.Error = 0;

      rt_kprintf("YYJ_Status_to_Runing: %05d\r\n", __LINE__);
   }
}



void YYJ_Run_Deal(YYJ_ALL_DEF *yyj)
{
   yyj->DO.Relay.Solo.FRESH_AIR_GATE_FIX = 1; //新风机定量风阀
   yyj->DO.Relay.Solo.FRESH_AIR_GATE_TIGHT = 1; //新风机密闭阀
   if (yyj->Time.StartupTimer != 0)
   {
      return;
   }
   if (yyj->toStatus.Solo.toStandby)
   {
      yyj->Status.Solo.Standby = 1;
   }
   else
   {
      yyj->Status.Solo.Standby = 0;
   }
   YYJ_RunMode_FCorFF(yyj);
   //状态跳转判断
   if (yyj->toStatus.Solo.toError)
   {
      yyj->Status.Solo.Error = 1;
      yyj->Status.Solo.Stop = 0;
      yyj->Status.Solo.Standby = 0;
      yyj->Status.Solo.Runing = 0;
      yyj->Status.Solo.Init = 0;

      yyj->Flag.Solo.BlowerRunning = 0;
      yyj->WorkStep = 0;
      rt_kprintf("YYJ_Status_to_Error: %05d\r\n", __LINE__);
   }
   else if (yyj->toStatus.Solo.toColdStop || yyj->toStatus.Solo.toOffStop)
   {
      yyj->Status.Solo.Stop = 1;
      yyj->Status.Solo.Error = 0;
      yyj->Status.Solo.Standby = 0;
      yyj->Status.Solo.Runing = 0;
      yyj->Status.Solo.Init = 0;

      if (yyj->toStatus.Solo.toColdStop)
      {
         yyj->Flag.Solo.BlowerRunning = 0;
         yyj->Flag.Solo.ColdStopFlag = 1;
         yyj->WorkStep = 0;
         rt_kprintf("YYJ_Status_to_ColdStop: %05d\r\n", __LINE__);
      }
      if (yyj->toStatus.Solo.toOffStop)
      {
         yyj->Flag.Solo.BlowerRunning = 0;
         yyj->Flag.Solo.OffStopFlag = 1;
         yyj->WorkStep = 0;
         rt_kprintf("YYJ_Status_to_OffStop: %05d\r\n", __LINE__);
      }
   }

}

void YYJ_Stop_Deal(YYJ_ALL_DEF *yyj)
{
   if (yyj->Flag.Solo.ColdStopFlag)
   {
      YYJ_ColdStop_Step(yyj);
      if (yyj->toStatus.Solo.toInit)
      {
         yyj->Status.Solo.Init = 1;
         yyj->Status.Solo.Standby = 0;
         yyj->Status.Solo.Runing = 0;
         yyj->Status.Solo.Stop = 0;
         yyj->Status.Solo.Error = 0;

         rt_kprintf("YYJ_Status_to_Init: %05d\r\n", __LINE__);
         yyj->Flag.Solo.ColdStopFlag = 0;
         yyj->WorkStep = 0;
      }
   }
   if (yyj->Flag.Solo.OffStopFlag)
   {
      YYJ_OffStop_Step(yyj);
      if (yyj->toStatus.Solo.toRuning)
      {
         yyj->Status.Solo.Runing = 1;
         yyj->Status.Solo.Init = 0;
         yyj->Status.Solo.Stop = 0;
         yyj->Status.Solo.Error = 0;

         rt_kprintf("YYJ_Status_to_Run: %05d\r\n", __LINE__);
         yyj->Flag.Solo.OffStopFlag = 0;
         yyj->WorkStep = 0;
      }
   }
}


void YYJ_Error_Deal(YYJ_ALL_DEF *yyj)
{
   YYJ_Close_All(yyj);
   if (yyj->toStatus.Solo.toInit)
   {
      yyj->Status.Solo.Init = 1;
      yyj->Status.Solo.Stop = 0;
      yyj->Status.Solo.Error = 0;
      yyj->Status.Solo.Standby = 0;
      yyj->Status.Solo.Runing = 0;

      rt_kprintf("YYJ_Status_to_Init: %05d\r\n", __LINE__);
   }
}

void YYJ_StatusChange(YYJ_ALL_DEF *yyj)
{
   if (yyj->Status.Solo.Init)
   {
      YYJ_Init_Deal(yyj);
   }
   else if (yyj->Status.Solo.Runing)
   {
      YYJ_Run_Deal(yyj);
   }
   else if (yyj->Status.Solo.Error)
   {
      YYJ_Error_Deal(yyj);
   }
   else if (yyj->Status.Solo.Stop)
   {
      YYJ_Stop_Deal(yyj);
   }
}


void YYJ_Panel_Logic(YYJ_ALL_DEF *yyj)
{
//---------------------
   if (yyj->Panel[0].Key.Solo.KeyStart || yyj->Panel[1].Key.Solo.KeyStart || yyj->Panel[2].Key.Solo.KeyStart)
   {
      yyj->PanelLogic.Key.Solo.KeyStart = 1;
   }
   else
   {
      yyj->PanelLogic.Key.Solo.KeyStart = 0;
   }
//---------------------
   uint08 tmp = 0;
   if (yyj->Panel[0].Key.Solo.KeyStandby && yyj->Panel[0].Key.Solo.KeyStart)
   {
      tmp++;
   }
   if (yyj->Panel[1].Key.Solo.KeyStandby && yyj->Panel[1].Key.Solo.KeyStart)
   {
      tmp++;
   }
   if (yyj->Panel[2].Key.Solo.KeyStandby && yyj->Panel[2].Key.Solo.KeyStart)
   {
      tmp++;
   }
   if (tmp >= 3)
   {
      yyj->PanelLogic.Key.Solo.KeyStandby = 1;
   }
   else
   {
      yyj->PanelLogic.Key.Solo.KeyStandby = 0;
   }
//---------------------
   if (yyj->Panel[0].Key.Solo.KeyNgt || yyj->Panel[1].Key.Solo.KeyNgt || yyj->Panel[2].Key.Solo.KeyNgt)
   {
      yyj->PanelLogic.Key.Solo.KeyNgt = 1;
   }
   else
   {
      yyj->PanelLogic.Key.Solo.KeyNgt = 0;
   }
//---------------------
   if (yyj->Panel[0].Key.Solo.KeySpare || yyj->Panel[1].Key.Solo.KeySpare || yyj->Panel[2].Key.Solo.KeySpare)
   {
      yyj->PanelLogic.Key.Solo.KeySpare = 1;
   }
   else
   {
      yyj->PanelLogic.Key.Solo.KeySpare = 0;
   }
//---------------------温湿度逻辑写在通讯


}

void YYJ_TimeDeal(YYJ_ALL_DEF *yyj)
{
   if (yyj->Time.StartupTimer > 0)
   {
      yyj->Time.StartupTimer--;
   }
   if (yyj->Time.ShaJunDengTimer > 0)
   {
      yyj->Time.ShaJunDengTimer--;
   }
   if (yyj->Time.StarTime > 0)
   {
      yyj->Time.StarTime--;
   }
   if (yyj->Time.NoWindTime > 0)
   {
      yyj->Time.NoWindTime--;
   }
   if (yyj->Time.NgtPressTime > 0)
   {
      yyj->Time.NgtPressTime--;
   }
   if (yyj->Time.ColdProtectTime > 0)
   {
      yyj->Time.ColdProtectTime--;
   }
   if (yyj->Time.StopOffTime > 0)
   {
      yyj->Time.StopOffTime--;
   }
   if (yyj->Time.StopCntTime > 0)
   {
      yyj->Time.StopCntTime--;
   }
   if (yyj->Time.StopDelayTime > 0)
   {
      yyj->Time.StopDelayTime--;
   }
   if (yyj->Time.OpenColdTime > 0)
   {
      yyj->Time.OpenColdTime--;
   }
   if (yyj->Time.CloseColdTime > 0)
   {
      yyj->Time.CloseColdTime--;
   }
}


void YYJ_PanelFeedBack(YYJ_ALL_DEF *yyj)
{
   yyj->PanelFeedBack.Bits.All = 0;
   if (yyj->toStatus.Solo.toRuning)
   {
      yyj->PanelFeedBack.Bits.Solo.Run = 1;
      if (yyj->toStatus.Solo.toStandby)
      {
         yyj->PanelFeedBack.Bits.Solo.StandBy = 1;
      }
   }
   if (yyj->DI.Solo.INPUT_GAO_XIAO)
   {
      yyj->PanelFeedBack.Bits.Solo.HPEFault = 1;
   }
   if (yyj->DO.Relay.Solo.NGT_PRESS)
   {
      yyj->PanelFeedBack.Bits.Solo.NgtPress = 1;
   }
   if (yyj->toStatus.Solo.toError)
   {
      yyj->PanelFeedBack.Bits.Solo.AhuFault = 1;
   }
   if (yyj->Flag.Solo.HumidifierFlag)
   {
      yyj->PanelFeedBack.Bits.Solo.HumidifierRun = 1;
   }
   if (yyj->Flag.Solo.Sum0Win1)
   {
      yyj->PanelFeedBack.Bits.Solo.Sum0Win1 = 1;
   }
   if (yyj->DO.Relay.Solo.EHEAT_LV01)
   {
      yyj->PanelFeedBack.Bits.Solo.EHeat01 = 1;
   }
   if (yyj->DO.Relay.Solo.EHEAT_LV02)
   {
      yyj->PanelFeedBack.Bits.Solo.EHeat02 = 1;
   }
   if (yyj->DO.Relay.Solo.EHEAT_LV03)
   {
      yyj->PanelFeedBack.Bits.Solo.EHeat03 = 1;
   }
   yyj->PanelFeedBack.AhuHotGate    = OpenHotWater;
   yyj->PanelFeedBack.AhuColdGate   = OpenColdWater;
   yyj->PanelFeedBack.AhuWindPress  = SetPress;
   yyj->PanelFeedBack.AhuDifPress   = NowPress;
   yyj->PanelFeedBack.AhuTmep01     = NowTemp;
   yyj->PanelFeedBack.AhuRh01       = NowRH;
   yyj->PanelFeedBack.AhuTmep02     = NowTemp;
   yyj->PanelFeedBack.AhuRh02       = NowRH;
   yyj->PanelFeedBack.AhuTmep03     = NowTemp;
   yyj->PanelFeedBack.AhuRh03       = NowRH;
   yyj->PanelFeedBack.NowTempSet    = NowTemp;
   yyj->PanelFeedBack.NowRHSet      = NowRH;
}


void YYJ_SmallPanelFeedBack(YYJ_ALL_DEF *yyj)
{
   yyj->Small.Solo.LED16bit = 0;
   if (1)
   {
      yyj->Small.Solo.LED16bit |= 0x0001;
   }
   if (yyj->toStatus.Solo.toStandby)
   {
      yyj->Small.Solo.LED16bit |= 0x0002;
   }
   if (yyj->toStatus.Solo.toRuning)
   {
      yyj->Small.Solo.LED16bit |= 0x0004;
   }
   if (UartAppData3.MasterTimeout > 0)
   {
      yyj->Small.Solo.LED16bit |= 0x0008;
   }
   if (yyj->Status.Solo.Error) //
   {
      yyj->Small.Solo.LED16bit |= 0x0010;
   }
   if (yyj->DI.Solo.INPUT_CHU_XIAO)
   {
      yyj->Small.Solo.LED16bit |= 0x0020;
   }
   if (yyj->DI.Solo.FC_FEEDBACK_ERROR || yyj->DI.Solo.FF_FEEDBACK_ERR)
   {
      yyj->Small.Solo.LED16bit |= 0x0040;
   }
   if (yyj->DI.Solo.INPUT_ZHONG_XIAO)
   {
      yyj->Small.Solo.LED16bit |= 0x0080;
   }
   if (yyj->Flag.Solo.NowindFlag)
   {
      yyj->Small.Solo.LED16bit |= 0x0100;
   }
   if (yyj->DI.Solo.INPUT_YA_GAO_XIAO)
   {
      yyj->Small.Solo.LED16bit |= 0x0200;
   }
   if (yyj->DI.Solo.INPUT_HEAT_HIGH_TEMP)
   {
      yyj->Small.Solo.LED16bit |= 0x0400;
   }
   if (yyj->DI.Solo.INPUT_GAO_XIAO)
   {
      yyj->Small.Solo.LED16bit |= 0x0800;
   }
   if (yyj->DI.Solo.INPUT_PRE_HEAT_HIGH_TEMP)
   {
      yyj->Small.Solo.LED16bit |= 0x1000;
   }
   if (yyj->Flag.Solo.ColdStopFlag)
   {
      yyj->Small.Solo.LED16bit |= 0x2000;
   }
   if (yyj->DI.Solo.INPUT_COLD_PROTECT)
   {
      yyj->Small.Solo.LED16bit |= 0x4000;
   }
   if (!yyj->DI.Solo.INPUT_EMC || !yyj->DI.Solo.BOX_PANEL_KEY_EMC_STOP || !yyj->DI.Solo.INPUT_FIRE_EMC) //
   {
      yyj->Small.Solo.LED16bit |= 0x8000;
   }
   yyj->Small.Solo.SmallAddr = yyj->OP.SmallAddr;
}

#define ______________________________________________________________________________________________________________

uint16 ReadPanelBlock(YYJ_Panel_all_def *p2data, uint16 index)
{
   if (index == 0)
   {
      return p2data->Key.Solo.KeyStart;
   }
   if (index == 1)
   {
      return p2data->Key.Solo.KeyStandby;
   }
   if (index == 2)
   {
      return p2data->Key.Solo.KeyNgt;
   }
   if (index == 3)
   {
      return p2data->Key.Solo.KeySpare;
   }
   if (index == 4)
   {
      return p2data->TempSet;
   }
   if (index == 5)
   {
      return p2data->RhSet;
   }
   return 0;
}



uint16 YYJ_Communication_Read(YYJ_ALL_DEF *yyj, uint16 index)
{
   if (index == 0)
   {
      return yyj->PanelFeedBack.Bits.Solo.Run;
   }
   if (index == 1)
   {
      return yyj->PanelFeedBack.Bits.Solo.StandBy;
   }
   if (index == 2)
   {
      return yyj->PanelFeedBack.Bits.Solo.HPEFault;
   }
   if (index == 3)
   {
      return yyj->PanelFeedBack.Bits.Solo.NgtPress;
   }
   if (index == 4)
   {
      return yyj->PanelFeedBack.Bits.Solo.AhuFault;
   }
   if (index == 5)
   {
      return yyj->PanelFeedBack.Bits.Solo.HumidifierRun;
   }
   if (index == 6)
   {
      return yyj->PanelFeedBack.Bits.Solo.Sum0Win1;
   }
   if (index == 7)
   {
      return yyj->PanelFeedBack.Bits.Solo.EHeat01;
   }
   if (index == 8)
   {
      return yyj->PanelFeedBack.Bits.Solo.EHeat02;
   }
   if (index == 9)
   {
      return yyj->PanelFeedBack.Bits.Solo.EHeat03;
   }
   if (index >= 10 && index <= 13)
   {
      return 0;
   }
   if (index == 14)
   {
      return yyj->PanelFeedBack.AhuHotGate;
   }
   if (index == 15)
   {
      return yyj->PanelFeedBack.AhuColdGate;
   }
   if (index == 16)
   {
      return yyj->PanelFeedBack.AhuWindPress;
   }
   if (index == 17)
   {
      return yyj->PanelFeedBack.AhuDifPress;
   }
   if (index == 18)
   {
      return yyj->PanelFeedBack.AhuTmep01;
   }
   if (index == 19)
   {
      return yyj->PanelFeedBack.AhuRh01;
   }
   if (index == 20)
   {
      return yyj->PanelFeedBack.AhuTmep02;
   }
   if (index == 21)
   {
      return yyj->PanelFeedBack.AhuRh02;
   }
   if (index == 22)
   {
      return yyj->PanelFeedBack.AhuTmep03;
   }
   if (index == 23)
   {
      return yyj->PanelFeedBack.AhuRh03;
   }
   if (index >= 22 &&  index <= 27)
   {
      return 0;
   }
   if (index >= 28 + 6 * 0 && index <= 33 + 6 * 0)
   {
      return ReadPanelBlock(&yyj->Panel[0], index - 28 - 6 * 0);
   }
   if (index >= 28 + 6 * 1 && index <= 33 + 6 * 1)
   {
      return ReadPanelBlock(&yyj->Panel[1], index - 28 - 6 * 1);
   }
   if (index >= 28 + 6 * 2 && index <= 33 + 6 * 2)
   {
      return ReadPanelBlock(&yyj->Panel[2], index - 28 - 6 * 2);
   }
   if (index >= 28 + 6 * 3 && index <= 33 + 6 * 3)
   {
      return ReadPanelBlock(&yyj->PanelLogic, index - 28 - 6 * 3);
   }
   return 0;
}



void WritePanelBlock(YYJ_Panel_all_def *p2data, YYJ_Panel_all_def *p2logic, uint16 index, uint16 wdata)
{
   if (index == 0)
   {
      p2data->Key.Solo.KeyStart = wdata;
   }
   if (index == 1)
   {
      p2data->Key.Solo.KeyStandby = wdata;
   }
   if (index == 2)
   {
      p2data->Key.Solo.KeyNgt = wdata;
   }
   if (index == 3)
   {
      p2data->Key.Solo.KeySpare = wdata;
   }
   if (index == 4)
   {
      if (p2data->TempSet != wdata)
      {
         if (wdata <= 15)
         {
            wdata = 15;
         }
         if (wdata >= 50)
         {
            wdata = 50;
         }
         p2data->TempSet = wdata;
         p2logic->TempSet = wdata;
      }
   }
   if (index == 5)
   {
      if (p2data->RhSet != wdata)
      {
         if (wdata <= 20)
         {
            wdata = 20;
         }
         if (wdata >= 90)
         {
            wdata = 90;
         }
         p2data->RhSet = wdata;
         p2logic->RhSet = wdata;
      }
   }
}

void YYJ_Communication_Write(YYJ_ALL_DEF *yyj, uint16 index, uint16 wdata)
{
   if (index == 0)
   {
      yyj->PanelFeedBack.Bits.Solo.Run = wdata;
   }
   if (index == 1)
   {
      yyj->PanelFeedBack.Bits.Solo.StandBy = wdata;
   }
   if (index == 2)
   {
      yyj->PanelFeedBack.Bits.Solo.HPEFault = wdata;
   }
   if (index == 3)
   {
      yyj->PanelFeedBack.Bits.Solo.NgtPress = wdata;
   }
   if (index == 4)
   {
      yyj->PanelFeedBack.Bits.Solo.AhuFault = wdata;
   }
   if (index == 5)
   {
      yyj->PanelFeedBack.Bits.Solo.HumidifierRun = wdata;
   }
   if (index == 6)
   {
      yyj->PanelFeedBack.Bits.Solo.Sum0Win1 = wdata;
   }
   if (index == 7)
   {
      yyj->PanelFeedBack.Bits.Solo.EHeat01 = wdata;
   }
   if (index == 8)
   {
      yyj->PanelFeedBack.Bits.Solo.EHeat02 = wdata;
   }
   if (index == 9)
   {
      yyj->PanelFeedBack.Bits.Solo.EHeat03 = wdata;
   }
   if (index >= 10 && index <= 13)
   {
      ;
   }
   if (index == 14)
   {
      yyj->PanelFeedBack.AhuHotGate = wdata;
   }
   if (index == 15)
   {
      yyj->PanelFeedBack.AhuColdGate = wdata;
   }
   if (index == 16)
   {
      yyj->PanelFeedBack.AhuWindPress = wdata;
   }
   if (index == 17)
   {
      yyj->PanelFeedBack.AhuDifPress = wdata;
   }
   if (index == 18)
   {
      yyj->PanelFeedBack.AhuTmep01 = wdata;
   }
   if (index == 19)
   {
      yyj->PanelFeedBack.AhuRh01 = wdata;
   }
   if (index == 20)
   {
      yyj->PanelFeedBack.AhuTmep02 = wdata;
   }
   if (index == 21)
   {
      yyj->PanelFeedBack.AhuRh02 = wdata;
   }
   if (index == 22)
   {
      yyj->PanelFeedBack.AhuTmep03 = wdata;
   }
   if (index == 23)
   {
      yyj->PanelFeedBack.AhuRh03 = wdata;
   }
   if (index >= 28 + 6 * 0 && index <= 33 + 6 * 0)
   {
      WritePanelBlock(&yyj->Panel[0], &yyj->PanelLogic, index - 28 - 6 * 0, wdata);
   }
   if (index >= 28 + 6 * 1 && index <= 33 + 6 * 1)
   {
      WritePanelBlock(&yyj->Panel[1], &yyj->PanelLogic, index - 28 - 6 * 1, wdata);
   }
   if (index >= 28 + 6 * 2 && index <= 33 + 6 * 2)
   {
      WritePanelBlock(&yyj->Panel[2], &yyj->PanelLogic, index - 28 - 6 * 2, wdata);
   }
   if (index >= 28 + 6 * 3 && index <= 33 + 6 * 3)
   {
      WritePanelBlock(&yyj->PanelLogic, &yyj->PanelLogic, index - 28 - 6 * 3, wdata);
   }
}

uint16 YYJ_Read_SmallPanel(YYJ_ALL_DEF *yyj, uint16 index)
{
   if (index == 52)
   {
      return yyj->Small.Solo.RemotePower;
   }
   if (index == 53)
   {
      return yyj->Small.Solo.RemoteStandby;
   }
   if (index == 54)
   {
      return yyj->Small.Solo.LocalPower;
   }
   if (index == 55)
   {
      return yyj->Small.Solo.LocalStandby;
   }
   if (index == 56)
   {
      return yyj->Small.Solo.LED16bit;
   }
   if (index == 56)
   {
      return yyj->Small.Solo.LED16bit;
   }
   if (index == 57)
   {
      return yyj->Small.Solo.SmallAddr;
   }
   return 0;
}


void YYJ_Write_SmallPanel(YYJ_ALL_DEF *yyj, uint16 index, uint16 wdata)
{
   if (index == 52)
   {
      yyj->Small.Solo.RemotePower = wdata;
   }
   if (index == 53)
   {
      yyj->Small.Solo.RemoteStandby = wdata;
   }
   if (index == 54)
   {
      yyj->Small.Solo.LocalPower = wdata;
   }
   if (index == 55)
   {
      yyj->Small.Solo.LocalStandby = wdata;
   }
   if (index == 56)
   {
      yyj->Small.Solo.LED16bit = wdata;
   }
   if (index == 57)
   {
      yyj->Small.Solo.SmallAddr = wdata;
   }
}



uint16 YYJ_ReadPID(YYJ_OPTIONS *pid, uint16 index)
{
   if (index == 0)
   {
      return pid->RHpid.Kp;
   }
   if (index == 1)
   {
      return pid->RHpid.Ki;
   }
   if (index == 2)
   {
      return pid->RHpid.Kd;
   }
   if (index == 3)
   {
      return pid->RHpid.SampleTime;
   }
   if (index == 4)
   {
      return pid->RHpid.DeadBand;
   }
   if (index == 5)
   {
      return pid->RHpidInv.Kp;
   }
   if (index == 6)
   {
      return pid->RHpidInv.Ki;
   }
   if (index == 7)
   {
      return pid->RHpidInv.Kd;
   }
   if (index == 8)
   {
      return pid->RHpidInv.SampleTime;
   }
   if (index == 9)
   {
      return pid->RHpidInv.DeadBand;
   }
   if (index == 10)
   {
      return pid->Hotpid.Kp;
   }
   if (index == 11)
   {
      return pid->Hotpid.Ki;
   }
   if (index == 12)
   {
      return pid->Hotpid.Kd;
   }
   if (index == 13)
   {
      return pid->Hotpid.SampleTime;
   }
   if (index == 14)
   {
      return pid->Hotpid.DeadBand;
   }
   if (index == 15)
   {
      return pid->Coolpid.Kp;
   }
   if (index == 16)
   {
      return pid->Coolpid.Ki;
   }
   if (index == 17)
   {
      return pid->Coolpid.Kd;
   }
   if (index == 18)
   {
      return pid->Coolpid.SampleTime;
   }
   if (index == 19)
   {
      return pid->Coolpid.DeadBand;
   }
   if (index == 20)
   {
      return pid->Freqpid.Kp;
   }
   if (index == 21)
   {
      return pid->Freqpid.Ki;
   }
   if (index == 22)
   {
      return pid->Freqpid.Kd;
   }
   if (index == 23)
   {
      return pid->Freqpid.SampleTime;
   }
   if (index == 24)
   {
      return pid->Freqpid.DeadBand;
   }
   return 0;
}


void YYJ_WritePID(YYJ_OPTIONS *pid, uint16 index, uint16 wdata)
{
   if (index == 0)
   {
      pid->RHpid.Kp = wdata;
   }
   if (index == 1)
   {
      pid->RHpid.Ki = wdata;
   }
   if (index == 2)
   {
      pid->RHpid.Kd = wdata;
   }
   if (index == 3)
   {
      pid->RHpid.SampleTime = wdata;
   }
   if (index == 4)
   {
      pid->RHpid.DeadBand = wdata;
   }
   if (index == 5)
   {
      pid->RHpidInv.Kp = wdata;
   }
   if (index == 6)
   {
      pid->RHpidInv.Ki = wdata;
   }
   if (index == 7)
   {
      pid->RHpidInv.Kd = wdata;
   }
   if (index == 8)
   {
      pid->RHpidInv.SampleTime = wdata;
   }
   if (index == 9)
   {
      pid->RHpidInv.DeadBand = wdata;
   }
   if (index == 10)
   {
      pid->Hotpid.Kp = wdata;
   }
   if (index == 11)
   {
      pid->Hotpid.Ki = wdata;
   }
   if (index == 12)
   {
      pid->Hotpid.Kd = wdata;
   }
   if (index == 13)
   {
      pid->Hotpid.SampleTime = wdata;
   }
   if (index == 14)
   {
      pid->Hotpid.DeadBand = wdata;
   }
   if (index == 15)
   {
      pid->Coolpid.Kp = wdata;
   }
   if (index == 16)
   {
      pid->Coolpid.Ki = wdata;
   }
   if (index == 17)
   {
      pid->Coolpid.Kd = wdata;
   }
   if (index == 18)
   {
      pid->Coolpid.SampleTime = wdata;
   }
   if (index == 19)
   {
      pid->Coolpid.DeadBand = wdata;
   }
   if (index == 20)
   {
      pid->Freqpid.Kp = wdata;
   }
   if (index == 21)
   {
      pid->Freqpid.Ki = wdata;
   }
   if (index == 22)
   {
      pid->Freqpid.Kd = wdata;
   }
   if (index == 23)
   {
      pid->Freqpid.SampleTime = wdata;
   }
   if (index == 24)
   {
      pid->Freqpid.DeadBand = wdata;
   }
}

uint16 YYJ_ReadPar(YYJ_OPTIONS *pdata, uint16 index)
{
//时间设置
   if (index == 0)
   {
      return pdata->SetSize.StartupTimer;
   }
   if (index == 1)
   {
      return pdata->SetSize.ShaJunDengTimer;
   }
   if (index == 2)
   {
      return pdata->SetSize.NoWindTime;
   }
   if (index == 3)
   {
      return pdata->SetSize.NgtPressTime;
   }
   if (index == 4)
   {
      return pdata->SetSize.ColdProtectTime;
   }
   if (index == 5)
   {
      return pdata->SetSize.StopOffTime;
   }
   if (index == 6)
   {
      return pdata->SetSize.StopCntTime;
   }
   if (index == 7)
   {
      return pdata->SetSize.OpenColdTime;
   }
   if (index == 8)
   {
      return pdata->SetSize.CloseColdTime;
   }
   if (index == 9)
   {
      return pdata->SetSize.StopDelayTime;
   }
//-----------------------------------------
   if (index == 10)
   {
      return pdata->SysPar.PreHotStart;
   }
   if (index == 11)
   {
      return pdata->SysPar.PreHotEnd;
   }
   if (index == 12)
   {
      return pdata->SysPar.AirPress;
   }
   if (index == 13)
   {
      return pdata->SysPar.SaveBit.Solo.MCU1_PLC0;
   }
   if (index == 14)
   {
      return pdata->SysPar.TmepRange;
   }
   if (index == 15)
   {
      return pdata->SysPar.RhRange;
   }
   if (index == 16)
   {
      return pdata->SysPar.PressRange;
   }
   if (index == 17)
   {
      return pdata->SysPar.PreHeatRange;
   }
   if (index == 18)
   {
      if (pdata->StopBitSet.COM2 == 0x0000)
      {
         return 1;
      }
      if (pdata->StopBitSet.COM2 == 0x2000)
      {
         return 2;
      }
   }
   if (index == 19)
   {
      if (pdata->StopBitSet.COM3 == 0x0000)
      {
         return 1;
      }
      if (pdata->StopBitSet.COM3 == 0x2000)
      {
         return 2;
      }
   }
   if (index == 20)
   {
      if (pdata->StopBitSet.COM4 == 0x0000) //1stop
      {
         return 1;
      }
      if (pdata->StopBitSet.COM4 == 0x2000) //2stop
      {
         return 2;
      }
   }
   if (index == 21)
   {
      if (pdata->ParitySet.COM2 == 0x0000) //no
      {
         return 0;
      }
      if (pdata->ParitySet.COM2 == 0x0600) //even
      {
         return 1;
      }
      if (pdata->ParitySet.COM2 == 0x0400) //odd
      {
         return 2;
      }
   }
   if (index == 22)
   {
      if (pdata->ParitySet.COM3 == 0x0000) //no
      {
         return 0;
      }
      if (pdata->ParitySet.COM3 == 0x0600) //even
      {
         return 1;
      }
      if (pdata->ParitySet.COM3 == 0x0400) //odd
      {
         return 2;
      }
   }
   if (index == 23)
   {
      if (pdata->ParitySet.COM4 == 0x0000) //no
      {
         return 0;
      }
      if (pdata->ParitySet.COM4 == 0x0600) //even
      {
         return 1;
      }
      if (pdata->ParitySet.COM4 == 0x0400) //odd
      {
         return 2;
      }
   }
   if (index == 24)
   {
      return pdata->BaudSet.COM2;
   }
   if (index == 25)
   {
      return pdata->BaudSet.COM3;
   }
   if (index == 26)
   {
      return pdata->BaudSet.COM4;
   }
   return 0;
}
void YYJ_WritePar(YYJ_OPTIONS *pdata, uint16 index, uint16 wdata)
{
//时间设置
   if (index == 0)
   {
      pdata->SetSize.StartupTimer = wdata;
   }
   if (index == 1)
   {
      pdata->SetSize.ShaJunDengTimer = wdata;
   }
   if (index == 2)
   {
      pdata->SetSize.NoWindTime = wdata;
   }
   if (index == 3)
   {
      pdata->SetSize.NgtPressTime = wdata;
   }
   if (index == 4)
   {
      pdata->SetSize.ColdProtectTime = wdata;
   }
   if (index == 5)
   {
      pdata->SetSize.StopOffTime = wdata;
   }
   if (index == 6)
   {
      pdata->SetSize.StopCntTime = wdata;
   }
   if (index == 7)
   {
      pdata->SetSize.OpenColdTime = wdata;
   }
   if (index == 8)
   {
      pdata->SetSize.CloseColdTime = wdata;
   }
   if (index == 9)
   {
      pdata->SetSize.StopDelayTime = wdata;
   }
//-----------------------------------------
   if (index == 10)
   {
      if (wdata <= 3)
      {
         wdata = 3;
      }
      if (wdata >= 5)
      {
         wdata = 5;
      }
      pdata->SysPar.PreHotStart = wdata;
   }
   if (index == 11)
   {
      if (wdata <= 10)
      {
         wdata = 10;
      }
      if (wdata >= 12)
      {
         wdata = 12;
      }
      pdata->SysPar.PreHotEnd = wdata;
   }
   if (index == 12)
   {
      pdata->SysPar.AirPress = wdata;
   }
   if (index == 13)
   {
      pdata->SysPar.SaveBit.Solo.MCU1_PLC0 = wdata;
   }
   if (index == 14)
   {
      pdata->SysPar.TmepRange = wdata;
   }
   if (index == 15)
   {
      pdata->SysPar.RhRange = wdata;
   }
   if (index == 16)
   {
      pdata->SysPar.PressRange = wdata;
   }
   if (index == 17)
   {
      pdata->SysPar.PreHeatRange = wdata;
   }
   if (index == 18)
   {
      if (wdata == 1)
      {
         pdata->StopBitSet.COM2 = 0x0000;
      }
      if (wdata == 2)
      {
         pdata->StopBitSet.COM2 = 0x2000;
      }
   }
   if (index == 19)
   {
      if (wdata == 1)
      {
         pdata->StopBitSet.COM3 = 0x0000;
      }
      if (wdata == 2)
      {
         pdata->StopBitSet.COM3 = 0x2000;
      }
   }
   if (index == 20)
   {
      if (wdata == 1)
      {
         pdata->StopBitSet.COM4 = 0x0000;
      }
      if (wdata == 2)
      {
         pdata->StopBitSet.COM4 = 0x2000;
      }
   }
   if (index == 21)
   {
      if (wdata == 0)
      {
         pdata->ParitySet.COM2 = 0x0000;
      }
      if (wdata == 1)
      {
         pdata->ParitySet.COM2 = 0x0600;
      }
      if (wdata == 2)
      {
         pdata->ParitySet.COM2 = 0x0400;
      }
   }
   if (index == 22)
   {
      if (wdata == 0)
      {
         pdata->ParitySet.COM3 = 0x0000;
      }
      if (wdata == 1)
      {
         pdata->ParitySet.COM3 = 0x0600;
      }
      if (wdata == 2)
      {
         pdata->ParitySet.COM3 = 0x0400;
      }
   }
   if (index == 23)
   {
      if (wdata == 0)
      {
         pdata->ParitySet.COM4 = 0x0000;
      }
      if (wdata == 1)
      {
         pdata->ParitySet.COM4 = 0x0600;
      }
      if (wdata == 2)
      {
         pdata->ParitySet.COM4 = 0x0400;
      }
   }
   if (index == 24)
   {
      pdata->BaudSet.COM2 = wdata;
   }
   if (index == 25)
   {
      pdata->BaudSet.COM3 = wdata;
   }
   if (index == 26)
   {
      pdata->BaudSet.COM4 = wdata;
   }
}
#define ______________________________________________________________________________________________________________

/**PID控制制冷函数**/
void CoolPidCompute(YYJ_ALL_DEF *yyj) //
{
   yyj->PID.Coolpid.myInput = NowTemp;
   if (SetTemp >= 15 && SetTemp <= 50)
   {
      yyj->PID.Coolpid.mySetpoint = SetTemp * 10;
   }
   yyj->PID.Coolpid.Flags.inAuto = 1;
   if (Compute(&yyj->PID.Coolpid) > 0)
   {

   }
}
/**PID控制加热函数**/
void HotPidCompute(YYJ_ALL_DEF *yyj)
{
   yyj->PID.Hotpid.myInput = NowTemp;
   if (SetTemp >= 15 && SetTemp <= 50)
   {
      yyj->PID.Hotpid.mySetpoint = SetTemp * 10;
   }
   yyj->PID.Hotpid.Flags.inAuto = 1;
   if (Compute(&yyj->PID.Hotpid) > 0)
   {

   }
}
/**PID控制加湿函数**/
void RHPidCompute(YYJ_ALL_DEF *yyj)
{
   yyj->PID.RHpid.myInput = NowRH;
   if (SetRH >= 20 && SetRH <= 99)
   {
      yyj->PID.RHpid.mySetpoint = SetRH * 10;
   }
   yyj->PID.RHpid.Flags.inAuto = 1;
   if (Compute(&yyj->PID.RHpid) != 0)
   {
      if (yyj->PID.RHpid.myOutput > 0)
      {
         yyj->DO.Relay.Solo.HUMIDIFIER_GATE = 1;  //加湿器电磁阀
         yyj->DO.Relay.Solo.HUMIDIFIER_CHAIN = 1; //加湿器互锁
         yyj->DO.Relay.Solo.HUMIDIFIER_START = 1; //加湿器开关
         yyj->Flag.Solo.HumidifierFlag = 1;
      }
      else
      {
         yyj->DO.Relay.Solo.HUMIDIFIER_GATE = 0;  //加湿器电磁阀
         yyj->DO.Relay.Solo.HUMIDIFIER_CHAIN = 0; //加湿器互锁
         yyj->DO.Relay.Solo.HUMIDIFIER_START = 0; //加湿器开关
         yyj->Flag.Solo.HumidifierFlag = 0;
      }
   }
}
/**PID控制除湿函数**/
void RHPidInvCompute(YYJ_ALL_DEF *yyj)
{
   yyj->PID.RHpidInv.myInput = NowRH;
   if (SetRH >= 20 && SetRH <= 99)
   {
      yyj->PID.RHpidInv.mySetpoint = SetRH * 10;
   }
   yyj->PID.RHpidInv.Flags.inAuto = 1;
   if (Compute(&yyj->PID.RHpidInv) != 0)
   {

   }
}
/**PID控制频率函数**/
void FreqCompute(YYJ_ALL_DEF *yyj)
{
   yyj->PID.Freqpid.myInput = NowPress; //回风压力
   if (SetPress >= 100 && SetPress <= 500)
   {
      yyj->PID.Freqpid.mySetpoint = SetPress; //设定的送风压力
   }
   yyj->PID.Freqpid.Flags.inAuto = 1;
   if (Compute(&yyj->PID.Freqpid) > 0)
   {

   }
}
#define ______________________________________________________________________________________________
void YYJ_ALL_MAIN(YYJ_ALL_DEF *yyj)
{

   YYJ1.BuffLoad();
   YYJ1.PidPar();
   YYJ_Panel_Logic(yyj);
   YYJ_StatusToChange(yyj);
   YYJ_StatusChange(yyj);

   YYJ_SmallPanelFeedBack(yyj);
   YYJ_ALL_Alarm(yyj);
   YYJ_Status_OutputCtrl(yyj);
   YYJ_PanelFeedBack(yyj);
}



void YYJ_AO_Adjust(YYJ_ALL_DEF *yyj, uint16 trgVolt, uint08 chnr)
{
   uint32 ltmp;
   ltmp =  POL_AO_Block.All[chnr] *  yyj->OP.Check.AOadjust.All[chnr] / trgVolt;
   if (ltmp <= 12000 && ltmp >= 8000)
   {
      yyj->OP.Check.AOadjust.All[chnr] = ltmp;
   }
}

void YYJ_AI_Adjust(YYJ_ALL_DEF *yyj, uint16 trgVolt, uint16 chnr)
{
   uint32 ltmp;
   uint32 tmp;
   tmp = trgVolt * 4096 / 1000;
   ltmp = yyj->OP.Check.AIadjust.All[chnr] * tmp / POL_AI_Block.All[chnr];
   if (ltmp <= 12000 && ltmp >= 8000)
   {
      yyj->OP.Check.AIadjust.All[chnr] = ltmp;
   }
}

uint16 YYJ_Adjust_Read(YYJ_ALL_DEF *yyj, uint16 index)
{
   if (index <= 6)
   {
//    return yyj->OP.Check.AIadjust.All[index];
      return POL_AI_Block.All[index];
   }
   if (index >= 7 && index <= 14)
   {
//    return yyj->OP.Check.AOadjust.All[index - 7];
      return POL_AO_Block.All[index - 7];
   }
   return 0;
}

void YYJ_Adjust_Write(YYJ_ALL_DEF *yyj, uint16 index, uint16 Data)
{
   if (index <= 6)
   {
      YYJ_AI_Adjust(yyj, Data, index);
   }
   if (index >= 7 && index <= 14)
   {
      YYJ_AO_Adjust(yyj, Data, index - 7);
   }
}



















































#define READBIT(x,y) (x & (1<<y)) ? 1 : 0
uint16 YYJ_TestRead(YYJ_ALL_DEF *yyj, uint16 index)
{
//------------------------------
   if (index == 0)
   {
      return yyj->Status.All;
   }
// if (index >= 1 && index <= 8)
// {
//    return yyj->AO.All[index - 1];
// }
// if (index >= 9 && index <= 10)
// {
//    return yyj->AI.All[index - 9];
// }
   if (index == 11)
   {
      return yyj->AI.Solo.HW_AI_PRESS;
   }
   if (index == 12)
   {
      return yyj->AI.Solo.HW_AI_PRE_HEAT_TEMP;
   }
   if (index >= 13 && index <= 14)
   {
      return yyj->AI.All[index - 11];
   }
   if (index == 15)
   {
      return TestMe_1;
   }
   if (index == 16)
   {
      return TestMe_2;
   }
   if (index == 17)
   {
      return TestMe_3;
   }
   if (index == 18)
   {
      return TestMe_4;
   }
   if (index == 19)
   {
      return TestMe_5;
   }
   if (index == 20)
   {
      return TestMe_6;
   }
   if (index == 21)
   {
      return TestMe_7;
   }
   if (index == 22)
   {
      return yyj->Time.StartupTimer;
   }
   if (index == 23)
   {
      return yyj->Time.NoWindTime;
   }
   if (index == 24)
   {
      return yyj->Time.NgtPressTime;
   }
   if (index == 25)
   {
      return yyj->Time.ColdProtectTime;
   }
   if (index == 26)
   {
      return yyj->Time.StopCntTime;
   }
   if (index == 27)
   {
      return yyj->Time.ShaJunDengTimer;
   }
   if (index == 28)
   {
      return yyj->Time.StopOffTime;
   }
   if (index == 29)
   {
      return yyj->Time.OpenColdTime;
   }
   if (index == 30)
   {
      return yyj->Time.CloseColdTime;
   }
   return 0;
}

void YYJ_TestWrite(YYJ_ALL_DEF *yyj, uint16 index, uint16 Data)
{
// if (index >= 1 && index <= 8)
// {
//    yyj->AO.All[index - 1] = Data;
// }
   if (index >= 9 && index <= 10)
   {
      yyj->AI.All[index - 9] = Data;
   }
   if (index == 11)
   {
      yyj->AI.Solo.HW_AI_PRESS = Data;
   }
   if (index == 12)
   {
      yyj->AI.Solo.HW_AI_PRE_HEAT_TEMP = Data;
   }
   if (index >= 13 && index <= 14)
   {
      yyj->AI.All[index - 11] = Data;
   }
//-------------------------------------
   if (index == 22)
   {
      yyj->Time.StartupTimer = Data;
   }
   if (index == 23)
   {
      yyj->Time.NoWindTime = Data;
   }
   if (index == 24)
   {
      yyj->Time.NgtPressTime = Data;
   }
   if (index == 25)
   {
      yyj->Time.ColdProtectTime = Data;
   }
   if (index == 26)
   {
      yyj->Time.StopCntTime = Data;
   }
   if (index == 27)
   {
      yyj->Time.ShaJunDengTimer = Data;
   }
   if (index == 28)
   {
      yyj->Time.StopOffTime = Data;
   }
   if (index == 29)
   {
      yyj->Time.OpenColdTime = Data;
   }
   if (index == 30)
   {
      yyj->Time.CloseColdTime = Data;
   }
}

void YYJ_TestFunction(YYJ_ALL_DEF *yyj)
{
   TestMe_1 = 0x0000;
   if (yyj->DO.Relay.Solo.FAN_FF_START)
   {
      TestMe_1 |= 0x0001;
   }
   if (yyj->DO.Relay.Solo.FAN_FC_START)
   {
      TestMe_1 |= 0x0002;
   }
   if (yyj->DO.Relay.Solo.FAN_STAR_START)
   {
      TestMe_1 |= 0x0004;
   }
   if (yyj->DO.Relay.Solo.FAN_COOLER)
   {
      TestMe_1 |= 0x0008;
   }
   if (yyj->DO.Relay.Solo.BOX_COOLER)
   {
      TestMe_1 |= 0x0010;
   }
   if (yyj->DO.Relay.Solo.FRESH_AIR_GATE_FIX)
   {
      TestMe_1 |= 0x0020;
   }
   if (yyj->DO.Relay.Solo.FRESH_AIR_GATE_TIGHT)
   {
      TestMe_1 |= 0x0040;
   }
   if (yyj->DO.Relay.Solo.FC_CTRL_START)
   {
      TestMe_1 |= 0x0080;
   }
   if (yyj->DO.Relay.Solo.FC_CTRL_STANDBY)
   {
      TestMe_1 |= 0x0100;
   }
   if (yyj->DO.Relay.Solo.NGT_PRESS)
   {
      TestMe_1 |= 0x0200;
   }
   if (yyj->DO.Relay.Solo.AUTO_GATES_01)
   {
      TestMe_1 |= 0x0400;
   }
   if (yyj->DO.Relay.Solo.AUTO_GATES_02)
   {
      TestMe_1 |= 0x0800;
   }
   if (yyj->DO.Relay.Solo.AUTO_GATES_03)
   {
      TestMe_1 |= 0x1000;
   }
   if (yyj->DO.Relay.Solo.AUTO_GATES_04)
   {
      TestMe_1 |= 0x2000;
   }
   if (yyj->DO.Relay.Solo.AUTO_GATES_05)
   {
      TestMe_1 |= 0x4000;
   }
   if (yyj->DO.Relay.Solo.AUTO_GATES_06)
   {
      TestMe_1 |= 0x8000;
   }
//----------------------------------------------------
   TestMe_2 = 0x0000;
   if (yyj->DO.Relay.Solo.EHEAT_LV01)
   {
      TestMe_2 |= 0x0001;
   }
   if (yyj->DO.Relay.Solo.EHEAT_LV02)
   {
      TestMe_2 |= 0x0002;
   }
   if (yyj->DO.Relay.Solo.EHEAT_LV03)
   {
      TestMe_2 |= 0x0004;
   }
   if (yyj->DO.Relay.Solo.REHEAT_LV01)
   {
      TestMe_2 |= 0x0008;
   }
   if (yyj->DO.Relay.Solo.REHEAT_LV02)
   {
      TestMe_2 |= 0x0010;
   }
   if (yyj->DO.Relay.Solo.REHEAT_LV03)
   {
      TestMe_2 |= 0x0020;
   }
   if (yyj->DO.Relay.Solo.HUMIDIFIER_CHAIN)
   {
      TestMe_2 |= 0x0040;
   }
   if (yyj->DO.Relay.Solo.HUMIDIFIER_START)
   {
      TestMe_2 |= 0x0080;
   }
   if (yyj->DO.Relay.Solo.HUMIDIFIER_GATE)
   {
      TestMe_2 |= 0x0100;
   }
   if (yyj->DO.Relay.Solo.STOP_WARMING)
   {
      TestMe_2 |= 0x0200;
   }
   if (yyj->DO.Relay.Solo.SHA_JUN_DENG)
   {
      TestMe_2 |= 0x0400;
   }
   if (yyj->DO.Relay.Solo.HIGH_TEMP_CHAIN)
   {
      TestMe_2 |= 0x0800;
   }
   if (yyj->DO.Relay.Solo.NO_WIND_CHAIN)
   {
      TestMe_2 |= 0x1000;
   }
//-----------------------------------------------
   TestMe_3 = 0x0000;
   if (yyj->DO.Relay.Solo.PANEL_RUN)
   {
      TestMe_3 |= 0x0001;
   }
   if (yyj->DO.Relay.Solo.PANEL_STANDBY)
   {
      TestMe_3 |= 0x0002;
   }
   if (yyj->DO.Relay.Solo.PANEL_FILTER)
   {
      TestMe_3 |= 0x0004;
   }
   if (yyj->DO.Relay.Solo.PANEL_ERR)
   {
      TestMe_3 |= 0x0008;
   }
//-----------------------------------------------
   TestMe_4 = 0x0000;
   if (yyj->DI.Solo.BOX_PANEL_KEY_RUN)
   {
      TestMe_4 |= 0x0001;
   }
   if (yyj->DI.Solo.BOX_PANEL_KEY_STANDBY)
   {
      TestMe_4 |= 0x0002;
   }
   if (yyj->DI.Solo.BOX_PANEL_KEY_REMOTE_RUN)
   {
      TestMe_4 |= 0x0004;
   }
   if (yyj->DI.Solo.BOX_PANEL_KEY_REMOTE_STANDBY)
   {
      TestMe_4 |= 0x0008;
   }
   if (yyj->Small.Solo.LocalPower)
   {
      TestMe_4 |= 0x0010;
   }
   if (yyj->Small.Solo.LocalStandby)
   {
      TestMe_4 |= 0x0020;
   }
   if (yyj->Small.Solo.RemotePower)
   {
      TestMe_4 |= 0x0040;
   }
   if (yyj->Small.Solo.RemoteStandby)
   {
      TestMe_4 |= 0x0080;
   }
//---------------------------------------------
   TestMe_5 = 0x0000;
   if (yyj->DI.Solo.INPUT_EMC)
   {
      TestMe_5 |= 0x0001;
   }
   if (yyj->DI.Solo.INPUT_FIRE_EMC)
   {
      TestMe_5 |= 0x0002;
   }
   if (yyj->DI.Solo.INPUT_NO_WIND)
   {
      TestMe_5 |= 0x0004;
   }
   if (yyj->DI.Solo.INPUT_CHU_XIAO)
   {
      TestMe_5 |= 0x0008;
   }
   if (yyj->DI.Solo.INPUT_ZHONG_XIAO)
   {
      TestMe_5 |= 0x0010;
   }
   if (yyj->DI.Solo.INPUT_YA_GAO_XIAO)
   {
      TestMe_5 |= 0x0020;
   }
   if (yyj->DI.Solo.INPUT_GAO_XIAO)
   {
      TestMe_5 |= 0x0040;
   }
   if (yyj->DI.Solo.INPUT_WIND_GATE_01)
   {
      TestMe_5 |= 0x0080;
   }
   if (yyj->DI.Solo.INPUT_WIND_GATE_02)
   {
      TestMe_5 |= 0x0100;
   }
   if (yyj->DI.Solo.INPUT_WIND_GATE_03)
   {
      TestMe_5 |= 0x0200;
   }
   if (yyj->DI.Solo.INPUT_WIND_GATE_04)
   {
      TestMe_5 |= 0x0400;
   }
   if (yyj->DI.Solo.INPUT_WIND_GATE_05)
   {
      TestMe_5 |= 0x0800;
   }
   if (yyj->DI.Solo.INPUT_WIND_GATE_06)
   {
      TestMe_5 |= 0x1000;
   }
   if (yyj->DI.Solo.INPUT_HEAT_HIGH_TEMP)
   {
      TestMe_5 |= 0x2000;
   }
   if (yyj->DI.Solo.INPUT_PRE_HEAT_HIGH_TEMP)
   {
      TestMe_5 |= 0x4000;
   }
   if (yyj->DI.Solo.INPUT_COLD_PROTECT)
   {
      TestMe_5 |= 0x8000;
   }
//---------------------------------------------
   TestMe_6 = 0x0000;
   if (yyj->DI.Solo.PANEL_KEY_RUN)
   {
      TestMe_6 |= 0x0001;
   }
   if (yyj->DI.Solo.PANEL_KEY_STANDBY)
   {
      TestMe_6 |= 0x0002;
   }
   if (yyj->DI.Solo.PANEL_KEY_NGT)
   {
      TestMe_6 |= 0x0004;
   }
   if (yyj->DI.Solo.SEL_MODE_FRQ_CVT)
   {
      TestMe_6 |= 0x0008;
   }
   if (yyj->DI.Solo.SEL_MODE_MANUAL_FRQ)
   {
      TestMe_6 |= 0x0010;
   }
   if (yyj->DI.Solo.SEL_TRIANGLE_START)
   {
      TestMe_6 |= 0x0020;
   }
   if (yyj->DI.Solo.SEL_STAR_START)
   {
      TestMe_6 |= 0x0040;
   }
   if (yyj->DI.Solo.SEL_MODE_FIX_FRQ)
   {
      TestMe_6 |= 0x0080;
   }
   if (yyj->DI.Solo.FC_FEEDBACK_RUN)
   {
      TestMe_6 |= 0x0100;
   }
   if (yyj->DI.Solo.FC_FEEDBACK_ERROR)
   {
      TestMe_6 |= 0x0200;
   }
   if (yyj->DI.Solo.FF_FEEDBACK_RUN)
   {
      TestMe_6 |= 0x0400;
   }
   if (yyj->DI.Solo.FF_FEEDBACK_ERR)
   {
      TestMe_6 |= 0x0800;
   }
   if (yyj->DI.Solo.SEL_SEASON_WINTER)
   {
      TestMe_6 |= 0x1000;
   }
   if (yyj->DI.Solo.SEL_SEASON_SUMMER)
   {
      TestMe_6 |= 0x2000;
   }
   if (yyj->DI.Solo.INPUT_WATER_SENSOR)
   {
      TestMe_6 |= 0x4000;
   }
   if (0)
   {
      TestMe_6 |= 0x8000;
   }
//----------------------------------------------
   if (yyj->DI.Solo.TRIANGLE_STAR_TIMESET)
   {
      TestMe_7 = yyj->Time.StarTime;
   }
//----------------------------------------------
}


uint16 ReadCOM2(YYJ_ALL_DEF *yyj, uint16 index)
{
//温度设定值
//湿度设定值
//按键状态
   if (index == 0)
   {
      return yyj->PanelLogic.TempSet;
   }
   if (index == 1)
   {
      return yyj->PanelLogic.RhSet;
   }
   if (index == 2)
   {
      yyj->state1 = 0;
      if (yyj->PanelLogic.Key.Solo.KeyStandby)
      {
         yyj->state1 |= 0x02;
      }
      if (yyj->PanelLogic.Key.Solo.KeyStart)
      {
         yyj->state1 |= 0x04;
      }
      if (yyj->PanelLogic.Key.Solo.KeySpare)
      {
         yyj->state1 |= 0x08;
      }
      if (yyj->PanelLogic.Key.Solo.KeyNgt)
      {
         yyj->state1 |= 0x10;
      }
      return yyj->state1;
   }
//显示温度值
//显示湿度值
//设备状态
//温度设定值
//湿度设定值
   if (index == 9)
   {
      return yyj->PanelFeedBack.AhuTmep01;
   }
   if (index == 10)
   {
      return yyj->PanelFeedBack.AhuRh01;
   }
   if (index == 11)
   {
      yyj->state2 = 0;
      if (yyj->PanelFeedBack.Bits.Solo.AhuFault)
      {
         yyj->state2 |= 0x01;
      }
      if (yyj->PanelFeedBack.Bits.Solo.HPEFault)
      {
         yyj->state2 |= 0x02;
      }
      if (yyj->PanelFeedBack.Bits.Solo.StandBy)
      {
         yyj->state2 |= 0x04;
      }
      if (yyj->PanelFeedBack.Bits.Solo.Run)
      {
         yyj->state2 |= 0x08;
      }
      if (yyj->PanelLogic.Key.Solo.KeySpare)
      {
         yyj->state2 |= 0x10;
      }
      if (yyj->PanelFeedBack.Bits.Solo.NgtPress)
      {
         yyj->state2 |= 0x20;
      }
      return yyj->state2;
   }
   if (index == 12)
   {
      return yyj->PanelLogic.TempSet;
   }
   if (index == 13)
   {
      return yyj->PanelLogic.RhSet;
   }
   return 0;
}

void WriteCOM2(YYJ_ALL_DEF *yyj, uint16 index, uint16 wdata)
{
//温度设定值
//湿度设定值
//按键状态
   if (index == 0)
   {
      yyj->PanelLogic.TempSet = wdata;
   }
   if (index == 1)
   {
      yyj->PanelLogic.RhSet = wdata;
   }
   if (index == 2)
   {
      yyj->state1 = wdata;
       yyj->PanelLogic.Key.Solo.KeyStandby = 0;
       yyj->PanelLogic.Key.Solo.KeyStart = 0;
       yyj->PanelLogic.Key.Solo.KeySpare = 0;
       yyj->PanelLogic.Key.Solo.KeyNgt = 0;
      if (yyj->state1 & 0x02)
      {
         yyj->PanelLogic.Key.Solo.KeyStandby = 1;
      }
      if (yyj->state1 & 0x04)
      {
         yyj->PanelLogic.Key.Solo.KeyStart = 1;
      }
      if (yyj->state1 & 0x08)
      {
         yyj->PanelLogic.Key.Solo.KeySpare = 1;
      }
      if (yyj->state1 & 0x10)
      {
         yyj->PanelLogic.Key.Solo.KeyNgt = 1;
      }
   }
//显示温度值
//显示湿度值
//设备状态
//温度设定值
//湿度设定值
   if (index == 9)
   {
      yyj->PanelFeedBack.AhuTmep01 = wdata;
   }
   if (index == 10)
   {
      yyj->PanelFeedBack.AhuRh01 = wdata;
   }
   if (index == 11)
   {
      yyj->state2 = wdata;
      yyj->PanelFeedBack.Bits.Solo.AhuFault = 0;
      yyj->PanelFeedBack.Bits.Solo.HPEFault = 0;
      yyj->PanelFeedBack.Bits.Solo.StandBy = 0;
      yyj->PanelFeedBack.Bits.Solo.Run = 0;
      yyj->PanelLogic.Key.Solo.KeySpare = 0;
      yyj->PanelFeedBack.Bits.Solo.NgtPress = 0;
      if (yyj->state1 & 0x01)
      {
         yyj->PanelFeedBack.Bits.Solo.AhuFault = 1;
      }
      if (yyj->state1 & 0x02)
      {
        yyj->PanelFeedBack.Bits.Solo.HPEFault = 1;
      }
      if (yyj->state1 & 0x04)
      {
         yyj->PanelFeedBack.Bits.Solo.StandBy = 1;
      }
      if (yyj->state1 & 0x08)
      {
         yyj->PanelFeedBack.Bits.Solo.Run = 1;
      }
      if (yyj->state1 & 0x10)
      {
         yyj->PanelLogic.Key.Solo.KeySpare = 1;
      }
      if (yyj->state1 & 0x20)
      {
         yyj->PanelFeedBack.Bits.Solo.NgtPress = 1;
      }
   }
   if (index == 12)
   {
      yyj->PanelLogic.TempSet = wdata;
   }
   if (index == 13)
   {
      yyj->PanelLogic.RhSet = wdata;
   }
}









