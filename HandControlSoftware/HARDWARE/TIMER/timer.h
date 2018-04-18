#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define MAX_ARR 8999  //PWM²¨ÆµÂÊ 72000000/9000=8kHz

void TIM1_Init(void);
void TIM2_Init(void);
void TIM4_Init(void);
void TIM3_Init(u16 arr, u16 psc);

#endif
