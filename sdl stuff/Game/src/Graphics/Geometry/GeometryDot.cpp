#include "GeometryDot.h"
#include "../../Graphics/Screen.h"

GeometryDot::GeometryDot() : GeometryObject("GeometryDot", 1)
{
	filled = false;
	loaded = false;
}

GeometryDot::GeometryDot(const std::string name) : GeometryObject(name, 1)
{
	filled = false;
	loaded = false;
}

GeometryDot::~GeometryDot() {
	Log::s()->logDebug("GeometryDot (" + name + ") was UNloaded");
}

void GeometryDot::resetToDefaultValues() {
	GeometryObject::resetToDefaultValues();

	name = "GeometryDot";
	type = 1;
	filled = false;
	loaded = false;
}

void GeometryDot::update() {
}

void GeometryDot::render(Screen* screen) {
	screen->renderGeometryDot(this);
}

bool GeometryDot::load(float x, float y, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) {
	GeometryObject::load(x, y, 0, false, rMod, gMod, bMod, alpha);

	Log::s()->logDebug("GeometryDot (" + name + ") was loaded");

	this->loaded = true;
	return loaded;
}

bool GeometryDot::load(float x, float y, Colors color) {
	GeometryObject::load(x, y, 0, false, color.r, color.g, color.b, color.a);

	Log::s()->logDebug("GeometryDot (" + name + ") was loaded");

	this->loaded = true;
	return loaded;
}

void GeometryDot::setAnchor(const float x, const float y) {
	fakeAnchor->x = 0;
	fakeAnchor->y = 0;
	realAnchor->x = 0;
	realAnchor->y = 0;
}