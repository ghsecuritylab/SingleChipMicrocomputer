
#ifndef _HW_PANEL_H_
#define _HW_PANEL_H_

typedef struct
{
    uint16 HW_AI_RA_TEMP;//�ط��¶�
    uint16 HW_AI_RA_RH;//�ط�ʪ��
    uint16 HW_AI_HWP_SET_TEMP;//�趨�¶�
    uint16 HW_AI_HWP_SET_RH;//�趨ʪ��
    uint16 HW_AI_PRESS;//�ط�ѹ��
    uint16 HW_AI_PRE_HEAT_TEMP;//Ԥ���¸�
    uint16 HW_AI_MANUAL_FRQ_SET;//�ֶ�����
}HwAi_Solo_Def;


typedef union
{
    uint16 All[7];
    HwAi_Solo_Def Solo;
}YYJ_AI_DEF;


typedef struct
{
    uint16 HW_AO_FC_FRQ;//��ƵƵ��
    uint16 HW_AO_HUMIDIFIER_CTRL;//��ʪ�������ź�
    uint16 HW_AO_COLD_GATE;//��ˮ��
    uint16 HW_AO_COLDHOT_GATE;//�䡢��ˮ��
    uint16 HW_AO_HOT_GATE;//��ˮ��
    uint16 HW_AO_HWP_DISP_TEMP;//(��չ��)��ʾ�¶�
    uint16 HW_AO_HWP_DISP_RH;//(��չ��)��ʾʪ��
    uint16 HW_AO_MANUAL_FRQ_SET;//�ֶ����Ƶ��
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
