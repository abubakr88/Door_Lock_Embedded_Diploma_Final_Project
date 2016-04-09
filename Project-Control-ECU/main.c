/*
 * main.c
 *
 *  Created on: Jun 20, 2015
 *      Author: abubakr
 */

// COntrol-ECU

#include "main.h"

int main (void){
	uint8 a,option;

//=================================================================================//
//============== intialize UART, I2c, I/O Ports and external eeprom  ==============//
//=================================================================================//

	APP_Init();

//=====================================================================================================//
//============== Get The byte in address 0x0311  in external eeprom and send it to MCU1  ==============//
//=====================================================================================================//

	EEPROM_Read_Byte(0x0311, &a);
	while(UART_RecieveByte() != M2_READY){} // wait until MC1 is ready
	UART_SendByte(a); // MC1 is ready

//==================================================================================================================//
//==== If a value not equal 0xbb get password from MCU1 and save it external eeprom in address 0x0312 ==============//
//==================================================================================================================//

	if (a != PASSWORD_IS_SET)
	{
		savePassword();

		UART_SendByte(M2_READY); // MC2 is ready
		a=UART_RecieveByte();
		EEPROM_Write_Byte(0x0311,a);

	}
while(1){

//==================================================//
//=========== Receive Option From MCU1  =======//
//==================================================//

	UART_SendByte(M2_READY); // MC2 is ready
	option=UART_RecieveByte();

	switch (option) {
	case OPEN_DOOR :
		openDoor();
		break;

	case AUTH :
		authResponse();
		break;

	case SAVE_PASSWD :
		savePassword();
		break;

	case ALERT:
		alert();
		break;

	}
}
return (0);
}
