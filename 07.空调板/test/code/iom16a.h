/****************************************************************************
 **             - iom16.h -
 **
 **     This file declares the internal register addresses for ATmega16.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright 2000 IAR Systems AB. All rights reserved.
 **
 **     File version: $Revision: 8192 $
 **
 ***************************************************************************/

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#include "iomacro.h"

#if TID_GUARD(3)
#error This file should only be compiled with iccavr or aavr with processor option -v3
#endif /* TID_GUARD(3) */

#ifdef __HAS_RAMPZ__
#error This file should not have RAMPZ enabled, use --cpu or --64k_flash
#endif /* __HAS_RAMPZ__ */

#ifndef __IOM16_H

/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#define    RESET_vect           (0x00)
#define    INT0_vect            (0x04)
#define    INT1_vect            (0x08)
#define    TIMER2_COMP_vect     (0x0C)
#define    TIMER2_OVF_vect      (0x10)
#define    TIMER1_CAPT_vect     (0x14)
#define    TIMER1_COMPA_vect    (0x18)
#define    TIMER1_COMPB_vect    (0x1C)
#define    TIMER1_OVF_vect      (0x20)
#define    TIMER0_OVF_vect      (0x24)
#define    SPI_STC_vect         (0x28)
#define    USART_RXC_vect       (0x2C)
#define    USART_UDRE_vect      (0x30)
#define    USART_TXC_vect       (0x34)
#define    ADC_vect             (0x38)
#define    EE_RDY_vect          (0x3C)
#define    ANA_COMP_vect        (0x40)
#define    TWI_vect             (0x44)
#define    INT2_vect            (0x48)
#define    TIMER0_COMP_vect     (0x4C)
#define    SPM_RDY_vect         (0x50)

#ifdef __IAR_SYSTEMS_ASM__   
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif /* ENABLE_BIT_DEFINITIONS */
#include "bitdefinitions/iom16a.inc"
#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* __IOM16_H (define part) */


/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */
#if !defined(__IOM16_H) || defined(__IAR_SYSTEMS_ASM__)
#define __IOM16_H

#pragma language=save
#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call, 
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call, 
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union { 
 *              unsigned char TCCR2; 
 *              struct { 
 *                      unsigned char TCCR2_Bit0:1, 
 *                                    TCCR2_Bit1:1, 
 *                                    TCCR2_Bit2:1, 
 *                                    TCCR2_Bit3:1, 
 *                                    TCCR2_Bit4:1, 
 *                                    TCCR2_Bit5:1, 
 *                                    TCCR2_Bit6:1, 
 *                                    TCCR2_Bit7:1; 
 *                     }; 
 *              struct { 
 *                      unsigned char TCCR2_CS20:1, 
 *                                    TCCR2_CS21:1, 
 *                                    TCCR2_CS22:1, 
 *                                    TCCR2_WGM21:1, 
 *                                    TCCR2_COM20:1, 
 *                                    TCCR2_COM21:1, 
 *                                    TCCR2_WGM20:1, 
 *                                    TCCR2_FOC2:1; 
 *                     }; 
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5); 
 * or if ENABLE_BIT_DEFINITIONS is defined   
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

SFR_B_N(0x3F,SREG,I,T,H,S,V,N,Z,C)
SFR_W_N(0x3D,SP,Dummy15,Dummy14,Dummy13,Dummy12,Dummy11,SP10,SP9,SP8,SP7,SP6,SP5,SP4,SP3,SP2,SP1,SP0)
SFR_B_R(0x3C,OCR0)
SFR_B_N(0x3B,GICR,INT1,INT0,INT2,Dummy4,Dummy3,Dummy2,IVSEL,IVCE)
SFR_B_N(0x3A,GIFR,INTF1,INTF0,INTF2,Dummy4,Dummy3,Dummy2,Dummy1,Dummy0)
SFR_B_N(0x39,TIMSK,OCIE2,TOIE2,TICIE1,OCIE1A,OCIE1B,TOIE1,OCIE0,TOIE0)
SFR_B_N(0x38,TIFR,OCF2,TOV2,ICF1,OCF1A,OCF1B,TOV1,OCF0,TOV0)
SFR_B_N(0x37,SPMCR,SPMIE,RWWSB,Dummy5,RWWSRE,BLBSET,PGWRT,PGERS,SPMEN)
SFR_B_N(0x36,TWCR,TWINT,TWEA,TWSTA,TWSTO,TWWC,TWEN,Dummy1,TWIE)
SFR_B_N(0x35,MCUCR,SM2,SE,SM1,SM0,ISC11,ISC10,ISC01,ISC00)
SFR_B_N(0x34,MCUCSR,JTD,ISC2,Dummy5,JTRF,WDRF,BORF,EXTRF,PORF)
SFR_B_N(0x33,TCCR0,FOC0,WGM00,COM01,COM00,WGM01,CS02,CS01,CS00)
SFR_B_R(0x32,TCNT0)
SFR_B2_R(0x31,OSCCAL,OCDR)
SFR_B_N(0x30,SFIOR,ADTS2,ADTS1,ADTS0,Dummy4,ACME,PUD,PSR2,PSR10)
SFR_B_N(0x2F,TCCR1A,COM1A1,COM1A0,COM1B1,COM1B0,FOC1A,FOC1B,WGM11,WGM10)
SFR_B_N(0x2E,TCCR1B,ICNC1,ICES1,Dummy5,WGM13,WGM12,CS12,CS11,CS10)
SFR_W_R(0x2C,TCNT1)
SFR_W_R(0x2A,OCR1A)
SFR_W_R(0x28,OCR1B)
SFR_W_R(0x26,ICR1)
SFR_B_N(0x25,TCCR2,FOC2,WGM20,COM21,COM20,WGM21,CS22,CS21,CS20)
SFR_B_R(0x24,TCNT2)
SFR_B_R(0x23,OCR2)
SFR_B_N(0x22,ASSR,Dummy7,Dummy6,Dummy5,Dummy4,AS2,TCN2UB,OCR2UB,TCR2UB)
SFR_B_N(0x21,WDTCR,Dummy7,Dummy6,Dummy5,WDTOE,WDE,WDP2,WDP1,WDP0)
SFR_B2_N(0x20,UBRRH,UCSRC,URSEL,UMSEL,UPM1,UPM0,USBS,UCSZ1,UCSZ0,UCPOL)
SFR_W_R(0x1E,EEAR)
SFR_B_R(0x1D,EEDR)
SFR_B_N(0x1C,EECR,Dummy7,Dummy6,Dummy5,Dummy4,EERIE,EEMWE,EEWE,EERE)
SFR_B_N(0x1B,PORTA,PORTA7,PORTA6,PORTA5,PORTA4,PORTA3,PORTA2,PORTA1,PORTA0)
SFR_B_N(0x1A,DDRA,DDA7,DDA6,DDA5,DDA4,DDA3,DDA2,DDA1,DDA0)
SFR_B_N(0x19,PINA,PINA7,PINA6,PINA5,PINA4,PINA3,PINA2,PINA1,PINA0)
SFR_B_N(0x18,PORTB,PORTB7,PORTB6,PORTB5,PORTB4,PORTB3,PORTB2,PORTB1,PORTB0)
SFR_B_N(0x17,DDRB,DDB7,DDB6,DDB5,DDB4,DDB3,DDB2,DDB1,DDB0)
SFR_B_N(0x16,PINB,PINB7,PINB6,PINB5,PINB4,PINB3,PINB2,PINB1,PINB0)
SFR_B_N(0x15,PORTC,PORTC7,PORTC6,PORTC5,PORTC4,PORTC3,PORTC2,PORTC1,PORTC0)
SFR_B_N(0x14,DDRC,DDC7,DDC6,DDC5,DDC4,DDC3,DDC2,DDC1,DDC0)
SFR_B_N(0x13,PINC,PINC7,PINC6,PINC5,PINC4,PINC3,PINC2,PINC1,PINC0)
SFR_B_N(0x12,PORTD,PORTD7,PORTD6,PORTD5,PORTD4,PORTD3,PORTD2,PORTD1,PORTD0)
SFR_B_N(0x11,DDRD,DDD7,DDD6,DDD5,DDD4,DDD3,DDD2,DDD1,DDD0)
SFR_B_N(0x10,PIND,PIND7,PIND6,PIND5,PIND4,PIND3,PIND2,PIND1,PIND0)
SFR_B_R(0x0F,SPDR)
SFR_B_N(0x0E,SPSR,SPIF,WCOL,Dummy5,Dummy4,Dummy3,Dummy2,Dummy1,SPI2X)
SFR_B_N(0x0D,SPCR,SPIE,SPE,DORD,MSTR,CPOL,CPHA,SPR1,SPR0)
SFR_B_R(0x0C,UDR)
SFR_B_N(0x0B,UCSRA,RXC,TXC,UDRE,FE,DOR,PE,U2X,MPCM)
SFR_B_N(0x0A,UCSRB,RXCIE,TXCIE,UDRIE,RXEN,TXEN,UCSZ2,RXB8,TXB8)
SFR_B_R(0x09,UBRRL)
SFR_B_N(0x08,ACSR,ACD,ACBG,ACO,ACI,ACIE,ACIC,ACIS1,ACIS0)
SFR_B_N(0x07,ADMUX,REFS1,REFS0,ADLAR,MUX4,MUX3,MUX2,MUX1,MUX0)
SFR_B_N(0x06,ADCSRA,ADEN,ADSC,ADATE,ADIF,ADIE,ADPS2,ADPS1,ADPS0)
SFR_W_R(0x04,ADC)
SFR_B_R(0x03,TWDR)
SFR_B_N(0x02,TWAR,TWA6,TWA5,TWA4,TWA3,TWA2,TWA1,TWA0,TWGCE)
SFR_B_N(0x01,TWSR,TWS7,TWS6,TWS5,TWS4,TWS3,Dummy2,TWPS1,TWPS0)
SFR_B_R(0x00,TWBR)

#pragma language=restore

#ifndef __IAR_SYSTEMS_ASM__
#include "bitdefinitions/iom16a.inc"
#endif

#endif /* __IOM16_H (SFR part) */
