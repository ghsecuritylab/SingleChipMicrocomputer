#ifndef ___LCDDIS_H___
#define ___LCDDIS_H___
//#include <intrinsics.h>
#define nop do{asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");}while(0)
#define SYSDIS   0x00	  //关系统振荡器和LCD偏压发生器	
#define SYSEN    0x02     //打开系统振荡器	
#define LCDOFF   0x04     //关LCD偏压
#define LCDON    0x06     //开LCD偏压
#define TONEON   0x12     //打开声音输出
#define TONEOFF  0x10     //关闭声音输出
#define XTAL     0x28     //外部接晶振								 
#define RC       0x30     //内部RC振荡	
#define BIAS     0x52     //1/3偏压 4公共口	
#define WDTDIS   0x0a     //禁止看门狗
#define WDTEN    0x0e     //开启看门狗


#define SEG_A 0x01
#define SEG_B 0x02
#define SEG_C 0x04
#define SEG_D 0x08
#define SEG_E 0x10
#define SEG_F 0x20
#define SEG_G 0x40

#define _FLAG_NUM_0 (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F)
#define _FLAG_NUM_1 (SEG_B|SEG_C)
#define _FLAG_NUM_2 (SEG_A|SEG_B|SEG_G|SEG_E|SEG_D)
#define _FLAG_NUM_3 (SEG_A|SEG_B|SEG_G|SEG_C|SEG_D)
#define _FLAG_NUM_4 (SEG_B|SEG_C|SEG_F|SEG_G)
#define _FLAG_NUM_5 (SEG_A|SEG_F|SEG_G|SEG_C|SEG_D)
#define _FLAG_NUM_6 (SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define _FLAG_NUM_7 (SEG_A|SEG_B|SEG_C)
#define _FLAG_NUM_8 (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define _FLAG_NUM_9 (SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G) 
#define _FLAG_NUM_A (SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G) 
#define _FLAG_NUM_B (SEG_E|SEG_G|SEG_F|SEG_C|SEG_D) 
#define _FLAG_NUM_C (SEG_A|SEG_D|SEG_E|SEG_F) 
#define _FLAG_NUM_D (SEG_E|SEG_B|SEG_C|SEG_D|SEG_G) 
#define _FLAG_NUM_E (SEG_A|SEG_G|SEG_D|SEG_E|SEG_F) 
#define _FLAG_NUM_F (SEG_A|SEG_G|SEG_E|SEG_F) 
#define _FLAG_NUM_H (SEG_B|_SEG_C|SEG_G|SEG_F|SEG_E)


typedef union 
{
   uint08 All[10];
   struct
   {          uint08 ROM_TEMP_4B:1;
      uint08 ROM_TEMP_4G:1;
      uint08 ROM_TEMP_4C:1;
      uint08 TEMP_ICON2:1;              
      	 	      uint08 ROM_TEMP_4A:1;
      uint08 ROM_TEMP_4F:1;
      uint08 ROM_TEMP_4E:1;
      uint08 ROM_TEMP_4D:1;

      uint08 ROM_TEMP_3B:1;
      uint08 ROM_TEMP_3G:1;
      uint08 ROM_TEMP_3C:1;
      uint08 ROM_TEMP_ICON:1;
      uint08 ROM_TEMP_3A:1;
      uint08 ROM_TEMP_3F:1;
      uint08 ROM_TEMP_3E:1;
      uint08 ROM_TEMP_3D:1;
      uint08 SET_TEMP_2B:1;
      uint08 SET_TEMP_2G:1;
      uint08 SET_TEMP_2C:1;
      uint08 TEMP_ICON1:1;
      uint08 SET_TEMP_2A:1;
      uint08 SET_TEMP_2F:1;
      uint08 SET_TEMP_2E:1;
      uint08 SET_TEMP_2D:1;
      uint08 SET_TEMP_1B:1;
      uint08 SET_TEMP_1G:1;
      uint08 SET_TEMP_1C:1;
      uint08 SET_TEMP_ICON:1;
      uint08 SET_TEMP_1A:1;
      uint08 SET_TEMP_1F:1;
      uint08 SET_TEMP_1E:1;
      uint08 SET_TEMP_1D:1;
      uint08 TWOLINE_ICON:1;
      uint08 AUTO_ICON:1;
      uint08 LOW_ICON:1;
      uint08 NONE_2:1;
      uint08 FAN_ICON:1;
      uint08 HIGH_ICON:1;
      uint08 MED_ICON:1;
      uint08 NONE_1:1;


      uint08 MODE_ICON:1;
      uint08 COOL_ICON:1;
      uint08 HOT_ICON:1;
      uint08 SLEEP_ICON:1;

      uint08 TIME_5A:1;
      uint08 TIME_5F:1;
      uint08 TIME_5E:1;
      uint08 TIME_5D:1;
      uint08 TIME_5B:1;
      uint08 TIME_5G:1;
      uint08 TIME_5C:1;
      uint08 TIME2START_ICON:1;
      uint08 TIME_6A:1;
      uint08 TIME_6F:1;
      uint08 TIME_6E:1;
      uint08 TIME_6D:1;
      uint08 TIME_6B:1;
      uint08 TIME_6G:1;
      uint08 TIME_6C:1;
      uint08 COLON_ICON:1;
      uint08 TIME_7A:1;
      uint08 TIME_7F:1;
      uint08 TIME_7E:1;
      uint08 TIME_7D:1;
      uint08 TIME_7B:1;
      uint08 TIME_7G:1;
      uint08 TIME_7C:1;
      uint08 TIME2STOP_ICON:1;
      uint08 TIME_8A:1;
      uint08 TIME_8F:1;
      uint08 TIME_8E:1;
      uint08 TIME_8D:1;
      uint08 TIME_8B:1;
      uint08 TIME_8G:1;
      uint08 TIME_8C:1;
      uint08 TIME_ICON:1;

   } Solo;        
        		
// {
//    uint08 MODE_ICON:1;
//    uint08 COOL_ICON:1;
//    uint08 HOT_ICON:1;
//    uint08 SLEEP_ICON:1;
//    uint08 FAN_ICON:1;
//    uint08 HIGH_ICON:1;
//    uint08 MED_ICON:1;
//    uint08 NONE_1:1;
//    uint08 TWOLINE_ICON:1;
//    uint08 AUTO_ICON:1;
//    uint08 LOW_ICON:1;
//    uint08 NONE_2:1;
//    uint08 SET_TEMP_1A:1;
//    uint08 SET_TEMP_1F:1;
//    uint08 SET_TEMP_1E:1;
//    uint08 SET_TEMP_1D:1;
//    uint08 SET_TEMP_1B:1;
//    uint08 SET_TEMP_1G:1;
//    uint08 SET_TEMP_1C:1;
//    uint08 SET_TEMP_ICON:1;
//    uint08 SET_TEMP_2A:1;
//    uint08 SET_TEMP_2F:1;
//    uint08 SET_TEMP_2E:1;
//    uint08 SET_TEMP_2D:1;
//    uint08 SET_TEMP_2B:1;
//    uint08 SET_TEMP_2G:1;
//    uint08 SET_TEMP_2C:1;
//    uint08 TEMP_ICON1:1;
//    uint08 ROM_TEMP_3A:1;
//    uint08 ROM_TEMP_3F:1;
//    uint08 ROM_TEMP_3E:1;
//    uint08 ROM_TEMP_3D:1;
//    uint08 ROM_TEMP_3B:1;
//    uint08 ROM_TEMP_3G:1;
//    uint08 ROM_TEMP_3C:1;
//    uint08 ROM_TEMP_ICON:1;
//    uint08 ROM_TEMP_4A:1;
//    uint08 ROM_TEMP_4F:1;
//    uint08 ROM_TEMP_4E:1;
//    uint08 ROM_TEMP_4D:1;
//    uint08 ROM_TEMP_4B:1;
//    uint08 ROM_TEMP_4G:1;
//    uint08 ROM_TEMP_4C:1;
//    uint08 TEMP_ICON2:1;
//    uint08 TIME_5A:1;
//    uint08 TIME_5F:1;
//    uint08 TIME_5E:1;
//    uint08 TIME_5D:1;
//    uint08 TIME_5B:1;
//    uint08 TIME_5G:1;
//    uint08 TIME_5C:1;
//    uint08 TIME2START_ICON:1;
//    uint08 TIME_6A:1;
//    uint08 TIME_6F:1;
//    uint08 TIME_6E:1;
//    uint08 TIME_6D:1;
//    uint08 TIME_6B:1;
//    uint08 TIME_6G:1;
//    uint08 TIME_6C:1;
//    uint08 COLON_ICON:1;
//    uint08 TIME_7A:1;
//    uint08 TIME_7F:1;
//    uint08 TIME_7E:1;
//    uint08 TIME_7D:1;
//    uint08 TIME_7B:1;
//    uint08 TIME_7G:1;
//    uint08 TIME_7C:1;
//    uint08 TIME2STOP_ICON:1;
//    uint08 TIME_8A:1;
//    uint08 TIME_8F:1;
//    uint08 TIME_8E:1;
//    uint08 TIME_8D:1;
//    uint08 TIME_8B:1;
//    uint08 TIME_8G:1;
//    uint08 TIME_8C:1;
//    uint08 TIME_ICON:1;
//
// } Solo;
}FC_DISP_DEF;

void LCDShowAll();
void TM1621_init(void);
void delay_nms(uint n);
//void LCDDispNum();
void DisplaySetTemp(uchar trg);
void DisplayRomTemp(uchar trg);

extern  uint08 cntLCD;

#endif
