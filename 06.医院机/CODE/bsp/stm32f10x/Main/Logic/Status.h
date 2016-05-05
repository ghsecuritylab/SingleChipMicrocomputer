
#include "includes.h"


typedef union
{
   uchar uint08All[8];
   uint16 uint16All[4];
   struct 
   {
      /*00*/     uint08  BOX_PANEL_KEY_RUN:1;                 //��������  (�Ű�)
      /*01*/     uint08  BOX_PANEL_KEY_STANDBY:1;             //����ֵ��  (�Ű�)
      /*02*/     uint08  BOX_PANEL_KEY_REMOTE_RUN:1;          //Զ��ʹ��  (�Ű�)
      /*03*/     uint08  BOX_PANEL_KEY_REMOTE_STANDBY:1;      //Զֵʹ��  (�Ű�)
      /*04*/     uint08  BOX_PANEL_KEY_EMC_STOP:1;            //�Ű弱ͣ����
      /*05*/     uint08  FC_FEEDBACK_RUN:1;                   //(����)��Ƶ����
      /*06*/     uint08  FC_FEEDBACK_ERROR:1;                 //(����)��Ƶ����
      /*07*/     uint08  FF_FEEDBACK_RUN:1;                   //(����)��Ƶ����
      /*08*/     uint08  FF_FEEDBACK_ERR:1;                   //(����)��Ƶ����
      /*09*/     uint08  PANEL_KEY_RUN:1;                     //Զ����(��չ��)
      /*10*/     uint08  PANEL_KEY_STANDBY:1;                 //Զֵ��(��չ��)
      /*11*/     uint08  PANEL_KEY_NGT:1;                     //Զ��ѹ(��չ��)
      /*12*/     uint08  INPUT_EMC:1;                         //��ͣ��ť
      /*13*/     uint08  INPUT_FIRE_EMC:1;                    //����(��)
      /*14*/     uint08  INPUT_NO_WIND:1;                     //ȱ��
      /*15*/     uint08  INPUT_CHU_XIAO:1;                    //��Ч
      /*16*/     uint08  INPUT_WIND_GATE_01:1;                //�ŷ��1
      /*17*/     uint08  INPUT_WIND_GATE_02:1;                //�ŷ��2
      /*18*/     uint08  INPUT_WIND_GATE_03:1;                //�ŷ��3
      /*19*/     uint08  INPUT_WIND_GATE_04:1;                //�ŷ��4
      /*20*/     uint08  INPUT_WIND_GATE_05:1;                //�ŷ��5
      /*21*/     uint08  INPUT_WIND_GATE_06:1;                //�ŷ��6
      /*22*/     uint08  SEL_SEASON_WINTER:1;                 //�ֶ�����
      /*23*/     uint08  SEL_SEASON_SUMMER:1;                 //�ֶ�����
      /*28*/     uint08  TRIANGLE_STAR_TIMESET:5;             //ʱ���趨5�����뿪��
      /*31*/     uint08  TRIANGLE_STAR_NOUSED:3;              //��ʹ��3bit
      /*32*/     uint08  INPUT_ZHONG_XIAO:1;                  //��Ч
      /*33*/     uint08  INPUT_YA_GAO_XIAO:1;                 //�Ǹ�Ч
      /*34*/     uint08  INPUT_GAO_XIAO:1;                    //��Ч
      /*35*/     uint08  INPUT_HEAT_HIGH_TEMP:1;              //�����(�ȸ���)*
      /*36*/     uint08  INPUT_PRE_HEAT_HIGH_TEMP:1;          //Ԥ�ȸ���
      /*37*/     uint08  INPUT_WATER_SENSOR:1;                //����(ˮ,������)*
      /*38*/     uint08  INPUT_COLD_PROTECT:1;                //����
      /*39*/     uint08  SEL_STAR_START:1;                    //����
      /*40*/     uint08  SEL_TRIANGLE_START:1;                //������
      /*41*/     uint08  SEL_MODE_FIX_FRQ:1;                  //��Ƶ
      /*42*/     uint08  SEL_MODE_FRQ_CVT:1;                  //��Ƶ
      /*43*/     uint08  SEL_MODE_MANUAL_FRQ:1;               //��Ƶ���Ƶ�ѹѡ��
      /*44*/     uint08  SEL_MODE_SPARE_01:1;                 //����1
      /*45*/     uint08  SEL_MODE_SPARE_02:1;                 //����2
		 uint08  SysWorking:1;                        //ϵͳ����״̬
   }Solo;
}StatusDef;




extern StatusDef Status;
















