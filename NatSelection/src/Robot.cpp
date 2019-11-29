#include "Robot.h"
#include "Const.h"


// direction has to be [0-7]
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

void Robot::DoCurrentAction(const std::vector<std::vector<Cell*>>& cells)
{
	this->actionTimer--;
	if (actionTimer <= 0)
	{
		if (this->currAction == Actions::EATING_FOOD)
		{
			this->lifeTimer += sda::FOOD_HP;
			this->currAction = Actions::NONE;
			cells[this->x][this->y]->RemoveObject();
			this->x += this->pendingMoveX;
			this->y += this->pendingMoveY;
			cells[this->x][this->y]->SetObject(Objects::ROBOT);
		}

		else if (this->currAction == Actions::TURNING_WALL_TO_FOOD)
		{
			this->currAction = Actions::NONE;
			cells[this->x + this->pendingMoveX][this->y + this->pendingMoveY]->SetObject(Objects::FOOD);
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
	// Left
	if (direction == 0 || direction == 1 || direction == 7)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x - 1][this->y]->GetObject() == Objects::FOOD)
			{
				this->currAction = Actions::EATING_FOOD;
				this->actionTimer = this->code[63];
				this->pendingMoveX = -1;
				this->pendingMoveY = 0;
			}
		}
	}

	// Up
	if (direction == 1 || direction == 2 || direction == 3)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x][this->y - 1]->GetObject() == Objects::FOOD)
			{
				this->currAction = Actions::EATING_FOOD;
				this->actionTimer = this->code[63];
				this->pendingMoveX = 0;
				this->pendingMoveY = -1;
			}
		}
	}

	// Right
	if (direction == 3 || direction == 4 || direction == 5)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x + 1][this->y]->GetObject() == Objects::FOOD)
			{
				this->currAction = Actions::EATING_FOOD;
				this->actionTimer = this->code[63];
				this->pendingMoveX = 1;
				this->pendingMoveY = 0;
			}
		}
	}

	// Down
	if (direction == 5 || direction == 6 || direction == 7)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x][this->y + 1]->GetObject() == Objects::FOOD)
			{
				this->currAction = Actions::EATING_FOOD;
				this->actionTimer = this->code[63];
				this->pendingMoveX = 0;
				this->pendingMoveY = 1;
			}
		}
	}
}

void Robot::TurnWallIntoFood(unsigned int direction, const std::vector<std::vector<Cell*>>& cells)
{
	// Left
	if (direction == 0 || direction == 1 || direction == 7)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x - 1][this->y]->GetObject() == Objects::WALL)
			{
				this->currAction = Actions::TURNING_WALL_TO_FOOD;
				this->actionTimer = this->code[62];
				this->pendingMoveX = -1;
				this->pendingMoveY = 0;
			}
		}
	}

	// Up
	if (direction == 1 || direction == 2 || direction == 3)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x][this->y - 1]->GetObject() == Objects::WALL)
			{
				this->currAction = Actions::TURNING_WALL_TO_FOOD;
				this->actionTimer = this->code[62];
				this->pendingMoveX = 0;
				this->pendingMoveY = -1;
			}
		}
	}

	// Right
	if (direction == 3 || direction == 4 || direction == 5)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x + 1][this->y]->GetObject() == Objects::WALL)
			{
				this->currAction = Actions::TURNING_WALL_TO_FOOD;
				this->actionTimer = this->code[62];
				this->pendingMoveX = 1;
				this->pendingMoveY = 0;
			}
		}
	}

	// Down
	if (direction == 5 || direction == 6 || direction == 7)
	{
		if (CheckBorders(direction))
		{
			if (cells[this->x][this->y + 1]->GetObject() == Objects::WALL)
			{
				this->currAction = Actions::TURNING_WALL_TO_FOOD;
				this->actionTimer = this->code[62];
				this->pendingMoveX = 0;
				this->pendingMoveY = 1;
			}
		}
	}
}

void Robot::AddLife(unsigned int amount)
{
	this->lifeTimer += amount / 1.5;
}

Robot::Robot(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
	
	this->SetDefaults();

	this->font.loadFromFile("CarLock.otf");

	this->text.setFont(this->font);
	this->text.setCharacterSize(11);
	this->text.setFillColor(sf::Color::Black);

	// 64 commands, each command is in [0-63] range
	for (int i = 0; i < 64; i++)
	{
		this->code.push_back(rand() % 64);
	}

	this->drawRect.setSize(sf::Vector2f(sda::CELL_W, sda::CELL_H));
	this->drawRect.setOutlineThickness(0.0f);
	this->drawRect.setFillColor(sf::Color(sda::COLOR_ROBOT[0], sda::COLOR_ROBOT[1], sda::COLOR_ROBOT[2]));
}

Robot::Robot(unsigned int x, unsigned int y, std::vector<unsigned int> code)
{
	this->x = x;
	this->y = y;
	this->code = code;

	this->SetDefaults();

	this->font.loadFromFile("CarLock.otf");

	this->text.setFont(this->font);
	this->text.setCharacterSize(11);
	this->text.setFillColor(sf::Color::Black);

	this->drawRect.setSize(sf::Vector2f(sda::CELL_W, sda::CELL_H));
	this->drawRect.setOutlineThickness(0.0f);
	this->drawRect.setFillColor(sf::Color(sda::COLOR_ROBOT[0], sda::COLOR_ROBOT[1], sda::COLOR_ROBOT[2]));
}

int Robot::GetHealth()
{
	return this->lifeTimer;
}

void Robot::SetDefaults()
{
	this->lifeTimer = sda::ROBOT_LIFE_TIME;
	this->codePtr = 0;
	this->actionTimer = 0;
	this->currAction = Actions::NONE;
	this->pendingMoveX = 0;
	this->pendingMoveY = 0;
}

int Robot::getX()
{
	return x;
}

int Robot::getY()
{
	return y;
}

void Robot::SetRandomPos(std::vector<std::vector<Cell*>>& cells)
{
	while (true)
	{
		int a = std::rand() % sda::CELLS_IN_ROW;
		int b = std::rand() % sda::CELLS_IN_ROW;

		if (cells[a][b]->GetObject() == Objects::NONE)
		{
			cells[this->x][this->y]->SetObject(Objects::NONE);
			this->x = a;
			this->y = b;
			cells[a][b]->SetObject(Objects::ROBOT);
			break;
		}
	}
}

bool Robot::ExecuteProgram(std::vector<std::vector<Cell*>>& cells, std::vector<std::unique_ptr<Robot>>& robots)
{
	if (--this->lifeTimer <= 0)
	{
		return true;
	}
	
	if (this->currAction != Actions::NONE)
	{
		this->DoCurrentAction(cells);
		return false;
	}
	
	unsigned int cmd = this->code[this->codePtr];

	// Move
	if (cmd >= 0 && cmd <= 7)
	{
		this->Move(cmd, cells);
	}

	else if (cmd >= 8 && cmd <= 15)
	{
		this->EatFood(cmd % 8, cells);
	}

	else if (cmd >= 16 && cmd <= 23)
	{
		this->TurnWallIntoFood(cmd % 8, cells);
	}

	else if (cmd >= 24 && cmd <= 31)
	{
		this->AddLife(cmd % 8);
	}

	else if (cmd >= 32 && cmd <= 63)
	{
		// Nothing
	}

	this->codePtr++;
	if (this->codePtr > 63)
		this->codePtr = 0;

	return false;
}

std::vector<unsigned int>& Robot::GetCode()
{
	return this->code;
}

void Robot::Draw(sf::RenderWindow& window)
{
	float x = sda::GRID_LEFT + sda::CELL_W * this->x;
	float y = sda::GRID_TOP + sda::CELL_H * this->y;
	this->drawRect.setPosition(x, y);
	window.draw(this->drawRect);
	
	this->text.setString(std::to_string(this->lifeTimer));
	this->text.setPosition(x + 1, y + 1);
	window.draw(this->text);
}
