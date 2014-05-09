#include "GeometryObject.h"
#include "../../Graphics/Screen.h"

GeometryObject::GeometryObject() : GameObject("GeometryObject"), type(0), filled(false), loaded(false)
{
	resetToDefaultValues();
}

GeometryObject::GeometryObject(const Uint8 type) : GameObject("GeometryObject"), type(type), filled(false), loaded(false)
{
	resetToDefaultValues();
}

GeometryObject::~GeometryObject() {
	Log::s()->logDebug("GeometryObject (" + name + ") was UNloaded");
}

void GeometryObject::resetToDefaultValues() {
	GameObject::resetToDefaultValues();

	name = "GeometryObject";
	type = 0;
	filled = false;
	loaded = false;
}

void GeometryObject::update() {
}

void GeometryObject::render(Screen* screen) {
}

bool GeometryObject::load(float x, float y, double angle, bool filled, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) {
	GameObject::load(x, y, angle, rMod, gMod, bMod, alpha);

	this->filled = filled;

	Log::s()->logDebug("GeometryObject (" + name + ") was loaded");

	this->loaded = true;
	return loaded;
}

void GeometryObject::setAnchor(const double x, const double y) {
}