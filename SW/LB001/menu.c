/*
 * menu.c
 *
 *  Created on: 2013.12.23.
 *      Author: zoli
 */

#include "menu.h"
#include "config.h"
#include "flash.h"
#include "serial.h"
#include "textconv.h"

void_func_ptr btn_func_list[CONFIG_BTN_VECTOR_MAX];
char *btn_func_names[CONFIG_BTN_VECTOR_MAX];
MENU_btn_vector_data_descriptor * btn_func_data[CONFIG_BTN_VECTOR_MAX];
char btn_func_count = 0;

MENU_entry *menuarr[CONFIG_MENULEN_MAX];
char menuarr_count = 0;

signed char context = -1;
char menubuff[10];
unsigned char menulen = 0;

const char *num_validator = "0123456789\r\x08";
char *current_validator;


void MENU_add_btn_vector(void_func_ptr btn_vector, char * btn_descriptor, MENU_btn_vector_data_descriptor * btn_data)
{
	btn_func_list[btn_func_count] = btn_vector;
	btn_func_names[btn_func_count] = btn_descriptor;
	btn_func_data[btn_func_count] = btn_data;
	btn_func_count++;
}

void MENU_add_menuentry(MENU_entry *menuentry)
{
	menuarr[menuarr_count++] = menuentry;
}


char validate_input(char *validator, char input_char)
{
	// char * validator = "0123456789\r\x08";
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

void MENU_btn_dummy_vector() {}

void MENU_print(char *text)
{
	TimerA_UART_print(text);
}

void MENU_init()
{
	MENU_add_btn_vector(MENU_btn_dummy_vector, "Empty", 0);
}

char MENU_validate_flash()
{
	char retvalue = 1;
	unsigned char i, j;

	for(i = 0; i < CONFIG_BTN_COUNT && retvalue; i++)
	{
		retvalue = 0;
		for(j = 0; j < btn_func_count && !retvalue; j++)
		{
			retvalue = FLASH_CONF->BTN_FUNC[i] ==  btn_func_list[j];
		}
	}
	return retvalue;
}

void menu_print(char menunum)
{
	unsigned char i, j;
	char minstr[4];
	// MENU_entry *currententry;
	switch(menunum)
	{
		case 0:	// main menu
			TimerA_UART_print("\x1B[2J\r");
			for(i = 0;i < CONFIG_BTN_COUNT;i++)
			{
				TimerA_UART_tx(i + 0x31);
				TimerA_UART_print(") Change button ");
				TimerA_UART_tx(i + 0x31);
				TimerA_UART_print(". function: ");
				for(j = 0; j < btn_func_count; j++)
				{
					if(RAM_CONF->BTN_FUNC[i] ==  btn_func_list[j])
					{
						TimerA_UART_print(btn_func_names[j]);
						if(btn_func_data[j] != 0)
						{
							TimerA_UART_print(" (");
							if(!btn_func_data[j]->is_unit_postfix)
							{
								TimerA_UART_print(btn_func_data[j]->unit);
							}
							TimerA_UART_print(ByteToStr(RAM_CONF->BTN_DATA[i], minstr));
							if(btn_func_data[j]->is_unit_postfix)
							{
								TimerA_UART_print(btn_func_data[j]->unit);
							}
							TimerA_UART_print(")");
						}
					}
				}
				TimerA_UART_print("\r\n");
			}
			for(; i < CONFIG_BTN_COUNT + menuarr_count; i++)
			{
				TimerA_UART_tx(i + 0x31);
				TimerA_UART_print(") ");
				menuarr[i - CONFIG_BTN_COUNT]->menutext();
				TimerA_UART_print("\r\n");
			}
			/*
			TimerA_UART_tx(i++ + 0x31);
			TimerA_UART_print(") Beep length\r\n");
			TimerA_UART_tx(i++ + 0x31);
			TimerA_UART_print(") Beep volume\r\n");
			TimerA_UART_tx(i++ + 0x31);
			TimerA_UART_print(") Output polarity\r\n");
			TimerA_UART_tx(i++ + 0x31);
			TimerA_UART_print(") Save settings\r\n");
			*/
			print_input_prompt();
			break;
	}
}

void check_input()
{
	unsigned char i;
	signed char input_value;
	if(rxBuffLen > 0)
	{
		if(context == -1)
		{
			context = 0;
			menu_print(0);
			current_validator = num_validator;
		}
		else
		{
			if(validate_input(current_validator, rxBuffer))
			{
				switch(rxBuffer)
				{
					case '\r':
						rxBuffLen = 0;
						if(menulen == 0)
						{
							context = 0;
							menu_print(0);
							break;
						}

						if(context == 0)
						{
							// Main menu
							input_value = buff2value();
							menulen = 0;
							if(input_value > 0 && input_value <= CONFIG_BTN_COUNT)
							{
								TimerA_UART_print("\r\n\r\nSelect Button ");
								TimerA_UART_tx(input_value + 0x30);
								TimerA_UART_print(". Function");
								for(i = 0;i < btn_func_count;i++)
								{
									TimerA_UART_print("\r\n  ");
									TimerA_UART_tx(i + 0x31);
									TimerA_UART_print(")  ");
									TimerA_UART_print(btn_func_names[i]);
								}
								print_input_prompt();
								context = input_value;
								current_validator = num_validator;
							}
							if(input_value > CONFIG_BTN_COUNT && input_value <= (CONFIG_BTN_COUNT + menuarr_count))
							{
								// main menu, non button entry selected
								current_validator = menuarr[input_value - CONFIG_BTN_COUNT -1]->input_validator;
								TimerA_UART_print("\r\n\r\n");
								menuarr[input_value - CONFIG_BTN_COUNT -1]->question();
								context = input_value;
							}
							break;
						}
						if(context > 0 && context <= CONFIG_BTN_COUNT)
						{
							input_value = buff2value();
							menulen = 0;
							RAM_CONF->BTN_FUNC[context -1] = btn_func_list[input_value-1];
							if(btn_func_data[input_value-1] != 0)	// If it has a pointer to the data handling structure
							{
								// Question for the function data, switch to context something - also store in the context the button number
								// let say form 100 to 103
								context += 99;
								TimerA_UART_print("\r\n\r\n");
								TimerA_UART_print(btn_func_data[input_value-1]->input_question);
								current_validator = num_validator;
							}
							else
							{
								// Back to the main menu
								context = 0;
								menu_print(0);
								current_validator = num_validator;
							}
							break;
						}
						if(context > 99 && context <= CONFIG_BTN_COUNT + 99)
						{
							input_value = buff2value();
							menulen = 0;
							RAM_CONF->BTN_DATA[context - 100] = input_value;
							context = 0;
							menu_print(0);
							current_validator = num_validator;
							break;
						}
						if(context > CONFIG_BTN_COUNT && context <= (CONFIG_BTN_COUNT + menuarr_count))
						{
							// processing non button entry
							menubuff[menulen] = 0;
							menuarr[context - CONFIG_BTN_COUNT - 1]->execute(&menubuff);
							context = 0;
							menu_print(0);
							current_validator = num_validator;
							menulen = 0;
							break;
						}
						menulen = 0;
						break;
					case 8: // backspace
						if(menulen > 0)
						{
							menulen++;
							TimerA_UART_tx(rxBuffer);
						}
						break;
					default:
						if(menulen < 9)
						{
							menubuff[menulen] = rxBuffer;
							menulen++;
							TimerA_UART_tx(rxBuffer);
						}
						break;
				}

			}
		}
		rxBuffLen = 0;
	}
}

