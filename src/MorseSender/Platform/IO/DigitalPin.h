/*
 * Digital.h
 */ 
#pragma once

#include "..\Types.h"
#include "Pins.h"
#include <stdio.h>

namespace Platform
{
	namespace IO
	{
		class DigitalPin
		{
		public:
	
			explicit DigitalPin(Pin pin);
			DigitalPin(Pin p, PinMode mode);
	
			PinMode Mode();
			void Mode(PinMode mode);
	
			void Clear();
			void Set();
	
			void		 Write(DigitalValue value);
			DigitalValue Read();
	
			void Pulse(DigitalValue peak = HIGH);
			
			void Toggle();
	
			typedef uint16_t			Port;
			typedef uint8_t				Bitmask;
			typedef volatile uint8_t*	Address;
			
		private:
			const Pin					pin_;
			const Bitmask				bitmask_;
			
			#ifdef DEBUG
			
			void AssertCanRead();
			void AssertCanWrite();
			
			#endif
		};
	}
}