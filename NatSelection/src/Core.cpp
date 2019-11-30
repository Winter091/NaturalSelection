#include <iostream>

#include "Core.h"
#include "Const.h"

void Core::PollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		// Arrows up and down are controlling delay
		else if (event.type == sf::Event::KeyPressed)	
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				delete this->sleepTimer;
				this->milliSecs++;
				this->sleepTimer = new sf::Time(sf::milliseconds(this->milliSecs));
			}

			else if (event.key.code == sf::Keyboard::Down)
			{
				delete this->sleepTimer;
				if (this->milliSecs)
					this->milliSecs--;
				this->sleepTimer = new sf::Time(sf::milliseconds(this->milliSecs));
			}
		}
	}
}

void Core::Update()
{
	// If true, the new generation is created in this frame
	if (cellField.Update())
	{
		//std::cout << cellField.GetGeneration() << std::endl;
	}

	// Some useful info
	std::string info = cellField.getParams();
	info.append("    Delay: ");
	info.append(std::to_string(this->milliSecs));
	info.append(" ms");
	this->text.setString(info);
}

void Core::Draw()
{
	while (window.isOpen())
	{
		window.clear(sf::Color(sda::COLOR_BG[0], sda::COLOR_BG[1], sda::COLOR_BG[2]));

		cellField.Draw(window);
		this->window.draw(this->text);

		window.display();
	}
}

void Core::MainLoop()
{
	while (window.isOpen())
	{
		PollEvents();
		Update();
		//if (cellField.GetGeneration() > sda::PRE_GENERATE)
			//Draw();
		sf::sleep(*this->sleepTimer);
	}
}

Core::Core()
	: window(sf::VideoMode(sda::WINDOW_W, sda::WINDOW_H), "Natural Selection"),
	cellField(),
	thread(&Core::Draw, this)
{
	this->font.loadFromFile("CarLock.otf");
	this->text.setString(cellField.getParams());
	this->text.setFont(this->font);
	this->text.setCharacterSize(12);
	this->text.setFillColor(sf::Color::Black);
	this->text.setPosition(10, 10);
	
	this->window.setFramerateLimit(sda::FPS_LIMIT);
	this->window.setActive(false);

	this->sleepTimer = new sf::Time(sf::milliseconds(this->milliSecs));

	thread.launch();
	this->MainLoop();
	thread.wait();
}

