/*
 * MorseSender.cpp
 */ 

#include "Morse.h"
#include <avr/pgmspace.h>

Morse::Char Morse::LONG  = '-';
Morse::Char Morse::SHORT = '.';
Morse::Char Morse::SPACE = ' ';
Morse::Char Morse::END   = '\0';

const size_t Morse::MAX_LENGTH = 7;


Morse::String::String()
	: buffer_({0}) 
{ }
	
Morse::String::Iterator Morse::String::GetIterator()
{
	return Morse::String::Iterator(buffer_);
};

void Morse::String::LoadFromAddress(const size_t address)
{
	uchar* buffer = const_cast<uchar*>(buffer_);
	for(size_t i = 0; i < MAX_LENGTH; i++)
	{
		Morse::Char sym = pgm_read_byte(address + i);
		buffer[i] = sym;
	}
}

Morse::String::Iterator::Iterator(Char* buffer) 
	: buffer_(buffer),
	  index_(-1)
{ }
	
bool Morse::String::Iterator::Next()
{
	index_++;
	if(index_ >= Morse::MAX_LENGTH)
	{
		return false;
	}
	
	if(Current() == Morse::END)
	{
		return false;
	}
	
	return true;
}

Morse::Char Morse::String::Iterator::Current()
{
	return buffer_[index_];
}


static const Morse::Char MorseTable[][8] PROGMEM =
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

static const Morse::Char Space[8] = { Morse::SPACE };

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

const size_t AddressOf(Morse::Char* address)
{
	return reinterpret_cast<const size_t>(address);
}

bool Morse::Encode(uchar symbol, String& result)
{
	if(symbol == ' ')
	{
		result.LoadFromAddress(AddressOf(Space));
		return true;
	}

	if(!ConvertSymbol(symbol, symbol))
	{
		return false;
	}

	result.LoadFromAddress(AddressOf(MorseTable[symbol - '0']));
	
	return true;
}
