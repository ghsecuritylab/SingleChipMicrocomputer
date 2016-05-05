
#ifndef _HW_PANEL_H_
#define _HW_PANEL_H_

typedef struct
{
    uint16 HW_AI_RA_TEMP;//回风温度
    uint16 HW_AI_RA_RH;//回风湿度
    uint16 HW_AI_HWP_SET_TEMP;//设定温度
    uint16 HW_AI_HWP_SET_RH;//设定湿度
    uint16 HW_AI_PRESS;//回风压差
    uint16 HW_AI_PRE_HEAT_TEMP;//预热温感
    uint16 HW_AI_MANUAL_FRQ_SET;//手动调速
}HwAi_Solo_Def;


typedef union
{
    uint16 All[7];
    HwAi_Solo_Def Solo;
}YYJ_AI_DEF;


typedef struct
{
    uint16 HW_AO_FC_FRQ;//变频频率
    uint16 HW_AO_HUMIDIFIER_CTRL;//加湿器控制信号
    uint16 HW_AO_COLD_GATE;//冷水阀
    uint16 HW_AO_COLDHOT_GATE;//冷、热水阀
    uint16 HW_AO_HOT_GATE;//热水阀
    uint16 HW_AO_HWP_DISP_TEMP;//(扩展板)显示温度
    uint16 HW_AO_HWP_DISP_RH;//(扩展板)显示湿度
    uint16 HW_AO_MANUAL_FRQ_SET;//手动输出频率
}HwAo_Solo_Def;

typedef union
{
    uint16 All[8];
    HwAo_Solo_Def Solo;
}YYJ_AO_DEF;

extern YYJ_AI_DEF POL_AI_Block;
extern YYJ_AO_DEF POL_AO_Block;
void DoAOPoll();
void DoAIFilter();
#endif
