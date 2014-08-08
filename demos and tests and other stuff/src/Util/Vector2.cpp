#include "Vector2.h"

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

Vector2::~Vector2()
{
}

Vector2 Vector2::createVector(const float x, const float y) {
	return Vector2(x, y);
}

Vector2 Vector2::add(const Vector2 vector) const {
	return createVector(x + vector.x, y + vector.y);
}

Vector2 Vector2::sub(const Vector2 vector) const {
	return createVector(x - vector.x, y - vector.y);
}

Vector2 Vector2::mul(const Vector2 vector) const {
	return createVector(x * vector.x, y * vector.y);
}

Vector2 Vector2::div(const Vector2 vector) const {
	return createVector(x / vector.x, y / vector.y);
}

Vector2 Vector2::add(const float value) const {
	return createVector(x + value, y + value);
}

Vector2 Vector2::sub(const float value) const {
	return createVector(x - value, y - value);
}

Vector2 Vector2::mul(const float value) const {
	return createVector(x * value, y * value);
}

Vector2 Vector2::div(const float value) const {
	return createVector(x / value, y / value);
}

float Vector2::length() const {
	return (float) sqrt((float) (x * x) + (y * y));
}

float Vector2::dot(Vector2 vector) const {
	return (x * vector.x + y * vector.y);
}

Vector2 Vector2::normalize() {
	float l = length();
	x /= l;
	y /= l;

	return *this;
}

void Vector2::clear() {
	setPosition(0, 0);
}

inline void Vector2::setPosition(const float x, const float y) {
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator+(const Vector2 vector) {
	return createVector(x + vector.x, y + vector.y);
}

Vector2 Vector2::operator-(const Vector2 vector) {
	return createVector(x - vector.x, y - vector.y);
}

Vector2 Vector2::operator*(const Vector2 vector) {
	return createVector(x * vector.x, y * vector.y);
}

Vector2 Vector2::operator/(const Vector2 vector) {
	return createVector(x / vector.x, y / vector.y);
}

Vector2 Vector2::operator+(const float value) {
	return createVector(x + value, y + value);
}

Vector2 Vector2::operator-(const float value) {
	return createVector(x - value, y - value);
}

Vector2 Vector2::operator*(const float value) {
	return createVector(x * value, y * value);
}

Vector2 Vector2::operator/(const float value) {
	return createVector(x / value, y / value);
}

inline bool Vector2::operator==(const Vector2& vector) const {
	return (x == vector.x && y == vector.y);
}
inline bool Vector2::operator!=(const Vector2& vector) const {
	return !operator==(vector);
}