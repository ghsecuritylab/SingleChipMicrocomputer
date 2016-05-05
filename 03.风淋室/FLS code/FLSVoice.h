



#ifndef FLSVOICE_H
#define FLSVOICE_H


typedef union 
{
   uint All[2];
   struct 
   {
      uint Enable       :1;
      uint PinRST       :1;
      uint PinDATA      :1;
      uint Step         :5;
      uint Cmd          :8;
      uint Timer        :8;
   }Solo;
}WTV040_CONTROL_DEF;


extern  WTV040_CONTROL_DEF WTV1;


void FlsVoice(WTV040_CONTROL_DEF *voice, FLS_DEF *Fls);

#endif 
