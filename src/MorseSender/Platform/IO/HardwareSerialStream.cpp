/*
 * HardwareSerialStream.cpp
 */ 

#include "HardwareSerial.h"
#include "RingBuffer.h"
#include <avr/interrupt.h>

namespace Platform
{
	namespace IO
	{
		//#if (RAMEND < 1000)
		//#define SERIAL_BUFFER_SIZE 16
		//#else
		//#define SERIAL_BUFFER_SIZE 64
		//#endif
		//
		//
		//
		//RingBuffer RxBuffer;
		//RingBuffer TxBuffer;
		//
		//inline void store_char(unsigned char c, RingBuffer *buffer)
		//{
			//int i = (unsigned int)(buffer->head + 1) % SERIAL_BUFFER_SIZE;
//
			//// if we should be storing the received character into the location
			//// just before the tail (meaning that the head would advance to the
			//// current location of the tail), we're about to overflow the buffer
			//// and so we don't write the character or advance the head.
			//if (i != buffer->tail) {
				//buffer->buffer[buffer->head] = c;
				//buffer->head = i;
			//}
		//}
		
		
		//void HardwareSerialStream:: SendByte(uchar data) { }
		//uchar HardwareSerialStream:: ReceiveByte() { return 0; }
		
		//HardwareSerialStream HardwareSerial;
		
		RingBuffer* RxBuffer;
		StaticRingBuffer<64> RxBufferImpl;
		
		void Init()
		{
			RxBuffer = &RxBufferImpl;
		}
		
		ISR(USART_RX_vect)
		/*************************************************************************
		Function: UART Receive Complete interrupt
		Purpose:  called when the UART has received a character
		**************************************************************************/
		{
			    /* read UART status register and UART data register */
			  unsigned char   usr  = UCSR0A;
			  unsigned char   data = UDR0;
				unsigned char  lastRxError = (usr & ((1<<FE0)|(1<<DOR0)) );
				
			unsigned char c  =  UDR0;
			RxBuffer->Store(data);
		}
			
	}
}