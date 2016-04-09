/*
 * app.h
 *
 *  Created on: Jun 28, 2015
 *      Author: abubakr
 */

#ifndef APP_H_
#define APP_H_

#include <avr/eeprom.h>
#include "USART.h"
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "I2C.h"
#include "External_EEPROM.h"
#include "lcd.h"

#define M2_READY 0x10
#define SIZE 16

#define OPEN_DOOR 0x01
#define AUTH 0x02
#define ALERT 0x03
#define SAVE_PASSWD 0x04

#define ROTATE_CLOCK_WISE PC6
#define ROTATE_ANTI_CLOCK_WISE PC7
#define BUZZER PD7

void savePassword(void);
void authResponse(void);
void alert(void);

#endif /* APP_H_ */
