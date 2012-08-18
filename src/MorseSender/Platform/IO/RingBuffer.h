/*
* RingBuffer.h
*/

#pragma once

namespace Platform
{
	namespace IO
	{
		class RingBuffer
		{
		public:
			typedef unsigned char Element;
			typedef unsigned int  Size;
			
			virtual ~RingBuffer() { }
				
			void Store(Element element);
			
			Size BufferSize();
			bool IsEmpty();
			Element Peek();
			
		protected:
			virtual Element*	GetBuffer() = 0;
			virtual Size		GetSize() = 0;
			
		private:
			volatile Size head_;
			volatile Size tail_;
		};
		
		template<int TBufferSize>
		class StaticRingBuffer: public RingBuffer
		{			
		private:
			Element buffer_[TBufferSize];
			
		protected:
			virtual Element* GetBuffer() 
			{
				return buffer_;
			}
			
			virtual unsigned int GetSize()
			{
				return TBufferSize;
			}
		};
	}
}