#include "timer.h"
#include "rcc.h"
#include "gpio.h"

void main(void)
{
    RCC_Init();
    GPIO_Init();
    SysTick_Init();
    enablePeriphClock();
    GPIOC->BSRRL |= GPIO_BSRR_BS_13; // Toggle pin 13
    while(1) {
    }
}