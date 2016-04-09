/*
 * Keypad.h
 *
 * Created: 4/3/2014 3:02:56 PM
 *  Author: Mohamed Tarek
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include<avr/io.h>

#define N_col 4
#define N_row 4

#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA 

unsigned char KeyPad_GetPressedKey(void);
unsigned char KeyPad_4x3_AdjustKeyNumber(unsigned char button_number);
unsigned char KeyPad_4x4_AdjustKeyNumber(unsigned char button_number);

#endif /* KEYPAD_H_ */