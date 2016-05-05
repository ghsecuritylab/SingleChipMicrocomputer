

#ifndef DEFINES_H
#define DEFINES_H


#define _SEG_A 0x01
#define _SEG_B 0x02
#define _SEG_C 0x04
#define _SEG_D 0x08
#define _SEG_E 0x10
#define _SEG_F 0x20
#define _SEG_G 0x40
#define _SEG_H 0x80


#define _FLAG_0 _SEG_A|_SEG_B|_SEG_C|_SEG_D|_SEG_E|_SEG_F
#define _FLAG_1 _SEG_B|_SEG_C
#define _FLAG_2 _SEG_B|_SEG_A|_SEG_G|_SEG_D|_SEG_E
#define _FLAG_3 _SEG_D|_SEG_A|_SEG_B|_SEG_C|_SEG_G
#define _FLAG_4 _SEG_F|_SEG_G|_SEG_B|_SEG_C
#define _FLAG_5 _SEG_F|_SEG_A|_SEG_G|_SEG_D|_SEG_C
#define _FLAG_6 _SEG_F|_SEG_A|_SEG_G|_SEG_E|_SEG_C|_SEG_D
#define _FLAG_7 _SEG_A|_SEG_B|_SEG_C
#define _FLAG_8 _SEG_A|_SEG_B|_SEG_C|_SEG_D|_SEG_E|_SEG_F|_SEG_G
#define _FLAG_9 _SEG_A|_SEG_B|_SEG_C|_SEG_D|_SEG_F|_SEG_G
#define _FLAG_A _SEG_A|_SEG_B|_SEG_C|_SEG_E|_SEG_F|_SEG_G
#define _FLAG_B _SEG_E|_SEG_G|_SEG_F|_SEG_C|_SEG_D
#define _FLAG_C _SEG_A|_SEG_D|_SEG_E|_SEG_F
#define _FLAG_D _SEG_E|_SEG_B|_SEG_C|_SEG_D|_SEG_G
#define _FLAG_E _SEG_A|_SEG_G|_SEG_D|_SEG_E|_SEG_F
#define _FLAG_F _SEG_A|_SEG_G|_SEG_E|_SEG_F
#define _FLAG_R _SEG_G|_SEG_F|_SEG_E
#define _FLAG_o _SEG_G|_SEG_C|_SEG_D|_SEG_E
#define _FLAG_O _SEG_E|_SEG_F|_SEG_A|_SEG_B|_SEG_C
#define _FLAG_n  _SEG_G|_SEG_C|_SEG_E
#define _FLAG_N _SEG_A|_SEG_B|_SEG_C|_SEG_E|_SEG_F
#define _FLAG_P _SEG_A|_SEG_B|_SEG_E|_SEG_F|_SEG_G
#define _FLAG_S _SEG_F|_SEG_A|_SEG_G|_SEG_D|_SEG_C
#define _FLAG_H _SEG_B|_SEG_C|_SEG_E|_SEG_F|_SEG_G
#define _FLAG_t _SEG_D|_SEG_E|_SEG_F|_SEG_G
#define _FLAG_U _SEG_B|_SEG_C|_SEG_D|_SEG_E|_SEG_F
#define _FLAG_L _SEG_D|_SEG_E|_SEG_F
#define _FLAG_r _SEG_E|_SEG_G
#define _FLAG_I _SEG_B|_SEG_C
#define _FLAG_c _SEG_G|_SEG_D|_SEG_E
#define _FLAG_Y _SEG_B|_SEG_C|_SEG_D|_SEG_F|_SEG_G

#define RevBit(port, bitn)           (port ^=  (1<<(bitn)))                            
#define SetBit(port, bitn)           (port |=  (1<<(bitn)))                                
#define ClrBit(port, bitn)           (port &= ~(1<<(bitn)))                               
#define GetBit(port, bitn)           (port &   (1<<(bitn)))                              
#define OutBit(port, bitn, value)    ((value) ? (SetBit(port, bitn)) : (ClrBit(port, bitn)))
#define BIT(bitn) (1<<bitn)


#define __5ms__ (5)

#define TMEP_COM_100BIT_OFF()  SetBit(PORTA, 0)
#define TMEP_COM_100BIT_ON()   ClrBit(PORTA, 0)
#define TMEP_COM_10BIT_OFF()   SetBit(PORTA, 1)
#define TMEP_COM_10BIT_ON()    ClrBit(PORTA, 1)
#define TMEP_COM_1BIT_OFF()    SetBit(PORTA, 2)
#define TMEP_COM_1BIT_ON()     ClrBit(PORTA, 2)


#define RH_COM_100BIT_OFF()    SetBit(PORTG, 1)
#define RH_COM_100BIT_ON()     ClrBit(PORTG, 1)
#define RH_COM_10BIT_OFF()     SetBit(PORTG, 0)
#define RH_COM_10BIT_ON()      ClrBit(PORTG, 0)
#define RH_COM_1BIT_OFF()      SetBit(PORTD, 7)
#define RH_COM_1BIT_ON()       ClrBit(PORTD, 7)

#define TMEP_COM_ALL_OFF() {TMEP_COM_100BIT_OFF();TMEP_COM_10BIT_OFF();TMEP_COM_1BIT_OFF();}
#define TMEP_COM_ALL_ON()  {TMEP_COM_100BIT_ON();TMEP_COM_10BIT_ON();TMEP_COM_1BIT_ON();}
#define RH_COM_ALL_OFF()   {RH_COM_100BIT_OFF();RH_COM_10BIT_OFF();RH_COM_1BIT_OFF();}
#define RH_COM_ALL_ON()    {RH_COM_100BIT_ON();RH_COM_10BIT_ON();RH_COM_1BIT_ON();}



#endif