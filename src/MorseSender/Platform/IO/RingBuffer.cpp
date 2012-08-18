/*
* RingBuffer.cpp
*/
#include "RingBuffer.h"

namespace Platform
{
	namespace IO
	{
		void RingBuffer::Store(RingBuffer::Element element)
		{
			RingBuffer::Size i = (RingBuffer::Size)(head_ + 1) % GetSize();

			if (i != tail_)
			{
				GetBuffer()[head_] = element;
				head_= i;
			}
		}
		
		RingBuffer::Size RingBuffer::BufferSize()
		{
			RingBuffer::Size buffer_size = GetSize();
			return (RingBuffer::Size)(buffer_size + head_ - tail_) % buffer_size;
		}
		
		bool RingBuffer::IsEmpty()
		{
			return head_ == tail_;
		}
		
		RingBuffer::Element RingBuffer::Peek()
		{
			RingBuffer::Element element = GetBuffer()[tail_];
			tail_ = (RingBuffer::Size)(tail_ + 1) % GetSize();
			return element;
		}
	}
}