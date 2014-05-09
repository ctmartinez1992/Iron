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
#include "../General/GameObject.h"
#include "../Util/Vector2.h"
#include "../Util/Log.h"

class Screen;
class SpriteSheet;

class Sprite : public GameObject {
	/*************** Variables ***************/
private:
	//SDL_Rect (clip) of the sprite
	SDL_Rect*				clip;

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
	virtual ~Sprite();

	/*************** Methods ***************/
private:
	//Update the animation in this sprite
	void					updateAnimations();

	//Resets all variables to default values
	void					resetToDefaultValues();

protected:

public:
	//Update the sprite
	void					update();

	//Render the sprite
	void					render(Screen* screen);

	//Loads the sprite clip
	bool					load(float x, float y, SDL_Rect clip, bool useClip = false, bool useAnimation = false, double angle = 0, Uint8 rMod = 255, Uint8 gMod = 255, Uint8 bMod = 255, Uint8 alpha = 255);

	//Sets the position with the given values
	void					setAnchor(const float x, const float y);

	//Sets the sprite clip with the given values
	void					setSpriteClip(const Uint16 x, const Uint16 y, const  Uint16 w, const Uint16 h);

	//Gets the sprite clip
	SDL_Rect*				getSpriteClip() const;
};

#endif
