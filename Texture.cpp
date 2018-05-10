#include "Texture.h"

#include "Game.h"

Texture::Texture()
{
	unopenedBox = loadTexture("image/unopened_box.png");
	emptyBox = loadTexture("image/empty_box.png");
	flag = loadTexture("image/flag.png");
	mine = loadTexture("image/mine.png");
	num1 = loadTexture("image/number_1.png");
	num2 = loadTexture("image/number_2.png");
	num3 = loadTexture("image/number_3.png");
	num4 = loadTexture("image/number_4.png");
	num5 = loadTexture("image/number_5.png");
	num6 = loadTexture("image/number_6.png");
	num7 = loadTexture("image/number_7.png");
	num8 = loadTexture("image/number_8.png");
}

Texture::~Texture()
{
	SDL_DestroyTexture(unopenedBox);
	SDL_DestroyTexture(emptyBox);
	SDL_DestroyTexture(flag);
	SDL_DestroyTexture(mine);
	SDL_DestroyTexture(num1);
	SDL_DestroyTexture(num2);
	SDL_DestroyTexture(num3);
	SDL_DestroyTexture(num4);
	SDL_DestroyTexture(num5);
	SDL_DestroyTexture(num6);
	SDL_DestroyTexture(num7);
	SDL_DestroyTexture(num8);
}

SDL_Texture* Texture::loadTexture(const char* imageTitle)
{
	SDL_Surface* surface = IMG_Load(imageTitle);
	SDL_Texture* texture;

	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

	SDL_FreeSurface(surface);

	return texture;
}

void Texture::drawTexture(const char* imageTitle)
{
	SDL_Texture* texture = loadTexture(imageTitle);

	SDL_RenderCopy(Game::renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(Game::renderer);
}

void Texture::drawTexture(SDL_Texture* texture, const int& x, const int& y)
{
	SDL_Rect desRect;

	desRect.x = x;
	desRect.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &desRect.w, &desRect.h);
	SDL_RenderCopy(Game::renderer, texture, NULL, &desRect);
	SDL_RenderPresent(Game::renderer);
}

void Texture::drawText(const std::string text, SDL_Rect desRect)
{
	SDL_Color textColor = { 0,0,0,0 };
	std::string _text = "_";
	_text += text;

	while (_text.length() < MAX_TEXT_LENGTH)
	{
		_text += "_";
	}

	_text += "_";
	SDL_Surface* text_surf = TTF_RenderText_Solid(Game::font, _text.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, text_surf);

	SDL_RenderCopy(Game::renderer, texture, NULL, &desRect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(text_surf);
	SDL_RenderPresent(Game::renderer);
}

SDL_Texture* Texture::getTexture(const int& i)
{
	SDL_Texture* texture = NULL;

	switch (i)
	{
	case -2:
		texture = flag;
		break;
	case -1:
		texture = unopenedBox;
		break;
	case 0:
		texture = emptyBox;
		break;
	case 1:
		texture = num1;
		break;
	case 2:
		texture = num2;
		break;
	case 3:
		texture = num3;
		break;
	case 4:
		texture = num4;
		break;
	case 5:
		texture = num5;
		break;
	case 6:
		texture = num6;
		break;
	case 7:
		texture = num7;
		break;
	case 8:
		texture = num8;
		break;
	case 9:
		texture = mine;
		break;
	default:
		break;
	}

	return texture;
}