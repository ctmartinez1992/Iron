#ifndef VECTOR2_H_
#define VECTOR2_H_

#include "IronMath.h"

namespace iron {

	/*! \brief Defines a floating point vector with 2 coordinates.
	*
	*  Defines a floating point vector with 2 coordinates along with a set of helpful functions.
	*/
	class Vector2 {
		/****************************** Variables ******************************/
	private:

	protected:

	public:
		float			x;		/*!< X coordinate. */
		float			y;		/*!< Y coordinate. */

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Constructs a new 2D vector with coordinates initialized to 0 value.
		*/
		Vector2();

		/**
		* Constructs a new 2D vector with coordinates initialized to the given float values.
		*
		* @param x X coordinate.
		* @param y Y coordinate.
		*/
		explicit Vector2(const float x, const float y);

		/**
		* Constructs a new 2D vector based on the direction between the given vectors.
		*
		* @param p1 First point.
		* @param p2 Second point.
		*/
		Vector2(const Vector2& p1, const Vector2& p2);

		/**
		* Constructs a new 2D vector that is a copy of the given vector.
		*
		* @param vector Vector to copy.
		*/
		Vector2(const Vector2& vector);

		/**
		* Destructor.
		*/
		~Vector2();

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Returns a 2D vector with coordinates set to the 0 value.
		*
		* @return 2D vector with coordinates set to the 0 value.
		*/
		static const Vector2& zero();

		/**
		* Returns a 2D vector with coordinates set to the 1 value. Stands for "Positive One".
		*
		* @return 2D vector with coordinates set to the 1 value.
		*/
		static const Vector2& pOne();

		/**
		* Returns a 2D vector with coordinates set to the -1 value. Stands for "Negative One".
		*
		* @return 2D vector with coordinates set to the -1 value.
		*/
		static const Vector2& nOne();

		/**
		* Returns a 2D vector set along the positive x axis. Stands for "Positive X".
		*
		* @return 2D vector set along the positive x axis.
		*/
		static const Vector2& pX();

		/**
		* Returns a 2D vector set along the negative x axis. Stands for "Negative X".
		*
		* @return 2D vector set along the negative x axis.
		*/
		static const Vector2& nX();

		/**
		* Returns a 2D vector set along the positive y axis. Stands for "Positive Y".
		*
		* @return 2D vector set along the positive y axis.
		*/
		static const Vector2& pY();

		/**
		* Returns a 2D vector set along the negative y axis. Stands for "Negative Y".
		*
		* @return 2D vector set along the negative y axis.
		*/
		static const Vector2& nY();
		
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
		*/
		void add(const float x, const float y);

		/**
		* Adds the elements of the given vector to this one.
		*
		* @param vector The vector to add.
		*/
		void add(const Vector2& vector);

		/**
		* Adds the given vectors and stores the result in the third parameter.
		*
		* @param v1 The first vector.
		* @param v2 The second vector.
		* @param dst The vector that stores the result.
		*/
		static void add(const Vector2& v1, const Vector2& v2, Vector2* dst);

		/**
		* Subtracts the given float values to this vector.
		*
		* @param x The value to be subtracted to the x coordinate.
		* @param y The value to be subtracted to the y coordinate.
		*/
		void subtract(const float x, const float y);

		/**
		* Subtracts the elements of the given vector to this one.
		*
		* @param vector The vector to subtract.
		*/
		void subtract(const Vector2& vector);

		/**
		* Subtracts the given vectors and stores the result in the third parameter.
		*
		* @param v1 The first vector.
		* @param v2 The second vector.
		* @param dst The vector that stores the result.
		*/
		static void subtract(const Vector2& v1, const Vector2& v2, Vector2* dst);

		/**
		* Scales the coordinates in this vector by the given float value.
		*
		* @param scalar The scalar value.
		*/
		void scale(const float scalar);

		/**
		* Scales the coordinates in this vector by the given float value and stores the result in dst (pointer to a Vector2 object).
		*
		* @param scalar The scalar value.
		* @param dst The vector that stores the result.
		*/
		void scale(const float scalar, Vector2* dst) const;

		/**
		* Divides the coordinates in this vector by the given float value.
		*
		* @param denominator The denominator value.
		*/
		void divide(const float denominator);

		/**
		* Divides the coordinates in this vector by the given float value and stores the result in dst (pointer to a Vector2 object).
		*
		* @param denominator The denominator value.
		* @param dst The vector that stores the result.
		*/
		void divide(const float denominator, Vector2* dst) const;

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
		float distance(const Vector2& vector) const;

		/**
		* Calculates the squared distance between this vector and the given vector.
		*
		* @param vector The other vector.
		* @return The squared distance between this vector and the given vector.
		*
		* @see distance
		*/
		float distanceSquared(const Vector2& vector) const;

		/**
		* Calculates the dot product between the given vectors.
		*
		* @param v1 The first vector.
		* @param v2 The second vector.
		* @return The dot product between the given vectors.
		*/
		static float dot(const Vector2& v1, const Vector2& v2);

		/**
		* Calculates the dot product between this vector and the given vector.
		*
		* @param vector The vector used in the calculation of the dot product.
		* @return The dot product.
		*/
		float dot(const Vector2& vector) const;

		/**
		* Normalizes the given vector and stores the result in dst (pointer to a Vector2 object).
		*
		* @param vector The vector with the values.
		* @param dst The vector that will store the result.
		*/
		static void normalize(const Vector2& vector, Vector2* dst);

		/**
		* Normalizes this vector and stores the result in this vector.
		*
		* @return This vector with the result of the normalization.
		*/
		Vector2& normalize();

		/**
		* Normalizes this vector and stores the result in the dst (pointer to a Vector2 object).
		*
		* @return The result of the normalization in dst.
		*/
		void normalize(Vector2* dst) const;

		/**
		* Calculates the linear interpolation between 2 given vectors and stores in dst (pointer to a Vector2 object).
		*
		* @param start Start vector.
		* @param end End vector.
		* @param value Value to interpolate by.
		* @param dst The vector to store the result.
		*/
		static void lerp(const Vector2& start, const Vector2& end, float value, Vector2* dst);

		/**
		* Calculates the linear interpolation between this vector and the given vector and stores the result in this vector, the start vector is this.
		*
		* @param end End vector.
		* @param value Value to interpolate by.
		*/
		void lerp(const Vector2& end, float value);

		/**
		* Clamps the given vector within the given minX, minY, maxX and maxY values and stores the result in dst (pointer to a Vector2 object).
		*
		* @param vector The vector to clamp.
		* @param minX The minimum x value.
		* @param minY The minimum y value.
		* @param maxX The maximum x value.
		* @param maxY The maximum y value.
		* @param dst A pointer to a Vector2 object to store the result in.
		*/
		static void clamp(const Vector2& vector, const float minX, const float minY, const float maxX, const float maxY, Vector2* dst);

		/**
		* Clamps the given vector within the given min and max values and stores the result in dst (pointer to a Vector2 object).
		*
		* @param vector The vector to clamp.
		* @param min The minimum value.
		* @param max The maximum value.
		* @param dst A pointer to a Vector2 object to store the result in.
		*/
		static void clamp(const Vector2& vector, const Vector2& min, const Vector2& max, Vector2* dst);

		/**
		* Clamps this vector within the given minX, minY, maxX and maxY values and stores the result in this vector.
		*
		* @param minX The minimum x value.
		* @param minY The minimum y value.
		* @param maxX The maximum x value.
		* @param maxY The maximum y value.
		*/
		void clamp(const float minX, const float minY, const float maxX, const float maxY);

		/**
		* Clamps this vector within the given min and max values and stores the result in this vector.
		*
		* @param min The minimum value.
		* @param max The maximum value.
		*/
		void clamp(const Vector2& min, const Vector2& max);

		/**
		* Rotate this vector by the given angle (radians) around the given coordinates, it's basically a pivot.
		*
		* @param pointX The x coordinate of the point.
		* @param pointY The y coordinate of the point.
		* @param angle The angle (radians).
		*/
		void rotate(const float pointX, const float pointY, float angle);

		/**
		* Rotate this vector by the given angle (radians) around the given point (Vector2), it's basically a pivot.
		*
		* @param point The point (Vector2).
		* @param angle The angle (radians).
		*/
		void rotate(const Vector2& point, float angle);

		/**
		* Sets the elements of this vector to the given int values. It never initializes them, only assigns.
		*
		* @param x The new x coordinate.
		* @param y The new y coordinate.
		*/
		void set(const int x, const int y);

		/**
		* Sets the elements of this vector to the given float values. It never initializes them, only assigns.
		*
		* @param x The new x coordinate.
		* @param y The new y coordinate.
		*/
		void set(const float x, const float y);

		/**
		* Sets the elements of this vector to the given double values. It never initializes them, only assigns.
		*
		* @param x The new x coordinate.
		* @param y The new y coordinate.
		*/
		void set(const double x, const double y);

		/**
		* Sets this vector to the directional vector between the given points. It never initializes them, only assigns.
		*
		* @param p1 The first point.
		* @param p2 The second point.
		*/
		void set(const Vector2& p1, const Vector2& p2);

		/**
		* Copies the elements of the given vector to this vector. It never initializes them, only assigns.
		*
		* @param vector The vector to copy.
		*/
		void set(const Vector2& vector);

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
		inline const Vector2 operator=(const Vector2& vector);

		/**
		* Determines if this vector is equal to the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is equal to the given vector, false if not.
		*/
		inline bool operator==(const Vector2& vector) const;

		/**
		* Determines if this vector is not equal to the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is not equal to the given vector, false if not.
		*/
		inline bool operator!=(const Vector2& vector) const;

		/**
		* Determines if this vector is below the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is below the given vector, false if not.
		*/
		inline bool operator<(const Vector2& vector) const;

		/**
		* Determines if this vector is below or equal to the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is below or equal to the given vector, false if not.
		*/
		inline bool operator<=(const Vector2& vector) const;

		/**
		* Determines if this vector is above the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is above the given vector, false if not.
		*/
		inline bool operator>(const Vector2& vector) const;

		/**
		* Determines if this vector is above or equal to the given vector.
		*
		* @param vector The vector to compare against.
		* @return True if this vector is above or equal to the given vector, false if not.
		*/
		inline bool operator>=(const Vector2& vector) const;

		/**
		* Calculates the sum of this vector with the given vector. This vector and the given one remain unchanged.
		*
		* @param vector The vector to add.
		* @return The vector with the result of the addition.
		*/
		inline const Vector2 operator+(const Vector2& vector) const;

		/**
		* Adds the given vector to this vector.
		*
		* @param vector The vector to add.
		* @return This vector with the result of the addition.
		*/
		inline Vector2& operator+=(const Vector2& vector);

		/**
		* Calculates the subtraction of this vector with the given vector. This vector and the given one remain unchanged.
		*
		* @param vector The vector to subtract.
		* @return The vector with the result of the subtraction.
		*/
		inline const Vector2 operator-(const Vector2& vector) const;

		/**
		* Subtracts the given vector to this vector.
		*
		* @param vector The vector to add.
		* @return This vector with the result of the subtraction.
		*/
		inline Vector2& operator-=(const Vector2& vector);

		/**
		* Calculates the negation of this vector. This vector remains unchanged.
		*
		* @return This vector negated.
		*/
		inline const Vector2 operator-() const;

		/**
		* Calculates the scalar product of this vector with the given value. This vector remains unchanged.
		*
		* @param x The value used to scale.
		* @return The scaled vector.
		*/
		inline const Vector2 operator*(const float x) const;

		/**
		* Calculates the scalar product of this vector with the given value.
		*
		* @param x The value used to scale.
		* @return This vector with the result of the scaling.
		*/
		inline Vector2& operator*=(const float x);

		/**
		* Calculates the division between this vector values and the given value. This vector remains unchanged.
		*
		* @param x the value used to divide.
		* @return The divided vector.
		*/
		inline const Vector2 operator/(const float x) const;

		/**
		* Calculates the division between this vector with the given value.
		*
		* @param x The value used to divide.
		* @return This vector with the result of the division.
		*/
		inline Vector2& operator/=(const float x);
	};
}

#include "Vector2.inl"

#endif
