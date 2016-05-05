
#include "includes.h"
#include "rtc.h"



_calendar_obj calendar;//ʱ�ӽṹ�� 
/*
void set_clock(uint16 divx)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��  
    PWR_BackupAccessCmd(ENABLE);	//ʹ��RTC�ͺ󱸼Ĵ������� 

    RTC_EnterConfigMode();/// ��������	
 
    RTC_SetPrescaler(divx); //����RTCԤ��Ƶ��ֵ          									 
    RTC_ExitConfigMode();//�˳�����ģʽ  				   		 									  
    RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������		 									  
}	   
*/
static void RTC_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;      //RTCȫ���ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�1λ,�����ȼ�3λ
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //��ռ���ȼ�0λ,�����ȼ�4λ
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //ʹ�ܸ�ͨ���ж�
    NVIC_Init(&NVIC_InitStructure);     //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

//ʵʱʱ������
//��ʼ��RTCʱ��,ͬʱ���ʱ���Ƿ�������
//BKP->DR1���ڱ����Ƿ��һ�����õ�����
//����0:����
//����:�������

uint08 RTC_Init(void)
{
    //����ǲ��ǵ�һ������ʱ��
    uint08 temp=0;

    if ( BKP_ReadBackupRegister(BKP_DR1) != 0x5050 )      //��ָ���ĺ󱸼Ĵ����ж�������:��������д���ָ�����ݲ����
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);    //ʹ��PWR��BKP����ʱ��   
        PWR_BackupAccessCmd(ENABLE);    //ʹ�ܺ󱸼Ĵ������� 
        BKP_DeInit();   //��λ�������� 	
        RCC_LSEConfig(RCC_LSE_ON);  //�����ⲿ���پ���(LSE),ʹ��������پ���
        while ( RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET && temp< 252) //���ָ����RCC��־λ�������,�ȴ����پ������
        {
            temp++;
            //delay_ms(10);
            //OSTimeDlyHMSM(0, 0, 0, 10); 
        }
        if ( temp>=250 )
        {
          return 1;//��ʼ��ʱ��ʧ��,����������	 
        }
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);     //����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��    
        RCC_RTCCLKCmd(ENABLE);  //ʹ��RTCʱ��  
        RTC_WaitForLastTask();  //�ȴ����һ�ζ�RTC�Ĵ�����д�������
        RTC_WaitForSynchro();       //�ȴ�RTC�Ĵ���ͬ��  
        RTC_ITConfig(RTC_IT_SEC, ENABLE);       //ʹ��RTC���ж�
        RTC_WaitForLastTask();  //�ȴ����һ�ζ�RTC�Ĵ�����д�������
        RTC_EnterConfigMode();/// ��������	
        RTC_SetPrescaler(32767); //����RTCԤ��Ƶ��ֵ
        RTC_WaitForLastTask();  //�ȴ����һ�ζ�RTC�Ĵ�����д�������
        RTC_Set(2009,12,2,10,0,55);  //����ʱ��	
        RTC_ExitConfigMode(); //�˳�����ģʽ  
        BKP_WriteBackupRegister(BKP_DR1, 0X5050);   //��ָ���ĺ󱸼Ĵ�����д���û���������
    }
    else//ϵͳ������ʱ
    {

        RTC_WaitForSynchro();   //�ȴ����һ�ζ�RTC�Ĵ�����д�������
        RTC_ITConfig(RTC_IT_SEC, ENABLE);   //ʹ��RTC���ж�
        RTC_WaitForLastTask();  //�ȴ����һ�ζ�RTC�Ĵ�����д�������
    }
    RTC_NVIC_Config();//RCT�жϷ�������		    				     
    RTC_Get();//����ʱ��	
    return 0; //ok

}                           
//RTCʱ���ж�
//ÿ�봥��һ��  
void RTC_IRQHandler(void)
{
    
    #warning !!!And code here!!!
    //�û�����..  
    if ( RTC_GetITStatus(RTC_IT_SEC) != RESET )//�����ж�
    {
        RTC_Get();//����ʱ��   
        ReNewRTC();//����ʱ��   
    }
    if ( RTC_GetITStatus(RTC_IT_ALR)!= RESET )//�����ж�
    {
        RTC_ClearITPendingBit(RTC_IT_ALR);      //�������ж�	  	   
    }
    RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);        //�������ж�
    RTC_WaitForLastTask();       
    

    #warning !!!And code here!!!                                 
}
//�ж��Ƿ������꺯��
//�·�   1  2  3  4  5  6  7  8  9  10 11 12
//����   31 29 31 30 31 30 31 31 30 31 30 31
//������ 31 28 31 30 31 30 31 31 30 31 30 31
//����:���
//���:������ǲ�������.1,��.0,����
uint08 Is_Leap_Year(uint16 year)
{
    if ( year%4==0 ) //�����ܱ�4����
    {
        if ( year%100==0 )
        {
            if ( year%400==0 )
            {
                return 1;//�����00��β,��Ҫ�ܱ�400����
            }
            else 
            {
                return 0;
            }
        }
        else 
        {
            return 1;
        }
    }
    else 
    {
        return 0;
    }
}                  
//����ʱ��
//�������ʱ��ת��Ϊ����
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����
//����ֵ:0,�ɹ�;����:�������.
//�·����ݱ�											 
uint08 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�	  
//ƽ����·����ڱ�
const uint08 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};

uint08 RTC_Set_Stamp(uint32 stamp)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);    //ʹ��PWR��BKP����ʱ��  
    PWR_BackupAccessCmd(ENABLE);    //ʹ��RTC�ͺ󱸼Ĵ������� 
    RTC_SetCounter(stamp);   //����RTC��������ֵ

    RTC_WaitForLastTask();  //�ȴ����һ�ζ�RTC�Ĵ�����д�������  	
    return 0;       
}

uint08 RTC_Set(uint16 syear,uint08 smon,uint08 sday,uint08 hour,uint08 min,uint08 sec)
{
    uint16 t;
    uint32 seccount=0;
    if ( syear<1970||syear>2099 )return 1;
    for ( t=1970;t<syear;t++ ) //��������ݵ��������
    {
        if ( Is_Leap_Year(t) )
        {
            seccount+=31622400;//�����������
        }
        else 
        {
            seccount+=31536000;              //ƽ���������
        }
    }
    smon-=1;
    for ( t=0;t<smon;t++ )    //��ǰ���·ݵ����������
    {
        seccount+=(uint32)mon_table[t]*86400;//�·����������
        if ( Is_Leap_Year(syear)&&t==1 )
        {
            seccount+=86400;//����2�·�����һ���������
        }
    }
    seccount+=(uint32)(sday-1)*86400;//��ǰ�����ڵ���������� 
    seccount+=(uint32)hour*3600;//Сʱ������
    seccount+=(uint32)min*60;    //����������
    seccount+=sec;//�������Ӽ���ȥ

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);    //ʹ��PWR��BKP����ʱ��  
    PWR_BackupAccessCmd(ENABLE);    //ʹ��RTC�ͺ󱸼Ĵ������� 
    RTC_SetCounter(seccount);   //����RTC��������ֵ

    RTC_WaitForLastTask();  //�ȴ����һ�ζ�RTC�Ĵ�����д�������  	
    return 0;       
}

void ReNewRTC()
{
        UINT32T04BYTE Stamp;
        Stamp.Words.HWORD = RTC->CNTH;
        Stamp.Words.LWORD = RTC->CNTL;

    #warning !!!And code here!!!   
}

//�õ���ǰ��ʱ��
//����ֵ:0,�ɹ�;����:�������.
uint08 RTC_Get(void)
{
    static uint16 daycnt=0;
    uint32 timecount=0; 
    uint32 temp=0;
    uint16 temp1=0;   
    timecount=RTC->CNTH;//�õ��������е�ֵ(������)
    timecount<<=16;
    timecount+=RTC->CNTL;            

    temp=timecount/86400;   //�õ�����(��������Ӧ��)
    if ( daycnt!=temp )//����һ����
    {
        daycnt=temp;
        temp1=1970; //��1970�꿪ʼ
        while ( temp>=365 )
        {
            if ( Is_Leap_Year(temp1) )//������
            {
                if ( temp>=366 )
                {
                    temp-=366;//�����������
                }
                else
                {
                    temp1++;break;
                }  
            }
            else
            {
                temp-=365;   //ƽ��
            }
            temp1++;  
        }   
        calendar.w_year=temp1;//�õ����
        temp1=0;
        while ( temp>=28 )//������һ����
        {
            if ( Is_Leap_Year(calendar.w_year)&&temp1==1 )//�����ǲ�������/2�·�
            {
                if ( temp>=29 )
                {
                    temp-=29;//�����������
                }
                else 
                {
                    break;
                }
            }
            else
            {
                if ( temp>=mon_table[temp1] )
                {
                    temp-=mon_table[temp1];//ƽ��
                }
                else 
                {
                    break;
                }
            }
            temp1++;  
        }
        calendar.w_month=temp1+1;   //�õ��·�
        calendar.w_date=temp+1;     //�õ����� 
    }
    temp=timecount%86400;           //�õ�������   	   
    calendar.hour=temp/3600;        //Сʱ
    calendar.min=(temp%3600)/60;    //����	
    calendar.sec=(temp%3600)%60;    //����
    calendar.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//��ȡ����   
    return 0;
}    
//������������ڼ�
//��������:���빫�����ڵõ�����(ֻ����1901-2099��)
//������������������� 
//����ֵ�����ں�																						 
uint08 RTC_Get_Week(uint16 year,uint08 month,uint08 day)
{
    uint16 temp2;
    uint08 yearH,yearL;

    yearH=year/100; 
    yearL=year%100; 
    // ���Ϊ21����,�������100  
    if ( yearH>19 )
    {
        yearL+=100;
    }
    // ����������ֻ��1900��֮���  
    temp2=yearL+yearL/4;
    temp2=temp2%7; 
    temp2=temp2+day+table_week[month-1];
    if ( yearL%4==0&&month<3 )
    {
        temp2--;
    }
    return(temp2%7);
}             
















