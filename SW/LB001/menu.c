/*
 * menu.c
 *
 *  Created on: 2013.12.23.
 *      Author: zoli
 */

#include "menu.h"
#include "serial.h"
#include "flash.h"
#include "counter.h"
#include "main.h"
#include "textconv.h"

const void_func_ptr btn_func_list[] = { FLASH_dummy, ctr_up, ctr_down, ctr_stop,  start_count };
char * btn_func_names[] = { "Empty", "Counter Up", "Counter Down", "Counter Stop",  "Counter Start" };
signed char context = -1;
unsigned char menubuff[10];
unsigned char menulen = 0;

signed char input_value;

char validate_input(char input_char)
{
	string validator = "0123456789\r\x08";
	while(*validator)
	{
		if(input_char == *validator++)
		{
			return 1;
		}
	}
	return 0;
}

signed char buff2value()
{
	unsigned int retvalue = 0;
	unsigned char i;
	if(menulen < 4)
	{
		for(i=0;i<menulen;i++)
		{
			retvalue = retvalue * 10 + menubuff[i] - 0x30;
		}
		if(retvalue < 128)
		{
			return retvalue;
		}
	}
	return -1;
}

void print_input_prompt()
{
	TimerA_UART_print("\r\n\r\nEnter number to select an option: ");
}


/*
void insert_write(char *text, char *insertionstrings[])
{
	unsigned int i;
	char *insertionstring;
	for(;*text;text++)
	{
		if(*text != '%')
		{
			TimerA_UART_tx(*text);
		}
		else
		{
			text++;
			if(text > 0x29 && text < 0x3A)
			{
				insertionstring = insertionstrings[*text - 0x30];
				for(;*insertionstring;insertionstring++)
				{
					TimerA_UART_tx(*insertionstring);
				}
			}
		}
	}
}
*/

void menu_init()
{
	unsigned char i, j, flash_invalid;
	for(i = 0;i < 4;i++)
	{
		for(j = 0; j < 5; j++)
		{
			flash_invalid = 1;
			if(FLASH_BTN_FUNC[i] ==  btn_func_list[j])
			{
				flash_invalid = 0;
			}
		}
		if(flash_invalid)
		{
			break;
		}
	}
	if(flash_invalid)
	{
		FLASH_clear();

	}
}


void menu_print(char menunum)
{
	unsigned char i, j;
	char minstr[4];
	switch(menunum)
	{
		case 0:	// main menu
			TimerA_UART_print("\x1B[2J\r");
			for(i = 0;i < BTN_Count;i++)
			{
				TimerA_UART_tx(i + 0x31);
				TimerA_UART_print(") Change button ");
				TimerA_UART_tx(i + 0x31);
				TimerA_UART_print(". function: ");
				for(j = 0; j < 5; j++)
				{
					if(FLASH_BTN_FUNC[i] ==  btn_func_list[j])
					{
						TimerA_UART_print(btn_func_names[j]);
						if(j == 4)
						{
							TimerA_UART_print(" (");
							TimerA_UART_print(ByteToStr(FLASH_BTN_DATA[i], minstr));
							TimerA_UART_print(" min)");
						}
					}
				}
				TimerA_UART_print("\r\n");
			}
			TimerA_UART_tx(i++ + 0x31);
			TimerA_UART_print(") Beep length\r\n");
			TimerA_UART_tx(i++ + 0x31);
			TimerA_UART_print(") Beep volume\r\n");
			TimerA_UART_tx(i++ + 0x31);
			TimerA_UART_print(") Output polarity\r\n");
			print_input_prompt();
			break;
	}
}

void check_input()
{
	unsigned char i;
	if(rxBuffLen > 0)
	{
		if(context == -1)
		{
			context = 0;
			menu_print(0);
		}
		else
		{
			if(validate_input(rxBuffer))
			{
				switch(rxBuffer)
				{
					case '\r':
						rxBuffLen = 0;
						input_value = buff2value();
						menulen = 0;
						if(input_value > -1)
						{
							switch(context)
							{
								case 0:	// Main menu
									switch(input_value)
									{
										case 1:
										case 2:
										case 3:
										case 4:
											TimerA_UART_print("\r\n\r\nSelect Button ");
											TimerA_UART_tx(input_value + 0x30);
											TimerA_UART_print(". Function");
											for(i = 0;i < 5;i++)
											{
												TimerA_UART_print("\r\n  ");
												TimerA_UART_tx(i + 0x31);
												TimerA_UART_print(")  ");
												TimerA_UART_print(btn_func_names[i]);
											}
											print_input_prompt();
											context = input_value;
											break;
									}
									break;
								case 1:
								case 2:
								case 3:
								case 4:
									FLASH_BTN_FUNC[context -1] = btn_func_list[input_value-1];
									if(input_value == 5)
									{
										// Question for the startup minute, switch to context something - also store in the context the button number
										// let say form 100 to 103
										context += 99;
										TimerA_UART_print("\r\n\r\nEnter the counter time in minutes: ");
									}
									else
									{
										// Back to the main menu
										context = 0;
										menu_print(0);
									}
									break;
								case 100:
								case 101:
								case 102:
								case 103:
									FLASH_BTN_DATA[context - 100] = input_value;
									context = 0;
									menu_print(0);
									break;
							}
						}
						break;
					case 8: // backspace
						if(menulen > 0)
						{
							menulen++;
							TimerA_UART_tx(rxBuffer);
						}
						// rxBuffLen = 0;
						break;
					default:
						if(menulen < 10)
						{
							menubuff[menulen] = rxBuffer;
							menulen++;
							TimerA_UART_tx(rxBuffer);
						}
						// rxBuffLen = 0;
						break;
				}

			}
		}
		rxBuffLen = 0;
	}
}

