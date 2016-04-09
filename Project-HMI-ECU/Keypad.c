/*
 * Keypad.c
 *
 * Created: 4/3/2014 3:02:35 PM
 *  Author: Mohamed Tarek
 */

#include "Keypad.h"

unsigned char KeyPad_GetPressedKey(void){
	unsigned char col,row;
	while(1)
	{
		KEYPAD_PORT_OUT |= 0x0F; //enable the internal pull up resistors for the first 4 pins in PORTA --> ROW pins.
		for(col=0;col<N_col;col++) //loop for columns
		{
			//each time only one of the column pins will be output and the rest will be input pins include the row pins 
			KEYPAD_PORT_DIR = (0b00010000<<col); 
			KEYPAD_PORT_OUT = (~(0b00010000<<col)); // clear the column which is the output pin in this trace 
			for(row=0;row<N_row;row++) //loop for rows
			{
				if((KEYPAD_PORT_IN & (1<<row)) == 0) //if the switch is press in this row 
				{
					#if (N_col == 3)  
						return KeyPad_4x3_AdjustKeyNumber((row*N_col)+col+1); //return the number of the switch 
					#else
						return KeyPad_4x4_AdjustKeyNumber((row*N_col)+col+1); //return the number of the switch 
					#endif				
				}
			}
		}
	}	
}

/*
 * this function responsible for mapping the switch number in the keypad to 
 * its corresponding functional number in the proteus for 4x3 keypad 
 */ 
unsigned char KeyPad_4x3_AdjustKeyNumber(unsigned char button_number)
{
	switch(button_number)
	{
		case 10: return '*'; // ASCII Code of =
				 break;
		case 11: return 0;
				 break;		
		case 12: return '#'; // ASCII Code of +
				 break;
		default: return button_number;								 						
	}
} 

/*
 * this function responsible for mapping the switch number in the keypad to 
 * its corresponding functional number in the proteus for 4x3 keypad  
 */ 
unsigned char KeyPad_4x4_AdjustKeyNumber(unsigned char button_number)
{
	switch(button_number)
	{
		case 1: return 7; 
				break;
		case 2: return 8; 
				break;
		case 3: return 9; 
				break;
		case 4: return '%'; // ASCII Code of %
				break;
		case 5: return 4; 
				break;
		case 6: return 5;
				break;
		case 7: return 6; 
				break;
		case 8: return '*'; // ASCII Code of *
				break;		
		case 9: return 1; 
				break;
		case 10: return 2; 
				break;
		case 11: return 3; 
				break;
		case 12: return '-'; // ASCII Code of -
				break;
		case 13: return 13;  // ASCII of Enter
				break;			
		case 14: return 0; 
				break;
		case 15: return '='; // ASCII Code of =
				break;
		case 16: return '+'; // ASCII Code of +
				break;
		default: return button_number;								 						
	}
} 