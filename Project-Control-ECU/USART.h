/*
 * USART.h
 *
 * Created: 2/19/2014 8:08:52 PM
 *  Author: Mohamed Tarek
 */ 


#ifndef USART_H_
#define USART_H_

#include <avr/io.h>

void UART_Init(void);

void UART_SendByte(const char data);

char UART_RecieveByte(void);

void UART_SendString(const char *Str);

void UART_ReceiveString(char *Str); // Receive until #

#endif /* USART_H_ */