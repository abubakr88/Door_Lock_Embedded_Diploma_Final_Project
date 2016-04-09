/*
/** @file    App.c
 ** @brief   AVR Micro-controllers specific configurations
 ** @author  Mohamed Tarek
 ** @date    22/1/2014
 ** @version 1.0
 */ 


#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 8000000UL //1MHz Clock frequency
#endif  

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif /* MICRO_CONFIG_H_ */
