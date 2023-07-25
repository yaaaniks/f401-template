#ifndef TIMER_H
#define TIMER_H

#include <stm32f4xx.h>

#define F_CPU 84000000U             // macros system core clock
#define F_CPU_MHZ   F_CPU/1000000   // macros F_CPU in MHz
#define TIM3_DELAY  0xFFF           

void SysTick_Init();
void timerInit();
void SysTick_Handler();
void TIM3_IRQHandler();
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

#endif // TIMER_H