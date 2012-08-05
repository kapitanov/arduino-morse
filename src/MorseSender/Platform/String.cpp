/*
 * String.cpp
 */ 
#include "String.h"

using namespace Platform;

/* Platform::String class */
Platform::UInt String::GetLength() const
{
	Platform::UInt bufferLength = GetBufferLength();
	const Platform::Char* pointer =  GetPointer();
	Platform::UInt i = 0;
	
	for(; i < bufferLength; i++)
	{
		if(pointer[i] == '\0')
		{
			break;
		}
	}
	
	return i;
}

Char& String::operator[](Platform::UInt index)
{
	return GetPointer()[index];
}

const Char& String::operator[](Platform::UInt index) const
{
	return GetPointer()[index];
}

String::Iterator String::GetIterator() const
{
	return String::Iterator(*this);
}

void String::Clear()
{
	Char* buffer = GetPointer();
	UInt length = GetBufferLength();
	for(UInt index = 0; index < length; index++)
	{
		buffer[length] = 0;
	}
}

/* Platform::String::Iterator class */
String::Iterator::Iterator(const String& str)
	: str_(str),
	  index_(-1)
{ }

bool String::Iterator::CanMoveNext()
{
	int index = index_ + 1;
	if(index >= str_.GetBufferLength())
	{
		// End of buffer reached
		return false;
	}
	
	if(str_[index] == 0)
	{
		// End of string reached
		return false;
	}
	
	return true;
}

bool String::Iterator::MoveNext()
{
	if(CanMoveNext())
	{
		index_++;
		return true;
	}
	
	return false;
}

Char String::Iterator::Current()
{
	return str_[index_];
}