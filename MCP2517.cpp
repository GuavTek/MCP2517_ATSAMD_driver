/*
 * MCP2517.cpp
 *
 * Created: 10/10/2021 15:18:05
 *  Author: GuavTek
 */ 

#include "MCP2517.h"

extern const CAN_Filter_t Unused_Filter = {
	.enabled = false,
	.fifoDestination = 1,
	.extendedID = false,
	.ID = 0,
	.matchBothIDTypes = false,
	.maskID = 0
};

extern const CAN_FIFO_t Unused_Fifo = {
	.enabled = false,
	.payloadSize = 0,
	.fifoDepth = 0,
	.retransmitAttempt = CAN_FIFO_t::None,
	.messagePriority = 0,
	.txEnable = false,
	.autoRemote = false,
	.receiveTimestamp = false,
	.exhaustedTxInterrupt = false,
	.overflowInterrupt = false,
	.fullEmptyInterrupt = false,
	.halfFullEmptyInterrupt = false,
	.notFullEmptyInterrupt = false
};

extern CAN_Filter_t CAN_FLT0 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT1 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT2 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT3 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT4 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT5 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT6 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT7 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT8 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT9 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT10 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT11 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT12 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT13 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT14 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT15 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT16 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT17 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT18 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT19 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT20 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT21 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT22 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT23 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT24 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT25 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT26 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT27 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT28 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT29 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT30 __attribute__ ((weak, alias("Unused_Filter")));
extern CAN_Filter_t CAN_FLT31 __attribute__ ((weak, alias("Unused_Filter")));

CAN_Filter_t* Filter_Settings[32] = {
	&CAN_FLT0, &CAN_FLT1, &CAN_FLT2, &CAN_FLT3, &CAN_FLT4, 
	&CAN_FLT5, &CAN_FLT6, &CAN_FLT7, &CAN_FLT8, &CAN_FLT9,
	&CAN_FLT10, &CAN_FLT11, &CAN_FLT12, &CAN_FLT13, &CAN_FLT14, 
	&CAN_FLT15, &CAN_FLT16, &CAN_FLT17, &CAN_FLT18, &CAN_FLT19, 
	&CAN_FLT20, &CAN_FLT21, &CAN_FLT22, &CAN_FLT23, &CAN_FLT24,
	&CAN_FLT25, &CAN_FLT26, &CAN_FLT27, &CAN_FLT28, &CAN_FLT29,
	&CAN_FLT30, &CAN_FLT31
};

extern CAN_FIFO_t CAN_TXQ __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO1 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO2 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO3 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO4 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO5 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO6 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO7 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO8 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO9 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO10 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO11 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO12 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO13 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO14 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO15 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO16 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO17 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO18 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO19 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO20 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO21 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO22 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO23 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO24 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO25 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO26 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO27 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO28 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO29 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO30 __attribute__ ((weak, alias("Unused_Fifo")));
extern CAN_FIFO_t CAN_FIFO31 __attribute__ ((weak, alias("Unused_Fifo")));

CAN_FIFO_t* FIFO_Settings[32] = {
	&CAN_TXQ, &CAN_FIFO1, &CAN_FIFO2, &CAN_FIFO3, &CAN_FIFO4,
	&CAN_FIFO5, &CAN_FIFO6, &CAN_FIFO7, &CAN_FIFO8, &CAN_FIFO9,
	&CAN_FIFO10, &CAN_FIFO11, &CAN_FIFO12, &CAN_FIFO13, &CAN_FIFO14,
	&CAN_FIFO15, &CAN_FIFO16, &CAN_FIFO17, &CAN_FIFO18, &CAN_FIFO19,
	&CAN_FIFO20, &CAN_FIFO21, &CAN_FIFO22, &CAN_FIFO23, &CAN_FIFO24,
	&CAN_FIFO25, &CAN_FIFO26, &CAN_FIFO27, &CAN_FIFO28, &CAN_FIFO29,
	&CAN_FIFO30, &CAN_FIFO31
};

// Initializes the MCP2517 chip
void MCP2517_C::Init(const CAN_Config_t canConfig){
	// Connect to com interface
	comSlaveNum = canConfig.comSlaveNum;
	com->Set_Slave_Callback(comSlaveNum, this);
	
	msgState = MCP2517_C::Msg_Idle;
	
	Reset();
	
	uint32_t temp;
	
	temp = 0;
	temp |= 1 << 27;							// Abort all pending transmissions
	temp |= ((uint8_t) CAN_MODE_E::Configuration) << 24;	// Request config mode
	Write_Word_Blocking(ADDR_E::C1CON, temp);
	
	// Wait for config mode
	do {
		temp = Receive_Word_Blocking(ADDR_E::C1CON);
	} while ((temp & (0b111 << 21)) != (0b100 << 21));
	
	filterTimestamp = 0;
	for (uint8_t i = 0; i < 32; i++){
		// Configure filters
		if (Filter_Settings[i]->enabled){
			Filter_Init(Filter_Settings[i], i);
		}
		// Configure FIFOs
		if (FIFO_Settings[i]->enabled){
			FIFO_Init(FIFO_Settings[i], i);
		}
	}
	
	// Configure interrupts
	temp = 0;
	temp |= (canConfig.enableIntInvalidMessage ? 1 : 0) << 31;
	temp |= (canConfig.enableIntWakeup ? 1 : 0) << 30;
	temp |= (canConfig.enableIntBusError ? 1 : 0) << 29;
	temp |= (canConfig.enableIntSysError ? 1 : 0) << 28;
	temp |= (canConfig.enableIntRxOverflow ? 1 : 0) << 27;
	temp |= (canConfig.enableIntTxAttempt ? 1 : 0) << 26;
	temp |= (canConfig.enableIntCrcError ? 1 : 0) << 25;
	temp |= (canConfig.enableIntEccError ? 1 : 0) << 24;
	temp |= (canConfig.enableIntTxEvent ? 1 : 0) << 20;
	temp |= (canConfig.enableIntModeChange ? 1 : 0) << 19;
	temp |= (canConfig.enableIntTimebaseCount ? 1 : 0) << 18;
	temp |= (canConfig.enableIntRxFifo ? 1 : 0) << 17;
	temp |= (canConfig.enableIntTxFifo ? 1 : 0) << 16;
	Write_Word_Blocking(ADDR_E::C1INT, temp);
	
	temp = 0;
	temp |= (canConfig.enableEdgeFilter ? 1 : 0) << 25;
	temp |= (canConfig.enableSID11 ? 1 : 0) << 24;
	temp |= ((uint8_t) canConfig.txDelayCompensation) << 16;
	temp |= (canConfig.txDelayCompOffset) << 8;
	Write_Word_Blocking(ADDR_E::C1TDC, temp);
	
	temp = 0;
	temp |= canConfig.nominalBaudPrescaler << 24;	
	temp |= canConfig.nominalTSEG1 << 16;	
	temp |= canConfig.nominalTSEG2 << 8;	
	temp |= canConfig.nominalSyncJump;		
	Write_Word_Blocking(ADDR_E::C1NBTCFG, temp);
	
	temp = 0;
	temp |= canConfig.dataBaudPrescaler << 24;	
	temp |= canConfig.dataTSEG1 << 16;	
	temp |= canConfig.dataTSEG2 << 8;		
	temp |= canConfig.dataSyncJump;			
	Write_Word_Blocking(ADDR_E::C1DBTCFG, temp);
	
	temp = 0;
	temp |= ((uint8_t) canConfig.clkOutDiv) << 5;
	temp |= (canConfig.sysClkDiv ? 1 : 0) << 4;
	temp |= (canConfig.clkDisable ? 1 : 0) << 2;
	temp |= (canConfig.pllEnable ? 1 : 0);
	Write_Word_Blocking(ADDR_E::OSC, temp);
	
	temp = 0;
	temp |= ((uint8_t) canConfig.txBandwidthShare) << 28;
	temp |= ((uint8_t) canConfig.opMode) << 24;
	temp |= (canConfig.txQueueEnable ? 1 : 0) << 20;
	temp |= (canConfig.txEventStore ? 1 : 0) << 19;
	temp |= (canConfig.listenOnlyOnError ? 1 : 0) << 18;
	temp |= (canConfig.restrictRetransmit ? 1 : 0) << 16;
	temp |= (canConfig.disableBitrateSwitch ? 1 : 0) << 12;
	temp |= ((uint8_t) canConfig.wakeFilter) << 9;
	temp |= (canConfig.enableWakeFilter ? 1 : 0) << 8;
	temp |= (canConfig.disableProtocolException ? 1 : 0) << 6;
	temp |= (canConfig.enableIsoCrc ? 1 : 0) << 5;
	temp |= canConfig.deviceNetFilterBits;
	Write_Word_Blocking(ADDR_E::C1CON, temp);
	
	// Wait for chosen mode
	do {
		temp = Receive_Word_Blocking(ADDR_E::C1CON);
	} while ((temp & (0b111 << 21)) != (((uint8_t) canConfig.opMode) << 21));
	
}

void MCP2517_C::Reconfigure_Filters(uint32_t mask){
	// Disable interrupts
	//system_interrupt_enter_critical_section();
	
	// Set config mode
	uint32_t temp;
	uint32_t lastMode;
	lastMode = Receive_Word_Blocking(ADDR_E::C1CON);
	temp = lastMode & ~(0b111 << 24);
	temp |= 0b100 << 24;	// Request config mode
	Write_Word_Blocking(ADDR_E::C1CON, temp);
	
	// Wait for config mode
	do {
		temp = Receive_Word_Blocking(ADDR_E::C1CON);
	} while ((temp & (0b111 << 21)) != (0b100 << 21));
	
	for (uint8_t i = 0; i < 32; i++){
		// Configure filters
		if (mask & (1 << i)){
			Filter_Init(Filter_Settings[i], i);
		}
	}
	
	// Set previous mode
	Write_Word_Blocking(ADDR_E::C1CON, lastMode);
	
	// Wait for previous mode
	do {
		temp = Receive_Word_Blocking(ADDR_E::C1CON);
	} while ((temp & (0b111 << 21)) != (lastMode & (0b111 << 21)));
	
	// Re-enable interrupts
	//system_interrupt_leave_critical_section();
}

// Reset the CAN controller
void MCP2517_C::Reset(){
	char temp[4] = {0,0,0,0};
	while(com->Get_Status() != Idle);
	com->Select_Slave(comSlaveNum);
	com->Transfer(temp, 4, Tx);
	while(com->Get_Status() != Idle);
	com->Select_Slave(-1);
}

// Sends a number of bytes to the specified address of the MCP2517
uint8_t MCP2517_C::Send_Buffer(enum ADDR_E addr, char* data, uint8_t length){
	if (com->Get_Status() == Idle){
		char tempBuff[length+2];
		// Write buffer
		tempBuff[0] = ((char) MCP2517_INSTR_E::Write << 4) | ((uint16_t) addr >> 8);
		tempBuff[1] = (uint8_t) addr & 0xff;
		
		for (uint8_t i = 0; i < length; i++){
			tempBuff[i+2] = data[i];
		}
		
		com->Select_Slave(comSlaveNum);
		com->Transfer(tempBuff, length+2, Tx);
		
		// Return success
		return 1;
	} else {
		// Return not success
		return 0;
	}
};

// Reads a number of bytes from the specified address of the MCP2517
uint8_t MCP2517_C::Receive_Buffer(enum ADDR_E addr, uint8_t length){
	if (com->Get_Status() == Idle){
		char tempBuff[length+2];
		// Write buffer
		tempBuff[0] = ((char) MCP2517_INSTR_E::Read << 4) | ((uint16_t) addr >> 8);
		tempBuff[1] = (uint8_t) addr & 0xff;
		
		com->Select_Slave(comSlaveNum);
		com->Transfer(tempBuff, length+2, RxTx);
		
		return 1;
	} else {
		return 0;
	}
};

// Write a word to CAN controller and block execution until it is done
void MCP2517_C::Write_Word_Blocking(enum ADDR_E addr, uint32_t data){
	char temp[6];
	temp[0] = ((char) MCP2517_INSTR_E::Write << 4) | ((uint16_t) addr >> 8);
	temp[1] = (uint8_t) addr & 0xff;
	temp[2] = data & 0xff;
	temp[3] = (data >> 8) & 0xff;
	temp[4] = (data >> 16) & 0xff;
	temp[5] = (data >> 24) & 0xff;
	while(com->Get_Status() != Idle);
	com->Select_Slave(comSlaveNum);
	com->Transfer(temp, 6, Tx);
	while(com->Get_Status() != Idle);
	com->Select_Slave(-1);
}

uint32_t MCP2517_C::Receive_Word_Blocking(enum ADDR_E addr){
	char temp[6];
	temp[0] = ((char) MCP2517_INSTR_E::Read << 4) | ((uint16_t) addr >> 8);
	temp[1] = (uint8_t) addr & 0xff;
	for (uint8_t i = 2; i < 6; i++){
		temp[i] = 0;
	}
	while(com->Get_Status() != Idle);
	com->Select_Slave(comSlaveNum);
	com->Transfer(temp, 6, RxTx);
	while(com->Get_Status() != Rx_Ready);
	com->Read_Buffer(temp);
	com->Select_Slave(-1);
	uint32_t result = temp[2] | (temp[3] << 8) | (temp[4] << 16) | (temp[5] << 24);
	return result;
}

void MCP2517_C::FIFO_Increment(uint8_t fifoNum, uint8_t txRequest){
	uint16_t addr = Get_FIFOCON_Addr(fifoNum);
	
	char data = 1 | (txRequest << 1);
	
	Send_Buffer((ADDR_E) addr, &data, 1);
}

void MCP2517_C::FIFO_User_Address(uint8_t fifoNum){
	uint16_t addr = Get_FIFOUA_Addr(fifoNum);
	Receive_Buffer((ADDR_E) addr, 2);
}

// Formats the ID field
uint32_t MCP2517_C::GetID(uint16_t SID, uint32_t EID){
	uint32_t temp = 0;
	temp = SID & 0x07ff;
	temp |= EID << 11;
	temp |= (SID >> 11) << 29;
	return temp;
}

// Attempts to start a message transfer
uint8_t MCP2517_C::Transmit_Message(CAN_Tx_msg_t* data, uint8_t fifoNum){
	if (msgState == Msg_Idle){
		payloadLength = Get_Data_Length(data->dataLengthCode);
		msgBuff[2] = data->id;
		msgBuff[3] = data->id >> 8;
		msgBuff[4] = data->id >> 16;
		msgBuff[5] = data->id >> 24;
		
		uint8_t temp = 0;
		temp |= data->dataLengthCode;
		temp |= (data->extendedID ? 1 : 0) << 4;
		temp |= (data->requestRemote ? 1 : 0) << 5;
		temp |= (data->bitrateSwitch ? 1 : 0) << 6;
		temp |= (data->canFDFrame ? 1 : 0) << 7;
		msgBuff[6] = temp;
		
		temp = 0;
		temp |= (data->errorIndicator ? 1 : 0);
		temp |= data->sequence << 1;
		msgBuff[7] = temp;
		msgBuff[8] = 0;
		msgBuff[9] = 0;
		
		for (uint8_t i = 0; i < payloadLength; i++){
			msgBuff[i+10] = data->payload[i];
		}
		
		currentFifo = fifoNum;
		
		msgState = Msg_Tx_Addr;
		FIFO_User_Address(fifoNum);
		return 1;
	} else {
		return 0;
	}
}

// Send the payload
// Payload was loaded to buffer by Transmit_Message
void MCP2517_C::Send_Message_Object(uint16_t addr){
	msgBuff[0] = ((char) MCP2517_INSTR_E::Write << 4) | ((uint16_t) addr >> 8);
	msgBuff[1] = addr & 0xff;
	
	com->Select_Slave(comSlaveNum);
	com->Transfer(msgBuff, payloadLength + 10, Tx);
}

// Request status info of FIFO
void MCP2517_C::Check_FIFO_Status(uint8_t fifoNum){
	uint16_t addr = Get_FIFOSTA_Addr(fifoNum);
	msgState = Msg_FIFO_Int;
	Receive_Buffer((ADDR_E) addr, 1);
}

void MCP2517_C::Check_Int_Reg(){
	msgState = Msg_Status;
	Receive_Buffer(ADDR_E::C1VEC, 4);
}

void MCP2517_C::Check_Rx_Flags_Reg(){
	msgState = Msg_Rx_Flags;
	Receive_Buffer(ADDR_E::C1RXIF, 4);
}

/*
// Checks MCP2517 interrupt pin
void MCP2517_C::Check_Rx_Int(){
	if (!port_pin_get_input_level(interruptPin)){	// TODO: decouple MCU
		msgState = Msg_Rx_Addr;
		Check_Rx_Flags_Reg();
	}
}

// Check MCP2517 interrupt register every RTC tick
void MCP2517_C::Check_Rx_RTC(){
	static uint32_t count = 0;
	if (count < RTC->MODE0.COUNT.reg){
		count = RTC->MODE0.COUNT.reg;
		Check_Rx_Flags_Reg();
	}
} //*/

uint8_t MCP2517_C::Check_Rx(){
	if (msgState == MCP2517_C::Msg_Idle){
		// Start checking the Rx flags
		Check_Rx_Flags_Reg();
		return 1;
	}
	return 0;
}

void MCP2517_C::com_cb(){
	switch(msgState){
		case Msg_Rx_Flags:
		if (com->Get_Status() == Rx_Ready){
			// Rx flags were fetched, check if data is waiting
			com->Select_Slave(-1);
			char temp[6];
			com->Read_Buffer(temp);
			uint32_t intFlags = temp[2] | (temp[3] << 8) | (temp[4] << 16) | (temp[5] << 24);
			if (intFlags == 0){
				// No message
				msgState = Msg_Idle;
			} else {
				// Message waiting in buffer
				for (uint8_t i = 1; i < 32; i++){
					if (intFlags & (1 << i)){
						msgState = Msg_Rx_Addr;
						FIFO_User_Address(i);
						currentFifo = i;	// TODO: verify
						break;
					}
				}
			}
		}
		break;
		case Msg_Rx_Addr:
		if (com->Get_Status() == Rx_Ready){
			// Rx RAM address fetched, start fetching data
			com->Select_Slave(-1);
			msgState = Msg_Rx_Data;
			char temp[4];
			com->Read_Buffer(temp);
			
			uint16_t addr = (temp[3] << 8) | temp[2];
			addr += (uint16_t) ADDR_E::RAM_START;
			Receive_Buffer((ADDR_E) addr, 26);
		}
		break;
		case Msg_Rx_Data:
		if (com->Get_Status() == Rx_Ready){
			// Rx data fetched, increment fifo
			com->Select_Slave(-1);
			char buffer[26];
			com->Read_Buffer(buffer);
			CAN_Rx_msg_t tempMsg;
			
			tempMsg.id = buffer[2] | (buffer[3] << 8) | (buffer[4] << 16) | (buffer[5] << 24);
			tempMsg.dataLengthCode = buffer[6] & 0x0f;
			tempMsg.extendedID = (buffer[6] & 0x10) ? 1 : 0;
			tempMsg.requestRemote = (buffer[6] & 0x20) ? 1 : 0;
			tempMsg.bitrateSwitch = (buffer[6] & 0x40) ? 1 : 0;
			tempMsg.canFDFrame = (buffer[6] & 0x80) ? 1 : 0;
			tempMsg.errorStatus = (buffer[7] & 0x01) ? 1 : 0;
			tempMsg.filterHit = buffer[7] >> 3;
			
			if (filterTimestamp & (1 << tempMsg.filterHit)){
				tempMsg.timeStamp = buffer[10] | (buffer[11] << 8) | (buffer[12] << 16) | (buffer[13] << 24);
				tempMsg.payload = &buffer[14];
			} else {
				tempMsg.payload = &buffer[10];
			}
			
			Rx_Callback(&tempMsg);
			msgState = Msg_Rx_FIFO;
			FIFO_Increment(currentFifo, 0);
		}
		break;
		case Msg_Rx_FIFO:
		if (com->Get_Status() == Idle){
			// Rx done
			com->Select_Slave(-1);
			msgState = Msg_Idle;
		}
		break;
		case Msg_Tx_Addr:
		if (com->Get_Status() == Rx_Ready){
			// Tx RAM address was fetched, send data
			com->Select_Slave(-1);
			msgState = Msg_Tx_Data;
			char temp[4];
			com->Read_Buffer(temp);
			
			uint16_t addr = (temp[3] << 8) | temp[2];
			addr += (uint16_t) ADDR_E::RAM_START;
			Send_Message_Object(addr);
		}
		break;
		case Msg_Tx_Data:
		if (com->Get_Status() == Idle){
			// Tx data was sent to RAM, increment fifo and request data send
			com->Select_Slave(-1);
			msgState = Msg_Tx_FIFO;
			FIFO_Increment(currentFifo, 1);
		}
		break;
		case Msg_Tx_FIFO:
		if (com->Get_Status() == Idle){
			// Tx done
			com->Select_Slave(-1);
			msgState = Msg_Idle;
		}
		break;
		default:
		break;
	}
}
