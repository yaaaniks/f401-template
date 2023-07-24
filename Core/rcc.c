#include "rcc.h"

void RCC_Init(void) {
    #ifdef HSE_ON
	/*************************FLASH Configuration*************************/
	FLASH->ACR |= (FLASH_ACR_LATENCY_2WS 			// 3 cycles for 85 MHz
			   | FLASH_ACR_PRFTEN 
			   | FLASH_ACR_ICEN 
			   | FLASH_ACR_DCEN);

	/*************************PLL Configuration*************************/
	uint32_t pllConfig = RCC->PLLCFGR;
    // RCC->CR |= RCC_CR_CSSON;						// Enable CSS 
    RCC->CR |= (RCC_CR_HSEON); 		        		// Enable HSE
	while((RCC->CR & RCC_CR_HSERDY) == 0);      	// Ready to start HSE

	pllConfig |= RCC_PLLCFGR_PLLSRC_HSE; 			// Set HSE as PLL source
	RCC->CR &= ~(RCC_CR_PLLON); 					// Disable PLL before changes

	pllConfig &= ~(RCC_PLLCFGR_PLLM); 				// Clear all PLLM bits
	pllConfig |= (RCC_PLLCFGR_PLLM_0 
		| RCC_PLLCFGR_PLLM_3 
		| RCC_PLLCFGR_PLLM_4); 						// Divided by 25

	pllConfig &= ~(RCC_PLLCFGR_PLLN); 				// Clear all PLLN bits with mask
	pllConfig |= RCC_PLLCFGR_PLLN_4; 				// Multiplied by 336
	pllConfig |= RCC_PLLCFGR_PLLN_6; 	
	pllConfig |= RCC_PLLCFGR_PLLN_8; 

	pllConfig &= ~(RCC_PLLCFGR_PLLP); 				// Clear main PLL division PLLP
	pllConfig |= RCC_PLLCFGR_PLLP_0; 				// Divided by 4

	pllConfig &= ~(RCC_PLLCFGR_PLLQ);				// Clear PLLP values
	pllConfig |= RCC_PLLCFGR_PLLQ_2 ;				// Divided by 4

	RCC->PLLCFGR = pllConfig;						// Write in pllConfig

	/*************************Division Configuration*************************/
	uint32_t divConfig = RCC->CFGR;
	
	divConfig &= ~(RCC_CFGR_HPRE); 					// AHB Prescaler = 1
	divConfig &= ~(RCC_CFGR_PPRE1_DIV16); 	
	divConfig |=RCC_CFGR_PPRE1_2;					// APB1 Prescaler = 2
	divConfig &= ~(RCC_CFGR_PPRE2_DIV16);
	divConfig |= RCC_CFGR_PPRE2_DIV1;				// APB2 Prescaler = 1

	RCC->CFGR = divConfig;							// Write in divConfig
	
	/*************************PLL Enable*************************/
	RCC->CR |= RCC_CR_PLLON; 						// Enalbe PLL
	while(!(RCC->CR & RCC_CR_PLLRDY)); 				// Wait for PLL is ready

	/*************************PLL Switching*************************/
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL; 					// PLL selected as system clock
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));			// Wait for PLL is used
	PWR->CR = PWR_CR_VOS_1;
    RCC->CR &= ~RCC_CR_HSION;               		// Disable HSI
    #else 
    SystemInit();
    #endif
    SystemCoreClockUpdate();						// Update core clock 
}

// TODO: Configure deinit of RCC
void RCC_DeInit(void) {
    RCC->CR = RCC_CR_HSION;
}

void enablePeriphClock(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
} 