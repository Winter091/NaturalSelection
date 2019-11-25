#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class Robot
{
private:
	unsigned int x, y;
	unsigned int life_timer;
	std::vector<unsigned int> code;

public:
	Robot(unsigned int x, unsigned int y);
	Robot(unsigned int x, unsigned int y, std::vector<unsigned int> code);

	void Draw(sf::RenderWindow& window);
};