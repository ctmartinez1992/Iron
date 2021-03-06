#ifndef GEOMETRYOBJECT_H
#define GEOMETRYOBJECT_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>

//C++
#include <stdio.h>
#include <string>

//OWN
#include "../../General/GameObject.h"
#include "../../Graphics/Colors.h"

class Screen;

class GeometryObject : public GameObject {
	/*************** Variables ***************/
private:

protected:

public:
	//Type defines the type of geometry it is: [0:Nothing; 1:Dot; 2:Line; 3:Triangle; 4:Rectangle; 5:Circle]
	Uint8					type;

	//Is the geometry filled or not
	bool					filled;

	//Is the object loaded
	bool					loaded;

	/*************** Contructors & Destructors ***************/
public:
	GeometryObject();
	GeometryObject(const std::string name, const Uint8 type);
	virtual ~GeometryObject();

	/*************** Methods ***************/
private:

protected:
	//Resets all variables to default values
	virtual void			resetToDefaultValues();

public:
	//Update the geometry object
	virtual void			update() = 0;

	//Render the geometry object
	virtual void			render(Screen* screen) = 0;

	//Loads the geometry object
	virtual bool			load(float x, float y, float angle = 0, bool filled = false, Uint8 rMod = 255, Uint8 gMod = 255, Uint8 bMod = 255, Uint8 alpha = 255);

	//Loads the geometry object
	virtual bool			load(float x, float y, float angle = 0, bool filled = false, Colors color = Colors::White);

	//Sets the position with the given values
	virtual void			setAnchor(const float x, const float y) = 0;
};

#endif
