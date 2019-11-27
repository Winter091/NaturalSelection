#pragma once

#include <vector>

#include "Cell.h"

#include <SFML/Graphics.hpp>

enum class Actions
{
	NONE,
	EATING_FOOD,
	TURNING_WALL_TO_FOOD
};

class Robot
{
private:
	unsigned int x, y;
	unsigned int lifeTimer;

	int actionTimer;
	Actions currAction;

	std::vector<unsigned int> code;
	unsigned int codePtr;

	sf::RectangleShape drawRect;

	bool CheckBorders(unsigned int direction);

	void DoCurrentAction();
	void Move(unsigned int direction, const std::vector<std::vector<Cell*>>& cells);
	void EatFood(unsigned int direction, const std::vector<std::vector<Cell*>>& cells);
	void TurnWallIntoFood(unsigned int direction, const std::vector<std::vector<Cell*>>& cells);
	void AddLife(unsigned int amount);

public:
	Robot(unsigned int x, unsigned int y);
	Robot(unsigned int x, unsigned int y, std::vector<unsigned int> code);

	void ExecuteProgram(const std::vector<std::vector<Cell*>>& cells);
	void Draw(sf::RenderWindow& window);
};