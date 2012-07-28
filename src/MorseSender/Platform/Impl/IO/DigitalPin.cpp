/*
* DigitalPinImpl.cpp
*/
#include "DigitalPin.h"
#include <avr/io.h>
#include <avr/pgmspace.h>

using namespace Platform::Impl::IO;
using namespace Platform::IO;

namespace Platform
{
	namespace Hardware
	{
		/* Maps DigitalPin::Pin -> IO bitmask */
		#define BIT(bit) (1 << (bit))
		const DigitalPin::Bitmask PROGMEM Bitmasks[PINS_COUNT] =
		{
			/* PORT D */
			BIT(0),	// 0
			BIT(1),
			BIT(2),
			BIT(3),
			BIT(4),
			BIT(5),
			BIT(6),
			BIT(7),
			/* PORT B */
			BIT(0),	// 8
			BIT(1),
			BIT(2),
			BIT(3),
			BIT(4),
			BIT(5),
			/* PORT C */
			BIT(0),	// 14
			BIT(1),
			BIT(2),
			BIT(3),
			BIT(4),
			BIT(5)
		};
		#undef BIT

		/* Maps DigitalPin::Pin -> Input port address */
		#define InputPort(port) (DigitalPin::Port)(&PIN##port)
		const DigitalPin::Port PROGMEM InputPorts[PINS_COUNT] =
		{
			/* PORT D */
			InputPort(D),	// 0
			InputPort(D),
			InputPort(D),
			InputPort(D),
			InputPort(D),
			InputPort(D),
			InputPort(D),
			InputPort(D),
			/* PORT B */
			InputPort(B),	// 8
			InputPort(B),
			InputPort(B),
			InputPort(B),
			InputPort(B),
			InputPort(B),
			/* PORT C */
			InputPort(C),	// 14
			InputPort(C),
			InputPort(C),
			InputPort(C),
			InputPort(C),
			InputPort(C)
		};
		#undef InputPort

		/* Maps DigitalPin::Pin -> Output port address */
		#define OutputPort(port)		(DigitalPin::Port)(&PORT##port)
		const DigitalPin::Port PROGMEM OutputPorts[PINS_COUNT] =
		{
			/* PORT D */
			OutputPort(D),	// 0
			OutputPort(D),
			OutputPort(D),
			OutputPort(D),
			OutputPort(D),
			OutputPort(D),
			OutputPort(D),
			OutputPort(D),
			/* PORT B */
			OutputPort(B),	// 8
			OutputPort(B),
			OutputPort(B),
			OutputPort(B),
			OutputPort(B),
			OutputPort(B),
			/* PORT C */
			OutputPort(C),	// 14
			OutputPort(C),
			OutputPort(C),
			OutputPort(C),
			OutputPort(C),
			OutputPort(C)
		};
		#undef OutputPort

		/* Maps DigitalPin::Pin -> Config port address */
		#define DdrPort(port)		(DigitalPin::Port)(&DDR##port)
		const DigitalPin::Port PROGMEM DdrPorts[PINS_COUNT] =
		{
			/* PORT D */
			DdrPort(D),	// 0
			DdrPort(D),
			DdrPort(D),
			DdrPort(D),
			DdrPort(D),
			DdrPort(D),
			DdrPort(D),
			DdrPort(D),
			/* PORT B */
			DdrPort(B),	// 8
			DdrPort(B),
			DdrPort(B),
			DdrPort(B),
			DdrPort(B),
			DdrPort(B),
			/* PORT C */
			DdrPort(C),	// 14
			DdrPort(C),
			DdrPort(C),
			DdrPort(C),
			DdrPort(C),
			DdrPort(C)
		};
		#undef DdrPort
	}
}

namespace Platform
{
	namespace Impl
	{
		namespace IO
		{
			DigitalPin::Address InputPort(Pin pin)
			{
				return reinterpret_cast<DigitalPin::Address>(pgm_read_word(&Platform::Hardware::InputPorts[pin]));
			}

			DigitalPin::Address OutputPort(Pin pin)
			{
				return reinterpret_cast<DigitalPin::Address>(pgm_read_word(&Platform::Hardware::OutputPorts[pin]));
			}

			DigitalPin::Address DdrPort(Pin pin)
			{
				return reinterpret_cast<DigitalPin::Address>(pgm_read_word(&Platform::Hardware::DdrPorts[pin]));
			}

			DigitalPin::Bitmask Bitmask(Pin pin)
			{
				return static_cast<DigitalPin::Bitmask>(pgm_read_byte(&Platform::Hardware::Bitmasks[pin]));
			}

			void SetBit(DigitalPin::Address address, DigitalPin::Bitmask bitmask)
			{
				uint8_t value = *address;
				value |= bitmask;
				*address = value;
			}

			void ClearBit(DigitalPin::Address address, DigitalPin::Bitmask bitmask)
			{
				uint8_t value = *address;
				value &= ~bitmask;
				*address = value;
			}

			DigitalValue ReadBit(DigitalPin::Address address, DigitalPin::Bitmask bitmask)
			{
				return static_cast<DigitalValue>((*address) & bitmask);
			}
		}
	}
}