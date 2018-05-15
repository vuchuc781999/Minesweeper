/*********************************
 **	MINESWEEPER		**
 **				**
 **	Author: Vũ Văn Chức	**
 *********************************/

#define _WIN32_WINNT 0x0500

#include <iostream>
#include <Windows.h>

#include "Game.h"
#include "StartScreen.h"
#include "Map.h"
#include "PlayAgain.h"

const char* WINDOW_TITLE = "Minesweeper";
const int WINDOW_WTDTH = 600;
const int WINDOW_HEIGHT = 900;
const bool FULL_SCREEN = false;

int main(int argc, char* argv[])
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	Game* game = new Game();
	PlayAgain playagain;

	game->Init(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WTDTH, WINDOW_HEIGHT, FULL_SCREEN);

	StartScreen* startScreen = new StartScreen();

	startScreen->pressStart();

	do
	{
		startScreen->loadInputScreen();

		while (startScreen->inputingSize())
		{
			SDL_StartTextInput();

			startScreen->handleInput();
			startScreen->renderInput();

			SDL_StopTextInput();
		}

		startScreen->cleanInput();

		if (Game::isRunning)
		{
			game->createMap();
			game->printMap();
		}
		while (Game::isRunning)
		{
			game->handleEvents();
			game->render();
		}

		playagain.endScreen(WINDOW_WTDTH, WINDOW_HEIGHT);

		game->cleanGame();
	} while (PlayAgain::playAgain);

	delete startScreen;
	delete game;

	//ShowWindow(hWnd, SW_SHOW);
	//system("pause");
	return 0;
}
