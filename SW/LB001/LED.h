/*
 * LED.h
 *
 *  Created on: 2013.11.02.
 *      Author: zoli
 */

#ifndef LED_H_
#define LED_H_

extern unsigned char LED_MINUTE;
extern unsigned char LED_SECOND;
extern unsigned char LED_FLAGS;

#define LED_EN_MIN	0x08
#define LED_EN_SEC	0x04
#define LED_UD	0x02
#define LED_LD	0x01

void LED_displaydigit();
void LED_off();

#endif /* LED_H_ */
