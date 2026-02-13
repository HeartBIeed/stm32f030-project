#ifndef DMA_H_
#define DMA_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void DMA_init();
void dma_uart1_tx(uint8_t *data, uint16_t len);
void dma_uart1_rx(uint32_t len);


#endif /* DMA_H_ */
