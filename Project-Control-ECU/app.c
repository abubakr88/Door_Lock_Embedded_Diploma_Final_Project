/*
 * app.c
 *
 *  Created on: Jun 28, 2015
 *      Author: abubakr
 */


#include "app.h"

//=================================================================================//
//============== intialize UART, I2c, I/O Ports and external eeprom  ==============//
//=================================================================================//

void APP_Init(void)
{
	UART_Init();
	LCD_init();
	EEPROM_Init();
	SET_BIT(DDRC,ROTATE_CLOCK_WISE);
	SET_BIT(DDRC,ROTATE_ANTI_CLOCK_WISE);
	SET_BIT(DDRD,BUZZER);

}

//====================================================================================================//
//============== This Function get password from MCU1 and compare it withe the password ==============//
//==============    saved in the external eeprom and if they matched send 0x01 to MCU1  ==============//
//====================================================================================================//

void authResponse(void){
	uint8 i, password[SIZE]={}, savedPassword[SIZE]={}, temp[SIZE];
	uint16  address= 0x0312;

	UART_SendByte(M2_READY); // MC2 is ready
	UART_ReceiveString(password);

	address = 0x0312;

	for (i=0;i<sizeof(savedPassword);i++){
		EEPROM_Read_Byte(address++, &savedPassword[i]); // Read 0x0F from the external EEPROM

	}

	if (!strcmp(password,savedPassword)){

		while(UART_RecieveByte() != M2_READY){} // wait until MC2 is ready
		UART_SendByte(0x01);

	}
}

//======================================================================================================//
//============== This function receive password from MCU1 and save it in the ext. eeprom  ==============//
//======================================================================================================//

void savePassword(void){
	uint16  address;
	uint8 i,passwd[SIZE];

	UART_SendByte(M2_READY); // MC2 is ready
	UART_ReceiveString(passwd);

	address = 0x0312; // the first address in the eeprom where to save the password.

	for (i=0;i<=sizeof(passwd);i++)
	{
		EEPROM_Write_Byte(address++, passwd[i]);
		_delay_ms(10);
	}
}

//==================================================================================//
//============= alert() function stop the system and Set the Buzer ON ==============//
//==================================================================================//

void alert(void){
	SET_BIT(PORTD,BUZZER);
	_delay_ms(60000);
}

//==========================================================================//
//======= This Function control the motor to open and close the door =======//
//==========================================================================//

void openDoor(void){

//========= (Rotate clock wise - Open the Door) ============//

	CLEAR_BIT(PORTC,ROTATE_ANTI_CLOCK_WISE);
	SET_BIT(PORTC,ROTATE_CLOCK_WISE);
	_delay_ms(5000);

//======== (Rotate anti-clock wise - Close the door)========//

	SET_BIT(PORTC,ROTATE_ANTI_CLOCK_WISE);
	CLEAR_BIT(PORTC,ROTATE_CLOCK_WISE);
	_delay_ms(5000);

//====================== Stop MOTOR ========================//

	CLEAR_BIT(PORTC,ROTATE_CLOCK_WISE);
	CLEAR_BIT(PORTC,ROTATE_ANTI_CLOCK_WISE);

}
