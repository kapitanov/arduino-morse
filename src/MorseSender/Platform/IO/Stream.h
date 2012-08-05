/*
* Stream.h
*/
#pragma once

#include "..\Memory.h"
#include "..\Types.h"
#include "..\String.h"
#include <stdio.h>

namespace Platform
{
	namespace IO
	{
		class Stream
		{
		public:
			virtual ~Stream() { }
			
			void Send(char data);
			void Send(uchar data);
			void Send(uint data);
			void Send(const char* data);
			void Send(const uchar* data);
			void Send(Platform::String& str);
			
			uchar  Receive();
			size_t Receive(uchar* buffer, size_t buffer_len);
			size_t Receive(Platform::String& str);
			
			protected:
			virtual void  SendByte(uchar data) = 0;
			virtual uchar ReceiveByte()        = 0;
		};
	}
}