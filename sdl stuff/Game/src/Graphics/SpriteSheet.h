#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>
#include <SDL_image.h>

//C++
#include <stdio.h>
#include <string>
#include <math.h>

//OWN
class Sprite;

//This sheet assumes that the number of rows is equal to the number of columns
class SpriteSheet {
	/*************** Variables ***************/
private:
	//Texture sheet
	SDL_Texture*			sheet;

	//Total number of sprites in the sheet and the number of rows, which is equal to the number of columns
	Uint16					nSprites;
	Uint16					nRowsAndColumns;

	//Sheet dimensions
	Uint16					sheetWidth;
	Uint16					sheetHeight;

	//Individual sprite dimensions
	Uint16					spriteWidth;
	Uint16					spriteHeight;

	//Is the sheet loaded and ready to be used?
	bool					loaded;

protected:

public:
	//pointer to the used SDL renderer
	SDL_Renderer*			renderer;

	/*************** Contructors & Destructors ***************/
public:
	SpriteSheet();
	SpriteSheet(SDL_Renderer* renderer);
	~SpriteSheet();

	/*************** Methods ***************/
private:

protected:

public:
	//Loads a texture from a file
	bool					loadTextureAndClips(std::string path, Uint16 sheetWidth, Uint16 sheetHeight, Uint16 nSprites);

	//Deallocates texture
	void					freeTexture();

	//Gets image position and dimensions
	SDL_Texture*			getTexture() const;
	Uint16					getNRowsAndColumns() const;
	Uint16					getSheetWidth() const;
	Uint16					getSheetHeight() const;
	Uint16					getSpriteWidth() const;
	Uint16					getSpriteHeight() const;
};

#endif
