#pragma once

#include <vector>

#include "Robot.h"
#include "Cell.h"
#include "Const.h"

#include <SFML/Graphics.hpp>

class CellField
{
private:
	std::vector<std::unique_ptr<Robot>> robots;
	std::vector<std::vector<Cell*>> cells;

	unsigned int generation = 1;
	unsigned int bestTime = 0;
	unsigned int currTime = 0;
	unsigned int bestGeneration = 0;

	float avgWalkCommands = 0.0f;
	float avgEatFoodCommands = 0.0f;
	float avgChangeWallCommands = 0.0f;
	float avgFreeFoodCommands = 0.0f;
	float avgDoNothingCommands = 0.0f;

	unsigned int GetAvgHealth();
	void setCommandAmounts();

public:
	CellField();

	std::string getParams();
	unsigned int GetGeneration();

	void SetDefaultsForRobots();

	void DeleteObjects();
	void GenerateRandomObjects(unsigned int freq);

	void GenerateRandomRobots(unsigned int count = sda::ROBOT_COUNT);
	void InheritRobots();

	bool Update();
	void Draw(sf::RenderWindow& window);

};
