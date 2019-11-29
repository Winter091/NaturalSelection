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
	int lifeTimer;

	int actionTimer;
	Actions currAction;
	int pendingMoveX, pendingMoveY;

	std::vector<unsigned int> code;
	unsigned int codePtr;

	sf::RectangleShape drawRect;
	sf::Font font;
	sf::Text text;

	bool CheckBorders(unsigned int direction);

	void DoCurrentAction(const std::vector<std::vector<Cell*>>& cells);
	void Move(unsigned int direction, const std::vector<std::vector<Cell*>>& cells);
	void EatFood(unsigned int direction, const std::vector<std::vector<Cell*>>& cells);
	void TurnWallIntoFood(unsigned int direction, const std::vector<std::vector<Cell*>>& cells);
	void AddLife(unsigned int amount);

public:
	Robot(unsigned int x, unsigned int y);
	Robot(unsigned int x, unsigned int y, std::vector<unsigned int> code);

	int GetHealth();
	void SetDefaults();
	int getX();
	int getY();
	void SetRandomPos(std::vector<std::vector<Cell*>>& cells);
	bool ExecuteProgram(std::vector<std::vector<Cell*>>& cells, std::vector<std::unique_ptr<Robot>>& robots);
	std::vector<unsigned int>& GetCode();
	void Draw(sf::RenderWindow& window);
};