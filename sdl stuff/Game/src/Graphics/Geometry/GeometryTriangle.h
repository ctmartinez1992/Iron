#ifndef GEOMETRYLINE_H
#define GEOMETRYLINE_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>

//C++
#include <stdio.h>
#include <string>

//OWN
#include "GeometryObject.h"

class Screen;

class GeometryTriangle : public GeometryObject {
	/*************** Variables ***************/
private:
	//The second point of the triangle
	Vector2*				position2;

	//The thrid point of the triangle
	Vector2*				position3;

protected:

public:

	/*************** Contructors & Destructors ***************/
public:
	GeometryTriangle();
	GeometryTriangle(const std::string name);
	virtual ~GeometryTriangle();

	/*************** Methods ***************/
private:

protected:
	//Resets all variables to default values
	virtual void			resetToDefaultValues();

public:
	//Update the line
	virtual void			update();

	//Render the line
	virtual void			render(Screen* screen);

	//Loads the line, x, y are the origin coordinate and x2, y2 are the destination coordinates
	virtual bool			load(float x, float y, float x2, float y2, float x3, float y3, Uint8 rMod = 255, Uint8 gMod = 255, Uint8 bMod = 255, Uint8 alpha = 255);

	//Loads the line
	virtual bool			load(float x, float y, float x2, float y2, float x3, float y3, Colors color = Colors::White);

	//Sets the position with the given values
	virtual void			setAnchor(const float x, const float y);

	//Sets the first, second and third point of the triangle
	void					setPositionAll(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3);

	//Sets the first point of the triangle
	void					setPosition1(const float x, const float y);

	//Gets the first point of the triangle
	Vector2*				getPosition1() const;

	//Sets the second point of the triangle
	void					setPosition2(const float x, const float y);

	//Gets the second point of the triangle
	Vector2*				getPosition2() const;

	//Sets the third point of the triangle
	void					setPosition3(const float x, const float y);

	//Gets the third point of the triangle
	Vector2*				getPosition3() const;
};

#endif
