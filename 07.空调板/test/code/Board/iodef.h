

#ifndef IODEF_H
#define IODEF_H
#include "typedef.h"


#define KLED     PORTB |=  BIT(5)    //���
#define GLED     PORTB &= ~BIT(5)
#define KJQC5    PORTB |=  BIT(4)    //���ָʾ��
#define GJQC5    PORTB &= ~BIT(4)
#define KJQC4    PORTB |=  BIT(3)
#define GJQC4    PORTB &= ~BIT(3)
#define KJQC3    PORTB |=  BIT(2)    //����
#define GJQC3    PORTB &= ~BIT(2)
#define KJQC2    PORTB |=  BIT(1)    //������
#define GJQC2    PORTB &= ~BIT(1)
#define KJQC1    PORTB |=  BIT(0)    //������
#define GJQC1    PORTB &= ~BIT(0)



#endif























