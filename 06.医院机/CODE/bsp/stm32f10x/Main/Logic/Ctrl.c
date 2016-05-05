
#include  "includes.h"



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