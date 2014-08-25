#ifndef IRON_BASE_H_
#define IRON_BASE_H_

//C and C++ libraries
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <vector>

//Util
#include "Log.h"

//Assert macros
#ifdef _DEBUG
#define IRON_ASSERT(expression) assert(expression)
#else
#define IRON_ASSERT(expression)
#endif

//Code line for breakpoint
#if defined(WIN32) && defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK()
#endif

//Graphics
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	//#define USE_VAO
	#include "SDL.h"
	#include "glew.h"
	#define GLEW_STATIC
#elif __linux__
	//#define USE_VAO
	//#define GLEW_STATIC
	//#include <GL/glew.h>
#elif __APPLE__
	/*#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		#define USE_VAO
		#ifdef __arm__
			#define NEON_ON
		#endif
	#elif TARGET_OS_MAC
		#define USE_VAO
	#endif*/
#elif __ANDROID__
#else
	#error "Unknown Architecture"
#endif

#endif