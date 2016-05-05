#ifndef __RTC_H
#define __RTC_H     
//时间结构体
typedef struct 
{
	uint08 hour;
	uint08 min;
	uint08 sec;			
	//公历日月年周
	uint16 w_year;
	uint08 w_month;
	uint08 w_date;
	uint08 week;		 
}_calendar_obj;					 
extern _calendar_obj calendar;	//日历结构体

extern uint08 const mon_table[12];	//月份日期数据表
void Disp_Time(uint08 x,uint08 y,uint08 size);//在制定位置开始显示时间
void Disp_Week(uint08 x,uint08 y,uint08 size,uint08 lang);//在指定位置显示星期
uint08 RTC_Set_Stamp(uint32 stamp);
uint08 RTC_Init(void);        //初始化RTC,返回0,失败;1,成功;
uint08 Is_Leap_Year(u16 year);//平年,闰年判断
uint08 RTC_Get(void);         //更新时间   
uint08 RTC_Get_Week(u16 year,uint08 month,uint08 day);
uint08 RTC_Set(u16 syear,uint08 smon,uint08 sday,uint08 hour,uint08 min,uint08 sec);//设置时间		
void ReNewRTC();
	 
	 
#endif


