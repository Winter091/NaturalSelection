#include "Core.h"
#include "Const.h"

void Core::PollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Core::Update()
{
}

void Core::Draw()
{
	window.clear(sf::Color(128, 128, 128));

	cellField.Draw(window);

	window.display();
}

void Core::MainLoop()
{
	while (window.isOpen())
	{
		PollEvents();
		Update();
		Draw();
	}
}

Core::Core()
	: window(sf::VideoMode(sda::WINDOW_W, sda::WINDOW_H), "Natural Selection")
{
	this->MainLoop();
}

