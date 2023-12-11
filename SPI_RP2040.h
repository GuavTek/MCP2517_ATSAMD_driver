/*
 * SPI_RP2040.h
 *
 * Created: 25/09/2023
 *  Author: GuavTek
 */ 


#ifndef SPI_RP2040_H_
#define SPI_RP2040_H_
#include "communication_base.h"

struct spi_config_t {
	uint32_t speed;
};

class SPI_RP2040_C : public communication_base_c
{
	public:
		void Init(const spi_config_t config);
		inline void Handler();
		SPI_RP2040_C(){};
		~SPI_RP2040_C(){};
	protected:
		char msgBuff[32];
};

// SPI interrupt handler
inline void SPI_RP2040_C::Handler(){

}

#endif /* SPI_RP2040_H_ */