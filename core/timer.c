#include "timer.h"

#define TIM3_DELAY 0xFFF

uint32_t timeStamp;

void timerInit() {
    TIM3->SR = 0;
    TIM3->ARR = TIM3_DELAY;
    TIM3->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM3_IRQn);
    NVIC_SetPriority(TIM3_IRQn, 0);
}

void TIM3_IRQHandler() {

}