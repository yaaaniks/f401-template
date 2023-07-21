#ifndef RCC_H
#define RCC_H

#include <stm32f401xc.h>

static inline void RCC_Init();
static inline void RCC_DeInit();
static inline void enablePeriphClock();

#endif // RCC_H