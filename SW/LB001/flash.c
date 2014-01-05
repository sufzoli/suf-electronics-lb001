/*
 * flash.c
 *
 *  Created on: 2013.11.23.
 *      Author: zoli
 */
#include <msp430.h>
#include "flash.h"
#include "config.h"
#include "menu.h"

#define CONFIG_FLASH_ADDR	0x1000u	// Base address of the used 64Byte flash Segment (0x1000 - Segment D)


flashdata *FLASH_CONF = (flashdata*)CONFIG_FLASH_ADDR;
flashdata RAM_CONF_data;
flashdata *RAM_CONF = &RAM_CONF_data;

// Flags:
// 0 - Output Polarity (0 - Active High, 1 - Active Low)

void menusave_text()
{
	MENU_print("Save settings");
}

void menusave_question()
{
	MENU_print("Do you want to save the settings? (y/n): ");
}

void menusave_execute(char *text)
{
	if(text[0] == 'y' || text[0] == 'Y')
	{
		if(!FLASH_compare())
		{
			FLASH_erase();
			FLASH_write();
		}
	}
}

const MENU_entry menusave_entry = {menusave_text, menusave_question, "ynYN\r", menusave_execute};

void FLASH_init()
{
	// Setup the flash timer
	// bit
	// 7-6 - 01 - MCLK
	// 5-0 - 1E - Divider 30 (assuming the 12MHz master clock the timing will be ~400kHz)
	FCTL2 = FWKEY + FSSEL0 + 0x1E;
	MENU_add_menuentry(&menusave_entry);
}

/*
void memcpy(void *src, void *dst, unsigned int len)
{
	char *d = dst;
	const char *s = src;
	for(i = 0; i < len; i++)
	{
		d[i] = s[i];
	}
}
*/
void FLASH_erase()
{
	char *flashptr;
	flashptr = (char *) CONFIG_FLASH_ADDR;	// Initialize flash segment pointer
	FCTL1 = FWKEY + ERASE;		// Set Erase bit
	FCTL3 = FWKEY;              // Clear Lock bit
	*flashptr = 0;              // Write to the flash segment to erase it
	FCTL1 = FWKEY;            	// Clear Erase bit
	FCTL3 = FWKEY + LOCK;       // Set Lock bit
}

char FLASH_compare()
{
	unsigned int i;
	char *f = (char*)FLASH_CONF;
	char *r = (char*)RAM_CONF;
	char retvalue = 1;
	for(i = 0; i < sizeof(flashdata) && retvalue; i++)
	{
		retvalue = f[i] == r[i];
	}
	return retvalue;
}

void FLASH_write()
{
	FCTL1 = FWKEY + WRT;        // Set Write bit for write operation
	FCTL3 = FWKEY;              // Clear Lock bit
	memcpy(FLASH_CONF, RAM_CONF, sizeof(flashdata));
	FCTL1 = FWKEY;            	// Clear Write bit
	FCTL3 = FWKEY + LOCK;       // Set Lock bit
}

void FLASH_read()
{
	memcpy(RAM_CONF, FLASH_CONF, sizeof(flashdata));
}



