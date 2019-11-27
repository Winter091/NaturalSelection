#pragma once

#include <string>

enum class Objects
{
	NONE,
	WALL,
	FOOD,
	ROBOT
};

class Cell
{
private:
	Objects object;

public:
	Cell();

	void SetObject(Objects object);
	void RemoveObject();
	Objects GetObject();
};