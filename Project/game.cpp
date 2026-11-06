#include "raylib.h"
#include "game.h"

void Game::Init()
{
    board.Init();
}

void Game::Draw()
{
    DrawFPS(0, 0);
    board.Draw();
}

void Game::Update()
{
    bool placed = false;

    if (IsKeyReleased(KEY_ONE))
    {
        board.PlaceChip(0, currentPlayer);
        placed = true;
    }
    if (IsKeyReleased(KEY_TWO))
    {
        board.PlaceChip(1, currentPlayer);
        placed = true;
    }
    if (IsKeyReleased(KEY_THREE))
    {
        board.PlaceChip(2, currentPlayer);
        placed = true;

    }
    if (IsKeyReleased(KEY_FOUR))
    {
        board.PlaceChip(3, currentPlayer);
        placed = true;
    }
    if (IsKeyReleased(KEY_FIVE))
    {
        board.PlaceChip(4, currentPlayer);
        placed = true;
    }
    if (IsKeyReleased(KEY_SIX))
    {
        board.PlaceChip(5, currentPlayer);
        placed = true;
    }
    if (IsKeyReleased(KEY_SEVEN))
    {
        board.PlaceChip(6, currentPlayer);
        placed = true;
    }

    if (placed)
    {
        if (currentPlayer == Team::Red)
        {
            currentPlayer = Team::Yellow;
        }
        else if (currentPlayer == Team::Yellow)
        {
            currentPlayer = Team::Red;
        }
    }

    if (IsKeyReleased(KEY_Q))
    {
        board.Rotate();
    }

    board.Update();

    switch (currentPlayer)
    {
    case Team::Red:
        DrawText("Turn Red", GetScreenWidth() / 2.0f, 20, 20, RED);
        break;
    case Team::Yellow:
        DrawText("Turn Yellow", GetScreenWidth() / 2.0f, 20, 20, YELLOW);
        break;
    default:
        break;
    }

}
