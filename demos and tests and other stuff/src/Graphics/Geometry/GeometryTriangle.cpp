#include "GeometryTriangle.h"
#include "../../Graphics/Screen.h"

GeometryTriangle::GeometryTriangle() : GeometryObject("GeometryTriangle", 3)
{
	filled = false;
	loaded = false;
}

GeometryTriangle::GeometryTriangle(const std::string name) : GeometryObject(name, 3)
{
	filled = false;
	loaded = false;
}

GeometryTriangle::~GeometryTriangle() {
	delete position2;
	position2 = nullptr;
	delete position3;
	position3 = nullptr;

	Log::s()->logDebug("GeometryTriangle (" + name + ") was UNloaded");
}

void GeometryTriangle::resetToDefaultValues() {
	GeometryObject::resetToDefaultValues();

	name = "GeometryTriangle";
	type = 3;
	filled = false;
	loaded = false;
}

void GeometryTriangle::update() {
}

void GeometryTriangle::render(Screen* screen) {
	screen->renderGeometryTriangle(this);
}

bool GeometryTriangle::load(float x, float y, float x2, float y2, float x3, float y3, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) {
	GeometryObject::load(x, y, 0, false, rMod, gMod, bMod, alpha);

	this->position2 = new Vector2(x2, y2);
	this->position3 = new Vector2(x3, y3);

	Log::s()->logDebug("GeometryTriangle (" + name + ") was loaded");

	this->loaded = true;
	return loaded;
}

bool GeometryTriangle::load(float x, float y, float x2, float y2, float x3, float y3, Colors color) {
	return this->load(x, y, x2, y2, x3, y3, color.r, color.g, color.b, color.a);
}

void GeometryTriangle::setAnchor(const float x, const float y) {
	fakeAnchor->x = 0;
	fakeAnchor->y = 0;
	realAnchor->x = 0;
	realAnchor->y = 0;
}

void GeometryTriangle::setPositionAll(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3) {
	setPosition1(x1, y1);
	setPosition2(x2, y2);
	setPosition3(x3, y3);
}

void GeometryTriangle::setPosition1(const float x, const float y) {
	setPosition(x, y);
}

Vector2* GeometryTriangle::getPosition1() const {
	return getPosition();
}

void GeometryTriangle::setPosition2(const float x, const float y) {
	position2->x = x;
	position2->y = y;
}

Vector2* GeometryTriangle::getPosition2() const {
	return position2;
}

void GeometryTriangle::setPosition3(const float x, const float y) {
	position3->x = x;
	position3->y = y;
}

Vector2* GeometryTriangle::getPosition3() const {
	return position3;
}