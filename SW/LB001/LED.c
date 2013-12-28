/*
 * LED.c
 *
 *  Created on: 2013.11.02.
 *      Author: zoli
 */

#include "MCP23017.h"
#include "7segment.h"
#include "LED.h"

unsigned char LED_MINUTE;
unsigned char LED_SECOND;
unsigned char LED_FLAGS;

unsigned char _digit_count = 0;
unsigned char _disp_buff[4];
/*
_disp_buff[0] = 0;
_disp_buff[1] = 0;
_disp_buff[2] = 0;
_disp_buff[3] = 0;
*/
void LED_displaydigit()
{
	// process the displaying data at the first digit should be displayed
	if(_digit_count == 0)
	{
		_disp_buff[0] = (LED_FLAGS & LED_EN_MIN) ? segments[LED_MINUTE / 10] : 0;
		_disp_buff[1] = ((LED_FLAGS & LED_EN_MIN) ? segments[LED_MINUTE % 10] : 0) | (((LED_FLAGS & LED_LD) == LED_LD) ? 0x80 : 0);
		_disp_buff[2] = ((LED_FLAGS & LED_EN_SEC) ? segments[LED_SECOND / 10] : 0) | (((LED_FLAGS & LED_UD) == LED_UD) ? 0x80 : 0);
		_disp_buff[3] = (LED_FLAGS & LED_EN_SEC) ? segments[LED_SECOND % 10] : 0;
	}
	MCP_Write(MCP_GPIOA, 0);
	MCP_Write(MCP_GPIOB, 1 << _digit_count);
	MCP_Write(MCP_GPIOA, _disp_buff[_digit_count]);
	_digit_count = (_digit_count == 3) ? 0 : ++_digit_count;
}

void LED_off()
{
	MCP_Write(MCP_GPIOA, 0);
}


