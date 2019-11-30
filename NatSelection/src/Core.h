#pragma once

#include <SFML/Graphics.hpp>

#include "CellField.h"

#include <thread>

class Core
{
private:
	sf::RenderWindow window;
	CellField cellField;

	// to draw text above grid
	sf::Font font;
	sf::Text text;

	// Draw() has its own thread
	sf::Thread thread;

	// To slow down main thread
	unsigned long long milliSecs = 0;
	sf::Time* sleepTimer;

	void PollEvents();
	void Update();
	void Draw();
	void MainLoop();

public:
	Core();
};
