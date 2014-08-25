#include "Vector4.h"

namespace iron {

	inline const Vector4 Vector4::operator=(const Vector4& vector) {
		set(vector);
		return *this;
	}

	inline bool Vector4::operator==(const Vector4& vector) const {
		return ((x == vector.x) && (y == vector.y) && (z == vector.z));
	}

	inline bool Vector4::operator!=(const Vector4& vector) const {
		return ((x != vector.x) || (y != vector.y) || (z != vector.z));
	}

	inline bool Vector4::operator<(const Vector4& vector) const {
		if (x == vector.x)
			if (y == vector.y)
				return z < vector.z;
			return y < vector.y;
		return x < vector.x;
	}

	inline bool Vector4::operator<=(const Vector4& vector) const {
		if (x > vector.x)
			if (y > vector.y)
				return z <= vector.z;
			return y <= vector.y;
		return x <= vector.x;
	}

	inline bool Vector4::operator>(const Vector4& vector) const {
		if (x == vector.x)
			if (y == vector.y)
				return z > vector.z;
			return y > vector.y;
		return x > vector.x;
	}

	inline bool Vector4::operator>=(const Vector4& vector) const {
		if (x < vector.x)
			if (y < vector.y)
				return z >= vector.z;
			return y >= vector.y;
		return x >= vector.x;
	}

	inline const Vector4 Vector4::operator+(const Vector4& vector) const {
		Vector4 result(*this);
		result.add(vector);
		return result;
	}

	inline Vector4& Vector4::operator+=(const Vector4& vector) {
		add(vector);
		return *this;
	}

	inline const Vector4 Vector4::operator-(const Vector4& vector) const {
		Vector4 result(*this);
		result.subtract(vector);
		return result;
	}

	inline Vector4& Vector4::operator-=(const Vector4& vector) {
		subtract(vector);
		return *this;
	}

	inline const Vector4 Vector4::operator-() const {
		Vector4 result(*this);
		result.negate();
		return result;
	}

	inline const Vector4 Vector4::operator*(const float x) const {
		Vector4 result(*this);
		result.scale(x);
		return result;
	}

	inline Vector4& Vector4::operator*=(const float x) {
		scale(x);
		return *this;
	}

	inline const Vector4 Vector4::operator/(const float x) const {
		Vector4 result(*this);
		result.divide(x);
		return result;
	}

	inline Vector4& Vector4::operator/=(const float x) {
		divide(x);
		return *this;
	}
	
	inline float& Vector4::operator[](int i) {
		if (i == 0) 
			return x;
		if (i == 1) 
			return y;
		return z;
	}
}
