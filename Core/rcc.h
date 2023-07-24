#ifndef RCC_H
#define RCC_H

#include <stm32f4xx.h>

#define HSE_ON  

void RCC_Init(void);
void RCC_DeInit(void);
void enablePeriphClock(void);

#endif // RCC_H