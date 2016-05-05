
#include "includes.h"


#define _____________________________________________
//void Panel_LED_Ctrl_Status()//�Ű�16��LED��ʾ����
//{
//   Lamps.Solo.LAMP_AHU_RUNNING         =  ( Status.Solo.LAMP_AHU_RUNNING        ) ? ( 1 : 0 ); //����
//   Lamps.Solo.LAMP_AHU_STANDBY         =  ( Status.Solo.LAMP_AHU_STANDBY        ) ? ( 1 : 0 ); //ֵ��
//   Lamps.Solo.LAMP_EX01                =  ( Status.Solo.LAMP_EX01               ) ? ( 1 : 0 ); //����1
//   Lamps.Solo.LAMP_AHU_ERROR           =  ( Status.Solo.LAMP_AHU_ERROR          ) ? ( 1 : 0 ); //���ϱ���
//   Lamps.Solo.LAMP_AHU_NOWIND          =  ( Status.Solo.LAMP_AHU_NOWIND         ) ? ( 1 : 0 ); //ȱ�籨��
//   Lamps.Solo.LAMP_AHU_CHU_XIAO        =  ( Status.Solo.LAMP_AHU_CHU_XIAO       ) ? ( 1 : 0 ); //��Ч����
//   Lamps.Solo.LAMP_AHU_ZHONG_XIAO      =  ( Status.Solo.LAMP_AHU_ZHONG_XIAO     ) ? ( 1 : 0 ); //��Ч����
//   Lamps.Solo.LAMP_AHU_YA_GAO_XIAO     =  ( Status.Solo.LAMP_AHU_YA_GAO_XIAO    ) ? ( 1 : 0 ); //�Ǹ�Ч����
//   Lamps.Solo.LAMP_AHU_GAO_XIAO        =  ( Status.Solo.LAMP_AHU_GAO_XIAO       ) ? ( 1 : 0 ); //��Ч����
//   Lamps.Solo.LAMP_AHU_EHEAT_HIGH      =  ( Status.Solo.LAMP_AHU_EHEAT_HIGH     ) ? ( 1 : 0 ); //���ȸ��±���
//   Lamps.Solo.LAMP_AHU_PREHEAT_HIGH    =  ( Status.Solo.LAMP_AHU_PREHEAT_HIGH   ) ? ( 1 : 0 ); //Ԥ�ȸ��±���
//   Lamps.Solo.LAMP_AHU_COLD_ERR        =  ( Status.Solo.LAMP_AHU_COLD_ERR       ) ? ( 1 : 0 ); //��������
//   Lamps.Solo.LAMP_AHU_COLD_STOP_ERR   =  ( Status.Solo.LAMP_AHU_COLD_STOP_ERR  ) ? ( 1 : 0 ); //����ͣ������
//   Lamps.Solo.LAMP_AHU_EXTERN_EMC_ERR  =  ( Status.Solo.LAMP_AHU_EXTERN_EMC_ERR ) ? ( 1 : 0 ); //�⼱ͣ����
//   Lamps.Solo.LAMP_AHU_FIRE_ERR        =  ( Status.Solo.LAMP_AHU_FIRE_ERR       ) ? ( 1 : 0 ); //��������
//   Lamps.Solo.LAMP_EX02                =  ( Status.Solo.LAMP_EX02               ) ? ( 1 : 0 ); //����2
//}

#define   _________________________���ȴ���_________________________
void HeatDeal()
{
   if (ϵͳ���ڹ���״̬)
   {
      if (NowValueTemp < SetValueTemp * 10)
      {
         uchar tmp;
         uint itmp = SetValueTemp * 10 - NowValueTemp;
         if (itmp < 5) //С��0.5�ȾͲ�����
         {
            itmp = 0;
         }
         itmp = itmp / 15;
         if (itmp > 7) //��Ϊ3�� 0b0000 0111
         {
            itmp = 7;
         }
         Relays.Solo.EHEAT_LV01 = 0;   //һ������
         Relays.Solo.EHEAT_LV02 = 0;   //��������
         Relays.Solo.EHEAT_LV03 = 0;   //��������
         tmp = itmp;
         if (testbit(tmp, 0))
         {
            Relays.Solo.EHEAT_LV01 = 1;
         }
         if (testbit(tmp, 1))
         {
            Relays.Solo.EHEAT_LV02 = 1;
         }
         if (testbit(tmp, 2))
         {
            Relays.Solo.EHEAT_LV03 = 1;
         }
      }
   }
   else
   {
      Relays.Solo.EHEAT_LV01 = 0;
      Relays.Solo.EHEAT_LV02 = 0;
      Relays.Solo.EHEAT_LV03 = 0;
   }
}

#define ___________________Ԥ�ȴ���____________________________
void PreHeatDeal()
{
   uint PreNowValueTemp;
//   MakeWord(&ADCValues[10]);
//   PreNowValueTemp = (unsigned int)((unsigned long)iAllbuff1 * 1024 / 1000 / 2);
   POL_AI_Block.HW_AI_PRE_HEAT_TEMP //Ԥ���¸�
   if (SysWorking())
   {
      if (PreNowValueTemp < 5 * 10)
      {
         uchar tmp;
         uint itmp = SetValueTemp * 10 - PreNowValueTemp;
         if (itmp < 5) //С��0.5�ȾͲ�����
         {
            itmp = 0;
         }
         itmp = itmp / 15;
         if (itmp > 7)
         {
            itmp = 7;
         }
         Relays.Solo.REHEAT_LV01 = 0;
         Relays.Solo.REHEAT_LV02 = 0;
         Relays.Solo.REHEAT_LV03 = 0;
         tmp = itmp;
         if (testbit(tmp, 0))
         {
            Relays.Solo.REHEAT_LV01 = 1;
         }
         if (testbit(tmp, 1))
         {
            Relays.Solo.REHEAT_LV02 = 1;
         }
         if (testbit(tmp, 2))
         {
            Relays.Solo.REHEAT_LV03 = 1;
         }
      }
   }
   else
   {
      Relays.Solo.REHEAT_LV01 = 0;
      Relays.Solo.REHEAT_LV02 = 0;
      Relays.Solo.REHEAT_LV03 = 0;
   }
}


void ExhaustFanCtrl() //�ŷ������
{
   if (SysWorking()) //����д�������� ||SysStandBy()��ȫֵ��ʱ,�����ŷ��
   {
      if (Status.Solo.INPUT_WIND_GATE_01) // #1
      {
         Relays.Solo.AUTO_GATES_01 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_01 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_02) // #2
      {
         Relays.Solo.AUTO_GATES_02 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_02 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_03) // #3
      {
         Relays.Solo.AUTO_GATES_03 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_03 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_04) // #4
      {
         Relays.Solo.AUTO_GATES_04 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_04 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_05) // #5
      {
         Relays.Solo.AUTO_GATES_05 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_05 = 0;
      }
      if (Status.Solo.INPUT_WIND_GATE_06) // #6
      {
         Relays.Solo.AUTO_GATES_06 = 1;
      }
      else
      {
         Relays.Solo.AUTO_GATES_06 = 0;
      }
   }
   else
   {
      Relays.Solo.AUTO_GATES_01 = 0;
      Relays.Solo.AUTO_GATES_02 = 0;
      Relays.Solo.AUTO_GATES_03 = 0;
      Relays.Solo.AUTO_GATES_04 = 0;
      Relays.Solo.AUTO_GATES_05 = 0;
      Relays.Solo.AUTO_GATES_06 = 0;
   }
   //��ѹ�ŷ�
   if (PanelDataRead(48) != 0)
   {
      Relays.Solo.NGT_PRESS = 1;
   }
   else
   {
      Relays.Solo.NGT_PRESS = 0;
   }
}

void CoolingFan() //���ɢ�ȷ���
{
   if (SysWorking())
   {
      Relays.Solo.BOX_COOLER = 1;
   }
   else
   {
      Relays.Solo.BOX_COOLER = 0;
   }
}








































































uchar SysBoot() //����
{
   if (POL_DI_Block.Solo.INPUT_EMC == 0 || POL_DI_Block.Solo.INPUT_FIRE_EMC == 0 || POL_DI_Block.Solo.INPUT_NO_WIND == 0) //�⼱ͣ ���� ȱ��
   {
      return 0;
   }
   if (POL_DI_Block.Solo.BOX_PANEL_KEY_RUN) //Ӳ���ߵı��ؿ���
   {
      return 1;
   }
   if (XXXXX != 0) //С�������ı��ؿ���
   {
      return 1;
   }
   if (POL_DI_Block.Solo.BOX_PANEL_KEY_REMOTE_RUN || XXXXX) //Ӳ���ߵ�Զ�̿���  С��������Զ�̿���
   {
      if (PanelDataRead(46) != 0) //�鱨���Ŀ�������
      {
         return 1;
      }
   }
   //PC��������
   return 0;
}


uchar SysStandby() //ֵ��
{
   if (POL_DI_Block.Solo.BOX_PANEL_KEY_STANDBY) //Ӳ���ߵı���ֵ��
   {
      return 1;
   }
   if (XXXXX != 0) //С�������ı���ֵ��
   {
      return 1;
   }
   if (POL_DI_Block.Solo.BOX_PANEL_KEY_REMOTE_STANDBY || XXXXX) //Ӳ���ߵ�Զ��ֵ��  С��������Զ��ֵ��
   {
      if (PanelDataRead(47) != 0) //�鱨����ֵ������
      {
         return 1;
      }
   }
   //PC��������
   return 0;
}

uchar SysWorking() //����״̬
{
   if ( (WorkStep < START_DISABLE) && (WorkStep != 0) )
   {
      return 1;
   }
   else
   {
      return 0;
   }
}




































