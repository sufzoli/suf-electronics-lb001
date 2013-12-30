/*
 * flash.c
 *
 *  Created on: 2013.11.23.
 *      Author: zoli
 */
#include "flash.h"

void_func_ptr FLASH_BTN_FUNC[4];
int FLASH_BTN_DATA[4];
unsigned char FLASH_FLAGS = 0;
unsigned char FLASH_BEEP_LEN = 2;
unsigned char FLASH_BEEP_VOL = 10;
// Flags:
// 0 - Output Polarity (0 - Active High, 1 - Active Low)

void FLASH_dummy() {}
void FLASH_init()
{
	// Setup the flash timer
	// bit
	// 7-6 - 01 - MCLK
	// 5-0 - 1E - Divider 30 (assuming the 12MHz master clock the timing will be ~400kHz)
//	FCTL2 = FWKEY + FSSEL0 + 0x1E;


	unsigned char i;
	for(i=0;i<4;i++)
	{
		FLASH_BTN_FUNC[i] = FLASH_dummy;
		FLASH_BTN_DATA[i] = 0;
	}
}

void FLASH_erase()
{
}



