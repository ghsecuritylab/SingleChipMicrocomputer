
#ifndef _CTRL_H
#define _CTRL_H

#define _5SEC 5
#define _10SEC 10
#define _30SEC 30
#define _60SEC 60
#define _3MIN 3*60
#define _10MIN 10*60
#define _30MIN 30*60
#define _60MIN 60*60
#define _2HOUR 2*60*60



#define OpenHotWater  (yyj->AO.Solo.HW_AO_HOT_GATE*100/1024)     //0~100
#define OpenColdWater (yyj->AO.Solo.HW_AO_COLD_GATE*100/1024)    //0~100
#define OpenHotOrCold (yyj->AO.Solo.HW_AO_COLDHOT_GATE*100/1024) //0~100








//#define  NowTemp   (yyj->AI.Solo.HW_AI_RA_TEMP  * 1000 / 4096 / 2)        //回风温度 0~50
//#define  NowRH     (yyj->AI.Solo.HW_AI_RA_RH * 1000  / 4096 / 1)             //回风湿度 0~100

//--------------------------------------------------------------------------------------
#define  SetPress  (yyj->OP.SysPar.AirPress)     //100~500pa
//#define  NowPress  (yyj->AI.Solo.HW_AI_PRESS * 1000  / 4096 / 2)           //回风压差 0~500

#define  AtuoFreq     (yyj->AO.Solo.HW_AO_FC_FRQ)
#define  ManualFreq   (yyj->AO.Solo.HW_AO_MANUAL_FRQ_SET)
#define  NowFreq       (yyj->AI.Solo.HW_AI_MANUAL_FRQ_SET * 1000 / 2048) // 0~1000
//--------------------------------------------------------------------------------------
//#define  PreTemp       (yyj->AI.Solo.HW_AI_PRE_HEAT_TEMP * 1000 / 4096  / 2 / 5)  //预热温感 0~100
#define  SetPreStart   (yyj->OP.SysPar.PreHotStart) // 3~5
#define  SetPreEnd     (yyj->OP.SysPar.PreHotEnd)   // 10~12
//--------------------------------------------------------------------------------------



#define  STANDBY_FRQ 30
#define  MaxWindPower 3000
#define  RATEDWINDFLOW  1500 //额定风量1500
#define  STANDBY_FRQ 30
#define  MAXFANPRESS  3000    //最大风压3000pa
//额定风量*√(现在风压/最大风压) = 现在风量

//PWM输出的百分比
#define AO_PWM_OUT_0    0*1024/1000
#define AO_PWM_OUT_10   100*1024/1000
#define AO_PWM_OUT_20   200*1024/1000
#define AO_PWM_OUT_30   300*1024/1000
#define AO_PWM_OUT_40   400*1024/1000
#define AO_PWM_OUT_50   500*1024/1000
#define AO_PWM_OUT_60   600*1024/1000
#define AO_PWM_OUT_70   700*1024/1000
#define AO_PWM_OUT_80   800*1024/1000
#define AO_PWM_OUT_90   900*1024/1000
#define AO_PWM_OUT_100  1000*1024/1000

typedef struct
{
   YYJ_AI_DEF AIadjust;
   YYJ_AO_DEF AOadjust;
}YYJ_Adjust_Def;


typedef struct
{
   uint16 StartupTimer;    //初始化启动延时
   uint16 ShaJunDengTimer; //杀菌灯开启时间
   uint16 StarTime;        //星形启动时间
   uint16 NoWindTime;      //缺风延时
   uint16 NgtPressTime;    //负压排风延时
   uint16 ColdProtectTime; //防冻延时
   uint16 StopOffTime;     //关机延时
   uint16 StopCntTime;     //停机计数时间
   uint16 OpenColdTime;
   uint16 CloseColdTime;
   uint16 StopDelayTime;
}YYJ_TimePar_Def;


typedef struct
{
   uint16 PreHotStart; //设置开预热起始温度
   uint16 PreHotEnd;   //设置关预热结束温度
   uint16 FloatValve;  //扩展板浮点阀开度时间
   uint16 FreqMode;    //频率算法切换
   uint16 AirPress;    //送风压力设置值
   uint16 TmepRange;
   uint16 RhRange;
   uint16 PressRange;
   uint16 PreHeatRange;
   union 
   {
      uint16 All;
      struct
      {
	 uint16  MCU1_PLC0:1;
	 uint16  Nouse:15;
      }Solo;
   }SaveBit;
}YYJ_SYS_DEF;



typedef union
{
   uint16 All;
   struct {
      uint16 NowindFlag:1;       //缺风报警标志
      uint16 BlowerRunning:1;    //风机运行标志
      uint16 ColdStopFlag:1;     //防冻停机标志位
      uint16 OffStopFlag:1;      //关机停机标志位
      uint16 StopTimeFlag:1;
      uint16 HumidifierFlag:1;
      uint16 Sum0Win1:1;
      uint16 Nouse:4;
   }Solo;
}YYJ__Flags_Def;


typedef union
{
   uint08 All;
   struct {
      uint08 toInit:1;
      uint08 toRuning:1;
      uint08 toStandby:1;
      uint08 toColdStop:1;
      uint08 toOffStop:1;
      uint08 toError:1;
      uint08 Nouse:2;
   }
   Solo;
}YYJ_Change_Status;

typedef union
{
   uint16 All;
   struct {
      uint16 Init:1;
      uint16 Runing:1;
      uint16 Standby:1;
      uint16 Stop:1;
      uint16 Error:1;
   }
   Solo;
}YYJ_WorkMode_Status;



typedef union
{
   uint16 All[3];
   struct {
      uint16 LocalPower:1;    //小控制面板本地开机
      uint16 RemotePower:1;   //小控制面板远程开机
      uint16 LocalStandby:1;  //小控制面板本地值机
      uint16 RemoteStandby:1; //小控制面板远程值机
      uint16 NOUSE:12;
      uint16 LED16bit;
      uint16 SmallAddr;
   }Solo;
}YYJ_SmallCtrl_Panel;



typedef union
{
   uint16 All;
   struct {
      uint16 Run:1;           //工作 返回
      uint16 StandBy:1;       //值班 返回
      uint16 HPEFault:1;      //高效堵塞 返回
      uint16 NgtPress:1;      //负压 返回
      uint16 AhuFault:1;      //空调故障 返回
      uint16 HumidifierRun:1; //加湿器工作信号返回
      uint16 Sum0Win1:1;      //机组当前--工作模式
      uint16 EHeat01:1;       //一级电加热工作返回
      uint16 EHeat02:1;       //二级电加热工作返回
      uint16 EHeat03:1;       //三级电加热工作返回
      uint16 NoUse:6;
   }Solo;
}YYJ_Panel_Feedback_Bit_def;


typedef struct
{
   YYJ_Panel_Feedback_Bit_def Bits;
   uint16 AhuHotGate;            //空调热水阀--开度值
   uint16 AhuColdGate;           //空调冷水阀--开度值
   uint16 AhuWindPress;          //空调送风压力显示值
   uint16 AhuDifPress;           //房间压差----显示值
   uint16 AhuTmep01;             //1#空调温度--显示值
   uint16 AhuRh01;               //1#空调湿度--显示值
   uint16 AhuTmep02;             //2#空调温度--显示值
   uint16 AhuRh02;               //2#空调湿度--显示值
   uint16 AhuTmep03;             //3#空调温度--显示值
   uint16 AhuRh03;               //3#空调湿度--显示值
   uint16 NowTempSet;            //当前温度设定值
   uint16 NowRHSet;              //当前湿度设定值
}YYJ_Panel_Feedback_All_def;

typedef union
{
   uint16 All;
   struct {
      uint16 KeyStart:1;
      uint16 KeyStandby:1;
      uint16 KeyNgt:1;
      uint16 KeySpare:1;
      uint16 KeyNode:12;
   }Solo;
}YYJ_Panel_KEYS;

typedef struct
{
   YYJ_Panel_KEYS Key;
   uint16 TempSet;
   uint16 RhSet;
}YYJ_Panel_all_def;

typedef struct
{
   uint32 COM2;
   uint32 COM3;
   uint32 COM4;
}YYJ_BAUD_SET;

typedef struct
{
   uint16_t COM2;
   uint16_t COM3;
   uint16_t COM4;
}YYJ_STOPBIT_SET;

typedef struct
{
   uint16_t COM2;
   uint16_t COM3;
   uint16_t COM4;
}YYJ_PARITY_SET;

typedef struct
{
   uPidParaSet RHpid;
   uPidParaSet RHpidInv;
   uPidParaSet Coolpid;
   uPidParaSet Hotpid;
   uPidParaSet Freqpid;
   YYJ_TimePar_Def SetSize;
   YYJ_SYS_DEF SysPar;
   YYJ_BAUD_SET BaudSet;
   YYJ_STOPBIT_SET StopBitSet;
   YYJ_PARITY_SET ParitySet;
   YYJ_Adjust_Def Check;
   uint16 My485Addr;
   uint08 COM4Shield;
   uint08 COM2poll;
   uint16 SmallAddr;
   uint16 FlashCRC;
}YYJ_OPTIONS;

typedef struct
{
   uPID RHpid;
   uPID RHpidInv;
   uPID Coolpid;
   uPID Hotpid;
   uPID Freqpid;
}YYJ_PID;

typedef struct
{
   YYJ_OPTIONS OP;
   YYJ_TimePar_Def Time;
   YYJ_PID PID;
   YYJ_DI_DEF DI;
   YYJ_AI_DEF AI;
   YYJ_DO_DEF DO;
   YYJ_AO_DEF AO;
   YYJ__Flags_Def   Flag;
   YYJ_Change_Status toStatus;
   YYJ_WorkMode_Status Status;
   YYJ_SmallCtrl_Panel Small;
   YYJ_Panel_all_def Panel[3];
   YYJ_Panel_all_def PanelLogic;
   YYJ_Panel_Feedback_All_def PanelFeedBack;
   uint16 WorkStep;
   uint16 ExtendPanel;
   uint08 state1;
   uint08 state2;
   void (*BuffLoad)();
   void (*PidPar)();

}YYJ_ALL_DEF;



void YYJ_PanelExtendChange(YYJ_ALL_DEF *yyj);
uint16 YYJ_Communication_Read(YYJ_ALL_DEF *yyj, uint16 index);
void YYJ_Communication_Write(YYJ_ALL_DEF *yyj, uint16 index, uint16 wdata);
uint16 YYJ_Read_SmallPanel(YYJ_ALL_DEF *yyj, uint16 index);
void YYJ_Write_SmallPanel(YYJ_ALL_DEF *yyj, uint16 index, uint16 wdata);
uint16 YYJ_ReadPID(YYJ_OPTIONS *pid, uint16 index);
void YYJ_WritePID(YYJ_OPTIONS *pid, uint16 index, uint16 wdata);
uint16 YYJ_ReadPar(YYJ_OPTIONS *pdata, uint16 index);
void YYJ_WritePar(YYJ_OPTIONS *pdata, uint16 index, uint16 wdata);


void YYJ_Buff_1Set();
void YYJ_Buff_2Set();
void YYJ_Buff_SetTimeSize(YYJ_ALL_DEF *yyj);

void YYJ_TimeDeal(YYJ_ALL_DEF *yyj);
void YYJ_ALL_Alarm(YYJ_ALL_DEF *yyj);
void YYJ_ALL_MAIN(YYJ_ALL_DEF *yyj);
void YYJ_PanelFeedBack(YYJ_ALL_DEF *yyj);

void FFWORK(YYJ_ALL_DEF *yyj);
void FCWORK(YYJ_ALL_DEF *yyj);
void FanFreqCtrl(YYJ_ALL_DEF *yyj);

void CoolPidCompute(YYJ_ALL_DEF *yyj);
void HotPidCompute(YYJ_ALL_DEF *yyj);
void RHPidCompute(YYJ_ALL_DEF *yyj);
void RHPidInvCompute(YYJ_ALL_DEF *yyj);
void FreqCompute(YYJ_ALL_DEF *yyj);

void YYJ_SetRange(YYJ_ALL_DEF *yyj);
void YYJ_Panel_Extend1(YYJ_ALL_DEF *yyj);
void YYJ_SetTmepOrRh(YYJ_ALL_DEF *yyj);
void YYJ_ExtendChange(YYJ_ALL_DEF *yyj);
uint16 YYJ_TestRead(YYJ_ALL_DEF *yyj, uint16 index);
void YYJ_TestWrite(YYJ_ALL_DEF *yyj, uint16 index, uint16 Data);
void YYJ_TestFunction(YYJ_ALL_DEF *yyj);
void YYJ_PIDSetParInit(uPidParaSet *p2data, sint16 Kp, sint16 Ki, sint16 Kd, sint16 SampleTime, sint16 DeadBand);
void YYJ_BaudStopParityInit(YYJ_ALL_DEF *yyj);
uint16 YYJ_StopBitReadSet(YYJ_OPTIONS *pdata);
uint16 YYJ_ParityReadSet(YYJ_OPTIONS *pdata);
void YYJ_StopBitWriteSet(YYJ_OPTIONS *pdata,  uint16 Data);
void YYJ_ParityWriteSet(YYJ_OPTIONS *pdata,  uint16 Data);
uint16 YYJ_Adjust_Read(YYJ_ALL_DEF *yyj, uint16 index);
void YYJ_Adjust_Write(YYJ_ALL_DEF *yyj, uint16 index, uint16 Data);

uint16 ReadCOM2(YYJ_ALL_DEF *yyj, uint16 index);
void WriteCOM2(YYJ_ALL_DEF *yyj, uint16 index, uint16 wdata);

extern YYJ_ALL_DEF YYJ1;


#endif
