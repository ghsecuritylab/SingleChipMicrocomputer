
#include "includes.h"


#define _____________________________________________
//void Panel_LED_Ctrl_Status()//门板16个LED显示控制
//{
//   Lamps.Solo.LAMP_AHU_RUNNING         =  ( Status.Solo.LAMP_AHU_RUNNING        ) ? ( 1 : 0 ); //运行
//   Lamps.Solo.LAMP_AHU_STANDBY         =  ( Status.Solo.LAMP_AHU_STANDBY        ) ? ( 1 : 0 ); //值机
//   Lamps.Solo.LAMP_EX01                =  ( Status.Solo.LAMP_EX01               ) ? ( 1 : 0 ); //备用1
//   Lamps.Solo.LAMP_AHU_ERROR           =  ( Status.Solo.LAMP_AHU_ERROR          ) ? ( 1 : 0 ); //故障报警
//   Lamps.Solo.LAMP_AHU_NOWIND          =  ( Status.Solo.LAMP_AHU_NOWIND         ) ? ( 1 : 0 ); //缺风报警
//   Lamps.Solo.LAMP_AHU_CHU_XIAO        =  ( Status.Solo.LAMP_AHU_CHU_XIAO       ) ? ( 1 : 0 ); //初效报警
//   Lamps.Solo.LAMP_AHU_ZHONG_XIAO      =  ( Status.Solo.LAMP_AHU_ZHONG_XIAO     ) ? ( 1 : 0 ); //中效报警
//   Lamps.Solo.LAMP_AHU_YA_GAO_XIAO     =  ( Status.Solo.LAMP_AHU_YA_GAO_XIAO    ) ? ( 1 : 0 ); //亚高效报警
//   Lamps.Solo.LAMP_AHU_GAO_XIAO        =  ( Status.Solo.LAMP_AHU_GAO_XIAO       ) ? ( 1 : 0 ); //高效报警
//   Lamps.Solo.LAMP_AHU_EHEAT_HIGH      =  ( Status.Solo.LAMP_AHU_EHEAT_HIGH     ) ? ( 1 : 0 ); //电热高温报警
//   Lamps.Solo.LAMP_AHU_PREHEAT_HIGH    =  ( Status.Solo.LAMP_AHU_PREHEAT_HIGH   ) ? ( 1 : 0 ); //预热高温报警
//   Lamps.Solo.LAMP_AHU_COLD_ERR        =  ( Status.Solo.LAMP_AHU_COLD_ERR       ) ? ( 1 : 0 ); //防冻报警
//   Lamps.Solo.LAMP_AHU_COLD_STOP_ERR   =  ( Status.Solo.LAMP_AHU_COLD_STOP_ERR  ) ? ( 1 : 0 ); //防冻停机报警
//   Lamps.Solo.LAMP_AHU_EXTERN_EMC_ERR  =  ( Status.Solo.LAMP_AHU_EXTERN_EMC_ERR ) ? ( 1 : 0 ); //外急停报警
//   Lamps.Solo.LAMP_AHU_FIRE_ERR        =  ( Status.Solo.LAMP_AHU_FIRE_ERR       ) ? ( 1 : 0 ); //消防报警
//   Lamps.Solo.LAMP_EX02                =  ( Status.Solo.LAMP_EX02               ) ? ( 1 : 0 ); //备用2
//}

#define   _________________________加热处理_________________________
void HeatDeal()
{
   if (系统处于工作状态)
   {
      if (NowValueTemp < SetValueTemp * 10)
      {
         uchar tmp;
         uint itmp = SetValueTemp * 10 - NowValueTemp;
         if (itmp < 5) //小于0.5度就不动作
         {
            itmp = 0;
         }
         itmp = itmp / 15;
         if (itmp > 7) //分为3级 0b0000 0111
         {
            itmp = 7;
         }
         Relays.Solo.EHEAT_LV01 = 0;   //一级再热
         Relays.Solo.EHEAT_LV02 = 0;   //二级再热
         Relays.Solo.EHEAT_LV03 = 0;   //三级再热
         tmp = itmp;
         if (testbit(tmp, 0))
         {
            Relays.Solo.EHEAT_LV01 = 1;
         }
         if (testbit(tmp, 1))
         {
            Relays.Solo.EHEAT_LV02 = 1;
         }
         if (testbit(tmp, 2))
         {
            Relays.Solo.EHEAT_LV03 = 1;
         }
      }
   }
   else
   {
      Relays.Solo.EHEAT_LV01 = 0;
      Relays.Solo.EHEAT_LV02 = 0;
      Relays.Solo.EHEAT_LV03 = 0;
   }
}

#define ___________________预热处理____________________________
void PreHeatDeal()
{
   uint PreNowValueTemp;
//   MakeWord(&ADCValues[10]);
//   PreNowValueTemp = (unsigned int)((unsigned long)iAllbuff1 * 1024 / 1000 / 2);
   POL_AI_Block.HW_AI_PRE_HEAT_TEMP //预热温感
   if (SysWorking())
   {
      if (PreNowValueTemp < 5 * 10)
      {
         uchar tmp;
         uint itmp = SetValueTemp * 10 - PreNowValueTemp;
         if (itmp < 5) //小于0.5度就不动作
         {
            itmp = 0;
         }
         itmp = itmp / 15;
         if (itmp > 7)
         {
            itmp = 7;
         }
         Relays.Solo.REHEAT_LV01 = 0;
         Relays.Solo.REHEAT_LV02 = 0;
         Relays.Solo.REHEAT_LV03 = 0;
         tmp = itmp;
         if (testbit(tmp, 0))
         {
            Relays.Solo.REHEAT_LV01 = 1;
         }
         if (testbit(tmp, 1))
         {
            Relays.Solo.REHEAT_LV02 = 1;
         }
         if (testbit(tmp, 2))
         {
            Relays.Solo.REHEAT_LV03 = 1;
         }
      }
   }
   else
   {
      Relays.Solo.REHEAT_LV01 = 0;
      Relays.Solo.REHEAT_LV02 = 0;
      Relays.Solo.REHEAT_LV03 = 0;
   }
}


void ExhaustFanCtrl() //排风机控制
{
   if (SysWorking()) //这里写启动条件 ||SysStandBy()完全值机时,不开排风机
   {
      if (Status.Solo.INPUT_WIND_GATE_01) // #1
      {
         Relays.Solo.AUTO_GATES_01 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_01 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_02) // #2
      {
         Relays.Solo.AUTO_GATES_02 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_02 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_03) // #3
      {
         Relays.Solo.AUTO_GATES_03 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_03 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_04) // #4
      {
         Relays.Solo.AUTO_GATES_04 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_04 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_05) // #5
      {
         Relays.Solo.AUTO_GATES_05 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_05 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_06) // #6
      {
         Relays.Solo.AUTO_GATES_06 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_06 = 0;
      }
   }
   else
   {
      Relays.Solo.AUTO_GATES_01 = 0;
      Relays.Solo.AUTO_GATES_02 = 0;
      Relays.Solo.AUTO_GATES_03 = 0;
      Relays.Solo.AUTO_GATES_04 = 0;
      Relays.Solo.AUTO_GATES_05 = 0;
      Relays.Solo.AUTO_GATES_06 = 0;
   }
   //负压排风
   if (PanelDataRead(48) != 0)
   {
      Relays.Solo.NGT_PRESS = 1;
   }
   else
   {
      Relays.Solo.NGT_PRESS = 0;
   }
}

void CoolingFan() //电柜散热风扇
{
   if (SysWorking())
   {
      Relays.Solo.BOX_COOLER = 1;
   }
   else
   {
      Relays.Solo.BOX_COOLER = 0;
   }
}








































































uchar SysBoot() //开机
{
   if (POL_DI_Block.Solo.INPUT_EMC == 0 || POL_DI_Block.Solo.INPUT_FIRE_EMC == 0 || POL_DI_Block.Solo.INPUT_NO_WIND == 0) //外急停 消防 缺风
   {
      return 0;
   }
   if (POL_DI_Block.Solo.BOX_PANEL_KEY_RUN) //硬接线的本地开机
   {
      return 1;
   }
   if (XXXXX != 0) //小控制面板的本地开机
   {
      return 1;
   }
   if (POL_DI_Block.Solo.BOX_PANEL_KEY_REMOTE_RUN || XXXXX) //硬接线的远程开机  小控制面板的远程开机
   {
      if (PanelDataRead(46) != 0) //情报面板的开机按键
      {
         return 1;
      }
   }
   //PC控制暂无
   return 0;
}


uchar SysStandby() //值机
{
   if (POL_DI_Block.Solo.BOX_PANEL_KEY_STANDBY) //硬接线的本地值机
   {
      return 1;
   }
   if (XXXXX != 0) //小控制面板的本地值机
   {
      return 1;
   }
   if (POL_DI_Block.Solo.BOX_PANEL_KEY_REMOTE_STANDBY || XXXXX) //硬接线的远程值机  小控制面板的远程值机
   {
      if (PanelDataRead(47) != 0) //情报面板的值机按键
      {
         return 1;
      }
   }
   //PC控制暂无
   return 0;
}

uchar SysWorking() //工作状态
{
   if ( (WorkStep < START_DISABLE) && (WorkStep != 0) )
   {
      return 1;
   }
   else
   {
      return 0;
   }
}




































