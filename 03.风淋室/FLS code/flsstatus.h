



#ifndef FLSSTATUS_H
#define FLSSTATUS_H

typedef union 
{
   uint All;
   struct 
   {
    uint Emc:1;
    uint EnterFls:1;
    uint LeaveFls:1;
    uint Running:1;
    uint Idle:1;
    uint None:3;
    uint Step:8;

   }Solo;
}FLS_STATUS_DEF;


typedef union 
{
   uint All;
   struct 
   {
      uchar Fan           :1;
      uchar WorkLed       :1;
      uchar Light         :1;
      uchar Indoor        :1;
      uchar Outdoor       :1;
   }Solo;
}FLS_CONTROL_DEF;


typedef union 
{
   uint All;
   struct 
   {
  /*0*/  uint  QingZhanZaiGanYingQu         :1;   //你好、请站在感应区内
  /*1*/  uint  QingZhuanDongShenTi360Du     :1;   //正在工作、请转动身体360度
  /*2*/  uint  QingBuYaoChuMoKaiGuan        :1;   //正在工作、请你不要触摸开关
  /*3*/  uint  ChuiLinWanBi                 :1;   //吹淋完毕、请从后门进入
  /*4*/  uint  ChuiLinWanBiWaiMen                 :1;	  //吹淋完毕、请从外门离开
  /*5*/  uint  GongNengZhengChang      	    :1;   //自检完结、功能正常
  /*6*/  uint  SheBeiGuZhang      	    :1;   //设备故障、请联系维护人员
  /*7*/  uint  WelcomeUseCanlend            :1;   //欢迎使用能迪科技产品
  /*8*/  uint  WelcomeUseJinTian            :1;   //欢迎使用金田瑞麟产品

   }Solo;
}FLS_VOICE_TIP_DEF;


typedef union
{
   uint All;
   struct 
   {
 /*0*/    uint KeyEmc:1;
 /*1*/    uint KeyFan:1;
 /*2*/    uint KeyLight:1;
 /*3*/    uint KeyAdd:1;
 /*4*/    uint KeySub:1;	       
 /*5*/    uint Infrared:1;      //1:door open 0:door Close
 /*6*/    uint InsideMagnet:1;  //1:door open 0:door Close
 /*7*/    uint OutsideMagnet:1; //1:有人 0:无人
 /*8*/    uint TestIndoor:1;
 /*9*/    uint TestOutdoor:1;
 /*10*/   uint TestLight:1;
 /*11*/   uint TestFan:1;
   } Solo;
}FLS_KEY_DEF;


typedef struct 
{
   uint16 FanRunningTime;
   uint16 Crc;
}FLS_PARS_DEF;


typedef struct
{
   uint WorkTimer;
   uint secWorkTimer;
   uint VoiceDelay;
}FLS_Timers_DEF;


//typedef enum
//{
//     FLS_1=1;
//     FLS_2=2;
//     FLS_3=3;
//     FLS_4=4;
//     FLS_5=5;
//     FLS_6=6;
//     FLS_7=7;
//     FLS_8=8;
//}FLS_DATA_INDEX_Enum;



typedef struct 
{
   FLS_STATUS_DEF     Status;
   FLS_KEY_DEF        Input;
   FLS_KEY_DEF        KeyTreated;
   FLS_CONTROL_DEF    Output;
   FLS_CONTROL_DEF    FOutput;//force output
   FLS_VOICE_TIP_DEF  Voice;
   FLS_PARS_DEF       Par;
   FLS_Timers_DEF     Time;
}FLS_DEF;


extern FLS_DEF FLS1;

void FlsLeaving(FLS_DEF *Fls);
void FlsEntering(FLS_DEF *Fls);
void FlsDealAll(FLS_DEF *FLS);
void StatusDeal(FLS_DEF *Fls);





















#endif