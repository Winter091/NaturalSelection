#include "Robot.h"
#include "Const.h"

bool Robot::CheckBorders(unsigned int direction)
{
	// Left
	if (direction == 0 || direction == 1 || direction == 7)
		if (this->x <= 0) return false;

	// Up
	if (direction == 1 || direction == 2 || direction == 3)
		if (this->y <= 0) return false;

	// Right
	if (direction == 3 || direction == 4 || direction == 5)
		if (this->x >= sda::CELLS_IN_ROW - 1) return false;

	// Down
	if (direction == 5 || direction == 6 || direction == 7)
		if (this->y >= sda::CELLS_IN_ROW - 1) return false;

	return true;
}

void Robot::DoCurrentAction()
{
	this->actionTimer--;
	if (actionTimer <= 0)
	{
		if (this->currAction == Actions::EATING_FOOD)
		{
			// TODO
		}

		else if (this->currAction == Actions::TURNING_WALL_TO_FOOD)
		{
			// TODO
		}
	}
}

void Robot::Move(unsigned int direction, const std::vector<std::vector<Cell*>>& cells)
{
	// Left
	if (direction == 0 || direction == 1 || direction == 7)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x - 1][this->y]->GetObject() == Objects::NONE)
			{
				cells[this->x][this->y]->RemoveObject();
				this->x--;
				cells[this->x][this->y]->SetObject(Objects::ROBOT);
			}
		}
	}

	// Up
	if (direction == 1 || direction == 2 || direction == 3)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x][this->y - 1]->GetObject() == Objects::NONE)
			{
				cells[this->x][this->y]->RemoveObject();
				this->y--;
				cells[this->x][this->y]->SetObject(Objects::ROBOT);
			}
		}
	}

	// Right
	if (direction == 3 || direction == 4 || direction == 5)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x + 1][this->y]->GetObject() == Objects::NONE)
			{
				cells[this->x][this->y]->RemoveObject();
				this->x++;
				cells[this->x][this->y]->SetObject(Objects::ROBOT);
			}
		}
	}

	// Down
	if (direction == 5 || direction == 6 || direction == 7)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x][this->y + 1]->GetObject() == Objects::NONE)
			{
				cells[this->x][this->y]->RemoveObject();
				this->y++;
				cells[this->x][this->y]->SetObject(Objects::ROBOT);
			}
		}
	}
}

void Robot::EatFood(unsigned int direction, const std::vector<std::vector<Cell*>>& cells)
{
}

void Robot::TurnWallIntoFood(unsigned int direction, const std::vector<std::vector<Cell*>>& cells)
{
}

void Robot::AddLife(unsigned int amount)
{
}

Robot::Robot(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
	this->lifeTimer = sda::ROBOT_LIFE_TIME;
	this->codePtr = 0;
	this->actionTimer = 0;
	this->currAction = Actions::NONE;

	// 64 commands, each command is in [0-63] range
	for (int i = 0; i < 64; i++)
	{
		this->code.push_back(rand() % 64);
	}

	this->drawRect.setSize(sf::Vector2f(sda::CELL_SIZE, sda::CELL_SIZE));
	this->drawRect.setOutlineThickness(0.0f);
	this->drawRect.setFillColor(sf::Color(sda::COLOR_ROBOT[0], sda::COLOR_ROBOT[1], sda::COLOR_ROBOT[2]));
}

Robot::Robot(unsigned int x, unsigned int y, std::vector<unsigned int> code)
{
	this->x = x;
	this->y = y;
	this->lifeTimer = sda::ROBOT_LIFE_TIME;
	this->code = code;
	this->codePtr = 0;
	this->actionTimer = 0;
	this->currAction = Actions::NONE;

	this->drawRect.setSize(sf::Vector2f(sda::CELL_SIZE, sda::CELL_SIZE));
	this->drawRect.setOutlineThickness(0.0f);
	this->drawRect.setFillColor(sf::Color(sda::COLOR_ROBOT[0], sda::COLOR_ROBOT[1], sda::COLOR_ROBOT[2]));
}

void Robot::ExecuteProgram(const std::vector<std::vector<Cell*>>& cells)
{
	if (this->currAction != Actions::NONE)
	{
		this->DoCurrentAction();
		return;
	}
	
	unsigned int cmd = this->code[this->codePtr];

	// Move
	if (cmd >= 0 && cmd <= 7)
	{
		this->Move(cmd, cells);
	}

	this->codePtr++;
	if (this->codePtr > 63)
		this->codePtr = 0;
}

void Robot::Draw(sf::RenderWindow& window)
{
	float x = sda::GRID_LEFT + sda::CELL_SIZE * this->x;
	float y = sda::GRID_TOP + sda::CELL_SIZE * this->y;
	this->drawRect.setPosition(x, y);

	window.draw(this->drawRect);
}
