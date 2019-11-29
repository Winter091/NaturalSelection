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

	// There's a delay in action commiting 
	int actionTimer;
	Actions currAction;
	int pendingMoveX, pendingMoveY;

	// code's length is 64
	std::vector<unsigned int> code;
	unsigned int codePtr;

	// All robots share the same drawing stuff
	static sf::RectangleShape drawRect;
	static sf::Font font;
	static sf::Text text;

	bool CheckBorders(unsigned int direction);

	void DoCurrentAction(const std::vector<std::vector<Cell*>>& cells);
	void Move(unsigned int direction, const std::vector<std::vector<Cell*>>& cells);
	void EatFood(unsigned int direction, const std::vector<std::vector<Cell*>>& cells);
	void TurnWallIntoFood(unsigned int direction, const std::vector<std::vector<Cell*>>& cells);
	void AddLife(unsigned int amount);

	void MoveTo(unsigned int x, unsigned int y, const std::vector<std::vector<Cell*>>& cells);

public:
	Robot(unsigned int x, unsigned int y);
	Robot(unsigned int x, unsigned int y, std::vector<unsigned int> code);

	std::vector<unsigned int>& GetCode();
	int GetHealth();
	unsigned int GetX();
	unsigned int GetY();

	static void InitDrawingStuff();
	void SetDefaults();
	void SetRandomPos(std::vector<std::vector<Cell*>>& cells);

	bool ExecuteProgram(std::vector<std::vector<Cell*>>& cells, std::vector<std::unique_ptr<Robot>>& robots);
	void Draw(sf::RenderWindow& window);
};