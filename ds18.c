#include "ds18.h"


void ds18_init()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 

	GPIOA->OTYPER |= 0x01; // PA0 open drain
	GPIOA->OSPEEDR |= (0x10); // PA0 high speed 
//	GPIOA->PUPDR |= (0x01); // PA0 up  

}


uint8_t ds18_search()
{

	uint8_t dt_result;

	PA0_OUTPUT; // пин на выход
<<<<<<< HEAD
	CLEAR_BIT(GPIOA->ODR, 1<<0); // опускаем в 0
		_delay_us(480);
	SET_BIT(GPIOA->ODR , 1<<0); // поднимаем в 1
		_delay_us(35); 
=======
	CLEAR_BIT(GPIOA->ODR, 0); // опускаем в 0
		_delay_us(500);
>>>>>>> 199da966384f9ea92f8a3e410588d959c2f46c6a

	PA0_INPUT;  // пин на вход
	
	dt_result = !(READ_BIT(GPIOA->IDR , 1<<0)); // если пин в нуле то 1 
		_delay_us(240);


	return dt_result;
}



void ds18_send(uint8_t data)
{
	PA0_OUTPUT;

	for(uint8_t i=0; i<8; i++)
	{
	CLEAR_BIT(GPIOA->ODR, 1<<0); // down
				_delay_us(1);

		if (data & 0x01)
			{
				_delay_us(15);

			SET_BIT(GPIOA->ODR , 1<<0);//подняли линию - отправился 1 
				_delay_us(45);

			} 

		else{
			_delay_us(45);	// линию не подняли  - отправился 0 
			SET_BIT(GPIOA->ODR , 1<<0);//подняли линию перед след слотом-  1 
			}

	data >>=1; // сдвинули под следующий бит
	}

}


uint8_t ds18_read()
{

uint8_t data =0;
uint8_t bit;



  for(uint8_t i=0; i<8; i++)
	{
		PA0_OUTPUT; // master pulse
		CLEAR_BIT(GPIOA->ODR, 1<<0); //down
			_delay_us(1);
		SET_BIT(GPIOA->ODR , 1<<0); //up

		PA0_INPUT; // read slave
			_delay_us(15);
		
		bit = READ_BIT(GPIOA->IDR , 1<<0);
		data |= (bit<<i); // запись полученного бита в байт
			_delay_us(45);

<<<<<<< HEAD
		SET_BIT(GPIOA->ODR , 1<<0); //конец слота - up
=======
//		SET_BIT(GPIOA->ODR , 0); //конец слота - up
>>>>>>> 199da966384f9ea92f8a3e410588d959c2f46c6a

	}	 



  return data;
	
}

int16_t ds18_get()
{

int16_t temp;
uint8_t LS_bit;
uint8_t MS_bit;

	if (ds18_search())
	{
		ds18_send(NOID);
		ds18_send(CONVERT);
			_delay_ms(750); 

		ds18_search();
		ds18_send(NOID);
		ds18_send(READ_DATA);

		LS_bit = ds18_read();
		MS_bit = ds18_read();
		temp = (MS_bit <<8) | LS_bit;
		
		usart1_send_byte((char)LS_bit);
		usart1_send_byte((char)MS_bit);
		usart1_send_byte('\n');
	}
	else
	{
			temp = 0;
		

	}

return temp;
}

