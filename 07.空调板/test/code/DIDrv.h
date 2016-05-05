

#ifndef _74HC165_H_
#define _74HC165_H_

#define  _165PLDto0  GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define  _165PLDto1  GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define  _165CLKto0  GPIO_ResetBits(GPIOG,GPIO_Pin_2)         
#define  _165CLKto1  GPIO_SetBits(GPIOG,GPIO_Pin_2)           
#define  _165SDOis1  (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8)!=0x00)


#define INPUT_CLR 0x80
#define INPUT_INQ 0x40

extern uint08 InputState[2];
extern uint08 InputStateRec[2];
extern uint08 InputCnt[8];

void Input165();
void InputDeal();

#endif
