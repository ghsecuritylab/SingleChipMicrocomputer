
#include "includes.h"

FC_DISP_DEF DispBuff;


const uchar numberSeg[] =
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

void DisplaySetTemp(uchar trg)
{
    uchar tmp = numberSeg[trg / 10];
    DispBuff.Solo.SET_TEMP_1A = (tmp & SEG_A)? 1:0;
    DispBuff.Solo.SET_TEMP_1B = (tmp & SEG_B)? 1:0;
    DispBuff.Solo.SET_TEMP_1C = (tmp & SEG_C)? 1:0;
    DispBuff.Solo.SET_TEMP_1D = (tmp & SEG_D)? 1:0;
    DispBuff.Solo.SET_TEMP_1E = (tmp & SEG_E)? 1:0;
    DispBuff.Solo.SET_TEMP_1F = (tmp & SEG_F)? 1:0;
    DispBuff.Solo.SET_TEMP_1G = (tmp & SEG_G)? 1:0;
    tmp = numberSeg[trg % 10];
    DispBuff.Solo.SET_TEMP_2A = (tmp & SEG_A)? 1:0;
    DispBuff.Solo.SET_TEMP_2B = (tmp & SEG_B)? 1:0;
    DispBuff.Solo.SET_TEMP_2C = (tmp & SEG_C)? 1:0;
    DispBuff.Solo.SET_TEMP_2D = (tmp & SEG_D)? 1:0;
    DispBuff.Solo.SET_TEMP_2E = (tmp & SEG_E)? 1:0;
    DispBuff.Solo.SET_TEMP_2F = (tmp & SEG_F)? 1:0;
    DispBuff.Solo.SET_TEMP_2G = (tmp & SEG_G)? 1:0;
}

void DisplayRomTemp(uchar trg)
{
    uchar tmp = numberSeg[trg / 10];
    DispBuff.Solo.ROM_TEMP_3A = (tmp & SEG_A)? 1:0;
    DispBuff.Solo.ROM_TEMP_3B = (tmp & SEG_B)? 1:0;
    DispBuff.Solo.ROM_TEMP_3C = (tmp & SEG_C)? 1:0;
    DispBuff.Solo.ROM_TEMP_3D = (tmp & SEG_D)? 1:0;
    DispBuff.Solo.ROM_TEMP_3E = (tmp & SEG_E)? 1:0;
    DispBuff.Solo.ROM_TEMP_3F = (tmp & SEG_F)? 1:0;
    DispBuff.Solo.ROM_TEMP_3G = (tmp & SEG_G)? 1:0;
    tmp = numberSeg[trg % 10];
    DispBuff.Solo.ROM_TEMP_4A = (tmp & SEG_A)? 1:0;
    DispBuff.Solo.ROM_TEMP_4B = (tmp & SEG_B)? 1:0;
    DispBuff.Solo.ROM_TEMP_4C = (tmp & SEG_C)? 1:0;
    DispBuff.Solo.ROM_TEMP_4D = (tmp & SEG_D)? 1:0;
    DispBuff.Solo.ROM_TEMP_4E = (tmp & SEG_E)? 1:0;
    DispBuff.Solo.ROM_TEMP_4F = (tmp & SEG_F)? 1:0;
    DispBuff.Solo.ROM_TEMP_4G = (tmp & SEG_G)? 1:0;
}

void LCDDispNum()
{
    DisplaySetTemp(FC1.Run.SetTemp);
    DisplayRomTemp(FC1.Buff.RoomTemp);

//  DisplaySetTemp(FC1.Run.SetTemp);
//  DisplayRomTemp(FC1.Run.RoomTemp);
//  displayLeft(FC1.Run.SetTemp);
//  displayLeft(FC1.Run.SetTemp);
//  DisplayRomTemp(FC1.Buff.DiIn.Solo.Addr);
    



//  DispBuff.Solo.TIME_5A = (numberSeg[FC1.Run.SetTime / 60 / 10] & SEG_A && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_5B = (numberSeg[FC1.Run.SetTime / 60 / 10] & SEG_B && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_5C = (numberSeg[FC1.Run.SetTime / 60 / 10] & SEG_C && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_5D = (numberSeg[FC1.Run.SetTime / 60 / 10] & SEG_D && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_5E = (numberSeg[FC1.Run.SetTime / 60 / 10] & SEG_E && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_5F = (numberSeg[FC1.Run.SetTime / 60 / 10] & SEG_F && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_5G = (numberSeg[FC1.Run.SetTime / 60 / 10] & SEG_G && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_6A = (numberSeg[FC1.Run.SetTime / 60 % 10] & SEG_A && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_6B = (numberSeg[FC1.Run.SetTime / 60 % 10] & SEG_B && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_6C = (numberSeg[FC1.Run.SetTime / 60 % 10] & SEG_C && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_6D = (numberSeg[FC1.Run.SetTime / 60 % 10] & SEG_D && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_6E = (numberSeg[FC1.Run.SetTime / 60 % 10] & SEG_E && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_6F = (numberSeg[FC1.Run.SetTime / 60 % 10] & SEG_F && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//  DispBuff.Solo.TIME_6G = (numberSeg[FC1.Run.SetTime / 60 % 10] & SEG_G && FC1.Buff.Flag.solo.HourBlink)? 1:0;
//
//  DispBuff.Solo.TIME_7A = (numberSeg[FC1.Run.SetTime % 60 / 10] & SEG_A && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_7B = (numberSeg[FC1.Run.SetTime % 60 / 10] & SEG_B && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_7C = (numberSeg[FC1.Run.SetTime % 60 / 10] & SEG_C && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_7D = (numberSeg[FC1.Run.SetTime % 60 / 10] & SEG_D && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_7E = (numberSeg[FC1.Run.SetTime % 60 / 10] & SEG_E && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_7F = (numberSeg[FC1.Run.SetTime % 60 / 10] & SEG_F && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_7G = (numberSeg[FC1.Run.SetTime % 60 / 10] & SEG_G && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_8A = (numberSeg[FC1.Run.SetTime % 60 % 10] & SEG_A && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_8B = (numberSeg[FC1.Run.SetTime % 60 % 10] & SEG_B && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_8C = (numberSeg[FC1.Run.SetTime % 60 % 10] & SEG_C && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_8D = (numberSeg[FC1.Run.SetTime % 60 % 10] & SEG_D && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_8E = (numberSeg[FC1.Run.SetTime % 60 % 10] & SEG_E && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_8F = (numberSeg[FC1.Run.SetTime % 60 % 10] & SEG_F && FC1.Buff.Flag.solo.MinBlink)? 1:0;
//  DispBuff.Solo.TIME_8G = (numberSeg[FC1.Run.SetTime % 60 % 10] & SEG_G && FC1.Buff.Flag.solo.MinBlink)? 1:0;


}

void LCDDispIcon()
{
    DispBuff.Solo.AUTO_ICON = FC1.State.Sys.Solo.FanLvlAuto;
    DispBuff.Solo.LOW_ICON = FC1.State.Sys.Solo.FanLvlLow;
    DispBuff.Solo.MED_ICON = FC1.State.Sys.Solo.FanLvlMed;
    DispBuff.Solo.HIGH_ICON = FC1.State.Sys.Solo.FanLvlHigh;
    DispBuff.Solo.COOL_ICON = FC1.State.Sys.Solo.Cool;
    DispBuff.Solo.HOT_ICON = FC1.State.Sys.Solo.Hot;
    DispBuff.Solo.SLEEP_ICON = FC1.State.Sys.Solo.Sleep;
//  DispBuff.Solo.COLON_ICON = 1;
    DispBuff.Solo.FAN_ICON = 1;
    DispBuff.Solo.MODE_ICON = 1;
    DispBuff.Solo.TEMP_ICON1 = 1;
    DispBuff.Solo.TEMP_ICON2 = 1;
    DispBuff.Solo.SET_TEMP_ICON = 1;
    DispBuff.Solo.ROM_TEMP_ICON = 1;
    DispBuff.Solo.TWOLINE_ICON = 1;
    DispBuff.Solo.TIME2STOP_ICON = FC1.State.Sys.Solo.Time2Stop;
    DispBuff.Solo.TIME2START_ICON = FC1.State.Sys.Solo.Time2Start;
    DispBuff.Solo.TIME_ICON = FC1.State.Sys.Solo.Time2Stop || FC1.State.Sys.Solo.Time2Start;
}
//{
//    DispBuff.Solo.AUTO_ICON = 1;
//    DispBuff.Solo.LOW_ICON = 0;
//    DispBuff.Solo.MED_ICON = 1;
//    DispBuff.Solo.HIGH_ICON = 0;
//    DispBuff.Solo.COOL_ICON =  1;
//    DispBuff.Solo.HOT_ICON = 0;
//    DispBuff.Solo.SLEEP_ICON =1;
//    DispBuff.Solo.COLON_ICON = 0;
//    DispBuff.Solo.FAN_ICON = 1;
//    DispBuff.Solo.MODE_ICON = 0;
//    DispBuff.Solo.TEMP_ICON1 = 1;
//    DispBuff.Solo.TEMP_ICON2 = 0;
//    DispBuff.Solo.TWOLINE_ICON = 1;
//    DispBuff.Solo.TIME2STOP_ICON = FC1.State.Sys.Solo.Time2Stop;
//    DispBuff.Solo.TIME2START_ICON = FC1.State.Sys.Solo.Time2Start;
//    DispBuff.Solo.TIME_ICON = FC1.State.Sys.Solo.Time2Stop || FC1.State.Sys.Solo.Time2Start;
//}

uint08 cntLCD = 0;
void LCDShowAll()
{

    if (FC1.State.Sys.Solo.Started)
    {
        LCDDispIcon();
        LCDDispNum();
    }
    else
    {
        for (uint08 tmp = 0; tmp < 10; tmp++)
        {
            DispBuff.All[tmp] = 0;
        }
    }
   WriteAllData(0,DispBuff.All,10);
}


