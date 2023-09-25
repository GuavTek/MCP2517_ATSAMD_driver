/*
 * SPI_RP2040.h
 *
 * Created: 25/09/2023
 *  Author: GuavTek
 */ 


#ifndef SPI_RP2040_H_
#define SPI_RP2040_H_
#include "communication_base.h"

class SPI_RP2040_C : public communication_base_c
{
	public:
		inline void Handler();
		SPI_RP2040_C();
	protected:
		char msgBuff[32];
};

// SPI interrupt handler
inline void SPI_RP2040_C::Handler(){

}

#endif /* SPI_SAMD_H_ */