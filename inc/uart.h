#ifndef UART_H_
#define UART_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void UART_init(uint16_t speed);
void usart1_send_byte(char tx_data); // отправка байта
void usart1_send_str(char *str); // отправка строки - принимаем строковый массив
void USART1_IRQHandler(); // обработчик прерывания
void echo();

extern volatile uint8_t data_buffer[32]; //буффер uart
extern volatile uint8_t index_buffer;
extern volatile uint8_t usart1_flag;

#endif /* UART_H_ */
