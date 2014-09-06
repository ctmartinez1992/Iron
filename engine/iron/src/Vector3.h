#ifndef IRON_MATH_VECTOR3_H_
#define IRON_MATH_VECTOR3_H_

#include "IronMath.h"

namespace iron {

	/*! \brief Defines a floating point vector with 3 coordinates.
	*
	*  Defines a floating point vector with 3 coordinates along with a set of helpful functions.
	*/
	class Vector3 {
		/****************************** Variables ******************************/
	private:

	protected:

	public:
		float					x;			/*!< X coordinate. */
		float					y;			/*!< Y coordinate. */
		float					z;			/*!< Z coordinate. */

		const static Vector3	GRAVITY;	/*!< Y value set to the gravity constant. */
		const static Vector3	LEFT;		/*!< Left vector. */
		const static Vector3	RIGHT;		/*!< Right vector. */
		const static Vector3	UP;			/*!< Up vector. */
		const static Vector3	DOWN;		/*!< Down vector. */
		const static Vector3	FRONT;		/*!< Front vector. */
		const static Vector3	BACK;		/*!< Back vector. */

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Constructs a new 3D vector with coordinates initialized to 0 value.
		*/
		Vector3();

		/**
		* Constructs a new 3D vector with coordinates initialized to the given float values.
		*
		* @param x X coordinate.
		* @param y Y coordinate.
		* @param z Z coordinate.
		*/
		explicit Vector3(const float x, const float y, const float z);

		/**
		* Constructs a new 3D vector based on the direction between the given vectors.
		*
		* @param p1 First point.
		* @param p2 Second point.
		*/
		Vector3(const Vector3& p1, const Vector3& p2);

		/**
		* Constructs a new 3D vector that is a copy of the given vector.
		*
		* @param vector Vector to copy.
		*/
		Vector3(const Vector3& vector);

		/**
		* Destructor.
		*/
		~Vector3();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Returns a 3D vector with coordinates set to the 0 value.
		*
		* @return 3D vector with coordinates set to the 0 value.
		*/
		static const Vector3& zero();

		/**
		* Returns a 3D vector with coordinates set to the 1 value. Stands for "Positive One".
		*
		* @return 3D vector with coordinates set to the 1 value.
		*/
		static const Vector3& pOne();

		/**
		* Returns a 3D vector with coordinates set to the -1 value. Stands for "Negative One".
		*
		* @return 3D vector with coordinates set to the -1 value.
		*/
		static const Vector3& nOne();

		/**
		* Returns a 3D vector set along the positive x axis. Stands for "Positive X".
		*
		* @return 3D vector set along the positive x axis.
		*/
		static const Vector3& pX();

		/**
		* Returns a 3D vector set along the negative x axis. Stands for "Negative X".
		*
		* @return 3D vector set along the negative x axis.
		*/
		static const Vector3& nX();

		/**
		* Returns a 3D vector set along the positive y axis. Stands for "Positive Y".
		*
		* @return 3D vector set along the positive y axis.
		*/
		static const Vector3& pY();

		/**
		* Returns a 3D vector set along the negative y axis. Stands for "Negative Y".
		*
		* @return 3D vector set along the negative y axis.
		*/
		static const Vector3& nY();

		/**
		* Returns a 3D vector set along the positive z axis. Stands for "Positive Z".
		*
		* @return 3D vector set along the positive z axis.
		*/
		static const Vector3& pZ();

		/**
		* Returns a 3D vector set along the negative z axis. Stands for "Negative Z".
		*
		* @return 3D vector set along the negative z axis.
		*/
		static const Vector3& nZ();

		/**
		* Tells if the vector coordinates are set to the value 0.
		*
		* @return true if this vector coordinates are set to the value 0, false if not.
		*
		* @see isOne, isNOne
		*/
		bool isZero() const;

		/**
		* Tells if the vector coordinates are set to the value 1.
		*
		* @return true if this vector coordinates are set to the value 1, false if not.
		*
		* @see isZero, isNOne
		*/
		bool isOne() const;

		/**
		* Tells if the vector coordinates are set to the value -1.
		*
		* @return true if this vector coordinates are set to the value -1, false if not.
		*
		* @see isZero, isOne
		*/
		bool isNOne() const;

		/**
		* Negates this vector. Does not mean the result yields a vector of negative values.
		*/
		void negate();

		/**
		* Adds the given float values to this vector.
		*
		* @param x The value to be added to the x coordinate.
		* @param y The value to be added to the y coordinate.
		* @param z The value to be added to the z coordinate.
		*/
		void add(const float x, const float y, const float z);

		/**
		* Adds the elements of the given vector to this one.
		*
		* @param vector The vector to add.
		*/
		void add(const Vector3& vector);

		/**
		* Adds the given vectors and stores the result in ptr.
		*
		* @param v1 The first vector.
		* @param v2 The second vector.
		* @param ptr The vector that stores the result.
		*/
		static void add(const Vector3& v1, const Vector3& v2, Vector3* ptr);

		/**
		* Subtracts the given float values to this vector.
		*
		* @param x The value to be subtracted to the x coordinate.
		* @param y The value to be subtracted to the y coordinate.
		* @param z The value to be subtracted to the z coordinate.
		*/
		void subtract(const float x, const float y, const float z);

		/**
		* Subtracts the elements of the given vector to this one.
		*
		* @param vector The vector to subtract.
		*/
		void subtract(const Vector3& vector);

		/**
		* Subtracts the given vectors and stores the result in ptr.
		*
		* @param v1 The first vector.
		* @param v2 The second vector.
		* @param ptr The vector that stores the result.
		*/
		static void subtract(const Vector3& v1, const Vector3& v2, Vector3* ptr);

		/**
		* Scales the coordinates in this vector by the given float value.
		*
		* @param scalar The scalar value.
		*/
		void scale(const float scalar);

		/**
		* Scales the coordinates in this vector by the given float value and stores the result in
		* ptr.
		*
		* @param scalar The scalar value.
		* @param ptr The vector that stores the result.
		*/
		void scale(const float scalar, Vector3* ptr) const;

		/**
		* Divides the coordinates in this vector by the given float value.
		*
		* @param denominator The denominator value.
		*/
		void divide(const float denominator);

		/**
		* Divides the coordinates in this vector by the given float value and stores the result in ptr.
		*
		* @param denominator The denominator value.
		* @param ptr The vector that stores the result.
		*/
		void divide(const float denominator, Vector3* ptr) const;

		/**
		* Adds the given vector to this, scaled by the given amount.
		*
		* @param vector The vector to add.
		* @param scale The value that scales the given vector.
		*/
		void addScaledVector(const Vector3& vector, float scale);

		/**
		* Calculates the length of this vector.
		*
		* @return The length of this vector.
		*
		* @see lengthSquared
		*/
		float length() const;

		/**
		* Calculates the squared length of this vector.
		*
		* @return The squared length of this vector.
		*
		* @see length
		*/
		float lengthSquared() const;

		/**
		* Calculates the distance between this vector and the given vector.
		*
		* @param vector The other vector.
		* @return The distance between this vector and the given vector.
		*
		* @see distanceSquared
		*/
		float distance(const Vector3& vector) const;

		/**
		* Calculates the squared distance between this vector and the given vector.
		*
		* @param vector The other vector.
		* @return The squared distance between this vector and the given vector.
		*
		* @see distance
		*/
		float distanceSquared(const Vector3& vector) const;

		/**
		* Calculates the dot product between the given vectors.
		*
		* @param v1 The first vector.
		* @param v2 The second vector.
		* @return The dot product between the given vectors.
		*/
		static float dot(const Vector3& v1, const Vector3& v2);

		/**
		* Calculates the dot product between this vector and the given vector.
		*
		* @param vector The vector used in the calculation of the dot product.
		* @return The dot product.
		*/
		float dot(const Vector3& vector) const;

		/**
		* Calculates the cross product between the given vectors.
		*
		* @param v1 The first vector.
		* @param v2 The second vector.
		* @param ptr The cross product between the given vectors.
		*/
		static void cross(const Vector3& v1, const Vector3& v2, Vector3* ptr);

		/**
		* Calculates the cross product between this vector and the given vector. Stores the result in
		* this vector.
		*
		* @param vector The vector used in the calculation of the cross product.
		*/
		void cross(const Vector3& vector);

		/**
		* Normalizes the given vector and stores the result in ptr.
		*
		* @param vector The vector with the values.
		* @param ptr The vector that will store the result.
		*/
		static void normalize(const Vector3& vector, Vector3* ptr);

		/**
		* Normalizes this vector and stores the result in this vector.
		*
		* @return This vector with the result of the normalization.
		*/
		Vector3& normalize();

		/**
		* Normalizes this vector and stores the result in the ptr.
		*
		* @return The result of the normalization in ptr.
		*/
		void normalize(Vector3* ptr) const;

		/**
		* Clamps the given vector within the given minX, minY, maxX and maxY values and stores the
		* result in ptr.
		*
		* @param vector The vector to clamp.
		* @param minX The minimum x value.
		* @param minY The minimum y value.
		* @param minZ The minimum y value.
		* @param maxX The maximum x value.
		* @param maxY The maximum y value.
		* @param maxZ The maximum y value.
		* @param ptr A pointer to a Vector3 object to store the result in.
		*/
		static void clamp(const Vector3& vector, const float minX, const float minY, const float minZ, 
			const float maxX, const float maxY, const float maxZ, Vector3* ptr);

		/**
		* Clamps the given vector within the given min and max values and stores the result in ptr.
		*
		* @param vector The vector to clamp.
		* @param min The minimum value.
		* @param max The maximum value.
		* @param ptr A pointer to a Vector3 object to store the result in.
		*/
		static void clamp(const Vector3& vector, const Vector3& min, const Vector3& max, Vector3* ptr);

		/**
		* Clamps this vector within the given minX, minY, maxX and maxY values and stores the result in
		* this vector.
		*
		* @param minX The minimum x value.
		* @param minY The minimum y value.
		* @param minZ The minimum y value.
		* @param maxX The maximum x value.
		* @param maxY The maximum y value.
		* @param maxZ The maximum y value.
		*/
		void clamp(const float minX, const float minY, const float minZ, const float maxX, 
			const float maxY, const float maxZ);

		/**
		* Clamps this vector within the given min and max values and stores the result in this vector.
		*
		* @param min The minimum value.
		* @param max The maximum value.
		*/
		void clamp(const Vector3& min, const Vector3& max);

		/**
		* Sets the elements of this vector to the given int values. It never initializes them, only
		* assigns.
		*
		* @param x The new x coordinate.
		* @param y The new y coordinate.
		* @param z The new z coordinate.
		*/
		void set(const int x, const int y, const int z);

		/**
		* Sets the elements of this vector to the given float values. It never initializes them, only
		* assigns.
		*
		* @param x The new x coordinate.
		* @param y The new y coordinate.
		* @param z The new z coordinate.
		*/
		void set(const float x, const float y, const float z);

		/**
		* Sets the elements of this vector to the given double values. It never initializes them, only
		* assigns.
		*
		* @param x The new x coordinate.
		* @param y The new y coordinate.
		* @param z The new z coordinate.
		*/
		void set(const double x, const double y, const double z);

		/**
		* Sets this vector to the directional vector between the given points. It never initializes
		* them, only assigns.
		*
		* @param p1 The first point.
		* @param p2 The second point.
		*/
		void set(const Vector3& p1, const Vector3& p2);

		/**
		* Copies the elements of the given vector to this vector. It never initializes them, only
		* assigns.
		*
		* @param vector The vector to copy.
		*/
		void set(const Vector3& vector);

		/****************************** Operators Overloading ******************************/
	private:

	protected:

	public:
		/**
		* This vector gets assigned the values in the given vector.
		*
		* @param vector The vector to read its coordinates.
		* @return This vector with a new set of values.
		*/
		inline const Vector3 operator=(const Vector3& vector);

		/**
		* Determines if this vector is equal to the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is equal to the given vector, false if not.
		*/
		inline bool operator==(const Vector3& vector) const;

		/**
		* Determines if this vector is not equal to the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is not equal to the given vector, false if not.
		*/
		inline bool operator!=(const Vector3& vector) const;

		/**
		* Determines if this vector is below the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is below the given vector, false if not.
		*/
		inline bool operator<(const Vector3& vector) const;

		/**
		* Determines if this vector is below or equal to the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is below or equal to the given vector, false if not.
		*/
		inline bool operator<=(const Vector3& vector) const;

		/**
		* Determines if this vector is above the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is above the given vector, false if not.
		*/
		inline bool operator>(const Vector3& vector) const;

		/**
		* Determines if this vector is above or equal to the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is above or equal to the given vector, false if not.
		*/
		inline bool operator>=(const Vector3& vector) const;

		/**
		* Calculates the sum of this vector with the given vector. This vector and the given one remain
		* unchanged.
		*
		* @param vector The vector to add.
		* @return The vector with the result of the addition.
		*/
		inline const Vector3 operator+(const Vector3& vector) const;

		/**
		* Adds the given vector to this vector.
		*
		* @param vector The vector to add.
		* @return This vector with the result of the addition.
		*/
		inline Vector3& operator+=(const Vector3& vector);

		/**
		* Calculates the subtraction of this vector with the given vector. This vector and the given
		* one remain unchanged.
		*
		* @param vector The vector to subtract.
		* @return The vector with the result of the subtraction.
		*/
		inline const Vector3 operator-(const Vector3& vector) const;

		/**
		* Subtracts the given vector to this vector.
		*
		* @param vector The vector to add.
		* @return This vector with the result of the subtraction.
		*/
		inline Vector3& operator-=(const Vector3& vector);

		/**
		* Calculates the negation of this vector. This vector remains unchanged.
		*
		* @return This vector negated.
		*/
		inline const Vector3 operator-() const;

		/**
		* Calculates the scalar product of this vector with the given value. This vector remains
		* unchanged.
		*
		* @param x The value used to scale.
		* @return The scaled vector.
		*/
		inline const Vector3 operator*(const float x) const;

		/**
		* Calculates the scalar product of this vector with the given value.
		*
		* @param x The value used to scale.
		* @return This vector with the result of the scaling.
		*/
		inline Vector3& operator*=(const float x);

		/**
		* Calculates the division between this vector values and the given value. This vector remains
		* unchanged.
		*
		* @param x the value used to divide.
		* @return The divided vector.
		*/
		inline const Vector3 operator/(const float x) const;

		/**
		* Calculates the division between this vector with the given value.
		*
		* @param x The value used to divide.
		* @return This vector with the result of the division.
		*/
		inline Vector3& operator/=(const float x);

		/**
		* Ensures array accessibility with square brackets.
		*
		* @param i The index to search the "array".
		* @return The value at the position.
		*/
		inline float& operator[](int i);
	};
}

#include "Vector3.inl"

#endif
