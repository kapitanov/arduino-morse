/*
* Digital.cpp
*
* Created: 22.07.2012 21:36:40
*  Author: Альберт
*/

#include "DigitalPin.h"
#include "..\Impl\IO\DigitalPin.h"

#ifdef DEBUG
#include "..\Diagnostics.h"
#endif

using namespace Platform::IO;

DigitalPin::DigitalPin(Pin pin)
	: in_port_(Platform::Impl::IO::InputPort(pin)),
	  out_port_(Platform::Impl::IO::OutputPort(pin)),
	  ddr_port_(Platform::Impl::IO::DdrPort(pin)),
	  bitmask_(Platform::Impl::IO::Bitmask(pin))
{ }

DigitalPin::DigitalPin(Pin pin, PinMode mode)
	: in_port_(Platform::Impl::IO::InputPort(pin)),
	  out_port_(Platform::Impl::IO::OutputPort(pin)),
	  ddr_port_(Platform::Impl::IO::DdrPort(pin)),
	  bitmask_(Platform::Impl::IO::Bitmask(pin))
{
	Mode(mode);
}

PinMode DigitalPin::Mode()
{
	bool is_ddr_set = Platform::Impl::IO::ReadBit(ddr_port_, bitmask_);
	if(is_ddr_set)
	{
		return WRITE;
	}
	
	bool is_out_set = Platform::Impl::IO::ReadBit(out_port_, bitmask_);
	
	if(is_out_set)
	{
		return READ_PULLUP;
	}
	
	return READ;
}

void DigitalPin::Mode(PinMode mode)
{
	switch(mode)
	{
	case READ:
		Platform::Impl::IO::ClearBit(ddr_port_, bitmask_);
		Platform::Impl::IO::ClearBit(out_port_, bitmask_);
		break;
	
	case WRITE:
		Platform::Impl::IO::SetBit(ddr_port_, bitmask_);
		Platform::Impl::IO::ClearBit(out_port_, bitmask_);
		break;
	
	case READ_PULLUP:
		Platform::Impl::IO::ClearBit(ddr_port_, bitmask_);
		Platform::Impl::IO::SetBit(out_port_, bitmask_);
		break;
		
	default:
		return;
	}
}

void DigitalPin::Clear()
{
	Write(LOW);
}

void DigitalPin::Set()
{
	Write(HIGH);
}

void DigitalPin::Write(DigitalValue value)
{
	#ifdef DEBUG
	AssertCanWrite();
	#endif

	switch (value)
	{
		case HIGH:
			Platform::Impl::IO::SetBit(out_port_, bitmask_);
			break;
		case LOW:
			Platform::Impl::IO::ClearBit(out_port_, bitmask_);
			break;
	}
}

DigitalValue DigitalPin::Read()
{
	#ifdef DEBUG
	AssertCanRead();
	#endif
	
	return Platform::Impl::IO::ReadBit(in_port_, bitmask_);
}

void DigitalPin::Pulse(DigitalValue peak)
{
	switch (peak)
	{
	case HIGH:
		Clear();
		Set();
		Clear();
		break;
		
	case LOW:
		Set();
		Clear();
		Set();
		break;
	}
}

void DigitalPin::Toggle()
{
	#ifdef DEBUG
	AssertCanWrite();
	#endif
		
	bool state = Platform::Impl::IO::ReadBit(out_port_, bitmask_);
	
	if(state)
	{
		Clear();
	}
	else
	{
		Set();
	}
}

void DigitalPin::AssertCanRead()
{
	PinMode mode = Mode();
	Platform::Diagnostics::Assert(mode == READ || mode == READ_PULLUP);
}
	
void DigitalPin::AssertCanWrite()
{
	PinMode mode = Mode();
	Platform::Diagnostics::Assert(mode == WRITE);
}