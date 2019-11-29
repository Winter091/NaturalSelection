#pragma once

#include <SFML/Graphics.hpp>

#include "CellField.h"

class Core
{
private:
	sf::RenderWindow window;
	CellField cellField;
	sf::Font font;
	sf::Text text;

	void DrawInfo();
	void PollEvents();
	void Update();
	void Draw();
	void MainLoop();

public:
	Core();
};
