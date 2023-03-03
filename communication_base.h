/*
 * communication_base.h
 *
 * Created: 25/02/2023 14:56:40
 *  Author: GuavTek
 */ 


#ifndef COMMUNICATION_BASE_H_
#define COMMUNICATION_BASE_H_

#include <stdint.h>

enum com_state_e {
	Idle = 0,
	Rx,
	Tx,
	RxTx,
	Rx_Ready
};

// An abstract class providing a callback handle the communication base uses
class com_driver_c
{
	public:
		virtual void com_cb();
};

// An abstract class providing a base API the MCP2517 driver can use
// To port the MCP2517 driver to other MCUs one only needs to make an SPI driver extended from this class
class communication_base_c
{
	public:
		inline com_state_e Get_Status(){ return currentState; }		// Returns the internal state of the object
		virtual void Set_Slave_Callback(uint8_t slaveNum, com_driver_c* cb);	// Set the object to call its com_cb function when transactions finish
		virtual void Select_Slave(int slaveNum);	// Set the selected slave (-1 to de-select)
		virtual uint8_t Read_Buffer(char* buff);	// Transfers data from the internal buffer to *buff, returns the number of bytes transferred
		virtual uint8_t Transfer(char* buff, uint8_t length, com_state_e state);	// Try to start a transfer, returns 0 if operation failed
	protected:
		com_state_e currentState;
};

#endif /* COMMUNICATION_BASE_H_ */