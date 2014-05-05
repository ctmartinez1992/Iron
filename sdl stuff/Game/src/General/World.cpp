#include "World.h"

World::World() : sheets(), sprites()
{
}

World::World(Screen* screen) : sheets(), sprites()
{
	this->screen = screen;
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

	screen = nullptr;
}

void World::updateSprites() {
	if (nSprites > 0) {
		for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it) {
			(*it)->update();
		}
	}
}

void World::update() {
	updateSprites();
}

void World::render() {
	if (nSprites > 0) {
		for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it) {
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