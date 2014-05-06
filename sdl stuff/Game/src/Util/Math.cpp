#include "Math.h"

inline float Math::toRadian(const float degree) {
	return (degree * DEG2RAD);
}

inline float Math::toDegree(const float radian) {
	return (radian * RAD2DEG);
}