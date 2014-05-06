#include "Sprite.h"
#include "Screen.h"
#include "SpriteSheet.h"

Sprite::Sprite() : angle(0), useClip(false), useAnimation(false), loaded(false)
{
	position = new Vector2();
	fakeAnchor = new Vector2();
	realAnchor = new SDL_Point();
	clip = new SDL_Rect();
	colorMod = new SDL_Color();
	animations = new Animations();
	flip = SDL_FLIP_NONE;
	this->sheet = nullptr;
	this->texture = nullptr;

	resetToDefaultValues();
}

Sprite::Sprite(SpriteSheet* sheet) : angle(0), useClip(false), useAnimation(false), loaded(false)
{
	position = new Vector2();
	fakeAnchor = new Vector2();
	realAnchor = new SDL_Point();
	clip = new SDL_Rect();
	colorMod = new SDL_Color();
	animations = new Animations();
	flip = SDL_FLIP_NONE;
	this->sheet = sheet;
	this->texture = sheet->getTexture();

	resetToDefaultValues();
}

Sprite::~Sprite() {
	delete animations;
	animations = nullptr;
	delete position;
	position = nullptr;
	delete fakeAnchor;
	fakeAnchor = nullptr;
	delete realAnchor;
	realAnchor = nullptr;
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

void Sprite::resetToDefaultValues() {
	position->x = 0;
	position->y = 0;

	fakeAnchor->x = 0.5;
	fakeAnchor->y = 0.5;
	if (sheet != nullptr) {
		realAnchor->x = 0.5 * sheet->getSpriteWidth();
		realAnchor->y = 0.5 * sheet->getSpriteHeight();
	}

	clip->x = 0;
	clip->y = 0;
	clip->w = 0;
	clip->h = 0;

	colorMod->r = 255;
	colorMod->g = 255;
	colorMod->b = 255;
	colorMod->a = 255;

	flip = SDL_FLIP_NONE;
	angle = 0;
	useClip = false;
	useAnimation = false;

	loaded = true;
}

void Sprite::update() {
	updateAnimations();
}

void Sprite::render(Screen* screen) {
	screen->renderSprite(this);
}

bool Sprite::loadSprite(double x, double y, SDL_Rect clip, bool useClip, bool useAnimation, double angle, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) {
	setPosition(x, y);
	setSpriteClip(clip.x, clip.y, clip.w, clip.h);
	setColorMod(rMod, gMod, bMod, alpha);

	this->angle = angle;
	this->useClip = useClip;
	this->useAnimation = useAnimation;

	this->loaded = true;
	return loaded;
}

void Sprite::setPosition(const double x, const double y) {
	position->x = x;
	position->y = y;
}

Vector2* Sprite::getPosition() const {
	return position;
}

void Sprite::setAnchor(const double x, const double y) {
	fakeAnchor->x = x;
	fakeAnchor->y = y;
	if (sheet != nullptr) {
		realAnchor->x = x * sheet->getSpriteWidth();
		realAnchor->y = y * sheet->getSpriteHeight();
	}
}

SDL_Point* Sprite::getAnchor() const {
	return realAnchor;
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