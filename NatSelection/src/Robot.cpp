#include "Robot.h"
#include "Const.h"

// Static objects declaration
sf::RectangleShape Robot::drawRect;
sf::Font Robot::font;
sf::Text Robot::text;

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
			this->SetPosition(this->x + this->pendingMoveX, this->y + this->pendingMoveY, cells);
		}

		else if (this->currAction == Actions::TURNING_WALL_TO_FOOD)
		{
			cells[this->x + this->pendingMoveX][this->y + this->pendingMoveY]->SetObject(Objects::FOOD);
		}

		this->currAction = Actions::NONE;
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
				this->SetPosition(this->x - 1, this->y, cells);
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
				this->SetPosition(this->x, this->y - 1, cells);
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
				this->SetPosition(this->x + 1, this->y, cells);
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
				this->SetPosition(this->x, this->y + 1, cells);
			}
		}
	}
}

// this->code[63] is time to wait before eating food
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

// this->code[62] is time to wait before changing wall to food
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
	if (sda::FREE_HP == -1)
		this->lifeTimer += amount * sda::FREE_HP_MULTIPLIER;
	else
		this->lifeTimer += sda::FREE_HP;
}

Robot::Robot(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
	
	this->SetDefaults();

	// 64 commands, each command is in [0-63] range
	for (int i = 0; i < 64; i++)
	{
		this->code.push_back(std::rand() % 64);
	}
}

Robot::Robot(unsigned int x, unsigned int y, std::vector<unsigned int> code)
{
	this->x = x;
	this->y = y;
	this->code = code;

	this->SetDefaults();
}

void Robot::InitDrawingStuff()
{
	Robot::font.loadFromFile("CarLock.otf");

	Robot::drawRect.setSize(sf::Vector2f(sda::CELL_W, sda::CELL_H));
	Robot::drawRect.setOutlineThickness(0.0f);
	Robot::drawRect.setFillColor(sf::Color(sda::COLOR_ROBOT[0], sda::COLOR_ROBOT[1], sda::COLOR_ROBOT[2]));

	Robot::text.setFont(Robot::font);
	Robot::text.setCharacterSize(sda::ROBOT_FONT_SIZE);
	Robot::text.setFillColor(sf::Color::Black);
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

unsigned int Robot::GetX()
{
	return x;
}

unsigned int Robot::GetY()
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
			this->SetPosition(a, b, cells);
			break;
		}
	}
}

void Robot::SetPosition(unsigned int x, unsigned int y, const std::vector<std::vector<Cell*>>& cells)
{
	cells[this->x][this->y]->RemoveObject();
	this->x = x;
	this->y = y;
	cells[this->x][this->y]->SetObject(Objects::ROBOT);
}

// Returns true only if this robot has died right now
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
	// To avoid errors that happen because
	// Draw() is executed by another thread
	if (this == nullptr)
		return;
	
	// Rectangle
	float x = sda::GRID_LEFT + sda::CELL_W * this->x;
	float y = sda::GRID_TOP + sda::CELL_H * this->y;
	this->drawRect.setPosition(x, y);
	window.draw(this->drawRect);
	
	if (sda::ROBOT_DRAW_TEXT)
	{
		// Text on top representing amount of HP
		this->text.setString(std::to_string(this->lifeTimer));
		this->text.setPosition(x + 1, y + 1);
		window.draw(this->text);
	}
}
