#ifdef WIN32

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "Iron.h"

using namespace iron;

/**
* Where it all starts...
*/
extern "C" int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
	std::cout << "Hello" << std::endl;
	std::getchar();
}

#endif