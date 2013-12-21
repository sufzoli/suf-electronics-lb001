/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/

/*
 * i2c_usi.c
 *
 *  Created on: 2013.04.25.
 *      Author: zoli
 */

#include <msp430.h>
#include "systime.h"


// depricated definitions

// #define number_of_TX_bytes 2                // How many bytes do you want to TX?
// #define number_of_RX_bytes 3                // How many bytes do you want to RX?
// char MST_Data = 0x55;                       // Variable for transmitted data
// char SLV_Addr = 0x90;



// Internal variables

unsigned char _I2C_SLAVE;	// Target address without the R/W bit
unsigned char _I2C_OPERATION = 0;	// 0 - Receive
									// 1 - Transmit
									// 2 - Slave Present (Read) - Used in address scan
									// 3 - Slave Present (Write) - Used in address scan
int _I2C_SLAVE_PRESENT = -1;	// Used by the SLAVE_PRESENT or bus scan function
unsigned char *_I2C_BUFFPTR;


int _I2C_State, _I2C_BYTECOUNT, _I2C_NUMBYTES, _I2C_RPT_START = 0;

// Internal function definitions

void Data_TX (void);
void Data_RX (void);

// Public functions
void i2c_init(char int_pullup)
{
	if(SYSTIME_DCO_CLOCK == 0)			// If system clock is not initialized by systime.c roiutines
	{
		set_dco(1);						// set DCO to 1MHz
	}
	timer_a_i2c_100k();					// set timer to provide 100kHz I2C clock
	if(int_pullup)						// setup internal pullup
	{
		P1OUT |= 0xC0;                  // P1.6 & P1.7 Pullups
		P1REN |= 0xC0;                  // P1.6 & P1.7 Pullups
		P1DIR |= 0xC0;                  // P1.6 & P1.7 as outputs
	}
	_DINT();								// Disable interrupt
	USICTL0 = USIPE6 + USIPE7 + USIMST + USISWRST;  // Port & USI mode setup
	USICTL1 = USII2C + USIIE;                   // Enable I2C mode & USI interrupt
	USICKCTL = USIDIV_1 + USISSEL_5 + USICKPL;    // USI clk: SCL = TACCR0
	USICNT |= USIIFGCC;                       // Disable automatic clear control
	USICTL0 &= ~USISWRST;                     // Enable USI
	USICTL1 &= ~USIIFG;                       // Clear pending flag
	_EINT();
}

int i2c_slave_present(unsigned char slave_addr, unsigned char rw)
{
	_I2C_RPT_START = 0;
	_I2C_SLAVE_PRESENT = -1;
	_I2C_SLAVE = slave_addr;
	_I2C_OPERATION = rw | 2;
    USICTL1 |= USIIFG;                      // Set flag and start communication
    LPM0;                                   // CPU off, await USI interrupt
    return _I2C_SLAVE_PRESENT;
}

void i2c_transmit(unsigned char slave_addr, unsigned int numchar, unsigned char *buff)
{
	_I2C_RPT_START = 0;
	_I2C_SLAVE = slave_addr;
	_I2C_OPERATION = 1;
	_I2C_BUFFPTR = buff;
	_I2C_NUMBYTES = numchar;
    USICTL1 |= USIIFG;                      // Set flag and start communication
    LPM0;                                   // CPU off, await USI interrupt
}

void i2c_reg_read(unsigned char slave_addr, unsigned char reg_addr, unsigned int numchar, unsigned char *buff)
{
	_I2C_RPT_START = 1;
	_I2C_SLAVE = slave_addr;
	_I2C_OPERATION = 1;
	_I2C_BUFFPTR = &reg_addr;
	_I2C_NUMBYTES = 1;
    USICTL1 |= USIIFG;                      // Set flag and start communication
    LPM0;                                   // CPU off, await USI interrupt
	_I2C_RPT_START = 0;
	_I2C_SLAVE = slave_addr;
	_I2C_OPERATION = 0;
	_I2C_BUFFPTR = buff;
	_I2C_NUMBYTES = numchar;
    USICTL1 |= USIIFG;                      // Set flag and start communication
    LPM0;                                   // CPU off, await USI interrupt
}


/******************************************************
// USI interrupt service routine
// Data Transmit : state 0 -> 2 -> 4 -> 10 -> 12 -> 14
// Data Recieve  : state 0 -> 2 -> 4 -> 6 -> 8 -> 14
******************************************************/
#pragma vector = USI_VECTOR
__interrupt void USI_TXRX (void)
{
	switch(__even_in_range(_I2C_State,14))
    {
		case 0: // Generate Start Condition & send address to slave
			_I2C_BYTECOUNT = 0;
			USISRL = 0x00;              		// Generate Start Condition...
			USICTL0 |= USIGE+USIOE;
			USICTL0 &= ~USIGE;

			USISRL = (_I2C_SLAVE << 1) + ((_I2C_OPERATION & 1) ? 0 : 1);	// I2C Address puls R/W bit
            USICNT = (USICNT & 0xE0) + 0x08;	// Bit counter = 8, TX Address
            _I2C_State = 2;                		// next state: rcv address (N)Ack
            break;

		case 2: // Receive Address Ack/Nack bit
			USICTL0 &= ~USIOE;            		// SDA = input
			USICNT |= 0x01;               		// Bit counter=1, receive (N)Ack bit
			_I2C_State = 4;                		// Go to next state: check (N)Ack
			break;

		case 4: // Process Address Ack/Nack & handle data TX
			switch(_I2C_OPERATION)
			{
				case 0: // receive
		               if (USISRL & 0x01)            	// If Nack received
		               { // Prep Stop Condition
		            	   USICTL0 |= USIOE;
		            	   USISRL = 0x00;
		            	   USICNT |=  0x01;            	// Bit counter= 1, SCL high, SDA low
		            	   _I2C_State = 8;              	// Go to next state: generate Stop
		               }
		               else
		               { // Ack received, Read data
		            	   Data_RX();
		               }
					break;
				case 1: // transmit
	            	USICTL0 |= USIOE;             	// SDA = output
	            	if (USISRL & 0x01)            	// If Nack received...
	            	{ // Send stop...
	            		USISRL = 0x00;
	            		USICNT |=  0x01;            // Bit counter=1, SCL high, SDA low
	            		_I2C_State = 14;            // Go to next state: generate Stop
	            	}
	            	else
	            	{ // Ack received, TX data to slave...
	            		USISRL = *(_I2C_BUFFPTR + _I2C_BYTECOUNT);	// Put the data to the shift register
	            		USICNT |=  0x08;            // Bit counter = 8, start TX
	            		_I2C_State = 10;       		// next state: receive data (N)Ack

	            		_I2C_BYTECOUNT++;
	            		break;
	            	}
					break;
				case 2: // slave present (Read)
		               if (USISRL & 0x01)            	// If Nack received
		               {
		            	   _I2C_SLAVE_PRESENT = 0;
		               }
		               else
		               {
		            	   _I2C_SLAVE_PRESENT = 1;
		               }
		               // Prepare stop condition
					   USICTL0 |= USIOE;
					   USISRL = 0x00;
					   USICNT |=  0x01;            	// Bit counter= 1, SCL high, SDA low
	            	   _I2C_State = 14;              	// Go to next state: generate Stop
					break;
				case 3: // slave present (Write)
		               if (USISRL & 0x01)            	// If Nack received
		               {
		            	   _I2C_SLAVE_PRESENT = 0;
		               }
		               else
		               {
		            	   _I2C_SLAVE_PRESENT = 1;
		               }
		               // Prepare stop condition
					   USICTL0 |= USIOE;
					   USISRL = 0x00;
					   USICNT |=  0x01;            	// Bit counter= 1, SCL high, SDA low
	            	   _I2C_State = 8;              	// Go to next state: generate Stop
					break;
			}
            break;

		case 6: // Read data, Send Data Ack/Nack bit
			// Data available - put into the buffer
			*(_I2C_BUFFPTR + _I2C_BYTECOUNT) = USISRL;
			USICTL0 |= USIOE;             		// SDA = output
            if (_I2C_BYTECOUNT <= _I2C_NUMBYTES-2)
            {	// If this is not the last byte
            	USISRL = 0x00;              	// Send Ack
                _I2C_State = 4;              	// Go to next state: data/rcv again
                _I2C_BYTECOUNT++;
            }
            else
            {	//last byte: send NACK
                USISRL = 0xFF;              	// Send NAck
                _I2C_State = 8;              	// stop condition
            }
            USICNT |= 0x01;               		// Bit counter = 1, send (N)Ack bit
            break;

		case 8: // Prep Stop Condition
			USICTL0 |= USIOE;             		// SDA = output
			USISRL = 0x00;
			USICNT |=  0x01;              		// Bit counter= 1, SCL high, SDA low
			_I2C_State = 14;               		// Go to next state: generate Stop
			break;

		case 10: // Receive Data Ack/Nack bit
			USICTL0 &= ~USIOE;            		// SDA = input
			USICNT |= 0x01;               		// Bit counter = 1, receive (N)Ack bit
			_I2C_State = 12;               		// Go to next state: check (N)Ack
			break;

		case 12: // Process Data Ack/Nack & send Stop
			USICTL0 |= USIOE;
			if (_I2C_BYTECOUNT == _I2C_NUMBYTES)
			{	// If last byte
				if(_I2C_RPT_START == 1)
				{
					USISRL = 0xFF;             	// this will prevent a stop condition
					USICTL0 |= USIOE;           // SDA = output
				}
				else
				{
					USISRL = 0x00;
				}
				_I2C_State = 14;               	// Go to next state: generate Stop
				USICNT |=  0x01;        		// set count=1 to trigger next state
			}
			else
			{
				Data_TX();                  // TX byte
			}
			break;

      case 14:// Generate Stop Condition
    	  USISRL = 0x0FF;               // USISRL = 1 to release SDA
    	  USICTL0 |= USIGE;             // Transparent latch enabled
    	  USICTL0 &= ~(USIGE+USIOE);    // Latch/SDA output disabled
    	  _I2C_State = 0;                // Reset state machine for next xmt
    	  LPM0_EXIT;                    // Exit active for next transfer
    	  break;
    }
	USICTL1 &= ~USIIFG;                       // Clear pending flag
}


void Data_TX (void)
{
	// Send data byte
	USISRL = *(_I2C_BUFFPTR + _I2C_BYTECOUNT);
	USICNT |=  0x08;              // Bit counter = 8, start TX
	_I2C_State = 10;               // next state: receive data (N)Ack
	_I2C_BYTECOUNT++;
}

void Data_RX (void)
{
	USICTL0 &= ~USIOE;                  // SDA = input --> redundant
	USICNT |=  0x08;                    // Bit counter = 8, RX data
	_I2C_State = 6;                      // Next state: Test data and (N)Ack
}

