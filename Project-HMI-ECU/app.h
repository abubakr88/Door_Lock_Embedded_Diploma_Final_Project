/*
 * app.h
 *
 *  Created on: Jun 23, 2015
 *      Author: abubakr
 */

#ifndef APP_H_
#define APP_H_

#include "lcd.h"
#include "Keypad.h"
#include "set_Passwd.h"
#include "USART.h"
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#define M2_READY 0x10
#define PASSWORD_IS_SET 0xbb

#define OPEN_DOOR 0x01
#define AUTH 0x02
#define ALERT 0x03
#define SAVE_PASSWD 0x04


void defaultScreen(void);
uint8 authRequest(void);
void changePassword(void);
void alert(void);

#endif /* APP_H_ */
