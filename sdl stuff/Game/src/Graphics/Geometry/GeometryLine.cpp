#include "GeometryLine.h"
#include "../../Graphics/Screen.h"

GeometryLine::GeometryLine() : GeometryObject("GeometryLine", 2)
{
	filled = false;
	loaded = false;
}

GeometryLine::GeometryLine(const std::string name) : GeometryObject(name, 2)
{
	filled = false;
	loaded = false;
}

GeometryLine::~GeometryLine() {
	delete positionDestination;
	positionDestination = nullptr;

	Log::s()->logDebug("GeometryLine (" + name + ") was UNloaded");
}

void GeometryLine::resetToDefaultValues() {
	GeometryObject::resetToDefaultValues();

	name = "GeometryLine";
	type = 2;
	filled = false;
	loaded = false;
}

void GeometryLine::update() {
}

void GeometryLine::render(Screen* screen) {
	screen->renderGeometryLine(this);
}

bool GeometryLine::load(float x, float y, float x2, float y2, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) {
	GeometryObject::load(x, y, 0, false, rMod, gMod, bMod, alpha);

	this->positionDestination = new Vector2(x2, y2);

	Log::s()->logDebug("GeometryLine (" + name + ") was loaded");

	this->loaded = true;
	return loaded;
}

bool GeometryLine::load(float x, float y, float x2, float y2, Colors color) {
	return this->load(x, y, x2, y2, color.r, color.g, color.b, color.a);
}

void GeometryLine::setAnchor(const float x, const float y) {
	fakeAnchor->x = 0;
	fakeAnchor->y = 0;
	realAnchor->x = 0;
	realAnchor->y = 0;
}

void GeometryLine::setPositionAll(const float xO, const float yO, const float xD, const float yD) {
	setPositionOrigin(xO, yO);
	setPositionDestination(xD, yD);
}

void GeometryLine::setPositionOrigin(const float x, const float y) {
	setPosition(x, y);
}

Vector2* GeometryLine::getPositionOrigin() const {
	return getPosition();
}

void GeometryLine::setPositionDestination(const float x, const float y) {
	positionDestination->x = x;
	positionDestination->y = y;
}

Vector2* GeometryLine::getPositionDestination() const {
	return positionDestination;
}