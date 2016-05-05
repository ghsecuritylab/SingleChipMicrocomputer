#include "includes.h"

FLS_SHOW_DEF SHOWBuff;

const uchar number[] =
{
   _FLAG_NUM_0,
   _FLAG_NUM_1,
   _FLAG_NUM_2,
   _FLAG_NUM_3,
   _FLAG_NUM_4,
   _FLAG_NUM_5,
   _FLAG_NUM_6,
   _FLAG_NUM_7,
   _FLAG_NUM_8,
   _FLAG_NUM_9,
   _FLAG_NUM_A,
   _FLAG_NUM_B,
   _FLAG_NUM_C,
   _FLAG_NUM_D,
   _FLAG_NUM_E,
   _FLAG_NUM_F
};

void delay_nms(uint n)
{
   uint i;
   while (n--) 
   for (i = 0; i < 500; i++) ;
}


void Write_Data_H(uchar Data, uchar Cnt)     
{
   uchar i;
   for (i = 0; i < Cnt; i++)
   {
      WRITE0;
      if (Data & 0x80)  
      {
         DATA1;
      }
      else 
      {
         DATA0;
      }
      nop;
      WRITE1;
      Data <<= 1;
   }
   WRITE0;
   DATA0;
}

void Write_Data_L(uchar Data, uchar Cnt)       
{
   unsigned char i;
   for (i = 0; i < Cnt; i++)
   {
      WRITE0;
      if (Data & 0x01)                         
         DATA1;
      else 
	 DATA0;
      nop;
      nop;
      WRITE1;
      Data >>= 1;
   }
   WRITE0;
   DATA0;
}

void WriteCmd(uchar Cmd)
{
   CS0;
   nop;
   Write_Data_H(0x80, 4);     
   Write_Data_H(Cmd, 8);      
   CS1;
   nop;
}

void WriteOneData4(uchar Addr, uchar Data)
{
   CS0;
   Write_Data_H(0xa0, 3);     
   Write_Data_H(Addr << 2, 6);  
   Write_Data_L(Data, 4);    
   CS1;
   nop;
}

void WriteOneData8(uchar Addr, uchar Data)
{
   CS0;
   Write_Data_H(0xa0, 3);     
   Write_Data_H(Addr << 2, 6);  
   Write_Data_L(Data, 8);    
   CS1;
   nop;
}

void WriteAllData(uchar Addr, uchar *p, uchar cnt)
{
   uchar i;
   CS0;
   Write_Data_H(0xa0, 3);      
   Write_Data_H(Addr << 2, 6);   
   for (i = 0; i < cnt; i++)     
   {
      Write_Data_L(*p, 8);
      p++;
   }
   CS1;
   nop;
}

void TM1621_init(void)
{
   CS1;
   WRITE1;
   DATA1;
   nop;
   delay_nms(1);
   WriteCmd(BIAS);         
   WriteCmd(RC);           
   WriteCmd(SYSDIS);       
   WriteCmd(WDTDIS);       
   WriteCmd(SYSEN);        
   WriteCmd(LCDON);        
}

void LCDShowAll(uchar *p2Data)
{
//   uchar tmpData;
//   uchar tmp;
   if (!RunFlag.Solo._10ms) 
   {
       return;
   }
   WriteAllData(0,p2Data,6);
}

void DispNumL(FLS_SHOW_DEF *show, uchar Data)
{
   show->Solo.NUMBER_2A = 0;
   if ((Data & SEG_A) != 0)
   {
      show->Solo.NUMBER_2A = 1;
   }

   show->Solo.NUMBER_2B = 0;
   if ((Data & SEG_B) != 0)
   {
      show->Solo.NUMBER_2B = 1;
   }

   show->Solo.NUMBER_2C = 0;
   if ((Data & SEG_C) != 0)
   {
      show->Solo.NUMBER_2C = 1;
   }

   show->Solo.NUMBER_2D = 0;
   if ((Data & SEG_D) != 0)
   {
      show->Solo.NUMBER_2D = 1;
   }

   show->Solo.NUMBER_2E = 0;
   if ((Data & SEG_E) != 0)
   {
      show->Solo.NUMBER_2E = 1;
   }

   show->Solo.NUMBER_2F = 0;
   if ((Data & SEG_F) != 0)
   {
      show->Solo.NUMBER_2F = 1;
   }

   show->Solo.NUMBER_2G = 0;
   if ((Data & SEG_G) != 0)
   {
      show->Solo.NUMBER_2G = 1;
   }
}

void DispNumH(FLS_SHOW_DEF *show, uchar Data)
{

   show->Solo.NUMBER_1A = 0;
   if ((Data & SEG_A) != 0)
   {
      show->Solo.NUMBER_1A = 1;
   }

   show->Solo.NUMBER_1B = 0;
   if ((Data & SEG_B) != 0)
   {
      show->Solo.NUMBER_1B = 1;
   }

   show->Solo.NUMBER_1C = 0;
   if ((Data & SEG_C) != 0)
   {
      show->Solo.NUMBER_1C = 1;
   }

   show->Solo.NUMBER_1D = 0;
   if ((Data & SEG_D) != 0)
   {
      show->Solo.NUMBER_1D = 1;
   }

   show->Solo.NUMBER_1E = 0;
   if ((Data & SEG_E) != 0)
   {
      show->Solo.NUMBER_1E = 1;
   }

   show->Solo.NUMBER_1F = 0;
   if ((Data & SEG_F) != 0)
   {
      show->Solo.NUMBER_1F = 1;
   }

   show->Solo.NUMBER_1G = 0;
   if ((Data & SEG_G) != 0)
   {
      show->Solo.NUMBER_1G = 1;
   }
}

void LCDDispNum(FLS_SHOW_DEF *show, uchar Data)
{
   uchar temp1, temp2;
   temp1 = number[Data / 10];
   temp2 = number[Data % 10];
   DispNumH(show, temp1);
   DispNumL(show, temp2);

}


void LCDDispWord(FLS_SHOW_DEF *show)
{
   show->Solo.WORD_BOX_1 = 1;
   show->Solo.WOED_BOX_2 = 1;
   show->Solo.WOED_BOX_FAN = 1;
}

void DispTestErr(FLS_SHOW_DEF *show, FLS_DEF *Fls)
{
//-----------------------------

   show->Solo.FAN_ERR = 0;
   if (Fls->Output.Solo.Fan)
   {
      if (Fls->Input.Solo.TestFan)
      {
	 show->Solo.FAN_ERR = RunFlag.Solo.FastBlink;
      }
      else
      {
	 show->Solo.FAN_ERR = 0;
      }
   }
//-----------------------------
   show->Solo.LIGHT_ERR = 0;
   if (Fls->Output.Solo.Light)
   {
      if (Fls->Input.Solo.TestLight)
      {
	 show->Solo.LIGHT_ERR = RunFlag.Solo.FastBlink;
      }
      else
      {
	 show->Solo.LIGHT_ERR = 0;
      }
   }
//-----------------------------
   show->Solo.IN_DOOR_LOCK_ERR = 0;
   if (Fls->Output.Solo.Indoor)
   {
      if (Fls->Input.Solo.TestIndoor)
      {
	 show->Solo.IN_DOOR_LOCK_ERR = RunFlag.Solo.FastBlink;
      }
      else
      {
	 show->Solo.IN_DOOR_LOCK_ERR = 0;
      }
   }
//-----------------------------
   show->Solo.OUT_DOOR_LOCK_ERR = 0;
   if (Fls->Output.Solo.Outdoor)
   {
      if (Fls->Input.Solo.TestOutdoor)
      {
	 show->Solo.OUT_DOOR_LOCK_ERR = RunFlag.Solo.FastBlink;
      }
      else
      {
	 show->Solo.OUT_DOOR_LOCK_ERR = 0;
      }
   }

}

void DispOneFls(FLS_SHOW_DEF *show, FLS_DEF *Fls)
{
   uint tmp = (msTick / 70) % 3;
   if (Fls->Output.Solo.Fan && Fls->Time.secWorkTimer>0) 
   {
       LCDDispNum(show, Fls->Time.secWorkTimer);
   }
   else 
   {
       LCDDispNum(show,FLS1.Par.FanRunningTime);// 
       //LCDDispNum(show, Fls->Status.All);
       //LCDDispNum(show, Fls->Input.All);
       //LCDDispNum(show, TestMe); 
       //LCDDispNum(show, WTV1.Solo.Step);
   }
//   if (Fls->KeyTreated.Solo.KeyEmc)
//   {
//       LCDDispNum(show, Fls->Status.Solo.Step);
//   }
//--------------------------------
   if (Fls->Output.Solo.Fan)
   {
      show->Solo.FAN_ICON_1 = 0;
      show->Solo.FAN_ICON_2 = 0;
      show->Solo.FAN_ICON_3 = 0;
      show->Solo.FAN_ICON_ROUND = 1;
      if (tmp == 0)
      {
         show->Solo.FAN_ICON_1 = 1;
         show->Solo.FAN_ICON_2 = 1;
      }
      if (tmp == 1)
      {
         show->Solo.FAN_ICON_1 = 1;
         show->Solo.FAN_ICON_3 = 1;
      }
      if (tmp == 2)
      {
         show->Solo.FAN_ICON_2 = 1;
         show->Solo.FAN_ICON_3 = 1;
      }
   }
   else
   {
      show->Solo.FAN_ICON_1 = 0;
      show->Solo.FAN_ICON_2 = 0;
      show->Solo.FAN_ICON_3 = 0;
      show->Solo.FAN_ICON_ROUND = 0;
   }
//--------------------------------
   if (Fls->Output.Solo.Light)
   {
      show->Solo.LIGHT_ICON = 1;
   }
   else
   {
      show->Solo.LIGHT_ICON = 0;
   }
//--------------------------------
   if (Fls->Input.Solo.InsideMagnet)
   {
      show->Solo.IN_DOOR_LOCK_ICON = 1;
   }
   else
   {
      show->Solo.IN_DOOR_LOCK_ICON = 0;
   }
//--------------------------------
   if (Fls->Input.Solo.OutsideMagnet)
   {
      show->Solo.OUT_DOOR_LOCK_ICON = 1;
   }
   else
   {
      show->Solo.OUT_DOOR_LOCK_ICON = 0;
   }
//-------------------------------
   if (Fls->Status.Solo.Emc)
   {
      show->Solo.EMC_ICON = 1;
   }
   else
   {
      show->Solo.EMC_ICON = 0;
   }
//-----------------------------
   if (Fls->Input.Solo.Infrared)
   {
      show->Solo.INFRARED_ICON = 1;
   }
   else
   {
      show->Solo.INFRARED_ICON = 0;
   }

   if (RunFlag.Solo._1ms)
   {
      DispTestErr(show,Fls);
   }
}





