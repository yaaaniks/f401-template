#ifndef TIMER_H
#define TIMER_H

#include <stm32f4xx.h>

extern uint32_t timeStamp;

void timerInit();
void TIM3_IRQHandler();

#endif // TIMER_H