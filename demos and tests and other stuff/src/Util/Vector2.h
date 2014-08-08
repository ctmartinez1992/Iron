#ifndef VECTOR2_H
#define VECTOR2_H

//SDL

//C++

//OWN
#include "Math.h"

class Vector2 {
	/*************** Variables ***************/
private:

protected:

public:
	//The values that constitute the vector
	float					x;
	float					y;

	/*************** Contructors & Destructors ***************/
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	/*************** Methods ***************/
private:

protected:

public:
	//Statically, creates a vector and returns it, simplicity sometimes helps
	static Vector2			createVector(const float x, const float y);

	//Addition, subtraction, multiplication and division between this and the passed Vector2 value. The result is returned in a new Vector2
	Vector2					add(const Vector2 vector) const;
	Vector2					sub(const Vector2 vector) const;
	Vector2					mul(const Vector2 vector) const;
	Vector2					div(const Vector2 vector) const;

	//Addition, subtraction, multiplication and division between this and the passed float. The result is returned in a new Vector2
	Vector2					add(const float value) const;
	Vector2					sub(const float value) const;
	Vector2					mul(const float value) const;
	Vector2					div(const float value) const;

	//Calculates and returns the length of the vector
	float					length() const;

	//Calculates the dot product between this vector and the passed vector
	float					dot(Vector2 vector) const;

	//Normalizes this vector and returns a pointer to this
	Vector2					normalize();

	//Resets the x and y to 0
	void					clear();

	//sets both values to the given values
	inline void				setPosition(const float x, const float y);

	//Operators (+, -, *, /) overload, the passed argument is a Vector2 reference
	Vector2					operator+(const Vector2 vector);
	Vector2					operator-(const Vector2 vector);
	Vector2					operator*(const Vector2 vector);
	Vector2					operator/(const Vector2 vector);

	//Operators (+, -, *, /) overload, the passed argument is a float
	Vector2					operator+(const float value);
	Vector2					operator-(const float value);
	Vector2					operator*(const float value);
	Vector2					operator/(const float value);

	//Operator overload for equals and !equals, the passed argument is a Vector2 reference
	inline bool				operator==(const Vector2& r) const;
	inline bool				operator!=(const Vector2& r) const;
};

#endif