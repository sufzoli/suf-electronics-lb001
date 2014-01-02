/*
 * counter.h
 *
 *  Created on: 2013.11.03.
 *      Author: zoli
 */

#ifndef COUNTER_H_
#define COUNTER_H_

extern unsigned char CTR_MIN;
extern unsigned char CTR_SEC;
extern unsigned char CTR_RUNNING;
extern unsigned char CTR_ON;
extern unsigned char CTR_DISP;
extern unsigned char CTR_BEEPTRIGGER;


void CTR_init();
void CTR_up();
void CTR_down();
void CTR_stop();
void CTR_start(unsigned char min, unsigned char sec);

#endif /* COUNTER_H_ */
