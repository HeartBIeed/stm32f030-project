

#include "stm32f030x6.h"

int main( void )
{
 

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 


	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 
//						 PA output(01)

	GPIOA->MODER |= ( 0x01 << (5*2)); // 5 / 01
	GPIOA->MODER |= ( 0x01 << (6*2)); // 6
	GPIOA->MODER |= ( 0x01 << (7*2)); // 7
	GPIOA->MODER |= ( 0x01 << (15*2)); // 15 

//						 PB input 00

	GPIOB->MODER &= ~( 0xFF << (1*2));// 1 
	GPIOB->MODER |= ( 0x01 << (3*2)); // 3
	GPIOB->PUPDR |= ( 0x01 << (1*2)); //1 / up 01

//  output 01 input 00



 while( 1 )
	{


	if ((GPIOB->IDR & (1<<1))==0)
	{
	GPIOA->ODR |= (1 << 15);
	GPIOB->ODR &= ~(1 << 3);
	}
	else 
	{
	GPIOA->ODR &= ~(1 << 15);
	GPIOB->ODR |= (1 << 3);
	}

		    

}
}
