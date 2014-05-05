#ifndef NORMALTEXTURE_H
#define NORMALTEXTURE_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>
#include <SDL_image.h>

//C++
#include <stdio.h>
#include <string>

class NormalTexture {
	/*************** Variables ***************/
private:
	//The actual hardware texture
	SDL_Texture*			texture;

	//Image position and dimensions
	SDL_Rect*				positionAndSize;

	//Is the image loaded and ready to be used?
	bool					loaded;

protected:

public:
	//pointer to the used SDL renderer
	SDL_Renderer*			renderer;

	/*************** Contructors & Destructors ***************/
public:
	NormalTexture();
	NormalTexture(SDL_Point* position, SDL_Renderer* renderer);
	~NormalTexture();

	/*************** Methods ***************/
private:

protected:

public:
	//Loads a texture from a file
	bool					loadTexture(std::string path);

	//Deallocates texture
	void					freeTexture();

	//Gets for texture, image position and dimensions
	SDL_Texture*			getTexture() const;
	SDL_Rect*				getPositionAndSize() const;
	int						getX() const;
	int						getY() const;
	int						getWidth() const;
	int						getHeight() const;
};

#endif
