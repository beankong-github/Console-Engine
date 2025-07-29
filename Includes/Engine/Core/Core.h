#pragma once

#pragma warning (disable : 4251)	// template dll export warning
#pragma warning (disable : 4172)	// return local variable address warning

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#if EngineDLL 
# define Engine_API __declspec(dllexport)
#else
# define Engine_API __declspec(dllimport)
#endif

template<typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete  target;
		target = nullptr;
	}
}

template<typename T>
void SafeDeleteArray(T*& target)
{
	if (target)
	{
		delete[]  target;
		target = nullptr;
	}
}