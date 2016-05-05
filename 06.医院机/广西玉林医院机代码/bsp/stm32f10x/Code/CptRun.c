//
//#include "includes.h"
//#include "../HW/CptRun.h"
//#define CPT_KEY_IN TotalDi.Solo.MiscDi.Bits.CPT_Key
//
//CptCtrl_Def CptCtrl;
//#define CptRun_PIN			     GPIOG,GPIO_Pin_6
//#define CptRunOFF			    GPIO_SetBits(CptRun_PIN)
//#define CptRunON				GPIO_ResetBits(CptRun_PIN)
//
//
////this function should run every 5ms
//void CptRun()
//{
//    if(CptCtrl.Solo.Step==0)
//    {
//        CptRunOFF;
//        if(CPT_KEY_IN)
//        {
//            CptCtrl.Solo.Cnt++;
//            if(CptCtrl.Solo.Cnt>400)
//            {
//                CptCtrl.Solo.Cnt=0;
//                CptCtrl.Solo.Step++;
//                //¸´Î»RS232
//                RS232_Disable();
//                //GPIO_SetBits(GPIOG,GPIO_Pin_6);
//            }
//        }
//        else
//        {
//                CptCtrl.Solo.Cnt=0;
//        }
//    }
//    else if(CptCtrl.Solo.Step==1)
//    {
//        CptRunON;
//        if(!CPT_KEY_IN)
//        {
//            CptCtrl.Solo.Cnt++;
//            if(CptCtrl.Solo.Cnt>10)
//            {
//                CptCtrl.Solo.Step=0;
//                //¸´Î»RS232
//                RS232_Ensable();
//                //GPIO_ResetBits(GPIOG,GPIO_Pin_6);
//            }
//        }
//        else
//        {
//                CptCtrl.Solo.Cnt=0;
//        }
//    }
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
