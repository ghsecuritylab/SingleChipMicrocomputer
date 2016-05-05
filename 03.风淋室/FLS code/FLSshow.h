#ifndef FLSSHOW_H
#define FLSSHOW_H

#define nop {asm("nop");}
#define SYSDIS   0x00	  //关系统振荡器和LCD偏压发生器	
#define SYSEN    0x02     //打开系统振荡器	
#define LCDOFF   0x04     //关LCD偏压
#define LCDON    0x06     //开LCD偏压
#define TONEON   0x12     //打开声音输出
#define TONEOFF  0x10     //关闭声音输出
#define XTAL     0x28     //外部接晶振								 
#define RC       0x30     //内部RC振荡	
#define BIAS     0x4a     //1/3偏压 4公共口	
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
   uchar All[6];
   struct
   {                  	 	
      uchar FAN_ICON_1	 	 : 1; 
      uchar FAN_ICON_2	 	 : 1;
      uchar FAN_ICON_3	 	 : 1;
      uchar NONE_0    	 	 : 1;
     
      uchar EMC_ICON 	 	 : 1;
      uchar EMC_ERR  	 	 : 1;
      uchar WORD_BOX_1	 	 : 1;
      uchar NONE_1    	 	 : 1;

      uchar INFRARED_ERR 	 : 1;
      uchar INFRARED_ICON	 : 1;
      uchar LIGHT_ERR     	 : 1;
      uchar NONE_2        	 : 1;

      uchar IN_DOOR_LOCK_ERR  	 : 1;
      uchar IN_DOOR_LOCK_ICON 	 : 1;
      uchar LIGHT_ICON       	 : 1;
      uchar NONE_3           	 : 1;
 

      uchar OUT_DOOR_LOCK_ERR 	 : 1;
      uchar OUT_DOOR_LOCK_ICON	 : 1;
      uchar WOED_BOX_2       	 : 1;
      uchar NONE_4           	 : 1;

      uchar NUMBER_2B     	 : 1;
      uchar NUMBER_2C     	 : 1;
      uchar WOED_BOX_FAN  	 : 1;
      uchar NONE_5        	 : 1;

      uchar NUMBER_2A  		 : 1;
      uchar NUMBER_2G  		 : 1;
      uchar NUMBER_2D  		 : 1;
      uchar NONE_6     		 : 1;

      uchar NUMBER_2F		 : 1;
      uchar NUMBER_2E		 : 1;
      uchar FAN_ERR  		 : 1;
      uchar NONE_7   		 : 1;

      uchar NUMBER_1B            : 1;
      uchar NUMBER_1C            : 1;
      uchar FAN_ICON_ROUND       : 1;
      uchar NONE_8               : 1;

      uchar NUMBER_1A		 : 1;
      uchar NUMBER_1G		 : 1;
      uchar NUMBER_1D		 : 1;
      uchar NONE_9   		 : 1;

      uchar NUMBER_1F  		 : 1;
      uchar NUMBER_1E  		 : 1;
      uchar NONE_10    		 : 1;
      uchar NONE_11    		 : 1;
   } Solo;             		
}FLS_SHOW_DEF;



extern FLS_SHOW_DEF SHOWBuff;


void DispTestErr(FLS_SHOW_DEF *show, FLS_DEF *Fls);
void LCDShowAll(uchar *p2Data);
void LCDDispWord(FLS_SHOW_DEF *buff);
void LCDDispNum(FLS_SHOW_DEF *buff, uchar Data);
//void WriteOneData4(uchar Addr, uchar Data);
//void WriteOneData8(uchar Addr, uchar Data);
//void WriteAllData(uchar Addr, uchar *p, uchar cnt);
void TM1621_init(void);
void DispOneFls(FLS_SHOW_DEF *show, FLS_DEF *Fls);

#endif

