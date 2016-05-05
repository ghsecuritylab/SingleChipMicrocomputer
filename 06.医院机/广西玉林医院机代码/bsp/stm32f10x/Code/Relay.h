

#ifndef RELAY_H
#define RELAY_H


typedef union
{
    uint08 uint08All[8];
    uint16 uint16All[4];
    struct  
    {
/*00*/   uint16 FAN_FC_START:1;//�ͷ����Ƶ
/*01*/   uint16 FAN_FF_START:1;//�ͷ����Ƶ
/*02*/   uint16 FAN_TRIANGLE_START:1;//�ͷ��������
/*03*/   uint16 FAN_STAR_START:1;//�ͷ������
/*04*/   uint16 FAN_COOLER:1;//�ͷ��ɢ�ȷ���
/*05*/   uint16 EHEAT_LV01:1;//һ������
/*06*/   uint16 EHEAT_LV02:1;//��������
/*07*/   uint16 EHEAT_LV03:1;//��������
/*08*/   uint16 REHEAT_LV01:1;//һ��Ԥ��
/*09*/   uint16 REHEAT_LV02:1;//����Ԥ��
/*10*/   uint16 REHEAT_LV03:1;//����Ԥ��
/*11*/   uint16 BOX_COOLER:1;//�������ɢ�ȷ���
/*12*/   uint16 STOP_WARMING:1;//ͣ������
/*13*/   uint16 NGT_PRESS:1;//��ѹ�ŷ�
/*14*/   uint16 SHA_JUN_DENG:1;//ɱ����
         uint16 UNUSED02:1;//δʹ��                                                                                                                                            
/*15*/   uint16 AUTO_GATES_01:1;//�ŷ���Զ���1
/*16*/   uint16 AUTO_GATES_02:1;//�ŷ���Զ���2
/*17*/   uint16 AUTO_GATES_03:1;//�ŷ���Զ���3
/*18*/   uint16 AUTO_GATES_04:1;//�ŷ���Զ���4
/*19*/   uint16 AUTO_GATES_05:1;//�ŷ���Զ���5
/*20*/   uint16 AUTO_GATES_06:1;//�ŷ���Զ���6
         uint16 AUTO_GATES_UNUSED01:1;//δʹ��
         uint16 AUTO_GATES_UNUSED02:1;//δʹ��
         uint16 AUTO_GATES_UNUSED03:1;//δʹ��
         uint16 AUTO_GATES_UNUSED04:1;//δʹ��
         uint16 AUTO_GATES_UNUSED05:1;//δʹ��
         uint16 AUTO_GATES_UNUSED06:1;//δʹ��
         uint16 AUTO_GATES_UNUSED07:1;//δʹ��
         uint16 AUTO_GATES_UNUSED08:1;//δʹ��
         uint16 AUTO_GATES_UNUSED09:1;//δʹ��
         uint16 AUTO_GATES_UNUSED10:1;//δʹ��
/*21*/   uint16 FC_CTRL_SPARE:1;//(��Ƶ������)����
/*22*/   uint16 FRESH_AIR_GATE_FIX:1;//�·�������緧
/*23*/   uint16 FRESH_AIR_GATE_TIGHT:1;//�·���ܱշ�
/*24*/   uint16 FC_CTRL_START:1;//(��Ƶ������)����
/*25*/   uint16 FC_CTRL_STANDBY:1;//(��Ƶ������)ֵ��:1  ȫ��:0
/*26*/   uint16 HIGH_TEMP_CHAIN:1;//��������
/*27*/   uint16 NO_WIND_CHAIN:1;//ȱ������ 
/*28*/   uint16 HUMIDIFIER_GATE:1;//��ʪ����ŷ�
/*29*/   uint16 HUMIDIFIER_START:1;//��ʪ������
/*30*/   uint16 HUMIDIFIER_CHAIN:1;//��ʪ������
/*31*/   uint16 PANEL_RUN:1;//(��չ��)����
/*32*/   uint16 PANEL_STANDBY:1;//(��չ��)ֵ��
/*33*/   uint16 PANEL_FILTER:1;//(��չ��)����
/*34*/   uint16 PANEL_ERR:1;//(��չ��)����
    }Solo;
}YYJ_DOR_DEF;


typedef union  //AHU״̬�����ָʾ
{
    uint08 uint08All[2];
    uint16 uint16All[1];
    struct  
    {
/*00*/ uint16 LAMP_AHU_RUNNING:1;//�������е� 
/*01*/ uint16 LAMP_AHU_STANDBY:1;//����ֵ����
/*02*/ uint16 LAMP_EX01:1;//����1
/*03*/ uint16 LAMP_AHU_ERROR:1;//������ϵ�
/*04*/ uint16 LAMP_AHU_NOWIND:1;//ȱ�籨����
/*05*/ uint16 LAMP_AHU_CHU_XIAO:1;//��Ч������
/*06*/ uint16 LAMP_AHU_ZHONG_XIAO:1;//��Ч������
/*07*/ uint16 LAMP_AHU_YA_GAO_XIAO:1;//�Ǹ�Ч������
/*08*/ uint16 LAMP_AHU_GAO_XIAO:1;//��Ч������
/*09*/ uint16 LAMP_AHU_EHEAT_HIGH:1;//���ȸ��±�����
/*10*/ uint16 LAMP_AHU_PREHEAT_HIGH:1;//Ԥ�ȸ��±�����
/*11*/ uint16 LAMP_AHU_COLD_ERR:1;//����������
/*12*/ uint16 LAMP_AHU_COLD_STOP_ERR:1;//����ͣ��������
/*13*/ uint16 LAMP_AHU_EXTERN_EMC_ERR:1;//��Ӽ�ͣ������
/*14*/ uint16 LAMP_AHU_FIRE_ERR:1;//����������
    }Solo;
}YYJ_DOL_DEF;

typedef struct 
{
   YYJ_DOR_DEF Relay;
   YYJ_DOL_DEF Light;
}YYJ_DO_DEF;





//extern uint08 ReadBits(uint08 *p2data, uint08 index);
//extern void WriteBits(uint08 *p2data, uint08 index, uint08 bits);
extern void OutPutPoll();
extern void Run_uchar(void (*ptask)(uchar),uchar state); 
extern void Run_void(void (*ptask)()); 
extern void RelayAll(uchar RelayNum, uchar state);
extern YYJ_DOR_DEF Relays;
extern YYJ_DOL_DEF Lamps;
#endif












