/*
 * main.c
 *
 *  Created on: Jun 20, 2015
 *      Author: abubakr
 */

// HMI-ECU

#include "main.h"
#include "app.h"


uint8 * passwd;

int main (void){

	uint8 a= PASSWORD_IS_SET , * returnPasswd;
	passwd=(uint8 *) malloc(15);

//==================================================//
//==============intialize LCD and UART==============//
//==================================================//

	APP_Init();

//===========================================================================================================//
//===== Ask MC2 for a value which is saved in eeprom, if it return 0xbb it means that the user password======//
//===== is already entered and saved in eeprom and will take the user to the default screen directly.========//
//===========================================================================================================//

	UART_SendByte(M2_READY); // MC2 is ready
	a=UART_RecieveByte();

//=================================================//
//======Set User Password for the first time=======//
//=================================================//

	if (a != PASSWORD_IS_SET){

		while (set_Passwd()){
		}

//=================================================//
//=====Send password to MC2 to save in eeprom======//
//=================================================//

		while(UART_RecieveByte() != M2_READY){} // wait until MC2 is ready
		UART_SendString(passwd);

//=============================================================//
//=====Send 0xbb to MC2 to save in eeprom for first check======//
//=============================================================//

		while(UART_RecieveByte() != M2_READY){} // wait until MC2 is ready
		UART_SendByte(PASSWORD_IS_SET);
	}

//===========================================================//
//================ Display Menu Options Screen ==============//
//===========================================================//

	defaultScreen();

	while(1){

//===========================================================//
//========== if "+" key presses Change the Password =========//
//===========================================================//

		if(KeyPad_GetPressedKey()== '+'){
			changePassword();
		}

//===========================================================//
//============= if "-" key pressed Open the Door ============//
//===========================================================//

		if(KeyPad_GetPressedKey()== '-'){

			openDoor();
		}

//===========================================================//
	}
	return (0);

}
