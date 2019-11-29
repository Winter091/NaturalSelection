#pragma once

#include <SFML/Graphics.hpp>

#include "CellField.h"

class Core
{
private:
	sf::RenderWindow window;
	CellField cellField;

	// to draw text above grid
	sf::Font font;
	sf::Text text;

	void PollEvents();
	void Update();
	void Draw();
	void MainLoop();

public:
	Core();
};
