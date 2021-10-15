/*
 * SPI.h
 *
 * Created: 01/07/2021 17:50:40
 *  Author: GuavTek
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <sam.h>
#include "conf_board.h"
#include <port.h>
#include <interrupt.h>

struct spi_config_t {
	uint8_t sercomNum;
	uint8_t dipoVal;
	uint8_t dopoVal;
	uint64_t speed;
	uint8_t pin_cs;
	uint32_t pinmux_mosi;
	uint32_t pinmux_miso;
	uint32_t pinmux_sck;
};

class SPI_C
{
	public:
		Sercom* const com;
		inline void Select_Slave(const bool state) { port_pin_set_output_level(ssPin, !state); }
		inline uint8_t Get_Status(){ return currentState; }
		uint8_t Read_Buffer(char* buff);
		uint8_t Send(char* buff, uint8_t length);
		uint8_t Send(uint8_t length);
		void Transfer_Blocking(char* buff, uint8_t length);
		uint8_t Receive(uint8_t length);
		void Init(const spi_config_t config);
		inline void Handler();
		SPI_C(Sercom* const SercomInstance) : com(SercomInstance){};
			
	protected:
		char msgBuff[30];
		uint8_t msgLength;
		uint8_t rxIndex;
		uint8_t txIndex;
		enum {Idle = 0, Rx, Tx, Rx_Ready} currentState;
		uint8_t ssPin;
};

// SPI interrupt handler
inline void SPI_C::Handler(){
	if (com->SPI.INTFLAG.bit.TXC && com->SPI.INTENSET.bit.TXC) {
		com->SPI.INTENCLR.reg = SERCOM_SPI_INTENCLR_TXC;
		currentState = Idle;	// Transmission end
	}
	if (com->SPI.INTFLAG.bit.DRE && com->SPI.INTENSET.bit.DRE) {
		// Data register empty
		if (currentState == Tx) {
			com->SPI.DATA.reg = msgBuff[txIndex];
		} else if(currentState == Rx) {
			com->SPI.DATA.reg = 0;		// Send dummy byte
		}
		
		txIndex++;
		
		if (txIndex >= msgLength) {
			com->SPI.INTENCLR.reg = SERCOM_SPI_INTENCLR_DRE;
			if (currentState == Tx) {
				com->SPI.INTENSET.reg = SERCOM_SPI_INTENSET_TXC;	// Wait for transmission complete
				com->SPI.INTFLAG.reg = SERCOM_SPI_INTFLAG_TXC;	// Clear flag
			}
		}
	}
	if (com->SPI.INTFLAG.bit.RXC && com->SPI.INTENSET.bit.RXC) {
		if (currentState == Rx) {
			msgBuff[rxIndex++] = com->SPI.DATA.reg;
			if (rxIndex >= msgLength) {
				currentState = Rx_Ready;
			}
		} else {
			volatile uint8_t dumdum = com->SPI.DATA.reg;
		}	
	}
	
	//NVIC_ClearPendingIRQ(SERCOM5_IRQn);
}

#endif /* SPI_H_ */