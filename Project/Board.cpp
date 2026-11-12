#include "Board.h"

Board::Board() : directionIndicator({0.0f, 0.0f}), rect({0.0f, 0.0f, 0.0f, 0.0f})
{
}

void Board::Init()
{
	directionIndicator = { GetScreenWidth() / 2.0f, GetScreenHeight() - 20.0f };
	rect.x = GetScreenWidth() * 0.1f;
	rect.y = GetScreenHeight() * 0.1f;
	rect.width = GetScreenWidth() * 0.8f;
	rect.height = GetScreenHeight() * 0.8f;

	Chip::SetRadius(rect.height * 0.06f);
	Vector2 topCorner = { rect.x + (Chip::GetRadius() * 1.2f), rect.y + (Chip::GetRadius() * 1.2f) };
	Vector2 chipPos = {};
	Vector2 chipLocalPos = {};
	float chipPosMult = (Chip::GetRadius() * 3);

	for (int row = 0; row < COL_MAX; row++)
	{
		for (int col = 0; col < ROW_MAX; col++)
		{
			board[row][col].Init(downDirection);

			chipLocalPos = { row * chipPosMult, col * chipPosMult };
			chipPos = Vector2Add(topCorner, chipLocalPos);
			board[row][col].SetPos(chipPos);
		}
	}

	indexDirectionX = -1;
	indexDirectionY = -1;
	rowStart = ROW_MAX - 1;
	colStart = COL_MAX - 1;
	directionIndicator = { GetScreenWidth() / 2.0f, GetScreenHeight() - 20.0f };
}

void Board::Update()
{
}

void Board::Draw()
{
	DrawRectanglePro(rect, { 0.0f, 0.0f }, 0, BLUE);

	for (int row = 0; row < COL_MAX; row++)
	{
		for (int col = 0; col < ROW_MAX; col++)
		{
			board[row][col].Draw();
		}
	}

	switch (currentDirection)
	{
	case Directions::Down:
		DrawText("Down", 10, 10, 20, WHITE);
		break;
	case Directions::Up:
		DrawText("Up", 10, 10, 20, WHITE);
		break;
	case Directions::Left:
		DrawText("Left", 10, 10, 20, WHITE);
		break;
	case Directions::Right:
		DrawText("Right", 10, 10, 20, WHITE);
		break;
	default:
		break;
	}

	DrawCircleV(directionIndicator, 10.0f, RED);

}

bool Board::ValidChipPlacement(int t_x, int t_y)
{
	return (t_y < ROW_MAX && t_y >= 0 && t_x < COL_MAX && t_x >= 0);
}

bool Board::PlaceChip(int t_slot, Team t_team)
{
	bool placed = false;

	int tempX = 0;
	int tempY = 0;

	switch (currentDirection)
	{
	case Directions::Down:
		tempX = t_slot;
		tempY = 0;
		break;
	case Directions::Up:
		tempX = t_slot;
		tempY = ROW_MAX - 1;
		break;
	case Directions::Left:
		tempY = t_slot;
		tempX = COL_MAX - 1;
		break;
	case Directions::Right:
		tempY = t_slot;
		tempX = 0;
		break;
	default:
		break;
	}

	int lastX = tempX;
	int lastY = tempY;

	while (ValidChipPlacement(tempX, tempY))
	{
		if (board[tempX][tempY].GetTeam() != Team::None)
		{
			if (board[lastX][lastY].GetTeam() == Team::None)
			{
				board[lastX][lastY].SetTeam(t_team);

				if (CheckForWin({ (float)lastX, (float)lastY }, t_team))
					std::cout << "WIN FOUND: " << static_cast<int>(t_team) << "\n";
			}
			return placed;
		}

		if (!ValidChipPlacement(tempX + downDirection.x, tempY + downDirection.y))
		{
			board[tempX][tempY].SetTeam(t_team);
			placed = true;
		}

		lastX = tempX;
		lastY = tempY;

		tempX += downDirection.x;
		tempY += downDirection.y;
	}

	return placed;
}

void Board::Rotate()
{
	directionIndex++;

	if (directionIndex >= DIRECTIONS_MAX)
	{
		directionIndex = 0;
	}

	downDirection = allDirections[directionIndex];

	if (downDirection.x == 1)
	{
		currentDirection = Directions::Right;
		indexDirectionX = -1;
		indexDirectionY = -1;
		rowStart = COL_MAX - 1;
		colStart = ROW_MAX - 1;
		directionIndicator = { GetScreenWidth() - 20.0f, GetScreenHeight() / 2.0f };
	}
	if (downDirection.x == -1)
	{
		currentDirection = Directions::Left;
		indexDirectionX = 1;
		indexDirectionY = 1;
		rowStart = 0;
		colStart = 0;
		directionIndicator = { 20.0f, GetScreenHeight() / 2.0f };
	}
	if (downDirection.y == 1)
	{
		currentDirection = Directions::Down;
		indexDirectionX = -1;
		indexDirectionY = -1;
		rowStart = COL_MAX - 1;
		colStart = ROW_MAX - 1;
		directionIndicator = { GetScreenWidth() / 2.0f, GetScreenHeight() - 20.0f };
	}
	if (downDirection.y == -1)
	{
		currentDirection = Directions::Up;
		indexDirectionX = 1;
		indexDirectionY = 1;
		rowStart = 0;
		colStart = 0;
		directionIndicator = { GetScreenWidth() / 2.0f, 20.0f };
	}

	FallChips();
}


bool Board::RowLimitCheck(int t_row)
{
	bool result = false;

	switch (currentDirection)
	{
	case Directions::Up:
		result = t_row < COL_MAX;
		break;
	case Directions::Down:
		result = t_row >= 0;
		break;
	case Directions::Left:
		result = t_row < COL_MAX;
		break;
	case Directions::Right:
		result = t_row >= 0;
		break;
	default:
		break;
	}

	return result;
}

bool Board::ColLimitCheck(int t_col)
{
	bool result = false;

	switch (currentDirection)
	{
	case Directions::Up:
		result = t_col < ROW_MAX;
		break;
	case Directions::Down:
		result = t_col >= 0;
		break;
	case Directions::Left:
		result = t_col < ROW_MAX;
		break;
	case Directions::Right:
		result = t_col >= 0;
		break;
	default:
		break;
	}

	return result;
}

bool Board::CheckForWin(Vector2 t_dropIndex, Team t_droppedTeam)
{
	// Error Checking
	if (t_dropIndex.x >= COL_MAX || t_dropIndex.x < 0)
		return false;
	if (t_dropIndex.y >= ROW_MAX || t_dropIndex.y < 0)
		return false;

	// Horizontal Check
	if (CheckHorizontal(t_dropIndex, t_droppedTeam))
		return true;

	// Vertical Check
	if (CheckVertical(t_dropIndex, t_droppedTeam))
		return true;

	// Diagonal Check
	if (CheckDiagonal(t_dropIndex, t_droppedTeam))
		return true;

	return false;
}

bool Board::CheckHorizontal(Vector2 t_dropIndex, Team t_droppedTeam)
{
	// Horizontal Check (Positive)
	int winCondition = t_dropIndex.x + WIN_CONDITION;
	for (int x = t_dropIndex.x; x < winCondition; x++)
	{
		// Check if out of range
		if (x >= COL_MAX)
			break;

		if (board[x][(int)t_dropIndex.y].GetTeam() != t_droppedTeam)
			break; // Not the same team

		// If you reached goal
		if (x >= winCondition - 1)
			return true;
	}

	// Horizontal Check (Negative)
	winCondition = t_dropIndex.x - WIN_CONDITION;
	for (int x = t_dropIndex.x; x < winCondition; x--)
	{
		// Check if out of range
		if (x < 0)
			break;

		if (board[x][(int)t_dropIndex.y].GetTeam() != t_droppedTeam)
			break; // Not the same team

		// If you reached goal
		if (x >= winCondition + 1)
			return true;
	}

	return false;
}

bool Board::CheckVertical(Vector2 t_dropIndex, Team t_droppedTeam)
{
	// Vertical Check (Positive)
	int winCondition = t_dropIndex.y + WIN_CONDITION;
	for (int y = t_dropIndex.y; y < winCondition; y++)
	{
		// Check if out of range
		if (y >= ROW_MAX)
			break;

		if (board[(int)t_dropIndex.x][y].GetTeam() != t_droppedTeam)
			break; // Not the same team

		// If you reached goal
		if (y >= winCondition - 1)
			return true;
	}

	// Vertical Check (Negative)
	winCondition = t_dropIndex.y - WIN_CONDITION;
	for (int y = t_dropIndex.y; y < winCondition; y--)
	{
		// Check if out of range
		if (y < 0)
			break;

		if (board[(int)t_dropIndex.x][y].GetTeam() != t_droppedTeam)
			break; // Not the same team

		// If you reached goal
		if (y >= winCondition + 1)
			return true;
	}

	return false;
}

bool Board::CheckDiagonal(Vector2 t_dropIndex, Team t_droppedTeam)
{
	return false;
}

void Board::FallChips()
{
	int tempX = 0;
	int tempY = 0;
	Team teamBuffer;

	for (int row = rowStart; RowLimitCheck(row); row += indexDirectionX)
	{
		for (int col = colStart; ColLimitCheck(col); col += indexDirectionY)
		{
			if (board[row][col].GetTeam() != Team::None)
			{
				tempX = row;
				tempY = col;
				teamBuffer = board[row][col].GetTeam();

				while (ValidChipPlacement(tempX + downDirection.x, tempY + downDirection.y) && board[tempX + (int)downDirection.x][tempY + (int)downDirection.y].GetTeam() == Team::None)
				{
					tempX += downDirection.x;
					tempY += downDirection.y;
				}

				board[row][col].SetTeam(Team::None);
				board[tempX][tempY].SetTeam(teamBuffer);
			}
		}
	}
}