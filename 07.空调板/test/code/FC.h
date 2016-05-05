
#ifndef _FC_H_
#define _FC_H_
#include "includes.h"


#define  FC_SETTING_MAX  24
#define FC_EE_ADDR 0
#define FC_EE_LEN 24

typedef enum
{
   FC_KeyNull = 0x00,
   FC_KeyStartStop = 0x01,
   FC_KeyMode = 0x02,
   FC_KeyFanlvl = 0x03,
   FC_KeyAdd = 0x04,
   FC_KeySub = 0x05,
}FC_KEY_Enum;

typedef struct
{
   uint16 OnOffDelayTimer;
   uint16 FanLvlDelayTimer;
   uint16 TempCtrlDelayTimer;
//  uint16  BackLightDelayTimer;
   uint16 ModeSwDelayTimer;
   uint16 TempChangeTimer;
   uint16 KeyDelayTimer;
   uint32 CloseTimer;
   uint32 OpenTimer;
}FC_WorkingTimer_Def;

typedef struct
{
   /* 0000*/   uint16 SetTemp;
   /* 0001*/   uint16 FanLvlSet;
   /* 0002*/   uint16 ModeSet;
   /* 0003*/   uint16 SetTime;
   /* 0004*/   uint16 ManualHigh;
   /* 0005*/   uint16 ManualMed;
   /* 0006*/   uint16 ManualLow;
   /* 0004*/   uint16 SetTempMax;
   /* 0005*/   uint16 SetTempMin;
   /* 0004*/   uint16 SetFanVoltMax;
   /* 0005*/   uint16 SetFanVoltMin;
   /* 0007*/   uint16 TempCtrlDelay;
   /* 0008*/   uint16 FanLvlSwDelay;
   /* 0009*/   uint16 ModeSwDelay;
   /* 0010*/   uint16 BackLightDelay;
   /* 0011*/   uint16 AutoHighDiffTemp;
   /* 0012*/   uint16 AutoMedDiffTemp;
   /* 0013*/   uint16 AutoLowDiffTemp;
   uint16 SolenoidValveMax;
   uPidParaSet FCpidPar;
///* 0016*/   uint16 RoomTemp;
///* 0017*/   uint16 RoomTempAid;
///* 0018*/   uint16 RoomTempKvalue;
   uint16 RunCrc;
}FC_RUNING_Def;


typedef union
{
   uint16 All;
   struct {

      uint16 Started:1;
      uint16 Cool:1;
      uint16 Hot:1;
      uint16 Sleep:1;
      uint16 Time2Start:1;
      uint16 Time2Stop:1;
      uint16 FanLvlHigh:1;
      uint16 FanLvlMed:1;
      uint16 FanLvlLow:1;
      uint16 FanLvlAuto:1;
      uint16 RelayH:1;
      uint16 RelayM:1;
      uint16 RelayL:1;
      uint16 FloatRelayOn:1;
      uint16 FloatRelayOff:1;
   }Solo;

}FC_SysState_Def;

typedef struct
{
   /* 0000*/   uint16 SetTemp;
   /* 0001*/   uint16 FanLvlSet;
   /* 0002*/   uint16 ModeSet;
}FC_SL_Def;

typedef union
{
   uint16 All;
   struct {
      uint16 Addr:8;
      uint16 StartStop:1;
      uint16 Mode:1;
      uint16 Fanlvl:1;
      uint16 KeyAdd:1;
      uint16 KeySub:1;
      uint16 ManualHigh:1;
      uint16 ManualMed:1;
      uint16 ManualLow:1;
   }Solo;

}FC_DIState_Def;

typedef union
{
   uint16 All;
   struct {
      uint16 Blink:1;
      uint16 FastBlink:1;
      uint16 HourBlink:1;
      uint16 MinBlink:1;
      uint16 _1msFlag:1;
      uint16 _2msFlag:1;
      uint16 _4msFlag:1;
      uint16 _10msFlag:1;
      uint16 _20msFlag:1;
      uint16 _1000msFlag:1;
      uint16 _10000msFlag:1;
      uint16 _nmsFlag:1;
      uint16 KeySwitch:1;
   }solo;
}FC_RunFlag_Def;

typedef struct
{
   FC_SysState_Def Sys;
   FC_DIState_Def DI;
}FC_State_Def;

typedef union
{
   uint08 All;
   struct {
      uint08 coolTempOverSet:1;
      uint08 coolTempOverSetLow:1;
      uint08 coolTempOverSetMed:1;
      uint08 coolTempOverSetHigh:1;
      uint08 hotTempOverSet:1;
      uint08 hotTempOverSetLow:1;
      uint08 hotTempOverSetMed:1;
      uint08 hotTempOverSetHigh:1;
   }solo;
}FC_TempState_Def;


typedef struct
{
   /* 0025*/   uint16 ResetState;
   /* 0026*/   uint16 AnalogOut01;
   /* 0027*/   uint16 AnalogOut02;
   /* 0028*/   uint16 RoomTemp;
   /* 0029*/   uint16 RoomTempAid;
   /* 0030*/   uint16 RoomTempKvalue;
                    uint16 MasterSetTemp;
                    uint16 LastMasterSetTemp;
                    uint16 MasterSetMode;
                    uint16 LastMasterSetMode;
                    uint16 MasterSetFanlvl;
                    uint16 LastMasterSetFanlvl;
                    uint16 MasterStarted;
                    uint16 LastMasterStarted;
   FC_TempState_Def TempState;
   FC_TempState_Def TempStateTreat;
   FC_DIState_Def DiScan;
   FC_DIState_Def DiIn;
   FC_DIState_Def DiTreat;
   FC_SL_Def RunTreat;
   FC_RunFlag_Def Flag;
   FC_WorkingTimer_Def WorkTimer;
   Bitsdef KeyTmp1;
   uint08 KeyStep;

}FC_BUFF_Def;

typedef struct
{
   FC_RUNING_Def Run;
   FC_BUFF_Def Buff;
   FC_State_Def State;
   uPID FCpid;
}FCDataBaseDef;

typedef struct
{
   uint16 Default;
   uint16 Max;
   uint16 Min;
   uint08 Decima;
}FC_PAR_Cfg;

extern const FC_PAR_Cfg FCParCfg[FC_SETTING_MAX];
extern FCDataBaseDef FC1;
extern uint16 nowSolenoidValve;
extern uint08 StartOne;
extern uchar speedTI;
extern uint16 speedCnt;
void FCInitOne();
void FCKeyScan(FCDataBaseDef *FC);
void AdcGetAll(FCDataBaseDef *FC);
void FCAnalogOutSet(FCDataBaseDef *FC);
void FCKeyScan(FCDataBaseDef *FC);
void FCURun(FCDataBaseDef *FC);
void FCRelayOutput(FCDataBaseDef *FC);
void FCWorkTime(FCDataBaseDef *FC);
void FCEepromSave(FCDataBaseDef *FC);
void ResetDeal(FCDataBaseDef *FC);
void TestSpeed();
#endif

