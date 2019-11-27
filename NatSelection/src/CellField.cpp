#include <string>
#include <iostream>
#include <ctime>

#include "CellField.h"
#include "Cell.h"
#include "Const.h"

CellField::CellField()
	: cells(sda::CELLS_IN_ROW)
{
	for (int i = 0; i < sda::CELLS_IN_ROW; i++)
	{
		for (int j = 0; j < sda::CELLS_IN_ROW; j++)
		{
			cells[i].push_back(new Cell());
		}
	}

	std::srand(std::time(0));
	this->GenerateRandomObjects(sda::OBJECTS_FREQ);
	this->GenerateRandomRobots();
}

void CellField::GenerateRandomObjects(unsigned int freq)
{
	for (int i = 0; i < sda::CELLS_IN_ROW; i++)
		for (int j = 0; j < sda::CELLS_IN_ROW; j++)
			
			// if it's empty and random is good, place a new object
			if (this->cells[i][j]->GetObject() == Objects::NONE)
			{
				if (rand() % 100 < freq)
				{
					Objects obj = rand() % 2 ? Objects::FOOD : Objects::WALL;
					this->cells[i][j]->SetObject(obj);
				}
			}
}

void CellField::GenerateRandomRobots()
{
	for (int i = 0; i < sda::ROBOT_COUNT; i++)
	{
		while (true)
		{
			// Get random index
			unsigned int a = std::rand() % sda::CELLS_IN_ROW;
			unsigned int b = std::rand() % sda::CELLS_IN_ROW;

			if (this->cells[a][b]->GetObject() == Objects::NONE)
			{
				this->robots.push_back(new Robot(a, b));
				this->cells[a][b]->SetObject(Objects::ROBOT);
				break;
			}
		}
	}
}

void CellField::InheritRobots()
{
}

void CellField::Update()
{
	for (Robot* r : this->robots)
	{
		r->ExecuteProgram(this->cells);
	}
}

void CellField::Draw(sf::RenderWindow& window)
{
	// Vertical grid lines
	for (int i = 0; i <= sda::CELLS_IN_ROW; i++)
	{
		float x = sda::GRID_LEFT + sda::CELL_SIZE * i;

		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x, sda::GRID_TOP)),
			sf::Vertex(sf::Vector2f(x, sda::GRID_BOTTOM))
		};

		window.draw(line, 2, sf::Lines);
	}

	// Horisontal grid lines
	for (int i = 0; i <= sda::CELLS_IN_ROW; i++)
	{
		float y = sda::GRID_TOP + sda::CELL_SIZE * i;

		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(sda::GRID_LEFT, y)),
			sf::Vertex(sf::Vector2f(sda::GRID_RIGHT, y))
		};

		window.draw(line, 2, sf::Lines);
	}

	// Robots
	for (Robot* r : this->robots)
	{
		(*r).Draw(window);
	}

	// Walls & food
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(sda::CELL_SIZE, sda::CELL_SIZE));
	rect.setOutlineThickness(0.0f);

	for (int i = 0; i < sda::CELLS_IN_ROW; i++)
	{
		for (int j = 0; j < sda::CELLS_IN_ROW; j++)
		{
			if (this->cells[i][j]->GetObject() == Objects::FOOD)
			{
				sf::Color color;
				color.r = sda::COLOR_FOOD[0];
				color.g = sda::COLOR_FOOD[1];
				color.b = sda::COLOR_FOOD[2];

				float x = sda::GRID_LEFT + sda::CELL_SIZE * i;
				float y = sda::GRID_TOP + sda::CELL_SIZE * j;

				rect.setPosition(x, y);
				rect.setFillColor(color);
				window.draw(rect);
			}

			else if (this->cells[i][j]->GetObject() == Objects::WALL)
			{
				sf::Color color;
				color.r = sda::COLOR_WALL[0];
				color.g = sda::COLOR_WALL[1];
				color.b = sda::COLOR_WALL[2];

				float x = sda::GRID_LEFT + sda::CELL_SIZE * i;
				float y = sda::GRID_TOP + sda::CELL_SIZE * j;

				rect.setPosition(x, y);
				rect.setFillColor(color);
				window.draw(rect);
			}
		}
	}
}
