/*
* DigitalPinImpl.h
*/
#pragma once

#include "..\..\IO\DigitalPin.h"

namespace Platform
{
	namespace Impl
	{
		namespace IO
		{
			Platform::IO::DigitalPin::Address InputPort(Platform::IO::Pin pin);
			Platform::IO::DigitalPin::Address OutputPort(Platform::IO::Pin pin);
			Platform::IO::DigitalPin::Address DdrPort(Platform::IO::Pin pin);
			Platform::IO::DigitalPin::Bitmask Bitmask(Platform::IO::Pin pin);
			
			void SetBit(Platform::IO::DigitalPin::Address address, Platform::IO::DigitalPin::Bitmask bitmask);
			void ClearBit(Platform::IO::DigitalPin::Address address, Platform::IO::DigitalPin::Bitmask bitmask);
			Platform::IO::DigitalValue ReadBit(Platform::IO::DigitalPin::Address address, Platform::IO::DigitalPin::Bitmask bitmask);
		}
	}
}