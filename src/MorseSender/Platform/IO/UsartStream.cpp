/*
* UsartStream.cpp
*/

#include "UsartStream.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>

using namespace Platform::IO;

UsartStream::UsartStream(uint ubrr)
{
	/*Set baud rate */
	UBRR0H = (uchar)(ubrr>>8);
	UBRR0L = (uchar)ubrr;
	//Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void UsartStream::SendByte(uchar data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) ) 	{ }
	/* Put data into buffer, sends the data */
	UDR0 = char(data);
}

uchar UsartStream::ReceiveByte()
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) ) { }
	/* Get and return received data from buffer */
	return UDR0;
}