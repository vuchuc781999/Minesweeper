#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

#include "Map.h"
#include "Texture.h"

const int edgeBox = 25;
const int unopenedBox = -1;
const int emptyBox = 0;
const int mine = 9;
const int flag = -2;
const int DELAY_TIME = 2000;

class Game {

public:
	static SDL_Window* window;
	static int width;
	static int height;
	static int numMines;
	static SDL_Renderer* renderer;
	static bool isRunning;
	static TTF_Font* font;
	static bool win;
	static bool quit;

	Game();
	~Game();

	void Init(const char* windowTitle, const int& windowPosX, const int& windowPosY, const int& windowWidth, const int& windowHeight, bool fullscreen);
	void createMap();
	void printMap();
	void handleEvents();
	void render();
	void cleanGame();
	static void notifyError();

private:
	SDL_Event event;
	SDL_Rect desRect;
	Texture* texture;

	Map *mineMap;
	Map	*hiddenMap;

	int openPosX;
	int openPosY;
	int value;
	int opendBoxs;
	int flags;
	int noMineBoxs;
	bool mapIsCreated;

	void update();
	void open(const int& x,const int& y);
};