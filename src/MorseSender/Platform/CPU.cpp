/*
 * CPU.cpp
 */ 
#include "CPU.h"

#define F_CPU 16000000L
#define FOSC 16000000
#define BAUD 9600
#define UBRR (((((FOSC * 10) / (16L * BAUD)) + 5) / 10) - 1)

using namespace Platform;

const uint16_t CPU::GetCpuClock()
{
	return FOSC;
}

const uint16_t CPU::GetBaudRate()
{
	return BAUD;
}

const uint16_t CPU::GetUbrr()
{
	return UBRR;
}