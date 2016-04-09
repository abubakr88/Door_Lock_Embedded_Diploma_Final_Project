/*
 * set_Passwd.c
 *
 *  Created on: Jun 22, 2015
 *      Author: abubakr
 */


#include "set_Passwd.h"
extern uint8 * passwd;

//=====================================================================================================//
//========= set_Passwd function take password from user twice and check if they are matched ===========//
//=====================================================================================================//

uint8 set_Passwd(void){
	uint8 i=0,comp_Array=1,* re_Passwd;

		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Enter New Passwd");

		_delay_ms(500);

		passwd = enter_Passwd();


		_delay_ms(500);

		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Renter Passwd");
		re_Passwd = enter_Passwd();

		_delay_ms(500);

//=====================================================================================================//
//========== Compare the two passwords and return 0 if they matched or 1 if they don't match ==========//
//=====================================================================================================//

		if (!strcmp(passwd,re_Passwd)){
			LCD_clearScreen();
			LCD_displayString("match");
			_delay_ms(300);

			return(0);
		}
		else{

			LCD_clearScreen();
			LCD_displayString("dismatch");
			_delay_ms(300);

			return(1);
		}

}

//===========================================================================================//
//===== enter_Passwd() function get the pressed keys(password) and save it as a string  =====//
//===========================================================================================//

uint8 * enter_Passwd(void){
	uint8 j=0,col=0, * password;
	password = (uint8 *) malloc(15);
	while (KeyPad_GetPressedKey() != 13)             //======= loop till the enter key is pressed ======//
	{
		password[j++]='0'+KeyPad_GetPressedKey();    //=======     get the pressed key number     ======//
		LCD_displayStringRowColumn(1,col++,"*");
		_delay_ms(250);
	}
	password[col]='#'; 								 //======= The # for UART_SendString Function =====//
	password[col+1]='\0';
	return password;

}
