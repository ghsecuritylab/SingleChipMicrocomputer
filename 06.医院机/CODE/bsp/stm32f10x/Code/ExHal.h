#ifndef __EXHAL_H
#define __EXHAL_H

void ClkCfg(void);
void ComIOcfg(void);
void SDIOcfg(void);
void OutPutIOcfg(void);
void InputIOcfg(void);
void AdcIOcfg(void);
void UartTimeOut(UartType *P2data);
void ShellProc1(void);
void ShellProc2(void);
void ShellProc3(void);
void ShellProc4(void);
void ShellProc5(void);
void USART_Configuration(USART_TypeDef *USARTx, uint32_t baud, uint16_t stopbit, uint16_t  parity);
INT32 Asc2Int(char *TrgStr);

#define  RS232_Disable() GPIO_SetBits(GPIOG,GPIO_Pin_6)
#define  RS232_Ensable() GPIO_ResetBits(GPIOG,GPIO_Pin_6)



#endif

