#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>

//C++
#include <stdio.h>
#include <string>

//OWN
#include "../Util/Vector2.h"
#include "../Graphics/Colors.h"

class Screen;

class GameObject {
	/*************** Variables ***************/
private:

protected:
	//The position of the point in the world
	Vector2*				position;

	//The anchor is the pivot point at which the sprite is rendered upon, the fake anchor receives values more intuitive like [.5, .5] is the center of the sprite and [0, 0] is the upper left corner and [1, 0] is the right upper corner
	Vector2*				fakeAnchor;

	//The anchor is the pivot point at which the sprite is rendered upon, the real anchor holds the actual values, this is done by multiplying x with spriteWidth and y with spriteHeight from the SpriteSheet class
	SDL_Point*				realAnchor;

	//Color mod
	SDL_Color*				colorMod;

public:
	//Flips vertically or horizontally
	SDL_RendererFlip		flip;

	//Name of the game object
	std::string				name;

	//Angle of the game object
	double					angle;

	/*************** Contructors & Destructors ***************/
public:
	GameObject();
	GameObject(const std::string name);
	virtual ~GameObject();

	/*************** Methods ***************/
private:

protected:
	//Resets all variables to default values
	virtual void			resetToDefaultValues();

public:
	//Update the game object
	virtual void			update() = 0;

	//Render the game object
	virtual void			render(Screen* screen) = 0;

	//Loads the game object
	virtual bool			load(float x, float y, float angle = 0, Uint8 rMod = 255, Uint8 gMod = 255, Uint8 bMod = 255, Uint8 alpha = 255);

	//Loads the game object
	virtual bool			load(float x, float y, float angle = 0, Colors color = Colors::White);

	//Sets the position with the given values
	void					setPosition(const float x, const float y);

	//Gets the position
	Vector2*				getPosition() const;

	//Sets the position with the given values
	virtual void			setAnchor(const float x, const float y) = 0;

	//Gets the position
	SDL_Point*				getAnchor() const;

	//Sets the color mod with the given values
	void					setColorMod(const Uint8 r, const Uint8 g, const  Uint8 b, const Uint8 a);

	//Gets the color mod
	SDL_Color*				getColorMod() const;
};

#endif
