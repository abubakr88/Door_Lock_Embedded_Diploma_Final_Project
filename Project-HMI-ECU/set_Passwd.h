/*
 * set_Passwd.h
 *
 *  Created on: Jun 22, 2015
 *      Author: abubakr
 */

#ifndef SET_PASSWD_H_
#define SET_PASSWD_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#include "lcd.h"
#include "Keypad.h"
#include <string.h>

#define SIZE 16
#define M2_READY 0x10

//typedef struct password
//{
//	uint8 status;
//	uint8  *passwd;
//} passwd_new;

uint8 set_Passwd(void);
uint8 * enter_Passwd(void);

//passwd_new set_Passwd(void);

#endif /* SET_PASSWD_H_ */
