#include <iostream>

#include "Core.h"
#include "Const.h"

void Core::DrawInfo()
{
	this->window.draw(this->text);
}

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
	if (cellField.Update())
	{
		std::cout << cellField.GetGeneration() << std::endl;
	}
	this->text.setString(cellField.getParams());
}

void Core::Draw()
{
	window.clear(sf::Color(sda::COLOR_BG[0], sda::COLOR_BG[1], sda::COLOR_BG[2]));

	cellField.Draw(window);
	this->DrawInfo();

	window.display();
}

void Core::MainLoop()
{
	while (window.isOpen())
	{
		PollEvents();
		Update();
		if (cellField.GetGeneration() > sda::PRE_GENERATE)
		{
			Draw();

		}
	}
}

Core::Core()
	: window(sf::VideoMode(sda::WINDOW_W, sda::WINDOW_H), "Natural Selection"),
	cellField()
{
	this->font.loadFromFile("CarLock.otf");
	this->text.setString(cellField.getParams());
	this->text.setFont(this->font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color::Black);
	this->text.setPosition(10, 10);
	
	this->window.setFramerateLimit(sda::FPS_LIMIT);
	this->MainLoop();
}

