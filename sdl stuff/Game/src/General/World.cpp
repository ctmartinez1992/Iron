#include "World.h"

World::World() : sheets(), sprites(), geometry()
{
}

World::World(Screen* screen) : sheets(), sprites(), geometry()
{
	this->screen = screen;
	Log::s()->logDebug("World was created");
}

World::~World() {
	//First the sprites
	for (size_t i = 0; i < sprites.size(); ++i) {
		delete sprites[i];
		sprites[i] = nullptr;
	}

	//Then the sprite sheets
	for (size_t i = 0; i < sheets.size(); ++i) {
		delete sheets[i];
		sheets[i] = nullptr;
	}

	//Finally, the geometry
	for (size_t i = 0; i < geometry.size(); ++i) {
		delete geometry[i];
		geometry[i] = nullptr;
	}

	screen = nullptr;

	Log::s()->logDebug("World was destroyed");
}

void World::updateSprites() {
	if (nSprites > 0) {
		for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it) {
			(*it)->update();
		}
	}
}

void World::updateGeometry() {
	if (nGeometry > 0) {
		for (std::vector<GeometryObject*>::iterator it = geometry.begin(); it != geometry.end(); ++it) {
			(*it)->update();
		}
	}
}

void World::update() {
	updateSprites();
	updateGeometry();
}

void World::render() {
	if (nSprites > 0) {
		for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it) {
			(*it)->render(screen);
		}
	}

	if (nGeometry > 0) {
		for (std::vector<GeometryObject*>::iterator it = geometry.begin(); it != geometry.end(); ++it) {
			(*it)->render(screen);
		}
	}
}

void World::addSpriteSheet(SpriteSheet* sheet) {
	//Push the sprite sheet into the vector and increment the counter
	this->sheets.push_back(sheet);
	nSheets++;
}

void World::addSprite(Sprite* sprite) {
	//Push the sprite into the vector and increment the counter
	this->sprites.push_back(sprite);
	nSprites++;
}

void World::addGeometry(GeometryObject* geometry) {
	//Push the geometry object into the vector and increment the counter
	this->geometry.push_back(geometry);
	nGeometry++;
}