
#include  "includes.h"



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