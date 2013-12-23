/*
 * flash.c
 *
 *  Created on: 2013.11.23.
 *      Author: zoli
 */
#include "flash.h"

void_func_ptr FLASH_BTN_FUNC[4];
int FLASH_BTN_DATA[4];

void FLASH_dummy() {}
void FLASH_init()
{
	unsigned char i;
	for(i=0;i<4;i++)
	{
		FLASH_BTN_FUNC[i] = FLASH_dummy;
		FLASH_BTN_DATA[i] = 0;
	}
}



