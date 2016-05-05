


#ifndef DEFINES_H
#define DEFINES_H



#define BIT(x)        (  1 << x       )
#define SetBit(x,y)   (  x |= BIT(y)  ) 
#define ClrBit(x,y)   (  x &= ~BIT(y) ) 
#define GetBit(x,y)   (  x & BIT(y)   ) 

/*******************************************/ 
//#define LED1_ON()      SetBit(PORTA,6)   //运行指示灯
//#define LED2_ON()      SetBit(PORTC,2)   //值机指示灯
//#define LED3_ON()      SetBit(PORTA,7)   //电源指示灯
//#define LED4_ON()      SetBit(PORTC,7)   //机组故障灯
//#define LED5_ON()      SetBit(PORTC,0)   //缺风报警灯
//#define LED6_ON()      SetBit(PORTA,5)   //初效报警灯
//#define LED7_ON()      SetBit(PORTA,4)   //中效报警灯
//#define LED8_ON()      SetBit(PORTA,3)   //亚高效报警灯
//#define LED9_ON()      SetBit(PORTA,2)   //高效报警灯
//#define LED10_ON()     SetBit(PORTB,4)   //电热高温报警灯
//#define LED11_ON()     SetBit(PORTB,3)   //预热高温报警灯
//#define LED12_ON()     SetBit(PORTB,2)   //防冻报警灯
//#define LED13_ON()     SetBit(PORTB,1)   //防冻停机报警灯
//#define LED14_ON()     SetBit(PORTA,0)   //外接急停报警灯
//#define LED15_ON()     SetBit(PORTB,0)   //消防报警灯
//#define LED16_ON()     SetBit(PORTC,1)   //通讯指示灯
//#define LED17_ON()     SetBit(PORTC,6)   //远程开机指示灯
//#define LED18_ON()     SetBit(PORTC,5)   //远程值机指示灯
//#define LED19_ON()     SetBit(PORTC,4)   //本地开机指示灯
//#define LED20_ON()     SetBit(PORTC,3)   //本地值机指示灯
//
//#define LED1_OFF()     ClrBit(PORTA,6)    //运行指示灯
//#define LED2_OFF()     ClrBit(PORTC,2)    //值机指示灯
//#define LED3_OFF()     ClrBit(PORTA,7)    //电源指示灯
//#define LED4_OFF()     ClrBit(PORTC,7)    //机组故障灯
//#define LED5_OFF()     ClrBit(PORTC,0)    //缺风报警灯
//#define LED6_OFF()     ClrBit(PORTA,5)    //初效报警灯
//#define LED7_OFF()     ClrBit(PORTA,4)    //中效报警灯
//#define LED8_OFF()     ClrBit(PORTA,3)    //亚高效报警灯
//#define LED9_OFF()     ClrBit(PORTA,2)    //高效报警灯
//#define LED10_OFF()    ClrBit(PORTB,4)    //电热高温报警灯
//#define LED11_OFF()    ClrBit(PORTB,3)    //预热高温报警灯
//#define LED12_OFF()    ClrBit(PORTB,2)    //防冻报警灯
//#define LED13_OFF()    ClrBit(PORTB,1)    //防冻停机报警灯
//#define LED14_OFF()    ClrBit(PORTA,0)    //外接急停报警灯
//#define LED15_OFF()    ClrBit(PORTB,0)    //消防报警灯
//#define LED16_OFF()    ClrBit(PORTC,1)    //通讯指示灯
//#define LED17_OFF()    ClrBit(PORTC,6)    //远程开机指示灯
//#define LED18_OFF()    ClrBit(PORTC,5)    //远程值机指示灯
//#define LED19_OFF()    ClrBit(PORTC,4)    //本地开机指示灯
//#define LED20_OFF()    ClrBit(PORTC,3)    //本地值机指示灯


#define  LED1_ON()       SetBit(PORTA,7)    
#define  LED2_ON()       SetBit(PORTC,2)    
#define  LED3_ON()       SetBit(PORTA,6)    
#define  LED4_ON()       SetBit(PORTC,1)    
#define  LED5_ON()       SetBit(PORTC,7)    
#define  LED6_ON()       SetBit(PORTC,0)    
#define  LED7_ON()       SetBit(PORTA,5)    
#define  LED8_ON()       SetBit(PORTB,4)    
#define  LED9_ON()       SetBit(PORTA,4)    
#define  LED10_ON()      SetBit(PORTB,3)    
#define  LED11_ON()      SetBit(PORTA,3)    
#define  LED12_ON()      SetBit(PORTB,2)    
#define  LED13_ON()      SetBit(PORTA,2)    
#define  LED14_ON()      SetBit(PORTB,1)    
#define  LED15_ON()      SetBit(PORTA,0)    
#define  LED16_ON()      SetBit(PORTB,0)
#define  LED17_ON()      SetBit(PORTC,6)    //远程开机指示灯
#define  LED18_ON()      SetBit(PORTC,5)    //远程值机指示灯
#define  LED19_ON()      SetBit(PORTC,4)    //本地开机指示灯  
#define  LED20_ON()      SetBit(PORTC,3)    //本地值机指示灯  
	   
#define  LED1_OFF()       ClrBit(PORTA,7)    
#define  LED2_OFF()       ClrBit(PORTC,2)    
#define  LED3_OFF()       ClrBit(PORTA,6)    
#define  LED4_OFF()       ClrBit(PORTC,1)    
#define  LED5_OFF()       ClrBit(PORTC,7)    
#define  LED6_OFF()       ClrBit(PORTC,0)    
#define  LED7_OFF()       ClrBit(PORTA,5)    
#define  LED8_OFF()       ClrBit(PORTB,4)    
#define  LED9_OFF()       ClrBit(PORTA,4)    
#define  LED10_OFF()      ClrBit(PORTB,3)    
#define  LED11_OFF()      ClrBit(PORTA,3)    
#define  LED12_OFF()      ClrBit(PORTB,2)    
#define  LED13_OFF()      ClrBit(PORTA,2)    
#define  LED14_OFF()      ClrBit(PORTB,1)    
#define  LED15_OFF()      ClrBit(PORTA,0)    
#define  LED16_OFF()      ClrBit(PORTB,0) 	 
#define  LED17_OFF()      ClrBit(PORTC,6)    //远程开机指示灯
#define  LED18_OFF()      ClrBit(PORTC,5)    //远程值机指示灯
#define  LED19_OFF()      ClrBit(PORTC,4)    //本地开机指示灯  
#define  LED20_OFF()      ClrBit(PORTC,3)    //本地值机指示灯  
				  
#define Buzzer_ON()    SetBit(PORTA,1) 
#define Buzzer_OFF()   ClrBit(PORTA,1) 
#define RS485_ON()     SetBit(PORTD,2) 
#define RS485_OFF()    ClrBit(PORTD,2)


/*******************************************/ 
#define KEY1   (PIND&BIT(5))   //本地控制值机按键
#define KEY2   (PIND&BIT(4))   //本地控制开机按键
#define KEY3   (PIND&BIT(7))   //远程控制值机按键
#define KEY4   (PIND&BIT(6))   //远程控制开机按键


/*******************************************/ 
#define SYS_OSC        (8000000)
#define _MAX_DI_       (4)
#define CRC_LEN        (2)           //CRC16
#define __5ms__        (5)        




#endif
/*
#define  LED1_OFF()       ClrBit(PORTA,7)    
#define  LED2_OFF()       ClrBit(PORTC,2)    
#define  LED3_OFF()       ClrBit(PORTA,6)    
#define  LED4_OFF()       ClrBit(PORTC,1)    
#define  LED5_OFF()       ClrBit(PORTC,7)    
#define  LED6_OFF()       ClrBit(PORTC,0)    
#define  LED7_OFF()       ClrBit(PORTA,5)    
#define  LED8_OFF()       ClrBit(PORTB,4)    
#define  LED9_OFF()       ClrBit(PORTA,4)    
#define  LED10_OFF()      ClrBit(PORTB,3)    
#define  LED11_OFF()      ClrBit(PORTA,3)    
#define  LED12_OFF()      ClrBit(PORTB,2)    
#define  LED13_OFF()      ClrBit(PORTA,2)    
#define  LED14_OFF()      ClrBit(PORTB,1)    
#define  LED15_OFF()      ClrBit(PORTA,0)    
#define  LED16_OFF()      ClrBit(PORTB,0))    
*/

















  


