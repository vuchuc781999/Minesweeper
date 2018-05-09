#pragma once

#include <string>

#include "SDL.h"
#include "SDL_image.h"

const int MAX_TEXT_LENGTH = 7;

class Texture {

public:
	Texture();
	~Texture();

	static SDL_Texture* loadTexture(const char* imageTitle);
	static void drawTexture(const char* imageTitle);
	static void drawTexture(SDL_Texture* texture, const int& x, const int& y);
	static void drawText(const std::string text, SDL_Rect desRect);

	SDL_Texture* getTexture(const int& i);

private:
	SDL_Texture* unopenedBox;
	SDL_Texture* emptyBox;
	SDL_Texture* flag;
	SDL_Texture* mine;
	SDL_Texture* num1;
	SDL_Texture* num2;
	SDL_Texture* num3;
	SDL_Texture* num4;
	SDL_Texture* num5;
	SDL_Texture* num6;
	SDL_Texture* num7;
	SDL_Texture* num8;

};