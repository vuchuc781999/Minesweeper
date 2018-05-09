#pragma once

#include "Game.h"

#include <string>

#include "SDL_image.h"

const int MAX_INPUT_LENGTH = 6;
//const int MAX_NUM_BOX = 1000000;
const int MAX_WIDTH = 76;
const int MAX_HEIGHT = 40;

struct box
{
	int x;
	int y;
	int w;
	int h;

	box(int _x, int _y, int _w, int _h);
	bool inBox(int x, int y) const;
	SDL_Rect createDesRect() const;
};

const box startButton(159, 470, 280, 61);
const box widthBox(300, 560, 100, 30);
const box heightBox(300, 600, 100, 30);
const box mineBox(300, 640, 100, 30);
const box playButton(255, 730, 150, 60);
const box notifyBox(130, 690, 300, 15);

class StartScreen
{

public:
	StartScreen();
	~StartScreen();

	void pressStart();
	bool inputSize();
	void handleInput();
	void renderInput();

private:
	SDL_Event event;
	bool wait;
	std::string width, height, mine;
	bool wBox, hBox, mBox;
	SDL_Texture* choosedLine;
	SDL_Texture* unchoosedLine;
	SDL_Texture* emptyLine;
	SDL_Color background;
	char inputChar;

	void updateInput();
};