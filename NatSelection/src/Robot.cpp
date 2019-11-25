#include <ctime>

#include "Robot.h"
#include "Const.h"

Robot::Robot(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
	this->life_timer = sda::ROBOT_LIFE_TIME;

	srand(time(0));
	for (int i = 0; i < 64; i++)
	{
		this->code.push_back(rand() % 64);
	}
}

Robot::Robot(unsigned int x, unsigned int y, std::vector<unsigned int> code)
{
	this->x = x;
	this->y = y;

	this->code = code;
}

void Robot::Draw(sf::RenderWindow& window)
{
	//TODO: draw rectangle
}
