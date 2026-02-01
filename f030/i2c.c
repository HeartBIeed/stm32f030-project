#include "i2c.h"



void I2C_init( )
{

// PB6 - SCL
// PB7 - SDA

//	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // GPIOB
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // APB1 I2C1

//MODER 0b10 - 0x02 alt func - 2 bit
	GPIOB->MODER &= ~( 0x3 << (PB6 *2)); // PB6  clear
	GPIOB->MODER |= ( 0x2 << (PB6 *2)); // PB6 set TX

	GPIOB->MODER &= ~( 0x3 << (PB7 *2)); // PB7  clear
	GPIOB->MODER |= ( 0x2 << (PB7 *2)); // PB7 set RX

//OTYPER 1- Open Drain  - 1 bit 
	GPIOB->OTYPER |= ((1<<PB6 )|(1<<PB7 )); 

//OSPEEDR 10 high 2 - bit
	GPIOB->OSPEEDR |= ((0x2<<(PB6 *2))|(0x2<<(PB7 *2))); 

	GPIOB->AFR[0] &= ~((0xF<<(PB6 *4))|(0xF<<(PB7 *4))); // clear
	GPIOB->AFR[0] |= ((0x1<<(PB6 *4))|(0x1<<(PB7 *4)));  //0b001/ 4 bit 
//AFR 0b001 I2C enable mode


	I2C1->CR1 = 0;
	I2C1->CR2 = 0;

	I2C1->CR1 |= (1<<2); // RX interrupt enable
	I2C1->CR1 |= (1<<1); // TX interrupt enable
	I2C1->CR1 |= (1<<0); // PE
	
	I2C1->TIMINGR = (0x1<<28)|(0x4<<20)|(0x2<<16)|(0xF<<8)|(0x13<<0);
// PRESC | SCLDEL | SDADEL | SCLH | SCLL 
//table 75 from RM
//setup for fcpu 8MHz / i2c clk 100 kHz


}

void I2C_start(int addr,int nbytes)
	{	
		I2C1->CR2 = 0; 
		
		I2C1->CR2 |= (nbytes<< 16); //nbytes
		I2C1->CR2 |= (1 << 25); //autoend
		I2C1->CR2 |= (addr << 1); // set slave address
		I2C1->CR2 |= (1 << 13); //start 

	}


void I2C_stop( )
	{
		I2C1->CR2 |= (1<<14); // stop 

	}

int I2C_send_byte(char data,int addr)
	{
int nbytes = 1;

	I2C_start(addr,nbytes);

			while (!(I2C1->ISR & I2C_ISR_TXIS)); //txis 1 - txdr empty

		I2C1->TXDR = data; // send 

			while (!(I2C1->ISR & I2C_ISR_STOPF)); //stopf 1 - slave send stop

		I2C1->ICR |= (1<<5); //clear stopf 

			return 1;
	}

/*
int I2C_read_byte( )
{



	return 1;
}
*/