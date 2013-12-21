/*
 * MCP23017.h
 *
 *  Created on: 2013.11.01.
 *      Author: zoli
 */

#ifndef MCP23017_H_
#define MCP23017_H_

#define MCP23017_ADDR	0x20

#define MCP_IODIRA		0x00
#define MCP_IODIRB		0x10
#define MCP_IPOLA		0x01
#define MCP_IPOLB		0x11
#define MCP_GPINTENA	0x02
#define MCP_GPINTENB	0x12
#define MCP_DEFVALA		0x03
#define MCP_DEFVALB		0x13
#define MCP_INTCONA		0x04
#define MCP_INTCONB		0x14
#define MCP_IOCON		0x05
#define MCP_GPPUA		0x06
#define MCP_GPPUB		0x16
#define MCP_INTFA		0x07
#define MCP_INTFB		0x17
#define MCP_INTCAPA		0x08
#define MCP_INTCAPB		0x18
#define MCP_GPIOA		0x09
#define MCP_GPIOB		0x19
#define MCP_OLATA		0x0A
#define MCP_OLATB		0x1A

/*
#define MCP_IODIRA	0x00
#define MCP_IODIRB	0x01
#define MCP_GPIOA	0x12
#define MCP_GPIOB	0x13
*/


void MCP_init(unsigned char initialize_i2c, char pullup_i2c);
void MCP_Write(unsigned char mcpreg, unsigned char value);
unsigned char MCP_Read(unsigned char mcpreg);


#endif /* MCP23017_H_ */
