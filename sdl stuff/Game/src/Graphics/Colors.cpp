#include "Colors.h"

const Colors Colors::White = Colors(255, 255, 255, 255);
const Colors Colors::Black = Colors(0, 0, 0, 255);
const Colors Colors::Red = Colors(255, 0, 0, 255);
const Colors Colors::Green = Colors(0, 255, 0, 255);
const Colors Colors::Blue = Colors(0, 0, 255, 255);

Colors::Colors() : r(0), g(0), b(0), a(0)
{
}

Colors::Colors(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a)
{
}

Colors::~Colors() {
}