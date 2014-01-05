/*
 * flash.h
 *
 *  Created on: 2013.11.23.
 *      Author: zoli
 */
#include "config.h"

#ifndef FLASH_H_
#define FLASH_H_

typedef void (*void_func_ptr)(void);
typedef struct __attribute__((__packed__))
{
	void_func_ptr BTN_FUNC[CONFIG_BTN_COUNT];
	int BTN_DATA[CONFIG_BTN_COUNT];
	unsigned char FLAGS;
	unsigned char BEEP_LEN;
	unsigned char BEEP_VOL;
} flashdata;

extern flashdata * RAM_CONF;
extern flashdata * FLASH_CONF;

/*
extern void_func_ptr FLASH_BTN_FUNC[];
extern int FLASH_BTN_DATA[];
extern unsigned char FLASH_FLAGS;
extern unsigned char FLASH_BEEP_LEN;
extern unsigned char FLASH_BEEP_VOL;
*/
void FLASH_init();
void FLASH_read();
void FLASH_erase();
void FLASH_write();
char FLASH_compare();

#endif /* FLASH_H_ */
