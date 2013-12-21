/*
 * MCP23017.c
 *
 *  Created on: 2013.11.01.
 *      Author: zoli
 */
#include "i2c_usi.h"
#include "MCP23017.h"

void MCP_init(unsigned char initialize_i2c, char pullup_i2c)
{
	if(initialize_i2c)
	{
		i2c_init(pullup_i2c);
	}
	// Init Bank 1
	MCP_Write(0x0A,0xA0);

	// Initialize I/O (maybe put it somewhere else)
	MCP_Write(MCP_IODIRA,0);
	MCP_Write(MCP_IODIRB,0xF0);
	/*
	unsigned char buff[2];
	buff[0] = 0x0A;
	buff[1] = 0xA0;
	i2c_transmit(MCP23017_ADDR, 2, &buff[0]);

	buff[0] = MCP_IODIRA;
	buff[1] = 0;
	i2c_transmit(MCP23017_ADDR, 2, &buff[0]);

	buff[0] = MCP_IODIRB;
	buff[1] = 0xF0;
	i2c_transmit(MCP23017_ADDR, 2, &buff[0]);
	*/

}

void MCP_Write(unsigned char mcpreg, unsigned char value)
{
	unsigned char buff[2];
	buff[0] = mcpreg;
	buff[1] = value;
	i2c_transmit(MCP23017_ADDR, 2, &buff[0]);
}

unsigned char MCP_Read(unsigned char mcpreg)
{
	unsigned char retvalue;
	i2c_reg_read(MCP23017_ADDR, mcpreg, 1, &retvalue);
	return retvalue;
}

