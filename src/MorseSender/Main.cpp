/*
 * Sender.cpp
 *
 * Created: 22.07.2012 14:56:43
 */ 
#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "Platform/CPU.h"
#include "Platform/Memory.h"
#include "Platform/IO/UsartStream.h"
#include "Platform/Devices/SerialLedDisplay.h"
#include "Platform/IO/DigitalPin.h"
#include "Morse.h"

Platform::IO::UsartStream serial(Platform::CPU::GetUbrr());

void ProcessSymbol(uchar symbol)
{
	Morse::String encoded;
	if(Morse::Encode(symbol, encoded))
	{
		Morse::String::Iterator iterator = encoded.GetIterator();
		while(iterator.Next())
		{
			serial.Send(iterator.Current());
		}
	}
	else
	{
		serial.Send('?');
	}
	
	serial.Send(' ');
}

Platform::Devices::SerialLedDisplay led(Platform::IO::D3, Platform::IO::D2);

Platform::IO::DigitalPin pin(Platform::IO::D7, Platform::IO::WRITE);

int main(void)
{
	led.Reset();
	led.Increment();
	
	bool state = false;
    while(true)
    {
		const size_t recv_buffer_len = 32;
		uchar recv_buffer[recv_buffer_len] = {0};
		
		size_t received_bytes = serial.Receive(recv_buffer, recv_buffer_len);
		
		for(size_t i = 0; i < received_bytes; i++)
		{
			uchar symbol = recv_buffer[i];
			ProcessSymbol(symbol);
		}
		
		serial.Send('\n');
		pin.Toggle();
    }
}