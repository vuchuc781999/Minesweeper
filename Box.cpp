#include "Box.h"

box::box(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h)
{

}

box::~box()
{

}

bool box::inbox(int _x, int _y) const
{
	return (_x > x && _y > y && _x < x + w && _y < y + h);
}

SDL_Rect box::createDesRect() const
{
	return { x, y, w, h };
}