#include "Game.h"

#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Map.h"
#include "Texture.h"
#include "PlayAgain.h"

SDL_Window* Game::window = nullptr;
int Game::width = 0;
int Game::height = 0;
int Game::numMines = 0;
SDL_Renderer* Game::renderer = nullptr;
bool Game::isRunning = false;
TTF_Font* Game::font = nullptr;
bool Game::win = false;
bool Game::quit = false;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char* windowTitle, const int& windowPosX, const int& windowPosY, const int& windowWidth, const int& windowHeight, bool fullScreen)
{
	if (!PlayAgain::playAgain)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			notifyError();
		}
		else
		{
			std::cout << "Subsystem is initialized !!!..." << std::endl;

			window = SDL_CreateWindow(windowTitle, windowPosX, windowPosY, windowWidth, windowHeight, (fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN));

			if (window == nullptr)
			{
				notifyError();
			}
			else
			{
				std::cout << "Window is created !!!..." << std::endl;
			}

			SDL_Surface* icon = IMG_Load("image/icon.png");
			SDL_SetWindowIcon(window, icon);
			SDL_FreeSurface(icon);

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == nullptr)
			{
				notifyError();
			}
			else
			{
				std::cout << "Renderer is created !!!..." << std::endl;
			}

			isRunning = true;
		}
		if (TTF_Init() != 0)
		{
			notifyError();
		}
		else
		{
			font = TTF_OpenFont("arial.ttf", 100);
			if (font == NULL)
			{
				notifyError();
			}
		}
	}
}

void Game::createMap()
{
	mineMap = new Map(emptyBox);
	hiddenMap = new Map(unopenedBox);
	texture = new Texture;

	mineMap->random();

	desRect.w = edgeBox;
	desRect.h = edgeBox;

	opendBoxs = 0;
	flags = 0;
	noMineBoxs = width * height - numMines;
}

void Game::printMap()
{
	SDL_SetWindowSize(window, width*edgeBox, height*edgeBox);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	for (int i = 0; i < Game::width; i++)
	{
		for (int j = 0; j < Game::height; j++)
		{
			desRect.x = i * edgeBox;
			desRect.y = j * edgeBox;

			SDL_RenderCopy(renderer, texture->getTexture(unopenedBox), NULL, &desRect);
		}
	}

	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&event))
	{
		update();
	}
}


void Game::update()
{
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		quit = true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		openPosX = event.button.x / edgeBox;
		openPosY = event.button.y / edgeBox;
		value = mineMap->getValue(openPosX, openPosY);

		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (hiddenMap->getValue(openPosX, openPosY) == unopenedBox)
			{
				if (value == mine)
				{
					for (int i = 0; i < Game::width; i++)
					{
						for (int j = 0; j < Game::height; j++)
						{
							if (mineMap->getValue(i, j) == mine)
							{
								desRect.x = i * edgeBox;
								desRect.y = j * edgeBox;

								SDL_RenderCopy(renderer, texture->getTexture(mine), NULL, &desRect);
							}
						}
					}
					isRunning = false;
				}
				else if (value != emptyBox)
				{
					hiddenMap->change(openPosX, openPosY, value);

					opendBoxs++;
					desRect.x = openPosX * edgeBox;
					desRect.y = openPosY * edgeBox;

					SDL_RenderCopy(renderer, texture->getTexture(value), NULL, &desRect);
				}
				else if (value == emptyBox)
				{
					hiddenMap->change(openPosX, openPosY, mine);

					opendBoxs++;
					desRect.x = openPosX * edgeBox;
					desRect.y = openPosY * edgeBox;

					SDL_RenderCopy(renderer, texture->getTexture(emptyBox), NULL, &desRect);
					open(openPosX, openPosY);
				}
			}
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			if (hiddenMap->getValue(openPosX, openPosY) == unopenedBox)
			{
				hiddenMap->change(openPosX, openPosY, flag);

				flags++;
				desRect.x = openPosX * edgeBox;
				desRect.y = openPosY * edgeBox;

				SDL_RenderCopy(renderer, texture->getTexture(flag), NULL, &desRect);
			}
			else if (hiddenMap->getValue(openPosX, openPosY) == flag)
			{
				hiddenMap->change(openPosX, openPosY, unopenedBox);

				flags--;
				desRect.x = openPosX * edgeBox;
				desRect.y = openPosY * edgeBox;

				SDL_RenderCopy(renderer, texture->getTexture(unopenedBox), NULL, &desRect);
			}
		}
		break;
	default:
		break;
	}
	if (opendBoxs == noMineBoxs && flags == numMines)
	{
		win = true;
		isRunning = false;
	}
}

void Game::render()
{
	SDL_RenderPresent(renderer);
	if (!isRunning)
	{
		SDL_Delay(DELAY_TIME);
	}
}

void Game::cleanGame()
{
	if (!PlayAgain::playAgain)
	{
		delete mineMap;
		delete hiddenMap;
		delete texture;

		TTF_CloseFont(font);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		std::cout << "Game is cleaned !!!..." << std::endl;
	}
	else
	{
		width = 0;
		height = 0;
		numMines = 0;
		isRunning = true;

		delete mineMap;
		delete hiddenMap;
		delete texture;
	}
}

void Game::notifyError()
{
	std::cout << "Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	system("pause");
	exit(1);
}

void Game::open(const int& x, const int& y)
{
	int _x, _y;
	int _value;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0)
			{
				_x = x + i;
				_y = y + j;

				if (_x >= 0 && _x < width && _y >= 0 && _y < height)
				{
					_value = mineMap->getValue(_x, _y);

					if (hiddenMap->getValue(_x, _y) == unopenedBox)
					{
						hiddenMap->change(_x, _y, _value);

						opendBoxs++;
						desRect.x = _x * edgeBox;
						desRect.y = _y * edgeBox;

						SDL_RenderCopy(renderer, texture->getTexture(_value), NULL, &desRect);

						if (mineMap->getValue(_x, _y) == emptyBox)
						{
							open(_x, _y);
						}
					}
				}
			}
		}
	}
}