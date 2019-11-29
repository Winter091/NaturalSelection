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
	std::vector<std::vector<Cell*> > cells;

	unsigned int generation = 1;

	unsigned int GetAvgHealth();

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
