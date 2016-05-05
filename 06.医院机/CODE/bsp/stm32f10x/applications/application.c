
/*
1.保证通讯正常 
2.两种工作模式 MCU和PLC 
3.新协议和旧协议的兼容,新协议加功能 ,参数的调整和保存,扩展模块对应的控制位,传感器的量程应该可以设置
4.LED控制
5.调试记录
*/







/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2013-07-12     aozima       update for auto initial.
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <board.h>
#include <rtthread.h>


#ifdef  RT_USING_COMPONENTS_INIT
#include <components.h>
#endif  /* RT_USING_COMPONENTS_INIT */

#ifdef RT_USING_DFS
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>
#include <rtgui/calibration.h>
#endif




#include "board.h"

#include "includes.h"
#define DEBUG_MODE  0
UartType UartAppData1;
UartType UartAppData2;
UartType UartAppData3;
UartType UartAppData4;
UartType UartAppData5;
uchar DebugOut = 0;
//Cp_Rev_Def *cpcb1;
//New_Info_Panel_Def *InfoPanel;
Cp_Tcp_Dep Com2Tcp;
CpErrEnum Com2Ret = CP_ERR_OK;





ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t main_stack[512];

static struct rt_thread thread_main;


void app_hw_its_init()
{
   NVIC_InitTypeDef NVIC_InitStructure;

   /* Configure one bit for preemption priority */
   /*4位*4级*/
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

   /* Timer2中断*/
   NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   /* Timer3中断*/
   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   /*UART1*/
   NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   /* Uart1 interrupt configuration */

   /*UART2*/
   NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   /* Uart2 interrupt configuration */

   /*UART4*/
   NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   /* Uart4 interrupt configuration */

   /*UART3*/
   NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   /* Uart3 interrupt configuration */

   /*UART5*/
   NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   /* Uart5 interrupt configuration */

}

/***********************************/
void main_thread_entry(void *parameter)
{

   static uint32 MasterTaskCnt = 0x00;

   //ClkCfg();
   rt_hw_rtc_init();
   app_hw_its_init();
   UartPcbsInit();
   TIM3CntInit();
   OutPutIOcfg();
   InputIOcfg();
   AdcIOcfg();
   ComIOcfg();
   T1PWMInit();
   T8PWMInit();
   MdTcbInit();
   PolMdTcbInit();
   ADC_Configuration();

#define __IOInit__
   UART1_TXDIS();
   UART2_TXDIS();
   UART3_TXDIS();
   UART4_TXDIS();
   UART5_TXDIS();





   PID_Init();
   YYJ_Buff_SetTimeSize(&YYJ1);
   //可修改的保存数据
   if (ParSaveInit() != 0)
   {
      ClearFlashSave(&ParSave, 0);
      DoFlashSave(&ParSave);
   }



#define __MasterTask__
   //COM1 调试
   //USART_Configuration(USART1,19200);
   //COM2 情报面板
   USART_Configuration(USART2, YYJ1.OP.BaudSet.COM2, YYJ1.OP.StopBitSet.COM2, YYJ1.OP.ParitySet.COM2);
   //COM3 POL
   USART_Configuration(USART3, YYJ1.OP.BaudSet.COM3, YYJ1.OP.StopBitSet.COM3, YYJ1.OP.ParitySet.COM3);
   //COM4 高速485
   if (YYJ1.OP.COM4Shield != 0)
   {
      USART_Configuration(UART4, YYJ1.OP.BaudSet.COM4, YYJ1.OP.StopBitSet.COM4, YYJ1.OP.ParitySet.COM4);
   }

   //COM5 调试
   USART_Configuration(UART5, 115200, USART_StopBits_1, USART_Parity_No); 




#define ____________________TestHere____________________
   rt_kprintf("!!!!System Build %s--%s!!!!\r\n", __DATE__, __TIME__);

   //yyj init
   YYJ1.BuffLoad = YYJ_Buff_1Set;
   YYJ1.PidPar = YYJ_Buff_2Set;

   YYJ1.toStatus.All = 0;
   YYJ1.Status.Solo.Init = 1;
   rt_kprintf("YYJ_Status_to_Init: %05d\r\n", __LINE__);


   while (1)
   {
      rt_thread_delay(RT_TICK_PER_SECOND / 100); //10ms

      UartTimeOut(&UartAppData2);
      UartTimeOut(&UartAppData3);
      UartTimeOut(&UartAppData4);
      UartTimeOut(&UartAppData5);
      MasterTaskCnt++;
      Input165();
      InputDeal();
      ShellProc1();
      ShellProc2();
      ShellProc3();
      ShellProc4();
      ShellProc5();
      OutPutPoll();
      LedDisp();
      PolMdTimeOut();

      YYJ_ParSave();

      YYJ_BaudStopParityInit(&YYJ1);
      if (YYJ1.OP.SysPar.SaveBit.Solo.MCU1_PLC0 != 0)
      {
         YYJ_ALL_MAIN(&YYJ1);
      }
#define ____________________TestHere____________________
      if (MasterTaskCnt % 100 == 0)
      {
         if (YYJ1.OP.SysPar.SaveBit.Solo.MCU1_PLC0 != 0)
         {
            YYJ_TimeDeal(&YYJ1);
         }
         DoAIFilter();
         DoAOPoll();
         if (DebugOut == 1)
         {
            TRACEDATA("Input165 is", InputStateRec, 6);
         }
         if (DebugOut == 3)
         {
            TRACEDATA("Input165 is", POL_DI_Block.uint08All, 7);
         }
         if (DebugOut == 5)
         {
            TRACEDATA("Realy is", Relays.uint08All, 6);
         }
         if (DebugOut == 6)
         {
            TRACEDATA("Lamp is", Lamps.uint08All, 2);
         }
         if (DebugOut == 7)
         {
            TRACEDATA("AI is", POL_AI_Block.All, 7);
         }
      }
   }
}



FINSH_VAR_EXPORT(DebugOut, finsh_type_int, set the debut level);




#ifdef RT_USING_RTGUI
rt_bool_t cali_setup(void)
{
   rt_kprintf("cali setup entered\n");
   return RT_FALSE;
}

void cali_store(struct calibration_data *data)
{
   rt_kprintf("cali finished (%d, %d), (%d, %d)\n",
              data->min_x,
              data->max_x,
              data->min_y,
              data->max_y);
}
#endif /* RT_USING_RTGUI */

void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
   /* initialization RT-Thread Components */
   rt_components_init();
#endif

#ifdef  RT_USING_FINSH
   finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif  /* RT_USING_FINSH */

   /* Filesystem Initialization */
#if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
   /* mount sd card fat partition 1 as root directory */
   if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
   {
      rt_kprintf("File System initialized!\n");
   }
   else rt_kprintf("File System initialzation failed!\n");
#endif  /* RT_USING_DFS */

#ifdef RT_USING_RTGUI
   {
      extern void rt_hw_lcd_init();
      extern void rtgui_touch_hw_init(void);

      rt_device_t lcd;

      /* init lcd */
      rt_hw_lcd_init();

      /* init touch panel */
      rtgui_touch_hw_init();

      /* find lcd device */
      lcd = rt_device_find("lcd");

      /* set lcd device as rtgui graphic driver */
      rtgui_graphic_set_device(lcd);

#ifndef RT_USING_COMPONENTS_INIT
      /* init rtgui system server */
      rtgui_system_server_init();
#endif

      calibration_set_restore(cali_setup);
      calibration_set_after(cali_store);
      calibration_init();
   }
#endif /* #ifdef RT_USING_RTGUI */
}

int rt_application_init(void)
{
   rt_thread_t init_thread;

   rt_err_t result;

/*********************************************/
   result = rt_thread_init(&thread_main,

                           "main",

                           main_thread_entry, RT_NULL,

                           (rt_uint8_t *)&main_stack[0],

                           sizeof(main_stack), 15, 5);
   if (result == RT_EOK)

   {
      rt_thread_startup(&thread_main);
   }



#if (RT_THREAD_PRIORITY_MAX == 32)
   init_thread = rt_thread_create("init",
                                  rt_init_thread_entry, RT_NULL,
                                  2048, 8, 20);
#else
   init_thread = rt_thread_create("init",
                                  rt_init_thread_entry, RT_NULL,
                                  2048, 80, 20);
#endif

   if (init_thread != RT_NULL) rt_thread_startup(init_thread);

   return 0;
}

/*@}*/
