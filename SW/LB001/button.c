/*
 * button.c
 *
 *  Created on: 2013.11.04.
 *      Author: zoli
 */
#include "MCP23017.h"
#include "button.h"


unsigned char _btn_state = 0;
unsigned char _btn_count[4];

void BTN_init()
{
	// Inverse polarity
	MCP_Write(MCP_IPOLB,0xF0);
	// Enable pull-ups
	MCP_Write(MCP_GPPUB,0xF0);
}


unsigned char BTN_read()
{
	unsigned char btn_value;
	unsigned char i;
	// read button state from the port
	btn_value = (MCP_Read(MCP_GPIOB)) >> 4;
	// get the changed values
	btn_value ^= _btn_state;
	for(i = 0; i < 4; i++)
	{
		// if changed
		if((btn_value & (1 << i)) > 0)
		{
			// increase the debounce counter
			_btn_count[i]++;
			// if the debounce threshold reached
			if(_btn_count[i] > DEBOUNCE_COUNT)
			{
				// negate the button value
				_btn_state ^= (1 << i);
				// clear the debounce counter
				_btn_count[i] = 0;
			}
		}
		else
		{
			// if the button state not changed clear the debounce counter
			_btn_count[i] = 0;
		}
	}
	// return the button state
	return _btn_state;
	// return btn_value;
}
