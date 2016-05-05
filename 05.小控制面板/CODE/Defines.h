


#ifndef DEFINES_H
#define DEFINES_H



#define BIT(x)        (  1 << x       )
#define SetBit(x,y)   (  x |= BIT(y)  ) 
#define ClrBit(x,y)   (  x &= ~BIT(y) ) 
#define GetBit(x,y)   (  x & BIT(y)   ) 

/*******************************************/ 
//#define LED1_ON()      SetBit(PORTA,6)   //����ָʾ��
//#define LED2_ON()      SetBit(PORTC,2)   //ֵ��ָʾ��
//#define LED3_ON()      SetBit(PORTA,7)   //��Դָʾ��
//#define LED4_ON()      SetBit(PORTC,7)   //������ϵ�
//#define LED5_ON()      SetBit(PORTC,0)   //ȱ�籨����
//#define LED6_ON()      SetBit(PORTA,5)   //��Ч������
//#define LED7_ON()      SetBit(PORTA,4)   //��Ч������
//#define LED8_ON()      SetBit(PORTA,3)   //�Ǹ�Ч������
//#define LED9_ON()      SetBit(PORTA,2)   //��Ч������
//#define LED10_ON()     SetBit(PORTB,4)   //���ȸ��±�����
//#define LED11_ON()     SetBit(PORTB,3)   //Ԥ�ȸ��±�����
//#define LED12_ON()     SetBit(PORTB,2)   //����������
//#define LED13_ON()     SetBit(PORTB,1)   //����ͣ��������
//#define LED14_ON()     SetBit(PORTA,0)   //��Ӽ�ͣ������
//#define LED15_ON()     SetBit(PORTB,0)   //����������
//#define LED16_ON()     SetBit(PORTC,1)   //ͨѶָʾ��
//#define LED17_ON()     SetBit(PORTC,6)   //Զ�̿���ָʾ��
//#define LED18_ON()     SetBit(PORTC,5)   //Զ��ֵ��ָʾ��
//#define LED19_ON()     SetBit(PORTC,4)   //���ؿ���ָʾ��
//#define LED20_ON()     SetBit(PORTC,3)   //����ֵ��ָʾ��
//
//#define LED1_OFF()     ClrBit(PORTA,6)    //����ָʾ��
//#define LED2_OFF()     ClrBit(PORTC,2)    //ֵ��ָʾ��
//#define LED3_OFF()     ClrBit(PORTA,7)    //��Դָʾ��
//#define LED4_OFF()     ClrBit(PORTC,7)    //������ϵ�
//#define LED5_OFF()     ClrBit(PORTC,0)    //ȱ�籨����
//#define LED6_OFF()     ClrBit(PORTA,5)    //��Ч������
//#define LED7_OFF()     ClrBit(PORTA,4)    //��Ч������
//#define LED8_OFF()     ClrBit(PORTA,3)    //�Ǹ�Ч������
//#define LED9_OFF()     ClrBit(PORTA,2)    //��Ч������
//#define LED10_OFF()    ClrBit(PORTB,4)    //���ȸ��±�����
//#define LED11_OFF()    ClrBit(PORTB,3)    //Ԥ�ȸ��±�����
//#define LED12_OFF()    ClrBit(PORTB,2)    //����������
//#define LED13_OFF()    ClrBit(PORTB,1)    //����ͣ��������
//#define LED14_OFF()    ClrBit(PORTA,0)    //��Ӽ�ͣ������
//#define LED15_OFF()    ClrBit(PORTB,0)    //����������
//#define LED16_OFF()    ClrBit(PORTC,1)    //ͨѶָʾ��
//#define LED17_OFF()    ClrBit(PORTC,6)    //Զ�̿���ָʾ��
//#define LED18_OFF()    ClrBit(PORTC,5)    //Զ��ֵ��ָʾ��
//#define LED19_OFF()    ClrBit(PORTC,4)    //���ؿ���ָʾ��
//#define LED20_OFF()    ClrBit(PORTC,3)    //����ֵ��ָʾ��


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
#define  LED17_ON()      SetBit(PORTC,6)    //Զ�̿���ָʾ��
#define  LED18_ON()      SetBit(PORTC,5)    //Զ��ֵ��ָʾ��
#define  LED19_ON()      SetBit(PORTC,4)    //���ؿ���ָʾ��  
#define  LED20_ON()      SetBit(PORTC,3)    //����ֵ��ָʾ��  
	   
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
#define  LED17_OFF()      ClrBit(PORTC,6)    //Զ�̿���ָʾ��
#define  LED18_OFF()      ClrBit(PORTC,5)    //Զ��ֵ��ָʾ��
#define  LED19_OFF()      ClrBit(PORTC,4)    //���ؿ���ָʾ��  
#define  LED20_OFF()      ClrBit(PORTC,3)    //����ֵ��ָʾ��  
				  
#define Buzzer_ON()    SetBit(PORTA,1) 
#define Buzzer_OFF()   ClrBit(PORTA,1) 
#define RS485_ON()     SetBit(PORTD,2) 
#define RS485_OFF()    ClrBit(PORTD,2)


/*******************************************/ 
#define KEY1   (PIND&BIT(5))   //���ؿ���ֵ������
#define KEY2   (PIND&BIT(4))   //���ؿ��ƿ�������
#define KEY3   (PIND&BIT(7))   //Զ�̿���ֵ������
#define KEY4   (PIND&BIT(6))   //Զ�̿��ƿ�������


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

















  


