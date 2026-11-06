#pragma once
#include <raylib.h>
#include <iostream>

#include "Chip.h"

enum class Directions {
	Down,
	Up,
	Left,
	Right
};

class Board
{
public:
	Board();
	void Init();
	void Update();
	void Draw();

	bool ValidChipPlacement(int t_x, int t_y);
	bool RowLimitCheck(int t_row);
	bool ColLimitCheck(int t_col);

	void PlaceChip(int t_slot, Team t_team);
	void Rotate();
	void FallChips();

private:
	static const int ROW_MAX = 7;
	static const int COL_MAX = 6;
	Chip board[ROW_MAX][COL_MAX];
	int turn;
	static const int ROTATE_TURN = 4;
	Vector2 downDirection = { 0.0f, 1.0f };
	int directionIndex = 0;
	static const int DIRECTIONS_MAX = 4;
	Vector2 allDirections[DIRECTIONS_MAX] = { {0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, -1.0f}, {-1.0f, 0.0f} };
	Directions currentDirection = Directions::Down;

	int rowStart = 0;
	int colStart = 0;
	int indexDirectionX = 1;
	int indexDirectionY = 1;

	Vector2 directionIndicator;

	Rectangle rect;
};

