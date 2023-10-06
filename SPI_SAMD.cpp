/*
 * SPI.cpp
 *
 * Created: 10/10/2021 15:41:08
 *  Author: GuavTek
 */ 

#include "SPI_SAMD.h"

void SPI_SAMD_C::Init(const spi_config_t config){
	//Setting the Software Reset bit to 1
	com->SPI.CTRLA.bit.SWRST = 1;
	while(com->SPI.CTRLA.bit.SWRST || com->SPI.SYNCBUSY.bit.SWRST);
	
	// Enable SERCOM clock
	PM->APBCMASK.reg |= 1 << (PM_APBCMASK_SERCOM0_Pos + config.sercomNum);
	
	// Select generic clock
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | ((GCLK_CLKCTRL_ID_SERCOM0_CORE_Val + config.sercomNum) << GCLK_CLKCTRL_ID_Pos);

	// Configure chip select pin
	struct port_config chipSel = {
		.direction = PORT_PIN_DIR_OUTPUT,
		.input_pull = PORT_PIN_PULL_NONE,
		.powersave = false
	};
	csPin = (uint8_t*) malloc(config.num_cs * sizeof(uint8_t));
	slaveCallbacks = (com_driver_c**) malloc(4*config.num_cs);	// Allocate memory space for function pointers
	for (uint8_t i = 0; i < config.num_cs; i++)	{
		port_pin_set_config(config.pin_cs[i], &chipSel);
		port_pin_set_output_level(config.pin_cs[i], true);
		csPin[i] = config.pin_cs[i];
	}
	
	// Select peripheral pin function
	pin_set_peripheral_function(config.pinmux_miso);
	pin_set_peripheral_function(config.pinmux_mosi);
	pin_set_peripheral_function(config.pinmux_sck);

	// Set master mode and pad configuration
	com->SPI.CTRLA.reg = SERCOM_SPI_CTRLA_MODE_SPI_MASTER | SERCOM_SPI_CTRLA_DOPO(config.dopoVal)
	| SERCOM_SPI_CTRLA_DIPO(config.dipoVal) | SERCOM_SPI_CTRLA_MODE(0x0);
	
	// Enable Rx
	while(com->SPI.SYNCBUSY.bit.CTRLB);
	com->SPI.CTRLB.reg = SERCOM_SPI_CTRLB_RXEN;
	
	// Set baud rate
	while(com->SPI.SYNCBUSY.bit.CTRLB);
	com->SPI.BAUD.reg = (F_CPU/(2 * config.speed)) - 1;
	
	//Enable SPI
	com->SPI.CTRLA.reg |= SERCOM_SPI_CTRLA_ENABLE;
	
	// Enable interrupt
	while(com->SPI.SYNCBUSY.reg & SERCOM_SPI_SYNCBUSY_ENABLE);
	com->SPI.INTENSET.reg = SERCOM_SPI_INTENSET_RXC;
	
	// Send dummy byte
	com->SPI.DATA.reg = 69;
	// Wait for transfer to complete
	while(com->SPI.INTFLAG.bit.RXC == 0);
	volatile uint8_t temp = com->SPI.DATA.reg;
}

uint8_t SPI_SAMD_C::Transfer(char* buff, uint8_t length, com_state_e state){
	if (currentState == Idle){
		currentState = state;
		msgLength = length;
		txIndex = 0;
		rxIndex = 0;
		msgBuff = buff;
		com->SPI.INTFLAG.reg = SERCOM_SPI_INTENSET_RXC | SERCOM_SPI_INTFLAG_DRE;
		com->SPI.INTENSET.reg = SERCOM_SPI_INTENSET_RXC | SERCOM_SPI_INTENSET_DRE;
		return 1;
	}
	return 0;
}

