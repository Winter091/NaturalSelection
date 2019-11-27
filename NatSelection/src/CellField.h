#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Cell.h"
#include "Robot.h"

class CellField
{
private:
	std::vector<std::vector<Cell*> > cells;
	std::vector<Robot*> robots;

public:
	CellField();

	void GenerateRandomObjects(unsigned int freq);
	void GenerateRandomRobots();
	void InheritRobots();

	void Update();
	void Draw(sf::RenderWindow& window);

};
