/*
 * flash.c
 *
 *  Created on: 2013.11.23.
 *      Author: zoli
 */
#include "flash.h"
#include "config.h"
#include "menu.h"

void_func_ptr FLASH_BTN_FUNC[CONFIG_BTN_COUNT];
int FLASH_BTN_DATA[CONFIG_BTN_COUNT];
unsigned char FLASH_FLAGS = 0;
unsigned char FLASH_BEEP_LEN = 2;
unsigned char FLASH_BEEP_VOL = 10;
// Flags:
// 0 - Output Polarity (0 - Active High, 1 - Active Low)

// void FLASH_dummy() {}
void FLASH_init()
{
	// Add the FLASH_dummy function into the list of the button vectors
	unsigned char i;
	for(i=0;i<CONFIG_BTN_COUNT;i++)
	{
		FLASH_BTN_FUNC[i] = MENU_btn_dummy_vector;
		FLASH_BTN_DATA[i] = 0;
	}
	// Setup the flash timer
	// bit
	// 7-6 - 01 - MCLK
	// 5-0 - 1E - Divider 30 (assuming the 12MHz master clock the timing will be ~400kHz)
//	FCTL2 = FWKEY + FSSEL0 + 0x1E;

}

void FLASH_erase()
{
}



