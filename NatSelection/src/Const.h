#pragma once

namespace sda
{
	const unsigned int WINDOW_W = 800;
	const unsigned int WINDOW_H = 900;

	// 0 is unlimited fps
	const unsigned int FPS_LIMIT = 60;

	const unsigned int COLOR_BG[] =    { 200, 200, 200 };
	const unsigned int COLOR_WALL[] =  { 48, 48, 48 };
	const unsigned int COLOR_FOOD[] =  { 31, 224, 72 };
	const unsigned int COLOR_ROBOT[] = { 243, 51, 12 };

	// Grid dimensions relative to window
	const unsigned int GRID_LEFT = 20;
	const unsigned int GRID_RIGHT = WINDOW_W - 20;
	const unsigned int GRID_TOP = 120;
	const unsigned int GRID_BOTTOM = WINDOW_H - 20;

	const unsigned int CELLS_IN_ROW = 40;

	const unsigned int CELL_W = (GRID_RIGHT - GRID_LEFT) / CELLS_IN_ROW;
	const unsigned int CELL_H = (GRID_BOTTOM - GRID_TOP) / CELLS_IN_ROW;

	const unsigned int ROBOT_FONT_SIZE = 5;

	const unsigned int ROBOT_COUNT = 64;

	// Start new generation if there are this or less amount of robots left
	const unsigned int ROBOT_MIN_COUNT = 8;

	// Each frame is one tick
	const unsigned int ROBOT_LIFE_TIME = 500;

	// 0% - 100%
	const unsigned int ROBOT_MUTATION_FREQ = 5;

	// 0% - 100%
	const unsigned int OBJECTS_FREQ = 25;

	// How much hp the food gives
	const unsigned int FOOD_HP = 100;

	// How much hp will the robot get free if command is [24-31]
	// -1 to set it so it will depend on the actual command
	const int FREE_HP = -1;

	// Works with (FREE_HP = -1)
	const float FREE_HP_MULTIPLIER = 0.35f;
}