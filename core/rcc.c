#include "rcc.h"

static inline void RCC_Init() {
    RCC->CR |= RCC_CR_CSSON;
    RCC->CR |= (0x01<<RCC_CR_HSEON_Pos); // start HSE 
    while(!(RCC->CR & (1<<RCC_CR_HSERDY_Pos))); // wait for it
    RCC->CFGR |= (0x07<<RCC_PLLCFGR_PLLM_Pos) | (0x01<<RCC_PLLCFGR_PLLSRC_Pos);

    RCC->CR |= (1<<RCC_CR_PLLON_Pos); // start PLL
    while(!(RCC->CR & (1<<RCC_CR_PLLRDY_Pos))); // wait for it

    FLASH->ACR |= (0x02<<FLASH_ACR_LATENCY_Pos); // 2 cycles to wait flash

    RCC->CFGR |= (0x00<<RCC_CFGR_PPRE2_Pos) | (0x04<<RCC_CFGR_PPRE1_Pos) | (0x00<<RCC_CFGR_HPRE_Pos); // set dividers

    RCC->CFGR |= (0x02<<RCC_CFGR_SW_Pos); // switch to PLL 
    while((RCC->CFGR & RCC_CFGR_SWS_Msk) != (0x02<<RCC_CFGR_SWS_Pos)); // wait for it

    RCC->CR &= ~(1<<RCC_CR_HSION_Pos); // disable HSI

}

static inline void RCC_DeInit() {
    RCC->CR = RCC_CR_HSION;

}

static inline void enablePeriphClock() {
    RCC->AHB1ENR = RCC_AHB1ENR_CRCEN;
} 