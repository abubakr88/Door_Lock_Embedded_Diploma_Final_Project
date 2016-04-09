/*
 * DIO.c
 *
 *  Created on: May 23, 2015
 *      Author: abubakr
 */

#include "DIO.h"

void DIO_Set_Direction(const DIO_Config *s_Config_Msg){
uint8 *ddr_ptr;
switch (s_Config_Msg -> port){
case 'A':
ddr_ptr =&DDRA;
break;
case 'B':
	ddr_ptr =&DDRB;
	break;
case 'C':
	ddr_ptr =&DDRC;
	break;
case 'D':
	ddr_ptr =&DDRD;
	break;
}
if (s_Config_Msg -> direction == OUTPUT){
	SET_BIT(*ddr_ptr,s_Config_Msg ->pin_num);
}
else{
	CLEAR_BIT(*ddr_ptr,s_Config_Msg ->pin_num);
}
}

void DIO_Write_Pin(const DIO_Config * s_State){

	uint8 *port_ptr;
	switch (s_State -> port){
	case 'A':
		port_ptr =&PORTA;
	break;
	case 'B':
		port_ptr =&PORTB;
		break;
	case 'C':
		port_ptr =&PORTC;
		break;
	case 'D':
		port_ptr =&PORTD;
		break;
	}
	if (s_State -> value == LOGIC_HIGH){
		SET_BIT(*port_ptr,s_State ->pin_num);
	}
	else{
		CLEAR_BIT(*port_ptr,s_State ->pin_num);
	}
}

uint8 DIO_Read_Pin(const DIO_Config * s_State){

	uint8 *pin_ptr;
	switch (s_State -> port){
	case 'A':
		pin_ptr =&PINA;
	break;
	case 'B':
		pin_ptr =&PINB;
		break;
	case 'C':
		pin_ptr =&PINC;
		break;
	case 'D':
		pin_ptr =&PIND;
		break;
	}

	if (BIT_IS_SET(*pin_ptr, s_State ->pin_num)){
		return (LOGIC_HIGH);
	}
	else{
		return (LOGIC_LOW);
	}
}

