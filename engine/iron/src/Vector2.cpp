#include "Base.h"
#include "Vector2.h"

namespace iron {

	Vector2::Vector2()
		: x(0.0f), y(0.0f)
	{}

	Vector2::Vector2(const float x, const float y)
		: x(x), y(y)
	{}

	Vector2::Vector2(const Vector2& p1, const Vector2& p2) {
		set(p1, p2);
	}

	Vector2::Vector2(const Vector2& vector) {
		set(vector);
	}

	Vector2::~Vector2()	{
	}

	const Vector2& Vector2::zero() {
		static Vector2 value(0.0f, 0.0f);
		return value;
	}

	const Vector2& Vector2::pOne() {
		static Vector2 value(1.0f, 1.0f);
		return value;
	}

	const Vector2& Vector2::nOne() {
		static Vector2 value(-1.0f, -1.0f);
		return value;
	}

	const Vector2& Vector2::pX() {
		static Vector2 value(1.0f, 0.0f);
		return value;
	}

	const Vector2& Vector2::nX() {
		static Vector2 value(-1.0f, 0.0f);
		return value;
	}

	const Vector2& Vector2::pY() {
		static Vector2 value(0.0f, 1.0f);
		return value;
	}

	const Vector2& Vector2::nY() {
		static Vector2 value(0.0f, -1.0f);
		return value;
	}

	bool Vector2::isZero() const {
		return ((x == 0.0f) && (y == 0.0f));
	}

	bool Vector2::isOne() const {
		return ((x == 1.0f) && (y == 1.0f));
	}

	bool Vector2::isNOne() const {
		return ((x == -1.0f) && (y == -1.0f));
	}

	void Vector2::negate() {
		x = -x;
		y = -y;
	}

	void Vector2::add(const float x, const float y) {
		this->x += x;
		this->y += y;
	}

	void Vector2::add(const Vector2& vector) {
		x += vector.x;
		y += vector.y;
	}

	void Vector2::add(const Vector2& v1, const Vector2& v2, Vector2* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		ptr->x = v1.x + v2.x;
		ptr->y = v1.y + v2.y;
	}

	void Vector2::subtract(const float x, const float y) {
		this->x -= x;
		this->y -= y;
	}

	void Vector2::subtract(const Vector2& vector) {
		x -= vector.x;
		y -= vector.y;
	}

	void Vector2::subtract(const Vector2& v1, const Vector2& v2, Vector2* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		ptr->x = v1.x - v2.x;
		ptr->y = v1.y - v2.y;
	}

	void Vector2::scale(float scalar) {
		x *= scalar;
		y *= scalar;
	}

	void Vector2::scale(float scalar, Vector2* ptr) const {
		ptr->x *= scalar;
		ptr->y *= scalar;
	}

	void Vector2::divide(float denominator) {
		x /= denominator;
		y /= denominator;
	}

	void Vector2::divide(float denominator, Vector2* ptr) const {
		ptr->x /= denominator;
		ptr->y /= denominator;
	}
	
	void Vector2::addScaledVector(const Vector2& vector, float scale) {
		x += vector.x * scale;
		y += vector.y * scale;
	}

	float Vector2::length() const {
		return sqrt((x * x) + (y * y));
	}

	float Vector2::lengthSquared() const {
		return ((x * x) + (y * y));
	}

	float Vector2::distance(const Vector2& vector) const {
		float dx = vector.x - x;
		float dy = vector.y - y;
		return sqrt((dx * dx) + (dy * dy));
	}

	float Vector2::distanceSquared(const Vector2& vector) const {
		float dx = vector.x - x;
		float dy = vector.y - y;
		return ((dx * dx) + (dy * dy));
	}

	float Vector2::dot(const Vector2& v1, const Vector2& v2) {
		return ((v1.x * v2.x) + (v1.y * v2.y));
	}

	float Vector2::dot(const Vector2& vector) const {
		return ((x * vector.x) + (y * vector.y));
	}

	void Vector2::normalize(const Vector2& vector, Vector2* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		float l = ((vector.x * vector.x) + (vector.y * vector.y));
		if (l == 1.0f) {
			ptr->x = vector.x;
			ptr->y = vector.y;
			return;
		}

		l = sqrt(l);
		if (l < IronMath::MATH_FLOAT_MIN) {
			ptr->x = vector.x;
			ptr->y = vector.y;
			return;
		}

		l = (1.0f / l);
		ptr->x *= l;
		ptr->y *= l;
	}

	Vector2& Vector2::normalize() {
		normalize(this);
		return *this;
	}

	void Vector2::normalize(Vector2* ptr) const	{
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		float l = lengthSquared();
		if (l == 1.0f) {
			ptr->x = x;
			ptr->y = y;
			return;
		}

		l = sqrt(l);
		if (l < IronMath::MATH_FLOAT_MIN) {
			ptr->x = x;
			ptr->y = y;
			return;
		}

		l = (1.0f / l);
		ptr->x *= l;
		ptr->y *= l;
	}

	void Vector2::lerp(const Vector2& start, const Vector2& end, float value, Vector2* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		if ((value < 0.0f || value > 1.0f)) {
			iron::Log::s()->logError("The interpolation fraction value must be between 0 and 1 (including).", 
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		if (value == 0.0f) {
			ptr->x = start.x;
			ptr->y = start.y;
			return;
		}
		if (value == 1.0f) {
			ptr->x = end.x;
			ptr->y = end.y;
			return;
		}

		float value1 = 1.0f - value;
		ptr->x = value1 * start.x + value * end.x;
		ptr->y = value1 * start.y + value * end.y;
	}

	void Vector2::lerp(const Vector2& end, float value) {
		if ((value < 0.0f || value > 1.0f)) {
			iron::Log::s()->logError("The interpolation fraction value must be between 0 and 1 (including)", 
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		if (value == 0.0f) {
			return;
		}
		if (value == 1.0f) {
			x = end.x;
			y = end.y;
			return;
		}

		float value1 = 1.0f - value;
		x = value1 * x + value * end.x;
		y = value1 * y + value * end.y;
	}

	void Vector2::clamp(const Vector2& vector, const float minX, const float minY, const float maxX, 
		const float maxY, Vector2* ptr) 
	{
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		if ((minX > maxX || minY > maxY)) {
			iron::Log::s()->logWarning("The minimum values have to be inferior to the maximum values.", 
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		ptr->x = vector.x;
		if (ptr->x < minX) {
			ptr->x = minX;
		}
		if (ptr->x > maxX) {
			ptr->x = maxX;
		}
		ptr->y = vector.y;
		if (ptr->y < minY) {
			ptr->y = minY;
		}
		if (ptr->y > maxY) {
			ptr->y = maxY;
		}
	}

	void Vector2::clamp(const Vector2& v, const Vector2& min, const Vector2& max, Vector2* ptr)	{
		clamp(v, min.x, min.y, max.x, max.y, ptr);
	}

	void Vector2::clamp(const float minX, const float minY, const float maxX, const float maxY) {
		if ((minX > maxX || minY > maxY)) {
			iron::Log::s()->logWarning("The minimum values have to be inferior to the maximum values.", 
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		if (x < minX) {
			x = minX;
		}
		if (x > maxX) {
			x = maxX;
		}
		if (y < minY) {
			y = minY;
		}
		if (y > maxY) {
			y = maxY;
		}
	}

	void Vector2::clamp(const Vector2& min, const Vector2& max) {
		clamp(min.x, min.y, max.x, max.y);
	}

	void Vector2::rotate(const float pointX, const float pointY, float angle)	{
		float sA = sin(angle);
		float cA = cos(angle);
		if (pointX == 0 && pointY == 0) {
			float tempY = y;
 			y = y * cA + x * sA;
			x = x * cA - tempY * sA;
		} else {
			float tempX = x - pointX;
			float tempY = y - pointY;
			x = tempX * cA - tempY * sA + pointX;
			y = tempY * cA + tempX * sA + pointY;
		}
	}

	void Vector2::rotate(const Vector2& point, float angle)	{
		rotate(point.x, point.y, angle);
	}

	void Vector2::set(const int x, const int y) {
		this->x = (float)x;
		this->y = (float)y;
	}

	void Vector2::set(const float x, const float y) {
		this->x = x;
		this->y = y;
	}

	void Vector2::set(const double x, const double y) {
		this->x = (float)x;
		this->y = (float)y;
	}

	void Vector2::set(const Vector2& vector) {
		this->x = vector.x;
		this->y = vector.y;
	}

	void Vector2::set(const Vector2& p1, const Vector2& p2)	{
		x = (p2.x - p1.x);
		y = (p2.y - p1.y);
	}
}
