/*
 * Memory.cpp
 *
 * Created: 22.07.2012 17:20:00
 *  Author: Альберт
 */ 

#include "Memory.h"

void * operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void * ptr)
{
	free(ptr);
}

void __cxa_pure_virtual(void) {}; 