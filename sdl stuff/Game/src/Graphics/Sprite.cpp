#include "Sprite.h"
#include "Screen.h"
#include "SpriteSheet.h"

Sprite::Sprite() : GameObject("Sprite"), useClip(false), useAnimation(false), loaded(false)
{
	clip = new SDL_Rect();
	animations = new Animations();
	this->sheet = nullptr;
	this->texture = nullptr;

	resetToDefaultValues();
}

Sprite::Sprite(SpriteSheet* sheet) : GameObject("Sprite"), useClip(false), useAnimation(false), loaded(false)
{
	clip = new SDL_Rect();
	animations = new Animations();
	this->sheet = sheet;
	this->texture = sheet->getTexture();

	resetToDefaultValues();
}

Sprite::~Sprite() {
	delete animations;
	animations = nullptr;
	delete clip;
	clip = nullptr;
	sheet = nullptr;
	texture = nullptr;
	loaded = nullptr;

	Log::s()->logDebug("Sprite (" + name + ") was UNloaded");
}

void Sprite::updateAnimations() {
	animations->update();
}

void Sprite::resetToDefaultValues() {
	GameObject::resetToDefaultValues();

	fakeAnchor->x = 0.5;
	fakeAnchor->y = 0.5;
	if (sheet != nullptr) {
		realAnchor->x = (int) (0.5 * sheet->getSpriteWidth());
		realAnchor->y = (int) (0.5 * sheet->getSpriteHeight());
	}

	clip->x = 0;
	clip->y = 0;
	clip->w = 0;
	clip->h = 0;

	name = "Sprite";
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

bool Sprite::load(float x, float y, SDL_Rect clip, bool useClip, bool useAnimation, double angle, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) {
	GameObject::load(x, y, angle, rMod, gMod, bMod, alpha);

	setSpriteClip(clip.x, clip.y, clip.w, clip.h);

	this->useClip = useClip;
	this->useAnimation = useAnimation;

	Log::s()->logDebug("Sprite (" + name + ") was loaded");

	this->loaded = true;
	return loaded;
}

void Sprite::setAnchor(const float x, const float y) {
	fakeAnchor->x = x;
	fakeAnchor->y = y;
	if (sheet != nullptr) {
		realAnchor->x = (int) (x * sheet->getSpriteWidth());
		realAnchor->y = (int) (y * sheet->getSpriteHeight());
	}
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