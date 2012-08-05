/*
* MorseSender.cpp
*/

#include "Morse.h"

#include "Platform/CPU.h"
#include "Platform/IO/UsartStream.h"

#include <avr/pgmspace.h>

namespace Morse
{
	const Platform::Char LONG  = '-';
	const Platform::Char SHORT = '.';
	const Platform::Char SPACE = ' ';
	const Platform::Char END   = '\0';

	const size_t MAX_LENGTH    = 7;

	const Platform::Char MorseTable[][8] PROGMEM =
	{
		  "-----",  // 0
		  ".----",  // 1
		  "..---",  // 2
		  "...--",  // 3
		  "....-",  // 4
		  ".....",  // 5
		  "-....",  // 6
		  "--...",  // 7
		  "---..",  // 8
		  "----.",  // 9
	  
		  "---...", // :
		  ".-.-.-", // ; -> .
		  "--..--", // < -> ,
		  "-...-",  // =
		  "..--.",  // > -> !
		  "..--..", // ?
		  ".-..-.", // @ -> "
	  
		  ".-",     // A
		  "-...",   // B
		  "-.-.",   // C
		  "-..",    // D
		  ".",      // E
		  "..-.",   // F
		  "--.",    // G
		  "....",   // H
	  
		  "..",     // I
		  ".---",   // J
		  "-.-",    // K
		  ".-..",   // L
		  "--",     // M
		  "-.",     // N
		  "---",    // O
		  ".--.",   // P
		  "--.-",   // Q
	  
		  ".-.",    // R
		  "...",    // S
		  "-",      // T
		  "..-",    // U
		  "...-",   // V
		  ".--",    // W
		  "-..-",   // X
		  "-.--",   // Y
		  "--.."    // Z
	};

	const Platform::Char Space[8] = { SPACE };

	bool ConvertSymbol(uchar symbol, uchar& result)
	{
		if(symbol >= '0' && symbol <= 'Z')
		{
			result = symbol;
			return true;
		}		
	
		if(symbol >= 'a' && symbol <= 'z')
		{
			result = symbol - ('a' - 'A');
			return true;
		}		
	
		switch (symbol)
		{
			case ':': result = ':'; break;
			case '.': result = ';'; break;
			case ',': result = '<'; break;
			case '=': result = '='; break;
			case '!': result = '>'; break;
			case '?': result = '?'; break;
			case '"': result = '@'; break;
		
			default: return false;
		}
	
		return true;
	}
	
	bool ConvertSymbolBack(uchar symbol, uchar& result)
	{
		if(symbol >= '0' && symbol <= 'Z')
		{
			result = symbol;
			return true;
		}
		
		if(symbol >= 'a' && symbol <= 'z')
		{
			result = symbol - ('a' - 'A');
			return true;
		}
		
		switch (symbol)
		{
			case ':': result = ':'; break;
			case ';': result = '.'; break;
			case '<': result = ','; break;
			case '=': result = '='; break;
			case '>': result = '!'; break;
			case '?': result = '?'; break;
			case '@': result = '"'; break;
			
			default: return false;
		}
		
		return true;
	}

	const size_t AddressOf(const Platform::Char* address)
	{
		return reinterpret_cast<const size_t>(address);
	}
	
	void LoadFromAddress(const size_t address, Output& result)
	{
		for(size_t i = 0; i < MAX_LENGTH; i++)
		{
			Platform::Char sym = pgm_read_byte(address + i);
			result[i] = sym;
		}
	}

	StringType DetermineType(const Platform::String& str)
	{
		Platform::String::Iterator iterator = str.GetIterator();
		while(iterator.MoveNext())
		{
			Platform::Char ch = iterator.Current();
			if(ch != LONG  &&
			   ch != SHORT &&
			   ch != SPACE)
			{
				return TEXT;
			}
		}
	
		return MORSE;
	}

	bool Encode(uchar symbol, Output& result)
	{
		if(symbol == ' ')
		{
			LoadFromAddress(AddressOf(Space), result);
			return true;
		}

		if(!ConvertSymbol(symbol, symbol))
		{
			return false;
		}

		LoadFromAddress(AddressOf(MorseTable[symbol - '0']), result);
	
		return true;
	}
	
	enum TakeWordResult 
	{
		R_SPACE	= 0x00,
		R_WORD	= 0x01,
		R_EOF	= 0x02
	};

	TakeWordResult TakeMorseWord(Platform::String::Iterator& iterator, Platform::String& buffer)
	{
		buffer.Clear();
		Platform::Int index = 0;
		bool moveNext;
		
		while(moveNext = iterator.MoveNext() && index < MAX_LENGTH)
		{
			Platform::Char ch = iterator.Current();
			
			if(ch == SPACE)
			{
				break;
			}
			
			buffer[index] = ch;
			index++;
		}
		
		if(!moveNext)
		{
			return R_EOF;
		}
		
		if(index > 0)
		{
			return R_WORD;
		}
		
		return R_SPACE;
	}

	Platform::Char FindChar(const Platform::StaticString<8>& buffer)
	{
		for(int index = 0; index < sizeof(MorseTable); index++)
		{
			bool found = true;
			for(int i = 0; i < MAX_LENGTH; i++)
			{
				Platform::Char sym = pgm_read_byte(MorseTable[index] + i);
				if(buffer[i] != sym)
				{
					found = false;
					break;
				}
			}
		
			if(found)
			{
				Platform::Char result;
				if(ConvertSymbolBack(index + '0', result))
				{
					return result;
				}
				
				return '_';
			}
		}
	
		return '?';
	}

	bool Decode(const Platform::String& source, Platform::String& result)
	{
		int index = 0;
		
		Platform::String::Iterator iterator = source.GetIterator();
		while(iterator.CanMoveNext())
		{
			Platform::Char ch;
			
			Platform::StaticString<8> buffer;
			switch(TakeMorseWord(iterator, buffer))
			{
				case R_WORD:
					ch = FindChar(buffer);
					break;
				case R_SPACE:
					ch = ' ';
					break;
				case R_EOF:
					return true;
			}
			
			result[index] = ch;
			index++;
		}
	
		return true;
	}
}