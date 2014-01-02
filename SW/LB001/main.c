#include <msp430.h>
#include "main.h"
#include "i2c_usi.h"
#include "MCP23017.h"
#include "LED.h"
#include "counter.h"
#include "button.h"
#include "flash.h"
#include "serial.h"
#include "menu.h"


/*
 * main.c
 */


int start_count_value;
void start_count()
{
	CTR_start(start_count_value,0);
}

/*
void start_5min_count()
{
	ctr_start(5,0);
}
*/

void beep()
{
	unsigned int j;
	unsigned char k;
	j = FLASH_BEEP_LEN;
	P1DIR |= BUZZER_PIN;
	P1SEL &= ~BUZZER_PIN;
	P1SEL2 &= ~BUZZER_PIN;
	for(j *= 4000; j > 0 ; j--)
	{
		P1OUT |= BUZZER_PIN;
		for(k = 0; k < FLASH_BEEP_VOL; k++)
			_delay_cycles(140);
		P1OUT &= ~BUZZER_PIN;
		for(k = 0; k < 20 - FLASH_BEEP_VOL; k++)
			_delay_cycles(140);
	}
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    // Set 12MHz clock
	// DCOCTL = 0;
	BCSCTL1 = CALBC1_12MHZ;
	DCOCTL = CALDCO_12MHZ;

	// BIT 7-6 = 00 Select MCLK to DCOCLK
	// BIT 5-4 = 00 Set MCLK Clock Divider to /1
	// BIT   3 =  0 Select SMCLK to DCOCLK
	// BIT 2-1 = 00 Set SMCLK Clock Divider to /1
	// BIT   0 =  0 DCO resistor: internal (no meaning because using external is not possible)
	BCSCTL2 = 0;

	// Bit 5-4 = 11 Set ACLK Clock Divider to /8
	// BCSCTL1 |= DIVA0 + DIVA1;

	// Bit 5-4 = 11 Set ACLK Clock Divider to /1
	BCSCTL1 &= ~(DIVA0 + DIVA1);


	// Bit 5-4 = 10 Select Low frequency clock to VLOCLK
	//BCSCTL3 &= ~LFXT1S0;
	//BCSCTL3 |= LFXT1S1;

	// Bit 5-4 = 10 Select Low frequency clock to LFXT1 (32768Hz XTAL)
	BCSCTL3 &= ~(LFXT1S0 + LFXT1S1);

	// Startup Delay
	_delay_cycles(2000);

	unsigned char buttonstate = 0;
	unsigned char buttonvalue = 0;
/*
	unsigned char prev_min = 0;
	unsigned char prev_sec = 0;
*/
	MENU_init();
	FLASH_init();

	FLASH_BTN_FUNC[0] = CTR_up;
	FLASH_BTN_FUNC[1] = CTR_down;
	FLASH_BTN_FUNC[2] = CTR_stop;
	FLASH_BTN_FUNC[3] = start_count;
	FLASH_BTN_DATA[3] = 5;

	MCP_init(1, 1);
	BTN_init();

	CTR_init();

	MENU_btn_vector_data_descriptor start_data_descriptor_data;
	MENU_btn_vector_data_descriptor * start_data_descriptor = &start_data_descriptor_data;

	start_data_descriptor->is_unit_postfix = 1;
	start_data_descriptor->unit = " min";
	start_data_descriptor->input_question = "Enter the counter time in minutes: ";

	MENU_add_btn_vector(start_count, "Counter Start", start_data_descriptor);

	// ctr_start(2,0);
	serial_init();

    // TimerA_UART_print("\x1B[2JLB001 USB - READY.\r\n");

	// set output pin: P1.0
	P1DIR |= BIT0;
	P1SEL &= ~BIT0;
	P1SEL2 &= ~BIT0;

	unsigned char i;

	while(1)
	{
		check_input();
		// Set output state
		if(CTR_ON != (FLASH_FLAGS & 0x01))
		{
			P1OUT |= BIT0;
		}
		else
		{
			P1OUT &= ~BIT0;
		}
		if(CTR_BEEPTRIGGER)
		{
			CTR_BEEPTRIGGER = 0;
			LED_off();
			beep();
		}
		if(CTR_DISP)
		{
			LED_MINUTE = CTR_MIN;
			LED_SECOND = CTR_SEC;
			LED_FLAGS = LED_EN_MIN + LED_EN_SEC + LED_UD + LED_LD;
			/*
			if(prev_min != CTR_MIN || prev_sec != CTR_SEC)
			{
				TimerA_UART_tx((CTR_MIN / 10) + 0x30);
				TimerA_UART_tx((CTR_MIN % 10) + 0x30);
				TimerA_UART_tx(0x3A);
				TimerA_UART_tx((CTR_SEC / 10) + 0x30);
				TimerA_UART_tx((CTR_SEC % 10) + 0x30);
				TimerA_UART_tx(0x0D);
				prev_min = CTR_MIN;
				prev_sec = CTR_SEC;
			}
			*/
		}
		else
		{
			LED_MINUTE = 0;
			LED_SECOND = 0;
			LED_FLAGS = 0;
			/*
			prev_min = 0;
			prev_sec = 0;
			*/
		}
		LED_displaydigit();
		// button handling
		buttonvalue = BTN_read();
		for(i=0;i<4;i++)
		{
			if((buttonstate & (1 << i)) == 0 && (buttonvalue & (1 << i)) > 0)
			{
				// ctr_stop();
				start_count_value = FLASH_BTN_DATA[i];
				FLASH_BTN_FUNC[i]();
			}
		}
		buttonstate = buttonvalue;
		_delay_cycles(2000);
	}

/*
	unsigned char buttons;
	buttons = BTN_read();
	LED_MINUTE = (buttons & 0x80 ? 10 : 0) + (buttons & 0x40 ? 1 : 0);
	LED_SECOND = (buttons & 0x20 ? 10 : 0) + (buttons & 0x10 ? 1 : 0);
	LED_displaydigit();
*/
/*
	unsigned char buttons;
	while(1)
	{
		buttons = BTN_read();
		LED_FLAGS = LED_EN_MIN + LED_EN_SEC;
		// LED_MINUTE = 0;
		// LED_SECOND = 0;
		LED_MINUTE = (buttons & 8 ? 10 : 0) + (buttons & 4 ? 1 : 0);
		LED_SECOND = (buttons & 2 ? 10 : 0) + (buttons & 1 ? 1 : 0);
		LED_displaydigit();
		_delay_cycles(2000);
	}
*/
	return 0;
}
