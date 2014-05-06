#ifndef MATH_H
#define MATH_H

//SDL

//C++
#include <cmath>

//OWN

#define PI			3.141592653589793238462f
#define DEG2RAD		0.01745329251994329576923690768f
#define RAD2DEG		57.2957795130823208767981548141f

class Math {
	/*************** Variables ***************/
private:

protected:

public:

	/*************** Contructors & Destructors ***************/
public:

	/*************** Methods ***************/
private:

protected:

public:
	//Converts and returns degrees to radians
	inline static float toRadian(const float degree);

	//Converts and returns radians to degrees
	inline static float toDegree(const float radian);
};

#endif