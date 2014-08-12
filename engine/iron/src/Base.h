#ifndef BASE_H_
#define BASE_H_

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

#endif