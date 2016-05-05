

#ifndef _FFU_H_
#define _FFU_H_
#define FFU1_EE_ADDR 10
#define FFU_EE_LEN 6



typedef enum 
{
     FFU_KeyNull = 0x00,
     FFU_KeyOnOff = 0x01,
     FFU_KeyAdd = 0x02,
     FFU_KeySub = 0x03,
}FFU_KEY_Enum;


typedef union
{
    uint16 All;
    struct
    {
        uint16 RELAY_12V:1;
        uint16 RELAY_24V_1:1;
        uint16 RELAY_24V_2:1;
        uint16 RELAY_50V:1;
        uint16 RELAY_110V:1;
        uint16 NONE:11;
    }Solo;
}FFU_IO_RELAY_Def;

typedef union
{
    uint16 All;
    struct
    {
        uint16 LEV_LED_01:1;
        uint16 LEV_LED_02:1;
        uint16 LEV_LED_03:1;
        uint16 LEV_LED_04:1;
        uint16 LEV_LED_05:1;
        uint16 LEV_LED_06:1;
        uint16 LEV_LED_07:1;
        uint16 LEV_LED_08:1;
        uint16 LEV_LED_09:1;
        uint16 LEV_LED_10:1;
        uint16 POWER:1;
        uint16 NONE:5;
    }Solo;
}FFU_IO_LED_Def;

typedef union
{
    uint16 All;
    struct
    {
        uint16 KeyOnOff:1;
        uint16 KeyAdd:1;
        uint16 KeySub:1;
        uint16 CurError:1;
        uint16 NONE1:4;
        uint16 Addr:8;
    }Solo;
}FFU_IO_DI_Def;

typedef union
{
    uint16 All;
    struct
    {
        uint16 Running:1;
        uint16 Stopped:1;
        uint16 Erroring01:1;
        uint16 Erroring02:1;
        uint16 Erroring03:1;
    }Solo;
}FFU_RUN_STATUS_Def;

typedef struct
{
    FFU_IO_RELAY_Def RL;
    FFU_IO_LED_Def LED;
    FFU_IO_DI_Def DIState;
    UINT16 Now_FanCur;
    UINT16 Now_FanRelayLvl;
    UINT16 Now_Status;
    UINT16 Now_FanBTLvl;
    UINT16 Now_FanError;
    UINT16 LastCtrl;
    UINT16 READ_SPARE[11];
    UINT16 Tel_Lvl_Set;
    UINT16 Tel_FFU_Run;
    UINT16 Tel_BTLvl_Set;
    UINT16 CTRL_SPARE[9];
}FFU_RUNING_Def;

typedef enum 
{
     FFU_ManualCtrl = 0,
     FFU_TelCtrl = 1,
     FFU_TEL_LVL = 20,
     FFU_TEL_RUN = 21,
     FFU_TEL_BTLVL = 22,
     FFU_TEL_LVL_FEEDBACK = 4,
     FFU_TEL_RUN_FEEDBACK = 5,
     FFU_TEL_BTLVL_FEEDBACK = 6,
}FFU_DATA_INDEX_Enum;

typedef struct
{
    FFU_IO_DI_Def DiScan;
    FFU_IO_DI_Def DiIn;
    FFU_IO_DI_Def DiTreat;
    UINT16 ErrStopTimer;
    UINT16 Tel_Lvl_Set;
    UINT16 Tel_FFU_Run;
    UINT16 Tel_BTLvl_Set;
}FFU_BUFF_Def;

typedef struct
{
    FFU_RUNING_Def Run;
    FFU_BUFF_Def Buff;
}FFUDataBaseDef;

#define RL000 0x00
#define RL012 0x01
#define RL241 0x02
#define RL242 0x04
#define RL050 0x08
#define RL110 0x10

#define RL_LV00 (RL000|RL000|RL000|RL000|RL000)
#define RL_LV01 (RL000|RL000|RL000|RL000|RL110)
#define RL_LV02 (RL012|RL000|RL000|RL000|RL110)
#define RL_LV03 (RL000|RL241|RL000|RL000|RL110)
#define RL_LV04 (RL012 |RL241|RL000|RL000|RL110)
#define RL_LV05 (RL000 |RL241|RL242|RL000|RL110)
#define RL_LV06 (RL012 |RL000|RL000|RL050|RL110)
#define RL_LV07 (RL000 |RL241|RL000|RL050|RL110)
#define RL_LV08 (RL012 |RL241|RL000|RL050|RL110)
#define RL_LV09 (RL000|RL241|RL242|RL050|RL110)
#define RL_LV10 (RL012|RL241|RL242|RL050|RL110)




void T0_Init(void);
void ExtIntInit();
extern __flash uint08 BT139_Lvl_Table[12];
void DispOff(FFUDataBaseDef *FFU);
extern FFU_KEY_Enum FUKey;
extern FFUDataBaseDef FFU1;
void LedBuffToIO(uint16 buff);
void DispLvl(FFUDataBaseDef *FFU);
void FFUDealOne(FFUDataBaseDef *FFU);
void FFUInitOne();
void FFU_MD_CTRL(FFUDataBaseDef *FFU,uint16 Index,uint16 Data);
uint16 FF_MD_READ(FFUDataBaseDef *FFU,uint16 Index);

#define FFU_BT139_ON() {SetBit(PORTB, 3);}
#define FFU_BT139_OFF() {ClrBit(PORTB, 3);}
#define FFU_BT139_REV() {RevBit(PORTB, 3);}

#endif
