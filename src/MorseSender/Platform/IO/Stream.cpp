/*
 * Stream.cpp
 */ 

#include "Stream.h"

using namespace Platform::IO;

void Stream::Send(char data)
{
	SendByte(data);
}

void Stream::Send(uchar data)
{
	SendByte(data);
}

void Stream::Send(uint data)
{
	char str[10];
	sprintf(str,"%u", data);
	Send(str);
}

void Stream::Send(const char* data)
{
	while (*data)
	{
		SendByte(*data++);
	}
}

void Stream::Send(const uchar* data)
{
	while (*data)
	{
		SendByte(*data++);
	}
}

uchar Stream::Receive()
{
	return ReceiveByte();
}

size_t Stream::Receive(uchar* buffer, size_t buffer_len)
{
	for(size_t i = 0; i < buffer_len; i++)
	{
		buffer[i] = 0;
	}
	
	size_t index = 0;
	while(index < buffer_len)
	{
		uchar symbol = ReceiveByte();
		if(symbol == '\n')
		{
			break;
		}
		
		buffer[index] = symbol;
		index++;
	}
	
	index--;
	return index;
}
