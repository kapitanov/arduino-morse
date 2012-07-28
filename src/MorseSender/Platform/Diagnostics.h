/*
 * Diagnostics.h
 *
 * Created: 28.07.2012 19:49:13
 *  Author: Альберт
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