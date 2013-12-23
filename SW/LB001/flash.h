/*
 * flash.h
 *
 *  Created on: 2013.11.23.
 *      Author: zoli
 */

#ifndef FLASH_H_
#define FLASH_H_

typedef void (*void_func_ptr)(void);
extern void_func_ptr FLASH_BTN_FUNC[];
extern int FLASH_BTN_DATA[];
void FLASH_init();
void FLASH_dummy();

#endif /* FLASH_H_ */
