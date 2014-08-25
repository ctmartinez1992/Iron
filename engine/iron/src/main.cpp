#ifdef WIN32

#include "Iron.h"

using namespace iron;

/**
* Where it all starts...
*/
int main(int argc, const char* argv[]) {
	std::printf("Hello World!");

	SDL_Init(SDL_INIT_EVERYTHING);

	return 0;
}

#endif