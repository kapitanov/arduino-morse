/*
 * CPU.h
 */ 
#pragma once

#include <avr/io.h>

namespace Platform
{
	class CPU
	{
	private:
		CPU() { }
	public:
		static const uint16_t GetCpuClock();
		static const uint16_t GetBaudRate();
		static const uint16_t GetUbrr();
	};
}