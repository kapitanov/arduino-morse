/*
 * String.h
 */ 
#pragma once

#include "Types.h"

namespace Platform
{
	class String
	{
	protected:
		String() { }
	public:
		virtual ~String() { }
	
		virtual Char*		GetPointer() = 0;
		virtual const Char*	GetPointer() const = 0;
		virtual				Platform::UInt GetBufferLength() const = 0;
		Platform::UInt		GetLength() const;
		
		Char& operator[](Platform::UInt index);
		const Char& operator[](Platform::UInt index) const;
		
		class Iterator
		{
		public:
			bool CanMoveNext();
			bool MoveNext();
			Char Current();
			
		private:
			friend class String;
			
			explicit Iterator(const String& str);
			
			const String&	str_;
			int				index_;
		};
		
		Iterator GetIterator() const;
		
		void Clear();
	};
	
	template<int Size>
	class StaticString : public String
	{
	public:
		StaticString() 
			: buffer_({0}) 
		{ }
		
		virtual Char* GetPointer()
		{
			return &buffer_[0];
		}
		
		virtual const Char*	GetPointer() const
		{
			return buffer_;
		}
		
		virtual Platform::UInt GetBufferLength() const
		{
			return Size;
		}
		
	private:
		Char buffer_[Size];
	};
}
