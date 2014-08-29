#version 130
//The fragment shader operates on each pixel in a given polygon

in vec2 fragPosition;
in vec4 fragColor;

//This is the 4 component float vector that gets outputted to the screen for each pixel.
out vec4 color;

uniform float time;

void main() {
    color = vec4(fragColor.r * (sin(fragPosition.x * 10 + time) + 0.5) * 0.5,
				 fragColor.g * (cos(fragPosition.y * 7.5 + time) + 1.0) * 0.5,
				 sin(fragColor.b * (sin(fragPosition.x * 4 + time) + 1.0) * 0.5),
				 fragColor.a);
}