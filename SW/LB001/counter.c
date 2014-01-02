/*
 * counter.c
 *
 *  Created on: 2013.11.03.
 *      Author: zoli
 */
#include <msp430.h>
#include "counter.h"
#include "menu.h"

unsigned char FLASH_CTR_DELAY = 5;

unsigned char CTR_DISP = 0;		// True if the counter display should be on (used in blinking of the display)
unsigned char CTR_ON = 0;		// True if the counter is switched on
unsigned char CTR_BEEPTRIGGER = 0;
unsigned char CTR_DELAY = 0;
unsigned char CTR_RUNNING = 0;
unsigned char CTR_MIN = 0;
unsigned char CTR_SEC = 0;

unsigned char _ctr_wdt_count = 0;


// Setup the Watchdog timer
void CTR_init()
{
	MENU_add_btn_vector(CTR_up, "Counter Up", 0);
	MENU_add_btn_vector(CTR_down, "Counter Down", 0);
	MENU_add_btn_vector(CTR_stop, "Counter Stop", 0);

	// Setup Watchdog timer to provide the measurement time
    // WDTSSEL -  1 - Source ACLK (~12 kHz VLO)
	// WDTISx -  01 - clock/8192 (4 Hz)
    // WDTTMSEL - 1 - Interval mode
    WDTCTL = WDTPW | WDTSSEL | WDTTMSEL | WDTIS0;
    IE1 |= WDTIE; // Enable WDT interrupt
    _EINT();	// Enable interrupts
}

void CTR_up()
{
	CTR_BEEPTRIGGER = 0;
	CTR_DELAY = FLASH_CTR_DELAY;
	CTR_MIN++;
/*
	if(CTR_SEC == 0)
	{
		CTR_MIN++;
	}
*/
	CTR_SEC = 0;
}

void CTR_down()
{
	CTR_BEEPTRIGGER = 0;
	if(CTR_SEC > 0)
	{
		CTR_SEC = 0;
	}
	else
	{
		if(CTR_MIN > 0)
		{
			CTR_MIN--;
		}
	}
	if(CTR_MIN > 0 || CTR_SEC > 0)
	{
		CTR_DELAY = FLASH_CTR_DELAY;
	}
	else
	{
		// Stop condition
		CTR_RUNNING = 0;
		CTR_DISP = 0;
		CTR_ON = 0;
	}
}

void CTR_start(unsigned char min, unsigned char sec)
{
	CTR_ON = 1;
	CTR_MIN = min;
	CTR_SEC = sec;
	CTR_RUNNING = 1;
	CTR_BEEPTRIGGER = 0;
}

void CTR_stop()
{
	// Stop condition
	CTR_MIN = 0;
	CTR_SEC = 0;
	CTR_RUNNING = 0;
	CTR_DISP = 0;
	CTR_ON = 0;
}

// Watchdog timer interrupt
// Schedule the measurement operation
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	// reset WDT
	WDTCTL = WDTPW | WDTSSEL | WDTTMSEL | WDTCNTCL | WDTIS0;

	if(_ctr_wdt_count >= 4)
	{

		// Counter delayed startup (the delay counter also start when up or down event occured)
		if(CTR_DELAY > 0)
		{
			CTR_RUNNING = 0;	// Stop the counter
			CTR_DELAY--;
			CTR_DISP = 1; // Switch the display on
			if(CTR_DELAY == 0)
			{
				CTR_DISP = 1;
				CTR_RUNNING = 1; // Start the counter
			}
		}

		if(CTR_RUNNING)
		{
			CTR_ON = 1;	// Switch the counter on
			CTR_DISP = 1; // Switch the display on
			if(CTR_SEC > 0)
			{
				CTR_SEC--;
			}
			else
			{
				if(CTR_MIN > 0)
				{
					CTR_MIN--;
					CTR_SEC = 59;
				}
				else
				{
					// stop condition, timer finished, beep at the end
					// the beep flag should be switched of by the caller
					CTR_RUNNING = 0;
					CTR_DISP = 0;
					CTR_ON = 0;
					CTR_BEEPTRIGGER = 1;
				}
			}
		}
		_ctr_wdt_count = 0;
	}
	else
	{
		_ctr_wdt_count++;
	}
	if(_ctr_wdt_count == 2 && CTR_DELAY > 0)
	{
		CTR_DISP = 0;
	}
	// Clear interrupt
	IFG1 &= ~WDTIFG;
	// Exit low power mode
}
