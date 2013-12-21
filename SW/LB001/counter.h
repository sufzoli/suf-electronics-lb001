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
extern unsigned char CTR_DISP;

void ctr_init();
void ctr_up();
void ctr_down();
void ctr_stop();
void ctr_start(unsigned char min, unsigned char sec);

#endif /* COUNTER_H_ */
