#ifndef TIMER_H
#define TIMER_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>

//C++
#include <stdio.h>
#include <string>

//OWN	
#include "Log.h"

class Timer {
	/*************** Variables ***************/
private:

protected:

public:

	/*************** Contructors & Destructors ***************/
public:
	Timer();
	~Timer();

	/*************** Methods ***************/
private:
	/*!
	\brief Internal function that gets a positive SDL_GetTicks() value
	\return The tick count
	*/
	Uint32				getTicks();

protected:

public:
};

#endif
