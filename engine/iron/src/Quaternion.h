#ifndef IRON_MATH_QUATERNION_H_
#define IRON_MATH_QUATERNION_H_

#include "Vector3.h"
#include "Matrix.h"

class Matrix;

namespace iron {

	/*! \brief Quaternions are used to represent an object's orientation (rotation) in space.
	*
	*  They are not affected by gimbal lock and can be interpolated. Used as a replacement
	*  for rotation matrices and euler angles.
	*
	*  The class does not handle automatic normalization, the normalize method should be
	*  called when necessary.
	*/
	class Quaternion {
		/****************************** Variables ******************************/
	private:

	protected:

	public:
		float					x;			/*!< The x component. */

		float					y;			/*!< The y component. */

		float					z;			/*!< The z component. */

		float					w;			/*!< The scalar component. */

		const static Quaternion	ZERO;		/*!< Zero Quaternion. */
		const static Quaternion	IDENTITY;	/*!< Identity Quaternion. */

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Constructs a new quaternion object initialized to 0, 0, 0, 1.
		*/
		Quaternion();

		/**
		* Constructs a new quaternion initialized to the given values.
		*
		* @param x The x component.
		* @param y The y component.
		* @param z The z component.
		* @param w The w component.
		*/
		Quaternion(const float x, const float y, const float z, const float w);

		/**
		* Constructs a new quaternion object with the result of the rotation between
		* the given axis and angle.
		*
		* @param axis The axis of the rotation.
		* @param angle The angle of the rotation (radians).
		*/
		Quaternion(const Vector3& axis, const float angle);

		/**
		* Constructs a new quaternion that is a copy of the given quaternion.
		*
		* @param q The quaternion to copy.
		*/
		Quaternion(const Quaternion& q);

		/**
		* Destructor.
		*/
		~Quaternion();

	private:

		/****************************** Methods ******************************/
	private:
		/**
		* Spherical linear interpolation between 2 quaternions. I am not the author of this algorithm,
		* i only remember getting it from somewhere a few years ago. Credit is to someone out there.
		* I have adapted it to the engine necessities.
		*
		* @warning The given quaternions must be of unit length.
		*
		* @param x1 The x component of the first quaternion.
		* @param y1 The y component of the first quaternion.
		* @param z1 The z component of the first quaternion.
		* @param w1 The w component of the first quaternion.
		* @param x2 The x component of the second quaternion.
		* @param y2 The y component of the second quaternion.
		* @param z2 The z component of the second quaternion.
		* @param w2 The w component of the second quaternion.
		* @param c The interpolation coefficient.
		* @param dstx The float that stores the x component result.
		* @param dsty The float that stores the y component result.
		* @param dstz The float that stores the z component result.
		* @param dstw The float that stores the w component result.
		*/
		static void slerp(float x1, float y1, float z1, float w1, float x2, float y2, float z2, 
			float w2, float c, float* dstx, float* dsty, float* dstz, float* dstw);

	protected:

	public:
		/**
		* Linear interpolation between 2 quaternions. Produces a straight line.
		*
		* @param q1 The first quaternion.
		* @param q2 The second quaternion.
		* @param c The interpolation coefficient.
		* @param dst The quaternion that stores the result.
		*/
		static void lerp(const Quaternion& q1, const Quaternion& q2, const float c, Quaternion* dst);

		/**
		* Linear interpolation between this quaternion and the given one. Produces a straight line.
		*
		* @param q The quaternion used in the interpolation.
		* @param c The interpolation coefficient.
		*/
		void lerp(const Quaternion& q, const float c);

		/**
		* Spherical linear interpolation between 2 quaternions.
		*
		* @warning The given quaternions must be normalized, if necessary.
		* @see normalize
		*
		* @param q1 The first quaternion.
		* @param q2 The second quaternion.
		* @param c The interpolation coefficient.
		* @param dst The quaternion that stores the result.
		*/
		static void slerp(const Quaternion& q1, const Quaternion& q2, const float c, Quaternion* dst);

		/**
		* Spherical linear interpolation between this quaternion and the given one.
		*
		* @warning This quaternion and the given must be normalized, if necessary.
		* @see normalize
		*
		* @param q The quaternion used in the interpolation.
		* @param c The interpolation coefficient.
		*/
		void slerp(const Quaternion& q, const float c);

		/**
		* Multiplies the given quaternions and stores the result in dst.
		*
		* @param q1 The first quaternion.
		* @param q2 The second quaternion.
		* @param dst The quaternion that stores the result.
		*/
		static void multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst);

		/**
		* Multiplies the given vector by this one.
		*
		* @param q The quaternion to multiply.
		*/
		void multiply(const Quaternion& q);

		/**
		* Returns true if the given quaternion was successfully inverted, false if not. The inverse
		* is stored in dst.
		*
		* @param q The quaternion.
		* @param dst The quaternion that stores the result.
		* @return True if the given quaternion was successfully inverted, false if not.
		*/
		static bool invert(const Quaternion& q, Quaternion* dst);

		/**
		* Returns true if successfully inverted, false if not. The inverse is stored in this quaternion.
		*
		* @return True if successfully inverted, false if not.
		*/
		bool invert();

		/**
		* Calculates the conjugate of the given quaternion and stores the result in dst.
		*
		* @param q The quaternion.
		* @param dst The quaternion that stores the result.
		*/
		static void conjugate(const Quaternion& q, Quaternion* dst);

		/**
		* Sets this quaternion to the conjugate of itself.
		*/
		void conjugate();

		/**
		* Normalizes the given quaternion and stores the result in dst.
		*
		* @param q The quaternion.
		* @param dst The quaternion that stores the result.
		*/
		static void normalize(const Quaternion& q, Quaternion* dst);
		
		/**
		* Normalizes this quaternion.
		*/
		void normalize();

		/**
		* Returns the identity quaternion.
		*
		* @return The identity quaternion.
		*/
		static const Quaternion& identity();

		/**
		* Sets this quaternion to be equal to an identity quaternion.
		*/
		void setIdentity();

		/**
		* Returns true if this quaternion is equal to an identity quaternion. Otherwise, false.
		*
		* @return true if this quaternion is equal to an identity quaternion. Otherwise, false.
		*/
		bool isIdentity() const;

		/**
		* Returns the quaternion with all components set to 0.
		*
		* @return The quaternion with all components set to 0.
		*/
		static const Quaternion& zero();

		/**
		* Sets this quaternion components to be equal to 0.
		*/
		void setZero();

		/**
		* Returns true if this quaternion is equal to a "zeroed" quaternion. Otherwise, false.
		*
		* @return true if this quaternion is equal to a "zeroed" quaternion. Otherwise, false.
		*/
		bool isZero() const;

		/**
		* Sets the elements of the quaternion to the specified values.
		*
		* @param x The new x-value.
		* @param y The new y-value.
		* @param z The new z-value.
		* @param w The new w-value.
		*/
		void set(const float x, const float y, const float z, const float w);

		/**
		* Sets this quaternion components with the result of the rotation between the given axis 
		* and angle.
		*
		* @param axis The axis of the rotation.
		* @param angle The angle of the rotation (radians).
		*/
		void set(const Vector3& axis, const float angle);

		/**
		* Sets this quaternion components with the components of the given quaternion.
		*
		* @param q The quaternion to copy.
		*/
		void set(const Quaternion& q);

		/****************************** Operators Overloading ******************************/
	private:

	protected:

	public:
		/**
		* Returns the quaternion product of this quaternion with the given quaternion. It does not
		* modify this quaternion.
		*
		* @param q The quaternion to multiply.
		* @return The quaternion product.
		*/
		inline const Quaternion operator*(const Quaternion& q) const;

		/**
		* Calculates the product between this quaternion with the given quaternion. It stores the
		* result in this quaternion
		*
		* @param q The quaternion to multiply.
		* @return This quaternion with the result.
		*/
		inline Quaternion& operator*=(const Quaternion& q);

	};
}

#include "Quaternion.inl"

#endif
