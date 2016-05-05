
#ifndef PAR_SAVE_H
#define PAR_SAVE_H


//256 128 512 
#define PARSAVE_SHIFT_LEN   512
#define PARSAVE_FLASH_FIRST_PAGE_ADDRESS 0x08040000
#define PARSAVE_FLASH_LAST_PAGE_ADDRESS   0x08080000


extern FlashSave_def ParSave;
uint08 ParSaveInit();
void ParSaveTest(uint16 Times);

uint08 CrcCheck(void *P2Data, uint16 len);
void YYJ_ParSave();

#endif



