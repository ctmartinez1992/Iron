#ifndef IRON_MATH_IRONMATH_H_
#define IRON_MATH_IRONMATH_H_

namespace iron {

	/*! \brief Simple utility class that provides some useful function that involve math.
	*
	*  Simple utility class that provides some useful function that involve math.
	*/
	class IronMath {
		/****************************** Variables ******************************/
	private:

	protected:

	public:
		static const float	MATH_FLOAT_MIN;		/*!< Value close to zero. */
		static const float	MATH_LOG2E;			/*!< Base 2 logarithm of e. */
		static const float	MATH_LOG10E;		/*!< Base 10 logarithm of e. */
		static const float	MATH_PI;			/*!< Pi value. */
		static const float	MATH_PIOVER2;		/*!< Half Pi value. */
		static const float	MATH_PIOVER4;		/*!< Quarter Pi value. */
		static const float	MATH_PIX2;			/*!< Double Pi value. */

		/****************************** Contructors & Destructors ******************************/
	public:

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Returns the given degree value to radians
		*
		* @param deg The value in degrees.
		* @return The value in radians
		*/
		static float deg_to_rad(const float deg);

		/**
		* Returns the given radian value to degrees
		*
		* @param rad The value in radians.
		* @return The value in degrees
		*/
		static float rad_to_deg(const float rad);

		/****************************** Operators Overloading ******************************/
	private:

	protected:

	public:

	};
}

#endif
