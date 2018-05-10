#pragma once

#include "SDL.h"

struct box
{
	int x;
	int y;
	int w;
	int h;

	box(int _x, int _y, int _w, int _h);
	~box();

	bool inBox(int x, int y) const;
	SDL_Rect createDesRect() const;
};