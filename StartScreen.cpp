#include "StartScreen.h"

#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Texture.h"

using std::string;

box::box(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h)
{

}

bool box::inBox(int _x, int _y) const
{
	return (_x > x && _y > y && _x < x + w && _y < y + h);
}

SDL_Rect box::createDesRect() const
{
	return { x, y, w, h };
}

StartScreen::StartScreen()
{
	wait = true;
	width = "";
	height = "";
	mine = "";
	wBox = false;
	hBox = false;
	mBox = false;
	choosedLine = Texture::loadTexture("image/choosed_line.png");
	unchoosedLine = Texture::loadTexture("image/unchoosed_line.png");
	emptyLine = Texture::loadTexture("image/empty_line.png");
}

StartScreen::~StartScreen()
{
	SDL_DestroyTexture(choosedLine);
	SDL_DestroyTexture(unchoosedLine);
	SDL_DestroyTexture(emptyLine);

	//std::cout << "Start screen is cleaned !!!..." << std::endl;
}

void StartScreen::pressStart()
{
	bool _wait = true;

	Texture::drawTexture("image/start_screen_1.png");
	while (_wait)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				Game::isRunning = false;
				Game::quit = true;
				wait = false;
				_wait = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button = SDL_BUTTON_LEFT && startButton.inBox(event.button.x, event.button.y))
				{
					_wait = false;
				}
			default:
				break;
			}
		}
	}
	Texture::drawTexture("image/start_screen_2.png");
}

bool StartScreen::inputSize()
{
	return wait;
}

void StartScreen::handleInput()
{
	while (SDL_PollEvent(&event))
	{
		updateInput();
	}
}

void StartScreen::updateInput()
{
	switch (event.type)
	{
	case SDL_QUIT:
		Game::isRunning = false;
		Game::quit = true;
		wait = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (widthBox.inBox(event.button.x, event.button.y))
			{
				wBox = true;
				hBox = false;
				mBox = false;
			}
			else if (heightBox.inBox(event.button.x, event.button.y))
			{
				wBox = false;
				hBox = true;
				mBox = false;
			}
			else if (mineBox.inBox(event.button.x, event.button.y))
			{
				wBox = false;
				hBox = false;
				mBox = true;
			}
			else if (playButton.inBox(event.button.x, event.button.y))
			{
				if (Game::width == 0 || Game::height == 0 || Game::numMines == 0)
				{
					//std::cout << "Input all and diverse 0.\n";
					SDL_RenderCopy(Game::renderer, emptyLine, NULL, &notifyBox.createDesRect());
					Texture::drawText("Input all and diverse 0.", notifyBox.createDesRect());
				}
				else if (/*Game::width * Game::height > MAX_NUM_BOX*/Game::width > MAX_WIDTH || Game::height > MAX_HEIGHT)
				{
					//std::cout << "The map is too large.___\n";
					SDL_RenderCopy(Game::renderer, emptyLine, NULL, &notifyBox.createDesRect());
					Texture::drawText("The map is too large.___", notifyBox.createDesRect());
				}
				else if (Game::width * Game::height < Game::numMines)
				{
					//std::cout << "Has too many mines.____ \n";
					SDL_RenderCopy(Game::renderer, emptyLine, NULL, &notifyBox.createDesRect());
					Texture::drawText("Has too many mines. ____", notifyBox.createDesRect());
				}
				else
				{
					wait = false;
				}
			}
			else
			{
				wBox = false;
				hBox = false;
				mBox = false;
			}
		}
		break;
	case SDL_TEXTINPUT:
		inputChar = event.text.text[0];
		if (inputChar >= '0' && inputChar <= '9')
		{
			if (wBox && width.length() < MAX_INPUT_LENGTH)
			{
				width += event.text.text;
				Game::width *= 10;
				Game::width += (int)(inputChar - 48);
				//std::cout << Game::width << std::endl;
			}
			else if (hBox && height.length() < MAX_INPUT_LENGTH)
			{
				height += event.text.text;
				Game::height *= 10;
				Game::height += (int)(inputChar - 48);
				//std::cout << Game::height << std::endl;
			}
			else if (mBox && mine.length() < MAX_INPUT_LENGTH)
			{
				mine += event.text.text;
				Game::numMines *= 10;
				Game::numMines += (int)(inputChar - 48);
				//std::cout << Game::numMines << std::endl;
			}
		}
		break;
	case SDL_KEYDOWN:
		if (wBox && event.key.keysym.sym == SDLK_BACKSPACE && width.length() > 0)
		{
			width.pop_back();
			Game::width /= 10;
			//std::cout << Game::width << std::endl;
		}
		else if (hBox && event.key.keysym.sym == SDLK_BACKSPACE && height.length() > 0)
		{
			height.pop_back();
			Game::height /= 10;
			//std::cout << Game::height << std::endl;
		}
		else if (mBox && event.key.keysym.sym == SDLK_BACKSPACE && mine.length() > 0)
		{
			mine.pop_back();
			Game::numMines /= 10;
			//std::cout << Game::numMines << std::endl;
		}
		else if (event.key.keysym.sym == SDLK_TAB || event.key.keysym.sym == SDLK_DOWN)
		{
			if (wBox)
			{
				wBox = false;
				hBox = true;
				mBox = false;
			}
			else if (hBox)
			{
				wBox = false;
				hBox = false;
				mBox = true;
			}
			else if (mBox)
			{
				wBox = true;
				hBox = false;
				mBox = false;
			}
		}
		else if (event.key.keysym.sym == SDLK_UP)
		{
			if (wBox)
			{
				wBox = false;
				hBox = false;
				mBox = true;
			}
			else if (hBox)
			{
				wBox = true;
				hBox = false;
				mBox = false;
			}
			else if (mBox)
			{
				wBox = false;
				hBox = true;
				mBox = false;
			}
		}
		break;
	default:
		break;
	}
}

void StartScreen::renderInput()
{
	if (wBox)
	{
		Texture::drawTexture(choosedLine, widthBox.x - 1, widthBox.y - 1);
		SDL_RenderCopy(Game::renderer, emptyLine, NULL, &widthBox.createDesRect());
		Texture::drawText(width, widthBox.createDesRect());
	}
	else
	{
		Texture::drawTexture(unchoosedLine, widthBox.x - 1, widthBox.y - 1);
	}
	if (hBox)
	{
		Texture::drawTexture(choosedLine, heightBox.x - 1, heightBox.y - 1);
		SDL_RenderCopy(Game::renderer, emptyLine, NULL, &heightBox.createDesRect());
		Texture::drawText(height, heightBox.createDesRect());
	}
	else
	{
		Texture::drawTexture(unchoosedLine, heightBox.x - 1, heightBox.y - 1);
	}
	if (mBox)
	{
		Texture::drawTexture(choosedLine, mineBox.x - 1, mineBox.y - 1);
		SDL_RenderCopy(Game::renderer, emptyLine, NULL, &mineBox.createDesRect());
		Texture::drawText(mine, mineBox.createDesRect());
	}
	else
	{
		Texture::drawTexture(unchoosedLine, mineBox.x - 1, mineBox.y - 1);
	}
}
