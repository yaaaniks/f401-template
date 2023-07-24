#ifndef TIMER_H
#define TIMER_H

#include <stm32f4xx.h>

extern uint32_t timeStamp;

void SysTick_Init();
void timerInit();
void SysTick_Handler();
void TIM3_IRQHandler();
void delay_ms(int ms);

#endif // TIMER_H