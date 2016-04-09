/*
 * USART.c
 *
 * Created: 2/19/2014 8:07:58 PM
 * Author: Mohamed Tarek
 */

#include "USART.h"
 
void UART_Init(void)
{

	UCSRA = (1<<U2X); //double transmission speed
	
	UCSRB = (1<<RXEN) | (1<<TXEN); //enable UART as transmitter and receiver.
	
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1); //8-bit data, NO parity, one stop bit and asynch 
	
	/* baud rate=9600 & Fosc=1MHz -->  UBBR=( Fosc / (8 * baud rate) ) - 1 = 12 */  
	UBRRH = 0;
	UBRRL = 12;
}
	
void UART_SendByte(const char data)
{
	while(!(UCSRA & (1<<UDRE))){} //UDRE flag is set when the buffer is empty and ready for transmitting a new byte so wait until this flag is set to one.
	UDR = data;
}

char UART_RecieveByte(void)
{
	while(!(UCSRA & (1<<RXC))){} //RXC flag is set when the UART receive data so until this flag is set to one
    return UDR;		
}

void UART_SendString(const char *Str)
{
	unsigned char i = 0;
	while(Str[i] != '\0')
	{
		UART_SendByte(Str[i]);
		i++;
	}
}

void UART_ReceiveString(char *Str)
{
	unsigned char i = 0;
	Str[i] = UART_RecieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_RecieveByte();
	}
	Str[i] = '\0';
}
