#include "dma.h"
void DMA_init()
	{
	RCC ->AHBENR |= RCC_AHBENR_DMA1EN;
	}

uint32_t rx_buffer[64];

// TX - Channel 2 / 4

void dma_uart1_tx(uint8_t *data, uint16_t len)
{

CLEAR_BIT(DMA1_Channel2->CCR, 1<<0); // off channel 

DMA1_Channel2->CMAR = (uint32_t) data; // source data from memory
DMA1_Channel2->CPAR = (uint32_t)&USART1->TDR; // adress perif
DMA1_Channel2->CNDTR = len; // len bytes

SET_BIT(DMA1_Channel2->CCR, 1<<4); // Mem to perif set
SET_BIT(DMA1_Channel2->CCR, 1<<7); // memory increment on
SET_BIT(DMA1_Channel2->CCR, 1<<1); //  transfer intrrupt on
SET_BIT(DMA1_Channel2->CCR, 2<<12); //  proirity level 0b10 - high


SET_BIT(DMA1_Channel2->CCR, 1<<0); // on channel 

USART1->CR3 |= USART_CR3_DMAT;	// tx dma en

}

// RX - Channel 3 / 5

void dma_uart1_rx(uint32_t len)
{
CLEAR_BIT(DMA1_Channel3->CCR, 1<<0); // off channel 

DMA1_Channel3->CPAR = (uint32_t)&USART1->RDR; // adress perif
DMA1_Channel3->CMAR = (uint32_t)rx_buffer; //  data on memory
DMA1_Channel3->CNDTR = len; // len bytes

CLEAR_BIT(DMA1_Channel3->CCR, 1<<4); // Perif to mem set
SET_BIT(DMA1_Channel3->CCR, 1<<7); // memory increment on
SET_BIT(DMA1_Channel3->CCR, 1<<1); //  transfer intrrupt on
SET_BIT(DMA1_Channel3->CCR, 2<<12); //  proirity level 0b10 - high

SET_BIT(DMA1_Channel3->CCR, 1<<0); // on channel 

USART1->CR3 |= USART_CR3_DMAR;	// rx dma en
}


