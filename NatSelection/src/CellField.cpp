#include <string>

#include "CellField.h"
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

	this->GenerateRandomObjects(15);
}

void CellField::GenerateRandomObjects(unsigned int freq)
{
	for (int i = 0; i < sda::CELLS_IN_ROW; i++)
		for (int j = 0; j < sda::CELLS_IN_ROW; j++)
			
			// if it's empty and random is good, place a new object
			if (this->cells[i][j]->GetObject() == "")
			{
				if (rand() % 100 < freq)
				{
					std::string obj = rand() % 2 ? "Food" : "Wall";
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
			unsigned int a = rand() % sda::CELLS_IN_ROW;
			unsigned int b = rand() % sda::CELLS_IN_ROW;

			if (this->cells[a][b]->GetObject() == "")
			{
				this->robots.push_back(new Robot(a, b));
			}
		}
	}
}

void CellField::InheritRobots()
{
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
	for (Robot*& r : this->robots)
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
			if (this->cells[i][j]->GetObject() == "Wall")
			{
				float x = sda::GRID_LEFT + sda::CELL_SIZE * i;
				float y = sda::GRID_TOP + sda::CELL_SIZE * j;

				rect.setPosition(x, y);
				rect.setFillColor(sf::Color(sda::COLOR_WALL[0], 
					sda::COLOR_WALL[1], sda::COLOR_WALL[2]));
				
				window.draw(rect);
			}

			else if (this->cells[i][j]->GetObject() == "Food")
			{
				float x = sda::GRID_LEFT + sda::CELL_SIZE * i;
				float y = sda::GRID_TOP + sda::CELL_SIZE * j;

				rect.setPosition(x, y);
				rect.setFillColor(sf::Color(sda::COLOR_FOOD[0], 
					sda::COLOR_FOOD[1], sda::COLOR_FOOD[2]));

				window.draw(rect);
			}
		}
	}
}
