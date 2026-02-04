#include "i2c.h"

uint32_t timeout;

void I2C_init( )
{

// PB6 - SCL
// PB7 - SDA

	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // GPIOB
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // APB1 I2C1

//MODER 0b10 - 0x02 alt func - 2 bit
	GPIOB->MODER &= ~( 0x3 << (PB6 *2)); // PB6  clear
	GPIOB->MODER |= ( 0x2 << (PB6 *2)); // PB6 set TX

	GPIOB->MODER &= ~( 0x3 << (PB7 *2)); // PB7  clear
	GPIOB->MODER |= ( 0x2 << (PB7 *2)); // PB7 set RX

//OTYPER 1- Open Drain  - 1 bit 
	GPIOB->OTYPER |= ((1<<PB6 )|(1<<PB7 )); 

//pullup	
//	GPIOB->PUPDR  &= ~((0x3 << (PB6*2)) | (0x3 << (PB7*2)));// no 

//OSPEEDR 10 high 2 - bit
	GPIOB->OSPEEDR |= ((0x2<<(PB6 *2))|(0x2<<(PB7 *2))); 

	GPIOB->AFR[0] &= ~((0xF<<(PB6 *4))|(0xF<<(PB7 *4))); // clear
	GPIOB->AFR[0] |= ((0x1<<(PB6 *4))|(0x1<<(PB7 *4)));  //0b001/ 4 bit 
//AFR 0b001 I2C enable mode


	I2C1->CR1 = 0;
	I2C1->CR2 = 0;

//	I2C1->CR1 |= (1<<2); // RX interrupt enable
//	I2C1->CR1 |= (1<<1); // TX interrupt enable
	
	I2C1->TIMINGR = (0x1<<28)|(0x4<<20)|(0x2<<16)|(0x0F<<8)|(0x13<<0);
// PRESC | SCLDEL | SDADEL | SCLH | SCLL 
//table 75 from RM
//setup for fcpu 8MHz / i2c clk 100 kHz

	I2C1->CR1 |= (1<<0); // PE


}


void I2C_write_byte(int addr,uint8_t* data,int nbytes)
	{

		I2C1->CR2 = 0; 
		
		I2C1->CR2 |= (nbytes<< 16); //nbytes
		I2C1->CR2 |= (1 << 25); //autoend
		I2C1->CR2 |= (addr << 1); // set slave address
		I2C1->CR2 |= (1 << 13); //start 

		while (!(I2C1->ISR & I2C_ISR_TXIS)); //txis 1 - txdr empty

		for (int i = 0; i < nbytes; ++i)
			{
				while (!(I2C1->ISR & I2C_ISR_TXIS)); //wait empty tx buffer
				I2C1->TXDR = data[i];// send 

			}

while (!(I2C1->ISR & I2C_ISR_STOPF)); //wait stop
I2C1->ICR = I2C_ICR_STOPCF; //clear 

	}

void I2C_read_byte(int addr,uint8_t* data,int len)
	{

		I2C1->CR2 = 0; 
		
		I2C1->CR2 |= (1 << 10); // 1 read
		I2C1->CR2 |= (len<< 16); //len
		I2C1->CR2 |= (1 << 25); //autoend
		I2C1->CR2 |= (addr << 1); // set slave address
		I2C1->CR2 |= (1 << 13); //start 


		for (int i = 0; i < len; ++i)
			{				
				while (!(I2C1->ISR & I2C_ISR_RXNE)); //wait transmit
				data[i] = I2C1->RXDR; // read 
			}
while (!(I2C1->ISR & I2C_ISR_STOPF)); //wait stop
I2C1->ICR = I2C_ICR_STOPCF; //clear 

	}






int I2C_check_address(int addr)
{

//clear errors
I2C1->ICR = (1<<4)|(1<<5)|(1<<8)|(1<<9);

		I2C1->CR2 = 0; 
		
		I2C1->CR2 |= (0 << 16); //nbytes
		I2C1->CR2 |= (1 << 25); //autoend
		I2C1->CR2 |= (addr << 1); // set slave address
		I2C1->CR2 |= (1 << 13); //start 

timeout = TIMEOUT;
while (!(I2C1->ISR & (I2C_ISR_NACKF | I2C_ISR_STOPF | I2C_ISR_TC))) //wait NACK STOPF TC
	{
		if (--timeout == 0) return 0; //none ack
	}

if (I2C1->ISR & I2C_ISR_NACKF) // if nack
	{
	        I2C1->ICR = I2C_ICR_NACKCF | I2C_ICR_STOPCF; //clear flags
	        return 0; // no device

	}


 timeout = TIMEOUT;
while (!(I2C1->ISR & I2C_ISR_STOPF )) // wait STOPF 
	{
		if (--timeout == 0) break;
	}

I2C1->ICR = I2C_ICR_STOPCF; //clear stopf
return 1; 

}


void I2C_scan()
	{
	int addr;

	for (addr = 0x08; addr < 0x77; addr++)
		{
			if (I2C_check_address(addr)) usart1_send_str("GET \n\r");

		}

	}