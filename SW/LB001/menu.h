/*
 * menu.h
 *
 *  Created on: 2013.12.23.
 *      Author: zoli
 */

#ifndef MENU_H_
#define MENU_H_

#include "flash.h"


typedef struct
{
	char is_unit_postfix;	// true if the unit descriptor come after the unit name
	char *unit;	// unit descriptor
	char *input_question;	// question for the data input
} MENU_btn_vector_data_descriptor;

void MENU_init();
void MENU_add_btn_vector(void_func_ptr btn_vector, char * btn_descriptor, MENU_btn_vector_data_descriptor * btn_data);
void MENU_btn_dummy_vector();


// #define BTN_Count 4

//typedef const char * string;


void check_input();

#endif /* MENU_H_ */
