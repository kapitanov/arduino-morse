/*
 * Morse.h
 *
 * Created: 22.07.2012 15:18:06
 *  Author: Альберт
 */ 
#pragma once
#include "Platform/Types.h"
#include <stdio.h>

class Morse
{
private:
	Morse() { }
	
public:
	typedef const uchar Char;

	static Char LONG;
	static Char SHORT;
	static Char SPACE;
	static Char END;
	
	static const size_t MAX_LENGTH;
	
	class StringIterator;
	
	class String
	{
	public:
		String();
		
		class Iterator
		{
		public:
			bool Next();
			Char Current();
			
		private:
			friend class String;
			
			explicit Iterator(Char* buffer);
			
			Char* buffer_;
			int index_;
			};
			
		String::Iterator GetIterator();
					
		void LoadFromAddress(const size_t address);
		
	private:
		Char buffer_[8];
	};

	static bool Encode(uchar symbol, String& result);
};