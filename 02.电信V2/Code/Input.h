
#ifndef INPUT_H
#define INPUT_H



uint16  InputGet(void);
void InputScan(uint16 Key, DianXin_All_Def *pData);
void InputDeal(DianXin_All_Def *pData);
void InputAddr(DianXin_All_Def *pData);

#endif
