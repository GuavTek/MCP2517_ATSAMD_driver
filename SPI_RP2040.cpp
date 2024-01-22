/*
 * SPI_RP2040.cpp
 *
 * Created: 25/09/2023
 *  Author: GuavTek
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "SPI_RP2040.h"

void SPI_RP2040_C::Init(const spi_config_t config){
	// Set baud rate
	spi_init(com, config.speed);

	// Set format
	spi_set_format(com, 8, config.polarity, config.phase, config.order);
	
	// Set pin functions
	gpio_set_function(config.pin_tx, GPIO_FUNC_SPI);
	gpio_set_function(config.pin_rx, GPIO_FUNC_SPI);
	gpio_set_function(config.pin_ck, GPIO_FUNC_SPI);
	
	csPin = (uint8_t*) malloc(config.num_cs * sizeof(uint8_t));
	slaveCallbacks = (com_driver_c**) malloc(4*config.num_cs);	// Allocate memory space for function pointers
	for (uint8_t i = 0; i < config.num_cs; i++){
		csPin[i] = config.pin_cs[i];
		gpio_init(config.pin_cs[i]);
		gpio_set_dir(config.pin_cs[i], GPIO_OUT);
		gpio_put(config.pin_cs[i], 1);
	}

	// Configure DMA channels
    dmaTx = dma_claim_unused_channel(true);
    dmaRx = dma_claim_unused_channel(true);

    dma_channel_config c = dma_channel_get_default_config(dmaTx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_dreq(&c, spi_get_dreq(com, true));
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, false);
    dma_channel_set_config(dmaTx, &c, false);
	dma_channel_set_write_addr(dmaTx, &spi_get_hw(com)->dr, false);

    c = dma_channel_get_default_config(dmaRx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_dreq(&c, spi_get_dreq(com, false));
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, true);
    dma_channel_set_config(dmaRx, &c, false);
    dma_channel_set_read_addr(dmaRx, &spi_get_hw(com)->dr, false);

	// Enable irq
	dmaNum = config.dma_irq_num;
	dma_irqn_set_channel_mask_enabled(config.dma_irq_num, (1 << dmaTx) | (1 << dmaRx), true);
	
}

uint8_t SPI_RP2040_C::Transfer(char* buff, uint8_t length, com_state_e state){
	if (currentState == Idle){
		uint32_t chanMask = 0;
		currentState = state;
		if ((state == Rx) || (state == RxTx)){
			dma_channel_set_trans_count(dmaRx, length, false);
			dma_channel_set_write_addr(dmaRx, buff, false);
			chanMask |= 1 << dmaRx;
		}
		if ((state == Tx) || (state == RxTx)){
			dma_channel_set_trans_count(dmaTx, length, false);
			dma_channel_set_read_addr(dmaTx, buff, false);
			chanMask |= 1 << dmaTx;
		}
		dma_start_channel_mask(chanMask);
		return 1;
	}
	return 0;
}

