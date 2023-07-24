#include "timer.h"

#define TIM3_DELAY  0xFFF
#define F_CPU       84000000
#define F_CPU_MHZ   F_CPU/1000000

volatile uint32_t ticks;

// TODO: configure system clock and RTC timer

void SysTick_Init() {
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/10000); // set tick to every 1ms	
}

void timerInit() {
    TIM3->SR = 0;
    TIM3->ARR = TIM3_DELAY;
    TIM3->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM3_IRQn);
    NVIC_SetPriority(TIM3_IRQn, 0);
}

void SysTick_Handler(void) {
    ticks++;
}

void delay_ms(int ms) {
    uint32_t started = ticks;
    while((ticks-started)<=ms); // rollover-safe (within limits)
}

void TIM3_IRQHandler() {

}