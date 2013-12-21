/*
 * systime.c
 *
 *  Created on: 2013.05.02.
 *      Author: zoli
 */

#include <msp430.h>

unsigned int SYSTIME_DCO_CLOCK = 0;

void set_dco(unsigned int dco_clk)
{
	SYSTIME_DCO_CLOCK = dco_clk;
	switch(dco_clk)
	{
		case 1:
			DCOCTL = 0;
			BCSCTL1 = CALBC1_1MHZ;
			DCOCTL = CALDCO_1MHZ;
			break;
// #ifdef CALDCO_8MHZ
		case 8:
			DCOCTL = 0;
			BCSCTL1 = CALBC1_8MHZ;
			DCOCTL = CALDCO_8MHZ;
			break;
//#endif
//#ifdef CALDCO_12MHZ
		case 12:
			DCOCTL = 0;
			BCSCTL1 = CALBC1_12MHZ;
			DCOCTL = CALDCO_12MHZ;
			break;
//#endif
//#ifdef CALDCO_16MHZ
		case 16:
			DCOCTL = 0;
			BCSCTL1 = CALBC1_16MHZ;
			DCOCTL = CALDCO_16MHZ;
			break;
//#endif
		default:
			DCOCTL = 0;
			BCSCTL1 = CALBC1_1MHZ;
			DCOCTL = CALDCO_1MHZ;
			SYSTIME_DCO_CLOCK = 1;
			break;
	}
}

void timer_a_i2c_100k()
{
	// BIT 9-8 - 10 SMCLK input
	// BIT 7-6 - 00 Input divide by 1
	// BIT 5-4 - 01 Up. Timer counts up to TACCR0
	// BIT   2 - Timer_A clear: no
	// BIT   1 - TAIE - Timer interrupt disabled
	TACTL = TASSEL1 + MC0;

	TACCR0 = SYSTIME_DCO_CLOCK * 10;
	TACCR1 = SYSTIME_DCO_CLOCK * 5;

	TACCTL0 = OUTMOD_3;
}

