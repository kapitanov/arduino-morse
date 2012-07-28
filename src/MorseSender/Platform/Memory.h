/*
 * Memory.h
 *
 * Created: 22.07.2012 17:14:02
 *  Author: Альберт
 */ 
#pragma once

#include <stdlib.h>

void * operator new(size_t size);
void operator delete(void * ptr);

extern "C" void __cxa_pure_virtual(void); 