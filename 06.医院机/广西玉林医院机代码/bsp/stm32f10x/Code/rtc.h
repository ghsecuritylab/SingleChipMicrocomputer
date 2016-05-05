#ifndef __RTC_H
#define __RTC_H     
//ʱ��ṹ��
typedef struct 
{
	uint08 hour;
	uint08 min;
	uint08 sec;			
	//������������
	uint16 w_year;
	uint08 w_month;
	uint08 w_date;
	uint08 week;		 
}_calendar_obj;					 
extern _calendar_obj calendar;	//�����ṹ��

extern uint08 const mon_table[12];	//�·��������ݱ�
void Disp_Time(uint08 x,uint08 y,uint08 size);//���ƶ�λ�ÿ�ʼ��ʾʱ��
void Disp_Week(uint08 x,uint08 y,uint08 size,uint08 lang);//��ָ��λ����ʾ����
uint08 RTC_Set_Stamp(uint32 stamp);
uint08 RTC_Init(void);        //��ʼ��RTC,����0,ʧ��;1,�ɹ�;
uint08 Is_Leap_Year(u16 year);//ƽ��,�����ж�
uint08 RTC_Get(void);         //����ʱ��   
uint08 RTC_Get_Week(u16 year,uint08 month,uint08 day);
uint08 RTC_Set(u16 syear,uint08 smon,uint08 sday,uint08 hour,uint08 min,uint08 sec);//����ʱ��		
void ReNewRTC();
	 
	 
#endif


