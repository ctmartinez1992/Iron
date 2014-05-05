#ifndef SPRITE_H
#define SPRITE_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>
#include <SDL_image.h>

//C++
#include <stdio.h>
#include <string>

//OWN
#include "Animations.h"

class Screen;
class SpriteSheet;

class Sprite {
	/*************** Variables ***************/
private:
	//The position of the pointin the world
	SDL_Point*				position;

	//SDL_Rect (clip) of the sprite
	SDL_Rect*				clip;

	//Color mod
	SDL_Color*				colorMod;

protected:

public:
	//Pointer to the sprite sheet that the sprite image was taken from
	SpriteSheet*			sheet;

	//Pointer to the Texture that the sprite image comes from
	SDL_Texture*			texture;

	//Animation applied to the sprite
	Animations*				animations;

	//Use the clip of the sprite
	bool					useClip;

	//Animate the sprite or not
	bool					useAnimation;

	//Is the sprite loaded and ready to be used
	bool					loaded;

	/*************** Contructors & Destructors ***************/
public:
	Sprite();
	Sprite(SpriteSheet* sheet);
	~Sprite();

	/*************** Methods ***************/
private:
	//Update the animation in this sprite
	void					updateAnimations();

protected:

public:
	//Update the sprite
	void					update();

	//Render the sprite
	void					render(Screen* screen);

	//Loads the sprite clip
	bool					loadSprite(double x, double y, SDL_Rect* clip, bool useClip = false, bool useAnimation = false, Uint8 rMod = 255, Uint8 gMod = 255, Uint8 bMod = 255, Uint8 alpha = 255);

	//Sets the sprite clip with the given values
	void					setSpriteClip(const Uint16 x, const Uint16 y, const  Uint16 w, const Uint16 h);

	//Gets the sprite clip
	SDL_Rect*				getSpriteClip() const;

	//Sets the color mod with the given values
	void					setColorMod(const Uint8 r, const Uint8 g, const  Uint8 b, const Uint8 a);

	//Gets the color mod
	SDL_Color*				getColorMod() const;

	//Sets the position with the given values
	void					setPosition(const double x, const double y);

	//Gets the position
	SDL_Point*				getPosition() const;
};

#endif
