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
#include "../Fonts.h"

class Screen;

class TTFText {
	/*************** Variables ***************/
private:

protected:

public:
	/*!
	\brief Pointer to the screen
	*/
	Screen*					screen;

	/*!
	\brief The texture holds the text parts that need to be rendered
	*/
	SDL_Texture*			textTexture;

	/*!
	\brief Text texture width and height
	*/
	int						textWidth;
	int						textHeight;

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