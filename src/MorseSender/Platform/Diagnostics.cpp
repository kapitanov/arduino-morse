/*
 * Diagnostics.cpp
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