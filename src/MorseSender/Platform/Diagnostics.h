/*
 * Diagnostics.h
 */ 
#pragma once

namespace Platform
{
	namespace Diagnostics
	{
		void Reset();
		void Assert(bool condition);
		void Assert(bool condition, const char* message);
	}
}