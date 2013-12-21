#include <msp430.h>
#include "i2c_usi.h"
#include "systime.h"
#include "MCP23017.h"
#include "LED.h"
#include "counter.h"
#include "button.h"
#include "flash.h"

/*
 * main.c
 */

void start_5min_count()
{
	ctr_start(5,0);
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    set_dco(16);		// Set 1MHz clock

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

	FLASH_init();

	FLASH_BTN_FUNC[0] = ctr_up;
	FLASH_BTN_FUNC[1] = ctr_down;
	FLASH_BTN_FUNC[2] = ctr_stop;
	FLASH_BTN_FUNC[3] = start_5min_count;

	MCP_init(1, 1);
	BTN_init();

	ctr_init();
	// ctr_start(2,0);

	unsigned char i;

	while(1)
	{
		if(CTR_DISP)
		{
			LED_MINUTE = CTR_MIN;
			LED_SECOND = CTR_SEC;
			LED_FLAGS = LED_EN_MIN + LED_EN_SEC + LED_UD + LED_LD;
		}
		else
		{
			LED_MINUTE = 0;
			LED_SECOND = 0;
			LED_FLAGS = 0;
		}
		LED_displaydigit();
		// button handling
		buttonvalue = BTN_read();
		for(i=0;i<4;i++)
		{
			if((buttonstate & (1 << i)) == 0 && (buttonvalue & (1 << i)) > 0)
			{
				// ctr_stop();
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
