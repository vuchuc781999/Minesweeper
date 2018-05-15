#include "Map.h"

#include <vector>
#include <cstdlib>
#include <ctime>

#include "Game.h"

Map::Map()
{
	
}

Map::Map(const int& defaultValue)
{
	this->map = new int*[Game::height];

	for (int i = 0; i < Game::height; i++)
	{
		this->map[i] = new int[Game::width];

		for (int j = 0; j < Game::width; j++)
		{
			this->map[i][j] = defaultValue;
		}
	}
}


Map::~Map()
{
	for (int i = 0; i < Game::height; i++)
	{
		delete this->map[i];
	}

	delete this->map;
}


void Map::random()
{
	srand(time(NULL));

	std::vector<int> notSelected;

	int temp = Game::width * Game::height;
	int pos;
	int _x, _y;

	for (int i = 0; i < temp; i++)
	{
		notSelected.push_back(i);
	}

	for (int i = 0; i < Game::numMines; i++)
	{
		pos = rand() % notSelected.size();
		_x = notSelected[pos] % Game::width;
		_y = notSelected[pos] / Game::width;

		this->map[_y][_x] = mine;

		this->increaseAround(_x, _y);

		notSelected.erase(notSelected.begin() + pos);
	}
}

int Map::getValue(const int& x, const int& y) const
{
	return this->map[y][x];
}

void Map::change(const int& x, const int& y, const int& value)
{
	this->map[y][x] = value;
}

void Map::increaseAround(const int& _x, const int& _y)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0)
			{
				if (_x + j >= 0 && _x + j < Game::width && _y + i >= 0 && _y + i < Game::height)
				{
					if (this->map[_y + i][_x + j] != mine)
					{
						this->map[_y + i][_x + j]++;
					}
				}
			}
		}
	}
}