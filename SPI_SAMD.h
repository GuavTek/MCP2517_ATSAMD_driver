/*
 * SPI.h
 *
 * Created: 01/07/2021 17:50:40
 *  Author: GuavTek
 */ 


#ifndef SPI_SAMD_H_
#define SPI_SAMD_H_

#include <sam.h>
#include "conf_board.h"
#include <port.h>
#include <interrupt.h>
#include "communication_base.h"

struct spi_config_t {
	uint8_t sercomNum;
	uint8_t dipoVal;
	uint8_t dopoVal;
	uint64_t speed;
	uint32_t pinmux_mosi;
	uint32_t pinmux_miso;
	uint32_t pinmux_sck;
	uint8_t pin_cs[];
};

class SPI_SAMD_C : public communication_base_c
{
	public:
		virtual inline void Set_Slave_Callback(uint8_t slaveNum, com_driver_c* cb);
		virtual uint8_t Transfer(char* buff, uint8_t length, com_state_e state);
		virtual inline void Select_Slave(uint8_t slaveNum, uint8_t enabled);
		void Init(const spi_config_t config);
		inline void Handler();
		SPI_SAMD_C(Sercom* const SercomInstance, uint8_t num_ss) : communication_base_c(num_ss), com(SercomInstance){};
	protected:
		Sercom* const com;
		char* msgBuff;
		uint8_t lastSlave;
		uint8_t slaveSelected;
		uint8_t msgLength;
		uint8_t rxIndex;
		uint8_t txIndex;
		uint8_t* csPin;
};

inline void SPI_SAMD_C::Set_Slave_Callback(uint8_t slaveNum, com_driver_c* cb){
	slaveCallbacks[slaveNum] = cb;
}

inline void SPI_SAMD_C::Select_Slave(uint8_t slaveNum, uint8_t enabled) {
	if (enabled && !slaveSelected){
		port_pin_set_output_level(csPin[slaveNum], 0);
		lastSlave = slaveNum;
		slaveSelected = 1;
		return 1;
	} else if (slaveNum == lastSlave) {
		port_pin_set_output_level(csPin[slaveNum], 1);
		slaveSelected = 0;
		return 1;
	}
	return 0;
}

// SPI interrupt handler
inline void SPI_SAMD_C::Handler(){
	if (com->SPI.INTFLAG.bit.TXC && com->SPI.INTENSET.bit.TXC) {
		com->SPI.INTENCLR.reg = SERCOM_SPI_INTENCLR_TXC;
		currentState = Idle;	// Transmission end
		slaveCallbacks[lastSlave]->com_cb();
	}
	if (com->SPI.INTFLAG.bit.DRE && com->SPI.INTENSET.bit.DRE) {
		// Data register empty
		if ((currentState == Tx) || (currentState == RxTx)) {
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
		if ((currentState == Rx) || (currentState == RxTx)) {
			msgBuff[rxIndex++] = com->SPI.DATA.reg;
			if (rxIndex >= msgLength) {
				currentState = Idle;
				slaveCallbacks[lastSlave]->com_cb();
				//com->SPI.INTENCLR.reg = SERCOM_SPI_INTENCLR_RXC;
			}
		} else {
			volatile uint8_t dumdum = com->SPI.DATA.reg;
		}	
	}
	
	//NVIC_ClearPendingIRQ(SERCOM5_IRQn);
}

#endif /* SPI_SAMD_H_ */