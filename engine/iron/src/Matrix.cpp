#include "Base.h"
#include "Matrix.h"

namespace iron {

	const float Matrix::MATRIX_SIZE = sizeof(float) * 16;
	const Matrix Matrix::ZERO = Matrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	const Matrix Matrix::IDENTITY = Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	

	Matrix::Matrix() {
		*this = Matrix::identity();
	}

	Matrix::Matrix(const float x1y1, const float x2y1, const float x3y1, const float x4y1,
		const float x1y2, const float x2y2, const float x3y2, const float x4y2,
		const float x1y3, const float x2y3, const float x3y3, const float x4y3,
		const float x1y4, const float x2y4, const float x3y4, const float x4y4)
	{
		set(x1y1, x2y1, x3y1, x4y1, x1y2, x2y2, x3y2, x4y2, 
			x1y3, x2y3, x3y3, x4y3, x1y4, x2y4, x3y4, x4y4);
	}

	Matrix::Matrix(const float* a) {
		set(a);
	}

	Matrix::Matrix(const Matrix& m) {
		set(m);
	}

	Matrix::~Matrix()
	{
	}

	void Matrix::lookAt(const Vector3& eye, const Vector3& point, const Vector3& up, Matrix* ptr) {
		lookAt(eye.x, eye.y, eye.z, point.x, point.y, point.z, up.x, up.y, up.z, ptr);
	}

	void Matrix::lookAt(const float eyeX, const float eyeY, const float eyeZ,
		const float pointX, const float pointY, const float pointZ,
		const float upX, const float upY, const float upZ, Matrix* ptr)
	{
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		Vector3 e(eyeX, eyeY, eyeZ);
		Vector3 p(pointX, pointY, pointZ);
		Vector3 u(upX, upY, upZ);

		u.normalize();

		Vector3 z;
		Vector3::subtract(e, p, &z);
		z.normalize();

		Vector3 x;
		Vector3::cross(u, z, &x);
		x.normalize();

		Vector3 y;
		Vector3::cross(z, x, &y);
		y.normalize();

		ptr->m[0] = x.x;
		ptr->m[1] = y.x;
		ptr->m[2] = z.x;
		ptr->m[3] = 0.0f;
		ptr->m[4] = x.y;
		ptr->m[5] = y.y;
		ptr->m[6] = z.y;
		ptr->m[7] = 0.0f;
		ptr->m[8] = x.z;
		ptr->m[9] = y.z;
		ptr->m[10] = z.z;
		ptr->m[11] = 0.0f;
		ptr->m[12] = -Vector3::dot(x, e);
		ptr->m[13] = -Vector3::dot(y, e);
		ptr->m[14] = -Vector3::dot(z, e);
		ptr->m[15] = 1.0f;
	}

	void Matrix::orthographic(const float w, const float h, const float zNear, const float zFar,
		Matrix* ptr) 
	{
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		if (w == h) {
			iron::Log::s()->logError("Width and height variables must have different numerical values.",
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		if (zNear == zFar) {
			iron::Log::s()->logError("Near and far planes must have different numerical values.",
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		float hW = w / 2.0f;
		float hH = h / 2.0f;
		float l = -hW;
		float r = hW;
		float u = hH;
		float d = -hH;

		memset(ptr->m, 0, ((size_t)MATRIX_SIZE));

		ptr->m[0] = (2 / (r - l));
		ptr->m[5] = (2 / (u - d));
		ptr->m[10] = (1 / (zNear - zFar));
		ptr->m[12] = ((l + r) / (l - r));
		ptr->m[13] = ((u + d) / (d - u));
		ptr->m[14] = (zNear / (zNear - zFar));
		ptr->m[15] = 1;
	}
	
	void Matrix::perspective(const float fov, const float aspect, const float zNear, 
		const float zFar, Matrix* ptr)
	{
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		if (zNear == zFar) {
			iron::Log::s()->logError("Near and far planes must have different numerical values.",
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			return;
		}

		float safeFOV = fov;

		if (fov < 30.0f) {
			iron::Log::s()->logWarning("Field of View value should be between 30 and 180 degrees.",
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			safeFOV = 30.0f;
		}

		if (fov > 180.0f) {
			iron::Log::s()->logWarning("Field of View value should be between 30 and 180 degrees.",
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
			safeFOV = 180.0f;
		}

		float iz = (1.0f / (zFar - zNear));
		float t = iron::IronMath::deg_to_rad(safeFOV) * 0.5f;
		float d = std::tan(t);
		float id = 1.0f / d;

		memset(ptr->m, 0, ((size_t)MATRIX_SIZE));

		ptr->m[0] = ((1.0f / aspect) * id);
		ptr->m[5] = id;
		ptr->m[10] = ((-(zFar + zNear)) * iz);
		ptr->m[11] = -1.0f;
		ptr->m[14] = ((-2.0f * zFar) * (zNear * iz));
	}

	void Matrix::translate(const float x, const float y, const float z, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		multiply(*this, Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1), ptr);
	}

	void Matrix::translate(const float x, const float y, const float z) {
		multiply(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1));
	}

	void Matrix::translate(const Vector3& t, Matrix* ptr) {
		translate(t.x, t.y, t.z, ptr);
	}

	void Matrix::translate(const Vector3& t) {
		multiply(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, t.x, t.y, t.z, 1));
	}

	void Matrix::rotate(const Quaternion& q, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		Matrix r;

		float xx = q.x + q.x; float yy = q.y + q.y; float zz = q.z + q.z;

		float xxx = q.x * xx; float yyy = q.y * yy; float zzz = q.z * zz;
		float xyy = q.x * yy; float xzz = q.x * zz; float yzz = q.y * zz;
		float wxx = q.w * xx; float wyy = q.w * yy; float wzz = q.w * zz;

		ptr->setIdentity();

		ptr->m[0] -= yyy - zzz;	ptr->m[1] = xyy + wzz; ptr->m[2] = xzz - wyy;
		ptr->m[4] = xyy - wzz; ptr->m[5] -= xxx - zzz; ptr->m[6] = yzz + wxx;
		ptr->m[8] = xzz + wyy; ptr->m[9] = yzz - wxx; ptr->m[10] -= xxx - yyy;

		multiply(*this, r, ptr);
	}

	void Matrix::rotate(const Quaternion& q) {
		rotate(q, this);
	}

	void Matrix::rotate(const Vector3& axis, const float a, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		Matrix r;

		float x = axis.x; float y = axis.y; float z = axis.z;

		float n = ((x * x) + (y * y) + (z * z));
		if (n != 1.0f) {
			n = sqrt(n);
			if (n > 0.00001f) {
				n = 1.0f / n;
				x *= n; y *= n; z *= n;
			}
		}

		float c = std::cos(a); float s = std::sin(a);

		float ic = 1.0f - c;
		float icx = ic * x; float icy = ic * y; float icz = ic * z;
		float icxy = icx * y; float icxz = icx * z; float icyz = icy * z;
		float sx = s * x; float sy = s * y;	float sz = s * z;

		ptr->setIdentity();

		ptr->m[0] = (c + (icx * x)); ptr->m[1] = icxy + sz; ptr->m[2] = icxz - sy;
		ptr->m[4] = icxy - sz; ptr->m[5] = (c + (icy * y)); ptr->m[6] = icyz + sx;
		ptr->m[8] = icxz + sy; ptr->m[9] = icyz - sx; ptr->m[10] = (c + (icz * z));

		multiply(*this, r, ptr);
	}

	void Matrix::rotate(const Vector3& axis, const float a) {
		rotate(axis, a, this);
	}

	void Matrix::rotateX(const float a, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		float c = std::cos(a);
		float s = std::sin(a);

		Matrix r = Matrix(1, 0, 0, 0, 0, c, s, 0, 0, -s, -c, 0, 0, 0, 0, 1);

		multiply(*this, r, ptr);
	}

	void Matrix::rotateX(const float a) {
		rotateX(a, this);
	}

	void Matrix::rotateY(const float a, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		float c = std::cos(a);
		float s = std::sin(a);

		Matrix r = Matrix(c, 0, -s, 0, 0, 1, 0, 0, s, 0, c, 0, 0, 0, 0, 1);
		
		multiply(*this, r, ptr);
	}

	void Matrix::rotateY(const float a) {
		rotateY(a, this);
	}

	void Matrix::rotateZ(const float a, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		float c = std::cos(a);
		float s = std::sin(a);

		Matrix r = Matrix(c, s, 0, 0, -s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

		multiply(*this, r, ptr);
	}

	void Matrix::rotateZ(const float a) {
		rotateZ(a, this);
	}

	void Matrix::scale(const float s, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->setIdentity();
		ptr->m[0] = s; ptr->m[5] = s; ptr->m[10] = s;
	}

	void Matrix::scale(const float s) {
		scale(s, this);
	}

	void Matrix::scale(const float x, const float y, const float z, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->setIdentity();
		ptr->m[0] = x; ptr->m[5] = y; ptr->m[10] = z;
	}

	void Matrix::scale(const float x, const float y, const float z) {
		scale(x, y, z, this);
	}

	void Matrix::scale(const Vector3& s, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}
		
		ptr->setIdentity();
		ptr->m[0] = s.x; ptr->m[5] = s.y; ptr->m[10] = s.z;
	}

	void Matrix::scale(const Vector3& s) {
		scale(s, this);
	}

	bool Matrix::getTranslate(Vector3* ptr) const {
		ptr->x = m[12];
		ptr->y = m[13];
		ptr->z = m[14];

		return true;
	}

	//TOU AQUI
	//TOU AQUI
	//TOU AQUI
	//TOU AQUI
	//TOU AQUI
	bool Matrix::getRotate(Quaternion* ptr) const {
		//return decompose(NULL, rotation, NULL);
		return false;
	}

	bool Matrix::getScale(Vector3* ptr) const {
		Vector3 x(m[0], m[1], m[2]); 
		Vector3 y(m[4], m[5], m[6]);	
		Vector3 z(m[8], m[9], m[10]);

		ptr->x = x.length();			
		ptr->y = y.length();			
		ptr->z = z.length();

		return true;
	}

	//bool Matrix::separate(Vector3* ptrt, Quaternion* ptrr, Vector3* ptrs) const {

	//	// Nothing left to do.
	//	if (rotation == NULL)
	//		return true;

	//	// Scale too close to zero, can't decompose rotation.
	//	if (scaleX < MATH_TOLERANCE || scaleY < MATH_TOLERANCE || fabs(scaleZ) < MATH_TOLERANCE)
	//		return false;

	//	float rn;

	//	// Factor the scale out of the matrix axes.
	//	rn = 1.0f / scaleX;
	//	xaxis.x *= rn;
	//	xaxis.y *= rn;
	//	xaxis.z *= rn;

	//	rn = 1.0f / scaleY;
	//	yaxis.x *= rn;
	//	yaxis.y *= rn;
	//	yaxis.z *= rn;

	//	rn = 1.0f / scaleZ;
	//	zaxis.x *= rn;
	//	zaxis.y *= rn;
	//	zaxis.z *= rn;

	//	// Now calculate the rotation from the resulting matrix (axes).
	//	float trace = xaxis.x + yaxis.y + zaxis.z + 1.0f;

	//	if (trace > MATH_EPSILON)
	//	{
	//		float s = 0.5f / sqrt(trace);
	//		rotation->w = 0.25f / s;
	//		rotation->x = (yaxis.z - zaxis.y) * s;
	//		rotation->y = (zaxis.x - xaxis.z) * s;
	//		rotation->z = (xaxis.y - yaxis.x) * s;
	//	}
	//	else
	//	{
	//		// Note: since xaxis, yaxis, and zaxis are normalized, 
	//		// we will never divide by zero in the code below.
	//		if (xaxis.x > yaxis.y && xaxis.x > zaxis.z)
	//		{
	//			float s = 0.5f / sqrt(1.0f + xaxis.x - yaxis.y - zaxis.z);
	//			rotation->w = (yaxis.z - zaxis.y) * s;
	//			rotation->x = 0.25f / s;
	//			rotation->y = (yaxis.x + xaxis.y) * s;
	//			rotation->z = (zaxis.x + xaxis.z) * s;
	//		}
	//		else if (yaxis.y > zaxis.z)
	//		{
	//			float s = 0.5f / sqrt(1.0f + yaxis.y - xaxis.x - zaxis.z);
	//			rotation->w = (zaxis.x - xaxis.z) * s;
	//			rotation->x = (yaxis.x + xaxis.y) * s;
	//			rotation->y = 0.25f / s;
	//			rotation->z = (zaxis.y + yaxis.z) * s;
	//		}
	//		else
	//		{
	//			float s = 0.5f / sqrt(1.0f + zaxis.z - xaxis.x - yaxis.y);
	//			rotation->w = (xaxis.y - yaxis.x) * s;
	//			rotation->x = (zaxis.x + xaxis.z) * s;
	//			rotation->y = (zaxis.y + yaxis.z) * s;
	//			rotation->z = 0.25f / s;
	//		}
	//	}

	//	return true;
	//}

	void Matrix::upVector(Vector3* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->x = m[4]; ptr->y = m[5]; ptr->z = m[6];
	}

	void Matrix::downVector(Vector3* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}


		ptr->x = -m[4]; ptr->y = -m[5]; ptr->z = -m[6];
	}

	void Matrix::leftVector(Vector3* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->x = -m[0]; ptr->y = -m[1]; ptr->z = -m[2];
	}

	void Matrix::rightVector(Vector3* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->x = m[0]; ptr->y = m[1]; ptr->z = m[2];
	}

	void Matrix::frontVector(Vector3* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->x = -m[8]; ptr->y = -m[9]; ptr->z = -m[10];
	}

	void Matrix::backVector(Vector3* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->x = m[8]; ptr->y = m[9]; ptr->z = m[10];
	}

	void Matrix::transformPoint(const Vector3& p, Vector3* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->x = ((p.x * m[0]) + (p.y * m[4]) + (p.z * m[8]) + (1.0f * m[12]));
		ptr->y = ((p.x * m[1]) + (p.y * m[5]) + (p.z * m[9]) + (1.0f * m[13]));
		ptr->z = ((p.x * m[2]) + (p.y * m[6]) + (p.z * m[10]) + (1.0f * m[14]));
	}

	void Matrix::transformVector(const Vector3& v, Vector3* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}
		
		ptr->x = ((v.x * m[0]) + (v.y * m[4]) + (v.z * m[8]) + (0.0f * m[12]));
		ptr->y = ((v.x * m[1]) + (v.y * m[5]) + (v.z * m[9]) + (0.0f * m[13]));
		ptr->z = ((v.x * m[2]) + (v.y * m[6]) + (v.z * m[10]) + (0.0f * m[14]));
	}

	void Matrix::transformVector(const Vector4& v, Vector4* ptr) const	{
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->x = ((v.x * m[0]) + (v.y * m[4]) + (v.z * m[8]) + (v.w * m[12]));
		ptr->y = ((v.x * m[1]) + (v.y * m[5]) + (v.z * m[9]) + (v.w * m[13]));
		ptr->z = ((v.x * m[2]) + (v.y * m[6]) + (v.z * m[10]) + (v.w * m[14]));
		ptr->w = ((v.x * m[3]) + (v.y * m[7]) + (v.z * m[11]) + (v.w * m[15]));
	}
	
	void Matrix::add(const float s) {
		m[0] += s; m[1] += s; m[2] += s; m[3] += s;
		m[4] += s; m[5] += s; m[6] += s; m[7] += s;
		m[8] += s; m[9] += s; m[10] += s; m[11] += s;
		m[12] += s; m[13] += s; m[14] += s; m[15] += s;
	}

	void Matrix::add(const Matrix& m1, const Matrix& m2, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->m[0] = m1.m[0] + m2.m[0]; ptr->m[1] = m1.m[1] + m2.m[1];
		ptr->m[2] = m1.m[2] + m2.m[2]; ptr->m[3] = m1.m[3] + m2.m[3];
		ptr->m[4] = m1.m[4] + m2.m[4]; ptr->m[5] = m1.m[5] + m2.m[5];
		ptr->m[6] = m1.m[6] + m2.m[6]; ptr->m[7] = m1.m[7] + m2.m[7];
		ptr->m[8] = m1.m[8] + m2.m[8]; ptr->m[9] = m1.m[9] + m2.m[9];
		ptr->m[10] = m1.m[10] + m2.m[10]; ptr->m[11] = m1.m[11] + m2.m[11];
		ptr->m[12] = m1.m[12] + m2.m[12]; ptr->m[13] = m1.m[13] + m2.m[13];
		ptr->m[14] = m1.m[14] + m2.m[14]; ptr->m[15] = m1.m[15] + m2.m[15];
	}

	void Matrix::add(const Matrix& m) {
		add(*this, m, this);
	}

	void Matrix::subtract(const Matrix& m1, const Matrix& m2, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->m[0] = m1.m[0] - m2.m[0]; ptr->m[1] = m1.m[1] - m2.m[1];
		ptr->m[2] = m1.m[2] - m2.m[2]; ptr->m[3] = m1.m[3] - m2.m[3];
		ptr->m[4] = m1.m[4] - m2.m[4]; ptr->m[5] = m1.m[5] - m2.m[5];
		ptr->m[6] = m1.m[6] - m2.m[6]; ptr->m[7] = m1.m[7] - m2.m[7];
		ptr->m[8] = m1.m[8] - m2.m[8]; ptr->m[9] = m1.m[9] - m2.m[9];
		ptr->m[10] = m1.m[10] - m2.m[10]; ptr->m[11] = m1.m[11] - m2.m[11];
		ptr->m[12] = m1.m[12] - m2.m[12]; ptr->m[13] = m1.m[13] - m2.m[13];
		ptr->m[14] = m1.m[14] - m2.m[14]; ptr->m[15] = m1.m[15] - m2.m[15];
	}

	void Matrix::subtract(const Matrix& m) {
		subtract(*this, m, this);
	}

	void Matrix::multiply(float s) {
		m[0] *= s; m[1] *= s; m[2] *= s; m[3] *= s;
		m[4] *= s; m[5] *= s; m[6] *= s; m[7] *= s;
		m[8] *= s; m[9] *= s; m[10] *= s; m[11] *= s;
		m[12] *= s; m[13] *= s; m[14] *= s; m[15] *= s;
	}

	void Matrix::multiply(const Matrix& m1, const Matrix& m2, Matrix* ptr) {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}
		
		ptr->m[0] = ((m1.m[0] * m2.m[0]) + (m1.m[4] * m2.m[1]) +
			(m1.m[8] * m2.m[2]) + (m1.m[12] * m2.m[3]));
		ptr->m[1] = ((m1.m[1] * m2.m[0]) + (m1.m[5] * m2.m[1]) + 
			(m1.m[9] * m2.m[2]) + (m1.m[13] * m2.m[3]));
		ptr->m[2] = ((m1.m[2] * m2.m[0]) + (m1.m[6] * m2.m[1]) + 
			(m1.m[10] * m2.m[2]) + (m1.m[14] * m2.m[3]));
		ptr->m[3] = ((m1.m[3] * m2.m[0]) + (m1.m[7] * m2.m[1]) + 
			(m1.m[11] * m2.m[2]) + (m1.m[15] * m2.m[3]));

		ptr->m[4] = ((m1.m[0] * m2.m[4]) + (m1.m[4] * m2.m[5]) + 
			(m1.m[8] * m2.m[6]) + (m1.m[12] * m2.m[7]));
		ptr->m[5] = ((m1.m[1] * m2.m[4]) + (m1.m[5] * m2.m[5]) + 
			(m1.m[9] * m2.m[6]) + (m1.m[13] * m2.m[7]));
		ptr->m[6] = ((m1.m[2] * m2.m[4]) + (m1.m[6] * m2.m[5]) + 
			(m1.m[10] * m2.m[6]) + (m1.m[14] * m2.m[7]));
		ptr->m[7] = ((m1.m[3] * m2.m[4]) + (m1.m[7] * m2.m[5]) + 
			(m1.m[11] * m2.m[6]) + (m1.m[15] * m2.m[7]));

		ptr->m[8] = ((m1.m[0] * m2.m[8]) + (m1.m[4] * m2.m[9]) + 
			(m1.m[8] * m2.m[10]) + (m1.m[12] * m2.m[11]));
		ptr->m[9] = ((m1.m[1] * m2.m[8]) + (m1.m[5] * m2.m[9]) + 
			(m1.m[9] * m2.m[10]) + (m1.m[13] * m2.m[11]));
		ptr->m[10] = ((m1.m[2] * m2.m[8]) + (m1.m[6] * m2.m[9]) + 
			(m1.m[10] * m2.m[10]) + (m1.m[14] * m2.m[11]));
		ptr->m[11] = ((m1.m[3] * m2.m[8]) + (m1.m[7] * m2.m[9]) + 
			(m1.m[11] * m2.m[10]) + (m1.m[15] * m2.m[11]));

		ptr->m[12] = ((m1.m[0] * m2.m[12]) + (m1.m[4] * m2.m[13]) + 
			(m1.m[8] * m2.m[14]) + (m1.m[12] * m2.m[15]));
		ptr->m[13] = ((m1.m[1] * m2.m[12]) + (m1.m[5] * m2.m[13]) + 
			(m1.m[9] * m2.m[14]) + (m1.m[13] * m2.m[15]));
		ptr->m[14] = ((m1.m[2] * m2.m[12]) + (m1.m[6] * m2.m[13]) + 
			(m1.m[10] * m2.m[14]) + (m1.m[14] * m2.m[15]));
		ptr->m[15] = ((m1.m[3] * m2.m[12]) + (m1.m[7] * m2.m[13]) + 
			(m1.m[11] * m2.m[14]) + (m1.m[15] * m2.m[15]));
	}

	void Matrix::multiply(const Matrix& m) {
		multiply(*this, m, this);
	}
	
	bool Matrix::invert(Matrix* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return false;
		}

		//Matrix Determinant. Magic...
		float d = (((((m[0] * m[5]) - (m[1] * m[4]))) * (((m[10] * m[15]) - (m[11] * m[14])))) -
			((((m[0] * m[6]) - (m[2] * m[4]))) * (((m[9] * m[15]) - (m[11] * m[13])))) +
			((((m[0] * m[7]) - (m[3] * m[4]))) * (((m[9] * m[14]) - (m[10] * m[13])))) +
			((((m[1] * m[6]) - (m[2] * m[5]))) * (((m[8] * m[15]) - (m[11] * m[12])))) -
			((((m[1] * m[7]) - (m[3] * m[5]))) * (((m[8] * m[14]) - (m[10] * m[12])))) +
			((((m[2] * m[7]) - (m[3] * m[6]))) * (((m[8] * m[13]) - (m[9] * m[12])))));

		if (fabs(d) <= iron::IronMath::MATH_FLOAT_MIN) {
			return false;
		}

		for (int i = 1; i < 4; i++) {
			ptr->m[i] /= ptr->m[0];
		}

		for (int i = 1; i < 4; i++) {
			for (int j = i; j < 4; j++)  {
				float sum = 0.0f;
				for (int k = 0; k < i; k++) {
					sum += ptr->m[((j * 4) + k)] * ptr->m[((k * 4) + i)];
				}

				ptr->m[((j * 4) + i)] -= sum;
			}

			if (i == 3) {
				continue;
			}

			for (int j = i + 1; j < 4; j++) {
				float sum = 0.0f;
				for (int k = 0; k < i; k++) {
					sum += ptr->m[((i * 4) + k)] * ptr->m[((k * 4) + j)];
				}

				ptr->m[((i * 4) + j)] = (ptr->m[((i * 4) + j)] - sum) / ptr->m[((i * 4) + i)];
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = i; j < 4; j++)  {
				float x = 1.0;
				if (i != j) {
					x = 0.0f;
					for (int k = i; k < j; k++) {
						x -= ptr->m[((j * 4) + k)] * ptr->m[((k * 4) + i)];
					}
				}

				ptr->m[((j * 4) + i)] = x / ptr->m[((j * 4) + j)];
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = i; j < 4; j++)  {
				if (i == j) {
					continue;
				}

				float sum = 0.0f;
				for (int k = i; k < j; k++) {
					sum += ((float)ptr->m[((k * 4) + j)] * ((i == k) ? 1.0f : ptr->m[i * 4 + k]));
				}

				ptr->m[i * 4 + j] = -sum;
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)  {
				float sum = 0.0f;
				for (int k = ((i>j) ? i : j); k < 4; k++) {
					sum += ((float)((j == k) ? 1.0f : ptr->m[((j * 4) + k)]) * ptr->m[((k * 4) + i)]);
				}

				ptr->m[((j * 4) + i)] = sum;
			}
		}

		return true;

		//float a0 = m[0] * m[5] - m[1] * m[4];
		//float a1 = m[0] * m[6] - m[2] * m[4];
		//float a2 = m[0] * m[7] - m[3] * m[4];
		//float a3 = m[1] * m[6] - m[2] * m[5];
		//float a4 = m[1] * m[7] - m[3] * m[5];
		//float a5 = m[2] * m[7] - m[3] * m[6];
		//float b0 = m[8] * m[13] - m[9] * m[12];
		//float b1 = m[8] * m[14] - m[10] * m[12];
		//float b2 = m[8] * m[15] - m[11] * m[12];
		//float b3 = m[9] * m[14] - m[10] * m[13];
		//float b4 = m[9] * m[15] - m[11] * m[13];
		//float b5 = m[10] * m[15] - m[11] * m[14];

		//// Calculate the determinant.
		//float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

		//// Close to zero, can't invert.
		//if (fabs(det) <= MATH_TOLERANCE)
		//	return false;

		//// Support the case where m == ptr.
		//Matrix inverse;
		//inverse.m[0] = m[5] * b5 - m[6] * b4 + m[7] * b3;
		//inverse.m[1] = -m[1] * b5 + m[2] * b4 - m[3] * b3;
		//inverse.m[2] = m[13] * a5 - m[14] * a4 + m[15] * a3;
		//inverse.m[3] = -m[9] * a5 + m[10] * a4 - m[11] * a3;

		//inverse.m[4] = -m[4] * b5 + m[6] * b2 - m[7] * b1;
		//inverse.m[5] = m[0] * b5 - m[2] * b2 + m[3] * b1;
		//inverse.m[6] = -m[12] * a5 + m[14] * a2 - m[15] * a1;
		//inverse.m[7] = m[8] * a5 - m[10] * a2 + m[11] * a1;

		//inverse.m[8] = m[4] * b4 - m[5] * b2 + m[7] * b0;
		//inverse.m[9] = -m[0] * b4 + m[1] * b2 - m[3] * b0;
		//inverse.m[10] = m[12] * a4 - m[13] * a2 + m[15] * a0;
		//inverse.m[11] = -m[8] * a4 + m[9] * a2 - m[11] * a0;

		//inverse.m[12] = -m[4] * b3 + m[5] * b1 - m[6] * b0;
		//inverse.m[13] = m[0] * b3 - m[1] * b1 + m[2] * b0;
		//inverse.m[14] = -m[12] * a3 + m[13] * a1 - m[14] * a0;
		//inverse.m[15] = m[8] * a3 - m[9] * a1 + m[10] * a0;

		//multiply(inverse, 1.0f / det, ptr);

		//return true;
	}

	bool Matrix::invert() {
		return invert(this);
	}

	void Matrix::negate(Matrix* ptr) const {
		if (ptr == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		ptr->m[0] = -m[0]; ptr->m[1] = -m[1]; ptr->m[2] = -m[2]; ptr->m[3] = -m[3];
		ptr->m[4] = -m[4]; ptr->m[5] = -m[5]; ptr->m[6] = -m[6]; ptr->m[7] = -m[7];
		ptr->m[8] = -m[8]; ptr->m[9] = -m[9]; ptr->m[10] = -m[10]; ptr->m[11] = -m[11];
		ptr->m[12] = -m[12]; ptr->m[13] = -m[13]; ptr->m[14] = -m[14]; ptr->m[15] = -m[15];
	}

	void Matrix::negate() {
		negate(this);
	}
	
	const Matrix& Matrix::identity() {
		static Matrix m(1, 0, 0, 0, 0, 1, 0, 0,	0, 0, 1, 0,	0, 0, 0, 1);
		return m;
	}

	void Matrix::setIdentity() {
		set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}

	bool Matrix::isIdentity() const {
		return (memcmp(m, IDENTITY.m, ((size_t)MATRIX_SIZE)) == 0);
	}

	const Matrix& Matrix::zero() {
		static Matrix m(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		return m;
	}

	void Matrix::setZero() {
		set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	bool Matrix::isZero() const {
		return (memcmp(m, ZERO.m, ((size_t)MATRIX_SIZE)) == 0);
	}
	
	void Matrix::set(const float x1y1, const float x2y1, const float x3y1, const float x4y1,
		const float x1y2, const float x2y2, const float x3y2, const float x4y2,
		const float x1y3, const float x2y3, const float x3y3, const float x4y3,
		const float x1y4, const float x2y4, const float x3y4, const float x4y4)
	{
		m[0] = x1y1;
		m[1] = x2y1;
		m[2] = x3y1;
		m[3] = x4y1;
		m[4] = x1y2;
		m[5] = x2y2;
		m[6] = x3y2;
		m[7] = x4y2;
		m[8] = x1y3;
		m[9] = x2y3;
		m[10] = x3y3;
		m[11] = x4y3;
		m[12] = x1y4;
		m[13] = x2y4;
		m[14] = x3y4;
		m[15] = x4y4;
	}

	void Matrix::set(const float* a) {
		memcpy(this->m, a, ((size_t)MATRIX_SIZE));
	}

	void Matrix::set(const Matrix& m) {
		memcpy(this->m, m.m, ((size_t)MATRIX_SIZE));
	}
}
