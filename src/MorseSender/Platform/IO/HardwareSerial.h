/*
 * HardwareSerial.h
 */ 
#pragma once

#include "Stream.h"
#include "RingBuffer.h"

namespace Platform
{
	namespace IO
	{
		class HardwareSerialStream : public Stream
		{
		public:
			HardwareSerialStream(uint ubrr);
			
			protected:
			virtual void SendByte(uchar data);
			virtual uchar ReceiveByte();
		};
		
		extern HardwareSerialStream HardwareSerial;
		extern RingBuffer* RxBuffer;
		
		void Init();
	}
}