#ifndef FONT_H
#define FONT_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>
#include <SDL_ttf.h>

//C++
#include <stdio.h>
#include <string>

//OWN
#include "../Util/Log.h"
#include "Colors.h"

class Font {
	/*************** Variables ***************/
private:

protected:

public:
	/*!
	\brief a TTF_Font variable that holds the loaded font
	*/
	TTF_Font*					font;

	/*!
	\brief The color of the font
	*/
	Colors*						color;

	/*!
	\brief The path to the font
	*/
	std::string					path;

	/*!
	\brief The size of the font
	*/
	Uint8						size;

	/*************** Contructors & Destructors ***************/
public:
	//TODO change this class to be a singleton and not static as it is
	Font();
	Font(std::string path, Uint8 size, Colors color);
	~Font();

	/*************** Methods ***************/
private:

protected:

public:
};

#endif
