/*
 * systime.h
 *
 *  Created on: 2013.05.02.
 *      Author: zoli
 */

#ifndef SYSTIME_H_
#define SYSTIME_H_

extern unsigned int SYSTIME_DCO_CLOCK;
void set_dco(unsigned int dco_clk);
void timer_a_i2c_100k();

#endif /* SYSTIME_H_ */
