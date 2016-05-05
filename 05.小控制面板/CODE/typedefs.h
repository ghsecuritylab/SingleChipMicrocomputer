
#ifndef TYPEDEFS_H
#define TYPEDEFS_H


/*******************************************/ 
typedef  char  int8,INT8;
typedef  int   int16,INT16;
typedef  long  int32,INT32;
typedef unsigned char  uchar,uint08,UIN8;
typedef unsigned int   uint,uint16,UIN16;
typedef unsigned long  uint32,UIN32;


/*******************************************/ 
typedef union
{
   uint All;
   struct {
      uint  _1ms          :1;   //1毫秒
      uint  _10ms         :1;   //10毫秒
      uint  _100ms        :1;   //100毫秒
      uint  _1000ms       :1;   //1000毫秒
      uint  _10000ms      :1;   //5000毫秒
      uint  Blink         :1;   //闪烁
      uint  FastBlink     :1;   //快闪
      uint  Timer         :9;   //定时时间    
   } Solo;
}RUNFLAG_DEF;
/*******************************************/ 
typedef union
{
   uchar All;
   struct {
      uchar Key_RemotePower      :1;     //远程控制开机按键
      uchar Key_RemoteStandby    :1;     //远程控制值机按键
      uchar Key_LocalPower       :1;     //本地控制开机按键 
      uchar Key_LocalStandby     :1;     //本地控制值机按键
      uchar Key_None             :4;  
   }Solo;
}DI_KEY_DEF;
/*******************************************/ 
typedef union
{
   uint All[2];
   struct {
// /*1*/      uint  Run                         :1;  //运行——绿
// /*2*/      uint  Standby                     :1;  //值机——绿
// /*3*/      uint  Power                       :1;  //电源——绿
// /*4*/      uint  Faultr                      :1;  //故障——红
// /*5*/      uint  Inefficient                 :1;  //初效——红
// /*6*/      uint  InEeffect                   :1;  //中效——红
// /*7*/      uint  Deigo                       :1;  //亚高——红
// /*8*/      uint  Efficient                   :1;  //高效——红
// /*9*/      uint  LackOfWind                  :1;  //缺风——红
// /*10*/     uint  ElectricHeatingTemperature  :1;  //电热高温——红
// /*11*/     uint  PreheatingTemperature       :1;  //预热高温——红
// /*12*/     uint  AntiFreezingAlarm           :1;  //防冻报警——红
// /*13*/     uint  FreezingStop                :1;  //防冻停机——红
// /*14*/     uint  EmergencyStop               :1;  //急停——红
// /*15*/     uint  FireControl                 :1;  //消防——红
// /*16*/     uint  Communication               :1;  //通讯——绿

 /*1*/      uint  Power                       :1;  //电源——绿
 /*2*/      uint  Run                         :1;  //运行——绿
 /*3*/      uint  Standby                     :1;  //值机——绿
 /*4*/      uint  Communication               :1;  //通讯——绿
 /*5*/      uint  Faultr                      :1;  //故障——红
 /*6*/      uint  Inefficient                 :1;  //初效滤网报警——红
 /*7*/      uint  FanFaultr                   :1;  //风机故障——红
 /*8*/      uint  InEeffect                   :1;  //中效滤网报警——红
 /*9*/      uint  LackOfWind                  :1;  //缺风报警——红
 /*10*/     uint  Deigo                       :1;  //亚高效滤网报警——红
 /*11*/     uint  ElectricHeatingTemperature  :1;  //电热高温——红
 /*12*/     uint  Efficient                   :1;  //高效滤网报警——红
 /*13*/     uint  PreheatingTemperature       :1;  //预热高温——红
 /*14*/     uint  FreezingStop                :1;  //防冻停机——红
 /*15*/     uint  AntiFreezingAlarm           :1;  //防冻停机报警——红
 /*16*/     uint  FireControlEmc              :1;  //消防/急停报警——红
/****/      uint  Buzzer                      :1;  //蜂鸣器
/****/      uint  RemotePower                 :1;  //远程控制_开机——绿
/****/      uint  RemoteStandby               :1;  //远程控制_值机——绿
/****/      uint  LocalPower                  :1;  //本地控制_开机——绿
/****/      uint  LocalStandby                :1;  //本地控制_值机——绿
/****/      uint  NONE                        :11; //空余
   }Solo;
}DO_LED_DEF;

/*******************************************/
typedef union
{
   uint All;
   struct
   {
      uint   RemotePower         :1 ;      //远程控制 1:开机 0:关机  
      uint   RemoteStandby       :1 ;      //远程控制 1:值机 0:关机  
      uint   LocalPower          :1 ;      //本地控制 1:开机 0:关机  
      uint   LocalStandby        :1 ;      //本地控制 1:值机 0:关机  
      uint   RemoteORLocal       :1 ;      //本地控制 1:值机 0:关机 
      uint   None                :11;      //空余
   }Solo;             
}DO_LED_CTRL_DEF;
/*******************************************/
typedef struct
{
   DO_LED_CTRL_DEF Ctrl;
   uint   RS485addr;   //485地址
   uint   Crc;         //CRC校验 
   uint   LED_16bit;   //16位LED               
}STATUS_DEF;
/*******************************************/ 
typedef struct
{       	     
   RUNFLAG_DEF       Runflag;
   DI_KEY_DEF        Input;
   DI_KEY_DEF        KeyTreated;
   DO_LED_DEF        Output;
   STATUS_DEF        Status;
}CTRL_DEF;
/*******************************************/ 




extern CTRL_DEF  CTR1;




#endif




