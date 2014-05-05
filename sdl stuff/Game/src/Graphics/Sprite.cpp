#include "Sprite.h"
#include "Screen.h"
#include "SpriteSheet.h"

Sprite::Sprite() : useClip(false), useAnimation(false), loaded(false)
{
	position = new SDL_Point();
	clip = new SDL_Rect();
	colorMod = new SDL_Color();
	animations = new Animations();
}

Sprite::Sprite(SpriteSheet* sheet) : useClip(false), useAnimation(false), loaded(false)
{
	position = new SDL_Point();
	clip = new SDL_Rect();
	colorMod = new SDL_Color();
	animations = new Animations();
	this->sheet = sheet;
	this->texture = sheet->getTexture();
}

Sprite::~Sprite() {
	delete animations;
	animations = nullptr;
	delete position;
	position = nullptr;
	delete clip;
	clip = nullptr;
	delete colorMod;
	colorMod = nullptr;
	sheet = nullptr;
	texture = nullptr;
	loaded = nullptr;
}

void Sprite::updateAnimations() {
	animations->update();
}

void Sprite::update() {
	updateAnimations();
}

void Sprite::render(Screen* screen) {
	screen->renderSprite(this);
}

bool Sprite::loadSprite(double x, double y, SDL_Rect* clip, bool useClip, bool useAnimation, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) {
	setPosition(x, y);
	setSpriteClip(clip->x, clip->y, clip->w, clip->h);
	setColorMod(rMod, gMod, bMod, alpha);

	this->useClip = useClip;
	this->useAnimation = useAnimation;

	this->loaded = true;
	return loaded;
}

void Sprite::setSpriteClip(const Uint16 x, const Uint16 y, const Uint16 w, const Uint16 h) {
	clip->x = x;
	clip->y = y;
	clip->w = w;
	clip->h = h;
}

SDL_Rect* Sprite::getSpriteClip() const {
	return clip;
}

void Sprite::setColorMod(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
	colorMod->r = r;
	colorMod->g = g;
	colorMod->b = b;
	colorMod->a = a;
}

SDL_Color* Sprite::getColorMod() const {
	return colorMod;
}

void Sprite::setPosition(const double x, const double y) {
	position->x = x;
	position->y = y;
}

SDL_Point* Sprite::getPosition() const {
	return position;
}