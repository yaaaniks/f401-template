#include "timer.h"
#include "rcc.h"
#include "gpio.h"

void main(void)
{
    RCC_Init();
    enablePeriphClock();
    SysTick_Init();
    GPIO_Init();
    while(1) {
        delay_ms(500);
        GPIOC->BSRRL |= GPIO_BSRR_BS_13;
        delay_ms(500);
        GPIOC->BSRRH |= GPIO_BSRR_BS_13;
    }
}