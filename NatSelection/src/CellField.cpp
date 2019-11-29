#include <string>
#include <iostream>
#include <ctime>

#include "CellField.h"
#include "Cell.h"
#include "Const.h"

unsigned int CellField::GetAvgHealth()
{
	unsigned int sum = 0;
	for (int i = 0; i < this->robots.size(); i++)
	{
		sum += robots[i]->GetHealth();
	}
	return sum / this->robots.size();
}

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

	Robot::InitDrawingStuff();

	std::srand(std::time(0));
	this->GenerateRandomObjects(sda::OBJECTS_FREQ);
	this->GenerateRandomRobots();
}

std::string CellField::getParams()
{
	std::string params;

	params.append("Robot count: ");
	params.append(std::to_string(this->robots.size()));
	params.append("\n");

	params.append("AVG Health: ");
	params.append(std::to_string(this->GetAvgHealth()));
	params.append("\n");

	params.append("Generation: ");
	params.append(std::to_string(this->generation));

	params.append("     Curr generation time: ");
	params.append(std::to_string(this->currTime));
	params.append("\n");

	params.append("Best generation: ");
	params.append(std::to_string(this->bestGeneration));

	params.append("     Best generation time: ");
	params.append(std::to_string(this->bestTime));
	params.append("\n");

	return params;
}

unsigned int CellField::GetGeneration()
{
	return this->generation;
}

void CellField::SetDefaultsForRobots()
{
	for (int i = 0; i < this->robots.size(); i++)
	{
		robots[i]->SetDefaults();
	}
}

void CellField::DeleteObjects()
{
	for (int i = 0; i < sda::CELLS_IN_ROW; i++)
	{
		for (int j = 0; j < sda::CELLS_IN_ROW; j++)
		{
			if (this->cells[i][j]->GetObject() == Objects::FOOD || this->cells[i][j]->GetObject() == Objects::WALL)
			{
				this->cells[i][j]->SetObject(Objects::NONE);
			}
		}
	}
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

void CellField::GenerateRandomRobots(unsigned int count)
{
	for (int i = 0; i < count; i++)
	{
		while (true)
		{
			// Get random index
			unsigned int a = std::rand() % sda::CELLS_IN_ROW;
			unsigned int b = std::rand() % sda::CELLS_IN_ROW;

			if (this->cells[a][b]->GetObject() == Objects::NONE)
			{
				this->robots.push_back(std::make_unique<Robot>(a, b));
				//this->robots.push_back(new Robot(a, b));
				this->cells[a][b]->SetObject(Objects::ROBOT);
				break;
			}
		}
	}
}

void CellField::InheritRobots()
{	
	for (int i = 0; i < sda::ROBOT_COUNT - sda::ROBOT_MIN_COUNT; i++)
	{
		// Code from random 4 robots
		unsigned int robot1 = std::rand() % sda::ROBOT_MIN_COUNT;
		unsigned int robot2 = std::rand() % sda::ROBOT_MIN_COUNT;
		unsigned int robot3 = std::rand() % sda::ROBOT_MIN_COUNT;
		unsigned int robot4 = std::rand() % sda::ROBOT_MIN_COUNT;

		std::vector<unsigned int> code1 = robots[robot1]->GetCode();
		std::vector<unsigned int> code2 = robots[robot2]->GetCode();
		std::vector<unsigned int> code3 = robots[robot3]->GetCode();
		std::vector<unsigned int> code4 = robots[robot4]->GetCode();

		std::vector<unsigned int> newCode;
		newCode.insert(newCode.end(), code1.begin()     , code1.begin() + 16);
		newCode.insert(newCode.end(), code2.begin() + 16, code2.begin() + 32);
		newCode.insert(newCode.end(), code3.begin() + 32, code3.begin() + 48);
		newCode.insert(newCode.end(), code4.begin() + 48, code4.begin() + 64);

		// Mutate this robot if luck is good
		if (std::rand() % 100 < sda::ROBOT_MUTATION_FREQ)
		{
			// Remove 8 random commands
			for (int i = 0; i < 8; i++)
				newCode.erase(newCode.begin() + std::rand() % newCode.size());

			// Push random commands
			for (int i = 0; i < 8; i++)
				newCode.push_back(std::rand() % 64);
		}

		// Put this robot in empty cell
		while (true)
		{
			unsigned int a = std::rand() % sda::CELLS_IN_ROW;
			unsigned int b = std::rand() % sda::CELLS_IN_ROW;

			if (this->cells[a][b]->GetObject() == Objects::NONE)
			{
				this->robots.push_back(std::make_unique<Robot>(a, b, newCode));
				break;
			}
		}
	}
}

bool CellField::Update()
{	
	currTime++;
	
	for (int i = 0; i < this->robots.size(); i++)
	{
		// If robot has died
		if (robots[i]->ExecuteProgram(this->cells, this->robots))
		{
			// Remove this robot
			int x = robots[i]->GetX();
			int y = robots[i]->GetY();
			this->cells[x][y]->RemoveObject();
			this->robots.erase(std::remove(robots.begin(), robots.end(), robots[i]), robots.end());
		}
	}

	if (this->robots.size() <= sda::ROBOT_MIN_COUNT)
	{

		if (this->currTime > this->bestTime)
		{
			this->bestTime = this->currTime;
			this->bestGeneration = this->generation;
		}

		this->generation++;
		this->currTime = 0;

		// ReCreate all objects
		this->DeleteObjects();
		this->GenerateRandomObjects(sda::OBJECTS_FREQ);

		// Shuffle all remaining robots
		for (int i = 0; i < this->robots.size(); i++)
		{
			robots[i]->SetRandomPos(this->cells);
		}
		
		// If there are not enough robots (less than sda::ROBOT_MIN_COUNT),
		// add random robots
		if (this->robots.size() < sda::ROBOT_MIN_COUNT)
		{
			this->GenerateRandomRobots(sda::ROBOT_MIN_COUNT - this->robots.size());
		}

		this->InheritRobots();
		this->SetDefaultsForRobots();

		return true;
	}

	return false;
}

void CellField::Draw(sf::RenderWindow& window)
{
	// Vertical grid lines
	for (int i = 0; i <= sda::CELLS_IN_ROW; i++)
	{
		float x = sda::GRID_LEFT + sda::CELL_W * i;

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
		float y = sda::GRID_TOP + sda::CELL_H * i;

		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(sda::GRID_LEFT, y)),
			sf::Vertex(sf::Vector2f(sda::GRID_RIGHT, y))
		};

		window.draw(line, 2, sf::Lines);
	}

	// Robots
	for (int i = 0; i < this->robots.size(); i++)
	{
		robots[i]->Draw(window);
	}

	// Walls & food
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(sda::CELL_W, sda::CELL_H));
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

				float x = sda::GRID_LEFT + sda::CELL_W * i;
				float y = sda::GRID_TOP + sda::CELL_H * j;

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

				float x = sda::GRID_LEFT + sda::CELL_W * i;
				float y = sda::GRID_TOP + sda::CELL_H * j;

				rect.setPosition(x, y);
				rect.setFillColor(color);
				window.draw(rect);
			}
		}
	}
}
