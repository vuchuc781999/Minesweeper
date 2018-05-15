#pragma once

class Map
{
public:
	Map();
	Map(const int& defaultValue = 0);
	~Map();

	void random();
	int getValue(const int& x, const int& y) const;
	void change(const int& x, const int& y, const int& value);

private:
	int** map;

	void increaseAround(const int& _x, const int& _y);
};

