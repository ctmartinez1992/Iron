#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>

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
    Vertex vertexData[6];

    //First Triangle
    vertexData[0].position.x = x + w;
    vertexData[0].position.y = y + h;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + h;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

    //Second Triangle
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + w;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + w;
	vertexData[5].position.y = y + h;

	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 25;
		vertexData[i].color.b = 55;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 0;
	vertexData[1].color.g = 255;
	vertexData[1].color.b = 55;
	vertexData[1].color.a = 255;

	vertexData[4].color.r = 255;
	vertexData[4].color.g = 200;
	vertexData[4].color.b = 0;
	vertexData[4].color.a = 255;

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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//Color attrib pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    //Draw the 6 vertices to the screen
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Disable the vertex attrib array. This is not optional.
    glDisableVertexAttribArray(0);

    //Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}