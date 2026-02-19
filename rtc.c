#include "rtc.h"

void RTC_init()
	{

	RCC->CSR |= (1<<0); // LSI on
	while(!(RCC->CSR & (1<<1))); // wait si ready
	RCC->APB1ENR |= (1<<28); // pwr en

	//Power control registers
	PWR->CR |=(1<<8); // DBP: Disable RTC domain write protection.


	//RTC domain control register (RCC_BDCR)
	RCC->BDCR |= (2<<8); // LSI oscillator
	//00: No clock
	//01: LSE oscillator clock used as RTC clock
	//10: LSI oscillator clock used as RTC clock
	//11: HSE oscillator clock divided by 32 used as RTC clock

	RCC->BDCR |= (1<<15); // RTC clock enable

	RTC->WPR = 0xCA; //Write access for RTC registers
	RTC->WPR = 0x53;  
	RTC->ISR |= RTC_ISR_INIT; // enable init phase 
	while(!(RTC->ISR & (1<<6))); // wait INITF ready
	//Bit 6 INITF: Initialization flag

	//Bits 22:16 PREDIV_A[6:0]: Asynchronous prescaler factor
	//Bits 14:0 PREDIV_S[14:0]: Synchronous prescaler factor
	     RTC->PRER |= (uint32_t)(99<<16); //Asynchronous
	     RTC->PRER |= (uint32_t)399;

	RTC->ISR &= ~RTC_ISR_INIT; // Disable init phase 
	RTC->WPR = 0xFE; 
	RTC->WPR = 0x64; // Disable write access for RTC registers 

	}


void RTC_set_time(uint8_t h,uint8_t m)
	{

	RTC->WPR = 0xCA; 
	RTC->WPR = 0x53;  
	RTC->ISR |= RTC_ISR_INIT; 
	while(!(RTC->ISR & (1<<6))); // wait INITF ready

	uint32_t tr =((h / 10) << 20) |
				((h % 10) << 16) |
				((m / 10) << 12) |
				((m % 10) << 8);


	RTC->TR |= tr;


	RTC->ISR &= ~RTC_ISR_INIT; 
	RTC->WPR = 0xFE; 
	RTC->WPR = 0x64; 

	}

void RTC_get_time(uint8_t *hour,uint8_t *min)
{

	uint32_t tr = RTC->TR;

	*hour = ((tr>>20)&0x3)*10 + ((tr>>16)&0xF); // 0x3 read 2 bits
	*min =  ((tr>>12)&0x7)*10 + ((tr>>8)&0xF); // 0x7 read 3 bits
// 0xF read 4 bits

}