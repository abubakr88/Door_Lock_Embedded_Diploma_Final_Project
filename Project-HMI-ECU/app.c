/*
 * app.c
 *
 *  Created on: Jun 23, 2015
 *      Author: abubakr
 */
#include "app.h"
extern uint8 * passwd;

//==================================================//
//==============intialize LCD and UART==============//
//==================================================//

void APP_Init(void)
{
	UART_Init();
    LCD_init();

}

//==================================================//
//================Option Menu Function==============//
//==================================================//

void defaultScreen(void){
	LCD_displayStringRowColumn(0,0,"+ : Change Pass");
	LCD_displayStringRowColumn(1,0,"- : Open Door");
}

//==================================================//
//============authentication Request Function=======//
//==================================================//

uint8 authRequest(void){
	uint8 response ,* entredPasswd;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Your Paswd");
	_delay_ms(500);

	entredPasswd=enter_Passwd();

// send option to MC2 for auth

	while(UART_RecieveByte() != M2_READY){} // wait until MC2 is ready
	UART_SendByte(AUTH);

// send the password the user entered to MC2 to check it.

	while(UART_RecieveByte() != M2_READY){} // wait until MC2 is ready
	UART_SendString(entredPasswd);

// receive the authentication result from MC2

	UART_SendByte(M2_READY); // MC2 is ready
	response = UART_RecieveByte();



	if (response == 0x01){
		return (1);
	}
	else {
		return (0);
	}
}

//==========================================================================================================//
//====changePassword () function ask for user password if correct ask the user to enter new password =======//
//====      and send it to MCU2 and if the user insert wrong password for 3 times makes an alert     =======//
//==========================================================================================================//

void changePassword(void){

	uint8 wrongCount=0;

	while ( wrongCount <3 && !authRequest()){
		wrongCount++;
	}

	if (wrongCount==3){
		alert();
	}
	else{
		while (set_Passwd()){
		}
		// Send password to MC2 to save to eeprom.

		while(UART_RecieveByte() != M2_READY){} // wait until MC2 is ready
		UART_SendByte(SAVE_PASSWD);

		while(UART_RecieveByte() != M2_READY){} // wait until MC2 is ready
		UART_SendString(passwd);

	}
	defaultScreen();
}

//===========================================================================================//
//============= alert() function stop the system and send alert signal to MCU2 ==============//
//===========================================================================================//

void alert(void){

	while(UART_RecieveByte() != M2_READY){} // wait until MC2 is ready
	UART_SendByte(ALERT);

	LCD_clearScreen();
	LCD_displayString("Alert");
	_delay_ms(60000);

	defaultScreen();
}

//============================================================================================//
//====== openDoor() function ask for user password if correct and send opendoor signal =======//
//======    to MCU2 and if the user insert wrong password for 3 times makes an alert   =======//
//============================================================================================//

void openDoor(void){

	uint8 wrongCount=0;

	while ( wrongCount <3 && !authRequest()){
		wrongCount++;
	}

	if (wrongCount==3){
		alert();
	}

	else {

	while(UART_RecieveByte() != M2_READY){} // wait until MC2 is ready
	UART_SendByte(OPEN_DOOR);

	LCD_clearScreen();
	LCD_displayString("DOOR IS OPENING");
	_delay_ms(5000);
	LCD_clearScreen();
	LCD_displayString("DOOR IS CLOSING");
	_delay_ms(5000);

	}
	defaultScreen();

}
