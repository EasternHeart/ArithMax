#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include "am.h"

extern u8 ShiftState;

extern const unsigned char gImage_mainlogo[384];
extern const unsigned char Font_Ascii_5X7E_Menu[];

void Setup_main();
void About_main();
void Mode_main();

/* Exported macro ------------------------------------------------------------*/
#define ABS(x)         (x < 0) ? (-x) : x
/* Exported functions ------------------------------------------------------- */
//void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

#endif
