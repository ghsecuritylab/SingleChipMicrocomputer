#include "A_IIC.h"


//延时

void DelayUS(UINT8  count)
{
    while ( count )
    {
        count--;
    }
}


void IIC_START(void)
{
    SDAout();
    CLKto1();
    SDAto1();
    DelayUS(5);
    SDAto0(); 
    DelayUS(5);    
    CLKto0();
    DelayUS(5);
}

void IIC_STOP(void)
{
    CLKto0();
    SDAout();
    SDAto0();
    DelayUS(5);
    CLKto1();
    DelayUS(5);     
    SDAto1(); 
    DelayUS(5);    
}

void IIC_SENDBYTE(UINT8 data)
{
    UINT8 tmp;

    for ( tmp=0; tmp<8; tmp++ )
    {
        if ( data&(0x80>>tmp) )
        {
            SDAto1();
        }
        else
        {
            SDAto0();
        } 
        DelayUS(5);
        CLKto1();
        nop;       
        CLKto0();       
    }
    //接收ACK
    SDAin();
    DelayUS(5);
    CLKto1(); 
    nop;
    CLKto0();
    SDAout();
    nop;
}

UINT8 IIC_RD1BYTE(UINT8 ackFlag)
{
    UINT8 tmp,DataOut;

    SDAin();
    CLKto0();
    DataOut =0;
    for ( tmp=0; tmp<8; tmp++ )
    {
        DelayUS(5); 
        CLKto1();           
        DelayUS(5);
        DataOut<<=1;  
        if ( testSDA )
        {
            DataOut|=1;
        }
        CLKto0();              
    }
    //发送ACK
    DelayUS(5);
    SDAout();
    if ( ackFlag )
    {
        SDAto0();
    }
    else
    {
        SDAto1();
    }
    CLKto1();
    DelayUS(5);
    CLKto0();
    return(DataOut);
}





void PTC2313Set()
{
    IIC_START();
    IIC_SENDBYTE(0x88);
    IIC_SENDBYTE(0x88);

}
