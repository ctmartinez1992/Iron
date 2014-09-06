#ifndef IRON_MATH_MATRIX_H_
#define IRON_MATH_MATRIX_H_

#include "Vector4.h"
#include "Quaternion.h"

class Quaternion;

namespace iron {

	/*! \brief Represents a 4 x 4 matrix.
	*
	* The matrix uses column-major format and its components are organized like an OpenGl translation 
	* matrix (compatible) which as the following aspect:
	*
	*   ——————————————
	*   ¦ 1  0  0  x ¦
	*   ¦ 0  1  0  y ¦
	*   ¦ 0  0  1  z ¦
	*   ¦ 0  0  0  1 ¦
	*   ——————————————
	*
	* Multiplication must be done in the the reverse order of operations. Rotation (Matrix R) and then 
	* translation (Matrix T) = RT.
	*
	* If multiple transformations are needed, the class Transform should be used instead of this one.
	*/
	class Matrix {
		/****************************** Variables ******************************/
	private:

	protected:

	public:
		float					m[16];			/*!< Holds the matrix data. */

		const static float		MATRIX_SIZE;	/*!< Size of a Matrix. */
		const static Matrix		ZERO;			/*!< Zero matrix. */
		const static Matrix		IDENTITY;		/*!< Identity matrix. */

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Constructs a new matrix equal to the matrix identity.
		*/
		Matrix();

		/**
		* Constructs a new matrix initialized with the given values.
		*
		* @param x1y1 The First column, First Row.
		* @param x2y1 The Second column, First Row.
		* @param x3y1 The Third column, First Row.
		* @param x4y1 The Fourth column, First Row.
		* @param x1y2 The First column, Second Row.
		* @param x2y2 The Second column, Second Row.
		* @param x3y2 The Third column, Second Row.
		* @param x4y2 The Fourth column, Second Row.
		* @param x1y3 The First column, Third Row.
		* @param x2y3 The Second column, Third Row.
		* @param x3y3 The Third column, Third Row.
		* @param x4y3 The Fourth column, Third Row.
		* @param x1y4 The First column, Fourth Row.
		* @param x2y4 The Second column, Fourth Row.
		* @param x3y4 The Third column, Fourth Row.
		* @param x4y4 The Fourth column, Fourth Row.
		*/
		Matrix(const float x1y1, const float x2y1, const float x3y1, const float x4y1,
			const float x1y2, const float x2y2, const float x3y2, const float x4y2,
			const float x1y3, const float x2y3, const float x3y3, const float x4y3,
			const float x1y4, const float x2y4, const float x3y4, const float x4y4);

		/**
		* Construct a new matrix initialized with the given array. since the matrix is column-major,
		* the given array must be provided in column-major as well.
		*
		* @param a The array with 16 floats exactly in column-major.
		*/
		Matrix(const float* a);

		/**
		* Constructs a new matrix with the values of the given matrix.
		*
		* @param m The matrix to copy.
		*/
		Matrix(const Matrix& m);

		/**
		* Destructor.
		*/
		~Matrix();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Simulates a camera with the given values and stores the result in ptr.
		*
		* @param eye The eye position.
		* @param point The target point (where the camera looks at).
		* @param up The up vector.
		* @param ptr The matrix that stores the result.
		*/
		static void lookAt(const Vector3& eye, const Vector3& point, const Vector3& up, Matrix* ptr);

		/**
		* Simulates a "eye-point" camera with the given values and stores the result in ptr.
		*
		* @param eyeX The eye x-coordinate position.
		* @param eyeY The eye y-coordinate position.
		* @param eyeZ The eye z-coordinate position.
		* @param pointX The target's center x-coordinate position.
		* @param pointY The target's center y-coordinate position.
		* @param pointZ The target's center z-coordinate position.
		* @param upX The up vector x-coordinate value.
		* @param upY The up vector y-coordinate value.
		* @param upZ The up vector z-coordinate value.
		* @param ptr The matrix that stores the result.
		*/
		static void lookAt(const float eyeX, const float eyeY, const float eyeZ,
			const float pointX, const float pointY, const float pointZ,
			const float upX, const float upY, const float upZ, Matrix* ptr);

		/**
		* Simulates an orthographic projection matrix which forms a square of visible space and stores the
		* result in ptr.
		*
		* @param w The width of the space.
		* @param h The height of the space.
		* @param zNear The distance to the near view plane in the z coordinate.
		* @param zFar The distance to the far view plane in the z coordinate.
		* @param ptr The matrix that stores the result.
		*/
		static void orthographic(const float w, const float h, const float zNear, const float zFar, 
			Matrix* ptr);

		/**
		* Simulates a perspective projection matrix with the given values and stores the result in ptr.
		*
		* @param fov The field of view in the y coordinate (degrees). Clamped between 30 and 180 degrees.
		* @param aspect The aspect ratio (width/height).
		* @param zNear The distance to the near view plane in the z coordinate.
		* @param zFar The distance to the far view plane in the z coordinate.
		* @param ptr The matrix that stores the result.
		*/
		static void perspective(const float fov, const float aspect, const float zNear, const float zFar,
			Matrix* ptr);

		/**
		* Translates this matrix with the given values and stores the result in ptr.
		*
		* @param x The translation value applied on the x coordinate.
		* @param y The translation value applied on the y coordinate.
		* @param z The translation value applied on the z coordinate.
		* @param ptr The matrix that stores the result.
		*/
		void translate(const float x, const float y, const float z, Matrix* ptr);

		/**
		* Translates this matrix by the given values.

		* @param x The translation value applied on the x coordinate.
		* @param y The translation value applied on the y coordinate.
		* @param z The translation value applied on the z coordinate.
		*/
		void translate(const float x, const float y, const float z);

		/**
		* Translates this matrix with the given vector and stores the result in ptr.
		*
		* @param t The translation vector.
		* @param ptr The matrix that stores the result.
		*/
		void translate(const Vector3& t, Matrix* ptr);

		/**
		* Translates this matrix with the given vector.
		*
		* @param t The translation vector.
		*/
		void translate(const Vector3& t);

		/**
		* Rotates this matrix with the given quaternion's matrix rotation and stores the result in ptr.
		*
		* @param q The quaternion to rotate by.
		* @param ptr The matrix that stores the result.
		*/
		void rotate(const Quaternion& q, Matrix* ptr);

		/**
		* Rotates this matrix with the given quaternion's matrix rotation.
		*
		* @param q The quaternion to rotate by.
		*/
		void rotate(const Quaternion& q);

		/**
		* Rotates this matrix around the result of the rotation between the given axis and angle,
		* stores the result in ptr.
		*
		* @param axis The axis of the rotation.
		* @param a The angle of the rotation (radians).
		* @param ptr The matrix that stores the result.
		*/
		void rotate(const Vector3& axis, const float a, Matrix* ptr);

		/**
		* Rotates this matrix with the given vector by the given rotation.
		*
		* @param axis The axis of the rotation
		* @param a The angle of the rotation (radians).
		*/
		void rotate(const Vector3& axis, const float a);

		/**
		* Rotates this matrix around the x axis.
		*
		* @param a The angle of the rotation (radians).
		* @param ptr The matrix that stores the result.
		*/
		void rotateX(const float a, Matrix* ptr);

		/**
		* Rotates this matrix around the x axis.
		*
		* @param a The angle of the rotation (radians).
		*/
		void rotateX(const float a);

		/**
		* Rotates this matrix around the y axis.
		*
		* @param a The angle of the rotation (radians).
		* @param ptr The matrix that stores the result.
		*/
		void rotateY(const float a, Matrix* ptr);

		/**
		* Rotates this matrix around the y axis.
		*
		* @param a The angle of the rotation (radians).
		*/
		void rotateY(const float a);

		/**
		* Rotates this matrix around the z axis.
		*
		* @param a The angle of the rotation (radians).
		* @param ptr The matrix that stores the result.
		*/
		void rotateZ(float a, Matrix* ptr);

		/**
		* Rotates this matrix around the z axis.
		*
		* @param a The angle of the rotation (radians).
		*/
		void rotateZ(const float a);

		/**
		* Scales this matrix by the given value and stores the result in ptr.
		*
		* @param s The amount to scale.
		* @param ptr The matrix that stores the result.
		*/
		void scale(const float s, Matrix* ptr);

		/**
		* Scales this matrix by the given value.
		*
		* @param s The amount to scale
		*/
		void scale(const float s);

		/**
		* Scales this matrix by the given values and stores the result in ptr.
		*
		* @param x The amount to scale along the x coordinate.
		* @param y The amount to scale along the y coordinate.
		* @param z The amount to scale along the z coordinate.
		* @param ptr The matrix that stores the result.
		*/
		void scale(const float x, const float y, const float z, Matrix* ptr);

		/**
		* Scales this matrix by the given values.
		*
		* @param x The amount to scale along the x coordinate.
		* @param y The amount to scale along the y coordinate.
		* @param z The amount to scale along the z coordinate.
		*/
		void scale(const float x, const float y, const float z);

		/**
		* Scales this matrix by the given vector and stores the result in ptr.
		*
		* @param s The vector with the scaling values.
		* @param ptr The matrix that stores the result.
		*/
		void scale(const Vector3& s, Matrix* ptr);

		/**
		* Scales this matrix by the given vector.
		*
		* @param s The vector with the scaling values.
		*/
		void scale(const Vector3& s);

		/**
		* Gets the translate component of this matrix and stores the result in ptr.
		*
		* @param ptr The vector that stores the result.
		* @return true If it successfully separated the translate component from the matrix, false if
		* not.
		*/
		bool getTranslate(Vector3* ptr) const;

		/**
		* Gets the rotation component of this matrix and stores the result in ptr.
		*
		* @param ptr The vector that stores the result.
		* @return true If it successfully separated the rotation component from the matrix, false if not.
		*/
		bool getRotate(Quaternion* ptr) const;

		/**
		* Gets the scalar component of this matrix and stores the result in ptr.
		*
		* @param ptr The vector that stores the result.
		* @return true If it successfully separated the scalar component from the matrix, false if not.
		*/
		bool getScale(Vector3* ptr) const;

		/**
		* Gets the up vector of this matrix and stores the result in ptr.
		*
		* @param ptr The vector that stores the result.
		*/
		void upVector(Vector3* ptr) const;

		/**
		* Gets the down vector of this matrix and stores the result in ptr.
		*
		* @param ptr The vector that stores the result.
		*/
		void downVector(Vector3* ptr) const;

		/**
		* Gets the left vector of this matrix and stores the result in ptr.
		*
		* @param ptr The vector that stores the result.
		*/
		void leftVector(Vector3* ptr) const;

		/**
		* Gets the right vector of this matrix and stores the result in ptr.
		*
		* @param ptr The vector that stores the result.
		*/
		void rightVector(Vector3* ptr) const;

		/**
		* Gets the front vector of this matrix and stores the result in ptr.
		*
		* @param ptr The vector that stores the result.
		*/
		void frontVector(Vector3* ptr) const;

		/**
		* Gets the back vector of this matrix and stores the result in ptr.
		*
		* @param ptr The vector that stores the result.
		*/
		void backVector(Vector3* ptr) const;

		/**
		* Transforms the given point with this matrix and stores the result in ptr.
		*
		* @param p The point.
		* @param ptr The vector that stores the result.
		*/
		void transformPoint(const Vector3& p, Vector3* ptr) const;

		/**
		* Transforms the given vector with this matrix by and stores the result in ptr.
		*
		* @param v The vector.
		* @param ptr The vector that stores the result.
		*/
		void transformVector(const Vector3& v, Vector3* ptr) const;

		/**
		* Transforms the given vector with this matrix by and stores the result in ptr.
		*
		* @param v The vector.
		* @param ptr The vector that stores the result.
		*/
		void transformVector(const Vector4& v, Vector4* ptr) const;

		/**
		* Adds the given float value to all components of this matrix. Negative scalar for subtraction.
		*
		* @param s The scalar.
		*/
		void add(const float s);

		/**
		* Adds the given matrices and stores the result in ptr.
		*
		* @param m1 The first matrix.
		* @param m2 The second matrix.
		* @param ptr The matrix that stores the result.
		*/
		static void add(const Matrix& m1, const Matrix& m2, Matrix* ptr);

		/**
		* Adds the given matrix to this matrix.
		*
		* @param m The matrix to add.
		*/
		void add(const Matrix& m);

		/**
		* Subtracts the given matrices and stores the result in ptr.
		*
		* @param m1 The first matrix.
		* @param m2 The second matrix.
		* @param ptr The matrix that stores the result.
		*/
		static void subtract(const Matrix& m1, const Matrix& m2, Matrix* ptr);

		/**
		* Subtracts the given matrix to this matrix.
		*
		* @param m The matrix to add.
		*/
		void subtract(const Matrix& m);
		
		/**
		* Multiplies the given float value to all components of this matrix.
		*
		* @param s The scalar.
		*/
		void multiply(float s);

		/**
		* Multiplies the given matrices and stores the result in ptr.
		*
		* @param m1 The first matrix.
		* @param m2 The second matrix.
		* @param ptr The matrix that stores the result.
		*/
		static void multiply(const Matrix& m1, const Matrix& m2, Matrix* ptr);

		/**
		* Multiplies the given matrix to this matrix.
		*
		* @param m The matrix to multiply with.
		*/
		void multiply(const Matrix& m);

		/**
		* Stores the inverse of this matrix in the specified matrix.
		*
		* @param ptr A matrix to store the invert of this matrix in.
		*
		* @return true if the the matrix can be inverted, false otherwise.
		*/
		bool invert(Matrix* ptr) const;

		/**
		* Inverts this matrix.
		*
		* @return true if the the matrix can be inverted, false otherwise.
		*/
		bool invert();

		/**
		* Negates this matrix and stores the result in ptr.
		*
		* @param ptr A matrix to store the result in.
		*/
		void negate(Matrix* ptr) const;

		/**
		* Negates this matrix.
		*/
		void negate();

		/**
		* Returns the identity matrix.
		*
		* @return The identity matrix.
		*/
		static const Matrix& identity();

		/**
		* Sets this matrix to be equal to an identity matrix.
		*/
		void setIdentity();

		/**
		* Returns true if this matrix is equal to an identity matrix. Otherwise, false.
		*
		* @return true if this matrix is equal to an identity matrix. Otherwise, false.
		*/
		bool isIdentity() const;

		/**
		* Returns the "zeroed" matrix.
		*
		* @return The "zeroed" matrix.
		*/
		static const Matrix& zero();

		/**
		* Sets this matrix to be equal to a "zeroed" matrix.
		*/
		void setZero();

		/**
		* Returns true if this matrix is equal to a "zeroed" matrix. Otherwise, false.
		*
		* @return true if this matrix is equal to a "zeroed" matrix. Otherwise, false.
		*/
		bool isZero() const;
		
		/**
		* Sets this matrix with the given values.
		*
		* @param x1y1 The First column, First Row.
		* @param x2y1 The Second column, First Row.
		* @param x3y1 The Third column, First Row.
		* @param x4y1 The Fourth column, First Row.
		* @param x1y2 The First column, Second Row.
		* @param x2y2 The Second column, Second Row.
		* @param x3y2 The Third column, Second Row.
		* @param x4y2 The Fourth column, Second Row.
		* @param x1y3 The First column, Third Row.
		* @param x2y3 The Second column, Third Row.
		* @param x3y3 The Third column, Third Row.
		* @param x4y3 The Fourth column, Third Row.
		* @param x1y4 The First column, Fourth Row.
		* @param x2y4 The Second column, Fourth Row.
		* @param x3y4 The Third column, Fourth Row.
		* @param x4y4 The Fourth column, Fourth Row.
		*/
		void set(const float x1y1, const float x2y1, const float x3y1, const float x4y1,
			const float x1y2, const float x2y2, const float x3y2, const float x4y2,
			const float x1y3, const float x2y3, const float x3y3, const float x4y3,
			const float x1y4, const float x2y4, const float x3y4, const float x4y4);

		/**
		* Sets this matrix with the given array. since the matrix is column-major, the given array
		* must be provided in column-major as well.
		*
		* @param a The array with 16 floats exactly in column-major.
		*/
		void set(const float* a);

		/**
		* Sets this matrix with given matrix.
		*
		* @param m The matrix to copy.
		*/
		void set(const Matrix& m);

		/****************************** Operators Overloading ******************************/
	private:

	protected:

	public:
		/**
		* Calculates the sum of this matrix with the given matrix. This matrix and the given one remain
		* unchanged.
		*
		* @param m The matrix to add.
		* @return The matrix with the result of the addition.
		*/
		inline const Matrix operator+(const Matrix& m) const;

		/**
		* Adds the given matrix to this matrix.
		*
		* @param m The matrix to add.
		* @return This matrix with the result of the addition.
		*/
		inline Matrix& operator+=(const Matrix& m);

		/**
		* Calculates the subtraction of this matrix with the given matrix. This matrix and the given
		* one remain unchanged.
		*
		* @param m The matrix to subtract.
		* @return The matrix with the result of the subtraction.
		*/
		inline const Matrix operator-(const Matrix& m) const;

		/**
		* Subtracts the given matrix to this matrix.
		*
		* @param m The matrix to subtract.
		* @return The matrix with the result of the subtraction.
		*/
		inline Matrix& operator-=(const Matrix& m);

		/**
		* Calculates the negation of this matrix. This matrix remains unchanged.
		*
		* @return This matrix negated.
		*/
		inline const Matrix operator-() const;

		/**
		* Calculates the matrix product of this matrix with the given matrix. This matrix remains
		* unchanged.
		*
		* @param m The matrix to multiply by.
		* @return This matrix with the result of the product.
		*/
		inline const Matrix operator*(const Matrix& m) const;

		/**
		* Multiplies this matrix with the given matrix.
		*
		* @param m The matrix to multiply by.
		* @return This matrix with the result of the product.
		*/
		inline Matrix& operator*=(const Matrix& m);

	};
}

#include "Matrix.inl"

#endif
