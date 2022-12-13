#pragma once
#include <Windows.h>

#ifdef _DEBUG
#define Assert(expr) \
	if(!expr) \
	{ \
		__debugbreak(); \
	}
#else
#define Assert(expr) \
	if (!expr) \
	{ \
		std::abort(); \
	}
#endif