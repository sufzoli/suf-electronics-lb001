/*
 * i2c_usi.h
 *
 *  Created on: 2013.04.25.
 *      Author: zoli
 */

#ifndef I2C_USI_H_
#define I2C_USI_H_

void i2c_init(char int_pullup);

int i2c_slave_present(unsigned char slave_addr, unsigned char rw);
void i2c_transmit(unsigned char slave_addr, unsigned int numchar, unsigned char *buff);
void i2c_reg_read(unsigned char slave_addr, unsigned char reg_addr, unsigned int numchar, unsigned char *buff);

#endif /* I2C_USI_H_ */
