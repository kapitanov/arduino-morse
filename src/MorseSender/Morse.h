/*
 * Morse.h
 */ 
#pragma once

#include "Platform/Types.h"
#include "Platform/String.h"
#include <stdio.h>

namespace Morse
{
	extern const Platform::Char LONG;
	extern const Platform::Char SHORT;
	extern const Platform::Char SPACE;
	extern const Platform::Char END;
	
	extern const size_t MAX_LENGTH;
	
	typedef Platform::StaticString<8> Output;
	
	enum StringType
	{
		TEXT	= 0x00,
		MORSE	= 0x01
	};
	
	StringType DetermineType(const Platform::String& str);

	bool Encode(uchar symbol, Output& result);
	
	bool Decode(const Platform::String& source, Platform::String& result);
};