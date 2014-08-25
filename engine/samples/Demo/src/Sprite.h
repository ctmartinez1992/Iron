#ifndef Demo_Sprite_H_
#define Demo_Sprite_H_

#include <glew.h>

//A 2D quad that can be rendered to the screen
class Sprite
{
public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float w, float h);
    void render();
    
private:
	GLuint vboID;
    float x;
    float y;
    float w;
    float h;

};

#endif

