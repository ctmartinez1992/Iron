#include "GameObject.h"
#include "../Graphics/Screen.h"

GameObject::GameObject() : name("GameObject"), angle(0)
{
	position = new Vector2();
	fakeAnchor = new Vector2();
	realAnchor = new SDL_Point();
	colorMod = new SDL_Color();
	flip = SDL_FLIP_NONE;

	resetToDefaultValues();
}

GameObject::GameObject(const std::string name) : name(name), angle(0)
{
	position = new Vector2();
	fakeAnchor = new Vector2();
	realAnchor = new SDL_Point();
	colorMod = new SDL_Color();
	flip = SDL_FLIP_NONE;

	resetToDefaultValues();
}

GameObject::~GameObject() {
	delete position;
	position = nullptr;
	delete fakeAnchor;
	fakeAnchor = nullptr;
	delete realAnchor;
	realAnchor = nullptr;
	delete colorMod;
	colorMod = nullptr;

	Log::s()->logDebug("GameObject (" + name + ") was UNloaded");
}

void GameObject::resetToDefaultValues() {
	position->x = 0;
	position->y = 0;

	colorMod->r = 255;
	colorMod->g = 255;
	colorMod->b = 255;
	colorMod->a = 255;

	name = "GameObject";
	flip = SDL_FLIP_NONE;
	angle = 0;
}

void GameObject::update() {
}

void GameObject::render(Screen* screen) {
}

bool GameObject::load(float x, float y, double angle, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) {
	setPosition(x, y);
	setColorMod(rMod, gMod, bMod, alpha);

	this->angle = angle;

	Log::s()->logDebug("GameObject (" + name + ") was loaded");

	return true;
}

void GameObject::setPosition(const float x, const float y) {
	position->x = x;
	position->y = y;
}

Vector2* GameObject::getPosition() const {
	return position;
}

void GameObject::setAnchor(const float x, const float y) {
}

SDL_Point* GameObject::getAnchor() const {
	return realAnchor;
}

void GameObject::setColorMod(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
	colorMod->r = r;
	colorMod->g = g;
	colorMod->b = b;
	colorMod->a = a;
}

SDL_Color* GameObject::getColorMod() const {
	return colorMod;
}