
#ifndef DEVICE_DEAL_H
#define DEVICE_DEAL_H


typedef union
{
    uint08 All;
    struct  {
        uint08 Air01H:1;   //Error Air01H
        uint08 Air01L:1;   //Error Air01L
        uint08 Air02H:1;   //Error Air02H
        uint08 Air02L:1;   //Error Air02L
        uint08 Air03H:1;   //Error Air03H
        uint08 Air03L:1;   //Error Air03L
        uint08 Air04H:1;   //Error Air04H
        uint08 Air04L:1;   //Error Air04L
    }Solo;
}Air_ErrH_Def;

typedef union
{
    uint08 All;
    struct  {
        uint08 Air05H:1;   //Error Air05H
        uint08 Air05L:1;   //Error Air05L
        uint08 Air06H:1;   //Error Air06H
        uint08 Air06L:1;   //Error Air06L
        uint08 Air07H:1;   //Error Air07H
        uint08 Air07L:1;   //Error Air07L
        uint08 Air08H:1;   //Error Air08H
        uint08 Air08L:1;   //Error Air08L
    }Solo;
}Air_ErrL_Def;

typedef union
{
    uint08 All;
    struct  {
        uint08 PumpRunning:1;
        uint08 PumpErr:1;
        uint08 FireAlarm:1;
        uint08 CPT_ON:1;
        uint08 unused:4;
    }Solo;
}Misc_State_Def;


typedef union
{
    uint08 All;
    struct  {
        uint08 PumpStart:2; //写入为设置; 读取为当前的泵状态;  当写入后,指定时间没有反应其值将回到原始状态 
        uint08 unused:5;
        uint08 ScreenLock:1;   //1 时候现场界面锁定，0为现场参数远程可调 
    }Solo;
}Misc_Ctrl_Def;


typedef union
{
    uint08 All;
    struct  {
        uint08 start:2;       
        uint08 stop:2;   
        uint08 reset:2;   
        uint08 unused:2;      
    }Solo;
}OpTimer_key_Def;


typedef union
{
    uint08 All;
    struct  {
        uint08 start:2;       
        uint08 stop:2;   
        uint08 reset:2;   
        uint08 sets:2;      
    }Solo;
}AnTimer_key_Def;

typedef union
{
    uint08 All;
    struct  {
        uint08 start:2;       
        uint08 standby:2;     
        uint08 stop:2;   
        uint08 spare:2;                  
    }Solo;
}AHU_key_Def;

typedef union
{
    uint08 All;
    struct  {
        uint08 Running:1;       
        uint08 StandBy:1;     
        uint08 GaoXiao:1;   
        uint08 Nagative:1;       
        uint08 AHUErr:1;            
        uint08 unused:3;            
    }Solo;
}AHU_Status_Def;

typedef union
{
    uint08 All;
    struct  {
        uint08 Lamp01:2;       
        uint08 Lamp02:2;     
        uint08 Lamp03:2;   
        uint08 Lamp04:2;                  
    }Solo;
}Lamp_Key_Def1;

typedef union
{
    uint08 All;
    struct  {
        uint08 Lamp05:2;       
        uint08 Lamp06:2;     
        uint08 Lamp07:2;   
        uint08 Lamp08:2;                  
    }Solo;
}Lamp_Key_Def2;

typedef union
{
    uint08 All;
    struct  {
        uint08 Lamp09:2;       
        uint08 Lamp10:2;     
        uint08 Lamp11:2;   
        uint08 Lamp12:2;                  
    }Solo;
}Lamp_Key_Def3;


typedef union
{
    uint08 All;
    struct  {
        uint08 phoneStart:2;       
        uint08 CallStart:2;     
        uint08 musicStart:2;   
        uint08 musicAlt:2;                  
    }Solo;
}phone_Key_Def1;

typedef union
{
    uint08 All;
    struct  {
        uint08 redial:2;       
        uint08 mulit_call:2;     
        uint08 mute:2;   
        uint08 unused:2;                  
    }Solo;
}phone_Key_Def2;

typedef union
{
    uint08 All;
    struct  {
        uint08 CallingIn:1;       
        uint08 unused:7;                  
    }Solo;
}phone_status_Def;

typedef union
{
    uint08 All[10];
    struct  {
        uint08 Num01:4;     
        uint08 Num02:4;   
        uint08 Num03:4;   
        uint08 Num04:4;   
        uint08 Num05:4;   
        uint08 Num06:4;     
        uint08 Num07:4;   
        uint08 Num08:4;   
        uint08 Num09:4;   
        uint08 Num10:4; 
        uint08 Num11:4;     
        uint08 Num12:4;   
        uint08 Num13:4;   
        uint08 Num14:4;   
        uint08 Num15:4; 
        uint08 Num16:4;     
        uint08 Num17:4;   
        uint08 Num18:4;   
        uint08 Num19:4;   
        uint08 Num20:4;              
    }Solo;
}phone_DialArray_Def;



typedef union
{
    uint08 All;
    struct  {
        uint08 Key1:2;       
        uint08 Key2:2;     
        uint08 Key3:2;   
        uint08 Key4:2;                  
    }Solo;
}common_Key_Def;

typedef union
{
    uint08 All;
    struct  {
        uint08 Start:2;       
        uint08 Next:2;     
        uint08 Pre:2;   
        uint08 unused:2;                   
    }Solo;
}Mp3Key_Def;

typedef union
{
    uint08 All;
    struct  {
        uint08 Volume:4;       
        uint08 LoadSel:4;                  
    }Solo;
}Spk_Def;


typedef struct  {
/*0x2001*/   Air_ErrL_Def AirErrorL;
/*0x2002*/   Air_ErrH_Def AirErrorH;
/*0x2003*/   Misc_State_Def MiscStates;
/*0x2004*/   Misc_Ctrl_Def MiscCtrls;
/*0x2005*/   uint08 unused1;
/*0x2006*/   uint08 OperateTimerH ;
/*0x2007*/   uint08 OperateTimerM ;
/*0x2008*/   uint08 OperateTimerL ;
/*0x2009*/   uint08 AnaesthesiaTimerH ;
/*0x200A*/   uint08 AnaesthesiaTimerM ;	
/*0x200B*/   uint08 AnaesthesiaTimerL ;	
/*0x200C*/   OpTimer_key_Def OpTimerKey ;	
/*0x200D*/   AnTimer_key_Def AnTimerKey ;	
/*0x200E*/   uint08 TempSet;
/*0x200F*/   uint08 RHSet;
/*0x2010*/   uint08 DispTempH;
/*0x2011*/   uint08 DispTempL;
/*0x2012*/   uint08 DispRhH;
/*0x2013*/   uint08 DispRhL;
/*0x2014*/   AHU_key_Def  AHUKey;
/*0x2015*/   AHU_Status_Def AHUState;
/*0x2016*/   uint08 HotGatePercent;
/*0x2017*/   uint08 ColdGatePercent;
/*0x2018*/   uint08 WindOputPress;
/*0x2019*/   uint08 RoomPress;
/*0x201A*/   uint08 unused2;
/*0x201B*/   uint08 unused3;
/*0x201C*/   uint08 unused4;
/*0x201D*/   uint08 unused5;
/*0x201E*/   Lamp_Key_Def1 LampKey1;
/*0x201F*/   Lamp_Key_Def2 LampKey2;
/*0x2020*/   Lamp_Key_Def3 LampKey3;
/*0x2021*/   phone_Key_Def1 PhKey1;
/*0x2022*/   phone_Key_Def2 PhKey2;
/*0x2023*/   phone_status_Def PhState;
/*0x2024*/   uint08 PhVolume;
/*0x2025*/   uint08 BGMVolume;
/*0x2026*/   uint08 CallingVolume;
/*0x2027*/   Spk_Def BigSpkVolume;
/*0x2028*/   Mp3Key_Def Mp3Key;
/*0x2029*/   uint08 Mp3Volume;
/*0x202A*/   uint08 DialNum[10];
/*0x202B*/  // uint08 DialNum02;
/*0x202C*/  // uint08 DialNum03;
/*0x202D*/  // uint08 DialNum04;
/*0x202E*/  // uint08 DialNum05;
/*0x202F*/  // uint08 DialNum06;
/*0x2030*/  // uint08 DialNum07;
/*0x2031*/  // uint08 DialNum08;
/*0x2032*/  // uint08 DialNum09;
/*0x2033*/  // uint08 DialNum10;
/*0x2034*/   uint08 RTCHH;
/*0x2035*/   uint08 RTCH;
/*0x2036*/   uint08 RTCL;
/*0x2037*/   uint08 RTCLL;
/*0x20XX*/   uint08 SetTempRec;
/*0x20XX*/   uint08 SetRhRec;
}New_Info_Panel_Def;




typedef enum 
{
    CP02_CMD_ADDR = 0x001,
    CP02_START_ADDR1 = 0x2001,
    CP02_END_ADDR1 = 0x2037,
    CP02_START_ADDR2 = 0x9001,
    CP02_END_ADDR2 = 0x9010,
    CP02_9000_START = 0x34,
}Cp02AddrEnum;

typedef enum 
{
    FORCE_ON = 0x03,
    FORCE_OFF = 0x02,
    NOW_ON =  0x01,
    NOW_OFF = 0x00,
}KEY_CTRL_DEF;

CpErrEnum Cp02WriteDeal(uint08 *RawData, uint16 trgaddr, uint08 len);

#endif 

















