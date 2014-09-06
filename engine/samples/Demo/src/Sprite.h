#pragma once
#include <glew.h>

//A 2D quad that can be rendered to the screen
class Sprite
{
public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float width, float height);

    void draw();
    
private:
    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboID;

};

