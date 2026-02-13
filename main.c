#include "main.h"

void GPIO()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 

	GPIOA->MODER |= ( 0x01 << (5*2)); // 5 pin/ 01
// PA output 0x10

	GPIOB->MODER &= ~( 3 << (1*2));// 1 pin
	GPIOB->PUPDR |= ( 1 << (1*2)); //1 pin / up 01
// PB input 0x00

	GPIOB->MODER |= ( 0x01 << (6*2)); // 5 pin/ 01
	GPIOB->MODER |= ( 0x01 << (7*2)); // 5 pin/ 01

}


int main(void)
{

	SystemClock_HSI_8MHz();
	SysTick_init();

	I2C_init();
	UART_init(9600);
	DMA_init();
	GPIO();

	GPIOA->ODR |= (1 << 5); // PA5 en relay
	usart1_send_str("UART EN");

//int16_t temp_ds = 0;
//char data_ds[32];
uint8_t string[] = "dma string \n\r";

 while( 1 )
	{

	dma_uart1_tx(string, strlen((char*)string));
	_delay_ms(500);

	AHT_to_uart();
	_delay_ms(500);

	echo();

	}
}

