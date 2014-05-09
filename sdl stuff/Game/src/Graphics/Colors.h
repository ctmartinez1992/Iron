#ifndef COLORS_H
#define COLORS_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>
#include <SDL_image.h>

//C++
#include <stdio.h>
#include <string>

class Colors {
	/*************** Variables ***************/
private:

protected:

public:
	//Pre-constructed colors
	static const Colors			White;
	static const Colors			Black;
	static const Colors			Red;
	static const Colors			Green;
	static const Colors			Blue;

	//RGBA
	unsigned char				r;
	unsigned char				g;
	unsigned char				b;
	unsigned char				a;

	/*************** Contructors & Destructors ***************/
public:
	Colors();
	Colors(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	~Colors();

	/*************** Methods ***************/
private:

protected:

public:
};

#endif
