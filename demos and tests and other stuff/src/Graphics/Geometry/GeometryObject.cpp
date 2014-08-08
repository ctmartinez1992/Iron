#include "GeometryObject.h"
#include "../../Graphics/Screen.h"

GeometryObject::GeometryObject() : GameObject("GeometryObject"), type(0), filled(false), loaded(false)
{
}

GeometryObject::GeometryObject(const std::string name, const Uint8 type) : GameObject(name), type(type), filled(false), loaded(false)
{
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

bool GeometryObject::load(float x, float y, float angle, bool filled, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) {
	GameObject::load(x, y, angle, rMod, gMod, bMod, alpha);

	this->filled = filled;

	Log::s()->logDebug("GeometryObject (" + name + ") was loaded");

	return true;
}

bool GeometryObject::load(float x, float y, float angle, bool filled, Colors color) {
	GameObject::load(x, y, angle, color.r, color.g, color.b, color.a);

	this->filled = filled;

	Log::s()->logDebug("GeometryObject (" + name + ") was loaded");

	return true;
}

void GeometryObject::setAnchor(const float x, const float y) {
}