/*
 * Pins.h
 *
 * Created: 28.07.2012 19:18:08
 *  Author: Альберт
 */ 
#pragma once

namespace Platform
{
	namespace IO
	{
		enum PinMode
		{
			READ,
			WRITE,
			READ_PULLUP
		};

		enum DigitalValue
		{
			HIGH,
			LOW
		};

		enum Pin
		{
			D0 = 0x00,
			D1,
			D2,
			D3,
			D4,
			D5,
			D6,
			D7,
			D8,
			D9,
			D10,
			D11,
			D12,
			D13
		};
		
		const int PINS_COUNT = 20;
	}
}