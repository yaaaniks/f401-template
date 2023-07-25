#include "timer.h"

__IO uint32_t SysTick_CNT = 0;

// TODO: configure RTC timer

void SysTick_Init(void) {
    SystemCoreClockUpdate();
    // SysTick->LOAD &= ~(SysTick_LOAD_RELOAD_Msk);
    // SysTick->LOAD |= F_CPU/1000-1; 
    // SysTick->VAL &= ~SysTick_VAL_CURRENT_Msk;
    // SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk |
    //                   SysTick_CTRL_TICKINT_Msk   |
    //                   SysTick_CTRL_ENABLE_Msk);                          
    SysTick_Config(F_CPU/1000-1); // set tick to every 1ms	
}

void timerInit() {
    TIM3->SR = 0;
    TIM3->ARR = TIM3_DELAY;
    TIM3->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM3_IRQn);
    NVIC_SetPriority(TIM3_IRQn, 0);
}

void SysTick_Handler(void) {
    if (SysTick_CNT > 0) SysTick_CNT--;
}

void delay_ms(uint32_t ms) {
    SysTick_CNT = ms;
    while(SysTick_CNT); // rollover-safe (within limits)
}

void delay_us(uint32_t us) {

}

void TIM3_IRQHandler() {

}