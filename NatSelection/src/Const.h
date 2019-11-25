#pragma once

namespace sda
{
	const unsigned int WINDOW_W = 800;
	const unsigned int WINDOW_H = 900;

	const unsigned int GRID_LEFT = 0;
	const unsigned int GRID_RIGHT = WINDOW_W;
	const unsigned int GRID_TOP = 100;
	const unsigned int GRID_BOTTOM = WINDOW_H;

	const unsigned int CELLS_IN_ROW = 10;
	const unsigned int CELL_SIZE = WINDOW_W / CELLS_IN_ROW;

	const unsigned int ROBOT_COUNT = 64;
	const unsigned int ROBOT_LIFE_TIME = 512;
}