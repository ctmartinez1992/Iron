#include "Vector2.h"

namespace iron {

	inline const Vector2 Vector2::operator=(const Vector2& vector) {
		set(vector);
		return *this;
	}

	inline bool Vector2::operator==(const Vector2& vector) const {
		return ((x == vector.x) && (y == vector.y));
	}

	inline bool Vector2::operator!=(const Vector2& vector) const {
		return ((x != vector.x) || (y != vector.y));
	}

	inline bool Vector2::operator<(const Vector2& vector) const {
		if (x == vector.x)
			return y < vector.y;
		return x < vector.x;
	}

	inline bool Vector2::operator<=(const Vector2& vector) const {
		if (x > vector.x)
			return y <= vector.y;
		return x <= vector.x;
	}

	inline bool Vector2::operator>(const Vector2& vector) const {
		if (x == vector.x)
			return y > vector.y;
		return x > vector.x;
	}

	inline bool Vector2::operator>=(const Vector2& vector) const {
		if (x < vector.x)
			return y >= vector.y;
		return x >= vector.x;
	}

	inline const Vector2 Vector2::operator+(const Vector2& vector) const {
		Vector2 result(*this);
		result.add(vector);
		return result;
	}

	inline Vector2& Vector2::operator+=(const Vector2& vector) {
		add(vector);
		return *this;
	}

	inline const Vector2 Vector2::operator-(const Vector2& vector) const {
		Vector2 result(*this);
		result.subtract(vector);
		return result;
	}

	inline Vector2& Vector2::operator-=(const Vector2& vector) {
		subtract(vector);
		return *this;
	}

	inline const Vector2 Vector2::operator-() const {
		Vector2 result(*this);
		result.negate();
		return result;
	}

	inline const Vector2 Vector2::operator*(const float x) const {
		Vector2 result(*this);
		result.scale(x);
		return result;
	}

	inline Vector2& Vector2::operator*=(const float x) {
		scale(x);
		return *this;
	}

	inline const Vector2 Vector2::operator/(const float x) const {
		Vector2 result(*this);
		result.divide(x);
		return result;
	}

	inline Vector2& Vector2::operator/=(const float x) {
		divide(x);
		return *this;
	}
}
