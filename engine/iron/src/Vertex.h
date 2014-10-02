#ifndef IRON_GRAPHICS_VERTEX_H_
#define IRON_GRAPHICS_VERTEX_H_

#include <sdl/glew.h>

namespace iron {

	namespace graphics {

		struct Position {
			float x;
			float y;
		};

		struct Color {
			GLubyte r;
			GLubyte g;
			GLubyte b;
			GLubyte a;
		};

		struct UV {
			float u;
			float v;
		};

		//The vertex definition
		struct Vertex {
			//This is the position struct. When you store a struct or class
			//inside of another struct or class, it is called composition. This is
			//layed out exactly the same in memory as if we had a float position[2],
			//but doing it this way makes more sense.
			Position position;

			//4 bytes for r g b a color.
			Color color;

			//UV texture coordinates.
			UV uv;

			void setPosition(float x, float y) {
				position.x = x;
				position.y = y;
			}

			void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
				color.r = r;
				color.g = g;
				color.b = b;
				color.a = a;
			}

			void setUV(float u, float v) {
				uv.u = u;
				uv.v = v;
			}
		};
	}
}

#endif