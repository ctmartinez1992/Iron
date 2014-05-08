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
#include "../Util/Vector2.h"
#include "../Util/Log.h"

class Screen;
class SpriteSheet;

class Sprite {
	/*************** Variables ***************/
private:
	//The position of the point in the world
	Vector2*				position;

	//The anchor is the pivot point at which the sprite is rendered upon, the fake anchor receives values more intuitive like [.5, .5] is the center of the sprite and [0, 0] is the upper left corner and [1, 0] is the right upper corner
	Vector2*				fakeAnchor;

	//The anchor is the pivot point at which the sprite is rendered upon, the real anchor holds the actual values, this is done by multiplying x with spriteWidth and y with spriteHeight from the SpriteSheet class
	SDL_Point*				realAnchor;

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

	//Flips vertically or horizontally
	SDL_RendererFlip		flip;

	//Name of the sprite
	std::string				name;

	//Angle of the sprite
	double					angle;

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

	//Resets all variables to default values
	void					resetToDefaultValues();

protected:

public:
	//Update the sprite
	void					update();

	//Render the sprite
	void					render(Screen* screen);

	//Loads the sprite clip
	bool					loadSprite(double x, double y, SDL_Rect clip, bool useClip = false, bool useAnimation = false, double angle = 0, Uint8 rMod = 255, Uint8 gMod = 255, Uint8 bMod = 255, Uint8 alpha = 255);

	//Sets the position with the given values
	void					setPosition(const double x, const double y);

	//Gets the position
	Vector2*				getPosition() const;

	//Sets the position with the given values
	void					setAnchor(const double x, const double y);

	//Gets the position
	SDL_Point*				getAnchor() const;

	//Sets the sprite clip with the given values
	void					setSpriteClip(const Uint16 x, const Uint16 y, const  Uint16 w, const Uint16 h);

	//Gets the sprite clip
	SDL_Rect*				getSpriteClip() const;

	//Sets the color mod with the given values
	void					setColorMod(const Uint8 r, const Uint8 g, const  Uint8 b, const Uint8 a);

	//Gets the color mod
	SDL_Color*				getColorMod() const;
};

#endif
