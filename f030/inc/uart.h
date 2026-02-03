#ifndef UART_H_
#define UART_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void UART_init(uint16_t speed);
void usart1_send_byte(uint8_t tx_data);
uint8_t usart1_recieve_byte();
void usart1_rxen_flag();
void usart1_send_str(char *str);
void usart1_echo();

extern volatile uint8_t uart1_flag;


#endif /* UART_H_ */
