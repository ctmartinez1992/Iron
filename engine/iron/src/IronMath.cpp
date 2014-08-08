#include "Base.h"
#include "Vector2.h"
#include "IronMath.h"

namespace iron {

	const float IronMath::MATH_FLOAT_MIN =		1.0e-37f;
	const float IronMath::MATH_LOG2E =			1.4426950408889633f;
	const float IronMath::MATH_LOG10E =			0.4342944819032518f;
	const float IronMath::MATH_PI =				3.1415926535897932f;
	const float IronMath::MATH_PIOVER2 =		1.5707963267948966f;
	const float IronMath::MATH_PIOVER4 =		0.7853981633974483f;
	const float IronMath::MATH_PIX2 =			6.2831853071795864f;

	float IronMath::deg_to_rad(const float deg) {
		return (deg * (MATH_PI / 180));
	}

	float IronMath::rad_to_deg(const float rad) {
		return (rad * (180 / MATH_PI));
	}
}