/*
 * UsartStream.h
 */ 
#pragma once

#include "Stream.h"

namespace Platform
{
	namespace IO
	{
		class UsartStream : public Stream
		{
		public:
			UsartStream(uint ubrr);
	
		protected:
			virtual void SendByte(uchar data);
			virtual uchar ReceiveByte();
		};
	}
}