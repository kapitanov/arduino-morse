/*
 * SerialLedDisplay.h
 *
 * Created: 26.07.2012 0:37:42
 *  Author: Альберт
 */ 
#pragma once

#include "..\IO\DigitalPin.h"

namespace Platform
{
	namespace Devices
	{
		class SerialLedDisplay
		{
		public:
			SerialLedDisplay(Platform::IO::Pin clock_pin, Platform::IO::Pin reset_pin);
			
			void Reset();
			
			void Increment();
			void Add(uint16_t value);
			void Show(uint16_t value);
			
		private:
			Platform::IO::DigitalPin clock_pin_;
			Platform::IO::DigitalPin reset_pin_;
			
			void Tick();
		};
	}
}