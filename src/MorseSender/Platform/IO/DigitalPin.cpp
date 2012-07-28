/*
* Digital.cpp
*/

#include "DigitalPin.h"
#include "..\Impl\IO\DigitalPin.h"

#ifdef DEBUG
#include "..\Diagnostics.h"
#endif

using namespace Platform::IO;

DigitalPin::DigitalPin(Pin pin)
	: pin_(pin),
	  bitmask_(Platform::Impl::IO::Bitmask(pin))
{ }

DigitalPin::DigitalPin(Pin pin, PinMode mode)
	: pin_(pin),
	  bitmask_(Platform::Impl::IO::Bitmask(pin))
{
	Mode(mode);
}

PinMode DigitalPin::Mode()
{
	Address ddr_port = Platform::Impl::IO::DdrPort(pin_);
	bool is_ddr_set = Platform::Impl::IO::ReadBit(ddr_port, bitmask_);
	if(is_ddr_set)
	{
		return WRITE;
	}
	
	Address out_port = Platform::Impl::IO::OutputPort(pin_);
	bool is_out_set = Platform::Impl::IO::ReadBit(out_port, bitmask_);
	
	if(is_out_set)
	{
		return READ_PULLUP;
	}
	
	return READ;
}

void DigitalPin::Mode(PinMode mode)
{
	Address ddr_port = Platform::Impl::IO::DdrPort(pin_);
	Address out_port = Platform::Impl::IO::OutputPort(pin_);
	
	switch(mode)
	{
	case READ:
		Platform::Impl::IO::ClearBit(ddr_port, bitmask_);
		Platform::Impl::IO::ClearBit(out_port, bitmask_);
		break;
	
	case WRITE:
		Platform::Impl::IO::SetBit(ddr_port, bitmask_);
		Platform::Impl::IO::ClearBit(out_port, bitmask_);
		break;
	
	case READ_PULLUP:
		Platform::Impl::IO::ClearBit(ddr_port, bitmask_);
		Platform::Impl::IO::SetBit(out_port, bitmask_);
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

	Address out_port = Platform::Impl::IO::OutputPort(pin_);
	switch (value)
	{
		case HIGH:
			Platform::Impl::IO::SetBit(out_port, bitmask_);
			break;
		case LOW:
			Platform::Impl::IO::ClearBit(out_port, bitmask_);
			break;
	}
}

DigitalValue DigitalPin::Read()
{
	#ifdef DEBUG
	AssertCanRead();
	#endif
	
	Address in_port = Platform::Impl::IO::InputPort(pin_);
	return Platform::Impl::IO::ReadBit(in_port, bitmask_);
}

void DigitalPin::Pulse(DigitalValue peak)
{
	Address out_port = Platform::Impl::IO::OutputPort(pin_);
	switch (peak)
	{
	case HIGH:
		Platform::Impl::IO::ClearBit(out_port, bitmask_);
		Platform::Impl::IO::SetBit(out_port, bitmask_);
		Platform::Impl::IO::ClearBit(out_port, bitmask_);
		break;
		
	case LOW:
		Platform::Impl::IO::SetBit(out_port, bitmask_);
		Platform::Impl::IO::ClearBit(out_port, bitmask_);
		Platform::Impl::IO::SetBit(out_port, bitmask_);
		break;
	}
}

void DigitalPin::Toggle()
{
	#ifdef DEBUG
	AssertCanWrite();
	#endif
		
	Address out_port = Platform::Impl::IO::OutputPort(pin_);
	bool state = Platform::Impl::IO::ReadBit(out_port, bitmask_);
	
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