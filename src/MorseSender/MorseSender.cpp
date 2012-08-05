/*
 * Main.cpp
 */ 
#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "Platform/CPU.h"
#include "Platform/Memory.h"
#include "Platform/String.h"
#include "Platform/IO/UsartStream.h"
#include "Platform/Devices/SerialLedDisplay.h"
#include "Platform/IO/DigitalPin.h"
#include "Morse.h"

Platform::IO::UsartStream serial(Platform::CPU::GetUbrr());

void ProcessSymbol(uchar symbol)
{
	Morse::Output encoded;
	if(Morse::Encode(symbol, encoded))
	{
		Platform::String::Iterator iterator = encoded.GetIterator();
		while(iterator.MoveNext())
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

Platform::Devices::SerialLedDisplay led(Platform::IO::D2, Platform::IO::D3);
Platform::IO::DigitalPin pin(Platform::IO::D7, Platform::IO::WRITE);

int main(void)
{
	led.Reset();
	led.Increment();
	
	bool state = false;
    while(true)
    {
		Platform::StaticString<128> recv_buffer;
		size_t received_bytes = serial.Receive(recv_buffer);
		
		Morse::StringType type = Morse::DetermineType(recv_buffer);
		switch(type)
		{
			case Morse::MORSE:
				{
					Platform::StaticString<32> result_buffer;
					Morse::Decode(recv_buffer, result_buffer);
					serial.Send(result_buffer);
				}
				break;
				
			case Morse::TEXT:
				for(size_t i = 0; i < received_bytes; i++)
				{
					uchar symbol = recv_buffer[i];
					ProcessSymbol(symbol);
				}
				break;
				
			default:
				serial.Send('?');
				break;
		}
		serial.Send('\n');
		pin.Toggle();
    }
}