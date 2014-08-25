#include "Sprite.h"

Sprite::Sprite() : vboID(0), x(0), y(0), w(0), h(0)
{
}

Sprite::~Sprite() {
    if (vboID != 0) {
        glDeleteBuffers(1, &vboID);
    }
}

void Sprite::init(float x, float y, float w, float h) {
    this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

    if (vboID == 0) {
        glGenBuffers(1, &vboID);
    }

    //6 vertices, each vertex has 2 floats (X,Y).
    float vertexData[12];

    //First Triangle
    vertexData[0] = x + w;
    vertexData[1] = y + h;

    vertexData[2] = x;
    vertexData[3] = y + h;

    vertexData[4] = x;
    vertexData[5] = y;

    //Second Triangle
    vertexData[6] = x;
    vertexData[7] = y;

    vertexData[8] = x + w;
    vertexData[9] = y;

    vertexData[10] = x + w;
    vertexData[11] = y + h;

    //Tell opengl to bind our vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    //Upload the data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    //Unbind the buffer (optional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Draws the sprite to the screen
void Sprite::render() {
    //bind the buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    //Tell opengl that we want to use the first
    //attribute array. We only need one array right
    //now since we are only using position.
    glEnableVertexAttribArray(0);

    //Point opengl to the data in our VBO. We will learn
    //more on this later
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the 6 vertices to the screen
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Disable the vertex attrib array. This is not optional.
    glDisableVertexAttribArray(0);

    //Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}