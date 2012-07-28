/*
 * Cpu.h
 *
 * Created: 28.07.2012 20:00:25
 *  Author: Альберт
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