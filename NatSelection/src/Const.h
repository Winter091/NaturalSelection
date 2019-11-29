#pragma once

namespace sda
{
	const unsigned int WINDOW_W = 800;
	const unsigned int WINDOW_H = 900;

	// 0 is unlimited fps
	const unsigned int FPS_LIMIT = 0;

	const unsigned int COLOR_BG[] =    { 200, 200, 200 };
	const unsigned int COLOR_WALL[] =  { 48, 48, 48 };
	const unsigned int COLOR_FOOD[] =  { 31, 224, 72 };
	const unsigned int COLOR_ROBOT[] = { 243, 51, 12 };

	// Grid dimensions relative to window
	const unsigned int GRID_LEFT = 0;
	const unsigned int GRID_RIGHT = WINDOW_W;
	const unsigned int GRID_TOP = 100;
	const unsigned int GRID_BOTTOM = WINDOW_H;

	const unsigned int CELLS_IN_ROW = 40;
	const unsigned int CELL_W = (GRID_RIGHT - GRID_LEFT) / CELLS_IN_ROW;
	const unsigned int CELL_H = (GRID_BOTTOM - GRID_TOP) / CELLS_IN_ROW;

	const unsigned int ROBOT_COUNT = 64;

	// Start new generation if there are this amount of robots left
	const unsigned int ROBOT_MIN_COUNT = 8;

	// Each frame is one tick
	const unsigned int ROBOT_LIFE_TIME = 500;

	// 0% - 100%
	const unsigned int ROBOT_MUTATION_FREQ = 5;

	// 0% - 100%
	const unsigned int OBJECTS_FREQ = 25;

	// How much hp the food gives
	const unsigned int FOOD_HP = 100;

	// Simulate n generations and start drawing from (n+1)th
	const unsigned int PRE_GENERATE = 1000;
}