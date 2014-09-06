#include "Base.h"
#include "Quaternion.h"

namespace iron {

	const Quaternion Quaternion::ZERO = Quaternion(0, 0, 0, 0);
	const Quaternion Quaternion::IDENTITY = Quaternion(0, 0, 0, 1);

	Quaternion::Quaternion()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	Quaternion::Quaternion(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	Quaternion::Quaternion(const Vector3& axis, float angle) {
		set(axis, angle);
	}

	Quaternion::Quaternion(const Quaternion& copy) {
		set(copy);
	}

	Quaternion::~Quaternion() {
	}

	void Quaternion::slerp(float x1, float y1, float z1, float w1, float x2, float y2, float z2,
		float w2, float c, float* ptrx, float* ptry, float* ptrz, float* ptrw)
	{
		if (ptrx == nullptr || ptry == nullptr || ptrz == nullptr || ptrw == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		if ((c < 0.0f || c > 1.0f)) {
			iron::Log::s()->logWarning("The interpolation coeficcient value must be between 0 and 1 (including).",
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		if (c == 0.0f) {
			*ptrx = x1;	*ptry = y1;	*ptrz = z1;	*ptrw = w1;
			return;
		}
		else if (c == 1.0f) {
			*ptrx = x2;	*ptry = y2;	*ptrz = z2;	*ptrw = w2;
			return;
		}

		if (x1 == x2 && y1 == y2 && z1 == z2 && w1 == w2) {
			*ptrx = x1;	*ptry = y1;	*ptrz = z1;	*ptrw = w1;
			return;
		}

		float a, b, u, sq1, sq2, f1, fa2, fb2, ct, ct1, ct2, hY, r1, r2;

		ct = ((w1 * w2) + (x1 * x2) + (y1 * y2) + (z1 * z2));
		a = (ct >= 0) ? 1.0f : -1.0f;
		hY = (1.0f + (a * ct));
		fb2 = c - 0.5f;
		u = (fb2 >= 0) ? fb2 : -fb2;
		fa2 = u - fb2;
		fb2 += u;
		u += u;
		f1 = 1.0f - u;

		ct1 = (1.09f - ((0.476537f - (0.0903321f * hY)) * hY));
		ct1 *= (1.5f - (hY * ct1 * ct1));
		ct2 = (1.0f - (hY * ct1));

		sq1 = f1 * f1;
		sq2 = u * u;
		r2 = 0.0000440917108f * ct2;
		r1 = (-0.00158730159f + ((sq1 - 16.0f) * r2));
		r1 = (0.0333333333f + (r1 * (sq1 - 9.0f) * ct2));
		r1 = (-0.333333333f + (r1 * (sq1 - 4.0f) * ct2));
		r1 = (1.0f + (r1 * (sq1 - 1.0f) * ct2));
		r2 = (-0.00158730159f + ((sq2 - 16.0f) * r2));
		r2 = (0.0333333333f + (r2 * (sq2 - 9.0f) * ct2));
		r2 = (-0.333333333f + (r2 * (sq2 - 4.0f) * ct2));
		r2 = (1.0f + (r2 * (sq2 - 1.0f) * ct2));

		f1 *= r1 * ct1;
		fa2 *= r2;
		fb2 *= r2;
		a *= f1 + fa2;
		b = f1 + fb2;

		float x = a * x1 + b * x2; float y = a * y1 + b * y2; 
		float z = a * z1 + b * z2; float w = a * w1 + b * w2;

		f1 = (1.5f - (0.5f * ((w * w) + (x * x) + (y * y) + (z * z))));
		*ptrw = w * f1;	*ptrx = x * f1;	*ptry = y * f1;	*ptrz = z * f1;
	}

	void Quaternion::lerp(const Quaternion& q1, const Quaternion& q2, const float c, Quaternion* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		if ((c < 0.0f || c > 1.0f)) {
			iron::Log::s()->logWarning("The interpolation coeficcient value must be between 0 and 1 (including).",
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		if (c == 0.0f) {
			ptr->set(q1);
			return;
		} else if (c == 1.0f) {
			ptr->set(q2);
			return;
		}

		float nc = 1.0f - c;

		ptr->x = nc * q1.x + c * q2.x; ptr->y = nc * q1.y + c * q2.y;
		ptr->z = nc * q1.z + c * q2.z; ptr->w = nc * q1.w + c * q2.w;
	}

	void Quaternion::lerp(const Quaternion& q, const float c) {
		lerp(*this, q, c, this);
	}

	void Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, const float c, Quaternion* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		slerp(q1.x, q1.y, q1.z, q1.w, q2.x, q2.y, q2.z, q2.w, c, &ptr->x, &ptr->y, &ptr->z, &ptr->w);
	}

	void Quaternion::slerp(const Quaternion& q, const float c) {
		slerp(x, y, z, w, q.x, q.y, q.z, q.w, c, &x, &y, &z, &w);
	}

	void Quaternion::multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		float x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
		float y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
		float z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
		float w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);

		ptr->x = x;	ptr->y = y;	ptr->z = z;	ptr->w = w;
	}

	void Quaternion::multiply(const Quaternion& q) {
		multiply(*this, q, this);
	}

	bool Quaternion::invert(const Quaternion& q, Quaternion* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return false;
		}

		float p = ((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w));
		if (p == 1.0f) {
			ptr->x = -q.x; ptr->y = -q.y; ptr->z = -q.z; ptr->w = q.w;
			return true;
		}

		if (p < 0.00001f) {
			return false;
		}

		float ip = 1.0f / p;
		ptr->x = -q.x * ip; ptr->y = -q.y * ip; ptr->z = -q.z * ip; ptr->w = q.w * ip;

		return true;
	}

	bool Quaternion::invert() {
		return invert(*this, this);
	}

	void Quaternion::conjugate(const Quaternion& q, Quaternion* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->x = -q.x; ptr->y = -q.y; ptr->z = -q.z; ptr->w = q.w;
	}

	void Quaternion::conjugate() {
		conjugate(*this, this);
	}

	void Quaternion::normalize(const Quaternion& q, Quaternion* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		if (&q != ptr) {
			ptr->x = q.x; ptr->y = q.y; ptr->z = q.z; ptr->w = q.w;
		}

		float p = ((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w));

		if (p == 1.0f) {
			return;
		}

		float sp = sqrt(p);
		if (sp < 0.00001f) {
			return;
		}

		float isp = 1.0f / sp;
		ptr->x *= isp; ptr->y *= isp; ptr->z *= isp; ptr->w *= isp;
	}

	void Quaternion::normalize() {
		normalize(*this, this);
	}
	const Quaternion& Quaternion::identity() {
		static Quaternion value(0.0f, 0.0f, 0.0f, 1.0f);
		return value;
	}

	void Quaternion::setIdentity() {
		x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f;
	}

	bool Quaternion::isIdentity() const {
		return ((x == 0.0f) && (y == 0.0f) && (z == 0.0f) && (w == 1.0f));
	}

	const Quaternion& Quaternion::zero() {
		static Quaternion value(0.0f, 0.0f, 0.0f, 0.0f);
		return value;
	}

	void Quaternion::setZero() {
		x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f;
	}

	bool Quaternion::isZero() const {
		return ((x == 0.0f) && (y == 0.0f) && (z == 0.0f) && (w == 0.0f));
	}

	void Quaternion::set(const float x, const float y, const float z, const float w) {
		this->x = x; this->y = y; this->z = z; this->w = w;
	}

	void Quaternion::set(const Vector3& axis, const float angle) {
		//Quaternion::createFromAxisAngle(axis, angle, this);
	}

	void Quaternion::set(const Quaternion& q) {
		this->x = q.x; this->y = q.y; this->z = q.z; this->w = q.w;
	}


	/*void Quaternion::createFromRotationMatrix(const Matrix& m, Quaternion* ptr)
	{
		m.getRotation(ptr);
	}

	void Quaternion::createFromAxisAngle(const Vector3& axis, float angle, Quaternion* ptr)
	{
		GP_ASSERT(ptr);

		float halfAngle = angle * 0.5f;
		float sinHalfAngle = sinf(halfAngle);

		Vector3 normal(axis);
		normal.normalize();
		ptr->x = normal.x * sinHalfAngle;
		ptr->y = normal.y * sinHalfAngle;
		ptr->z = normal.z * sinHalfAngle;
		ptr->w = cosf(halfAngle);
	}

	float Quaternion::toAxisAngle(Vector3* axis) const
	{
		GP_ASSERT(axis);

		Quaternion q(x, y, z, w);
		q.normalize();
		axis->x = q.x;
		axis->y = q.y;
		axis->z = q.z;
		axis->normalize();

		return (2.0f * acos(q.w));
	}*/

}