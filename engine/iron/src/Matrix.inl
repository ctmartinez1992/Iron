#include "Matrix.h"

namespace iron {

	inline const Matrix Matrix::operator+(const Matrix& m) const {
		Matrix result(*this);
		result.add(m);
		return result;
	}

	inline Matrix& Matrix::operator+=(const Matrix& m) {
		add(m);
		return *this;
	}

	inline const Matrix Matrix::operator-(const Matrix& m) const {
		Matrix result(*this);
		result.subtract(m);
		return result;
	}

	inline Matrix& Matrix::operator-=(const Matrix& m) {
		subtract(m);
		return *this;
	}

	inline const Matrix Matrix::operator-() const {
		Matrix m(*this);
		m.negate();
		return m;
	}

	inline const Matrix Matrix::operator*(const Matrix& m) const {
		Matrix result(*this);
		result.multiply(m);
		return result;
	}

	inline Matrix& Matrix::operator*=(const Matrix& m) {
		multiply(m);
		return *this;
	}
}
