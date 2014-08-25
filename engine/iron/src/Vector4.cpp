#include "Base.h"
#include "Vector4.h"

namespace iron {

	//const Vector4 Vector4::GRAVITY = Vector4(0, -9.81f, 0);

	Vector4::Vector4()
		: x(0.0f), y(0.0f), z(0.0f)
	{}

	Vector4::Vector4(const float x, const float y, const float z)
		: x(x), y(y), z(z)
	{}

	Vector4::Vector4(const Vector4& p1, const Vector4& p2) {
		set(p1, p2);
	}

	Vector4::Vector4(const Vector4& vector) {
		set(vector);
	}

	Vector4::~Vector4()	{
	}

	const Vector4& Vector4::zero() {
		static Vector4 value(0.0f, 0.0f, 0.0f);
		return value;
	}

	const Vector4& Vector4::pOne() {
		static Vector4 value(1.0f, 1.0f, 1.0f);
		return value;
	}

	const Vector4& Vector4::nOne() {
		static Vector4 value(-1.0f, -1.0f, -1.0f);
		return value;
	}

	const Vector4& Vector4::pX() {
		static Vector4 value(1.0f, 0.0f, 0.0f);
		return value;
	}

	const Vector4& Vector4::nX() {
		static Vector4 value(-1.0f, 0.0f, 0.0f);
		return value;
	}

	const Vector4& Vector4::pY() {
		static Vector4 value(0.0f, 1.0f, 0.0f);
		return value;
	}

	const Vector4& Vector4::nY() {
		static Vector4 value(0.0f, -1.0f, 0.0f);
		return value;
	}

	const Vector4& Vector4::pZ() {
		static Vector4 value(0.0f, 0.0f, 1.0f);
		return value;
	}

	const Vector4& Vector4::nZ() {
		static Vector4 value(0.0f, 0.0f, -1.0f);
		return value;
	}

	bool Vector4::isZero() const {
		return ((x == 0.0f) && (y == 0.0f) && (z == 0.0f));
	}

	bool Vector4::isOne() const {
		return ((x == 1.0f) && (y == 1.0f) && (z == 1.0f));
	}

	bool Vector4::isNOne() const {
		return ((x == -1.0f) && (y == -1.0f) && (z == -1.0f));
	}

	void Vector4::negate() {
		x = -x;
		y = -y;
		y = -z;
	}

	void Vector4::add(const float x, const float y, const float z) {
		this->x += x;
		this->y += y;
		this->z += z;
	}

	void Vector4::add(const Vector4& vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;
	}

	void Vector4::add(const Vector4& v1, const Vector4& v2, Vector4* dst) {
		if (dst == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		dst->x = v1.x + v2.x;
		dst->y = v1.y + v2.y;
		dst->z = v1.z + v2.z;
	}

	void Vector4::subtract(const float x, const float y, const float z) {
		this->x -= x;
		this->y -= y;
		this->z -= z;
	}

	void Vector4::subtract(const Vector4& vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
	}

	void Vector4::subtract(const Vector4& v1, const Vector4& v2, Vector4* dst) {
		if (dst == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		dst->x = v1.x - v2.x;
		dst->y = v1.y - v2.y;
		dst->z = v1.z - v2.z;
	}

	void Vector4::scale(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	void Vector4::scale(float scalar, Vector4* dst) const {
		dst->x *= scalar;
		dst->y *= scalar;
		dst->z *= scalar;
	}

	void Vector4::divide(float denominator) {
		x /= denominator;
		y /= denominator;
		z /= denominator;
	}

	void Vector4::divide(float denominator, Vector4* dst) const {
		dst->x /= denominator;
		dst->y /= denominator;
		dst->z /= denominator;
	}
	
	void Vector4::addScaledVector(const Vector4& vector, float scale) {
		x += vector.x * scale;
		y += vector.y * scale;
		z += vector.z * scale;
	}

	float Vector4::length() const {
		return sqrt((x * x) + (y * y) + (z * z));
	}

	float Vector4::lengthSquared() const {
		return ((x * x) + (y * y) + (z * z));
	}

	float Vector4::distance(const Vector4& vector) const {
		float dx = vector.x - x;
		float dy = vector.y - y;
		float dz = vector.z - z;
		return sqrt((dx * dx) + (dy * dy) + (dz * dz));
	}

	float Vector4::distanceSquared(const Vector4& vector) const {
		float dx = vector.x - x;
		float dy = vector.y - y;
		float dz = vector.z - z;
		return ((dx * dx) + (dy * dy) + (dz * dz));
	}

	float Vector4::dot(const Vector4& v1, const Vector4& v2) {
		return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
	}

	float Vector4::dot(const Vector4& vector) const {
		return ((x * vector.x) + (y * vector.y) + (z * vector.z));
	}

	void Vector4::cross(const Vector4& v1, const Vector4& v2, Vector4* dst)	{
		if (dst == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		dst->x = (v1.y * v2.z) - (v1.z * v2.y);
		dst->y = (v1.z * v2.x) - (v1.x * v2.z);
		dst->z = (v1.x * v2.y) - (v1.y * v2.x);
	}

	void Vector4::cross(const Vector4& vector) {
		cross(*this, vector, this);
	}

	void Vector4::normalize(const Vector4& vector, Vector4* dst) {
		if (dst == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		float l = ((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
		if (l == 1.0f) {
			dst->x = vector.x;
			dst->y = vector.y;
			dst->z = vector.z;
			return;
		}

		l = sqrt(l);
		if (l < IronMath::MATH_FLOAT_MIN) {
			dst->x = vector.x;
			dst->y = vector.y;
			dst->z = vector.z;
			return;
		}

		l = (1.0f / l);
		dst->x *= l;
		dst->y *= l;
		dst->z *= l;
	}

	Vector4& Vector4::normalize() {
		normalize(this);
		return *this;
	}

	void Vector4::normalize(Vector4* dst) const	{
		if (dst == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		float l = lengthSquared();
		if (l == 1.0f) {
			dst->x = x;
			dst->y = y;
			dst->z = z;
			return;
		}

		l = sqrt(l);
		if (l < IronMath::MATH_FLOAT_MIN) {
			dst->x = x;
			dst->y = y;
			dst->z = z;
			return;
		}

		l = (1.0f / l);
		dst->x *= l;
		dst->y *= l;
		dst->z *= l;
	}

	void Vector4::clamp(const Vector4& vector, const float minX, const float minY, const float minZ, 
		const float maxX, const float maxY, const float maxZ, Vector4* dst)
	{
		if (dst == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__), 
				std::string(__FILE__));
			return;
		}

		if ((minX > maxX || minY > maxY || minZ > maxZ)) {
			iron::Log::s()->logWarning("The minimum values have to be inferior to the maximum values.", 
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		dst->x = vector.x;
		if (dst->x < minX) {
			dst->x = minX;
		}
		if (dst->x > maxX) {
			dst->x = maxX;
		}
		dst->y = vector.y;
		if (dst->y < minY) {
			dst->y = minY;
		}
		if (dst->y > maxY) {
			dst->y = maxY;
		}
		dst->z = vector.z;
		if (dst->z < minZ) {
			dst->z = minZ;
		}
		if (dst->z > maxZ) {
			dst->z = maxZ;
		}
	}

	void Vector4::clamp(const Vector4& v, const Vector4& min, const Vector4& max, Vector4* dst)	{
		clamp(v, min.x, min.y, min.z, max.x, max.y, max.z, dst);
	}

	void Vector4::clamp(const float minX, const float minY, const float minZ, const float maxX, 
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

	void Vector4::clamp(const Vector4& min, const Vector4& max) {
		clamp(min.x, min.y, min.z, max.x, max.y, max.z);
	}

	void Vector4::set(const int x, const int y, const int z) {
		this->x = (float)x;
		this->y = (float)y;
		this->z = (float)z;
	}

	void Vector4::set(const float x, const float y, const float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Vector4::set(const double x, const double y, const double z) {
		this->x = (float)x;
		this->y = (float)y;
		this->z = (float)z;
	}

	void Vector4::set(const Vector4& vector) {
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;
	}

	void Vector4::set(const Vector4& p1, const Vector4& p2)	{
		x = (p2.x - p1.x);
		y = (p2.y - p1.y);
		z = (p2.z - p1.z);
	}
}
