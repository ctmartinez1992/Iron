#ifndef FRAMERATE_H
#define FRAMERATE_H

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

/*!
\brief Highest possible frames per second
*/
#define FPS_HIGHEST			200

/*!
\brief Lowest possible frames per second
*/
#define FPS_LOWEST			1

/*!
\brief Default frames per second
*/
#define FPS_DEFAULT			30

class FrameRate {
	/*************** Variables ***************/
private:
	Uint32				rate;
	Uint32				baseTicks;
	Uint32				lastTicks;
	Uint32				frameCount;

	float				rateTicks;

protected:

public:

	/*************** Contructors & Destructors ***************/
public:
	FrameRate();
	~FrameRate();

	/*************** Methods ***************/
private:
	/*!
	\brief Internal function that gets a positive SDL_GetTicks() value
	\return The tick count
	*/
	Uint32				getTicks();

protected:

public:

	/*!
	\brief Sets the frame rate with the given value
	\param rate the new rate value
	*/
	void				setFrameRate(Uint32 rate);
	
	/*!
	\brief Gets the frame rate
	\return 0 for sucess and -1 for error
	*/
	int					getFrameRate();

	/*!
	\brief Default frames per second
	\return 0 for sucess and -1 for error
	*/
	int					getFrameCount();

	/*!
	\brief Default frames per second
	\return 0 for sucess and -1 for error
	*/
	Uint32				frameRateDelay();
};

#endif
