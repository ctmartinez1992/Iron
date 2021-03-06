#ifndef WORLD_H
#define WORLD_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>
#include <SDL_image.h>

//C++
#include <vector>

//OWN
#include "../Graphics/Screen.h"
#include "../Graphics/SpriteSheet.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Geometry/GeometryObject.h"
#include "../General/World.h"

//World controls everything
class World {
	/*************** Variables ***************/
private:
	//Holds all the sprite sheets in the game
	std::vector<SpriteSheet*>		sheets;

	//Holds all the sprites in the game
	std::vector<Sprite*>			sprites;

	//Holds all the geometry objects in the game
	std::vector<GeometryObject*>	geometry;

	//Stores the number of sprite sheets that were added in the game
	Uint16							nSheets;

	//Stores the number of sprites that were added in the game
	Uint16							nSprites;

	//Stores the number of geometry objects that were added in the game
	Uint16							nGeometry;

protected:

public:
	//pointer to the used screen
	Screen*					screen;

	/*************** Contructors & Destructors ***************/
public:
	World();
	World(Screen* screen);
	~World();

	/*************** Methods ***************/
private:
	//Updates all the sprites in the world
	void					updateSprites();

	//Updates all the geometry objects in the world
	void					updateGeometry();

protected:

public:
	//Updates everything that needs to be updated
	void					update();

	//Renders everything that needs to be rendered
	void					render();

	//Adds a sprite sheet to the world
	void					addSpriteSheet(SpriteSheet* sheet);

	//Adds a sprite to the world
	void					addSprite(Sprite* sprite);

	//Adds a geometry object to the world
	void					addGeometry(GeometryObject* geometry);
};

#endif
