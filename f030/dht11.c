#include "dht11.h"

void dht_request() //start down-up
	{
		GPIOA->MODER |= ( 0x01 << (4*2)); // out 4

		CLEAR_BIT(GPIOA->ODR,4);
		_delay_ms(20);

		SET_BIT(GPIOA->ODR,4);
		_delay_us(30);

	}

void dht_response(void) //ответ - ждем up-down-up
	{

		GPIOA->MODER &= ~( 3 << (4*2)); // inp 4
		while (READ_BIT(GPIOA->IDR, 4)); // ожидание 1
		while ((READ_BIT(GPIOA->IDR,4))==0); // ожидание 0
		while (READ_BIT(GPIOA->IDR,4));

	}

uint8_t dht_receive_data() //получаем байт
	{
	
	uint8_t c =0;

	for (int i = 0; i < 8; i++)
		{

		while ((READ_BIT(GPIOA->IDR,4))==0); // ждем появления 1. пока 0 - не выходим из цикла
			
		_delay_us(40);			

		if (READ_BIT(GPIOA->IDR, 4)) // если пин в 1 более 30 мс
			{
				c=(c<<1)|(0x01); // то сдвиг влево и пишем в конец 1
			}
		else 
			{
				c=(c<<1); // то сдвиг влево. в конце 0
			}

		}

	return c;
	}

void dht_write_data(char* data)
	{
		uint8_t I_RH,D_RH,I_TEMP,D_TEMP,C_SUMM_GET,CSUMM;
		uint8_t Temp,Humi;

		dht_request();
		dht_response();
		
		I_RH = dht_receive_data(); // целая часть
		D_RH = dht_receive_data(); // дробная
		I_TEMP = dht_receive_data();
		D_TEMP = dht_receive_data();

		C_SUMM_GET = dht_receive_data();
		CSUMM = ((I_RH + D_RH + I_TEMP + D_TEMP) & 0xFF);

		if (C_SUMM_GET == CSUMM) sprintf(data,"%d %d", I_RH,I_TEMP);
		else sprintf(data,"ERR");
	}



/*
int main(void)
{

	char data[16];
	dht_write_data(data);
	
}

//	sprintf(data, "RH:%d.%d % T:%d.%dC", I_RH, D_RH, I_TEMP, D_TEMP);

/*
	dht_request();
	dht_response();
	I_RH = dht_receive_data(); // целая часть
	D_RH = dht_receive_data(); // дробная*//*
	I_TEMP = dht_receive_data();
	D_TEMP = dht_receive_data();


*/

