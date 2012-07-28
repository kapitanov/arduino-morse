/*
 * SerialLedDisplay.cpp
 */ 

#include "SerialLedDisplay.h"

using namespace Platform::IO;
using namespace Platform::Devices;

SerialLedDisplay::SerialLedDisplay(Pin clock_pin, Pin reset_pin)
	: clock_pin_(clock_pin, WRITE),
	  reset_pin_(reset_pin, WRITE)
{
	Reset();
}	

void SerialLedDisplay::Reset()
{
	reset_pin_.Pulse();
}

void SerialLedDisplay::Increment()
{
	Tick();
}

void SerialLedDisplay::Add(uint16_t value)
{
	for(uint16_t i = 0; i < value; i++)
	{
		Increment();
	}
}

void SerialLedDisplay::Show(uint16_t value)
{
	Reset();
	Add(value);
}

void SerialLedDisplay::Tick()
{
	clock_pin_.Pulse();
}