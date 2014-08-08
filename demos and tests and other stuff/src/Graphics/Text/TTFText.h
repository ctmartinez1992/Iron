#ifndef TTFTEXT_H
#define TTFTEXT_H

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
#include "../FontManager.h"

class Screen;

class TTFText {
	/*************** Variables ***************/
private:
	/*!
	\brief Text that is going to be rendered
	*/
	std::string				text;

protected:

	//TODO add position
public:
	/*!
	\brief Pointer to the screen
	*/
	Screen*					screen;

	/*!
	\brief Holds the texture of the loaded font
	*/
	SDL_Texture*			texture;

	/*!
	\brief Width and height of the text
	*/
	int						width;
	int						height;

	/*************** Contructors & Destructors ***************/
public:
	TTFText();
	TTFText(Screen*	screen);
	~TTFText();

	/*************** Methods ***************/
private:

protected:

public:
	int						load();

	void					render();
};

#endif