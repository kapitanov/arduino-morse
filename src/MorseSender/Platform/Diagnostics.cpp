/*
 * Diagnostics.cpp
 *
 * Created: 28.07.2012 19:50:13
 *  Author: Альберт
 */ 
#include "Diagnostics.h"
#include <stdio.h>

void Platform::Diagnostics::Reset()
{
	asm("rjmp __vectors");
}

void Platform::Diagnostics::Assert(bool condition)
{
	Platform::Diagnostics::Assert(condition, "ASSERT");
}

void Platform::Diagnostics::Assert(bool condition, const char* message)
{
	if (!condition)
	{
		fprintf(stderr, message);
		fflush(stderr);
		Platform::Diagnostics::Reset();
	}
}