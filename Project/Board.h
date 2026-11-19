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
	void DrawUi();

	bool ValidChipPlacement(int t_x, int t_y);
	bool RowLimitCheck(int t_row);
	bool ColLimitCheck(int t_col);

	bool PlaceChip(int t_slot, Team t_team);
	void Rotate();
	void FallChips();

	Directions GetDirection() const { return currentDirection; }
	Team WholeBoardCheck();

	int Evaluate(Team t_team);

private:
	Texture2D texture;

	bool CheckForWin(Vector2 t_dropIndex, Team t_droppedTeam);
	// Specific win types
	bool CheckHorizontal(Vector2 t_dropIndex, Team t_droppedTeam);
	bool CheckVertical(Vector2 t_dropIndex, Team t_droppedTeam);
	bool CheckDiagonal(Vector2 t_dropIndex, Team t_droppedTeam);

	// Count horizontals
	static const int SINGLE_ROW_SCORE = 10;
	static const int TWO_IN_A_ROW_SCORE = 50;
	static const int THREE_IN_A_ROW_SCORE = 150;
	int GetHorizontalScore(Team t_team);
	int GetVerticalScore(Team t_team);
	int GetDiagonalScore(Team t_team);

	static const int COL_MAX = 7;
	static const int ROW_MAX = 6;
	Chip board[COL_MAX][ROW_MAX];
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
	static const int WIN_CONDITION = 4;

	Rectangle rect;
};

