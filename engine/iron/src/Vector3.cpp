#include "Base.h"
#include "Vector3.h"

namespace iron {

	const Vector3 Vector3::GRAVITY = Vector3(0, -9.81f, 0);
	const Vector3 Vector3::LEFT = Vector3(-1, 0, 0);
	const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
	const Vector3 Vector3::UP = Vector3(0, 1, 0);
	const Vector3 Vector3::DOWN = Vector3(0, -1, 0);
	const Vector3 Vector3::FRONT = Vector3(0, 0, 1);
	const Vector3 Vector3::BACK = Vector3(0, 0, -1);

	Vector3::Vector3()
		: x(0.0f), y(0.0f), z(0.0f)
	{}

	Vector3::Vector3(const float x, const float y, const float z)
		: x(x), y(y), z(z)
	{}

	Vector3::Vector3(const Vector3& p1, const Vector3& p2) {
		set(p1, p2);
	}

	Vector3::Vector3(const Vector3& vector) {
		set(vector);
	}

	Vector3::~Vector3()	{
	}

	const Vector3& Vector3::zero() {
		static Vector3 value(0.0f, 0.0f, 0.0f);
		return value;
	}

	const Vector3& Vector3::pOne() {
		static Vector3 value(1.0f, 1.0f, 1.0f);
		return value;
	}

	const Vector3& Vector3::nOne() {
		static Vector3 value(-1.0f, -1.0f, -1.0f);
		return value;
	}

	const Vector3& Vector3::pX() {
		static Vector3 value(1.0f, 0.0f, 0.0f);
		return value;
	}

	const Vector3& Vector3::nX() {
		static Vector3 value(-1.0f, 0.0f, 0.0f);
		return value;
	}

	const Vector3& Vector3::pY() {
		static Vector3 value(0.0f, 1.0f, 0.0f);
		return value;
	}

	const Vector3& Vector3::nY() {
		static Vector3 value(0.0f, -1.0f, 0.0f);
		return value;
	}

	const Vector3& Vector3::pZ() {
		static Vector3 value(0.0f, 0.0f, 1.0f);
		return value;
	}

	const Vector3& Vector3::nZ() {
		static Vector3 value(0.0f, 0.0f, -1.0f);
		return value;
	}

	bool Vector3::isZero() const {
		return ((x == 0.0f) && (y == 0.0f) && (z == 0.0f));
	}

	bool Vector3::isOne() const {
		return ((x == 1.0f) && (y == 1.0f) && (z == 1.0f));
	}

	bool Vector3::isNOne() const {
		return ((x == -1.0f) && (y == -1.0f) && (z == -1.0f));
	}

	void Vector3::negate() {
		x = -x;
		y = -y;
		y = -z;
	}

	void Vector3::add(const float x, const float y, const float z) {
		this->x += x;
		this->y += y;
		this->z += z;
	}

	void Vector3::add(const Vector3& vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;
	}

	void Vector3::add(const Vector3& v1, const Vector3& v2, Vector3* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		ptr->x = v1.x + v2.x;
		ptr->y = v1.y + v2.y;
		ptr->z = v1.z + v2.z;
	}

	void Vector3::subtract(const float x, const float y, const float z) {
		this->x -= x;
		this->y -= y;
		this->z -= z;
	}

	void Vector3::subtract(const Vector3& vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
	}

	void Vector3::subtract(const Vector3& v1, const Vector3& v2, Vector3* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		ptr->x = v1.x - v2.x;
		ptr->y = v1.y - v2.y;
		ptr->z = v1.z - v2.z;
	}

	void Vector3::scale(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	void Vector3::scale(float scalar, Vector3* ptr) const {
		ptr->x *= scalar;
		ptr->y *= scalar;
		ptr->z *= scalar;
	}

	void Vector3::divide(float denominator) {
		x /= denominator;
		y /= denominator;
		z /= denominator;
	}

	void Vector3::divide(float denominator, Vector3* ptr) const {
		ptr->x /= denominator;
		ptr->y /= denominator;
		ptr->z /= denominator;
	}
	
	void Vector3::addScaledVector(const Vector3& vector, float scale) {
		x += vector.x * scale;
		y += vector.y * scale;
		z += vector.z * scale;
	}

	float Vector3::length() const {
		return sqrt((x * x) + (y * y) + (z * z));
	}

	float Vector3::lengthSquared() const {
		return ((x * x) + (y * y) + (z * z));
	}

	float Vector3::distance(const Vector3& vector) const {
		float dx = vector.x - x;
		float dy = vector.y - y;
		float dz = vector.z - z;
		return sqrt((dx * dx) + (dy * dy) + (dz * dz));
	}

	float Vector3::distanceSquared(const Vector3& vector) const {
		float dx = vector.x - x;
		float dy = vector.y - y;
		float dz = vector.z - z;
		return ((dx * dx) + (dy * dy) + (dz * dz));
	}

	float Vector3::dot(const Vector3& v1, const Vector3& v2) {
		return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
	}

	float Vector3::dot(const Vector3& vector) const {
		return ((x * vector.x) + (y * vector.y) + (z * vector.z));
	}

	void Vector3::cross(const Vector3& v1, const Vector3& v2, Vector3* ptr)	{
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		ptr->x = (v1.y * v2.z) - (v1.z * v2.y);
		ptr->y = (v1.z * v2.x) - (v1.x * v2.z);
		ptr->z = (v1.x * v2.y) - (v1.y * v2.x);
	}

	void Vector3::cross(const Vector3& vector) {
		cross(*this, vector, this);
	}

	void Vector3::normalize(const Vector3& vector, Vector3* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		float l = ((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
		if (l == 1.0f) {
			ptr->x = vector.x;
			ptr->y = vector.y;
			ptr->z = vector.z;
			return;
		}

		l = sqrt(l);
		if (l < IronMath::MATH_FLOAT_MIN) {
			ptr->x = vector.x;
			ptr->y = vector.y;
			ptr->z = vector.z;
			return;
		}

		l = (1.0f / l);
		ptr->x *= l;
		ptr->y *= l;
		ptr->z *= l;
	}

	Vector3& Vector3::normalize() {
		normalize(this);
		return *this;
	}

	void Vector3::normalize(Vector3* ptr) const	{
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		float l = lengthSquared();
		if (l == 1.0f) {
			ptr->x = x;
			ptr->y = y;
			ptr->z = z;
			return;
		}

		l = sqrt(l);
		if (l < IronMath::MATH_FLOAT_MIN) {
			ptr->x = x;
			ptr->y = y;
			ptr->z = z;
			return;
		}

		l = (1.0f / l);
		ptr->x *= l;
		ptr->y *= l;
		ptr->z *= l;
	}

	void Vector3::clamp(const Vector3& vector, const float minX, const float minY, const float minZ, 
		const float maxX, const float maxY, const float maxZ, Vector3* ptr)
	{
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		if ((minX > maxX || minY > maxY || minZ > maxZ)) {
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
		ptr->z = vector.z;
		if (ptr->z < minZ) {
			ptr->z = minZ;
		}
		if (ptr->z > maxZ) {
			ptr->z = maxZ;
		}
	}

	void Vector3::clamp(const Vector3& v, const Vector3& min, const Vector3& max, Vector3* ptr)	{
		clamp(v, min.x, min.y, min.z, max.x, max.y, max.z, ptr);
	}

	void Vector3::clamp(const float minX, const float minY, const float minZ, const float maxX, 
		const float maxY, const float maxZ) 
	{
		if ((minX > maxX || minY > maxY || minZ > maxZ)) {
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
		if (z < minZ) {
			z = minZ;
		}
		if (z > maxZ) {
			z = maxZ;
		}
	}

	void Vector3::clamp(const Vector3& min, const Vector3& max) {
		clamp(min.x, min.y, min.z, max.x, max.y, max.z);
	}

	void Vector3::set(const int x, const int y, const int z) {
		this->x = (float)x;
		this->y = (float)y;
		this->z = (float)z;
	}

	void Vector3::set(const float x, const float y, const float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Vector3::set(const double x, const double y, const double z) {
		this->x = (float)x;
		this->y = (float)y;
		this->z = (float)z;
	}

	void Vector3::set(const Vector3& vector) {
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;
	}

	void Vector3::set(const Vector3& p1, const Vector3& p2)	{
		x = (p2.x - p1.x);
		y = (p2.y - p1.y);
		z = (p2.z - p1.z);
	}
}
